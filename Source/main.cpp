#include <iostream>

#include <Color/RGB.h>
#include <Canvas.hpp>

#include <Math/Algorithms.hpp>

void RGBTest() {
    L_RT::Color::RGB rgbModel(255,143,11,0);
    std::cout << static_cast<int>(rgbModel.R()) << " " << static_cast<int>(rgbModel.G()) << " " << static_cast<int>(rgbModel.B())
              << " " << static_cast<int>(rgbModel.A()) << "\n";

    rgbModel.R() = 111;
    std::cout << static_cast<int>(rgbModel.R()) << " " << static_cast<int>(rgbModel.G()) << " " << static_cast<int>(rgbModel.B())
              << " " << static_cast<int>(rgbModel.A()) << std::endl;;
    rgbModel.G() = 33;
    std::cout << static_cast<int>(rgbModel.R()) << " " << static_cast<int>(rgbModel.G()) << " " << static_cast<int>(rgbModel.B())
              << " " << static_cast<int>(rgbModel.A()) << std::endl;;
    rgbModel.B() = 1;
    std::cout << static_cast<int>(rgbModel.R()) << " " << static_cast<int>(rgbModel.G()) << " " << static_cast<int>(rgbModel.B())
              << " " << static_cast<int>(rgbModel.A()) << std::endl;
    rgbModel.A() = 142;

    std::cout << static_cast<int>(rgbModel.R()) << " " << static_cast<int>(rgbModel.G()) << " " << static_cast<int>(rgbModel.B())
              << " " << static_cast<int>(rgbModel.A()) << std::endl;;
}

void CanvasTest() try {
    L_RT::Canvas<L_RT::Color::RGB> canvasDefaultC(1080, 1920);
    auto defCanvPixel = canvasDefaultC.GetPixel(12, 156);
    std::cout << (int)defCanvPixel.R() << " " << (int)defCanvPixel.G() << " " << (int)defCanvPixel.B() << "\n";

    L_RT::Canvas<L_RT::Color::RGB> canvasThatMove(std::move(canvasDefaultC));
    canvasThatMove.PutPixel(12, 156, {123, 124, 125});
    auto moveCanvPixel = canvasThatMove.GetPixel(12, 156);
    std::cout << (int)moveCanvPixel.R() << " " << (int)moveCanvPixel.G() << " " << (int)moveCanvPixel.B() << "\n";

    L_RT::Canvas<L_RT::Color::RGB> canvasThatCopy = canvasThatMove;

    canvasThatMove.PutPixel(12, 156, {123, 4, 215});

    auto otherMoveCanvPixel = canvasThatMove.GetPixel(12, 156);
    std::cout << (int)otherMoveCanvPixel.R() << " " << (int)otherMoveCanvPixel.G() << " " << (int)otherMoveCanvPixel.B() << "\n";

} catch (std::exception &exception) {
    std::cerr << exception.what() << "\n";
}

int main() {
    RGBTest();
    CanvasTest();
}
