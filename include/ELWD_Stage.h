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

#ifndef ELEMENTO_ELWD_STAGE_H
#define ELEMENTO_ELWD_STAGE_H

#include <ELWD_Safe_Queue.h>

#include <tuple>
#include <thread>


// ELWD Pipeline stage structure.
// It introduces the virtual functions to be overridden by the user to make it useful.

template <class InputT, class OutputT, class ParamT>
struct ELWD_Stage{
  ParamT fParams;
  ELWD_Queue_I<InputT>* fInputQ;
  ELWD_Queue_I<OutputT>* fOutputQ;
  mutable bool fKeepRunning = true;
  size_t fNCalls = 0;

  ELWD_Stage(){
    fParams = ParamT();
    fInputQ = nullptr;
    fOutputQ = nullptr;
  }

  ELWD_Stage(ParamT params){
    fParams=std::move(params);
    fInputQ = nullptr;
    fOutputQ = nullptr;
  }

  ELWD_Stage(ParamT params, ELWD_Queue_I<InputT>* inputQ, ELWD_Queue_I<OutputT>* outputQ){
    fParams=std::move(params);
    fInputQ=std::move(inputQ);
    fOutputQ=std::move(outputQ);
  }

  ELWD_Stage(const ELWD_Stage& stage){
    fParams = stage.fParams;
    fInputQ = stage.fInputQ;
    fOutputQ = stage.fOutputQ;
  }

  void process(){
    while (fKeepRunning){
      handle_output(process_input(get_input()));
      fNCalls++;
    }
  }

  virtual InputT* get_input() = 0;
  virtual OutputT* process_input(InputT* input) = 0;
  virtual void handle_output(OutputT* output) = 0;
};

#endif //ELEMENTO_ELWD_STAGE_H
