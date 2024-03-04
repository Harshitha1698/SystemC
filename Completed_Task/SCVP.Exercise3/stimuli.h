#ifndef STIMULI_H
#define STIMULI_H

#include <string>
#include <systemc.h>

SC_MODULE(stimuli)
{
public:
    sc_in<bool> clk;
    sc_out<char> output;
    SC_HAS_PROCESS(stimuli);   //This is the macro provided by SystemC to declare that the module has a process.
    stimuli(const sc_module_name &name); //: This is the constructor of the module.It takes a reference to sc_module_name as an argument,which represents the name of the module.

private:
    std::string sequence;
    void process();
    unsigned int counter;
};

#endif // STIMULI_H
