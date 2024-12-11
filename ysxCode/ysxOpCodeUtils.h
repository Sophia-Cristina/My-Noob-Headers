#pragma once

#ifndef YSXOPCODEUTILS_H
#define YSXOPCODEUTILS_H

// #####################
// ####### By Sophia Cristina
// ####### Code to help you to code. Manage Op Codes, automaticaly write codes and etc.
// ####### Take in mind that this is for general Op Codes, for specific Op Codes, like,
// ####### for example, 6502, then, you may find codes to help with it at:
// ####### ysxComputer/Emulation/ICs/Processors/6502/ysxM6502Opcode.h
// ####### For things not related to IC, you may fing it at: ysxComputer/Emulation
// #####################


// #################################################
/* REFERENCES:
 [1] 
*/

// #################################################
// ##############  ##############

/*This is an object to organize a set of instructions produced by functions and classes:
For example, let's say you make a 'sine wave' function in assembly, you may want to use this struct.
You would then give a 'Name' like 'Sine Wave Func', an ID, write how many cycles it takes to finish
the entire set, and then add all the Op Codes in the vector. This can then be used in any class, function
and etc that mess with coding.*/
struct ysxCODE_CodeSet
{
 std::string Name = "None"; // You may add a name if you want to find your code inside the classes that "plays" the code
 uint16_t ID = 0; // It may be useful to define same procedures with same ID, for now, this is up to the programmer, but may change if i need to
 uint16_t CodeCycles = 0; // This should be how long, in machine cycles, that it takes to complete the entire OpCode set
 std::vector<uint8_t> OpCodeSet; // Write the full code here 
};

/*Get a set of Op Codes and copy it a number of times:
Ex.: Input: (ysxCODE_CodeSet MyCode, 2);
The input above is going to add the code inside 'OpCodeSet' two more times, totalling three times the same code set.
Let's say the set is {11, 22}, the end result is {11, 22, 11, 22, 11, 22}.*/
ysxCODE_CodeSet ysxCODE_CodeSetFill(const ysxCODE_CodeSet& MySet, size_t Copies)
{
 ysxCODE_CodeSet Set = MySet;
 for (size_t n = 0; n < Copies; ++n)
 {
  for (size_t m = 0; m < MySet.OpCodeSet.size(); ++m)
  {
   Set.OpCodeSet.push_back(MySet.OpCodeSet[m]);
  }
 }
 Set.CodeCyles *= Copies;
 return(Set);
};

// #################################################
// #################################################
// #################################################

#endif