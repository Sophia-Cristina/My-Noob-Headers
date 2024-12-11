#ifndef YSXMINISENG_H
#define YSXMINISENG_H

// I rather that you include the headers of my collection:
// #include "ysxfiles/ysxWAVE.h"
// #include "ysxMusic/ysxMusic.h"
//#include "ysxLibsUtils\SDL\Audio\ysxSDLAudio.h"

// #####################
// ####### By Sophia Cristina
// ####### Very simple and small fully capable sound engine!
// #####################

// #################################################
// REFERENCES:
// #################################################

/*~*~ ~*~ ~*~ MINI SOUND ENGINE ~*~ ~*~ ~*~
* this comment section is an introduction to the code idea *
* However, i also made another comment section for the class that is an 'emulator-like' of what would be
* a hardware version of this engine: "class ysxMSENG_PCB_ALPHA1".

The engine originally was smaller, but i decided to code it aiming to look more hardware-like.
But it can use pretty small kilobytes with certain setups, or skewing the codes here.
I pretend to make another class that is more hardware-like than that, by emulating electronic
devices, like clock, using flip-flops to count and using gates and etc... For now
i think this is hardware-like enough for me!

I hope this engine can be used in almost all types of system.
Because i made this engine aiming to use in different projects from different systems and CPUs.

The sampling system calls for a signal which is then processed and sent to DAC.
A protocol data is sent to the signal source before calling for audio-samples.
This data is pretty simple, 5 bytes cointaining the voice that is being R / W,
and the amount of samples that is going to be requested from the signal source.

~*~ CONST OR MACROS ~*~
* PATSIZE: Since the pattern is based on bitwise logic, the pattern size is the number of bits;
* SIGTYPE: Object type of the signal sample;
* SRATE: Sample Rate;
* BUFSIZE: Or Block Size, is the size of the array of samples to be sent to playback.
		   Bigger blocks may take long to process and may give sound artifacts;
			"std::array<ui8, BUFSIZE * sizeof(SIGTYPE)> BUF;"
	 
* INSTR: How much instrument signals are going to be called by the sampling system;
* VOICES: Number of voices PER INSTRUMENT;

		i.e.: "a.wav -> 16 bits, mono, 44100;
			  SIGTYPE = uint16_t, or 'short' (signed) and etc;
			  If not mono, you must create functions manipulating things inside the classes!
			  SRATE = 44100;"
			  !!! HOWEVER: if 'SIGTYPE' is a 'float' or 'double', the function inside the class
			  outputs 8-bit samples, and NOT 'float' or 'double'. Maybe in the future, for now,
			  you must code it yourself. !!!


							~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~

~*~ SAMPLES ~*~
Samples are counted with 'RAM->n' (or just 'n'). If 'n' reaches 'RAM->Samples', the engine considers that
the playback was complete.
'n' and a modulo operates inside the sample-block (buffer), which is really what makes the sound play:
'BUF[n % BUFSIZE]';

The sampling system keeps overwriting a space in 'BUF' while 'n < Samples'.
When 'n' is equal to the last index of BUF, the SDL delay function is activated for time enough to play the
entire BUF sample block. And consequently, a new bunch of process happens each 'n' to fill BUF with another
playable set of samples.
You can imagine the sample block as a circle that begins where it ends, and writes a sample before looping.

Until now i have not found problems in this system and i could hear with same quality in the program and in
the '.wav' file.

~*~ PATTERN ~*~
Is based on the bit positions. Meaning that you can change the pattern at will.
If you set PATSIZE, for example, to uint16_t, you are going to have two bytes (ysxMSENG_DATA_Time::PatBits = 16):
	0x0000
It is four bits per beat, then ui16 can compose four beats per pattern.
In case you want a note in each beat, you can set the pattern to:
	0x8888 | 34952 | 1000.1000 1000.1000

The object 'ui8 b' counts the current bit. If 'b = 4':
	10001000
	0123^
		b
Whenever sample 'n' is a multiple of 'L', it check b's position in the pattern using this formula:
	(*PatPins >> (PatBits - 1 - b)) & 1
In this case, 'b' is at a bit that is set to '1', and then it writes the protocol data for the sampling system,
or else, it will just skip the writting, and a data-less instrument is ignored by the sampling system.

After all this process:
++b; b %= PatBits;

~*~ INSTRUMENT DATA ~*~
The hardware should have a RAM space for protocol data for EACH instrument.
Be it the hardware or the signal source.
The data is based on classes inside some headers i made:

"ysxSignal.h": class SigStream;
"ysxSynth.h":  class SigSynth;

~*~ DAC ~*~
To make some noise, you need to send to the DSP. With SDL, it is constantly sending out after
calling the 'SDL_PauseAudio(0)' function.
But we process a sample block 'RAM->BUF' fastly (to avoid artifacts), then we use 'SDL_Delay' to
playblack what we processed.

		if (RAM->n % BUFSIZE == BUFSIZE - 1) { SDL_Delay((BUFSIZE / SRATE) * 1000.0); }
		RAM->y = 0; RAM->Cc = 0;
		++RAM->n;

Take in mind this last line above!
'n' is a sample counter and it belongs to the RAM (and it is public). Consequently, it is up to the programmer
to make a correct use of it! 'n' must be '< RAM->Samples', since this should be the last sample of the
playback. And if you find some strange use for 'n >= RAM->Samples', enjoy!
You don't need to use "++RAM->n" if you process it inside a 'for' loop!
*/

