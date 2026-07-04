#include <windows.h>
#include "common.h"
#include "linklist.h"
#include "stack.h"
#include "queue.h"
#include "data_io.h"
#include "menu.h"

LinkedList g_user_list;
LinkedList g_goods_list;
LinkedList g_comment_list;
Stack g_undo_stack;
Queue g_new_goods_queue;
User* g_current_user = NULL;

void init_system() {
    g_user_list = *list_create(sizeof(User));
    g_goods_list = *list_create(sizeof(Goods));
    g_comment_list = *list_create(sizeof(Comment));
    g_undo_stack = *stack_create(100, sizeof(int));
    g_new_goods_queue = *queue_create(10, sizeof(int));
    g_current_user = NULL;
    
    load_users();
    load_goods();
    load_comments();
    
    if (g_user_list.size == 0) {
        User admin;
        memset(&admin, 0, sizeof(User));
        admin.id = 1;
        strcpy(admin.username, "admin");
        strcpy(admin.password, "admin123");
        strcpy(admin.phone, "13800138000");
        strcpy(admin.email, "admin@school.com");
        strcpy(admin.name, "管理员");
        strcpy(admin.address, "学校");
        admin.role = ROLE_ADMIN;
        admin.register_time = time(NULL);
        list_add(&g_user_list, &admin);
        save_users();
    }
}

void cleanup_system() {
    save_all_data();
    
    list_destroy(&g_user_list);
    list_destroy(&g_goods_list);
    list_destroy(&g_comment_list);
    stack_destroy(&g_undo_stack);
    queue_destroy(&g_new_goods_queue);
}

void save_all_data() {
    save_users();
    save_goods();
    save_comments();
}

void load_all_data() {
    load_users();
    load_goods();
    load_comments();
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
#endif
    
    init_system();
    
    printf("欢迎使用校园二手交易平台!\n");
    printf("初始化完成，用户数: %d, 商品数: %d\n", 
           g_user_list.size, g_goods_list.size);
    
    show_main_menu();
    
    cleanup_system();
    
    printf("\n感谢使用校园二手交易平台!\n");
    return 0;
}
