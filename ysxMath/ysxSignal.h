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
// !!!!!!!	* ATTENTION: The header 'ysxElectr.h' must include this header.
// !!!!!!!	* HUGE: Soon to fix all the redundancy with templates.
// !!!!!!!	* Use function "ysxVEC_MultVecTerms" or "ysxVEC_SumVecTerms" to modify the signal amplitude.
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
// ####### ELECTRICITY #######
// ############################

double ysxSIG_ElecPower(double V, double Q, double t) { return((V * Q) / t); } // = V * I // Q = Coulombs / t = seconds / I = Amperes / V = Volts
double ysxSIG_ElecPowerRes(double V, double R) { return((V * V) / R); } // = R * I^2 = I * V // Instant power

// TOTAL ENERGY:
double ysxSIG_TotalSigEnrgy(double T, int n, double Omega, double (*f)(double, double))
{
    if (n < 1) { n = 1; } double dt = T / n; double Sum = 0;
    for (int i = 1; i <= n; i++) { Sum += f((-T) + (i - 0.5) * dt, Omega) * dt; }
    return(Sum);
}
// TOTAl ENERGY BASED ON DISCRETE TIME (DEPENDS ON YOUR VECTOR):
double ysxSIG_TotalSigEnrgy(std::vector<double> V) { double Sum = 0; for (int n = 0; n < V.size(); ++n) { Sum += V[n] * V[n]; } return(Sum); }

// AVERAGE POWER (USING MINIFORM):
double ysxSIG_AvrgPower(double T, int n, double Omega, double (*f)(double, double))
{
    if (n < 1) { n = 1; }
    double dt = T / n; double Sum = 0;
    for (int i = 1; i <= n; i++) Sum += f((-T) + (i - 0.5) * dt, Omega) * dt;
    return((1.0 / T) * Sum);
}
// AVERAGE POWER BASED OM DISCRETE TIME (DEPENDS ON YOUR VECTOR):
// Since the formula is based on signal and not c++ vectors, i'm going to change it a little based on the principle that a vector begins at '0'.
// Consequently the new formula is: P = Limit N : inf -> (1 / N + 1) * SUM(x^2[n], 0, N)
// Instead of: P = Lim N : inf -> (1 / 2N + 1) * SUM(x^2[n], -N, N);
double ysxSIG_AvrgPower(std::vector<double> V)
{
    double Sum = 0; int N = V.size();
    for (int n = 0; n < N; ++n) { Sum += V[n] * V[n]; }
    return((1.0 / (N + 1)) * Sum);
}
// BOOK: 'caso de um sinal x[n] com período fundamental N':
double ysxSIG_AvrgPowerFundPeriod(std::vector<double> V)
{
    double Sum = 0; int N = V.size() - 1;
    for (int n = 0; n < N; ++n) { Sum += V[n] * V[n]; }
    return((1.0 / N) * Sum);
}

// CAPACITANCE, PARALLEL AND SERIES:
double ysxSIG_CapacitancePara(std::vector<double> Farad) { double F = 0; for (size_t n = 0; n < Farad.size(); ++n) { F += Farad[n]; } return(F); }
double ysxSIG_CapacitanceSer(std::vector<double> Farad) { double F = 0; for (size_t n = 0; n < Farad.size(); ++n) { F += 1 / Farad[n]; } return(1 / F); }

// TIME CONSTANT:
// Resis * Farad;

// ############################
// ####### SIGNAL VECTORS #######
// ############################

// ####### SIGNAL:
std::vector<double> ysxSIG_SignalVec(uint32_t Size, double Volts) { std::vector<double> s(Size); for (uint32_t n = 0; n < Size; ++n) { s[n] = Volts; } return(s); }
std::vector<double> ysxSIG_SignalVec(uint32_t Size, double Volts, double NoiseGain)
{
    std::vector<double> s(Size);
    for (uint32_t n = 0; n < Size; ++n) { s[n] = Volts - NoiseGain + NoiseGain * (((rand() % 20001) - 10000) / 10000.0); }
    return(s);
}

// Step signal:
//double StepSig(int n) { if (n >= 0) { return(1); } return(0); }

// ####### TRIGONOMETRIC:
// !!! ATTENTION !!!
// EVERYTHING below here that needs more than one type IS GOING to have a template and very likely that it wont work with older codes!
// Sine (phase in radians):
std::vector<double> ysxSIG_SinWaveVec(uint32_t Size, double x0, double x1, double Amp, double Freq, double Phase)
{
    std::vector<double> R(Size);
    if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size;
    for (uint32_t n = 0; n < Size; ++n) { R[n] = Amp * sin(Phase + (x0 + (Delta * n * Freq))); }
    return(R);
}
std::vector<float> ysxSIG_SinWaveVecF(uint32_t Size, float x0, float x1, float Amp, float Freq, float Phase)
{
    std::vector<float> R(Size);
    if (x0 > x1) { float t = x0; x0 = x1; x1 = t; } float Delta = (x1 - x0) / Size;
    for (uint32_t n = 0; n < Size; ++n) { R[n] = Amp * sin(Phase + (x0 + (Delta * n * Freq))); }
    return(R);
}

// Cosine (phase in radians):
std::vector<double> ysxSIG_CosWaveVec(uint32_t Size, double x0, double x1, double Amp, double Freq, double Phase)
{
    std::vector<double> R(Size);
    if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size;
    for (uint32_t n = 0; n < Size; ++n) { R[n] = Amp * cos(Phase + (x0 + (Delta * n * Freq))); }
    return(R);
}
std::vector<float> ysxSIG_CosWaveVecF(uint32_t Size, float x0, float x1, float Amp, float Freq, float Phase)
{
    std::vector<float> R(Size);
    if (x0 > x1) { float t = x0; x0 = x1; x1 = t; } float Delta = (x1 - x0) / Size;
    for (uint32_t n = 0; n < Size; ++n) { R[n] = Amp * cos(Phase + (x0 + (Delta * n * Freq))); }
    return(R);
}

