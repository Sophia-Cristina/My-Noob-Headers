#pragma once

#ifndef YSXSYNTH_H
#define YSXSYNTH_H
//#include <time.h>
//#include "include/asio.hpp"
//#include "sdk/common/asio.h"

// #####################
// ####### By Sophia Cristina
// #######
// #####################

// #################################################
// REFERENCES:
// [1] ASIO SDK 2.3.pdf - Included in the SDK zip file;
// [2] https://stackoverflow.com/questions/27852225/c-asio-accessing-buffers#27855067
// #################################################

// #################################################
// [2]:
/*
The hostsample in the ASIO SDK is pretty close to what you need. In the bufferSwitchTimeInfo callback there is some code like this:

---
for (int i = 0; i < asioDriverInfo.inputBuffers + asioDriverInfo.outputBuffers; i++)
{
	int ch = asioDriverInfo.bufferInfos[i].channelNum;
	if (asioDriverInfo.bufferInfos[i].isInput == ASIOTrue)
	{
		char* buf = asioDriver.bufferInfos[i].buffers[index];
		....
---

Inside of that if block asioDriver.bufferInfos[i].buffers[index] is a pointer to the raw audio data (index is a parameter to the method).

The format of the buffer is dependent upon the driver and that can be discovered by testing asioDriverInfo.channelInfos[i].type. The types of formats will be 32bit int LSB first, 32bit int MSB first, and so on. You can find the list of values in the ASIOSampleType enum in asio.h. At this point you'll want to convert the samples to some common format for downstream signal processing code. If you're doing signal processing you'll probably want convert to double. The file host\asioconvertsample.cpp will give you some idea of what's involved in the conversion. The most common format you're going to encounter is probably INT32 MSB. Here is how you'd convert it to double.

---
for (int i = 0; i < asioDriverInfo.inputBuffers + asioDriverInfo.outputBuffers; i++)
{
	int ch = asioDriverInfo.bufferInfos[i].channelNum;
	if (asioDriverInfo.bufferInfos[i].isInput == ASIOTrue)
	{
		switch (asioDriverInfo.channelInfos[i].type)
		{
			case ASIOInt32LSB:
			{
				double* pDoubleBuf = new double[_bufferSize];
				for (int i = 0 ; i < _bufferSize ; ++i)
				{
					pDoubleBuf[i] = *(int*)asioDriverInfo.bufferInfos.buffers[index] / (double)0x7fffffff;
				}
				// now pDoubleBuf contains one channels worth of samples in the range of -1.0 to 1.0.
				break;
			}
			// and so on...
---
*/

// ###############################################################################################################################################################################
// ###############################################################################################################################################################################
// ###############################################################################################################################################################################

class Synth
{
public:
	//ASIODriverInfo Driver;

	Synth(/*long DriverVersion, std::string Name32b, std::string ErrorMsg,*/ void* SysRef) // [1]
	{
		// 'on input' - the host version. This is 0 for earlier ASIO implementations.
		// The asioMessage callback is implemented only if asioVersion is 2 or greater.
		// (Sorry but due to a design oversight the driver doesn't have access to the host version in
		// ASIOInit, see also Appendix E.).
		// Added selector for host(engine) version in the asioMessage callback so we're ok from now on.

		// 'on return', - ASIO implementation version. Older versions are 1.
		// If you support this version(namely, ASIOOutputReady()) this should be 2 or higher.
		// also see the note in ASIOGetSamplePosition()!
		//Driver.asioVersion = 2;

		//Driver.driverVersion = DriverVersion; // on return, the driver version (format is driver specific)
		//char* p = Driver.name;
		//StrInChar(Name32b, p, 32); // on return, a null-terminated string containing the driver's name
		//p = Driver.errorMessage;
		//StrInChar(ErrorMsg, p, 124); // on return, should contain a user message describing the type
									   // of error that occurred during ASIOInit(), if any.

		//Driver.sysRef = SysRef; // on input: system reference (Windows: application main window handle, Mac & SGI: 0)
	}

	~Synth()
	{
	}
};

// ###############################################################################################################################################################################
// ####### MAIN #################################################################################################################################################################
// ###############################################################################################################################################################################

#endif // SCPARSE_