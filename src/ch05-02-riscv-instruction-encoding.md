## RISC-V Instruction Encoding

### Instructions

Write a C program that reads a string with a RISC-V instruction from STDIN, parses its content in a way of obtaining its fields, packs the instruction's fields in a 32 bit value and writes the hexadecimal representation of the instruction to STDOUT.

The code snippet below can be used to compare strings as standard C libraries such as string.h are not available in the simulator. It is similar to string.h's strcmp but it has the number of characters to be compared as a parameter.

```c
int strcmp_custom(char *str1, char *str2, int n_char){
    for (int i = 0; i < n_char; i++){
        if (str1[i] < str2 [i])
            return -1;
        else if (str1[i] > str2 [i])
            return 1;
    }
    return 0;
}
```

The set of instructions that need to be encoded by your program is presented in the table below, alongside its opcode, instruction type and other fields (e.g. funct3 and funct7) if applicable.

| Instruction |      Inst Syntax      | Inst Type | OPCODE  | FUNCT3 |  FUNCT7   |
| :---------- | :-------------------: | :-------: | :-----: | :----: | :-------: |
| lui         |      lui rd, imm      |     U     | 0110111 |  N/A   |    N/A    |
| auipc       |     auipc rd, imm     |     U     | 0010111 |  N/A   |    N/A    |
| jal         |      jal rd, imm      |     J     | 1101111 |  N/A   |    N/A    |
| jalr        |   jalr rd, imm(rs1)   |     I     | 1100111 |  000   |    N/A    |
| beq         |   beq rs1, rs2, imm   |     B     | 1100011 |  000   |    N/A    |
| bne         |   bne rs1, rs2, imm   |     B     | 1100011 |  001   |    N/A    |
| blt         |   blt rs1, rs2, imm   |     B     | 1100011 |  100   |    N/A    |
| bge         |   bge rs1, rs2, imm   |     B     | 1100011 |  101   |    N/A    |
| bltu        |  bltu rs1, rs2, imm   |     B     | 1100011 |  110   |    N/A    |
| bgeu        |  bgeu rs1, rs2, imm   |     B     | 1100011 |  111   |    N/A    |
| lb          |    lb rd, imm(rs1)    |     I     | 0000011 |  000   |    N/A    |
| lh          |    lh rd, imm(rs1)    |     I     | 0000011 |  001   |    N/A    |
| lw          |    lw rd, imm(rs1)    |     I     | 0000011 |  010   |    N/A    |
| lbu         |   lbu rd, imm(rs1)    |     I     | 0000011 |  100   |    N/A    |
| lhu         |   lhu rd, imm(rs1)    |     I     | 0000011 |  101   |    N/A    |
| sb          |   sb rs2, imm(rs1)    |     S     | 0100011 |  000   |    N/A    |
| sh          |   sh rs2, imm(rs1)    |     S     | 0100011 |  001   |    N/A    |
| sw          |   sw rs2, imm(rs1)    |     S     | 0100011 |  010   |    N/A    |
| addi        |   addi rd, rs1, imm   |     I     | 0010011 |  000   |    N/A    |
| slti        |   slti rd, rs1, imm   |     I     | 0010011 |  010   |    N/A    |
| sltiu       |  sltiu rd, rs1, imm   |     I     | 0010011 |  011   |    N/A    |
| xori        |   xori rd, rs1, imm   |     I     | 0010011 |  100   |    N/A    |
| ori         |   ori rd, rs1, imm    |     I     | 0010011 |  110   |    N/A    |
| andi        |   andi rd, rs1, imm   |     I     | 0010011 |  111   |    N/A    |
| slli        | slli rd, rs1, imm\*\* |     I     | 0010011 |  001   | 0000000\* |
| srli        |   srli rd, rs1, imm   |     I     | 0010011 |  101   | 0000000\* |
| srai        |   srai rd, rs1, imm   |     I     | 0010011 |  101   | 0100000\* |
| add         |   add rd, rs1, rs2    |     R     | 0110011 |  000   |  0000000  |
| sub         |   sub rd, rs1, rs2    |     R     | 0110011 |  000   |  0100000  |
| sll         |   sll rd, rs1, rs2    |     R     | 0110011 |  001   |  0000000  |
| slt         |   slt rd, rs1, rs2    |     R     | 0110011 |  010   |  0000000  |
| sltu        |   sltu rd, rs1, rs2   |     R     | 0110011 |  011   |  0000000  |
| xor         |   xor rd, rs1, rs2    |     R     | 0110011 |  100   |  0000000  |
| srl         |   srl rd, rs1, rs2    |     R     | 0110011 |  101   |  0000000  |
| sra         |   sra rd, rs1, rs2    |     R     | 0110011 |  101   |  0100000  |
| or          |    or rd, rs1, rs2    |     R     | 0110011 |  110   |  0000000  |
| and         |   and rd, rs1, rs2    |     R     | 0110011 |  111   |  0000000  |

