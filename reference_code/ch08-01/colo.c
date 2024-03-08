#include "control_api.h"

char buffer[200];

/* Prints log in the following format: ID <Target.x, Target.y, Target.z> (Car.x, Car.y, Car.z) [Distance] Timestamp */
void print_log(int id, Node* checkpoint, int x, int y, int z, int distance, char *str){
    unsigned int time = get_time();
    int legth;
    str = itoa(id, str, 10);
    legth = strlen_custom(str);
    str[legth] = ' ';
    str[legth + 1] = '<';
    itoa(checkpoint->x, &str[legth + 2], 10);
    legth = strlen_custom(str);
    str[legth] = ',';
    itoa(checkpoint->y, &str[legth + 1], 10);
    legth = strlen_custom(str);
    str[legth] = ',';
    itoa(checkpoint->z, &str[legth + 1], 10);
    legth = strlen_custom(str);
    str[legth] = '>';
    str[legth + 1] = ' ';
    str[legth + 2] = '(';
    itoa(x, &str[legth + 3], 10);
    legth = strlen_custom(str);
    str[legth] = ',';
    itoa(y, &str[legth + 1], 10);
    legth = strlen_custom(str);
    str[legth] = ',';
    itoa(z, &str[legth + 1], 10);
    legth = strlen_custom(str);
    str[legth] = ')';
    str[legth + 1] = ' ';
    str[legth + 2] = '[';
    itoa(distance, &str[legth + 3], 10);
    legth = strlen_custom(str);
    str[legth] = ']';
    str[legth + 1] = ' ';
    itoa(time, &str[legth + 2], 10);
    puts(str);
}

/* Absolute of a value */
int abs(int val){
    if (val < 0)
        return -val;
    return val;
}

/* Checks if angle is close in a 5 degree margin */
int is_angle_close(int a, int b){
    if (abs(a -b) < 5 || abs (a-b-360) < 5){
        return 1;
    }
    return 0;
}

/* Checks direction of angle adjustment */
int angle_adjustment(int angle, int target){
    if (angle - target == 0)
        return 0;
    if (angle < target)
        return 1;
    return -1;
}

/* Go to target braking in small intervals until reaches it inside a radius of 12 meters */
void go_to(Node* target){
    int x, y, z;
    int a_x, a_y, a_z;
    int brake = 0, no_brake_count = 0;
    
    get_position(&x, &y, &z);
    get_rotation(&a_x, &a_y, &a_z);
    set_engine(1, 0);
    set_handbrake(brake);
    while (get_distance(x, y, z, target->x, target->y, target->z) > 12)
    {
        set_engine(1, angle_adjustment(a_y, target->a_y));
        set_handbrake(brake);
        get_rotation(&a_x, &a_y, &a_z);
        get_position(&x, &y, &z);
        if (no_brake_count < 3){
            brake = 0;
            no_brake_count++;
        } else {
            brake = 1;
            no_brake_count = 0;
        }
        set_handbrake(brake);
    }
    set_handbrake(0);
    set_engine(0, 0);
}

/* Stops engine and performs a turn to left or right until car is aligned with target gyroscope angle */
void turn(int direction, Node* target){
    int x, y, z, old_y;
    int engine_on = 0;
    int cycle_count = 0;
    set_handbrake(0);
    set_engine(0 , direction*90);
    get_rotation(&x, &y, &z);
    old_y = y;
    while (is_angle_close(y, target->a_y) == 0){
        get_rotation(&x, &y, &z);
        cycle_count++;
        if (engine_on){
            engine_on = 0;
            set_engine(0, direction*90);
        }
        if (cycle_count == 4){
            if (old_y == y){
                set_engine(1 , direction*90);
                engine_on = 1; 
            }
            cycle_count = 0;
            old_y = y;
        }
    }
    set_engine(0 , 0);
}

/* Stops engine and turns back until car is aligned with target gyroscope angle */
void turn_back(Node* target){
    int x, y, z, old_y;
    int engine_on = 0;
    int cycle_count = 0;
    set_handbrake(0);
    set_engine(0 , -127);
    get_rotation(&x, &y, &z);
    old_y = y;
    while (is_angle_close(y, target->a_y) == 0){
        get_rotation(&x, &y, &z);
        cycle_count++;
        if (engine_on){
            engine_on = 0;
            set_engine(0, -127);
        }
        if (cycle_count == 4){
            if (old_y == y){
                set_engine(1 , -127);
                engine_on = 1; 
            }
            cycle_count = 0;
            old_y = y;
        }
    }
    set_engine(0 , 0);
}

int main(){    
    Node *next, fill;
    int time, x, y, z, id = 0, run = 1;

    /* Get route ID and load route's head node */
    int route_id = atoi(gets(buffer));
    switch (route_id) {
    case 0:
        next = &A_0;
        break;
    case 1:
        next = &B_0;
        break;
    case 2:
        next = &C_0;
        break;
    default:
        next = &A_0;
        break;
    }
    /* Pop head of linked list */
    next = fill_and_pop(next, &fill);

    /* Performs loop with go_to, print_log and action until last checkpoint is reached */
    while (run){
        go_to(&fill);
        get_position(&x, &y, &z);
        print_log(id, &fill, x, y, z, get_distance(x, y, z, fill.x, fill.y, fill.z), buffer);
        
        switch (fill.action){
        case GoBack:
            turn_back(next);
            break;
        case TurnLeft:
            turn(-1, next);
            break;
        case TurnRight:
            turn(1, next);
            break;
        case End:
            run = 0;
            break;
        default:
            break;
        }
        next = fill_and_pop(next, &fill);
        id++;
    }
    set_handbrake(1);
}
