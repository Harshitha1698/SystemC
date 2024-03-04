#include <systemc.h>

#include "place.h"
#include "transition.h"
#include "subnet.h"

// Toplevel:
// TODO

SC_MODULE(toplevel)
{
   // place<int> p1,p2,p3,p4;  //TASK2
    //place<1,1> p1,p2,p3,p4;  // <1,1> <Win,Wout> //TASK2
    //transition<int> t2;
    //TASK3
    //transition<1,2> t1;
    //transition<2,1> t2;
    //transition<1,1> t3;

    //TASK4
    // place<3,3> ACTIVE;
    // place<1,1> IDLE;
    // transition<1,1,0> ACT;
    // transition<1,1,0> PRE;
    // transition<1,1,0> RD;
    // transition<1,1,0> WR;

    //TASK3
    //SC_CTOR(toplevel) : p1(1),p2(0),p3(0),p4(0),t1("t1"), t2("t2"),t3("t3")   
    //p1(1): p1 is a place object, and it's being initialized with an initial value of 1.t1("t1"): t1 is a transition object, and it's being initialized with the name "t1".
    //{
        // t1.in(p1);
        // t1.out(p2);

        // t2.in(p2);
        // t2.out(p1);

        // t1.in(p1);
        // t1.out(p3);
        // t1.out(p2);

        // t3.in(p3);
        // t3.out(p4);

        // t2.in(p4);
        // t2.in(p2);
        // t2.out(p1);
    //    SC_THREAD(process);
    //}

    //TASK4
    // SC_CTOR(toplevel) :IDLE(1),ACTIVE(0),RD("RD"),WR("WR"),PRE("PRE"),ACT("ACT")
    // {
    //     ACT.in(IDLE);
	// 	ACT.out(ACTIVE);

	// 	RD.in(ACTIVE);
	// 	RD.out(ACTIVE);

	// 	WR.in(ACTIVE);
	// 	WR.out(ACTIVE);

	// 	PRE.in(ACTIVE);
	// 	PRE.out(IDLE);

	// 	SC_THREAD(process);
    // }

    //TASK5
   place<1,1> IDLE;
   subnet<1,1> s1,s2;

    SC_CTOR(toplevel) :s1("s1"),s2("s2"),IDLE(2)
    {
        //s1.ACT.in(IDLE);
        //s2.ACT.in(IDLE);

        s1.IDLE.bind(IDLE);
        s2.IDLE.bind(IDLE);

        
        //s1.PRE.out(IDLE);
		//s2.PRE.out(IDLE);

		SC_THREAD(process);
    }


    //TASK3
    //void process()
    //{
    // while (true)
    // {
    // wait(10, SC_NS);
    // t1.fire();
    // //wait(10, SC_NS);
    // //t2.fire();
    // wait(10, SC_NS);
    // t1.fire();
    // wait(10, SC_NS);
    // t2.fire();
    // //wait(10, SC_NS);
    // //t2.fire();
    // sc_stop();
    // }
    // }

    //TASK3

    // while (true)
    // {
    // wait(10, SC_NS);
    // t1.fire();
    // wait(10, SC_NS);
    // t2.fire();
    // wait(10, SC_NS);
    // t3.fire();
    // wait(10, SC_NS);
    // t2.fire();
    // sc_stop();
    // }
    // }


    //TASK4
    // void process()
    // {
    //     while (true)
    //     {
    //     wait(10, SC_NS);
    //     ACT.fire();
    //     wait(10, SC_NS);
    //     ACT.fire();
    //     wait(10, SC_NS);
    //     RD.fire();
    //     wait(10, SC_NS);
    //     WR.fire();
    //     wait(10, SC_NS);
    //     PRE.fire();
    //     wait(10, SC_NS);
    //     ACT.fire();
    //     sc_stop();
    //     }
    // }


        void process()
        {
            while (true)
            {
            wait(10, SC_NS);
            s1.ACT.fire();
            wait(10, SC_NS);
            s1.ACT.fire();
            wait(10, SC_NS);
            s1.RD.fire();
            wait(10, SC_NS);
            s1.WR.fire();
            wait(10, SC_NS);
            s1.PRE.fire();
            wait(10, SC_NS);
            s1.ACT.fire();
            wait(10, SC_NS);
            s2.ACT.fire();
            wait(10, SC_NS);
            s2.ACT.fire();
            wait(10, SC_NS);
            s1.PRE.fire();
            wait(10, SC_NS);
            s2.PRE.fire();
            wait(10, SC_NS);
            sc_stop();
            }
        }
    


};



int sc_main(int, char**)
{
    // TODO
    toplevel t("t");

    sc_start();
    return 0;
}
