// TUTORIAL PARA NEURAL NET: https://youtu.be/KkwX7FkLfug
// https://vimeo.com/19569529

#pragma once

#ifndef YSXNEURAL_H
#define YSXNEURAL_H

#include "ysxmath.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <cassert>

// #################################################

vector<unsigned> Tplg; // Tplg = Topology

// #################################################
// ####### TRAINING DATA #######
// #################################################

// FAZER!

// #################################################
// #################################################
// #################################################

struct Connection {	double Weight, DeltaWeight; };

class Neuron;
typedef vector<Neuron> Layer;

// #################################################
// ####### NEURON #######
// #################################################

class Neuron
{
public:
	Neuron(unsigned OutputNum, unsigned tIndex);
	void SetOutput(double Val) { Output = Val; }
	double GetOutput() const { return Output; }
	double GetInput() const { return tInput; }
	void FF(const Layer &PrevLayer);
	void CalcOutGrads(double targetVal);
	void CalcHiddenGrads(const Layer &NextLayer);
	void UpdateInputWeights(Layer &PrevLayer);

	// Era Private:
	double SumDOW(const Layer &NextLayer) const;
	double Output;
	double tInput; // This Input, e não o do Net. | CORREÇÃO, VER ACIMA!
	vector<Connection> Weights;
	unsigned Index;
	double Gradient;

private:
	static double eta;   // [0.0..1.0] overall net training rate
	static double Alpha; // [0.0..n] multiplier of last weight change (momentum)
	static double Transfer(double x);
	static double TransferDeriv(double x);
	static double RandomWeight() { return rand() / double(RAND_MAX); }
};

// ###################################################################################################################################################

double Neuron::eta = 0.15;    // overall net learning rate, [0.0..1.0]
double Neuron::Alpha = 0.5;   // momentum, multiplier of last deltaWeight, [0.0..1.0]

void Neuron::UpdateInputWeights(Layer &PrevLayer)
{
	// The weights to be updated are in the Connection container
	// in the neurons in the preceding layer

	for (unsigned n = 0; n < PrevLayer.size(); ++n)
	{
		Neuron &Nrn = PrevLayer[n];
		double OldDeltaWeight = Nrn.Weights[Index].DeltaWeight;
		double NewDeltaWeight =	eta	* Nrn.GetOutput() * Gradient + Alpha * OldDeltaWeight;
		Nrn.Weights[Index].DeltaWeight = NewDeltaWeight;
		Nrn.Weights[Index].Weight += NewDeltaWeight;
	}
}

double Neuron::SumDOW(const Layer &NextLayer) const
{
	double Sum = 0.0;

	// Sum our contributions of the errors at the nodes we feed.
	for (unsigned n = 0; n < NextLayer.size() - 1; ++n)
	{
		Sum += Weights[n].Weight * NextLayer[n].Gradient;
	}

	return Sum;
}

void Neuron::CalcHiddenGrads(const Layer &NextLayer)
{
	double dow = SumDOW(NextLayer);
	Gradient = dow * Neuron::TransferDeriv(tInput); // CORREÇÃO
	//Gradient = dow * Neuron::TransferDeriv(Output);
}

void Neuron::CalcOutGrads(double targetVal)
{
	double Delta = targetVal - Output;
	Gradient = Delta * Neuron::TransferDeriv(tInput); // CORREÇÃO
	//Gradient = Delta * Neuron::TransferDeriv(Output);
}

double Neuron::Transfer(double x) {	return tanh(x); }

//double Neuron::TransferDeriv(double x) { return (1.0 - x * x); }
double Neuron::TransferDeriv(double x) { return (1.0 - tanh(x) * tanh(x)); } // CORREÇÃO, VER TOPO!

void Neuron::FF(const Layer &PrevLayer)
{
	double Sum = 0.0;

	// Sum the previous layer's outputs (which are our inputs)
	// Include the bias node from the previous layer.

	for (unsigned n = 0; n < PrevLayer.size(); ++n)
	{
		Sum += PrevLayer[n].GetOutput() *
			PrevLayer[n].Weights[Index].Weight;
	}

	tInput = Sum; // CORREÇÃO!
	Output = Neuron::Transfer(Sum);
}

