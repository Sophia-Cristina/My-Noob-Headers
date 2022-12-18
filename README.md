# My-Noob-Headers
Those are headers i made since i began to use c++.

My philosophy for those headers are to maintain those pretty simple, that any noob can read and understand. I have been using this since i was super noob in c++ and i think it is pretty useful to use it in such way.

This repository is made to share with friends, but feel free to enjoy whatever you can with it.

There is nothing advanced and since I use those codes since the beginning of my programming journey, it have lot of rubbish that I'm lazy to fix.

I love to do music and I began to learn programming because music. Since "music is math", I'm enjoying using c++ to make small silly programs to use in other softwares for music.


UPDATES:

! I took the "using namespace std" from it, it now works correctly and won't have conflicts with other codes.

! I translated some of my header (which were in Brazilian Portuguese), and soon i'm going to make it all in english.

! Now i'm using templates. Hope i have not missed anything.

! Now headers have prefix for the type of code inside: "ysxCODETYPE_Something". Ex.: "ysxVEC_" for anything that uses "std::vector".



* ysxBytes.h:

Anything that i may use to operate objects by bytes or bits;

* ysxCImg.h:

Uses the header "CImg" (cimg.eu) to do useful things, some that uses other headers I made;
There is functions that "CImg" header already have, that the "CImg" header do better, but I used to learn;

* ysxDoc.h:

Almost empty file I found useful after I had to catalog stuffs, maybe it will become more useful by time;

* ysxMath.h:

A math header I made. I'm not a math pro, there is things I know is wrong on this file, yet, I'm either lazy to fix or i'm going to do it later.
I think it is useful enough already;
Don't joke me, at least I'm learning and trying... :p

* ysxNeural.h:

I saw a video on youtube that taugh how to do a very simple c++ neural net;
Long time I don't mess with this file, there is lot of rubbish, but enjoy it if you can...

* ysxPrint.h:

Print in ".txt" useful information. I use this to copy-paste stuffs or to add data to other kind of softwares...

* ysxText.h:

Pretty new, i made no good use for this yet.
The objective is to use functions to read text files and to generate std::string objects readable for human (not for bytes).
I'm going to delete the code that is in FOR NOW inside it because i'm going to move it to ysxplg/ysxMoney.h

* ysxWin.h:

To make simple to write programs that uses windows library.


##################################################################################################
##################### FOLDERS #####################


####### ysxplg #######


I should have named it ysxPlg, too lazy to fix it now...

It is basically header to "Plug" to some of my main headers.

