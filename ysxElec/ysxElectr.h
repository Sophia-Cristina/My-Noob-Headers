#pragma once

#ifndef YSXELECTR_H
#define YSXELECTR_H

#include "ysxMath/ysxConst.h"
#include "ysxData/ysxBytes.h"
#include "ysxMath/ysxSignal.h"

// #####################
// ####### By Sophia Cristina
// ####### Simulating electronic devices with my
// ####### best attempt at having accuracy.
// #####################

// ############################################################################################################################################
// ################################################# NOTES AND ATTENTIONS #################################################
// !!!!!!!	
// !!!!!!!	CATALOGUE ANY CHANGE THAT CAN AFFECT CODE VERSIONS:
// !!!!!!!	* Took out pointer to "ysxELEC_Component" in "Wire", it now points to a vector buffer;
// !!!!!!!	
// ################################################# NOTES AND ATTENTIONS #################################################
// ############################################################################################################################################

// #################################################
// ##################### FORWARD DECLARATIONS:
// #################################################
// Nem funciona essas merdas:
//template<size_t SigSize> class ysxELEC_Component;
//template<size_t SigSize> class Wire;
// #################################################

// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// #################################################
// ####### CLASSES #######
// #################################################

// ####### PIECES AND TOOLS #######

// THIS SHOULD BE SEEM AS THE INCLUDE OF THE 'Component' CLASS :
class ysxELEC_CompConfig
{
public:
    uint32_t Samples = 64; // This probably is only going to be used in components which power up stuffs
    double Volts = 1; // For 'normalization'
    float NoiseGain = 0.1; // !!! Noise Multiplied by input vector is always scaled to 'Volts' !!!

    ysxELEC_CompConfig(int InSamples, double InVolts, float InNoiseGain)
    {
        Samples = InSamples;
        Volts = InVolts;
        NoiseGain = InNoiseGain;
    }    
};

// THIS SHOULD BE SEEM AS THE MAIN CLASS:
class ysxELEC_Component
{
public:
    // Every component should have at least one signal. Anyway, this is public, so you can modify at your risk.
    std::vector<std::vector<double>> Signals = std::vector<std::vector<double>>::vector(1);
    virtual void ProcessSignal() { }
    ~ysxELEC_Component() { }
};

// #################################################

// WIRE, YOU PROBABLY GONNA USE IT ON EVERYTHING:
class ysxELEC_Wire : public ysxELEC_Component
{
public:
    // If you need identification for your wire!
    // Standard is NONE, however, there is only 4 bytes, so you might use some binary code for 2^32 combinations.
    // You can transfer an int number to uint8[4] using a pointer.
    uint8_t ID[4] = { 'N', 'O', 'N', 'E' };
    
    // * OUTPUT can be another wire! Ex.: Wire W; OUTs.push_back(W.Signals[0]); // NOTE: Every component starts with at least one signal!
    // * OUTPUT can be itself! Ex.: OUTs.push_back(Signals[0]);
    std::vector<std::vector<double>*> OUTs;
    std::vector<double> SumSig;
    // #####################
    void ProcessSignal() override
    {
        if (OUTs.size() > 0)
        {
            for (uint32_t n = 0; n < Signals.size(); ++n)
            {
                if (SumSig.size() < Signals[n].size()) { SumSig.resize(Signals[n].size()); }
                for (uint32_t m = 0; m < Signals[n].size(); ++n)
                {
                    SumSig[m] += Signals[n][m];
                }
            }
            for (uint32_t n = 0; n < OUTs.size(); ++n) { *OUTs[n] = SumSig; }
            SumSig = std::vector<double>::vector();
        }
    }

    // #####################
    ysxELEC_Wire(uint8_t SetID[4])
    {
        ID[0] = SetID[0]; ID[1] = SetID[1];
        ID[2] = SetID[2]; ID[3] = SetID[3];
    }
    ysxELEC_Wire() { }
};

// ARRUMAR TUDO ISSO, ALIAS, INPUT DE WIRES AGORA:
class ysxELEC_SumWire : public ysxELEC_Component
{
public:
    std::vector<double> Sum;
    ysxELEC_SumWire() { }
    // #####################
    std::vector<std::vector<double>*> OUTs; // OUTPUT (it can be another wire)
    // #####################
    

