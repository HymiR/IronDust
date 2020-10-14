# This file is part of the irondust project.
# Copyright 2020 CyberViking Softwareschmiede GbR <leghissa@cyber-viking.com>.
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


set(IRONDUST_LOGLEVEL 2 CACHE STRING "Loglevel of the whole system.")
set_property(CACHE IRONDUST_LOGLEVEL PROPERTY STRINGS 1 2 3 4)

if(IRONDUST_LOGLEVEL)
    add_definitions(-DLOG_LEVEL=${IRONDUST_LOGLEVEL})
endif()
