#ifndef COMPONENT_H
#define COMPONENT_H

#include "pch.h"

namespace tj {

    class IComponent {

    public:
        explicit IComponent() = default;
        virtual ~IComponent()                         = default;
        // virtual void Start()                         = 0;
        // virtual void Update(float _deltaTime)        = 0;
        // virtual void Draw(sf::RenderTarget& _target) = 0;
        // virtual void Destroy()                       = 0;
    };

} // namespace tj

#endif // COMPONENT_H
