/*******************************************************
* This file is part of Elemento Warpdrive.
*
* This is a project by (the owners):
* Gabriele Gaetano Fronzé <gfronze_at_elemento.cloud>
* and
* Filippo Valle <fvalle_at_elemento.cloud>
*
* Created by Gabriele Gaetano Fronzé on 2018-12-01.
*
*******************************************************/

#ifndef ELEMENTO_ELWD_LOAD_BALANCED_THREAD_POOL_H
#define ELEMENTO_ELWD_LOAD_BALANCED_THREAD_POOL_H

#include "ELWD_Thread_Pool.h"
#include "ELWD_Thread.h"
#include "ELWD_Controller.h"
#include <thread>


// Load balancer stage built as ELWD_Controller.
// Based on the status of a queue (e.g. size) it is able to stop and restart a ELWD pipeline's threads.
// If the backpressure increases the stopped threads will be started.
// If the queue is empty, the running threads will be stopped to balance the load.

struct Load_Balancer : public ELWD_Controller{
  ELWD_Sizeable* fQueue;
  ELWD_Pipeline* fPipeline;

  Load_Balancer(size_t hertz, ELWD_Sizeable* queue, ELWD_Pipeline* pipeline):
  fQueue(queue),
  fPipeline(pipeline),
  ELWD_Controller(hertz){}

  void controller_logic() final {
    std::cout << "### HERE COMES THE LOAD BALANCER ###\n";
    std::cout << "Queue size " << fQueue->size() << std::endl;
    std::cout << "Threads number " << fPipeline->fThreads.size() << std::endl;
    std::cout << "Running threads " << fPipeline->runningThreads() << std::endl;
    std::cout << "Stopped threads " << fPipeline->stoppedThreads() << std::endl;

    if (fQueue->size() >= fPipeline->countThreads(ELWD_Thread_State::kRunning)){
      if (not fPipeline->allRunning()){
        for(auto const& thread : fPipeline->fThreads){
          if(thread->fState == ELWD_Thread_State::kStopped){
            std::cout << "starting thread\n";
            thread->start();
            break;
          }
        }
      }
    } else {
      for(auto& thread : fPipeline->fThreads){
        if(thread->fState == ELWD_Thread_State::kRunning) {
          std::cout << "stopping thread\n";
          thread->fEmptyOnStop = false;
          thread->stop();
          thread->fEmptyOnStop = true;
          break;
        }
      }
    }
    std::cout << "### HERE GOES THE LOAD BALANCER ###\n";
  }

  void printStats() final{
    printf("---> Load balancer called %zu times\n", this->fNCalls);
  }
};


// Automatically load balanced thread pool built as a combination of a standard ELWD ThreadPool and a Load Balancer.
// It automatically creates the maxmimum system concurrency number of clones of the base thread.
// The Load Balancer operates automatic starting and stopping of the Thread Pool threads.

template <class ThreadT, typename ThreadPoolT = ELWD_Thread_Pool<ThreadT>>
struct ELWD_Load_Balanced_Thread_Pool : public ELWD_Thread_I{
  Load_Balancer fLoadBalancer;
  ThreadPoolT fPipeline;
  size_t fNcalls = 0;

  ELWD_Load_Balanced_Thread_Pool(ThreadT threadPrototype,
                                size_t controllerClock):
  fPipeline(threadPrototype, std::thread::hardware_concurrency()),
  fLoadBalancer(controllerClock,threadPrototype.fInputQ,&fPipeline){}

  void printStats(){
    size_t i = 0;
    printf("Load balancing pipeline started %zu times\n",fNcalls);
    fLoadBalancer.printStats();
    fPipeline.printStats();
  }

  void start() final{
    fPipeline.start();
    fLoadBalancer.start();
    fState = ELWD_Thread_State::kRunning;
    fNcalls++;
  }

  void stop() final{
    fLoadBalancer.stop();
    fPipeline.stop();
    fState = ELWD_Thread_State::kStopped;
  }

  void reset() final{
    stop();
    start();
  }
};

#endif //ELEMENTO_ELWD_LOAD_BALANCED_THREAD_POOL_H
