#pragma once

#ifndef YSXWINAUDIO_H
#define YSXWINAUDIO_H

#include "ysxData/Files/ysxWAVE.h"

//#include "Audioclient.h" // https://docs.microsoft.com/en-us/windows/desktop/api/_coreaudio/

// To develop Core Audio APIs, you need these headers:
//#include "audioclient.h"
//#include "audioendpoints.h"
//#include "audioenginebaseapo.h"
//#include "audioengineendpoint.h"
//#include "audiopolicy.h"
//#include "audiosessiontypes.h"
//#include "devicetopology.h"
//#include "endpointvolume.h"
#include "mmdeviceapi.h"
//#include "mmeapi.h"
//#include "spatialaudioclient.h"
//#include "spatialaudiohrtf.h"
//#include "spatialaudiometadata.h"
#include <MMSystem.h>
#include <amstream.h>

// #####################
// ####### By Sophia Cristina
// #######
// #####################

// #################################################
// REFERENCES:
// [1] https://docs.microsoft.com/en-us/windows/win32/api/_coreaudio/
// [2] https://docs.microsoft.com/en-us/windows/win32/coreaudio/programming-reference
// [3] https://docs.microsoft.com/en-us/windows/win32/coreaudio/programming-guide
// [4] https://docs.microsoft.com/en-us/windows/win32/coreaudio/core-audio-interfaces
// [5] https://docs.microsoft.com/en-us/windows/win32/coreaudio/mmdevice-api
// [6] https://docs.microsoft.com/en-us/previous-versions/dd743680(v=vs.85) // PLAYSOUND
// BOOL PlaySound(LPCTSTR pszSound, HMODULE hmod, DWORD fdwSound);
// * pszSound
// The sound to play. The maximum length, including the null terminator, is 256 characters. If this parameter is NULL, any currently playing waveform sound is stopped.
// Three flags in fdwSound(SND_ALIAS, SND_FILENAME, and SND_RESOURCE) determine whether the name is interpreted as an alias for a system event, a file name, or a resource identifier.
// If none of these flags are specified, PlaySound searches the registry or the WIN.INI file for an association with the specified sound name.
// If an association is found, the sound event is played. If no association is found in the registry, the name is interpreted as a file name.

// * hmod
// Handle to the executable file that contains the resource to be loaded.This parameter must be NULL unless SND_RESOURCE is specified in fdwSound.

// * fdwSound
// Flags for playing the sound. The following values are defined:
/*
* SND_APPLICATION:
	The pszSound parameter is an application - specific alias in the registry.You can combine this flag with the SND_ALIAS or SND_ALIAS_ID flag to specify an application - defined sound alias.
* SND_ALIAS:
	The pszSound parameter is a system - event alias in the registry or the WIN.INI file. Do not use with either SND_FILENAME or SND_RESOURCE.
* SND_ALIAS_ID:
	The pszSound parameter is a predefined identifier for a system - event alias.See Remarks.
* SND_ASYNC:
	The sound is played asynchronously and PlaySound returns immediately after beginning the sound.
	To terminate an asynchronously played waveform sound, call PlaySound with pszSound set to NULL.
	!!! If you combine the SND_MEMORY and SND_ASYNC flags, the memory buffer that contains the sound must remain valid until the sound has completed playing !!!
* SND_FILENAME:
	The pszSound parameter is a file name.If the file cannot be found, the function plays the default sound unless the SND_NODEFAULT flag is set.
* SND_LOOP:
	The sound plays repeatedly until PlaySound is called again with the pszSound parameter set to NULL.If this flag is set, you must also set the SND_ASYNC flag.
* SND_MEMORY:
	The pszSound parameter points to a sound loaded in memory.
	For more information, see Playing WAVE Resources.
* SND_NODEFAULT:
	No default sound event is used.If the sound cannot be found, PlaySound returns silently without playing the default sound.
* SND_NOSTOP:
	The specified sound event will yield to another sound event that is already playing in the same process. If a sound cannot be played because the resource needed to generate that sound
	is busy playing another sound, the function immediately returns FALSE without playing the requested sound.
	If this flag is not specified, PlaySound attempts to stop any sound that is currently playing in the same process. Sounds played in other processes are not affected.
* SND_NOWAIT:
	Not supported.
	!!! Note: Previous versions of the documentation implied incorrectly that this flag is supported. The function ignores this flag !!!
* SND_PURGE:
	Not supported.
* SND_RESOURCE:
	The pszSound parameter is a resource identifier; hmod must identify the instance that contains the resource.
	For more information, see Playing WAVE Resources.
* SND_SENTRY:
	Note  Requires Windows Vista or later.
	If this flag is set, the function triggers a SoundSentry event when the sound is played.
	SoundSentry is an accessibility feature that causes the computer to display a visual cue when a sound is played.
	If the user did not enable SoundSentry, the visual cue is not displayed.
* SND_SYNC:
	The sound is played synchronously, and PlaySound returns after the sound event completes. This is the default behavior.
* SND_SYSTEM:
	Note Requires Windows Vista or later.
	If this flag is set, the sound is assigned to the audio session for system notification sounds. The system volume - control program (SndVol)
	displays a volume slider that controls system notification sounds.Setting this flag puts the sound under the control of that volume slider.
	If this flag is not set, the sound is assigned to the default audio session for the application's process.
*/

