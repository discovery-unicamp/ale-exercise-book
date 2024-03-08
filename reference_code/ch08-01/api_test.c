#define NULL 0

typedef enum Action { GoForward, TurnLeft, TurnRight, GoBack, End } Action;

typedef struct Node {
    int x, y, z; // GPS coordinates
    int a_x, a_y, a_z; // Euler Angles for adjustments
    Action action; // Actions to perform
    struct Node *next; // Next node
} Node;

void puts ( const char * str );
char * gets ( char * str );
int atoi (const char * str);
char *  itoa ( int value, char * str, int base );
unsigned int get_time(void);
int approx_sqrt(int x, int iterations);
int get_distance(int x_c, int y_c, int z_c, int x_t, int y_t, int z_t);
int strlen_custom ( const char *str );
Node *fill_and_pop(Node *head, Node *fill);


char buffer[100];
int number; // variable staticaly set by the assistant
Node node_0; // variable staticaly set by the assistant
Node node_1; // variable staticaly set by the assistant

void print_node(Node *node, char *str_pointer){
    int legth, has_next = 0;
    str_pointer = itoa(node->x, str_pointer, 10);
    legth = strlen_custom(str_pointer);
    str_pointer[legth] = '|';
    itoa(node->y, &str_pointer[legth + 1], 10);
    legth = strlen_custom(str_pointer);
    str_pointer[legth] = '|';
    itoa(node->z, &str_pointer[legth + 1], 10);
    legth = strlen_custom(str_pointer);
    str_pointer[legth] = '|';
    itoa(node->a_x, &str_pointer[legth + 1], 10);
    legth = strlen_custom(str_pointer);
    str_pointer[legth] = '|';
    itoa(node->a_y, &str_pointer[legth + 1], 10);
    legth = strlen_custom(str_pointer);
    str_pointer[legth] = '|';
    itoa(node->a_z, &str_pointer[legth + 1], 10);
    legth = strlen_custom(str_pointer);
    str_pointer[legth] = '|';
    itoa((int) node->action, &str_pointer[legth + 1], 10);
    legth = strlen_custom(str_pointer);
    str_pointer[legth] = '|';
    if (node-> next != NULL){
        has_next = 1;
    }
    itoa(has_next, &str_pointer[legth + 1], 16);
    puts(str_pointer);
}

void run_operation(int op){
    int t0, t1, i;
    // node_0 and node_1 are set by the assistant here
    
    Node fill, *linked_list = &node_0;
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
            puts(itoa(strlen_custom(buffer), buffer, 10));
            break;
        case 5:
            t0 = get_time();
            t1 = get_time();
            puts(itoa(t1-t0, buffer, 10));
            break;
        case 6:
            puts(itoa(approx_sqrt(number, 40), buffer, 10));
            break;
        case 7:
            puts(itoa(get_distance(node_0.x, node_0.y, node_0.z, node_1.x, node_1.y, node_1.z), buffer, 10));
            break;
        case 8:
            fill_and_pop(linked_list, &fill);
            print_node(&fill, buffer);
            break;
        case 9:
            linked_list = fill_and_pop(linked_list, &fill);
            print_node(linked_list, buffer);
            break;
        default:
            break;
    }
}

int main(){
    int operation = atoi(gets(buffer));
    run_operation(operation);
    while(1);
    return 0;
}
