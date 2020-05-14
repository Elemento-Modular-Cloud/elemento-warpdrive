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
#include "ELWD_Starting_Stage_I.h"
#include "ELWD_Middle_Stage_I.h"
#include "ELWD_Ending_Stage_I.h"

#include <ELWD_Dummy_Queue.h>

// This is a super simple thread which keeps writing to the output queue the value passed to the ctor.
struct producer : public ELWD_Starting_Stage_I<int, int>{
    producer(int value, ELWD_Safe_Queue<int>* queue) : ELWD_Starting_Stage_I(value,queue){}

    int* process_input(DummyT* input) final{
      std::this_thread::sleep_for(std::chrono::microseconds(1000000/10));
      auto output = new int(fParams);
      std::cout << "prod: pushing " << *output << "\n";
      return output;
    }

    void handle_output(int* output) final{
      fOutputQ->append(*output);
    }
};

// This thread picks from the input queue and copies to the output queue, passing through values.
struct passthrough : public ELWD_Middle_Stage_I<int, int, int>{
    passthrough(ELWD_Safe_Queue<int>* inputQueue, ELWD_Safe_Queue<int>* outputQueue) :
    ELWD_Middle_Stage_I(0,inputQueue,outputQueue){}

    int* get_input() final{
      return new int(fInputQ->poll_and_pinch());
    }

    int* process_input(int* input) final{
      std::cout << "pass: passing through " << *input << "\n";
      return input;
    }

    void handle_output(int* output) final{
      fOutputQ->append(*output);
    }
};

// This thread picks from the input queue and does nothing but writing to the terminal!
struct consumer : public ELWD_Ending_Stage_I<int, int>{
    consumer(ELWD_Safe_Queue<int>* queue) : ELWD_Ending_Stage_I(0,queue){}

    int* get_input() final{
      return new int(fInputQ->poll_and_pinch());
    }

    DummyT* process_input(int* input) final{
      std::cout << "cons: got " << *input << "\n";
      return nullptr;
    }
};

// This is an example of pipeline allocation using the previously defined simple processes.
int main(){
  auto queue1 = new ELWD_Safe_Queue<int>();
  auto queue2 = new ELWD_Safe_Queue<int>();

  auto prod = producer(42, queue1);
  auto pass = passthrough(queue1, queue2);
  auto cons = consumer(queue2);

  {
    ELWD_Pipeline pipeline;

    pipeline | prod | pass | cons;

    pipeline.start();
    std::this_thread::sleep_for(std::chrono::seconds(10));
    pipeline.stop();

    pipeline.printStats();
  }

  return 0;
}