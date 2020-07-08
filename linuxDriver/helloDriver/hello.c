#include <linux/init.h>
#include<linux/kernel.h>
#include <linux/module.h>

int __init hello_init(void){
    printk(KERN_INFO,"----%s---%s----%d---",__FILE__,__func__,__LINE__);
    printk(KERN_INFO,"This is my first kernel");
    return 0;
}
void __exit hello_exit(void){
    printk(KERN_INFO,"---%s---%s---%d---",__FILE__,__func__,__LINE__);
    return 0;
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");

