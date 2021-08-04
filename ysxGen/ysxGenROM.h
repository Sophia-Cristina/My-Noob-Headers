#pragma once

#ifndef YSXGENROM_H
#define YSXGENROM_H

// #####################
// ####### By Sophia Cristina
// ####### SEGA GENESIS / MEGA-DRIVE MAPPING
// #####################

// #####################
// ####### FORWARD DECLARATIONS:
// #####################

// #################################################
// #####################
// #######
// REFERENCES:
// WIKIBOOKS GENESIS PROGRAMMING:
// *** https://en.wikibooks.org/wiki/Genesis_Programming

// #################################################
// ############## AAA ##############

// #################################################

// #################################################
// ####### CLASSES #######
// #################################################

// #################################################
// ####### PROCESSOR:

// MOTOROLA 68000 MEMORY MAP:
struct M68KMAP
{
	// !!!!!!!    GameHut Source shows as this    !!!!!!!
	//   !!! Check if enum will have problem or not !!!
	// VDP_DATA:	EQU	$FFC00000
	// VDP_STATUS:  EQU	$FFC00004
	// VDP_CONTROL: EQU $FFC00004
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// STARTS:
	enum S
	{
		// ####### TECHNICAL #######
		M68S_ROMRAM = 0, M68S_Ver = 0xA10000, M68S_TMSS = 0xA14000, M68S_RAM68k = 0xFF0000,
		// ####### Z80 STUFFS #######
		M68S_Z80RAM = 0xA00000, M68S_Z80bus = 0xA1110, M68S_Z80reset = 0xA11200,
		// ####### CONTROL1 #######
		M68S_Contr1D = 0xA10002, M68S_Contr1C = 0xA10008, M68S_Contr1ST = 0xA1000E, M68S_Contr1SR = 0xA10010, M68S_Contr1SC = 0xA10012,
		// ####### CONTROL2 #######
		M68S_Contr2D = 0xA10004, M68S_Contr2C = 0xA1000A, M68S_Contr2ST = 0xA10014, M68S_Contr2SR = 0xA10016, M68S_Contr2SC = 0xA10018,
		// ####### EXPANSION PORT #######
		M68S_ExpD = 0xA10006, M68S_ExpC = 0xA1000C, M68S_ExpST = 0xA1001A, M68S_ExpSR = 0xA1001C, M68S_ExpSC = 0xA1001E,
		// ####### VDP #######
		M68S_VDPD = 0xC00000, M68S_VDPDm = 0xC00002, M68S_VDPC = 0xC00004, M68S_VDPCm = 0xC00006, M68S_VDPHVc = 0xC00008,
		// ####### RESERVEDS #######
		M68S_Res0 = 0x400000, M68S_Res1 = 0x800000, M68S_Res2 = 0xA10020, M68S_Res3 = 0xA11002, M68S_Res4 = 0xA11102,
		M68S_Res5 = 0xA11202, M68S_Res6 = 0xA14004, M68S_Res7 = 0xC0000A, M68S_Res8 = 0xC00012
	};
	// ENDS:
	enum E
	{
		// ####### TECHNICAL #######
		M68E_ROMRAM = 0x3FFFFF, M68E_Ver = 0xA10001, M68E_TMSS = 0xA14003, M68E_RAM68k = 0xFFFFFF,
		// ####### Z80 STUFFS #######
		M68E_Z80RAM = 0xA0FFFF, M68E_Z80bus = 0xA11101, M68E_Z80reset = 0xA11201,
		// ####### CONTROL1 #######
		M68E_Contr1D = 0xA10003, M68E_Contr1C = 0xA10009, M68E_Contr1ST = 0xA1000F, M68E_Contr1SR = 0xA10011, M68E_Contr1SC = 0xA10013,
		// ####### CONTROL2 #######
		M68E_Contr2D = 0xA10005, M68E_Contr2C = 0xA1000B, M68E_Contr2ST = 0xA10015,	M68E_Contr2SR = 0xA10017, M68E_Contr2SC = 0xA10019,
		// ####### EXPANSION PORT #######
		M68E_ExpD = 0xA10007, M68E_ExpC = 0xA1000D, M68E_ExpST = 0xA1001B, M68E_ExpSR = 0xA1001D, M68E_ExpSC = 0xA1001F,
		// ####### VDP #######
		M68E_VDPD = 0xC00001, M68E_VDPDm = 0xC00003, M68E_VDPC = 0xC00005, M68E_VDPCm = 0xC00007, M68E_VDPHVc = 0xC00009,
		// ####### RESERVEDS #######
		M68E_Res0 = 0x7FFFFF, M68E_Res1 = 0x9FFFFF, M68E_Res2 = 0xA10FFF, M68E_Res3 = 0xA110FF, M68E_Res4 = 0xA111FF,
		M68E_Res5 = 0xA13FFF, M68E_Res6 = 0xBFFFFF, M68E_Res7 = 0xC00010, M68E_Res8 = 0xFEFFFF,
	};

