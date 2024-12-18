﻿#pragma once

#ifndef YSXREEDSOLO_H
#define YSXREEDSOLO_H

#include <vector>

// ############################################################################################################################################
// ################################################# ANOTATIONS AND ALTERATIONS #################################################
//
// CHANGES (KEEP ORDER):
//
// ################################################# ANOTATIONS AND ALTERATIONS #################################################
// ############################################################################################################################################

// #####################################################################################################################################

// REED-SOLOMON ERROR CODE CLASS:
class ysx_ReedSolomon
{
public:
	uint8_t MSG_CNT = 3, POLY_CNT = 14;
	uint8_t msg_length, ecc_length;
	
	//std::vector<uint8_t> PolyNoms = std::vector<uint8_t>::vector(17);
	std::vector<uint8_t>* MSG; // ID_MSG_IN
	void NewMSG(std::vector<uint8_t>* New) { MSG = New; msg_length = MSG->size(); }
	//std::vector<uint8_t> MSGOUT; // ID_MSG_OUT
	std::vector<uint8_t>* ECC;
	void NewECC(std::vector<uint8_t>* New) { ECC = New; ecc_length = ECC->size(); }

	std::vector<uint8_t> GEN; // ID_GENERATOR
	std::vector<uint8_t> E; // ID_MSG_E

	std::vector<uint8_t> synd; // ID_SYNDROMES
	std::vector<uint8_t> forney; // ID_FORNEY

	std::vector<uint8_t> errata_loc; // ID_ERASURES_LOC
	std::vector<uint8_t> eloc; // ID_ERRORS_LOC

	std::vector<uint8_t> epos; // ID_ERASURES
	std::vector<uint8_t> err; // ID_ERRORS
		
	std::vector<uint8_t> c_pos; // ID_COEF_POS
	std::vector<uint8_t> e_eval; // ID_ERR_EVAL
	
	// #################################################

	ysxFIELD_GaloisBase2<uint8_t> GF; // GALOIS MATH

	// #################################################
	// #################################################
	// #################################################

	// Set vectors for field maths (care with size on src pointer):
	void Set(std::vector<uint8_t>& dest, uint8_t* src, uint8_t len, uint8_t offset = 0)
	{
		if (len <= dest.size() - offset) { memcpy(&dest[offset], src, len); } //length = len + offset;
	}

	// #################################################
	// #################################################
	// #################################################

	void GeneratorPoly()
	{
		GEN = { 1 }; //gen.size() = 1; // gen->at(0) = 1;

		std::vector<uint8_t> mulp = std::vector<uint8_t>::vector(2); //Poly* mulp = polynoms + ID_TPOLY1;
		//Poly* temp = polynoms + ID_TPOLY2;
		//mulp.size() = 2;

		for (uint16_t i = 0; i < ecc_length; ++i)
		{
			mulp[0] = 1;
			mulp[1] = GF.Pow(2, i);

			GEN = GF.PolyMult(GEN, mulp); // gen->Copy(temp);
		}
	}

	void CalcSyndromes()
	{
		synd = std::vector<uint8_t>::vector(ecc_length + 1);
		synd[0] = 0;
		for (uint8_t i = 1; i < ecc_length + 1; ++i)
		{
			synd[i] = GF.PolyEval(*MSG, GF.Pow(2, i - 1));
		}
	}

	// #################################################

	void FindErrataLocator(std::vector<uint8_t>* epos_ptr)
	{
		//Poly* errata_loc = &polynoms[ID_ERASURES_LOC];
		std::vector<uint8_t> mulp = std::vector<uint8_t>::vector(1); //Poly *mulp = &polynoms[ID_TPOLY1]; // mulp->size() = 1;
		std::vector<uint8_t> addp = std::vector<uint8_t>::vector(2); //Poly* addp = &polynoms[ID_TPOLY2]; // addp->size() = 2;
		std::vector<uint8_t> apol; //Poly* apol = &polynoms[ID_TPOLY3];
		
		errata_loc = { 1 };

		for (uint16_t i = 0; i < epos_ptr->size(); ++i)
		{
			mulp[0] = 1;
			addp[0] = GF.Pow(2, epos_ptr->at(i));
			addp[1] = 0;

			apol = GF.PolyAdd(mulp, addp);
			errata_loc = GF.PolyMult(errata_loc, apol); // errata_loc->Copy(temp);
		}
	}
	
