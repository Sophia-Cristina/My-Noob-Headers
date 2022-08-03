#pragma once

#pragma comment (lib, "SDL2test.lib")
#pragma comment (lib, "SDL2main.lib")
#pragma comment (lib, "SDL2.lib") // Be sure that you have built SDL2 lib!
#include "ysxSDL.h"
#ifdef main
#undef main
#endif
#include "ysxMusic/ysxSDLAudio.h"

// I preffer that you include the headers of my collection:
// #include "ysxfiles/ysxWAVE.h"
// #include "ysxMusic/ysxMusic.h"

#ifndef YSXMINISENG_H
#define YSXMINISENG_H

// #####################
// ####### By Sophia Cristina
// ####### Very simple and small fully capable sound engine!
// #####################

// #################################################
// REFERENCES:
// #################################################

/*~*~ ~*~ ~*~ MINI SOUND ENGINE ~*~ ~*~ ~*~
The engine originally was way smaller, but i decided to make it in a way that is more "portable" to hardware.
However, it can use pretty small kilobytes with certain setups.

I designed this engine aiming this algorithm, data structures and logic to be most-universal-as-possible
to any hardware.
Because at first i made this engine aiming to use in the creation of demos (demoscene), and i wanted it to run
on windows, on a mega-drive and on a ZX... Well, it ran on windows, yet, i need to know if it will run smoothly
on other hardwares, and, probably i'm going to have to translate this code to assembly :s.

The sampling system calls for a signal which is then processed and sent to DAC.
The signal is called togheter with certain important data to control how it will sound and record.

~*~ TEMPLATE ~*~
* PATSIZE: Since the pattern is based on bitwise, the pattern size (hence the name) is the number of bits;
* SIGTYPE: Signal sample value is based on this type;
* SRATE: Sample Rate, duh;
* SIGSIZE: Or Block Size, is the size of the array of samples which will be sent to playback.
		   Bigger block size may take longer to process and may give sound artifacts;
		   !!!!!!! VERY IMPORTANT !!!!!!!
	"array<ui8, SIGSIZE * sizeof(SIGTYPE)> SIG;"
	 That means that you should specify the SDL
		   !!!!!!!				  !!!!!!!
* INSTR: How much instrument signals are going to be called by the sampling system;
* VOICES: Number of voices PER INSTRUMENT;

							~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~

~*~ SAMPLES ~*~
Samples are counted with 'RAM->n' (or just 'n'). If 'n' reaches 'ROM->Samples', the engine considers that
the playback was complete.
'n' and a modulo operates inside the sample-block, which is really what makes the sound play:
'SIG[n % SIGSIZE]';

The sampling system keeps overwritting a space in SIG until 'n == Samples'.
When 'n' is equal to the last index of SIG, the SDL delay function is activated for time enough to play the
entire SIG sample block. And consequently, a new bunch of process happens each 'n' to fill SIG with another
playable set of samples.
You can imagine the sample block as a circle that begins where it ends, and writes a sample before looping.

Until now i have not found problems in this system and i could hear in the program and in the '.wav' file
with same quality. Would be nice to know if there is a problem with this system, and then i encourage
to report this issue to me.

~*~ PATTERN ~*~
Is based on the bit positions. Meaning that you can change the pattern at will.
If you set PATSIZE, for example, to uint16_t, you are going to have two bytes (DATA_Time::PatBits = 16):
	0x0000
If you imagine four bits per beat, then you can compose four beats per pattern.
In case you want a note in each beat, you can set the pattern to:
	0x8888 | 34952 | 10001000 10001000

The object 'ui8 b' counts the current bit. In the example below, 'b = 4':
	10001000
		^
		b
Whenever sample 'n' is a multiple of 'L', check b's position in the pattern using this formula:
	(*PatPins >> (PatBits - 1 - b)) & 1
In this case, 'b' is bellow the number '1', and then it writes the instrument data for the sampling system,
or else, it will just skip the writting, and a data-less instrument is ignored by the sampling system.

After all this process:
++b; b %= PatBits;

~*~ INSTRUMENT DATA ~*~
!!! The hardware should have a RAM space for signal data of EACH instruments !!!
The data is based on classes inside some headers i made:

"ysxSignal":
template<class T_> class SigStream
{
public:
	uint32_t Size = 0; // As samples
	std::vector<uint32_t> C; // 'C'ount (iterator), use vector index as different voices
	virtual T_ IO(T_ T_bits) { return(T_bits); }
	SigStream() { C.push_back(0); }
};


"ysxSynth.h":
template<class T_> class SigSynth : public SigStream<T_>
{
public:
	std::vector<Point<uint8_t>> MIDI; // x = note; y = velocity
	uint8_t V = 0; // Voice for the counter, ex.: C[V]
	float Freq = 1, Gain = 1;
};

~*~ DAC ~*~
To make some noise, you need to send it out! With SDL, it is constantly sending out after 'SDL_PauseAudio(0)'
function!
But we process a sample block 'RAM->SIG' fastly, to avoid artifacts, and use 'SDL_Delay' to let it playback
what we just made!

		if (RAM->n % SIGSIZE == SIGSIZE - 1) { SDL_Delay((SIGSIZE / SRATE) * 1000.0); }
		RAM->y = 0; RAM->Cc = 0;
		++RAM->n;

Take in mind this last line above!
'n' is a sample couter and it belongs to the RAM. Consequently, it is up to the programmer to make a correct
use of it! 'n' must be '< ROM->Samples', since this should be the last sample of the playback. Nothing forces
you for that, and if you find some strange use for 'n >= ROM->Samples', enjoy! And even share if you want!
*/

