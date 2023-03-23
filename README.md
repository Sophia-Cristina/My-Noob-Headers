# My-Noob-Headers
These are headers i made since i began to use c++.
Consequently, expect to find some utter noob coding from the first days i began messing with C++ mixed with things i'm doing currently.
I'm constantly messing up with the codes, so you may find lot of codes that aren't working because it is a W.I.P yet.

My philosophy for these headers are to maintain these pretty simple, that any noob can read and understand. I have been using this since i was super noob in c++ and i think it is pretty useful to use it in such way. I also used CImg as my first lib and i loved the fact it uses only header files and no aditional cpp files. I prefer this way.

This repository is made to share with friends, but feel free to enjoy whatever you can from it.


I love to do music and I began to learn programming because music. Since "music is math", I'm enjoying using c++ to make small silly programs to use in other softwares for music.


UPDATES:

! I translated some of my headers (which were in Brazilian Portuguese), and soon i'm going to make it all in english.

! Now i'm using templates. Hope i have not missed anything. It was also a pain to write "constexpr" in a lot of functions, wish people have taught about this since i began learning.

! Now headers have prefix for the type of code inside: "ysxCODETYPE_Something". Ex.: "ysxVEC_" for anything that uses "std::vector".

! It may work on Linux now with G++ if you use "fpermissive".

! Big change in the directories for better organization. When making more and more headers, i noticed i had to do it sooner or later and would be better to do it sooner.


##################################################################################################
##################### FOLDERS #####################


####### YSXDOS #######

  
It won't work in Visual Studio, i use this on Borland Turbo C in my DosBox.
  
I may change some objects to macros.
  

* cvector.h:
  
This is not mine, i forgot from where i got this header, but i got in Github somewhere.
  
The author forgot to add his name in the file, so i'm sorry for that dude! If you are the author, give me a hi (somehow)!
  
I got this because there is not "std::vector" in oldscholl c++. Anyway, you may need to skew it to work in my version of Turbo cpp.
  

* DOS.H:
  
This is not mine too, this is the header that comes with the Borland Turbo C IDE. I just added to this folder so i can use on Visual Studio.
  
You can't compile on Visual Studio, but at least the color codes and Intellisense works and help a lot, in my opinion. Way better than only stupid yellow text.
  

* YSXDCLK.HPP:
  
Pretty empty, but everything related to DOS clock.
  
Ex.: unsigned short* DOSClock = (unsigned short*)0x046C; // this points to the 18.2hz system clock
  
Maybe this example above should be made in macro.
  

* YSXDIMG.HPP:
  
VGA paiting related stuffs.
  

* YSXDOS.HPP:
  
Pretty empty for now. For now, it is only used to include other headers.
  

* YSXDVGA.HPP:
  
VGA related stuffs. Differently from 'YSXDIMG.HPP' that is used to paint and etc, this is about manipulating the hardware and serials.
  

* YSXDWAVE.HPP:
  
Useless for now, this is yet a copy-paste of my header to read '.wav' files.
  
However, i may update it to make it work on DOS OS.
  
I also may use it to generate audio, but probably i'm going to create a specific header for audio. Probably 'YSXDAUDIO.HPP'.
  

* YSXIMGPLOTTER.HPP:
  
Does not work yet. Copy-Paste of 'ysxciPlotters.h', however, i'm going to "port" it to DOS OS.

####### ysxComputer #######

  
Stands for ySPHAx Computer.
  
Regardless of the name computer, it stands for all headers based on emulating electronic components, ICs and other computer related stuffs like sorting algorithms and logic stuffs.
  

* Algorithms
* * ysxAlgos.h: Just a header to include all you need. I may add small things on it eventually (or not).
* * ysxSortSearch.h: The name says it all. Algorithms for sorting and searching. For now, there is only for sorting.

* Communications
* * ysxCommunications.h: Things related to communication. Morse, braile, barcode, qr-code and etc... This header probably will be used only to include other headers.
* * ysxQRCode.h: W.I.P, the name says it all.

* Emulation

There is lot of folders inside it for me to explain each one, the name of the folders should be self-explanatory.
You may find very useful documents, like, references or schematics.
The folder "MyFantasies" are fantasy systems i'm currently doing, for now i'm only trying to make a gaming console out of an Intel 4k4 using only compenents from below 1980 (unless i surrender and decide to jump a decade).

* * ysxEMU.h: Header to include other headers.
* * ysxEMUEdu.h: Emulation of educational stuffs related to computing, like my emulator of a WDR paper computer.
* * ysxEMUEsoLang.h: Emulation of esolang machines, or compiler.
* * ysxEMUHist.h: Historical computers, however, nothing here works yet.
* * ysxEMUICs.h: Emulating small and simple ICs, if the emulation gets complex, it is going inside "ICs" folder.
* * ysxEMULowLevel.h: Emulating small electronic components or contraptions. It also hosts the most important class for inheritance "ysxEMU_Component".
There is a DataBus class, flip-flops, counters and etc...

* Logic
* * ysxLogic.h: Related to logic gates and logic chores. Empty for now.
  

####### ysxCryp #######

* ysxCrypto.h: Cryptography algorithms. But i got bored and paused and i have still not finished it yet.

####### ysxData #######

  
Headers related to reading and writting binary files, ports, peripheral and protocols.
  
* Files

Some images to understand WAVE files.

* * ysxWAVE.h: I use this a lot. A class to manage ".wav" files. There is probably some vestiges of noobness here, the class is big.
* ysxBytes.h: Utils to manage bytes and bitwise stuffs
* ysxData.h: Ports, peripheral and protocols. Pretty empty for now...  

