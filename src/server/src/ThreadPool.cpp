//
// Created by eyal on 21/01/18.
//

#include "../include/ThreadPool.h"
#include <unistd.h>

/**
 * c'tor for thread pool
 * @param threadsNum num of threads
 */
ThreadPool::ThreadPool(int threadsNum) : stopped(false) {
    threads = new pthread_t[threadsNum];
    for (int i = 0; i < threadsNum; ++i) {
        pthread_create(threads + i, NULL, execute, this);
    }
    pthread_mutex_init(&lock, NULL);
}

/**
 * executes the tasks
 * @param arg threadPool
 * @return
 */
void * ThreadPool::execute(void *arg) {
    ThreadPool *deadPool = (ThreadPool *) arg;
    deadPool->executeTasks();
}

/**
 * adds a task to the queue
 * @param t taks to add
 */
void ThreadPool::addTask(Task *t) {
    tasks.push(t);
}

/**
 * executes the tasks
 */
void ThreadPool::executeTasks() {
    while (!stopped) {
        pthread_mutex_lock(&lock);
        if (!tasks.empty()) {
            Task *t = tasks.front();
            tasks.pop();
            pthread_mutex_unlock(&lock);
            t->execute();
        } else {
            pthread_mutex_unlock(&lock);
            sleep(1);
        }
    }
}

/**
 * stops the execution of the tasks
 */
void ThreadPool::terminate() {
    pthread_mutex_destroy(&lock);
    stopped = true;
}

/**
 * d'tor for thread pool
 */
ThreadPool::~ThreadPool() {
    delete[] threads;
}
