#include "lib.h"

char buffer[100];

#define NULL 0

void _start(){
    int val;
    Node root_node, node_1, node_2, node_3, node_4, node_5, node_6, node_7;

    root_node.val = 12; root_node.left = &node_1; root_node.right = &node_2;
    node_1.val = 5; node_1.left = &node_3; node_1.right = &node_4;
    node_2.val = -78; node_2.left = NULL; node_2.right = &node_5;
    node_3.val = -43; node_3.left = NULL; node_3.right = NULL;
    node_4.val = 361; node_4.left = NULL; node_4.right = NULL;
    node_5.val = 562; node_5.left = &node_6; node_5.right = &node_7;
    node_6.val = 9; node_6.left = NULL; node_6.right = NULL;
    node_7.val = -798; node_7.left = NULL; node_7.right = NULL;

    val = atoi(gets(buffer));
    puts(itoa(recursive_tree_search(&root_node, val), buffer, 10));
    exit(0);
}
