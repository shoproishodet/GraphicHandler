#include <Color/RGB.h>


using namespace L_RT::Color;

RGB::RGB() : mRGBA(0) {}

RGB::RGB(uint32_t red, uint32_t green, uint32_t blue, uint32_t alpha) {
    uint8_t componentLimit = std::numeric_limits<uint8_t>::max();

    if (red > componentLimit || green > componentLimit || blue > componentLimit || alpha > componentLimit) {
        throw std::invalid_argument("Color component limit overflow!");
    }

    mRGBA = 0;
    mRGBA |= (red << RED_COMPONENT_OFFSET);
    mRGBA |= (green << GREEN_COMPONENT_OFFSET);
    mRGBA |= (blue << BLUE_COMPONENT_OFFSET);
    mRGBA |= (alpha << ALPHA_COMPONENT_OFFSET);
}

RGB::RGB(System::ErrorCode &ec, uint32_t red, uint32_t green, uint32_t blue, uint32_t alpha) noexcept {
    ec = System::NO_ERRORS;

    uint8_t componentLimit = std::numeric_limits<uint8_t>::max();

    if (red > componentLimit || green > componentLimit || blue > componentLimit || alpha > componentLimit) {
        ec = System::INCORRECT_COLOR_COMPONENT_VALUE;
    }

    mRGBA = 0;
    mRGBA |= (red << RED_COMPONENT_OFFSET);
    mRGBA |= (green << GREEN_COMPONENT_OFFSET);
    mRGBA |= (blue << BLUE_COMPONENT_OFFSET);
    mRGBA |= (alpha << ALPHA_COMPONENT_OFFSET);
}

RGB::ByteReference L_RT::Color::RGB::R() noexcept {
    return {&mRGBA, RED_COMPONENT_OFFSET};
}

RGB::ByteReference L_RT::Color::RGB::G() noexcept {
    return {&mRGBA, GREEN_COMPONENT_OFFSET};
}

RGB::ByteReference L_RT::Color::RGB::B() noexcept {
    return {&mRGBA, BLUE_COMPONENT_OFFSET};
}

RGB::ByteReference L_RT::Color::RGB::A() noexcept {
    return {&mRGBA, ALPHA_COMPONENT_OFFSET};
}

uint32_t RGB::Data() const noexcept {
    return mRGBA;
}

// ByteReference_t things

RGB::ByteReference_t::ByteReference_t(uint32_t *dP, uint32_t o) noexcept : dataPointer(dP), offset(o) {}

RGB::ByteReference_t& RGB::ByteReference_t::operator=(uint32_t value) {
    uint8_t componentLimit = std::numeric_limits<uint8_t>::max();

    if (value > componentLimit)
        throw std::invalid_argument("Color component limit overflow!");

    *dataPointer = (*dataPointer & (~(L_RT_FULL_BYTE << offset)) | (value << offset));
    return *this;
}

RGB::ByteReference_t::operator uint8_t() noexcept {
    return static_cast<uint8_t>(*dataPointer >> offset);
}


