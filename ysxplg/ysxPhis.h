#pragma once

#ifndef YSXPHIS_H
#define YSXPHIS_H

#include "ysxConst.h";

using namespace std;

// #####################################################################################################################################
// ####### DECLARAÇÕES:
double DensityAir(double, double, double);
// #####################
// ####### FERRAMENTAS:
struct Friction { double mus, muk, kg; }; // mus or muk * Fnormal = muk * (mass * gravity * cos(angle of inclination))
void CoutFriction(Friction Fric) { cout << "mus: " << Fric.mus << " | muk: " << Fric.muk << " | kg: " << Fric.kg << endl; }
void CoutFricVec(vector<Friction> Vec) { cout << endl; for (int n = 0; n < Vec.size(); ++n) { cout << n << ": "; CoutFriction(Vec[n]); } }
struct Force { double Fx, Fy, N, Angle, kg, Accel; };
void CoutFrc(Force Frc) { cout << "Fx: " << Frc.Fx << " | Fy: " << Frc.Fy << " | kg: " << Frc.kg << " | Angle: " << Frc.Angle << " | Accel.: " << Frc.Accel << endl; }
void CoutFrcVec(vector<Force> Vec) { cout << endl; for (int n = 0; n < Vec.size(); ++n) { cout << n << ": "; CoutFrc(Vec[n]); } }
struct Particle { double Force, Momentum, Velocity, Mass, Direction, /*Radians*/ x, y; /*Coordinates*/};

// #####################
// ### MINHAS FORMULAS:
// #####################

// #####################
// ### FIM | MINHAS ###
// #####################
// #####################################################################################################################################
// Boa parte das funções aqui são simples e iguais, mas a ideia é memorizar, se esquecer qual é a formula, escreva o nome da formula e mesmo que seja simples, ja saberá
// o que fazer, inclusive com os comentarios em cada função.
// ####### ####### #######
// ####### CONVERSORES:

// COMPRIMENTOS: 
// https://en.wikipedia.org/wiki/Conversion_of_units
double kmh2ms(double kmh) { return(kmh / 3.6); } // km/h to m/s
double ms2kmh(double ms) { return(ms * 3.6); } // m/s to km/h
double foot2m(double foot) { return(foot * 0.3048); } // foot to m
double m2foot(double m) { return(m / 0.3048); } // m to foot
double mileh2ms(double mile) { return(mile * 0.44704); } // miles per hour to m/s
double ms2mileh(double ms) { return(ms / 0.44704); } // miles per hour to m/s
double mile2km(double mile) { return(mile * 1.609344); } // mile to km
double km2mile(double km) { return(km / 1.609344); } // km to mile
double mile2knot(double mile) { return(mile * 0.868976); } // miles to knots
double knot2mile(double knot) { return(knot / 0.868976); } // knots to miles
double kmh2knot(double km) { return(km * 1.852); } // km/h to knots
double knot2kmh(double knot) { return(knot / 1.852); } // knots to km/h
double mile2fts(double mile) { return(mile * 1.467); } // miles per hour to feet per sec
double fts2mile(double fts) { return(fts / 1.467); } // feet per sec to mile per hour
double inch2cm(double inch) { return((inch * 25.4) * 0.1); } // inch to cm
double cm2inch(double cm) { return((cm * 10) * 0.03937008); } // cm to inch
double yard2m(double yard) { return(yard * 0.9144); } // yard 2 meters
double m2yard(double m) { return(m / 0.9144); } // meter 2 yard
double ms2fts(double ms) { return(ms * 3.28084); } // m/s to feets per sec
double ms2knot(double ms) { return(ms * 1.9438444924); } // m/2 to knot (orignally 1.9438444924406047516198704103672, but cut to 'double')
double knot2ms(double knot) { return(knot / 1.9438444924); } // m/2 to knot (orignally 1.9438444924406047516198704103672, but cut to 'double')

// PESO:
double lbs2kg(double lbs) { return(lbs * 0.45359237); } // Pounds to kg
double kg2lbs(double kg) { return(kg / 0.45359237); } // kg to pounds
double oz2g(double oz) { return(oz * 28.349523125); } // oz to grams
double g2oz(double g) { return(g / 28.349523125); } // grams to oz
double g2gr(double g) { return(g / 0.06479891); } // grams to grains
double gr2g(double g) { return(g * 0.06479891); } // grains to grams