// Tangent (phase in radians):
std::vector<double> ysxSIG_TanWaveVec(uint32_t Size, double x0, double x1, double Amp, double Freq, double Phase)
{
    std::vector<double> R(Size);
    if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size;
    for (uint32_t n = 0; n < Size; ++n) { R[n] = Amp * tan(Phase + (x0 + (Delta * n * Freq))); }
    return(R);
}
std::vector<float> ysxSIG_TanWaveVecF(uint32_t Size, float x0, float x1, float Amp, float Freq, float Phase)
{
    std::vector<float> R(Size);
    if (x0 > x1) { float t = x0; x0 = x1; x1 = t; } float Delta = (x1 - x0) / Size;
    for (uint32_t n = 0; n < Size; ++n) { R[n] = Amp * tan(Phase + (x0 + (Delta * n * Freq))); }
    return(R);
}

// Cotangent (phase in radians):
std::vector<double> ysxSIG_CotWaveVec(uint32_t Size, double x0, double x1, double Amp, double Freq, double Phase)
{
    std::vector<double> R(Size);
    if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size;
    for (uint32_t n = 0; n < Size; ++n) { R[n] = Amp * cot(Phase + (x0 + (Delta * n * Freq))); }
    return(R);
}
std::vector<float> ysxSIG_CotWaveVecF(uint32_t Size, float x0, float x1, float Amp, float Freq, float Phase)
{
    std::vector<float> R(Size);
    if (x0 > x1) { float t = x0; x0 = x1; x1 = t; } float Delta = (x1 - x0) / Size;
    for (uint32_t n = 0; n < Size; ++n) { R[n] = Amp * cot(Phase + (x0 + (Delta * n * Freq))); }
    return(R);
}

// // ####### RECT AND TRI:
// SquareWave (phase in radians):
std::vector<double> ysxSIG_SqrWaveVec(uint32_t Size, double x0, double x1, double Amp, double Freq, double Phase)
{
    std::vector<double> R(Size);
    if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size;
    for (uint32_t n = 0; n < Size; ++n) { R[n] = Amp * rect(Phase + (x0 + (Delta * n * Freq))); }
    return(R);
}
std::vector<float> ysxSIG_SqrWaveVecF(uint32_t Size, float x0, float x1, float Amp, float Freq, float Phase)
{
    std::vector<float> R(Size);
    if (x0 > x1) { float t = x0; x0 = x1; x1 = t; } float Delta = (x1 - x0) / Size;
    for (uint32_t n = 0; n < Size; ++n) { R[n] = Amp * rect(Phase + (x0 + (Delta * n * Freq))); }
    return(R);
}

// SawWave (phase in radians):
std::vector<double> ysxSIG_SawWaveVec(uint32_t Size, double x0, double x1, double Amp, double Freq, double Phase)
{
    std::vector<double> R(Size);
    if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size;
    for (uint32_t n = 0; n < Size; ++n) { R[n] = Amp * saw(Phase + (x0 + (Delta * n * Freq))); }
    return(R);
}
std::vector<float> ysxSIG_SawWaveVecF(uint32_t Size, float x0, float x1, float Amp, float Freq, float Phase)
{
    std::vector<float> R(Size);
    if (x0 > x1) { float t = x0; x0 = x1; x1 = t; } float Delta = (x1 - x0) / Size;
    for (uint32_t n = 0; n < Size; ++n) { R[n] = Amp * saw(Phase + (x0 + (Delta * n * Freq))); }
    return(R);
}

// SawWave (phase in radians):
std::vector<double> ysxSIG_TriWaveVec(uint32_t Size, double x0, double x1, double Amp, double Freq, double Phase)
{
    std::vector<double> R(Size);
    if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size;
    for (uint32_t n = 0; n < Size; ++n) { R[n] = Amp * tri(Phase + (x0 + (Delta * n) * Freq)); }
    return(R);
}
std::vector<float> ysxSIG_TriWaveVecF(uint32_t Size, float x0, float x1, float Amp, float Freq, float Phase)
{
    std::vector<float> R(Size);
    if (x0 > x1) { float t = x0; x0 = x1; x1 = t; } float Delta = (x1 - x0) / Size;
    for (uint32_t n = 0; n < Size; ++n) { R[n] = Amp * tri(Phase + (x0 + (Delta * n) * Freq)); }
    return(R);
}

// ####### FORMULA:

// Miniform vector (phase in radians):
std::vector<double> ysxSIG_FuncVec(uint32_t Size, double x0, double x1, double Amp, double Freq, double Phase, double (*f)(double, double))
{
    std::vector<double> R(Size);
    if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size;
    for (uint32_t n = 0; n < Size; ++n) { R[n] = Amp * f(Phase + x0 + (Delta * n), Freq); }
    return(R);
}
std::vector<float> ysxSIG_FuncVecF(uint32_t Size, float x0, float x1, float Amp, float Freq, float Phase, double (*f)(double, double))
{
    std::vector<float> R(Size);
    if (x0 > x1) { float t = x0; x0 = x1; x1 = t; } float Delta = (x1 - x0) / Size;
    for (uint32_t n = 0; n < Size; ++n) { R[n] = Amp * f(Phase + x0 + (Delta * n), Freq); }
    return(R);
}

