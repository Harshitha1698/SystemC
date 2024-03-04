#ifndef PLACE_H
#define PLACE_H

#include <systemc.h>

// Place Interface:
// TODO
//template <class T>
class placeInterface : public sc_interface
{
    public:
    virtual void addTokens() = 0;
    virtual void removeTokens() = 0;  //makes it a pure specifier by "=0"
    virtual unsigned int testTokens() = 0;
};

// Place Channel:
// TODO
//template<unsigned int N=1 , unsigned int M=1>
template<unsigned int Win = 1, unsigned int Wout = 1>
//template <class T>
class place : public placeInterface  //<T>//, public sc_prim_channel
{
    public:
    unsigned int tokens; //specifies current number of tokens

    public:
    place(unsigned int size) : tokens(size){}

    //TASK2 
    // void addTokens(unsigned int n){
    //     tokens += n;
    // }

    // void removeTokens(unsigned int n){
    //     tokens -= n;
    // }

    // unsigned int testTokens(){
    //     return (tokens);
    // }

    void addTokens(){
        tokens += Win;
    }

    void removeTokens(){
        tokens -= Wout;
    }

    unsigned int testTokens(){
        return (tokens >= Wout);
    }

};
#endif 
// PLACE_H
