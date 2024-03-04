#include <iostream>
#include <systemc.h>

#include "kpn.h"
#include "kpn.cpp"

int sc_main(int, char**)
{
    kpn kahn("kpn");
    sc_start();
    return 0;
}
