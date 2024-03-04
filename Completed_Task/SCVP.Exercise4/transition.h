#ifndef TRANSITION_H
#define TRANSITION_H

#include <systemc.h>

#include "place.h"

using namespace std;

// Transition:
// TODO

//template <class T>
//TASK2 
//template<unsigned int N, unsigned int M>
//TASK3
//template<unsigned int N=1, unsigned int M=1>
//TASK4
// "inhibitor arc" is a type of arc that connects a place to a transition and imposes a condition on the firing of the transition. 
//Unlike a regular (token-bearing) arc, which enables a transition to fire when there are a sufficient number of tokens in the connected place, an inhibitor arc acts as an inhibiting condition.
template<unsigned int N=1, unsigned int M=1, unsigned int L=0>
SC_MODULE(transition)
{
    public:
    //sc_port< placeInterface<int> > in;
    //sc_port< placeInterface<int> > out;

    //TASK2
    // sc_port<placeInterface<int>, N, SC_ALL_BOUND> in;
    // sc_port<placeInterface<int>, M, SC_ALL_BOUND> out;

    //TASK3
    //sc_port<placeInterface, N, SC_ALL_BOUND> in;  //remove template T from placeInterface 
    //sc_port<placeInterface, M, SC_ALL_BOUND> out;

    //TASK4
    sc_port<placeInterface, N, SC_ALL_BOUND> in; 
    sc_port<placeInterface, M, SC_ALL_BOUND> out;
    sc_port<placeInterface, L, SC_ZERO_OR_MORE_BOUND> inhibitors;

    SC_CTOR(transition){
    }

    void fire() {
        // if (in->testTokens() > 0){
        //     cout << this->name() << ": Fired" << endl;
        //     in->removeTokens(1);
        //     out->addTokens(1);
        // }
        // else {
        //     cout << this->name() << ": NOT Fired" << endl;
        // }

        // for(int i=0;i<N;i++) {
        // if (in[i]->testTokens() > 0){
        //     cout << this->name() << ": Fired" << endl;
        //     in[i]->removeTokens(1);
        //     out[i]->addTokens(1);
        // }
        // else {
        //     cout << this->name() << ": NOT Fired" << endl;
        // }
        // }

        bool Fire = true;
        bool inhibit = true; //if inhibitor not have token
        for (int i = 0; i < L; i++) {
            if (inhibitors[i]->testTokens() > 0) {
                inhibit = false; //inhibitor have token
                break;
            }
        }

        for (int i = 0; i < N; i++) {
            if (in[i]->testTokens() == 0) {
                Fire = false;
                break;
            }
        }

        if(Fire && inhibit) {
            cout << this->name() << ": Fired" << endl;
            for (int i = 0; i < N; i++) {         
            in[i]->removeTokens();
            }

            for (int i = 0; i < M; i++) {
            out[i]->addTokens();
            }
            
        } 
        else {
            cout << this->name() << ": NOT Fired" << endl;
        }
            
    }   
};

#endif // TRANSITION_H
