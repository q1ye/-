# 编译器配置
CC = gcc
CFLAGS = -Wall -g -std=c99
# 最终程序名
TARGET = campus_trade
# 源码根目录
SRC_DIR = src
# 编译中间文件存放目录
OBJ_DIR = obj
# 数据持久化文件夹
DATA_DIR = data

# 自动查找所有 .c 源码文件
SRCS := $(wildcard $(SRC_DIR)/*.c $(SRC_DIR)/data/*.c $(SRC_DIR)/service/*.c $(SRC_DIR)/view/*.c)
# 将 .c 替换为 obj/xxx.o 中间文件
OBJS := $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))

# 主编译目标
all: dir $(TARGET)

# 创建目录：obj、data（不存在则自动生成）
dir:
	mkdir -p $(OBJ_DIR)/$(SRC_DIR)/data
	mkdir -p $(OBJ_DIR)/$(SRC_DIR)/service
	mkdir -p $(OBJ_DIR)/$(SRC_DIR)/view
	mkdir -p $(DATA_DIR)

# 链接所有目标文件生成可执行程序
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# 通用编译规则：.c -> obj/xxx.o
$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 一键运行程序
run: all
	./$(TARGET)

# 清理编译产物、日志缓存
clean:
	rm -rf $(OBJ_DIR)
	rm -f $(TARGET)
	rm -f *.log *.tmp

# 彻底清理（包含数据文件，慎用！）
clean-all: clean
	rm -rf $(DATA_DIR)/*.dat

# 打包交付（答辩提交用，生成压缩包）
pack: clean
	zip -r 校园二手交易平台源码.zip Makefile src README.md