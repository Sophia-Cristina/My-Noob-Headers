i400x_analyzer, an analyzer for Intel 4004 processor, MCS-4 family
==================================================================

	Written by Lajos Kintli, lajos.kintli@gmail.com, 2008-2009, 2018

	This is a schematic and layout analyzer and a simulator program prepared for the Intel's
	MCS-4 family, including the:

		- Intel 4004, Intel's first microprocessor
		- Intel 4001, 256 byte ROM and 4 bit I/O port
		- Intel 4002, 320 bit RAM and 4 bit output port
		- Intel 4003, 10 bit shift register

	The basic motivation for developing this application was to check the transistor level
	circuit diagram of the ICs, to match the layout with the schematic, and to demonstrate its
	operation up to the execution of an assembly code. The included simulator is able to drive
	the analyzed circuit with a signal sequence defined by an emulated MCS-4 environment; it
	shows the disassembly list of the executed code, the digital waveforms of the signals; and
	the wires and transistors on the schematic are colored with the actual state of the relevant
	signals.

	You can get more information about Intel 4004 from the 35th anniversary project homepage:

					http://www.4004.com

	or from Intel's historical pages:

				http://www.intel.com/museum/archives/4004.htm


Main features
=============

	- analyzes the masks used for layers of layout, the netlist is extracted
	- analyzes the raster picture of the schematic, the netlist is extracted
	- the two netlists are compared and components/signals are matched
	- the schematic and the layout are displayed parallel, matched objects are synchronized
	- a simulator is included, which
	  - drives the inputs, and determines the actual logic levels of each internal signals
	  - records the logic levels of the last 10000 clock phases for all signals
	  - shows the digital waveforms like an oscilloscope
	  - is interactive, step by step execution or animation
	- CPU, RAMs and ROMs can be simulated independently or can be connected together through
	  a TCP/IP server application like they were wired in a real MCS-4 system
	- the schematic can be colored according to logic levels of a selected timeslot
	- disassembly window is synchronized with the fetched ROM address
	- runs on standard WIN32 environment


System requirements & installation
==================================

	No special installation is needed, the files should be extracted from the downloaded zip
	package into any directory, and i400x_analyzer_x32/x64.exe can be run. The program expects the
	input files containing the layers of the layout, the picture file of the schematic and the
	file with the list of the signal names to have in the working directory (beside the
	analyzer exe). 
	
	It allocates around 100-120 MB from the virtual memory used for storing	the images and the
	details of the analyzis.

	Requires WS2_32.DLL, the Windows Sockets 2 Application Program Interface run time library,
	which is generally available in the different windows releases.


Package contains:
=================

	i400x_analyzer_x32.exe	the program itself (32 bit version)
	i400x_analyzer_x64.exe	the program itself (64 bit version)
	readme.txt		this file
	license.txt		Intel's license for (re)using the 4004 related source materials
	i4001_metal.bmp		image of mask for metal layer for 4001 ROM
	i4001_vias.bmp		image of mask for vias for 4001 ROM
	i4001_poly.bmp		image of mask for polysilicon layer for 4001 ROM
	i4001_diffusion.bmp	image of mask for diffusion layer for 4001 ROM
	i4001_schematic.bmp	picture of the circuit diagram for 4001 ROM
	i4001_signals.txt	list of signal names and reference points of the schematic for 4001 ROM
	i4002_metal.bmp		image of mask for metal layer for 4002 RAM
	i4002_vias.bmp		image of mask for vias for 4002 RAM
	i4002_poly.bmp		image of mask for polysilicon layer for 4002 RAM
	i4002_diffusion.bmp	image of mask for diffusion layer for 4002 RAM
	i4002_schematic.bmp	picture of the circuit diagram for 4002 RAM
	i4002_signals.txt	list of signal names and reference points of the schematic for 4002 RAM
	i4003_metal.bmp		image of mask for metal layer for 4003
	i4003_vias.bmp		image of mask for vias for 4003
	i4003_poly.bmp		image of mask for polysilicon layer for 4003
	i4003_diffusion.bmp	image of mask for diffusion layer for 4003
	i4003_schematic.bmp	picture of the circuit diagram for 4003
	i4003_signals.txt	list of signal names and reference points of the schematic for 4003
	i4004_metal.bmp		image of mask for metal layer for 4004 CPU
	i4004_vias.bmp		image of mask for vias for 4004 CPU
	i4004_poly.bmp		image of mask for polysilicon layer for 4004 CPU
	i4004_contacts.bmp	image of mask for contacts for 4004 CPU
	i4004_diffusion.bmp	image of mask for diffusion layer for 4004 CPU
	i4004_schematic.bmp	picture of the circuit diagram for 4004 CPU
	i4004_signals.txt	list of signal names and reference points of the schematic for 4004 CPU
	sample.asm		i4004 sample assembly code for testing the instruction set
	sample.hex		compiled form of sample assembly code
	mcs4_net_sample_x32.bat	starts a network mode minimal system with a CPU/ROM/RAM on the same PC
	mcs4_net_sample_x64.bat	the same for 64 bit platform
	myproc_x32.exe		small utility for creating a process (32 bit version)
	myproc_x64.exe		the same for 64 bit platform
	mysleep_x32.exe		small utility for waiting the given (or 1000) miliseconds (32 bit)
	mysleep_x64.exe		the same for 64 bit platform


