#ifndef FILE_IO_H
#define FILE_IO_H
#include "../goods/goods.h"

#define GOODS_FILE_PATH "./data/goods.txt"

int load_goods_from_file(GoodsList head);
int save_goods_to_file(GoodsList head);

#endif