#pragma once

#ifndef YSXPHYS_H
#define YSXPHYS_H

#include "ysxConst.h"

/*#####################
####### By Sophia Cristina
####### Header for my bad skills at physics.
#####################*/

// #####################################################################################################################################
// ####### DECLARATIONS:
double ysxPHYS_DensityAir(double, double, double);

// #####################################################################################################################################
// Some functions are equal, but is for me to memorize it.
// ####### ####### #######

// #####################################################################################################################################
// ####### FORCE, ENERGY, POWER, MASS AND ALIKE:
double ysxPHYS_Joules(double NorWorPaorC, double morsorcubemorV) { return(NorWorPaorC * morsorcubemorV); } // (Newton or Watts or Pa or Coulomb) * (meter or seconds or meter^3 or Volts) | Energy
double ysxPHYS_Joules(double kg, double m, double s) { return((kg * m * m) / (s * s)); } // (kg * meter^2) / s^2 | Energy
double ysxPHYS_Watts(double J, double s) { return(J / s); } // Its simple Joules per sec | Power
double ysxPHYS_Watts(double N, double m, double s) { return((N * m) / s); } // (Newton * meter) / seconds | Power
double ysxPHYS_Newtons(double m) { return(m * GRAVITY); } // Newton = mass * Gravity_accel | Force
double ysxPHYS_Newtons(double m, double a) { return(m * a); } // Newton = mass * acceleration | Force
double ysxPHYS_Newtons(double kg, double meter, double s) { return((kg * meter) / (s * s)); } // Newton = (kg * meter) / s^2 | Force
double ysxPHYS_Tension(double kg, double rad) { return((kg * GRAVITY) / sin(rad)); } // (kg * 9.80665) / sin(rad)
double ysxPHYS_Momentum(double kg, double ms) { return(kg * ms); }
double ysxPHYS_Pressure(double Force, double Area) { return(Force / Area); }
double ysxPHYS_NormForce(double kg) { return(kg * GRAVITY); } // Normal force
double ysxPHYS_NormForce(double kg, double Ang) { return(kg * GRAVITY * cos(Ang)); } // Normal force

// ####### NETS:
struct ysxPHYS_Friction { double mus, muk, kg; }; // mus or muk * Fnormal = muk * (mass * gravity * cos(angle of inclination))
struct ysxPHYS_Force { double Fx, Fy, N, Angle, kg, Accel; };
struct ysxPHYS_Particle { double Force, Momentum, Velocity, Mass, DirectionRad, x, y; };
ysxPHYS_Friction ysxPHYS_MakeFriction(double CoeffS, double CoeffK, double kg)
{ ysxPHYS_Friction F; F.mus = CoeffS * kg * GRAVITY; F.muk = CoeffK * kg * GRAVITY; F.kg = kg; return(F); } // Make structure
ysxPHYS_Friction ysxPHYS_MakeFriction(double CoeffS, double CoeffK, double kg, double Grav)
{ ysxPHYS_Friction F; F.mus = CoeffS * kg * Grav; F.muk = CoeffK * kg * Grav; F.kg = kg; return(F); }
ysxPHYS_Force ysxPHYS_ForceGravity(ysxPHYS_Force Frc) { ysxPHYS_Force F; F.Fy = Frc.kg * -GRAVITY; F.Fx = 0; F.Angle = sin(1.5 * PI); return(F); }
ysxPHYS_Force ysxPHYS_MakeForce(double Frc, double Ang, double Mass)
{
	ysxPHYS_Force F; F.Fx = Frc * cos(Ang); F.Fy = Frc * sin(Ang); F.N = Frc; F.Angle = Ang; F.kg = Mass; F.Accel = Frc / Mass;
	if (Ang > PI * 0.5 && Ang < PI * 1.5) { F.Fx *= -1; } if (Ang > PI && Ang < 2 * PI) { F.Fy *= -1; }	return(F);
}
double ysxPHYS_FnetFriction(ysxPHYS_Friction Strct, double N)
{ double Fs = Strct.mus * Strct.kg * GRAVITY, Fk = Strct.muk * Strct.kg * GRAVITY; if (N <= Fs) { return(0); } return(N - Fk); }
double ysxPHYS_FnetFriction(ysxPHYS_Friction Strct, double N, double Grav)
{ double Fs = Strct.mus * Strct.kg * Grav, Fk = Strct.muk * Strct.kg * Grav; if (N <= Fs) { return(0); } return(N - Fk); }

