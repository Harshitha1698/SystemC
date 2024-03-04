#include <iostream>

#include "state_machine.h"
#include "stimuli.h"

using namespace std;

// TODO

void stateMachine::process()
{
    static base state = Start;  //enum type base --> state is the name of the variable with initial value Start

    switch(state) {
        case Start:
            seq_count++;
            if (input.read() == 'G') {
                state = G;
                g_position++;
            }
            else {
                state = Start;
                g_position = 0;
            }
            break;

        case G:
            if (input.read() == 'A') {
                state = GA;
                g_position++;
            }
            else if (input.read() == 'G') {
                state = G;
                g_position = 0;
            }
            else {
                state = Start;
                g_position = 0;
            }
            break;

        case GA:
            if (input.read() == 'A') {
                state = GAA;
                g_position++;
            }
            else if (input.read() == 'G') {
                state = G;
                g_position = 0;
            }
            else {
                state = Start;
                g_position = 0;
            }
            break;

        case GAA:
            if (input.read() == 'A') {
                state = GAAAAG;
                g_position=0;
            }
            else if (input.read() == 'G') {
                state = GAAG;
                g_position++;
                cout << "SEQUENCE  " << seq_count << endl;
                cout << "GAA position  " <<g_position << endl;
                cout << "FOUND GAA @    " << (seq_count - g_position)<< endl;
			    counter++;
			    cout << "How many times    " <<counter << endl;
            }
            else {
                state = Start;
                g_position = 0;
            }
            break;

        case GAAAAG:
            if (input == 'G') {
			    state = Start;
                g_position = 0;
            }
             else if (input.read() == 'A') {
                state = GAAAAG;
                g_position = 0;
            }
            else {
                state = Start;
                g_position = 0;
            }
        break;

        case GAAG:
            if (input == 'G') {
			    state = G;
            }
            else {
                state = Start;
                g_position = 0;  
            }
            break;

    
            default:
                cout << "DONE";
                break;
            }


       
};


