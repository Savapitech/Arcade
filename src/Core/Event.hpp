#pragma once

#include "Keys.hpp"

#include <stack>

class Event
{
    private:
        std::stack<core::Keys> keyStack;
        bool close = false;
    public:
        bool getCloseState(){return close;}
        void setCloseState(bool state){close = state;}
        std::stack<core::Keys> &getKeyStack(){return keyStack;}
        void addKey(core::Keys key){keyStack.push(key);}
};