Neuron::Neuron(unsigned OutputNum, unsigned tIndex)
{
	for (unsigned c = 0; c < OutputNum; ++c)
	{
		Weights.push_back(Connection());
		Weights.back().Weight = RandomWeight();
	}

	Index = tIndex;
}

// #################################################
// ####### NET #######
// #################################################

class Net
{
public:
	Net();
	void FF(const vector<double> &Inputs); // Feed Forward
	void BP(const vector<double> &Targets); // Back Propagation
	void GetResults(vector<double> &Results) const; // Get the "double Output" from all Neurons in the last Layer
	void GetHiddenOut(vector<double> &HiddenData) const; // Get "double Ouput" from all Neuron classes that is in a hidden Layer
	void GetHiddenIn(vector<double> &HiddenData) const; // Get "double tInput" from all Neuron classes that is in a hidden Layer
	void GetHiddenWeights(vector<double> &WeightsData) const; // Get all Weights from all Neurons in all Layers
	void GetNeuronWeights(vector<double> &WeightsData, int Neuronn, int Layern) const; // Get all Weights from a single Neuron in a Layer
	void GetNeuronsWeights(vector<double> &WeightsData, int Layern) const; // Get all Weights from all Neurons in a Layer
	void GetWeightsFromNeurons(vector<double> &WeightsData, int Layern, int Weightn) const; // Get a single Weight from a all Neurons in a Layer
	void GetWeightFromNeuron(vector<double> &WeightsData, int Neuronn, int Layern, int Weightn) const; // Get a single Weight from a single Neuron in a Layer
	void GetGrads(vector<double> &Vector, bool Pure) const; // Get "double Gradient" from all Neurons that from the second Layer and beyond
	double GetRecentAvrgError() const { return RecentAvrgError; }

	// Era private:
	vector<Layer> Layers; // Layers[LayerNum][NeuronNum]
	double Error;
	double RecentAvrgError;
	static double RecentAvrgErrorSmoothingFactor;
};

// ###################################################################################################################################################

typedef vector<Net> Nets; // Nets;

// ###################################################################################################################################################

double Net::RecentAvrgErrorSmoothingFactor = 100.0; // Number of training samples to average over

// ###################################################################################################################################################

void Net::GetResults(vector<double> &Results) const
{
	Results.clear();

	for (unsigned n = 0; n < Layers.back().size() - 1; ++n)
	{
		Results.push_back(Layers.back()[n].GetOutput());
	}
}

void Net::GetHiddenOut(vector<double> &HiddenData) const
{
	HiddenData.clear();
	for (int Hiddens = 1; Hiddens < Layers.size() - 1; ++Hiddens)
	{
		for (unsigned n = 0; n < Layers[Hiddens].size() - 1; ++n)
		{
			HiddenData.push_back(Layers[Hiddens][n].GetOutput());
		}
	}
}

void Net::GetHiddenIn(vector<double> &HiddenData) const
{
	HiddenData.clear();
	for (int Hiddens = 1; Hiddens < Layers.size() - 1; ++Hiddens)
	{
		for (unsigned n = 0; n < Layers[Hiddens].size() - 1; ++n)
		{
			HiddenData.push_back(Layers[Hiddens][n].GetInput());
		}
	}
}

void Net::GetHiddenWeights(vector<double> &WeightsData) const
{
	WeightsData.clear();

	for (unsigned n = 0; n < Layers.size(); ++n)
	{
		for (int m = 0; m < Layers[n].size(); ++m)
		{
			for (int k = 0; k < Layers[n][m].Weights.size(); ++k)
			{
				WeightsData.push_back(Layers[n][m].Weights[k].Weight);
			}
		}
	}
}

void Net::GetNeuronWeights(vector<double> &WeightsData, int Neuronn, int Layern) const
{
	WeightsData.clear();
	if (Layern < 0) { Layern = 0; } if (Layern > Layers.size() - 1) { Layern = Layers.size() - 1; }
	if (Neuronn < 0) { Neuronn = 0; } if (Neuronn > Layers[Layern].size() - 1) { Neuronn = Layers[Layern].size() - 1; }
	for (int n = 0; n < Layers[Layern][Neuronn].Weights.size(); ++n)
	{
		//cout << "LAYER: " << Layern << " | Neuronn: " << Neuronn << " | Pushing back!" << n << ": " << Layers[Layern][Neuronn].Weights[n].Weight << endl;
		WeightsData.push_back(Layers[Layern][Neuronn].Weights[n].Weight);
	}
}

