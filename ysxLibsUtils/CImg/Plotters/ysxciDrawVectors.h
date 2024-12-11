#pragma once

#ifndef YSXCIDRAWVECTORS_H
#define YSXCIDRAWVECTORS_H

using namespace cimg_library;

// #####################
// ####### By Sophia Cristina
// ####### Things to plot using 'std::vector'!
// #####################

// !!! ATTENTION: Going to modify lot of these redundant functions. !!!

// ####################################################################################
// ####################################################################################
// ####################################################################################

// ######################################################################

// ############## VETORES:
// THREE VECTORS TO RGB:
std::vector<Point3D<double>> ysxCIMG_Vectors2RGB(std::vector<double> VecR, std::vector<double> VecG, std::vector<double> VecB)
{
	uint32_t Size = VecR.size(); std::vector<Point3D<double>> RGBs(Size); Point3D<double> RGB;
	if (VecR.size() == VecG.size() && VecG.size() == VecB.size())
	{
		for (size_t n = 0; n < Size; ++n)
		{ RGB.x = VecR[n] * 255; RGB.y = VecG[n] * 255; RGB.z = VecB[n] * 255; RGBs[n] = RGB; }
	}
	return(RGBs);
}

// ######################################################################

// PLOT VECTOR (LINE):
// Plot std::vector making a line from cell to cell:
CImg<uint8_t> ysxCIMG_DRAW_VectorLine(std::vector<double> V, int SegSize, uint8_t BG, uint8_t* C)
{
	uint32_t Size = V.size();
	double Max, Min; ysxVEC_MaxMinVec(V, Max, Min);
	double Absmx = 0, Absmn = 0;
	if (Max < 0) { Absmx = abs(Max); Max += Absmx; Min += Absmx; }
	if (Min < 0) { Absmn = abs(Min); Max += Absmn; Min += Absmn; }
	int MaxMin = ceil((Max + Min) * SegSize);
	
	CImg<uint8_t> Print(Size * SegSize, MaxMin, 1, 3, BG);

	for (size_t n = 1; n < Size; ++n)
	{ ysxCIMG_DRAW_Linexy(Print, (n - 1)  * SegSize, MaxMin - ((V[n - 1] + Absmn) * SegSize), n * SegSize, MaxMin - ((V[n] + Absmn) * SegSize), C); }

	return(Print);
}

CImg<uint8_t> ysxCIMG_DRAW_VectorPoint(std::vector<double> V, uint8_t BG, uint8_t* C)
{
	uint32_t Size = V.size();
	double Max, Min; ysxVEC_MaxMinVec(V, Max, Min);
	double Absmx = 0, Absmn = 0;
	if (Max < 0) { Absmx = abs(Max); Max += Absmx; Min += Absmx; }
	if (Min < 0) { Absmn = abs(Min); Max += Absmn; Min += Absmn; }
	int MaxMin = ceil(Max + Min); // Pixels
	
	CImg<uint8_t> Print(Size, MaxMin, 1, 3, BG);

	for (size_t n = 0; n < Size; ++n)
	{
		Print.draw_point(n, MaxMin - (V[n] + Absmn), C);
	}

	return(Print);
}

// ######################################################################

// Esse assume que o valor do vetor é a amplitude, então, faz uma linha em cada divisão de um circulo pelo size() de acordo com a amplitude:
// REDO IT!!!
CImg<uint8_t> ysxCIMG_DRAW_VectorPolygn(std::vector<double> V, uint8_t BG, bool Vertex, uint8_t* C = nullptr)
{
	uint32_t Sides = V.size();
	double x, y;	
	std::vector<Point<int>> xy(Sides); // Coordinates for image
	double rad, Cos, Sin, Div = TAU / Sides;
	int m = 0; // Counter
	uint8_t c[3]; // vertex

	double Max, Min; ysxVEC_MaxMinVec(V, Max, Min); // Pixels
	double Abs = 0;
	if (Max < 0) { Abs = abs(Max); Max += Abs; Min += Abs; }
	else if (Min < 0) { Abs = abs(Min); Max += Abs; Min += Abs; }
	int MaxMin = ceil(Max + Min);
	if (Min > 0) { MaxMin -= Min; }	if (Abs > 0) { for (int n = 0; n < Sides; ++n) { V[n] += Abs; } }

	// ####### COORDINATES:
	for (size_t n = 0; n < Sides; ++n)
	{
		rad = n * Div; Cos = (cos(rad) + 1) * 0.5; Sin = (sin(rad) + 1) * 0.5;
		x = Cos * V[n]; y = Sin * V[n];
		if (m < Sides) { xy[m].x = round(x); xy[m].y = MaxMin - round(y); } // Poem na matriz de coordenada
		++m;
	}
	CImg<uint8_t> Ret(MaxMin, MaxMin, 1, 3, BG); // IMAGE

	 // ####### PRINT:
	for (size_t ns = 1; ns < Sides; ++ns)
	{
		ysxCIMG_DRAW_Linexy(Ret, xy[ns - 1].x, xy[ns - 1].y, xy[ns].x, xy[ns].y, C); // LINES
		if (ns == Sides - 1) { ysxCIMG_DRAW_Linexy(Ret, xy[0].x, xy[0].y, xy[ns].x, xy[ns].y, C); } // LAST LINE
		if (Vertex) // VERTEXES
		{
			if (!C) { double Val = ns / Sides; ysxCOLOR_LinearRGB(Val, 1, 1, c); ysxCIMG_AddVert(Ret, xy[ns].x, xy[ns].y, 3, c); }
			else { ysxCIMG_AddVert(Ret, xy[ns].x, xy[ns].y, 3, C); }
			if (ns == 1) { c[0] = 255; c[1] = 0; c[2] = 0; ysxCIMG_AddVert(Ret, xy[0].x, xy[0].y, 3, c); }
		}
	}
	return(Ret);
}

