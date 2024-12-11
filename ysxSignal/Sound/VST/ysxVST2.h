#pragma once

#ifndef YSXVST2_H
#define YSXVST2_H

// #####################
// ####### By Sophia Cristina
// ####### Steinberg VST2 stuff.
// #####################

#include <string>
#include <vector>
#include <windows.h>

#include "aeffect.h"
#include "aeffectx.h"
#include "vstfxstore.h"

/*#################################################
REFERENCES:
[1]: http://teragonaudio.com/article/How-to-make-your-own-VST-host.html
#################################################*/

// ###############################################################################################################################################################################
// ###############################################################################################################################################################################
// ###############################################################################################################################################################################

// ############## CALLBACK:

// MAINS HOST CALLBACK:
// VstIntPtr is "int32_t" if at 32x, VstInt32 is also "int32_t"!
VstIntPtr VSTCALLBACK ysxVST2_HostCallBack(AEffect* effect, VstInt32 opcode, VstInt32 index, VstInt32 value, void* ptr, float opt)
{
	switch (opcode)
	{
	case audioMasterVersion:
		return(2400);
	case audioMasterIdle:
		effect->dispatcher(effect, effEditIdle, 0, 0, 0, 0);
		// Handle other opcodes here... there will be lots of them
	default:
		std::cout << "Plugin requested value of opcode: " << opcode << "!\n\n";
		break;
	}
}

// PLUGIN'S ENTRY POINT:
typedef AEffect* (*ysxVST2_PluginFuncPtr)(audioMasterCallback host);

// PLUGIN'S DISPATCHER FUCNTION:
typedef VstIntPtr(*ysxVST2_DispatcherFuncPtr)(AEffect* effect, VstInt32 opCode,	VstInt32 index, VstInt32 value, void* ptr, float opt);


/*// Plugin's getParameter() method
typedef float (*getParameterFuncPtr)(AEffect* effect, VstInt32 index);
// Plugin's setParameter() method
typedef void (*setParameterFuncPtr)(AEffect* effect, VstInt32 index, float value);
// Plugin's processEvents() method
typedef VstInt32(*processEventsFuncPtr)(VstEvents* events);
// Plugin's process() method
typedef void (*processFuncPtr)(AEffect* effect, float** inputs,	float** outputs, VstInt32 sampleFrames);*/

// #################################################
// ############## CLASSES ##############

template <const uint32_t SRATE, const uint32_t BUFSIZE, const uint8_t CHANNELS>
class ysxVST2_Plugin
{
public:
	// VST config:
	AEffect* Plugin;
	LPCWSTR Path;
	HMODULE Ptr;
	ysxVST2_PluginFuncPtr EntryPt;
	ysxVST2_DispatcherFuncPtr Dispatcher; // Create dispatcher handle
	
	// Predefined events:
	std::vector<VstEvents> Events;

	// ####### SIGNALS:
	float* Ins[CHANNELS];
	float* Outs[CHANNELS];
	float BufsIn[CHANNELS][BUFSIZE];
	float BufsOut[CHANNELS][BUFSIZE];


	// #################################################
	// ############## DES-/CONS-TRUCTOR ##############
	// #################################################

	ysxVST2_Plugin(LPCWSTR SetPath)
	{
		Path = SetPath;
		Ptr = LoadLibrary(Path);
		if (Ptr == NULL) { std::cerr << "Failed loading VST ('" << Path << ")!\nError: " << GetLastError() << "!\n\n"; }
		EntryPt = (ysxVST2_PluginFuncPtr)GetProcAddress(Ptr, "VSTPluginMain");

		Plugin = EntryPt(ysxVST2_HostCallBack); // Instantiate the plugin
		if (Plugin->magic != kEffectMagic) { std::cerr << "Incorrect plugin magic number (" << Plugin->magic << ")! Should be: 'VstP'!\n\n"; }
		Dispatcher = (ysxVST2_DispatcherFuncPtr)(Plugin->dispatcher);
		for (uint8_t n = 0; n < CHANNELS; ++n) { Ins[n] = &BufsIn[n][0]; Outs[n] = &BufsOut[n][0]; }
	}

	~ysxVST2_Plugin()
	{
	}

	// #################################################
	// #################################################
	// #################################################

	void StartPlugin()
	{
		Dispatcher(Plugin, effOpen, 0, 0, NULL, 0.0f);
		Dispatcher(Plugin, effSetSampleRate, 0, 0, NULL, SRATE);
		Dispatcher(Plugin, effSetBlockSize, 0, BUFSIZE, NULL, 0.0f);
		//resume();
	}

	void Resume() { Dispatcher(Plugin, effMainsChanged, 0, 1, NULL, 0.0f); }

	void Suspend() { Dispatcher(Plugin, effMainsChanged, 0, 0, NULL, 0.0f); }

	/*PLUGIN CAPABILITIES:
	The VST protocol uses “canDo” strings to define plugin capabilities, the most common of which
	are defined in "audioeffectx.cpp" in the "PlugCanDos namespace" near the top of the file.
	To ask a plugin if it supports one of these capabilities, USE the following dispatcher call:*/
	bool CanPluginDo(char* CanDoString) { return(Dispatcher(Plugin, effCanDo, 0, 0, (void*)CanDoString, 0.0f) > 0); }

	// #################################################
	
