CC = gcc
CFLAGS = -Wall -g -std=c99
TARGET = trade.exe

SRCS = \
src/main.c \
src/data/log.c src/data/user.c src/data/goods.c src/data/collect.c src/data/comment.c src/data/file_io.c \
src/service/admin.c src/service/user_service.c src/service/goods_service.c src/service/search.c src/service/inter_service.c \
src/view/admin_view.c src/view/user_view.c src/view/goods_view.c src/view/search_view.c src/view/inter_view.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	.\$(TARGET)

# Windows 安全清理，分步删除避免路径冲突
clean:
	if exist *.o del *.o
	if exist src\*.o del src\*.o
	if exist src\data\*.o del src\data\*.o
	if exist src\service\*.o del src\service\*.o
	if exist src\view\*.o del src\view\*.o
	if exist $(TARGET) del $(TARGET)