Background of the development
=============================

	During the university years the basics of microelectronics were taught, however it remained
	on gate level. The need for knowing the details of complex circuits, such as a processor
	were not really satisfied on the expected level. Around June of 2007 I searched for some
	useful information on a similar topic, and www.4004.com was offered by an internet search
	engine for my pleasure. By checking the site I was amazed by the released schematic of the
	first microprocessor, and the java simulator. I did not hesitate to offer my help, as
	volunteers were requested, and my profession and interest were fit into the listed areas.
	Luckily the team was open, and soon I became member of the 35th anniversary project team.

	A challenging request outlined around June of 2008: comparing the netlist of the giant
	replica of the 4004 processor designed for the Intel Museum with the netlist extracted
	from the scanned pictures of masks used for manufacturing the processor itself. The picture
	of masks were provided, and I started to develop code for netlist extraction and
	comparison. Then I wanted to visualize the result. Unfortunately the schematic was not
	available in an appropriate format, so finally I decided to generate it in some way. Not
	having better source print screens about the revised schematic PDF document were made, and
	the parts were put together into a big picture. It was not estimated to be too big work as
	it seems at first, because in the original design methodology the schematic and layout was
	quite close to each other. Practically the multiple blocks had to be redrawn (e.g. the 4 bit
	wide data bus buffers). Additionally the 3 pages of the original drawing was "wired"
	together. Then a component/circuit recognition algorithm was implemented, and parallel with
	it the picture was refined. When the whole circuit was recognized, the earlier developed
	matching algorithm was applied on it, and the possible differences had been corrected.
	
	The identified main differences are shortlisted here:
	
	- in many cases the polysilicon layer not just overlapped but also intersected the
		diffusion at bootstrap capacitors, resulting transistors.
	- two layers due to some pixel errors became incorrectly connected
	- the schematic was "revision G", while the masks might come from an earlier revision.
		The real difference was at the TEST input pin: the masks formed just a simple
		inverter, while it had a complex circuit on the schematic
	- the input order of gates (e.g. a NAND gate with 2 or 3 inputs) were reversed/mixed
		between the schematic and layout
	- in few cases extra inverters were used from the original signals instead the already
		available inverted signals (e.g. "~O2" is won from "O2" using an extra inverter,
		and not directly from the "~O2" used at the other part of the circuit)
	- "JCN+ISZ" had slightly different decoding logic, providing the same result
	
	Finally both sources contained the same result apart from the bootstrap loaders,
	which are indicated on the schematic as a resistor, however those are combinations of
	a resistor, a capacitor and a transistor. The matched data contains the following
	number of components:
	
			component type		layout	    schematic			
			---------------------------------------------
			transistor:		  1807	1807-66= 1741
			resistor:		   427    	  427
			capacitor:		    66	  66-66=    0
			input (gate) protector:	     8		    8
						  ----		 ----
			sum:			  2308		 2176

	After reaching this result, for ensuring its correctness the idea came to simulate the
	extracted circuit, for testing, whether the whole circuit would perform the same result
	on executing an assembly code, how the MCS-4 manual defines it. A simulator logic had been
	included into the package. For easier testing gradually more and more functions had been
	added, rough temporary solutions had been replaced with more matured ones. It was realized
	that the experienced problems came from the weakness of the implemented simulator logic,
	which was improved till it reached a reliably working version.
	
	Special thanks to members of 35th anniversary project team

		Tim McNerney, project leader, digital design, correcting the masks 
		Fred Huettig, netlist extraction software, electrical engineering, correcting the masks
		Barry Silverman, reverse-engineering, java simulation software 
		Brian Silverman, reverse-engineering, java simulation software 

	and collaborators

		Federico Faggin, CEO Foveon, 4004 chip designer
		Tracey Mazur, Curator, Intel Museum
		Rachel Stewart, former Intel archivist
		Dag Spicer, Curator, Computer History Museum

	and people directly not mentioned here, but closely working on this (or some branch of this)
	project in the background. Without their support the source material of the Intel 4004
	chip would have not been published, this analyzer program would have not been developed.

Additions to Version 2.00:
	After completing the work of Intel 4004 microprocessor the desire to simulate a complete
	microcomputer set (CPU, ROMs and RAMs) at transistor level was quite natural. At late
	December in 2008 Tim sent me the masks of Intel 4002 RAM, which was directly usable for the
	simulator. Unfortunately the schematic was not available in any form, however by reusing
	the blocks from the schematic of CPU it could be reproduced in relatively short time.
	The situation with the ROM was not so lucky: I could get only high resolution electron
	microscope photos of Intel 4001 ROM, one for the entire chip, and one with etched metal
	layer... and not in the best quality. The only expedient alternative seemed to be to redraw
	the entire picture into the required layers, and to reverse engineer the schematic.
	For the	sake of completeness of the project it has been done.
	
	At first only the individual chips were simulated separately by generating the necessary
	test patterns for the external pins of RAM/ROM (which required to include nearly a clock
	cycle level accurate simulator of Intel 4004 CPU too). Then the individual applications were
	connected together through a TCP/IP server application. This way the CPU/RAM/ROM simulators
	can be run parallel in a network, as they were wired in a real system. Sharing the resources
	of several computers was considered for providing more screens to the schematic/layout and
	simulator windows; but it was not a minor importance to win more processing power and memory
	for the entire simulated environment.
	
	In 2009 October layout masks of 4003 10 bit shift register was sent also to me. Similarly to
	4002 RAM the schematic was regenerated, and the result was added to the package.

	In 2009 November Intel gave us conformation to publish non-commercially our work under a
	Creative-Common license, including rest of MCS-4 related materials.
	
