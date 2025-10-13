#pragma once

#ifndef YSXSHA_H
#define YSXSHA_H

// #####################
// ####### By Sophia Cristina
// ####### Any SHA algorithm and SHA related stuff.
// ####### It also contains HMAC.
// #####################

/// #################################################
// REFERENCES:
// [1] https://en.wikipedia.org/wiki/SHA-2
// [2] https://qvault.io/cryptography/how-sha-2-works-step-by-step-sha-256/
// [3] https://en.wikipedia.org/wiki/HMAC
// #################################################

// ###############################################################################################################################################################################
// ###############################################################################################################################################################################
// ###############################################################################################################################################################################

// Use 'Type' enum to define the type of 'SHA' algorithm you want in the constructor, this class can do any 'SHA' type.
// Types: tSHA1, tSHA224, tSHA256, tSHA384, tSHA512, tSHA512_224 and tSHA512_256:
class ysxCRYPT_SHA
{
    uint8_t SHAType;
    bool IsFinalized;

    // Shared buffer for partial block data
    std::vector<uint8_t> Buffer;
    uint64_t LenHighTotal; // for 128-bit length support (high 64 bits)
    uint64_t LenLowTotal;
    // State: use 64-bit internal array big enough for SHA-512; for 32-bit variants we use only first 8 words.
    std::array<uint64_t, 8> State;


    // #################################################


    uint32_t rotr32(uint32_t x, unsigned s) { return((x >> s) | (x << (32 - s))); }
    uint64_t rotr64(uint64_t x, unsigned s) { return((x >> s) | (x << (64 - s))); }
    uint32_t ch32(uint32_t x, uint32_t y, uint32_t z) { return((x & y) ^ ((~x) & z)); }
    uint32_t maj32(uint32_t x, uint32_t y, uint32_t z) { return((x & y) ^ (x & z) ^ (y & z)); }
    uint64_t ch64(uint64_t x, uint64_t y, uint64_t z) { return((x & y) ^ ((~x) & z)); }
    uint64_t maj64(uint64_t x, uint64_t y, uint64_t z) { return((x & y) ^ (x & z) ^ (y & z)); }

    // Big-endian (32 / 64) functions:
    uint32_t be32(const uint8_t* p) { return((uint32_t(p[0]) << 24) | (uint32_t(p[1]) << 16) | (uint32_t(p[2]) << 8) | uint32_t(p[3])); }
    static uint64_t be64(const uint8_t* p)
    {
        return((uint64_t(p[0]) << 56) | (uint64_t(p[1]) << 48) | (uint64_t(p[2]) << 40) | (uint64_t(p[3]) << 32) | (uint64_t(p[4]) << 24) | (uint64_t(p[5]) << 16) | (uint64_t(p[6]) << 8) | uint64_t(p[7]));
    }
    void Storebe32(uint8_t* p, uint32_t v) { p[0] = uint8_t((v >> 24) & 0xFF); p[1] = uint8_t((v >> 16) & 0xFF); p[2] = uint8_t((v >> 8) & 0xFF); p[3] = uint8_t((v) & 0xFF); }
    void Storebe64(uint8_t* p, uint64_t v)
    {
        p[0] = uint8_t((v >> 56) & 0xFF); p[1] = uint8_t((v >> 48) & 0xFF); p[2] = uint8_t((v >> 40) & 0xFF); p[3] = uint8_t((v >> 32) & 0xFF);
        p[4] = uint8_t((v >> 24) & 0xFF); p[5] = uint8_t((v >> 16) & 0xFF); p[6] = uint8_t((v >> 8) & 0xFF); p[7] = uint8_t((v) & 0xFF);
    }


    // #################################################


