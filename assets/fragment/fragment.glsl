

Ray[totalRays+1] reflectionRays;
Ray[totalRays+1] refractionRays;
Light light;
Plane ground;
Sphere[N] spheres;
Cuboid[BOX_COUNT] cuboids;



Hit RayCastPlane(vec3 rayOrigin, vec3 rayDir, in Plane plane, float delta) {
    Hit hit;
    hit.d = -1.0; 

    rayOrigin += delta * plane.normal;

    float denominator = dot(rayDir, plane.normal);
    
    if (denominator != 0.0) {
        float d = dot(plane.center - rayOrigin, plane.normal) / denominator;

        if (d >= 0.0) { // Only consider hits in the direction of the ray
            hit.d = d;
            hit.point = rayOrigin + d * rayDir;

            hit.normal = plane.normal;
            if (denominator > 0.0) {
                hit.normal = -plane.normal; // Flip the normal if the ray is coming from the opposite side
            }

            vec3 relPoint = abs(hit.point - plane.center);
            if (plane.normal.y == 1.0) {
                if (relPoint.x > plane.size.x * 0.5 || relPoint.z > plane.size.z * 0.5) {
                    hit.d = -1.0; // Not within the bounds
                }
            } else {
                if (relPoint.y > plane.size.x * 0.5 || relPoint.z > plane.size.z * 0.5) {
                    hit.d = -1.0; // Not within the bounds
                }
            }
        }
    }

    return hit;
}

Hit RayCastCuboid(vec3 rayOrigin, vec3 rayDir, in Cuboid cuboid) {
    Hit hit;
    hit.d = -1.0;  
    float tMin = -1e10; 
    float tMax = 1e10; 

    vec3 halfSize = cuboid.size * 0.5;

    for (int i = 0; i < 3; ++i) {
        float origin = rayOrigin[i];
        float direction = rayDir[i];

        if (direction != 0.0) {
            float t1 = (cuboid.center[i] - halfSize[i] - origin) / direction;
            float t2 = (cuboid.center[i] + halfSize[i] - origin) / direction;

            if (t1 > t2) {
                float temp = t1;
                t1 = t2;
                t2 = temp;
            }

            tMin = max(tMin, t1);
            tMax = min(tMax, t2);

            if (tMin > tMax) {
                hit.d = -1.0;  // No intersection
                return hit;
            }
        } else {
            if (origin < cuboid.center[i] - halfSize[i] || origin > cuboid.center[i] + halfSize[i]) {
                hit.d = -1.0;  // No intersection
                return hit;
            }
        }
    }

    hit.d = tMin;
    hit.point = rayOrigin + hit.d * rayDir;

    if (abs(hit.point.x - (cuboid.center.x - halfSize.x)) < 1e-4) {
        hit.normal = vec3(-1.0, 0.0, 0.0);  // Left face
    } else if (abs(hit.point.x - (cuboid.center.x + halfSize.x)) < 1e-4) {
        hit.normal = vec3(1.0, 0.0, 0.0);   // Right face
    } else if (abs(hit.point.y - (cuboid.center.y - halfSize.y)) < 1e-4) {
        hit.normal = vec3(0.0, -1.0, 0.0);  // Bottom face
    } else if (abs(hit.point.y - (cuboid.center.y + halfSize.y)) < 1e-4) {
        hit.normal = vec3(0.0, 1.0, 0.0);   // Top face
    } else if (abs(hit.point.z - (cuboid.center.z - halfSize.z)) < 1e-4) {
        hit.normal = vec3(0.0, 0.0, -1.0);  // Near face
    } else if (abs(hit.point.z - (cuboid.center.z + halfSize.z)) < 1e-4) {
        hit.normal = vec3(0.0, 0.0, 1.0);   // Far face
    }

    return hit;
}


Hit RayCastSphere(vec3 rayOrigin, vec3 rayDir, in Sphere sphere){
    Hit hit = Hit(-1.0, vec3(0), vec3(0));
    
    float a = dot(rayDir, rayDir);
    float b = 2.0 * dot(rayDir, rayOrigin-sphere.center);
    float c = dot(rayOrigin-sphere.center, rayOrigin-sphere.center) - 
                sphere.radius * sphere.radius;
    
    float det = b*b - 4.0*a*c;
    if (det >= 0.0){
        float d1 = (-b-sqrt(det))/2.0*a;
        float d2 = (-b+sqrt(det))/2.0*a;
        hit.d = min(d1,d2);
        hit.point = rayOrigin + hit.d * rayDir;
        hit.normal = normalize(hit.point - sphere.center);
    }
    return hit;
}

