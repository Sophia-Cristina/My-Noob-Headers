#pragma once

#ifndef YSXELECTR_H
#define YSXELECTR_H

#include "ysxCImg.h" // Some output needs
#include "ysxConst.h";
#include "ysxBytes.h"

// #####################
// ####### By Sophia Cristina
// ####### Simulating electronic devices with my
// ####### best attempt at having accuracy.
// #####################

// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################
// ################################################# ANOTAÇÕES E ATENÇÕES #################################################
// !!!!!!!	
// !!!!!!!	CATALOGAR TODAS AS MUDANÇAS QUE PODEM AFETAR VERSÕES DE CÓDIGO:
// !!!!!!!	* Tirei ponteiro para "Component" no "Wire", agora deve testar outputs e inputs destes e o "SendSignal()";
// !!!!!!!	
// ################################################# ANOTAÇÕES E ATENÇÕES #################################################
// ############################################################################################################################################
// ############################################################################################################################################
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

// ############################
// ####### TRIGONEMETRICOS E SINAIS
// ############################

// Signal:
std::vector<double> SignalVec(int Size, double Volts) { std::vector<double> s(Size); for (int n = 0; n < Size; ++n) { s[n] = Volts; } return(s); }
std::vector<double> SignalVec(int Size, double Volts, double NoiseGain)
{
    std::vector<double> s(Size);
    for (int n = 0; n < Size; ++n) { s[n] = Volts - NoiseGain + NoiseGain * (((rand() % 20001) - 10000) / 10000.0); }
    return(s);
}

// Step signal:
//double StepSig(int n) { if (n >= 0) { return(1); } return(0); }

// Seno (phase in radians):
std::vector<double> SineWaveVec(int Size, double x0, double x1, double Amp, double Freq, double Phase)
{
    std::vector<double> R; if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size; for (int n = 0; n < Size; ++n) { R.push_back(Amp * sin(Phase + (x0 + (Delta * n * Freq)))); } return(R);
}

// Coseno (phase in radians):
std::vector<double> CosineWaveVec(int Size, double x0, double x1, double Amp, double Freq, double Phase)
{
    std::vector<double> R; if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size; for (int n = 0; n < Size; ++n) { R.push_back(Amp * cos(Phase + (x0 + (Delta * n * Freq)))); } return(R);
}

// Tangente (phase in radians):
std::vector<double> TangentWaveVec(int Size, double x0, double x1, double Amp, double Freq, double Phase)
{
    std::vector<double> R; if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size; for (int n = 0; n < Size; ++n) { R.push_back(Amp * tan(Phase + (x0 + (Delta * n * Freq)))); } return(R);
}

// Cotangente (phase in radians):
std::vector<double> CotangentWaveVec(int Size, double x0, double x1, double Amp, double Freq, double Phase)
{
    std::vector<double> R; if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size; for (int n = 0; n < Size; ++n) { R.push_back(Amp * cot(Phase + (x0 + (Delta * n * Freq)))); } return(R);
}

// SquareWave (phase in radians):
std::vector<double> SquareWaveVec(int Size, double x0, double x1, double Amp, double Freq, double Phase)
{
    std::vector<double> R; if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size; for (int n = 0; n < Size; ++n) { R.push_back(Amp * rect(Phase + (x0 + (Delta * n * Freq)))); } return(R);
}

// SawWave (phase in radians):
std::vector<double> SawWaveVec(int Size, double x0, double x1, double Amp, double Freq, double Phase)
{
    std::vector<double> R; if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size; for (int n = 0; n < Size; ++n) { R.push_back(Amp * saw(Phase + (x0 + (Delta * n * Freq)))); } return(R);
}

// SawWave (phase in radians):
std::vector<double> TriWaveVec(int Size, double x0, double x1, double Amp, double Freq, double Phase)
{
    std::vector<double> R; if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size; for (int n = 0; n < Size; ++n) { R.push_back(Amp * tri(Phase + (x0 + (Delta * n) * Freq))); } return(R);
}

// Miniform vector (phase in radians):
std::vector<double> MiniFormVec(int Size, double x0, double x1, double Amp, double Freq, double Phase)
{
    std::vector<double> R; if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size; for (int n = 0; n < Size; ++n) { R.push_back(Amp * MiniForm(Phase + x0 + (Delta * n), Freq)); } return(R);
}

