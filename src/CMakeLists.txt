project(src)

add_executable(demo main.cpp core.cpp renderer.cpp)

target_link_libraries(demo ${SDL2_LIBRARY})
target_link_libraries(demo ${Boost_LIBRARIES})
target_link_libraries(demo glbinding)
target_link_libraries(demo ${OPENGL_LIBRARIES})
target_link_libraries(demo assimp)
target_link_libraries(demo ${GLM_LIBRARIES})

install(TARGETS demo RUNTIME DESTINATION ${BUILD_DIR})