/*
If the SND_ALIAS_ID flag is specified in fdwSound, the pszSound parameter must be one of the following values:
SND_ALIAS_SYSTEMASTERISK:	 "SystemAsterisk";
SND_ALIAS_SYSTEMDEFAULT:	 "SystemDefault";
SND_ALIAS_SYSTEMEXCLAMATION: "SystemExclamation";
SND_ALIAS_SYSTEMEXIT:		 "SystemExit";
SND_ALIAS_SYSTEMHAND:		 "SystemHand";
SND_ALIAS_SYSTEMQUESTION:	 "SystemQuestion";
SND_ALIAS_SYSTEMSTART:		 "SystemStart";
SND_ALIAS_SYSTEMWELCOME:	 "SystemWelcome";
*/

// [7] https://docs.microsoft.com/pt-br/windows/win32/multimedia/devices-and-data-types
/*
auxGetNumDevs:	   Retrieves the number of auxiliary output devices present in the system.
waveInGetNumDevs:  Retrieves the number of waveform - audio input devices present in the system.
waveOutGetNumDevs: Retrieves the number of waveform - audio output devices present in the system.

Device Handles and Device Identifiers:
Each function that opens an audio device specifies a device identifier, a pointer to a memory location,
and some parameters that are unique to each type of device. The memory location is filled with a device handle.
Use this device handle to identify the open audio device when calling other audio functions.
The difference between identifiers and handles for audio devices is subtle but important:
	* Device identifiers are determined implicitly from the number of devices present in a system.
	  This number is obtained by using the auxGetNumDevs, waveInGetNumDevs, or waveOutGetNumDevs function.
	* Device handles are returned when device drivers are opened by using the waveInOpen or waveOutOpen function.
There are no functions that open or close auxiliary audio devices. Auxiliary audio devices need not be opened and closed like waveform-audio devices because there is no continuous data transfer associated with them. All auxiliary audio functions use device identifiers to identify devices.
*/

/* [8] https://docs.microsoft.com/en-us/windows/win32/api/mmeapi/nf-mmeapi-waveoutgetdevcaps
MMRESULT waveOutGetDevCaps(UINT uDeviceID, LPWAVEOUTCAPS pwoc, UINT cbwoc);
uDeviceID: Identifier of the waveform - audio output device.It can be either a device identifier or a handle of an open waveform - audio output device.
pwoc: Pointer to a WAVEOUTCAPS structure to be filled with information about the capabilities of the device.
cbwoc: Size, in bytes, of the WAVEOUTCAPS structure.
*/

