#ifndef ENGINE_H
#define ENGINE_H

#include "pch.h"

namespace tj {

    class TJ_API Engine {
    public:
        Engine(std::string_view _title, unsigned int _fps, bool _vsync = false);

    private:
        bool bVsync = false;
        sf::Uint8 _frameRate = 60;

        sf::RenderWindow window;
    };

} // namespace tj

#endif // ENGINE_H