	unsigned int MemoModReg = 0xA110000; // Memory mode register
	unsigned int PSGOut = 0xC00010; // PSG output
};

// #################################################
// #################################################
// #################################################

struct Z80MAP
{
	// !!!!!!! Every one is listed as 'nnnnh' !!!!!!!
	// STARTS:
	enum S { Z80S_RAM = 0x0000, Z80S_Res0 = 0x2000, Z80S_Res1 = 0x4004, Z80S_Res2 = 0x6001, Z80S_3 = 0x7F12, Z80S_68kMemBank = 0x8000 };
	// ENDS:
	enum E { Z80E_RAM = 0x1FFF, Z80E_Res0 = 0x3FFF, Z80E_Res1 = 0x5FFF, Z80E_Res2 = 0x7F10, Z80E_3 = 0x7FFF, Z80E_68kMemBank = 0xFFFF };
	unsigned short YM2612A0 = 0x4000, YM2612A1 = 0x4002;
	unsigned short YM2612D0 = 0x4001, YM2612D1 = 0x4003;
	unsigned short BankReg = 0x6000, PSG = 0x7F11;
};

// ####################################################################################################################################################################################################
// ####################################################################################################################################################################################################
// ####################################################################################################################################################################################################

// #################################################
// ####### HEADER:

// HEADER, I WANT IT TO BE AN EASY TO SIMPLE LOAD A FILE:
struct GENHeader
{
	// CONSOLE NAME:		{  0    1    2    3    4  };
	unsigned char SEGA[5] = { 'S', 'E', 'G', 'A', ' ' }; // Use to compare and to map
	unsigned char Console[11]; // Should be either "GENESIS" or "MEGA DRIVE" (depending on the region you are planning to program your game for).
	// 5 + 11 = 16 !!!!!!! Must be 16 characters long !!!!!!!

	// FIRM NAME:		  {  0    1    2  };
	unsigned char CR[3] = { '(', 'C', ')' }; // Copyright
	unsigned char Firm[5]; //  !!!!!!! Should begin with one space: Copyright + 4 chars + One Space = 8 !!!!!!!
	unsigned char Date[8]; // After 8 bytes, Date appears
	// 3 + 5 + 8 = 16 !!!!!!! Must be 16 characters long !!!!!!!

	// GAME NAME:
	unsigned char GameName[48];
	unsigned char GameNameInter[48];
	// 48 + 48 = 96

	// !!!!!!!!!!!!!!!!!!!!! "GM XXXXXXXX-XX" | TYPE AND SERIAL !!!!!!!!!!!!!!!!!!!!!
	unsigned char Type[3]; // "GM " (game) or "AL " (educational) !!! PAY ATTENTION TO SPACE !!!
	//												     [0 1 2 3 4 5 6 7 8]
	unsigned char Serial[9]; // Note the '-' in the end: [X X X X X X X X -]
	unsigned char Ver[2]; // VERSION
	// 3 + 9 + 2 = 14

	unsigned short CheckSum; // 2 bytes | WORD '.w' in assembly