    void InitState()
    {
        switch (SHAType)
        {
            case tSHA1:
                State[0] = 0x67452301u; State[1] = 0xEFCDAB89u;
                State[2] = 0x98BADCFEu; State[3] = 0x10325476u;
                State[4] = 0xC3D2E1F0u;
                for (int i = 5; i < 8; ++i) State[i] = 0; // remaining unused
                break;

            case tSHA224:
                State[0] = 0xC1059ED8ull; State[1] = 0x367CD507ull;
                State[2] = 0x3070DD17ull; State[3] = 0xF70E5939ull;
                State[4] = 0xFFC00B31ull; State[5] = 0x68581511ull;
                State[6] = 0x64F98FA7ull; State[7] = 0xBEFA4FA4ull;
                break;

            case tSHA256:
                State[0] = 0x6A09E667ull; State[1] = 0xBB67AE85ull;
                State[2] = 0x3C6EF372ull; State[3] = 0xA54FF53Aull;
                State[4] = 0x510E527Full; State[5] = 0x9B05688Cull;
                State[6] = 0x1F83D9ABull; State[7] = 0x5BE0CD19ull;
                break;

            case tSHA384:
                State[0] = 0xCBBB9D5DC1059ED8ull; State[1] = 0x629A292A367CD507ull;
                State[2] = 0x9159015A3070DD17ull; State[3] = 0x152FECD8F70E5939ull;
                State[4] = 0x67332667FFC00B31ull; State[5] = 0x8EB44A8768581511ull;
                State[6] = 0xDB0C2E0D64F98FA7ull; State[7] = 0x47B5481DBEFA4FA4ull;
                break;

            case tSHA512:
                State[0] = 0x6A09E667F3BCC908ull; State[1] = 0xBB67AE8584CAA73Bull;
                State[2] = 0x3C6EF372FE94F82Bull; State[3] = 0xA54FF53A5F1D36F1ull;
                State[4] = 0x510E527FADE682D1ull; State[5] = 0x9B05688C2B3E6C1Full;
                State[6] = 0x1F83D9ABFB41BD6Bull; State[7] = 0x5BE0CD19137E2179ull;
                break;

            case tSHA512_224:
                // initial values specified in FIPS 180-4
                State[0] = 0x8C3D37C819544DA2ull; State[1] = 0x73E1996689DCD4D6ull;
                State[2] = 0x1DFAB7AE32FF9C82ull; State[3] = 0x679DD514582F9FCFull;
                State[4] = 0x0F6D2B697BD44DA8ull; State[5] = 0x77E36F7304C48942ull;
                State[6] = 0x3F9D85A86A1D36C8ull; State[7] = 0x1112E6AD91D692A1ull;
                break;

            case tSHA512_256:
                State[0] = 0x22312194FC2BF72Cull; State[1] = 0x9F555FA3C84C64C2ull;
                State[2] = 0x2393B86B6F53B151ull; State[3] = 0x963877195940EABDull;
                State[4] = 0x96283EE2A88EFFE3ull; State[5] = 0xBE5E1E2553863992ull;
                State[6] = 0x2B0199FC2C85B8AAull; State[7] = 0x0EB72DDC81C52CA2ull;
                break;
        }
    }

    // Padding / length helpers
    void AddLength(size_t Size)
    {
        // Maintain a 128-bit length (high/low) counting bits
        uint64_t bits = (uint64_t(Size) << 3);
        uint64_t prev = LenLowTotal;
        LenLowTotal += bits;
        if (LenLowTotal < prev) { ++LenHighTotal; }
    }


    // #################################################


    void ProcessBlock(const uint8_t* Block)
    {
        // Dispatch depending on algorithm
        switch (SHAType)
        {
            case tSHA1:
                ProcessBlockSHA1(Block);
                break;
            case tSHA224:
            case tSHA256:
                ProcessBlockSHA256(Block);
                break;
            case tSHA384:
            case tSHA512:
            case tSHA512_224:
            case tSHA512_256:
                ProcessBlockSHA512(Block);
                break;
            default:
                break;
        }
    }

