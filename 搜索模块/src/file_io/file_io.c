#include "file_io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int load_goods_from_file(GoodsList head) {
    FILE *fp = fopen(GOODS_FILE_PATH, "r");
    if (!fp) {
        fp = fopen(GOODS_FILE_PATH, "w");
        if (fp) fclose(fp);
        return 0;
    }

    Goods g;
    while (fscanf(fp, "%d,%[^,],%[^,],%f,%[^,],%d,%d\n",
                  &g.id, g.name, g.category, &g.price, g.desc, &g.uid, &g.status) != EOF) {
        add_goods(head, g);
    }
    fclose(fp);
    return 1;
}

int save_goods_to_file(GoodsList head) {
    FILE *fp = fopen(GOODS_FILE_PATH, "w");
    if (!fp) {
        perror("open goods file write fail");
        return 0;
    }
    Goods *p = head->next;
    while (p != NULL) {
        fprintf(fp, "%d,%s,%s,%.2f,%s,%d,%d\n",
                p->id, p->name, p->category, p->price, p->desc, p->uid, p->status);
        p = p->next;
    }
    fclose(fp);
    return 1;
}