	// ####################################################################################################################################################################################################
	unsigned char J = 'J';			  // 'dc.b' BYTE		   || I/O device support (unused)
	unsigned int ROMStart = 0;		  // 'dc.l' LONG = 4 Bytes || Start of the ROM. This should always be 0
	unsigned int ROMEnd;			  // 'dc.l' LONG = 4 bytes || End of the ROM. It's best to use a label at the end of your source file to determine this
	unsigned int RAMStart = 0xFF0000; // 'dc.l' LONG = 4 bytes || Start of RAM. Just about every game starts at $FF0000, but RAM is mirrored at
									  //					   || several other places, and you can use those if you want.
	unsigned int RAMEnd = 0xFFFFFF;   // 'dc.l' LONG = 4 bytes || End of RAM. Should be $FFFF -------> after the starting point <-------
									  //					   || #########################################################################################################
	unsigned char BLANKS[5];		  //					   || CHECK TABLE BELOW:
									  //					   || [
									  // 'dc.b' BYTE		   ||	0 = Backup RAM ID. Fill this with spaces if there is none, otherwise, use this formula:
									  //					   ||				FORMULA -------> dc.b "RA",%1x1yy000,%0010000 <------- FORMULA
									  //					   ||		   %1  x 1
									  //					   ||		where 'x' is true when the RAM is for backup and false if not (I've no idea what the difference is).
									  //					   ||		| yy | 000, % 0010000
									  //					   ||		|'yy'| is '11' if addressing is odd bytes only, '10' if even only, and '00' if both.
									  // 'dc.b' BYTE		   ||	1 = Start address of backup RAM. Fill with spaces if there is no backup RAM.
									  // 'dc.b' BYTE		   ||	2 = End address of backup RAM.
									  // 'dc.b' BYTE		   ||	3 = Modem support. Fill with spaces if there is no modem, otherwise follow this formula:
									  //					   ||				FORMULA -------> "MO|xxxx|yy|.|zzz|" <------- FORMULA
									  //					   ||		   MO |xxxx|                   |yy|                         .|zzz|
									  //					   ||		where |xxxx| is the firm name, |yy| is the modem number, and |zzz| is the version number (This is also unused).
									  // 'dc.b' BYTE		   ||	4 = Notes. Put whatever you want here, and fill the empty spaces with zeroes.
									  //					   || ]
									  //					   || #########################################################################################################
	unsigned char Countries[3];		  // 'dc.b' BYTE		   || Country codes:
									  //					   ||	* J is for Japan
									  //					   ||	* U is for the United States
									  //					   ||	* E is for Europe
									  //					   || !!!!!!! You need to fill in the rest of this field with spaces !!!!!!!
									  //					   || So, JU for the country code would tell the Sega that the game is for Japan and the US,
									  //					   || JUE would tell it that it is for Japan, the US, and Europe
	// ####################################################################################################################################################################################################

	// ##################### INFO #####################
	// 5 + 11 = 16;				  // CONSOLE NAME
	// 16 + 3 + 5 + 8 = 32;		  // FIRM NAME
	// 32 + 96 = 128;			  // GAME NAME
	// 128 + 3 + 9 + 2 = 142	  // SERIAL
	// 142 + 2 = 144			  // CHECKSUM
	// 144 + 'J' = 145
	// 145 + 4 + 4 + 4 + 4 = 161; // ROM AND RAM STARTS AND ENDS
	// 161 + 5 = 166;			  // BLANKS
	// 166 + 3 = 169;			  // JUE AND <------- TOTAL -------
	// #################################################
};

// ####################################################################################################################################################################################################
// ####################################################################################################################################################################################################
// ####################################################################################################################################################################################################

// #################################################
// CLASS FOR HEADER MANIPULATION:
class GENROM
{
public:
	// ####### ENUMS:

	// ####### OBJECTS:
	// The ROM header starts at $000100 and contains information about the cartridge.
	const unsigned short Start = 0x100; // HEX: 0x100 || DEC: 256 || BIN (as short): |0000-0001|0000-0000| // It could also be 0x01 and just add a byte, like '0x 01 00'
	fstream FILE; // If you want to opem a ROM file...
	unsigned int FILESize = 0;
	GENHeader Header; // Functions normally overwrite this, so i would advice to not touch it too much.

	// #################################################
	unsigned int DATA1[64]; // I don't know yet how to map the ROM, what is this DATA above the header?
	std::string DATA2; // Every data below header
	// #################################################