// ####### LINES AND CURVES:
std::vector<double> ysxSIG_LineVec(uint32_t Size, double x0, double x1, double Sum, double Mult)
{
    std::vector<double> R(Size);
    if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size;
    for (uint32_t n = 0; n < Size; ++n) { double x = x0 + (Delta * n); R[n] = Sum + x * Mult; }
    return(R);
}
std::vector<float> ysxSIG_LineVecF(uint32_t Size, float x0, float x1, float Sum, float Mult)
{
    std::vector<float> R(Size);
    if (x0 > x1) { float t = x0; x0 = x1; x1 = t; } float Delta = (x1 - x0) / Size;
    for (uint32_t n = 0; n < Size; ++n) { float x = x0 + (Delta * n); R[n] = Sum + x * Mult; }
    return(R);
}
std::vector<double> ysxSIG_LineVecDown(uint32_t Size, double x0, double x1, double Sum, double Mult)
{
    std::vector<double> R(Size);
    if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size;
    for (uint32_t n = 0; n < Size; ++n) { double x = x0 + (Delta * n); R[n] = 1 - (Sum + x * Mult); }
    return(R);
}
std::vector<float> ysxSIG_LineVecDownF(uint32_t Size, float x0, float x1, float Sum, float Mult)
{
    std::vector<float> R(Size);
    if (x0 > x1) { float t = x0; x0 = x1; x1 = t; } float Delta = (x1 - x0) / Size;
    for (uint32_t n = 0; n < Size; ++n) { float x = x0 + (Delta * n); R[n] = 1 - (Sum + x * Mult); }
    return(R);
}

// Curve by power | 'x^Pow / Div^Pow':
std::vector<double> ysxSIG_PowCurveVec(uint32_t Size, double x0, double x1, double Pow, double Div)
{
    std::vector<double> R(Size);
    if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size;
    for (uint32_t n = 0; n < Size; ++n) { double x = x0 + (Delta * n); R[n] = pow(x, Pow) / pow(Div, Pow); }
    return(R);
}
std::vector<float> ysxSIG_PowCurveVecF(uint32_t Size, float x0, float x1, float Pow, float Div)
{
    std::vector<float> R(Size);
    if (x0 > x1) { float t = x0; x0 = x1; x1 = t; } float Delta = (x1 - x0) / Size;
    for (uint32_t n = 0; n < Size; ++n) { float x = x0 + (Delta * n); R[n] = pow(x, Pow) / pow(Div, Pow); }
    return(R);
}

// POWER VECTOR 'a^x'':
std::vector<double> ysxSIG_PowofaVec(uint32_t Size, double x0, double x1, double a)
{ 
    if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size;
    std::vector<double> V(Size); for (uint32_t n = 0; n < Size; ++n) { V[n] = pow(a, x0 + (Delta * n)); } return(V);
}
std::vector<float> ysxSIG_PowofaVecF(uint32_t Size, float x0, float x1, float a)
{
    if (x0 > x1) { float t = x0; x0 = x1; x1 = t; } float Delta = (x1 - x0) / Size;
    std::vector<float> V(Size); for (uint32_t n = 0; n < Size; ++n) { V[n] = pow(a, x0 + (Delta * n)); } return(V);
}

// POWER VECTOR 'x^a'':
std::vector<double> ysxSIG_PowofxVec(uint32_t Size, double x0, double x1, double a)
{
    if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size;
    std::vector<double> V(Size); for (uint32_t n = 0; n < Size; ++n) { V[n] = pow(x0 + (Delta * n), a); } return(V);
}
std::vector<float> ysxSIG_PowofxVecF(uint32_t Size, float x0, float x1, float a)
{
    if (x0 > x1) { float t = x0; x0 = x1; x1 = t; } float Delta = (x1 - x0) / Size;
    std::vector<float> V(Size); for (uint32_t n = 0; n < Size; ++n) { V[n] = pow(x0 + (Delta * n), a); } return(V);
}

// ####### TIME BASED:

// SINE WAVE THAT CHANGES FREQUENCY BY TIME:
std::vector<double> ysxSIG_SineWaveVecTimeFreq(uint32_t Size, double x0, double x1, double TimeRatio, double Gain, double Freq, double Phase)
{
    std::vector<double> R(Size); if (x0 > x1) { double t = x0; x0 = x1; x1 = t; }
    double Delta = (x1 - x0) / Size;
    for (uint32_t n = 0; n < Size; ++n) { R[n] = Gain * sin(Phase + x0 + Freq * pow(TimeRatio, n) * Delta * n); } return(R);
}
std::vector<float> ysxSIG_SineWaveVecTimeFreqF(uint32_t Size, float x0, float x1, float TimeRatio, float Gain, float Freq, float Phase)
{
    std::vector<float> R(Size); if (x0 > x1) { float t = x0; x0 = x1; x1 = t; }
    float Delta = (x1 - x0) / Size;
    for (uint32_t n = 0; n < Size; ++n) { R[n] = Gain * sin(Phase + x0 + Freq * pow(TimeRatio, n) * Delta * n); } return(R);
}
// SINE WAVE THAT CHANGES PHASE BY TIME:
std::vector<double> ysxSIG_SineWaveVecTimePhase(uint32_t Size, double x0, double x1, double TimeRatio, double Gain, double Freq, double Phase)
{
    std::vector<double> R(Size); if (x0 > x1) { double t = x0; x0 = x1; x1 = t; }
    double Delta = (x1 - x0) / Size;
    for (uint32_t n = 0; n < Size; ++n) { R[n] = Gain * sin((pow(TimeRatio, n) * Phase) + (x0 + (Delta * n * Freq))); } return(R);
}
std::vector<float> ysxSIG_SineWaveVecTimePhaseF(uint32_t Size, float x0, float x1, float TimeRatio, float Gain, float Freq, float Phase)
{
    std::vector<float> R(Size); if (x0 > x1) { float t = x0; x0 = x1; x1 = t; }
    float Delta = (x1 - x0) / Size;
    for (uint32_t n = 0; n < Size; ++n) { R[n] = Gain * sin((pow(TimeRatio, n) * Phase) + (x0 + (Delta * n * Freq))); } return(R);
}
// SINE WAVE THAT CHANGES GAIN BY TIME:
std::vector<double> ysxSIG_SineWaveVecTimeGain(uint32_t Size, double x0, double x1, double TimeRatio, double Gain, double Freq, double Phase)
{
    std::vector<double> R(Size); if (x0 > x1) { double t = x0; x0 = x1; x1 = t; }
    double Delta = (x1 - x0) / Size;
    for (uint32_t n = 0; n < Size; ++n) { R[n] = (pow(TimeRatio, n) * Gain) * sin(Phase + x0 + (Delta * n * Freq)); } return(R);
}
std::vector<float> ysxSIG_SineWaveVecTimeGainF(uint32_t Size, float x0, float x1, float TimeRatio, float Gain, float Freq, float Phase)
{
    std::vector<float> R(Size); if (x0 > x1) { float t = x0; x0 = x1; x1 = t; }
    float Delta = (x1 - x0) / Size;
    for (uint32_t n = 0; n < Size; ++n) { R[n] = (pow(TimeRatio, n) * Gain) * sin(Phase + x0 + (Delta * n * Freq)); } return(R);
}
// GENERAL FM FORMULA (SINE WAVE):
std::vector<double> ysxSIG_SineWaveVecFM(uint32_t Size, double x0, double x1, double Gain, double Freq, double FreqFM, double FMAmp, double Phase)
{
    std::vector<double> R(Size);
    if (x0 > x1) { double t = x0; x0 = x1; x1 = t; }
    double Delta = (x1 - x0) / Size;
    double x;
    for (uint32_t n = 0; n < Size; ++n)
    {
        x = x0 + Delta * n;
        R[n] = Gain * sin(sin(x * FreqFM + Phase) * FMAmp + Freq * x + Phase);
    }
    return(R);
}
std::vector<float> ysxSIG_SineWaveVecFMFlt(uint32_t Size, float x0, float x1, float Gain, float Freq, float FreqFM, float FMAmp, float Phase)
{
    std::vector<float> R(Size);
    if (x0 > x1) { float t = x0; x0 = x1; x1 = t; }
    float Delta = (x1 - x0) / Size;
    float x;
    for (uint32_t n = 0; n < Size; ++n)
    {
        x = x0 + Delta * n;
        R[n] = Gain * sin(sin(x * FreqFM + Phase) * FMAmp + Freq * x + Phase);
    }
    return(R);
}

