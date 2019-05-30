// (C) 2019 by CyberViking Softwareschmiede GbR
// All rights reserved.
// -----------------------------------------------------
// created by: armin
// created on: 20.05.2019
// -----------------------------------------------------
// This document contains proprietary information belonging to
// CyberViking Softwareschmiede GbR.
// Passing on and copying of this document, use and communication
// of its contents is not permitted without prior written authorization.


#include <geometry.hpp>

namespace cg
{
    glm::f32 ratio(glm::u32 w, glm::u32 h)
    {
        return static_cast<glm::f32>(static_cast<glm::f64>(w) / h);
    }

    glm::f32 ratio(glm::i32 w, glm::i32 h)
    {
        return glm::abs(static_cast<glm::f32>(static_cast<glm::f64>(w) / h));
    }

    glm::f32 ratio(glm::f64 w, glm::f64 h)
    {
        return glm::abs(static_cast<glm::f32>(w / h));
    }


    glm::f32 bounce_step(glm::f64 t, glm::u32 T, glm::f32 a, glm::f32 b)
    {
        glm::f64 w = PI2m / T;
        return glm::abs(static_cast<glm::f32>(glm::sin(w*t))*a) + b;
    }

    glm::f32 rotate_radians(glm::f64 t, glm::u16 speed)
    {
        glm::f64 deg = fmod(t / speed, 360);
        return static_cast<glm::f32>(glm::radians(deg));
    }
}
