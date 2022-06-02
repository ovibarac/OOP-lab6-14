cmake_minimum_required(VERSION 3.21)
project(qtlab10)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH "/home/ovi/Programs/Qt/6.2.4/gcc_64/lib/cmake/")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(qtlab10 main.cpp GUI.cpp GUI.h Film.cpp Film.h FilmRepo.cpp FilmRepo.h
        FilmService.cpp FilmService.h Validator.cpp Validator.h UI.cpp UI.h MyVector.h Cos.cpp Cos.h Undo.h Observer.h CosGUI.cpp CosGUI.h)
target_link_libraries(qtlab10
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

