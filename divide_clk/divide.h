#include"systemc.h"

//普通变量与信号的区别：
	//信号赋值之后需要一个延迟周期才能更新值，变量赋值之后立即更新值。

class divide : public sc_module
{
public: //定义 端口
    sc_in<bool> clk,rst_n;  //输入信号，其中clk的输入周期是10NS
    sc_out<bool> clkout;    //分频之后的输出信号
public://定义信号 
    sc_signal<bool> clk_p,clk_n;  //clk_p为上升沿触发时分频时钟，clk_n为下降沿触发时分频时钟
    sc_signal<int> cnt_p,cnt_n;   //cnt_p为上升沿触发时的计数器，cnt_n为下降沿触发时的计数器

public: //定义普通变量
    int dvide_n = 3;

public:
    SC_HAS_PROCESS(divide);
	divide(sc_module_name name,int dvide_n): sc_module(name)
	{
        this->dvide_n = dvide_n;
        
		//上升沿触发时计数器的控制
		SC_METHOD(risi_cnt);
        sensitive<<clk.pos()<<rst_n.neg();

        
		//上升沿触发的分频时钟输出,如果N为奇数得到的时钟占空比不是50%；如果N为偶数得到的时钟占空比为50%
		SC_METHOD(risi_out);
        sensitive<<clk.pos()<<rst_n.neg();

        
		//下降沿触发时计数器的控制
		SC_METHOD(fall_cnt);
        sensitive<<clk.neg()<<rst_n.neg();

        //下降沿触发的分频时钟输出，和clk_p相差半个时钟
		SC_METHOD(fall_out);
        sensitive<<clk.neg();

        //分频之后的信号输出
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
		//条件判断表达式
                                                                    //当N=1时，直接输出clk
                                                                    //当N为偶数也就是N的最低位为0，N（0）=0，输出clk_p
                                                                    //当N为奇数也就是N最低位为1，N（0）=1，输出clk_p&clk_n。正周期多所以是相与
    }
};