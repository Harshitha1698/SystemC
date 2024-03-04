#include <systemc.h>
using namespace std;

SC_MODULE(AND)
{
sc_in<bool> A;
sc_in<bool> B;
sc_out<bool> Z;

void do_and(){
Z.write(!A.read() && B.read()); 
}

SC_CTOR(AND) {  
	SC_METHOD(do_and);
	sensitive << A << B ;  //execute compute methos when a or b changes.
	}
};