// ####### NOISES:

// Noise ((-1 to +1) * Gain):
std::vector<double> ysxSIG_Noise(uint32_t Size, double Gain)
{
    std::vector<double> N(Size); int Random;
    for (uint32_t n = 0; n < Size; ++n)
    {
        Random = rand() % 20001;
        N[n] = Gain * (Random - 10000.0) / 10000.0;
    }
    return(N);
}
// Noise (Sum + Gain * (-1 to +1)):
std::vector<double> ysxSIG_Noise(uint32_t Size, double Gain, double Sum)
{
    std::vector<double> N(Size); int Random;
    for (uint32_t n = 0; n < Size; ++n)
    {
        Random = rand() % 20001;
        N[n] = Sum + Gain * (Random - 10000) / 10000.0;
    }
    return(N);
}
// Noise ((0 to +1) * Gain):
std::vector<double> ysxSIG_NoiseAbs(uint32_t Size, double Gain)
{
    std::vector<double> N(Size); int Random;
    for (uint32_t n = 0; n < Size; ++n)
    {
        Random = rand() % 10001;
        N[n] = Gain * Random / 10000.0;
    }
    return(N);
}
// Noise (Sum + Gain * (-1 to +1)):
std::vector<double> ysxSIG_NoiseAbs(uint32_t Size, double Gain, double Sum)
{
    std::vector<double> N(Size); int Random;
    for (uint32_t n = 0; n < Size; ++n)
    {
        Random = rand() % 10001;
        N[n] = Sum + Gain * Random / 10000.0;
    }
    return(N);
}

// ADD NOISE TO VECTOR:
void ysxSIG_AddNoise(std::vector<double>& V, double NoiseGain)
{
    double Amp = ysxVEC_MaxVec(V); double Rand;
    for (uint32_t n = 0; n < V.size(); ++n)
    {
        Rand = ((rand() % 20001) - 10000) / 10000.0;
        V[n] = V[n] - NoiseGain + Rand * NoiseGain;
    }
}

// NOISE SAMPLE:
double ysxSIG_NoiseSample(double Volts, double NoiseGain) { return(Volts - NoiseGain + NoiseGain * (((rand() % 20001) - 10000) / 10000.0)); }

// ####### PHYSICS:
// HARMONIC OSCILLATOR:
std::vector<double> ysxSIG_HarmOsc(uint32_t Size, double x0, double x1, double Amp, double Freq, double Phase)
{
    std::vector<double> R(Size);
    if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size;
    for (uint32_t n = 0; n < Size; ++n) { R[n] = Amp * cos(Phase + (x0 + (Delta * n * Freq))); }
    return(R);
}
std::vector<float> ysxSIG_HarmOscF(uint32_t Size, float x0, float x1, float Amp, float Freq, float Phase)
{
    std::vector<float> R(Size);
    if (x0 > x1) { float t = x0; x0 = x1; x1 = t; } float Delta = (x1 - x0) / Size;
    for (uint32_t n = 0; n < Size; ++n) { R[n] = Amp * cos(Phase + (x0 + (Delta * n * Freq))); }
    return(R);
}

// ####################################################################################################################################################################################################
// ####################################################################################################################################################################################################
// ####################################################################################################################################################################################################

// ############################
// ####### ENVELOPES
// ############################

// ENVELOPE:
double ysxSIG_Envelope(double Attack, double Decay, double x)
{ if (x < Attack) { return(x / Attack); } else { return(1.0 - ((x - Attack) / Decay)); } } // There is probably an optimal function
float ysxSIG_EnvelopeF(float Attack, float Decay, float x)
{ if (x < Attack) { return(x / Attack); } else { return(1.0 - ((x - Attack) / Decay)); } } // There is probably an optimal function

