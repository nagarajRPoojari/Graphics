#version 430 core

out vec4 fragColor;
in vec2 TexCoords;

uniform vec3 iResolution;
uniform float iTime;
uniform sampler2D iChannel0;
uniform sampler2D iChannel1; 

uniform vec3 cameraPosition;
uniform vec3 cameraViewDir;
uniform vec3 cameraUp;


#define PI 3.1415926535
#define SHADOWS

float FLOAT_MAX = 10e+10;
float FLOAT_MIN = -10e+10;

// Global Parameters
vec4 ambientLight = vec4(1,1,1,1);
float ambientStrength = 0.1;
const int R = 3;    // Num reflections
const float delta = 10e-5;
float shadowFactor = 0.1;
const int N = 2; 
const int LIGHT_COUNT = 1;   // Num spheres
const int PLANE_COUNT = 1;   // Num spheres
bool transform = true;
bool deg = false;
float fov = 0.8;   // 0 < fov
const int totalRays = int(pow(2.0, float(R)));

//--------------------------------------//

struct Material{
    vec4 color;
    float kd;   // Diffuse factor
    float ks;   // Diffuse factor
    float kr;   // Reflectivity
    float kt;   // Transmitivity
    float n;    // Refractive index
};

struct Sphere{
    Material mat;
    vec3 center;
    float radius;
};

struct Plane{
    vec3 center;
    vec3 size;
    vec3 normal;
    Material mat;
};

struct Light{
    vec3 dir;
    vec4 color;
    vec3 ray;
    float mag;
};

struct Ray{
    vec3 dir;
    vec3 origin;
    float factor;   // color multiplier for ray
    float n;    // index of medium ray in currently in
};

struct Hit{
    float d;
    vec3 point;
    vec3 normal;
};

uniform Sphere u_spheres[N];
uniform Light u_lights[LIGHT_COUNT];
uniform Plane u_planes[PLANE_COUNT];
