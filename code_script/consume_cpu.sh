#!/bin/bash
#定义生成的c文件名称和可执行程序名称
fileName="cpu_use"
#定义使用方法说明
usage(){
  echo "./`basename $0` <start|stop|adjust> <CPU_Rate> [sleeptime/worktime] [adjustRange]"
  echo ""
  echo "start:按照核的数量启动 $fileName"
  echo "stop:停止所有 $fileName"
  echo "adjust:自动调整占用CPU的使用率"
  echo "CPU_Rate:占用cpu比率"
  echo "sleeptime/worktime:CPU空闲和工作时间的占比 可以通过该参数调整"
  echo "adjustRange:允许CPU的波动范围 即curentCPU-adjustRange CPU_Rate curentCPU+adjustRange就不再调整"
  echo ""
  exit 
}
#判定参数的个数，参数不能少于1个，且必须为限定参数:start,stop,adjust


if [ $# -lt 1 ]
then
  usage
fi
#设置需要占用的CPU比率，默认为50%
if [ "$2" == "" ]
then
  CPU_Rate=50
else
  CPU_Rate=$2
fi
#设置允许的波动范围，默认为5
if [ "$4" == "" ]
then
  adjustRange=5
else
  adjustRange=$4
fi
#停止
#没有参数
stop_thread(){
    if [ `ps -ef|grep $fileName|grep -v grep|awk '{print $2}'|wc -l` -ne 0 ]
    then
      ps -ef|grep $fileName|grep -v grep|awk '{print $2}'|xargs kill -9
    fi
}
#创建
#参数一个:cpu空闲时间和工作时间的比率，默认是1，对应脚本入参的第三个参数[sleeptime/worktime]
start_thread(){
    if [ "$1" == "" ]
    then
      rate=1
    else
      rate=$1
    fi
cat <<EOF > $fileName.c
    #include <time.h>
    #include <sys/time.h>
    #include <unistd.h>
    #include<stdlib.h>
    #include<math.h>

    #define DWORD unsigned long  
    #define UINT64 unsigned long long  
    const int INTERVAL = 300;

    int main(int argc, char* argv[] )
    {
        struct timeval tms;
        int half = INTERVAL/2, i;
        clock_t startTime = 0;
        while(1)
        {
            timerclear(&tms);
            gettimeofday(&tms,NULL);
            UINT64 startTime = tms.tv_usec;
            while(1)
            {
                timerclear(&tms);
                gettimeofday(&tms,NULL);
                UINT64 nowTime = tms.tv_usec;
                if((nowTime - startTime)/1000 > INTERVAL)
                    break;
            }
            if(usleep(INTERVAL*1000*$rate))
                exit(-1);    
        }
        return 0;
    }
EOF
    echo "编译 $fileName.c ... "
    gcc $fileName.c -o $fileName
    if [ $? -eq 0 ]; then
        echo "执行$fileName 开始... "
        echo
        cpuNum=`cat /proc/cpuinfo |grep processor|wc -l`
        for i in `seq 1 $cpuNum`
        do
        echo "  ... 执行$fileName 第 "$i"次开始 ... "
        ./$fileName &
        echo "  ... 执行$fileName 第 "$i"次结束 ... "
        echo
        done
        echo "执行$fileName 结束... "
      echo ""
    else
        echo "编译 $fileName.c ERROR! "
    fi
}
#自动调整cpu的使用率，使其满足CPU_Rate
# 第一个:sleep/work
times=1
adjustment(){
  stop_thread
  start_thread $1
  #此处根据不同的操作系统可能会有不同的结果展示，根据情况修改==7是只取一行，取哪行自己定但不能是第一行 $4对应us%使用率
  cur_cpu=`mpstat 1 6|awk '{if(NR==7){print $4}}'`
  if [ "$cur_cpu" \< "$(expr $CPU_Rate - $adjustRange)" -o "$cur_cpu" \> "$(expr $CPU_Rate + $adjustRange)" ]
  then
    echo "======期望CPU使用率:$CPU_Rate=====当前CPU使用率:$cur_cpu==========开始第【$((times++))】次调整==========="
    echo ""
    adjustment $(expr $cur_cpu/$CPU_Rate*$1)
  else
    echo "======期望CPU使用率:$CPU_Rate=====当前CPU使用率:$cur_cpu==========结束调整并退出========="
    echo ""
  fi
}


if [ $1 == 'start' ]
then
  stop_thread
  start_thread $3
fi
if [ $1 == 'adjust' ]
then
  stop_thread
  adjustment $3
fi
if [ $1 == 'stop' ]
then
  stop_thread
fi