// ######################################################################

// IMPRIME DADOS DE UM VETOR POR COLUNA:
// Soon to be obsolete, changed to the one with the img as input.
// Esse assume que cada pixel de uma imagem corresponde a um dx (PROVAVELMENTE IGUAL O SEM "Norm"):
// f[n] = y = V[n] * (sy / 255) | V[n] is based in '0 to 255':
// Ex.: f(x) = sin(x) * (512 / 255) = sin(x) * 2.007843 -> y;
template <class T_>
CImg<uint8_t> ysxCIMG_DRAW_VectorPointNorm(std::vector<T_>& V, uint32_t sy, double yrto = 1)
{
	uint32_t Size = V.size(); CImg<uint8_t> R(Size, sy, 1, 3, 0);
	//float Min = 0, Max = 0, Total = 0;
	float Max = 0;
	for (size_t n = 0; n < Size; ++n) { if (V[n] > Max) { Max = V[n]; } } //if (V[n] < Min) { Min = V[n]; } }
	//Min < 0 ? Total = fabs(Max) + fabs(Min) : Total = fabs(Max);
	float syd = sy / (double)(pow(256, sizeof(T_)) - 1);
	uint8_t C[3];

	for (size_t n = 0; n < Size; ++n)
	{
		if (std::is_floating_point<T_>::value)
		{
			ysxCOLOR_LinearRGB(V[n], 1, 1, C);
			R.draw_point(n, round(0.5 * sy - ((0.5 * yrto * sy * V[n]) / fabs(Max))), C);
		}
		else
		{
			ysxCOLOR_LinearRGB(V[n] / (double)(pow(256, sizeof(T_)) - 1), 1, 1, C);
			R.draw_point(n, round(sy - V[n] * syd * yrto), C);
		}
	}
	return (R);
}
template <class T_>
CImg<uint8_t> ysxCIMG_DRAW_VectorPointNorm(std::vector<T_>& V)
{
	uint32_t Size = V.size(); float Min = 0, Max = 0, Total;
	for (size_t n = 0; n < Size; ++n) { if (V[n] > Max) { Max = V[n]; } if (V[n] < Min) { Min = V[n]; } }
	Total = fabs(Max) + fabs(Min); // Shouldn't it be negative? 'Max - Min'?
	CImg<uint8_t> R(Size, ceil(Total), 1, 3, 0);
	uint8_t C[3];

	for (size_t n = 0; n < Size; ++n)
	{
		if (std::is_floating_point<T_>::value) { ysxCOLOR_LinearRGB(V[n], 1, 1, C); }
		else { ysxCOLOR_LinearRGB(V[n] / fabs(Max), 1, 1, C); }
		R.draw_point(n, round(Total - (V[n] - Min)), C);
	}
	return (R);
}

template <class T_>
CImg<uint8_t> ysxCIMG_DRAW_VectorPointNorm(std::vector<T_>& V, uint32_t sy, uint8_t* C, double yrto = 1)
{
	uint32_t Size = V.size(); CImg<uint8_t> R(Size, sy, 1, 3, 0);
	float syd = sy / (double)(pow(256, sizeof(T_)) - 1);
	double Max, Min; ysxVEC_MaxMinVecAbs(V, Max, Min);
	for (size_t n = 0; n < Size; ++n)
	{
		if (std::is_floating_point<T_>::value) { R.draw_point(n, round(0.5 * sy - ((0.5 * yrto * sy * V[n]) / Max)), C); }
		else { R.draw_point(n, round(sy - V[n] * syd * yrto), C); }		
	}
	return (R);
}

// ######################################################################

