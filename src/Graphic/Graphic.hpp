#pragma once

#include <vector>

#include "Entity.hpp"

namespace arcade 
{
    class IGraphic 
    {
        public:
            virtual void openWindow() = 0;
            virtual void closeWindow() = 0;
            virtual bool isOpen() = 0;

            virtual void initWindow(const std::vector<game::Entity> &) = 0;
            virtual void drawEntities(const std::vector<game::Entity> &) = 0;
    };
}