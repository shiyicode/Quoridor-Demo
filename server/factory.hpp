//
// Created by shiyi on 2017/1/1.
//

#ifndef ASIOSERVER_FACTORY_H
#define ASIOSERVER_FACTORY_H

#include <map>
#include <string>
#include "action/action.h"
#include <iostream>

class factory
{
public:
    template <typename F>
    struct Register
    {
        Register(const std::string& key)
        {
            factory::get().m_map.emplace(key, []{
                return new F();
            });
        }

        template<typename... Args>
        Register(const std::string& key, Args... args)
        {
            factory::get().m_map.emplace(key, [&]{
                return new F(args...);
            });
        }
    };

    static action* produce(const std::string& key)
    {
        auto map = factory::get().m_map;
        if(map.find(key) == map.end())
        {
            throw std::invalid_argument("error");
        }
        return map[key]();
    }

private:
    factory() = default;
    factory(const factory&) = delete;
    factory(factory&&) = delete;

    static factory &get()
    {
        static factory instance;
        return instance;
    }

    std::map<std::string, std::function<action*(void)>> m_map;
};

#define REGISTER_ACTION_NAME(T) msg_name_##T##_
#define REGISTER_ACTION(T, key, ...) \
static factory::Register<T> REGISTER_ACTION_NAME(T)(key,##__VA_ARGS__)

#endif //ASIOSERVER_FACTORY_H
