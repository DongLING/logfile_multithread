/*
 * ipc_semaphore.c
 * dongLING 20141003
 */

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void *doSomething1();
void *doSomething2();
void *doSomething3();

sem_t sem;

int main()
{
    // initialize semaphore to 2
    sem_init(&sem, 1, 2);

    pthread_t thread1, thread2, thread3;

    pthread_create(&thread1, NULL, &doSomething1, NULL);
    pthread_create(&thread2, NULL, &doSomething2, NULL);
    pthread_create(&thread3, NULL, &doSomething3, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    return 0;
}

void doSomething(char c)
{
    int i, time;
    for (i = 0; i < 3; i++)
	{

        // P operation
        if (sem_wait(&sem) == 0)
		{

            // generate random amount of time (< 30 seconds)
            time = (int) ((double) rand() / RAND_MAX * 30);

            printf("Thread %c enters and sleeps for %d seconds...\n", c, time);

            sleep(time);

            printf("Thread %c leaves the critical section\n", c);

            // V operation
            sem_post(&sem);
        }
    }
}

void *doSomething1()
{
    // thread A
    doSomething('A');

    return 0;
}

void *doSomething2()
{
    // thread B
    doSomething('B');

    return 0;
}

void *doSomething3()
{
    // thread C
    doSomething('C');

    return 0;
} 

/* 2.3.2 POSIX Semaphores
https://www.comp.nus.edu.sg/~phanquyt/cs2106/posix_semaphores.html
The POSIX semaphore types and functions can be found in <semaphore.h>.

Creating a Semaphore

int sem_init(sem_t *sem, int pshared, unsigned int value);

    Initializes an unnamed semaphore pointed to by sem to value. pshared indicates whether the semaphore is shared among processes (if pshared is zero, the semaphores is not shared; otherwise it is shared).
    Returns 0 on success and -1 on error
    Example

sem_t sem;
sem_init(&sem, 0, 1);

sem_t *sem_open(const char *name, int oflag);
sem_t *sem_open(const char *name, int oflag, mode_t mode, unsigned int value);

    Initializes the named name semaphore to value. oflag is defined by OR'ing two values: O_CREAT (to create a semaphore if it does not exist) and O_EXCL (to return an error if the semaphore already exists). mode specifies the permission of the semaphore.
    Returns the address of the semaphore on success, and SEM_FAILED on error.
    Example

// the absolute path to the semaphore
const char sem_name[] = "/tmp/sem";

// 0644 is the permission of the semaphore
sem_t *sem = sem_open(sem_name, O_CREAT, 0644, 1);

Waiting on a Semaphore

int sem_wait(sem_t *sem);
int sem_trywait(sem_t *sem);
int sem_timedwait(sem_t *sem, const struct timespec *abs_timeout);

    If the value of the semaphore pointed to by sem is greater than 0, sem_wait() decreases it by 1 and returns immediately. Otherwise, the process is blocked. sem_trywait() is similar to sem_wait() except that if the semaphore value is not greater than 0, it returns an error. sem_timedwait() specifies a time limit pointed to by abs_timeout. If the decrement cannot proceed and time limit expires, the function returns an error.
    All these functions return 0 on success and -1 on error.
    Example

sem_t sem;
...
if (sem_wait(&sem) == 0) {
    // do critical stuff
}

Incrementing a Semaphore

int sem_post(sem_t *sem);

    Increments the value of the semaphore pointed to by sem. If the value becomes greater than 0, a process may be unblocked.
    Returns 0 on success and -1 on error.
    Example

sem_t sem;
...
// do critical stuff
sem_post(&sem);

Getting the Value of a Semaphore

int sem_getvalue(sem_t *sem, int *sval);

    Gets the value of the semaphore pointed to by sem and places it in the location pointed to by sval.
    Returns 0 on success and -1 on error.
    Example

sem_t sem;
...
int value;
sem_getvalue(&sem, &value);

Destroying a Semaphore

int sem_destroy(sem_t *sem);

    Destroys the unnamed semaphore pointed to by sem (only used for semaphores initialized by sem_init()). If there are processes waiting on this semaphore or the semaphore has already been destroyed, the function may produce undefined behaviour.
    Returns 0 on success and -1 on error.
    Example

sem_t sem;
...
sem_destroy(&sem);

int sem_close(sem_t *sem);

    Disassociates the named semaphore pointed by sem from the process (only used for semaphores created by sem_open()). The state of the semaphore is preserved after it is closed. If the semaphore is reopened, it returns to the state when it was closed.
    Returns 0 on success and -1 on error.
    Example

const char sem_name[] = "/tmp/sem";
sem_t *sem = sem_open(sem_name, O_CREAT, 0644, 1);
...
sem_close(sem);

int sem_unlink(const char *name);

    Removes the named name semaphore. This is used after all the processes have closed the semaphore by calling sem_close().
    Returns 0 on success and -1 on error.
    Example

const char sem_name[] = "/tmp/sem";
sem_t *sem = sem_open(sem_name, O_CREAT, 0644, 1);
...
sem_close(sem);
sem_unlink(sem_name);

Example

In the following program, we have 3 threads. Each thread needs to enter the critical section 3 times, where it sleeps for a random amount of time. We initialize the semaphore to 2 so that at most 2 threads can be in the critical section at the same time. We can see in the output that this is indeed the case.

/home/dong/logfile_multithread_git_dong/ipc_semaphore/ipc_semaphore.c

Run the program:

$ gcc -Wall -o sem sem.c -lpthread -lrt
$ ./sem

-lpthread and -lrt are options passed into the compiler to use pthreads and POSIX semaphores.

Output

Thread A enters and sleeps for 25 seconds...
    Thread B enters and sleeps for 11 seconds...
    Thread B leaves the critical section
    Thread B enters and sleeps for 23 seconds...
Thread A leaves the critical section
Thread A enters and sleeps for 23 seconds...
    Thread B leaves the critical section
    Thread B enters and sleeps for 27 seconds...
Thread A leaves the critical section
Thread A enters and sleeps for 5 seconds...
Thread A leaves the critical section
Thread C enters and sleeps for 10 seconds...
    Thread B leaves the critical section
Thread C leaves the critical section
Thread C enters and sleeps for 23 seconds...
Thread C leaves the critical section
Thread C enters and sleeps for 8 seconds...
Thread C leaves the critical section

The indentation and use of colours are to make the output a bit easier to read. Two lines that have the same colour and indentation level indicate that they are the correspoding entry and exit to and from the critical section of one thread. With the use of a random amount of sleeping time inside the critical section, we can see the interleavings of the threads more clearly. We also notice that there are at most two threads in the critical section at the same time (i.e. at most two nested "enters..." with different colours). This is what we expect because the semaphore is initialized to 2.

Through this example, we have shown how POSIX semaphores can be used. We also go through the output of the program and verify that the maximum number of threads that can be in the critical section at the same time is exactly the initial value of the semaphore.
References
1. Semaphores
2. Synchronizing Threads with POSIX Semaphores
3. Linux man pages
4. Semaphores, Message Queues and Shared Memory
5. IPC:Semaphores (Information on UNIX System V IPC Semaphores, another way to implement/use semaphores.) */
