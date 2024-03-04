#include <systemc.h>
using namespace std;

#include "kpn.h"

// ADD THINGS HERE

    void kpn :: add(){
        while(true)
        {
            //wait(10, SC_NS);
            b.write(a.read() + c.read());
            //wait(SC_ZERO_TIME);
        }
    }

    void kpn :: split(){
        for (int i = 0; i < 10; ++i) {
            unsigned int inputB = b.read();
            //unsigned int inputC = c.read();

            //wait(10, SC_NS);
            a.write(inputB);
            d.write(inputB);

            e.write(inputB);

            cout << "Time: " << sc_delta_count() << " - Output at e by Split   " << e << "   value of b " << inputB << endl;
            //wait(SC_ZERO_TIME);
        }
    }

    void kpn :: delay(){
        for (int i = 0; i < 10; ++i) {
            //wait(10, SC_NS);
            unsigned int output = d.read();
            c.write(output);
            //wait(SC_ZERO_TIME); 
        }
    }
    



