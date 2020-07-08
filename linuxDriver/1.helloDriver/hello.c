#include <linux/init.h>
#include<linux/kernel.h>
#include <linux/module.h>

static int __init hello_init(void){
    printk(KERN_INFO"----%s---%s----%d---\r\n",__FILE__,__func__,__LINE__);
    printk(KERN_INFO"Hello\r\n");
    printk(KERN_INFO"This is my first kernel module\r\n");
    return 0;
}
static void __exit hello_exit(void){
    printk(KERN_INFO"---%s---%s---%d---\r\n",__FILE__,__func__,__LINE__);
    printk(KERN_INFO"Bye\r\n");
    return ;
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jiang Di");
MODULE_DESCRIPTION("Test Driver Module");