// #################################################
// ############## DATA ##############

/*~*~ OUTPUT DATA:
Raw audio sample data, if outputting to a file, be sure to set the correct file position, 
ex.: wav file: .seekp(44)! Casted "fstream* SigO" is going to write to file.
!!! MAKE SURE YOU HAVE SPACE FOR ALL 'BUFTYPE' TYPE BYTES IN THE INPUT SIGNAL: "void Out(void* SigI)" !!!
This is just the output data-packet (as 'SIGTYPE'), you should add a 'protocol' (or electric component)
for different kind of output ports, like USB!

This struct is made only to partially emulate how it would be on hardware, but it is kinda useless if
you use it on c++! And so, you may not use it AT ALL!
! CAREFUL WITH DATA TYPE !:*/
template <class SIGTYPE, const uint16_t BUFSIZE>
struct ysxMSENG_DATA_O
{
	void* SigO = nullptr;
	size_t C = 0; // Buffer data counter

	/* OUTPUT TO FILE:
	CAREFUL! 'SigO' is casted to 'fstream*'! "(fstream*)SigO->write(...)"!
	Be sure that SigO is INDEED pointing to a 'fstream' object!*/
	void OF(void* SigI)
	{
		if (SigO && SigI) { ((std::fstream*)SigO)->write((char*)SigI, sizeof(SIGTYPE)); C = ((std::fstream*)SigO)->tellp(); }
		else { std::cerr << "Input or output signal is not connected! 'fstream* Sig = nullptr'!\n"; }
	}
	/* OUTPUT TO BUFFER:
	CAREFUL! 'SigO' is casted to 'SIGTYPE'! "*(SIGTYPE*)&SigO[C] = *(SIGTYPE*)SigI;"!
	Be sure that SigO is INDEED pointing to a 'SIGTYPE' object and that 'C' is inside SigO's memory space!*/
	void OB(void* SigI)
	{
		if (SigO && SigI) { *(SIGTYPE*)(SigO + C) = *(SIGTYPE*)SigI; C += sizeof(SIGTYPE); } // Maybe change it to a 'for' or 'while' loop
		else { std::cerr << "Input or output signal is not connected! 'void* Sig = nullptr'!\n"; }

		//if (*(int*)SigI == 1 || *(std::string*)SigI == "MOV") { std::cout << "1 OR MOV\n"; } // TEST
	}
};

// Insert 5 bytes of data for signal sources:
void ysxMSENG_DATA_Encod(uint8_t DATA[5], uint8_t Voice, uint32_t Data) { DATA[0] = Voice; *(uint32_t*)&DATA[1] = Data; }

