#include <job_scheduler.h>

// init initQueue[50];
// int initCount = 0;

// pthread_mutex_t mutexInit;
// pthread_cond_t condInit;



// void executeTask (init* task)
// {
//     task->taskFunction(task->graph, task->id, task->row, task->column, task->data);
// }



// void submitTask(init task) {
//     pthread_mutex_lock(&mutexInit);
//     initQueue[initCount++] = task;
//     pthread_mutex_unlock(&mutexInit);
//     pthread_cond_signal(&condInit);
// }



// void* startThread(void* args) {
//     while (1) {
//         init task;

//         pthread_mutex_lock(&mutexInit);
//         while (initCount == 0) {
//             pthread_cond_wait(&condInit, &mutexInit);
//         }

//         task = initQueue[0];
//         int i;
//         for (i = 0; i < initCount - 1; i++) {
//             initQueue[i] = initQueue[i + 1];
//         }
//         initCount--;
//         pthread_mutex_unlock(&mutexInit);
//         executeTask(&task);
//     }
// }