void Net::GetNeuronsWeights(vector<double> &WeightsData, int Layern) const
{
	WeightsData.clear();
	if (Layern < 0) { Layern = 0; } if (Layern > Layers.size() - 1) { Layern = Layers.size() - 1; }

	for (int n = 0; n < Layers[Layern].size(); ++n)
	{
		for (int m = 0; m < Layers[Layern][n].Weights.size(); ++m)
		{
			WeightsData.push_back(Layers[Layern][n].Weights[m].Weight);
		}
	}
}

void Net::GetWeightsFromNeurons(vector<double> &WeightsData, int Layern, int Weightn) const
{
	WeightsData.clear();
	if (Layern < 0) { Layern = 0; } if (Layern > Layers.size() - 1) { Layern = Layers.size() - 1; }

	//for (int n = 0; n < Layers[Layern].size(); ++n)
	for (int n = 0; n < Layers[Layern].size() - 1; ++n)
	{
			WeightsData.push_back(Layers[Layern][n].Weights[Weightn].Weight);
	}
}

void Net::GetWeightFromNeuron(vector<double> &WeightsData, int Neuronn, int Layern, int Weightn) const
{
	WeightsData.clear();
	if (Layern < 0) { Layern = 0; } if (Layern > Layers.size() - 1) { Layern = Layers.size() - 1; }
	if (Neuronn < 0) { Neuronn = 0; } if (Neuronn > Layers[Layern].size() - 1) { Neuronn = Layers[Layern].size() - 1; }
	WeightsData.push_back(Layers[Layern][Neuronn].Weights[Weightn].Weight);
}

void Net::GetGrads(vector<double> &Vector, bool Pure) const
{
	Vector.clear();

	for (unsigned n = 1; n < Layers.size(); ++n)
	{
		for (int m = 0; m < Layers[n].size(); ++m)
		{
			if (Pure) {	Vector.push_back(Layers[n][m].Gradient); }
			else { Vector.push_back(((Layers[n][m].Gradient * 5) + 1.70) * 0.3); } // Para Imagem tem que ter valor 0.0 -> 1.0, essa formula ainda tem uns numeros tipo "-0.03";
		}
	}
}

// ###################################################################################################################################################

void Net::BP(const vector<double> &Targets)
{
	// Calculate overall net error (RMS of output neuron errors)

	Layer &OutputLayer = Layers.back();
	Error = 0.0;

	for (unsigned n = 0; n < OutputLayer.size() - 1; ++n)
	{
		double Delta = Targets[n] - OutputLayer[n].GetOutput();
		Error += Delta * Delta;
	}
	Error /= OutputLayer.size() - 1; // get average error squared
	Error = sqrt(Error); // RMS

	// Implement a recent average measurement

	RecentAvrgError = (RecentAvrgError * RecentAvrgErrorSmoothingFactor + Error) / (RecentAvrgErrorSmoothingFactor + 1.0);

	// Calculate output layer gradients

	for (unsigned n = 0; n < OutputLayer.size() - 1; ++n)
	{
		OutputLayer[n].CalcOutGrads(Targets[n]);
	}

	// Calculate hidden layer gradients

	for (unsigned Layern = Layers.size() - 2; Layern > 0; --Layern)
	{
		Layer &HiddenLayer = Layers[Layern];
		Layer &NextLayer = Layers[Layern + 1];

		for (unsigned n = 0; n < HiddenLayer.size(); ++n)
		{
			HiddenLayer[n].CalcHiddenGrads(NextLayer);
		}
	}

	// For all layers from outputs to first hidden layer,
	// update connection weights

	for (unsigned Layern = Layers.size() - 1; Layern > 0; --Layern)
	{
		Layer &Lrn = Layers[Layern];
		Layer &PrevLayer = Layers[Layern - 1];

		for (unsigned n = 0; n < Lrn.size() - 1; ++n)
		{
			Lrn[n].UpdateInputWeights(PrevLayer);
		}
	}
}

