#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/ide.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/errno.h>
#include <linux/gpio.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/of_gpio.h>
#include <linux/semaphore.h>
#include <linux/timer.h>
#include <linux/irq.h>
#include <linux/wait.h>
#include <linux/poll.h>
#include <linux/fs.h>
#include <linux/fcntl.h>
#include <linux/platform_device.h>

#define SUCCESS 0
#define DEVICE_NAME "platdev"
#define MINOR_COUNT 0
#define DEVICE_COUNT 1

struct stPlatdevice{
    dev_t devid;
    struct cdev scdev;
    struct class *sclass;
    struct device *sdevice;
    int major;
    int minor;
}platdev;


static ssize_t platdev_read  (struct file *filp, char __user *buf, size_t cnt, loff_t * offet) {

    int ret = SUCCESS ;


    return ret;
}
static ssize_t platdev_write (struct file *filp, const char __user *buf, size_t cnt, loff_t *offet){

    return SUCCESS;
}
static int platdev_open (struct inode *inodep, struct file *filep){

    printk("%s %s line %d\r\n",__FILE__,__func__,__LINE__);

    return SUCCESS;
}
static int platdev_release (struct inode *inodep, struct file *filep){
    
    printk("%s %s line %d\r\n",__FILE__,__func__,__LINE__);

    return SUCCESS;
}

struct file_operations platdev_fops ={
    .owner = THIS_MODULE,
     .open = platdev_open,
     .read = platdev_read,
     .write = platdev_write,
     .release = platdev_release,
};


static int platdev_probe(struct platform_device *dev){

    int ret = 0;

    if(platdev.major){
        platdev.minor = MINOR_COUNT;
        platdev.devid = MKDEV(platdev.major, platdev.minor);
        ret = register_chrdev_region(platdev.devid,DEVICE_COUNT,DEVICE_NAME);
    }
    else{
        ret = alloc_chrdev_region(&platdev.devid,0,DEVICE_COUNT,DEVICE_NAME);
        platdev.major = MAJOR(platdev.devid);
        platdev.minor = MINOR(platdev.devid);
    }
    
    if (ret < 0){
        printk("failed to apply devid\r\n");
        goto fail_devid;
    }
    platdev.scdev.owner = THIS_MODULE;
    cdev_init(&platdev.scdev,&platdev_fops);
    if((ret = cdev_add(&platdev.scdev,platdev.devid,DEVICE_COUNT)) < 0){
        printk("failed cdev add\r\n");
        goto fail_cdev;
    }



    platdev.sclass = class_create(THIS_MODULE , DEVICE_NAME);
    if(IS_ERR(platdev.sclass)){
        ret =  PTR_ERR(platdev.sclass);
        goto fail_class;
    }

    platdev.sdevice = device_create(platdev.sclass ,NULL,platdev.devid,NULL,DEVICE_NAME);
        if(IS_ERR(platdev.sdevice)){
        ret = PTR_ERR(platdev.sdevice);
        goto fail_device;
    }

    return ret;

fail_device:
    printk("failed create device\r\n");
    class_destroy(platdev.sclass);
fail_class:
    printk("filed create class\r\n");
fail_cdev:
    cdev_del(&platdev.scdev);
    unregister_chrdev_region(platdev.devid,DEVICE_COUNT);
fail_devid:

    return ret;
}

static int platdev_remove(struct platform_device *dev){
    
    cdev_del(&platdev.scdev);
    unregister_chrdev_region(platdev.devid,DEVICE_COUNT);
    device_destroy(platdev.sclass,platdev.devid);
    class_destroy(platdev.sclass);

    return 0;
}
static const struct of_device_id platdev_of_match[] = {
        {.compatible = "platdevice-demo1"},
        {/* Sentinel */}
};
static struct platform_driver platdev_dri = {
    .driver = {
        .name = "platdevive", /* 驱动名字 */
        .of_match_table = platdev_of_match, /*设备树匹配表*/
    },
    .probe = platdev_probe,
    .remove = platdev_remove,
};

static int __init platdev_init(void){
  
  return platform_driver_register(&platdev_dri);

}
static void __exit platdev_exit(void){

    platform_driver_unregister(&platdev_dri);
}

module_init(platdev_init);
module_exit(platdev_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jiangdi");