####### ysxDocuments #######

* ysxDoc.h: Empty. For documents organization, i'm going to use to make easy to for things like CSV files and etc.
* ysxPrintTxt.h: Print text to a ".txt" file or uses "std::cout". Lot of noobness here that i'm very lazy to fix. It prints a variety of information.
* ysxText.h: Manages text, like verify if a char is a number, convert text to an object and etc...

####### ysxElec #######

* ysxElecEmu.h: Same as "ysxEMU" stuffs, but tried to simulate it in an electrical level.
* ysxElectr.h: Same as "ysxEMULowLevel" stuffs, but tried to simulate it in an electrical level.

####### ysxLibsUtils #######

The name says it all. Would be hard to describe each folder and file.
However, these are headers to make simpler (or at least simpler to me) or in my style (OOP that loves classes).
It also contains algorithms to avoid making chore, for example, a class that creates a SDL window (with ifdef to change between SDL2 or 3) or to play audio in a simple way with SDL.
The headers i was using for making my colourful plots for CImg are all here now.


! ATTENTION: SDL is migratting to SDL3, i have never messed with SDL3, i just added some ifdef for it, but not sure if the code is working. I just changed the code so i could stop receiving compiler errors, lol... But i have not tested. Define "USE_SDL2" to avoid errors.

####### ysxMath #######
* GEO

Headers related to Geometry. The header names are intuitive.

* * ysxGEO.h: Include all other headers to avoid such chore. You should include this header, since the geometry headers are dependent of the trigonometric functions inside this header.
It also comes with a glossary so you can understand my naming convention.

* Physics
* * ysxPhys.h: Header related to physics... And I suck at physics, so, don't joke me for being noob at it.
Also, this header is one of the first headers i made. It is filled with nasty noobness and it is a pain to even watch it. You may extract good stuffs from it, like, acoustic waves, and the force class.

* ysxArith.: For arithmetic. Note, Fraction class is W.I.P.
* ysxCalc.h: Header to things related to calculus or alike.
* ysxConst.h: Constants macros.
* ysxConv.h: Converting... I want it to be international, i'm going to separate units by continents.
* ysxEucVector.h: Euclidean vector. Due to noobness of the time, i just made functions, i'll make a class with overloads in the future.
* ysxField.h: Field math, for now, there is only GaloisBase2. And i'm not even sure if it works correctly.
* ysxFractal.h: There is few ones here, ones that I made by the way (which doesn't works)... :p
But I pretend to fill this header one day, as I love fractals and I can make arts with it or even put on musics.  
This header was one of the first ones i made and it is filled with noobness and incomplete prototypes of fractals i tried to invent. I'm lazy to fix and it is a mine field. I also once made a maldebrot for C++, but i think i added to the "CImg" folder inside the "ysxLibsUtils" folder.
* ysxMath.h: The main file of this folder, it includes all other files and special STL headers dependencies.
* ysxMoney.h: Tools to deal with economy related maths. Pretty empty for now.
It have structures / classes for trading orders and i'll add trading indicators.
* ysxNumbers.h: Prime, fibonnaci sequence and etc...
* ysxPolyNom.h: For now, there is only a stupid quadratic function solver.
* ysxReedSolo.h: I think this is not working. But it is used to encode / decode a QR Code or other things i never touched.
* ysxSignal.h: Related to discrete time representation of signals. NOTE: It have the class "ysxSIG_Stream" that is inherited by my synths.
* ysxTable.h: Mathematical tables, it uses macros with scopes, ex.:
#define TWOPOWERS16B { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536 }.
* ysxTime.h: Things related to time, pretty empty, but it have ms converters or hours & minutes and etc. It also can cout a double in the format mm:ss.
* ysxVector.h: Functions to work with std::vector, not Euclidean Vectors. ATTENTION: I'll add this header to the folder ysxComputer/Algorithms. For now it is here because it was always here and i'm lazy to change old projects i made using it.

####### ysxMech #######

Related to mechanical things.

* ysxEngn.h: functions for engineering. For now it have only one function for the headloss of the grate of a culvert.
* ysxMechPieces.h: Semi-old header that i barely messed with, so it may be filled with trash, i don't even remember. But it is mechanical pieces, like gears.

####### ysxMusic #######

* SoundEngines
* * README MiniSENG Instruments.h: Header with a template so you can see how i set up the intruments to play my engine.
* * ysxMiniSEng.h: My mini sound engine that uses few bytes and i pretend to make it look more low-level, since one day i dream to make it into a real circuit board. And i hope it is as small as a watch screen.
* VST
* * ysxVST2.h: C cultists, get out! This is a header to mess with VST2 in an OOP way. I'm also not usin the convetion of "pointers to pointers", but instead using an array of pointers and a 2D array. It have a class that can load a VST, it is working. However, the editor window is not working yet, i just copy pasted a window (from Windows OS) code but i have not messed with it.
As the name says, it is not a class for VST3.

* ysxMusic.h: Functions normally used in music and related areas. 
Ex.: MIDI to Frequency.
It also have lot of converter for BPM, frequency, beat, time, samples and etc.
* ysxSynth.h: My synths... :3
It also have synths that use "ysxSIG_Stream", so it work in my sound engine.

####### ysxNeural #######

* ysxNeural.h: Don't even touch that shit, i made it based on a tutorial and i was super noob in c++ and super noob in Neural Network things. This header is a pain to read. Opening this file my hurt your eyes!

##################################################################################################

~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ 
