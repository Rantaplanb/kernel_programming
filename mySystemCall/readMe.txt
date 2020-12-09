/*-----Mertzanis Loukas-----
 *--------AM: 4457----------
 *-------Assignment 3-------
 *-----------Hy345----------
*/

I implemented the system call set_deadlines in the linux
operating system. To do so, i added 2 fields in the
task_struct, deadline and computation_time. When the macro
set_deadlines(pid, deadline, compTime) is triggered to test the syscall,
syscall(341, a1, a2, a3) is called (341 is the number of our
system call) and a trap to kernel level occurs. In kernel
level, we search for the process with pid, then, if we are
allowed to do so, we change the 2 added fields of task_struct
of the process with pid to the system call arguments.
Appropriate messages are logged, in order to check if
our system call behaved properly.

I am sending all the files that i wrote/modified in
a directory tree structure, equivalent to that of the
Linux OS, for you to be able to check easily which
files were modified.

The file d_params.h is actually useless in my
implementation, but I added it to the kernel 
as the assignment instructions suggested.

Thanks!