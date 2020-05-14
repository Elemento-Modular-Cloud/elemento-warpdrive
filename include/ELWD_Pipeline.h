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

#ifndef ELEMENTO_ELWD_PIPELINE_H
#define ELEMENTO_ELWD_PIPELINE_H

#include "ELWD_Thread_I.h"
#include "ELWD_Thread.h"

#include <vector>


// Pipeline implementation as a vector of ELWD_Thread_I.
// Since a pipeline is in turn derived from ELWD_Thread_I, it can be attached to an existing pipeline.

struct ELWD_Pipeline : public ELWD_Thread_I{
  std::vector<ELWD_Thread_I*> fThreads;
  size_t fNcalls = 0;

  ELWD_Pipeline* add_stage(ELWD_Thread_I *thread){
    fThreads.emplace_back(thread);
    return this;
  }

  void printStats(){
    size_t i = 0;
    printf("Pipeline started %zu times\n",fNcalls);
    for(auto const & thread : fThreads){
      thread->printStats();
    }
  }

  void start() final{
    for(auto &thread : fThreads) thread->start();
    fNcalls++;
    fState = ELWD_Thread_State::kRunning;
  }

  void stop() final{
    for(auto &thread : fThreads) thread->stop();
    fState = ELWD_Thread_State::kStopped;
  }

  void reset() final{
    stop();
    start();
  }

  bool allRunning(){
    for(auto const& thread : fThreads){
      if(thread->fState == ELWD_Thread_State::kStopped) return false;
    }
    return true;
  }

  size_t countThreads(ELWD_Thread_State state){
    size_t count = 0;
    for(auto const& thread : fThreads){
      if(thread->fState == state) count++;
    }
    return count;
  }

  size_t runningThreads(){
    return countThreads(ELWD_Thread_State::kRunning);
  }

  size_t stoppedThreads(){
    return countThreads(ELWD_Thread_State::kStopped);
  }
};

static ELWD_Pipeline& operator|(ELWD_Pipeline& ppl, const ELWD_Thread_I* thread){
  ppl.add_stage((ELWD_Thread_I*)(thread));
  return ppl;
}

static ELWD_Pipeline& operator|(ELWD_Pipeline& ppl, ELWD_Thread_I& thread){
  ppl.add_stage(&thread);
  return ppl;
}

#endif //ELEMENTO_ELWD_PIPELINE_H
