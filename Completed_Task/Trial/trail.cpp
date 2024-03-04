
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
Z.write(A.read() && B.read()); 
}

SC_CTOR(AND) {  
	SC_METHOD(do_and);
	sensitive << A << B ;  //execute compute methos when a or b changes.
	}
};

SC_MODULE(NOT)
{
sc_in<bool> A;
sc_out<bool> Z;

void do_not(){
Z.write(!A.read()); 
}

SC_CTOR(NOT) {  
	SC_METHOD(do_not);
	sensitive << A ;  //execute compute methos when a or b changes.
	}
};

SC_MODULE(topmodule)
{
sc_in<bool> A;
sc_out<bool> Z;

AND and1;
NOT not1;
sc_signal<bool> h1;


SC_CTOR(topmodule) : //Macro same as constructor 
	A("A"),Z("Z"),h1("h1"),and1("and1"),not1("not1")
	{

    and1.A.bind(A);
    and1.B.bind(h1);
    and1.Z.bind(Z);

    not1.A.bind(Z);
    not1.Z.bind(h1);

	}
};


int sc_main(int, char**)
{
    sc_signal<bool> sigA,sigZ;

    stim Stim1("Stimulus");
    Stim1.A(sigA);
    //Stim1.Z(sigZ);

    topmodule DUT("topmodule");
    DUT.A(sigA);
    DUT.Z(sigZ);

    Monitor mon("Monitor");
    mon.A(sigA);
    mon.Z(sigZ);
    
    sc_start(100,SC_NS);  // run forever

    return 0;
}


// TODO: Insert your code here

