#pragma once

#ifndef YSXSIGNAL_H
#define YSXSIGNAL_H

// #####################
// ####### By Sophia Cristina
// ####### Signals, for emulator, simulator, math and more!
// #####################

// ############################################################################################################################################
// ################################################# NOTES AND ATTENTIONS #################################################
// !!!!!!!	
// !!!!!!!	CATALOGUE ANY CHANGE THAT CAN AFFECT CODE VERSIONS:
// !!!!!!!	* ATTENTION: This header MUST be included by 'ysxElectr.h'. Or else, you must include the headers that makes it work;
// !!!!!!!	
// ################################################# NOTES AND ATTENTIONS #################################################
// ############################################################################################################################################

// #################################################
// ##################### FORWARD DECLARATIONS:
// #################################################

// #################################################

// ####################################################################################################################################################################################################
// ####################################################################################################################################################################################################
// ####################################################################################################################################################################################################

// ############################
// ####### SIGNAL VECTORS #######
// ############################

// Signal:
std::vector<double> SignalVec(unsigned int Size, double Volts) { std::vector<double> s(Size); for (unsigned int n = 0; n < Size; ++n) { s[n] = Volts; } return(s); }
std::vector<double> SignalVec(unsigned int Size, double Volts, double NoiseGain)
{
    std::vector<double> s(Size);
    for (unsigned int n = 0; n < Size; ++n) { s[n] = Volts - NoiseGain + NoiseGain * (((rand() % 20001) - 10000) / 10000.0); }
    return(s);
}

// Step signal:
//double StepSig(int n) { if (n >= 0) { return(1); } return(0); }

// Seno (phase in radians):
std::vector<double> SineWaveVec(unsigned int Size, double x0, double x1, double Amp, double Freq, double Phase)
{
    std::vector<double> R(Size);
    if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size;
    for (unsigned int n = 0; n < Size; ++n) { R[n] = Amp * sin(Phase + (x0 + (Delta * n * Freq))); }
    return(R);
}
std::vector<float> SineWaveVecF(unsigned int Size, float x0, float x1, float Amp, float Freq, float Phase)
{
    std::vector<float> R(Size);
    if (x0 > x1) { float t = x0; x0 = x1; x1 = t; } float Delta = (x1 - x0) / Size;
    for (unsigned int n = 0; n < Size; ++n) { R[n] = Amp * sin(Phase + (x0 + (Delta * n * Freq))); }
    return(R);
}

// Coseno (phase in radians):
std::vector<double> CosineWaveVec(unsigned int Size, double x0, double x1, double Amp, double Freq, double Phase)
{
    std::vector<double> R(Size);
    if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size;
    for (unsigned int n = 0; n < Size; ++n) { R[n] = Amp * cos(Phase + (x0 + (Delta * n * Freq))); }
    return(R);
}
std::vector<float> CosineWaveVecF(unsigned int Size, float x0, float x1, float Amp, float Freq, float Phase)
{
    std::vector<float> R(Size);
    if (x0 > x1) { float t = x0; x0 = x1; x1 = t; } float Delta = (x1 - x0) / Size;
    for (unsigned int n = 0; n < Size; ++n) { R[n] = Amp * cos(Phase + (x0 + (Delta * n * Freq))); }
    return(R);
}

// Tangente (phase in radians):
std::vector<double> TangentWaveVec(unsigned int Size, double x0, double x1, double Amp, double Freq, double Phase)
{
    std::vector<double> R(Size);
    if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size;
    for (unsigned int n = 0; n < Size; ++n) { R[n] = Amp * tan(Phase + (x0 + (Delta * n * Freq))); }
    return(R);
}
std::vector<float> TangentWaveVecF(unsigned int Size, float x0, float x1, float Amp, float Freq, float Phase)
{
    std::vector<float> R(Size);
    if (x0 > x1) { float t = x0; x0 = x1; x1 = t; } float Delta = (x1 - x0) / Size;
    for (unsigned int n = 0; n < Size; ++n) { R[n] = Amp * tan(Phase + (x0 + (Delta * n * Freq))); }
    return(R);
}

// Cotangente (phase in radians):
std::vector<double> CotangentWaveVec(unsigned int Size, double x0, double x1, double Amp, double Freq, double Phase)
{
    std::vector<double> R(Size);
    if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size;
    for (unsigned int n = 0; n < Size; ++n) { R[n] = Amp * cot(Phase + (x0 + (Delta * n * Freq))); }
    return(R);
}
std::vector<float> CotangentWaveVecF(unsigned int Size, float x0, float x1, float Amp, float Freq, float Phase)
{
    std::vector<float> R(Size);
    if (x0 > x1) { float t = x0; x0 = x1; x1 = t; } float Delta = (x1 - x0) / Size;
    for (unsigned int n = 0; n < Size; ++n) { R[n] = Amp * cot(Phase + (x0 + (Delta * n * Freq))); }
    return(R);
}

