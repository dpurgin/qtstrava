# qtstrava-cli - An example usage of QtStrava, a Qt wrapper for Strava API
# Copyright (C) 2020 Dmitriy Purgin <dpurgin@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

find_package(Qt5 COMPONENTS Core Network NetworkAuth Gui REQUIRED)

add_executable(qtstrava-cli
    src/main.cpp
    src/authorizationhandler.cpp

    src/authorizationhandler.h
)
target_link_libraries(qtstrava-cli
    Qt5::Core
    Qt5::Network
    Qt5::NetworkAuth
    Qt5::Gui
    qtstrava
)
