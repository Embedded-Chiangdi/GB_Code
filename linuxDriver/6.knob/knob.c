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

#define knob_RETURN_SUCCESS 0
#define knob_RETURN_FAILED 1 
#define knob_DEV_NAME "knob"
#define knob_CLASS_NAME "knob_class"
#define knob_COUNT 1

struct knob_Dev {
    dev_t knobDevId;
    struct cdev knobCdev;
    struct class *knobClass;
    struct device *knobDevice;
    int major;
    int minor;
};

struct knob_Dev knobDev; 

static ssize_t knob_read  (struct file *filp, char __user *buf, size_t cnt, loff_t * offet) {

    return knob_RETURN_SUCCESS;
}
static ssize_t knob_write (struct file *filp, const char __user *buf, size_t cnt, loff_t *offet){

    return knob_RETURN_SUCCESS;
}
static int knob_open (struct inode *inodep, struct file *filep){

    printk("%s %s line %d\r\n",__FILE__,__func__,__LINE__);

    return knob_RETURN_SUCCESS;
}
static int knob_release (struct inode *inodep, struct file *filep){
    
    printk("%s %s line %d\r\n",__FILE__,__func__,__LINE__);

    return knob_RETURN_SUCCESS;
}

struct file_operations knobFops ={
    .owner = THIS_MODULE,
    .open = knob_open,
    .read = knob_read,
    .write = knob_write,
    .release = knob_release,
};

static int __init knobDev_init(void){
    int ret;
    printk("%s %s line %d\r\n",__FILE__,__func__,__LINE__);

    if(knobDev.major){
        knobDev.knobDevId = MKDEV(knobDev.major,0);
        if((ret = register_chrdev_region(knobDev.knobDevId,knob_COUNT,knob_DEV_NAME)) < 0)
            {
                printk("%s %s line %d\r\n",__FILE__,__func__,__LINE__);
                printk("faled to get dev_id\r\n");
                ret = knob_RETURN_FAILED;
                goto err1;
            }
    }
    else{
        
        if((ret = alloc_chrdev_region(&knobDev.knobDevId,0,knob_COUNT,knob_DEV_NAME)) < 0)
            {
                printk("%s %s line %d\r\n",__FILE__,__func__,__LINE__);
                printk("faled to allocate dev_id\r\n");
                ret = knob_RETURN_FAILED;
                goto err1;
            }
            knobDev.major = MAJOR(knobDev.knobDevId);
            knobDev.minor = MINOR(knobDev.knobDevId);
        printk("major id is %d, minor id is %d\r\n",knobDev.major,knobDev.minor);
    }

    knobDev.knobCdev.owner = THIS_MODULE;
    
    cdev_init(&knobDev.knobCdev,&knobFops);
    cdev_add(&knobDev.knobCdev,knobDev.knobDevId,knob_COUNT);

    knobDev.knobClass = class_create(THIS_MODULE,knob_CLASS_NAME);
    if(IS_ERR(knobDev.knobClass)){
        ret = PTR_ERR(knobDev.knobClass);
        goto err2;
    }

    knobDev.knobDevice = device_create( knobDev.knobClass, NULL , knobDev.knobDevId, NULL ,knob_DEV_NAME);
    if(IS_ERR(knobDev.knobDevice)){
        ret = PTR_ERR(knobDev.knobDevice);
        goto err3;
    }

    printk("HELLO knob TEST DRIVER\r\n");
    return knob_RETURN_SUCCESS;

err3:
    class_destroy(knobDev.knobClass);
err2:
    cdev_del(&knobDev.knobCdev);
    unregister_chrdev_region(knobDev.knobDevId,knob_COUNT);
err1:
    printk("knob TEST DRIVER FAILED\r\n");
    return ret;
}
static void __exit knobDev_exit(void){
    printk("%s %s line %d\r\n",__FILE__,__func__,__LINE__);
    
    cdev_del(&knobDev.knobCdev);
    
    unregister_chrdev_region(knobDev.knobDevId,knob_COUNT);
    
    device_destroy(knobDev.knobClass,knobDev.knobDevId);
    
    class_destroy(knobDev.knobClass);

    printk("BYE knob TEST DRIVER\r\n");
}
module_init(knobDev_init);
module_exit(knobDev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jiang Di");
MODULE_DESCRIPTION("knob Test Driver Module");