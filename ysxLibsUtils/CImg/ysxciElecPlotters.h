#pragma once

#ifndef YSXCIELECPLOTTER_H
#define YSXCIELECPLOTTER_H

// BE SURE THAT YOU HAVE INCLUDED:
//#include "ysxElec/ysxElectr.h"
// THIS FILE IS CO-DEPENDENT OF THE HEADER ABOVE!

// ############################################################################################################################################
// ################################################# NOTES #################################################
// !!!	
// !!!	
// !!!	
// ################################################# NOTES #################################################
// ############################################################################################################################################

// ###################################

// ############################################################################################################################################
// ############## LIGHTS AND REFERENCE COMPONENTS:

// MAKE LEDS, IT CAN HAVE MORE THAN ONE SIGNAL, HOWEVER, THE OUTPUT WILL BE THE AVERAGE OF THE SUM OF ALL SIGNALS:
// * Add ohmns *
template<size_t SigSize> class ysxELEC_CIMG_LED : public ysxELEC_Component
{
public:
    uint8_t LEDSize;
    double Volts, x;
    ysxELEC_Wire* Out;
    CImg<uint8_t> I;
    uint8_t Color[3];
    std::string Txt;

    // TAKE CARE WITH THE AMMOUNT OF COLLUMS, IT IS !!! A COLLUM PER BIT, NOT BYTE !!!:
    ysxELEC_CIMG_LED(uint8_t LED_Diameter, double Voltage)
    {
        LEDSize = LED_Diameter; Volts = Voltage;
        I = CImg<uint8_t>::CImg<uint8_t>(LEDSize, LEDSize, 1, 3, 255);
        I.draw_circle(LEDSize * 0.5, LEDSize * 0.5, LEDSize * 0.5, Color, 1, 1);
        FillArea(I, LEDSize * 0.5, LEDSize * 0.5, Color);
    }

    // CALLS IMAGE OF INDEX (SigSample) FROM CERTAIN SIGNAL (SigIndex):
    void SeeLED(uint32_t Sig, uint32_t Sample)
    {
        I = CImg<uint8_t>::CImg<uint8_t>(LEDSize, LEDSize, 1, 3, 255);
        x = Signals[Sig % Signals.size()][Sample % SigSize];
        Color[0] = round((x / Volts) * 160);
        Color[1] = round(pow((x / Volts), 7) * 63.0);
        Color[2] = Color[1];
        I.draw_circle(LEDSize * 0.5, LEDSize * 0.5, LEDSize * 0.5, Color, 1, 1);
        FillArea(I, LEDSize * 0.5, LEDSize * 0.5, Color);
        Txt = "LED " + std::to_string(Volts) + "v\nSig.: " + std::to_string(x) + "v\nSample: " + std::to_string(Sample);
        Color[0] = 255 - Color[0]; Color[1] = 255 - Color[1]; Color[2] = 255 - Color[2];
        ysxCIMG_AddText(I, LEDSize * 0.25, LEDSize * 0.25, Txt, Color);
    }

    // Join signals for output:
    void JoinSigs()
    {
        if (Signals.size() > 1)
        {
            Out->Signals[0] = Signals[0];
            for (int n = 1; n < Signals.size(); ++n)
            {
                Out->Signals[0] = ysxVEC_SumTwoVec(Signals[n], Out->Signals[0]);
            }
            ysxVEC_MultVecTerms(Out->Signals[0], 1.0 / Signals.size());
        }
        else { Out->Signals[0] = Signals[0]; }
    }

    // RUN PROGRAM FOR SOME SECONDS:
    // Negative numbers makes it run stopless, so close window to stop it!
    void ProcessSignal() override
    {
        uint32_t Sample = 0, Signal = 0;
        // #####################
        std::cout << "DOWN / UP = Last / Next Signal Sample | LEFT / RIGHT = Last / Next Signal\n\nTYPE SOMETHING TO CONTINUE: ";
        char NADA; std::cin >> NADA;
        SeeLED(0, 0);
        CImgDisplay D(I, "LED");
        while (!D.is_closed())
        {
            D.wait();
            if (D.is_keyARROWUP())
            {   // THERE IS PROBABLY A BETTER WAY TO DISPLAY, CHECK MY TETRIS FILE:
                ++Sample; Sample %= Signals[0].size(); SeeLED(Signal, Sample); D.display(I); std::cout << "Signal: " << Signal << " | Sample: " << Sample << std::endl;
            }
            if (D.is_keyARROWDOWN())
            {
                ++Sample; Sample %= Signals[0].size(); SeeLED(Signal, Sample); D.display(I); std::cout << "Signal: " << Signal << " | Sample: " << Sample << std::endl;
            }
            if (D.is_keyARROWRIGHT())
            {
                ++Signal; Signal %= Signals.size(); SeeLED(Signal, Sample); D.display(I); std::cout << "Signal: " << Signal << " | Sample: " << Sample << std::endl;
            }
            if (D.is_keyARROWLEFT())
            {
                --Signal; Signal %= Signals.size(); SeeLED(Signal, Sample); D.display(I); std::cout << "Signal: " << Signal << " | Sample: " << Sample << std::endl;
            }
        }
        // #####################
        JoinSigs();
        Out->ProcessSignal();
    }
};