// [9] https://docs.microsoft.com/en-us/windows/win32/directshow/audio-streaming-sample-code // !!!!!!! SAMPLE CODE !!!!!!!
// [10] https://docs.microsoft.com/en-us/windows/win32/api/mmeapi/nf-mmeapi-waveoutopen // WAVEOUT
// [11] https://docs.microsoft.com/en-us/windows/win32/multimedia/using-waveform-and-auxiliary-audio
//	   [1] https://docs.microsoft.com/en-us/windows/win32/multimedia/using-the-waveformatex-structure
/*	   [2] https://docs.microsoft.com/en-us/windows/win32/api/mmeapi/ns-mmeapi-waveformatex
	   Formats that support more than two channels or sample sizes of more than 16 bits can be described in a WAVEFORMATEXTENSIBLE structure, which includes the WAVEFORMAT structure.
	   typedef struct tWAVEFORMATEX { WORD wFormatTag; WORD nChannels; DWORD nSamplesPerSec; DWORD nAvgBytesPerSec; WORD nBlockAlign; WORD wBitsPerSample; WORD cbSize; }
	   WAVEFORMATEX, *PWAVEFORMATEX, *NPWAVEFORMATEX, *LPWAVEFORMATEX;

	   nSamplesPerSec: For non-PCM formats, this member must be computed according to the manufacturer's specification of the format tag;
	   nAvgBytesPerSec: Should be equal to the product of nSamplesPerSec and nBlockAlign;
	   cbSize: Size, in bytes, of extra format information appended to the end of the WAVEFORMATEX structure.
			   This information can be used by non-PCM formats to store extra attributes for the wFormatTag.
			   If no extra information is required by the wFormatTag, this member must be set to 0.
			   For WAVE_FORMAT_PCM formats (and only WAVE_FORMAT_PCM formats), this member is ignored.
			   When this structure is included in a WAVEFORMATEXTENSIBLE structure, this value must be at least 22.
*/
// [12] https://docs.microsoft.com/en-us/windows/win32/multimedia/waveform-functions
// [13] https://docs.microsoft.com/en-us/windows/win32/multimedia/example-of-writing-waveform-data // WAVEHDR
/*	   [1] https://docs.microsoft.com/en-us/windows/win32/api/mmeapi/ns-mmeapi-wavehdr
typedef struct wavehdr_tag
{
	LPSTR lpData; // Pointer to the waveform buffer
	DWORD dwBufferLength; // Length, in bytes, of the buffer
	DWORD dwBytesRecorded; // When the header is used in input, specifies how much data is in the buffer
	DWORD_PTR dwUser; // User data
	DWORD dwFlags; // A bitwise OR of zero of more flags. Check flags below!
	DWORD dwLoops; // Number of times to play the loop. This member is used only with output buffers.
	struct wavehdr_tag* lpNext; // Reserved
	DWORD_PTR reserved;
} WAVEHDR, * PWAVEHDR, * NPWAVEHDR, * LPWAVEHDR;

FLAGS:
WHDR_BEGINLOOP: This buffer is the first buffer in a loop. This flag is used only with output buffers.
WHDR_DONE: Set by the device driver to indicate that it is finished with the buffer and is returning it to the application.
WHDR_ENDLOOP: This buffer is the last buffer in a loop. This flag is used only with output buffers.
WHDR_INQUEUE: Set by Windows to indicate that the buffer is queued for playback.
WHDR_PREPARED: Set by Windows to indicate that the buffer has been prepared with the waveInPrepareHeader or waveOutPrepareHeader function.

REMARKS:
Use the WHDR_BEGINLOOP and WHDR_ENDLOOP flags in the dwFlags member to specify the beginning and ending data blocks for looping.
To loop on a single block, specify both flags for the same block. Use the dwLoops member in the WAVEHDR structure for the first
block in the loop to specify the number of times to play the loop.

The lpData, dwBufferLength, and dwFlags members must be set before calling the waveInPrepareHeader or waveOutPrepareHeader function
(for either function, the dwFlags member must be set to zero).
*/
/* [14] https://docs.microsoft.com/en-us/previous-versions/dd743868(v=vs.85) // PREPARE HEADER
MMRESULT waveOutPrepareHeader(HWAVEOUT hwo, LPWAVEHDR pwh, UINT cbwh);
pwh: Pointer to a WAVEHDR structure that identifies the data block to be prepared.
cbwh: Size, in bytes, of the WAVEHDR structure.

Returns MMSYSERR_NOERROR if successful or an error otherwise. Possible error values include the following:
MMSYSERR_INVALHANDLE: Specified device handle is invalid;
MMSYSERR_NODRIVER: No device driver is present;
MMSYSERR_NOMEM: Unable to allocate or lock memory.

REMARKS:
Set the lpData, dwBufferLength, and dwFlags members of the WAVEHDR structure before calling this function. Set the dwFlags member to zero.
The dwFlags, dwBufferLength, and dwLoops members of the WAVEHDR structure can change between calls to this function and the waveOutWrite function.
If you change the size specified by dwBufferLength before the call to waveOutWrite, the new value must be less than the prepared value.
If the method succeeds, the WHDR_PREPARED flag is set in the dwFlags member of the WAVEHDR structure.
Preparing a header that has already been prepared has no effect, and the function returns zero.
*/
/* [15] https://docs.microsoft.com/en-us/windows/win32/api/mmeapi/nf-mmeapi-waveoutwrite // sends a data block to the given waveform-audio output device.
MMRESULT waveOutWrite(HWAVEOUT hwo, LPWAVEHDR pwh, UINT cbwh);

REMARKS:
When the buffer is finished, the WHDR_DONE bit is set in the dwFlags member of the WAVEHDR structure.
The buffer must be prepared with the waveOutPrepareHeader function before it is passed to waveOutWrite.
Unless the device is paused by calling the waveOutPause function, playback begins when the first data block is sent to the device.
*/

