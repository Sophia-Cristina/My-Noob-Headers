#pragma once

#ifndef YSXCRYPTO_H
#define YSXCRYPTO_H

#include <bit>

// #####################
// ####### By Sophia Cristina
// ####### For anything related to cryptography.
// ####### Even coins and blockchains.
// #####################

// ############################################################################################################################################
// ################################################# ANOTATIONS AND ALTERATIONS #################################################
// 	
// 	CHANGES (KEEP ORDER):
// 	* Use only 'unsigned long' for 4-bit integer, so this header elements wouldn't give problems when compiler sees 'int' objects as 2-bytes size (like in MS-DOS);
// 	
// ################################################# ANOTATIONS AND ALTERATIONS #################################################
// ############################################################################################################################################

// #################################################
// REFERENCES:
// [1] https://en.wikipedia.org/wiki/SHA-2
/*   - Note 1: All variables are 32 bit unsigned integers and addition is calculated modulo 232
	   Note 2: For each round, there is one round constant k[i] and one entry in the message schedule array w[i], 0 <= i <= 63
	   Note 3: The compression function uses 8 working variables, a through h
	   Note 4: Big-endian convention is used when expressing the constants in this pseudocode,
	   and when parsing message block data from bytes to words, for example,
	   the first word of the input message "abc" after padding is 0x61626380.

       PRE-PROCESSING (PADDING):
	   begin with the original message of length L bits;
	   append a single '1' bit;
	   append K '0' bits, where K is the minimum number >= 0 such that L + 1 + K + 64 is a multiple of 512;
	   append L as a 64-bit big-endian integer, making the total post-processed length a multiple of 512 bits;
	   such that the bits in the message are L 1 00..<K 0's>..00 <L as 64 bit integer> = k*512 total bits;
*/
// [2] https://qvault.io/cryptography/how-sha-2-works-step-by-step-sha-256/
// #################################################

// ###############################################################################################################################################################################
// ###############################################################################################################################################################################
// ###############################################################################################################################################################################

class SHA256
{
public:
	// INITIALIZE HASH VALUES:
	// (first 32 bits of the fractional parts of the square roots of the first 8 primes 2..19):
	const unsigned long Hashes[8] = { 0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19 };

	// INITIALIZE ARRAY OF ROUND CONSTANTS:
	// (first 32 bits of the fractional parts of the cube roots of the first 64 primes 2..311):
	const unsigned long k[64] =
	{
		0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
		0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
		0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
		0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
		0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
		0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
		0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
		0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
	};

	/* Process the message in successive 512-bit chunks:
	   break message into 512-bit chunks, for each chunk, create a 64-entry message schedule array w[0..63] of 32-bit words
	   (The initial values in w[0..63] don't matter, so many implementations zero them here).
	   Copy chunk into first 16 words w[0..15] of the message schedule array. */

	/* Extend the first 16 words into the remaining 48 words w[16..63] of the message schedule array:
	   for i from 16 to 63
	   s0 := (w[i-15] rightrotate  7) xor (w[i-15] rightrotate 18) xor (w[i-15] rightshift  3)
	   s1 := (w[i- 2] rightrotate 17) xor (w[i- 2] rightrotate 19) xor (w[i- 2] rightshift 10)
	   w[i] := w[i-16] + s0 + w[i-7] + s1; */
	
	void DoHashing(std::string Chunk)
	{
		unsigned long w[64];
		unsigned long s0 = 0, s1 = 0;
		//memcpy(w, &Chunk[0], Chunk.size() - 1);
		for (char n = 0; n < 64; ++n)
		{
			w[n] = 0; // !!!
			if (n < 16)
			{
				for (unsigned char Byte = 0; Byte < 4; ++Byte)
				{
					w[n] += (unsigned long)Chunk[Byte + n * 4] * pow(16, (3 - Byte) * 2); // 16^0 to 16^6
				}
			}
			else
			{
				//s0 = (w[n - 15] rightrotate 7) ^ (w[n - 15] rightrotate 18) ^ (w[n - 15] rightshift 3);
				//s1 = (w[n - 2] rightrotate 17) ^ (w[n - 2] rightrotate 19) ^ (w[n - 2] rightshift 10);
				w[n] = w[n - 16] + s0 + w[n - 7] + s1;
			}
		}

		//for (unsigned long i = 16; i < 64; ++i)
		//{

		//}
		std::cout << "W[]:\n";
		for (int n = 0; n < 64; ++n)
		{
			std::cout << "| w[" << n << "] = " <<  w[n] << ' ';
			if (n % 4 == 3) { std::cout << std::endl; }
		}
		std::cout << '\n';
	}


	// Message should have a size under 57 Bytes:
	SHA256(std::string Message, bool LittleBig)
	{
		if (Message.size() < 57)
		{
			size_t Size = Message.size();
			/*if (!LittleBig)
			{
				std::string Invert;
				for (size_t n = 0; n < Size; ++n)
				{
					Invert.push_back(Message[Size - 1 - n]);
				}
				Message = Invert;
			}*/
			// PADDING:
			unsigned long Ini = Size;
			//unsigned long HSize = ceil(((float)Message.size() / 512)); // 'H'ash 'Size', in case the message is bigger than our chunck block
			unsigned long HSize = 1; // !!! MAYBE LATER: i'm going to do SHA-N and you can choose any 'N' you want, or maybe only multiples of '2^n'!!!
			Message += 128;
			unsigned short End = (HSize * 64 - Size) - 2; // '-1' in the end, because the last byte is the 'message size' value (Ini * 8)
			for (int n = 0; n < End; ++n)
			{
				Message += (char)0;
			}
			Message += Ini * 8; // Initial string size is appended // !!! REMEMBER: '* 8', this means, no message above size 31 !!!
			if (!LittleBig) // ENDIAN
			{
				std::string Invert;
				for (size_t n = 0; n < Size; ++n)
				{
					Invert.push_back(Message[Size - 1 - n]);
				}
				Message = Invert;
			}
			std::cout << "TEST:\n";
			for (int n = 0; n < Size; ++n)
			{
				std::cout << (unsigned long)Message[n] << " ";
			}
			std::cout << "\n---\n";
			DoHashing(Message);
			std::cout << "\n\n---\n\n";
		}
		else { std::cout << "Use a 'Message' with size lower than '57'!\n"; }
	}

	~SHA256()
	{
	}
};

// ###############################################################################################################################################################################
// ####### MAIN #################################################################################################################################################################
// ###############################################################################################################################################################################

#endif // SCPARSE_