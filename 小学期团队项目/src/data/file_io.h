#ifndef FILE_IO_H
#define FILE_IO_H
#include "goods.h"  

// 商品数据文件路径（统一路径，便于配置）
#define GOODS_FILE_PATH "./data/goods.txt"

// 从文件加载商品到链表（无返回值版本，兼容原逻辑；如需返回状态可调整为 int）
void loadGoodsFromFile();

// 将链表中所有商品写入文件（无返回值版本，兼容原逻辑；如需返回状态可调整为 int）
void saveGoodsToFile();

#endif