    void ProcessSignal() override//, Component* Output) override
    {        
        if (Signals.size() > 0)
        {
            if (Signals.size() > 1)
            {
                for (uint32_t n = 0; n < Signals.size(); ++n) { Sum = ysxVEC_SumTwoVec(Sum, Signals[n]); }
            }
            else { Sum = Signals[0]; }
        }
        if (OUTs.size() > 0) { for (uint32_t n = 0; n < OUTs.size(); ++n) { *OUTs[n] = Sum; } }
    }
};

// #################################################
// #################################################
// #################################################

// ####### CURRENT CONTROL COMPONENTS #######

class ysxELEC_PowerDC : public ysxELEC_Component
{
public:
    ysxELEC_Wire* Output;
    ysxELEC_CompConfig* Config;
    std::vector<double> Sig;

    ysxELEC_PowerDC(ysxELEC_CompConfig& InConfig)
    {
        Sig = std::vector<double>::vector(InConfig.Samples);
        Config = &InConfig;
        for (size_t n = 0; n < Sig.size(); ++n)
        {
            Sig[n] = Config->Volts - Config->NoiseGain + Config->NoiseGain * ((double)((rand() % 20001) - 10000) / 10000);
        }
    }

    void ProcessSignal() override
    {
        for (size_t n = 0; n < Output->Signals.size(); ++n) { Output->Signals[n] = Sig; }
        //Output->ProcessSignal();
    }
};

// #################################################

class ysxELEC_Resistor : public ysxELEC_Component
{
public:
    double Ohms = 1;
    ysxELEC_Wire* Output;

    ysxELEC_Resistor(double SetOhms)
    {
        Ohms = SetOhms;
        if (Ohms == 0) { Ohms = 1; }
    }
    void ProcessSignal() override
    {
        if (Ohms == 0) { Ohms = 1; }
        Output->Signals[0] = Signals[0]; size_t os = Output->Signals[0].size();
        for (uint32_t n = 0; n < os; ++n) { Output->Signals[0][n] /= Ohms; }
        
    }
};


// #################################################

// CAPACITOR (W.I.P):
// For discrete time, i need to make a function to charge it by 'dt'.
// * Implementar um jeito de filtrar com eles.
class ysxELEC_Capacitor : public ysxELEC_Component
{
public:
    double F = 1, C, V, J; // Farad, Coulomb, Volts, Joules
    double Vd = 1; // Volt. Diff.
    ysxELEC_Wire* Output;

    ysxELEC_Capacitor(double Farad, double Volts) { F = Farad; if (F == 0) { F = 1; } V = Volts; C = F * V; J = 0.5 * F * V * V; }
    
    void ProcessSignal() override
    {
        if (F == 0) { F = 1; }
        Output->Signals[0] = Signals[0];
        for (uint32_t n = 0; n < Output->Signals[0].size(); ++n) { Output->Signals[0][n] = 1; } // W.I.P, because i'm making it possible to add, it ends with "= 1"
    }
};

double ysxELEC_CapacitancePara(ysxELEC_Capacitor* Caps, size_t TotalCaps)
{ double F = 0; for (size_t n = 0; n < TotalCaps; ++n) { F += Caps[n].F; } return(F); }
double ysxELEC_CapacitanceSer(ysxELEC_Capacitor* Caps, size_t TotalCaps)
{ double F = 0; for (size_t n = 0; n < TotalCaps; ++n) { F += 1 / Caps[n].F; } return(1 / F); }

// #################################################

/* Bipolar Junction Transistor, NPN PNP, needs two inputs:
 PNP can have one or two outputs.
 NPN: iC--v->oE | PNP: oC--v-<iE
         iB     |         oB
https://www.youtube.com/watch?v=J4oO7PT_nzQ */
class ysxELEC_TrnsBipolarSig : public ysxELEC_Component
{
public:
    double ActV = 0.6, BrnV = 1; // Volts to active it | Volts to burn it
    double Gain = 1, Ratio = 1; // If feedbacked, maybe there is a better way
    bool Burned = false, NPN_PNP = false;
    ysxELEC_Wire* Output; // Emitter

