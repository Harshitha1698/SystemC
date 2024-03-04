#include <systemc.h>
using namespace std;


SC_MODULE(NAND)
{
sc_in<bool> A;
sc_in<bool> B;
sc_out<bool> Z;

void do_nand(){
Z.write(!(A.read() && B.read())); 
}

SC_CTOR(NAND) {  //Macro same as constructor
	SC_METHOD(do_nand);
	sensitive << A<< B ;  //execute compute methos when a or b changes.
	}
};


SC_MODULE(exor)
{
sc_in<bool> A_in;
sc_in<bool> B_in;
sc_out<bool> Z_out;

NAND nand_a,nand_b,nand_c,nand_d;
sc_signal<bool> h1,h2,h3;

sc_time currentTime;
unsigned long long currentDelta;

SC_CTOR(exor) : //Macro same as constructor
	//A("A_in"),B("B_in"),Z("Z_out"),  
	A_in("A_in"),B_in("B_in"),Z_out("Z_in"), 
	nand_a("nand_a"),nand_b("nand_b"),nand_c("nand_c"),nand_d("nand_d"),
	h1("h1"),h2("h2"),h3("h3")

	{
	nand_a.A.bind(A_in);
	nand_a.B.bind(B_in);
	nand_a.Z.bind(h1);

	nand_b.A.bind(B_in);
	nand_b.B.bind(h1);
	nand_b.Z.bind(h2);

	nand_c.A.bind(A_in);
	nand_c.B.bind(h1);
	nand_c.Z.bind(h3);

	nand_d.A.bind(h2);
	nand_d.B.bind(h3);
	nand_d.Z.bind(Z_out);
	}

	 void waitAndPrint(sc_time delay)
    {
        wait(delay);
        sc_time time = sc_time_stamp();

        // The sc_delta_count() returns the total number of executed
        // delta delays. In order to estimate the delta delay
        // between the time advances the following is done:
        if(time > currentTime)
        {
           currentDelta = sc_delta_count();
           currentTime = time;
        }

        unsigned long long delta = sc_delta_count() - currentDelta;

        std::cout << time <<" + " << delta << "δ\t"
                  << A_in.read() << "\t"
                  << B_in.read() << "\t"
                  << Z_out.read() << "\t" << std::endl;
    }

    void process()
    {

		sc_signal<bool> sig_1,sig_2,sig_3;
		exor xorr("exor");

		xorr.A_in.bind(sig_1);
		xorr.B_in.bind(sig_2);
		xorr.Z_out.bind(sig_3);

        // Start in Reset State
        waitAndPrint(SC_ZERO_TIME);
        waitAndPrint(SC_ZERO_TIME);
        waitAndPrint(SC_ZERO_TIME);

        // Set:
        std::cout << "\nA=1, B=0\n" << std::endl;
        waitAndPrint(sc_time(10,SC_NS));

        sig_1.write(true);
        sig_2.write(false);

        waitAndPrint(SC_ZERO_TIME);
        waitAndPrint(SC_ZERO_TIME);
        waitAndPrint(SC_ZERO_TIME);

        // Reset:
        std::cout << "\nA=0, B=1\n" << std::endl;
        waitAndPrint(sc_time(10,SC_NS));

        sig_1.write(false);
        sig_2.write(true);

        waitAndPrint(SC_ZERO_TIME);
        waitAndPrint(SC_ZERO_TIME);
        waitAndPrint(SC_ZERO_TIME);

        sc_stop();
    }
};



int sc_main(int __attribute__((unused)) sc_argc,
             char __attribute__((unused)) *sc_argv[])
{
sc_signal<bool> sig_1,sig_2,sig_3;

exor xorr("exor");

sig_1.write(false);
sig_2.write(true);

xorr.A_in.bind(sig_1);
xorr.B_in.bind(sig_2);
xorr.Z_out.bind(sig_3);

//XOR 
// A	B	Z
// 0	0	0
// 0	1	1
// 1	0	1
// 1	1	0
// sc_signal<bool> sig_1,sig_2,sig_3;
// NAND nand("nand");
// sig_1.write(true);
// sig_2.write(false);
// nand.A.bind(sig_1);
// nand.B.bind(sig_2);
// nand.Z.bind(sig_3);



//cout << sig_3.read() << endl;

std::cout << "\nT\t\tA\tB\tZ" << std::endl;

sc_set_stop_mode(SC_STOP_FINISH_DELTA);
sc_start();
return 0;

}