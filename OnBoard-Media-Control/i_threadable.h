#ifndef I_THREADABLE_H
#define I_THREADABLE_H
#pragma once
#include <thread>


class I_Threadable
{
public:
    I_Threadable() { }
    virtual ~I_Threadable() { }

    bool StartThread()
    {
        if (pthread_create(&thread_tracker, NULL, ThreadReference, this) == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void WaitForThreadToExit()
    {
        pthread_join(thread_tracker, NULL);
    }



protected:
    /** Anything inheriting this class must define this function */
    virtual void ThreadFunction() = 0;

private:
    static void * ThreadReference(void * thread_id)
    {
        ((I_Threadable *)thread_id)->ThreadFunction();
        return NULL;
    }

    pthread_t thread_tracker;
};

#endif // I_THREADABLE_H

