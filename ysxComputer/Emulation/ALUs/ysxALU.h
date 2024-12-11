#pragma once

#ifndef YSXALU_H
#define YSXALU_H
//#include <time.h>

// #####################
// ####### By Sophia Cristina
// ####### I'm trying to study some computer stuffs...
// #######
// ####### ALU emulation goes here AND NOT on the include:
// ####### "ysxComp/ysxEMU.h"
// ####### ALU electrical simulation components goes on the include:
// ####### "ysxplg/ysxElectr.h"
// #######
// #####################

// #################################################
// #################################################
// #################################################


// ###############################################################################################################################################################################
// ###############################################################################################################################################################################
// ###############################################################################################################################################################################

// #################################################
// ############## ADDER ##############

template <class T_> void HalfAdder(T_* A, T_* B, T_* S, T_* C)
{
	if (A && B && S && C) { *S = *A ^ *B; *C = *A & *B; }
}

template <class T_> void FullAdder(T_* A, T_* B, T_* Cin, T_* S, T_* Cout)
{
	T_ XOR = 0;
	if (A && B && Cin && S && Cout)
	{
		XOR = *A ^ *B; *S = XOR ^ *Cin;
		*Cout =  (*XOR & *Cin) | (*A & *B);
	}
}

template <class T_> void HalfSubtractor(T_* A, T_* B, T_* S, T_* C)
{
	if (A && B && S && C) { *S = *A ^ *B; *C = ~*A & *B; }
}

template <class T_> void FullSubtractor(T_* A, T_* B, T_* Cin, T_* S, T_* Cout)
{
	T_ XOR = 0;
	if (A && B && Cin && S && Cout)
	{
		XOR = *A ^ *B; *S = XOR ^ *Cin;
		*Cout =  (~*XOR & *Cin) | (~*A & *B);
	}
}


// ###############################################################################################################################################################################
// ####### MAIN #################################################################################################################################################################
// ###############################################################################################################################################################################

#endif // SCPARSE_
