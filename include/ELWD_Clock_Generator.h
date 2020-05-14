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

#ifndef ELEMENTO_ELWD_CLOCK_GENERATOR_H
#define ELEMENTO_ELWD_CLOCK_GENERATOR_H

#include <ELWD_Queue_I.h>
#include <chrono>
#include <thread>

typedef void* DummyT;


// ELWD Clock generator which satisfies queue interface.
// Clock generation is handled via timed polling.
// It can be used as input queue to clock the underlying computing.

struct ELWD_Clock_Generator : public ELWD_Queue_I<DummyT>{
  size_t fHertz;
  std::chrono::microseconds fPeriod;

  ELWD_Clock_Generator(size_t hertz):fHertz(hertz){
    if(fHertz!=0){
      fPeriod = std::chrono::microseconds(1000000/fHertz);
    } else {
      fPeriod = std::chrono::seconds(1);
    }
  }

  inline void append(DummyT const& data) final{}

  inline bool empty() const final { return true; }

  inline void poll() final { std::this_thread::sleep_for(fPeriod); }

  inline DummyT pinch() final { return nullptr; }

  inline void notify() final {}

  inline size_t size() const final { return 0; }
};

#endif //ELEMENTO_ELWD_CLOCK_GENERATOR_H
