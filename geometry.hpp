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


#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

//#include <glm/fwd.hpp>
#include <glm/gtc/constants.hpp>
//#include <glm/geometric.hpp>
#include <glm/glm.hpp>


const glm::f32 PIl = glm::pi<glm::f32>();
const glm::f32 PI2l = PIl * 2.f;
const glm::f32 HPIl = PIl / 2.f;

const glm::f64 PIm = glm::pi<glm::f64>();
const glm::f64 PI2m = PIm * 2.;
const glm::f64 HPIm = PIm / 2.;


namespace cg
{
//    template<typename I>  glm::f32 ratio(I w, I h)
//    {
//        return w / h;
//    }

    glm::f32 ratio(glm::u32 w, glm::u32 h);
    glm::f32 ratio(glm::i32 w, glm::i32 h);
    glm::f32 ratio(glm::f64 w, glm::f64 h);

    glm::f32 bounce_step(glm::f64 t, glm::u32 T=2000, glm::f32 a=1.0, glm::f32 b=0.0);
    glm::f32 rotate_radians(glm::f64 t, glm::u16 speed=30);
}


#endif // GEOMETRY_HPP