	// #################################################
	// ####### CONSTRUCTORS:
	GENROM()
	{

	}

	GENROM(bool GENorMD, unsigned char Firm[4], std::string Date, std::string GName, std::string GIName, unsigned char Type[2], std::string Serial,
		unsigned char Ver[2], unsigned short CheckSum, unsigned int ROMStr, unsigned int ROMEnd, unsigned int RAMStr, unsigned int RAMEnd)
	{
		//CreateHeader(GENorMD, Firm, Date, GName, GIName, Type, Serial, Ver, CheckSum, ROMStr, ROMEnd, RAMStr, RAMEnd);
	}

	// Don't need suffix (must be .bin, later i'll add other suffixes):
	GENROM(std::string Path)
	{
		Path += ".bin";
		FILE.open(Path, ios::in | ios::out | ios::binary);
		GetFILESize(); GetDATA1();  GetHeader(); GetDATA2();
	}
	~GENROM()
	{
		if (FILE.is_open()) { FILE.close(); }
	}

	// #################################################
	void GetFILESize() { FILE.seekg(0, ios::end); FILESize = FILE.tellg(); FILE.seekg(0, ios::beg); }
	// #################################################

	// GET HEADER FROM A BINARY FILE:
	void GetHeader()
	{
		if (FILE.is_open()) { FILE.seekg(Start); FILE.read((char*)&Header, sizeof(GENHeader)); FixEndian(); }
		else { std::cout << "!!!!!!! You must open a file! fstream GENHeaderManip::FILE !!!!!!!\n\n"; }
	}

	// CREATE UOUR CUSTOM HEADER:
	void CreateHeader( bool GENorMD, unsigned char Firm[4], std::string Date, std::string GName, std::string GIName, unsigned char Type[2], std::string Serial,
						unsigned char Ver[2], unsigned short CheckSum, unsigned int ROMStr, unsigned int ROMEnd, unsigned int RAMStr, unsigned int RAMEnd )
	{
		unsigned char n;																							  // COUNTER
		if (!GENorMD) { std::string s = "GENESIS    "; for (n = 0; n < 11; ++n) { Header.Console[n] = s[n]; } }		  // GENESIS
		else { std::string s = "MEGA DRIVE "; for (n = 0; n < 11; ++n) { Header.Console[n] = s[n]; } }				  // MEGADRIVE
		for (n = 0; n < 4; ++n) { Header.Firm[n] = Firm[n]; }														  // FIRM
		if (Date.size() < 8) { for (n = 0; n < 8; ++n) { if (n < Date.size()) { Header.Date[n] = Date[n]; } else { Header.Date[n] = ' '; } } }
		if (Date.size() >= 8) { for (n = 0; n < 8; ++n) { Header.Date[n] = Date[n]; } }								  // DATE
		if (GName.size() < 48) { for (n = 0; n < 48; ++n) { if (n < GName.size()) { Header.GameName[n] = GName[n]; } else { Header.GameName[n] = ' '; } } }
		if (GName.size() >= 48) { for (n = 0; n < 48; ++n) { Header.GameName[n] = GName[n]; } }						  // NAME
		if (GIName.size() < 48) { for (n = 0; n < 48; ++n) { if (n < GIName.size()) { Header.GameNameInter[n] = GIName[n]; } else { Header.GameNameInter[n] = ' '; } } }
		if (GIName.size() >= 48) { for (n = 0; n < 48; ++n) { Header.GameNameInter[n] = GIName[n]; } }				  // NAME INTER
		Header.Type[0] = Type[0]; Header.Type[1] = Type[1]; Header.Type[2] = ' ';									  // TYPE
		if (Serial.size() < 8) { for (n = 0; n < 8; ++n) { if (n < Serial.size()) { Header.Serial[n] = Serial[n]; } else { Header.Serial[n] = '0'; } } }
		if (Serial.size() >= 8) { for (n = 0; n < 8; ++n) { Header.Serial[n] = Serial[n]; } } Header.Serial[9] = '-'; // SERIAL
		Header.Ver[0] = Ver[0]; Header.Ver[1] = Ver[1]; Header.CheckSum = CheckSum;									  // VERSION & CHECKSUM
		Header.ROMStart = ROMStr; Header.RAMStart = RAMStr; Header.ROMEnd = ROMEnd; Header.RAMEnd = RAMEnd;			  // ROM & RAM
		Header.BLANKS[0] = 0; Header.BLANKS[1] = 0; Header.BLANKS[2] = 0; Header.BLANKS[3] = 0; Header.BLANKS[4] = 0; // BLANKS
		Header.Countries[0] = 'J'; Header.Countries[1] = 'U'; Header.Countries[2] = 'E';							  // JUE
		// ####### ENDIAN #######
		FixEndian();
	}