void Net::FF(const vector<double> &Inputs)
{
	assert(Inputs.size() == Layers[0].size() - 1);

	// Assign (latch) the input values into the input neurons
	for (unsigned i = 0; i < Inputs.size(); ++i)
	{
		Layers[0][i].SetOutput(Inputs[i]);
	}

	// forward propagate
	for (unsigned Layern = 1; Layern < Layers.size(); ++Layern)
	{
		Layer &PrevLayer = Layers[Layern - 1];
		for (unsigned n = 0; n < Layers[Layern].size() - 1; ++n)
		{
			Layers[Layern][n].FF(PrevLayer);
		}
	}
}

Net::Net()
{
	unsigned numLayers = Tplg.size();
	for (unsigned Layern = 0; Layern < numLayers; ++Layern)
	{
		Layers.push_back(Layer());
		unsigned OutputNum = Layern == Tplg.size() - 1 ? 0 : Tplg[Layern + 1];

		for (unsigned neuronNum = 0; neuronNum <= Tplg[Layern]; ++neuronNum)
		{
			Layers.back().push_back(Neuron(OutputNum, neuronNum));
		}

		// Force the bias node's output to 1.0 (it was the last neuron pushed in this layer):
		Layers.back().back().SetOutput(1.0);
	}
}
// #################################################
// ####### MODELOS NET #######
// #################################################

// #################################################
// ####### CONVOLUTIONAL NEURAL NET #######
// #################################################
/*
What a convolution layer does in depth:
A convolution layer consists of many kernels.These kernels (sometimes called convolution filters) present in the convolution layer,
learn local features present in an image(e.g.how the eye of a person looks like).
Such a local feature that a convolution layer learns is called a feature map. Then these features are convolved over the image.
This convolution operation will result in a matrix (that is sometimes called an activation map).
The activation map produces a high value at a given location, if the feature represented in the convolution filter is present at that location of the input.
*/

class CNN
{
public:
	vector<double> Inputs, FeatureMap, ActivationMap;
	vector<double> Kernel;
	vector<double> KernelMath(vector<double> Inputs, vector<double> Kernel) // Multiply kernel with inputs, then sum the kernel cells and give an output
	{
		vector<double> KernelRet;
		return(KernelRet);
	}


}
;



// #################################################
// ####### FUNÇÕES INFORMATIVAS #######
// #################################################

// COUT elementos de um vetor:
void ShowVectorVals(string Label, vector<double> &v) { cout << Label << " "; for (unsigned i = 0; i < v.size(); ++i) { cout << v[i] << " "; } cout << endl; }

