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

target_sources(${PROJECT_NAME}_app
PRIVATE
	irondust.cpp
)

find_package(glfw3 REQUIRED)

target_link_libraries(${PROJECT_NAME}_app
PRIVATE
	${PROJECT_NAME} # irondust lib
	glfw
)
# define (only!) local include dirs.
target_include_directories(${PROJECT_NAME}_app PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_compile_features(${PROJECT_NAME}_app PRIVATE cxx_std_11)
target_compile_options(${PROJECT_NAME}_app PRIVATE -Werror)
