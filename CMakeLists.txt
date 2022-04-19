cmake_minimum_required(VERSION 3.17)
project(DuoLingo)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 6)

#set(CMAKE_CXX_FLAGS "-fsanitize=undefined -fsanitize=leak -fsanitize=address")

find_package(Qt6Core REQUIRED)
find_package(Qt6Widgets REQUIRED)
find_package(Qt6Multimedia REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(
        SOURCES
        main.cpp
        controller.cpp
        main_page.cpp
        model.cpp
        exercise_page.cpp
        randomizer.cpp
        pick_widget.cpp
        input_widget.cpp
        audio_exercise.h
        audio_widget.cpp audio_widget.h)

find_package(Qt${QT_VERSION} COMPONENTS Widgets Multimedia Core)


qt6_add_big_resources(SOURCES resources.qrc)

#add_executable(DuoLingo )

add_executable(${PROJECT_NAME} ${SOURCES} ${APP_ICON_RESOURCE_WINDOWS})
target_link_libraries(${PROJECT_NAME} Qt6::Core)
target_link_libraries(${PROJECT_NAME} Qt6::Widgets)
target_link_libraries(${PROJECT_NAME} Qt6::Multimedia)