CImg<uint8_t> ysxCIMG_DRAW_VectorPointNormFill(std::vector<uint8_t>& V, uint32_t sy, double yrto = 1)
{
	uint32_t Size = V.size(); CImg<uint8_t> R(Size, sy, 1, 3, 0); uint8_t C[3];
	double ndiv, syd = sy / 255.0;
	for (size_t n = 0; n < Size; ++n)
	{
		ndiv = (double)n / (Size - 1);
		ysxCOLOR_LinearRGB(V[n] / 255.0, 1, 1, C);
		R.draw_line(n, sy, n, round(sy - V[n] * syd * yrto), C);
	}
	return (R);
}
CImg<uint8_t> ysxCIMG_DRAW_VectorPointNormFill(std::vector<double>& V, uint32_t sy, double yrto = 1)
{
	uint32_t Size = V.size(); CImg<uint8_t> R(Size, sy, 1, 3, 0); uint8_t C[3];
	double Max, Min; ysxVEC_MaxMinVecAbs(V, Max, Min);
	
	for (size_t n = 0; n < Size; ++n)
	{
		ysxCOLOR_LinearRGB(V[n], 1, 1, C);
		R.draw_line(n, sy * 0.5, n, round(0.5 * sy - ((0.5 * yrto * sy * V[n]) / Max)), C);
	}
	return (R);
}

// ######################################################################

void ysxCIMG_DRAW_VectorLineOnImg(CImg<uint8_t>& Img, std::vector<double>& V, double yrto = 1, uint8_t* C = nullptr)
{
	uint32_t Size = V.size(), sy = Img.height(), sx = Img.width();
	double Max, Min, sig0, sig1; ysxVEC_MaxMinVecAbs(V, Max, Min);
	double dx = sx / (double)Size;
	uint8_t c[3];
	uint16_t x0, y0, x1, y1;

	for (size_t n = 1; n < Size; ++n)
	{
		sig0 = (V[n - 1] / Max) * (sy * 0.5) * yrto; // SCALE
		sig1 = (V[n] / Max) * (sy * 0.5) * yrto;
		
		x0 = round((n - 1) * dx); // COORDINATES
		y0 = round(sy - (sig0 + sy * 0.5));
		x1 = round(n * dx);
		y1 = round(sy - (sig1 + sy * 0.5));

		if (y0 > sy) { y0 = sy; } if (y0 < 0) { y0 = 0; } if (y1 > sy) { y1 = sy; } if (y1 < 0) { y1 = 0; }
		if (x0 > sx) { x0 = sx; } if (x0 < 0) { x0 = 0; } if (x1 > sx) { x1 = sx; } if (x1 < 0) { x1 = 0; }
		
		if (!C) { ysxCOLOR_LinearRGB(V[n], 1, 1, c); ysxCIMG_DRAW_Linexy(Img, x0, y0, x1, y1, c); }
		else { ysxCOLOR_LinearRGB(V[n], 1, 1, c); ysxCIMG_DRAW_Linexy(Img, x0, y0, x1, y1, C); }
	}
}

void ysxCIMG_DRAW_VectorPointOnImg(CImg<uint8_t>& Img, std::vector<double>& V, double yrto = 1, uint8_t* C = nullptr)
{

	uint32_t Size = V.size(), sy = Img.height(), sx = Img.width(), x, y;
	uint8_t c[3];
	double Max, Min, Sig; ysxVEC_MaxMinVecAbs(V, Max, Min);
	double dx = sx / (double)Size;
	if (Max == 0) { Max = 1; }
	for (size_t n = 0; n < Size; ++n)
	{
		Sig = (V[n] / Max) * (sy * 0.5) * yrto;
		x = round(n * dx);
		y = round(sy - (Sig + sy * 0.5));
		if (y > sy) { y = sy; } if (y < 0) { y = 0; }
		if (x > sx) { x = sx; } if (x < 0) { x = 0; }
		if (!C) { ysxCOLOR_LinearRGB(V[n], 1, 1, c); Img.draw_point(x, y, c); }
		else { Img.draw_point(x, y, C); }
	}
}
void ysxCIMG_DRAW_VectorPtOnImgPolar(CImg<uint8_t>& Img, std::vector<double>& V, double Ratio, uint8_t* C = nullptr)
{
	uint32_t Size = V.size(), sy = Img.height(), sx = Img.width();
	double dx = sx / (double)Size;
	double t, Cos, Sin, xr = (sx * 0.5), yr = (sy * 0.5);
	uint8_t c[3]; uint16_t x, y;

	for (size_t n = 0; n < Size; ++n)
	{
		Cos = cos(TAU * n / Size) * V[n];
		Sin = sin(TAU * n / Size) * V[n];
		
		x = round(Cos * xr * Ratio + xr); y = round(sy - (Sin * yr * Ratio + yr));
		if (y > sy) { y = sy; } if (y < 0) { y = 0; }
		if (x > sx) { x = sx; } if (x < 0) { x = 0; }
		if (!C) { ysxCOLOR_LinearRGB((float)n / Size, 1, 1, c); Img.draw_point(x, y, c); }
		else { Img.draw_point(x, y, C); }
	}
}

