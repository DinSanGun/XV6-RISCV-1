# xv6 Assignment 1 — Processes, System Calls & Scheduling  
*Based on OS Assignment 1: Processes and Scheduling*

## 📌 Overview  
This project extends the xv6-riscv teaching operating system by adding new system calls, modifying the process control block, and implementing multi-process workloads.  
It introduces fundamental OS concepts including userspace/kernel transitions, memory measurement, process lifecycle management, and simple parallel computation.

---

## 🚀 Implemented Features

### 1️⃣ Userspace Program: `helloworld.c`  
A minimal program demonstrating how xv6 compiles, links, and runs user applications.

### 2️⃣ System Call: `memsize()`  
Returns the memory footprint of the calling process in bytes.

#### Work Included
- Registered a new syscall number + wrapper.  
- Implemented `sys_memsize()` using the PCB `sz` field.  
- Created a test program to measure memory before/after allocations.

---

## 🧩 Extending Process Termination: Exit Messages  
Enhanced the `exit()` system call to support human-readable exit messages.

### Additions
- Introduced `exit_msg[32]` into `struct proc`.  
- Modified `exit()` to accept a message from userspace.  
- Modified `wait()` to return this message to the parent.  
- Updated the shell to display messages of terminated child processes.

This required safe userspace→kernel (`argstr`) and kernel→userspace (`copyout`) transfers.

---

## ⚙️ Multi-Process Work Distribution: `forkn()` and `waitall()`  

### `forkn(n, pids[])`
- Creates *n* child processes **atomically**.  
- If any creation fails, all partial children are cleaned up.  
- Parent receives `0`; each child receives its own sequence index.

### `waitall(&n, statuses[])`
- Waits for all child processes belonging to the caller.  
- Returns number of completed children and their exit statuses.  
- Avoids deadlocks by respecting xv6 process-locking constraints.

---

## 🧮 Example Application: `bigarray.c`  
A parallel reduction program using the new system calls.

### Workflow
1. Initialize a large integer array.  
2. Spawn multiple processes with `forkn()`.  
3. Each child computes a partial sum.  
4. Child returns result via exit status.  
5. Parent aggregates results and prints final sum.

---

## 🛠️ Skills Demonstrated
- Kernel modification & system call design  
- PCB extension, memory safety, and argument handling  
- Controlled multi-process creation and cleanup  
- Understanding of xv6 scheduling and process lifecycle  
- Designing user applications that leverage custom OS primitives  

---

## 📜 License  
For academic and demonstration purposes only.
