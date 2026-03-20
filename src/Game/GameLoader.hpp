#pragma once
#include "IGame.hpp"
#include <memory>

class GameLoader 
{
    public:
        std::unique_ptr<IGame> gameLoader();
};