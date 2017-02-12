//
//  sync_queue.h
//  AsioServer
//
//  Created by shiyi on 2016/12/29.
//  Copyright © 2016年 shiyi. All rights reserved.
//

#ifndef sync_queue_H
#define sync_queue_H

#include <stdio.h>
#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <forward_list>
#include "message.h"

class sync_queue
{
public:
    sync_queue(std::size_t max_size);
    
    ~sync_queue();
    
    bool push(message& x);
    
    bool push(message&& x);

    void pop();
    
    message& front();
    
    void stop();
    
    bool empty();
    
private:
    bool add(message&& x);
    
    bool full();
    
    std::size_t m_max_size;
    bool m_isStop;
    std::mutex m_mutex;
    std::condition_variable m_notFull;
    std::queue<message> m_queue;
};


#endif /* sync_queue_H */
