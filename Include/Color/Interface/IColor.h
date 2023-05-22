#ifndef RAYTRACER_ICOLOR_H
#define RAYTRACER_ICOLOR_H

#include <cstdint>

class IColor {
public:
    virtual ~IColor() = default;
    virtual uint32_t Data() const noexcept = 0;
};

#endif //RAYTRACER_ICOLOR_H
