#ifndef SUBNET_H
#define SUBNET_H

#include <systemc.h>

#include "place.h"
#include "transition.h"

// Subnet:
// TODO
template<unsigned int N=1, unsigned int M=1>
SC_MODULE(subnet) {

transition<1,1,1> ACT;
transition<1,1,0> RD;
transition<1,1,0> WR;
transition<1,1,0> PRE;

place<1,1> ACTIVE;  //Win and Wout  are supposed to be one.
//place<2,2> IDLE;
sc_port<placeInterface> IDLE;

SC_CTOR(subnet) : ACT("ACT"),RD("RD"),WR("WR"),PRE("PRE"),ACTIVE(0),IDLE("IDLE")
{
        ACT.in(IDLE);
        ACT.out(ACTIVE);
        ACT.inhibitors(ACTIVE);

        RD.in(ACTIVE);
        RD.out(ACTIVE);
        
        WR.in(ACTIVE);
        WR.out(ACTIVE);

        PRE.in(ACTIVE);
        PRE.out(IDLE);
    }
  
};
 #endif // SUBNET_H