// SquareWave (phase in radians):
std::vector<double> SquareWaveVec(unsigned int Size, double x0, double x1, double Amp, double Freq, double Phase)
{
    std::vector<double> R(Size);
    if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size;
    for (unsigned int n = 0; n < Size; ++n) { R[n] = Amp * rect(Phase + (x0 + (Delta * n * Freq))); }
    return(R);
}
std::vector<float> SquareWaveVecF(unsigned int Size, float x0, float x1, float Amp, float Freq, float Phase)
{
    std::vector<float> R(Size);
    if (x0 > x1) { float t = x0; x0 = x1; x1 = t; } float Delta = (x1 - x0) / Size;
    for (unsigned int n = 0; n < Size; ++n) { R[n] = Amp * rect(Phase + (x0 + (Delta * n * Freq))); }
    return(R);
}

// SawWave (phase in radians):
std::vector<double> SawWaveVec(unsigned int Size, double x0, double x1, double Amp, double Freq, double Phase)
{
    std::vector<double> R(Size);
    if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size;
    for (unsigned int n = 0; n < Size; ++n) { R[n] = Amp * saw(Phase + (x0 + (Delta * n * Freq))); }
    return(R);
}
std::vector<float> SawWaveVecF(unsigned int Size, float x0, float x1, float Amp, float Freq, float Phase)
{
    std::vector<float> R(Size);
    if (x0 > x1) { float t = x0; x0 = x1; x1 = t; } float Delta = (x1 - x0) / Size;
    for (unsigned int n = 0; n < Size; ++n) { R[n] = Amp * saw(Phase + (x0 + (Delta * n * Freq))); }
    return(R);
}

// SawWave (phase in radians):
std::vector<double> TriWaveVec(unsigned int Size, double x0, double x1, double Amp, double Freq, double Phase)
{
    std::vector<double> R(Size);
    if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size;
    for (unsigned int n = 0; n < Size; ++n) { R[n] = Amp * tri(Phase + (x0 + (Delta * n) * Freq)); }
    return(R);
}
std::vector<float> TriWaveVecF(unsigned int Size, float x0, float x1, float Amp, float Freq, float Phase)
{
    std::vector<float> R(Size);
    if (x0 > x1) { float t = x0; x0 = x1; x1 = t; } float Delta = (x1 - x0) / Size;
    for (unsigned int n = 0; n < Size; ++n) { R[n] = Amp * tri(Phase + (x0 + (Delta * n) * Freq)); }
    return(R);
}

// Miniform vector (phase in radians):
std::vector<double> MiniFormVec(unsigned int Size, double x0, double x1, double Amp, double Freq, double Phase)
{
    std::vector<double> R(Size);
    if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size;
    for (unsigned int n = 0; n < Size; ++n) { R[n] = Amp * MiniForm(Phase + x0 + (Delta * n), Freq); }
    return(R);
}
std::vector<float> MiniFormVecF(unsigned int Size, float x0, float x1, float Amp, float Freq, float Phase)
{
    std::vector<float> R(Size);
    if (x0 > x1) { float t = x0; x0 = x1; x1 = t; } float Delta = (x1 - x0) / Size;
    for (unsigned int n = 0; n < Size; ++n) { R[n] = Amp * MiniForm(Phase + x0 + (Delta * n), Freq); }
    return(R);
}

// Linha:
std::vector<double> LineVec(unsigned int Size, double x0, double x1, double Sum, double Mult)
{
    std::vector<double> R(Size);
    if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size;
    for (unsigned int n = 0; n < Size; ++n) { double x = x0 + (Delta * n); R[n] = Sum + x * Mult; }
    return(R);
}
std::vector<float> LineVecF(unsigned int Size, float x0, float x1, float Sum, float Mult)
{
    std::vector<float> R(Size);
    if (x0 > x1) { float t = x0; x0 = x1; x1 = t; } float Delta = (x1 - x0) / Size;
    for (unsigned int n = 0; n < Size; ++n) { float x = x0 + (Delta * n); R[n] = Sum + x * Mult; }
    return(R);
}
std::vector<double> LineVecDown(unsigned int Size, double x0, double x1, double Sum, double Mult)
{
    std::vector<double> R(Size);
    if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size;
    for (unsigned int n = 0; n < Size; ++n) { double x = x0 + (Delta * n); R[n] = 1 - (Sum + x * Mult); }
    return(R);
}
std::vector<float> LineVecDownF(unsigned int Size, float x0, float x1, float Sum, float Mult)
{
    std::vector<float> R(Size);
    if (x0 > x1) { float t = x0; x0 = x1; x1 = t; } float Delta = (x1 - x0) / Size;
    for (unsigned int n = 0; n < Size; ++n) { float x = x0 + (Delta * n); R[n] = 1 - (Sum + x * Mult); }
    return(R);
}