    // Block-processing implementations:
    void ProcessBlockSHA1(const uint8_t* Block)
    {
        // SHA-1 uses 32-bit words; 80-word schedule
        uint32_t w[80];
        for (int i = 0; i < 16; ++i) { w[i] = be32(Block + i * 4); }
        for (int t = 16; t < 80; ++t) { uint32_t x = w[t - 3] ^ w[t - 8] ^ w[t - 14] ^ w[t - 16]; w[t] = rotr32(x, 31); } // left rotate 1 == right rotate 31

        uint32_t a = uint32_t(State[0]), b = uint32_t(State[1]), c = uint32_t(State[2]), d = uint32_t(State[3]), e = uint32_t(State[4]);

        for (int t = 0; t < 80; ++t)
        {
            uint32_t f, k;

            if (t < 20) { f = (b & c) | ((~b) & d); k = 0x5A827999u; }
            else if (t < 40) { f = b ^ c ^ d; k = 0x6ED9EBA1u; }
            else if (t < 60) { f = (b & c) | (b & d) | (c & d); k = 0x8F1BBCDCu; }
            else { f = b ^ c ^ d; k = 0xCA62C1D6u; }
            uint32_t temp = rotr32(a, 27) + f + e + k + w[t];
            e = d; d = c;
            c = rotr32(b, 2);
            b = a; a = temp;
        }
        State[0] = uint64_t(uint32_t(State[0]) + a); State[1] = uint64_t(uint32_t(State[1]) + b);
        State[2] = uint64_t(uint32_t(State[2]) + c); State[3] = uint64_t(uint32_t(State[3]) + d);
        State[4] = uint64_t(uint32_t(State[4]) + e);
    }

    void ProcessBlockSHA256(const uint8_t* Block)
    {
        const uint32_t K[64] =
        {
            0x428A2F98u,0x71374491u,0xB5C0FBCFu,0xE9B5DBA5u,0x3956C25Bu,0x59F111F1u,0x923F82A4u,0xAB1C5ED5u,
            0xD807AA98u,0x12835B01u,0x243185BEu,0x550C7DC3u,0x72BE5D74u,0x80DEB1FEu,0x9BDC06A7u,0xC19BF174u,
            0xE49B69C1u,0xEFBE4786u,0x0FC19DC6u,0x240CA1CCu,0x2DE92C6Fu,0x4A7484AAu,0x5CB0A9DCu,0x76F988DAu,
            0x983E5152u,0xA831C66Du,0xB00327C8u,0xBF597FC7u,0xC6E00BF3u,0xD5A79147u,0x06CA6351u,0x14292967u,
            0x27B70A85u,0x2E1B2138u,0x4D2C6DFCu,0x53380D13u,0x650A7354u,0x766A0ABBu,0x81C2C92Eu,0x92722C85u,
            0xA2BFE8A1u,0xA81A664Bu,0xC24B8B70u,0xC76C51A3u,0xD192E819u,0xD6990624u,0xF40E3585u,0x106AA070u,
            0x19A4C116u,0x1E376C08u,0x2748774Cu,0x34B0BCB5u,0x391C0CB3u,0x4ED8AA4Au,0x5B9CCA4Fu,0x682E6FF3u,
            0x748F82EEu,0x78A5636Fu,0x84C87814u,0x8CC70208u,0x90BEFFFAu,0xA4506CEBu,0xBEF9A3F7u,0xC67178F2u
        };

        uint32_t w[64];
        for (int i = 0; i < 16; ++i) { w[i] = be32(Block + i * 4); }
        for (int t = 16; t < 64; ++t)
        {
            uint32_t s0 = rotr32(w[t - 15], 7) ^ rotr32(w[t - 15], 18) ^ (w[t - 15] >> 3);
            uint32_t s1 = rotr32(w[t - 2], 17) ^ rotr32(w[t - 2], 19) ^ (w[t - 2] >> 10);
            w[t] = w[t - 16] + s0 + w[t - 7] + s1;
        }

        uint32_t a = uint32_t(State[0]), b = uint32_t(State[1]),
        c = uint32_t(State[2]), d = uint32_t(State[3]),
        e = uint32_t(State[4]), f = uint32_t(State[5]),
        g = uint32_t(State[6]), h = uint32_t(State[7]);

        for (int t = 0; t < 64; ++t)
        {
            uint32_t S1 = rotr32(e, 6) ^ rotr32(e, 11) ^ rotr32(e, 25);
            uint32_t temp1 = h + S1 + ch32(e, f, g) + K[t] + w[t];
            uint32_t S0 = rotr32(a, 2) ^ rotr32(a, 13) ^ rotr32(a, 22);
            uint32_t temp2 = S0 + maj32(a, b, c);
            h = g; g = f; f = e;
            e = d + temp1;
            d = c; c = b;
            b = a; a = temp1 + temp2;
        }

        State[0] = uint64_t(uint32_t(State[0]) + a); State[1] = uint64_t(uint32_t(State[1]) + b);
        State[2] = uint64_t(uint32_t(State[2]) + c); State[3] = uint64_t(uint32_t(State[3]) + d);
        State[4] = uint64_t(uint32_t(State[4]) + e); State[5] = uint64_t(uint32_t(State[5]) + f);
        State[6] = uint64_t(uint32_t(State[6]) + g); State[7] = uint64_t(uint32_t(State[7]) + h);
    }