	// #################################################

	void COutInfo()
	{
		std::cout << "###############################################################\n                     ####### DATA #######\n";
		for (char n = 0; n < 64; ++n) { std::cout << (short)n << ": " << DATA1[n]; if (n % 4 == 0) { std::cout << endl; } else { std::cout << ", "; } }
		std::cout << "\n###############################################################\n                     ####### HEADER #######\n";
		std::cout << "SEGA: " << Header.SEGA[0] << Header.SEGA[1] << Header.SEGA[2] << Header.SEGA[3] << endl;
		std::cout << "Console: "; for (char n = 0; n < 10; ++n) { std::cout << Header.Console[n]; } std::cout << endl;
		std::cout << "Company: " << Header.CR[0] << Header.CR[1] << Header.CR[2] << Header.Firm[0] << Header.Firm[1] << Header.Firm[2] << Header.Firm[3] << " | DATE: ";
		for (char n = 0; n < 8; ++n) { std::cout << Header.Date[n]; } std::cout << endl;
		std::cout << "Game Name: "; for (char n = 0; n < 48; ++n) { std::cout << Header.GameName[n]; } std::cout << endl;
		std::cout << "Game Name (Inter): "; for (char n = 0; n < 48; ++n) { std::cout << Header.GameNameInter[n]; } std::cout << endl;
		std::cout << "Type and Serial: " << Header.Type[0] << Header.Type[1] << ' ';
		for (char n = 0; n < 8; ++n) { std::cout << Header.Serial[n]; } std::cout << '-' << Header.Ver[0] << Header.Ver[1] << endl;
		std::cout << "CHECKSUM: " << Header.CheckSum << endl;
		std::cout << "ROM Start / End: " << Header.ROMStart << "B | " << Header.ROMEnd << "B\n";
		std::cout << "RAM Start / End: " << Header.RAMStart << "B | " << Header.RAMEnd << "B\n";
		std::cout << "Blanks: "; for (char n = 0; n < 5; ++n) { std::cout << (short)n << " = " << (short)Header.BLANKS[n] << " | "; } std::cout << endl;
		std::cout << "Countries: " << Header.Countries[0] << Header.Countries[1] << Header.Countries[2] << endl;
		std::cout << "\n#################################################\n";
	}
	void PrintInfo()
	{
		ofstream O("!ROM INFO.txt");
		O << "###############################################################\n                     ####### DATA #######\n";
		for (char n = 0; n < 64; ++n) { O << (short)n << ": " << DATA1[n]; if (n % 4 == 0) { O << endl; } else { O << ", "; } }
		O << "\n###############################################################\n                     ####### HEADER #######\n";		
		O << "SEGA: " << Header.SEGA[0] << Header.SEGA[1] << Header.SEGA[2] << Header.SEGA[3] << endl;
		O << "Console: "; for (char n = 0; n < 10; ++n) { O << Header.Console[n]; } O << endl;
		O << "Company: " << Header.CR[0] << Header.CR[1] << Header.CR[2] << Header.Firm[0] << Header.Firm[1] << Header.Firm[2] << Header.Firm[3] << " | DATE: ";
		for (char n = 0; n < 8; ++n) { O << Header.Date[n]; } O << endl;
		O << "Game Name: "; for (char n = 0; n < 48; ++n) { O << Header.GameName[n]; } O << endl;
		O << "Game Name (Inter): "; for (char n = 0; n < 48; ++n) { O << Header.GameNameInter[n]; } O << endl;
		O << "Type and Serial: " << Header.Type[0] << Header.Type[1] << ' ';
		for (char n = 0; n < 8; ++n) { O << Header.Serial[n]; } O << '-' << Header.Ver[0] << Header.Ver[1] << endl;
		O << "CHECKSUM: " << Header.CheckSum << endl;
		O << "ROM Start / End: " << Header.ROMStart << "B | " << Header.ROMEnd << "B\n";
		O << "RAM Start / End: " << Header.RAMStart << "B | " << Header.RAMEnd << "B\n";
		O << "Blanks: "; for (char n = 0; n < 5; ++n) { O << (short)n << " = " << (short)Header.BLANKS[n] << " | "; } O << endl;
		O << "Countries: " << Header.Countries[0] << Header.Countries[1] << Header.Countries[2] << endl;
		O << "\n#################################################\n";
		O.close();
	}