// TEMPERATURAS:
double Fahr2Cel(double F) { return((F - 32) * (5.0 / 9)); }
double Cel2Fahr(double C) { return((C * 9.0 / 5) + 32); }

// PRESSÃO:
double atm2pa(double atm) { return(atm * 101325); }
double pa2atm(double Pa) { return(Pa / 101325); }

// SOM:
// !!! VEJA SE ESTOU CERTO SOBRE ANULAR DB < 0 !!!
// Sound Intensity to Decibels for propper sound intesity level
// https://en.wikipedia.org/wiki/Sound_intensity#Sound_intensity_level:
double SndInt2db(double I) { double Result = 10 * log10(I / 1.0e-12); if (Result < 0) { Result = 0; } return(Result); }
double SndInt2db(double I, double I0) { double Result = 10 * log10(I / I0); if (Result < 0) { Result = 0; } return(Result); }
double SndInt2db(double I, double p, double Watts, double m2) { double Result = 10 * log10(I / ((p * Watts) / m2)); if (Result < 0) { Result = 0; } return(Result); }

// #####################################################################################################################################
// ######################################################## UNIDADES ########################################################
// #####################################################################################################################################
// ####### FORÇA, ENERGIA, POTÊNCIA E MASSA:
double Joules(double NorWorPaorC, double morsorcubemorV) { return(NorWorPaorC * morsorcubemorV); } // (Newton or Watts or Pa or Coulomb) * (meter or seconds or meter^3 or Volts) | Energy
double Joules(double kg, double m, double s) { return((kg * m * m) / (s * s)); } // (kg * meter^2) / s^2 | Energy
double Watts(double J, double s) { return(J / s); } // Its simple Joules per sec | Power
double Watts(double N, double m, double s) { return((N * m) / s); } // (Newton * meter) / seconds | Power
double Newtons(double m) { return(m * 9.80665); } // Newton = mass * acceleration | Force
double Newtons(double m, double a) { return(m * a); } // Newton = mass * acceleration | Force
double Newtons(double kg, double meter, double s) { return((kg * meter) / (s * s)); } // Newton = (kg * meter) / s^2 | Force
double Tension(double kg, double Angle) { double Fd = kg * 9.80665; return(Fd / sin(Angle)); }
double Momentum(double kg, double ms) { return(kg * ms); } // Momentum
double Pressure(double Force, double Area) { return(Force / Area); } // Pressão
double NormForce(double kg) { return(kg * Gravity); } // Normal force
double NormForce(double kg, double Ang) { return(kg * Gravity * cos(Ang)); } // Normal force

// Net:
double FnetFriction(Friction Strct, double N) { double Fs = Strct.mus * Strct.kg * 9.80665, Fk = Strct.muk * Strct.kg * 9.80665; if (N <= Fs) { return(0); } return(N - Fk); }
double FnetFriction(Friction Strct, double N, double Grav) { double Fs = Strct.mus * Strct.kg * Grav, Fk = Strct.muk * Strct.kg * Grav; if (N <= Fs) { return(0); } return(N - Fk); }
Friction MakeFriction(double CoeffS, double CoeffK, double kg) { Friction F; F.mus = CoeffS * kg * 9.80665; F.muk = CoeffK * kg * 9.80665; F.kg = kg; return(F); } // Make structure
Friction MakeFriction(double CoeffS, double CoeffK, double kg, double Grav) { Friction F; F.mus = CoeffS * kg * Grav; F.muk = CoeffK * kg * Grav; F.kg = kg; return(F); }
// FORCE STRUCT:
Force ForceGravity(Force Frc) { Force F; F.Fy = Frc.kg * -9.80655; F.Fx = 0; F.Angle = sin(1.5 * Pi); return(F); }
Force MakeForce(double Frc, double Ang, double Mass)
{
	Force F; F.Fx = Frc * cos(Ang); F.Fy = Frc * sin(Ang); F.N = Frc; F.Angle = Ang; F.kg = Mass; F.Accel = Frc / Mass;
	if (Ang > Pi * 0.5 && Ang < Pi * 1.5) { F.Fx *= -1; } if (Ang > Pi && Ang < 2 * Pi) { F.Fy *= -1; }	return(F);
}

// #####################################################################################################################################

