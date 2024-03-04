
#ifndef KPN_H
#define KPN_H

// The #ifndef, #define, and #endif directives are known as include guards, and they are used to prevent multiple inclusions of the same header file in a single translation unit. Without include guards, if a header file is included in multiple places within a program, it could lead to redefinition errors.
// #ifndef: Stands for "if not defined". It checks if a macro has not been defined.
// #define: Defines the macro if it hasn't been defined yet. This effectively creates a flag indicating that the contents of the file have been included.
// #endif: Ends the conditional block.
#include <systemc.h>

SC_MODULE(kpn)
{
private:
    sc_fifo<int> a{"a", 10};
    sc_fifo<int> b{"b", 10};
    sc_fifo<int> c{"c", 10};
    sc_fifo<int> d{"d", 10};

    // sc_fifo<int> a;
    // sc_fifo<int> b;
    // sc_fifo<int> c;
    // sc_fifo<int> d;
    sc_signal<int> e;

public:
    SC_CTOR(kpn)
    {
        b.write(1);
        c.write(0);

        SC_THREAD(add);
        SC_THREAD(split);
        SC_THREAD(delay);

        sensitive << a.data_written_event() << b.data_written_event() << c.data_written_event() << d.data_written_event();
    }

    void add();
    void split();
    void delay();
};

#endif // KPN_H