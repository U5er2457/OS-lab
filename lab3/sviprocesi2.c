#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Jednostavan modul koji ispisuje procese s parent PID");
MODULE_AUTHOR("PK");

int sviprocesi_init(void) {
    struct task_struct *task;

    printk(KERN_INFO "Ispis svih procesa:\n");
    for_each_process(task) {
        printk(KERN_INFO "Ime procesa: %s, PID: %d, Parent PID: %d\n",
               task->comm, task->pid, task->real_parent->pid);
    }

    return 0;
}

void sviprocesi_exit(void) {
    printk(KERN_INFO "Uklanjanje jezgrenog modula.\n");
}

module_init(sviprocesi_init);
module_exit(sviprocesi_exit);

/*

Makefile:
obj-m += sviprocesi2.o
all:
    make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
    make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean


naredbe:
make
insmod sviprocesi2.ko
lsmod -- ispis učitanih modula
dmesg -- dnevnik jezgre
rmmod sviprocesi2 -- uklanjanje modula
*/