// Linha:
std::vector<double> LineVec(int Size, double x0, double x1, double Sum, double Mult)
{
    std::vector<double> R; if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size; for (int n = 0; n < Size; ++n) { double x = x0 + (Delta * n); R.push_back(Sum + x * Mult); } return(R);
}

// Linha curva por exponente | 'x^Pow / Div^Pow':
std::vector<double> ExpCurveVec(int Size, double x0, double x1, double Pow, double Div)
{
    std::vector<double> R; if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size;
    for (int n = 0; n < Size; ++n) { double x = x0 + (Delta * n); R.push_back(pow(x, Pow) / pow(Div, Pow)); }
    return(R);
}

// Vetor Exponencial 'a^n'':
std::vector<double> ExponentVec(int Size, double x0, double x1, double a)
{
    std::vector<double> V;
    for (int n = 0; n < Size; ++n)
    {
        V.push_back(pow(a, n));
    }
    return(V);
}

// Vetor Exponencial 'B * (r^n)':
std::vector<double> ExponentVec(int Size, double x0, double x1, double B, double r)
{
    std::vector<double> V;

    for (int n = 0; n < Size; ++n)
    {
        V.push_back(B * pow(r, n));
    }
    return(V);
}

// ### TIME BASED:

// Seno com mudança de frequencia por tempo:
std::vector<double> SineWaveVecTimeFreq(int Size, double x0, double x1, double TimeRatio, double Gain, double Freq, double Phase)
{
    std::vector<double> R; if (x0 > x1) { double t = x0; x0 = x1; x1 = t; }
    double Delta = (x1 - x0) / Size;
    for (int n = 0; n < Size; ++n) { R.push_back(Gain * sin(Phase + x0 + Freq * pow(TimeRatio, n) * Delta * n)); } return(R);
}
// Seno com mudança de fase por tempo:
std::vector<double> SineWaveVecTimePhase(int Size, double x0, double x1, double TimeRatio, double Gain, double Freq, double Phase)
{
    std::vector<double> R; if (x0 > x1) { double t = x0; x0 = x1; x1 = t; }
    double Delta = (x1 - x0) / Size;
    for (int n = 0; n < Size; ++n) { R.push_back(Gain * sin((pow(TimeRatio, n) * Phase) + (x0 + (Delta * n * Freq)))); } return(R);
}
// Seno com mudança de ganho por tempo:
std::vector<double> SineWaveVecTimeGain(int Size, double x0, double x1, double TimeRatio, double Gain, double Freq, double Phase)
{
    std::vector<double> R; if (x0 > x1) { double t = x0; x0 = x1; x1 = t; }
    double Delta = (x1 - x0) / Size;
    for (int n = 0; n < Size; ++n) { R.push_back((pow(TimeRatio, n) * Gain) * sin(Phase + x0 + (Delta * n * Freq))); } return(R);
}
// Seno com mudança de frequencia por modulação (FM):
std::vector<double> SineWaveVecFM(int Size, double x0, double x1, double Gain, double Freq, double FreqFM, double Phase)
{
    std::vector<double> R; if (x0 > x1) { double t = x0; x0 = x1; x1 = t; }
    double Delta = (x1 - x0) / Size;
    for (int n = 0; n < Size; ++n)
    {
        double x = Phase + (x0 + Freq * Delta * n);
        double xm = Phase + (x0 + FreqFM * Delta * n);
        R.push_back(Gain * sin(sin(x) * FreqFM));
    }
    return(R);
}

// ### NOISE:

// White noise ((-1 to +1) * Gain):
std::vector<double> WhiteNoise(int Size, double Gain)
{
    std::vector<double> WN; for (int n = 0; n < Size; ++n) { int Random = rand() % 20001; double RealVal = (Random - 10000) / 10000.0; WN.push_back(Gain * RealVal); } return(WN);
}
// White noise (Sum + Gain * (-1 to +1)):
std::vector<double> WhiteNoise(int Size, double Gain, double Sum)
{
    std::vector<double> WN; for (int n = 0; n < Size; ++n) { int Random = rand() % 20001; double RealVal = (Random - 10000) / 10000.0; WN.push_back(Sum + Gain * RealVal); } return(WN);
}
// White noise ((-1 to +1) * Gain):
std::vector<double> WhiteNoiseAbs(int Size, double Gain)
{
    std::vector<double> WN; for (int n = 0; n < Size; ++n) { int Random = rand() % 10001; double RealVal = Random / 10000.0; WN.push_back(Gain * RealVal); } return(WN);
}
// White noise (Sum + Gain * (-1 to +1)):
std::vector<double> WhiteNoiseAbs(int Size, double Gain, double Sum)
{
    std::vector<double> WN; for (int n = 0; n < Size; ++n) { int Random = rand() % 10001; double RealVal = Random / 10000.0; WN.push_back(Sum + Gain * RealVal); } return(WN);
}