// Get 5 bytes of data from signal sources into different variables:
void ysxMSENG_DATA_Decod(uint8_t* DATA, uint8_t& GetVoice, uint32_t& GetData) { GetVoice = DATA[0]; GetData = *(uint32_t*)&DATA[1]; }


/* TIME DATA STRUCTURE:
This is a data structure with everything the engine needs to understand the playback.
You can use it however you want, but it is preferably to use the structure 'ysxMSENG_ROM_Map',
because it contains a MtoF look-up-table, and if i'm to add features to this engine, i'm going to
add on that class preferably!*/
template <class PATSIZE, uint32_t SRATE>
struct ysxMSENG_DATA_Time
{
	const uint8_t PatBits = sizeof(PATSIZE) * 8; // Number of bits per pattern
	const double t = 1.0 / SRATE; // t = 1.0 / SRATE;
};

// #################################################
// ############## MEMORY ##############

// ROM MAP V.1:
// Yes, it is only the time data and a look-up-table.
// The ROM should be provided by the user.
template <class PATSIZE, uint32_t SRATE>
struct ysxMSENG_ROM_Map : public ysxMSENG_DATA_Time<PATSIZE, SRATE>
{ std::array<float, 128> MtoF; };

/* RAM MAP V.1:
This structure maps the data packet to be read and written by the engine.
Don't matter at what point you want the engine to read / write, the engine starts to read and write
from the address and eventually will use the entire size in bytes of this structure.
TAKE IN MIND that you should configure the 'Spec' and 'sD' (signal data) to make it possible to be
played with SDL! This would work different if this project is made as hardware!

Take in mind that SIGTYPE and BUFSIZE makes this struct have ambiguous size!
*/
template <class SIGTYPE, const uint16_t BUFSIZE>
struct ysxMSENG_RAM_Map
{
	// TIME:
	float Min = 0, Sec = 0; // Playback time
	uint32_t Samples = 0; // Total samples in music
	float BPM = 120, Beat = 500, BeatSmp = 22050; // Beat as ms and as samples
	float L = BeatSmp / 4.0; // Samples to change to the next bit (in a pattern)
	float nEnd = 8 * L; // Total samples in a pattern

	// music(x):
	uint32_t n = 0; // Actual sample. But it can be used for other things (glitches may happen if you modify to a bad number)
	uint8_t b = 0; // Bit of the byte (or bytes) that represents the music pattern
	uint8_t Cc = 0; // Main counter. Remember to set it back to '0'
	float Gg = 1; // Total gain, for 'n = 0' to 'n < INSTR', do 'y += f(x) / Gg'
	float Max = 0; // Comment (or somewhere else that uses it) to stop saving the peaks of a playback (may reduce lag)
	void* ptr = nullptr; // General use pointer! Consequently, NEVER trust it! DELETE allocations before using 'RESET()'!
	double x = 0; // Music is a 'f(x)', and 't' are metrics on the x's axis
	uint8_t g = 255; // Gain: y *= g / 255.0
	
	// 'y' is the number which will be send to the signal block and then to DAC.
	// Be sure to make your instruments the same type!
	SIGTYPE y = 0;

	// Consider that on hardware, there would NOT have SDL, consequently, this data structure would
	// be slightly different:
	SDL_AudioSpec Spec; // Specifications for SDL
	ysxSDL_AU_SignalData sD; // Callback function data structure

	/* MAIN BUFFER:
	 MSA1 can't play stereo, maybe the next version will.
	 But if you don't care about hardware accuracy, then you can declare another array on your 'main.cpp',
	 then copy and modify 'MSA1.DAC()' so that it also register to the new array.*/
	std::array<uint8_t, BUFSIZE * (std::is_floating_point<SIGTYPE>::value ? 1 : sizeof(SIGTYPE))> BUF;
};

