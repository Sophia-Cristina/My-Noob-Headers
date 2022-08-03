#pragma once

#ifndef YSXMINISENGINSTR_H
#define YSXMINISENGINSTR_H

// #####################
// ####### By Sophia Cristina
// ####### This file is used by the Mini Engine to be modified by the user!
// ####### Check informations on the 'ysxMiniSEng.h'!
// #####################

//{
	//bool NewR = 1;
	//while (NewR)
	//{
	//	cout << "New Random?: "; cin >> NewR;
		//Instrs[pK].Ptrn = (rand() % 65535) + (rand() % 65535) * 65536; cout << "!!! Kick: " << Instrs[pK].Ptrn << " !!!\n";
		//Instrs[pHigh].Ptrn = (rand() % 65535) + (rand() % 65535) * 65536; cout << "!!! High: " << Instrs[pHigh].Ptrn << " !!!\n";
		//Instrs[pMid].Ptrn = (rand() % 65535) + (rand() % 65535) * 65536; cout << "!!! Mid: " << Instrs[pMid].Ptrn << " !!!\n";
		//Instrs[pBass].Ptrn = (rand() % 65535) + (rand() % 65535) * 65536; cout << "!!! Bass: " << Instrs[pBass].Ptrn << " !!!\n";
	//}
//}
	//Instrs[pK].Ptrn = 0x80008000;
	//Instrs[pBass].Ptrn = 0xffffffff;
	//Instrs[pMid].Ptrn = 1;
	//Instrs[pHigh].Ptrn = 1;

	//Instrs[pK].Ptrn = 0;
	//Instrs[pBass].Ptrn = 0;
	//Instrs[pMid].Ptrn = 0;
	//Instrs[pHigh].Ptrn = 0;

// #####################

cout << "<v^> INSTRUMENTS <v^>\n\n";
IO_KickSTR K1; K1.Size = 2.5 * SRATE; //K1.SecBySize(SRATE);
K1.C = vector<uint32_t>::vector(VOICES); K1.MIDI = vector<Point<uint8_t>>::vector(VOICES);
for (uint8_t n = 0; n < VOICES; ++n) { K1.MIDI[n].x = ScrtMsn0[0]; K1.MIDI[n].y = 127; }
K1.RatioR = 0.777778; K1.RatioT = 7.778 / 7.0;
K1.pFreq = 1.5; K1.pAmp = 1.5; K1.Atk = 0.07;
Instrs[pK].S = &K1;
//pS, pHH, pRide, pCrash, pPads

// #####################

//IO_OSC_AD OSC1; OSC1.Size = 0.49 * SRATE;
IO_OSC_AD_FMSum OSC1; OSC1.Size = 0.49 * SRATE;
OSC1.C = vector<uint32_t>::vector(VOICES); OSC1.MIDI = vector<Point<uint8_t>>::vector(VOICES);
for (uint8_t n = 0; n < VOICES; ++n) { OSC1.MIDI[n].x = ScrtMsn1[0]; OSC1.MIDI[n].y = 127; }
OSC1.F = 0x7f; OSC1.AD = 0x7f; // (PW or Phase * TAU) | 15.0; sw, r, t, s | Atk and Dcy: 0 to 15;
OSC1.FMFreq = ScrtMsn2[0] / 56.0; OSC1.FMAmp = MtoF[3];
Instrs[pBass].S = &OSC1;

// #####################

IO_OSC_AD OSC2; OSC2.Size = 0.67 * SRATE;
OSC2.C = vector<uint32_t>::vector(VOICES); OSC2.MIDI = vector<Point<uint8_t>>::vector(VOICES);
for (uint8_t n = 0; n < VOICES; ++n) { OSC2.MIDI[n].x = 77; OSC2.MIDI[n].y = 127; }
OSC2.F = 0x3A; OSC2.AD = 0x3f;
Instrs[pMid].S = &OSC2;

// #####################

IO_CCRDSYNTH OSC3; OSC3.Size = 1.125 * SRATE; OSC3.C = vector<uint32_t>::vector(8);
OSC3.D = 72; OSC3.SecBySize(SRATE);
OSC3.AD = 0x7f; //OSC3.AD = 0xa9;
OSC3.Cs = CS.Cs; OSC3.Ratio = CS.Ratio;
Instrs[pHigh].S = &OSC3;

// #####################
// #####################
// #####################

#endif