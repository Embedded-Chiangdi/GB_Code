#define EncoderA  P01

#define EncoderB  P02         //A ,  B 两个引脚

uint8 time_cnt = 0;                //用于记录次数

uint8 input_status = 0;            //输入的状态
uint8 input_status0 = 0;        //用于记录上一次初始状态
uint8 pulse0 = 0;                //记录正旋转的状态次数
uint8 pulse1 = 0;                //记录反旋转的状态次数
uint8 scanf_status = 0;            //获取到的状态
uint8 fun_one = 0;                //判断函数是否第一次执行

//125us
void EC11_Key_Detect(void)
{
    if (++time_cnt <= 3)        
    {
        return;
    }
    time_cnt = 0;
    
    //每500us 进入一次 判断A、B引脚有无电平变化
    if (EncoderA)
    {
        if (EncoderB)
        {
             //状态1
            input_status = 1;        //A = 1; B = 1
        }
        else if (!EncoderB)
        {
             //状态4
            input_status = 4;        //A = 1; B = 0
        }
    }
    else if(!EncoderA)
    {
        if (EncoderB)
        {
             //状态2
            input_status = 2;        //A = 0; B = 1
        }
        else if (!EncoderB)
        {
             //状态3
            input_status = 3;        //A = 0; B = 0
        }
    }
    //通过判断两个状态是否相等来 判断状态确实有变化(类似于按键消抖过程)
    if (input_status == input_status0)
    {
        //如果第一次执行该函数
        if (fun_one == 0)
        {
            fun_one = 1;
            scanf_status = input_status;
        }
        input_status0 = input_status;
        
        //如果状态为 1 因为开关旋转后 电平会停在 1 状态，在此执行所需要的东西
        if (scanf_status == 1)
        {
            //正旋转了一个周期
            if (pulse0 >= 4)
            {
                pulse0 = 0;
                //开关正旋转一次写在这里就行了
                //需要执行的语句

            }
            //反旋转一个周期
            if (pulse1 >= 4)
            {
                pulse1 = 0;

                //开关反旋转一次写在这里就行了

                //需要执行的语句

            }
            //在状态1 的 前提下，判断是正旋转还是反旋转

            if (input_status == 2)        //正旋转
            {
                scanf_status = 2;
                pulse0++;
            }
            else if (input_status == 4)        //反旋转
            {
                scanf_status = 4;
                pulse1++;
            }
        }
        //在状态 2 的 前提下，判断是正旋转还是反旋转 
        if (scanf_status == 2)
        {
            if (input_status == 3)        //正旋转
            {
                scanf_status = 3;
                pulse0++;
            }
            if (input_status == 1)        //反旋转
            {
                scanf_status = 1;
                pulse1++;
            }
        }
        //在状态 3 的 前提下，判断是正旋转还是反旋转
        if (scanf_status == 3)
        {
            if (input_status == 4)        //正旋转
            {
                scanf_status = 4;
                pulse0++;
            }
            if (input_status == 2)        //反旋转
            {
                scanf_status = 2;
                pulse1++;
            }
        }
        //在状态 4 的 前提下，判断是正旋转还是反旋转
        if (scanf_status == 4)
        {
            if (input_status == 1)        //正旋转
            {
                scanf_status = 1;
                pulse0++;
            }
            if (input_status == 3)        //反旋转
            {
                scanf_status = 3;
                pulse1++;
            }
        }
    }
    else
    {
        input_status0 = input_status;
    }
}
