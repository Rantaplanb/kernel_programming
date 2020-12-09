/*-----Mertzanis Loukas-----
 *--------AM: 4457----------
 *-------Assignment 3-------
 *-----------Hy345----------
*/

#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <asm/uaccess.h>
#include <linux/slab.h>
#include <linux/d_params.h>

asmlinkage long sys_set_deadlines(int pid, unsigned long deadline,unsigned long computation_time)
{
    struct task_struct *tmp;
    printk("\ncsd4457: set_deadlines was called with arguments:");
    printk("\npid:%d \ndeadline:%lu \ncomputation_time:%lu", pid, deadline, computation_time);
	
	if(deadline > computation_time)
	{
		printk("\nDeadline should be greater or equal to computation_time!");
		return EINVAL;
	}

    if (pid == -1 || pid == current->pid) /*for current process*/
    {
        /*current points to the task struct of the process that called our syscall*/
        current->deadline = deadline;
        current->computation_time = (int)computation_time;
        printk("\nCurrent proccess' deadlines were set!");
        return 0;
    }

    if (pid == 0 || pid < -1)
    {
        printk("\nInvalid pid argument!");
        return EINVAL;
    }

    for_each_process(tmp) /*for child proccesses*/
    {
        if (pid == tmp->pid && tmp->parent->pid == current->pid)
        {
            tmp->deadline = deadline;
            tmp->computation_time = (int)computation_time;
            printk("\nChild's proccess deadlines were set!");
            return 0;
        }
    }
    printk("\nThe given pid was either invalid, or it did not match neither current nor any child pid!");
    return EINVAL;
}