// ATTACK AND DECAY, TAKING IN ACCOUNT THE NUMBER OF ITEMS IN A 'vector':
// SO 'A' AND 'D' ARE RATIOS
std::vector<double> ysxSIG_AttackDecay(std::vector<double>& Input, double A, double D, double Gain)
{
    uint32_t Size = Input.size();
    std::vector<double> R(Size);
    double Sum = A + D, RatioA = A / Sum, RatioD = D / Sum;
    uint32_t SizeA = floor(Size * RatioA), SizeD = Size - SizeA;
    double DeltaA = 1.0 / SizeA, DeltaD = 1.0 / SizeD;
    for (uint32_t n = 0; n < SizeA; ++n) { R[n] = (DeltaA * n) * Input[n] * Gain; }
    for (uint32_t n = SizeA; n < Size; ++n) { R[n] = (1 - (DeltaD * (n - SizeA))) * Input[n] * Gain; }
    return(R);
}
std::vector<float> ysxSIG_AttackDecayF(std::vector<float>& Input, float A, float D, float Gain)
{
    uint32_t Size = Input.size();
    std::vector<float> R(Size);
    float Sum = A + D, RatioA = A / Sum, RatioD = D / Sum;
    uint32_t SizeA = (uint32_t)floor(Size * RatioA), SizeD = Size - SizeA;
    float DeltaA = 1.0 / SizeA, DeltaD = 1.0 / SizeD;
    for (uint32_t n = 0; n < SizeA; ++n) { R[n] = (DeltaA * n) * Input[n] * Gain; }
    for (uint32_t n = SizeA; n < Size; ++n) { R[n] = (1 - (DeltaD * (n - SizeA))) * Input[n] * Gain; }
    return(R);
}
// #######
// ATTACKS:
std::vector<double> ysxSIG_AttackVector(std::vector<double>& Input, double Gain)
{
    uint32_t Size = Input.size(); std::vector<double> R(Size);
    for (uint32_t n = 0; n < Size; ++n) { R[n] = (n / (double)Size) * Input[n] * Gain; }
    return(R);
}
std::vector<double> ysxSIG_AttackVector(std::vector<double>& Input, double Gain, uint32_t n0, uint32_t n1)
{
    if (n0 > n1) { uint32_t t = n1; n1 = n0, n0 = t; }
    if (n0 < 0) { n0 = 0; } if (n1 < 1) { n1 = 1; } if (n0 = n1) { n1 = n0 + 1; }
    uint32_t N = n1 - n0, Size = Input.size(); std::vector<double> R(Size);
    for (uint32_t n = n0; n < Input.size(); ++n)
    {
        R[n % Size] = n - n0 < N ? (n / (double)N) * Input[n % Size] * Gain : Input[n % Size] * Gain;
    }
    return(R);
}
std::vector<float> ysxSIG_AttackVectorF(std::vector<float>& Input, float Gain)
{
    uint32_t Size = Input.size(); std::vector<float> R(Size);
    for (uint32_t n = 0; n < Size; ++n) { R[n] = (n / (float)Size) * Input[n] * Gain; }
    return(R);
}
std::vector<float> ysxSIG_AttackVectorF(std::vector<float>& Input, float Gain, uint32_t n0, uint32_t n1)
{
    if (n0 > n1) { uint32_t t = n1; n1 = n0, n0 = t; }
    if (n0 < 0) { n0 = 0; } if (n1 < 1) { n1 = 1; } if (n0 = n1) { n1 = n0 + 1; }
    uint32_t N = n1 - n0, Size = Input.size(); std::vector<float> R(Size);
    for (uint32_t n = n0; n < Input.size(); ++n)
    {
        R[n % Size] = n - n0 < N ? (n / (float)N) * Input[n % Size] * Gain : Input[n % Size] * Gain;
    }
    return(R);
}
// (pow(n, Pow) / pow(Size, Pow)) * Input[n] * Gain:
std::vector<double> ysxSIG_AttackExpVector(std::vector<double>& Input, double Pow, double Gain)
{

    uint32_t Size = Input.size(); std::vector<double> R(Size);
    for (uint32_t n = 0; n < Size; ++n) { R[n] = ((double)pow(n, Pow) / pow(Size, Pow)) * Input[n] * Gain; }
    return(R);
}
std::vector<double> ysxSIG_AttackExpVector(std::vector<double>& Input, double Pow, double Gain, uint32_t n0, uint32_t n1)
{
    if (n0 > n1) { uint32_t t = n1; n1 = n0, n0 = t; }
    if (n0 < 0) { n0 = 0; } if (n1 < 1) { n1 = 1; } if (n0 = n1) { n1 = n0 + 1; }
    uint32_t N = n1 - n0, Size = Input.size(); std::vector<double> R(Size);
    for (uint32_t n = n0; n < n1; ++n)
    {
        R[n % Size] = n - n0 < N ? ((double)pow(n, Pow) / pow(N, Pow)) * Input[n % Size] * Gain : Input[n % Size] * Gain;
    }
    return(R);
}
std::vector<float> ysxSIG_AttackExpVectorF(std::vector<float>& Input, float Pow, float Gain)
{
    uint32_t Size = Input.size(); std::vector<float> R(Size);
    for (uint32_t n = 0; n < Size; ++n) { R[n] = ((float)pow(n, Pow) / pow(Size, Pow)) * Input[n] * Gain; }
    return(R);
}
std::vector<float> ysxSIG_AttackExpVectorF(std::vector<float>& Input, float Pow, float Gain, uint32_t n0, uint32_t n1)
{
    if (n0 > n1) { uint32_t t = n1; n1 = n0, n0 = t; }
    if (n0 < 0) { n0 = 0; } if (n1 < 1) { n1 = 1; } if (n0 = n1) { n1 = n0 + 1; }
    uint32_t N = n1 - n0, Size = Input.size(); std::vector<float> R(Size);
    for (uint32_t n = n0; n < n1; ++n)
    {
        R[n % Size] = n - n0 < N ? ((float)pow(n, Pow) / pow(N, Pow)) * Input[n % Size] * Gain : Input[n % Size] * Gain;
    }
    return(R);
}
// #######
// DECAYS:
std::vector<double> ysxSIG_DecayVector(std::vector<double>& Input, double Gain)
{
    uint32_t Size = Input.size(); std::vector<double> R(Size);
    for (uint32_t n = 0; n < Size; ++n) { R[n] = ((double)(Size - n) / Size) * Input[n] * Gain; }
    return(R);
}
std::vector<double> ysxSIG_DecayVector(std::vector<double>& Input, double Gain, uint32_t n0, uint32_t n1)
{
    if (n0 > n1) { uint32_t t = n1; n1 = n0, n0 = t; }
    if (n0 < 0) { n0 = 0; } if (n1 < 1) { n1 = 1; } if (n0 = n1) { n1 = n0 + 1; }
    uint32_t N = n1 - n0, Size = Input.size(); std::vector<double> R(Size);
    for (uint32_t n = n0; n < Input.size(); ++n)
    {
        R[n % Size] = n - n0 < N ? ((N - n - n0) / (double)N) * Input[n % Size] * Gain : Input[n % Size] * Gain;
    }
    return(R);
}
std::vector<float> ysxSIG_DecayVectorF(std::vector<float>& Input, float Gain)
{
    uint32_t Size = Input.size(); std::vector<float> R(Size);
    for (uint32_t n = 0; n < Size; ++n) { R[n] = ((float)(Size - n) / Size) * Input[n] * Gain; }
    return(R);
}
std::vector<float> ysxSIG_DecayVectorF(std::vector<float>& Input, float Gain, uint32_t n0, uint32_t n1)
{
    if (n0 > n1) { uint32_t t = n1; n1 = n0, n0 = t; }
    if (n0 < 0) { n0 = 0; } if (n1 < 1) { n1 = 1; } if (n0 = n1) { n1 = n0 + 1; }
    uint32_t N = n1 - n0, Size = Input.size(); std::vector<float> R(Size);
    for (uint32_t n = n0; n < Input.size(); ++n)
    {
        R[n % Size] = n - n0 < N ? ((N - n - n0) / (float)N) * Input[n % Size] * Gain : Input[n % Size] * Gain;
    }
    return(R);
}
//  (pow(Size - n, Pow) / pow(Size, Pow)) * Input[n] * Gain:
std::vector<double> ysxSIG_DecayExpVector(std::vector<double>& Input, double Pow, double Gain)
{
    uint32_t Size = Input.size(); std::vector<double> R(Size);
    for (uint32_t n = 0; n < Size; ++n) { R[n] = ((double)pow(Size - n, Pow) / pow(Size, Pow)) * Input[n] * Gain; }
    return(R);
}
std::vector<double> ysxSIG_DecayExpVector(std::vector<double>& Input, double Pow, double Gain, uint32_t n0, uint32_t n1)
{
    if (n0 > n1) { uint32_t t = n1; n1 = n0, n0 = t; }
    if (n0 < 0) { n0 = 0; } if (n1 < 1) { n1 = 1; } if (n0 = n1) { n1 = n0 + 1; }
    uint32_t N = n1 - n0, Size = Input.size(); std::vector<double> R(Size);
    for (uint32_t n = n0; n < n1; ++n)
    {
        R[n % Size] = n - n0 < N ? ((double)pow(N - n - n0, Pow) / pow(N, Pow)) * Input[n % Size] * Gain : Input[n % Size] * Gain;
    }
    return(R);
}
std::vector<float> ysxSIG_DecayExpVectorF(std::vector<float>& Input, float Pow, float Gain)
{
    uint32_t Size = Input.size(); std::vector<float> R(Size);
    for (uint32_t n = 0; n < Size; ++n) { R[n] = ((float)pow(Size - n, Pow) / pow(Size, Pow)) * Input[n] * Gain; }
    return(R);
}
std::vector<float> ysxSIG_DecayExpVectorF(std::vector<float>& Input, float Pow, float Gain, uint32_t n0, uint32_t n1)
{
    if (n0 > n1) { uint32_t t = n1; n1 = n0, n0 = t; }
    if (n0 < 0) { n0 = 0; } if (n1 < 1) { n1 = 1; } if (n0 = n1) { n1 = n0 + 1; }
    uint32_t N = n1 - n0, Size = Input.size(); std::vector<float> R(Size);
    for (uint32_t n = n0; n < n1; ++n)
    {
        R[n % Size] = n - n0 < N ? ((float)pow(N - n - n0, Pow) / pow(N, Pow)) * Input[n % Size] * Gain : Input[n % Size] * Gain;
    }
    return(R);
}
// #######
// CHANGE INPUT VECTOR BY A GRADUATION FROM L1 TO L2, SIMILAR TO AN ATTACK, BUT WITH BOTH SIDES:
std::vector<double> ysxSIG_LineEnvelop(std::vector<double>& Input, double L1, double L2, double Gain)
{
    uint32_t Size = Input.size(); std::vector<double> R(Size);
    //if (L1 > L2) { float t = L1; L1 = L2; L2 = t; }
    if (L1 > 1) { L1 = 1; } if (L1 < 0) { L1 = 0; } if (L2 > 1) { L2 = 1; } if (L2 < 0) { L2 = 0; }
    double Delta = (L2 - L1) / Size;
    for (uint32_t n = 0; n < Size; ++n) { R[n] = (L1 + Delta * n) * Input[n] * Gain; }
    return(R);
}
std::vector<double> ysxSIG_LineEnvelop(std::vector<double>& Input, double L1, double L2, double Gain, uint32_t n0, uint32_t n1)
{
    if (n0 > n1) { uint32_t t = n1; n1 = n0, n0 = t; }
    if (n0 < 0) { n0 = 0; } if (n1 < 1) { n1 = 1; } if (n0 = n1) { n1 = n0 + 1; }
    uint32_t N = n1 - n0, Size = Input.size(); std::vector<double> R(Size);
    if (L1 > 1) { L1 = 1; } if (L1 < 0) { L1 = 0; } if (L2 > 1) { L2 = 1; } if (L2 < 0) { L2 = 0; }
    double Delta = (L2 - L1) / (n1 - n0);
    for (uint32_t n = n0; n < n1; ++n)
    {
        R[n % Size] = n - n0 < N ? (L1 + Delta * n) * Input[n % Size] * Gain : Input[n % Size] * Gain;
    }
    return(R);
}
std::vector<float> ysxSIG_LineEnvelopF(std::vector<float>& Input, float L1, float L2, float Gain)
{
    uint32_t Size = Input.size(); std::vector<float> R(Size);
    if (L1 > 1) { L1 = 1; } if (L1 < 0) { L1 = 0; } if (L2 > 1) { L2 = 1; } if (L2 < 0) { L2 = 0; }
    float Delta = (L2 - L1) / Size;
    for (uint32_t n = 0; n < Size; ++n) { R[n] = (L1 + Delta * n) * Input[n] * Gain; }
    return(R);
}
std::vector<float> ysxSIG_LineEnvelopF(std::vector<float>& Input, float L1, float L2, float Gain, uint32_t n0, uint32_t n1)
{
    if (n0 > n1) { uint32_t t = n1; n1 = n0, n0 = t; }
    if (n0 < 0) { n0 = 0; } if (n1 < 1) { n1 = 1; } if (n0 = n1) { n1 = n0 + 1; }
    uint32_t N = n1 - n0, Size = Input.size(); std::vector<float> R(Size);
    if (L1 > 1) { L1 = 1; } if (L1 < 0) { L1 = 0; } if (L2 > 1) { L2 = 1; } if (L2 < 0) { L2 = 0; }
    double Delta = (L2 - L1) / (n1 - n0);
    for (uint32_t n = n0; n < n1; ++n)
    {
        R[n % Size] = n - n0 < N ? (L1 + Delta * n) * Input[n % Size] * Gain : Input[n % Size] * Gain;
    }
    return(R);
}

