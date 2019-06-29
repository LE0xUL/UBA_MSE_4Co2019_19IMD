#include <linux/init.h>
#include <linux/utsname.h>
#include <linux/module.h>
#include <linux/kernel.h>

static int __init hello_init(void)
{
    pr_alert("Hello Master. You are currently using Linux: %s\n", init_uts_ns.name.release);
    return 0;
}

// static int __init hello2_init(void)
// {
//     pr_alert("Hello #2 Master. You are currently using Linux: %s", init_uts_ns.name.release);
//     return 0;
// }

static void __exit hello_exit(void)
{
    pr_alert("Good Bye\n");
}

// static void __exit hello2_exit(void)
// {
//     pr_alert("Good Bye #2");
// }

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Greeting module");
MODULE_AUTHOR("William Shakespeare");