void ysxPHYS_CoutFriction(ysxPHYS_Friction Fric) { std::cout << "mus: " << Fric.mus << " | muk: " << Fric.muk << " | kg: " << Fric.kg << std::endl; }
void ysxPHYS_CoutFriction(std::vector<ysxPHYS_Friction> Vec)
{ std::cout << std::endl; for (size_t n = 0; n < Vec.size(); ++n) { std::cout << n << ": "; ysxPHYS_CoutFriction(Vec[n]); } }
void ysxPHYS_CoutFrc(ysxPHYS_Force Frc)
{ std::cout << "Fx: " << Frc.Fx << " | Fy: " << Frc.Fy << " | kg: " << Frc.kg << " | Angle: " << Frc.Angle << " | Accel.: " << Frc.Accel << std::endl; }
void ysxPHYS_CoutFrc(std::vector<ysxPHYS_Force> Vec)
{ std::cout << std::endl; for (size_t n = 0; n < Vec.size(); ++n) { std::cout << n << ": "; ysxPHYS_CoutFrc(Vec[n]); } }


class ysxPHYS_ForceNet
{
public:
	std::vector<ysxPHYS_Force> Forces;
	ysxPHYS_Friction Friction;
	ysxPHYS_Force FTotal; // Force that will be the sum of all Forces;

	void SumAll() // Sum all forces; Frictions[Friction Index], use '-1' to avoid friction;
	{
		ysxPHYS_Force Tot; Tot.Fx = 0; Tot.Fy = 0; Tot.N = 0;
		if (Forces.size() > 0)
		{
			if (Forces.size() > 1)
			{
				for (size_t n = 1; n < Forces.size(); ++n)
				{
					Tot.Fx += Forces[n - 1].Fx + Forces[n].Fx;
					Tot.Fy += Forces[n - 1].Fy + Forces[n].Fy;
				}
			}
			else if (Forces.size() == 1) { Tot = Forces[0]; }
			if (Tot.N < Friction.mus) { Tot.N = 0; Tot.Fx = 0; Tot.Fy = 0; }
			else { Tot.N = Tot.N - Friction.muk; Tot.Fx = sqrt((Tot.N * Tot.N) - (Tot.Fy * Tot.Fy)); Tot.Fy = sqrt((Tot.N * Tot.N) - (Tot.Fx * Tot.Fx)); }
			Tot.N = sqrt((Tot.Fx * Tot.Fx) + (Tot.Fy * Tot.Fy));
			Tot.Angle = ysxGEO_LawSinRad(Tot.Fx, Tot.Fy, HPI);
			Tot.Accel = Tot.N / Tot.kg;
		}
		FTotal = Tot; // !!!!!!! DONE !!!!!!!
	}
};

// #####################################################################################################################################

// #####################################################################################################################################
// ######################################################## CLASSIC MECHANICS ########################################################
// #####################################################################################################################################

// ####### VELOCITY AND ETC:
/* Formulas:
	Velo = (x2 - x1) / (t2 - t1); Acell = d2x/dt2 = (v2 - v1) / (t2 - t1); Jerk = d3x/dt3 = (a2 - a1) / (t2 - t1)
	Velo = Derivative(x1, x2, t1, t2); Acell = Derivative(v1, v2, t1, t2)
*/
double ysxPHYS_Accel(double F, double m) { return(F / m); } // Acceleration can be written as Force / mass
// BASE:
double ysxPHYS_DistTrav(double Vel0, double t, double Accel) { return((Vel0 * t) + (0.5 * Accel * t * t)); } // Distance traveled

// WIND:
 // U(h) speed at height h; SurfRough is the exponential coefficient based on ground surface roughness, typically between 0.08 and 0.52:
double ysxPHYS_SpeedWindHeight(double h0, double h, double SurfRough) { return(h0 * pow(h, SurfRough)); }
double ysxPHYS_SpeedWindHghtGrad(double h0, double h, double SurfRough) { return(SurfRough * (ysxPHYS_SpeedWindHeight(h0, h, SurfRough) / h)); }

// PARTICLE:
double ysxPHYS_ParticleVel(double d1, double d2, double t1, double t2) { return((d2 - d1) / (t2 - t1)); } // d = displacement; t = time;