Additions to Version 2.01:
        As 64 bit windows versions became quite widespread during the last period, it was decided
        to compile the source to this platform too. Now the same package contains native exe programs
        for the 32 and 64 bit platforms. As 64 bit platform can directly run 32 bit exe, this has
        less importance at the moment, but who knows what the future brings.
        
        Other aspect is the antivirus systems. As experienced, nowadays the antivirus programs become
        more and more heuristic, which results, that many of the old-style programs - which use mostly
        lower level windows API - are judged as "virus". Unfortunately time to time this is not an
        exception for the 32 bit version of the analyzer program. Interestingly, there is no similar
        problem with the 64 bit programs. If you were afraid of "virus" warnings, it is better to use
        the 64 bit version.

Starting the program
====================

	The program can be run in "standalone", "network" and "server" mode. In "standalone" mode
	the selected component is analyzed independently, rest of the MCS-4 family is simulated;
	while in "network" mode, the built in MCS-4 simulator is disabled, the components of the
	target system must be started as separate instances of the application, which must be
	connected through a server application. The "server" mode starts the server application,
	which distributes the signals between the components (CLK1, CLK2, SYNC, RESET, 4 bit bus).

	When the program is started, an operation mode dialog box is opened, where you must
	select, which component (CPU, RAM or ROM) is the target of the started program instance,
	and a check box decide, whether the program is working independently, or in network mode
	connecting to a network server. There is a radio button selection for starting the network
	server application too. It is highly recommended to leave the default settings for the
	first time, and to use the more complex working modes after gaining certain level of
	experience. The default settings would start the standalone anayzis of the CPU (which
	provides nearly the same functionality, than the first version of this program had).

standalone mode with CPU:
	If the "CPU" mode is selected without connecting to the 400x network, four windows are
	opened for displaying the following things:

	- schematic window for the picture of the schematic
	- layout window for the layers of the integrated circuit
	- simulator window for the digital waveforms of the signals
	- disassembly window for listing the sequence of disassembled code

	At program startup the raster pictures of masks used for layer metal, poly, diffusion, via
	and contact are automatically read from the default monochrome bitmap files, similarly
	the schematic is read from a bitmap file too. Both are analyzed: the individual components
	(transistors, resistors, capacitors) are identified, the extra components of bootstrap
	loaders of the layout are internally combined into unified resistors, and the two different
	sources are matched together. Reference names on the schematic are read from a text file
	with the x,y coordinate of the anchor point, rest of the signals and the components get
	generated names. The matched signals and components on the layout inherit the corresponding
	names from the schematic, while the unmapped objects get unique names.

	After the analyzis the signals of the schematic are listed in the simulator window, a
	sample code is loaded into the disassembly window. The whole circuit is initialized with a
	long enough reset signal and with generating the necessary amount pulses of the two phase
	clock, the simulator window is updated with the waveform of this initialization process.
	
	Now the circuit can be tested interactively. Although there is a sample program already
	loaded into the disassembly window, but the first byte is not read by the processor yet,
	so it is still the right time to change it to another one (from file menu of the disassembly
	window). Than it can be executed step by step manually (press F7 for a clock phase, F8 for
	32 phases [an entire instruction cycle]) or automatically by invoking the "animate" function.
	
	The individual windows are logically connected together. The assembly window highlights
	the location from where the last byte was fetched, while clicking to any signal in the
	simulator, schematic or layout window, the other windows focus to the same signal too.
	This mechanism also works for components between the schematic and layout window, where
	the components and signals can be searched by their name too.

modes with RAMs:
	MCS-4 family is designed in a way that the CPU can drive with the help of a 3/8 decoder
	altogether 8 CMRAM lines (or 4 CMRAM lines directly), and any of the decoded CMRAM line
	can accept 4 i4002 RAM chips. One out of the four chips is selected based on the "CS" pin,
	and a metal mask option, which is decided during production process. This metal option
	is automatically redrawn on the metal layer and the relevant connection on the schematic
	at program startup, additionally the CS signal is driven by GND or VDD, depending on the
	RAM number combo box of the operation mode selection dialog box.
	
