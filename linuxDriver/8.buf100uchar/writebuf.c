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



#define DEVICE_NAME "writebuf"
#define DEVICE_COUNT 1
static dev_t dev;
static struct cdev wf_cdev;
static struct class *class_p;
static struct device *device_p;

#define WF_SIZE 1024
#define MIN_SIZE(x , y)  ( x < y ? x : y )
/*ioctls*/
#define TYPE_KEY 'w'
#define COMMAND_WF1 _IOWR(TYPE_KEY,1,unsigned long)
#define COMMAND_WF2 _IOWR(TYPE_KEY,2,unsigned long)
#define COMMAND_WF3 _IOWR(TYPE_KEY,3,unsigned long)

static ssize_t dev_write(const void *buf,size_t count){
    int i , j;
    const unsigned char *temp = buf;
    for(i =0 ;i < 64;i++){
        printk("Line%d: ",i+1);
       for(j=0; j<16;j++){
           printk("%#x,",*temp);
           temp++;
       }
        printk("\n");
    }

    return count;
}

static long wf_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    int err = 0;
    char ioarg = 1;
    switch(cmd){
        case COMMAND_WF1:
                printk("Enter COMMAND1 Program! arg = %ld\n",arg);
            break;
        case COMMAND_WF2:
                printk("Enter COMMAND2 Program! \n");
            break;
        case COMMAND_WF3:
                printk("Enter COMMAND3 Program! ouput %d \n",ioarg);
                put_user(ioarg,(char *)arg);
            break;
        default:
                printk("No ops\n");
                err = -1;
            break;
    }

    return err;
}
static int wf_open(struct inode *inode, struct file *filp){
    
    printk("Open wf chrDev\n");

    return 0;
}
static int wf_release(struct inode *inode, struct file *filp){
    
    printk("Closed wf chrDev\n");

    return 0;
}
static ssize_t wf_read(struct file *filp, char __user *buf,
			 size_t count, loff_t *f_pos)
{
    int retval = 0;
    char status[]="-1";

    if(copy_to_user(buf,status,sizeof(status))){
        retval = -1;
        goto err;
    }
    
    printk("Read %d bytes\n",1);

err:
    return retval;
}
static ssize_t wf_write(struct file *filp, const char __user *buf,
			  size_t count, loff_t *f_pos)
{
    int retval = 0;
    void *kernbuf;

    kernbuf = kmalloc(WF_SIZE,GFP_KERNEL);
    if(!kernbuf){
        retval = -1;
        goto err;
    }

    while(count){
        int bytes_this_pass = MIN_SIZE(count,WF_SIZE);

        if(copy_from_user(kernbuf,buf,bytes_this_pass) != 0){
            retval = -2;
            break;
        }
        count -= bytes_this_pass;   
        
        retval = dev_write(kernbuf,bytes_this_pass);

        printk("received %d bytes\n",bytes_this_pass);
        
    }


    kfree(kernbuf);

err:
    return retval;
  
}
static const struct file_operations wf_fops = {
    .owner = THIS_MODULE,
    .read =	     wf_read,
	.write =     wf_write,
	.open =	     wf_open,
	.release =   wf_release,
    .unlocked_ioctl = wf_ioctl,
};

static int __init wf_init(void){
    int ret = 0;

    if((ret = alloc_chrdev_region(&dev,0,DEVICE_COUNT,DEVICE_NAME)) < 0){
        printk(KERN_ERR"wf couldn't alloc chrdev region , error = %d",ret);
        return ret;
    }


    cdev_init(&wf_cdev,&wf_fops);
    wf_cdev.owner = THIS_MODULE;
    wf_cdev.ops = &wf_fops;

    if((ret = cdev_add(&wf_cdev,dev,DEVICE_COUNT))){
        printk(KERN_ERR"Could not cdev_add, error = %d",ret);
        goto undo_chrdev_region;

    }

    class_p = class_create(THIS_MODULE,DEVICE_NAME);
    if(IS_ERR(class_p)){
        ret = PTR_ERR(class_p);
        goto undo_cdev;
    }


    device_p = device_create(class_p,NULL,dev,NULL,DEVICE_NAME);
    if (IS_ERR(device_p)) {
		ret = PTR_ERR(device_p);
		goto undo_class;
	}
    printk("wf Module probe\n");
    return ret;

undo_class:
    class_destroy(class_p);
undo_cdev:
    cdev_del(&wf_cdev);
undo_chrdev_region:
    unregister_chrdev_region(dev, DEVICE_COUNT);
    return ret;

}
static void __exit wf_exit(void){
    
    device_destroy(class_p,dev);
    class_destroy(class_p);
    cdev_del(&wf_cdev);
    unregister_chrdev_region(dev, DEVICE_COUNT);
    
    printk("leave wf Module \n");
    return ;
}

module_init(wf_init);
module_exit(wf_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jiang Di");
MODULE_DESCRIPTION("Test Driver Module");

