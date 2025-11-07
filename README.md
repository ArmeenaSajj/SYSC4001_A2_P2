# SYSC4001_A2_P2
Concurrent Processes in Unix
SYSC4001 – Assignment 2 (Part 2)
- Armeena Sajjad (101295773)
- Ajay Uppal (101308579)

This assignment explores how processes are created and how they communicate in Linux.  
We start by making two processes with fork() then we move to launching a second program with exec() and 
wait for a child process to finish, using shared memory to share variables, and finally using 
semaphores to protect shared memory.

Part 2.1 (part1.c)
- Uses fork() to create two processes.
- Each process runs its own counter in an infinite loop.
- To stop the program: use `ps` to find the PID, then `kill <PID>`.

Run:
    make part1
    ./part1

Parts 2.2–2.5 (process1.c and process2.c)

Process 1 = Parent program  
Process 2 = Child program launched using exec()

Part 2.2:
- Process 1 increments a counter and prints when values are multiples of 3.
- Process 2 decrements a counter and also prints multiples of 3.
Run:
    make part2
    ./process1

Part 2.3:
- Process 1 waits for Process 2 to finish.
- Process 2 stops when its counter goes below -500.
Run:
    make part3
    ./process1

Part 2.4:
- Shared memory is added.
- Shared counter is not printed by Process 2 until it is > 100.
- Both processes end when the shared counter is > 500.
Run:
    make part4
    ./process1

Part 2.5:
- Same as Part II.4, but shared memory is protected using a semaphore so only one process 
  accesses it at a time.
Run:
    make part5
    ./process1

How to Stop:
    ps aux | grep process
    kill <PID>
