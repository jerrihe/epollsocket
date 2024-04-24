# 服务器名
SET(EXEC_NAME client)

# 生成可执行文件路径
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}../../run/${EXEC_NAME})

INCLUDE_DIRECTORIES(.)
# INCLUDE_DIRECTORIES(server)
# INCLUDE_DIRECTORIES(../network)
# INCLUDE_DIRECTORIES(../common)

# 源文件赋值给SRV_SRC
FILE(GLOB_RECURSE SRV_SRC "*.cc" "*.cpp" "*.c" "*.h" "*.hpp")

# 生成可执行文件
ADD_EXECUTABLE(${EXEC_NAME} ${SRV_SRC})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRV_SRC})

# 链接指定库，目前只链接静态库
TARGET_LINK_LIBRARIES(${EXEC_NAME}
 libcommon.a
 libnetwork.a
)