// [16] https://docs.microsoft.com/en-us/windows/win32/multimedia/processing-the-mm-wom-done-message // with sample code

// XAUDIO2:
// [x1] https://docs.microsoft.com/en-us/windows/win32/xaudio2/programming-guide

// MMDEVICE API:
// [m1] https://docs.microsoft.com/en-us/windows/win32/coreaudio/mmdevice-api
// [m2] https://docs.microsoft.com/en-us/windows/win32/api/mmdeviceapi/nf-mmdeviceapi-immdevicecollection-item
// [m3] https://docs.microsoft.com/en-us/windows/win32/coreaudio/rendering-a-stream
// #################################################

// ###############################################################################################################################################################################

// CALLBACK WAVE:
void CALLBACK WaveCallback(HWAVEOUT hWave, UINT uMsg, DWORD dwUser,	DWORD dw1, DWORD dw2)
{
	if (uMsg == WOM_DONE) { ReleaseSemaphore((HANDLE)dwUser, 1, NULL); }
	if (uMsg == WOM_DONE) { ReleaseSemaphore((HANDLE)dwUser, 1, NULL); }
	if (uMsg == WOM_DONE) { ReleaseSemaphore((HANDLE)dwUser, 1, NULL); }
}

// PLAY SOUND (SND_ASYNC), USE L"":
void PlaySnd(std::wstring FileName) { PlaySound(FileName.data(), NULL, SND_ASYNC); }

// STOP SOUND:
void StopSound() { PlaySound(NULL, 0, 0); }

