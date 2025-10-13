#pragma once

#ifndef YSXSIGNAL_H
#define YSXSIGNAL_H

// #####################
// ####### By Sophia Cristina
// ####### Signals, for emulator, simulator, math and more!
// #####################

// ####################################################################################
// ####################################################################################
// ####################################################################################

// ############################
// ####### MAIN CLASS #######
// ############################

/* MAIN SIGNAL STREAM BUFFER CLASS FOR INHERITANCE:
SigStream WORKS LIKE a pointer to an invisible buffer.
The best usage of SigStream is to use 'Size' as some sort of limit, or modulo.
And use C as a C.ounter, useful in both cases of ascending and descending.
Use 'C' vector to add channels / voices.
Using the input function 'IO(T_)', you can process the sample from a 't'ime that is based
on 'Size' and 'C'ounter.
*/
template<class T_> class ysxSIG_Stream
{
public:
    size_t Size = 0; // As samples
    size_t V = 0; // Voice for the counter, ex.: C[V]; it can also be seem as 'channel'
    std::vector<size_t> C; // 'C'ount samples, use vector index as different voices, careful with changes

    // INPUT, FOR INHERITANCE:
    // * Think about the input as 'void', but limited to n-bits, use casts.
    virtual T_ IO(T_ Data) { return(Data); }

    //ysxSIG_Stream(uint8_t Voices) { }
    //~ysxSIG_Stream() { }
};

/* SIGNAL IO OBJECT FOR INHERITANCE:
Very simple object made only for iheritance.
Use a object type as 'time' or 'x' (in a 'f(x)') and enjoy the magic returned from the virtual function.
*/
template<class T_> class ysxSIG_IO
{
public:
    virtual T_ IO(T_* Data) { return(*Data); }

    //ysxSIG_IO() { }
    //~ysxSIG_IO() { }
};

// ####################################################################################

// ############################
// ####### EXTRA RESOURCES #######
// ############################

#include "ysxSigElec.h"
#include "ysxDSPTools.h"
//#include "ysxSigMath.h"
#include "ysxSigTransform.h"
#include "ysxSigVectors.h"
#include "ysxSigEfx.h"

// ####################################################################################
// ####################################################################################
// ####################################################################################

#endif
