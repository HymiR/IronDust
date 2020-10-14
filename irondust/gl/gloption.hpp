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


#ifndef GLOPTION_HPP
#define GLOPTION_HPP

#include <glm/fwd.hpp>
#include <irondust/gl/glIncludes.hpp>
#include <irondust/gl/iglbindable.hpp>
#include <irondust/util/log.hpp>


#define ENUM_BEG(name, type)                                  \
        namespace name##_ { enum  name##_ : type {
#define ENUM_END(name) };};                                   \
        using name = name##_::name##_;

// cast operators for several enum types to GLenum
#define Enum2NumOperator(M)                                   \
        auto operator+(M m)                                   \
        {                                                     \
            return static_cast<std::underlying_type_t<M>>(m); \
        }


namespace irondust
{
    namespace gl
    {
        ENUM_BEG(Size, glm::u8)
            One = 1u,
            Two = 2u,
            Four= 4u,
        ENUM_END(Size)
#undef ENUM_BEG
#undef ENUM_END

        enum class OptKind : GLenum
        {
            Culling = GL_CULL_FACE,
            Depth = GL_DEPTH,
            Blending = GL_BLEND,
        };

        enum class FaceMode : GLenum
        {
            Back = GL_BACK,
            Front = GL_FRONT,
            Both = GL_FRONT_AND_BACK,
        };

        enum class PolyMode : GLenum
        {
            Point = GL_POINT,
            Line = GL_LINE,
            Fill = GL_FILL,
        };

        enum class DepthMode : GLenum
        {
            Never = GL_NEVER,
            Less = GL_LESS,
            Equal = GL_EQUAL,
            LEqual = GL_LEQUAL,
            Greater = GL_GREATER,
            NotEqual = GL_NOTEQUAL,
            GEqual = GL_GEQUAL,
            Always = GL_ALWAYS,
        };

        enum class BlendMode : GLenum
        {
            Zero = GL_ZERO,
            One = GL_ONE,
            SrcAlphaSat = GL_SRC_ALPHA_SATURATE,
            //========================================
            SrcColor   = GL_SRC_COLOR,
            Src1Color  = GL_SRC1_COLOR,
            DstColor   = GL_DST_COLOR,
            SrcAlpha   = GL_SRC_ALPHA,
            Src1Alpha  = GL_SRC1_ALPHA,
            DstAlpha   = GL_DST_ALPHA,
            ConstColor = GL_CONSTANT_COLOR,
            ConstAlpha = GL_CONSTANT_ALPHA,
            //========================================
            InvSrcColor   = GL_ONE_MINUS_SRC_COLOR,
            InvSrc1Color  = GL_ONE_MINUS_SRC1_COLOR,
            InvDstColor   = GL_ONE_MINUS_DST_COLOR,
            InvSrcAlpha   = GL_ONE_MINUS_SRC_ALPHA,
            InvSrc1Alpha  = GL_ONE_MINUS_SRC1_ALPHA,
            InvDstAlpha   = GL_ONE_MINUS_DST_ALPHA,
            InvConstColor = GL_ONE_MINUS_CONSTANT_COLOR,
            InvConstAlpha = GL_ONE_MINUS_CONSTANT_ALPHA,
        };


        Enum2NumOperator(Size)
        Enum2NumOperator(OptKind)
        Enum2NumOperator(PolyMode)
        Enum2NumOperator(FaceMode)
        Enum2NumOperator(DepthMode)
        Enum2NumOperator(BlendMode)
#undef Enum2NumOperator


        template<typename T, Size S, OptKind K>
        class IGlOption : public IGlBindable
        {
        public:
            template<typename... TT>
            IGlOption(bool enabled, TT... modes)
                : cmodes{modes...}
                , penabled(false)
                , cenabled(enabled)
                , saved(false)
            {
            }

            virtual void bind() override
            {
                if(!saved) { // backup current state
                    if(cenabled) pullModes(pmodes);
                    penabled = pullEnabled();
                    saved = true;
                }

                if(cenabled) pushModes(cmodes);
                pushEnabled(cenabled);
            }

            virtual void unbind() override
            {
                if(cenabled) pushModes(pmodes);
                pushEnabled(penabled);
            }

        protected:
            T cmodes[S];
            T pmodes[S];

            virtual bool pullEnabled()
            {
                return glIsEnabled(+K);
            }

            virtual void pushEnabled(bool enabled)
            {
                if(enabled) glEnable(+K);
                else glDisable(+K);
            }

            virtual void pullModes(T modes[S]) = 0;
            virtual void pushModes(T modes[S]) = 0;

        private:
            bool penabled;
            bool cenabled;
            bool saved;
        };


        template<typename T, Size S>
        class IGlMode : public IGlBindable
        {
        public:
            template<typename... TT>
            IGlMode(TT... modes)
                : cmodes{modes...}
                , saved(false)
            {
            }

            virtual void bind() override
            {
                if(!saved) { // backup current state
                    pullModes(pmodes);
                    saved = true;
                }

                pushModes(cmodes);
            }

            virtual void unbind() override
            {
                pushModes(pmodes);
            }

        protected:
            T cmodes[S];
            T pmodes[S];

            virtual void pullModes(T modes[S]) = 0;
            virtual void pushModes(T modes[S]) = 0;

        private:
            bool saved;
        };



        class GlCullOption : public IGlOption<FaceMode, Size::One, OptKind::Culling>
        {
        public:
            GlCullOption(bool enabled=true, FaceMode mode=FaceMode::Back);
        protected:
            // IGlOption interface
            virtual void pullModes(FaceMode modes[Size::One]) override;
            virtual void pushModes(FaceMode modes[Size::One]) override;
        };


        class GlPolyMode : public IGlMode<PolyMode, Size::Two>
        {
        public:
            GlPolyMode(PolyMode front, PolyMode back=PolyMode::Fill);
        protected:
            // IGlMode interface
            virtual void pullModes(PolyMode modes[Size::Two]) override;
            virtual void pushModes(PolyMode modes[Size::Two]) override;
        };


        class GlBlendOption : public IGlOption<BlendMode, Size::Two, OptKind::Blending>
        {
        public:
            GlBlendOption(bool enabled=true, BlendMode src=BlendMode::SrcAlpha, BlendMode dst=BlendMode::InvSrcAlpha);
        protected:
            // IGlOption interface
            virtual void pullModes(BlendMode modes[Size::Two]) override;
            virtual void pushModes(BlendMode modes[Size::Two]) override;
        };


        class GlDepthOption : public IGlOption<DepthMode, Size::One, OptKind::Depth>
        {
        public:
            GlDepthOption(bool enabled=true, DepthMode mode=DepthMode::Less);
        protected:
            // IGlOption interface
            virtual void pullModes(DepthMode mode[Size::One]) override;
            virtual void pushModes(DepthMode mode[Size::One]) override;
        };
    }
}

#endif // GLOPTION_HPP