/* Made for the older RAM version, soon to be modified or deleted:
template <class PATSIZE, uint32_t SRATE>
void ysxMSENG_RAM_Set_Timing(ysxMSENG_RAM_Map<PATSIZE, SRATE>* D, float SetMin = 0, float SetSec = 59, float SetBPM = 120)
{
	D->Min = SetMin; D->Sec = SetSec; D->Samples = (SetSec + SetMin * 60) * SRATE;
	D->BPM = SetBPM; D->Beat = 60000.0 / SetBPM; D->BeatSmp = (D->Beat / 1000.0) * SRATE;
	D->L = D->BeatSmp / 4.0; D->nEnd = sizeof(PATSIZE) * 8 * D->L;
}*/

/* INSTRUMENT DATA WHICH WOULD BE REQUESTED BY THE ENGINE:
Slight modification of the classes 'ysxSIG_Stream' and 'ysxSIG_Synth',
Check how those work at 'ysxSignal.h' and 'ysxSynth.h'.
THE CLASS DON'T USE THIS STRUCT, THIS IS HERE AS AN EXAMPLE!
The class is using:
"std::array<ysxSIG_Synth<SIGTYPE>*, INSTR> SigPins"*/
template <uint8_t VOICES> struct ysxMSENG_INSTR_RAM_Data
{
	uint32_t Size = 0; uint32_t C[VOICES];
	Point<uint8_t> MIDI[VOICES];
	uint8_t V = 0; float Freq = 1;	
};

// #################################################
// ############## PRODUCTS ##############

