cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME Yolov8OnnxRuntimeCPPInference)
project(${PROJECT_NAME} VERSION 0.0.1 LANGUAGES CXX)


# -------------- Support C++17 for using filesystem  ------------------#
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


# -------------- OpenCV  ------------------#
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})


# -------------- Compile CUDA for FP16 inference if needed  ------------------#

set(USE_CUDA OFF)

# -------------- ONNXRUNTIME  ------------------#
# 设置ONNX Runtime库的路径  
set(ONNXRUNTIME_DIR "${CMAKE_SOURCE_DIR}/onnxruntime-linux-x64-1.17.1")  
set(ONNXRUNTIME_INCLUDE_DIR "${ONNXRUNTIME_DIR}/include")  
set(ONNXRUNTIME_LIB_DIR "${ONNXRUNTIME_DIR}/lib")  
# 包含ONNX Runtime的头文件  
include_directories(${ONNXRUNTIME_INCLUDE_DIR})


set(PROJECT_SOURCES
        main.cpp
        inference.h
        inference.cpp
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} "${ONNXRUNTIME_LIB_DIR}/libonnxruntime.so")



configure_file(coco.yaml ${CMAKE_CURRENT_BINARY_DIR}/coco.yaml COPYONLY)

# Copy yolov8n.onnx file to the same folder of the executable file
configure_file(yolov8n.onnx ${CMAKE_CURRENT_BINARY_DIR}/yolov8n.onnx COPYONLY)

# Create folder name images in the same folder of the executable file
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/images
)
