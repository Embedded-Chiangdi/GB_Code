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

#define OLED_RETURN_SUCCESS 0
#define OLED_RETURN_FAILED 1 
#define OLED_DEV_NAME "oled"
#define OLED_CLASS_NAME "oled_class"
#define OLED_COUNT 1

struct oled_Dev {
    dev_t oledDevId;
    struct cdev oledCdev;
    struct class *oledClass;
    struct device *oledDevice;
    int major;
    int minor;
};

struct oled_Dev oledDev; 

static ssize_t oled_read  (struct file *filp, char __user *buf, size_t cnt, loff_t * offet) {

    return OLED_RETURN_SUCCESS;
}
static ssize_t oled_write (struct file *filp, const char __user *buf, size_t cnt, loff_t *offet){

    return OLED_RETURN_SUCCESS;
}
static int oled_open (struct inode *inodep, struct file *filep){

    printk("%s %s line %d\r\n",__FILE__,__func__,__LINE__);

    return OLED_RETURN_SUCCESS;
}
static int oled_release (struct inode *inodep, struct file *filep){
    
    printk("%s %s line %d\r\n",__FILE__,__func__,__LINE__);

    return OLED_RETURN_SUCCESS;
}

struct file_operations oledFops ={
    .owner = THIS_MODULE,
    .open = oled_open,
    .read = oled_read,
    .write = oled_write,
    .release = oled_release,
};

static int __init oledDev_init(void){
    int ret;
    printk("%s %s line %d\r\n",__FILE__,__func__,__LINE__);

    if(oledDev.major){
        oledDev.oledDevId = MKDEV(oledDev.major,0);
        if((ret = register_chrdev_region(oledDev.oledDevId,OLED_COUNT,OLED_DEV_NAME)) < 0)
            {
                printk("%s %s line %d\r\n",__FILE__,__func__,__LINE__);
                printk("faled to get dev_id\r\n");
                ret = OLED_RETURN_FAILED;
                goto err1;
            }
    }
    else{
        
        if((ret = alloc_chrdev_region(&oledDev.oledDevId,0,OLED_COUNT,OLED_DEV_NAME)) < 0)
            {
                printk("%s %s line %d\r\n",__FILE__,__func__,__LINE__);
                printk("faled to allocate dev_id\r\n");
                ret = OLED_RETURN_FAILED;
                goto err1;
            }
            oledDev.major = MAJOR(oledDev.oledDevId);
            oledDev.minor = MINOR(oledDev.oledDevId);
        printk("major id is %d, minor id is %d\r\n",oledDev.major,oledDev.minor);
    }

    oledDev.oledCdev.owner = THIS_MODULE;
    
    cdev_init(&oledDev.oledCdev,&oledFops);
    cdev_add(&oledDev.oledCdev,oledDev.oledDevId,OLED_COUNT);

    oledDev.oledClass = class_create(THIS_MODULE,OLED_CLASS_NAME);
    if(IS_ERR(oledDev.oledClass)){
        ret = PTR_ERR(oledDev.oledClass);
        goto err2;
    }

    oledDev.oledDevice = device_create( oledDev.oledClass, NULL , oledDev.oledDevId, NULL ,OLED_DEV_NAME);
    if(IS_ERR(oledDev.oledDevice)){
        ret = PTR_ERR(oledDev.oledDevice);
        goto err3;
    }

    printk("HELLO OLED TEST DRIVER\r\n");
    return OLED_RETURN_SUCCESS;

err3:
    class_destroy(oledDev.oledClass);
err2:
    cdev_del(&oledDev.oledCdev);
    unregister_chrdev_region(oledDev.oledDevId,OLED_COUNT);
err1:
    printk("OLED TEST DRIVER FAILED\r\n");
    return ret;
}
static void __exit oledDev_exit(void){
    printk("%s %s line %d\r\n",__FILE__,__func__,__LINE__);
    
    cdev_del(&oledDev.oledCdev);
    
    unregister_chrdev_region(oledDev.oledDevId,OLED_COUNT);
    
    device_destroy(oledDev.oledClass,oledDev.oledDevId);
    
    class_destroy(oledDev.oledClass);

    printk("BYE OLED TEST DRIVER\r\n");
}
module_init(oledDev_init);
module_exit(oledDev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jiang Di");
MODULE_DESCRIPTION("OLED Test Driver Module");