// #####################################################################################################################################
// ######################################################## MECANICA CLASSICA ########################################################
// #####################################################################################################################################
// ####### VELOCIDADES E ETC:
/* Formulas:
	Velo = (x2 - x1) / (t2 - t1); Acell = d2x/dt2 = (v2 - v1) / (t2 - t1); Jerk = d3x/dt3 = (a2 - a1) / (t2 - t1)
	Velo = Derivative(x1, x2, t1, t2); Acell = Derivative(v1, v2, t1, t2)
*/
// Parece estar funcionando corretamente, mas me questiono se é "t3 - t0" ou "(t3 - t2) + (t1 - t0)":
double Accel(double x0, double x1, double x2, double x3, double t0, double t1, double t2, double t3)
{ return((((x3 - x2) / (t3 - t2)) - ((x1 - x0) / (t1 - t0))) / ((t3 - t2) * (t1 - t0))); } // antes a divisão era (t3 - t0), agora mutiplica
// î_ Pode ser que tenha que ter (x3 - x2)/dt2 - (x2 - x1)/dt1 -(x1 - x0) / dt0
// î_ Acho que nenhum desses funciona.

double Accel(double F, double m) { return(F / m); } // Acceleration can be written as Force / mass
// BASE:
double DistTrav(double Vel0, double t, double Accel) { return((Vel0 * t) + (0.5 * Accel * t * t)); } // Distance traveled

// VENTO:
 // U(h) speed at height h; SurfRough is the exponential coefficient based on ground surface roughness, typically between 0.08 and 0.52:
double WindSpeedHeight(double h0, double h, double SurfRough) { return(h0 * pow(h, SurfRough)); }
double WindSpeedHghtGrad(double h0, double h, double SurfRough) { return(SurfRough * (WindSpeedHeight(h0, h, SurfRough) / h)); }

// PARTICULA:
double ParticleVel(double d1, double d2, double t1, double t2) { return((d2 - d1) / (t2 - t1)); } // d = displacement; t = time;

//  Cinética:
double KineticEnrg(double kg, double ms) { return(0.5 * kg * ms * ms); } // Speed in m/s | return = Joules
double KineticEnMom(double p, double kg) { return((p * p) / (2 * kg)); } // The kinetic energy of an object is related to its momentum
double Density(double kg, double Vol) { return(kg / Vol); } // Densidade, kg/m^3
double DensityAir(double Pa, double GasConst, double T) { return((Pa / (GasConst * T))); } // Pa = Pressure; Gas Constant in J/(kg·K); T = Temperature in Kelvins
double Stiffness(double F, double d) { return(F / d); } // Force / Displacement (menor distancia entre x1 e x2)| https://en.wikipedia.org/wiki/Displacement_(vector)

// ####### ELASTICIDADE E ETC:
double BulkMod(double P1, double P2, double p1, double p2) { return((P2 - P1)/ (- (p2 - p1) / p1)); } // P = pressure | p = density | change p (elasticity) to v if needed

// #####################################################################################################################################
// ######################################################## ACÚSTICA ########################################################
// #####################################################################################################################################
// https://en.wikipedia.org/wiki/List_of_equations_in_wave_theory

// #####################################################################################################################################
// ENVELOPES:
double Envelope(double Attack, double Decay, double t) { if (t < Attack) { return(t / Attack); } else { return(1.0 - ((t - Attack) / Decay)); } } // Mudar se achar algo melhor

