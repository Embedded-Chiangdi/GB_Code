#!/bin/bash
fileName="cpu_consume"
help(){
	echo "\t"
	echo "***********************************"
	echo "----------------Usage---------------"
	echo "SYNOPSIS:$0 <CPU_Rate:>"
	echo "CPU_Rate 占用CPU比例 输入值小于100 "
	echo "-----------------------------------"
	echo "***********************************"
	echo "\t"	
exit 1
}
start(){
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
        float temp=0.0;
	temp=(100.0-$1)/$1;
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
            if(usleep(INTERVAL*1000*temp))
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
if [ $# -lt 1 ];then
	help
fi
if [ $1 == "" ];then
	CPU_Rate=50
else
	CPU_Rate=$1
fi
if [ $1 -ge 0 -a $1 -lt 100 ];then
	start $1
else
	echo "Error"
	exit 1
fi
