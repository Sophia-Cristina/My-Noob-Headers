enum ePtrn { pK, pS, pHH, pRide, pCrash, pPads, pBass, pMid, pHigh };
PATSIZE Ptrns[INSTR]; for (uint8_t n = 0; n < INSTR; ++n) { Ptrns[n] = 0; }
Ptrns[pK] = 0x80008000;

// #####################

cout << "<v^> INSTRUMENTS <v^>\n\n";
IO_KickSTR<VOICES> K1; K1.Size = 2.5 * SRATE; //K1.SecBySize(SRATE);
for (uint8_t n = 0; n < VOICES; ++n) { K1.MIDI[n].x = ScrtMsn0[0]; K1.MIDI[n].y = 127; }
K1.RatioR = 0.777778; K1.RatioT = 7.778 / 7.0;
K1.pFreq = 1.5; K1.pAmp = 1.5; K1.Atk = 0.07;
MSEA1.SigPins[pK] = &K1;
//pS, pHH, pRide, pCrash, pPads

// #####################

//IO_OSC_AD OSC1; OSC1.Size = 0.49 * SRATE;
IO_OSC_AD_FMSum<VOICES> OSC1; OSC1.Size = 0.49 * SRATE;
for (uint8_t n = 0; n < VOICES; ++n) { OSC1.MIDI[n].x = ScrtMsn1[0]; OSC1.MIDI[n].y = 127; }
OSC1.F = 0x7f; OSC1.AD = 0x7f; // (PW or Phase * TAU) | 15.0; sw, r, t, s | Atk and Dcy: 0 to 15;
OSC1.FMFreq = ScrtMsn2[0] / 56.0; OSC1.FMAmp = ROM.MtoF[3];
MSEA1.SigPins[pBass] = &OSC1;

// #####################

IO_OSC_AD<VOICES> OSC2; OSC2.Size = 0.67 * SRATE;
for (uint8_t n = 0; n < VOICES; ++n) { OSC2.MIDI[n].x = 77; OSC2.MIDI[n].y = 127; }
OSC2.F = 0x3A; OSC2.AD = 0x3f;
MSEA1.SigPins[pMid] = &OSC2;

// #####################

IO_CCRDSYNTH<VOICES> OSC3(7, 0, 0.91, 0x7f); OSC3.Size = 1.125 * SRATE;
for (uint8_t n = 0; n < VOICES; ++n) { OSC3.MIDI[n].x = 72; OSC3.MIDI[n].y = 127; }
MSEA1.SigPins[pHigh] = &OSC3;

// #####################
// #####################
// #####################