/* ##################### MINI SOUND ENGINE ALPHA 1 #####################

!!!!!!! Maybe, WIP, nothing sure now !!!!!!!

That is a small, light and simple SoundEngine that is capable of doing complex music.
I wanted that to be a program that can run in almost any hardware. There is lot of space
for optimization, because i'm not a good progammer.
I also want to make the code to look as much like an emulator to what would be a hardware
version of this engine, which i may one day make. So imagine the code in the way you would
imagine a hardware, and imagine the template as different models or setups of the same hardware.

### MUSIC PATTERN BY BITWISE INPUT:
The hardware is going to have 'PATSIZE' pins for the music pattern.
A CLK is connected externally, not sure at how much extent it is going to control
the circuit yet.
A counter is going to call a loop for each instrument for each pin accessed, regadless of it
being 'on' or 'off'.
If the pin is 'on' at instrument 'm', then the engine writes a protocol data to call
instrument samples at the 'sampling system'.
The musician should be aware when to change the pin inputs for each instrument when the loop
happens, which would need a certain level of computing knowledge for a precise timing at
processor speed.
if  (
		   Sample % EndOfTheMusicPattern
						==
		(uint32_t)round(Pin * SamplesPerPin)
	)
	{
	 for (uint8_t m = 0; m < Total_instruments; ++m)
	 {
		Prepares protocol data for the number of samples
		to be called from each instrument and what voice.

		Here is where the musician should change the pin
		bits for each instrument if he wants certain
		compositions. The changes should align with each
		'm' loop.
		For that, the Output called CALLINSTR should ask
		a program, like Arduino, the moment of opportunity
		to change composition.
	 }
	 // Next bit (pin) of PatPins:
	 BitCount(); // ++Pin; Pin %= Pins;
	}

The protocol is a small data packet which is going to be "outputted" to the intrument
(or whatever program) input. This should make the instrument aware that it is going to be called
soon for an audio sample.
The protocol at first asks, for each voice, if there is samples left to be played.
It uses the "RAM->Cc" to count the loops. If all the voices are occupied, it overwrittes the
last voice.

		while (Instrument_samples[Cc] != 0 && Cc < Voices - 1) { ++Cc; }
		Instrument_samples[Cc] = Samples_per_note;
		Cc = 0;

The musician should be aware how to use his audio system before the samples are called.
For example, buffer a sample block in the moment the system can be busy, and the samples
are going to be ready without much processing when those are called.

### SAMPLING SYSTEM:
Now that the instrument knows what sample we want, let's call it!
For that, the progam loops for each instrument again!
And for each instrument, it loops for each voice asking for a number different than '0'.

If the number is not '0', it output a number for frequency, which can be ignored, but can help
by making you avoid transforming MIDI note to frequency from the instrument.
Then it asks the instrument for the audio sample and divides it by "Gg" (imagine it like an inverse
master gain). It also increments "Cc", that is used to normalize the audio signal, but you can make
your sampling system without the use of this variable, and the DAC pre-processing will set it to '1'.
"Cc" is a general counter that should be inside a writtable memory, like a RAM, but should be used
with care, because unknow things may end up using this variable.
The sampling system also decrements the number of samples that is left to be asked to the instrument.

		for (Voice = 0; Voice < Instrument_Voices; ++Voice)
		{
			if (Instrument_samples != 0)
			{
				Instrument_Freq = MtoF[Instrument_MIDI_note];
				Instrument_Voice = Voice;
				y += Instrument_audio_sample(x) / Gg;
				--Instrument_samples; ++Cc;
			}
		}

### DAC:
Not technically DAC in this class, but the final processing that will send the samples to DAC!
It would be technically DAC if this engine is made as hardware!
It works with PCM!

The DAC is simple, however, inside this class, you should write your own DAC if you don't want 'float'
or 'double' to register 8-bit samples to the DAC buffer.

The hardware would have a specific DAC program which would deal with all sort of audio formats. Maybe
this class will also do that in the future.

For now, 'float' and 'double' outputs an 8-bit sample. But you can use integer types for bigger
samples, however, your audio system (SigPins) should have the same return type.

You can log the maximum absolute value played, this makes easier to find clipping audio.

It has 255 master gain levels, which would represent a '0 to 1' gain margin.

It writes a sample in the DAC Sample block (buffer) in the position:
		"BUF[Actual_Sample % BUFSIZE] = Sample;"

if "Actual_Sample % BUFSIZE == BUFSIZE - 1", it pauses the system to play it for 'BUFSIZE' time:
			"1000.0 * BUFSIZE / SampleRate"

Consequently, the bigger the sample-block is, the faster your system need to process the samples
to avoid interruptions in the audio or other artifacts.

### CIRCUIT BOARD:
#  = PCB; [] = Connectors; . = Pins; : = I. Circ.;

|[..........&UI32PatPins..........][CALLINTR]| // Pin inputs. A connector to send signal that a loop happened (next instrument)
|[CLK]##:COUNTER:############################| // CLK the system, and an IC to count the pins, maybe flip-flops
|############:           :###########[SIGOUT]| // Send a number to pick an instrument, then send protocol data to instrument
|############: SYSTEM IC :###########[SIG IN]| // Receive audio sample from the instrument
|[DATAOUT]###:           :###:DSP:##[SPEAKER]| // Raw audio data output and outputs DAC audio to speaker!
*/
template <class PATSIZE, class SIGTYPE, uint32_t SRATE,	const uint16_t BUFSIZE, const uint8_t INSTR, const uint8_t VOICES>
class ysxMSENG_PCB_ALPHA1
{
public:
	// SDL stuff, but a DSP would be here if on a PCB:
	SDL_AudioDeviceID DeviceID;
	char Device[512]; // Maybe it should be bigger is segfault happens, this is what happens when you use C...

	/*There are some I pins and some O pins, this array pretends to be both :
	Some future versions of the hardware may accept different types of cables to
	connect guitars, keyboards and MIDI, but 'ALPHA1' accepts only small electronics
	signals, like, chiptune. The oscillators can be done with a ROM	with a look-up
	table looping, a program in an Arduino, a small PCB oscillators	that are activated
	to record a sample block to output when called or anything you creatively think of.
	But it needs to be something that receives a call from the engine and returns a
	single audio sample back to the engine.
	The 'SigSynth' class is a class with all the memory space for protocol data	inside
	it, but on a real hardware, it would depend of the audio system from the user.*/
	std::array<ysxSIG_Synth<SIGTYPE>*, INSTR> SigPins;
	
	// Input pinning in the board to make bitwise music patterns,
	// this would be the actual hardware connection to the board
	// which can be freely changed at any time:
	PATSIZE* PatPins;