// PLOT LINE BETWEEN POINTS IN A COORDINATE VECTOR:
CImg<uint8_t> ysxCIMG_DRAW_Points(std::vector<Point<int>> Coord, int SegSize, uint8_t BG, bool Abs, uint8_t* C = nullptr)
{
	Point<int> max, min;
	ysxVEC_MaxMinVecPoint(Coord, max, min, Abs);

	uint32_t sx = (max.x - min.x + 1) * SegSize, sy = (max.y - min.y + 1) * SegSize, Size = Coord.size();
	CImg<uint8_t> Print(sx, sy, 1, 3, BG);
	uint8_t c[] = { 255, 0, 0 };
	for (size_t n = 1; n < Size; ++n)
	{
		if (!C) { ysxCOLOR_LinearRGB((float)n / Size, 1, 1, c);
		ysxCIMG_DRAW_Linexy(Print, (Coord[n - 1].x - min.x) * SegSize, (Coord[n - 1].y - min.y) * SegSize,
			(Coord[n].x - min.x) * SegSize, (Coord[n].y - min.y) * SegSize, c);	}
		else { ysxCIMG_DRAW_Linexy(Print, (Coord[n - 1].x - min.x) * SegSize, (Coord[n - 1].y - min.y) * SegSize,
			(Coord[n].x - min.x) * SegSize, (Coord[n].y - min.y) * SegSize, C); }
	}

	return(Print);
}

// PLOT LINES IN A VECTOR BY USING THE 'ysxMath.h' OBJECT CALLED 'LinePoint':
CImg<uint8_t> ysxCIMG_DRAW_LinePoints(std::vector<LinePoint<int>> Coord, int SegSize, uint8_t BG, bool Abs, uint8_t* C = nullptr) // Testar para ver se esta tudo certo
{
	LinePoint<int> max, min;
	ysxVEC_MaxMinVecLinePoint(Coord, max, min, Abs);

	int sx = 0;
	if (max.P0.x > max.P1.x) { sx = (max.P0.x + 1) * SegSize; }
	else { sx = (max.P0.x + 1) * SegSize; }
	uint32_t sy = 0;
	if (max.P0.y > max.P1.y) { sy = (max.P0.y + 1) * SegSize; }
	else { sy = (max.P0.y + 1) * SegSize; }
	uint8_t c[3];

	CImg<uint8_t> Print(sx, sy, 1, 3, BG);
	for (size_t n = 0; n < Coord.size(); ++n)
	{
		if (!C)
		{
			ysxCOLOR_LinearRGB((float)n / Coord.size(), 1, 1, c);
			ysxCIMG_DRAW_Linexy(Print, Coord[n].P0.x * SegSize, Coord[n].P0.y * SegSize, Coord[n].P1.x * SegSize, Coord[n].P1.y * SegSize, c);
		}
		else { ysxCIMG_DRAW_Linexy(Print, Coord[n].P0.x * SegSize, Coord[n].P0.y * SegSize, Coord[n].P1.x * SegSize, Coord[n].P1.y * SegSize, C); }
	}
	return(Print);
}

// ######################################################################

