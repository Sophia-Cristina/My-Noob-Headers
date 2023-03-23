#pragma once

#ifndef YSX4K4S_H
#define YSX4K4S_H

// #####################
// ####### By Sophia Cristina
// ####### Fantasy system (mainly a console for gaming)
// ####### using Intel 4004 as processor.
// #####################

// I expect you to include my Intel 4004 header.

// #################################################
/* REFERENCES:
[1]
*/
// #################################################

// #################################################
/*############## 4K4S CARTRIDGE ##############
This is the cartridge of my fantasy console called 4K4S, check the class 'ysxEMU_4K4S'
for more information!

This class is for inheritance, it is just based on the design of the console slot
for the cartridge. The designer should make a class to make his cartridge as he
whishes as long it is inside the parameters of this class.*/
class ysxEMU_4K4SCart : public ysxEMU_Component<uint8_t>
{
public:

};
 
// #################################################
/*############## 4K4S FANTASY CONSOLE ##############
4K4S stands for "4004 system". Which is a computer system focused in gaming.
You could call it a game-console, but it is also a computer and i designed it in a way
that can be used as a computer.
The name says it all, the CPU is an Intel 4004 4-bit processor.

The console have a single firmware 256 bytes ROM that will initialize everything. That
way, the programmer have lot of freedom to mess up with the entire console using
a cartridge.

The RAM system will be entirely inside the console, but nothing impedes the creativity
of the designer to add extra RAM inside the cartridge.

Upper versions may be more "low-level-ish" emulated...
*/
class ysxEMU_4K4S : public ysxEMU_Component<uint8_t>
{
private:
	uint8_t Count = 0;
	uint8_t ClkBit = 0;
	bool ClkCyc = false;

public:
	uint8_t Clock = 0xAA;
	
	ysxEMU_MSC_4_Bus BusROM;
	uint8_t CM_ROM = 0;
	uint8_t ROMPins;
	
	ysxEMU_MSC_4_Bus BusRAM;
	uint8_t CM_RAM[4] = { 0, 0, 0, 0 };
	uint8_t RAMPins[16];

	// ####### ICs #######
	ysxEMU_Intel4004CPU CPU;
	ysxEMU_Intel4001ROM ROMFirmW; // ROM for Firmware. May need more, for now, one for test, the rest of ROMs are on the cartridge
	ysxEMU_Intel4002RAM<0> RAMs0[8]; // There is two models of 4002, then you wont need fancy circuits to enjoy 16 RAM ICs
	ysxEMU_Intel4002RAM<1> RAMs1[8]; // I may change the number of RAMs eventually if i add other resources

	// #################################################

	ysxEMU_4K4S()
	{
		ROMFirmW.Bus = &BusROM; ROMFirmW.Pins = &ROMPins;
		for (uint8_t n = 0; n < 8; ++n)
		{
			RAMs0[n].Bus = &BusRAM; RAMs1[n].Bus = &BusRAM; RAMs0[n].Pins = &RAMPins[n]; RAMs1[n].Pins = &RAMPins[n + 8];
		}
		BusROM.VDD = 1; BusRAM.VDD = 1; // Turn on

		// PROGRAMMING FIRMWARE:
		// TEST PROGRAM: Set Reg to 'A', then set ACC to 5 and ADD both!
		ROMFirmW.ROM[0] = 0x20; ROMFirmW.ROM[1] = 0x0A; ROMFirmW.ROM[2] = 0xD5; ROMFirmW.ROM[3] = 0x81;
	}

	// #################################################

	// Ticks and make procedures:
	// W.I.P; later to add clock to make a difference and not just "Tick()".
	void Tick()
	{
		CPU.Tick();
		ROMFirmW.Tick();
		for (uint8_t n = 0; n < 8; ++n) { RAMs0[n].Tick(); }
		++Count;
		Count %= 8;
	}

	void RunClock()
	{
		if (ClkBit == 1 && Clock & (1 << ClkBit))
		{
			Tick();
			ClkCyc = true;
		}
		else if (Clock & (1 << ClkBit))
		{
			if (!ClkCyc)
			{
				Tick();
				ClkCyc = true;
			}
		}
		else { if (ClkCyc) { ClkCyc = false; } }
		++ClkBit;
		ClkBit %= 8;
		if (LOG) { LogState(); }
	}

	// #################################################

	std::string* LOG;
	bool LOG_On = false;
	bool LOG_PlotMemASCII = false;
	
	// if (LOG_On) { LOG_On = false; } else { LOG_On = true; }:
	void TurnAllLOGsOnOff()
	{
		if (LOG_On) { LOG_On = false; }	else { LOG_On = true; }
		if (ROMFirmW.LOG_On) { ROMFirmW.LOG_On = false; } else { ROMFirmW.LOG_On = true; }
		for (uint8_t n = 0; n < 8; ++n)
		{
			if (RAMs0[n].LOG_On) { RAMs0[n].LOG_On = false; } else { RAMs0[n].LOG_On = true; }
		}
	}

	void LogState()
	{
		*LOG += "\n### 4K4S:\n";
		*LOG += "# Bus ROM data:\nIO: " + std::to_string((short)BusROM.Data) + " | Bus RAM data: " + std::to_string((short)BusRAM.Data) + "\n";
		*LOG += "# CM ROM:\nIO: " + std::to_string((short)CM_ROM) + " | CM_RAM: " + std::to_string((short)CM_RAM) + "\n";
		*LOG += "# Count: " + std::to_string((short)Count) + " | ROM.VDD: " + std::to_string(BusROM.VDD) + " | ROM.VDD: " + std::to_string(BusRAM.VDD) + "\n\n";
		*LOG += '\n\n';
	}
};




// ###############################################################################################################################################################################
// ####### MAIN #################################################################################################################################################################
// ###############################################################################################################################################################################

#endif // SCPARSE_