// #####################################################################################################################################
// SOUND SPEED:
double SpeedSound(double BulkMod, double p) { return(sqrt(BulkMod / p)); } // BulkMods; p = density
double SpeedSoundLiq(double BulkMod, double p) { return(sqrt(BulkMod / p)); } // BulkMods; p = density | Same as above, but Bulk Mod. of the fluid
double SpeedSndAir(double BulkMod, double K) { return(sqrt(BulkMod / DensityAir(101325, 287.058, K))); } // BulkMods; P = pressure; K = Temperature in Kelvins;
double SpeedSndAir(double BulkMod, double Pa, double K) { return(sqrt(BulkMod / DensityAir(Pa, 287.058, K))); } // BulkMods; P = pressure; K = Temperature in Kelvins;
double SpeedSndAir(double BulkMod, double Pa, double K, double GasConst) { return(sqrt(BulkMod / DensityAir(Pa, GasConst, K))); } // BulkMods; P = pressure; K = Kelvin;
double SpeedSndDryAir(double Celsius) { return(331.3 + 0.606 * Celsius); } // Return in m/s
// https://en.wikipedia.org/wiki/Speed_of_sound#Speed_of_sound_in_solids // pw = P-Waves, primary waves; sw = S-Waves, secondary waves;
double SpeedSndSolidpwBulk(double Bulk, double Shear, double Density) { return(sqrt((Bulk + (1.333333333 * Shear)) / Density)); } // Bulk formula
double SpeedSndSolidpwYoung(double Young, double Poisson, double Density) { return((Young * (1 - Poisson)) / (Density * (1 + Poisson) * (1 - (2 * Poisson)))); } // Young formula
double SpeedSndSolidsw(double Shear, double Density) { return(sqrt(Shear / Density)); }
double SpeedSndSolid1d(double Young, double Density) { return(sqrt(Young / Density)); }
// The speed of sound in a plasma for the common case that the electrons are hotter than the ions(but not too much hotter) is given by the formula:
// mi the ion mass; Mu the ratio of ion mass to proton mass Mu = mi / mp; Te the electron temperature; Z the charge state; k Boltzmann constant; y the adiabatic index.
double SpeedSndPlasma(double mi, double Te, double Z, double k, double y) { return(pow((y * Z * Te) / mi, 0.5)); } // Return in m/s
double SpeedSndPlasma0(double Mu, double Te, double Z, double k, double y) { return((9.79 * pow(10, 3)) * pow((y * Z * Te) / Mu, 0.5)); } // Return in m/s
double SingleShotTime(double CapDist, double Time) { return(CapDist / Time); } // Time amount sound takes to be captured in CapDist (like a microphone) shows sound velocity

// #####################################################################################################################################
// SOUND INTENSITY:
double SoundIntpv(double p, double v) { return (p * v); } // p = Sound pressure; v = Particle velocity;
double SoundIntPA(double Watts, double Area) { return (Watts / Area); } // Watts / m^2
double SoundIntSph(double Watts, double r) { return(Watts / (4 * Pi * r * r)); } // Inverse-square law, for Spherical sound intensity, 4 * Pi * r^2 = surface area of a sphere
double SoundIntSph(double Newtons, double meters, double seconds, double r) { return(((Newtons * meters) / seconds) / (4 * Pi * r * r)); } // Watt / 4Pir^2 = (Joules / s) / 4Pir^2

// WAVE LENGTH (Lambda):
double WaveLgh(double v, double f) { return(v / f); } // v = Phase velocity; f = Frequency;

// SOUND PRESSURE:
double SoundPress(double I, double v) { return(I / v); }
double SoundPress(double Watts, double Area, double v) { return((Watts / Area) / v); }

// #####################################################################################################################################
// NON-STATIONARY WAVE FUNCTION:
// * Ver se isso não é o mesmo que "particle displacement" *
// https://brilliant.org/wiki/waves/
// Waves moving (non-stationary) have a disturbance that varies both with time 't' as the distance 'z' can be expressed mathematically as *Formula*
// where 'A(z, t)' is the amplitude envelope of the wave, 'k' is the wave number, and 'Phase' is the phase constant. The velocity 'v' of this wave is given by 'v = Omega / k';
double NonStatWaveFunc(double A, double z, double t, double k, double Omega, double Phase) { return(A * sin((k * z) - (Omega * t) + Phase)); } // SINE WAVE

// #####################################################################################################################################
// PARTICLE VELOCITY, SINE WAVE:
double PartVel(double Dist, double Watts, double t1, double t2, double Omega, double Wavenum, double Phase)
{
	double Ray = ConstSpeedSnd * t1;
	double Dispa = NonStatWaveFunc(SoundIntSph(Watts, Ray), Dist, t1, Wavenum, Omega, Phase); // Disp = Displacement, Time in seconds
	Ray = ConstSpeedSnd * t2;
	double Dispb = NonStatWaveFunc(SoundIntSph(Watts, Ray), Dist, t2, Wavenum, Omega, Phase);
	return (Derivative(Dispa, Dispb, t1, t2));
}

