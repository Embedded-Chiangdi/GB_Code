#include <linux/module.h>

#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/miscdevice.h>
#include <linux/kernel.h>
#include <linux/major.h>
#include <linux/mutex.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/stat.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/tty.h>
#include <linux/kmod.h>
#include <linux/gfp.h>

static int charDevMajor = 0;
static struct class *charDevClass;
static char readbuf[1024];
#define CHARDEV_NAME "chardev"
#define MIN(a,b) (a < b ? a:b)


static ssize_t charDev_read (struct file *filp, char __user *buf, size_t cnt, loff_t * offet){
    int retValue = 0;

    retValue = copy_to_user(buf,readbuf,MIN(1024,cnt));
    if(retValue == 0){
        printk("kernel send data ok!\r\n");
    } 
    else{
        printk("kernel send data failed \r\n");
        return retValue;
    }

    return MIN(1024,cnt);
}
static ssize_t charDev_write (struct file *filp, const char __user *buf, size_t cnt, loff_t *offet){
    int retvalue = 0;
    retvalue = copy_from_user(readbuf,buf,cnt);
    if(retvalue == 0){
        printk("kernel receive data ok!\r\n");
    } 
    else{
        printk("kernel receive data failed \r\n");
        return retvalue;
    }
    return MIN(1024,cnt);
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
    printk("%s %s line %d\r\n",__FILE__,__func__,__LINE__);

    charDevMajor = register_chrdev(0, CHARDEV_NAME ,&charDev_fops);
    if(charDevMajor < 0){
        printk("chrdev register failed\r\n"); 
        retvalue = charDevMajor;
        goto err1;
    }
    charDevClass = class_create(THIS_MODULE,"charDevClass");
    retvalue = PTR_ERR(charDevClass);
    if(IS_ERR(charDevClass)){
        printk("%s %s line %d\r\n",__FILE__,__func__,__LINE__);
        retvalue = -1;
        goto err1;
    }
    device_create(charDevClass,NULL,MKDEV(charDevMajor,0),NULL,CHARDEV_NAME);
    return 0;

err1:
    return retvalue;
}
static void __exit charDev_exit(void){

    printk("%s %s line %d\r\n",__FILE__,__func__,__LINE__);
    device_destroy(charDevClass,MKDEV(charDevMajor,0));
    class_destroy(charDevClass);
    unregister_chrdev(charDevMajor,CHARDEV_NAME);
    printk("chrdev exit\r\n");
    printk("BYE\r\n");
}

module_init(charDev_init);
module_exit(charDev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jiang Di");
MODULE_DESCRIPTION("Test Driver Module");