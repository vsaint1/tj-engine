#ifndef RANDOM_H
#define RANDOM_H

#include "../pch.h"

namespace tj {


    class Random {

    public:
        Random(const Random&)            = delete;
        Random& operator=(const Random&) = delete;

        template <typename T>

        static T range(T _min, T _max) {
            return _min + rand() % ((_max - _min) + 1);
        }

        static unsigned int seed() {
            return static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());
        }

    private:
        Random();
    };

} // namespace tj

#endif // RANDOM_H
