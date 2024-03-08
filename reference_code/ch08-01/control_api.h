/*
  Control Application Programming Interface
*/

#ifndef CONTROL_API_H
#define CONTROL_API_H

#define NULL 0

// Type Definitions
typedef enum Action { GoForward, TurnLeft, TurnRight, GoBack, End } Action;

typedef struct Node {
    int x, y, z; // GPS coordinates
    int a_x, a_y, a_z; // Euler Angles for adjustments
    Action action; // Actions to perform
    struct Node *next; // Next node
} Node;

// Global Variables
extern Node A_0, B_0, C_0;

// Control API functions

/******************************************************************************/
/*  Car Peripheral                                                            */
/******************************************************************************/

/*
  Define values to vertical and horizontal movement of the car.
  Parameters: 
  * vertical:   a byte that defines the vertical movement of the car, between -1 and 1.
                -1 makes the car go backwards and 1 forward. (Engine)
  * horizontal: defines the vertical movement of the car, between -127 and 127
                Negative values make the car go to the left and positive to the right. (Steering Wheel)
  Returns:
  * 0 in case of a success.
  * -1 if any of the parameters are out of bounds.
*/
int set_engine(int vertical, int horizontal);


/*
  Set the handbrake of the car
  Parameters:
  * value:  a byte that defines if the brake will be triggered or not.
            1 to trigger the brake e 0 to stop using it.
  Returns:
  * 0 in case of success.
  * -1 if the value parameter is invalid.
*/
int set_handbrake(char value);

/*
  Reads distnace from the ultrasonic sensor
  Parameters: 
    None
  Returns: 
    * the distance detected by the sensor, in cetimeters, if an object is detected.
    * -1, if no object is detected.
*/
int read_sensor_distance();


/*
  Reads the approximate position of the car using a GPS device
  Parameters:
  * x: address of the variable that will store the value of the x position.
  * y: address of the variable that will store the value of the y position.
  * z: address of the variable that will store the value of the z position.
  Returns:
    Nothing
*/
void get_position(int* x, int* y, int* z);


/*
  Reads the global rotation of the gyroscope device
  Parameters:
  * x: address of the variable that will store the value of the Euler angle in x.
  * y: address of the variable that will store the value of the Euler angle in y.
  * z: address of the variable that will store the value of the Euler angle in z.
  Returns:
    Nothing
*/
void get_rotation(int* x, int* y, int* z);


/******************************************************************************/
/*  GPT Peripheral                                                            */
/******************************************************************************/

/*
  Reads system time
  Parameters:
    None
  Returns:
    System time, in milliseconds.
*/
unsigned int get_time();

/******************************************************************************/
/*  Utility Functions                                                         */
/******************************************************************************/

/*
  puts function from https://www.cplusplus.com/reference/cstdio/puts/ but in this 
  case it must use the Serial Port peripheral to perform writes.
  It prints a \n instead of the ending \0.
  Parameters:
    * str: string terminated in \0.
  Returns:
    Nothing
*/
void puts ( const char *str );

/*
  gets function from https://www.cplusplus.com/reference/cstdio/gets/ but in this 
  case it must use the Serial Port perifpheral to perform reads.
  Parameters:
    * str: Buffer to be filled.
  Returns:
    Filled butter with a \0 terminated string.
*/
char *gets ( char *str );

/*
  atoi function from https://www.cplusplus.com/reference/cstdlib/atoi/?kw=atoi 
  Parameters:
    * str: \0 terminated string of the decimal representation of a number.
  Returns:
    The integer value represented by the string.
*/
int atoi (const char *str);

/*
  itoa function from https://www.cplusplus.com/reference/cstdlib/itoa/ 
  Parameters:
    * value: integer value to be converted.
    * str: Buffer to be filled with \0 terminated string of the representation of the number.
    * base: base to use, either 10 or 16.
  Returns:
    Filled butter with a \0 terminated string.
*/
char *itoa ( int value, char *str, int base );

/*
  Custom implementation of the strlen function from https://cplusplus.com/reference/cstring/strlen/ 
  Parameters:
    * str: String terminated by \0
  Returns:
    Size of the string without counting the \0
*/
int strlen_custom( char *str );

/*
  Approximate Square Root computation using the Babylonian Method.
  Parameters:
    * value: integer value
    * iterations: number of iterations to perform the Babylonian method
  Returns:
    Approximate square root of value.
*/
int approx_sqrt(int value, int iterations);

/*
  Euclidean Distance between two points, A and B, in a 3D space.
  Parameters:
    * x_a: X coordinate of point A.
    * y_a: Y coordinate of point A.
    * z_a: Z coordinate of point A.
    * x_b: X coordinate of point B.
    * y_b: Y coordinate of point B.
    * z_b: Z coordinate of point B.
  Returns:
    Euclidean distance between the two points.
*/
int get_distance(int x_a, int y_a, int z_a, int x_b, int y_b, int z_b);

/*
  It copies all fields from the head node to the fill node and 
  returns the next node on the linked list (head->next).
  Parameters:
    * head: current head of the linked list
    * fill: node struct to be filled with values from the current head node. 
  Returns:
    Next node on the linked list.
*/
Node *fill_and_pop(Node *head, Node *fill);

#endif  /* CONTROL_API_H */