	void FindErrorEvaluator(std::vector<uint8_t>* InSynd, std::vector<uint8_t>* InErrataLoc, std::vector<uint8_t>* dst, uint8_t ECCSize)
	{
		std::vector<uint8_t> mulp = GF.PolyMult(*InSynd, *InErrataLoc);
		std::vector<uint8_t> divisor = std::vector<uint8_t>::vector(ECCSize + 2); //Poly* divisor = &polynoms[ID_TPOLY2];
		divisor[0] = 1;
		*dst = GF.PolyDiv(mulp, divisor);
	}

	// #################################################
	// #################################################
	// #################################################

	void CorrectErrata(std::vector<uint8_t>* InSynd, std::vector<uint8_t>* err_pos, std::vector<uint8_t>* MSGOUT)
	{
		c_pos = std::vector<uint8_t>::vector(err_pos->size()); //Poly* c_pos = &polynoms[ID_COEF_POS];

		for (uint16_t i = 0; i < err_pos->size(); ++i) { c_pos[i] = MSG->size() - 1 - err_pos->at(i); }
		/* uses t_poly 1, 2, 3, 4 */
		FindErrataLocator(&c_pos);
		//Poly* errata_loc = &polynoms[ID_ERASURES_LOC];

		/* reversing syndromes */
		//Poly* rsynd = &polynoms[ID_TPOLY3]; //rsynd.size() = synd.size();
		std::vector<uint8_t> rsynd = std::vector<uint8_t>::vector(InSynd->size());
		for (uint8_t i = 0, j = InSynd->size() - 1; i < InSynd->size(); ++i, --j) { rsynd[j] = InSynd->at(i); }
		
		/* getting reversed error evaluator polynomial */
		std::vector<uint8_t> re_eval; //Poly* re_eval = &polynoms[ID_TPOLY4];
		
		/* uses T_POLY 1, 2 */
		FindErrorEvaluator(&rsynd, &errata_loc, &re_eval, errata_loc.size() - 1);
		
		/* reversing it back */
		e_eval = std::vector<uint8_t>::vector(re_eval.size()); //Poly* e_eval = &polynoms[ID_ERR_EVAL];
		for (uint8_t i = 0, j = re_eval.size() - 1; i < re_eval.size(); ++i, --j) { e_eval[j] = re_eval[i]; }
		
		std::vector<uint8_t> X; //Poly* X = &polynoms[ID_TPOLY1]; /* this will store errors positions */
		// X.size() = 0;

		short l;
		for (uint16_t i = 0; i < c_pos.size(); ++i)
		{
			l = 255 - c_pos[i];
			X.push_back(GF.Pow(2, -l));
		}
		
		// Magnitude polynomial
		// Shit just got real
		E = std::vector<uint8_t>::vector(MSG->size()); //Poly* E = &polynoms[ID_MSG_E]; E->Reset(); E.size() = msg_in.size();

		uint8_t Xi_inv;
		std::vector<uint8_t> err_loc_prime_temp; //Poly* err_loc_prime_temp = &polynoms[ID_TPOLY2];
		uint8_t err_loc_prime, y;
		
		for (uint16_t i = 0; i < X.size(); ++i)
		{
			Xi_inv = GF.Inverse(X[i]);

			err_loc_prime_temp = std::vector<uint8_t>::vector(); // err_loc_prime_temp.size() = 0;
			for (uint8_t j = 0; j < X.size(); j++)
			{
				if (j != i) { err_loc_prime_temp.push_back(GF.AddSub(1, GF.Mult(Xi_inv, X[j]))); }
			}

			err_loc_prime = 1;
			for (uint8_t j = 0; j < err_loc_prime_temp.size(); j++)
			{
				err_loc_prime = GF.Mult(err_loc_prime, err_loc_prime_temp[j]);
			}

			y = GF.PolyEval(re_eval, Xi_inv);
			y = GF.Mult(GF.Pow(X[i], 1), y);

			E[err_pos->at(i)] = GF.Div(y, err_loc_prime);
		}
		
		*MSGOUT = GF.PolyAdd(*MSG, E);
	}

	// #################################################
	// #################################################
	// #################################################
	// #################################################

