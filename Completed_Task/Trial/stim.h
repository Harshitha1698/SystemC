SC_MODULE(stim)
{
public:
    sc_out<bool> A ;

    SC_CTOR(stim)
    {
        SC_THREAD(StimGen);
    }

    void StimGen()
    {
        wait(SC_ZERO_TIME);
        A.write(true);
        wait(10, SC_NS);
        A.write(false);
        wait(10, SC_NS);
        A.write(false);
        wait(10, SC_NS);
        A.write(true);
        wait(10, SC_NS);
        A.write(false);
        wait(10, SC_NS);
        A.write(true);
        wait(10, SC_NS);
        sc_stop();
    }
};