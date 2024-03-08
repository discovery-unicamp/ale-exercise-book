.globl A_0
.globl B_0
.globl C_0

.data
A_0: 
    .word -16 # x
    .word 1   # y 
    .word 7   # z
    .word 0   # a_x
    .word 93  # a_y
    .word 0   # a_z
    .word 0   # action
    .word A_1 # *next
.skip 10
A_1: 
    .word 146 # x
    .word 1   # y 
    .word -1  # z
    .word 0   # a_x
    .word 93  # a_y
    .word 0   # a_z
    .word 1   # action
    .word A_2 # *next
.skip 5
A_3:
    .word 285 # x
    .word 1   # y 
    .word 210 # z
    .word 0   # a_x
    .word 91   # a_y
    .word 0   # a_z
    .word 2   # action
    .word A_4 # *next
A_2:
    .word 160 # x
    .word 1   # y 
    .word 205 # z
    .word 0   # a_x
    .word 2  # a_y
    .word 0   # a_z
    .word 2   # action
    .word A_3 # *next
A_4:
    .word 285 # x
    .word 1   # y 
    .word 8  # z
    .word 0   # a_x
    .word 181 # a_y
    .word 0   # a_z
    .word 4   # action
    .word 0   # *next

B_0: 
    .word -16 # x
    .word 1   # y 
    .word 7   # z
    .word 0   # a_x
    .word 93  # a_y
    .word 0   # a_z
    .word 0   # action
    .word B_1 # *next
.skip 5
B_1: 
    .word 135 # x
    .word 1   # y 
    .word -1  # z
    .word 0   # a_x
    .word 93  # a_y
    .word 0   # a_z
    .word 0   # action
    .word B_2 # *next
.skip 10
B_3:
    .word 148 # x
    .word 1   # y 
    .word 10  # z
    .word 0   # a_x
    .word 272  # a_y
    .word 0   # a_z
    .word 0   # action
    .word B_4 # *next
.skip 4
B_2:
    .word 284 # x
    .word 1   # y 
    .word -6  # z
    .word 0   # a_x
    .word 93  # a_y
    .word 0   # a_z
    .word 3   # action
    .word B_3 # *next
B_4:
    .word -11 # x
    .word 1   # y 
    .word 18  # z
    .word 0   # a_x
    .word 272  # a_y
    .word 0   # a_z
    .word 4   # action
    .word 0   # *next

C_0:
    .word -16 # x
    .word 1   # y 
    .word 7   # z
    .word 0   # a_x
    .word 93  # a_y
    .word 0   # a_z
    .word 0   # action
    .word C_1 # *next
.skip 4
C_1: 
    .word 135 # x
    .word 1   # y 
    .word -1  # z
    .word 0   # a_x
    .word 93  # a_y
    .word 0   # a_z
    .word 0   # action
    .word C_2 # *next
.skip 5
C_2:
    .word 284 # x
    .word 1   # y 
    .word -6  # z
    .word 0   # a_x
    .word 93  # a_y
    .word 0   # a_z
    .word 3   # action
    .word C_3 # *next
.skip 11
C_3:
    .word 160 # x
    .word 1   # y 
    .word 14  # z
    .word 0   # a_x
    .word 272  # a_y
    .word 0   # a_z
    .word 2   # action
    .word C_4 # *next
C_4:
    .word 160 # x
    .word 1   # y 
    .word 203   # z
    .word 0   # a_x
    .word 2  # a_y
    .word 0   # a_z
    .word 1   # action
    .word C_5 # *next
C_5:
    .word 19  # x
    .word 1   # y 
    .word 213 # z
    .word 0   # a_x
    .word 271  # a_y
    .word 0   # a_z
    .word 4   # action
    .word 0   # *next
