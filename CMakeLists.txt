cmake_minimum_required(VERSION 3.21)
project(DuoLingo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

qt5_add_resources(SOURCES resources.qrc)

#add_executable(DuoLingo )

add_executable(DuoLingo ${SOURCES} main.cpp controller.cpp controller.h main_page.cpp main_page.h pick_exercise.h input_exercise.h model.cpp model.h pick_exercise_widget.cpp pick_exercise_widget.h randomizer.cpp randomizer.h)
target_link_libraries(DuoLingo
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets)