	bool FindErrorLocator(std::vector<uint8_t>* InSynd, std::vector<uint8_t>* erase_loc = NULL, size_t erase_count = 0)
	{
		// eloc = Poly* error_loc = &polynoms[ID_ERRORS_LOC];
		std::vector<uint8_t> err_loc, old_loc, temp, temp2; //Poly* err_loc = &polynoms[ID_TPOLY1]; //Poly* old_loc = &polynoms[ID_TPOLY2];
		//Poly* temp = &polynoms[ID_TPOLY3];
		//Poly* temp2 = &polynoms[ID_TPOLY4];

		if (erase_loc != NULL) { err_loc = *erase_loc; old_loc = *erase_loc; }
		else { err_loc.push_back(1); old_loc.push_back(1); }

		uint8_t synd_shift = 0;
		if (InSynd->size() > ecc_length) { synd_shift = InSynd->size() - ecc_length; }

		uint8_t K = 0, delta = 0, index;

		for (uint16_t i = 0; i < ecc_length - erase_count; ++i)
		{
			if (erase_loc != NULL) { K = erase_count + i + synd_shift; }
			else { K = i + synd_shift; }

			delta = InSynd->at(K);
			for (uint8_t j = 1; j < err_loc.size(); j++)
			{
				index = err_loc.size() - j - 1;
				delta ^= GF.Mult(err_loc[index], InSynd->at(K - j));
			}

			old_loc.push_back(0);

			if (delta != 0)
			{
				if (old_loc.size() > err_loc.size())
				{
					temp = GF.PolyScale(old_loc, delta);
					old_loc = GF.PolyScale(err_loc, GF.Inverse(delta));
					err_loc = temp;
				}
				temp = GF.PolyScale(old_loc, delta);
				temp2 = GF.PolyAdd(err_loc, temp);
				err_loc = temp2;
			}
		}

		unsigned long shift = 0; while (err_loc.size() && err_loc[shift] == 0) { shift++; }

		unsigned long errs = err_loc.size() - shift - 1;
		if (((errs - erase_count) * 2 + erase_count) > ecc_length) { return false; } // Error count is greater then we can fix!

		eloc = std::vector<uint8_t>::vector(err_loc.size() - shift); // eloc.size() = (err_loc->size() - shift);
		memcpy(&eloc[0], &err_loc[shift], err_loc.size() - shift);
		
		return(true);
	}

	// FIND ERRORS:
	bool FindErrors(std::vector<uint8_t>* error_loc, size_t msg_in_size)
	{
		std::cout << "In finderrors\n";
		err = std::vector<uint8_t>::vector(); //Poly* err = &polynoms[ID_ERRORS]; // err->size() = 0;
		uint8_t errs = error_loc->size() - 1;
		std::cout << "errorloc size\n";
		for (uint16_t i = 0; i < msg_in_size; ++i)
		{
			if (GF.PolyEval(*error_loc, GF.Pow(2, i)) == 0) { err.push_back(msg_in_size - 1 - i); }
		}
		std::cout << "push backs\n";
		/* Sanity check:
		 * the number of err/errata positions found
		 * should be exactly the same as the length of the errata locator polynomial */
		if (err.size() != errs) { std::cout << "false\n"; return(false); }
		std::cout << "True\n";
		return(true);
	}

	void CalcForneySyndromes(std::vector<uint8_t>* InSynd, std::vector<uint8_t>* erasures_pos, size_t msg_in_size)
	{
		std::vector<uint8_t> erase_pos_reversed; //Poly* erase_pos_reversed = &polynoms[ID_TPOLY1]; // erase_pos_reversed->size() = 0;
		//Poly* forney_synd = &polynoms[ID_FORNEY];
		
		for (uint16_t i = 0; i < erasures_pos->size(); ++i)
		{
			erase_pos_reversed.push_back(msg_in_size - 1 - erasures_pos->at(i));
		}

		forney = std::vector<uint8_t>::vector(InSynd->size() - 1); //forney_synd->Reset();
		Set(forney, &InSynd->at(1), InSynd->size() - 1); //forney_synd->Set(InSynd->ptr() + 1, InSynd->size() - 1);

		uint8_t x;
		for (uint16_t i = 0; i < erasures_pos->size(); ++i)
		{
			x = GF.Pow(2, erase_pos_reversed[i]);
			for (int8_t j = 0; j < forney.size() - 1; j++) { forney[j] = GF.Mult(forney[j], x) ^ forney[j + 1];	}
		}
	}

	// #################################################
	// #################################################

