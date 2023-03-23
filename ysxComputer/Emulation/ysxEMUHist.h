#pragma once

//#include <time.h>
//#include "ysxCImg.h" // To create terminal user interfaces

#ifndef YSXEMUHIST_H
#define YSXEMUHIST_H

#include "ysxMech/ysxMechPieces.h"

// #####################
// ####### By Sophia Cristina
// ####### I'm trying to study some computer stuffs...
// #######
// ####### Everything related to emulating some kind of computer
// ####### or electronic devide akin to it, but from old times.
// #######
// #####################

// #####################
// ####### FORWARD DECLARATIONS:
// #####################

// #################################################
/* REFERENCES:
PASCALINE:
 [P1] https://www.youtube.com/watch?v=3h71HAJWnVU // How the Pascaline Works
 [P2] https://en.wikipedia.org/wiki/Pascal%27s_calculator
DIFFERENCE ENGINE:
 [D1] http://satyam.com.ar/Babbage/en/index.html
  [D1.1] http://satyam.com.ar/Babbage/en/mathemat.htm
  [D1.2] http://satyam.com.ar/Babbage/en/overall.htm
  [D1.3] http://satyam.com.ar/Babbage/en/figure.htm
  [D1.4] http://satyam.com.ar/Babbage/en/addinga.htm
  [D1.5] http://satyam.com.ar/Babbage/en/restore.htm
  [D1.6] http://satyam.com.ar/Babbage/en/carrydet.htm
  [D1.7] http://satyam.com.ar/Babbage/en/carrypro.htm
  [D1.8] http://satyam.com.ar/Babbage/en/seccarry.htm
 [D2] http://ed-thelen.org/bab/bab-intro.html
*/
// #################################################

// #################################################
// ############## PASCALINE ############## // [P1]

// BASIC PASCALINE:
class Pascaline
{
public:
	std::vector<GearCrow<double>> Dials;
	std::vector<Wheel<double>> NumWheels;
	MechPin<double> CarryPin; // In the back of the accumulator. Ignore distance
	
	// Slider that goes from the top to the bottom of the number wheels
	// It is a double, so you can set any number on the number wheel
	//double DisplayBar = 0;
	bool DisplayBar = false; // For now
    
	// #################################################
	
	// ROTATE DIAL ENOUGH TO REACH THE NEXT NUMBER:
	void RotateDial(size_t Dial)
	{
		if (Dial < Dials.size())
		{
			std::cout << "# ROTATION #\n";
			double Turn = 1.0 / Dials[Dial].NumTooth;
			double* Rot = &Dials[Dial].Rotation;
			Dials[Dial].Rotation += Turn; if (*Rot >= 1) { *Rot = *Rot - floor(*Rot); }
			double Seg = *Rot * Dials[Dial].NumTooth;
			std::cout << "Dial: " << Dial << "  | Rot: " << *Rot << " | Seg: " << Seg << std::endl;
			if (Seg - floor(Seg) < Dials[Dial].ToothSeg)
			{
				if (Dial < NumWheels.size())
				{
					std::cout << "BEF.: " << NumWheels[Dial].Rotation * Dials[Dial].NumTooth;
					NumWheels[Dial].Rotation += Turn;
					std::cout << " | AFTER: " << NumWheels[Dial].Rotation * Dials[Dial].NumTooth << std::endl;
				}
				// Carry pin (varify if division is correct):
				if (Dial + 1 < Dials.size())
				{
					if (Dials[Dial].Diam > 0)
					{
						std::cout << "Carry condition: " << Seg << " >= " << Dials[Dial].NumTooth - 1 << std::endl;
						if (Seg - floor(Seg) < (CarryPin.Diam / Dials[Dial].Diam) && Seg >= Dials[Dial].NumTooth - 1)
						{
							std::cout << "CARRIED\n";
							Dials[Dial + 1].Rotation += Turn; // !!! Change later for it to change based on the size of the next dial diameter !!!
						}
					}
				}
			}
			std::cout << std::endl;
		}
	}

	// #################################################

