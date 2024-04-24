# 设置静态库名
SET(LIB_NAME common)
# 源文件
FILE(GLOB_RECURSE SRC "*.cc" "*.cpp" "*.c" "*.h" "*.hpp")
# 生成静态态库
ADD_LIBRARY(${LIB_NAME} ${SRC})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRC})