float RandFloat(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

vec4 GetLighting(in Material mat, in vec3 normal, in vec3 rayDir, in Light light){
    // Diffuse
    float diff = max(dot(normal, -light.dir), 0.0);
    // Specular
    vec3 reflectDir = -light.dir - 2.0 * normal * dot(-light.dir, normal);
    float spec = pow(max(dot(rayDir, reflectDir), 0.0), mat.ks); 
    // Total
    vec4 col = mat.color * light.color * (diff * mat.kd + spec * mat.kr);
    return col;
}

float Fresnel(float n1, float n2, vec3 normal, vec3 incident, float reflectivity){
    // Schlick aproximation
    float r0 = (n1-n2) / (n1+n2);
    r0 *= r0;
    float cosX = -dot(normal, incident);
    if (n1 > n2)
    {
        float n = n1/n2;
        float sinT2 = n*n*(1.0-cosX*cosX);
        // Total internal reflection
        if (sinT2 > 1.0)
            return 1.0;
        cosX = sqrt(1.0-sinT2);
    }
    float x = 1.0-cosX;
    float ret = r0+(1.0-r0)*x*x*x*x*x;

    // adjust reflect multiplier for object reflectivity
    ret = (reflectivity + (1.0-reflectivity) * ret);
    return ret;
}


vec4 RayTraceCore(inout Ray ray, inout Material hitMat, inout Hit hit, in int iter){
    
    // Plane distance calculations
    Hit hitGround = RayCastPlane(ray.origin, ray.dir, ground, 0.0);
    Hit[BOX_COUNT] hitBox;

    for( int i=0;i<BOX_COUNT;i++){
        hitBox[i]= RayCastCuboid(ray.origin, ray.dir, cuboids[i]);
    }
    // Sphere distance calculations
    Hit[N] hitSphere;
    for (int i=0; i<N; i++){
        hitSphere[i] = RayCastSphere(ray.origin, ray.dir, spheres[i]);
    }

    // Finding closest object to camera
    vec4 col = vec4(0,0,0,0);
    // Minimum distance for ground plane
    if (hitGround.d > 0.0){
        hit = hitGround;
        // sample ground texture
        vec2 groundTexScale = vec2(0.5);
        ground.mat.color = texture(iChannel1, hitGround.point.xz*groundTexScale);
        hitMat = ground.mat;
        col = GetLighting(ground.mat, hitGround.normal, ray.dir, light);
    }

    for(int i=0;i< BOX_COUNT;i++){
        if(hitBox[i].d < 0.0) hitBox[i].d = FLOAT_MAX;
        if(hitBox[i].d < hit.d){
            hit = hitBox[i];
            hitMat = cuboids[i].mat;
            col = GetLighting(cuboids[i].mat, hitBox[i].normal, ray.dir, light);
        }
    }

    // Minimum distances for all spheres
    for (int i=0; i<N; i++){
        if (hitSphere[i].d < 0.0) hitSphere[i].d = FLOAT_MAX;
        if (hitSphere[i].d < hit.d){
            hit = hitSphere[i];
            hitMat = spheres[i].mat;
            col = GetLighting(spheres[i].mat, hitSphere[i].normal, ray.dir, light);
        }
    }

    if (hit.d == FLOAT_MAX){
        col = texture(iChannel0, reflect(ray.dir, hit.normal));
        return col;
    }

#ifdef SHADOWS
    if (iter == R-1){
        Hit hitShadow;
        float minShadowDist = FLOAT_MAX;
        hitShadow = RayCastPlane(hit.point, -light.dir, ground, delta);
        if (hitShadow.d >= 0.0 && hitShadow.d < minShadowDist){
            col = vec4(0) * shadowFactor * exp(-1.0/hitShadow.d);
            minShadowDist = hitShadow.d;
        }

        for(int i=0;i< BOX_COUNT;i++){
            hitShadow = RayCastCuboid(hit.point, -light.dir, cuboids[i]);
            if (hitShadow.d >= 0.0 && hitShadow.d < minShadowDist){
                col = hitMat.color * shadowFactor * exp(-1.0/hitShadow.d);
                minShadowDist = hitShadow.d;
            }
        }

        for (int i=0; i<N; i++){
            hitShadow = RayCastSphere(hit.point + delta*hit.normal, -light.dir, spheres[i]);
            if (hitShadow.d >= 0.0 && hitShadow.d < minShadowDist){
                minShadowDist = hitShadow.d;
                col = hitMat.color * shadowFactor * exp(-1.0/hitShadow.d);
            }
        }
    }
#endif

    // Ambient light
    if (iter == 0)
        col += ambientStrength * ambientLight * hitMat.color;

    return col;
}


vec4 CastRays(in int iter){
    
    int startIdx = 0;
    if (iter != 0)
        startIdx = 1;
        for(int i=0;i<iter-1;i++)
            startIdx *= 2;
    int endIdx = 1;
    for(int i=0;i<iter;i++)
        endIdx *= 2;
    
    vec4 currLevelCol = vec4(0);

    // ------- REFLECTION PART -------
    // For each new reflection ray
    int j = 0;  // new ray counter
    for (int r=startIdx; r<endIdx; r++){
        // Incident ray
        Ray ray = reflectionRays[r];
        if (ray.dir == vec3(0) || ray.factor==0.0){
            // Rays that don't exist
            j += 1;
            continue;
        }

        Hit hit = Hit(FLOAT_MAX, vec3(0), vec3(0));
        Material hitMat;
        // Get color of ray
        vec4 col = RayTraceCore(ray, hitMat, hit, iter);
        currLevelCol += col * ray.factor;

        float n1, n2;
        if (ray.n != 1.0){
            n1 = ray.n;
            n2 = 1.0;
            hit.normal *= -1.0;
        } 
        else {
            n1 = 1.0;
            n2 = hitMat.n;
        }
        float Kr = Fresnel(n1, n2, hit.normal, ray.dir, hitMat.kr);
        
        // Add new reflection & refraction ray
        if (hit.d < FLOAT_MAX && hit.d > 0.0){
            // Add new reflection ray
            reflectionRays[endIdx+j].origin = hit.point + delta * hit.normal;
            reflectionRays[endIdx+j].dir = reflect(ray.dir, hit.normal);
            reflectionRays[endIdx+j].factor = ray.factor * Kr;
            reflectionRays[endIdx+j].n = n1;
            // Add new refraction ray
            if (hitMat.kt > 0.0){
                refractionRays[endIdx+j].origin = hit.point - delta * hit.normal;
                refractionRays[endIdx+j].factor = ray.factor * (1.0-Kr);
                refractionRays[endIdx+j].n = n2;
                refractionRays[endIdx+j].dir = refract(ray.dir, hit.normal, n1/n2);
            }
        }
        j += 1;
    }


    // ------- REFRACTION PART -------
    // For each new refraction ray
    for (int r=startIdx; r<endIdx; r++){
        Ray ray = refractionRays[r];
        if (ray.dir == vec3(0) || ray.factor==0.0){
            // Rays that don't exist
            j += 1;
            continue;
        }

        Hit hit = Hit(FLOAT_MAX, vec3(0), vec3(0));
        Material hitMat;
        // Get color of ray
        vec4 col = RayTraceCore(ray, hitMat, hit, iter);
        currLevelCol += col * ray.factor;

        float n1, n2;
        if (ray.n != 1.0){
            n1 = ray.n;
            n2 = 1.0;
            hit.normal *= -1.0;
        }
        else {
            n1 = 1.0;
            n2 = hitMat.n;
        }
        float Kr = Fresnel(n1, n2, hit.normal, ray.dir, hitMat.kr);
        
        // Add new reflection & refraction ray
        if (hit.d < FLOAT_MAX && hit.d > 0.0){
            // Add new reflection ray
            reflectionRays[endIdx+j].origin = hit.point + delta * hit.normal;
            reflectionRays[endIdx+j].dir = reflect(ray.dir, hit.normal);
            reflectionRays[endIdx+j].factor = ray.factor * Kr;
            reflectionRays[endIdx+j].n = n1;
            // Add new refraction ray
            if (hitMat.kt > 0.0){
                refractionRays[endIdx+j].origin = hit.point - delta * hit.normal;
                refractionRays[endIdx+j].factor = ray.factor * (1.0-Kr);
                refractionRays[endIdx+j].n = n2;
                refractionRays[endIdx+j].dir = refract(ray.dir, hit.normal, n1/n2);
            }
        }
        j += 1;
    }

    return currLevelCol;
}


//--------- Main Function ---------
void mainImage( out vec4 fragColor, in vec2 fragCoord )
{       
    vec3 cameraPos = cameraPosition;
    Ray ray;
    ray.origin = cameraPos;
    
    
    vec2 uv = (fragCoord-0.5*iResolution.xy)/iResolution.y;
    vec3 camR = cross(cameraViewDir, cameraUp);
    ray.dir= normalize(cameraViewDir + camR * uv.x + cameraUp * uv.y);
    ray.factor = 1.0;
    ray.n = 1.0;   


    for (int i=0; i<totalRays+1; i++){
        reflectionRays[i] = Ray(vec3(0), vec3(0), 0.0, 0.0);
        refractionRays[i] = Ray(vec3(0), vec3(0), 0.0, 0.0);
    }
    reflectionRays[0] = ray;
    vec4 finalCol = vec4(0);
    for(int iter=0; iter<R; iter++)
        finalCol += CastRays(iter);
    
    // Output to screen
    fragColor = finalCol;
}

void main() {
    ground = u_planes[0];
    light = u_lights[0];
    spheres = u_spheres;
    cuboids = u_cuboids;
    light.dir = vec3(-0.4, -1.0, -1);
    //light.dir = vec3(0.6, -0.5, 1);
    light.mag = 0.0;
    light.color = vec4(1,1,1,1);

    mainImage(fragColor, TexCoords * iResolution.xy);
}