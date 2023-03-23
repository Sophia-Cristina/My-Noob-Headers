		org 0
		
		nop
		nop

		jun	loc_jun
		
sub_1:		jms	sub_2
		bbl	1

sub_2:		jms	sub_3
		bbl	2

sub_3:		bbl	3
		
loc_jun:	jms	sub_1

		ldm	6
		jcn	z,loc_z
		jcn	nz,loc_z

		inc	r6

loc_z:		clb
		jcn	nz,loc_nz
		jcn	z,loc_nz

		inc	r6

loc_nz:		jcn	c,loc_nc
		jcn	nc,loc_nc
		
		inc	r6

loc_nc:		stc
		jcn	nc,loc_c
		jcn	c,loc_c

		inc	r6

loc_c:		ldm	5
		stc
		clb
		cmc
		cma
		clc

		ldm	2		; IAC/DAC
		dac
		dac
		dac
		dac
		iac
		iac
		iac
		iac

		clc			; TCC
		tcc
		stc
		tcc

		clc			; TCS
		tcs
		stc
		tcs

		clc			; DAA
		ldm	11
		daa
		stc
		ldm	2
		daa

		ldm	5		; KBP
		kbp
		ldm	8
		kbp

		dcl			; DCL
		clb
		dcl

		clb			; RAR/RAL test
		ldm	15
		rar
		rar
		rar
		rar
		rar
		ral
		ral
		ral
		ral
		ral

		nop

		clb		
		stc
		rar
		rar
		rar
		rar
		rar
		ral
		ral
		ral
		ral
		ral


		ldm	5		; XCH/ADD/SUB
		xch	r5
		ldm	10
		xch	r5

		xch	r4
		ldm	6
		stc
		add	r4
		sub	r5

		fim	r0r1,012h
		
		src	r0r1
		
		fin	r2r3
		
		fim	r8r9,loc_jin
		
		jin	r8r9
		
		nop
		
loc_jin:	inc	r1
		
		fim	r0r1,20h
		clb

loc_isz:	src	r0r1
		iac		
		wrm
		isz	r1,loc_isz

		ldm	2
		wrm
		iac
		wmp
		iac
		wrr
		iac
		wpm
		iac
		wr0
		iac
		wr1
		iac
		wr2
		iac
		wr3

		rd0
		rd1
		rd2
		rd3

		sbm
		rdm
		rdr
		adm

		fim	r0r1,01h
		fim	r2r3,23h
		fim	r4r5,45h
		fim	r6r7,67h
		fim	r8r9,89h
		fim	rarb,0abh
		fim	rcrd,0cdh
		fim	rerf,0efh

loc_t:		iac
		jcn	t,loc_t

loc_nt:		jcn	nt,loc_nt
		jun	loc_t

