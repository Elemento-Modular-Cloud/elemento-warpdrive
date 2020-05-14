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
#include "ELWD_Starting_Stage_I.h"
#include "ELWD_Ending_Stage_I.h"

#include <ELWD_Dummy_Queue.h>

// This is a super simple producer
struct producer : public ELWD_Starting_Stage_I<int, int>{
  producer():ELWD_Starting_Stage_I(){};

  DummyT* get_input() final{
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "catch: getting no input\n";
    return nullptr;
  }

  int* process_input(DummyT* input) final{
    std::cout << "catch: returning 10\n";
    return new int(10);
  }

  void handle_output(int* output) final{
    std::cout << "catch: returned " << *output << "\n";
  }
};

// This is a super simple consumer
struct consumer : public ELWD_Middle_Stage_I<int, int, int>{
  consumer():ELWD_Middle_Stage_I(){};

  int* get_input() final{
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "enc: getting 11 as input\n";
    return new int(11);
  }

  int* process_input(int* input) final{
    std::cout << "enc: returning 11\n";
    return input;
  }

  void handle_output(int* output) final{
    std::cout << "enc: returned " << *output << "\n";
  }
};

// This is a super simple dispatcher
struct dispatcher : public ELWD_Ending_Stage_I<int, int>{
  dispatcher():ELWD_Ending_Stage_I(){};

  int* get_input() final{
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "dis: getting 12 as input\n";
    return new int(12);
  }

  DummyT* process_input(int* input) final{
    std::cout << "dis: returning " << *input << "\n";
    return nullptr;
  }

  void handle_output(DummyT* output) final{
    std::cout << "dis: returned " << output << "\n";
  }
};


// This is an example of pipeline allocation using the previously defined simple processes.
int main(){

  auto prod = producer();
  auto cons = consumer();
  auto dis = dispatcher();

  {
    ELWD_Pipeline pipeline;

    pipeline | prod | cons | dis;

//    pipeline.start();
    std::this_thread::sleep_for(std::chrono::seconds(1));
//    pipeline.stop();

    pipeline.printStats();
  }

  return 0;
}