// Imprime vetor como barras, tipo grafico estastistico: (LEMBRAR DE FAZER COM QUE SE NÃO TIVER VALOR NEGATIVO, USAR METADE DA IMAGEM!)
// Width é 'N * (Width + 2 * Border)'
CImg<uint8_t> ysxCIMG_DRAW_VectorBars(std::vector<double> V, int Width, double Ratio, int Borderx, int Bordery, bool xAxis)
{
	double Max, Min; bool Neg = false;
	ysxVEC_MaxMinVec(V, Max, Min); if (Min < 0) { Neg = true; } ysxVEC_MaxMinVecAbs(V, Max, Min);
	Max *= Ratio; Min *= Ratio;
	uint32_t Size = V.size(), Mid = 0;

	CImg<uint8_t> VecPrint; //std::vector<CImg<uint8_t>> Prints;
	if (Neg)
	{
		if (xAxis) { VecPrint = CImg<uint8_t>::CImg(Max + Min + 2 + Borderx * 2, (Width + Bordery) * Size, 1, 3, 0); }
		else { VecPrint = CImg<uint8_t>::CImg((Width + Bordery) * Size, Max + Min + 2 + Bordery * 2, 1, 3, 0); }
	}
	else
	{
		if (xAxis) { VecPrint = CImg<uint8_t>::CImg(Max + 2 + Borderx * 2 , (Width + Borderx) * Size, 1, 3, 0); }
		else { VecPrint = CImg<uint8_t>::CImg((Width + Borderx) * Size, Max + 2 + Bordery * 2, 1, 3, 0); }
	}

	if (Neg) { double NewMax, NewMin; ysxVEC_MaxMinVec(V, NewMax, NewMin); NewMin *= Ratio; if (xAxis) { Mid = round((NewMin * -1) + Borderx); } else { Mid = round((NewMin * -1) + Bordery); } }
	//else { if (xAxis) { Mid = VecPrint.width(); } else { Mid = VecPrint.height(); } }
	for (size_t n = 0; n < Size; ++n)
	{
		if (V[n] != 0)
		{
			if (xAxis)
			{
				if (V[n] >= 0) { VecPrint.draw_image(Mid, n * (Width + Bordery), ysxCIMG_ValueBarAbs(Width, V[n], Ratio, Borderx, Bordery, xAxis)); }
				else { VecPrint.draw_image(Mid + (V[n] * Ratio), n * (Width + Bordery), ysxCIMG_ValueBarAbs(Width, V[n], Ratio, Borderx, Bordery, xAxis)); } // + porque é "+ -", o que torna "-"
			}
			else
			{
				if (V[n] >= 0) { VecPrint.draw_image(n * (Width + Borderx), VecPrint.height() - (Mid + (V[n] * Ratio)), ysxCIMG_ValueBarAbs(Width, V[n], Ratio, Borderx, Bordery, xAxis)); }
				else { VecPrint.draw_image(n * (Width + Borderx), VecPrint.height() - Mid, ysxCIMG_ValueBarAbs(Width, V[n], Ratio, Borderx, Bordery, xAxis)); }
			}
		}
	}
	return (VecPrint);
}
CImg<uint8_t> ysxCIMG_DRAW_VectorBars(std::vector<double> V, int Width, double Ratio, int Borderx, int Bordery, bool xAxis, uint8_t* C)
{
	CImg<uint8_t> VecPrint;
	return (VecPrint);
}
CImg<uint8_t> ysxCIMG_DRAW_VectorBarsAbs(std::vector<double> V, int Width, double Ratio, int Borderx, int Bordery, bool xAxis)
{
	CImg<uint8_t> VecPrint;
	return (VecPrint);
}
CImg<uint8_t> ysxCIMG_DRAW_VectorBarsAbs(std::vector<double> V, int Width, double Ratio, int Borderx, int Bordery, bool xAxis, uint8_t* C)
{
	CImg<uint8_t> VecPrint;
	return (VecPrint);
}

// ############## IMAGENS INFO:

// IMAGENS DA MATRIZ DOS VETORES:
// Salva uma imagem 'x' por 'y' usando um vetor com o RGB em double '0 a 1.0':
template <class T_> CImg<uint8_t> ysxCIMG_DRAW_VectorImg(std::vector<Point3D<T_>>& V, uint16_t x, int16_t y, double Rsize = 1.0)
{
	uint32_t Size = V.size(); CImg<uint8_t> Ret(x, y, 1, 3, 0);
	uint8_t C[3];

	for (size_t n = 0; n < Size; ++n)
	{
		if (std::is_floating_point<T_>::value)	{ C[0] = V[n].x * 255; C[1] = V[n].y * 255; C[2] = V[n].z * 255; }
		else { C[0] = V[n].x % 255; C[1] = V[n].y % 255; C[2] = V[n].z % 255; }
		Ret.draw_point(n % x, floor((float)n / x), C);
	}
	if (Rsize != 1.0) { ysxCIMG_Resize(Ret, round(x * Rsize), round(y * Rsize), 6); }
	return(Ret);
}
template <class T_> CImg<uint8_t> ysxCIMG_DRAW_VectorImg(std::vector<Point3D<T_>>& V, double Rsize = 1.0)
{
	uint32_t Size = V.size(); double SqrtVec = sqrt(Size); uint16_t x = round(SqrtVec), y;
	if (SqrtVec / x == 1) { y = round(SqrtVec); } else { y = ceil(SqrtVec); }
	CImg<uint8_t> Ret(x, y, 1, 3, 0); uint8_t R, G, B, C[3];
	
	for (size_t n = 0; n < Size; ++n)
	{
		if (std::is_floating_point<T_>::value) { C[0] = V[n].x * 255; C[1] = V[n].y * 255; C[2] = V[n].z * 255; }
		else { C[0] = V[n].x % 255; C[1] = V[n].y % 255; C[2] = V[n].z % 255; }
		Ret.draw_point(n % x, floor((float)n / x), C);
	}
	if (Rsize != 1.0) { ysxCIMG_Resize(Ret, round(x * Rsize), round(y * Rsize), 6); }
	return(Ret);
}

