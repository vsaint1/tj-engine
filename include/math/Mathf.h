#ifndef MATHF_H
#define MATHF_H

#include "../pch.h"


namespace tj {

    class Mathf {
    public:
        Mathf(const Mathf&) = delete;
        
        template <typename T>
        static T Dot(const sf::Vector2<T>& _v1, const sf::Vector2<T>& _v2) {
            return _v1.x * _v2.x + _v1.y * _v2.y;
        }

        template <typename T>
        static T Magnitude(const sf::Vector2<T>& _v) {
            return std::sqrt(_v.x * _v.x + _v.y * _v.y);
        }

        template <typename T>
        static sf::Vector2<T> Normalized(const sf::Vector2<T>& _v) {
            float mag = Magnitude(_v);
            if (mag > 0) {
                return sf::Vector2<T>(_v.x / mag, _v.y / mag);
            }
            return sf::Vector2<T>(0, 0);
        }

        static float Distance(const sf::Vector2<float>& _v1, const sf::Vector2<float>& _v2) {
            return std::sqrt(std::pow(_v2.x - _v1.x, 2) + std::pow(_v2.y - _v1.y, 2));
        }

        static float AngleBetween(const sf::Vector2i& _v1, const sf::Vector2i& _v2) {
            float dotProd = Dot(_v1, _v2);
            float mag1    = Magnitude(_v1);
            float mag2    = Magnitude(_v2);
            return std::acos(dotProd / (mag1 * mag2));
        }


        template <typename T>
        static T Clamp(T _value, T _min, T _max) {
            if (_value < _min) {
                return _min;
            }
            if (_value > _max) {
                return _max;
            }
            return _value;
        }

        static float Lerp(float _a, float _b, float _t) {
            return _a + _t * (_b - _a);
        }

        template<typename T>
        static sf::Vector2<T> Lerp(const sf::Vector2<T>& start, const sf::Vector2<T>& end, float t) {
            return start + t * (end - start);
        }

    private:
        Mathf();

       
    };

} // namespace tj


#endif // MATHF_H
