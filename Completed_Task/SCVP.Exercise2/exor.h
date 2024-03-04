#ifndef EXOR_H
#define EXOR_H

#include <systemc.h>

#include "nand.h"

SC_MODULE(exor)
{
sc_in<bool> A;
sc_in<bool> B;
sc_out<bool> Z;

nand nand_a,nand_b,nand_c,nand_d;
sc_signal<bool> h1,h2,h3;


SC_CTOR(exor) : //Macro same as constructor
	//A("A_in"),B("B_in"),Z("Z_out"),  
	A("A"),B("B"),Z("Z"), 
	nand_a("nand_a"),nand_b("nand_b"),nand_c("nand_c"),nand_d("nand_d"),
	h1("h1"),h2("h2"),h3("h3")

	{
	nand_a.A.bind(A);
	nand_a.B.bind(B);
	nand_a.Z.bind(h1);

	nand_b.A.bind(B);
	nand_b.B.bind(h1);
	nand_b.Z.bind(h2);

	nand_c.A.bind(A);
	nand_c.B.bind(h1);
	nand_c.Z.bind(h3);

	nand_d.A.bind(h2);
	nand_d.B.bind(h3);
	nand_d.Z.bind(Z);
	}
  
};


// int sc_main()
// {
// sc_signal<bool> sig_1,sig_2,sig_3;

// exor xorr("exor");

// sig_1.write(false);
// sig_2.write(true);

// xorr.A.bind(sig_1);
// xorr.B.bind(sig_2);
// xorr.Z.bind(sig_3);

// sc_start();
//XOR 
// A	B	Z
// 0	0	0
// 0	1	1
// 1	0	1
// 1	1	0

//return 0;

// TODO: Insert your code here

#endif // EXOR_H
  