// ADD NOISE TO VECTOR:
void AddNoise(std::vector<double>& V, double NoiseGain)
{
    double Amp = MaxVec(V);
    for (int n = 0; n < V.size(); ++n)
    {
        double Rand = ((rand() % 20001) - 10000) / 10000.0;
        V[n] = V[n] - NoiseGain + Rand * NoiseGain;
    }
}

// NOISE SAMPLE:
double NoiseSample(double Volts, double NoiseGain) { return(Volts - NoiseGain + NoiseGain * (((rand() % 20001) - 10000) / 10000.0)); }

// ####################################################################################################################################################################################################
// ####################################################################################################################################################################################################
// ####################################################################################################################################################################################################

// ############################
// ####### ENVELOPES
// ############################

// Attack Decay, considerando o numero de dados num 'vector',
// portanto A e D são razões:
std::vector<double> AttackDecay(std::vector<double> Input, double A, double D, double Gain)
{
    std::vector<double> R;
    double Sum = A + D, RatioA = A / Sum, RatioD = D / Sum;
    int Size = Input.size(); int SizeA = floor(Size * RatioA), SizeD = Size - SizeA;
    double DeltaA = 1.0 / SizeA, DeltaD = 1.0 / SizeD;
    //cout << " Size: " << Size << " | SA: " << SizeA << " | SD: " << SizeD << " | DeltaA: " << DeltaA << " | DeltaD: " << DeltaD << std::endl;
    for (int n = 0; n < SizeA; ++n) { double x = DeltaA * n; R.push_back(x * Input[n] * Gain); }
    for (int n = SizeA; n < Size; ++n) { double x = DeltaD * (n - SizeA); R.push_back((1 - x) * Input[n] * Gain); }
    return(R);
}

// Attack Envelope
std::vector<double> AttackVector(std::vector<double> Input, double Gain)
{
    std::vector<double> R;
    int Size = Input.size();
    for (int n = 0; n < Size; ++n) { double x = n / (double)Size; R.push_back(x * Input[n] * Gain); }
    return(R);
}
// Attack Exponetial Envelope
std::vector<double> AttackExpVector(std::vector<double> Input, double Pow, double Gain)
{
    std::vector<double> R;
    int Size = Input.size();
    for (int n = 0; n < Size; ++n) { double x = pow(n, Pow) / pow(Size, Pow); R.push_back(x * Input[n] * Gain); }
    return(R);
}

// Decay Envelope
std::vector<double> DecayVector(std::vector<double> Input, double Gain)
{
    std::vector<double> R;
    int Size = Input.size();
    for (int n = 0; n < Size; ++n) { double x = (Size - n) / Size; R.push_back(x * Input[n] * Gain); }
    return(R);
}

// Decay Exponetial Envelope
std::vector<double> DecayExpVector(std::vector<double> Input, double Pow, double Gain)
{
    std::vector<double> R;
    int Size = Input.size();
    for (int n = 0; n < Size; ++n) { double x = pow(Size - n, Pow) / pow(Size, Pow); R.push_back(x * Input[n] * Gain); }
    return(R);
}

// Change Input Vector by a graduation from L1 to L2, similar to an Attack, but with both sides:
std::vector<double> LineEnvelop(std::vector<double> Input, double L1, double L2, double Gain)
{
    std::vector<double> R;
    int Size = Input.size();
    if (L1 > 1) { L1 = 1; } if (L1 < 0) { L1 = 0; } if (L2 > 1) { L2 = 1; } if (L2 < 0) { L2 = 0; }
    //double BigL = L2; if (L1 > L2) { BigL = L1; } double SmallL = L1; if (L1 > L2) { SmallL = L2; }
    //double DeltaL = BigL - SmallL, Delta = DeltaL / Size;
    double DeltaL = L2 - L1, Delta = DeltaL / Size;
    for (int n = 0; n < Size; ++n) { double x = L1 + Delta * n; R.push_back(x * Input[n] * Gain); }
    return(R);
}