// #################################################
// ############## DATA ##############

/*
*/

/*~*~ OUTPUT DATA:
Raw audio sample data, be sure to set the correct file position (ex.: wav file: .seekp(44))!
fstream* SigO is going to write to file.
!!! MAKE SURE YOU HAVE SPACE FOR ALL 'SIGTYPE' TYPE BYTES IN THE INPUT SIGNAL: "void Out(void* SigI)" !!!
This is just the output data packet (as 'SIGTYPE'), you should add a 'protocol' (or electric component)
for different kind of output ports!*/

// OUTPUT TO BUFFER (CAREFUL WITH DATA TYPE):
template <class SIGTYPE, const uint16_t SIGSIZE>
struct MSENG_DATA_O
{
	void* SigO = nullptr;
	size_t C = 0; // Buffer data counter

	/* OUTPUT TO FILE:
	CAREFUL! 'SigO' is casted to 'fstream*'! "(fstream*)SigO->write(...)"!
	Be sure that SigO is INDEED pointing to a 'fstream' object!*/
	void OF(void* SigI)
	{
		if (SigO && SigI) { (std::fstream*)SigO->write((char*)SigI, sizeof(SIGTYPE)); C = SigO->tellp(); }
		else { std::cerr << "Input or output signal is not connected! 'fstream* Sig = nullptr'!\n"; }
	}
	/* OUTPUT TO BUFFER:
	CAREFUL! 'SigO' is casted to 'SIGTYPE'! "*(SIGTYPE*)&SigO[C] = *(SIGTYPE*)SigI;"!
	Be sure that SigO is INDEED pointing to a 'SIGTYPE' object and that 'C' is inside SigO's memory space!*/
	void OB(void* SigI)
	{
		if (SigO && SigI) { *(SIGTYPE*)&SigO[C] = *(SIGTYPE*)SigI; C += sizeof(SIGTYPE); }
		else { std::cerr << "Input or output signal is not connected! 'void* Sig = nullptr'!\n"; }

		if (*(int*)SigI == 1 || *(std::string*)SigI == "MOV") { std::cout << "1 OR MOV\n"; } // TEST
	}
};

struct MSENG_DATA_Decod
{

};


/* TIME DATA STRUCTURE:
This is a data structure with everything the engine needs to understand the playback.
You can use it however you want, but it is preferably to use the structure 'MSENG_ROM_Map',
because it contains a MtoF look-up-table, and if i'm to add features to this engine, i'm going to
add on that class preferably!

Sure size:
1 + 8 + 4 + 4 + 4 + 4 + 4 = 29 BYTES;
*/
template <class PATSIZE, uint32_t SRATE>
struct MSENG_DATA_Time
{
	const uint8_t PatBits = sizeof(PATSIZE) * 8; // Number of bits per pattern
	const double t = 1.0 / SRATE; // t = 1.0 / SRATE;
	float Min = 0, Sec = 0; // Playback time
	uint32_t Samples = 0; // Total samples in music
	float BPM = 120, Beat = 500, BeatSmp = 0.5 * SRATE; // Beat in ms and in samples	
	float L = BeatSmp / 4.0; // Samples to change to the next bit (in a pattern)
	float nEnd = PatBits * L; // Total samples in a pattern
};
template <class PATSIZE, uint32_t SRATE>
void MSENG_DATA_Time_Set(MSENG_DATA_Time<PATSIZE, SRATE>* D, float SetMin = 0, float SetSec = 59, float SetBPM = 120)
{
	D->Min = SetMin; D->Sec = SetSec; D->Samples = (SetSec + SetMin * 60) * SRATE;
	D->BPM = SetBPM; D->Beat = 60000.0 / SetBPM; D->BeatSmp = (D->Beat / 1000.0) * SRATE;
	D->L = D->BeatSmp / 4.0; D->nEnd = D->PatBits * D->L;
}

