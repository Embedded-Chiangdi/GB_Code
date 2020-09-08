#include <linux/kthread.h> 
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/kernel.h>	/* printk() */
#include <linux/slab.h>		/* kmalloc() */
#include <linux/fs.h>		/* everything... */
#include <linux/errno.h>	/* error codes */
#include <linux/types.h>	/* size_t */
#include <linux/fcntl.h>	/* O_ACCMODE */
#include <linux/uaccess.h>
#include <linux/ioctl.h>
#include <linux/cdev.h>
#include <linux/delay.h>

static struct task_struct *task_test;

int kernelThreadTest_func(void *data){

    printk("Enter Thread Func\n");
    while( !kthread_should_stop()){
        msleep(2000);
        printk("Hello World\n");
    }

    return 0;
}

static int __init kernelThreadTest_init(void){
    int err;
    task_test = kthread_create(kernelThreadTest_func,NULL,"kernelThreadTest_func");
    if(IS_ERR(task_test)){
        printk("Unable to start kernelThreadTest\n");
        err = PTR_ERR(task_test);
        task_test = NULL;
        return err;    
    }

    wake_up_process(task_test);

    printk("Start kernelThreadTest\n");

    return 0;
}

static void __exit kernelThreadTest_exit(void){

    if(task_test)
        kthread_stop(task_test);

    printk("Stop kernelThreadTest\n");

    return ;
}

module_init(kernelThreadTest_init);
module_exit(kernelThreadTest_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jiang Di");
MODULE_DESCRIPTION("Test Driver Module");
