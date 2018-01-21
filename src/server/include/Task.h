//
// Created by eyal on 21/01/18.
//

#ifndef EX1_TASK_H
#define EX1_TASK_H

class Task {
public:

    Task(void * (*func)(void *arg), void *arg) : func(func), arg(arg) {}
    void execute() {
        func(arg);
    }
    virtual ~Task() {}

private:

    void * (*func)(void *arg);
    void *arg;
};

#endif //EX1_TASK_H