	ysxWAV_File* wavf; // RIFF WAVE file
	std::string WAVFileName = "!TESTWAV.wav";

	// !!! TO BE DESIGNED A HARDWARE EMULATION FOR THIS:
	std::string LOG; bool bLOG = false;

	// #################################################
	// ### MEMORY ###
	ysxMSENG_ROM_Map<PATSIZE, SRATE>* ROM;
	ysxMSENG_RAM_Map<SIGTYPE, BUFSIZE>* RAM;
	//STM8S003F3P6TR MC; // Micro-controller with 8kb Flash, 128b EEPROM and 1kb RAM
	// #################################################
	
	ysxMSENG_DATA_O<SIGTYPE, BUFSIZE> Out; // Output

	// #################################################
	
	// I changed this to not change pointers to 'nullptr', not only this avoid accidents with memory leak,
	// it is also more realistic in "hardware terms", since you probably wouldn't unplug things when
	// resetting the system.
	void RESET()
	{
		RAM->Cc = 0; RAM->Gg = 1;
		RAM->Max = 0;
		LOG.clear(); bLOG = false;
		RAM->n = 0; RAM->x = 0; RAM->g = 255; RAM->y = 0; RAM->b = 0;
		memset(&RAM->BUF[0], 127, RAM->BUF.size()); // Take in mind '127' is not for all types of audio!
		WAVFileName = wavf->Path;
	}

	/*#################################################
	############## COMPOSITIONS TOOLS ##############
	#################################################
	It is not nescessary to use those tools to make your music, you can write your own functions!
	However, some tools here might make your work easier.*/
	
