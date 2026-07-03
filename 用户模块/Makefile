# 目标可执行程序名
TARGET = trade.exe
# 所有C源文件
SRCS = main.c user.c
# 自动生成.o中间文件
OBJS = $(SRCS:.c=.o)
# 编译器
CC = gcc
# 编译参数
CFLAGS = -Wall -g

# 主规则：生成程序
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# 通用.c转.o编译规则
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 一键运行程序
run: $(TARGET)
	.\$(TARGET)

# 清理编译产生的垃圾文件
clean:
	del /f $(OBJS) $(TARGET)