    void ProcessBlockSHA512(const uint8_t* Block)
    {
        const uint64_t K[80] =
        {
            0x428A2F98D728AE22ull,0x7137449123EF65CDull,0xB5C0FBCFEC4D3B2Full,0xE9B5DBA58189DBBCull,
            0x3956C25BF348B538ull,0x59F111F1B605D019ull,0x923F82A4AF194F9Bull,0xAB1C5ED5DA6D8118ull,
            0xD807AA98A3030242ull,0x12835B0145706FBEull,0x243185BE4EE4B28Cull,0x550C7DC3D5FFB4E2ull,
            0x72BE5D74F27B896Full,0x80DEB1FE3B1696B1ull,0x9BDC06A725C71235ull,0xC19BF174CF692694ull,
            0xE49B69C19EF14AD2ull,0xEFBE4786384F25E3ull,0x0FC19DC68B8CD5B5ull,0x240CA1CC77AC9C65ull,
            0x2DE92C6F592B0275ull,0x4A7484AA6EA6E483ull,0x5CB0A9DCBD41FBD4ull,0x76F988DA831153B5ull,
            0x983E5152EE66DFABull,0xA831C66D2DB43210ull,0xB00327C898FB213Full,0xBF597FC7BEEF0EE4ull,
            0xC6E00BF33DA88FC2ull,0xD5A79147930AA725ull,0x06CA6351E003826Full,0x142929670A0E6E70ull,
            0x27B70A8546D22FFCull,0x2E1B21385C26C926ull,0x4D2C6DFC5AC42AEDull,0x53380D139D95B3DFull,
            0x650A73548BAF63DEull,0x766A0ABB3C77B2A8ull,0x81C2C92E47EDAEE6ull,0x92722C851482353Bull,
            0xA2BFE8A14CF10364ull,0xA81A664BBC423001ull,0xC24B8B70D0F89791ull,0xC76C51A30654BE30ull,
            0xD192E819D6EF5218ull,0xD69906245565A910ull,0xF40E35855771202Aull,0x106AA07032BBD1B8ull,
            0x19A4C116B8D2D0C8ull,0x1E376C085141AB53ull,0x2748774CDF8EEB99ull,0x34B0BCB5E19B48A8ull,
            0x391C0CB3C5C95A63ull,0x4ED8AA4AE3418ACBull,0x5B9CCA4F7763E373ull,0x682E6FF3D6B2B8A3ull,
            0x748F82EE5DEFB2FCull,0x78A5636F43172F60ull,0x84C87814A1F0AB72ull,0x8CC702081A6439ECull,
            0x90BEFFFA23631E28ull,0xA4506CEBDE82BDE9ull,0xBEF9A3F7B2C67915ull,0xC67178F2E372532Bull,
            0xCA273ECEEA26619Cull,0xD186B8C721C0C207ull,0xEADA7DD6CDE0EB1Eull,0xF57D4F7FEE6ED178ull,
            0x06F067AA72176FBAull,0x0A637DC5A2C898A6ull,0x113F9804BEF90DAEull,0x1B710B35131C471Bull,
            0x28DB77F523047D84ull,0x32CAAB7B40C72493ull,0x3C9EBE0A15C9BEBCull,0x431D67C49C100D4Cull,
            0x4CC5D4BECB3E42B6ull,0x597F299CFC657E2Aull,0x5FCB6FAB3AD6FAECull,0x6C44198C4A475817ull
        };

        uint64_t w[80];
        for (int i = 0; i < 16; ++i) { w[i] = be64(Block + i * 8); }
        for (int t = 16; t < 80; ++t)
        {
            uint64_t s0 = rotr64(w[t - 15], 1) ^ rotr64(w[t - 15], 8) ^ (w[t - 15] >> 7);
            uint64_t s1 = rotr64(w[t - 2], 19) ^ rotr64(w[t - 2], 61) ^ (w[t - 2] >> 6);
            w[t] = w[t - 16] + s0 + w[t - 7] + s1;
        }

        uint64_t a = State[0], b = State[1],
        c = State[2], d = State[3],
        e = State[4], f = State[5],
        g = State[6], h = State[7];

        for (int t = 0; t < 80; ++t)
        {
            uint64_t S1 = rotr64(e, 14) ^ rotr64(e, 18) ^ rotr64(e, 41);
            uint64_t temp1 = h + S1 + ch64(e, f, g) + K[t] + w[t];
            uint64_t S0 = rotr64(a, 28) ^ rotr64(a, 34) ^ rotr64(a, 39);
            uint64_t temp2 = S0 + maj64(a, b, c);
            h = g; g = f; f = e;
            e = d + temp1;
            d = c; c = b; b = a;
            a = temp1 + temp2;
        }

        // add working variables back into state (single addition each)
        State[0] = State[0] + a; State[1] = State[1] + b;
        State[2] = State[2] + c; State[3] = State[3] + d;
        State[4] = State[4] + e; State[5] = State[5] + f;
        State[6] = State[6] + g; State[7] = State[7] + h;
    }


