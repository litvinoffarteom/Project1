#pragma once

#ifndef PROJECT1_VECTOR_H
#define PROJECT1_VECTOR_H

#include <numbers>
#include <cmath>

struct Vec3 {
    float x, y, z;

    Vec3 operator+(Vec3 d) const{
        return {x + d.x, y + d.y, z + d.z};
    }

    Vec3 operator-(Vec3 d) const{
        return {x - d.x, y - d.y, z - d.z};
    }

    Vec3 operator*(Vec3 d) const{
        return {x * d.x, y * d.y, z * d.z};
    }

    Vec3 operator/(Vec3 d) const{
        return {x / d.x, y / d.y, z / d.z};
    }

    void Normalize() {
        while (y < -180) {
            y += 360;
        }
        while (y > 180) {
            y -= 360;
        }
        if (x > 89) {
            x = 89;
        }
        if (x < -89) {
            x = -89;
        }
    }
};

#endif //PROJECT1_VECTOR_H