// Change Input Vector by a exponential graduation from L1 to L2, similar to an Attack, but with both sides:
/*std::vector<double> LineExpEnvelop(std::vector<double> Input, double L1, double L2, double Pow, double Gain)
{
    uint32_t Size = Input.size();
    std::vector<double> R(Size);
    if (L1 > 1) { L1 = 1; } if (L1 < 0) { L1 = 0; } if (L2 > 1) { L2 = 1; } if (L2 < 0) { L2 = 0; }
    //double BigL = L2; if (L1 > L2) { BigL = L1; } double SmallL = L1; if (L1 > L2) { SmallL = L2; }
    //double DeltaL = BigL - SmallL, Delta = DeltaL / Size;
    double Delta = L2 - L1;
    for (uint32_t n = 0; n < Size; ++n) { double x = L1 + pow(Delta * n, Pow) / pow(Size, Pow); R[n] = x * Input[n] * Gain; }
    return(R);
}*/

// #######
// MODULATE VECTOR WITH ANOTHER VECTOR.
// Last index will be from input:
std::vector<double> ysxSIG_VectorEnvelop(std::vector<double>& Input, std::vector<double>& Modulator, double Gain)
{
    std::vector<double> V;
    for (uint32_t n = 0; n < Input.size(); ++n)
    {
        if (n < Modulator.size()) { V.push_back(Input[n] * Modulator[n] * Gain); }
        else { V.push_back(Input[n] * Gain); }
    }
    return(V);
}
std::vector<float> ysxSIG_VectorEnvelopF(std::vector<float>& Input, std::vector<float>& Modulator, float Gain)
{
    std::vector<float> V;
    for (uint32_t n = 0; n < Input.size(); ++n)
    {
        if (n < Modulator.size()) { V.push_back(Input[n] * Modulator[n] * Gain); }
        else { V.push_back(Input[n] * Gain); }
    }
    return(V);
}

