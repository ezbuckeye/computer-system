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

## Concurrency

### Threads

- What factors lead to increased concurrency in applications since about 2005?  
  Since clock speed increases, the chip dissipates more heat.(especially as circuit elements shrink in size)  
  While exotic cooling is impractical in most modern systems, this leads to the trend of "Same speed, but multiple cores" for CPU.  
  In order to fully utilize multiple cores, it's necessary to increase concurrency in applications to be faster.

- What two options/approaches are covered in the class slides for building concurrent applications? What are the advantages and disadvantages of each approach?

  - Option 1: Build apps from many communicating processes
    - Pros:
      - Don't need new abstractions
      - ⭕️good for security
    - Cons:
      - Cumbersome programming
      - High communication overheads
      - Expensive context switching(why?⭕️ Thread context switching is cheaper)
  - Option 2: New abstraction -> thread

- Name the three common programming models for multithreaded applications.

  - Producer/consumer
  - Pipeline
  - Defer work from background thread

- What state do multiple threads which are part of the same process share (see below for more specific questions)?

  - page table base register (PTBR) value
  - address space (except stack)
    - code
    - heap
  - Process ID (PID)
  - Open file descriptors
  - Current working directory
  - User and group id

- Do threads which are part of the same process share an instruction pointer (IP) (in other words, do their Ips hold the same value)?  
  No, they don't. Even though they share code, but each thread may be executing different code at the same time.

- Do threads which are part of the same process share a stack segment?  
  No, they don't. Threads executing different functions (or even different instances of the same function) need different stacks.

- Be able to name the three common thread operations identified in the slides, and what each operation does (and the comparable operation for processes).

  - Create
  - Exit
  - Join (like wait() for process, but called join() for threads)

- Name and understand the characteristics of the two approaches to OS support for threads in the slides (User-level thread libraries, kernel threads). What are the advantages and disadvantages of each of these approaches?

  - User-level threads: Many-to-one thread mapping
    - Pro
      - Does not require OS support; Portable
      - Can tune scheduliong policy to meet app demands
      - Lower overhead thread operations since no system call for operations
    - Con
      - Cannot leverage multiprocessors -> no concurrent execution
      - Entire process blocks when one thread blocks
  - Kernel-level threads: One-to-one thread mapping
    - Pro
      - Each kernel-level thread can run in parallel on a multiprocessor
      - When one thread blocks, other threads from process can still be scheduled
    - Con
      - Higher overhead for thread operations; system calls required
      - OS must scale well with increasing number of threads

- Be able to define non-deterministic behavior of programs in terms of the relationship between input and output for the same program run multiple times  
  Non-determinism means that the same program, run multiple times with the same input, produces different output.

- What is the definition of a critical section?  
  A block a code that should be atomic/uniterruptable, otherwise would lead to race conditions.

- What does it mean for a critical section to execute atomically?  
  The code would not be interrupted by other relevant threads.

- How can races in a critical section lead to non-deterministic results if mutual exclusion is not insured?  
  If multiple threads could get access to a critical section at the same time, the read data might be "corrupted" / the write data might be "overwrote".

- What is the definition of mutual exclusion for critical sections?  
  If thread A is in critical section C, process B can't be. (okay if other threads do unrelated work, i.e., wrok not in critical sections)

- Be able to name and explain the operations for locks (allocate/initialize, acquire, release).
  - Allocate and Initialize
    ```
    Pthread_mutex_t mylock = PTHREAD_MUTEX_INITIALIZER;
    ```
  - Acquire
    ```
    Pthread_mutex_lock(&mylock);
    ```
    wait if lock is not available
  - Release
    ```
    Pthread_mutex_unlock(&mylock);
    ```
    release exclusive access to lock, let another process enter critical section

### Locks

- Be able to name the lock implementation goals, and briefly explain each.

  - Correctness
    - Mutual exclusion
    - Progress (deadlock-free)
    - Bounded (starvation-free)  
      Must eventually allow each waiting thread to enter
  - Fairness  
    Each thread waits for (roughly) same amount of time
  - Performance  
    CPU is not used unnecessarily (e.g., spinning)

- ⭕️When can locks be implemented with interrupts? What are the disadvantages of doing this, even when it is possible? In what kinds of systems can this not be done?
  Disadvantages:

  - Process can keep control of CPU for arbitrary time
  - Cannot perform other necessary work without interrupts
    Undesired systems:
  - multi-processors systems, since we cannot disable interrupts by other cores.

- What is the problem with implementing a lock with load and store instructions and a shared lock variable?  
  `while(*lock) /* wait */` is also a critical section, it will lead to the fact that multiple threads might grab the lock at the same time since Testing lock and Setting lock are not atomoic.

- Briefly describe Peterson’s Algorithm for implementation of a lock

  - software-based solution
  - shared turn variable and lock array with one element for each thread.

- ⭕️Why does Peterson’s Algorithm not work in modern systems

  - Cache coherency
  - different copes of a cached lock value might not have a consistent (equal) value)?

- Briefly explain the atomic xchg instruction (Test-And-Set or TAS).

  - write newval into addr
  - return the old value of \*addr

- Briefly explain the atomic CompareAndSwap instruction.

  - write newval into addr iff the old value equals to expected one
  - return the old value of \*addr

- To what value is a shared lock variable initialized in order to be used for a lock with TAS or CompareAndSwap?  
  `lock->flag = 0; /*indicates that the lock is unused*/`

- How can TAS or CompareAndSwap be used to acquire a lock using busy waiting?

  ```
  /*TAS*/
  while(xchg(&lock->flag, 1) == 1);

  /*CompareAndSwap*/
  while(CompareAndSwap(&lock->flag, 0, 1) == 1);
  ```

- How can a lock be released using TAS or CompareAndSwap?

  ```
  /*TAS or CompareAndSwap*/
  lock-flag = 0
  ```

- What is a spinlock? ⭕️Why are basic spinlocks unfair?  
  if a spinlock is waited by a thread, a thread will still be scheduled by Scheduler and just spin during its slice.

- When can spinlocks be fast?

  - many CPUs
  - locks held a short time
  - pro: avoid context switch

- When can spinlocks be slow?

  - one CPU
  - locks held a long time
  - con: spinning is wasteful

- What is the cost/waste/loss with spinlocks both with and without yield?
  - with yield: O(threads \* context_switch)
  - without yield: O(threads \* time_slice)
