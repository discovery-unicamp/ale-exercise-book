#include "lib.h"

char buffer[100];
int number = 635;

#define NULL 0

void run_operation(int op){
    int val;
    Node head_node, node_1, node_3, node_2;

    head_node.val1 = 10; head_node.val2 = -4; head_node.next = &node_1;
    node_1.val1 = 56; node_1.val2 = 78; node_1.next = &node_2;
    node_2.val1 = -654; node_2.val2 = 590; node_2.next = &node_3;
    node_3.val1 = -100; node_3.val2 = -43; node_3.next = NULL;
     
    switch (op){
        case 0:
            puts(buffer);
            break;

        case 1:
            gets(buffer);
            puts(buffer);
            break;

        case 2:
            puts(itoa(number, buffer, 10));
            break;

        case 3:
            puts(itoa(atoi(gets(buffer)), buffer, 16));
            break;

        case 4:
            gets(buffer);
            puts(buffer);
            gets(buffer);
            puts(buffer);
            break;

        case 5:
            val = atoi(gets(buffer));
            puts(itoa(linked_list_search(&head_node, val), buffer, 10));
            break;
        
        default:
            break;
        }
}

void _start(){
    int operation = atoi(gets(buffer));
    run_operation(operation);
    exit(0);
}
