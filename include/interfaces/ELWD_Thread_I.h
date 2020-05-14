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

#ifndef ELEMENTO_ELWD_THREAD_I_H
#define ELEMENTO_ELWD_THREAD_I_H

#include <ELWD_Thread_State.h>


// This is the common thread interface.
// Anything deriving from this interface can be attached to a pipeline.

struct ELWD_Thread_I{
  ELWD_Thread_State fState;
  bool fEmptyOnStop = true;

  virtual void start() = 0;
  virtual void stop() = 0;
  virtual void reset() = 0;

  virtual void printStats() = 0;
};

#endif //ELEMENTO_ELWD_THREAD_I_H
