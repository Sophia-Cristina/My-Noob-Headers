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

//struct PixelVGA { unsigned short x, y; unsigned char I; }; // coordinates 'x' and 'y' and then the palette index (256 colors)

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
void SetPalette(unsigned char TableWith768tems[768])
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

// ####################################################################################################################################################################################################
// ####################################################################################################################################################################################################
// ####################################################################################################################################################################################################

// #################################################
// ####### FILES #######
// #################################################

// Read my IBM (Indexed BitMap) file, please add suffix:
class IBMFile
{
public:
	FILE* fd;
	unsigned long End;
	unsigned int W;
	//fseek(0, 0L, SEEK_END);
	
	// #################################################

	IBMFile(char Path[254])
	{
		fd = fopen(Path, "rb"); fseek(fd, 0, SEEK_END); End = ftell(fd); fseek(fd, 0, SEEK_SET);
	}

	~IBMFile()
	{
		fclose(fd);
	}

	// #################################################

	PixelVGA* ReadIBMFileM1()
	{
		PixelVGA* R = new PixelVGA[(End - 2) / 5];
		if (fd != NULL)
		{
			char Read;

			fread(&Read, 1, 1, fd);
			cout << "READ CHAR: " << Read << " | INT: " << (int)Read << endl;
			if (Read == 'M')
			{
				fread(&Read, 1, 1, fd);
				if (Read == '1')
				{
					int n = 0;
					while ((int)ftell(fd) + sizeof(PixelVGA) < End)
					{
						PixelVGA P;

						fread(&P, sizeof(PixelVGA), 1, fd);
						R[n].x = P.x; R[n].y = P.y; R[n].I = P.I;
						++n;
					}
				}
				else { cout << "This function is for 'Mode = true'. The first two bytes from '.IBM' file must be written as ASCII 'M1' for this function.\n"; }
			}
			else { cout << "Can't read 'Mode'!\n"; }
		}
		else { cout << "ERROR OPENING FILE! 'fd' code: " << fd << endl; }

  		return(R);
	}

	// #################################################

	unsigned char* ReadIBMFileM0()
	{
		unsigned char* R = new unsigned char[End - 4];

		if (fd != NULL)
		{
			fread((char *)&R[0], 1, 1, fd);
			cout << "READ CHAR: " << (char)R[0] << " | INT: " << (int)R[0] << endl;
			if (R[0] == 'M')
			{
   				 cout << "READING MODE!\n";
				fread((char *)&R[1], 1, 1, fd);
    				cout << "READ CHAR: " << (char)R[1] << " | INT: " << (int)R[1] << endl;
				if (R[1] == '0')
				{
    					cout << "BEGIN READ!\n";
					fread((char*)&W, 2, 1, fd);
					cout << "WIDTH WAS READ!\n";
   
					 fread((char *)&R[2], End - 4, 1, fd);
   					 cout << " | R[2] = " << (int)R[2] << endl;
    					cout << "ENTIRE FILE WAS READ!\n";
				}
				else { cout << "This function is for 'Mode = false'. The first two bytes from '.IBM' file must be written as ASCII 'M0' for this function.\n"; }
			}
			else { cout << "Can't read 'Mode'!\n"; }
		}
		else { cout << "ERROR OPENING FILE! 'fd' code: " << fd << endl; }
		fclose(fd);
		return(R);
	}
	
	// #################################################
	
	void PrintIBMFileM0(VGAScreen& Screen)
	{
		unsigned char R;
	
		if (fd != NULL)
		{
			fread((char *)&R, 1, 1, fd);
			//cout << "READ CHAR: " << (char)R << " | INT: " << (int)R << endl;
			if ((char)R == 'M')
			{
				fread((char *)&R, 1, 1, fd);
				if ((char)R == '0')
				{
					fread((char*)&W, 2, 1, fd);
					unsigned int y = 0;
					for (unsigned long i = 0; i < End - 4; ++i)
					{
						fread((char*)&R, 1, 1, fd);
						if ((int)R != 0) { Screen.SetPixel(i % W, y, R); }
						if (i % 320 == 0) { ++y; }
					}
				}
				else { cout << "This function is for 'Mode = false'. The first two bytes from '.IBM' file must be written as ASCII 'M0' for this function.\n"; }
			}
			else { cout << "Can't read 'Mode'!\n"; }
		}
		else { cout << "ERROR OPENING FILE! Code: " << fd << endl; }
		fclose(fd);
	}


};

// ####################################################################################################################################################################################################
// ####################################################################################################################################################################################################
// ####################################################################################################################################################################################################

#endif // SCPARSE_