#pragma once

#ifndef YSXELECTR_H
#define YSXELECTR_H

#include "ysxConst.h";

// #####################################################################################################################################

// ############################

// ############################
// ####### SINAIS:
double StepSig(int n) { if (n >= 0) { return(1); } return(0); }

// ############################
// ####### ESPECIAL:

// #####################################################################################################################################

// ####### ####### ####### ####### ####### #######


class TestElectr
{
public:
	void Test()
	{
		cout << "Digite qual fun��o:\n";
		cout << "| 1 = | 2 =\n";
		int Op; cin >> Op;

		if (Op == 1)
		{
		}
		if (Op == 2)
		{
		}
		
	}
};

// ################################################# FIM ####################################################################################

#endif // SCPARSE_