// #####################################################################################################################################
// ACOUSTIC WAVE EQUATION:
double AcoWavEq(double d2p, double dx2, double Bulk, double Pa, double K, double GasConst, double dt2)
{ return((d2p / dx2) - (1.0 / pow(SpeedSndAir(Bulk, Pa, K, GasConst), 2)) * (d2p / dt2)); }
double AcoWavEq(double d2p, double dx2, double Bulk, double K, double dt2)
{ return((d2p / dx2) - (1.0 / pow(SpeedSndAir(Bulk, 101325, K, 287.058), 2)) * (d2p / dt2)); }
double AcoWavEq(double d2p, double dx2, double dt2) { return((d2p / dx2) - (1.0 / pow(SpeedSndAir(101325, 101325, 288.15, 287.058), 2)) * (d2p / dt2)); }

// WAVE EQUATION:
double WaveEq(double x, double Omega)
{ double Limit = 1.0e-6; double Eq = (MiniForm(x + Limit, Omega) - 2 * MiniForm(x, Omega) + MiniForm(x - Limit, Omega)) / (Limit * Limit); return(Eq); }

// P-WAVE:
double PWave() { return(0); }

// PENDULUM:
double PendPeriSimple(double Lenght) { return(2 * Pi * sqrt(Lenght / 9.80665)); }

// SIMPLE HARMONIC OSCILLATION:
double SimpleHarmOsc(double Tht0, double T, double t, double phi) { return(Tht0 * cos(phi + ((2 * Pi) / T) * t)); }

// #####################################################################################################################################
// #####################
// ### MATRIZES:
// CRIA MATRIZ DERIVADA DE OUTRA MATRIZ:
vector<double> VecDeriv(vector<double> VecData, double dt)
{ vector<double> Derivatives; for (int n = 1; n < VecData.size(); ++n) { Derivatives.push_back((VecData[n] - VecData[n - 1]) / dt); } return(Derivatives); }

// CRIA MATRIZ DE UMA ONDA SENO:
// Distance in time, not space, how long it takes to end in 's'
vector<double> NonStatWaveVec(int VectorSize, double SndSpeed, double Distance, double Watts, double Wrto, double Wavenumber, double Omega, double Phase)
{
	vector<double> ThisVector;
	for (int tn = 0; tn < VectorSize; ++tn)
	{
		double tdiv = (1.0 * tn) / (VectorSize - 1);
		double t = Distance * tdiv;
		double y = NonStatWaveFunc(SndInt2db(SoundIntSph(Watts, t * SndSpeed)), Distance, t, Wavenumber, Omega, Phase);
		ThisVector.push_back(y);
		Watts *= Wrto;
	}
	return (ThisVector);
}

// CRIA MATRIZ DE INTENSIDADE DO SOM (ESFÉRA):
vector<double> SndIntSphVec(int Size, double Watts, double r, double WRto)
{
	double tWatts = Watts; // Ratio Watts, por enquanto não sei
	double dr = r / Size;
	vector<double> Ret;
	for (int n = 0; n <= Size; ++n)
	{
		tWatts *= WRto;
		Ret.push_back(SoundIntSph(tWatts, n * dr));
	}
	return Ret;
}

// #####################

// #####################################################################################################################################
// #####################
// ### CLASSES:
// #####################

// ##################################################################################################
// PARTICLE SYSTEM:
class PartSys2D
{
	enum OpForce { Explosion, Pull, Fuel };
	double Wx, Wy; // Distance from wall to wall, if there is no wall, the particle is destroyed
	double PrtBxx, PrtBxy; // Particles will spawn inside this box randomly
	bool WL, WR, WU, WD; // Wall left, right, up, down; Is there a wall?
	double mus, muk; // Frictions

	vector<Particle> Particles;
};

// ##################################################################################################
// FORCENET:
class ForceNet
{
public:
	vector<Force> Forces;
	vector<Friction> Frictions;
	Force FTotal; // Force that will be the sum of all Forces;
	
	void SumAll(int FrcIndx) // Sum all forces; Frictions[Friction Index], use '-1' to avoid friction;
	{
		Force Tot; Tot.Fx = 0; Tot.Fy = 0; Tot.N = 0;
		if (Forces.size() > 1)
		{
			for (int n = 1; n < Forces.size(); ++n)
			{
				Tot.Fx += Forces[n - 1].Fx + Forces[n].Fx;
				Tot.Fy += Forces[n - 1].Fy + Forces[n].Fy;
			}
		}
		else if (Forces.size() == 1) { Tot = Forces[0]; }
		if (FrcIndx >= 0 && FrcIndx < Frictions.size() && Forces.size() > 0)
		{
			if (Tot.N < Frictions[FrcIndx].mus) { Tot.N = 0; Tot.Fx = 0; Tot.Fy = 0; }
			else { Tot.N = Tot.N - Frictions[FrcIndx].muk; Tot.Fx = sqrt((Tot.N * Tot.N) - (Tot.Fy * Tot.Fy)); Tot.Fy = sqrt((Tot.N * Tot.N) - (Tot.Fx * Tot.Fx)); }
		}
		Tot.N = sqrt((Tot.Fx * Tot.Fx) + (Tot.Fy * Tot.Fy));
		Tot.Angle = LawSinAngle(Tot.Fx, Tot.Fy, 90);
		Tot.Accel = Tot.N / Tot.kg;
		FTotal = Tot; // !!!!!!! DONE !!!!!!!
	}
};

