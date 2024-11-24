#include <physics/collider.hpp>


Collider::Collider(std::vector<Shape*> objects){
    this->objects = objects;
}

void Collider::sphere_sphere(Sphere& s1, Sphere& s2) {
    float loss= 0.5;

    glm::vec3 delta = s2.position - s1.position;
    float distance = glm::length(delta);
    
    if (distance > s2.radius + s1.radius) return; 
    glm::vec3 normal = glm::normalize(delta);

    float overlap = (s1.radius + s2.radius) - distance;
    s1.position -= normal * (overlap * 0.5f);
    s2.position += normal * (overlap * 0.5f);

    glm::vec3 relativeVelocity = s2.velocity - s1.velocity;
    float s1VrelativeTos2 = glm::dot(relativeVelocity, normal);
    float s2VrelativeTos1 = glm::dot(-relativeVelocity, normal);

    if (s1VrelativeTos2 > 0 ) return;

    float restitution = 1.0f; 
    float j = -(1 + restitution) * s1VrelativeTos2;

    s1.velocity -= (j / 1.0f) * normal;
    s2.velocity += (j / 1.0f) * normal; 

    s1.velocity-= abs(s1.velocity)*loss;
    s2.velocity-= abs(s2.velocity)*loss;
}



void Collider::plane_sphere(Sphere& s, Plane& p) {
    float distance = glm::dot(s.position - p.position, p.normal);
    
    if (distance < -s.radius) {
        return;
    } else if (distance <= s.radius) {
        float overlap = s.radius - distance;

        s.position += p.normal * overlap;

        float velocityAlongNormal = glm::dot(s.velocity, p.normal);
        
        if (velocityAlongNormal > 0) return;

        float restitution = 1.0f; 
        float j = -(1 + restitution) * velocityAlongNormal;

        s.velocity += (j) * p.normal; 
    }
}



void Collider::collide() {
    int n=this->objects.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (dynamic_cast<Sphere*>(objects[i]) && dynamic_cast<Sphere*>(objects[j])) {
                Sphere* sphere1 = dynamic_cast<Sphere*>(objects[i]);
                Sphere* sphere2 = dynamic_cast<Sphere*>(objects[j]);
                sphere_sphere(*sphere1, *sphere2);
            }
            else {
                Plane* plane;
                Sphere* sphere;
                if(dynamic_cast<Plane*>(objects[i])) {
                    plane = dynamic_cast<Plane*>(objects[i]);
                    sphere = dynamic_cast<Sphere*>(objects[j]);
                }
                else{
                    plane = dynamic_cast<Plane*>(objects[j]);
                    sphere = dynamic_cast<Sphere*>(objects[i]);
                }
                plane_sphere(*sphere, *plane);                
                
            }
        }
    }
}