// A LED Matrix that you can see your stuffs... The Voltage is how much Volts it needs to be fully lighten:
// I'll add outputs and ohmns in the future...
template<size_t SigSize> class ysxELEC_CIMG_LEDArray : public ysxELEC_Component
{
public:
    uint8_t LEDSize;
    uint8_t Bits; uint16_t Rows;
    double Volts;

    // TAKE CARE WITH THE AMMOUNT OF COLLUMS, IT IS !!! A COLLUM PER BIT, NOT BYTE !!!:
    ysxELEC_CIMG_LEDArray(uint8_t LED_Diameter, uint8_t Bytes, uint16_t iRows, double Voltage)
    {
        LEDSize = LED_Diameter; Bits = Bytes * 8; Rows = iRows; Volts = Voltage;
    }

    // CALLS IMAGE OF THE ARRAY FROM SIGNAL NUMBER 'INDEX', ROW PAGE BEGINS AT '0':
    // *** Take in mind that if it overflows the number of indexes in a signal, it will simple go back to zero (module) ***
    CImg<uint8_t> SeeArray(uint32_t SigIndex, uint32_t RowPage)
    {
        CImg<uint8_t> I(LEDSize * Bits, LEDSize * Rows, 1, 3, 255);
        uint8_t Red = 31; uint32_t s = Signals[SigIndex].size();
        for (uint32_t n = 0; n < Rows; ++n) // DRAW LED MATRIX
        {
            for (char m = 0; m < Bits; ++m)
            {
                double Val = Signals[SigIndex][(n * Bits + RowPage * Rows + m) % s];
                Red = round((Val / Volts) * 255);
                uint8_t Whiteness = round(pow((Val / Volts), 7) * 63.0);
                uint8_t Color[] = { Red, Whiteness, Whiteness };
                int x = ((Bits - 1 - m) * LEDSize) + LEDSize * 0.5;
                int y = n * LEDSize + LEDSize * 0.5;
                I.draw_circle(x, y, LEDSize * 0.5, Color, 1, 1);
                FillArea(I, x, y, Color);
                Red = 31;
            }
        }
        CImg<uint8_t> Append(I.width(), 16, 1, 3, 64); // APPEND INFORMATION
        for (uint32_t n = 0; n < Bits; ++n)
        {
            uint8_t Color[] = { 127, 127, 255 };
            ysxCIMG_AddText(Append, 4 + (Bits - 1 - n) * LEDSize, 2, std::to_string((int)pow(2, n)), Color);
        }
        I = JoinImg(Append, I, 1);
        return(I);
    }

    // RUN PROGRAM FOR SOME SECONDS:
    // Negative numbers makes it run stopless, so close window to stop it!
    void ProcessSignal() override
    {
        uint32_t Page = 0, Signal = 0;
        // #####################
        std::cout << "UP / DOWN = Rows Page\n\nTYPE SOMETHING TO CONTINUE: ";
        char NADA; std::cin >> NADA;
        CImg<uint8_t> Array = SeeArray(0, 0);
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

template<size_t SigSize> class ysxELEC_Oscilloscope : public ysxELEC_Component
{
public:
    double Volts = 0, BlockZoom = 1;
    uint16_t x, y;
    CImg<uint8_t> Print;
    bool Neg = true;
    // VOLTAGE TO APPEAR ON MONITOR | ZOOM BLOCK SAMPLE (PERCENTAGE) | SCREEN SIZE | NEGATIVE NUMBERS:
    ysxELEC_Oscilloscope(double iVolts, double iBlockZoom, uint16_t Screenx, uint16_t Screeny, bool InNeg)
    {
        Volts = iVolts, BlockZoom = iBlockZoom; x = Screenx; y = Screeny; Neg = InNeg;
        NewImage(Neg);
    }

    // #################################################
    void NewImage(bool Neg)
    {
        uint8_t Color[] = { 7, 31, 7 };
        Print = CImg<uint8_t>::CImg(x, y, 1, 3, 0); FillArea(Print, 2, 2, Color);
        Color[0] = 23; Color[1] = 95; Color[2] = 23;
        if (Neg) { ysxCIMG_DRAW_MetricLines(Print, -Volts, Volts, 4, false, true, Color); }
        else { ysxCIMG_DRAW_MetricLines(Print, 0, Volts, 8, false, true, Color); } // !!!!!!! ATTENTION, THE IMAGE PLOTTER IS PLOTTING IN THE MIDDLE OF IMAGE, FIX IT BEFORE USING THIS CODE !!!!!!!
        ysxCIMG_DRAW_MetricLines(Print, 0, Signals[0].size(), 4, true, false, Color); // I don't know why it isn't printing the horizontal division... :s
    }
    //void Zoom() {} // Use BlockZoom here!
    // #################################################
    void PrintImageInxCart(int Signal)
    {
        if (!Print.is_empty())
        {
            std::array<double, SigSize> S = Signals[Signal];
            double Max = MaxVec(S); MultVecTerms(S, 1.0 / Max); MultVecTerms(S, 64.0);
            uint8_t Color[] = { 47, 127, 47 };
            if (Neg) { ysxCIMG_DRAW_VectorLineOnImg(Print, S, Max / Volts, Color); }
            else { ysxCIMG_DRAW_VectorLineOnImg(Print, S, Max / Volts, Color); }
        }
    }

    // FAZER NA MESMA FUNÇÃO, SÓ TROCAR X POR Y E SX POR SY:
    //void PrintImageInyCart() { if (!Print.is_empty()) { double Max = MaxVec(Signals[Signal]); PrintVectorPointOnImg(Print, Signals[Signal], 64.0 / Max, 47, 127, 47); } } // I need to make a function for that
    // #################################################
    void PrintImageInPolar(int Signal)
    {
        // NOT POLAR YET
        if (!Print.is_empty())
        {
            std::array<double, SigSize> S = Signals[Signal];
            double Max = MaxVec(S); MultVecTerms(S, 1.0 / Max); MultVecTerms(S, 64.0);
            uint8_t Color[] = { 47, 127, 47 };
            PrintVectorLineOnImg(Print, S, Max / Volts, Color);
        }
    }
    // #################################################
    void ProcessSignal() override
    {

    }
};

// ################################################# FIM ####################################################################################

#endif // SCPARSE_