	// ENCODE BLOCK:
	// Maybe reset your 'src', prefer to use native ECC from this class.
	// // Copying message to the output buffer
	// // memcpy(dst_ptr, src, msg_length * sizeof(uint8_t)); <- dst_ptr = dst
	void Encode()
	{
		//msg_length = src->size(); ecc_length = dst->size();
		if (msg_length + ecc_length < 255)
		{
			/* Generator cache, it dosn't change for one template parameters */
			//static uint8_t generator_cache[ecc_length + 1] = { 0 };
			//static bool    generator_cached = false;

			/* Allocating memory on stack for polynomials storage */
			//uint8_t stack_memory[MSG_CNT * msg_length + POLY_CNT * ecc_length * 2];
			//this->memory = stack_memory;

			//Poly* msg_in = &polynoms[ID_MSG_IN];
			//Poly* msg_out = &polynoms[ID_MSG_OUT];
			//Poly* gen = &polynoms[ID_GENERATOR];

			// Weird shit, but without reseting msg_in it simply doesn't work
			//msg_in->Reset();
			//msg_out->Reset();

			// Using cached generator or generating new one
			//if (generator_cached) {
			//gen->Set(generator_cache, sizeof(generator_cache));
			//}
			//else {
			GeneratorPoly();
				//memcpy(generator_cache, gen->ptr(), gen->size());
				//generator_cached = true;
			//}

			// Copying input message to internal polynomial
			//Set(*MSG, &src->at(0), msg_length); //msg_in->Set(src_ptr, msg_length);
			std::vector<uint8_t> MSGOUT = std::vector<uint8_t>::vector(msg_length + ecc_length); //msg_out->size() = msg_in->size() + ecc_length;
			Set(MSGOUT, &MSG->at(0), msg_length); //msg_out->Set(src_ptr, msg_length);
						
			// Here all the magic happens
			uint8_t coef = 0; // cache
			for (uint16_t i = 0; i < msg_length; ++i)
			{
				coef = MSGOUT[i];
				if (coef != 0)
				{
					for (uint32_t j = 1; j < GEN.size(); j++) { MSGOUT[i + j] ^= GF.Mult(GEN[j], coef); }
				}
			}
			
			// Copying ECC to the output buffer
			*ECC = std::vector<uint8_t>::vector(ecc_length);
			memcpy(&ECC->at(0), &MSGOUT[msg_length], ecc_length);
		}
	}

	// #################################################
	// #################################################
	// #################################################

	// DECODE:
	// In a github a guy used 'ecc' as 'src_ptr + msg_lenght', but i think it is for his method, i'm using vectors, so use ECC vector instead:
	int Decode(std::vector<uint8_t>* Corrected, std::vector<uint8_t>* erase_pos = NULL, size_t erase_count = 0)
	{
		//if (msg_length + ecc_length < 255)
		//{
			/*const uint8_t* src_ptr = (const uint8_t*)src;
			const uint8_t* ecc_ptr = (const uint8_t*)ecc;
			uint8_t* dst_ptr = (uint8_t*)dst;*/
			uint8_t src_len = msg_length + ecc_length;
			//const uint8_t dst_len = src->size();

			bool ok;

			//Poly* msg_in = &polynoms[ID_MSG_IN];
			//Poly* msg_out = &polynoms[ID_MSG_OUT];
			//Poly* epos = &polynoms[ID_ERASURES];

			// Copying message to polynomials memory
			//MSG = std::vector<uint8_t>::vector(msg_length + ecc_length);
			//ECC = *ecc; // talvez usar ele no input
			//Set(MSG, &src->at(0), msg_length);
			//Set(MSG, &ecc->at(0), ecc_length, msg_length);
			std::vector<uint8_t>MSGOUT = std::vector<uint8_t>::vector(src_len);
			Set(MSGOUT, &MSG->at(0), msg_length); // Copy
						
			// Copying known errors to polynomial
			if (erase_pos == NULL) { epos = std::vector<uint8_t>::vector(); }
			else
			{
				epos = std::vector<uint8_t>::vector(erase_count);
				Set(epos, &erase_pos->at(0), erase_count);
				for (uint16_t i = 0; i < epos.size(); ++i) { MSG->at(epos[i]) = 0; }
			}
			
			// Too many errors
			if (epos.size() > ecc_length) { return(1); }
			
			//Poly* synd = &polynoms[ID_SYNDROMES];
			//Poly* eloc = &polynoms[ID_ERRORS_LOC];
			std::vector<uint8_t> reloc; //Poly* reloc = &polynoms[ID_TPOLY1];
			//Poly* err = &polynoms[ID_ERRORS];
			//Poly* forney = &polynoms[ID_FORNEY];

			// Calculating syndrome
			CalcSyndromes();
			
			// Checking for errors
			bool has_errors = false;
			for (uint16_t i = 0; i < synd.size(); ++i) { if (synd[i] != 0) { has_errors = true; break; } }
			
			// Going to exit if no errors
			if (has_errors)
			{
				CalcForneySyndromes(&synd, &epos, src_len);
				FindErrorLocator(&forney, NULL, epos.size());
				// Reversing syndrome
				// TODO optimize through special Poly flag
				reloc = std::vector<uint8_t>::vector(eloc.size());
				for (uint8_t i = 0, j = eloc.size() - 1; i < eloc.size(); ++i, --j) { reloc[j] = eloc[i]; }
				// Fing errors
				ok = FindErrors(&reloc, src_len); if (!ok) { std::cout << "not ok\n"; return(1); }
				//ok = FindErrors(&reloc, msg_length); if (!ok) { std::cout << "not ok\n"; return(1); }
				for (int n = 0; n < MSGOUT.size(); ++n) { std::cout << "MSGOUT[" << n << "] = " << MSGOUT.at(n) << std::endl; }
				// Error happened while finding errors (so helpfull :D)
				if (err.size() == 0) { return(1); }

				/* Adding found errors with known */
				for (uint16_t i = 0; i < err.size(); ++i)
				{
					epos.push_back(err[i]);
				}
				
				// Correcting errors
				CorrectErrata(&synd, &epos, &MSGOUT); for (int n = 0; n < MSGOUT.size(); ++n) { std::cout << "MSGOUT[" << n << "] = " << MSGOUT.at(n) << std::endl; }
			}
			// Wrighting corrected message to output buffer
			// MSGOUT.size() = dst_len; // Trying to translate as:
			// const uint8_t dst_len = src->size();
			for (int n = 0; n < MSGOUT.size(); ++n) { std::cout << "ooooMSGOUT[" << n << "] = " << MSGOUT.at(n) << std::endl; }
			*Corrected = std::vector<uint8_t>::vector(msg_length); std::cout << "C.size(): " << Corrected->size() << std::endl;
			memcpy(&Corrected->at(0), &MSGOUT[0], msg_length);
			for (int n = 0; n < Corrected->size(); ++n) { std::cout << "C[" << n << "] = " << Corrected->at(n) << std::endl; }
		//}
		return(0);
	}

