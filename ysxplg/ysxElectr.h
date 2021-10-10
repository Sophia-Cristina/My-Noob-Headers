#pragma once

#ifndef YSXELECTR_H
#define YSXELECTR_H

#include "ysxCImg.h" // Some output needs
#include "ysxConst.h";
#include "ysxBytes.h"
#include "ysxplg\\ysxSignal.h"

// #####################
// ####### By Sophia Cristina
// ####### Simulating electronic devices with my
// ####### best attempt at having accuracy.
// #####################

// ############################################################################################################################################
// ################################################# NOTES AND ATTENTIONS #################################################
// !!!!!!!	
// !!!!!!!	CATALOGUE ANY CHANGE THAT CAN AFFECT CODE VERSIONS:
// !!!!!!!	* Took out pointer to "Component" in "Wire", it now points to a vector buffer;
// !!!!!!!	* PAY ATTENTION to any change that may affect 'ysxSDLSudio' classes, since electronic devices normally have alike terms to music devices;
// !!!!!!!	
// ################################################# NOTES AND ATTENTIONS #################################################
// ############################################################################################################################################

// #################################################
// ##################### FORWARD DECLARATIONS:
// #################################################
// Nem funciona essas merdas:
class Component;
class Wire;
// #################################################

// ####################################################################################################################################################################################################
// ####################################################################################################################################################################################################
// ####################################################################################################################################################################################################


// ####################################################################################################################################################################################################
// ####################################################################################################################################################################################################
// ####################################################################################################################################################################################################

// #################################################
// ####### CLASSES #######
// #################################################

// ####### PIECES AND TOOLS #######

// THIS SHOULD BE SEEM AS THE INCLUDE OF THE 'Component' CLASS :
class CompConfig
{
public:
    unsigned int Samples = 64; // This probably is only going to be used in components which power up stuffs
    double Volts = 1; // For 'normalization'
    float NoiseGain = 0.1; // !!!Noise Multiplied by input vector is always normalized to 'Volts' !!!

    CompConfig(int InSamples, double InVolts, float InNoiseGain)
    {
        Samples = InSamples;
        Volts = InVolts;
        NoiseGain = InNoiseGain;
    }    
};

// THIS SHOULD BE SEEM AS THE MAIN CLASS:
class Component
{
public:
    // Every component should have at least one signal. Anyway, this is public, so you can modify at your risk.
    std::vector<std::vector<double>> Signals = std::vector<std::vector<double>>::vector(1);
    virtual void ProcessSignal() { }
    ~Component() { }
};

// #################################################

// WIRE, YOU PROBABLY GONNA USE IT ON EVERYTHING:
class Wire : public Component
{
public:
    // If you need identification for your wire!
    // Standard is NONE, however, there is only 4 bytes, so, you may use some binary code for 2^32 combinations.
    // You can transfer an int number to char[4] using a pointer.
    unsigned char ID[4] = { 'N', 'O', 'N', 'E' };
    
    Wire(std::string SetID4chars)
    {
        for (unsigned char n = 0; n < 4; ++n) { if (n < SetID4chars.size()) { ID[n] = SetID4chars[n]; } else { ID[n] = ' '; } }
    }
    Wire() { }
    // #####################
    // * OUTPUT can be another wire! Ex.: Wire W; OUTs.push_back(W.Signals[0]); // NOTE: Every component starts with at least one signal!
    // * OUTPUT can be itself! Ex.: OUTs.push_back(Signals[0]);
    std::vector<std::vector<double>*> OUTs;
    // #####################
    void ProcessSignal() override
    {
        if (OUTs.size() > 0)
        {
            for (unsigned int n = 0; n < OUTs.size(); ++n)
            {
                if (n < OUTs.size())
                {
                    *OUTs[n] = Signals[n % Signals.size()]; // Load Signal
                }
                else { break; }
            }
        }
    }
};

// ARRUMAR TUDO ISSO, ALIAS, INPUT DE WIRES AGORA:
class SumWire : public Component
{
public:
    //std::vector<double> TheSum;
    SumWire()
    {
    }
    // #####################
    std::vector<std::vector<double>*> OUTs; // OUTPUT (it can be another wire)
    // #####################
    

    void ProcessSignal() override//, Component* Output) override
    {
        std::vector<double> Sum;
        if (Signals.size() > 0)
        {
            if (Signals.size() == 1) { Sum = Signals[0]; }
            else
            {
                Sum = SumTwoVec(Signals[0], Signals[1]);
                if (Signals.size() > 2)
                {
                    for (unsigned int n = 2; n < Signals.size(); ++n) { Sum = SumTwoVec(Sum, Signals[n]); }
                }
            }
        }
        if (OUTs.size() > 0) { for (unsigned int n = 0; n < OUTs.size(); ++n) { *OUTs[n] = Sum; } }
    }
};

