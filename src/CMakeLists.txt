# cmake版本要求


cmake_minimum_required(VERSION 2.8.9)
# 项目名
PROJECT(jerri_server)
# 编译选项
SET(CMAKE_C_FLAGS_DEBUG "$ENV{CFLAGS} -g -DDEBUG ")
SET(CMAKE_C_FLAGS_RELEASE "$ENV{CFLAGS} -g -O3 -DNDEBUG ")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -std=c++17 -g -DDEBUG -Wall -Wno-misleading-indentation -Wno-sign-compare -Wno-reorder -Wno-unused-variable -Wno-unused-function -ffunction-sections -fdata-sections -fexceptions -Wno-unused-result -fsanitize=address -fno-omit-frame-pointer -fsanitize-recover=address -DOPENASAN") 
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -std=c++17 -g -O3 -DNDEBUG -Wall -Wno-misleading-indentation -Wno-sign-compare -Wno-reorder -Wno-unused-variable -Wno-unused-function -ffunction-sections -fdata-sections -fexceptions -Wno-unused-result")

INCLUDE_DIRECTORIES(after ${PROJECT_SOURCE_DIR})
INCLUDE_DIRECTORIES(common)
INCLUDE_DIRECTORIES(network)

# 指定库路径
LINK_DIRECTORIES(
 ../lib
)

# 生成库路径
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}../../lib)

# 公共库
ADD_SUBDIRECTORY(common)
ADD_SUBDIRECTORY(network)

ADD_SUBDIRECTORY(conn)
ADD_SUBDIRECTORY(client)