// Salva uma Imagem com a cor sendo função de 'x' e 'y':
template <class T_> CImg<uint8_t> ysxCIMG_DRAW_VectorInfoLRGB(std::vector<T_>& V, double Rsize = 1.0)
{
	uint32_t Size = V.size(); double SqrtVec = sqrt(Size); uint16_t x = round(SqrtVec), y;
	if (SqrtVec / x == 1) { y = x; } else { y = ceil(SqrtVec); }
	CImg<uint8_t> R(x, y, 1, 3, 0); uint8_t C[3];

	for (size_t n = 0; n < Size; ++n)
	{
		if (std::is_floating_point<T_>::value) { ysxCOLOR_LinearRGB(V[n], 1.0, 1.0, C); }
		else { ysxCOLOR_LinearRGB(V[n] / (float)(pow(256, sizeof(T_)) - 1), 1.0, 1.0, C); }
		R.draw_point(n % x, floor((float)n / x), C);
	}
	if (Rsize != 1.0) { ysxCIMG_Resize(R, round(x * Rsize), round(y * Rsize), 6); }
	return(R);
}
template <class T_> CImg<uint8_t> ysxCIMG_DRAW_VectorInfoLRGB(std::vector<T_>& V, int x, double Rsize = 1.0)
{
	uint32_t Size = V.size();
	if (x > Size) { x = Size; } if (x < 1) { x = 1; }
	uint16_t y = ceil(Size / (x * 1.0));
	CImg<uint8_t> R(x, y, 1, 3, 0); uint8_t C[3];
	
	for (size_t n = 0; n < Size; ++n)
	{
		if (std::is_floating_point<T_>::value) { ysxCOLOR_LinearRGB(V[n], 1.0, 1.0, C); }
		else { ysxCOLOR_LinearRGB(V[n] / (float)(pow(256, sizeof(T_)) - 1), 1.0, 1.0, C); }
		R.draw_point(n % x, floor((float)n / x), C);
	}
	if (Rsize != 1.0) { ysxCIMG_Resize(R, round(x * Rsize), round(y * Rsize), 6); }
	return(R);
}
CImg<uint8_t> ysxCIMG_DRAW_VectorInfoLRGB(std::string& str, double Rsize = 1.0)
{
	uint32_t Size = str.size();
	double SqrtVec = sqrt(Size); uint16_t x = (uint16_t)round(SqrtVec), y;
	if (SqrtVec / x == 1) { y = x; } else { y = ceil(SqrtVec); }
	CImg<uint8_t> R(x, y, 1, 3, 0); uint8_t C[3];

	for (size_t n = 0; n < Size; ++n)
	{
		ysxCOLOR_LinearRGB(str[n] / 255.0, 1.0, 1.0, C);
		R.draw_point(n % x, floor((float)n / x), C);
	}

	if (Rsize != 1.0) { ysxCIMG_Resize(R, round(x * Rsize), round(y * Rsize), 6); }
	return(R);
}
CImg<uint8_t> ysxCIMG_DRAW_VectorInfoLRGB(std::string& str, int x, double Rsize = 1.0)
{
	uint32_t Size = str.size();
	if (x > Size) { x = Size; } if (x < 1) { x = 1; }
	uint16_t y = (uint16_t)ceil(Size / (x * 1.0));
	CImg<uint8_t> R(x, y, 1, 3, 0); uint8_t C[3];

	for (size_t n = 0; n < Size; ++n)
	{
		ysxCOLOR_LinearRGB(str[n] / 255.0, 1.0, 1.0, C);
		R.draw_point(n % x, floor((float)n / x), C);
	}

	if (Rsize != 1.0) { ysxCIMG_Resize(R, round(x * Rsize), round(y * Rsize), 6); }
	return(R);
}