// ##################################################################################################
// WAVE OBJECT:
class AcousticWave
{
public:
	AcousticWave(double Freq, double Vel, double W, double Dist, int tVectorSize);
	double Frequency;
	double WaveLenght;
	double Pressure;
	double Omega; // Omega, radians per sec; Frequencia em termos musicais, 440hz é na verdade 440omega;
	double Velocity;
	double Wavenumber;
	double Distance;
	double VectorSize;
	double Watts;

	vector<double> WaveFunction;

	// ##################################################################################################
	// Mudar Tamanho da Onda:
	void ChangeWaveLenght(double NewNum)
	{
		Frequency = Velocity / NewNum; WaveLenght = Velocity / Frequency; Wavenumber = Tau / WaveLenght; Omega = Tau * Frequency;
		WaveFunction = NonStatWaveVec(VectorSize, Velocity, Distance, Watts, 1, Wavenumber, Omega, 0);
	}

	// Fazer vetor com razões por tempo:
	vector<double> MakeModVector(double Velr, double Freqr, double tPhase) // r = rate, if you leave as '1' it will not modulate, ex.: "tVel = Velocity * Velr".
	{
		vector<double> ThisVector;
		double tVel = Velocity, tWaven, tFreq = Frequency, tOmega;
		for (int tn = 0; tn < VectorSize; ++tn)
		{
			double tdiv = tn / (VectorSize - 1);
			double t = (Distance * tdiv);
			tPhase = (tPhase + tPhase) / 2.0; tVel *= Velr; tFreq *= Freqr;
			tOmega = Tau * tFreq; tWaven =  Tau / (tVel / tFreq);
			cout << tVel << " " << tFreq << " " << tOmega << " " << tWaven << endl;
			double y = NonStatWaveFunc(SndInt2db(SoundIntSph(Watts, t * tVel)), Distance, t, tWaven, tOmega, tPhase);
			ThisVector.push_back(y);
		}
		return (ThisVector);
	}
};

AcousticWave::AcousticWave(double Freq, double Vel, double W, double Dist, int tVectorSize)
{
	Frequency = Freq;
	Velocity = Vel;
	Distance = Dist;
	WaveLenght = Velocity / Frequency; // WaveLgh(Velocity, Frequency); Funtion for that.
	Wavenumber = Tau / WaveLenght;
	Omega = Tau * Frequency;
	Watts = W;
	VectorSize = tVectorSize;
	WaveFunction = NonStatWaveVec(VectorSize, Velocity, Distance, Watts, 1, Wavenumber, Omega, 0);
}

// ##################################################################################################
// FLUTE SYNTH:
class FluteSynth
{
public:
	FluteSynth(double Nwtn, double Ang, double Ang0, double Dist, double FlteSize, double Diamtr);
	double Size, Diameter, N, Angle, Angle0, MaxAng, Distance; // Size of the flute, Diameter, Newtons (change to watts, maybe?), Angles of blow, Distance of the mouth
	struct Hole { double Pos; bool Open; };
	vector<Hole> Holes;
	
};

FluteSynth::FluteSynth(double Nwtn, double Ang, double Ang0, double Dist, double FlteSize, double Diamtr)
{
	
}

// ##################################################################################################
// VELACELLNEWTON:
class VelAclNtnMntJlWt
{
public:

	VelAclNtnMntJlWt(double ms2, double kg, double OpForce, double Seconds, double CellSize);
	vector<double> Acell, Vel, Newton, Moment, Joule, Watt;
	vector<bool> SecMap;
	void ClearVectors()	{ vector<double> New; Acell = New; Vel = New; Newton = New; Moment = New; Joule = New; Watt = New; }
};

