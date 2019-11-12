# This file is part of the cg project.
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


LIST(APPEND ${PROJECT_NAME}_SOURCES
	src/cg/util/timer.cpp
	src/cg/util/math.cpp
	src/cg/oogl/Model.cpp
	src/cg/oogl/FrameBufferObject.cpp
	src/cg/oogl/Navigator.cpp
	src/cg/oogl/Image.cpp
	src/cg/oogl/timer.cpp
	src/cg/oogl/DisplayList.cpp
	src/cg/oogl/gl_error.cpp
	src/cg/oogl/GLSLShader.cpp
	src/cg/oogl/Texture2D.cpp
	src/cg/oogl/Texture.cpp
	src/cg/oogl/Texture3D.cpp
	src/cg/oogl/GLSLProgram.cpp
	src/cg/oogl/model/ModelObj.cpp
	src/cg/oogl/model/Model3ds.cpp
)