	// BIT CHECK:
	// If 'n' is at the position to trigger a new bit in the pattern, returns 'true'.
	virtual bool BitCheck()
	{
		if (RAM->n % (uint32_t)RAM->nEnd == (uint32_t)round(RAM->b * RAM->L)) { return(true); }
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
					// This would be the protocol data, but would be useless to emulate it by how
					// it would work at hardware level, but, perhaps i do it one day:
					while (SigPins[P]->C[RAM->Cc] != 0 && RAM->Cc < VOICES - 1) { ++RAM->Cc; }
					SigPins[P]->C[RAM->Cc] = SigPins[P]->Size;
					// The data at hardware level would be 5 bytes:
					// [.|....]: struct ProtData { ui8 Voice; ui32 Samples; }
					// So the user's audio-system should have a memory space to set it!
				}
				RAM->Cc = 0; // Always clean the general counter after use! Never know what can use it and how!
			}
	}

	/*IT IS IMPORTANT TO ADVANCE THE BIT COUNTER AFTER THE INIT FUNCTIONS ARE DONE:
	The way i work is using a 'for-loop' with 'RAM->n' to check the samples and using
	'SmpInit'. Consequently, after 'RAM->n' reaches the next amount of samples to advance
	a bit, i call this function!*/
	virtual void BitCount() { ++RAM->b; RAM->b %= ROM->PatBits; }

	/*CALLS SIGNAL SAMPLES FROM SIGNAL SOURCES:
	The data is based on my signal processing class.
	At hardware level, i wanted my engine to have a single input cable and the rest of the
	information in the RAM.
	The input cable could be the typicall guitar cable, or the typicall speaker cable you
	insert in your computer.

	'IgnoreMtoF': Ignores the value 'MIDI.x'. 'Freq' should be manually set by the user for each note.

	Take care with low 'Gg', the main formula is that:
	RAM->y += SigPins[I]->IO(RAM->x) / (float)RAM->Gg;
	*/
	virtual void Sampling(bool IgnoreMtoF = false)
	{
		if (!RAM->Gg) { RAM->Gg = 1; } // No zero division for you!
		for (uint8_t I = 0; I < INSTR; ++I)
		{
			if (SigPins[I])
			{
				// This loop can accept instruments with different amount of voices, so take care of how you design your instrument:
				for (uint8_t C = 0; C < SigPins[I]->C.size(); ++C)
				{
					if (SigPins[I]->C[C])
					{
						if (!IgnoreMtoF) { SigPins[I]->Freq = ROM->MtoF[SigPins[I]->MIDI[C].x]; }
						SigPins[I]->V = C; // Send the number of the voice in use
						RAM->y += SigPins[I]->IO(RAM->x) / (float)RAM->Gg; // Gets audio sample and divide by the gain
						--SigPins[I]->C[C]; //++RAM->Cc; // Decrement the number of samples left to play, and increses general counter (which is not vital)
					}
				}
			}
		}
	}

	// #################################################

	// PRE-PROCESS FOR DIGITAL TO ANALOG CONVERTER:
	// Process the data, add it to the buffer (sample-block), and send
	// to the DSP that makes the DAC process (output audio to speakers):
	virtual void DAC()
	{
		if (RAM->Cc == 0) { RAM->Cc = 1; } RAM->y /= RAM->Cc; // Gain stuffs
		if (std::is_floating_point<SIGTYPE>::value)
		{			
			if (RAM->y > 1) { RAM->y = 1; } if (RAM->y < -1) { RAM->y = -1; } // Normalize
			// (y + 1) * 127.5 * g * 0.00392156862745098: // This giant number is: '1/255'
			RAM->BUF[RAM->n % BUFSIZE] = 0.5 * RAM->g * (RAM->y + 1); // Create another DAC function if you want more than 8 bits per sample
			if (wavf) { wavf->wavFile.write((char*)&RAM->BUF[RAM->n % BUFSIZE], 1); }
			if (RAM->n % BUFSIZE == BUFSIZE - 1) { SDL_Delay(1000.0 * BUFSIZE / SRATE); } // Playback after sample block is filled
			//std::cout << "RAM->BUF[] = " << (short)RAM->BUF[RAM->n % BUFSIZE] << "\n ";
		}
		else
		{
			*(SIGTYPE*)&RAM->BUF[(RAM->n * sizeof(SIGTYPE)) % (BUFSIZE * sizeof(SIGTYPE))] = 0.00392156862745098 * RAM->g * RAM->y;
			if (wavf) { wavf->wavFile.write((char*)&RAM->BUF[(RAM->n * sizeof(SIGTYPE)) % (BUFSIZE * sizeof(SIGTYPE))], sizeof(SIGTYPE)); }
			if (RAM->n % BUFSIZE == BUFSIZE - 1) { SDL_Delay(1000.0 * BUFSIZE / SRATE); }
		}
		if (fabs(RAM->y) > RAM->Max)
		{
			if (bLOG)
			{
				LOG += "Y MAX = " + std::to_string(RAM->y) + " | BYTE: " + std::to_string((RAM->y + 1) * 127.5);
				LOG += " | Gg: " + std::to_string(RAM->Gg);
				if (wavf) { LOG += " | TELLP: " + std::to_string(wavf->wavFile.tellp()) + '\n'; }
			}
			RAM->Max = fabs(RAM->y);
		}
		RAM->y = 0; RAM->Cc = 0; // <------- RESETS
	}