VelAclNtnMntJlWt::VelAclNtnMntJlWt(double ms2, double kg, double OpForce, double Seconds, double CellSize)
{
	if (CellSize < 1) { CellSize = 1; }
	CellSize = Seconds / CellSize;
	int Cnt = 1; // Conta quantas células do vetor se passaram, todo vetor começa com uma célula
	double NetF; // Esse objeto vai reduzir a força em ação pela de Oposição (OpForce)
	double SecFrac = 1 / Seconds; // Fração do total de segundos, resultando na razão de um segundo
	Vel.push_back(0);
	Moment.push_back(kg * Vel[0]);
	Acell.push_back(ms2);
	Newton.push_back(Acell[0] * kg);
	Joule.push_back(Newton[0] * (Vel[0] * CellSize));
	Watt.push_back(Joule[0] / CellSize);
	for (double n = CellSize; n < Seconds; n += CellSize)
	{
		Vel.push_back(Vel[Cnt - 1] + (Acell[Cnt - 1] * CellSize));
		Moment.push_back(kg * Vel[Cnt - 1]);
		if (Newton[Cnt - 1] >= -OpForce) { NetF = Newton[Cnt - 1] - (OpForce * CellSize); }	else { NetF = -OpForce; }
		Acell.push_back(NetF / kg);
		Newton.push_back(Acell[Cnt - 1] * kg);
		Joule.push_back(Newton[Cnt - 1] * (Vel[Cnt - 1] * CellSize));
		Watt.push_back(Joule[Cnt - 1] / CellSize);
		cout << "Vel: " << Vel[Cnt] << " | Acell: " << Acell[Cnt] << " | N: " << Newton[Cnt] << endl;
		++Cnt;
	}
}
// ##################################################################################################

// #####################
// ### FIM | CLASSES ###
// #####################
// #####################################################################################################################################