// KINETIC:
double ysxPHYS_KineticEnrg(double kg, double ms) { return(0.5 * kg * ms * ms); } // Speed in m/s | return = Joules
double ysxPHYS_KineticEnMom(double p, double kg) { return((p * p) / (2 * kg)); } // The kinetic energy of an object is related to its momentum
double ysxPHYS_Density(double kg, double Vol) { return(kg / Vol); } // Densidade, kg/m^3
double ysxPHYS_DensityAir(double Pa, double GasConst, double T) { return((Pa / (GasConst * T))); } // Pa = Pressure; Gas Constant in J/(kg·K); T = Temperature in Kelvins
double ysxPHYS_Stiffness(double F, double d) { return(F / d); } // Force / Displacement (menor distancia entre x1 e x2)| https://en.wikipedia.org/wiki/Displacement_(vector)

// ####### ELASTICITY AND ETC:
 // P = pressure | p = density | change p (elasticity) to v if needed
double ysxPHYS_BulkMod(double P1, double P2, double p1, double p2) { return((P2 - P1) / (- (p2 - p1) / p1)); }

// #####################################################################################################################################
// ######################################################## ACOUSTICÚSTICA ########################################################
// #####################################################################################################################################
// https://en.wikipedia.org/wiki/List_of_equations_in_wave_theory

// #####################################################################################################################################
// SOUND SPEED:
double ysxPHYS_SpeedSound(double BulkMod, double p) { return(sqrt(BulkMod / p)); } // BulkMods; p = density
double ysxPHYS_SpeedSoundLiq(double BulkMod, double p) { return(sqrt(BulkMod / p)); } // BulkMods; p = density | Same as above, but Bulk Mod. of the fluid
double ysxPHYS_SpeedSndAir(double BulkMod, double K) { return(sqrt(BulkMod / ysxPHYS_DensityAir(101325, 287.058, K))); } // BulkMods; P = pressure; K = Temperature in Kelvins;
double ysxPHYS_SpeedSndAir(double BulkMod, double Pa, double K)
{ return(sqrt(BulkMod / ysxPHYS_DensityAir(Pa, 287.058, K))); } // BulkMods; P = pressure; K = Temperature in Kelvins;
double ysxPHYS_SpeedSndAir(double BulkMod, double Pa, double K, double GasConst)
{ return(sqrt(BulkMod / ysxPHYS_DensityAir(Pa, GasConst, K))); } // BulkMods; P = pressure; K = Kelvin;
double ysxPHYS_SpeedSndDryAir(double Celsius) { return(331.3 + 0.606 * Celsius); } // Return in m/s
// https://en.wikipedia.org/wiki/Speed_of_sound#Speed_of_sound_in_solids // pw = P-Waves, primary waves; sw = S-Waves, secondary waves;
double ysxPHYS_SpeedSndSolidpwBulk(double Bulk, double Shear, double Density) { return(sqrt((Bulk + (1.333333333 * Shear)) / Density)); } // Bulk formula
double ysxPHYS_SpeedSndSolidpwYoung(double Young, double Poisson, double Density)
{ return((Young * (1 - Poisson)) / (Density * (1 + Poisson) * (1 - (2 * Poisson)))); } // Young formula
double ysxPHYS_SpeedSndSolidsw(double Shear, double Density) { return(sqrt(Shear / Density)); }
double ysxPHYS_SpeedSndSolid1d(double Young, double Density) { return(sqrt(Young / Density)); }
// The speed of sound in a plasma for the common case that the electrons are hotter than the ions(but not too much hotter) is given by the formula:
// mi the ion mass; Mu the ratio of ion mass to proton mass Mu = mi / mp; Te the electron temperature; Z the charge state; k Boltzmann constant; y the adiabatic index.
double ysxPHYS_SpeedSndPlasma(double mi, double Te, double Z, double k, double y) { return(pow((y * Z * Te) / mi, 0.5)); } // Return in m/s
double ysxPHYS_SpeedSndPlasma0(double Mu, double Te, double Z, double k, double y) { return((9.79 * pow(10, 3)) * pow((y * Z * Te) / Mu, 0.5)); } // Return in m/s
double ysxPHYS_SingleShotTime(double CapDist, double Time) { return(CapDist / Time); } // Time amount sound takes to be captured in CapDist (like a microphone) shows sound velocity

// #####################################################################################################################################
// SOUND INTENSITY:
double ysxPHYS_SoundIntpv(double p, double v) { return (p * v); } // p = Sound pressure; v = Particle velocity;
double ysxPHYS_SoundIntPA(double Watts, double Area) { return (Watts / Area); } // Watts / m^2
 // Inverse-square law, for Spherical sound intensity, 4 * PI * r^2 = surface area of a sphere:
