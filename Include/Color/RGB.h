#ifndef RAYTRACER_RGB_H
#define RAYTRACER_RGB_H

/// \RGB
/// This class implemented RGB color model.\n
/// Default constructor set color as black.\n
/// Be careful, this class have 0 safety, you need to control all that contains

#include "Color/Interface/IColor.h"

#include <System/ErrorCode.h>
#include <System/System.h>

#include <cstdint>
#include <limits>
#include <stdexcept>


namespace L_RT::Color {

class RGB final : public IColor {
private:
    uint32_t mRGBA;

    typedef enum BitOffset_t {
        RED_COMPONENT_OFFSET    = 0x00,
        GREEN_COMPONENT_OFFSET  = 0x8,
        BLUE_COMPONENT_OFFSET   = 0x10,
        ALPHA_COMPONENT_OFFSET  = 0x18
    } BitOffset;

    typedef class ByteReference_t {
    private:
        uint32_t *dataPointer;
        uint32_t offset;
    public:
        ByteReference_t(uint32_t *dP, uint32_t o) noexcept;
        ByteReference_t& operator=(uint32_t value);
        operator uint8_t() noexcept;
    } ByteReference;

public:
    RGB(uint32_t red, uint32_t green, uint32_t blue, uint32_t alpha = 0);
    RGB(System::ErrorCode &ec, uint32_t red, uint32_t green, uint32_t blue, uint32_t alpha = 0) noexcept;
    RGB();

    ~RGB() final = default;

    ByteReference R() noexcept;
    ByteReference G() noexcept;
    ByteReference B() noexcept;
    ByteReference A() noexcept;

    uint32_t Data() const noexcept final;
};

}
#endif //RAYTRACER_RGB_H
