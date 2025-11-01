cmake_minimum_required(VERSION 3.20)
project(myapp LANGUAGES CXX)

add_executable(your_app_name
    src/main.cpp   # 你的源文件
)
set_target_properties(your_app_name PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}   # 统一输出目录，方便上传
)
