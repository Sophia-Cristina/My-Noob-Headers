#pragma once

#ifndef YSXSYNTH_H
#define YSXSYNTH_H
// Time is included by 'ysxSDLAudio.h'

// #####################
// ####### By Sophia Cristina
// ####### Codes about synth and related, for SDL Audio
// #####################

// ############################################################################################################################################
// ################################################# NOTES AND ATTENTIONS #################################################
// !!!!!!!	
// !!!!!!!	CATALOGUE ANY CHANGE THAT CAN AFFECT CODE VERSIONS:
// !!!!!!!	* PAY ATTENTION to any change that may affect 'ysxElectr.h' classes, since electronic devices normally have alike terms to music devices;
// !!!!!!!	
// ################################################# NOTES AND ATTENTIONS #################################################
// ############################################################################################################################################

/*
Glos.:
A = A.ttack; D = D.ecay; S = S.ustain; R = R.elease;
AD = A.ttack.D.ecay. A system where 'A' is a percentage of the playing time, and 'D' the end gain;
 ~ Ex.: to 15, A = 7; D = 7;
 ~ Until 0.467 seconds, there will happen the A.ttack.
 ~ After that, signal loses gain until D.ecay, the end gain would be 0.467;
F = F.loat, F.lag, F.requency; // Or something else if i miss
FFT = F.ast-F.ourier-T.ransform;
Flt32 = float; // If a float, *probably* something from -1 to 1, or 0 to 1
pSomething = probably 'the p.ower' or 'a p.ower' or 'iterator' or 'p.ointer' of 'Something';
PW = P.ulse-W.idth;
SRate = S.ample Rate;
BS = B.lock S.ize;
*/

// #################################################
// REFERENCES:
// [1] The Computer Music Tutorial - Curtis Roads
// #################################################

// #################################################
// ####### DRUM KIT #######

// KICK SAMPLE, Kick(x), HEHE:
// sin(x*Freq*TAU*((1 - x)^PF)) * (1 - x)^PA
// You can use bigger frequencies and changes in curves to make a hit or click sound.
double KickSmpD(double x, double Freq, double pFreq, double pAmp, double Atk, double sec = 1)
{
	if (sec <= 0) { sec = 1; } if (x < 0) { x *= -1; }
	if (x > sec) { x = (x - floor(x)) - (sec - floor(sec)); }
	float g = x < Atk ? x / Atk : 1;
	return(sin(x * (Freq * TAU * pow(1 - x / sec, pFreq))) * pow(1 - x / sec, pAmp) * g);
}
float KickSmpF(float x, float Freq, float pFreq, float pAmp, float Atk, double sec = 1)
{
	if (sec <= 0) { sec = 1; } if (x < 0) { x *= -1; }
	if (x > sec) { x = (x - floor(x)) - (sec - floor(sec)); }
	float g = x < Atk ? x / Atk : 1;
	return(sin(x * (Freq * TAU * pow(1 - x / sec, pFreq))) * pow(1 - x / sec, pAmp) * g);
}
uint8_t KickSmpU8(float x, float Freq, float pFreq, float pAmp, float Atk, double sec = 1)
{
	if (sec <= 0) { sec = 1; } if (x < 0) { x *= -1; }
	if (x > sec) { x = (x - floor(x)) - (sec - floor(sec)); }
	float g = x < Atk ? x / Atk : 1;
	return(((sin(x * (Freq * TAU * pow(1 - x / sec, pFreq))) * pow(1 - x / sec, pAmp)) + 1) * 127.5 * g);
}
uint16_t KickSmpU16(float x, float Freq, float pFreq, float pAmp, float Atk, double sec = 1)
{
	if (sec <= 0) { sec = 1; } if (x < 0) { x *= -1; }
	if (x > sec) { x = (x - floor(x)) - (sec - floor(sec)); }
	float g = x < Atk ? x / Atk : 1;
	return(((sin(x * (Freq * TAU * pow(1 - x / sec, pFreq))) * pow(1 - x / sec, pAmp)) + 1) * 32767.5 * g);
}
uint32_t KickSmpU32(float x, float Freq, float pFreq, float pAmp, float Atk, double sec = 1)
{
	if (sec <= 0) { sec = 1; } if (x < 0) { x *= -1; }
	if (x > sec) { x = (x - floor(x)) - (sec - floor(sec)); }
	float g = x < Atk ? x / Atk : 1;
	return(((sin(x * (Freq * TAU * pow(1 - x / sec, pFreq))) * pow(1 - x / sec, pAmp)) + 1) * 2147483647.5 * g);
}

