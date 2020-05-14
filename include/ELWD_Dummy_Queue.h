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

#ifndef ELEMENTO_ELWD_DUMMY_QUEUE_H
#define ELEMENTO_ELWD_DUMMY_QUEUE_H

#include <ELWD_Queue_I.h>


// Dummy queue to work as placeholder for stages which have no input or output required.

typedef void* DummyT;

struct ELWD_Dummy_Queue : public ELWD_Queue_I<DummyT>{
  inline void append(DummyT const& data) final{};

  inline bool empty() const final { return true; };

  inline void poll() final {};

  inline DummyT pinch() final { return nullptr; };

  inline void notify() final {};

  inline size_t size() const final { return 0; }
};

#endif //ELEMENTO_ELWD_DUMMY_QUEUE_H
