#pragma once

#ifndef YSXINTEL4003_H
#define YSXINTEL4003_H

// #####################
// ####### By Sophia Cristina
// ####### Intel 400x emulator.
// #####################

// #################################################
/* REFERENCES:
[1] https://codeabbey.github.io/heavy-data-1/msc-4-asm-manual-1973.pdf
*/
// #################################################


/*#################################################
############## CLASSES / STRUCTS ##############*/


/*####### 4003 #######
          ______
CP      -|      |- E
DATA_IN -| 4003 |- SO
Q0      -|      |- VDD
Q1      -|      |- Q9
VSS     -|      |- Q8
Q2      -|      |- Q7
Q3      -|      |- Q6
Q4      -|______|- Q5
10-BIT SERIAL-IN / PARALLEL-OUT SHIFT REGISTER
*/

class ysxEMU_Intel4003 : public ysxEMU_MSC_4
{
public:

	// PINS:
	enum Pinning
	{
		CP = 1, DATA_IN = 1 << 1, Q0 = 1 << 2, Q1 = 1 << 3, VSS << 4, Q2 = 1 << 5, Q3 = 1 << 6, Q4 = 1 << 7,
		Q5 = 1 << 8, Q6 = 1 << 9, Q7 = 1 << 10, Q8 = 1 << 11, Q9 = 1 << 12, VDD = 1 << 13, SO = 1 << 14, E = 1 << 15
	};
	uint16_t* Pins = nullptr;

	// SHIFT REGISTER:
	uint16_t ShiftReg = 0;

	// CLOCK STATE:
	uint8_t PrevCP = 0;

	// OUTPUT:
	void UpdateOutputs()
	{
		if (!Pins) { return; }
		*Pins &= ~(Q0 | Q1 | Q2 | Q3 | Q4 | Q5 | Q6 | Q7 | Q8 | Q9 | SO); // Clear the output pins first.
		if (*Pins & E) { *Pins |= (ShiftReg & 0x03FF) << 2; } // Parallel outputs are enabled when E is HIGH.
		if (ShiftReg & 0x0200) { *Pins |= SO; } // Serial output is independent of E.
	}

	// SYSTEM:
	void Process() override
	{
		if (!Pins) { return; }
		uint8_t CurrentCP = (*Pins & CP) != 0;
		// Shift on the rising edge of CP:
		if (CurrentCP && !PrevCP) { uint8_t Data = (*Pins & DATA_IN) != 0; ShiftReg = ((ShiftReg << 1) | Data) & 0x03FF; }
		PrevCP = CurrentCP;
		UpdateOutputs();
	}
};


// #################################################


#endif
