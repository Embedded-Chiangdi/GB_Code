#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/slab.h>

#define GLOBAL_MEM_SUCCESS 0
#define GLOBAL_MEM_FAILED 1
#define GLOBAL_MEM_NAME "global_mem"
#define GLOBAL_MEM_CLASS_NAME "global_mem_class"
#define GLOBAL_COUNT 1

struct global_mem_charDev{
    dev_t gmDevId;
    struct cdev gmCdev;
    struct class *gmClass;
    struct device *gmDevice;
    int major;
    int minor;
} gmdev;

static int gm_open(struct inode *ino, struct file *f)
{

	return 0;
}

static int gm_release(struct inode *ino, struct file *f)
{

	return 0;
}


static ssize_t gm_read(struct file *f, char __user *buf, size_t count,
		       loff_t *offp)
{

    return count;
}

static ssize_t gm_write(struct file *f, const char __user *buf, size_t count,
			loff_t *offp)
{
    return count;
}

static const struct file_operations gm_fops = {
	.owner = THIS_MODULE,
	.open = gm_open,
	.release = gm_release,
	.read = gm_read,
	.write = gm_write,
};

static int __init gm_init(void){
    
    printk("Hello Gm Init\r\n");
    
    printk("%s %s line %d\r\n",__FILE__,__func__,__LINE__);
    
    return GLOBAL_MEM_SUCCESS;
}

static void __exit gm_exit(void){

    printk("Bye Gm Exit\r\n");

    printk("%s %s line %d\r\n",__FILE__,__func__,__LINE__);

    return ;
}

module_init(gm_init);
module_exit(gm_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jiang DI");
MODULE_DESCRIPTION("Global Mem Driver Module");