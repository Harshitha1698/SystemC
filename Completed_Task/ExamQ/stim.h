#include <systemc.h>

SC_MODULE(stim)
{
public:
    sc_out<bool> A, B;

    SC_CTOR(stim)
    {
        SC_THREAD(StimGen);
        sensitive << A << B;
    }

private:
    void StimGen()
    {
        wait(SC_ZERO_TIME);
        //wait(10, SC_NS);
        A.write(false);
        B.write(false);
        wait(10, SC_NS);
        A.write(false);
        B.write(true);
        wait(10, SC_NS);
        A.write(true);
        B.write(false);
        wait(10, SC_NS);
        A.write(false);
        B.write(false);
        wait(10, SC_NS);
        A.write(false);
        B.write(true);
        wait(10, SC_NS);
        // A.write(true);
        // B.write(false);
        // wait(10, SC_NS);
        // A.write(true);
        // B.write(true);
        // wait(10, SC_NS);
        // A.write(false);
        // B.write(false);
        // wait(10, SC_NS);
        // A.write(false);
        // B.write(true);
        // wait(10, SC_NS);
        sc_stop();
    }
};