// #######
// FILL ENVELOPES:

// std::vector<double> ADSR()

std::vector<double> ysxSIG_EnvAtkDec(uint32_t Size, double A, double D, double Gain)
{
    std::vector<double> R(Size);
    double Sum = A + D, RatioA = A / Sum, RatioD = D / Sum;
    uint32_t SizeA = floor(Size * RatioA), SizeD = Size - SizeA;
    double DeltaA = 1.0 / SizeA, DeltaD = 1.0 / SizeD;
    for (uint32_t n = 0; n < SizeA; ++n) { R[n] = (DeltaA * n) * Gain; }
    for (uint32_t n = SizeA; n < Size; ++n) { R[n] = (1 - (DeltaD * (n - SizeA))) * Gain; }
    return(R);
}
std::vector<float> ysxSIG_EnvAtkDecF(uint32_t Size, float A, float D, float Gain)
{
    std::vector<float> R(Size);
    float Sum = A + D, RatioA = A / Sum, RatioD = D / Sum;
    uint32_t SizeA = (uint32_t)floor(Size * RatioA), SizeD = Size - SizeA;
    float DeltaA = 1.0 / SizeA, DeltaD = 1.0 / SizeD;
    for (uint32_t n = 0; n < SizeA; ++n) { R[n] = (DeltaA * n) * Gain; }
    for (uint32_t n = SizeA; n < Size; ++n) { R[n] = (1 - (DeltaD * (n - SizeA))) * Gain; }
    return(R);
}
std::vector<double> ysxSIG_EnvLine(uint32_t Size, double L1, double L2, double Gain)
{
    std::vector<double> R(Size);
    if (L1 > 1) { L1 = 1; } if (L1 < 0) { L1 = 0; } if (L2 > 1) { L2 = 1; } if (L2 < 0) { L2 = 0; }
    double Delta = (L2 - L1) / Size;
    for (uint32_t n = 0; n < Size; ++n) { R[n] = (L1 + Delta * n) * Gain; }
    return(R);
}
std::vector<double> ysxSIG_EnvLine(uint32_t Size, double L1, double L2, double Gain, uint32_t n0, uint32_t n1)
{
    if (n0 > n1) { uint32_t t = n1; n1 = n0, n0 = t; }
    if (n0 < 0) { n0 = 0; } if (n1 < 1) { n1 = 1; } if (n0 = n1) { n1 = n0 + 1; }
    uint32_t N = n1 - n0; std::vector<double> R(Size);
    if (L1 > 1) { L1 = 1; } if (L1 < 0) { L1 = 0; } if (L2 > 1) { L2 = 1; } if (L2 < 0) { L2 = 0; }
    double Delta = (L2 - L1) / (n1 - n0);
    for (uint32_t n = n0; n < n1; ++n)
    {
        R[n % Size] = n - n0 < N ? (L1 + Delta * n) * Gain : Gain;
    }
    return(R);
}
std::vector<float> ysxSIG_EnvLineF(uint32_t Size, float L1, float L2, float Gain)
{
    std::vector<float> R(Size);
    if (L1 > 1) { L1 = 1; } if (L1 < 0) { L1 = 0; } if (L2 > 1) { L2 = 1; } if (L2 < 0) { L2 = 0; }
    float Delta = (L2 - L1) / Size;
    for (uint32_t n = 0; n < Size; ++n) { R[n] = (L1 + Delta * n) * Gain; }
    return(R);
}
std::vector<float> ysxSIG_EnvLineF(uint32_t Size, float L1, float L2, float Gain, uint32_t n0, uint32_t n1)
{
    if (n0 > n1) { uint32_t t = n1; n1 = n0, n0 = t; }
    if (n0 < 0) { n0 = 0; } if (n1 < 1) { n1 = 1; } if (n0 = n1) { n1 = n0 + 1; }
    uint32_t N = n1 - n0; std::vector<float> R(Size);
    if (L1 > 1) { L1 = 1; } if (L1 < 0) { L1 = 0; } if (L2 > 1) { L2 = 1; } if (L2 < 0) { L2 = 0; }
    double Delta = (L2 - L1) / (n1 - n0);
    for (uint32_t n = n0; n < n1; ++n)
    {
        R[n % Size] = n - n0 < N ? (L1 + Delta * n) * Gain : Gain;
    }
    return(R);
}

