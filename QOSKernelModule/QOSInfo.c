#include <linux/module.h>
#include <linux/printk.h>
 #include <linux/kobject.h> 
#include <linux/sysfs.h> 
#include <linux/init.h> 
#include <linux/fs.h> 
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/netdevice.h> //
#include <linux/net_namespace.h>
#include <net/sch_generic.h> //

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ZUHERMAHER");
char* program_name = "QOSQueueSizeProject";
module_param(program_name,charp,S_IRUGO);

//-- Some global variables for our usage.
static struct kobject *glob_register_kobj;
static char* glob_dev_name;
static size_t glob_pid = 10;
static const int glob_error_value = -1;

//-----------------------------------------
//-- functionality that is added to kernel.
//-----------------------------------------
static ssize_t getQueueSize(struct kobject *kobj, struct kobj_attribute *attr,
                      char *buf)
{
    struct net_device* dev;
	struct Qdisc *curr_q;
	int num_of_packets = 0;
	struct net* the_net = get_net_ns_by_pid(glob_pid);
	if (!the_net)
	{
		printk(KERN_INFO "get_net_ns_by_pid falied\n");
		return 1;
	}
	read_lock(&dev_base_lock); //-- lock net device
	dev = first_net_device(the_net);
	while(dev)
	{
		printk(KERN_INFO "found [%s]\n", dev->name);
		dev = next_net_device(dev);
	}
	dev = dev_get_by_name(the_net, glob_dev_name);
	if(!dev)
	{
	    return sprintf(buf, "%d\n", glob_error_value);
	    return 0;
	}	
	curr_q = dev->qdisc;
	while (curr_q)
	{
		num_of_packets += curr_q->q.qlen;
		curr_q = curr_q->next_sched;
	}
	read_unlock(&dev_base_lock);
	return sprintf(buf, "%d\n", num_of_packets);
}

static ssize_t __used setDevice(struct kobject *kobj, struct kobj_attribute *attr,
                      const char *buf, size_t count)
{
        sscanf(buf, "%s %zu", glob_dev_name, &glob_pid);
		printk(KERN_INFO "device is %s\n", glob_dev_name);
//		sscanf(buf, "%zu", glob_pid);
		printk(KERN_INFO "found [%zu]\n", glob_pid);
        return count;
}

//-----------------------------------------
//-----------------------------------------
//-----------------------------------------

//-- Set of attributes to be added for the kernel object. 
//-- Setters
static struct kobj_attribute glob_store_attribute =__ATTR(setDevice, 0220, NULL,
                                                     setDevice);
//-- Getters
static struct kobj_attribute glob_print_attribute =__ATTR(getQueueSize, 0660, getQueueSize,
                                                     NULL);

// -----------------------//
static struct attribute *glob_register_attrs[] = {
    &glob_print_attribute.attr,
    &glob_store_attribute.attr,
    NULL,   /* NULL terminate the list*/
};
static struct attribute_group  glob_reg_attr_group = {
    .attrs = glob_register_attrs
};


int init_module (void)
{
	//-- allocate memory for glob_dev_name 
	glob_dev_name = kzalloc(PAGE_SIZE, GFP_KERNEL);
	if (!glob_dev_name) return -ENOMEM;
	
	//-- Create kernel object and check validity.
	glob_register_kobj = kobject_create_and_add("QOSInfo", kernel_kobj);
	if (!glob_register_kobj)
	{
		kfree(glob_dev_name);
		return -ENOMEM;
	}
	
	//-- Add attributes to kernel object, and check validity.
	if(sysfs_create_group(glob_register_kobj, &glob_reg_attr_group))
	{
		kfree(glob_dev_name);
       		kobject_put(glob_register_kobj); // free created kernel object.
       		return -ENOMEM;
    	}
	return 0;
}

void cleanup_module (void)
{
	kfree(glob_dev_name);
        kobject_put(glob_register_kobj);
}