// Salva uma Imagem com a cor sendo grayscale de '0' a '255':
CImg<uint8_t> ysxCIMG_DRAW_VectorInfo(std::vector<double> V, double Rsize = 1.0)
{
	uint32_t Size = V.size(); double SqrtVec = sqrt(Size);
	uint16_t x = (uint16_t)round(SqrtVec), y = (uint16_t)ceil(Size / (x * 1.0));
	CImg<uint8_t> R(x, y, 1, 3, 0); uint8_t C[3];
	if (SqrtVec / round(SqrtVec) == 1) { y = round(SqrtVec); }
	else { y = ceil(sqrt(Size)); }	
	
	for (size_t n = 0; n < Size; ++n)
	{
		if (V[n] > 1) { V[n] = 1; } if (V[n] < 0) { V[n] = 0; }
		C[0] = V[n] * 255; C[1] = V[n] * 255; C[2] = V[n] * 255;
		R.draw_point(n % x, floor((float)n / x), C);
	}

	if (Rsize != 1.0) { ysxCIMG_Resize(R, round(x * Rsize), round(y * Rsize), 6); }
	return(R);
}
CImg<uint8_t> ysxCIMG_DRAW_VectorInfo(std::vector<double> V, int x, double Rsize = 1.0)
{
	uint32_t Size = V.size(); double SqrtVec = sqrt(Size);
	if (x > Size) { x = Size; }	if (x < 1) { x = 1; }
	uint16_t y = ceil(Size / (x * 1.0));
	CImg<uint8_t> R(x, y, 1, 3, 0); uint8_t C[3];

	for (size_t n = 0; n < Size; ++n)
	{
		if (V[n] > 1) { V[n] = 1; } if (V[n] < 0) { V[n] = 0; }
		C[0] = V[n] * 255; C[1] = V[n] * 255; C[2] = V[n] * 255;
		R.draw_point(n % x, floor((float)n / x), C);
	}

	if (Rsize != 1.0) { ysxCIMG_Resize(R, round(x * Rsize), round(y * Rsize), 6); }
	return(R);
}

// Salva uma Imagem com a cor sendo função de 'y' dividido em 3 partes, de vermelho a azul:
CImg<uint8_t> ysxCIMG_DRAW_VectorInfoTriClr(std::vector<double> V, double Rsize = 1.0)
{
	uint32_t Size = V.size(); double SqrtVec = sqrt(Size);
	uint16_t x = (uint16_t)round(SqrtVec), y;
	if (SqrtVec / round(SqrtVec) == 1) { y = round(SqrtVec); }
	else { y = ceil(sqrt(Size)); }
	CImg<uint8_t> Ret(x, y, 1, 3, 0); uint8_t C[3];
	
	for (size_t n = 0; n < Size; ++n)
	{
		uint8_t R, G, B;
		if (abs(V[n]) < 0.333333) { R = 255; G = round((abs(V[n]) * 3) * 160); B = round((abs(V[n]) * 3) * 160); }
		else if (abs(V[n]) > 0.666667) { R = round(((abs(V[n]) - 0.666667) * 3) * 160); G = round(((abs(V[n]) - 0.666667) * 3) * 160); B = 255; }
		else { R = round(((abs(V[n]) - 0.33333) * 3) * 160); G = 255; B = round(((abs(V[n]) - 0.33333) * 3) * 160); }
		C[0] = R; C[1] = G; C[2] = B;
		Ret.draw_point(n % x, floor((float)n / x), C);
	}
	if (Rsize != 1.0) { ysxCIMG_Resize(Ret, round(x * Rsize), round(y * Rsize), 6); }
	return(Ret);
}

// Save file bytes as linear RGB (HUE):
// Salva uma Imagem com a cor sendo função de 'x' e 'y', Rsize = ysxCIMG_Resize:
CImg<uint8_t> ysxCIMG_DRAW_FileAsBMP(std::string Path, double Multiplier, double Rsize = 1.0)
{
	std::ifstream I(Path, std::ios::binary); // FILE
	I.seekg(0, std::ios::end); int End = I.tellg(); I.seekg(0, std::ios::beg);
	std::vector<uint8_t> V(End);
	if (I.is_open()) { I.read((char*)&V[0], End); } else { std::cout << "COULDN'T OPEN FILE!\n"; }
	//while (!I.eof()) { char c; I.read(&c, 1); V.push_back(c); std::cout << "CHAR: " << (int)c << " |\n"; } // Add this inside 'if' if you want to get char by char
	I.close();

	uint32_t Size = V.size(); double SqrtVec = sqrt(Size); // IMAGE
	uint16_t x = (uint16_t)round(SqrtVec), y;
	if (SqrtVec / x == 1) { y = x; } else { y = ceil(SqrtVec); }
	CImg<uint8_t> R(x, y, 1, 3, 0); uint8_t c[3];

	if (Size > 0)
	{
		for (size_t n = 0; n < Size; ++n)
		{
			ysxCOLOR_LinearRGB(((uint8_t)V[n] / 255.0) * Multiplier, 1.0, 1.0, c);
			R.draw_point(n % x, floor((float)n / x), c);
		}
		if (Rsize != 1.0) { ysxCIMG_Resize(R, round(x * Rsize), round(y * Rsize), 6); }
	}
	return(R);
}

// ############################################################################################################################################

// ############## COMPLEX:

