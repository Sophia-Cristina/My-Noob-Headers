#pragma once

#ifndef YSXMECHPIECES_H
#define YSXMECHPIECES_H

// #####################
// ####### By Sophia Cristina
// #######
// ####### Mechanical pieces, to assemble
// ####### machines.
// #######
// #####################

// #################################################
// REFERENCES:
// #################################################


// ###############################################################################################################################################################################
// ###############################################################################################################################################################################
// ###############################################################################################################################################################################

// #################################################
// ############## ASSEMBLE UTILS ##############

// ############## PIN-LIKE

// JUST A PIN FOR MECHANICAL EQUIPMENTS:
template <class T_>
struct MechPin
{
	T_ Diam; // Diameter
	T_ Height;
	T_ Dist; // Distance from a 'point' defined in an object.
			 // Ex.: 'Dist = 1; Wheel.Diam = 1.2;', then suppose 'point' is the distance of the pin from an edge.
};

// #################################################


// #################################################
// ############## WHEEL-LIKE ##############

template <class T_>
struct Wheel
{
	T_ Diam = 1; // Diameter
	T_ Height = 1;
	T_ Turn = 1; // Gear should be seem as a slice of pizza measured by 'Turn' in radians
	T_ Rotation = 0; // Gear rotation state in radians. A good use should be '0 to 1' or '0 to 2*PI'
};

// #################################################

template <class T_>
class Gear : public Wheel<T_>
{
public:
	unsigned int NumTooth = 16; // Tooth amount, 'int', why not 4 millions? :p
	unsigned char TeethType = 1; // Depend of the inheritance of this class
	T_ ToothSeg; // Tooth area ratio by tooth segment from diameter
	T_ TeethSize = 1;

	void SetupGear(unsigned int nTooth, T_ ToothSegment) { NumTooth = nTooth; ToothSeg = ToothSegment; }

	Gear()
	{
	}

	~Gear()
	{
	}
};

template <class T_>
class GearSpur : public Gear<T_>
{
public:
	
	GearSpur()
	{
	}

	~GearSpur()
	{
	}
};

template <class T_>
class GearCrow : public Gear<T_>
{
public:

	GearCrow()
	{
	}

	~GearCrow()
	{
	}
};

// #################################################

// #################################################
// ############## ROTATIONS ##############

// ROTATE ANY WHEEL BY THE SAME RATIO:
void RotateWheels(std::vector<Wheel<double>>& Axis, double Turn)
{
	for (size_t w = 0; w < Axis.size(); ++w) { Axis[w].Rotation += Turn; if (Axis[w].Rotation >= 1) { Axis[w].Rotation = 0; } }
}

// ROTATE ANY WHEEL BY DIFFERENT RATIO:
void RotateWheels(std::vector<Wheel<double>>& Axis, double Turn, double Ratio)
{
	for (size_t w = 0; w < Axis.size(); ++w) { Axis[w].Rotation += Turn * pow(Ratio, w - 1.0); if (Axis[w].Rotation >= 1) { Axis[w].Rotation = 0; } }
}

// ROTATE A GEAR AND RETURNS TRUE IF SEGMENT OF ROTATION IS ON A HIT POSITION:
bool RotateGear(Gear<double>& G, double Turn)
{
	if (G.NumTooth > 0)
	{
		G.Rotation += Turn; if (G.Rotation >= 1) { G.Rotation = 0; }
		double Seg = G.Rotation * G.NumTooth;	if (Seg - floor(Seg) < G.ToothSeg) { return(true); }
	}
	return(false);
}

// ###############################################################################################################################################################################
// ####### MAIN #################################################################################################################################################################
// ###############################################################################################################################################################################

#endif // SCPARSE_