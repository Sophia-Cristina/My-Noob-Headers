#pragma once

#ifndef YSXRP2A03INSTR_H
#define YSXRP2A03INSTR_H

// #####################
// ####### By Sophia Cristina
// ####### RP2A03 processor emulator instructions. Used on NES.
// ####### THIS WAS DESIGNED TO BE USED *ONLY* INSIDE 'ysxRP2A03.h'!!!
// #####################

/* Interrupt requests are a complex operation and only happen if the
"disable interrupt" flag is 0. IRQs can happen at any time, but
you dont want them to be destructive to the operation of the running 
program. Therefore the current instruction is allowed to finish
(which I facilitate by doing the whole thing when cycles == 0) and 
then the current program counter is stored on the stack. Then the
current status register is stored on the stack. When the routine
that services the interrupt has finished, the status register
and program counter can be restored to how they where before it 
occurred. This is impemented by the "RTI" instruction. Once the IRQ
has happened, in a similar way to a reset, a programmable address
is read form hard coded location 0xFFFE, which is subsequently
set to the program counter.*/
void IRQ()
{
    // If interrupts are allowed
    if (!(P & sfI))
    {
        // Push the program counter to the stack. It's 16-bits dont
        // forget so that takes two pushes
        write(0x0100 + S, (PC >> 8) & 0x00FF); S--;
        write(0x0100 + S, PC & 0x00FF); S--;

        // Then Push the status register to the stack
        P &= ~sfB; P |= sfU; P |= sfI;
        write(0x0100 + S, P); S--;

        // Read new program counter location from fixed address
        PC = (0xffff << 8) | 0xfffe;

        // IRQs take time
        //cycles = 7;
    }
}


