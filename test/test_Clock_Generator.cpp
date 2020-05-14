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

#include <ELWD_Clock_Generator.h>
#include <ELWD_Ending_Stage_I.h>
#include <ELWD_Pipeline.h>

#include <iostream>

// This is a super simple dispatcher
struct counter : public ELWD_Ending_Stage_I<DummyT, int>{
  counter(ELWD_Clock_Generator* clock):ELWD_Ending_Stage_I(0, clock){};

  DummyT* get_input() final{
    fInputQ->poll_and_pinch();
    return nullptr;
  }

  DummyT* process_input(DummyT* input) final{
    std::cout << "tik tok..." << "\n";
    return nullptr;
  }
};

int main(){
  auto clock = new ELWD_Clock_Generator(1);

  auto count  = counter(clock);

  {
    ELWD_Pipeline pipeline;

    pipeline | count;

    pipeline.start();
    std::this_thread::sleep_for(std::chrono::seconds(10));
    pipeline.stop();

    pipeline.printStats();
  }

  return 0;
}