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