// Change Input Vector by a exponential graduation from L1 to L2, similar to an Attack, but with both sides:
/*std::vector<double> LineExpEnvelop(std::vector<double> Input, double L1, double L2, double Pow, double Gain)
{
    std::vector<double> R;
    int Size = Input.size();
    if (L1 > 1) { L1 = 1; } if (L1 < 0) { L1 = 0; } if (L2 > 1) { L2 = 1; } if (L2 < 0) { L2 = 0; }
    //double BigL = L2; if (L1 > L2) { BigL = L1; } double SmallL = L1; if (L1 > L2) { SmallL = L2; }
    //double DeltaL = BigL - SmallL, Delta = DeltaL / Size;
    double Delta = L2 - L1;
    for (int n = 0; n < Size; ++n) { double x = L1 + pow(Delta * n, Pow) / pow(Size, Pow); R.push_back(x * Input[n] * Gain); }
    return(R);
}*/

// MODULATE VECTOR WITH ANOTHER VECTOR.
// Last index will be from input:
std::vector<double> VectorEnvelop(std::vector<double> Input, std::vector<double> Modulator, double Gain)
{
    std::vector<double> V; for (int n = 0; n < Input.size(); ++n) { if (n < Modulator.size()) { V.push_back(Input[n] * Modulator[n] * Gain); } else { V.push_back(Input[n] * Gain); } } return(V);
}

// std::vector<double> ADSR

// ####### NORMALIZERS #######

// IF BIGGER THAN Y THEN Y:
std::vector<double> LimitToptoY(std::vector<double> fx, double Y) { std::vector<double> gx = fx; for (int n = 0; n < gx.size(); ++n) { if (gx[n] > Y) { gx[n] = Y; } } return(gx); }

// IF BIGGER THAN Y AND LOWER THAN -Y, THEN Y AND -Y:
std::vector<double> LimittoY(std::vector<double> fx, double Y) { std::vector<double> gx = fx; for (int n = 0; n < gx.size(); ++n) { if (gx[n] > Y) { gx[n] = Y; } else if (gx[n] < -Y) { gx[n] = -Y; } } return(gx); }

// IF BIGGER THAN Y1 AND LOWER THAN Y0, THEN Y1 AND Y0:
std::vector<double> LimittoY1Y0(std::vector<double> fx, double Y1, double Y0)
{
    if (Y0 == Y1) { Y0 += 1.0e-9; } if (Y1 < Y0) { double T = Y1; Y1 = Y0; Y0 = T; }
    std::vector<double> gx = fx; for (int n = 0; n < gx.size(); ++n) { if (gx[n] > Y1) { gx[n] = Y1; } else if (gx[n] < Y0) { gx[n] = Y0; } } return(gx);
}

// MAX (TOP OF VECTOR) IS DIVIDED BY MAX:
std::vector<int> NormalizeTopto1(std::vector<int> fx) { std::vector<int> gx = fx; double Max = MaxVec(gx); if (Max == 0) { Max = 1.0e-9; } for (int n = 0; n < gx.size(); ++n) { gx[n] /= Max; } return(gx); }
std::vector<double> NormalizeTopto1(std::vector<double> fx) { std::vector<double> gx = fx; double Max = MaxVec(gx); if (Max == 0) { Max = 1.0e-9; } for (int n = 0; n < gx.size(); ++n) { gx[n] /= Max; } return(gx); }

// IF MAX AND MIN IS BIGGER THAN 1 AND LOWER THAN -1, DIVIDE BY THE BIGGER ABSOLUTE:
std::vector<int> Normalize(std::vector<int> fx) { std::vector<int> gx = fx; int Max = MaxVecAbs(gx); if (Max == 0) { Max = 1.0e-9; } for (int n = 0; n < gx.size(); ++n) { gx[n] /= Max; } return(gx); }
std::vector<double> Normalize(std::vector<double> fx) { std::vector<double> gx = fx; double Max = MaxVecAbs(gx); if (Max == 0) { Max = 1.0e-9; } for (int n = 0; n < gx.size(); ++n) { gx[n] /= Max; } return(gx); }

