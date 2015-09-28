#ifndef THREADCLASS_H
#define THREADCLASS_H
//#include <pthread.h>
//
#include <thread>

/** CREDIT: http://stackoverflow.com/a/1151615 **/

class MyThreadClass
{
public:
   MyThreadClass() {/* empty */}
   virtual ~MyThreadClass() {/* empty */}

   /** Returns true if the thread was successfully started, false if there was an error starting the thread */
   bool StartInternalThread()
   {
      return (pthread_create(&_thread, NULL, InternalThreadEntryFunc, this) == 0);
   }

   /** Will not return until the internal thread has exited. */
   void WaitForInternalThreadToExit()
   {
      (void) pthread_join(_thread, NULL);
   }

protected:
   /** Implement this method in your subclass with the code you want your thread to run. */
   virtual void InternalThreadEntry() = 0;

private:
   static void * InternalThreadEntryFunc(void * This) 
   {
       ((MyThreadClass *)This)->InternalThreadEntry();
       return NULL;
   }

   pthread_t _thread;
};

#endif
