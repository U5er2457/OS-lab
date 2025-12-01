#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/jiffies.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Jednostavan modul koji ispisuje broj jiffiesa i vrijeme");
MODULE_AUTHOR("PK");

int mojmodul_init(void) {
    printk(KERN_INFO "Jiffies = %lu, vrijeme = %lu sekunde\n", jiffies, jiffies/HZ);
    return 0;
}

void mojmodul_exit(void) {
    printk(KERN_INFO "Jiffies = %lu, vrijeme = %lu sekunde\n", jiffies, jiffies/HZ);
}

module_init(mojmodul_init);
module_exit(mojmodul_exit);

/*

Makefile:
obj-m += mojmodul.o
all:
    make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
    make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean


naredbe:
make
insmod mojmodul.ko
lsmod -- ispis učitanih modula
dmesg -- dnevnik jezgre
rmmod mojmodul -- uklanjanje modula
*/