	void PrintDATA2(bool HEXorDEC)
	{
		const char HexChars[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
		ofstream O("!ROM DATA.txt");
		O << "###############################################################\n                     ####### DATA #######\n";
		for (int n = 0; n < DATA2.size(); ++n)
		{
			if (!HEXorDEC) { float d = DATA2[n] / 16.0; int h2 = floor(d); int h1 = round((d - h2) * 16); O << HexChars[h2]; O << HexChars[h1];	}
			else { O << (unsigned short)DATA2[n]; }
			if (n % 2 == 0) { O << '|'; } else { O << '.'; } if (n % 4 == 0) { O << ' '; } if (n % 8 == 0) { O << ' '; } if (n % 16 == 0) { O << " | " << n << endl; }			
		}
		O << "\n#################################################\n";
		O.close();
	}

	// #################################################
	// #################################################
	// #################################################

	void FixEndian()
	{
		unsigned char* p = (unsigned char*)&Header.CheckSum;
		unsigned char si[] = { p[1], p[0] };
		p = si; Header.CheckSum = *p;

		p = (unsigned char*)&Header.ROMStart;
		unsigned char i[] = { p[3], p[2], p[1], p[0] };
		p = i; Header.ROMStart = *p;
		p = (unsigned char*)&Header.ROMEnd;
		i[0] = p[3]; i[1] = p[2]; i[2] = p[1]; i[3] = p[0];
		p = i; Header.ROMEnd = *p;

		p = (unsigned char*)&Header.RAMStart;
		i[0] = p[3]; i[1] = p[2]; i[2] = p[1]; i[3] = p[0];
		p = i; Header.RAMStart = *p;
		p = (unsigned char*)&Header.RAMEnd;
		i[0] = p[3]; i[1] = p[2]; i[2] = p[1]; i[3] = p[0];
		p = i; Header.RAMEnd = *p;
	}

	// #################################################

	void GetDATA1()
	{
		if (FILE.is_open())
		{
			FILE.seekg(0, ios::beg);
			for (char n = 0; n < 64; ++n)
			{
				unsigned char I[4];
				FILE.read((char*)I, 4);
				unsigned char T[] = { I[3], I[2], I[1], I[0] }; // 68k IS BIG ENDIAN
				int* p = (int*)&T; DATA1[n] = *p;
			}			
		}
		else { std::cout << "!!!!!!! You must open a file! fstream GENHeaderManip::FILE !!!!!!!\n\n"; }
	}

	void GetDATA2()
	{
		if (FILE.is_open())
		{
			unsigned int DataStart = Start + sizeof(GENHeader);
			unsigned int GetSize = FILESize - DataStart;
			std::string s;
			FILE.seekg(DataStart);
			while (!FILE.eof()) { char c; FILE.read(&c, 1); s.push_back(c); }
			DATA2 = s;
		}
		else { std::cout << "!!!!!!! You must open a file! fstream GENHeaderManip::FILE !!!!!!!\n\n"; }
	}
};

// #################################################

// #################################################
// ####### FUNÇÕES #######
// #################################################

// #################################################

// ###############################################################################################################################################################################
// ####### MAIN #################################################################################################################################################################
// ###############################################################################################################################################################################

#endif // SCPARSE_