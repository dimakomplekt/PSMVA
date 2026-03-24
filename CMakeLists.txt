cmake_minimum_required(VERSION 3.15)
project(PSMVA)

set(CMAKE_CXX_STANDARD 17)



file(GLOB_RECURSE PROJECT_SOURCES
    "src/*.cpp"
    "libs/**/*.cpp"
)

add_executable(PSMVA ${PROJECT_SOURCES})


# ---------------- SDL ----------------

# Include SDL
target_include_directories(PSMVA PRIVATE
    ${CMAKE_SOURCE_DIR}/libs/engine/SDL3-3.4.2/include
)

# Link SDL (x64)
target_link_libraries(PSMVA PRIVATE
    ${CMAKE_SOURCE_DIR}/libs/engine/SDL3-3.4.2/lib/x64/SDL3.lib
)

# SDL ttf include
target_include_directories(PSMVA PRIVATE
    ${CMAKE_SOURCE_DIR}/libs/engine/SDL3_ttf-3.1.0/include
)

target_include_directories(PSMVA PRIVATE
    ${CMAKE_SOURCE_DIR}/libs/engine/SDL3_ttf-3.1.0/include/SDL3_ttf
)

target_link_libraries(PSMVA PRIVATE
    ${CMAKE_SOURCE_DIR}/libs/engine/SDL3_ttf-3.1.0/lib/x64/SDL3_ttf.lib
)


# dll copying for SDL

add_custom_command(TARGET PSMVA POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/libs/engine/SDL3-3.4.2/lib/x64/SDL3.dll"
        "$<TARGET_FILE_DIR:PSMVA>"
)

add_custom_command(TARGET PSMVA POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/libs/engine/SDL3_ttf-3.1.0/lib/x64/SDL3_ttf.dll"
        "$<TARGET_FILE_DIR:PSMVA>"
)

# ---------------- OpenCV ----------------

set(OpenCV_DIR "C:/opencv/build")

find_package(OpenCV REQUIRED)

target_link_libraries(PSMVA PRIVATE ${OpenCV_LIBS})

target_include_directories(PSMVA PRIVATE ${OpenCV_INCLUDE_DIRS})
 

 # Добавляем include для IntelliSense
 target_include_directories(PSMVA PRIVATE

    "C:/opencv/build/include"
    "C:/opencv/build/x64/vc16/lib"
    "C:/opencv/modules/imgproc/include"
    "C:/opencv/modules/highgui/include" 
    "C:/opencv/sources/include/opencv2"

)
