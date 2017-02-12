//
//  message.cpp
//  AsioServer
//
//  Created by shiyi on 2016/12/27.
//  Copyright © 2016年 shiyi. All rights reserved.
//

#include "message.h"

void message::init(std::string data)
{
    char* body = this->body();
    std::strncpy(body, data.c_str(), strlen(data.c_str()));
    
    this->body_length(strlen(this->body()));
    this->encode_header();
    
}

message::message()
: m_body_length(0)
{
}

char* message::data()
{
    return m_data;
}

char* message::body()
{
    return m_data + HEADER_LENGTH;
}

void message::body_length(size_t body_length)
{
    m_body_length = body_length;
    if(m_body_length > MAX_BODY_LENGTH)
        m_body_length = MAX_BODY_LENGTH;
}

size_t message::body_length()
{
    return m_body_length;
}

size_t message::length()
{
    return HEADER_LENGTH + m_body_length;
}

bool message::decode_header()
{
    char head[HEADER_LENGTH + 1] = "";
    std::strncpy(head, m_data, HEADER_LENGTH);
    m_body_length = std::atoi(head);
    if(m_body_length > MAX_BODY_LENGTH)
    {
        m_body_length = 0;
        return false;
    }
    return true;
}

void message::encode_header()
{
    char head[HEADER_LENGTH + 1] = "";
    std::sprintf(head, "%4d", m_body_length);
    std::strncpy(m_data, head, HEADER_LENGTH);
}
