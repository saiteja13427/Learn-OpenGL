cmake_minimum_required(VERSION 3.10.0)
project(learn-opengl VERSION 0.1.0 LANGUAGES C CXX)

add_executable(learn-opengl ./src/main.cpp 
                            ./libs/glad.h 
                            ./libs/glad.c 
                            ./libs/shader.cpp 
                            ./libs/shader.h 
                            ./libs/mesh.h 
                            ./libs/stb_image.cpp 
                            ./libs/stb_image.h)

target_link_libraries(learn-opengl glfw)
target_link_libraries(learn-opengl assimp)
target_link_libraries(learn-opengl ${CMAKE_DL_LIBS})