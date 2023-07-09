cmake_minimum_required(VERSION 3.21)
project(ECSteroid LANGUAGES CXX)

cmake_policy(SET CMP0135 NEW)

add_subdirectory("extern/box2d")
add_subdirectory("extern/entt")
include_directories("extern/box2d")
include_directories("extern/entt")

file(GLOB_RECURSE ASSET_FILES "${CMAKE_SOURCE_DIR}/assets/*")

set(ASSET_FILES_DIR "${CMAKE_SOURCE_DIR}/assets")
file(COPY ${ASSET_FILES_DIR} DESTINATION ${CMAKE_BINARY_DIR})

include(FetchContent)
set(IMGUI_VERSION 1.87)

FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)

FetchContent_Declare(
        imgui
        URL "https://github.com/ocornut/imgui/archive/v${IMGUI_VERSION}.zip"
)

FetchContent_Declare(
        imgui-sfml
        GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
        GIT_TAG        master
)

FetchContent_MakeAvailable(SFML)
FetchContent_MakeAvailable(imgui)

set(IMGUI_DIR ${imgui_SOURCE_DIR})
option(IMGUI_SFML_FIND_SFML "Use find_package to find SFML" OFF)
option(IMGUI_SFML_IMGUI_DEMO "Build imgui_demo.cpp" ON)

FetchContent_MakeAvailable(imgui-sfml)

add_executable(ECSteroid ${ASSET_FILES} src/main.cpp src/components/Position.h src/components/LocalPlayer.h src/systems/SFMLRenderSystem.cpp src/systems/SFMLRenderSystem.h src/systems/LocalPlayerMovementSystem.cpp src/systems/LocalPlayerMovementSystem.h src/components/Speed.h src/util/Time.cpp src/util/Time.h src/datatype/Vector2.h src/systems/core/IRenderableSystem.h src/systems/core/ILoadableSystem.h src/systems/core/IUpdatableSystem.h src/systems/core/IFixedUpdatableSystem.h src/systems/core/IEventSubscriberSystem.h src/systems/core/SystemsHandler.cpp src/systems/core/SystemsHandler.h src/scenes/Scene.cpp src/scenes/Scene.h src/scenes/GameScene.cpp src/scenes/GameScene.h src/systems/Box2DPhysicsSystem.cpp src/systems/Box2DPhysicsSystem.h src/components/Rotation.h src/components/PhysicsBody.h src/components/PhysicsDefinition.h src/systems/core/IEntityRegistry.h src/systems/core/EventSystem.h src/systems/core/IEventPublisherSystem.h src/events/TestEvent.h src/Application.cpp src/Application.h src/components/SFMLDrawable.h src/components/SFMLTransformable.h src/events/CollisionEvent.h src/components/Sprite.h src/systems/SFMLSpriteSystem.cpp src/systems/SFMLSpriteSystem.h src/systems/Box2DDebugDrawSystem.cpp src/systems/Box2DDebugDrawSystem.h src/components/debug/Box2DDebug.h src/systems/WrapAroundSystem.cpp src/systems/WrapAroundSystem.h src/events/SFMLEvent.h src/components/WrapAround.h src/systems/PlayerShootSystem.cpp src/systems/PlayerShootSystem.h src/components/ShootAbility.h src/systems/ShootCooldownSystem.cpp src/systems/ShootCooldownSystem.h src/components/debug/DebugAngle.h src/systems/DebugAngleSystem.h src/components/bullet/BulletLifetime.h src/systems/BulletLifetimeSystem.cpp src/systems/BulletLifetimeSystem.h src/systems/BulletCollisionSystem.cpp src/systems/BulletCollisionSystem.h src/components/bullet/BulletDestroyOnCollision.h src/components/Health.h src/components/bullet/BulletDamage.h src/systems/DestroyOnZeroHealthSystem.cpp src/systems/DestroyOnZeroHealthSystem.h src/components/debug/DebugName.h src/systems/core/IFinalUpdatableSystem.h src/systems/core/ILateUpdatableSystem.h src/systems/AsteroidSpawnerSystem.cpp src/systems/AsteroidSpawnerSystem.h src/components/Asteroid.h src/util/Random.h src/components/Boid.h src/systems/BoidSystem.cpp src/systems/BoidSystem.h src/events/EntityDeathEvent.h src/datatype/CollisionGroup.h src/systems/ui/LocalPlayerHealthUISystem.cpp src/systems/ui/LocalPlayerHealthUISystem.h src/systems/AsteroidToPlayerCollisionSystem.cpp src/systems/AsteroidToPlayerCollisionSystem.h src/systems/ui/GameOverTextUISystem.cpp src/systems/ui/GameOverTextUISystem.h)
target_link_libraries(ECSteroid PRIVATE sfml-graphics box2d EnTT ImGui-SFML::ImGui-SFML)
target_compile_features(ECSteroid PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET ECSteroid POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:ECSteroid> $<TARGET_FILE_DIR:ECSteroid> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS ECSteroid)
