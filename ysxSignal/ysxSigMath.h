#pragma once

#ifndef YSXSIGMATH_H
#define YSXSIGMATH_H

// This is included by 'ysxSignal.h'.

// #####################
// ####### By Sophia Cristina
// ####### Signal maths.
// #####################

// #################################################

// !!! ATTENTION: Be sure that the size of these objects have the same numbers of voices and the same 'Size'.

// #####################
// ARITHMETIC:
// #####################


// ####### MATH BETWEEN SIGNALS #######

// /JOIN MULTIPLE SIGNALS (MAINTAIN AVERAGE GAIN):
template<class T_> class ysxSIG_MATH_AddSig : public ysxSIG_Stream<T_>
{
public:
	std::vector<ysxSIG_Stream<T_>*> Sigs;
	T_ y = 0;

	T_ IO(T_ x) override
	{
		size_t N = Sigs.size();
		if (N > 0)
		{
			for (size_t n = 0; n < N; ++n) { Sigs[n]->V = V; Sigs[n]->C[V] = C[V] % Sigs[n]->Size; y += Sigs[n]->IO(x); }
			y /= N;
		}
		return(y);
	}
};

// ADD MULTIPLE SIGNALS:
template<class T_> class ysxSIG_MATH_AddSig : public ysxSIG_Stream<T_>
{
public:
	std::vector<ysxSIG_Stream<T_>*> Sigs;
	T_ y = 0;

	T_ IO(T_ x) override
	{
		if (Sigs.size() > 0)
		{
			for (size_t n = 0; n < Sigs.size(); ++n) { Sigs[n]->V = V; Sigs[n]->C[V] = C[V] % Sigs[n]->Size; y += Sigs[n]->IO(x); }
		}
		return(y);
	}
};


// SUB MULTIPLE SIGNALS:
template<class T_> class ysxSIG_MATH_SubSig : public ysxSIG_Stream<T_>
{
public:
	std::vector<ysxSIG_Stream<T_>*> Sigs;
	T_ y = 0;

	T_ IO(T_ x) override
	{
		if (Sigs.size() > 0)
		{
			for (size_t n = 0; n < Sigs.size(); ++n) {  Sigs[n]->V = V; Sigs[n]->C[V] = C[V] % Sigs[n]->Size; y -= Sigs[n]->IO(x); }
		}
		return(y);
	}
};

// MULTIPLY MULTIPLE SIGNALS:
template<class T_> class ysxSIG_MATH_MultSig : public ysxSIG_Stream<T_>
{
public:
	std::vector<ysxSIG_Stream<T_>*> Sigs;
	T_ y = 0;

	T_ IO(T_ x) override
	{
		if (Sigs.size() > 0)
		{
			if (Sigs.size == 1)
			{
				return(Sigs[0]->IO(x));
			}
			else
			{
				y = Sigs[0]->IO(x);
				for (size_t n = 1; n < Sigs.size(); ++n)
				{
					Sigs[n]->V = V; Sigs[n]->C[V] = C[V] % Sigs[n]->Size;
					y *= Sigs[n]->IO(x);
				}
			}
			return(y);
		}
	}
};

// DIVIDE MULTIPLE SIGNALS (calls signal twice to avoid 'by zero division', 'Mult' is a faster way to divide):
template<class T_> class ysxSIG_MATH_DivSig : public ysxSIG_Stream<T_>
{
public:
	std::vector<ysxSIG_Stream<T_>*> Sigs;
	T_ y = 0;
	T_ Val = 0;

	T_ IO(T_ x) override
	{
		if (Sigs.size() > 0)
		{
			for (size_t n = 0; n < Sigs.size(); ++n)
			{
				Sigs[n]->V = V; Sigs[n]->C[V] = C[V] % Sigs[n]->Size;
				Val = Sigs[n]->IO(x);
				n == 0 ? y = Val : Val == 0 ? 0 : y /= Sigs[n]->IO(x);
			}
		}
		return(y);
	}
};

// POWER MULTIPLE SIGNALS:
template<class T_> class ysxSIG_MATH_PowSig : public ysxSIG_Stream<T_>
{
public:
	std::vector<ysxSIG_Stream<T_>*> Sigs;
	T_ y = 0;

	T_ IO(T_ x) override
	{
		if (Sigs.size() > 0)
		{
			for (size_t n = 0; n < Sigs.size(); ++n)
			{
				Sigs[n]->V = V; Sigs[n]->C[V] = C[V] % Sigs[n]->Size;
				n == 0 ? y = Sigs[n]->IO(x) : y = std::pow(y, Sigs[n]->IO(x));
			}
		}
		return(y);
	}
};

// ####### MATH WITH NUMBERS #######
// Classes here receive a Signal from a pointer and make an operation with a number from a pointer.

// ADD MULTIPLE A SIGNAL WITH A NUMBER:
template<class T_> class ysxSIG_MATH_AddNum : public ysxSIG_Stream<T_>
{
public:
	ysxSIG_Stream<T_>* Sig;
	T_* Num;
	T_ y = 0;

	T_ IO(T_ x) override
	{
		if (Sig && Num)
		{
			Sig->V = V; Sig->C[V] = C[V] % Sig->Size;
			y = Sig->IO(x) + *Num;
		}
		return(y);
	}
};


// SUB MULTIPLE SIGNALS:
template<class T_> class ysxSIG_MATH_SubNum : public ysxSIG_Stream<T_>
{
public:
	ysxSIG_Stream<T_>* Sig;
	T_* Num;
	T_ y = 0;

	T_ IO(T_ x) override
	{
		if (Sig && Num)
		{
			Sig->V = V; Sig->C[V] = C[V] % Sig->Size;
			y = Sig->IO(x) - *Num;
		}
		return(y);
	}
};

// MULTIPLY MULTIPLE SIGNALS:
template<class T_> class ysxSIG_MATH_MultNum : public ysxSIG_Stream<T_>
{
public:
	ysxSIG_Stream<T_>* Sig;
	T_* Num;
	T_ y = 0;

	T_ IO(T_ x) override
	{
		if (Sig && Num)
		{
			Sig->V = V; Sig->C[V] = C[V] % Sig->Size;
			y = Sig->IO(x) * *Num;
		}
		return(y);
	}
};

// DIVIDE MULTIPLE SIGNALS (calls signal twice to avoid 'by zero division', 'Mult' is a faster way to divide):
template<class T_> class ysxSIG_MATH_DivNum : public ysxSIG_Stream<T_>
{
public:
	ysxSIG_Stream<T_>* Sig;
	T_* Num;
	T_ y = 0;

	T_ IO(T_ x) override
	{

		if (Sig && Num)
		{
			Sig->V = V; Sig->C[V] = C[V] % Sig->Size;
			y = Sig->IO(x);
			*Num == 0 ? 0 : y /= *Num;
		}
		return(y);
	}
};

// POWER MULTIPLE SIGNALS:
template<class T_> class ysxSIG_MATH_PowNum : public ysxSIG_Stream<T_>
{
public:
	ysxSIG_Stream<T_>* Sig;
	T_* Num;
	T_ y = 0;

	T_ IO(T_ x) override
	{
		if (Sig && Num)
		{
			Sig->V = V; Sig->C[V] = C[V] % Sig->Size;
			y = Sig->IO(x);
			y = std::pow(y, *Num);
		}
		return(y);
	}
};

#endif