class TestPhis
{
public:
	void Test()
	{
		cout << "Digite qual função:\n";
		cout << "| 1 = Velocidade, Aceleração e Jerk |\n";
		cout << "| 2 = SoundIntSph | 3 = SoundIntPA | 4 = SoundIntPv |\n";
		cout << "| 4 = Kinetic Energy | 5 = Kinetic En. Momentum | 6 = Momentum |\n";
		cout << "| 7 = Density | 8 = Pressure  | 9 e 10 = NormForce |\n";
		cout << "| 11 = Stiffness | 12 = Bulk Modulus | 13 = Speed of Sound\n";
		cout << "| 14 = SpeedSndAir | 15 = Density Air | 16 = WaveEq |\n";
		cout << "| 17 = WaveLenght | 18 = Aco. Wave Eq.\n";
		int Op; cin >> Op;

		if (Op == 1)
		{
			cout << "f(x1, x2, t1, t2);\n"; double Opx1, Opx2, Opt1, Opt2; cout << "x1: "; cin >> Opx1; cout << "x2: "; cin >> Opx2;
			cout << "t1: "; cin >> Opt1; cout << "t2: "; cin >> Opt2; cout << "RETORNO: " << Derivative(Opx1, Opx2, Opt1, Opt2) << endl;
		}
		if (Op == 2)
		{
			cout << "SoundIntSph(Watts, r);\n"; double OpW, Opr; cout << "Watts: "; cin >> OpW; cout << "Radius: "; cin >> Opr;
			cout << "RETORNO: " << SoundIntSph(OpW, Opr) << " | DBs: " << SndInt2db(SoundIntSph(OpW, Opr)) << endl;
		}
		if (Op == 4)
		{ cout << "KineticEnrg(kg, ms);\n"; double Opm, Opv; cout << "kg: "; cin >> Opm; cout << "m/s: "; cin >> Opv; cout << "RETORNO: " << KineticEnrg(Opm, Opv) << endl;	}
		if (Op == 5)
		{ cout << "KineticEnMom(p, kg);\n"; double Opp, Opkg; cout << "p: "; cin >> Opp; cout << "kg: "; cin >> Opkg; cout << "RETORNO: " << KineticEnMom(Opp, Opkg) << endl; }
		if (Op == 6)
		{ cout << "Momentum(kg, ms);\n"; double Opkg, Opms; cout << "kg: "; cin >> Opkg; cout << "m/s: "; cin >> Opms; cout << "RETORNO: " << Momentum(Opkg, Opms) << endl; }
		if (Op == 7)
		{ cout << "Density(kg, Vol);\n"; double Opkg, OpVol; cout << "kg: "; cin >> Opkg; cout << "Vol: "; cin >> OpVol; cout << "RETORNO: " << Density(Opkg, OpVol) << endl; }
		if (Op == 8)
		{ cout << "Pressure(Force, Area);\n"; double OpF, OpA; cout << "F: "; cin >> OpF; cout << "Area: "; cin >> OpA; cout << "RETORNO: " << Pressure(OpF, OpA) << endl; }
		if (Op == 9) { cout << "NormForce(kg);\n"; double Opkg; cout << "kg: "; cin >> Opkg; cout << "RETORNO: " << NormForce(Opkg) << endl; }
		if (Op == 10)
		{ cout << "NormForce(p, kg);\n"; double Opp, Opkg; cout << "p: "; cin >> Opp; cout << "kg: "; cin >> Opkg; cout << "RETORNO: " << NormForce(Opp, Opkg) << endl;	}
		if (Op == 11)
		{ cout << "Stiffness(F, d);\n"; double OpF, Opd; cout << "F: "; cin >> OpF; cout << "Displacement: "; cin >> Opd; cout << "RETORNO: " << Stiffness(OpF, Opd) << endl;	}
		if (Op == 12)
		{
			cout << "BulkMod(P1, P2, p1, p2);\n"; double OpP1, OpP2, Opp1, Opp2; cout << "P1: "; cin >> OpP1; cout << "P2: "; cin >> OpP2;
			cout << "p1: "; cin >> Opp1; cout << "p2: "; cin >> Opp2; cout << "RETORNO: " << BulkMod(OpP1, OpP2, Opp1, Opp2) << endl;
		}
		if (Op == 13)
		{ cout << "SpeedSound(Bulk, p);\n"; double OpB, Opp; cout << "Bulk: "; cin >> OpB; cout << "p: "; cin >> Opp;	cout << "RETORNO: " << SpeedSound(OpB, Opp) << endl; }
		if (Op == 14)
		{
			cout << "SpeedSndAir(Bulk, Pa, GasConst, T);\n"; double OpB, OpPa, OpG, OpT; cout << "Bulk: "; cin >> OpB; cout << "Pa: "; cin >> OpPa;
			cout << "GasConst: "; cin >> OpG; cout << "Temp.: "; cin >> OpT; cout << "RETORNO: " << SpeedSndAir(OpB, OpPa, OpG, OpT) << endl;
		}
		if (Op == 15)
		{
			cout << "DensityAir(Pa, GasConst, K);\n"; double OpPa, OpG, OpK; cout << "Pa: "; cin >> OpPa; cout << "GasConst: "; cin >> OpG; cout << "Kelvins: "; cin >> OpK;
			cout << "RETORNO: " << DensityAir(OpPa, OpG, OpK) << endl;
		}
		if (Op == 16)
		{
			cout << "WaveEq(x, Omega);\n"; double Opx, OpF; cout << "x: "; cin >> Opx; cout << "Omega.: "; cin >> OpF;
			cout << "RETORNO: " << WaveEq(Opx, OpF) << endl;
		}
		if (Op == 17)
		{
			cout << "WaveLgh(v, f);\n"; double Opv, Opf; cout << "Phase Vel.: "; cin >> Opv; cout << "Freq.: "; cin >> Opf; cout << "RETORNO: " << WaveLgh(Opv, Opf) << endl;
		}
		if (Op == 18)
		{
			cout << "AcoWavEq(d2p, dx2, Bulk, Pa, K, GasConst, dt2);\n"; double Opd2p, Opdx2, OpB, OpPa, OpK, OpG, Opdt2;
			cout << "d^2p: "; cin >> Opd2p; cout << "dx^2.: "; cin >> Opdx2; cout << "Bulk: "; cin >> OpB; cout << "Pa: "; cin >> OpPa; cout << "Kelvins: "; cin >> OpK;
			cout << "Gas Const.: "; cin >> OpG; cout << "dt^2: "; cin >> Opdt2;
			cout << "RETORNO: " << AcoWavEq(Opd2p, Opdx2, OpB, OpPa, OpK, OpG, Opdt2) << endl;
		}
	}
};

// ################################################# FIM ####################################################################################

#endif // SCPARSE_
