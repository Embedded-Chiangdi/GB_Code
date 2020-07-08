#include <linux/types.h>
#include <linux/ide.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include<linux/kernel.h>


#define Chardev_major 200
#define CHARDEV_NAME "charDev"

static char readbuf[50];
static char writebuf[50];
static char kerneldata[]={"kernel data !"};

static ssize_t charDev_read (struct file *filp, char __user *buf, size_t cnt, loff_t * offet){
    int retValue = 0;

    memcpy(readbuf,kerneldata,sizeof(kerneldata));

    retValue = copy_to_user(buf,readbuf,cnt);
    if(retValue == 0){
        printk("kernel send data ok!\r\n");
    } 
    else{
        printk("kernel send data failed \r\n");
        return retValue;
    }

    return 0;
}
static ssize_t charDev_write (struct file *filp, const char __user *buf, size_t cnt, loff_t *offet){
    int retvalue = 0;
    retvalue = copy_from_user(writebuf,buf,cnt);
    if(retvalue == 0){
        printk("kernel receive data ok!\r\n");
    } 
    else{
        printk("kernel receive data failed \r\n");
        return retvalue;
    }
    return 0;
}
static int charDev_open (struct inode *inode, struct file *filp){
    printk("chrdevbase open\r\n");
    return 0;
}
static int charDev_release (struct inode *inode, struct file *filp){
        printk("chrdevbase release\r\n");
    return 0;
}
static struct file_operations charDev_fops = {
    .owner = THIS_MODULE,
    .open = charDev_open,
    .read = charDev_read,
    .write = charDev_write,
    .release = charDev_release,
};

static int __init charDev_init(void){
    int retvalue = 0;
    retvalue = register_chrdev(Chardev_major, CHARDEV_NAME ,&charDev_fops);
    if(retvalue < 0){
        printk("chrdev register failed\r\n"); 
    }

    return retvalue;
}
static void __exit charDev_exit(void){
    unregister_chrdev(Chardev_major,CHARDEV_NAME);
    printk("chedev exit\r\n");

}

module_init(charDev_init);
module_exit(charDev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jiang Di");
MODULE_DESCRIPTION("Test Driver Module");