modes with ROMs:
	In case of i4001 ROMs directly 16 can be connected to the CMROM pin of the CPU, and the
	corresponding is selected based on the 4 bit chip address metal mask option. This metal
	mask is automatically set (redrawn both on the schematic and the metal layer) at program
	startup based on the ROM number combo box of the mode selection dialog box.
	
	The content of the ROM is also determined by the metal layer. At program startup by default
	a sample program is loaded, the metal layer of the memory matrix is initialized based on
	that, and the corresponding transistors on the schematic get the necessary shortcuts too.
	If you change the program (by reading new program into the code memory, or by manually
	editing any of the program cells), you must adjust the metal mask by invoking the 
	"Set metal mask of RAM/ROM" menu point from the Simulation menu of the Simulator window 
	for putting the right connections to the metal layer and to the schematic. This function
	also reanalyzes of the changed circuit. 
	
	During the simulation the circuit is simulated, the fetched program code bytes are read
	from the state of relevant transistors in the memory matrix, regardless of the instruction
	sequence shown in the disassembly window. If the "Set metal mask of RAM/ROM" is correctly
	executed, the two different sources have the same content.
	
	The data file of the schematic drawing of the ROM (i4001-schematic.bmp) shows a state,
	where all shortcuts are removed. This corresponds to a case, where all the cells contains
	0xFF. Although 0xFF code byte is unspecified, but it is executed similarly to the 0x00
	NOP instruction by the 4004 CPU.
	
	Note: the number of the signals is strongly depending on the shortcuts of the memory cells,
	also the pattern of the metal mask results possibly parallel connected transistors, the
	component matching can not be determined just by checking the topology.	The situation is
	worse by the increased number of "0" bits. When all cells contain "0",	the circuit becomes
	so symmetrical, that the current matching algorithm is not able to match the components and
	signals in the matrix, but with real content the matching seems to be working reliably.
	
	ROM chips have several metal mask options for configuring the I/O circuits (port direction,
	negate/non negate input-output, pull up/down resistor. This part is not configured by the
	program, however there is the possibility to modify the layout and schematic too. By default
	the blocks are configured a readable non negated outputs. (Pull down resistor is not
	supported in the program, do not use it.)
	
	Although the program contains a quite general component recognition and simulator module,
	the place of (X,Y) coordinates of metal options for chip number, the individual bits of
	memory matrix, the not so simple byte and bit order inside the matrix is hardcoded into
	the program.
	
mode with 4003:
	4003 serial shift register is an optional component in the MCS-4 family for winning more
	digital output for controlling the peripheral devices in a complex environment. In this
	program its support is limited: the layout and schematic is displayed, the components and
	signals are matched, the testability in the simulator is partly solved.
		
network mode:
	As described above in network mode individual simulators can be connected together through
	the server application. In this mode the server application generates the two phase clock
	signal and the RESET signal; and SYNC, CMROM, CMRAMx signals and 4 bit data bus are
	distributed between the connected CPU/ROMs/RAMs. To utilize this feature the following is
	the recommended list of steps:
	
	- Start an instance of the application in "i400x Network Server" mode, which opens two
	windows, one simulator window for displaying the interconnecting signals and an instruction
	window. The TCP/IP port number, where the server is waiting for the connection from the
	clients	is configurable (default port is 1000).
	
	- Start the "client" applications (CPU, ROMs, RAMs) one by one by marking the
	"Connect to 400x Network" checkbox, and fill the IP or hostname of the server, and set the
	same port has been used in the server! You can start the client instances on different
	computers connected to the same TCP/IP network, but you can use the same computer for
	multipurpose too. For getting a working system you must have at least a CPU and a ROM0.
	The successfully connected clients can be monitored from the "Network" menu of the
	simulator window on the server application.
	
	- The sample code is automatically loaded into the server application only, you can load
	another one. E.g. use the "File -> Load Hex File" menu point of the disassembly window on
	the server (and not on the client!).
	
	- Invoke the "Simulation -> Distribute Program Code" on the simulator window of the server,
	which sends the entire program code for the clients.
	
	- Invoke "Simulation -> Set Metal Mask of RAM/ROM" on the simulator window of the server,
	which instructs all the ROMs to load the earlier sent program to the metal layer and also
	to the schematic! This function also reanalyzes all the clients schematic and layout and
	resets the initial state.
	
	- Now the system is ready for the program execution, the F7/F8 stepping can be called on
	the server and also on the clients too, and similarly "Cold Reset/Processor Reset/
	Go till end of reset/Go till sync/Step 3200 clock phase" are working. Animation can be
	initiated on the server only.

	In the package "mcs4_net_sample_x32/64.bat" batch files are included, which create a server,
	and a minimal system with a CPU, a ROM and a RAM on the same computer. Upon running it
	the sample code is loaded into the server only, it must be distributed to the ROM, and
	the ROM must be "maskprogrammed" separately.
	
	The batch file uses two external programs, one for creating processes, and the other
	for waiting certain time between starting the applications. There must be some delay
	between starting the server and client applications, otherwise the server is not
	initialized yet, the clients can not connect; but the delay is also beneficial to spread
	the initial overloading of the PC. The windows operating system may have similar
	utilities, and could be used instead of them. "start /b" can be used as a replacement
	of "myproc", and "sleep" can replace "mysleep".
	
command line parameters:
	A list of command line parameters is supported, the program startup mode can be specified,
	or some of the automatism can be disabled. The command line parameters are case sensitive,
	the unknown values are ignored. The following values are accepted:

	SERVER		- the application is started in server mode
	CPU/ROMxx/RAMxx	- the application is started in a specified Intel 400x mode
			  (xx is a number, 0..15 from ROMs, 0..31 for RAMs)
	use_network	- selects the network mode, the application connects to a server
	host <param>	- connects to the server specified in the parameter
			  (can be a hostname or an IP address)
	port <param>	- use the TCP/IP port number specified by the parameter
			  (must be a decimal number 1..65535, otherwise it is ignored)

	dialog		- the initial i400x mode configuration dialog is invoked, regardless that
			  the mode is already specified by the SERVER/CPU/ROMxx/RAMxx, but
			  the default settings are influenced by the command line parameters (this
			  parameter must come after the mode specifiers)

	no_nw_inform	- message boxes of connection establishment and lost are suppressed
			  (has meaning only in network mode)

	no_layout	- the layout is not loaded, the layout window is disabled
	no_analyze	- the initial analyzis of the layout is skipped
	no_match	- the matching between the analyzed schematic and layout is skipped
	no_simulate	- the simulator does not execute the first initialization cycles 
	no_schematic	- the schematic is not loaded, the schematic window is disabled
	no_code		- the default hexfile is not loaded
	no_mask		- the metal mask options of RAMs/ROMs initially are not set
	hide_simulator	- simulator window is hidden
	hide_layout	- layout window is hidden
	hide_schematic	- schematic window is hidden
	hide_code	- disassembly window is hidden

	E.g. you can use the following command to make a minimized MCS-4 system on a PC. The
	following commands start a network server and two clients (CPU and ROM0) on the same PC.
	Note, issuing the "host 127.0.0.1" parameter is unnecessary, as the "localhost" is
	the default value.

	i400x_analyzer SERVER port 1234
	i400x_analyzer CPU use_network host 127.0.0.1 port 1234 hide_layout hide_code
	i400x_analyzer ROM0 use_network host 127.0.0.1 port 1234 hide_layout hide_code

known issue:
	If several (networked) applications are started on the same PC concurrently (from a batch
	file), the computer becomes extremely overloaded temporarily, which may cause initialization
	problems also for the operating system. E.g. the system tray may not display all the newly
	created application window, although the successfully established connections can be be seen
	from the "Network" menu of the Server Simulator window. Applications can be monitored from
	the Windows Task Manager too.


The layout window
=================

	This window is for handling the layers of the chip. After loading the layer files and
	after the initial analyzis the components are recognized at the intersection of the
	polysilicon and diffusion which are migrated to the generated "active" layer.
	The diffusion layer is split by the polysilicon into a new layer too.
	
	Identified components of the layout are tried to map with the schematic. By selecting any
	object here is highlighted on the schematic window (and if it is a signal, it is selected
	on the simulator window too). If the selection is made with the	right mouse button, then
	it will not be followed on the schematic or simulator window.
	
	By double clicking on a signal (with left or right mouse button), the signal is appended
	or inserted to the simulator window.
	
	On mouse move the status line is refreshed with the local information of the (x,y)
	coordinate. If the metal, polysilicon or diffusion layer is filled, the assigned signal is
	listed in the status line. If there is already a simulation result, the	state is also
	displayed for the selected cycle with the two letter abbreviations described at the
	simulator part. The identified component is also updated into the status line with the
	On/Off state in case of the transistors.
	
	Layers can be individually switched on or off. Shift-F1..Shift-F8 switch off all layers,
	except the one assigned to the hotkey button, while Ctrl-F1..Ctrl-F8 toggle the displayed
	status of the assigned layers. Additionally the metal layer is displayed slightly
	transparently, if the "Transparent Metal Layer" is marked.
		
	There is a simple layer edit tool implemented in this window, which was used for correcting
	the critical pixel errors of the layers. By default it is disabled, but can be enabled
	through the switchable "Enable Pixel Edit". In this case holding the left mouse button
	pressed would fill pixels on the selected layer, while the right mouse button would erase
	the touched points.
	
	The edited layer can be saved, can be reanalyzed. At analyzis, the matching algorithm is
	executed too.
	
	Note: this version of program contains a simplified matching algorithm only, which is
	efficient enough for the entirely matched layout and schematic, however the efficiency
	may be dropped down if this were not a valid assumption. During the correction of the layout
	and the schematic other algorithms were used too (which consumed more memory, and was more
	efficient and informative in case of the possible differences by displaying special
	attributes assigned to the nodes of connection network), but those have been removed from
	the package for reducing the memory consumption.


The schematic window
====================

	This window is for handling the schematic. Similarly to the layout window selecting any
	object on the schematic would select the same object on the layout (and the simulator
	window in case of signals). If the selection is done with the right mouse button, the
	signal or component is just highlighted, but not followed in the other windows.
	Mouse double clicks would add the signal to the simulator window, which can be done with
	the left and right mouse button too.
	
	If the circuit has already simulation result, the circuit can be colored with the
	actual state of the selected timeslot. Light red or blue color carries defined or pulled
	high or low state, while dark red or blue represents floating high or low state. In case
	of unspecified state the wires remain grayed. Light or dark yellow color is assigned to
	the switched on or off transistors.


The simulator
=============

signal levels:
	The simulator works with digital signals, where the following states are distinguished:

		- Defined High (DH): the signal is externally driven by VDD
		- Defined Low (DL): the signal is externally driven by GND
		- Pulled High (PH): the signal is connected through an opened transistor or a
			list of	opened transistors to VDD, or to a resistor connected to the VDD
		- Pulled Low (PL): the signal is connected through an opened transistor (or a
			list of	opened transistors) to GND
		- Floating High (FH): the signal had been pulled to logic high level earlier, and a
			transistor which connected the signal towards VDD has been just switched
			off, and the signal keeps the earlier logic high level due to the
			capacitance of the wiring, components.
		- Floating Low (FL): the signal had been pulled to logic low level earlier, and a
			transistor which connected the signal towards GND has been just switched
			off, and the signal keeps the earlier logic low level due to the
			capacitance of the wiring, components.
		- Undefined (UX): the state of signal is unspecified.

	There are several ways, how the unspecified state is assigned to a signal:

		- all the signals get the unspecified state before starting the simulation, except
			the externally driven inputs.
		- a bidirectional signal (any of the external data lines in 4004 case) which was
			externally driven earlier looses the defined high/low level, the simulator
			initializes it to undefined.
		- at the same time a signal is pulled with transistors towards VDD and GND
		- a floating low and a floating high signal is connected through a just switched on
			transistor together
		- a floating high or low signal is just connected to an unspecified signal.

	Note, in the latter two cases, if the wiring capacitance of the floating signal is much
	bigger than the capacitance of the other floating (or unspecified signal), it will remain
	on the same floating level, furthermore its logic level is propagated to the just connected
	lower capacitance signal. The capacitance of connected signals are estimated based on the
	number of transistors connected to the signals. (If this 'dominant capacitance' rule were
	not implemented in the simulator, e.g. reading of the effective address or register would
	fail or the carry bit of the arithmetic unit would lose its value in certain cases.)
	
	The transistors have only two states, "On" or "Off". If an undefined state is connected to
	the gate of the transistor, it is considered as switched off.

simulator logic:
	The simulator works with a relatively simple logic: it implements a loop for recalculating
	the connected signals where there is some change in the neighborhood, which is executed
	until a stable state in the entire network is reached. (For safety reason the loop is
	executed maximum 100 times, which limitation would block an unstable network, e.g. if 3
	inverters would be connected into a ring.) When a signal is checked, it is determined
	what other signals are connected to this actual one through source and drains of the
	switched on transistors. Then the overall state is decided, and the transistors controlled
	by these signals are checked, and switched, if their earlier states were different. The
	drain and source signals of a changed transistor are marked for recalculation for the next
	loop. If the "Record Internal Iteration" is marked in the debug menu, all the steps of the
	main simulation loop is stored for the simulator window, while normally only the result of
	the last step is stored, when the network is stabilized.

MCS-4 environment:	
	The MCS-4 environment is coded into the simulator, but the simulator works in an authentic
	way: only checks the external input/output pins for making decision, when the external data
	bus carries the address or data, and puts the expected address or data to the bus according
	to protocol of MCS-4 system. The first 14 signals defined in the "i400?_signals.txt" file
	are assumed to be the external pins in the following order (independently how those are
	named):

	CPU:	CLK1, CLK2, POC, TEST, D0, D1, D2, D3, SYNC, CMROM, CMRAM0, CMRAM1, CMRAM2, CMRAM3
	ROM:	CLK1, CLK2, POC, CL,   D0, D1, D2, D3, SYNC, CM,    I/O0,   I/O1,   I/O2,   I/O3
	RAM:	CLK1, CLK2, POC, CS,   D0, D1, D2, D3, SYNC, CM,    OUT0,   OUT1,   OUT2,   OUT3
		  
	GND and VDD signals have unique signs on the schematic, those are automatically identified
	and named.
	
	In standalone mode a fully populated MCS-4 environment is implemented in the background
	with 16 ROM chips, and 32 RAMs. You can load the assembly code to be tested into the
	disassembly window. If you would like to test a certain instruction repeatedly, select the
	"Use only first byte from ROM" feature from the Debug menu, end enter the instruction code
	into location 000 of the memory. For two byte instructions the "Use 2nd byte too" must be
	marked too, and enter the instruction code into location 001 too. If a ROM is simulated,
	each time the content of the program memory is changing, the "Set metal mask of RAM/ROM"
	must be invoked to "mask program" the ROM, otherwise the disassembly window would show
	different instruction list from the fetched and executed instruction codes provided by
	the ROM itself.
	
	In the simulator the switching time is not calculated, so called "zero propagation delay"
	model is used. In the MCS-4 system the external signal outputs are synchronized to CLK2
	H->L (falling) edge; the SYNC, CMROM/CMRAM signal, and the data bus changes occur then.
	The external signals are also sampled with CLK2 signal. In the real system it has the
	consequence, that control signals generated by a node with certain delay to CLK2 signal
	is reached the other component after the CLK2 H->L transition. For this reason a step delay
	is applied in the signals, e.g. CMROM is generated by the CPU at CLK2 H->L, however, when
	the ROM is simulated, it is provided at CLK1 L->H. This cause a slight inaccuracy in the
	timing, but in a sense it is closer to the reality. For the bidirectional data bus this
	brings another problem, as at the bus drive direction change the external driving overwrites
	the bus with a step delay, while the component itself wants to put the data with zero
	propagation delay. Driving the external inputs are simulated with "defined" high or low
	level, while the component drives outputs with "pulled" high or low level.
	
	In network mode as many components of the MCS-4 environment is simulated, as many clients
	are connected to the server. The server generates the clock and reset signals only, rest of
	the signals are distributed between the client components (3/8 decoder for CMRAM lines are
	simulated too). In the network server simulator window A12-X32 machine cycle signals are
	regenerated based on the position of SYNC signal, additionally a list of component signals
	indicates, who drives the data bus. In the signal distribution the signals are automatically
	delayed with a clock phase, as the output of one of the component is carried to the rest of
	the system in the next simulation step only. Be aware of using the complex initialization
	process of network mode described earlier at the "starting the program" -> "network mode"
	part.
	
	There are two dialog boxes, one for showing the content of emulated environment (RAMs, ROM
	ports), and one for quick editing the content of the ROMs. Content of ROMs can be loaded
	from a file (in Intel Hex format) through the disassembly window.
	
	The state of TEST pin is determined by a menu point, can be marked or unmarked.

waveforms:
	The main object of the simulator window is to display the digital waveform of the signals.
	Initially all the signals are added to the window, but you can remove them and you can
	collect a set of interested signals:

	 - select any signal on the schematic, or a mapped signal on the layout, and press "Ctrl-O"
	 - double click with the mouse pointer on a signal on the schematic or on the layout

	On left button double click the selected signal is appended to the end of the signal list
	in the simulator window, on right button double click it is inserted before a selected
	signal (or appended at the end, if none of the signals is selected). To insert before you
	must select first the signal on the simulator window, than to add the signal from the
	schematic or layout with the double click of the right button.
	
	If you have already collected measurement, the states of signals are displayed in digital
	waveforms. The waveform is solid lined, when the signal has defined or pulled high or low
	state, and dotted line means floating low or high level, or unspecified, if it is in the
	middle of the waveform shape.
	
	If the "Record Internal Iteration" is used with the "Highlight Signal Check" feature, then
	the line is red, when the signal is calculated in that simulation step. The signal is
	colored to white in a suspicious situation, when a signal is pulled to logic high and low
	level at the same step. Note, this is natural temporarily in certain cases: when e.g. an
	inverter with a switched load changes its state, and controlling of pull up and pull down
	transistor happens with a slight simulation delay.
	
	By default the simulator uses logic levels, meaning the "logic 1" is on the top of the
	waveform, while "logic 0" is at the bottom. As MCS-4 family uses -15 Volt as the VDD level
	relative to the GND, this is the opposite, one would measure with a real oscilloscope
	directly on a pin. Intel usually uses the physical voltage levels on the released
	documents, rather than the logic levels. For this reason a "Reversed Logic Level" feature
	is implemented, by turning it on from the menu, the signals are inverted on the output
	window.

status line:
	The status line of the simulator window states of few internal signals are directly
	indicated. These states are determined based on the names of the signals. Note, in the
	status line the unspecified signals considered to be 0. Also, if the "signals.txt" does
	not contain a particular name, it is replaced with 0. The following identifiers
	are searched from file "i400?_signals.txt":
	
	D3,D2,D1,D0	- internal data bus
	A12,A22,A32,M12,M22,X12,X22,X32	- timing block outputs of an instruction cycle
	SC		- single cycle
	CN		- condition 
	INH		- inhibition of effective address refreshment
	CY		- carry
	ACC.0-3		- accumulator
	PC0-3.0-11	- effective address registers (e.g. PC1.11 for bit 11 of effective address 1)
	R0-15.0-3	- general register (e.g. R10.2 for bit 2 of register R10)
	TMP.0-3 	- temporary operand of ALU
	OPR.0-3		- OPR register
	OPA.0-3		- OPA register
	ADDR-PTR.0-1	- Effective address selector ("stack pointer")
	ADDR-RFSH.0-1	- Effective address block refresh register
	REG-RFSH.0-2	- register block refresh register
	DCL.0-2		- Designate Command Line register

	In case of RAM/ROM the status line is refreshed with the state of the simulated CPU
	environment, which works only in standalone mode.

interactivity:
	The simulator can be executed step by step manually or in an animated way. The cycle
	term in this window means a simulation step, which is not identical with the MCS-4 machine
	cycle or an instruction cycle.
	
	You can step one subphase of a machine cycle with pressing "F7", or pressing "F8" would go
	32 steps (identical with one instruction cycle), or "CTRL-R" goes 100 instruction cycle
	(=3200 steps). There is possible to go till end of SYNC signal by "F6", or there is a menu
	point for going till the end of the external POC (reset) signal. Note, when the external
	POC signal becomes inactive, the internal POC is still active temporarily, it needs few
	additional clock steps for starting the first instruction cycle.

	The result of the steps are recorded into the memory, the last 10000 steps are preserved.
	You can scroll back to an earlier cycle and by clicking to any timeslot, the schematic
	window is synchronized/colored with the state of the selected timeslot (the same signal
	is selected on the schematic, but by making the selection with the right mouse button
	click, the selected signal on the schematic window is not changed).

	You can choose the animation feature, where the speed of the animation can also be changed.
	This way the individual steps are automatically executed. Animation blocks a list of
	functions in the package. E.g. if you would like to change the content of ROM, you should
	first stop the animation. In networked mode animation can be invoked from the network
	server only.
	
	On mouse move the status line is continuously refreshed with the state of the time slot
	and signal determined by the mouse position.

	In network mode the network server makes the synchronization between the clients. When any
	of the stepping command is invoked on a client (e.g. F8 for 32 clock phases), this request
	is forwarded to the server, and the server generates the clock phases by changing the CLK1
	and CLK2 signals, and instructs the clients for processing the changed inputs. When all
	the clients acknowledge back that the current step is executed, the next steps are ordered
	by the server. For ensuring better performance the windows are not refreshed between the
	steps, just at the end of the very last step, however any external circumstance can occur
	(e.g. the user resize the window), which results window refreshment. Be aware that in this
	case the window may contain inconsistent data. Also, if any of the clients does not
	respond in time, the processing may stop for a meaningful period. Processing of "Ctrl-R"
	(3200 steps) can last dozens of seconds or even a longer period on a slower system or in a
	very complex simulation environment.


The disassembly window
======================

	This window shows the disassembled list of instructions loaded into the ROMs. You can
	read the content of the ROMs from Intel Hex file. During execution of the code, the
	simulated processor sends the address in the first three machine cycles. When the entire
	address is sent, the window is positioned into the line, which contains the byte of
	fetched location. Note, the simulator does not know why that address is fetched. It is
	usually a code byte, but during execution of "FIN" instruction the indirect address
	"interrupts" the sequence of code addresses.
	
	When an earlier time slot is selected in the simulator window by clicking to the earlier
	stage of any signal, the disassembly window will focus the line, which address was valid
	during the execution at that time.


Remarks
=======

Reset pulse:
	The longest reset pulse is needed for the 4002 RAM. It has 5 bit refresh counter, which
	requires at least 2^5=32 instruction cycles for clearing the entire memory matrix,
	after the CPU gives the first SYNC pulse. This means that (2^5)*32=1024 and a little bit
	more CLK1-CLK2 step phases are needed, which is set to 1100 in the simulator.

WPM instruction:
	Attached 4001 RAM schematic executes the instruction code 0xE3 WPM (designed for 4008/4009)
	as WRM (write main memory). The built in simulator follows this behavior.

Gate (input) protectors:
	The program assumes those transistors to be gate protectors, where the gate and one of the
	source or drain are connected to GND. This rule is in line with the design method of CPU,
	however the metal option transistors on ROM and RAM mislead this statistic.

"Y-shape" transistors of ROM:
	The output transistors of I/O stage of 4001 ROM originally form "Y-shape" on the
	polysilicon layer, which topology is not understood by the layout analyzer (the program
	expects that the polysilicon cuts into two parts the diffusion, and here it cuts into
	three parts; although two of them are shortcut through the metal layer). Finally the
	layout was simplified, the parallel transistors were replaced with simpler ones
	(T0062, T0064, T0066 and T0068).

Resistors:
	The program assumes, that the resistors are pullup resistors, meaning that one of the
	endings of any resistor is connected to VDD. This rule is generally valid to 4004 and 4002,
	and with two exceptions in 4001 and 4003:
	1, in 4001 ROM the I/O configuration has a metal option to connect a resistor to GND
	   (do not test this option, as it is not supported).
	2, R0206 of 4003 is originally formed by two serially connected transistors, which is
	   simplified to one transistor (both on the schematic and layout)
	   
Note: components (such as signals) can be searched by names in schematic and layout window through
	the Ctrl-F dialog box
	   

License note:
=============

You are free to use and distribute the analyzer program for non-commercial purposes.

Attached datafiles are considered as derivative work of the original copyrighted source material
of Intel MCS-4 family. For the 4004 processor it can be used non-commercially, see license.txt
or visit

	http://www.intel.com/museum/4004ipnclicense.htm.

Intel also provided written confirmation to use other MCS-4 related materials in this work and
publish non-commercially the recreated source materials of 4001 ROM, 4002 RAM and 4003 schematics
and 4001 layout under a Creative Commons license. It is available now 'By-attribution,
Non-Commercial, Share-Alike' (BY-NC-SA) according to the following legal notice:

	http://creativecommons.org/licenses/by-nc-sa/3.0/legalcode

Package is provided "AS IS", without warranty. You are welcome to feedback possible errors,
comments to the author.


References
==========

	http://www.4004.com	- 35th anniversary project page
		(revised version of schematic)

	http://www.intel.com	- Intel's home page

	http://www.intel.com/museum/archives/4004.htm - 4004 archive at Intel's Museum
		(MCS-4 manual, 4004 datasheet, schematic and layout masks)

	http://www.intel.com/museum/4004ipnclicense.htm
		(licensing of the source materials)

	http://www.intel4004.com - A testimonial from Federico Faggin

	http://en.wikipedia.org/wiki/Intel_4004 - Intel 4004 on Wikipedia


Revision history:
=================

	V1.00 (2008.12.23):	- first released version

	V2.00 (2009.11.14):	- Intel 4001 ROM, 4002 RAM and 4003 are included too
				- Network Support: Individual simulators can be connected
					together through TCP/IP
				- bug fixes

	V2.01 (2018.11.15):	- recompiled to 32 and 64 bit windows platform