// #################################################
// ############## MEMORY ##############

// ROM MAP V.1:
// Yes, it is only the time data and a look-up-table.
template <class PATSIZE, uint32_t SRATE>
struct MSENG_ROM_Map : public MSENG_DATA_Time<PATSIZE, SRATE>
{ std::array<float, 128> MtoF; };

/* RAM MAP V.1:
This structure maps the data packet to be read and written by the engine.
Don't matter at what point you want the engine to read / write, the engine starts to read and write
from the address until the size in bytes of this structure.
TAKE IN MIND that you should configure the 'Spec' and 'sD' (signal data) to make it possible to be
played with SDL!

Ambiguous size:
SIGSIZE * sizeof(SIGTYPE) + sizeof(SIGTYPE) + sizeof(SDL_AudioSpec) + sizeof(SignalData) + sizeof(void*);
Ideal: 485 bytes!

Sure size:
4 + 1 + 1 + 4 + 4 + 8 + 1 = 23 BYTES;

size of n-bits and 485 Bytes of signal stuffs:
485 = SIGSIZE * sizeof(SIGTYPE) + sizeof(SDL_AudioSpec) + sizeof(SignalData) + sizeof(void*);
485 + 1 + 23 = 509 BYTES;
485 + 2 + 23 = 510 BYTES;
485 + 4 + 23 = 512 BYTES; // Ideal to use something that is 2^n
*/
template <class SIGTYPE, const uint16_t SIGSIZE>
struct MSENG_RAM_Map
{
	std::array<uint8_t, SIGSIZE * (std::is_floating_point<SIGTYPE>::value ? 1 : sizeof(SIGTYPE))> SIG; // SIGNAL!!!
	
	// Consider that on hardware, there would NOT have SDL, consequently, this data structure would
	// be slightly different:
	SDL_AudioSpec Spec; // Specifications for SDL
	SignalData sD; // Callback function data structure

	uint32_t n = 0; // Actual sample. But it is sometimes used for other things (should avoid it if you do)
	uint8_t b = 0; // Bit of the byte (or bytes) that represents the music pattern !!! TO BE FLIP-FLOP !!!
	uint8_t Cc = 0; // Main counter. Remember to set it back to '0'
	float Gg = 0; // Gain sum, for normalization
	float Max = 0; // Comment (or somewhere else that uses it) to stop saving the peaks of a playback (may reduce lag)
	void* ptr = nullptr; // General use pointer! Consequently, NEVER trust it!
	double x = 0; // Music is a 'f(x)', and 't' are metrics on the x's axis
	uint8_t g = 1; // Gain: y *= g / 255.0
	
	// 'y' is the number which will be send to the signal block and then to DAC.
	// Be sure to make your instruments the same type!
	SIGTYPE y = 0;
};

struct MSENG_RAM_Data
{

};

// #################################################
// ############## PRODUCTS ##############

// !!!!!!! Maybe, WIP, nothing sure now !!!!!!!
template <class PATSIZE, class SIGTYPE, uint32_t SRATE,	const uint16_t SIGSIZE, const uint8_t INSTR, const uint8_t VOICES>
class MSENG_PCB_ALPHA1
{
public:
	// SDL stuff, that would not be on a PCB:
	SDL_AudioDeviceID Device;

	enum ePtrn { pK, pS, pHH, pRide, pCrash, pPads, pBass, pMid, pHigh }; // Instruments order
	std::array<SigSynth<SIGTYPE>*, INSTR> SigPins;
	//std::array<PATSIZE, INSTR> PatPins; // All instruments
	
	// Input pinning in the board to make bitwise music patterns,
	// this is the actual connection state to the board and can be freely changed.
	PATSIZE* PatPins;

	// !!! TO BE A PORT TO SOMETHING, LIKE, SD-CARD, USB OR SOMETHING ELSE:
	std::string WAVFileName = "!TESTWAV"; // You can save your wave (.wav) file
	WAVEFile* wavf; // RIFF WAVE file
	