Majority are included (#include) inside ysxMath.h.

This is what i consider the most important folder of this repository, so it is going to be the first i'm going to detail, the rest is going to be in alphabetical order.



* ysxCalc.h:

Header to things related to calculus or alike.


* ysxConst.h:

Constants. I changed from objects to macros...


* ysxConv.h:

Converting... I want it to be international, i'm going to separate units by continents.

Some codes here used to be on ysxCalc.h.


* ysxElectr.h:

To simulate electronic devices or electronic signals (using std::vector<double> as discrete time samples).
  
I'm made a class called "Component" and "Wire", those may be use to simulate REAL electronic equipments.
  
I have intention to be able to simulate ANY electronic device, from resistors to processors.
  
It may have "Component" inhered from ysxEMU.h (folder: ysxComp).


* ysxFractal.h:
  
Fractals... There is few ones there, ones that I made by the way (which don't works)... :p
  
But I pretend to fill this header one day, as I love fractals and I can make arts with it or even put on musics.
  
Long time i don't use it, so there may be lot of rubbish code.


* ysxGeo.h:
  
Header related to Geometry;

  
* ysxMoney.h:
  
Tools to deal with economic related maths.
  
Pretty empty for now, and nothing working.
  

* ysxMusic.h:
  
Functions normally used in music and related areas.
  
Ex.: MIDI to Frequency.
  

* ysxPhys.h:
  
Header related to physics... And I suck at physics, so, don't joke me for being noob at it.

  
* ysxSignal.h:

Related to discrete time representation of signals.
  

* ysxVector.h:
  
Functions to work with std::vector, not Euclidean Vectors.
  

####### ysxCImgIncludes #######

  
'ysxCImg.h' header was becoming too big, and then i separated the code by areas.

  
  
* ysxciColors.h:
  
Self-explanatory, it mess with color related functions, like, hue (Linear RGB, no gamut YET, since i do pretend to learn all those crazy color math).

  
* ysxciMisc.h:
  
Pretty empty right now, but i made it after i made a program which needed a function and i thought that would be cool that this function was included in other CImg projects that i may use later.
  

* ysxciPlotters.h:
  
Self-explanatory, and maybe my most important CImg header... At least i use those functions A LOT!
  
Needs translations.
  
Since Bresenham lines to Polar and Cartesian plots.
  
Some of those functions are already disponible by CImg (and the native CImg codes work faster), but i wanted to learn and have more control of it.
  

* ysxciUtils.h:
  
You may be asking, why do you have a "misc" and a "utils" header?!
  
Well, misc is kinda abstract, utils are tools we normally use in images when we use softwares like photoshop or ms paint.
  
Things like 'Fill', 'Resize' and etc...
  

####### ysxComp #######

  
Stands for ySPHAx Computer.
  
I'm going to use my "Component" class to simulate computer devices, like, integrated circuits.
  
But it is not only "Component" objects, there is going to have classes to emulate certain computer devices.
  
There are PDFs and other stuffs on the folder for reference.
  

  
* ysxEMU.h:
  
"Component" and emulation classes, this is going to be my main class for that, probably i'm going to separate the codes inside it later in other headers.

  
* ysxALU.h:
  
Same thing as 'ysxEMU.h', but focused on ALU electronic components. Empty for now.

  
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
  

####### ysxFiles #######

  
Header related to reading and writting binary files.
  
I'm going to delete the file in the folder "utils", i'm using as a learning resource.
  
There are some reference files.
  

  
* MyWAVEGuide.cpp:
  
Stupid file for noobs to understand '.wav' header, you may find and test it here:
  
https://www.onlinegdb.com/HyavW4JBD
  
It is not optimal, however, a learning tool. '.wav' is one of the easiet binary files to read, so it is a good introduction to binary files reading / writting.
  

* ysxBMP.h:
  
Pretty empty header. Going to use it in the future for reding '.bmp' files.

  
* ysxFileInspec.h:
  
Tools related to binary file reading / writting. Like getting a buffer and etc...

  
* ysxMIDI.h:
  
W.I.P... Self-explanatory, read / write '.mid' files, which uses the communication protocol called MIDI.
  
https://en.wikipedia.org/wiki/MIDI
  
"Musical Instrument Digital Interface".
  

* ysxnes.h:
  
Empty file. Going to use in the future to hack the binary data inside nes ROM image files.
  

* ysxWAVE.h:
  
'.wav' write and read. I need to clean some noob old codes...
  

####### ysxGen #######

  
Going to add header to manipulate Genesis / Mega-Drive ROM Images.

  
  
* ysxGenROM.h:
  
For now it have only a 68k map, z80 map and a class to get the ROM header (however, this class is going to receive codes to manipulate and hack ROM images).
  

####### ysxMusic #######

  
I may add the header 'ysxMusic.h' inside 'ysxplg' folder in this folder.
  
I dislike my old and noob approach in the formatting of the code for some music related stuffs here, so i may change A LOT the headers inside this folder.
  

  
* ysxJUCE.h:
  
I'm going to remove this header from this folder. Those are functions i intended to use for UI in the making of VSTs. But since those may be used in any UI in any application i make in JUCE, i'm going to add it somewhere else.
  
However, i can't pay for JUCE license, so i'm thinking about abandoning JUCE and learn something else. In the future i may use it for VST (probably only personal projects). But for audio, i may use other free or open-source tools.
  

* ysxmPattern.h:
  
Pattern normally are references to music's bar ( https://en.wikipedia.org/wiki/Bar_(music) ), however, in computer they are normally under a standard.
  
Since i use Renoise (DAW) and Max/MSP (visual programming), the codes are made based on those, however, may work in any tool.
  
I was pretty noob in c++ when i made this, so, there is a lot to fix and i'm trully lazy.
  
However, i'm going to be forced to fix those, since i do music.
  

* ysxmSaveVector.h:
  
This suffers from the same "i was noob in c++" problem. There is a lot to fix, oh, shit...
  
I totally dislike the codes here, but i may need some of the stuffs here.
  
I began this header for a specific project to write text for the object "coll" (object that reads '.txt' file and operates by line, comma and semi-colon) and "message" in Max/MSP. It may be compatible with PureData.
  

* ysxSDLAudio.h:
  
Audio DSP related stuffs... You may open and play "any" buffer using a class.
  
!!! Here comes a little rant from me. Whenever i search for tutorials to mess up with audio and etc, THERE IS NO FUCKING INFORMATION! Wtf, i hate this in the programming community! Lot of things that should be simple have absolutely no information. Windows API for audio? YEAH! GOOD FUCKING LUCKY finding simple tutorials online, you are going to have to read 3000000000000 lines of useless information in the microsoft documentation website to learn (not complaining about the ammount of lines, because it is pretty clear about every function and etc, but if you want a simple approach, it is a pain in the ass that you have to read lot of things you don't need 'for now' jsut to make some noise). Asking for help? Stackoverflow? "gEt JUCE dUdE", ok, and how JUCE programmers programmed JUCE? I bet lot people have doubts about audio-programming and they learn NOWHERE!


* ysxSDLAudioData.h

For everything related to how SDL handles samples and other kind of data.


* ysxSDLPattern.h

Same as 'ysxPattern.h', but focused on how SDL Lib works.  


* ysxSDLSynth.h:
  
Header to synthesize sound by DSP with SDL Library.
  
  
####### ysxWinplg #######

  
Headers to use with the header 'ysxWin.h'.

  
  
* ysxWinAudio.h:
  
Tools for windows' API for DSP.
  
Stuffs like WAVEFORMATEX and bla bla bla...
  

##################################################################################################

~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ 