// Linha curva por exponente | 'x^Pow / Div^Pow':
std::vector<double> ExpCurveVec(unsigned int Size, double x0, double x1, double Pow, double Div)
{
    std::vector<double> R(Size);
    if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size;
    for (unsigned int n = 0; n < Size; ++n) { double x = x0 + (Delta * n); R[n] = pow(x, Pow) / pow(Div, Pow); }
    return(R);
}
std::vector<float> ExpCurveVecF(unsigned int Size, float x0, float x1, float Pow, float Div)
{
    std::vector<float> R(Size);
    if (x0 > x1) { float t = x0; x0 = x1; x1 = t; } float Delta = (x1 - x0) / Size;
    for (unsigned int n = 0; n < Size; ++n) { float x = x0 + (Delta * n); R[n] = pow(x, Pow) / pow(Div, Pow); }
    return(R);
}

// Vetor Exponencial 'a^n'':
std::vector<double> ExponentVec(unsigned int Size, double x0, double x1, double a) { std::vector<double> V(Size); for (unsigned int n = 0; n < Size; ++n) { V[n] = pow(a, n); } return(V); }
std::vector<float> ExponentVecF(unsigned int Size, float x0, float x1, float a) { std::vector<float> V(Size); for (unsigned int n = 0; n < Size; ++n) { V[n] = pow(a, n); } return(V); }

// Vetor Exponencial 'B * (r^n)':
std::vector<double> ExponentVec(unsigned int Size, double x0, double x1, double B, double r) { std::vector<double> V; for (unsigned int n = 0; n < Size; ++n) { V[n] = B * pow(r, n); } return(V); }
std::vector<float> ExponentVecF(unsigned int Size, float x0, float x1, float B, float r) { std::vector<float> V; for (unsigned int n = 0; n < Size; ++n) { V[n] = B * pow(r, n); } return(V); }

// ### TIME BASED:

// Seno com mudança de frequencia por tempo:
std::vector<double> SineWaveVecTimeFreq(unsigned int Size, double x0, double x1, double TimeRatio, double Gain, double Freq, double Phase)
{
    std::vector<double> R(Size); if (x0 > x1) { double t = x0; x0 = x1; x1 = t; }
    double Delta = (x1 - x0) / Size;
    for (unsigned int n = 0; n < Size; ++n) { R[n] = Gain * sin(Phase + x0 + Freq * pow(TimeRatio, n) * Delta * n); } return(R);
}
std::vector<float> SineWaveVecTimeFreqF(unsigned int Size, float x0, float x1, float TimeRatio, float Gain, float Freq, float Phase)
{
    std::vector<float> R(Size); if (x0 > x1) { float t = x0; x0 = x1; x1 = t; }
    float Delta = (x1 - x0) / Size;
    for (unsigned int n = 0; n < Size; ++n) { R[n] = Gain * sin(Phase + x0 + Freq * pow(TimeRatio, n) * Delta * n); } return(R);
}
// Seno com mudança de fase por tempo:
std::vector<double> SineWaveVecTimePhase(unsigned int Size, double x0, double x1, double TimeRatio, double Gain, double Freq, double Phase)
{
    std::vector<double> R(Size); if (x0 > x1) { double t = x0; x0 = x1; x1 = t; }
    double Delta = (x1 - x0) / Size;
    for (unsigned int n = 0; n < Size; ++n) { R[n] = Gain * sin((pow(TimeRatio, n) * Phase) + (x0 + (Delta * n * Freq))); } return(R);
}
std::vector<float> SineWaveVecTimePhaseF(unsigned int Size, float x0, float x1, float TimeRatio, float Gain, float Freq, float Phase)
{
    std::vector<float> R(Size); if (x0 > x1) { float t = x0; x0 = x1; x1 = t; }
    float Delta = (x1 - x0) / Size;
    for (unsigned int n = 0; n < Size; ++n) { R[n] = Gain * sin((pow(TimeRatio, n) * Phase) + (x0 + (Delta * n * Freq))); } return(R);
}
// Seno com mudança de ganho por tempo:
std::vector<double> SineWaveVecTimeGain(unsigned int Size, double x0, double x1, double TimeRatio, double Gain, double Freq, double Phase)
{
    std::vector<double> R(Size); if (x0 > x1) { double t = x0; x0 = x1; x1 = t; }
    double Delta = (x1 - x0) / Size;
    for (unsigned int n = 0; n < Size; ++n) { R[n] = (pow(TimeRatio, n) * Gain) * sin(Phase + x0 + (Delta * n * Freq)); } return(R);
}
std::vector<float> SineWaveVecTimeGainF(unsigned int Size, float x0, float x1, float TimeRatio, float Gain, float Freq, float Phase)
{
    std::vector<float> R(Size); if (x0 > x1) { float t = x0; x0 = x1; x1 = t; }
    float Delta = (x1 - x0) / Size;
    for (unsigned int n = 0; n < Size; ++n) { R[n] = (pow(TimeRatio, n) * Gain) * sin(Phase + x0 + (Delta * n * Freq)); } return(R);
}
// Seno com mudança de frequencia por modulação (FM):
std::vector<double> SineWaveVecFM(unsigned int Size, double x0, double x1, double Gain, double Freq, double FreqFM, double Phase)
{
    std::vector<double> R(Size); if (x0 > x1) { double t = x0; x0 = x1; x1 = t; }
    double Delta = (x1 - x0) / Size;
    for (unsigned int n = 0; n < Size; ++n)
    {
        double x = Phase + (x0 + Freq * Delta * n);
        double xm = Phase + (x0 + FreqFM * Delta * n);
        R[n] = Gain * sin(sin(x) * FreqFM);
    }
    return(R);
}
std::vector<float> SineWaveVecFMF(unsigned int Size, float x0, float x1, float Gain, float Freq, float FreqFM, float Phase)
{
    std::vector<float> R(Size); if (x0 > x1) { float t = x0; x0 = x1; x1 = t; }
    float Delta = (x1 - x0) / Size;
    for (unsigned int n = 0; n < Size; ++n)
    {
        float x = Phase + (x0 + Freq * Delta * n);
        float xm = Phase + (x0 + FreqFM * Delta * n);
        R[n] = Gain * sin(sin(x) * FreqFM);
    }
    return(R);
}
// ### NOISE:

