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

#ifndef ELEMENTO_ELWD_MIDDLE_STAGE_I_H
#define ELEMENTO_ELWD_MIDDLE_STAGE_I_H

#include "ELWD_Thread.h"


// This struct represents an inner stage of a pipeline.
// It implements a stage which gets some input data, executes some computing and appends that data to the output queue.
// This is an interface class which can be reimplemented by the user to become usable.

template <class InputT, class OutputT, class ParamT, class ELWD_Input_Output_Thread = ELWD_Thread<InputT,OutputT,ParamT>>
struct ELWD_Middle_Stage_I : public ELWD_Input_Output_Thread{
  ELWD_Middle_Stage_I(ParamT params, ELWD_Safe_Queue<InputT>* inputQ, ELWD_Safe_Queue<OutputT>* outputQ):
  ELWD_Input_Output_Thread(params, inputQ, outputQ){}

  ELWD_Middle_Stage_I(ParamT params):
  ELWD_Input_Output_Thread(params){}

  ELWD_Middle_Stage_I():
  ELWD_Input_Output_Thread(){}
};

#endif //ELEMENTO_ELWD_MIDDLE_STAGE_I_H
