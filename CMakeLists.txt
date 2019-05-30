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


cmake_minimum_required(VERSION 3.11)

project(irondust
	LANGUAGES CXX
	VERSION 0.1
)

set(CMAKE_CXX_STANDARD 11)

# needed system libs
find_package(libcg REQUIRED)

# needed system libs via pkgconfig
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)


include_directories(
	${CMAKE_SOURCE_DIR}
	${libcg_INCLUDE_DIRS}
	${GLFW_INCLUDE_DIRS}
)

link_directories(BEFORE
	${libcg_LIBRARY_DIRS}
)

set(SOURCES
	geometry.cpp
	geometry.hpp
	irondust.cpp
	isgelement.cpp
	isgelement.hpp
	isgnode.cpp
	isgnode.hpp
	isgresource.cpp
	isgresource.hpp
	isgresourcenode.cpp
	isgresourcenode.hpp
	sgmodel.cpp
	sgmodel.hpp
	sgconstants.hpp
	sgcontext.cpp
	sgcontext.hpp
	sglightnode.cpp
	sglightnode.hpp
	sgmaterialnode.cpp
	sgmaterialnode.hpp
	sgnode.cpp
	sgnode.hpp
	sgrendernode.cpp
	sgrendernode.hpp
	sgscene.cpp
	sgscene.hpp
	sgshadernode.cpp
	sgshadernode.hpp
	sgtexturenode.cpp
	sgtexturenode.hpp
	sgtransformnode.cpp
	sgtransformnode.hpp
)

set(SHADERS
	default.vsh
	default.fsh
	phong.vsh
	phong.fsh
)

add_executable(${PROJECT_NAME}
	${SOURCES}
	${SHADERS}
)

target_link_libraries(${PROJECT_NAME}
	${GLFW_LIBRARIES}
	${libcg_LIBRARIES}
)
