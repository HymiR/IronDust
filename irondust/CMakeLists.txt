# This file is part of the irondust project.
# Copyright 2019 CyberViking Softwareschmiede GbR <leghissa@cyber-viking.com>.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.


cmake_minimum_required(VERSION 3.13)
target_sources(${PROJECT_NAME}
PRIVATE
    sg/isgresourcenode.cpp
    sg/sgmodel.cpp
    sg/sgcontext.cpp
    sg/sglightnode.cpp
    sg/sgmaterialnode.cpp
    sg/sgnode.cpp
    sg/sgrendernode.cpp
    sg/sgscene.cpp
    sg/sgshadernode.cpp
    sg/sgtexturenode.cpp
    sg/sgtransformnode.cpp
    gl/gloption.cpp
    gl/Image.cpp
    gl/GLSLShader.cpp
    gl/GLSLProgram.cpp
    gl/Texture.cpp
    gl/Texture2D.cpp
    gl/Texture3D.cpp
    gl/gl_error.cpp
    util/math.cpp
PUBLIC
    sg/isgelement.hpp
    sg/isgnode.hpp
    sg/isgresource.hpp
    sg/isgresourcenode.hpp
    sg/sgmodel.hpp
    sg/sgconstants.hpp
    sg/sgcontext.hpp
    sg/sglightnode.hpp
    sg/sgmaterialnode.hpp
    sg/sgnode.hpp
    sg/sgrendernode.hpp
    sg/sgscene.hpp
    sg/sgshadernode.hpp
    sg/sgtexturenode.hpp
    sg/sgtransformnode.hpp
    gl/iglbindable.hpp
    gl/gloption.hpp
    gl/Image.hpp
    gl/GLSLShader.hpp
    gl/GLSLProgram.hpp
    gl/Texture.hpp
    gl/Texture2D.hpp
    gl/Texture3D.hpp
    gl/glIncludes.hpp
    gl/glfwIncludes.hpp
    gl/gl_error.hpp
    util/math.hpp
    util/log.hpp
    util/loglevels.hpp
    util/glm_ostream.hpp
)

# determine some libraries (the ones which cmake has a find_module for) to link against
# to check for existing find_modules  hit: cmake --help-module-list in your terminal.
# to check for info and variables set hit: cmake --help-module Find<ModuleName> in your terminal.
find_package(OpenGL REQUIRED)
find_package(GLEW 1.11 REQUIRED)
find_package(DevIL REQUIRED)
find_package(glm 0.9.7 REQUIRED) # header only

# link external libraries. this has to be done for classic dymamic libs as well as heaser-only libs.
# lib paths and include paths were propagated transitively by useng the target_* functions.
target_link_libraries(${PROJECT_NAME} PUBLIC
    ${OPENGL_opengl_LIBRARY}
    ${GLEW_LIBRARIES}
    ${IL_LIBRARIES}
    ${ILU_LIBRARIES}
    ${ILUT_LIBRARIES}
    glm
)

# define (only!) local include dirs.
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR})

#target_compile_definitions(${PROJECT_NAME} PUBLIC USE_BARRY)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_11)
target_compile_options(${PROJECT_NAME} PRIVATE -Werror -Wno-reserved-id-macro)
