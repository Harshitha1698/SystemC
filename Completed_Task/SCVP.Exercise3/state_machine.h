#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <systemc.h>

// TODO

enum base {Start, G, GA, GAA, GAAG, GAAAAG};

SC_MODULE (stateMachine)
{

    public :

    sc_in<char> input;
    sc_in<bool> clk;

    int seq_count,g_position,counter;

    SC_CTOR(stateMachine)
    {
        SC_METHOD(process);
        sensitive << clk.pos();

    }
    private:
    void process();

};
#endif // STATE_MACHINE_H


