#include <systemc.h>
#include "mon.h"
#include "stim.h"
using namespace std;

SC_MODULE(nand)
{
    sc_in<bool> A;
    sc_in<bool> B;
    sc_out<bool> Z;

    void process()
    {
        Z.write(!(A.read() && B.read()));
    }

    SC_CTOR(nand)
    {
        SC_METHOD(process);
        sensitive << A << B << Z;
    }
};

SC_MODULE(toplevel)
{

    private:
    nand n1;
    unsigned int cnt;

    sc_signal<bool> A;
    sc_signal<bool> B;
    sc_signal<bool> Z;

    public:
    SC_CTOR(toplevel) : n1("n1"), cnt(0)
    {
        n1.A.bind(A);
        n1.B.bind(B);
        n1.Z.bind(Z);

        SC_METHOD(process);
        sensitive << A << B << Z;
    }


    void process()
    {
        
        cnt++;

        A.write(false);
        B.write(false);

        
        std::cout << "SC_METHOD process() trigger counter " << cnt << " simulation time " << sc_time_stamp().to_default_time_units() << " ps Δ cycle " << sc_delta_count() << ":\tA " << (A.read() ? "'1'" : "'0'") << " B " << (B.read() ? "'1'" : "'0'") << " Z " << (Z.read() ? "'1'" : "'0'") << std::endl;

        // Here both signals A and B are set to true.
        A.write(true);
        B.write(true);

        // This is the second message that is printed when the process is
        // executed.
        std::cout << "SC_METHOD process() trigger counter " << cnt << " simulation time " << sc_time_stamp().to_default_time_units() << " ps Δ cycle " << sc_delta_count() << ":\tA " << (A.read() ? "'1'" : "'0'") << " B " << (B.read() ? "'1'" : "'0'") << " Z " << (Z.read() ? "'1'" : "'0'") << std::endl;

        // Uncomment the lines below where signals A and B are modified.
        // Check the output messages in the terminal and try to understand
        // what is going on.
        // Questions:
        //  - How these writes to A and B affect Z?
        //  - Is the process triggered when Z changes?
        //  - Are some of the writes to A and B ignored?

        //A.write(false);
        //B.write(false);
        //A.write(true);
        //B.write(false);
        //A.write(false);
        //B.write(true);

        // Print a new line
        std::cout << std::endl;
    }
};

int sc_main(int, char**)
{
    // The toplevel module is instantiated here. Its constructor will be
    // called.
    //toplevel top("toplevel");

    sc_signal<bool> sigA;
    sc_signal<bool> sigB;
    sc_signal<bool> sigZ;
    sc_clock  Clk("Clk", 10, SC_NS);


    stim Stim1("Stimulus");
    Stim1.A(sigA);
    Stim1.B(sigB);
    Stim1.Clk(Clk);

    nand n1("n1");
    n1.A.bind(sigA);
    n1.B.bind(sigB);
    n1.Z.bind(sigZ);

    Monitor mon("Monitor");
    mon.A(sigA);
    mon.B(sigB);
    mon.Z(sigZ);
    mon.Clk(Clk);
    
    sc_start(100,SC_NS);

    return 0;
}

