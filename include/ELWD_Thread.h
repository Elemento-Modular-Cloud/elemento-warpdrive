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

#ifndef ELEMENTO_ELWD_THREAD_H
#define ELEMENTO_ELWD_THREAD_H

#include "ELWD_Thread_I.h"
#include "ELWD_Stage.h"

#include <thread>


// ELWD Thread implementation wrapping an std::thread.
// It adheres to ELWD_Thread_I interface.

template <class InputT, class OutputT, class ParamT>
struct ELWD_Thread : public ELWD_Thread_I, public ELWD_Stage<InputT,OutputT,ParamT>{
  std::thread fThread;

  ELWD_Thread():
  ELWD_Stage<InputT,OutputT,ParamT>(){
    fState = kStopped;
  }

  ELWD_Thread(ParamT params):
  ELWD_Stage<InputT,OutputT,ParamT>(params){
    fState = kStopped;
  }

  ELWD_Thread(const ELWD_Thread& thread):
  ELWD_Stage<InputT,OutputT,ParamT>(thread){
    fEmptyOnStop = true;
    fState = kStopped;
  }

  ELWD_Thread(ParamT params, ELWD_Queue_I<InputT>* inputQ, ELWD_Queue_I<OutputT>* outputQ):
  ELWD_Stage<InputT,OutputT,ParamT>(params, inputQ, outputQ){
    fState = kStopped;
  }

  ~ELWD_Thread(){
    this->stop();
    fState = kStopped;
    if (fThread.joinable())
      fThread.join();
    fThread.std::thread::~thread();
  }

  void start() final{
    this->fKeepRunning = true;
    fThread = std::thread([&] { this->process(); });
    fThread.detach();
    fState = kRunning;
  }

  void stop() override {
    if(fEmptyOnStop) {
      if (this->fInputQ) {
        while (!this->fInputQ->empty()) {
          std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
      }
    }
    this->fKeepRunning = false;
    fState = kStopped;
  }

  void reset() final{
    this->stop();
    this->start();
  }

  void printStats() override{
    printf("---> Thread called %zu times\n", this->fNCalls);
  }
};

#endif //ELEMENTO_ELWD_THREAD_H
