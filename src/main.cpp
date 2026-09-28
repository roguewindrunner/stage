#include "core/math_utils.hpp"
#include <iostream>

int main() {
    std::cout << "Welcome to the stage !\n";
    std::cout << "clamp(15, 0, 10) = " << stage::clamp(15.0f, 0.0f, 10.0f) << "\n";
    std::cout << "lerp(2, 8, 0.5) = " << stage::lerp(2.0f, 8.0f, 0.5f) << "\n";
    return 0;
}