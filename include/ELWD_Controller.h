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

#ifndef ELEMENTO_ELWD_CONTROLLER_H
#define ELEMENTO_ELWD_CONTROLLER_H

#include "ELWD_Thread.h"
#include "ELWD_Clock_Generator.h"
#include "ELWD_Dummy_Queue.h"


// Generic controller stage which allows to execute a input-output less function with fixed clock.
// Useful for monitoring or slow controls.

struct  ELWD_Controller : public ELWD_Thread<DummyT,DummyT,DummyT>{
  ELWD_Clock_Generator fClockGen;
  ELWD_Dummy_Queue fSink;

  ELWD_Controller(size_t hertz):
  fClockGen(hertz),
  fSink(),
  ELWD_Thread(DummyT(), &fClockGen, &fSink)
  {}

  DummyT* get_input() final{
    fClockGen.poll_and_pinch();
    return nullptr;
  }

  DummyT* process_input(DummyT* /*input*/) final{
    return nullptr;
  };

  virtual void controller_logic() = 0;

  void handle_output(DummyT* /*output*/) final{
    controller_logic();
  };
};

#endif //ELEMENTO_ELWD_CONTROLLER_H