    // #################################################


    void PadAndProcess()
    {
        size_t bs = BlockSize();
        std::vector<uint8_t> tmp;
        tmp.reserve(((Buffer.size() + bs + 16) / bs) * bs);

        // copy buffered bytes
        size_t CurrentLen = Buffer.size();
        tmp.insert(tmp.end(), Buffer.begin(), Buffer.end());

        // append 0x80
        tmp.push_back(0x80u);

        // length field size (bytes): 8 for SHA-1/SHA-224/SHA-256, 16 for SHA-384/SHA-512 variants
        size_t LenFieldSize = (SHAType == tSHA1 || SHAType == tSHA224 || SHAType == tSHA256) ? 8 : 16;

        // compute zero padding so that (message + 1 + pad + length_field) % bs == 0
        size_t mod = (CurrentLen + 1) % bs;
        size_t PadZeroes;
        if (mod <= bs - LenFieldSize) { PadZeroes = (bs - LenFieldSize) - mod; }
        else { PadZeroes = (bs - LenFieldSize) + (bs - mod); }
        tmp.insert(tmp.end(), PadZeroes, 0);

        // append length field (big-endian). LenLowTotal/high already contain bit-count.
        if (LenFieldSize == 8)
        {
            uint8_t LenField[8];
            // append low 64 bits of bit-length (SHA-256/SHA-1 expect 64-bit BE length)
            Storebe64(LenField, LenLowTotal);
            tmp.insert(tmp.end(), LenField, LenField + 8);
        }
        else
        {
            uint8_t len128[16];
            // append high 64 bits then low 64 bits of bit-length (big-endian 128-bit)
            Storebe64(len128, LenHighTotal);
            Storebe64(len128 + 8, LenLowTotal);
            tmp.insert(tmp.end(), len128, len128 + 16);
        }

        // process all resulting blocks
        const uint8_t* p = tmp.data();
        size_t n = tmp.size() / bs;
        for (size_t i = 0; i < n; ++i) { ProcessBlock(p + i * bs); }
        Buffer.clear();
    }


    // #################################################
    // #################################################
    // #################################################


public:
    enum Type { tSHA1, tSHA224, tSHA256, tSHA384, tSHA512, tSHA512_224, tSHA512_256 };

    // Return digest size in bytes for current Type:
    size_t DigestSize()
    {
        switch (SHAType)
        {
            case tSHA1:
                return(20);
            case tSHA224:
                return(28);
            case tSHA256:
                return(32);
            case tSHA384:
                return(48);
            case tSHA512:
                return(64);
            case tSHA512_224:
                return(28);
            case tSHA512_256:
                return(32);
            default:
                return(0);
        }
    }