	/*void InitIO()
	{
		// inputs and outputs are assumed to be float** and are declared elsewhere,
		// most likely the are fields owned by this class. numChannels and blocksize
		// are also fields, both should be size_t (or unsigned int, if you prefer).
		inputs = (float**)malloc(sizeof(float**) * numChannels);
		outputs = (float**)malloc(sizeof(float**) * numChannels);
		for (int channel = 0; channel < numChannels; channel++)
		{
			inputs[i] = (float*)malloc(sizeof(float*) * blocksize);
			outputs[i] = (float*)malloc(sizeof(float*) * blocksize);
		}
	}*/

	void SilenceChannels(float** ChannelData)
	{
		for (size_t C = 0; C < CHANNELS; ++C)
		{
			for (uint32_t n = 0; n < BUFSIZE; ++n) { ChannelData[C][n] = 0.0f; }
		}
	}

	/*Inputs and outputs array which should be initialized by your application as soon you have calculated
	the desired channel count and buffer size. You should not allocate the inputs and outputs arrays in the
	"ProcessAudio()" function, as doing so may severely impact performance.
	
	Hence, the call to "InitIO()" should be made as soon as possible and before the first call to
	"ProcessAudio()".

	You should also take care to properly initialize the data in both the inputs and outputs array to zero,
	or else you can get	static or other random noise in the processed signal.*/
	void ProcessAudio()
	{
		// Always reset the output array before processing.
		SilenceChannels(Outs);

		// Note: If you are processing an instrument, you should probably zero
		// out the input channels first to avoid any accidental noise. If you
		// are processing an effect, you should probably zero the values in the
		// output channels. See the silenceChannel() function below.
		// However, if you are reading input data from file (or elsewhere), this
		// step is not necessary.
		SilenceChannels(Ins);

		Plugin->processReplacing(Plugin, Ins, Outs, BUFSIZE);
	}

	// If you added things on the "std::vector Events" of this class,
	// you can pass it by reference: &Events[0].
	void ProcessMIDI(VstEvents* events)
	{
		Dispatcher(Plugin, effProcessEvents, 0, 0, events, 0.0f);
	}
	
	// #################################################
	// #################################################
	// #################################################

	// ####### EDITOR WINDOW:

	HINSTANCE hInst; // Add ID to our global variable
	PAINTSTRUCT PaintStruct;
	HDC hdc;
	int wmId = 0, nCmdShow;
	LPCWSTR szWindowClass;
	LPWSTR szTitle;
	MSG msg;

	LRESULT (CALLBACK* WndProc)(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_COMMAND:
		{

			wmId = LOWORD(wParam);
			// Analise as seleções do menu:
			//switch (wmId)
			//{
			//case IDM_ABOUT:
				//DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				//break;
			//case IDM_EXIT:
				//DestroyWindow(hWnd);
				//break;
			//default:
				//return DefWindowProc(hWnd, message, wParam, lParam);
			//}
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
		case WM_PAINT:
		{
			PaintStruct;
			hdc = BeginPaint(hWnd, &PaintStruct);
			// TODO: Adicione qualquer código de desenho que use hdc aqui...
			EndPaint(hWnd, &PaintStruct);
		}
		break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}

	}

	// #################################################

		// REGISTER WINDOW CLASS:
	ATOM MyRegisterClass()
	{
		WNDCLASSEXW wcex;

		wcex.cbSize = sizeof(WNDCLASSEX);
		//wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WndProc;
		//wcex.cbClsExtra = 0;
		//wcex.cbWndExtra = 0;
		wcex.hInstance = hInst;
		//wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TESTESAQUIWIN));
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		//wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_TESTESAQUIWIN);
		wcex.lpszClassName = szWindowClass;
		//wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

		return RegisterClassExW(&wcex);
	}

	// #################################################

	// SAVE INSTANCE ID, CREATE AND SHOW MAIN WINDOW:
	BOOL InitInstance()
	{
		HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInst, nullptr);
		if (!hWnd) { return(FALSE); }
		ShowWindow(hWnd, nCmdShow);
		UpdateWindow(hWnd);
		return(TRUE);
	}

	// #################################################
 
	// SHOW WINDOW:
	void MsgLoop()
	{
		while (GetMessage(&msg, nullptr, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	// #####################
	// ####### MAIN #######
	// #####################

	//int APIENTRY wWinMain(_In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
	int wWinMain()
	{
		//UNREFERENCED_PARAMETER(hPrevInstance);
		//UNREFERENCED_PARAMETER(lpCmdLine);

		// ##################### CODE #####################

		// #################################################

		// INITIALIZE GLOBAL STRINGS:
		//LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
		//LoadStringW(hInstance, IDC_TESTESAQUIWIN, szWindowClass, MAX_LOADSTRING);
		MyRegisterClass();

		// INITIALIZE APP:
		if (!InitInstance()) { return(FALSE); }
		//HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TESTESAQUIWIN));

		// #################################################
		// MAIN MESSAGE LOOP:
		/*MSG msg;
		while (GetMessage(&msg, nullptr, 0, 0))
		{
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}*/
		MsgLoop();
		// #################################################
		return((int)msg.wParam);
	}
};

// ###############################################################################################################################################################################
// ####### MAIN #################################################################################################################################################################
// ###############################################################################################################################################################################

#endif // SCPARSE_