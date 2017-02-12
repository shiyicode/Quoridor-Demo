//
//  message.h
//  AsioServer
//
//  Created by shiyi on 2016/12/27.
//  Copyright © 2016年 shiyi. All rights reserved.
//

#ifndef message_H
#define message_H

#include <stdio.h>
#include <iostream>
#include <string>

class message
{
public:
    
    void init(std::string data);
    
    //包头长度
    static const int HEADER_LENGTH = 4;
    //包体最大长度
    static const int MAX_BODY_LENGTH = 1024;
    
    message();
    
    char* data();
    
    char* body();
    
    void body_length(size_t body_length);
    
    size_t body_length();
    
    size_t length();
    
    //将header内容转化为包体长度
    bool decode_header();
    
    //将包体长度转化为header内容
    void encode_header();
    
private:
    char m_data[HEADER_LENGTH + MAX_BODY_LENGTH];
    size_t m_body_length;
};

#endif /* message_H */
