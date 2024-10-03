#ifndef MATHF_H
#define MATHF_H

#include "../pch.h"


namespace tj {

    class Mathf {
    public:
        Mathf(const Mathf&) = delete;


        template <typename T>
        static T numberBetween(T _min, T _max) {
            return _min + rand() % ((_max - _min) + 1);
        }

        template <typename T>
        static T dot(const sf::Vector2<T>& _v1, const sf::Vector2<T>& _v2) {
            return _v1.x * _v2.x + _v1.y * _v2.y;
        }

        template <typename T>
        static T magnitude(const sf::Vector2<T>& _v) {
            return std::sqrt(_v.x * _v.x + _v.y * _v.y);
        }

        template <typename T>
        static T normalize(const sf::Vector2<T>& _v) {
            float mag = magnitude(_v);
            if (mag > 0) {
                return sf::Vector2<T>(_v.x / mag, _v.y / mag);
            }
            return sf::Vector2<T>(0, 0);
        }

        static float distance(const sf::Vector2<float>& _v1, const sf::Vector2<float>& _v2) {
            return std::sqrt(std::pow(_v2.x - _v1.x, 2) + std::pow(_v2.y - _v1.y, 2));
        }

        static float angleBetween(const sf::Vector2i& _v1, const sf::Vector2i& _v2) {
            float dotProd = dot(_v1, _v2);
            float mag1    = magnitude(_v1);
            float mag2    = magnitude(_v2);
            return std::acos(dotProd / (mag1 * mag2));
        }


        template <typename T>
        static T clamp(T _value, T _min, T _max) {
            if (_value < _min) {
                return _min;
            }
            if (_value > _max) {
                return _max;
            }
            return _value;
        }

        static float lerp(float _a, float _b, float _t) {
            return _a + _t * (_b - _a);
        }

        template<typename T>
        static sf::Vector2<T> lerp(const sf::Vector2<T>& start, const sf::Vector2<T>& end, float t) {
            return start + t * (end - start);
        }

    private:
        Mathf();

        static unsigned int seed() {
            return static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());
        }
    };

} // namespace tj


#endif // MATHF_H