// #################################################
// #################################################
// #################################################

// ####### CURRENT CONTROL COMPONENTS #######

class PowerDC : public Component
{
public:
    Wire* Output;
    CompConfig* Config;
    std::vector<double> Sig;

    PowerDC(CompConfig& InConfig)
    {
        Config = &InConfig;
        Sig = SignalVec(Config->Samples, Config->Volts, Config->NoiseGain);
    }

    void ProcessSignal() override
    {
        Output->Signals[0] = Sig;
        Output->ProcessSignal();
    }

    //void ProcessSignal(std::vector<double> Sig) { Output->SendSignal(Sig); }
};

// #################################################

class Resistor : public Component
{
public:
    double Ohms = 1;
    Wire* Output;

    Resistor(double SetOhms)
    {
        Ohms = SetOhms;
        if (Ohms == 0) { Ohms = 1; }
    }
    void ProcessSignal() override
    {
        if (Ohms == 0) { Ohms = 1; }
        for (unsigned int n = 0; n < Signals[0].size(); ++n)
        {
            Signals[0][n] /= Ohms; Output->Signals[0] = Signals[0]; Output->ProcessSignal();
        }
    }
};

// #################################################
// #################################################
// #################################################

// MAKE LEDS, IT CAN HAVE MORE THAN ONE SIGNAL, HOWEVER, THE OUTPUT WILL BE THE AVERAGE OF THE SUM OF ALL SIGNALS:
class LED : public Component
{
public:
    unsigned char LEDSize;
    double Volts;
    Wire* Out;

    // TAKE CARE WITH THE AMMOUNT OF COLLUMS, IT IS !!! A COLLUM PER BIT, NOT BYTE !!!:
    LED(unsigned char LED_Diameter, double Voltage)
    {
        LEDSize = LED_Diameter; Volts = Voltage;
    }

    // CALLS IMAGE OF INDEX (SigSample) FROM CERTAIN SIGNAL (SigIndex):
    CImg<unsigned char> SeeLED(unsigned int SigIndex, unsigned int SigSample)
    {
        CImg<unsigned char> I(LEDSize, LEDSize, 1, 3, 255);
        unsigned char Red = 31; unsigned int s = Signals[SigIndex].size();
        double Val = Signals[SigIndex][SigSample % s];
        
        Red = round((Val / Volts) * 160);
        unsigned char Whiteness = round(pow((Val / Volts), 7) * 63.0);
        unsigned char Color[] = { Red, Whiteness, Whiteness };

        I.draw_circle(LEDSize * 0.5, LEDSize * 0.5, LEDSize * 0.5, Color, 1, 1);
        FillArea(I, LEDSize * 0.5, LEDSize * 0.5, Color);
        std::string str = "LED " + std::to_string(Volts) + "v\nSig.: " + std::to_string(Val) + "v\nSample: " + std::to_string(SigSample);
        Color[0] = 255 - Color[0]; Color[1] = 255 - Color[1]; Color[2] = 255 - Color[2];
        AddText(I, LEDSize * 0.25, LEDSize * 0.25, str, Color);
        Red = 31;
        return(I);
    }

    // Join signals for output:
    void JoinSigs()
    {
        if (Signals.size() > 1)
        {
            Out->Signals[0] = Signals[0];
            for (int n = 1; n < Signals.size(); ++n)
            {
                Out->Signals[0] = SumTwoVec(Signals[n], Out->Signals[0]);
            }
            MultVecTerms(Out->Signals[0], 1.0 / Signals.size());
        }
        else { Out->Signals[0] = Signals[0]; }
    }

