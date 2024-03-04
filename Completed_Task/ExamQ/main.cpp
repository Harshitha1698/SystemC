
#include <systemc.h>
#include "mon.h"
#include "stim.h"
using namespace std;

SC_MODULE(AND)
{
sc_in<bool> A;
sc_in<bool> B;
sc_out<bool> Z;

void do_and(){
Z.write((!(A.read())) && B.read()); 
}

SC_CTOR(AND) {  
	SC_METHOD(do_and);
	sensitive << A << B ;  //execute compute methos when a or b changes.
	}
};

SC_MODULE(OR)
{
sc_in<bool> A;
sc_in<bool> B;
sc_out<bool> Z;

void do_or(){
Z.write(A.read() || B.read()); 
}

SC_CTOR(OR) {  
	SC_METHOD(do_or);
	sensitive << A << B ;  //execute compute methos when a or b changes.
	}
};

SC_MODULE(topmodule)
{
sc_in<bool> A;
sc_in<bool> B;
sc_out<bool> Z;

AND and1;
OR or1;
sc_signal<bool> h1,h2;


SC_CTOR(topmodule) : //Macro same as constructor 
	A("A"),B("B"),Z("Z"),h1("h1"),h2("h2"),
	and1("and1"),or1("or1")
	{

    or1.A.bind(Z);
    or1.B.bind(B);
    or1.Z.bind(h1);

    and1.A.bind(A);
    and1.B.bind(B);
    and1.Z.bind(Z);

	}
};


int sc_main(int, char**)
{
    sc_signal<bool> sigA, sigB, sigZ;

    stim Stim1("Stimulus");
    Stim1.A(sigA);
    Stim1.B(sigB);

    topmodule DUT("topmodule");
    DUT.A(sigA);
    DUT.B(sigB);
    DUT.Z(sigZ);


    Monitor mon("Monitor");
    mon.A(sigA);
    mon.B(sigB);
    mon.Z(sigZ);
    
    sc_start();  // run forever

    return 0;
}


// TODO: Insert your code here