double ysxPHYS_SoundIntSph(double Watts, double r) { return(Watts / (4 * PI * r * r)); }
// Watt / 4PIr^2 = (Joules / s) / 4PIr^2:
double ysxPHYS_SoundIntSph(double Newtons, double meters, double seconds, double r)
{ return(((Newtons * meters) / seconds) / (4 * PI * r * r)); }

// WAVE LENGTH (Lambda):
double ysxPHYS_WaveLgh(double v, double f) { return(v / f); } // v = Phase velocity; f = Frequency;

// SOUND PRESSURE:
double ysxPHYS_SoundPress(double I, double v) { return(I / v); }
double ysxPHYS_SoundPress(double Watts, double Area, double v) { return((Watts / Area) / v); }

// #####################################################################################################################################
// NON-STATIONARY WAVE FUNCTION:
// https://brilliant.org/wiki/waves/
// Waves moving (non-stationary) have a disturbance that varies both with time 't' as the distance 'z' can be expressed mathematically as *Formula*
// where 'A(z, t)' is the amplitude envelope of the wave, 'k' is the wave number, and 'Phase' is the phase constant. The velocity 'v' of this wave is given by 'v = Omega / k';
double ysxPHYS_NonStatWaveFunc(double A, double z, double t, double k, double Omega, double Phase) { return(A * cos((k * z) - (Omega * t) + Phase)); }

// #####################################################################################################################################
// PARTICLE VELOCITY, SINE WAVE:
double ysxPHYS_ParticleVel(double Dist, double Watts, double t1, double t2, double Omega, double Wavenum, double Phase)
{
	double Ray = SPEEDSOUND * t1;
	double Dispa = ysxPHYS_NonStatWaveFunc(ysxPHYS_SoundIntSph(Watts, Ray), Dist, t1, Wavenum, Omega, Phase); // Disp = Displacement, Time in seconds
	Ray = SPEEDSOUND * t2;
	double Dispb = ysxPHYS_NonStatWaveFunc(ysxPHYS_SoundIntSph(Watts, Ray), Dist, t2, Wavenum, Omega, Phase);
	return (ysxCALC_Deriv(Dispa, Dispb, t1, t2));
}

// #####################################################################################################################################
// ACOUSTIC WAVE EQUATION:
double ysxPHYS_AcoWavEq(double d2p, double dx2, double Bulk, double Pa, double K, double GasConst, double dt2)
{ return((d2p / dx2) - (1.0 / pow(ysxPHYS_SpeedSndAir(Bulk, Pa, K, GasConst), 2)) * (d2p / dt2)); }
double ysxPHYS_AcoWavEq(double d2p, double dx2, double Bulk, double K, double dt2)
{ return((d2p / dx2) - (1.0 / pow(ysxPHYS_SpeedSndAir(Bulk, 101325, K, 287.058), 2)) * (d2p / dt2)); }
double ysxPHYS_AcoWavEq(double d2p, double dx2, double dt2) { return((d2p / dx2) - (1.0 / pow(ysxPHYS_SpeedSndAir(101325, 101325, 288.15, 287.058), 2)) * (d2p / dt2)); }

// WAVE EQUATION:
double ysxPHYS_WaveEq(double x, double Omega, double (*f)(double, double))
{ double Limit = 1.0e-6; return((f(x + Limit, Omega) - 2 * f(x, Omega) + f(x - Limit, Omega)) / (Limit * Limit)); }

// P-WAVE:
double ysxPHYS_PWave() { return(0); }

// PENDULUM:
double ysxPHYS_PendPeriSimple(double Lenght) { return(2 * PI * sqrt(Lenght / GRAVITY)); }

// SIMPLE HARMONIC OSCILLATION:
double ysxPHYS_SimpleHarmOsc(double Tht0, double T, double t, double phi) { return(Tht0 * cos(phi + ((2 * PI) / T) * t)); }

// #####################################################################################################################################
// ####### VECTORS:

// MAKE A VECTOR OF A WAVE:
// Sec = seconds for the wave to finish
// WRto = Watts ratio, it multiplies it by each dt
std::vector<double> ysxPHYS_NonStatWaveVec(int VecSize, double SndSpeed, double Sec, double Watts, double WRto, double Wavenumber, double Omega, double Phase)
{
	std::vector<double> V(VecSize);
	double tdiv, dt, y;
	for (size_t tn = 0; tn < VecSize; ++tn)
	{
		tdiv = (float)tn / VecSize;
		dt = Sec * tdiv;
		y = ysxPHYS_NonStatWaveFunc(SndInt2db(ysxPHYS_SoundIntSph(Watts, dt * SndSpeed)), Sec, dt, Wavenumber, Omega, Phase);
		V[tn] = y;
		Watts *= WRto;
	}
	return (V);
}

