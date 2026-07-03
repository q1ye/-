# 编译器
CC = gcc
# 编译参数：开启警告、标准C99
CFLAGS = -Wall -std=c99 -g
# 最终可执行程序名
TARGET = shop
# 所有.c源文件
SRCS = main.c goods.c file_io.c
# 自动生成对应的.o目标文件
OBJS = $(SRCS:.c=.o)

# 最终链接生成可执行文件（主目标）
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# 通用规则：.c 编译成 .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 清理：删除.o文件和可执行程序
clean:
	rm -f $(OBJS) $(TARGET)
# Windows系统如果用MinGW，替换clean为：
# clean:
# 	del /f $(OBJS) $(TARGET).exe

# 一键运行：先编译，再执行
run: $(TARGET)
	./$(TARGET)
# Windows MinGW运行命令替换：
# run: $(TARGET)
# 	$(TARGET).exe