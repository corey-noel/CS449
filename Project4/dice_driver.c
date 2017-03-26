/*
 * "Dice roller." minimal kernel module - /dev version
 *
 * Valerie Henson <val@nmt.edu>
 *
 * Modified by Corey Noel
 * For CS 0449 Assignment 4
 * University of Pittsburgh
 */

#include <linux/fs.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/random.h>

#include <asm/uaccess.h>

/*
 * dice_read is the function called when a process calls read() on
 * /dev/dice.  It writes a one byte value between 0 and 5 inclusive 
  *to the buffer passed in the read() call.
 */

static ssize_t dice_read(struct file * file, char * buf, size_t count, loff_t *ppos) {
	char *rolls;
	get_random_bytes(rolls, count);

	/*
	 * If file position is non-zero, then assume the string has
	 * been read and indicate there is no more data to be read.
	 */
	if (*ppos != 0)
		return 0;
	/*
	 * Besides copying the string to the user provided buffer,
	 * this function also checks that the user has permission to
	 * write to the buffer, that it is mapped, etc.
	 */
	if (copy_to_user(buf, hello_str, len))
		return -EINVAL;

	*ppos = count;
	return count;
}

/*
 * The only file operation we care about is read.
 */

static const struct file_operations dice_fops = {
	.owner		= THIS_MODULE,
	.read		= dice_read,
};

static struct miscdevice dice_dev = {
	/*
	 * We don't care what minor number we end up with, so tell the
	 * kernel to just pick one.
	 */
	MISC_DYNAMIC_MINOR,
	/*
	 * Name ourselves /dev/dice.
	 */
	"dice",
	/*
	 * What functions to call when a program performs file
	 * operations on the device.
	 */
	&dice_fops
};

static int __init
dice_init(void) {
	int ret;

	/*
	 * Create the "dice" device in the /sys/class/misc directory.
	 * Udev will automatically create the /dev/dice device using
	 * the default rules.
	 */
	ret = misc_register(&dice_dev);
	if (ret)
		printk(KERN_ERR
		       "Unable to register \"Dice roller\" misc device\n");

	return ret;
}

module_init(dice_init);

static void __exit
dice_exit(void) {
	misc_deregister(&dice_dev);
}

module_exit(dice_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Valerie Henson <val@nmt.edu>");
MODULE_DESCRIPTION("\"Dice roller\" minimal module");
MODULE_VERSION("dev");
