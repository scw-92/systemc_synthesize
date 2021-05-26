#include"systemc.h"

class divide : public sc_module
{
public: //define port
    sc_in<bool> clk,rst_n;
    sc_out<bool> clkout;
public://define signal 
    sc_signal<bool> clk_p,clk_n;  //clk_p为上升沿触发时分频时钟，clk_n为下降沿触发时分频时钟
    sc_signal<int> cnt_p,cnt_n;   //cnt_p为上升沿触发时的计数器，cnt_n为下降沿触发时的计数器

public: //define var
    int dvide_n = 3;

public:
    SC_HAS_PROCESS(divide);
	divide(sc_module_name name,int dvide_n): sc_module(name)
	{
        this->dvide_n = dvide_n;
        SC_METHOD(risi_cnt);
        sensitive<<clk.pos()<<rst_n.neg();

        SC_METHOD(risi_out);
        sensitive<<clk.pos()<<rst_n.neg();

        SC_METHOD(fall_cnt);
        sensitive<<clk.neg()<<rst_n.neg();

        SC_METHOD(fall_out);
        sensitive<<clk.neg();

        SC_METHOD(clk_out);
        sensitive<<clk<<clk_p<<clk_n;
	}


    void risi_cnt()
    {
        if(!rst_n)
            cnt_p=0;
        else if(cnt_p==(dvide_n-1))
            cnt_p=0;
        else    
            cnt_p = cnt_p+1;
    }

    void risi_out()
    {
        if(!rst_n)
            clk_p=0;
        else if (cnt_p<(dvide_n>>1))
            clk_p=0;
        else 
            clk_p=1; 
    }

    void fall_cnt()
    {
        if (!rst_n)
            cnt_n = 0;
        else if (cnt_n == (dvide_n - 1))
            cnt_n = 0;
        else
            cnt_n = cnt_n + 1;
    }

    void fall_out()
    {
        if (!rst_n)
            clk_n = 0;
        else if (cnt_n < (dvide_n >> 1))
            clk_n = 0;
        else
            clk_n = 1; //得到的分频时钟正周期比负周期多一个clk时钟
    }

    void clk_out()
    {
        clkout = (dvide_n==1)?clk:(dvide_n & 0x1)?(clk_p&clk_n):clk_p;
    }
};