// SET WAVEFORMAT [11][1]:
// * Format tag is set as WAVE_FORMAT_PCM
WAVEFORMATEX SetWaveFmt(unsigned short Channels, unsigned int SampleRate, unsigned int BytesPerSec, unsigned short BlockAlign, unsigned short BitsPerSample)
{
	WAVEFORMATEX Wave;
	Wave.wFormatTag = WAVE_FORMAT_PCM;
	Wave.nChannels = Channels;
	Wave.nSamplesPerSec = SampleRate;
	Wave.nAvgBytesPerSec = BytesPerSec;
	Wave.nBlockAlign = BlockAlign;
	Wave.wBitsPerSample = BitsPerSample;
	Wave.cbSize = 0; // If no extra information is required by the wFormatTag, this member must be set to 0.
					 // For WAVE_FORMAT_PCM formats (and only WAVE_FORMAT_PCM formats), this member is ignored.	
	return (Wave);
}
WAVEFORMATEX SetWaveFmt(std::string FileName)
{
	WAVEFORMATEX Wave;
	ysxWAV_File File(FileName);
	Wave.wFormatTag = WAVE_FORMAT_PCM;
	Wave.nChannels = File.FMT.Channels;
	Wave.nSamplesPerSec = File.FMT.SRate;
	Wave.nAvgBytesPerSec = File.FMT.ByteRate;
	Wave.nBlockAlign = File.FMT.BlockAlign;
	Wave.wBitsPerSample = File.FMT.BitsPerSample;
	Wave.cbSize = 0;
	return (Wave);
}
WAVEFORMATEX SetWaveFmt(ysxWAV_File File)
{
	WAVEFORMATEX Wave;
	Wave.wFormatTag = WAVE_FORMAT_PCM;
	Wave.nChannels = File.FMT.Channels;
	Wave.nSamplesPerSec = File.FMT.SRate;
	Wave.nAvgBytesPerSec = File.FMT.ByteRate;
	Wave.nBlockAlign = File.FMT.BlockAlign;
	Wave.wBitsPerSample = File.FMT.BitsPerSample;
	Wave.cbSize = 0;
	return (Wave);
}

// CHECK AUDIO SUPPORT:
/*void FormatSupport(WAVEFORMATEX Wave, HWND Window)
{
	UINT wReturn = IsFormatSupported(&Wave, WAVE_MAPPER);
	if (wReturn == 0) MessageBox(Window, L"Supported.", L"", MB_ICONINFORMATION);
	else if (wReturn == WAVERR_BADFORMAT) MessageBox(Window, L"NOT supported.", L"", MB_ICONINFORMATION);
	else MessageBox(Window, L"Error opening device.", L"Error", MB_ICONEXCLAMATION);
}*/

// ###############################################################################################################################################################################


// ###############################################################################################################################################################################
// ###############################################################################################################################################################################
// ###############################################################################################################################################################################
// ###############################################################################################################################################################################

// CORE AUDIO (API) BUFFER:
class cAudioBuffer
{
public:
	WAVEHDR Header;
	HWAVEOUT Wave;
	int Bytes;

	// #################################################
	BOOL Init(HWAVEOUT hWave, int Size)
	{
		Wave = hWave;
		Bytes = 0;
		Header.lpData = (LPSTR)LocalAlloc(LMEM_FIXED, Size); // Allocate a buffer and initialize the header
		if (Header.lpData == NULL) { return FALSE; }
		Header.dwBufferLength = Size;
		Header.dwBytesRecorded = 0;
		Header.dwUser = 0;
		Header.dwFlags = 0;
		Header.dwLoops = 0;
		Header.lpNext = 0;
		Header.reserved = 0;
		waveOutPrepareHeader(hWave, &Header, sizeof(WAVEHDR));
		return TRUE;
	}

	void Flush()
	{
		// ASSERT(Bytes != 0);
		Bytes = 0;
		waveOutWrite(Wave, &Header, sizeof(WAVEHDR));
	}