// GENERATE A KICK BUFFER, USE BYTES 1, 2 OR 4:
std::vector<uint8_t> KickSmpBuf(uint32_t Size, uint32_t SRate, uint8_t Bytes, float Freq, float pFreq, float pAmp, float Atk)
{
	if (Atk > 1) { Atk = 1; } if (Atk < 0) { Atk = 0; }
	uint32_t BSize = Size * Bytes, ASize = BSize * Atk;
	std::vector<uint8_t> B(BSize);
	
	if (Bytes == 4 || Bytes == 2 || Bytes == 1)
	{
		for (int n = 0; n < BSize; n += Bytes)
		{
			double x = (double)n / SRate;
			double b = sin(x * Freq * TAU * pow(1 - x, pFreq)) * pow(1 - x, pAmp);
			if (n < ASize) { b *= ((double)n / ASize); }
			if (Bytes == 4)	{ uint32_t a = (b + 1) * 2147483647.5; memcpy(&B[0], &a, Bytes); }
			else if (Bytes == 2) { uint16_t a = (b + 1) * 32767.5; memcpy(&B[0], &a, Bytes); }
			else { B[n] = (b + 1) * 127.5; }
		}
	}
	else { std::cout << "Sorry, for now, this only supports '1', '2' and '4' bytes format!\n"; }
	return(B);
}

// #################################################
// ####### INSTRUMENT FOR 'SIGNAL STREAM' INHERITANCE
// #################################################

// ### IO PLUGS:
// Add Seconds
struct iopSec : public SigStream<float> { float sec = 1; void SecBySize(uint32_t SRate) { sec = Size / SRate; } };
// ###

// KICK IO:
class IO_Kick : public iopSec
{
private:
	float g = 0;
public:
	float Freq = 1, pFreq = 1, pAmp = 1, Atk = 0.05;

	// USE TURNS! Preferably 32b:
	float IO(float x) override
	{
		if (sec <= 0) { sec = 1; } if (x < 0) { x *= -1; }
		if (x > sec) { x = (x - floor(x)) - (sec - floor(sec)); }
		if (x < Atk && Atk != 0) { g = x / Atk; }
		x = sin(x * Freq * TAU * pow(1 - x / sec, pFreq)) * pow(1 - x / sec, pAmp) * g;
		
		return(x);
	}
};

// KICK USES FEW BYTES:
class IO_KickMini : public SigStream<float>
{
private:
	float g = 0;
public:
	float Freq = 1;
	uint8_t PFPA = 8; // 15 levels of power, 0xF0 = pFreq; 0x0F = pAmp
	uint8_t AtkSec = 1; // 15 levels of: 0xF0 = Attack; 0x0F = sec / 3; 5 seconds max

	// USE TURNS! Preferably 32b:
	float IO(float x) override
	{
		if ((AtkSec & 15) == 0) { ++AtkSec; } if (x < 0) { x *= -1; }
		if (x > (AtkSec & 15) / 45.0) { x = (x - floor(x)) - ((AtkSec & 15) / 45.0 - floor((AtkSec & 15) / 45.0)); }
		if (x < (AtkSec >> 4) / 15.0 && (AtkSec >> 4) / 15.0 != 0) { g =  x / ((AtkSec >> 4) / 15.0); }
		x = sin(x * Freq * TAU * pow(1 - x / ((AtkSec & 15) / 45.0), (PFPA >> 4) / 15.0)) * pow(1 - x / ((AtkSec & 15) / 45.0), (PFPA & 15) / 15.0) * g;
		
		return(x);
	}
};

// KICK USES EVEN FEWER BYTES (WORK IN PROGRESS):
// 'x' is like fixed, 0 to 255 is 0 to 2*PI.
// 'g'ain is 0 to 255 as 0 to 1.
// 'Freq'uency is 0 to 255 equal MtoF.
class IO_KickMicro : public SigStream<uint8_t> // !!! WIP !!!
{
private:
	uint8_t g = 0;
public:
	// MIDI | 15 levels of power, 0xF0 = pFreq; 0x0F = pAmp | 15 levels of: F0 = Atk; 0F = sec / 3; 5 sec max
	uint8_t Freq = 1, PFPA = 8, AtkSec = 1;

	// USE TURNS! Preferably 32b:
	uint8_t IO(uint8_t ui8) override
	{
		if ((AtkSec & 15) == 0) { ++AtkSec; } if (ui8 < 0) { ui8 *= -1; }
		//if ((ui8 / 255.0) > (AtkSec & 15) / 45.0) { ui8 = ((ui8 / 255.0) - floor((ui8 / 255.0))) - ((AtkSec & 15) / 45.0 - floor((AtkSec & 15) / 45.0)); }
		//if (ui8 < (AtkSec >> 4) / 15.0 && (AtkSec >> 4) / 15.0 != 0) { g = ui8 / ((AtkSec >> 4) / 15.0); }
		if (ui8 > (AtkSec & 15) * 17) { ui8 %= (AtkSec & 15) * 17; }
		if (ui8 < (AtkSec >> 4) * 17 && AtkSec >> 4 != 0) { g = (AtkSec >> 4) * 17; }
		ui8 = sin((ui8 / 255.0) * MtoFMini(Freq) * TAU * pow(1 - (ui8 / 255.0) / ((AtkSec & 15) / 45.0), (PFPA >> 4) / 15.0)) * pow(1 - (ui8 / 255.0) / ((AtkSec & 15) / 45.0), (PFPA & 15) / 15.0) * (g / 255.0);
		return(ui8);
		//sin((n / 255.0) * M * TAU * pow(1 - (n / 255.0) / s, p) * pow(1 - (n / 255.0) / s, q) * (g / 255.0);
	}
};