// ####### LIMITERS AND NORMALIZERS #######

// IF BIGGER THAN Y THEN Y:
std::vector<double> ysxSIG_LimitToptoY(std::vector<double> fx, double Y)
{
    for (uint32_t n = 0; n < fx.size(); ++n)
    {
        if (fx[n] > Y) { fx[n] = Y; }
    }
    return(fx);
}

// IF BIGGER THAN Y AND LOWER THAN -Y, THEN Y AND -Y:
std::vector<double> ysxSIG_LimittoY(std::vector<double> fx, double Y)
{
    for (uint32_t n = 0; n < fx.size(); ++n)
    {
        if (fx[n] > Y) { fx[n] = Y; } else if (fx[n] < -Y) { fx[n] = -Y; }
    }
    return(fx);
}

// IF BIGGER THAN Y1 AND LOWER THAN Y0, THEN Y1 AND Y0:
std::vector<double> ysxSIG_LimittoY1Y0(std::vector<double> fx, double Y1, double Y0)
{
    if (Y0 == Y1) { Y0 += 1.0e-9; } if (Y1 < Y0) { double T = Y1; Y1 = Y0; Y0 = T; }
    for (uint32_t n = 0; n < fx.size(); ++n)
    {
        if (fx[n] > Y1) { fx[n] = Y1; } else if (fx[n] < Y0) { fx[n] = Y0; }
    }
    return(fx);
}

// NORMALIZE BETWEEN '-1' AND '1':
std::vector<double> ysxSIG_Normalize(std::vector<double> fx)
{
    double Max = ysxVEC_MaxVecAbs(fx); if (Max == 0) { Max = 1.0e-9; }
    for (uint32_t n = 0; n < fx.size(); ++n) { fx[n] /= Max; } return(fx);
}

// NORMALIZE BETWEEN '0' AND '1', "(f(x) + 1) * 0.5":
std::vector<double> ysxSIG_NormalizeMod(std::vector<double> fx)
{
    double Max = ysxVEC_MaxVecAbs(fx); if (Max == 0) { Max = 1.0e-9; }
    for (uint32_t n = 0; n < fx.size(); ++n) { fx[n] /= Max; fx[n] += 1; fx[n] *= 0.5; } return(fx);
}

// ####################################################################################
// ################################### MAIN CLASSES ###################################
// ####################################################################################

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
    // Maybe make an option to choose the bit of the 'Size' and 'C'
    uint32_t Size = 0; // As samples
    // 'C'ount (iterator), use vector index as different voices, careful with changes:
    std::vector<uint32_t> C;
    // INPUT, FOR INHERITANCE:
    // * Think about the input as 'void', but limited to n-bits, use casts.
    virtual T_ IO(T_ data) { return(data); }

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
    virtual T_ IO(T_* Type) { return(*Type); }

    //ysxSIG_IO() { }
    //~ysxSIG_IO() { }
};

// ################################################# FIM ####################################################################################

#endif // SCPARSE_