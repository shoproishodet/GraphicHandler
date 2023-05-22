#ifndef RAYTRACER_CANVAS_HPP
#define RAYTRACER_CANVAS_HPP

#include <Color/Interface/IColor.h>
#include <System/System.h>

#include <type_traits>
#include <memory>
#include <concepts>
#include <iostream>


namespace L_RT {

class Size {
public:
    uint32_t mWidth;
    uint32_t mHeight;
};

template<class ColorModel_t>
concept ColorModel_c = std::is_base_of_v<IColor, ColorModel_t> && !std::is_reference_v<ColorModel_t> && !std::is_pointer_v<ColorModel_t>;

template<ColorModel_c ColorModel_t, class Allocator_t = std::allocator<ColorModel_t>>
class Canvas {
private:
    Allocator_t mAllocator;
    ColorModel_t *mMat;

    uint32_t mWidth;
    uint32_t mHeight;

    using AllocatorTraits = std::allocator_traits<Allocator_t>;
public:
    Canvas() = delete;
    Canvas(uint32_t x, uint32_t y);
    Canvas(Canvas &&other) noexcept;
    Canvas(const Canvas &other);
    ~Canvas();

    void PutPixel(uint32_t x, uint32_t y, ColorModel_t colorValue) noexcept;
    ColorModel_t& GetPixel(uint32_t height, uint32_t y) const noexcept;
    Size GetSize() const;
};

template<ColorModel_c ColorModel_t, class Allocator_t>
Size Canvas<ColorModel_t, Allocator_t>::GetSize() const {
    return {mWidth, mHeight};
}

template<ColorModel_c ColorModel_t, class Allocator_t>
Canvas<ColorModel_t, Allocator_t>::Canvas(const Canvas &other) : mWidth(other.mWidth), mHeight(other.mHeight) {
    mAllocator = AllocatorTraits::select_on_container_copy_construction(other.mAllocator);
    mMat = AllocatorTraits::allocate(mAllocator, mWidth * mHeight);

    for (size_t i = 0; i < mWidth * mHeight; ++i)
        AllocatorTraits::construct(mAllocator, mMat + i, other.mMat[i]);
}

template<ColorModel_c ColorModel_t, class Allocator_t>
Canvas<ColorModel_t, Allocator_t>::Canvas(Canvas &&other) noexcept {
    /// change in future, UB may occurred

    mMat = other.mMat;
    mWidth = other.mWidth;
    mHeight = other.mHeight;
    mAllocator = std::move(other.mAllocator);

    other.mMat = nullptr;
    other.mWidth = 0;
    other.mHeight = 0;
}

template<ColorModel_c ColorModel_t, class Allocator_t>
Canvas<ColorModel_t, Allocator_t>::~Canvas() {
    for (size_t i = 0; i < mWidth * mHeight; ++i)
        AllocatorTraits::destroy(mAllocator, mMat + i);

    AllocatorTraits::deallocate(mAllocator, mMat, mWidth * mHeight);
}

template<ColorModel_c ColorModel_t, class Allocator_t>
Canvas<ColorModel_t, Allocator_t>::Canvas(uint32_t x, uint32_t y) try : mWidth(x), mHeight(y) {
    mMat = AllocatorTraits::allocate(mAllocator, mWidth * mHeight);

    for (size_t i = 0; i < mWidth * mHeight; ++i)
        AllocatorTraits::construct(mAllocator, mMat + i);
} catch (std::exception &e) {
    std::cerr << "Error occurred in canvas constructor, cause: " << e.what() << "\n";
    throw e;
}


template<ColorModel_c ColorModel_t, class Allocator_t>
ColorModel_t& Canvas<ColorModel_t, Allocator_t>::GetPixel(uint32_t x, uint32_t y) const noexcept {
    return *(mMat + y * mWidth + x);
}

template<ColorModel_c ColorModel_t, class Allocator_t>
void Canvas<ColorModel_t, Allocator_t>::PutPixel(uint32_t x, uint32_t y, ColorModel_t colorValue) noexcept {
    *(mMat + y * mWidth + x) = colorValue;
}

}
#endif //RAYTRACER_CANVAS_HPP
