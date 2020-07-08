#include <linux/init.h>
#include<linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>


#define SUCCESS 0
#define DEVICE_NAME "charDev"
#define BUF_LEN 20

static int Major;
static int Device_open = 0;

static char buff[BUF_LEN];
static char *pBuff;


static int device_open (struct inode * inode, struct file * file){
    static int counter = 0;
    if (Device_open){
        return -EBUSY;
    }
    Device_open++;
    sprintf(buff,"I already told you %d times Hello world!\n",counter);
    pBuff = buff;
    try_module_get(THIS_MODULE);
    return SUCCESS;
}
static int device_release (struct inode * inode, struct file * file){
    Device_open --;
    module_put(THIS_MODULE);
    return SUCCESS;
}

static ssize_t device_read (struct file *filp,
                             char __user *buffer, 
                                size_t length, 
                                loff_t * offset){
    int bytes_read = 0 ;
    if(*pBuff == 0)
        return 0;
    while(length && (*pBuff)){
        put_user(*(pBuff++),buffer++);
        length -- ;
        bytes_read ++ ;
    }

}
static ssize_t device_write(struct file *filp,
                             char __user *buffer, 
                                size_t length, 
                                loff_t * offset){
    printk(KERN_ALERT"Sorry, this operation isn't supported\r\n");
    return -EINVAL;
}
static struct file_operations fops ={
    .read = device_read,
    .write = device_write,
    .open = device_open,
    .release = device_release
};

static int __init charDev_init(void){
    printk(KERN_INFO"----%s---%s----%d---\r\n",__FILE__,__func__,__LINE__);
    printk(KERN_INFO"Hello\r\n");
    printk(KERN_INFO"This is my charDev kernel module\r\n");

    Major = register_chrdev(0,DEVICE_NAME,&fops);
    if(Major < 0){
        printk(KERN_ALERT"register_chrdev failed %d\r\n",Major);
        return Major;
    }

    printk(KERN_INFO"I was assigned major number %d . To talk to\r\n",Major);
    printk(KERN_INFO"the driver , create a dev file with\r\n");
    printk(KERN_INFO"mknod /dev/%s c %d 0\r\n",DEVICE_NAME,Major);
    printk(KERN_INFO"Try various minor numbers. Try to cat and echo to\r\n");
    printk(KERN_INFO"the Device file. \r\n");
    printk(KERN_INFO"Remove the device file and module when done\r\n");


    return SUCCESS;
}
static void __exit charDev_exit(void){
    
    unregister_chrdev(Major,DEVICE_NAME);
    

    printk(KERN_INFO"---%s---%s---%d---\r\n",__FILE__,__func__,__LINE__);
    printk(KERN_INFO"Bye\r\n");
    return ;
}



module_init(charDev_init);
module_exit(charDev_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jiang Di");
MODULE_DESCRIPTION("Test Driver Module");

