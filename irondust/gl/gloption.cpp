/**
 ** This file is part of the irondust project.
 ** Copyright 2019 CyberViking Softwareschmiede GbR <leghissa@cyber-viking.com>.
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU Lesser General Public License as
 ** published by the Free Software Foundation, either version 3 of the
 ** License, or (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU Lesser General Public License for more details.
 **
 ** You should have received a copy of the GNU Lesser General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/


#include <irondust/gl/gloption.hpp>
#include <irondust/gl/glIncludes.hpp>

#define GLGETINT(target, idx) glGetIntegerv(target, reinterpret_cast<GLint*>(modes+idx))


namespace irondust
{
    namespace gl
    {

        GlCullOption::GlCullOption(bool enabled, FaceMode mode)
            :  IGlOption(enabled, mode) {}

        void GlCullOption::pullModes(FaceMode modes[])
        {
            GLGETINT(GL_CULL_FACE_MODE, 0);
        }

        void GlCullOption::pushModes(FaceMode modes[])
        {
            glCullFace(+modes[0]);
        }



        GlPolyMode::GlPolyMode(PolyMode front, PolyMode back)
            : IGlMode(front, back) {}

        void GlPolyMode::pullModes(PolyMode modes[])
        {
            GLGETINT(GL_POLYGON_MODE, 0);
        }

        void GlPolyMode::pushModes(PolyMode modes[])
        {
            glPolygonMode(+FaceMode::Front, +modes[0]);
            glPolygonMode(+FaceMode::Back, +modes[1]);
        }



        GlBlendOption::GlBlendOption(bool enabled, BlendMode src, BlendMode dst)
            : IGlOption(enabled, src, dst) {}

        void GlBlendOption::pullModes(BlendMode modes[Size::Two])
        {
            GLGETINT(GL_BLEND_SRC, 0);
            GLGETINT(GL_BLEND_DST, 1);
        }

        void GlBlendOption::pushModes(BlendMode modes[Size::Two])
        {
            glBlendFunc(+modes[0], +modes[1]);
        }



        GlDepthOption::GlDepthOption(bool enabled, DepthMode mode)
            :IGlOption(enabled, mode) {}

        void GlDepthOption::pullModes(DepthMode modes[])
        {
            GLGETINT(GL_DEPTH_FUNC, 0);
        }

        void GlDepthOption::pushModes(DepthMode mode[])
        {
            glDepthFunc(+mode[0]);
        }
    }
}