    // Return block size in bytes for current Type:
    size_t BlockSize()
    {
        switch (SHAType)
        {
            case tSHA1:
            case tSHA224:
            case tSHA256:
                return(64); // 512-bit blocks
            case tSHA384:
            case tSHA512:
            case tSHA512_224:
            case tSHA512_256:
                return(128); // 1024-bit blocks
            default:
                return(0);
        }
    }

    // Feed data to the hash. After this process, run 'HexDigest()' to get your final hash return which can be used somewhere else:
    void Update(const void* Data, std::size_t Size)
    {
        if (Size == 0) { return; }
        if (IsFinalized) { throw std::runtime_error("ERROR: 'Update()' called after 'Finalize()', which leads to IsFinalized = true. Use 'Reset()' before new process!"); }

        const uint8_t* p = static_cast<const uint8_t*>(Data);
        std::size_t bs = BlockSize();
        AddLength(Size);

        // Fill buffer if there is already partial data
        if (Buffer.size() > 0)
        {
            std::size_t Need = bs - Buffer.size();
            if (Size < Need) { Need = Size; }
            Buffer.insert(Buffer.end(), p, p + Need);
            p += Need;
            Size -= Need;
            if (Buffer.size() == bs)
            {
                ProcessBlock(Buffer.data());
                Buffer.clear();
            }
        }

        while (Size >= bs) { ProcessBlock(p); p += bs; Size -= bs; }
        if (Size) { Buffer.insert(Buffer.end(), p, p + Size); }

    }

    // Finalize computation (idempotent). After finalize, HexDigest() is available:
    void Finalize() { if (IsFinalized) { return; } PadAndProcess(); IsFinalized = true; }

    // Get rwa binary digest vector. 'Finalize()' is called implicitly if needed:
    std::vector<uint8_t> Digest()
    {
        if (!IsFinalized) { Finalize(); }

        std::size_t ds = DigestSize(); // produce digest bytes per algorithm
        std::vector<uint8_t> Out; Out.reserve(ds);

        if (SHAType == tSHA1)
        {
            for (int i = 0; i < 5; ++i)
            {
                uint32_t v = uint32_t(State[i]);
                uint8_t b[4];
                Storebe32(b, v);
                Out.insert(Out.end(), b, b + 4);
            }
        }
        else if (SHAType == tSHA224 || SHAType == tSHA256)
        {
            for (int i = 0; i < 8; ++i)
            {
                uint32_t v = uint32_t(State[i]);
                uint8_t b[4];
                Storebe32(b, v);
                Out.insert(Out.end(), b, b + 4);
            }
            if (SHAType == tSHA224) { Out.resize(28); }
            else { Out.resize(32); }
        }
        else // SHA-512 family
        {
            for (int i = 0; i < 8; ++i)
            {
                uint64_t v = State[i];
                uint8_t b[8];
                Storebe64(b, v);
                Out.insert(Out.end(), b, b + 8);
            }
            if (SHAType == tSHA384) { Out.resize(48); }
            else if (SHAType == tSHA512_224) { Out.resize(28); }
            else if (SHAType == tSHA512_256) { Out.resize(32); }
            else { Out.resize(64); }
        }

        return(Out);
    }

    // Get lowercase hex digest string. 'Finalize()' is called implicitly if needed:
    std::string HexDigest()
    {
        std::vector<uint8_t> Out = Digest();
        // Lowercase hex digest:
        //std::string HexLower(const uint8_t* Data, std::size_t Size)
        //{
            std::ostringstream oss;
            oss << std::hex << std::setfill('0');
            for (std::size_t i = 0; i < Out.size(); ++i)
            {
                oss << std::setw(2) << (int(Out[i]) & 0xFF);
            }
           // return(oss.str());
        //}
        //return(HexLower(Out.data(), Out.size()));
        return(oss.str());
    }

    // Reset internal state to start a new hash of the same 'SHAType':
    void Reset()
    {
        Buffer.clear();
        LenHighTotal = 0; LenLowTotal = 0;
        IsFinalized = false;
        for (uint64_t n = 0; n < 8; ++n) { State[n] = 0; }
        InitState();
    }