// Noise ((-1 to +1) * Gain):
std::vector<double> Noise(unsigned int Size, double Gain)
{
    std::vector<double> N; for (unsigned int n = 0; n < Size; ++n) { int Random = rand() % 20001; double RealVal = (Random - 10000) / 10000.0; N.push_back(Gain * RealVal); } return(N);
}
// Noise (Sum + Gain * (-1 to +1)):
std::vector<double> Noise(unsigned int Size, double Gain, double Sum)
{
    std::vector<double> N; for (unsigned int n = 0; n < Size; ++n) { int Random = rand() % 20001; double RealVal = (Random - 10000) / 10000.0; N.push_back(Sum + Gain * RealVal); } return(N);
}
// Noise ((-1 to +1) * Gain):
std::vector<double> NoiseAbs(unsigned int Size, double Gain)
{
    std::vector<double> N; for (unsigned int n = 0; n < Size; ++n) { int Random = rand() % 10001; double RealVal = Random / 10000.0; N.push_back(Gain * RealVal); } return(N);
}
// Noise (Sum + Gain * (-1 to +1)):
std::vector<double> NoiseAbs(unsigned int Size, double Gain, double Sum)
{
    std::vector<double> N; for (unsigned int n = 0; n < Size; ++n) { int Random = rand() % 10001; double RealVal = Random / 10000.0; N.push_back(Sum + Gain * RealVal); } return(N);
}

