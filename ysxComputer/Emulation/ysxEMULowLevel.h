#pragma once

#ifndef YSXEMULOWLVL_H
#define YSXEMULOWLVL_H

// #####################
// ####### By Sophia Cristina
// ####### Emulating small electronic circuits or components.
// #####################

// UTILS:
#include <bitset>

// #################################################
/* REFERENCES:
 [1] https://en.wikipedia.org/wiki/Flip-flop_(electronics)
 [2] https://en.wikipedia.org/wiki/Bus_(computing)
COUNTER:
 [C1]https://en.wikipedia.org/wiki/Counter_(digital)
 [C2] https://teachics.org/computer-organization-and-architecture/decade-counter-bcd-counter/
 [C3] https://www.electronics-tutorial.net/Mini-Projects/DECADE-COUNTER/
 [C4] https://www.electronicsforu.com/technology-trends/learn-electronics/decade-counter-circuit-basics
  [C4.1] https://www.slideshare.net/slideshow/embed_code/key/pFFctjyDmwMMGw
*/

/*#################################################
############## MAIN EMU INHERITANCE ##############
This class acts as a way to make all components interact with each other.
This class is basically a copy of 'ysxELEC_Component'.*/
template <class T_> class ysxEMU_Component
{
public:
	virtual void Process() { }
	//virtual void W() { }
	//virtual void R() { }
	//~ysxEMU_Component() { }
};

// #################################################
// ############## SMALL COMPONENTS ##############

// ####### BASIC CIRCUIT:

/*TRANSFER DATA WITH AN EMULATED BUS: [2]*/
template <class T_, const size_t Size>
class ysxEMU_DataBus
{
public:
	std::array<T_*, Size> Pins;
	void Send(T_* Data) { if (Data) { for (size_t n = 0; n < Size; ++n) { if (Pins[n]) { *Pins[n] = *Data; } } } }
	// void R(T_* Data) override { for (size_t n = 0; n < Size; ++n) { if (p) { *Data = *p[n]; } } }
};

/* BIPOLAR TRANSISTOR (NPN AND PNP):
NPN: iC--v->oE | PNP: oC--v-<iE
		iB	   |		 oB
Same as an 'AND'*/
//T_ TrnsBip(T_ In, T_ B) { return(In & B); }

/*####### DE / MULTIPLEXER:
Data inputs are 2^Pow, and the switch inputs are Pow.*/
template <const size_t Pow>
class ysxEMU_Multiplexer
{

};

// #################################################
// ############## FLIP-FLOPS ##############

