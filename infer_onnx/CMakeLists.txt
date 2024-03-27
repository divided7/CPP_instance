cmake_minimum_required(VERSION 3.10)  
project(ONNXRuntimeExample)  
  
# 设置ONNX Runtime库的路径  
set(ONNXRUNTIME_DIR "${CMAKE_SOURCE_DIR}/onnxruntime-linux-x64-1.17.1")  
set(ONNXRUNTIME_INCLUDE_DIR "${ONNXRUNTIME_DIR}/include")  
set(ONNXRUNTIME_LIB_DIR "${ONNXRUNTIME_DIR}/lib")  
  
# 包含ONNX Runtime的头文件  
include_directories(${ONNXRUNTIME_INCLUDE_DIR})

# 添加OpenCV
find_package(OpenCV 4.5.4 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# 添加可执行文件  
add_executable(onnxruntime_example main.cpp)  

# 链接ONNX Runtime库  
target_link_libraries(onnxruntime_example "${ONNXRUNTIME_LIB_DIR}/libonnxruntime.so")
target_link_libraries(onnxruntime_example ${OpenCV_LIBS})

