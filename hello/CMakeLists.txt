cmake_minimum_required(VERSION 3.10)
PROJECT (HELLO)
SET(SRC_LIST main.cpp) # 添加源文件

ADD_EXECUTABLE(hello ${SRC_LIST}) # 生成可执行文件

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

# 添加OpenCV
find_package(OpenCV 4.5.4 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# 添加ONNXRUNTIME
set(ONNXRUNTIME_ROOT "/home/kiko/Desktop/onnxruntime-linux-x64-1.17.1")
include_directories(${PROJECT_NAME} ${ONNXRUNTIME_ROOT}/include)

# 静态链接ONNXRUNTIME库
set(OpenCV_STATIC ON)
target_link_libraries(hello PRIVATE ${OpenCV_LIBS})
set(ONNXRUNTIME_STATIC ON)
target_link_libraries(hello PRIVATE ${ONNXRUNTIME_ROOT}/lib/libonnxruntime.so)

# 静态链接标准库和其他系统库
#set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")