    // Main function, this will call 'Update()' and 'HexDigest()' with implicit 'Finalize()' function and then 'Reset()' at the end:
    std::string ComputeHex(std::string msg)
    {
        Update(msg.data(), msg.size());
        std::string Ret = HexDigest();
        Reset();
        return(Ret);
    }

    // Equal to 'ComputeHex(std::string)', but returns 'vector<uint8_t>' with raw binary:
    std::vector<uint8_t> ComputeRaw(std::string msg)
    {
        Update(msg.data(), msg.size());
        std::vector<uint8_t> Ret = Digest();
        Reset();
        return(Ret);
    }


    // #################################################


    ysxCRYPT_SHA(uint8_t SetSHAType = tSHA256)
    {
        SHAType = SetSHAType; IsFinalized = false; Buffer.clear(); LenHighTotal = 0; LenLowTotal = 0;
        for (uint64_t n = 0; n < 8; ++n) { State[n] = 0; }
        Reset();
    }
    ~ysxCRYPT_SHA() {};
};


// #################################################
// #################################################
// #################################################


class ysxCRYPT_HMAC
{
    uint8_t SHAType;
    std::vector<uint8_t> Key;
    std::unique_ptr<ysxCRYPT_SHA> InnerSHA;

public:
    ysxCRYPT_HMAC(uint8_t SetSHAType, const std::vector<uint8_t>& SetKey)
    {
        SHAType = SetSHAType;
        Key = SetKey;
        ysxCRYPT_SHA sha(SetSHAType);
        std::size_t BlockSize = sha.BlockSize();

        std::vector<uint8_t> KeyCopy = Key; // make local copy because we may modify it

        // If key is longer than BlockSize, shorten it by hashing
        if (KeyCopy.size() > BlockSize)
        {
            ysxCRYPT_SHA tmp(SetSHAType);
            tmp.Update(KeyCopy.data(), KeyCopy.size());
            KeyCopy = tmp.Digest(); // raw bytes
        }

        // Pad key to block size
        Key.assign(BlockSize, 0);
        std::copy(KeyCopy.begin(), KeyCopy.end(), Key.begin());

        // Initialize inner state immediately
        Reset();
    }

    void Update(const void* Data, std::size_t Size)
    {
        InnerSHA->Update(Data, Size);
    }

    std::vector<uint8_t> Digest()
    {
        // Finish inner hash
        std::vector<uint8_t> InnerDigest = InnerSHA->Digest();

        // Prepare outer hash with (K ⊕ opad)
        std::vector<uint8_t> OuterPad(Key);
        for (auto& b : OuterPad) { b ^= 0x5c; }

        ysxCRYPT_SHA m_outer(SHAType);
        m_outer.Update(OuterPad.data(), OuterPad.size());
        m_outer.Update(InnerDigest.data(), InnerDigest.size());

        return(m_outer.Digest()); // final raw vector
    }

    std::string HexDigest()
    {
        std::vector<uint8_t> InnerDigest = InnerSHA->Digest();
        std::vector<uint8_t> OuterPad(Key);
        for (auto& b : OuterPad) { b ^= 0x5c; }

        ysxCRYPT_SHA m_outer(SHAType);
        m_outer.Update(OuterPad.data(), OuterPad.size());
        m_outer.Update(InnerDigest.data(), InnerDigest.size());

        return(m_outer.HexDigest()); // final hex string
    }

    // One-shot convenience
    std::string ComputeHex(const std::string& msg)
    {
        Reset(); // start fresh
        Update(msg.data(), msg.size());
        std::string ret = HexDigest();
        Reset(); // ready for reuse
        return(ret);
    }

    std::vector<uint8_t> ComputeRaw(const std::string& msg)
    {
        Reset(); // start fresh
        Update(msg.data(), msg.size());
        std::vector<uint8_t> ret = Digest();
        Reset(); // ready for reuse
        return(ret);
    }

    void Reset()
    {
        // Prepare inner hash with (K ⊕ ipad)
        std::vector<uint8_t> InnerPad(Key);
        for (auto& b : InnerPad) { b ^= 0x36; }

        InnerSHA.reset(new ysxCRYPT_SHA(SHAType));
        InnerSHA->Update(InnerPad.data(), InnerPad.size());
    }
};


// #################################################
// #################################################
// #################################################


#endif