// ADD NOISE TO VECTOR:
void AddNoise(std::vector<double>& V, double NoiseGain)
{
    double Amp = MaxVec(V);
    for (unsigned int n = 0; n < V.size(); ++n)
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

// ATTACK AND DECAY, TAKING IN ACCOUNT THE NUMBER OF ITEMS IN A 'vector':
// SO 'A' AND 'D' ARE RATIOS
std::vector<double> AttackDecay(std::vector<double> Input, double A, double D, double Gain)
{
    unsigned int Size = Input.size();
    std::vector<double> R(Size);
    double Sum = A + D, RatioA = A / Sum, RatioD = D / Sum;
    unsigned int SizeA = floor(Size * RatioA), SizeD = Size - SizeA;
    double DeltaA = 1.0 / SizeA, DeltaD = 1.0 / SizeD;
    for (unsigned int n = 0; n < SizeA; ++n) { R[n] = (DeltaA * n) * Input[n] * Gain; }
    for (unsigned int n = SizeA; n < Size; ++n) { R[n] = (1 - (DeltaD * (n - SizeA))) * Input[n] * Gain; }
    return(R);
}
std::vector<float> AttackDecayF(std::vector<float> Input, float A, float D, float Gain)
{
    unsigned int Size = Input.size();
    std::vector<float> R(Size);
    float Sum = A + D, RatioA = A / Sum, RatioD = D / Sum;
    unsigned int SizeA = floor(Size * RatioA), SizeD = Size - SizeA;
    float DeltaA = 1.0 / SizeA, DeltaD = 1.0 / SizeD;
    for (unsigned int n = 0; n < SizeA; ++n) { R[n] = (DeltaA * n) * Input[n] * Gain; }
    for (unsigned int n = SizeA; n < Size; ++n) { R[n] = (1 - (DeltaD * (n - SizeA))) * Input[n] * Gain; }
    return(R);
}
// #######
// ATTACKS:
std::vector<double> AttackVector(std::vector<double> Input, double Gain)
{
    unsigned int Size = Input.size(); std::vector<double> R(Size);
    for (unsigned int n = 0; n < Size; ++n) { R[n] = (n / (double)Size) * Input[n] * Gain; }
    return(R);
}
std::vector<double> AttackVector(std::vector<double> Input, double Gain, unsigned int n0, unsigned int n1)
{
    if (n0 < 0) { n0 = 0; } if (n1 < 1) { n1 = 1; } if (n0 >= n1) { n1 = n0 + 1; }
    unsigned int Size = Input.size(); std::vector<double> R(Size);    
    for (unsigned int n = n0; n < n1; ++n) { R[n % Size] = (n / (double)Size) * Input[n % Size] * Gain; }
    return(R);
}
std::vector<float> AttackVectorF(std::vector<float> Input, float Gain)
{
    unsigned int Size = Input.size(); std::vector<float> R(Size);
    for (unsigned int n = 0; n < Size; ++n) { R[n] = (n / (float)Size) * Input[n] * Gain; }
    return(R);
}
std::vector<float> AttackVectorF(std::vector<float> Input, float Gain, unsigned int n0, unsigned int n1)
{
    if (n0 < 0) { n0 = 0; } if (n1 < 1) { n1 = 1; } if (n0 >= n1) { n1 = n0 + 1; }
    unsigned int Size = Input.size(); std::vector<float> R(Size);
    for (unsigned int n = n0; n < n1; ++n) { R[n % Size] = (n / (float)Size) * Input[n % Size] * Gain; }
    return(R);
}
// (pow(n, Pow) / pow(Size, Pow)) * Input[n] * Gain:
std::vector<double> AttackExpVector(std::vector<double> Input, double Pow, double Gain)
{

    unsigned int Size = Input.size(); std::vector<double> R(Size);
    for (unsigned int n = 0; n < Size; ++n) { R[n] = ((double)pow(n, Pow) / pow(Size, Pow)) * Input[n] * Gain; }
    return(R);
}
std::vector<double> AttackExpVector(std::vector<double> Input, double Pow, double Gain, unsigned int n0, unsigned int n1)
{
    if (n0 < 0) { n0 = 0; } if (n1 < 1) { n1 = 1; } if (n0 >= n1) { n1 = n0 + 1; }
    unsigned int Size = Input.size(); std::vector<double> R(Size);
    for (unsigned int n = n0; n < n1; ++n) { R[n % Size] = ((double)pow(n, Pow) / pow(Size, Pow)) * Input[n % Size] * Gain; }
    return(R);
}
std::vector<float> AttackExpVectorF(std::vector<float> Input, float Pow, float Gain)
{
    unsigned int Size = Input.size(); std::vector<float> R(Size);
    for (unsigned int n = 0; n < Size; ++n) { R[n] = ((float)pow(n, Pow) / pow(Size, Pow)) * Input[n] * Gain; }
    return(R);
}
std::vector<float> AttackExpVectorF(std::vector<float> Input, float Pow, float Gain, unsigned int n0, unsigned int n1)
{
    if (n0 < 0) { n0 = 0; } if (n1 < 1) { n1 = 1; } if (n0 >= n1) { n1 = n0 + 1; }
    unsigned int Size = Input.size(); std::vector<float> R(Size);
    for (unsigned int n = n0; n < n1; ++n) { R[n % Size] = ((float)pow(n, Pow) / pow(Size, Pow)) * Input[n % Size] * Gain; }
    return(R);
}
// #######
// DECAYS:
std::vector<double> DecayVector(std::vector<double> Input, double Gain)
{
    unsigned int Size = Input.size(); std::vector<double> R(Size);
    for (unsigned int n = 0; n < Size; ++n) { R[n] = ((double)(Size - n) / Size) * Input[n] * Gain; }
    return(R);
}
std::vector<double> DecayVector(std::vector<double> Input, double Gain, unsigned int n0, unsigned int n1)
{
    if (n0 < 0) { n0 = 0; } if (n1 < 1) { n1 = 1; } if (n0 >= n1) { n1 = n0 + 1; }
    unsigned int Size = Input.size(); std::vector<double> R(Size);
    for (unsigned int n = n0; n < n1; ++n) { R[n % Size] = ((double)(Size - n) / Size) * Input[n % Size] * Gain; }
    return(R);
}
std::vector<float> DecayVectorF(std::vector<float> Input, float Gain)
{
    unsigned int Size = Input.size(); std::vector<float> R(Size);
    for (unsigned int n = 0; n < Size; ++n) { R[n] = ((float)(Size - n) / Size) * Input[n] * Gain; }
    return(R);
}
std::vector<float> DecayVectorF(std::vector<float> Input, float Gain, unsigned int n0, unsigned int n1)
{
    if (n0 < 0) { n0 = 0; } if (n1 < 1) { n1 = 1; } if (n0 >= n1) { n1 = n0 + 1; }
    unsigned int Size = Input.size(); std::vector<float> R(Size);
    for (unsigned int n = n0; n < n1; ++n) { R[n % Size] = ((float)(Size - n) / Size) * Input[n % Size] * Gain; }
    return(R);
}
//  (pow(Size - n, Pow) / pow(Size, Pow)) * Input[n] * Gain:
std::vector<double> DecayExpVector(std::vector<double> Input, double Pow, double Gain)
{
    unsigned int Size = Input.size(); std::vector<double> R(Size);
    for (unsigned int n = 0; n < Size; ++n) { R[n] = ((double)pow(Size - n, Pow) / pow(Size, Pow)) * Input[n] * Gain; }
    return(R);
}
std::vector<double> DecayExpVector(std::vector<double> Input, double Pow, double Gain, unsigned int n0, unsigned int n1)
{
    if (n0 < 0) { n0 = 0; } if (n1 < 1) { n1 = 1; } if (n0 >= n1) { n1 = n0 + 1; }
    unsigned int Size = Input.size(); std::vector<double> R(Size);
    for (unsigned int n = n0; n < n1; ++n) { R[n % Size] = ((double)pow(Size - n, Pow) / pow(Size, Pow)) * Input[n % Size] * Gain; }
    return(R);
}
std::vector<float> DecayExpVectorF(std::vector<float> Input, float Pow, float Gain)
{
    unsigned int Size = Input.size(); std::vector<float> R(Size);
    for (unsigned int n = 0; n < Size; ++n) { R[n] = ((float)pow(Size - n, Pow) / pow(Size, Pow)) * Input[n] * Gain; }
    return(R);
}
std::vector<float> DecayExpVectorF(std::vector<float> Input, float Pow, float Gain, unsigned int n0, unsigned int n1)
{
    if (n0 < 0) { n0 = 0; } if (n1 < 1) { n1 = 1; } if (n0 >= n1) { n1 = n0 + 1; }
    unsigned int Size = Input.size(); std::vector<float> R(Size);
    for (unsigned int n = n0; n < n1; ++n) { R[n % Size] = ((float)pow(Size - n, Pow) / pow(Size, Pow)) * Input[n % Size] * Gain; }
    return(R);
}
// #######
// CHANGE INPUT VECTOR BY A GRADUATION FROM L1 TO L2, SIMILAR TO AN ATTACK, BUT WITH BOTH SIDES:
std::vector<double> LineEnvelop(std::vector<double> Input, double L1, double L2, double Gain)
{
    unsigned int Size = Input.size(); std::vector<double> R(Size);
    //if (L1 > L2) { float t = L1; L1 = L2; L2 = t; }
    if (L1 > 1) { L1 = 1; } if (L1 < 0) { L1 = 0; } if (L2 > 1) { L2 = 1; } if (L2 < 0) { L2 = 0; }
    double Delta = (L2 - L1) / Size;
    for (unsigned int n = 0; n < Size; ++n) { R[n] = (L1 + Delta * n) * Input[n] * Gain; }
    return(R);
}
std::vector<double> LineEnvelop(std::vector<double> Input, double L1, double L2, double Gain, unsigned int n0, unsigned int n1)
{
    if (n0 < 0) { n0 = 0; } if (n1 < 1) { n1 = 1; } if (n0 >= n1) { n1 = n0 + 1; }
    unsigned int Size = Input.size(); std::vector<double> R(Size);
    if (L1 > 1) { L1 = 1; } if (L1 < 0) { L1 = 0; } if (L2 > 1) { L2 = 1; } if (L2 < 0) { L2 = 0; }
    double Delta = (L2 - L1) / (n1 - n0);
    for (unsigned int n = n0; n < n1; ++n) { R[n % Size] = (L1 + Delta * n) * Input[n % Size] * Gain; }
    return(R);
}
std::vector<float> LineEnvelopF(std::vector<float> Input, float L1, float L2, float Gain)
{
    unsigned int Size = Input.size(); std::vector<float> R(Size);
    if (L1 > 1) { L1 = 1; } if (L1 < 0) { L1 = 0; } if (L2 > 1) { L2 = 1; } if (L2 < 0) { L2 = 0; }
    float Delta = (L2 - L1) / Size;
    for (unsigned int n = 0; n < Size; ++n) { R[n] = (L1 + Delta * n) * Input[n] * Gain; }
    return(R);
}
std::vector<float> LineEnvelopF(std::vector<float> Input, float L1, float L2, float Gain, unsigned int n0, unsigned int n1)
{
    if (n0 < 0) { n0 = 0; } if (n1 < 1) { n1 = 1; } if (n0 >= n1) { n1 = n0 + 1; }
    unsigned int Size = Input.size(); std::vector<float> R(Size);
    if (L1 > 1) { L1 = 1; } if (L1 < 0) { L1 = 0; } if (L2 > 1) { L2 = 1; } if (L2 < 0) { L2 = 0; }
    float Delta = (L2 - L1) / (n1 - n0);
    for (unsigned int n = n0; n < n1; ++n) { R[n % Size] = (L1 + Delta * n) * Input[n % Size] * Gain; }
    return(R);
}

// Change Input Vector by a exponential graduation from L1 to L2, similar to an Attack, but with both sides:
/*std::vector<double> LineExpEnvelop(std::vector<double> Input, double L1, double L2, double Pow, double Gain)
{
    unsigned int Size = Input.size();
    std::vector<double> R(Size);
    if (L1 > 1) { L1 = 1; } if (L1 < 0) { L1 = 0; } if (L2 > 1) { L2 = 1; } if (L2 < 0) { L2 = 0; }
    //double BigL = L2; if (L1 > L2) { BigL = L1; } double SmallL = L1; if (L1 > L2) { SmallL = L2; }
    //double DeltaL = BigL - SmallL, Delta = DeltaL / Size;
    double Delta = L2 - L1;
    for (unsigned int n = 0; n < Size; ++n) { double x = L1 + pow(Delta * n, Pow) / pow(Size, Pow); R[n] = x * Input[n] * Gain; }
    return(R);
}*/
// #######
// MODULATE VECTOR WITH ANOTHER VECTOR.
// Last index will be from input:
std::vector<double> VectorEnvelop(std::vector<double> Input, std::vector<double> Modulator, double Gain)
{
    std::vector<double> V;
    for (unsigned int n = 0; n < Input.size(); ++n)
    {
        if (n < Modulator.size()) { V.push_back(Input[n] * Modulator[n] * Gain); }
        else { V.push_back(Input[n] * Gain); }
    }
    return(V);
}
std::vector<float> VectorEnvelopF(std::vector<float> Input, std::vector<float> Modulator, float Gain)
{
    std::vector<float> V;
    for (unsigned int n = 0; n < Input.size(); ++n)
    {
        if (n < Modulator.size()) { V.push_back(Input[n] * Modulator[n] * Gain); }
        else { V.push_back(Input[n] * Gain); }
    }
    return(V);
}
// #######
// std::vector<double> ADSR

// #######
// FILL ENVELOPES:
// std::vector<double> ADSR
std::vector<double> EnvAtkDec(unsigned int Size, double A, double D, double Gain)
{
    std::vector<double> R(Size);
    double Sum = A + D, RatioA = A / Sum, RatioD = D / Sum;
    unsigned int SizeA = floor(Size * RatioA), SizeD = Size - SizeA;
    double DeltaA = 1.0 / SizeA, DeltaD = 1.0 / SizeD;
    for (unsigned int n = 0; n < SizeA; ++n) { R[n] = (DeltaA * n) * Gain; }
    for (unsigned int n = SizeA; n < Size; ++n) { R[n] = (1 - (DeltaD * (n - SizeA))) * Gain; }
    return(R);
}
std::vector<float> EnvAtkDecF(unsigned int Size, float A, float D, float Gain)
{
    std::vector<float> R(Size);
    float Sum = A + D, RatioA = A / Sum, RatioD = D / Sum;
    unsigned int SizeA = floor(Size * RatioA), SizeD = Size - SizeA;
    float DeltaA = 1.0 / SizeA, DeltaD = 1.0 / SizeD;
    for (unsigned int n = 0; n < SizeA; ++n) { R[n] = (DeltaA * n) * Gain; }
    for (unsigned int n = SizeA; n < Size; ++n) { R[n] = (1 - (DeltaD * (n - SizeA))) * Gain; }
    return(R);
}
std::vector<double> EnvLine(unsigned int Size, double L1, double L2, double Gain)
{
    std::vector<double> R(Size);
    if (L1 > 1) { L1 = 1; } if (L1 < 0) { L1 = 0; } if (L2 > 1) { L2 = 1; } if (L2 < 0) { L2 = 0; }
    double Delta = (L2 - L1) / Size;
    for (unsigned int n = 0; n < Size; ++n) { R[n] = (L1 + Delta * n) * Gain; }
    return(R);
}
std::vector<double> EnvLine(unsigned int Size, double L1, double L2, double Gain, unsigned int n0, unsigned int n1)
{
    if (n0 < 0) { n0 = 0; } if (n1 < 1) { n1 = 1; } if (n0 >= n1) { n1 = n0 + 1; }
    std::vector<double> R(Size);
    if (L1 > 1) { L1 = 1; } if (L1 < 0) { L1 = 0; } if (L2 > 1) { L2 = 1; } if (L2 < 0) { L2 = 0; }
    double Delta = (L2 - L1) / (n1 - n0);
    for (unsigned int n = n0; n < n1; ++n) { R[n % Size] = (L1 + Delta * n) * Gain; }
    return(R);
}
std::vector<float> EnvLineF(unsigned int Size, float L1, float L2, float Gain)
{
    std::vector<float> R(Size);
    if (L1 > 1) { L1 = 1; } if (L1 < 0) { L1 = 0; } if (L2 > 1) { L2 = 1; } if (L2 < 0) { L2 = 0; }
    float Delta = (L2 - L1) / Size;
    for (unsigned int n = 0; n < Size; ++n) { R[n] = (L1 + Delta * n) * Gain; }
    return(R);
}
std::vector<float> EnvLineF(unsigned int Size, float L1, float L2, float Gain, unsigned int n0, unsigned int n1)
{
    if (n0 < 0) { n0 = 0; } if (n1 < 1) { n1 = 1; } if (n0 >= n1) { n1 = n0 + 1; }
    std::vector<float> R(Size);
    if (L1 > 1) { L1 = 1; } if (L1 < 0) { L1 = 0; } if (L2 > 1) { L2 = 1; } if (L2 < 0) { L2 = 0; }
    float Delta = (L2 - L1) / (n1 - n0);
    for (unsigned int n = n0; n < n1; ++n) { R[n % Size] = (L1 + Delta * n) * Gain; }
    return(R);
}

// ####### NORMALIZERS #######

// IF BIGGER THAN Y THEN Y:
std::vector<double> LimitToptoY(std::vector<double> fx, double Y)
{
    for (unsigned int n = 0; n < fx.size(); ++n)
    {
        if (fx[n] > Y) { fx[n] = Y; }
    }
    return(fx);
}

// IF BIGGER THAN Y AND LOWER THAN -Y, THEN Y AND -Y:
std::vector<double> LimittoY(std::vector<double> fx, double Y)
{
    for (unsigned int n = 0; n < fx.size(); ++n)
    {
        if (fx[n] > Y) { fx[n] = Y; } else if (fx[n] < -Y) { fx[n] = -Y; }
    }
    return(fx);
}

// IF BIGGER THAN Y1 AND LOWER THAN Y0, THEN Y1 AND Y0:
std::vector<double> LimittoY1Y0(std::vector<double> fx, double Y1, double Y0)
{
    if (Y0 == Y1) { Y0 += 1.0e-9; } if (Y1 < Y0) { double T = Y1; Y1 = Y0; Y0 = T; }
    for (unsigned int n = 0; n < fx.size(); ++n)
    {
        if (fx[n] > Y1) { fx[n] = Y1; } else if (fx[n] < Y0) { fx[n] = Y0; }
    }
    return(fx);
}

// MAX (TOP OF VECTOR) IS DIVIDED BY MAX:
std::vector<int> NormalizeTopto1(std::vector<int> fx)
{
    double Max = MaxVec(fx); if (Max == 0) { Max = 1.0e-9; }
    for (unsigned int n = 0; n < fx.size(); ++n) { fx[n] /= Max; } return(fx);
}
std::vector<double> NormalizeTopto1(std::vector<double> fx) 
{
    double Max = MaxVec(fx); if (Max == 0) { Max = 1.0e-9; }
    for (unsigned int n = 0; n < fx.size(); ++n) { fx[n] /= Max; } return(fx); 
}

// IF MAX AND MIN IS BIGGER THAN 1 AND LOWER THAN -1, DIVIDE BY THE BIGGER ABSOLUTE:
std::vector<int> Normalize(std::vector<int> fx)
{
    int Max = MaxVecAbs(fx); if (Max == 0) { Max = 1.0e-9; }
    for (unsigned int n = 0; n < fx.size(); ++n) { fx[n] /= Max; } return(fx);
}
std::vector<double> Normalize(std::vector<double> fx)
{
    double Max = MaxVecAbs(fx); if (Max == 0) { Max = 1.0e-9; }
    for (unsigned int n = 0; n < fx.size(); ++n) { fx[n] /= Max; } return(fx);
}

// MOD NORMALIZE, (f(x) + 1) * 0.5:
std::vector<int> NormalizeModTopto1(std::vector<int> fx)
{
    double Max = MaxVec(fx); if (Max == 0) { Max = 1.0e-9; }
    for (unsigned int n = 0; n < fx.size(); ++n) { fx[n] /= Max; fx[n] += 1; fx[n] *= 0.5; } return(fx);
}
std::vector<double> NormalizeModTopto1(std::vector<double> fx)
{
    double Max = MaxVec(fx); if (Max == 0) { Max = 1.0e-9; }
    for (unsigned int n = 0; n < fx.size(); ++n) { fx[n] /= Max; fx[n] += 1; fx[n] *= 0.5; } return(fx);
}
std::vector<int> NormalizeMod(std::vector<int> fx)
{
    int Max = MaxVecAbs(fx); if (Max == 0) { Max = 1.0e-9; }
    for (unsigned int n = 0; n < fx.size(); ++n) { fx[n] /= Max; fx[n] += 1; fx[n] *= 0.5; } return(fx);
}
std::vector<double> NormalizeMod(std::vector<double> fx)
{
    double Max = MaxVecAbs(fx); if (Max == 0) { Max = 1.0e-9; }
    for (unsigned int n = 0; n < fx.size(); ++n) { fx[n] /= Max; fx[n] += 1; fx[n] *= 0.5; } return(fx);
}


// ####################################################################################################################################################################################################
// ####################################################################################################################################################################################################
// ####################################################################################################################################################################################################

// #################################################
// ####### CLASSES #######
// #################################################

// ####### AAA #######
// AAA:

/*
class a
{
    a() {}
    ~a() {}
};
*/

// ################################################# FIM ####################################################################################

#endif // SCPARSE_