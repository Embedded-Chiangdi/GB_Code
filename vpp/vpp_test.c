#include <stdlib.h>
#include <stdio.h>
#if 0
#define VPP_TEST 1
#endif 

#ifdef VPP_TEST
#include "vat.vat.h"
#include "vat/apiif.h"
#endif 
static int test_pass=0;
static int test_count=0;

#define EXPECT_BASE(eqStatus,expect,actual,format) \
do\
{\
test_count++;\
if(eqStatus)\
	test_pass++;\
else\
{\
	fprintf(stderr,"%s %d eqStatus : %d expect: "format"actual : "format"\n",__FILE__,__LINE__,eqStatus,expect,actual);\
}\
}while(0)\

#define EXPECT_INT(expect,actual); do{EXPECT_BASE(expect == actual,expect,actual,"d");}while(0)
#ifdef VPP_TEST	
#define XOR 3
#define LACP 5
enum BondL {BondL2,BondL34,BondL23}; 

int test_bond(){
	int iRet;
	iRet=apiif_bond_create (NULL,XOR,BondL34,1);
	EXPECT_INT(0,iRet);
}
#endif

int test_sub(void){
	EXPECT_INT(1,1);

}

int main(int argc,char *argv[]){
	test_sub();
#ifdef VPP_TEST
	test_bond();
#endif
	printf("test_pass:%d test_count:%d \ntest %3.2f/100.00%%\n",test_pass,test_count,test_pass*100.0/test_count);
	return 0;
}