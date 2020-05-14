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
#include "ELWD_Thread_Pool.h"

#include <ELWD_Safe_Queue.h>

// This is a super simple catcher
struct producer : public ELWD_Starting_Stage_I<int, int>{
  producer(ELWD_Safe_Queue<int>* queue) : ELWD_Starting_Stage_I(0,queue){}

  DummyT* get_input() final{
//    std::cout << "catch: getting no input\n";
    return nullptr;
  }

  int* process_input(DummyT* input) final{
    std::this_thread::sleep_for(std::chrono::microseconds(1000000/10));
    auto output = new int(rand() % 100);
    std::cout << "catch: returning " << *output << "\n";
    return output;
  }

  void handle_output(int* output) final{
//    std::cout << "catch: returned " << *output << "\n";
    fOutputQ->append(*output);
//    fOutputQ->append(*output-100);
  }
};

// This is a super simple encoder
struct consumer : public ELWD_Ending_Stage_I<int, int>{
  size_t fID;

  consumer(size_t id, ELWD_Safe_Queue<int>* queue) : ELWD_Ending_Stage_I(0,queue),fID(id){}

  consumer(const consumer& cons) : ELWD_Ending_Stage_I<int, int>(cons){}

  int* get_input() final{
//    std::cout << "enc: getting input: " << *input << "\n";
    return new int(fInputQ->poll_and_pinch());
  }

  DummyT* process_input(int* input) final{
    sleep(fID);
    std::cout << "enc" << fID << ": value = " << *input << " square = " << (*input)*(*input) << "\n";
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
  auto consumers = ELWD_Thread_Pool(consumer(1, queue), 2);
  consumers.fThreadPool[0].fID = 1;
  consumers.fThreadPool[1].fID = 2;

  {
    ELWD_Pipeline pipeline;

    pipeline | prod | consumers;

    pipeline.start();
    for (int j = 0; j < 4; ++j) {
      std::this_thread::sleep_for(std::chrono::seconds(1));
      std::cout << queue->size() << std::endl;
    }

    pipeline.stop();

    std::cout << "Final queue size: " << queue->size() << std::endl;

    pipeline.printStats();
  }

  return 0;
}