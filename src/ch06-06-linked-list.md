## Custom Search on a Linked List

### Instructions

In this activity, you must write a program in RISC-V assembly language that receives a number via STDIN, goes through a linked list and prints the index of the node where the sum of the two stored values is equal to the number read from STDIN. In case none of the nodes in the linked list fill this requirement, the number -1 must be printed.

<div style="text-align:center">

<img src="img/ch06_06_01.png" alt="linked list"/>

<span class="caption">Figure 6.6.1: Linked List</span>

</div>

For the linked list above, in case the input was 134, the number 1 (index of the second node on the list) should be printed as 56 + 78 = 134. If the input was a number that is not equal to the sum of any of the nodes (e.g. 8), -1 should be printed.

### Input

An ASCII encoded decimal number on the interval -10000 and 10000.

### Output

Index of the node where the sum of the two stored values is equal to the received value, if it exists on the linked list, -1 if it does not exist.

### Examples

Example of data.s file that will be linked to your program:

```riscvasm
.globl head_node

.data
head_node:
    .word 10
    .word -4
    .word node_1
.skip 10
node_1:
    .word 56
    .word 78
    .word node_2
.skip 5
node_3:
    .word -100
    .word -43
    .word 0
node_2:
    .word -654
    .word 590
    .word node_3
```

| Test Case | Input | Output |
| :-------- | :---: | :----: |
| 1         |   6   |   0    |
| 2         |  45   |   -1   |
| 3         |  -64  |   2    |

### Notes and Tips