    // RUN PROGRAM FOR SOME SECONDS:
    // Negative numbers makes it run stopless, so close window to stop it!
    void ProcessSignal() override
    {
        unsigned int Sample = 0, Signal = 0;
        // #####################
        std::cout << "DOWN / UP = Last / Next Signal Sample | LEFT / RIGHT = Last / Next Signal\n\nTYPE SOMETHING TO CONTINUE: ";
        char NADA; std::cin >> NADA;
        CImg<unsigned char> Array = SeeLED(0, 0);
        CImgDisplay D(Array, "LED");
        while (!D.is_closed())
        {
            D.wait();
            if (D.is_keyARROWUP())
            { ++Sample; Sample %= Signals[0].size(); Array = SeeLED(Signal, Sample); D.display(Array); std::cout << "Signal: " << Signal << " | Sample: " << Sample << std::endl; }
            if (D.is_keyARROWDOWN())
            { ++Sample; Sample %= Signals[0].size(); Array = SeeLED(Signal, Sample); D.display(Array); std::cout << "Signal: " << Signal << " | Sample: " << Sample << std::endl; }
            if (D.is_keyARROWRIGHT())
            { ++Signal; Signal %= Signals.size(); Array = SeeLED(Signal, Sample); D.display(Array); std::cout << "Signal: " << Signal << " | Sample: " << Sample << std::endl; }
            if (D.is_keyARROWLEFT())
            { --Signal; Signal %= Signals.size(); Array = SeeLED(Signal, Sample); D.display(Array); std::cout << "Signal: " << Signal << " | Sample: " << Sample << std::endl; }
        }
        // #####################
        JoinSigs();
        Out->ProcessSignal();
    }
};

class Oscilloscope : public Component
{
public:
    double Volts = 0, BlockZoom = 1;
    unsigned short x, y;
    CImg<unsigned char> Print;
    bool Neg = true;
    // VOLTAGE TO APPEAR ON MONITOR | ZOOM BLOCK SAMPLE (PERCENTAGE) | SCREEN SIZE | NEGATIVE NUMBERS:
    Oscilloscope(double iVolts, double iBlockZoom, unsigned short Screenx, unsigned short Screeny, bool InNeg)
    {
        Volts = iVolts, BlockZoom = iBlockZoom; x = Screenx; y = Screeny; Neg = InNeg;
        NewImage(Neg);
    }

    // #################################################
    void NewImage(bool Neg)
    {
        unsigned char Color[] = { 7, 31, 7 };
        Print = CImg<unsigned char>::CImg(x, y, 1, 3, 0); FillArea(Print, 2, 2, Color);
        Color[0] = 23; Color[1] = 95; Color[2] = 23;
        if (Neg) { MetricLines(Print, -Volts, Volts, 4, false, true, Color); }
        else { MetricLines(Print, 0, Volts, 8, false, true, Color); } // !!!!!!! ATTENTION, THE IMAGE PLOTTER IS PLOTTING IN THE MIDDLE OF IMAGE, FIX IT BEFORE USING THIS CODE !!!!!!!
        MetricLines(Print, 0, Signals[0].size(), 4, true, false, Color); // I don't know why it isn't printing the horizontal division... :s
    }
    //void Zoom() {} // Use BlockZoom here!
    // #################################################
    void PrintImageInxCart(int Signal)
    {
        if (!Print.is_empty())
        {
            std::vector<double> S = Signals[Signal];
            double Max = MaxVec(S); MultVecTerms(S, 1.0 / Max); MultVecTerms(S, 64.0);
            unsigned char Color[] = { 47, 127, 47 };
            if (Neg) { PrintVectorLineOnImg(Print, S, Max / Volts, Color); }
            else { PrintVectorLineOnImg(Print, S, Max / Volts, Color); }
        }
    }

    // FAZER NA MESMA FUNÇÃO, SÓ TROCAR X POR Y E SX POR SY:
    //void PrintImageIny() { if (!Print.is_empty()) { double Max = MaxVec(Signals[Signal]); PrintVectorPointOnImg(Print, Signals[Signal], 64.0 / Max, 47, 127, 47); } } // I need to make a function for that
    // #################################################
    void PrintImageInxPolar(int Signal)
    {
        // NOT POLAR YET
        if (!Print.is_empty())
        {
            std::vector<double> S = Signals[Signal];
            double Max = MaxVec(S); MultVecTerms(S, 1.0 / Max); MultVecTerms(S, 64.0);
            unsigned char Color[] = { 47, 127, 47 };
            PrintVectorLineOnImg(Print, S, Max / Volts, Color);
        }
    } 
    // #################################################
    void ProcessSignal() override
    {

    }
};

// A LED Matrix that you can see your stuffs... The Voltage is how much Volts it needs to be fully lighten:
// I'll add outputs in the future...
class LEDArray : public Component
{
public:
    unsigned char LEDSize;
    unsigned char Bits; unsigned short Rows;
    double Volts;
    
    // TAKE CARE WITH THE AMMOUNT OF COLLUMS, IT IS !!! A COLLUM PER BIT, NOT BYTE !!!:
    LEDArray(unsigned char LED_Diameter, unsigned char Bytes, unsigned short iRows, double Voltage)
    {
        LEDSize = LED_Diameter; Bits = Bytes * 8; Rows = iRows; Volts = Voltage;
    }

