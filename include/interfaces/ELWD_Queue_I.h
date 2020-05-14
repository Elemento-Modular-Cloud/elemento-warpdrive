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

#ifndef ELEMENTO_ELWD_QUEUE_I_H
#define ELEMENTO_ELWD_QUEUE_I_H

#include "ELWD_Sizeable_I.h"


// Interface defining the methods necessary for anything usable as input and output stack by threads

template <class contentT>
struct ELWD_Queue_I : ELWD_Sizeable{
  virtual void append(contentT const& data) = 0;

  virtual bool empty() const = 0;

  virtual void poll() = 0;

  virtual contentT pinch() = 0;

  contentT poll_and_pinch(){
    poll();
    return std::move(pinch());
  }

  virtual void notify() = 0;
};



#endif //ELEMENTO_ELWD_QUEUE_I_H