- The head node of the linked list is stored on the address marked by the label head_node (DO NOT use this label on your code).
- The fields of the linked list node struct are VAL1, VAL2, and NEXT, in this order. VAL1 and VAL2 are 32-bit **signed** integer values stored on the node and NEXT is the pointer to the next node on the linked list. If there isn't a next node, it will be a NULL pointer.
- To check if the received value is on the current node, the comparison VAL1 + VAL2 = received value must be made.
- A NULL pointer is represented by the value 0.
- The indexing of the list nodes starts at 0 (i.e. the head_node has index 0), and the linked list will have up to 1000 nodes in the test cases.
- All nodes will have different sum values.
- You can test your code using the simulator's assistant from this <a href="https://riscv-programming.org/ale/#select_url_content=TjRJZ3RnaGdsZ2RnK2dCd2djd0tZZ0Z3aEFHaEJBWndLZ0lCY0laUzRDQmpBSnlnVk14Q2pBUUhzN1NBQ1lBVlFDU2NBQktvQU5nbFIwY1BBSUpFUzVTbkFESzlScVFDK1BBR1owT1lIZ0IwUUFPZ0QwWURnQk1BcnVOUUVMaFltUXFrekFLd0tuak1OazV1UGdBWkRob0ljUUFsVkNEdFBRTWpVMHRyZTBkbkdnNFlHRlFhVWlnczcxOFFBRzUtUUs1ZVlCNWlNQWNJVWk0NFRNb0RjVWM2SGgxOVF4TnpLMXNISnd0YStzYTZJdE15bUg4YWNWY2VBRkVBRHdBMk9GV2VWR1hTVkJnYkFubEZkeFYxQmlaZ2Z4NGVGckk2T3p5dUFBb0FTa3VZYSt1Q095azZWK25QanhTQUFMRWhtT3hRSGdBWGg0T1FBN2p3aEtJSkw4bnFZVnRJYUNSVUR4Vm1aVmhnZUFCaE94a1hxcVZBUU9nMFlFOExJOENBOEVLd0FEV3FCc1RLVXBoZTAyTXBIOGZPdWpsNGRGaWxXaHNOUUNMQ0VXaVl1NC15dW54QllKYU9UeUJSZ0JETUNGSndLZW9yaVBLVlF0UXZIRXJQWmNBdFpBbEt1MWFCeWRBYXFHdGxwc2JySWNCZ3RpY2lvK24yRlBCc0RRZ2NBQVJ1SU9PR0FjclFkcUlXWUlEWVBic3lHaUE0RFRFVERBZ29QTjhsbFREZ1RaOUNBQlBHQTBIaHdhRUFQajRwY0Joc3FabEY3Z1Z4c3pnT0RvWWpVZkRkdmpTWlRjR2QrME1jQkQ1Q2VGcGdiSTlOdElBRzBBQXdBWFM3UGJqWUpzcUYwRUFjVkYwK2IyRURBT0poRURoMEY0OXJNbVhZcCthdnY5Mit1OThUVWVRVDN2WkJzSEIyS1FBQkNkaTZMbzBnOGlZM2FBcCtVQm1OK3Y3RHYrMGgwS0I0R1FTVTBIdmtDdzdmbkFnR2tMcXBCdnUrOTc0YkF4RndDZTZTa2R1VUM2RWh1NzdvZTRqSHFlTURucWdMdzhLS3BCMkhRSHlrUGNxQ3h0dWZFQ1I4QjdpQVFvbE5wOFdpeU1BQjc1bkFsSjBPSTVhRXNKZGlvRm84bGJwOHBad1NPcVpPQ1I4bW1BQUt1WlBBQUl3OEU4QUNPdWxrSnFMekZ2SmY2Qkk0YWt1WkVVQ2tPV2NCcGhaTUZHU0FxekdBS3VEeWRjcGlydEZNeXhlRjF6VkkrU0NpdFJkaFZvV01DRWs4RUE0T0dQRlFnMkVCbU1KYkN2TkNNTGhwVkRCZ0RWK25oUjUzYUdSK3c2SnNtWm5wcFpJQTJiYUFCTWprdWVaN21lZUYzbnNMNXFEK1JhUVVoZVpHWTRhWUFBc0FDc1NXVGF0SUFBTFIyZHRLVTRlbHVaVXE2dWc1UnFXUUZVVkpYMWd5RFhWYVZkVlBVMVBFdGR1YldBaDF1Rmd0MW82aFN0UGJXYlpBRE1vMnVYbEhuSFQyMDBJTE44MkJjRlFOeFgwZTJyR3RSMGxxbGZSRGRqYU9uZXc1M1pibG1xM2NWcFhsVzlOVlFxOVZYdlYwQm1sbDJwYTZGd2psQnBDTUpyVmhrSUFEd3duWnE1OHdBMUtMUEh2TnVRYmpnQllCTGJhTUwzbzYwZ3VnckpGemd1bm9yblptNWlUdUNid1QxNnZBOXVBQUdnMjhBQUpNQVVCYUdiT000ZkRpTjJBRmkybzdqMXl5NU9vVnJ1dWpzNGJ4RkJ5K3J5NjZ3SEowWlNUbDFremRqbDNWVGowTTdUOU9OYThuMkI5OTc2LVJueGxkZkJKNmNlSVk1T0VlRXExbVZqYmhTMjNCdHZLSzZtS0ZKZmZHeHhUcmtPLTN3VTM3WkhnUSt1bXJ3eURPbnVFb2ktSkRHT1NaM2VsNjNmczhBQWhEQ3E2UzJqUWJ3S0ZoeEstbmxYbWMzdmNJWHN5QWdtajdPZExPWm84Tno5bDh6dy1Pd3VyZmVYK0xLK2V6d1EtSmppb3RiNTNPOWVqM3M5UUhYUDNCU2FOMzRqeGhFOE1CT0lBQlU5bGw0OEFzSTVkZTVrQ0FIVit0Y0RPelo2NTF6aU11VXdoZElod0NnYVlkdU1Jb0hBUGtoWVJCY0pZQUFUaERxYzZsQWRRY0RJQUFXU2NBUUZBcUFuakFFZkJlU2cybHQ3VHhicVFBZ3Nnb0dFaWdiSVF1SkJnVHEyMGlKTFE2Q2VCQmtqTkdDVU5kUEFxMmRMc0V1Y1E2S2ZBa29KSGdac0FEaXc5VUNFaHRsQXJRWmdlQUFCRU9Cd2hnRkdaTVBCeXlBVTZLRlhpOWNFaTlBVUc0WlF2QnRpNUNBcHFXK2pKZ1NpbDBGQ0cyTkNKejBQNEZFRUlENVJRdWdBUExoaThMa1VnU1NRaFBEVVNWSFFkQ1hFY0dURkNVdzJ4MWg0azBhWU9zVHc1aFFCb0N5SGd3SnBEY1g1aTRPc1pna29BRTFBSTNBb0F5R1NIQmd4T05LVzRrRU9KcHlNaG9qaUVFRFFlQTNrT0pyZGtRSlJrZUlFandCQUJoMzVHSDVwRTZKc1RnRHhMb1dZUEpxVEtTN0V5ZGt2SWVTbmd6UDdOR0Y0eFR4bXVKc0JVa0FNeXpERkhxVzAwVUx4T2tRRzZXYlVzR2NXcEtnSU1DTUN1aEhDRlRvTTZjc2J4c0tmRlBwekMrVjhxU0lvUGpBSSt0STlyWDB2andCc0l0TDU3VDJwTEZGZ0piaThDOEJLVmhEUmdSbUZoUndaNERLUVJ0bURvWUdxc0NuaVFsRnZaRjRVRjVMTGl4UkFjc3k1QUd5REZSS3J3NjVTRThGRlFpOFZ5NDVYU3VWUkt3QlFDcVZkQjFVWWo0TXFzSktpMEx5QU0yaTFhck1YRW9iMHZvQ0N2Q2xvR0MralJ5REZ4OUh1VGVmMXRTeTFnQ1JZV3E1WkJEVlhNdmZXYTlmUndCbFJLUEI0VlRCdE9URGF2Y0dBa3BtRGhGd0Rrd3NrMHByb0J5UGFXTi1ESnRUYkNNTmgwWW9Sd2ltNjEwZGxFMTVzelJ5RGFVVnEwRm9BT3dBQTRNMEZ2TFhBZkdKYitvZHFHbFdtQSthczA4QXhodFhOQTZhMDhBMmdBVGtTZzJvZEhhd1lFMmpTQUJkLWJCM1pyOVcyb2RPYkYxem81QjJzZE8xUGhBTkxFR2I0OHNBQnVrUmRLeUVjTG9LZ1Y3eEM2UkRSZmJZU2hZRElEZ0krMXlrYlZpeURzbUROYXNnTVpBZUhYWk5hWU1UM2RqUmVmWGdWOWVaRXJ2czZ3aDViSDVRR2ZnNndFQUVxNDRYUFYrNjlsNVBXY3YyRDZwNEIwZzFCdi1SUjROOGtkQndsQkk0UnliNjNLNHZ3MCtwd1poWUJ6RHNPNnA0ZUh2M2NSNEFBSHlFelVPd2w2Q08xUjRKdEtDQ0RFR2JVdm9jUmtZMDNMMG0yT2VCR3FCNUxNZnlLeGdUMnBkUlFyNCtKdGp1bGxGM29mWko3K1hyZzZrZkl4UnFqRkh6TVh4eURzZU5oR0JickpkZTV3NEJLSElBSDRURWRwdHVodXk5c2VDRWdTbE1lU0hhWlU2ajFFOE0yd1hiWmFEWFJPbTJGblRONlMzUnlHMi1ISk1Fc3l3Si1TZTZlQTIxYzFRY3RKV1lCbXh6cVdXTEdxTzdhaWhUQ3VGRFhFVy1YMVlxOXI0clpBNlktVmxnZ1VHTUVDZ0RNYmIyOHNabFBCNjBpekROd3NpMmt5T0F2b1poa0FEbkVLMHlrSHB5MUpwbVVkSGdBcVp2ZUE0TEFORUlCdVF2dDRETWlVOEllQTJSMklzS3N2by1pbUNBcm9QYXJhUUF2RE1Ic0piM0MtdS1WVVFPRzdVb2VEQVFIRThaY016LVo4Q0NsSVNMK0FFQUl5YVEwVFVGaHdpN0ZJSHRPNGxJd0NtQ1VaZHZRcDRRY0lnQUdLbmtoNFVtSHBodm5GRitxTUFzVFFXakNRNE8wYVFDRXluYmFsTlJDbmN6T3Rta2tqd1Fwc1lJVUJtOVpRSjRZQllDeUVnTXNGK1dEK0xHUFpVeWxsYkxHWEVibGp5eHlzdmgwOENseDhBVmRraFVIYjE3QUVYbzNyam10MFVEZnJlbUNNRUhsNDYzZzdNY29jbXN4cjBqLXFlQmcwQnhmUjlzaGFIYkgxaFBKNEx2OWhTZVhuTjY0Z2ZsZ1NnT3NBN0RVZlBpUHFheDdpWDluS053S2M4QXVqREdjUlBGdDUrLVRuR3F4UHQ0NCtvVitzZEFTRmtqaG5zTWVKUkVmRnlSTDNoZkJzNHJ4Y29sUE1JMi02Y2xmc2JZdzJRSGRpNWpBWWlFb3pZMjBmZFZzMmhQQ0xqNWhKUDIyQS1sZ3otMWwxLXZ4RlpEejZBa1BscW92YnNyR3FmOFhBSUFXZ25tUUpnVUFIQW1DYWdJRmZzLVdRTDl3QklCQU9RbUFkS29Ed09mcUFuN1g5RWcteEVtLXlmMS14ZjA0WHNVQUp2VWZ4Z0dmMWYxSjBnSy0yZ05nTTRVRUFRT0FKZ05BTmYxWVRRS1FNd000VlVCd0otei0wNFg0QndMUEVqRmRBSUE0R2FEYVdhWERBNEdXQndLb09vSElHYVVRQk8wb0drQ3l4WUZYR1dFYlZKd0VJRUlBTHdCOVdvbEZDY2pIQW9EUUJZQ0dnMmhBRVVoQUFJSExGb0VpQmtpdndVTDNBdlNhU2NIVUswQzBDQUE=" target="_blank">link</a>.