/* SET-RESET NOR FLIP-FLOP:
S-+(~|)+--Q
  |    |
  +----+
	   ||
  +----+|
  |	    |
R-+(~|)-+-Q
 
S|R|Nx|Ny|Qx|Qy|
0|0| 1| 0| 1| 0|
1|0| 0| 1| 0| 1|
0|1|
1| |
*/
template <class T_> struct ysxEMU_FF_SRNOR
{
	T_* Q[2] = { nullptr, nullptr };
	T_ NOR[2] = { 0, 0 };
	const size_t N = sizeof(T_) * 8;
	
	// Flip-flop every bit:
	void FF(const T_ S, const T_ R = 0)
	{
		NOR[0] = 0; NOR[1] = 0;
		if (Q[0] && Q[1])
		{
			for (size_t b = 0; b < N; ++b)
			{
				if (b)
				{
					NOR[0] |= ~((NOR[1] << 1) | S) & (1 << b);
					NOR[1] |= ~((NOR[0] & (1 << b)) | R) & (1 << b);
				}
				else
				{
					NOR[0] |= ~((*Q[1] >> (N - 1)) | S) & 1;
					NOR[1] |= ~((NOR[0] & (1 << b)) | R) & 1;
				}
			}
			*Q[0] = NOR[0]; *Q[1] = NOR[1];
		}
	}
	
	// Flip-flop specific bit of 'T_':
	void FFBit(const T_ S, const T_ R, const size_t Bit)
	{
		NOR[0] = 0; NOR[1] = 0;
		if (Q[0] && Q[1])
		{
			if (Bit)
			{
				NOR[0] |= ~((NOR[1] << 1) | S) & (1 << Bit);
				NOR[1] |= ~((NOR[0] & (1 << Bit)) | R) & (1 << Bit);
			}
			else
			{
				NOR[0] |= ~((*Q[1] >> (N - 1)) | S) & 1;
				NOR[1] |= ~((NOR[0] & (1 << Bit)) | R) & 1;
			}
			Q[0] = NOR[0]; *Q[1] = NOR[1];
		}
	}

	void FFGated(const T_ S, const T_ R, const T_ E)
	{
		NOR[0] = 0; NOR[1] = 0;
		const T_ AND[2] = { E & S, E & R };
		if (Q[0] && Q[1])
		{
			for (size_t b = 0; b < N; ++b)
			{
				if (b)
				{
					NOR[0] |= ~((NOR[1] << 1) | AND[0]) & (1 << b);
					NOR[1] |= ~((NOR[0] & (1 << b)) | AND[1]) & (1 << b);
				}
				else
				{
					NOR[0] |= ~((*Q[1] >> (N - 1)) | AND[0]) & 1;
					NOR[1] |= ~((NOR[0] & (1 << b)) | AND[1]) & 1;
				}
			}
			*Q[0] = NOR[0]; *Q[1] = NOR[1];
		}
	}
};

// SET-RESET NAND FLIP-FLOP:
template <class T_> struct ysxEMU_FF_SRNAND
{
	T_* Q[2] = { nullptr, nullptr };
	T_ NAND[2] = { 0, 0 };
	const size_t N = sizeof(T_) * 8;
	void FF(const T_ S, const T_ R = 0)
	{
		NAND[0] = 0; NAND[1] = 0;
		if (Q[0] && Q[1])
		{
			for (size_t b = 0; b < N; ++b)
			{

				if (b)
				{
					NAND[0] |= ~((NAND[1] << 1) & S) & (1 << b);
					NAND[1] |= ~((NAND[0] & (1 << b)) & R) & (1 << b);
				}
				else
				{
					NAND[0] |= ~((*Q[1] >> (N - 1)) & S) & 1;
					NAND[1] |= ~((NAND[0] & (1 << b)) & R) & 1;
				}
			}
			*Q[0] = NAND[0]; *Q[1] = NAND[1];
		}
	}
};

// D-LATCH:
template <class T_> struct ysxEMU_FF_DLTACH
{
	T_* Q[2] = { nullptr, nullptr };
	T_ NOR[2] = { 0, 0 };
	T_ AND[2] = { 0, 0 };
	const size_t N = sizeof(T_) * 8;

	void FF(const T_ D, const T_ EN = 0)
	{
		NOR[0] = 0; NOR[1] = 0;
		AND[0] = (~D) & EN; AND[1] = D & EN;
		if (Q[0] && Q[1])
		{
			for (size_t b = 0; b < N; ++b)
			{
				if (b)
				{
					NOR[0] |= ~((NOR[1] << 1) | AND[0]) & (1 << b);
					NOR[1] |= ~((NOR[0] & (1 << b)) | AND[1]) & (1 << b);
				}
				else
				{
					NOR[0] |= ~((*Q[1] >> (N - 1)) | AND[0]) & 1;
					NOR[1] |= ~((NOR[0] & (1 << b)) | AND[1]) & 1;
				}
			}
			*Q[0] = NOR[0]; *Q[1] = NOR[1];
		}
	}
};

// D-LATCH GATED (W.I.P):
template <class T_> struct ysxEMU_FF_DLATCHGated
{
	T_* Q[2] = { nullptr, nullptr };
	Point<T_> AND, NOR; T_ iD, X;
	void FF(const T_& D, const T_& EN)
	{
		if (Q[0] && Q[1])
		{
			// REDO
		}
	}
};

