#pragma once

#ifndef YSXDIMG_H
#define YSXDIMG_H

#include "DOS.H"
#include <fstream.h> // Ignore error on Visual Studio

// #####################
// ####### By Sophia Cristina
// ####### Functions for VGA graphics
// #####################

// #################################################

// !!!!!!! THIS HEADER IS BASICALLY A COPY OF 'ysxCImg.h' ADDAPTED TO VGA !!!!!!!
// ** 'PixelVGA' is now a struct, if you got error, change the function 'PixelVGA' to 'PlotPixelVGA'

// #################################################
// ##############  ##############
// #######
// #######

struct PixelVGA { unsigned short x, y; unsigned char I; }; // coordinates 'x' and 'y' and then the palette index (256 colors)

// #######

unsigned char far* VGA = (unsigned char far*)0xA0000000L; // VGA Bitmap memory location, example, plotting a pixel: VGA[y * SCREEN_WIDTH + x] = color;
//unsigned char* VGA = (unsigned char *)0xA0000000L; // JUST SO VISUAL STUDIO DON'T GIVE ERROR, COMMENT ON TURBOC++
#define PaletteIndex = 0x3C8
#define PaletteData = 0x3C9

//#include "YSXDOS/YSXIMGPLOTTER.H"

// #################################################
// ####### PIXELS #######
// #################################################

// PLOT PIXEL:
void PlotPixelVGA(int x, int y, int ScreenWidth, unsigned char ColorIndex) { VGA[y * ScreenWidth + x] = ColorIndex; }

void PixelMode(int x, int y, unsigned char ColorIndex)
{
	union REGS regs;

	regs.h.ah = 0x0C; // BIOS function to plot pixel
	regs.h.al = ColorIndex;
	regs.x.cx = x;
	regs.x.dx = y;
	int86(0x10, &regs, &regs);
}

// #################################################
// ####### PALETTES #######
// #################################################

// Set a pallete with a table of size '256 * 3' (RGB):
void SetPalette(unsigned char* TableWith768tems)
{
	outp(0x3C8, 0);
	for (int i = 0; i < 768; ++i)
	{
		outp(0x3C9, TableWith768tems[i]);
	}
}

// PALETTE: Gradient from '0, 0, 255' to '255, 0, 127':
unsigned char* PALBlue2Pink()
{
	unsigned char P[768]; // '256' for '3' colors = '768' items
	// Each 'n' will look up for '3' colors, so it is '768 / 3' now. Since '255 * 3 = 765',
	// the other lines would break the point, so we end up with '256 - 2 = 254':
	for (int n = 0; n < 254; ++n)
	{
		P[n * 3] = n + 2; // R
		P[n * 3 + 1] = 0; // G
		P[n * 3 + 2] = 256 - ((n + 2) / 2); // B
	}
	//P = malloc(768);
	/*for (int n = 0; n < 300; ++n)
	{
		P[n * 3] = (n / 300.0) * 255; // R
		P[n * 3 + 1] = 0; // G
		P[n * 3 + 2] = 256 - ((n / 300.0) * 127); // B
	}*/
	unsigned char* Pt = P;
	return(Pt);
}

// #################################################
// ####### FILES #######
// #################################################

// Read my IBM (Indexed BitMap) file, please add suffix:
PixelVGA* ReadIBMFileM1(char Path[10])
{
	cout << "Path: ";
	for (int ASD = 0; ASD < 10; ++ASD) { cout << Path[ASD]; }
	cout << endl;
	FILE* fd = fopen("!IBMMM.IBM", "r"); // Ignore error, any problem use 'O_RDONLY'
	//ifstream I("!IBMMM.IBM");//, ios::in);

	//I.seekg(0, ios::end);
	//short int End = I.tellg(); cout << "END: " << End << endl;
	//I.seekg(0, ios::beg);

	//fseek(0, 0L, SEEK_END);
	fseek(fd, 0, SEEK_END);
	unsigned short End = ftell(fd); cout << "END: " << End << endl;
	fseek(fd, 0, SEEK_SET);

	PixelVGA* R = new PixelVGA[(End - 2) / 5];
	int NADA;

	//if (I.rdbuf()->is_open() != 0)
	//if (fd >= 0)
	if (fd != NULL)
	{
		cout << "If you are reading this, it is because the file was opened successfully!\nType anything... ";
		cin >> NADA;
		char Read;

		fread(&Read, 1, 1, fd);
		cout << "READ CHAR: " << Read << " | INT: " << (int)Read << endl;
		if (Read == 'M')
		{
			cout << "This letter should be 'M': " << Read << endl;
			fread(&Read, 1, 1, fd);
			if (Read == '1')
			{
				cout << "This number should be '1': " << Read << " | Write anything to continue!\n";
				cin >> NADA;
				int n = 0;
				while ((int)ftell(fd) + sizeof(PixelVGA) < End)
				{
					PixelVGA P;
					//I.read((char*)&P.x, sizeof(unsigned short));
					//I.read((char*)&P.y, sizeof(unsigned short));
					//I.read((char*)&P.I, sizeof(unsigned char));

					//fread(fd, &P, sizeof(PixelVGA));
					fread(&P, sizeof(PixelVGA), 1, fd);					
					R[n].x = P.x; R[n].y = P.y; R[n].I = P.I;
					cout << "R[" << n << "]" << " -> x: " << R[n].x << " | y: " << R[n].y << " | Index: " << (unsigned short)R[n].I << endl;
					cout << "P -> x: " << P.x << " | y: " << P.y << " | Index: " << (unsigned short)P.I << endl;
					++n;
				}
				cin >> NADA;
			}
			else { cout << "This function is for 'Mode = true'. The first two bytes from '.IBM' file must be written as ASCII 'M1' for this function.\n"; }
		}
		else { cout << "Can't read 'Mode'!\n"; }
	} else { cout << "ERROR OPENING, 'fd' code: " << fd << endl; }
	//I.close();
	fclose(fd);

	return(R);
}

// ###############################################################################################################################################################################
// ####### MAIN #################################################################################################################################################################
// ###############################################################################################################################################################################

#endif // SCPARSE_