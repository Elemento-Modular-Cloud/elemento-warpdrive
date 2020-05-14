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

#include <ELWD_Controller.h>
#include <ELWD_Pipeline.h>

struct testController : public ELWD_Controller{
  testController(size_t hertz):
  ELWD_Controller(hertz){}

  void controller_logic() final {
    printf("Call %zu\n", fNCalls);
  }

  void printStats() final{
    printf("---> Test controller called %zu times\n", this->fNCalls);
  }
};

int main(){
  auto controller  = testController(10);

  {
    ELWD_Pipeline pipeline;

    pipeline | controller;

    pipeline.start();
    std::this_thread::sleep_for(std::chrono::seconds(10));
    pipeline.stop();

    pipeline.printStats();
  }

  return 0;
}