// MOD NORMALIZE, (f(x) + 1) * 0.5:
std::vector<int> NormalizeModTopto1(std::vector<int> fx)
{
    std::vector<int> gx = fx; double Max = MaxVec(gx); if (Max == 0) { Max = 1.0e-9; } for (int n = 0; n < gx.size(); ++n) { gx[n] /= Max; gx[n] += 1; gx[n] *= 0.5; } return(gx);
}
std::vector<double> NormalizeModTopto1(std::vector<double> fx)
{
    std::vector<double> gx = fx; double Max = MaxVec(gx); if (Max == 0) { Max = 1.0e-9; } for (int n = 0; n < gx.size(); ++n) { gx[n] /= Max; gx[n] += 1; gx[n] *= 0.5; } return(gx);
}
std::vector<int> NormalizeMod(std::vector<int> fx) { std::vector<int> gx = fx; int Max = MaxVecAbs(gx); if (Max == 0) { Max = 1.0e-9; } for (int n = 0; n < gx.size(); ++n) { gx[n] /= Max; gx[n] += 1; gx[n] *= 0.5; } return(gx); }
std::vector<double> NormalizeMod(std::vector<double> fx)
{
    std::vector<double> gx = fx; double Max = MaxVecAbs(gx); if (Max == 0) { Max = 1.0e-9; } for (int n = 0; n < gx.size(); ++n) { gx[n] /= Max; gx[n] += 1; gx[n] *= 0.5; } return(gx);
}


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
    int Samples = 64; // This probably is only going to be used in components which power up stuffs
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
        for (int n = 0; n < 4; ++n) { if (n < SetID4chars.size()) { ID[n] = SetID4chars[n]; } else { ID[n] = ' '; } }
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
            for (int n = 0; n < OUTs.size(); ++n)
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
                    for (int n = 2; n < Signals.size(); ++n) { Sum = SumTwoVec(Sum, Signals[n]); }
                }
            }
        }
        if (OUTs.size() > 0) { for (int n = 0; n < OUTs.size(); ++n) { *OUTs[n] = Sum; } }
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
        for (int n = 0; n < Signals[0].size(); ++n)
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
        unsigned char clr[] = { Red, Whiteness, Whiteness };

        I.draw_circle(LEDSize * 0.5, LEDSize * 0.5, LEDSize * 0.5, clr, 1, 1);
        FillArea(I, LEDSize * 0.5, LEDSize * 0.5, Red, Whiteness, Whiteness);
        std::string str = "LED " + std::to_string(Volts) + "v\nSig.: " + std::to_string(Val) + "v\nSample: " + std::to_string(SigSample);
        AddText(I, LEDSize * 0.25, LEDSize * 0.25, str, 255 - Red, 255 - Whiteness, 255 - Whiteness);
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
        Print = CImg<unsigned char>::CImg(x, y, 1, 3, 0); FillArea(Print, 2, 2, 7, 31, 7);
        if (Neg) { MetricLines(Print, -Volts, Volts, 4, false, true, 23, 95, 23); }
        else { MetricLines(Print, 0, Volts, 8, false, true, 23, 95, 23); } // !!!!!!! ATTENTION, THE IMAGE PLOTTER IS PLOTTING IN THE MIDDLE OF IMAGE, FIX IT BEFORE USING THIS CODE !!!!!!!
        MetricLines(Print, 0, Signals[0].size(), 4, true, false, 23, 95, 23); // I don't know why it isn't printing the horizontal division... :s
    }
    //void Zoom() {} // Use BlockZoom here!
    // #################################################
    void PrintImageInxCart(int Signal)
    {
        if (!Print.is_empty())
        {
            std::vector<double> S = Signals[Signal];
            double Max = MaxVec(S); MultVecTerms(S, 1.0 / Max); MultVecTerms(S, 64);
            if (Neg) { PrintVectorLineOnImg(Print, S, Max / Volts, 47, 127, 47); }
            else { PrintVectorLineOnImg(Print, S, Max / Volts, 47, 127, 47); }
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
            double Max = MaxVec(S); MultVecTerms(S, 1.0 / Max); MultVecTerms(S, 64);
            PrintVectorLineOnImg(Print, S, Max / Volts, 47, 127, 47);
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
                unsigned char clr[] = { Red, Whiteness, Whiteness };
                int x = ((Bits - 1 - m) * LEDSize) + LEDSize * 0.5;
                int y = n * LEDSize + LEDSize * 0.5;
                I.draw_circle(x, y, LEDSize * 0.5, clr, 1, 1);
                FillArea(I, x, y, Red, Whiteness, Whiteness);
                Red = 31;
            }
        }
        CImg<unsigned char> Append(I.width(), 16, 1, 3, 64); // APPEND INFORMATION
        for (int n = 0; n < Bits; ++n)
        {
            AddText(Append, 4 + (Bits - 1 - n) * LEDSize, 2, std::to_string((int)pow(2, n)), 127, 127, 255);
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