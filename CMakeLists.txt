cmake_minimum_required(VERSION 3.21)
project(CMakeSFMLProject LANGUAGES CXX)

add_subdirectory("extern/box2d")
add_subdirectory("extern/entt")
include_directories("extern/box2d")
include_directories("extern/entt")

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(CMakeSFMLProject src/main.cpp src/components/Position.h src/components/SFMLRectangleShape.h src/components/LocalPlayer.h src/systems/RectangleDrawSystem.cpp src/systems/RectangleDrawSystem.h src/systems/LocalPlayerMovementSystem.cpp src/systems/LocalPlayerMovementSystem.h src/components/Speed.h src/util/Time.cpp src/util/Time.h src/datatype/Vector2.h src/systems/IRenderableSystem.h src/systems/ILoadableSystem.h src/systems/IUpdatableSystem.h src/systems/IFixedUpdatableSystem.h)
target_link_libraries(CMakeSFMLProject PRIVATE sfml-graphics box2d EnTT)
target_compile_features(CMakeSFMLProject PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET CMakeSFMLProject POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:CMakeSFMLProject> $<TARGET_FILE_DIR:CMakeSFMLProject> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS CMakeSFMLProject)