    // CALLS IMAGE OF THE ARRAY FROM SIGNAL NUMBER 'INDEX', ROW PAGE BEGINS AT '0':
    // *** Take in mind that if it overflows the number of indexes in a signal, it will simple go back to zero (module) ***
    CImg<unsigned char> SeeArray(unsigned int SigIndex, unsigned int RowPage)
    {
        CImg<unsigned char> I(LEDSize * Bits, LEDSize * Rows, 1, 3, 255);
        unsigned char Red = 31; unsigned int s = Signals[SigIndex].size();
        for (unsigned int n = 0; n < Rows; ++n) // DRAW LED MATRIX
        {
            for (char m = 0; m < Bits; ++m)
            {
                double Val = Signals[SigIndex][(n * Bits + RowPage * Rows + m) % s];
                Red = round((Val / Volts) * 255);
                unsigned char Whiteness = round(pow((Val / Volts), 7) * 63.0);
                unsigned char Color[] = { Red, Whiteness, Whiteness };
                int x = ((Bits - 1 - m) * LEDSize) + LEDSize * 0.5;
                int y = n * LEDSize + LEDSize * 0.5;
                I.draw_circle(x, y, LEDSize * 0.5, Color, 1, 1);
                FillArea(I, x, y, Color);
                Red = 31;
            }
        }
        CImg<unsigned char> Append(I.width(), 16, 1, 3, 64); // APPEND INFORMATION
        for (unsigned int n = 0; n < Bits; ++n)
        {
            unsigned char Color[] = { 127, 127, 255 };
            AddText(Append, 4 + (Bits - 1 - n) * LEDSize, 2, std::to_string((int)pow(2, n)), Color);
        }
        I = JoinImg(Append, I, 1);
        return(I);
    }

    // RUN PROGRAM FOR SOME SECONDS:
    // Negative numbers makes it run stopless, so close window to stop it!
    void ProcessSignal() override
    {
        unsigned int Page = 0, Signal = 0;
        // #####################
        std::cout << "UP / DOWN = Rows Page\n\nTYPE SOMETHING TO CONTINUE: ";
        char NADA; std::cin >> NADA;
        CImg<unsigned char> Array = SeeArray(0, 0);
        CImgDisplay D(Array, "LEDS");
        while (!D.is_closed())
        {
            D.wait();
            if (D.is_keyARROWUP()) { ++Page; Page %= Signals[0].size(); Array = SeeArray(Signal, Page); D.display(Array); std::cout << "Signal: " << Signal << " | Page: " << Page << std::endl; }
            if (D.is_keyARROWDOWN()) { --Page; Page %= Signals[0].size(); Array = SeeArray(Signal, Page); D.display(Array); std::cout << "Signal: " << Signal << " | Page: " << Page << std::endl; }
            if (D.is_keyARROWRIGHT()) { ++Signal; Signal %= Signals.size(); Array = SeeArray(Signal, Page); D.display(Array); std::cout << "Signal: " << Signal << " | Page: " << Page << std::endl; }
            if (D.is_keyARROWLEFT()) { --Signal; Signal %= Signals.size(); Array = SeeArray(Signal, Page); D.display(Array); std::cout << "Signal: " << Signal << " | Page: " << Page << std::endl; }
        }
        // #####################
    }
};

/*
float W = CellxSize * 4, H = CellySize * 8;
        CImg<unsigned char> Monitor(W, H, 1, 3, 0);
        //FillArea(Monitor, 10, 10, 32, 0, 0); // I don't know why it don't works anymore...
        int Border = (Width < Height ? Width : Height) * 0.00777; if (Border < 1) { Border = 1; }
        BoxMatrix(Monitor, Border, 4, 8, 255, 255, 255);
        double T = Border;
        W /= 4.0; H /= 8.0;
        float WD = W - T;
        float HD = H - T;
        //bool Red = false;
        char Red = 32; char m = 0; unsigned int s = DATA.size();
        for (unsigned int Byte = 0; Byte < DATA.size(); Byte += 8)
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
class Resistor : public Component
{
public:
public:
    double Ohms = 0; // Power supply will send this ammount of Volts to a wire

    PowerDC(double SetOhms, Wire* SetOutput)
    {
        Ohms = SetOhms;
        Output = SetOutput;
    }

};
*/

// ############################
// ####### ESPECIAL:

// #####################################################################################################################################

// ################################################# FIM ####################################################################################

#endif // SCPARSE_