<span class="caption">\* slli, srli and srai are type I instructions but its immediate takes up only 5 bits, the remaining 7 bits are filled with a funct7 value.</br>
\*\* The imm field may also appear as shamt, which stands for shift amount.</span>

### Input

- RV32I assembly instruction string with at most 40 bytes. There will be no pseudo-instructions, the registers will be referenced with their x-name (e.g. x2, x10), and immediate values will be in decimal.

### Output

- The 32 bit encoded instruction in its Big Endian hexadecimal representation (hex_code() from the previous exercise can be used).

### Examples

| Test Case |       Input       |   Output   |
| :-------- | :---------------: | :--------: |
| 1         |   lb x10, 4(x9)   | 0x00448503 |
| 2         | and x31, x20, x25 | 0x019A7FB3 |
| 3         | slti x12, x13, -1 | 0xFFF6A613 |
| 4         |  bge x7, x0, 256  | 0x1003D063 |
| 5         | jalr x1, -32(x9)  | 0xFE0480E7 |

### Notes and Tips

- This exercise depends on some things used in [Exercise 5.1](ch05-01-bit-masking-shift-operations.md), such as hex_code() and pack() functions, so it is recommended to do Exercise 5.1 first.
- You can use this [base code](https://github.com/discovery-unicamp/ale-exercise-book/blob/main/reference_code/ch05-02/base_code.c) as a starting point, or build your solution from scratch if you want.
- Refer to the [RISC-V Instruction Set Manual](https://riscv.org/wp-content/uploads/2017/05/riscv-spec-v2.2.pdf) to check how each instruction is encoded. Especially, consult the RV32I Base Instruction Set in Table 19.2, presented in Chapter 19. For information regarding the encoding of immediates, check Figures 2.3 and 2.4 in Section 2.3 .
- You can test your code using the simulator's assistant from this <a href="https://riscv-programming.org/ale/#select_url_content=TjRJZ3RnaGdsZ2RnK2dCd2djd0tZZ0Z3aEFHaEJBWndLZ0lCY0laUzRDQmpBSnlnVk14Q2pBUUhzN1NBQ1lIZ0tvQkpPQUFsVUFHd1NvNk9IZ0VFaUpjcFRnQmxlbzE0QmZIZ0RNNkhNRHdBNklBSFFCNk1Cd0FtQVZ3bW9DbHdzVElWUzVnRllFekFiaE1ZTms1dVBnQVpEaG9JQ1FBbFZGRFNYUU1qVXd0ck8wZG5TeG9PR0JoVUdsSW9QSjgtRUVDWUlKb0pOeDRBVVFBUEFGWTRBQ1llVkViU1ZCaGJBZ1VsRDFVTkJpWStJSjRlWEpneU9uc2lyZ0FLQUVvSm1DbXBnbnRwT2xYS3paNVNBQXNTYzNzb0hnQmVIZ0tBZDBFUmNTa1pKYk1tbVJvU1ZCNW04emFNRHhZa0kxQUJoQUMwQURVZUVKWnFSNWtVU2h0NmpCY3JaWU1nekNzRHBzbkx3NkFrdUx3YnZjZUpGb25GQ2R4OXBOTmljempNQ29pOGdSekFoN0FSamtzQ1lsc1VGYVZONmF6WUhNRnNVV2RkMW9jcG1ZSkJjeklDQU5wbU9pMk9Cc01CbU9SbUFSYXRJQUJnQWpJYWpjYXpBQmRIQUN6Wm1DQVhCQTBCVThaVWdWWHFzQ2EzQnBYVmVzejZvMm13MFdxMGJhVm1id3hKMHV0MGF2Vm1BQlNjWkF4c0RRWkFsdXRNcEFFWWtkQ2pLc043ckFjRG9iU1RRaVRLY0RTZjkrdURtYlNBQ05VQUJIZk91d3Vsb3RKZ0JDbFpOLXJOdnBBdGZyb2NPWmtiQlhiZEU3Ylc3dzc3dzZycHByUnJIMHFiRWxJTTduQysxSUNYQjVYUStQLW8zWVpBamJRdTVMODlqaS03dGRQYVJOYVl6NDV0ViszOWx2WFlmQjVIcStBNnJzdUpvWGhPVjVvTCttRE9nV2Q3N21rUUZtQ2VhYkhrT0g2YnJLamEzaHFkN2xtdXo1b1FhNTdwaUdXRWdCSXh5NFI2K0hEaFd3NjFvT3hGK3V1WkVOcktkdzBjV3BZRVl4VEV2bjY0SHNaK1dZU0kyTUZLdkJlRzhmUmhITVpXcEdZWmVWR1NYQkhaRm5SQjRNUWVUR2dXZTc3a1plQkE0YkIwYUZqSlpiRG1vTllnWUpJNUtVWmtHY3R4V2xwRFpqRjJTeERtR1J4SUFFRnhablNiUnNrSGg1dWxlYlpkWWlSUkVDMk9pZjczaDZmRzZRRytra2RGeW5PZHVVQ0pZaFpnNlNSQTcyUUdFRmZnUU9WcWVaQ0VBV2toV3NjVjNtZ1ZsWDZORnd1VkJScC03SlhKLUdOWXBtVk9WKzdWNWJWQlZydjFZR0RYNUZBSloxczQxVDEya1RRcFlHK2FKYVFWUklIVlNWMTg2Y2hBWUE3cjFxV1RhZDhtampGeGwwTnRlVUhVZEtWRmF0QmtYWTVma0VIUTBCM2NjaDNIY3RmWFBhK2JFUlhwWlZabkZ0aDVYUUFETVNheExaWjBaYTkwMGJXWTJ5bWJ0QzFkakRjTUk0RHJIUlNEVEZnNXRFZ1NGRHNQRHZEbm1JdzF5TWsyajI0VTdqTlA0eU93bXBhRFYzWmFRVlh3ZGpsTUh0VEVXMCt6VFY2U2pGRnRYbTgxN2pqVk40K2xLR2taenhQYytWTjNNd3JyTks4bXdNWldyTFZaaDlFQmEwTGl2MlcrVVdHME5XWmNHYmFUQ3dhVmFXeHpCdVhVYmFTelE3WmhPMEpvdkd1TFhNdGRvLUtma0s1eFFPWUVOd0QwWkJ2S2pJQ2drWUNCUUxVNHBWTGdEWndOY0FCOFVxYmp3UEpFdVlCSWVOU2ZJYlZNQks4M1FHd1IyZ0JRTURRY0M1T3dhZW9MSHppa0tzTkliYm8yb2Jmd2VqUUJJY0NvQkFOMEFKNkF2QzlnLUtIbjZWeE80ZW5LeUZ6Ui1GWGZ4MzVBQXEzYzhJYVBEZ2p3NGs4RXNMYnoyUVNJckZxRFlSOFE3Qk9PUGw4eEZBcEJUOXZQY05tSmpZOEkwSm81QUFCWWxpTkFBSnkzMzVGbkt1QnBHaitpQVVBZ0FITTBmVXNNb0cyMDJQd051U0FDUndEMFBZVkVHZEFSTEFnRGdSc2F3cmo1d2dPWWVFYkJWalhCdUkyR2hEQXdEME1YcHVXK1M4Y1NDalhwSFRlYW80N2YwVHZ2TWdQQU9nbjFtdWZTKzNjYjUzdzJnLUVJejlXejJEZmgtTCtDZEM1ZXo2UC1hR2hvNUNORGFQcWZSYlJtZ21IUVQtV0JSb3dIeUFBT3dBREVleG9NemhncVlXQ1U2VDA3dmd3aFNKaUdrUElYbkhnMURhR3NJb1l3NWhkQzFqc09sSnd3NHk4NlM4STNqSFFSR2pMd2lONE5EWStQQUtyRkNrVmZET3Q5b0diZ1VVLVR1eWpWR2YyU1JZeG1PU0FGdEgwWWFhR2Nod1JCbk1UQXYwalE3R2RJQUd6eUM2UTBzeHppTEZ1UFlCNHZCQkRtUXdGOFdRaWhWRHdraElZVHdKaHdTMkVOaGlac09KUEN6aUpLM3BVNFJCOGdHWk92RDhDK2VUWkdGT2xNVWhBU2pYN2JUVWJzelJrNDBELXhzZm9veFlqbWhkSUdYSWg1STRBSCttaGdBRVgxRjBweDN6QzdESndaNDhaUkR6NStKbVlFdVo5Q3JoaE9XWkUxWjFwSzdXZ2p0c2dSM2NVbVFUU2I4VEpPWTZDNUprWGtBcEdETG5YSlViY2lwZUtxblpoaUtTZ0JUVG9adEZBUkFyNTV5S0w2ZzZmVWZVU0Q5VDFCc2R5bHhmQnBqdU53VjRpWlV6LUdVSVJhaWhaU3lXRXJJMm1zcVltTFB4NGlPTjNkVXRoSlJkUDhLWVQ4ZWd1RG54bUtJeFVBQnJWQVU4NUFBRGNZanozTkR3RGdlZ2VBQUhsR3plRUtGNFhvdERuQkxBamlLT2VFeUNBckRXTUFCc09yUHA5Q01GLVNVRGRlZ3lBZ0QwZFJ0cjdVOENkWEtWQUd6NGxiS2pra2hsTUNBQUdoS0FBa3dCQkg2dDBDZkt0bWJ0Q2x2RmRTMHBOejM3MHAzakE2dXMwRTJDTVZQcVQyaHc0MjJEN2QzUlVob2gyWU1sU002VjBLZkd3dW1RRW9KcXJRbUxNUldpbUJHcjFuY0xwSHFxQXRnQURVaDdkMkx5eFFrcU9laFlBeEJMTTRSd3hJZUE1d1ZkR21CeGR1Q2x5cEtRRjBOYXk3M3ZLSzZtNDJLbzQtcnZkdUFndTdEZzZ1UUo5V3dQd2JqNmdnNXNLQUhyZzBYcG9YcTM5WUdCMnVvQUlUd2FqUllxWU9yNENDSUdJQnRESUh0aGdmTUU0R0F5QVRpRWYwT2FwWU9yTGczRU5NYXk0QUFlVzRYOXdNOENnTWVnajNiTmpRYmlqOFE5NUhDM29iSUxlcWpwQUNDS2lnT2FSRGh3b21hTEU3QnlVU3hOTS1BQUZTSDMxR3NTdzU4U1Bkd0lNMC1OYW1MRnZxOExabDBWNllBM3QweGFTVXVtY1FXSjFZMkNRSEEtNDNGcytZUnVxYjAyMmI3cG9tdTlnNjQ4RkxRQWNSZzZnUUVWYmRQYUhNRHdBRkhBN2d3QjgzRkhnVThPQ1JkMWFJMnoraERER0VVTzRGUXZBdWlGSHNCbkhnWEdJQThHT0FTUFFWd3ExM0ZnS091NDVnQkN4SENPWWVnRThlamV0OVVVWHI0UWxqZWQ4eXNYUVhXc3NjRGlsY013WFJXaHRBLVlrTXd1Y2xnMUNnRFFhMVRXWkI1cTQ2NFhPNWhTME5paVdlME1JN1lBOXpBTEFPUWtCR2pDZUhhZ1d1R3dBQ3lhYmpqbUQwRDU1WVgyVGlsMTdmTWd6U3dudVpQdXpBTlloNmVCUTdpVmQya2FBcUFqb1RUbXErU3drQ2tCNkhYT1FvYlk1VDJrQ3NGOWtHM3NDWmdPeVVnanJuWE9FbE1BYlF1NzBmT0ZMa2ZLVHJJYnVVQ1dHODlsK2FBcnZ4b01jYytXT2NmUTVKOUthSUJBZmdBSElZd2VpbHhnQ3h5SHo3NDQtdElCWlV1QkJTKzNadUpud29QUkp0NFJ6bnVieVRSSU9hRFlycFZuTmlTRWw0eDNYNWdOUUc3T0VicFl6VEJYSUl0NVlPcGhtemVlN2FHc0F6YlJWUGs4cDVLVXRqUXEzMjluTm9PUWtlYWQ2N0FLSElJcGJnK05nSkJBYTFpR0pmUzRXcFplWEZqN2VPN1o4RHZvdDNYZUdLUVhJQ3ZOaXJkVENqeDBZdkx2dWYrK0Q3QVVQTnh3OXg5emV6dzBNZWVCZDZ2ZzdqMDJoUUVEK1o2V2JRa0NZQXA0c1duaWVtZUd6WjU0REx2Y0dwODh3UHIwNzluczB5LU45cndKbERLdkNkd1p1Rkxuc1d1N2Z4Nkg4WVJ2Ty1PZmdpQWZxTUJYU3ZmQUtmeS1qb0FleEhCNXQ2Z1MtM2ZyOHQ4UzkwUjc4SzlFRXE5QlVhOVc4S2Rhc3c4STlnQW85ZTk5RXg5MmMyZys4VURyOGs5cDlVOTA4RjhOb2w4VjhFSjdwU0IxOU5FNjhyOVN3Z0NtODVBZWRnOXlDQUNpOGpoRGM3OWpjYUNXOUdNMjlZQ085NERFQys4ZUNLQzBEWThFQ3I4TlFzQ1o4Uk01OE04czlDQWM4NVpvWlNEQzVOOWI5UzlPYzk5ZzhvOE1sbENRRFdDZUJhREZjWUNIMU85aENBRG85a0RqREI4Sjh6Q05DeENjRDU5RU5ZTVI1NzBGZFB4MU1pNDN0SXNOZ2xNRERxZHU5elJhUXJzcGhidFk0T0E0Qkd4WUFsZ2MwNUF3aUZOaWRyUUlzb3NJaVlnZUJjNFVpZUFqTWFFT0ExQmFFNk1saC1jMlE0b3NqSjRlNW9pQ0E1QXBkOVF0ZHpBS3BkdFVCWGNTaUVjdzRwaGVnMFJPNVlnbGdyMUdoVUJiQWZDcjVZalB4NGlOaDhWTmdPaXVqRlEyaFhVR3hZY1ExVkJTQVFpd2lZQkVpVERHbGZodGNlQXBqZUVnalpqUWp3ajY4NUJtaFZqWWNSamJBSjAtQ05wMWl6aE5pNWlkaUtDOUVWakpqOUFvQk9qampCME1VY1FvbG1pN0JPNGhBbGhRMDVBamllam5BK2pTY3F0R2dhQUVnTTR5TjFJdG9Pb0R3UHBicGh3VFlPb1ZOR2lrTVVNdWd3U21Ba1JoUlVRNVJZTUNBZmk0UkkweGRYdDN0ejRMRWppeGpUak5GempzU3FBdGo1akZqQjhOUTlpMWdMRWFTSGNaaXJpRmpkaTdpWUZEakhqUmpKMDJTbUNMak9UdGp1U2JpV1RoU0tTWGoxVlQwNGozQ0VqNzROaXhTR1RDOFBRNUJEUi1jVFZOeDJUTGp4VEdUeDl2ZDlqN2lLU2hTemlSVGFUZ2lEVEVDcFNMU1pTcVNkMS1EYVFQallOMUIyaUJUdWpzMTQ4Z1RjUXlkR0RwaTZTdVREU0U5TlQtY0ZUU1NoakFpUFFxanRvd1N1YzVBYThkVHBROVRWVHJpVERiajlpZUJMQVRNc2l1QWZoWVJSUncxQVJaeEpRNkFDQU9oSkZLRC1NQ0Fnd0xUQXpyUzFTQkM3VGRTSGluaVRqN2lOUll5YWlsZ1hsRDV0VFRUUFRzTlhqblRReFhUTzRld1BTbmlBU0kxaVRUNS1UOWRpOTlTbXlHQ05URDVvWnQwQml5U05vTlJoeUxTdXpxajR6dmRFRURqTFNPU2d5YlRtemVUV3lHejZUMHlMRE16VHl6VEhURGhZY0R5NHphandEK3pUemR6SjFrelh5MnpSalpUWWszamFRWFRVUlBpNEFCQXB5dWlaemZTaU1GeWI4enpsejd6bWRtU3hFak1JeVBEdHpOeFl4NnlWU0x5VnlIeVd5VXpBTG5pWHllQUdpeHlJSzNUNHdZS3ZUZGQ0Sy1UZUFBeUNMR3pVTFF5eEZEUlZpdHlveWtNUFE5enFTQk1ZekR6YWpBRU1MVmlwZzN5Qkt3RUtLQUwzeWV6Yml1VStUa0sweUpTTXlTTFd5SFRWbDVTcWc5S3BnZ3RQcDAxa2xmaXNscEFhQVh0bUxuUk9DcWR2VGZDZ0RrY1N3UWM0QmRjbGdDQnpMc001QjNMQ2dUajgxV000UnhTOGNBcmpndWhkMGJLdzhxMVExZEJJcURDbTFkMCtkU0FCZHo1dkthQmZLNXlwZ2w5ZllGUjlEWk41aWdEeHk0QTJpVXJ1eWp5Vmc0TGJDcERGOFpDNnBzcVlGOGM4cmk4Q3J2alRMaXJSTGNpeXE3TGVpS3E4RE54TXFRQVBKbkRORjZyWUI4cWFMTzQxQTNMektTcmFqLWR5clo5Y0RwREpja0phcWhxQXFHcXp5Q3JKeldxUHoycTVxWUZKQ2VyeGRxcWRRVnJDNWhxTmhHcXhxb0xKckNocHJkck9yQVR1ckZxZmdFeFRyY0sxcVJyTHFXaTRBNkx0cWV6WnFIcUkwbnJyUUFpa05ncXVoSlIya3pBMWllQWNGSmRZUWU1enFxOFZnTWlzaUdBY2pEUkxjTWlCQUVCZGhRUVpEVmg4amJCQ2pxUXZ6eWl0ZGQwdHl2REtjZ3JaTVFyR2dZYXBjQmtwZGtUOUtlQkY0cnRTUW1oVnMrNHc1Y0FRQVpncjFrQk1CUUFPQk1TV1FSYUJhOGdoYjFRQ0FJQjVCTUE1NVVBOEJCYW9Ca0JaYUlCUVJGYjVobGFwYVlBWmFTQUlBQVZ0YjU0VmJwYTFhTmE3RVRiZGJWYjFiRGFoQnJhemI5YUxiRGFQdEhhOWFEYTVhMUIzYmJhTmFCQjNiZWdJQnZOTzRDQVFpQmRDaHJWR3dPQkdoM2JRN3FCeUE5dEVBT0Jic1pBWEthY1dBK1Y3Rk9sT2t0YThBZ2lEQld3bks2TjBBc0FURVFBWTktSXA1YUFZZ0pBQ0FSYUs3WU1IVWFpNjZNQjZkdEJ0QWdB" target="_blank">link</a>.
