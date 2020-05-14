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

#ifndef ELEMENTO_ELWD_THREAD_POOL_H
#define ELEMENTO_ELWD_THREAD_POOL_H

#include <ELWD_Pipeline.h>
#include <thread>


// Thread pool containing multiple threads created as clones of the reference one.
// Can be directly appended to a pipeline.

template <class ThreadT>
struct ELWD_Thread_Pool : public ELWD_Pipeline{
  ThreadT fThreadPrototype;
  std::vector<ThreadT> fThreadPool;

  ELWD_Thread_Pool(ThreadT threadPrototype, size_t nThreads) : fThreadPrototype(threadPrototype){
    auto maxConcurrency = std::thread::hardware_concurrency();

    if (nThreads > maxConcurrency){
      printf("Exceeding max hardware concurrency. Capping at %d", maxConcurrency);
      nThreads = maxConcurrency;
    }

    fThreadPool = std::vector<ThreadT>(nThreads, fThreadPrototype);

    for(auto& thread : fThreadPool){
      this->add_stage((ELWD_Thread_I*)&thread);
    }
  }
};

#endif //ELEMENTO_ELWD_THREAD_POOL_H