// SAVE IMAGES:
// Salva uma imagem 'x' por 'y' baseado nos dados de um vetor:
void SaveVectorImg(vector<double> Vector, int x, int y, string Sufix, double Rsize)
{
	CImg<unsigned char> ResultImg(x, y, 1, 3, 0);
	int Countx = 0, County = 0;
	for (int n = 0; n < Vector.size(); n += 3)
	{
		int R = Vector[n] * 255;
		int G = Vector[n + 1] * 255;
		int B = Vector[n + 2] * 255;
		//cout << "R: " << R << " | G: " << G << " | B: " << B << " | x : " << Countx << " | y: " << County << endl;
		unsigned char Clr[] = { R, G, B };
		ResultImg.draw_point(Countx, County, Clr);
		++Countx;
		if (Countx == x) { Countx = 0; ++County; }
	}
	string str = "BMP\\ResultImg" + Sufix + ".bmp";
	if (Rsize != 1.0) { Resize(round(x * Rsize), round(y * Rsize), 6, ResultImg); }
	ResultImg.save_bmp(Str2Char(str).data());
}
// Salva uma Imagem com a cor sendo função de 'y':
void SaveVectorInfoLRGB(vector<double> Vector, string Sufix, double Rsize)
{
	double SqrtVec = sqrt(Vector.size());
	int x = round(SqrtVec);
	int y;
	if (SqrtVec / round(SqrtVec) == 1) { y = round(SqrtVec); }
	else { y = ceil(sqrt(Vector.size())); }
	CImg<unsigned char> ResultImg(x, y, 1, 3, 0);
	int Countx = 0, County = 0;
	for (int n = 0; n < Vector.size(); ++n)
	{
		int R, G, B;
		LinearRGB(Vector[n] * 0.833333, 1.0, 1.0, R, G, B, false);
		//cout << "R: " << R << " | G: " << G << " | B: " << B << " | x : " << Countx << " | y: " << County << endl;
		unsigned char Clr[] = { R, G, B };
		ResultImg.draw_point(Countx, County, Clr);
		++Countx;
		if (Countx == x) { Countx = 0; ++County; }
	}
	string str = "BMP\\ResultImg" + Sufix + ".bmp";
	if (Rsize != 1.0) { Resize(round(x * Rsize), round(y * Rsize), 6, ResultImg); }
	ResultImg.save_bmp(Str2Char(str).data());
}
// Salva uma Imagem com a cor sendo função de 'y' dividido em 3 partes, de vermelho a azul:
void SaveVectorInfoTriClr(vector<double> Vector, string Sufix, double Rsize)
{
	double SqrtVec = sqrt(Vector.size());
	int x = round(SqrtVec);
	int y;
	if (SqrtVec / round(SqrtVec) == 1) { y = round(SqrtVec); }
	else { y = ceil(sqrt(Vector.size())); }
	CImg<unsigned char> ResultImg(x, y, 1, 3, 0);
	int Countx = 0, County = 0;
	for (int n = 0; n < Vector.size(); ++n)
	{
		int R, G, B;
		if (Vector[n] < 0.333333333) { R = 255; G = round((Vector[n] * 3) * 160); B = round((Vector[n] * 3) * 160); }
		else if (Vector[n] > 0.666666667) { R = round(((Vector[n] - 0.666666667) * 3) * 160); G = round(((Vector[n] - 0.666666667) * 3) * 160); B = 255; }
		else { R = round(((Vector[n] - 0.33333333) * 3) * 160); G = 255; B = round(((Vector[n] - 0.33333333) * 3) * 160); }
		//cout << "R: " << R << " | G: " << G << " | B: " << B << " | x : " << Countx << " | y: " << County << endl;
		unsigned char Clr[] = { R, G, B };
		ResultImg.draw_point(Countx, County, Clr);
		++Countx;
		if (Countx == x) { Countx = 0; ++County; }
	}
	string str = "BMP\\ResultImg" + Sufix + ".bmp";
	if (Rsize != 1.0) { Resize(round(x * Rsize), round(y * Rsize), 6, ResultImg); }
	ResultImg.save_bmp(Str2Char(str).data());
}

// RETURN ACCURACY:
double ReturnAccuracy(vector<double> ResultsData, vector<double> TargetData)
{ double Acc = 0; int Count = 0; for (int n = 0; n < ResultsData.size(); ++n) { Acc += (ResultsData[n] + TargetData[n]) * 0.5; ++Count; } Acc /= Count * 1.0; return(Acc); }

// #################################################
// ####### SAVE NET #######
// #################################################

// FAZER!
// SALVA REDE EM UM TXT:
void SaveNet(Net NetSav)
{
	ofstream NetData("NetData.txt");
	for (int Ln = 0; Ln < NetSav.Layers.size(); ++Ln)
	{
		NetData << "Layer " << Ln << endl;

		// ####### Neuronios:
		for (int Nn = 0; Nn < NetSav.Layers[Ln].size(); ++Nn)
		{
			NetData << "Neuron " << Nn << endl;
			NetData << "Weights:\n";
			for (int Wn = 0; Wn < NetSav.Layers[Ln][Nn].Weights.size(); ++Wn)
			{
				NetData << NetSav.Layers[Ln][Nn].Weights[Wn].Weight;
			}
			NetData << "DeltaWeights:\n";
			for (int DWn = 0; DWn < NetSav.Layers[Ln][Nn].Weights.size(); ++DWn)
			{
				NetData << NetSav.Layers[Ln][Nn].Weights[DWn].DeltaWeight;
			}
			NetData << "Output "  << NetSav.Layers[Ln][Nn].Output << endl;
			NetData << "tInput "  << NetSav.Layers[Ln][Nn].tInput << endl;
			NetData << "Gradient " << NetSav.Layers[Ln][Nn].Gradient << endl;
		}

		NetData << "Error " << NetSav.Error << endl;
		NetData << "RecentAvrgError " << NetSav.RecentAvrgError << endl;
		NetData << "RecentAvrgErrorSmoothingFactor " << NetSav.RecentAvrgErrorSmoothingFactor << endl;

		// ####### Rede:
	}
	NetData.close();
}

// #################################################
// #################################################
// #################################################

// FIM!!!!!!!

// #################################################
// #################################################
// #################################################

#endif // SCPARSE_