	BOOL Write(PBYTE pData, int nBytes, int& BytesWritten)
	{
		// ASSERT((DWORD)Bytes != Header.dwBufferLength);
		BytesWritten = min((int)Header.dwBufferLength - Bytes, nBytes);
		CopyMemory((PVOID)(Header.lpData + Bytes), (PVOID)pData, BytesWritten); // Destination, Source and Length
		Bytes += BytesWritten;
		if (Bytes == (int)Header.dwBufferLength) { Bytes = 0; waveOutWrite(Wave, &Header, sizeof(WAVEHDR)); return TRUE; } // WRITE
		return FALSE;
	}
	// #################################################

	~cAudioBuffer()
	{
		if (Header.lpData)
		{
			waveOutUnprepareHeader(Wave, &Header, sizeof(WAVEHDR));
			LocalFree(Header.lpData);
		}
	}
};

// ###############################################################################################################################################################################

// // CORE AUDIO (API) OUT (ALSO BUFFERS):
class cAudioOut
{
public:
	HANDLE Semaphore;
	int Buffers;
	int CurrentBuffer;
	BOOL NoBuffer;
	vector<cAudioBuffer> Headers;
	HWAVEOUT Wave;

	// #################################################
	void Flush()
	{
		if (!NoBuffer)
		{
			Headers[CurrentBuffer].Flush();
			NoBuffer = TRUE;
			CurrentBuffer = (CurrentBuffer + 1) % Buffers;
		}
	}

	void Reset() { waveOutReset(Wave); }

	void Write(PBYTE pData, int Bytes)
	{
		while (Bytes != 0)
		{
			// Get a buffer if necessary:
			if (NoBuffer)
			{
				WaitForSingleObject(Semaphore, INFINITE);
				NoBuffer = FALSE;
			}

			//  Write into a buffer:
			int nWritten;
			if (Headers[CurrentBuffer].Write(pData, Bytes, nWritten))
			{
				NoBuffer = TRUE;
				CurrentBuffer = (CurrentBuffer + 1) % Buffers;
				Bytes -= nWritten;
				pData += nWritten;
			}
			else { break; } // ASSERT(nWritten == Bytes);
		}
	}

	void Wait()
	{
		// Send any remaining buffers:
		Flush();
		// Wait for the buffers back:
		for (int i = 0; i < Buffers; i++) { WaitForSingleObject(Semaphore, INFINITE); }
		LONG lPrevCount;
		ReleaseSemaphore(Semaphore, Buffers, &lPrevCount);
	}
	// #################################################

	cAudioOut(LPCWAVEFORMATEX Format, int nBuffers, int BufferSize)
	{
		Buffers = nBuffers; CurrentBuffer = 0; NoBuffer = TRUE;
		Semaphore = CreateSemaphore(NULL, nBuffers, nBuffers, NULL);
		Headers = vector<cAudioBuffer>::vector(nBuffers);
		Wave = NULL;
		
		// Create wave device:
		// !!!!!!! THE PROBLEM IS (DWORD)WaveCallback, WHEN SET TO NULL, IT WORKS !!!!!!!
		waveOutOpen(&Wave, WAVE_MAPPER, Format, (DWORD)WaveCallback, (DWORD)Semaphore, CALLBACK_FUNCTION);

		// Initialize wave buffers:
		for (int i = 0; i < Headers.size(); i++) { Headers[i].Init(Wave, BufferSize); }
	}
	~cAudioOut()
	{
		waveOutReset(Wave); // Get the buffers back
		//delete[] Headers; // Free buffers
		waveOutClose(Wave); // Close device
		CloseHandle(Semaphore); // Free semaphore
	}
};

// ###############################################################################################################################################################################
// ###############################################################################################################################################################################
// ###############################################################################################################################################################################

