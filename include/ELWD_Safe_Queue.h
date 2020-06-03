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

#ifndef ELEMENTO_ELWD_SAFE_QUEUE_H
#define ELEMENTO_ELWD_SAFE_QUEUE_H

#include <ELWD_Queue_I.h>

#include <queue>
#include <mutex>
#include <condition_variable>

// Thread safe FIFO Implementation with sleep-less polling and wait semantics.

template <class contentT>
class ELWD_Safe_Queue : public ELWD_Queue_I<contentT>{
private:
  std::queue<contentT> fQueue;
  mutable std::mutex fMutex;
  std::condition_variable fCondVar;

public:
  void notify() final{
    fCondVar.notify_one();
  }

  void append(contentT const& data) final{
    std::unique_lock lock(fMutex);
    fQueue.push(data);
    lock.unlock();
    fCondVar.notify_one();
  }

  bool empty() const final{
    std::scoped_lock lock(fMutex);
    return fQueue.empty();
  }

  void poll() final{
    std::unique_lock lock(fMutex);
    while(fQueue.empty())
    {
      fCondVar.wait(lock);
    }
  }

  contentT pinch() final{
    std::scoped_lock lock(fMutex);
    contentT val = std::move(fQueue.front());
    fQueue.pop();
    return std::move(val);
  }

  size_t size() const final{
    return fQueue.size();
  }
};


#endif //ELEMENTO_ELWD_SAFE_QUEUE_H