// KICK INSTRUMENT, SIN-TRI-RECT:
class IO_KickSTR : public iopSec
{
private:
	float g = 0;
public:
	float Freq = 1, RatioT = 1, RatioR = 1, pFreq = 1, pAmp = 1, Atk = 0.05;

	// USE TURNS! Preferably 32b:
	float IO(float x) override
	{
		if (sec <= 0) { sec = 1; } if (x < 0) { x *= -1; }
		if (x > sec) { x = (x - floor(x)) - (sec - floor(sec)); }
		if (x < Atk && Atk != 0) { g = x / Atk; }
		x = (sin(x * Freq * TAU * pow(1 - x / sec, pFreq)) * pow(1 - x / sec, pAmp) * 0.3 +
			tri(x * Freq * RatioT * TAU * pow(1 - x / sec, pFreq)) * pow(1 - x / sec, pAmp) * 0.3 +
			rect(x * Freq * RatioR * TAU * pow(1 - x / sec, pFreq)) * pow(1 - x / sec, pAmp) * 0.3) * g;
		//if (fabs(x) > 1) { std::cout << "CLIP!!! x = " << x << '\n'; }
		return(x);
	}
};

// #################################################
// ####### OSCILLATORS #######

// SIMPLE OSCILLATOR:
class IO_SimpleOSC : public SigStream<float>
{
public:
	float Freq = 1, y = 0;
	uint8_t n = 0;
	uint8_t F = 1; // Flags, 1111 15-levels PW, or phase for others than rect | 1111 saw, rect, tri, sine

	// USE TURNS! Preferably 32b:
	float IO(float x) override
	{
		if (F == 0) { F = 1; }
		x *= 6.283185; y = 0; n = 0;
		if (F & 1) { y += sin(Freq * x + 6.283185 * (F >> 4) / 15.0); ++n; }
		if (F & 2) { y += tri(Freq * x + 6.283185 * (F >> 4) / 15.0); ++n; }
		if (F & 4) { y += rect(Freq * x, (F >> 4) / 15.0); ++n; }
		if (F & 8) { y += saw(Freq * x + 6.283185 * (F >> 4) / 15.0); ++n; }
		if (n == 0) { n = 1; } // Just for safety
		y /= n;
		return(y);
	}
};

// OSCILLATOR WITH 15 LEVELS OF ATTACK AND DECAY (NOT TESTED YET):
class IO_OSC_AD : public SigStream<float>
{
private:
	float y = 0, At = 0; uint8_t n = 0;
public:
	float Freq = 1;
	uint8_t AD = 0, sec = 0; // AD >> 4 = Attack; AD & 15 = Decay; sec = 1 / 25.5; 10 secs
	uint8_t F = 1; // Flags, 1111 15-levels PW or phase for non-rect | 1111 saw, rect, tri, sine
	
	// USE TURNS! Preferably 32b:
	float IO(float x) override
	{
		if (F & 15 == 0) { F += 1; } if (sec == 0) { sec = 1; }
		y = 0; n = 0; At = (AD >> 4) / 15.0; //std::cout << "At: " << At << '\n';
		if (x > sec * 0.039216) { x -= sec * 0.039216; x-= floor(x); }
		if (F & 1) { y += sin(Freq * x * 6.283185 + 6.283185 * (F >> 4) / 15.0); ++n; }
		if (F & 2) { y += tri(Freq * x * 6.283185 + 6.283185 * (F >> 4) / 15.0); ++n; }
		if (F & 4) { y += rect(Freq * x * 6.283185, (F >> 4) / 15.0); ++n; }
		if (F & 8) { y += saw(Freq * x * 6.283185 + 6.283185 * (F >> 4) / 15.0); ++n; }
		if (n == 0) { ++n; } // Just for safety
		y /= n;
		if (x < (AD >> 4) * sec / 3825.0 && (AD >> 4) * sec / 3825.0 != 0) { y *= x / ((AD >> 4) * sec / 3825.0); }
		else
		{
			/* Wolfram in:
			(d * y * ((s * 0.039216 - a * s / 3825.0 - (x - a * s / 3825.0)) / (s * 0.039216 - a * s / 3825.0))) + y * (1 - d);
			(y * (AD & 15) / 15.0) * (((x - sec * 0.039216) / (((AD >> 4) * sec / 3825.0) - sec * 0.039216)) - 1) + y;*/
			y = (y * (AD & 15) / 15.0) * (((x - sec * 0.039216) / (((AD >> 4) * sec / 3825) - sec * 0.039216)) - 1) + y;
			y *= 0.5;
		}
		return(y);
	}

	// CAREFUL WITH OVERFLOW:
	void SecBySize(uint32_t SRate) { sec = (Size / SRate) * 25.5; }
};

// ###############################################################################################################################################################################
// ###############################################################################################################################################################################
// ###############################################################################################################################################################################

#endif // SCPARSE_