	// !!! TO BE DESIGNED A HARDWARE EMULATION FOR THIS:
	std::string LOG; bool bLOG = false;

	// #################################################
	// ### MEMORY ###
	MSENG_ROM_Map<PATSIZE, SRATE>* ROM;
	MSENG_RAM_Map<SIGTYPE, SIGSIZE>* RAM;
	//STM8S003F3P6TR MC; // Micro-controller with 8kb Flash, 128b EEPROM and 1kb RAM
	// #################################################
	
	MSENG_DATA_O<SIGTYPE, SIGSIZE> Out; // Output

	// #################################################
	
	// BE SURE TO DESTROY UNUSED STUFFS, AS RESETS SETS POINTERS TO 'nullptr'!
	void RESET()
	{
		RAM->n = 0;	RAM->Cc = 0; RAM->Gg = 0;
		RAM->Max = 0; RAM->ptr = nullptr;
		LOG.clear(); bLOG = false;
		wavf->wavf(WAVFileName, SRATE); Out.SigO = &wavf->wavFile;
		for (uint8_t n = 0; n < INSTR; ++n) { SigPins[n] = nullptr; }
		PatPins = nullptr;
		RAM->x = 0; RAM->g = 1; RAM->y = 0; RAM->b = 0;
		memset(&RAM->SIG[0], 127, RAM->SIG.size());
	}

	//void SetTime(float SetMin, float SetSec) { ROM->Min = SetMin; ROM->Sec = SetSec; Samples = (ROM->Sec + ROM->Min * 60) * SRATE; }
	
	/*#################################################
	############## COMPOSITIONS TOOLS ##############
	#################################################
	It is not nescessary to use those tool to make your music, you can write your own function!
	However, some tools here might make your work easier.*/
	// BIT CHECK:
	// If 'n' is at the position to trigger a new bit in the pattern, returns 'true'.
	virtual bool BitCheck()
	{
		if (RAM->n % (uint32_t)ROM->nEnd == (uint32_t)round(RAM->b * RAM->L)) { return(true); }
		return(false);
	}
	
	/*SAMPLING INITIALIZATION:
	Set instruments' data for the sampling system.
	ATTENTION, MANUALLY DEFINE: ++RAM->b; RAM->b %= ROM->PatBits;*/
	virtual void SmpInit(uint8_t P)
	{
			if (SigPins[P] && PatPins && *PatPins)
			{
				if ((*PatPins >> (ROM->PatBits - 1 - RAM->b)) & 1)
				{
					while (SigPins[P]->C[RAM->Cc] != 0 && RAM->Cc < VOICES - 1) { ++RAM->Cc; }
					SigPins[P]->C[RAM->Cc] = SigPins[P]->Size;
				}
				RAM->Cc = 0;
			}
	}

	/*CALLS SIGNAL SAMPLES FROM SIGNAL SOURCES:
	The data is based on my signal processing class.
	At hardware level, i wanted my engine to have a single input cable
	and the rest of the information in the RAM.
	The input cable could be the typicall guitar cable, or the
	typicall phone cable you insert in your computer.*/
	virtual void Sampling()
	{
		for (uint8_t I = 0; I < INSTR; ++I)
		{
			if (SigPins[I])
			{
				for (uint8_t C = 0; C < SigPins[I]->C.size(); ++C)
				{
					if (SigPins[I]->C[C] != 0)
					{
						SigPins[I]->Freq = ROM->MtoF[SigPins[I]->MIDI[C].x];
						SigPins[I]->Gain = SigPins[I]->MIDI[C].y / 127.0;
						SigPins[I]->V = C;
						RAM->y += SigPins[I]->IO(RAM->x);
						--SigPins[I]->C[C]; ++RAM->Cc;
					}
				}
			}
		}
	}

