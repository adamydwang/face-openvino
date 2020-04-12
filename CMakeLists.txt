cmake_minimum_required(VERSION 2.7)
project(insightface)
add_definitions(-std=c++11)

find_package(InferenceEngine REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include
                    ${InferenceEngine_INCLUDE_DIRS}
                    ${OpenCV_INCLUDE_DIRS})

set(LIBS ${InferenceEngine_LIBRARIES} ${OpenCV_LIBRARIES})

set(SRCS  ${PROJECT_SOURCE_DIR}/src/insightface.cpp
          ${PROJECT_SOURCE_DIR}/src/facedetector.cpp
          ${PROJECT_SOURCE_DIR}/src/baseface.cpp)

add_library(face STATIC ${SRCS})
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)


add_executable(feature_extract ${PROJECT_SOURCE_DIR}/demo/feature_extract.cpp)
target_link_libraries(feature_extract  face ${LIBS})

add_executable(face_detect ${PROJECT_SOURCE_DIR}/demo/face_detect.cpp)
target_link_libraries(face_detect face ${LIBS})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
