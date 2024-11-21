#include <iostream>
#include <vector>
#include <array>

    struct Material{
        float color[4];
        float kd;   // Diffuse factor
        float ks;   // Diffuse factor
        float kr;   // Reflectivity
        float kt;   // Transmitivity
        float n;    // Refractive index
    };

    struct Sphere{
        float center[3];
        float radius;
        Material mat;
        char c;
    };
    // 36 + 12 + 4 = 48

int main(){

    std::cout << sizeof(Sphere) << std::endl;
    return 0;
}
// c 