// A Non-Maskable Interrupt cannot be ignored. It behaves in exactly the
// same way as a regular IRQ, but reads the new program counter address
// form location 0xFFFA.
void NMI()
{
    write(0x0100 + S, (PC >> 8) & 0x00FF); S--;
    write(0x0100 + S, PC & 0x00FF); S--;
    P &= ~sfB; P |= sfU; P |= sfI;
    write(0x0100 + S, P); S--;
    PC = (0xfffb << 8) | 0xfffa;
    //cycles = 8;
}

    // Perform one clock cycles worth of emulation
    void CLK()
    {
        /* Each instruction requires a variable number of clock cycles to execute.
        In my emulation, I only care about the final result and so I perform
        the entire computation in one hit. In hardware, each clock cycle would
        perform "microcode" style transformations of the CPUs state.
        
        To remain compliant with connected devices, it's important that the 
        emulation also takes "time" in order to execute instructions, so I
        implement that delay by simply counting down the cycles required by 
        the instruction. When it reaches 0, the instruction is complete, and
         the next one is ready to be executed.*/
        if (cycles == 0)
        {
            /* Read next instruction byte. This 8-bit value is used to index
            the translation table to get the relevant information about
            how to implement the instruction*/
            //opcode = read(pc);

            // Always set the unused status flag bit to 1
            P |= sfU;

            // Increment program counter, we read the opcode byte
            PC++;

            // Get Starting number of cycles
            //cycles = lookup[opcode].cycles;

            // Perform fetch of intermmediate data using the
            // required addressing mode
            //uint8_t additional_cycle1 = (this->*lookup[opcode].addrmode)();

            // Perform operation
            //uint8_t additional_cycle2 = (this->*lookup[opcode].operate)();

            // The addressmode and opcode may have altered the number
            // of cycles this instruction requires before its completed
            //cycles += (additional_cycle1 & additional_cycle2);

            // Always set the unused status flag bit to 1
            P |= sfU;
        }

        // Increment global clock count - This is actually unused unless logging is enabled
        // but I've kept it in because its a handy watch variable for debugging
        //clock_count++;

        // Decrement the number of cycles remaining for this instruction
        //cycles--;
    }

    // #################################################

    /*####### ADDRESSING MODES [7] (with some typos fix):
    0x0000 to 0xFFFF
    HIGH often referred to as the "page";
    LOW is the offset into that page.
    This implies there are 256 pages, each containing 256 bytes.

    If both instruction and address function return 1, then an
    additional clock cycle is required.*/
    uint8_t IMP(); uint8_t IMM();
    uint8_t ZP0(); uint8_t ZPX();
    uint8_t ZPY(); uint8_t REL();
    uint8_t ABS(); uint8_t ABX();
    uint8_t ABY(); uint8_t IND();
    uint8_t IZX(); uint8_t IZY();

    /*The 6502 can address between 0x0000 - 0xFFFF. The high byte is often referred
    to as the "page", and the low byte is the offset into that page. This implies
    there are 256 pages, each containing 256 bytes.

    Several addressing modes have the potential to require an additional clock
    cycle if they cross a page boundary. This is combined with several instructions
    that enable this additional clock cycle. So each addressing function returns
    a flag saying it has potential, as does each instruction. If both instruction
    and address function return 1, then an additional clock cycle is required.


    Address Mode: Implied
    There is no additional data required for this instruction. The instruction
    does something very simple like sets a status bit. However, we will
    target the accumulator, for instructions like PHA*/
    uint8_t IMP()
    {
        fetched = A;
        return 0;
    }


    // Address Mode: Immediate
    // The instruction expects the next byte to be used as a value, so we'll prep
    // the read address to point to the next byte
    uint8_t IMM()
    {
        addr_abs = pc++;
        return 0;
    }



    // Address Mode: Zero Page
    // To save program bytes, zero page addressing allows you to absolutely address
    // a location in first 0xFF bytes of address range. Clearly this only requires
    // one byte instead of the usual two.
    uint8_t ZP0()
    {
        addr_abs = read(pc);
        pc++;
        addr_abs &= 0x00FF;
        return 0;
    }



    // Address Mode: Zero Page with X Offset
    // Fundamentally the same as Zero Page addressing, but the contents of the X Register
    // is added to the supplied single byte address. This is useful for iterating through
    // ranges within the first page.
    uint8_t ZPX()
    {
        addr_abs = (read(pc) + x);
        pc++;
        addr_abs &= 0x00FF;
        return 0;
    }


    // Address Mode: Zero Page with Y Offset
    // Same as above but uses Y Register for offset
    uint8_t ZPY()
    {
        addr_abs = (read(pc) + y);
        pc++;
        addr_abs &= 0x00FF;
        return 0;
    }


    // Address Mode: Relative
    // This address mode is exclusive to branch instructions. The address
    // must reside within -128 to +127 of the branch instruction, i.e.
    // you cant directly branch to any address in the addressable range.
    uint8_t REL()
    {
        addr_rel = read(pc);
        pc++;
        if (addr_rel & 0x80)
            addr_rel |= 0xFF00;
        return 0;
    }


    // Address Mode: Absolute 
    // A full 16-bit address is loaded and used
    uint8_t ABS()
    {
        uint16_t lo = read(pc);
        pc++;
        uint16_t hi = read(pc);
        pc++;

        addr_abs = (hi << 8) | lo;

        return 0;
    }


    // Address Mode: Absolute with X Offset
    // Fundamentally the same as absolute addressing, but the contents of the X Register
    // is added to the supplied two byte address. If the resulting address changes
    // the page, an additional clock cycle is required
    uint8_t ABX()
    {
        uint16_t lo = read(pc);
        pc++;
        uint16_t hi = read(pc);
        pc++;

        addr_abs = (hi << 8) | lo;
        addr_abs += x;

        if ((addr_abs & 0xFF00) != (hi << 8))
            return 1;
        else
            return 0;
    }


    // Address Mode: Absolute with Y Offset
    // Fundamentally the same as absolute addressing, but the contents of the Y Register
    // is added to the supplied two byte address. If the resulting address changes
    // the page, an additional clock cycle is required
    uint8_t ABY()
    {
        uint16_t lo = read(pc);
        pc++;
        uint16_t hi = read(pc);
        pc++;

        addr_abs = (hi << 8) | lo;
        addr_abs += y;

        if ((addr_abs & 0xFF00) != (hi << 8))
            return 1;
        else
            return 0;
    }

    // Note: The next 3 address modes use indirection (aka Pointers!)

    // Address Mode: Indirect
    // The supplied 16-bit address is read to get the actual 16-bit address. This is
    // instruction is unusual in that it has a bug in the hardware! To emulate its
    // function accurately, we also need to emulate this bug. If the low byte of the
    // supplied address is 0xFF, then to read the high byte of the actual address
    // we need to cross a page boundary. This doesnt actually work on the chip as 
    // designed, instead it wraps back around in the same page, yielding an 
    // invalid actual address
    uint8_t IND()
    {
        uint16_t ptr_lo = read(pc);
        pc++;
        uint16_t ptr_hi = read(pc);
        pc++;

        uint16_t ptr = (ptr_hi << 8) | ptr_lo;

        if (ptr_lo == 0x00FF) // Simulate page boundary hardware bug
        {
            addr_abs = (read(ptr & 0xFF00) << 8) | read(ptr + 0);
        }
        else // Behave normally
        {
            addr_abs = (read(ptr + 1) << 8) | read(ptr + 0);
        }

        return 0;
    }


    // Address Mode: Indirect X
    // The supplied 8-bit address is offset by X Register to index
    // a location in page 0x00. The actual 16-bit address is read 
    // from this location
    uint8_t IZX()
    {
        uint16_t t = read(pc);
        pc++;

        uint16_t lo = read((uint16_t)(t + (uint16_t)x) & 0x00FF);
        uint16_t hi = read((uint16_t)(t + (uint16_t)x + 1) & 0x00FF);

        addr_abs = (hi << 8) | lo;

        return 0;
    }


    // Address Mode: Indirect Y
    // The supplied 8-bit address indexes a location in page 0x00. From 
    // here the actual 16-bit address is read, and the contents of
    // Y Register is added to it to offset it. If the offset causes a
    // change in page then an additional clock cycle is required.
    uint8_t IZY()
    {
        uint16_t t = read(pc);
        pc++;

        uint16_t lo = read(t & 0x00FF);
        uint16_t hi = read((t + 1) & 0x00FF);

        addr_abs = (hi << 8) | lo;
        addr_abs += y;

        if ((addr_abs & 0xFF00) != (hi << 8))
            return 1;
        else
            return 0;
    }

    // #################################################

	// INSTRUCTION IMPLEMENTATIONS

