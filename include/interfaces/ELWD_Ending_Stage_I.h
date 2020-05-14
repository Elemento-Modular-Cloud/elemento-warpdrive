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

#ifndef ELEMENTO_ELWD_ENDING_STAGE_I_H
#define ELEMENTO_ELWD_ENDING_STAGE_I_H

#include "ELWD_Thread.h"
#include <ELWD_Safe_Queue.h>
#include <ELWD_Dummy_Queue.h>

// This struct represents the ending point of a pipeline.
// It implements a stage which gets some data as an input and has no output.
// This is an interface class which can be reimplemented by the user to become usable.

template <class InputT, class ParamT, class ELWD_Input_Thread = ELWD_Thread<InputT,DummyT,ParamT>>
struct ELWD_Ending_Stage_I : public ELWD_Input_Thread{
  ELWD_Ending_Stage_I(ParamT params, ELWD_Queue_I<InputT>* inputQ):
  ELWD_Input_Thread(params, inputQ, new ELWD_Dummy_Queue()){}

  ELWD_Ending_Stage_I(ParamT params):
  ELWD_Input_Thread(params){}

  ELWD_Ending_Stage_I():
  ELWD_Input_Thread(){}

  ELWD_Ending_Stage_I(const ELWD_Ending_Stage_I& disp):
  ELWD_Input_Thread(disp){}

  void handle_output(DummyT* output) final{}
};

#endif //ELEMENTO_ELWD_ENDING_STAGE_I_H
