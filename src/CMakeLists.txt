SET(ROOT ${PATH_SRC})

SET(EXECUTABLE_NAME "epictvfighting")

SET(SOURCES
    "${ROOT}/AnimationSequence.cpp"
    "${ROOT}/ceciEstNotreMain.cpp"
    "${ROOT}/Dash.cpp"
    "${ROOT}/EmitSound.cpp"
    "${ROOT}/Game.cpp"
    "${ROOT}/LocalizationStrings.cpp"
    "${ROOT}/ResourcePath.cpp"
    "${ROOT}/Scene.cpp"
    "${ROOT}/Shoot.cpp"
    "${ROOT}/State.cpp"
    "${ROOT}/gamestates/GameplayState.cpp"
    "${ROOT}/gamestates/GameState.cpp"
    "${ROOT}/gamestates/MenuState.cpp"
    "${ROOT}/gamestates/VersusState.cpp"
    "${ROOT}/gamestates/PlayerSelectionState.cpp"
    "${ROOT}/gamestates/CreditsState.cpp"
    "${ROOT}/gamestates/OptionState.cpp"
    "${ROOT}/gamestates/VictoryState.cpp"
    "${ROOT}/managers/CollisionManager.cpp"
    "${ROOT}/managers/GameStateManager.cpp"
    "${ROOT}/managers/ObjectManager.cpp"
    "${ROOT}/managers/SoundBufferManager.cpp"
    "${ROOT}/managers/TextureManager.cpp"
    "${ROOT}/objects/Object.cpp"
    "${ROOT}/objects/actors/Actor.cpp"
    "${ROOT}/objects/actors/players/Player.cpp"
    "${ROOT}/objects/actors/players/PlayerGiranath.cpp"
    "${ROOT}/objects/actors/players/GenericPlayer.cpp"
    "${ROOT}/objects/effects/CustomFX.cpp"
    "${ROOT}/objects/effects/Fx.cpp"
    "${ROOT}/objects/effects/FXLoader.cpp"
    "${ROOT}/objects/projectiles/Guntherken.cpp"
    "${ROOT}/objects/projectiles/prinnyInTheHat.cpp"
    "${ROOT}/objects/projectiles/Projectile.cpp"
    "${ROOT}/objects/projectiles/ProjectileFactory.cpp"
    "${ROOT}/physic/PhysicBody.cpp"
    "${ROOT}/physic/PhysicWorld.cpp"
    "${ROOT}/physic/BoxBody.cpp"
    "${ROOT}/physic/Collision.cpp"
)

INCLUDE_DIRECTORIES(
    "${ROOT}/containers"
    "${ROOT}/gamestates"
    "${ROOT}/managers"
    "${ROOT}/objects"
    "${ROOT}/objects/actors"
    "${ROOT}/objects/actors/players"
    "${ROOT}/objects/effects"
    "${ROOT}/objects/projectiles"
    "${ROOT}/physic"
    "${ROOT}"
)

# Set the c++ standard to C++11
IF(${CMAKE_MAJOR_VERSION} EQUAL "3" AND ${CMAKE_MINOR_VERSION} GREATER "1")
    SET(CMAKE_CXX_STANDARD 11)
ELSE()
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ENDIF()

ADD_EXECUTABLE(${EXECUTABLE_NAME} ${SOURCES})

# Link to SFML
FIND_PACKAGE(SFML 2 COMPONENTS audio graphics window system REQUIRED)
INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})
TARGET_LINK_LIBRARIES(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