// EARLE LATCH (W.I.P):
// Check out if you can use SN7400 to do this. ;)
template <class T_> struct ysxEMU_FF_EarleLatch
{
	T_* Q = nullptr;
	T_ NAND[4];

};

/*JK FLIP-FLOP (W.I.P):
    +----------------+
J---+-(~&)-+(~&)+--+----Q
	|	   |    |  | |
	|	   +-----+ | |
CLK-+			|| | |
	|	   +----+| | |
	|	   |     | | |
K---+-(~&)-+(~&)-+---+--Q
    +--------------+
*/
template <class T_> struct ysxEMU_FF_JK
{
	T_* Q[2] = { nullptr, nullptr };
	T_ NAND[4];
	const size_t N = sizeof(T_) * 8;

	void FF(const T_ CLK, const T_ J, const T_ K)
	{
		for (uint8_t n = 0; n < 4; ++n) { NAND[n] = 0; } // Clean gates
	
		if (Q[0] && Q[1])
		{
			//std::cout << "&Q = " << (size_t)Q << '\n';
			//std::cout << "J = " << (size_t)J << " | K = " << (size_t)K << '\n';
			for (size_t b = 0; b < N; ++b)
			{
				if (b)
				{
					NAND[0] |= ~((NAND[3] << 1) & J & CLK) & (1 << b);
					NAND[1] |= ~((NAND[2] << 1) & K & CLK) & (1 << b);
					
					NAND[2] |= ~((NAND[3] << 1) & NAND[0]) & (1 << b);
					NAND[3] |= ~(NAND[2] & NAND[1]) & (1 << b);		
				}
				else
				{
					NAND[0] |= ~((*Q[1] >> (N - 1)) & J & CLK) & 1;
					NAND[1] |= ~((*Q[0] >> (N - 1)) & K & CLK) & 1;

					NAND[2] |= ~((*Q[1] >> (N - 1)) & NAND[0]) & 1;
					NAND[3] |= ~(NAND[2] & NAND[1]) & 1;
				}
			}
			*Q[0] = NAND[2]; *Q[1] = NAND[3];
			//std::cout << "New Qs: 0: " << (size_t)*Q[0] << " | 1: " << (size_t)*Q[1] << ";\n\n";
		}
	}

	void FFBit(const T_ CLK, const T_ J, const T_ K, const size_t Bit)
	{
		for (uint8_t n = 0; n < 4; ++n) { NAND[n] = 0; } // Clean gates

		if (Q[0] && Q[1])
		{
			if (Bit)
			{
				NAND[0] |= (~(((NAND[3] & (1 << (Bit - 1))) << 1) & (J & (1 << Bit)) & (CLK & (1 << Bit))) & (1 << Bit));
				NAND[1] |= (~(((NAND[2] & (1 << (Bit - 1))) << 1) & (J & (1 << Bit)) & (CLK & (1 << Bit))) & (1 << Bit));

				NAND[2] |= (~(((NAND[3] & (1 << (Bit - 1))) << 1) & (NAND[0] & (1 << Bit))) & (1 << Bit));
				NAND[3] |= (~((NAND[2] & (1 << Bit)) & (NAND[1] & (1 << Bit))) & (1 << Bit));

			}
			else
			{
				NAND[0] |= (~(((*Q[1] & (1 << (N - 1))) >> (N - 1)) & (J & 1) & (CLK & 1)) & 1);
				NAND[1] |= (~(((*Q[0] & (1 << (N - 1))) >> (N - 1)) & (J & 1) & (CLK & 1)) & 1);

				NAND[2] |= (~(((*Q[1] & (1 << (N - 1))) >> (N - 1)) & (NAND[0] & 1)) & 1);
				NAND[3] |= (~((NAND[2] & 1) & (NAND[1] & 1)) & 1);

			}
			*Q[0] = NAND[2]; *Q[1] = NAND[3];
		}
	}
};

