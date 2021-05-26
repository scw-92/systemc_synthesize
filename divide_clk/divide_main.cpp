#include"divide.h"

int sc_main(int argc,char * argv[])
{
    sc_signal<bool> pout;
    sc_signal<bool> rst_n;
    sc_trace_file *tf;
    sc_clock clock("master_clk",10,SC_NS);


    divide p1("divide",4);
    p1.clk(clock);
    p1.clkout(pout);
    p1.rst_n(rst_n);

    tf = sc_create_vcd_trace_file("pulse_vcd");
    sc_trace(tf,clock,"clock");
    sc_trace(tf,pout,"pout");

    rst_n = 0;
    sc_start(25,SC_NS);
    rst_n = 1;
    sc_start(125,SC_NS);
    sc_close_vcd_trace_file(tf);
    cout<<"Finish at time "<<sc_time_stamp()<<endl;
    return 0;

}