// CRIA MATRIZ DE INTENSIDADE DO SOM (ESFÉRA):
// WRto = Watts ratio, it multiplies it by each dt
std::vector<double> ysxPHYS_SndIntSphVec(int Size, double Watts, double r, double WRto)
{
	double tWatts = Watts; // Ratio Watts
	double dr = r / Size;
	std::vector<double> Ret;
	for (size_t n = 0; n <= Size; ++n)
	{
		tWatts *= WRto;
		Ret.push_back(ysxPHYS_SoundIntSph(tWatts, n * dr));
	}
	return Ret;
}

// #####################

// #####################################################################################################################################
// #####################
// ### CLASSES:
// #####################

// PARTICLE SYSTEM (W.I.P):
class ysxPHYS_ParticleSys2D
{
	enum OpForce { Explosion, Pull, Fuel };
	double Wx, Wy; // Distance from wall to wall, if there is no wall, the particle is destroyed
	double PrtBxx, PrtBxy; // Particles will spawn inside this box randomly
	bool WL, WR, WU, WD; // Wall left, right, up, down; Is there a wall?
	double mus, muk; // Frictions

	std::vector<ysxPHYS_Particle> Particles;
};

// ##################################################################################################
// WAVE OBJECT:
class ysxPHYS_AcousticWave
{
public:
	double Frequency, WaveLenght, Pressure;
	double Omega; // Omega, radians per sec; Frequencia em termos musicais, 440hz é na verdade 440omega;
	double Velocity, Wavenumber, Distance, VectorSize, Watts;
	std::vector<double> WaveVec;

	// #################################################
	// Mudar Tamanho da Onda:
	void ChangeWaveLenght(double NewNum)
	{
		Frequency = Velocity / NewNum; WaveLenght = Velocity / Frequency; Wavenumber = TAU / WaveLenght; Omega = TAU * Frequency;
		WaveVec = ysxPHYS_NonStatWaveVec(VectorSize, Velocity, Distance, Watts, 1, Wavenumber, Omega, 0);
	}

	// MAKE VECTORS WITH RATIOS BY TIME (dt):
	std::vector<double> MakeModVector(double Velr, double Freqr, double tPhase) // r = rate, if you leave as '1' it will not modulate, ex.: "tVel = Velocity * Velr".
	{
		std::vector<double> V;
		double tVel = Velocity, tWaven, tFreq = Frequency, tOmega;
		double tdiv, dt, y;
		for (int tn = 0; tn < VectorSize; ++tn)
		{
			tdiv = tn / (VectorSize - 1);
			dt = (Distance * tdiv);
			tPhase = (tPhase + tPhase) / 2.0; tVel *= Velr; tFreq *= Freqr;
			tOmega = TAU * tFreq; tWaven =  TAU / (tVel / tFreq);
			//cout << tVel << " " << tFreq << " " << tOmega << " " << tWaven << std::endl;
			y = ysxPHYS_NonStatWaveFunc(SndInt2db(ysxPHYS_SoundIntSph(Watts, dt * tVel)), Distance, dt, tWaven, tOmega, tPhase);
			V.push_back(y);
		}
		return (V);
	}

	// #################################################

	ysxPHYS_AcousticWave(double Freq, double Vel, double W, double Dist, int tVectorSize)
	{
		Frequency = Freq;
		Velocity = Vel;
		Distance = Dist;
		WaveLenght = Velocity / Frequency; // WaveLgh(Velocity, Frequency); Funtion for that.
		Wavenumber = TAU / WaveLenght;
		Omega = TAU * Frequency;
		Watts = W;
		VectorSize = tVectorSize;
		WaveVec = ysxPHYS_NonStatWaveVec(VectorSize, Velocity, Distance, Watts, 1, Wavenumber, Omega, 0);
	}
};

// ##################################################################################################
// FLUTE SYNTH (W.I.P, probably going to be moved to 'ysxSynth.h'):
class ysxPHYS_FluteSynth
{
public:
	double Size, Diameter, N, Angle, Angle0, MaxAng, Distance; // Size of the flute, Diameter, Newtons (change to watts, maybe?), Angles of blow, Distance of the mouth
	struct Hole { double Pos; bool Open; };
	std::vector<Hole> Holes;

	ysxPHYS_FluteSynth(double Nwtn, double Ang, double Ang0, double Dist, double FlteSize, double Diamtr)
	{

	}	
};

// ################################################# FIM ####################################################################################

#endif // SCPARSE_