	// #################################################
	void DAC()
	{
		if (RAM->Gg == 0) { RAM->Gg = 1; } if (RAM->Cc == 0) { RAM->Cc = 1; } RAM->y /= (RAM->Gg * RAM->Cc); // Gain stuffs
		if (std::is_floating_point<SIGTYPE>::value)
		{
			if (RAM->y > 1) { RAM->y = 1; } if (RAM->y < -1) { RAM->y = -1; } // Normalize
			RAM->SIG[RAM->n % SIGSIZE] = (RAM->y + 1) * 127.5 * RAM->g * 0.00392156862745098; // Sample block
			if (wavf) { wavf->wavFile.write((char*)&RAM->SIG[RAM->n % SIGSIZE], 1); }
		}
		else
		{
			*(SIGTYPE*)&RAM->SIG[(RAM->n * sizeof(SIGTYPE)) % (SIGSIZE * sizeof(SIGTYPE))] = RAM->g * (1 / 255.0) * RAM->y / (pow(256, sizeof(SIGTYPE)) - 1);
			if (wavf) { wavf->wavFile.write((char*)&RAM->SIG[(RAM->n * sizeof(SIGTYPE)) % (SIGSIZE * sizeof(SIGTYPE))], sizeof(SIGTYPE)); }
		}
		if (fabs(RAM->y) > RAM->Max)
		{
			if (bLOG)
			{
				LOG += "Y MAX = " + std::to_string(RAM->y) + " | BYTE: " + std::to_string((RAM->y + 1) * 127.5);
				LOG += " | Gg: " + RAM->Gg + '\n';
			}
			RAM->Max = fabs(RAM->y);
		}
		if (RAM->n % SIGSIZE == SIGSIZE - 1) { SDL_Delay((SIGSIZE / SRATE) * 1000.0); } // Playback after sample block is filled
		RAM->y = 0; RAM->Cc = 0; // <------- RESETS
	}

	/*Make noise! Assuming that you built SDL2 lib!
	Use 'SDL_CloseAudio()' function to close the audio!
	And if you decide to open it again, use this:
	Device = SDL_OpenAudio(&RAM->Spec, NULL);*/
	void StartEngine()
	{
		RAM->Gg = INSTR; // Max gain possible (if not clipping)
		// ####### CALLBACK #######
		if (Device < 0)
		{
			std::cerr << "!!! FAILED TO OPEN AUDIO: " << SDL_GetError() << " !!!\n";
			if (bLOG) { LOG += "!!! FAILED TO OPEN AUDIO: " + SDL_GetError() + " !!!\n"; }
		}
		else
		{
			if (bLOG) { LOG += SDLStringSpec(RAM->Spec); LOG += SDLStringData(RAM->sD); LOG += "Total samples: " + std::to_string(ROM->Samples) + "\n\n~*~ AUDIO OPEN:\n\n"; }
			SDL_PauseAudio(0);
		}
	}

	// Assuming that 'Device' is not '< 0':
	void PauseEngine() { SDL_PauseAudio(1); if (bLOG) { LOG += "Audio paused! "; } }

	// EXAMPLE
	void ExampleBasicComposition()
	{
		StartEngine();
		for (RAM->n = 0; RAM->n < ROM->Samples; ++RAM->n)
		{
			RAM->x = ROM->t * RAM->n;
			if (BitCheck()) // If 'n' triggers new bit in a pattern. Regardless if bit is on or off.
			{
				for (uint8_t m = 0; m < INSTR; ++m)
				{
					// COMPOSE PER INSTRUMENT HERE!
					SmpInit(m); // Initializes instrument data
				}
			}
			Sampling(); // Samples signal for buffer
			DAC(); // Play!
		}
		PauseEngine();
	}

	// #################################################

	void INIT()
	{
		Device = SDL_OpenAudio(&RAM->Spec, NULL);
		RAM->sD.Pos = &RAM->SIG[0]; RAM->sD.Samples = SIGSIZE; RAM->sD.Count = 0; RAM->Spec.userdata = &RAM->sD;
		RAM->Spec.callback = SignalCall;
		memset(&RAM->SIG[0], 127, RAM->SIG.size()); // Signal
		for (RAM->n = 0; RAM->n < INSTR; ++RAM->n) { SigPins[RAM->n] = nullptr; } RAM->n = 0; // Start with clean pointers
		PatPins = nullptr;
		Out.SigO = &wavf->wavFile; wavf->wavFile.seekp(44); // (std::fstream*)Out.SigO->seekp(44);
	}

	MSENG_PCB_ALPHA1(MSENG_ROM_Map<PATSIZE, SRATE>* SetROM, MSENG_RAM_Map<SIGTYPE, SIGSIZE>* SetRAM, WAVEFile* WAV)
	{
		wavf = WAV;	ROM = SetROM; RAM = SetRAM; INIT();
	}
		
	~MSENG_PCB_ALPHA1()
	{
		RESET(); // Don't forget to clean your pointers!
		SDL_CloseAudio();
	}
};

// ###############################################################################################################################################################################
// ####### MAIN #################################################################################################################################################################
// ###############################################################################################################################################################################

#endif // SCPARSE_