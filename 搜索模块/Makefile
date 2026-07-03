CC = gcc
CFLAGS = -Wall -g
# 所有源码文件，包含search模块
SRC = src/main.c \
src/data_struct/linklist.c \
src/goods/goods.c \
src/file_io/file.c \
src/search/search.c
OBJ = $(SRC:.c=.o)
TARGET = trade_platform

# 编译生成程序
all: $(TARGET)
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# 清理编译缓存
clean:
	rm -rf $(OBJ) $(TARGET)