// PRINT VECTOR OF COMPLEX NUMBER, EITHER REAL OR IMAGINARY:
CImg<uint8_t> ysxCIMG_DRAW_VectorComplexPointNorm(std::vector<std::complex<double>>& V, uint32_t sy, double yrto, bool RealImg = false)
{
	uint32_t Size = V.size(); CImg<uint8_t> R(Size, sy, 1, 3, 0);
	double Min = 0, Max = 0;
	
	if (RealImg)
	{ for (size_t n = 0; n < Size; ++n) { if (V[n].imag() > Max) { Max = V[n].imag(); } } }
	else
	{ for (size_t n = 0; n < Size; ++n) { if (V[n].real() > Max) { Max = V[n].real(); } } }

	double Tot = std::fabs(Max) < std::fabs(Min) ? std::fabs(Min) : std::fabs(Max);
	uint8_t C[3];

	for (size_t n = 0; n < Size; ++n)
	{
		if (RealImg)
		{
			ysxCOLOR_LinearRGB(V[n].imag(), 1, 1, C);
			R.draw_point(n, round(0.5 * sy - ((0.5 * yrto * sy * V[n].imag()) / Tot)), C);
		}
		else
		{
			ysxCOLOR_LinearRGB(V[n].real(), 1, 1, C);
			R.draw_point(n, round(0.5 * sy - ((0.5 * yrto * sy * V[n].real()) / Tot)), C);
		}
	}
	return (R);
}

// PRINT COMPLEX BASED ON MAGNITUDE:
CImg<uint8_t> ysxCIMG_DRAW_VectorComplexMagn(std::vector<std::complex<double>>& V, uint32_t sy, double yrto)
{
	uint32_t Size = V.size();
	double Min = 0, Max = 0;
	std::vector<double> Mag(Size);
	for (size_t n = 0; n < Size; ++n) // Get Magnitude and the Max of it:
	{
		Mag[n] = sqrt(V[n].real() * V[n].real() + V[n].imag() * V[n].imag());
		if (Mag.back() > Max) { Max = Mag.back(); } //std::cout << "Actual Max: " << Max << "\n"; }
	}

	CImg<uint8_t> R(Size, sy, 1, 3, 0);
	uint8_t C[3];

	for (size_t n = 0; n < Size; ++n)
	{
		ysxCOLOR_LinearRGB(Mag[n] / Max, 1, 1, C);
		R.draw_point(n, round(0.5 * sy - ((0.5 * yrto * sy * Mag[n]) / std::fabs(Max))), C);
	}
	return (R);
}

// PRINT POLAR OF A COMPLEX VECTOR:
CImg<uint8_t> ysxCIMG_DRAW_VectorComplexPolar(std::vector<std::complex<double>>& V, double Ratio, uint8_t* C = nullptr)
{
	uint32_t Size = V.size();
	double Minr = V[0].real(), Maxr = V[0].real();
	double Mini = V[0].imag(), Maxi = V[0].imag();

	for (size_t n = 0; n < Size; ++n)
   	{
	   	if (V[n].imag() > Maxi) { Maxi = V[n].imag(); } if (V[n].real() > Maxr) { Maxr = V[n].real(); }
	   	if (V[n].imag() < Mini) { Mini = V[n].imag(); } if (V[n].real() < Minr) { Minr = V[n].real(); }
   	}
	
	Minr *= Ratio; Maxr *= Ratio; Mini *= Ratio; Maxi *= Ratio;
	double Minrabs = Minr, Maxrabs = Maxr, Miniabs = Mini, Maxiabs = Maxi;
	if (Maxiabs < 0) { Miniabs += std::fabs(Maxiabs); Maxiabs = 0; }
	if (Miniabs < 0) { Maxiabs += std::fabs(Miniabs); Miniabs = 0; }
	if (Maxrabs < 0) { Minrabs += std::fabs(Maxrabs); Maxrabs = 0; }
	if (Minrabs < 0) { Maxrabs += std::fabs(Minrabs); Minrabs = 0; }

	CImg<uint8_t> R(Maxrabs - Minrabs, Maxiabs - Miniabs, 1, 3, 0);
	
	double x = 0, y = 0;

	for (size_t n = 0; n < Size; ++n)
	{
		if (Mini < 0) {	y = (Maxiabs - std::fabs(Mini)) - (Ratio * V[n].imag()); }
		else {	y = (Maxiabs - Mini) - (Ratio * V[n].imag() - Mini); }
		if (Minr < 0) {	x = (Maxrabs - std::fabs(Maxr)) + (Ratio * V[n].real()); }
		else {	x = (Maxrabs - Minr) - (Ratio * V[n].real() - Minr); }
				
		if (!C)
	   	{ uint8_t Clr[3]; ysxCOLOR_LinearRGB((V[n].real() + V[n].imag()) * 0.5, 1, 1, Clr); R.draw_point(x, y, Clr); }
		else { R.draw_point(x, y, C); }
	}
	return (R);
}
// ######################################################################
// ######################################################################
// ######################################################################

#endif // SCPARSE_
