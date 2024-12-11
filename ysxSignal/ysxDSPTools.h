#pragma once

#ifndef YSXDSPTOOLS_H
#define YSXDSPTOOLS_H

// #####################
// ####### By Sophia Cristina
// ####### Tools for the digital area of signal processing.
// ####### Like, things related to bytes, bitdepth, samples and etc...
// #####################

// ####################################################################################
// ####################################################################################
// ####################################################################################

// ############################
// ####### TOOLS #######
// ############################

/*FINDS THE BYTE ALIGNED TO BIT DEPTH AND CHANNEL INSIDE RAW PCM DATA:
Returns the aligned position of the byte inside a raw PCM data.
Inputs:
- sec: the second of the signal playback
- PlaySpeed: the speed of playback
- SampleRate: the sample rate of the file
- Channels: the number of channels in the file
- Bitdepth: the bit depth of the file
*/
uint32_t ysxSIG_ByteAlign(double Sec, double PlaySpeed, uint32_t SampleRate, uint8_t Channels, uint8_t Bitdepth)
{
    uint32_t BytesPerSample = Channels * Bitdepth / 8; // 2 * 16 / 8 = 4
    uint32_t BytesPerSec = BytesPerSample * SampleRate; // 4 * 44100 = 176400
    uint32_t Pos = (uint32_t)(Sec * PlaySpeed * BytesPerSec); // 7 * 1.5 * 176400 = 1852200
    Pos = Pos - Pos % BytesPerSample; // 1852200 - 1852200 % 4 = 1852200 - 0
    uint32_t ChanBytesPerSample = BytesPerSample / Channels; // 4 / 2 = 2
    uint32_t ChanBytesPerSec = ChanBytesPerSample * SampleRate; // 2 * 44100 = 88200
    uint32_t ChanPos = Pos % ChanBytesPerSample; // 1852200 % 2 = 0
    //uint32_t BlockPos = Pos / BytesPerSec; // 1852200 / 176400 = 10.5
    float BlockPos = (float)Pos / BytesPerSec; // 1852200 / 176400 = 10.5
    uint32_t Index = BlockPos * ChanBytesPerSec + ChanPos * Channels; // 10.5 * 88200 + 0 * 2 = 926100
    return(Index);
}

#endif // SCPARSE_
