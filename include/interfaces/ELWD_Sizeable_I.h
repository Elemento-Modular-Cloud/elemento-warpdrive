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

#ifndef ELEMENTO_ELWD_SIZEABLE_I_H
#define ELEMENTO_ELWD_SIZEABLE_I_H

#include <cstddef>


// This is a pure virtual struct to define every sizeable class.

struct ELWD_Sizeable{
  virtual size_t size() const = 0;
};

#endif //ELEMENTO_ELWD_SIZEABLE_I_H