	// ROTATE DIAL THE AMOUNT NESCESSARY TO REACH 'Num':
	void SetDialNum(size_t Num, size_t Dial)
	{
		std::cout << "Num: " << Num << " | Dial: " << Dial << std::endl;
		if (Dial < Dials.size())
		{
			Num %= Dials[Dial].NumTooth;
			double Turn = 1.0 / Dials[Dial].NumTooth;
			size_t Actual = floor(Dials[Dial].Rotation * (Dials[Dial].NumTooth - 1));
			std::cout << "Turn: " << Turn << " | Actual: " << Actual << std::endl;
			std::cout << "Num - Actual = " << Num - Actual << std::endl;
			std::cout << "nTooth - Actual + Num = " << Dials[Dial].NumTooth - Actual + Num << std::endl << std::endl;
			if (Num > Actual) { for (int n = 0; n < Num - Actual; ++n) { RotateDial(Dial); } }
			else if (Num < Actual)
			{
				for (size_t n = 0; n < Dials[Dial].NumTooth - Actual + Num; ++n) { RotateDial(Dial); }
			}
			std::cout << "Af Turn: " << Turn << " | Af Actual: " << Actual << std::endl << std::endl;
		}
	}

	// ROTATE DIAL THE AMOUNT NESCESSARY TO REACH 'Num':
	void SumDialNum(size_t Add, size_t Dial)
	{
		if (Dial < Dials.size())
		{
			double Turn = 1.0 / Dials[Dial].NumTooth;
			for (size_t n = 0; n < Add; ++n) { RotateDial(Dial); }
		}
	}
	
	// #################################################

	/* CHECK NUMBER WHEEL TO VERIFY THE RESULT:
	 * Check the status of your 'DisplayBar' *
	Wheel is the indexed Wheel, and Radix is the divisions that will be considered from the amount of rotation of the Wheel.
	Returns a double, there will be decimals in case the number is misaligned.*/
	double CheckNumberWheel(size_t Wheel, unsigned char Radix = 10)
	{
		std::cout << "NUM1: " << NumWheels[Wheel].Rotation * Radix << std::endl;
		if (Wheel < NumWheels.size())
		{
			if (DisplayBar) { return(Radix - NumWheels[Wheel].Rotation * Radix); }
			else { return(NumWheels[Wheel].Rotation * Radix); }
		}
	}


	// #################################################

	Pascaline() { }

	~Pascaline() { }
};

// #################################################
// ############## DIFFERENCE ENGINE ############## // [D1]

class DiffEngine
{
public:

	// #################################################
	// ### OVERALL ###
	
	// CARRY WHEEL:
	struct CarryWheel
	{
		unsigned int Count;
		bool DriveArm;
	};

	// MAKE WHEEL WITH SPUR GEAR:
	GearSpur<double> MakeFigureWheel()
	{
		GearSpur<double> W;
		W.NumTooth = 40;
		return(W);
	}

	GearSpur<double> MakeSectorWheel()
	{
		GearSpur<double> W;
		W.NumTooth = 40;
		return(W);
	}

	// FIGURE WHEEL RESTORE ARM:
	GearSpur<double> MakeFigWheelRestArm()
	{
		GearSpur<double> W;
		W.NumTooth = 2;
		W.Turn = 0.6;
		return(W);
	}

	// SECTOR WHEEL RESTORE ARM:
	GearSpur<double> MakeSecWheelRestArm()
	{
		GearSpur<double> W;
		W.NumTooth = 1;
		return(W);
	}

	// WHEEL AXIS:
	struct Axis
	{
		std::vector<Gear<double>>* Wheels; // Add wheels
	};

	// LEVERS:

	// RACKS:

	// HAND CRANK:

	// CAMS:

	// PRINT:

	// STEROTYPING TABLE:

	// #################################################

	// #################################################
	DiffEngine() {}

	~DiffEngine() {}
};


// ###############################################################################################################################################################################
// ####### MAIN #################################################################################################################################################################
// ###############################################################################################################################################################################

#endif // SCPARSE_