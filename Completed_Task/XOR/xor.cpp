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

SC_MODULE(XOR)
{
    sc_in<bool> A;
    sc_in<bool> B;
    sc_out<bool> Z;

    AND and1, and2;
    OR or1;
    NOT not1, not2;

    sc_signal<bool> h1, h2, h3, h4;

    SC_CTOR(XOR) : A("A"), B("B"), Z("Z"), and1("and1"), and2("and2"), or1("or1"), not1("not1"), not2("not2"),
                  h1("h1"), h2("h2"), h3("h3"), h4("h4")
    {
        not1.A(A);
        not1.Z(h1);

        not2.A(B);
        not2.Z(h2);

        and1.A(h1);
        and1.B(B);
        and1.Z(h3);

        and2.A(A);
        and2.B(h2);
        and2.Z(h4);

        or1.A(h4);
        or1.B(h3);
        or1.Z(Z);
    }
};

    int sc_main(int, char**)
    {
    sc_signal<bool> sigA, sigB, sigZ;

    stim Stim1("Stimulus");
    Stim1.A(sigA);
    Stim1.B(sigB);

    XOR DUT("XOR");
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



