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
project(irondust
    LANGUAGES CXX
    VERSION 0.2.4
)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(options)

# includes definitions for building libirondust
add_library(${PROJECT_NAME} SHARED "")
add_subdirectory(irondust)

# definitions for irondust app executable
add_executable(${PROJECT_NAME}_app "")
add_subdirectory(app)

# several pseudo targets for better maintaining other stuff within ide
add_custom_target(shaders SOURCES
    shaders/default.vsh
    shaders/default.fsh
    shaders/phong.vsh
    shaders/phong.fsh
    shaders/skybox.vsh
    shaders/skybox.fsh
)

add_custom_target(misc SOURCES
    README.md
    bufferobject.cpp
    bufferobject.hpp
)
