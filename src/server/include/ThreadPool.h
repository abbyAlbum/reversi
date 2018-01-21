//
// Created by eyal on 21/01/18.
//

#ifndef EX1_THREADPOOL_H
#define EX1_THREADPOOL_H


#include "Task.h"
#include <queue>
#include <pthread.h>

using namespace std;

class ThreadPool {
public:
    ThreadPool(int threadsNum);
    void addTask(Task *t);
    void terminate();
    virtual ~ThreadPool();

private:
    queue<Task *> tasks;
    pthread_t *threads;
    void executeTasks();
    bool stopped;
    pthread_mutex_t lock;

    static void *execute(void *arg);
};


#endif //EX1_THREADPOOL_H