/*#################################################
############## USER TOOLS ##############
#################################################*/
	
	void ResumeEngine()
	{
	   if (bLOG) { LOG += "Playing, 'n = " + std::to_string(RAM->n) + "'!\n"; }
		#ifdef USE_SDL3
		SDL_PlayAudioDevice(DeviceID);
		#endif
		#ifdef USE_SDL2
		SDL_PauseAudio(0);
		#endif
	}


	/*Make noise! Assuming that you built SDL2 lib!
	Use 'SDL_CloseAudioDevice(1);' function to close the audio!
	And if you decide to open it again, use this:
	Device = SDL_OpenAudioDevice(NULL, 0, &RAM->Spec, NULL, SDL_AUDIO_ALLOW_ANY_CHANGE);*/
	void StartEngine()
	{
		//RAM->Gg = INSTR; // Max gain possible (if not clipping)
		// ####### CALLBACK #######
		if (bLOG) { LOG += ysxSDL_AU_GetSpecInfo(RAM->Spec); LOG += ysxSDL_AU_GetDataInfo(RAM->sD); }
		ResumeEngine();
	}

	// Assuming that 'DeviceID' is not '< 0':
	void PauseEngine()
	{
		#ifdef USE_SDL3
		SDL_PauseAudioDevice(DeviceID);
		#endif
		#ifdef USE_SDL2
		SDL_PauseAudio(1);
		#endif
		if (bLOG) { LOG += "Audio paused, 'n = " + std::to_string(RAM->n) + "'!\n"; }
	}

	// #################################################

	// EXAMPLE OF A LIMITED WAY TO COMPOSE USING A SIMPLE FUNCTION:
	void ExampleBasicMusic()
	{
		StartEngine();
		for (RAM->n = 0; RAM->n < RAM->Samples; ++RAM->n)
		{
			RAM->x = ROM->t * RAM->n;
			if (BitCheck()) // If 'n' triggers new bit in a pattern. Regardless if bit is on or off.
			{
				for (uint8_t m = 0; m < INSTR; ++m)
				{
					// COMPOSE PER INSTRUMENT HERE!
					SmpInit(m); // Initializes instrument data
				}
				BitCount();
			}
			Sampling(); // Sample for buffer
			DAC(); // Buffer and Play!
		}
		PauseEngine();
		RAM->n = 0;
	}

	// #################################################

	// CAREFUL USING THIS FUNCTION, AS IT SETS POINTERS TO 'nullptr' AND MAY GIVE YOU MEMORY LEAK!
	// THIS FUNCTION IS USED BY THE CONSTRUCTOR!
	void INIT()
	{
		#ifdef USE_SDL3
		if (SDL_Init(SDL_INIT_AUDIO) < 0) { std::cerr << "SDL_Init failed!\nERROR: " << SDL_GetError() << "\n\n"; }
		DeviceID = SDL_OpenAudioDevice(Device, 0, &RAM->Spec, NULL, SDL_AUDIO_ALLOW_ANY_CHANGE);
		#endif
		#ifdef USE_SDL2
		DeviceID = SDL_OpenAudio(&RAM->Spec, NULL);
		#endif
		if (DeviceID < 0)
		{
			std::cerr << "Shit happened! Could not open device!\n";
			std::cerr << "ERROR: " << SDL_GetError() << "\n\n";
		}
		else { std::cout << "Device gotten: " << DeviceID << "\n\n"; }
		RAM->sD.Pos = &RAM->BUF[0]; RAM->sD.Samples = BUFSIZE; RAM->sD.Count = 0; RAM->Spec.userdata = &RAM->sD;
		RAM->Spec.callback = ysxSDL_AU_SignalCall;
		memset(&RAM->BUF[0], 127, RAM->BUF.size()); // Signal
		for (RAM->n = 0; RAM->n < INSTR; ++RAM->n) { SigPins[RAM->n] = nullptr; } RAM->n = 0; // Start with clean pointers
		PatPins = nullptr;
		Out.SigO = &wavf->wavFile; wavf->wavFile.seekp(44); // (std::fstream*)Out.SigO->seekp(44);
		WAVFileName = wavf->Path;
	}

	ysxMSENG_PCB_ALPHA1(ysxMSENG_ROM_Map<PATSIZE, SRATE>* SetROM, ysxMSENG_RAM_Map<SIGTYPE, BUFSIZE>* SetRAM, ysxWAV_File* WAV)
	{
		wavf = WAV; ROM = SetROM; RAM = SetRAM; INIT();
	}
		
	~ysxMSENG_PCB_ALPHA1()
	{
		RESET(); // Don't forget to clean your pointers!
		#ifdef USE_SDL3
		SDL_CloseAudioDevice(DeviceID);
		SDL_QuitSubSystem(SDL_INIT_AUDIO);
		#endif
		#ifdef USE_SDL2
		SDL_CloseAudio();
		#endif
	}
};

#endif // SCPARSE_
