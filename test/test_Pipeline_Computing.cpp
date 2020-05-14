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
#include <deque>

#include "ELWD_Pipeline.h"
#include "ELWD_Starting_Stage_I.h"
#include "ELWD_Starting_Stage_I.h"
#include "ELWD_Ending_Stage_I.h"

#include <ELWD_Safe_Queue.h>

// This is a super simple catcher
struct producer : public ELWD_Starting_Stage_I<int, int>{
  producer(ELWD_Safe_Queue<int>* queue) : ELWD_Starting_Stage_I(0,queue){}

  DummyT* get_input() final{
//    std::cout << "catch: getting no input\n";
    return nullptr;
  }

  int* process_input(DummyT* input) final{
    std::this_thread::sleep_for(std::chrono::microseconds(1000000/60));
    auto output = new int(rand() % 100);
    std::cout << "catch: returning " << *output << "\n";
    return output;
  }

  void handle_output(int* output) final{
//    std::cout << "catch: returned " << *output << "\n";
    fOutputQ->append(*output);
    fOutputQ->append(*output-100);
  }
};

// This is a super simple encoder
struct consumer : public ELWD_Ending_Stage_I<int, int>{
  consumer(ELWD_Safe_Queue<int>* queue) : ELWD_Ending_Stage_I(0,queue){}

  int* get_input() final{
    auto input = new int(fInputQ->poll_and_pinch());
//    std::cout << "enc: getting input: " << *input << "\n";
    return input;
  }

  DummyT* process_input(int* input) final{
    std::cout << "enc: value = " << *input << " square = " << (*input)*(*input) << "\n";
    return nullptr;
  }

  void handle_output(DummyT* output) final{
//    std::cout << "enc: done\n";
  }
};

// This is an example of pipeline allocation using the previously defined simple processes.
int main(){

  auto queue = new ELWD_Safe_Queue<int>();

  auto prod = producer(queue);
  auto cons = consumer(queue);

  {
    ELWD_Pipeline pipeline;

    pipeline | prod | cons;

    pipeline.start();
    std::this_thread::sleep_for(std::chrono::seconds(10));
    pipeline.stop();

    pipeline.printStats();
  }

  return 0;
}