// Note: Ive started with the two most complicated instructions to emulate, which
// ironically is addition and subtraction! Ive tried to include a detailed 
// explanation as to why they are so complex, yet so fundamental. Im also NOT
// going to do this through the explanation of 1 and 2's complement.

// Instruction: Add with Carry In
// Function:    A = A + M + C
// Flags Out:   C, V, N, Z
//
// Explanation:
// The purpose of this function is to add a value to the accumulator and a carry bit. If
// the result is > 255 there is an overflow setting the carry bit. Ths allows you to
// chain together ADC instructions to add numbers larger than 8-bits. This in itself is
// simple, however the 6502 supports the concepts of Negativity/Positivity and Signed Overflow.
//
// 10000100 = 128 + 4 = 132 in normal circumstances, we know this as unsigned and it allows
// us to represent numbers between 0 and 255 (given 8 bits). The 6502 can also interpret 
// this word as something else if we assume those 8 bits represent the range -128 to +127,
// i.e. it has become signed.
//
// Since 132 > 127, it effectively wraps around, through -128, to -124. This wraparound is
// called overflow, and this is a useful to know as it indicates that the calculation has
// gone outside the permissable range, and therefore no longer makes numeric sense.
//
// Note the implementation of ADD is the same in binary, this is just about how the numbers
// are represented, so the word 10000100 can be both -124 and 132 depending upon the 
// context the programming is using it in. We can prove this!
//
//  10000100 =  132  or  -124
// +00010001 = + 17      + 17
//  ========    ===       ===     See, both are valid additions, but our interpretation of
//  10010101 =  149  or  -107     the context changes the value, not the hardware!
//
// In principle under the -128 to 127 range:
// 10000000 = -128, 11111111 = -1, 00000000 = 0, 00000000 = +1, 01111111 = +127
// therefore negative numbers have the most significant set, positive numbers do not
//
// To assist us, the 6502 can set the overflow flag, if the result of the addition has
// wrapped around. V <- ~(A^M) & A^(A+M+C) :D lol, let's work out why!
//
// Let's suppose we have A = 30, M = 10 and C = 0
//          A = 30 = 00011110
//          M = 10 = 00001010+
//     RESULT = 40 = 00101000
//
// Here we have not gone out of range. The resulting significant bit has not changed.
// So let's make a truth table to understand when overflow has occurred. Here I take
// the MSB of each component, where R is RESULT.
//
// A  M  R | V | A^R | A^M |~(A^M) | 
// 0  0  0 | 0 |  0  |  0  |   1   |
// 0  0  1 | 1 |  1  |  0  |   1   |
// 0  1  0 | 0 |  0  |  1  |   0   |
// 0  1  1 | 0 |  1  |  1  |   0   |  so V = ~(A^M) & (A^R)
// 1  0  0 | 0 |  1  |  1  |   0   |
// 1  0  1 | 0 |  0  |  1  |   0   |
// 1  1  0 | 1 |  1  |  0  |   1   |
// 1  1  1 | 0 |  0  |  0  |   1   |
//
// We can see how the above equation calculates V, based on A, M and R. V was chosen
// based on the following hypothesis:
//       Positive Number + Positive Number = Negative Result -> Overflow
//       Negative Number + Negative Number = Positive Result -> Overflow
//       Positive Number + Negative Number = Either Result -> Cannot Overflow
//       Positive Number + Positive Number = Positive Result -> OK! No Overflow
//       Negative Number + Negative Number = Negative Result -> OK! NO Overflow

	uint8_t ADC()
	{
		// Grab the data that we are adding to the accumulator
		fetch();

		// Add is performed in 16-bit domain for emulation to capture any
		// carry bit, which will exist in bit 8 of the 16-bit word
		temp = (uint16_t)a + (uint16_t)fetched + (uint16_t)GetFlag(C);

		// The carry flag out exists in the high byte bit 0
		SetFlag(C, temp > 255);

		// The Zero flag is set if the result is 0
		SetFlag(Z, (temp & 0x00FF) == 0);

		// The signed Overflow flag is set based on all that up there! :D
		SetFlag(V, (~((uint16_t)a ^ (uint16_t)fetched) & ((uint16_t)a ^ (uint16_t)temp)) & 0x0080);

		// The negative flag is set to the most significant bit of the result
		SetFlag(N, temp & 0x80);

		// Load the result into the accumulator (it's 8-bit dont forget!)
		a = temp & 0x00FF;

		// This instruction has the potential to require an additional clock cycle
		return 1;
	}


	/* ####### OPCODES:
    There are 56 "legitimate" opcodes provided by the 6502 CPU.
    Unofficial codes will of course also influence the CPU circuitry in interesting ways,
    and can be exploited to gain additional functionality.
    Return '1' if busy.*/
	uint8_t ADC();	uint8_t AND();	uint8_t ASL();	uint8_t BCC();
	uint8_t BCS();	uint8_t BEQ();	uint8_t BIT();	uint8_t BMI();
	uint8_t BNE();	uint8_t BPL();	uint8_t BRK();	uint8_t BVC();
	uint8_t BVS();	uint8_t CLC();	uint8_t CLD();	uint8_t CLI();
	uint8_t CLV();	uint8_t CMP();	uint8_t CPX();	uint8_t CPY();
	uint8_t DEC();	uint8_t DEX();	uint8_t DEY();	uint8_t EOR();
	uint8_t INC();	uint8_t INX();	uint8_t INY();	uint8_t JMP();
	uint8_t JSR();	uint8_t LDA();	uint8_t LDX();	uint8_t LDY();
	uint8_t LSR();	uint8_t NOP();	uint8_t ORA();	uint8_t PHA();
	uint8_t PHP();	uint8_t PLA();	uint8_t PLP();	uint8_t ROL();
	uint8_t ROR();	uint8_t RTI();	uint8_t RTS();	uint8_t SBC();
	uint8_t SEC();	uint8_t SED();	uint8_t SEI();	uint8_t STA();
	uint8_t STX();	uint8_t STY();	uint8_t TAX();	uint8_t TAY();
	uint8_t TSX();	uint8_t TXA();	uint8_t TXS();	uint8_t TYA();

	/* "Unofficial" opcodes. It is functionally identical to a NOP:
	uint8_t XXX();

	Instruction: Subtraction with Borrow In
	Function:  A = A - M - (1 - C)
	Flags Out: C, V, N, Z
	Explanation:
	Given the explanation for ADC above, we can reorganise our data
	to use the same computation for addition, for subtraction by multiplying
	the data by -1, i.e. make it negative
	
	A = A - M - (1 - C)  ->  A = A + -1 * (M - (1 - C))  ->  A = A + (-M + 1 + C)
	
	To make a signed positive number negative, we can invert the bits and add 1
	(OK, I lied, a little bit of 1 and 2s complement :P)
	
	 5 = 00000101
	-5 = 11111010 + 00000001 = 11111011 (or 251 in our 0 to 255 range)
	
	The range is actually unimportant, because if I take the value 15, and add 251
	to it, given we wrap around at 256, the result is 10, so it has effectively 
	subtracted 5, which was the original intention. (15 + 251) % 256 = 10
	
	Note that the equation above used (1 - C), but this got converted to + 1 + C.
	This means we already have the +1, so all we need to do is invert the bits
	of M, the data(!) therfore we can simply add, exactly the same way we did
	before.*/
	uint8_t SBC()
	{
		fetch();

		// Operating in 16-bit domain to capture carry out

		// We can invert the bottom 8 bits with bitwise xor
		uint16_t value = ((uint16_t)fetched) ^ 0x00FF;

		// Notice this is exactly the same as addition from here!
		temp = (uint16_t)a + value + (uint16_t)GetFlag(C);
		SetFlag(C, temp & 0xFF00);
		SetFlag(Z, ((temp & 0x00FF) == 0));
		SetFlag(V, (temp ^ (uint16_t)a) & (temp ^ value) & 0x0080);
		SetFlag(N, temp & 0x0080);
		a = temp & 0x00FF;
		return 1;
	}

	// OK! Complicated operations are done! the following are much simpler
	// and conventional. The typical order of events is:
	// 1) Fetch the data you are working with
	// 2) Perform calculation
	// 3) Store the result in desired place
	// 4) Set Flags of the status register
	// 5) Return if instruction has potential to require additional 
	//    clock cycle


	// Instruction: Bitwise Logic AND
	// Function:    A = A & M
	// Flags Out:   N, Z
	uint8_t AND()
	{
		fetch();
		a = a & fetched;
		SetFlag(Z, a == 0x00);
		SetFlag(N, a & 0x80);
		return 1;
	}


	// Instruction: Arithmetic Shift Left
	// Function:    A = C <- (A << 1) <- 0
	// Flags Out:   N, Z, C
	uint8_t ASL()
	{
		fetch();
		temp = (uint16_t)fetched << 1;
		SetFlag(C, (temp & 0xFF00) > 0);
		SetFlag(Z, (temp & 0x00FF) == 0x00);
		SetFlag(N, temp & 0x80);
		if (lookup[opcode].addrmode == &olc6502::IMP)
			a = temp & 0x00FF;
		else
			write(addr_abs, temp & 0x00FF);
		return 0;
	}


	// Instruction: Branch if Carry Clear
	// Function:    if(C == 0) pc = address 
	uint8_t BCC()
	{
		if (GetFlag(C) == 0)
		{
			cycles++;
			addr_abs = pc + addr_rel;

			if ((addr_abs & 0xFF00) != (pc & 0xFF00))
				cycles++;

			pc = addr_abs;
		}
		return 0;
	}


	// Instruction: Branch if Carry Set
	// Function:    if(C == 1) pc = address
	uint8_t BCS()
	{
		if (GetFlag(C) == 1)
		{
			cycles++;
			addr_abs = pc + addr_rel;

			if ((addr_abs & 0xFF00) != (pc & 0xFF00))
				cycles++;

			pc = addr_abs;
		}
		return 0;
	}


	// Instruction: Branch if Equal
	// Function:    if(Z == 1) pc = address
	uint8_t BEQ()
	{
		if (GetFlag(Z) == 1)
		{
			cycles++;
			addr_abs = pc + addr_rel;

			if ((addr_abs & 0xFF00) != (pc & 0xFF00))
				cycles++;

			pc = addr_abs;
		}
		return 0;
	}

	uint8_t BIT()
	{
		fetch();
		temp = a & fetched;
		SetFlag(Z, (temp & 0x00FF) == 0x00);
		SetFlag(N, fetched & (1 << 7));
		SetFlag(V, fetched & (1 << 6));
		return 0;
	}


	// Instruction: Branch if Negative
	// Function:    if(N == 1) pc = address
	uint8_t BMI()
	{
		if (GetFlag(N) == 1)
		{
			cycles++;
			addr_abs = pc + addr_rel;

			if ((addr_abs & 0xFF00) != (pc & 0xFF00))
				cycles++;

			pc = addr_abs;
		}
		return 0;
	}


	// Instruction: Branch if Not Equal
	// Function:    if(Z == 0) pc = address
	uint8_t BNE()
	{
		if (GetFlag(Z) == 0)
		{
			cycles++;
			addr_abs = pc + addr_rel;

			if ((addr_abs & 0xFF00) != (pc & 0xFF00))
				cycles++;

			pc = addr_abs;
		}
		return 0;
	}


	// Instruction: Branch if Positive
	// Function:    if(N == 0) pc = address
	uint8_t BPL()
	{
		if (GetFlag(N) == 0)
		{
			cycles++;
			addr_abs = pc + addr_rel;

			if ((addr_abs & 0xFF00) != (pc & 0xFF00))
				cycles++;

			pc = addr_abs;
		}
		return 0;
	}

	// Instruction: Break
	// Function:    Program Sourced Interrupt
	uint8_t BRK()
	{
		pc++;

		SetFlag(I, 1);
		write(0x0100 + stkp, (pc >> 8) & 0x00FF);
		stkp--;
		write(0x0100 + stkp, pc & 0x00FF);
		stkp--;

		SetFlag(B, 1);
		write(0x0100 + stkp, status);
		stkp--;
		SetFlag(B, 0);

		pc = (uint16_t)read(0xFFFE) | ((uint16_t)read(0xFFFF) << 8);
		return 0;
	}


	// Instruction: Branch if Overflow Clear
	// Function:    if(V == 0) pc = address
	uint8_t BVC()
	{
		if (GetFlag(V) == 0)
		{
			cycles++;
			addr_abs = pc + addr_rel;

			if ((addr_abs & 0xFF00) != (pc & 0xFF00))
				cycles++;

			pc = addr_abs;
		}
		return 0;
	}


	// Instruction: Branch if Overflow Set
	// Function:    if(V == 1) pc = address
	uint8_t BVS()
	{
		if (GetFlag(V) == 1)
		{
			cycles++;
			addr_abs = pc + addr_rel;

			if ((addr_abs & 0xFF00) != (pc & 0xFF00))
				cycles++;

			pc = addr_abs;
		}
		return 0;
	}


	// Instruction: Clear Carry Flag
	// Function:    C = 0
	uint8_t CLC()
	{
		SetFlag(C, false);
		return 0;
	}


	// Instruction: Clear Decimal Flag
	// Function:    D = 0
	uint8_t CLD()
	{
		SetFlag(D, false);
		return 0;
	}


	// Instruction: Disable Interrupts / Clear Interrupt Flag
	// Function:    I = 0
	uint8_t CLI()
	{
		SetFlag(I, false);
		return 0;
	}


	// Instruction: Clear Overflow Flag
	// Function:    V = 0
	uint8_t CLV()
	{
		SetFlag(V, false);
		return 0;
	}

	// Instruction: Compare Accumulator
	// Function:    C <- A >= M      Z <- (A - M) == 0
	// Flags Out:   N, C, Z
	uint8_t CMP()
	{
		fetch();
		temp = (uint16_t)a - (uint16_t)fetched;
		SetFlag(C, a >= fetched);
		SetFlag(Z, (temp & 0x00FF) == 0x0000);
		SetFlag(N, temp & 0x0080);
		return 1;
	}


	// Instruction: Compare X Register
	// Function:    C <- X >= M      Z <- (X - M) == 0
	// Flags Out:   N, C, Z
	uint8_t CPX()
	{
		fetch();
		temp = (uint16_t)x - (uint16_t)fetched;
		SetFlag(C, x >= fetched);
		SetFlag(Z, (temp & 0x00FF) == 0x0000);
		SetFlag(N, temp & 0x0080);
		return 0;
	}


	// Instruction: Compare Y Register
	// Function:    C <- Y >= M      Z <- (Y - M) == 0
	// Flags Out:   N, C, Z
	uint8_t CPY()
	{
		fetch();
		temp = (uint16_t)y - (uint16_t)fetched;
		SetFlag(C, y >= fetched);
		SetFlag(Z, (temp & 0x00FF) == 0x0000);
		SetFlag(N, temp & 0x0080);
		return 0;
	}


	// Instruction: Decrement Value at Memory Location
	// Function:    M = M - 1
	// Flags Out:   N, Z
	uint8_t DEC()
	{
		fetch();
		temp = fetched - 1;
		write(addr_abs, temp & 0x00FF);
		SetFlag(Z, (temp & 0x00FF) == 0x0000);
		SetFlag(N, temp & 0x0080);
		return 0;
	}


	// Instruction: Decrement X Register
	// Function:    X = X - 1
	// Flags Out:   N, Z
	uint8_t DEX()
	{
		x--;
		SetFlag(Z, x == 0x00);
		SetFlag(N, x & 0x80);
		return 0;
	}


	// Instruction: Decrement Y Register
	// Function:    Y = Y - 1
	// Flags Out:   N, Z
	uint8_t DEY()
	{
		y--;
		SetFlag(Z, y == 0x00);
		SetFlag(N, y & 0x80);
		return 0;
	}


	// Instruction: Bitwise Logic XOR
	// Function:    A = A xor M
	// Flags Out:   N, Z
	uint8_t EOR()
	{
		fetch();
		a = a ^ fetched;
		SetFlag(Z, a == 0x00);
		SetFlag(N, a & 0x80);
		return 1;
	}


	// Instruction: Increment Value at Memory Location
	// Function:    M = M + 1
	// Flags Out:   N, Z
	uint8_t INC()
	{
		fetch();
		temp = fetched + 1;
		write(addr_abs, temp & 0x00FF);
		SetFlag(Z, (temp & 0x00FF) == 0x0000);
		SetFlag(N, temp & 0x0080);
		return 0;
	}


	// Instruction: Increment X Register
	// Function:    X = X + 1
	// Flags Out:   N, Z
	uint8_t INX()
	{
		x++;
		SetFlag(Z, x == 0x00);
		SetFlag(N, x & 0x80);
		return 0;
	}


	// Instruction: Increment Y Register
	// Function:    Y = Y + 1
	// Flags Out:   N, Z
	uint8_t INY()
	{
		y++;
		SetFlag(Z, y == 0x00);
		SetFlag(N, y & 0x80);
		return 0;
	}


	// Instruction: Jump To Location
	// Function:    pc = address
	uint8_t JMP()
	{
		pc = addr_abs;
		return 0;
	}


	// Instruction: Jump To Sub-Routine
	// Function:    Push current pc to stack, pc = address
	uint8_t JSR()
	{
		pc--;

		write(0x0100 + stkp, (pc >> 8) & 0x00FF);
		stkp--;
		write(0x0100 + stkp, pc & 0x00FF);
		stkp--;

		pc = addr_abs;
		return 0;
	}


	// Instruction: Load The Accumulator
	// Function:    A = M
	// Flags Out:   N, Z
	uint8_t LDA()
	{
		fetch();
		a = fetched;
		SetFlag(Z, a == 0x00);
		SetFlag(N, a & 0x80);
		return 1;
	}


	// Instruction: Load The X Register
	// Function:    X = M
	// Flags Out:   N, Z
	uint8_t LDX()
	{
		fetch();
		x = fetched;
		SetFlag(Z, x == 0x00);
		SetFlag(N, x & 0x80);
		return 1;
	}


	// Instruction: Load The Y Register
	// Function:    Y = M
	// Flags Out:   N, Z
	uint8_t LDY()
	{
		fetch();
		y = fetched;
		SetFlag(Z, y == 0x00);
		SetFlag(N, y & 0x80);
		return 1;
	}

	uint8_t LSR()
	{
		fetch();
		SetFlag(C, fetched & 0x0001);
		temp = fetched >> 1;
		SetFlag(Z, (temp & 0x00FF) == 0x0000);
		SetFlag(N, temp & 0x0080);
		if (lookup[opcode].addrmode == &olc6502::IMP)
			a = temp & 0x00FF;
		else
			write(addr_abs, temp & 0x00FF);
		return 0;
	}

	uint8_t NOP()
	{
		switch (opcode) {
		case 0x1C:
		case 0x3C:
		case 0x5C:
		case 0x7C:
		case 0xDC:
		case 0xFC:
			return 1;
			break;
		}
		return 0;
	}


	// Instruction: Bitwise Logic OR
	// Function:    A = A | M
	// Flags Out:   N, Z
	uint8_t ORA()
	{
		fetch();
		a = a | fetched;
		SetFlag(Z, a == 0x00);
		SetFlag(N, a & 0x80);
		return 1;
	}


	// Instruction: Push Accumulator to Stack
	// Function:    A -> stack
	uint8_t PHA()
	{
		write(0x0100 + stkp, a);
		stkp--;
		return 0;
	}


	// Instruction: Push Status Register to Stack
	// Function:    status -> stack
	// Note:        Break flag is set to 1 before push
	uint8_t PHP()
	{
		write(0x0100 + stkp, status | B | U);
		SetFlag(B, 0);
		SetFlag(U, 0);
		stkp--;
		return 0;
	}


	// Instruction: Pop Accumulator off Stack
	// Function:    A <- stack
	// Flags Out:   N, Z
	uint8_t PLA()
	{
		stkp++;
		a = read(0x0100 + stkp);
		SetFlag(Z, a == 0x00);
		SetFlag(N, a & 0x80);
		return 0;
	}


	// Instruction: Pop Status Register off Stack
	// Function:    Status <- stack
	uint8_t PLP()
	{
		stkp++;
		status = read(0x0100 + stkp);
		SetFlag(U, 1);
		return 0;
	}

	uint8_t ROL()
	{
		fetch();
		temp = (uint16_t)(fetched << 1) | GetFlag(C);
		SetFlag(C, temp & 0xFF00);
		SetFlag(Z, (temp & 0x00FF) == 0x0000);
		SetFlag(N, temp & 0x0080);
		if (lookup[opcode].addrmode == &olc6502::IMP)
			a = temp & 0x00FF;
		else
			write(addr_abs, temp & 0x00FF);
		return 0;
	}

	uint8_t ROR()
	{
		fetch();
		temp = (uint16_t)(GetFlag(C) << 7) | (fetched >> 1);
		SetFlag(C, fetched & 0x01);
		SetFlag(Z, (temp & 0x00FF) == 0x00);
		SetFlag(N, temp & 0x0080);
		if (lookup[opcode].addrmode == &olc6502::IMP)
			a = temp & 0x00FF;
		else
			write(addr_abs, temp & 0x00FF);
		return 0;
	}

	uint8_t RTI()
	{
		stkp++;
		status = read(0x0100 + stkp);
		status &= ~B;
		status &= ~U;

		stkp++;
		pc = (uint16_t)read(0x0100 + stkp);
		stkp++;
		pc |= (uint16_t)read(0x0100 + stkp) << 8;
		return 0;
	}

	uint8_t RTS()
	{
		stkp++;
		pc = (uint16_t)read(0x0100 + stkp);
		stkp++;
		pc |= (uint16_t)read(0x0100 + stkp) << 8;

		pc++;
		return 0;
	}




	// Instruction: Set Carry Flag
	// Function:    C = 1
	uint8_t SEC()
	{
		SetFlag(C, true);
		return 0;
	}


	// Instruction: Set Decimal Flag
	// Function:    D = 1
	uint8_t SED()
	{
		SetFlag(D, true);
		return 0;
	}


	// Instruction: Set Interrupt Flag / Enable Interrupts
	// Function:    I = 1
	uint8_t SEI()
	{
		SetFlag(I, true);
		return 0;
	}


	// Instruction: Store Accumulator at Address
	// Function:    M = A
	uint8_t STA()
	{
		write(addr_abs, a);
		return 0;
	}


	// Instruction: Store X Register at Address
	// Function:    M = X
	uint8_t STX()
	{
		write(addr_abs, x);
		return 0;
	}


	// Instruction: Store Y Register at Address
	// Function:    M = Y
	uint8_t STY()
	{
		write(addr_abs, y);
		return 0;
	}


	// Instruction: Transfer Accumulator to X Register
	// Function:    X = A
	// Flags Out:   N, Z
	uint8_t TAX()
	{
		x = a;
		SetFlag(Z, x == 0x00);
		SetFlag(N, x & 0x80);
		return 0;
	}


	// Instruction: Transfer Accumulator to Y Register
	// Function:    Y = A
	// Flags Out:   N, Z
	uint8_t TAY()
	{
		y = a;
		SetFlag(Z, y == 0x00);
		SetFlag(N, y & 0x80);
		return 0;
	}


	// Instruction: Transfer Stack Pointer to X Register
	// Function:    X = stack pointer
	// Flags Out:   N, Z
	uint8_t TSX()
	{
		x = stkp;
		SetFlag(Z, x == 0x00);
		SetFlag(N, x & 0x80);
		return 0;
	}


	// Instruction: Transfer X Register to Accumulator
	// Function:    A = X
	// Flags Out:   N, Z
	uint8_t TXA()
	{
		a = x;
		SetFlag(Z, a == 0x00);
		SetFlag(N, a & 0x80);
		return 0;
	}


	// Instruction: Transfer X Register to Stack Pointer
	// Function:    stack pointer = X
	uint8_t TXS()
	{
		stkp = x;
		return 0;
	}


	// Instruction: Transfer Y Register to Accumulator
	// Function:    A = Y
	// Flags Out:   N, Z
	uint8_t TYA()
	{
		a = y;
		SetFlag(Z, a == 0x00);
		SetFlag(N, a & 0x80);
		return 0;
	}


	// This function captures illegal opcodes
	uint8_t XXX()
	{
		return 0;
	}



#endif // SCPARSE_