/*HRESULT RenderStreamToDevice(IMultiMediaStream* pMMStream)
{
	WAVEFORMATEX wfx;
#define DATA_SIZE 5000

	IMediaStream* pStream = NULL;
	IAudioStreamSample* pSample = NULL;
	IAudioMediaStream* pAudioStream = NULL;
	IAudioData* pAudioData = NULL;

	HRESULT hr = pMMStream->GetMediaStream(MSPID_PrimaryAudio, &pStream);
	if (FAILED(hr))
	{
		return hr;
	}

	pStream->QueryInterface(IID_IAudioMediaStream, (void**)&pAudioStream);
	pStream->Release();

	hr = CoCreateInstance(CLSID_AMAudioData, NULL, CLSCTX_INPROC_SERVER, IID_IAudioData, (void**)&pAudioData);
	if (FAILED(hr))
	{
		pAudioStream->Release();
		return hr;
	}

	PBYTE pBuffer = (PBYTE)LocalAlloc(LMEM_FIXED, DATA_SIZE);
	if (pBuffer == NULL)
	{
		pAudioStream->Release();
		pAudioData->Release();
		return E_OUTOFMEMORY;
	}

	pAudioStream->GetFormat(&wfx);
	pAudioData->SetBuffer(DATA_SIZE, pBuffer, 0);
	pAudioData->SetFormat(&wfx);
	hr = pAudioStream->CreateSample(pAudioData, 0, &pSample);
	pAudioStream->Release();
	if (FAILED(hr))
	{
		LocalFree((HLOCAL)pBuffer);
		pAudioData->Release();
		pSample->Release();
		return hr;
	}

	AudioOut WaveOut(&wfx, 4, 2048);
	HANDLE hEvent = CreateEvent(FALSE, NULL, NULL, FALSE);
	if (hEvent != 0)
	{
		int iTimes;
		for (iTimes = 0; iTimes < 3; iTimes++)
		{
			DWORD dwStart = timeGetTime();
			for (; ; )
			{
				hr = pSample->Update(0, hEvent, NULL, 0);
				if (FAILED(hr) || hr == MS_S_ENDOFSTREAM)
				{
					break;
				}
				WaitForSingleObject(hEvent, INFINITE);
				DWORD dwTimeDiff = timeGetTime() - dwStart;
				// Limit to 10 seconds
				if (dwTimeDiff > 10000) {
					break;
				}
				DWORD dwLength;
				pAudioData->GetInfo(NULL, NULL, &dwLength);
				WaveOut.Write(pBuffer, dwLength);
			}
			pMMStream->Seek(0);
		}
	}

	pAudioData->Release();
	pSample->Release();
	LocalFree((HLOCAL)pBuffer);
	return S_OK;
}*/

// ###############################################################################################################################################################################

/*HRESULT RenderFileToMMStream(const char* szFileName, IMultiMediaStream** ppMMStream)
{
	if (strlen(szFileName) > MAX_PATH)
	{
		return E_INVALIDARG;
	}

	IAMMultiMediaStream* pAMStream;
	HRESULT hr = CoCreateInstance(CLSID_AMMultiMediaStream, NULL, CLSCTX_INPROC_SERVER, IID_IAMMultiMediaStream, (void**)&pAMStream);
	if (FAILED(hr))
	{
		return hr;
	}

	WCHAR wszName[MAX_PATH + 1];
	MultiByteToWideChar(CP_ACP, 0, szFileName, -1, wszName,	MAX_PATH + 1);

	pAMStream->Initialize(STREAMTYPE_READ, AMMSF_NOGRAPHTHREAD, NULL);
	pAMStream->AddMediaStream(NULL, &MSPID_PrimaryAudio, 0, NULL);
	hr = pAMStream->OpenFile(wszName, AMMSF_RUN);
	{
		if (SUCCEEDED(hr)) { hr = pAMStream->QueryInterface(IID_IMultiMediaStream, (void**)ppMMStream);	}
	}
	pAMStream->Release();
	return hr;
}*/

// ###############################################################################################################################################################################
// ####### MAIN #################################################################################################################################################################
// ###############################################################################################################################################################################

#endif // SCPARSE_