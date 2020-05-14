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

#include <iostream>
#include "ELWD_Pipeline.h"
#include "ELWD_Middle_Stage_I.h"

// This is a super simple stage which keeps writing on the terminal the value passed to the ctor.
// The passed value is stored in the form of the "param" internal state of a ELWD_Stage.
struct stupidStage : public ELWD_Middle_Stage_I<int, int, int>{

  stupidStage(int value):ELWD_Middle_Stage_I(value){
  };

  int* get_input() final{
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "catch: getting no input\n";
    return nullptr;
  }

  int* process_input(int* input) final{
    std::cout << "catch: returning " << this->fParams << "\n";
    return &this->fParams;
  }

  void handle_output(int* output) final{
    std::cout << "catch: returned " << *output << "\n";
  }
};

// This is an example of pipeline allocation using the previously defined simple processes.
int main(){

  auto stage1 = stupidStage(10);
  auto stage2 = stupidStage(11);
  auto stage3 = stupidStage(12);

  {
    ELWD_Pipeline pipeline;

    pipeline | stage1 | stage2 | stage3;

    pipeline.start();
    std::this_thread::sleep_for(std::chrono::seconds(10));
    pipeline.stop();

    pipeline.printStats();
  }

  return 0;
}