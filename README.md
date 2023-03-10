# Computer System

This repo contains my study notes and learning projects contained in the Ohio State University course CSE2431.

## Virtualization

- Definition of an OS  
   Software that converts hardware into a useful form for applications: Make sure the system operates correctly and efficiently in an easy to use manner.
- What are the three "pieces" of every modern OS, and what is the basic description of each of them? What abstractions are associated with each of the 3 pieces?

  - Virtualization  
    make the system behave so that each application can run as though it has certain critical resources to itself; i.e., make it believe it has exclusive use of each critical resource in the system (no sharing)  
    (⭕️related abstractions: process, address space)
  - Concurrency  
    OS must be able to handle concurrent events which can interact  
    (related abstractions: locks, semaphores, condition variables, shared memory, critical sections)
  - Persistence  
    preserve information permanently  
    (related abstractions: files, directories, links)

- What are some reasons cited in the class slides for studying operating systems?

  - build, modify, or administer an OS
  - behavior of OS impacts entire machine
  - tune workload performance
  - apply knowledge accross many layers(computer architecture, programming languages, data structure and algo, and performance modeling)

- Definition of a process  
  An execution stream in the context of a process execution state

- What is an execution stream

  - Stream of an executing instructions
  - Running piece of code
  - "thread of control"

- What is process execution state  
  Everything that the running code can affect or be affected by, including registers, address space and open files

- What is the difference between a process and a program?

  - Program: Static code and static data(on disk)
  - Process: Dynamic instance of code and data(in memory)

- What are typical interfaces/actions provided by the process API

  - Create
  - Destroy
  - Wait
  - Miscellaneous control
  - Status

- What does the OS(Unix/Linux) do to create a process

  1. bring the program's code and static data from disk into memory
  2. allocate space for a stack segment
  3. allocate space for the heap
  4. set up I/O facilities

- After the process is created, what must be done for the process to start execution?  
  The entry point must be stored as part of the executable which runs as the process

- What are the three process states, and what is a process doing in each state?

  - Ready: everything the process needs to run is in memory and I/O has been set up, the process is waiting in line to be able to execute instructions on the CPU
  - Running: the process is executing instructions on the CPU
  - Blocked: the process is waiting in line for some event to occur (e.g., I/O transfer, wait for a lock to be available)

- What are the differences between direct execution and limited execution?

  - Direct execution: OS creates process and transfers control to starting point, then process run directly on hardware.
  - Limited execution: OS and hardware maintain some control

- What are some problems with direct execution?

  - Process could do things that are not allowed
  - Process could run forever
  - Process could do something slow

- How does the hardware and the OS provide limited direct execution by processes on the CPU?  
  Use hardware to provide privilege levels: user processes run in user/unpriviledged/restricted mode, while OS runs in kernel/privileged/unrestricted mode.

- ⭕️What is the difference between an interrupt and an exception?  
  Interrupt is initiated by devices/hardware, while exception is initiated by processes.

- What are the two types of exceptions, and how are they different?

  - Traps: for a trap instruction, the instruction does not execute again after the trap is handled by the OS(system calls / errors)
  - Faults: when an instruction causes a fault, the instruction executes again after the fault is handled by the OS

- Why must the CPU(rather than the OS) change the status bit from user mode to privileged mode? When does the CPU do this?  
  If the OS kernel can change from the user mode to kernel mode, then user processes would also be able to make this change, and the purpose of the mode bit is defeated.  
  ⭕️It occurs when kernel code starts executing.
- Does the CPU or the OS change the status bit from privileged mode to user mode? When does it do this?  
  OS change the status bit from privileged mode to user mode.  
  ⭕️It occurs when kernel code finishes executing.

- What kinds of things are user processes not allowed to do?(in user mode, which is how user processes execute instructions)

  - General memory access
  - Disk I/O
  - Othes, e.g., changing the address in the PC

- ⭕️What happens if a user process tries to do something which is restricted(not permitted for user processes to do)?  
  The OS provides some security mechanisms to prevent the process from performing the action, e.g.

  - Permission denied error
  - Process termination
  - Access control enforcement

- How is the CPU taken away from a user process which is executing instructions? (how does the dispatcher get control of the CPU again?)  
  OS uses a periodic alarm clock while the interruption is generated by hardware, and the user process must not be able to mask(disable) timer interrupt.

- What is a context switch? What data is saved for one process and restored for another when a context switch occurs?  
  Context switch: OS saves the context/state of a running process so that it can be restored later, and then restores the context of another process so that it can be executed.  
  ⭕️In context switch, only registers related to process execution state need to be saved.

- What are the problems with cooperative multi-tasking?  
  Proceses may not cooperate and they can misbehave by avoiding all traps.

- What does "true multi-tasking" mean?  
  Guarantee OS/dispatcher can obtain control periodically.

- What does Unix/Linux fork do? ⭕️What are all the things which must be done to create a new process?  
  fork():
  - Stop current process and save its state
  - Make copy of code, data, stack and PCB
  - Add new PCB to ready list
  - ⭕️Any changes needed to child process?