// #################################################
// ############## COUNTERS ##############

// COUNTER: !!! WIP !!!
template<class T_, const uint16_t NumFFs> class ysxEMU_JKFF_Counter
{
private:
	const size_t T_Bits = sizeof(T_) * 8;
	const size_t Bytes = (size_t)std::ceil(NumFFs / 8.0);
	T_ AND = 0; // Remember to set to '0' after any activity.
public:
	ysxEMU_FF_JK<T_> FFs[NumFFs];
	T_ Qs[2][NumFFs];	
	std::vector<std::vector<uint8_t>> Os; // Parallel outs
	
	// #################################################
	ysxEMU_JKFF_Counter()
	{
		Os = std::vector<std::vector<uint8_t>>::vector(T_Bits);
		for (size_t n = 0; n < T_Bits; ++n) { Os[n] = std::vector<uint8_t>::vector(Bytes); }
		for (size_t n = 0; n < NumFFs; ++n) { FFs[n].Q[0] = &Qs[0][n]; FFs[n].Q[1] = &Qs[1][n]; }
	}
	// #################################################

	// GET PARALLEL OUT TO 'Os' ARRAY:
	void GetPrllOut()
	{
		uint16_t QByte = 0;
		for (size_t Bit = 0; Bit < T_Bits; ++Bit)
		{
			for (size_t m = 0; m < std::ceil(NumFFs / 8.0); ++m) { Os[Bit][m] = 0; }
			for (size_t Q = 0; Q < NumFFs; ++Q)
			{
				QByte = (uint16_t)std::floor(Q / 8.0);
				Os[Bit][QByte] |= ((*FFs[Q].Q[0] >> Bit) & 1) << Q;
				/*FFs[Q]| >> Bit|&1|<< Q|Os
					  b6|1011011| 0| 1:0|0->+
					  d2|1101001| 0| 2:0|0  |
					  b1|1011000| 1| 4:1|1  |
					  4d|0100110| 1| 8:1|1  +-> = 0xC = 12 = 1100*/
			}
		}
	}

	// Increment counter:
	void INC(T_ CLK)
	{
		std::cout << "####### Begin INC #######\n\n";
		if (NumFFs > 0)
		{
			std::cout << "NumFFs > 0;\n";
			FFs[0].FF(CLK, 0xff, 0xff); // Clock FFs[0], and Q.x is the first bit of the counter: 0001
			std::cout << "CLK = " << (size_t)CLK << ": FFs[0].Q[0]: " << (size_t)*FFs[0].Q[0] << '\n';
			if (NumFFs > 1)
			{ 
				size_t N = NumFFs - 1;
				std::cout << "\nNumFFs > 1; N = NumFFs - 1 = " << N << "\n";
				for (size_t n = 0; n < N; ++n)
				{

					if (!n)
					{
						FFs[n + 1].FF(CLK, *FFs[n].Q[0], *FFs[n].Q[0]); // Clock FFs[1] by FFs[0].Q.x, second bit out: 0010
						AND = *FFs[n + 1].Q[0] & *FFs[n].Q[0]; // Q[1] AND Q[0]
					}
					else
					{
						FFs[n + 1].FF(CLK, AND, AND); // Clock FFs[2] by AND from 'Q[1] AND Q[0]'
						AND = *FFs[n + 1].Q[0] & AND; // Q[2] AND Q[1]
					}
					std::cout << n << ": AND: " << (size_t)AND << '\n';
					std::cout << "FFs[" << n << "].Q[0]: " << (size_t)*FFs[n].Q[0] << '\n';
					std::cout << "FFs[" << n + 1 << "].Q[0]: " << (size_t)*FFs[n + 1].Q[0] << '\n';
				}
			}
			std::cout << "\n####### DONE #######\n\n";
			GetPrllOut();
			AND = 0;
		}
	}
};

// #################################################
// #################################################
// #################################################

#endif // SCPARSE_