	// #################################################
	// #################################################
	// #################################################

	// Set your message vector (overwrite), pick a vector to buffer ECC (overwrite), set a vector to get your message out (overwrite):
	// * MSGOut is going to have ''.size()' = MSGIn + ECCIn', so you may need a vector with slots to start up this class *
	ysx_ReedSolomon(std::vector<uint8_t>* SetMSG, std::vector<uint8_t>* SetECC)
	{
		MSG = SetMSG; ECC = SetECC;		
		msg_length = SetMSG->size(); ecc_length = SetECC->size();
		uint8_t enc_len = msg_length + ecc_length;
		uint8_t poly_len = ecc_length * 2;
		// I use a ECC vector, so i may not need 'enc_len', in fact, it may give problems:
		 // polynoms[0].Init(ID_MSG_IN, offset, enc_len, memptr);
		//MSGOUT = std::vector<uint8_t>::vector(enc_len); // polynoms[1].Init(ID_MSG_OUT, offset, enc_len, memptr);
		//unsigned short offset = 0;

		/* Initialize first six polys manually cause their amount depends on template parameters */
		//offset += enc_len;
		GEN = std::vector<uint8_t>::vector(poly_len); // ID_GENERATOR // for (uint8_t i = ID_GENERATOR;
		// ! TEMPS REMOVED !
		// i < ID_MSG_E; ++i)
		E = std::vector<uint8_t>::vector(enc_len); // ID_MSG_E polynoms[5].Init(ID_MSG_E, offset, enc_len, memptr); offset += enc_len;
		synd = std::vector<uint8_t>::vector(poly_len); // ID_SYNDROMES // for (uint8_t i = ID_TPOLY3;
		forney = std::vector<uint8_t>::vector(poly_len); // ID_FORNEY
		errata_loc = std::vector<uint8_t>::vector(poly_len); // ID_ERASURES_LOC
		eloc = std::vector<uint8_t>::vector(poly_len); // ID_ERRORS_LOC
		epos = std::vector<uint8_t>::vector(poly_len); // ID_ERASURES
		err = std::vector<uint8_t>::vector(poly_len); // ID_ERRORS
		c_pos = std::vector<uint8_t>::vector(poly_len); // ID_COEF_POS
		e_eval = std::vector<uint8_t>::vector(poly_len); // ID_ERR_EVAL // i < ID_ERR_EVAL + 2; ++i)
		//offset += enc_len;
	}
	~ysx_ReedSolomon() { } // Dummy destructor, gcc-generated one crashes programm
};

// #####################################################################################################################################

// ################################################# FIM ####################################################################################

#endif // SCPARSE_