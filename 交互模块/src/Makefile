CC = gcc
CFLAGS = -Wall -g

# 全部源码
SRC = main.c \
src/data/user.c src/data/goods.c src/data/collect.c src/data/comment.c \
src/service/inter_service.c \
src/view/inter_view.c

OBJ = $(SRC:.c=.o)
TARGET = trade

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

# 自动匹配头文件依赖
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(TARGET)