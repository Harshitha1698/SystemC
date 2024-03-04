

#include <iostream>
#include <systemc.h>

SC_MODULE(Monitor)
{
public:
    sc_in<bool> A,Z;

    SC_CTOR(Monitor)
    {
        std::cout << std::endl <<  "time\tA\tZ" << std::endl;
        SC_METHOD(monitor);
        sensitive << A << B << Z << Clk.pos();
        dont_initialize();
    }

private:
    void monitor()
    {
        std::cout << sc_time_stamp()  << "\t" << A << "\t" << Z << std::endl;
    }
};


