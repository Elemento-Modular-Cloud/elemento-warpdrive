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

#ifndef ELEMENTO_ELWD_STARTING_STAGE_I_H
#define ELEMENTO_ELWD_STARTING_STAGE_I_H

#include "ELWD_Thread.h"
#include <ELWD_Safe_Queue.h>
#include <ELWD_Dummy_Queue.h>


// This struct represents the starting point of a pipeline.
// It implements a stage which generates some data and appends that data to the output queue.
// This is an interface class which can be reimplemented by the user to become usable.

template <class OutputT, class ParamT, class ELWD_Output_Thread = ELWD_Thread<DummyT,OutputT,ParamT>>
struct ELWD_Starting_Stage_I : public ELWD_Output_Thread{
  ELWD_Starting_Stage_I(ParamT params, ELWD_Safe_Queue<OutputT>* outputQ):
  ELWD_Output_Thread(params, new ELWD_Dummy_Queue(), outputQ){}

  ELWD_Starting_Stage_I(ParamT params):
  ELWD_Output_Thread(params){}

  ELWD_Starting_Stage_I():
  ELWD_Output_Thread(){}
};

#endif //ELEMENTO_ELWD_STARTING_STAGE_I_H
