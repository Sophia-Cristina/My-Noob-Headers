#pragma once

#ifndef YSXSIGELEC_H
#define YSXSIGELEC_H

// #####################
// ####### By Sophia Cristina
// ####### Electrical engineering functions for signals. Basically and aproach to the analogic level of it.
// #####################

// ####################################################################################
// ####################################################################################
// ####################################################################################

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

#endif
