#pragma once

#ifndef YSXAUTOMATAS_H
#define YSXAUTOMATAS_H

// #####################
// ####### By Sophia Cristina
// ####### Automata, celular automata.
// #####################

/*#################################################
REFERENCES:
#################################################*/


// #################################################
// #################################################
// #################################################

// #################################################
// ##############  ##############


// #################################################
// ############## PATERSON'S WORMS ##############

class ysxAUTOM_PatersonsWorms
{
public:
	struct Cell
	{
		Point<size_t> P;
		bool Eaten = false;
	};
	std::vector<Cell> Cells; // Eaten cells
	Point<size_t> Pos; // Actual position
	uint16_t Dirs = 6; // All possible directions. In this class, it is possible to have more than 6 directions
	uint16_t ActualDir; // The actual POV of the worm; The last position diretion
	size_t CntStep = 0; // Count steps
	size_t CntArray = 0; // Count the actual position of a Rule-array
	double Angle = 1.0 / Dirs;

	void CheckIfPossibleMove()
	{

	}
	
	void Step(uint8_t* RuleArray, size_t ArraySize)
	{
		if (!CntStep) { Pos = 0; Cells = std::vector<Cell>::vector(); } // New vector
		
		++CntStep;
	}

	void StepNTimes(size_t N, uint8_t* RuleArray, size_t ArraySize)
	{
		Angle = 1.0 / Dirs;
		for (size_t n = 0; n < N; ++n) { Step(RuleArray, ArraySize); }
	}

	ysxAUTOM_PatersonsWorms()
	{

	}			
};

// #################################################
// #################################################
// #################################################

#endif // SCPARSE_
