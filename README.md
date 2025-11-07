# SYSC4001_A2_P
SYSC4001 – Assignment 2 (Part 2)

- Ajay Uppal (101308579)
- Armeena Sajjad (101295773)

This assignment shows how two processes run and communicate in Linux.

Part 2.1 (part1.c)
- Uses fork() to create two processes.
- Each process runs its own counter.
Run:
    make part1
    ./part1
Stop:
    ps aux | grep part1
    kill <PID>

Parts 2.2–2.5 (process1.c and process2.c)

Process 1 = parent program  
Process 2 = child program launched using exec()

Part 2.2:
- Process 1 counts up, Process 2 counts down.
Run:
    make part2
    ./process1

Part 2.3:
- Process 1 waits for Process 2 to finish.
Run:
    make part3
    ./process1

Part 2.4:
- Shared memory is added.
- Process 2 starts printing only after the shared counter > 100.
Run:
    make part4
    ./process1

Part 2.5:
- Same as Part 2.4, but shared memory is protected using a semaphore.
Run:
    make part5
    ./process1