    ysxELEC_TrnsBipolarSig(bool NPNorPNP = 0)
    {
        size_t Size = Signals[0].size();
        Signals = std::vector<std::vector<double>>::vector(2);
        Signals[0] = std::vector<double>::vector(Size); // [0] = Collector / Emitter;
        Signals[1] = Signals[0]; // [1] = Base
        NPN_PNP = NPNorPNP;
    }

    void ProcessSignal() override
    {
        size_t s = Signals[0].size(), os = Output->Signals.size(), oss = Output->Signals[0].size();
        double Out = 0;
        for (uint32_t n = 0; n < s; ++n)
        {
            if (Signals[0][n] >= BrnV) { Burned = true; }
            if (Burned) { Output->Signals[0][n] = 0; }
            else
            {
                //if (Signals[0][n] != 0 && Signals[1][n] > ActV)
                if (NPN_PNP)
                {
                    if (Signals[1][n] > ActV)
                    {
                        if (n < oss)
                        {
                            Output->Signals[0][n] = Signals[0][n] - Signals[1][n];
                            if (os > 1) { Output->Signals[1][n] = Signals[1][n]; }
                        }
                    }
                    else { Output->Signals[0][n] = 0; }
                    //Ratio * (Signals[0][n] / Signals[1][n]); // Find ratio on the transistor datasheet
                }
                else
                {
                    if (Signals[1][n] > ActV)
                    {
                        Out = Signals[0][n] + Signals[1][n];
                        if (n < oss) { Output->Signals[0][n] = Out; }
                    }
                    else { Output->Signals[0][n] = 0; }
                }
            }
        }
        Output->ProcessSignal();
    }
};

/*
float W = CellxSize * 4, H = CellySize * 8;
        CImg<uint8_t> Monitor(W, H, 1, 3, 0);
        //FillArea(Monitor, 10, 10, 32, 0, 0); // I don't know why it don't works anymore...
        int Border = (Width < Height ? Width : Height) * 0.00777; if (Border < 1) { Border = 1; }
        BoxMatrix(Monitor, Border, 4, 8, 255, 255, 255);
        double T = Border;
        W /= 4.0; H /= 8.0;
        float WD = W - T;
        float HD = H - T;
        //bool Red = false;
        char Red = 32; char m = 0; uint32_t s = DATA.size();
        for (uint32_t Byte = 0; Byte < DATA.size(); Byte += 8)
        {
            for (char n = 0; n < 8; ++n)
            {
                for (char m = 0; m < 4; ++m)
                {
                    if (m == 3) { 1 == (DATA[(n % s) + Byte] & 0x01) ? Red = 191 : Red = 32; }
                    if (m == 2) { 2 == (DATA[(n % s) + Byte] & 0x02) ? Red = 191 : Red = 32; }
                    if (m == 1) { 4 == (DATA[(n % s) + Byte] & 0x04) ? Red = 191 : Red = 32; }
                    //if(n % 4 == 3) OUTs[n] & 0x08 ? Red = 32 : Red = 127;
                    //if(n % 4 == 4) OUTs[n] & 0x10 ? Red = 32 : Red = 127;
                    //if(n % 4 == 5) OUTs[n] & 0x20 ? Red = 32 : Red = 127;
                    DrawBar(Monitor, 1, T + m * W, m * W + WD, HD - 1, T + n * H, Red, 0, 0);
                    Red = 32;
                    //DrawBar(*I, 1, T, (W / 8.0) - T * 2.0, H - T * 2, (n * (W / 8) - T * 0.5) + T, 255, 0, 0);
                }
            }
        }
*/

/*
// ####### TEMPLATE:
class A : public ysxELEC_Component
{
public:
    double a = 1;
    ysxELEC_Wire* Output;

    A(double Seta) { a = Seta; }
    void ProcessSignal() override
    {
        for (uint32_t n = 0; n < Signals[0].size(); ++n) { //Something }
        Output->Signals[0] = Signals[0]; Output->ProcessSignal();
    }
};
*/

// ############################
// ####### ESPECIAL:
#include "ysxElec/ysxElecEmu.h"

// #####################################################################################################################################

// ################################################# FIM ####################################################################################

#endif // SCPARSE_