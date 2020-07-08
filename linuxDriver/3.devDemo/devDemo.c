#include <linux/init.h>
#include<linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

#include <linux/slab.h>     /* kmalloc() */
#include <linux/errno.h>    /* error codes */
#include <linux/types.h>    /* size_t */
#include <linux/fcntl.h>    /* O_ACCMODE */
#include <linux/cdev.h>

#define BASEMINOR 0

#define COUNT 3

#define NAME "demo_dev"

static dev_t devno;
struct cdev *cdevp = NULL;

static int demo_open(struct inode* inode,struct file *file){
   printk(KERN_INFO"----%s---%s---%d---",__FILE__,__func__,__LINE__);
   return 0;
}
static int demo_release(struct inode* inode,struct file* file){
   printk(KERN_INFO"----%s---%s---%d---",__FILE__,__func__,__LINE__);
   return 0;
}

struct file_operations fops = {
   .owner = THIS_MODULE ,
   .open = demo_open ,
   .release = demo_release
};


static int __init demo_init(void){
   //0.alloc dev_t devno
   int ret ;
   ret = alloc_chrdev_region(&devno,BASEMINOR,COUNT,NAME);
   if(ret < 0){
      printk(KERN_ERR"alloc chrdev region fail\n");
      goto err1;
   }
   //1. alloc cdev
   cdevp = cdev_alloc();
   if(NULL == cdevp){
      printk(KERN_ERR"cdev alloc faile\n");
      ret = -ENOMEM;
      goto err2;
   }

   //2. cdev init
   cdev_init(cdevp,&fops);
   
   //3. cdev add
   ret = cdev_add(cdevp,devno,COUNT);
   if(ret < 0){
      printk(KERN_ERR"cdev alloc faile\n");
      goto err2;
   }

    printk(KERN_INFO"----%s---%s---%d---",__FILE__,__func__,__LINE__);
    return 0;
err2:
   unregister_chrdev_region(devno,COUNT);
err1:
   return ret;
}

static void __exit demo_exit(void){
   cdev_del(cdevp);
   unregister_chrdev_region(devno,COUNT);
   printk("----%s---%s---%d---",__FILE__,__func__,__LINE__);

}

module_init(demo_init);
module_exit(demo_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jiang Di");
MODULE_DESCRIPTION("Test Driver Module");