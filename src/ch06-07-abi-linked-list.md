## ABI-compliant Linked List Custom Search

### Instructions

In this activity, you must write a program in RISC-V assembly language that has a ABI-compliant function **int linked_list_search(Node \*head_node, int val)**, similar to the one implemented in [exercise 6.6](ch06-06-linked-list.md). Your code will be linked to a code in C that calls the **linked_list_search** function and expects the return value to be the index of the node where the sum of the values is equal to **val** or -1 in case there isn't such a node on the linked list.

In addition to **linked_list_search**, you will need to implement a few utility functions that will be required for this exercise and future ones. **There is no need to handle errors nor end-of-file (EOF).**

- <mark style="background:transparent;color:green">void puts ( const char \* str );</mark>

  | Description                                                              | Parameters              | Return Value |
  | :----------------------------------------------------------------------- | :---------------------- | :----------- |
  | [puts - C++ Reference](https://www.cplusplus.com/reference/cstdio/puts/) | String terminated by \0 | -            |

- <mark style="background:transparent;color:green">char \* gets ( char \* str );</mark>

  | Description                                                              | Parameters          | Return Value                 |
  | :----------------------------------------------------------------------- | :------------------ | :--------------------------- |
  | [gets - C++ Reference](https://www.cplusplus.com/reference/cstdio/gets/) | Buffer to be filled | Check function documentation |

- <mark style="background:transparent;color:green">int atoi (const char \* str);</mark>

  | Description                                                               | Parameters              | Return Value                      |
  | :------------------------------------------------------------------------ | :---------------------- | :-------------------------------- |
  | [atoi - C++ Reference](https://www.cplusplus.com/reference/cstdlib/atoi/) | String terminated by \0 | Integer represented by the string |

- <mark style="background:transparent;color:green">char \* itoa ( int value, char \* str, int base );</mark>

  | Description                                                               | Parameters                                                                                            | Return Value |
  | :------------------------------------------------------------------------ | :---------------------------------------------------------------------------------------------------- | :----------- |
  | [itoa - C++ Reference](https://www.cplusplus.com/reference/cstdlib/itoa/) | Check function documentation. Only bases 10 and 16 will be tested. The tests won't be case-sensitive. | -            |

- <mark style="background:transparent;color:green">void exit(int code);</mark>

  | Description                             | Parameters                                | Return Value |
  | :-------------------------------------- | :---------------------------------------- | :----------- |
  | Calls exit syscall to finish execution. | Return code (usually used as error code). | -            |

**lib.h**:

```c
typedef struct Node {
    int val1, val2;
    struct Node *next;
} Node;

int linked_list_search(Node *head_node, int val);
void puts ( const char *str );
char *gets ( char *str );
int atoi (const char *str);
char *itoa ( int value, char *str, int base );
void exit(int code);
```

### Input

Test Case index and specific input depending on the test case (check [example.c](https://github.com/discovery-unicamp/ale-exercise-book/blob/main/reference_code/ch06-07/example.c)).

### Output

Output according to the test case.

### Notes and Tips

- The **linked_list_search** function will receive the address of the head node on register a0 and the value being searched on register a1, and must return on the register a0 the index of the node, if found, or -1 otherwise.
- The fields of the linked list node struct are VAL1, VAL2 and NEXT, in this order. VAL1 and VAL2 are the **signed** int values stored on the node and NEXT is the pointer to the next node on the linked list. If there isn't a next node, it will be a NULL pointer.
- To check if the received value is on the current node, the comparison VAL1 + VAL2 = received value must be made.
- A NULL pointer is represented by the value 0.
- The indexing of the list nodes starts at 0 (i.e. the head_node has index 0), and the linked list will have up to 1000 nodes in the test cases.
- All nodes will have different sum values.
- Symbols must be set as global (`.globl` directive) for the linker to resolve undefined references.
- The character `\0` corresponds to the null byte, which has the value 0. However, using `li a0, '\0'` will lead to errors because the assembler interprets the value as the character `'0'` (which has an ASCII value of 48) rather than the null byte.
- You can test your code using the simulator's assistant from this <a href="https://riscv-programming.org/ale/#select_url_content=TjRJZ3RnaGdsZ2RnK2dCd2djd0tZZ0Z3aEFHaEJBWndLZ0lCY0laUzRDQmpBSnlnVk14Q2pBUUhzN1NBQ1lBVlFDU2NBQktvQU5nbFIwY1BBSUpFUzVTbkFESzlScVFDK1BBR1owT1lIZ0IwUUFPZ0QwWURnQk1BcnVOUUVMaFltUXFrekFLd0tuak1OazV1UGdBWkRob0ljUUFsVkNEdFBRTWpVMHRyZTBkbkdnNFlHRlFhVWlnczcxOFFBRzUtUUs1ZVlCNWlNQWNJVWk0NFRNb0RjVWM2SGgxOVF4TnpLMXNISnd0YStzYTZJdE15bUg4YWNWY2VBRkVBRHdBMk9BQjJIbFJsMGxRWUd3SjVSWGNWZFFZbVlIOGVIaGF5T2pzOHJnQUtBRW9ybUJ1Ymdqc3BPamZwbDhlS1FBQllrTXgyS0E4QUM4UEJ5QUhjZUVKUkJJLXM5VEN0cERRU0tnZUtzekJzTVBJQUVLQ0FDMG1YWTRpZ0hoNElWZ0FHdFVEWTZVb2VBQmhPeGtYcXFWQVFPZzBFR21WN1RZeWtmeGltNk9YaDBXS1ZHRncxQ0lzSVJhSnk3Z0E2NWZVSGdsbzVQSUZHQUVNd0lMa2c1Nnl1SWlyVlMxQzhha3dKazJPRFVzZ0tuWEd0QTVPZ05WQXV4bk0tMWtPQXdXeE9UV2ZMN1MyNWh1QUFJM0VIRGpzbXBjZmppYmpnS2pkcmhkakFjZWs3ckJ4cDlCMWdwR2VBRVlBQXkxbkFBVmxyMWV0a1p1SG9oVURNRUJzenIyWkhScmErcG5aaGdRVUhtK1N5cGh3TnEraEFBbmpBYUR3NERDQUh4OFdkQXkyVk15eTl3YWx0QW9HWkd4K2hOSm92Zzd2TzBzMlF4d0d3TkNEUEIxT29Pa0FEYTFZQXVpbUE4NnJwZnBXZjY1dm0waEhzZVVwUUdtRjV4bGV4bzN2NmNZUmxCYmJGbVlaNjZCQURoVUxvNDc3QkFZQzRyQ0VEd3RBdkR0cFNZNk9NMFlhb1doN2FRbVlpYklNODdaa1BlZGlrTVNkaTZMb0VFbENZZzVBa3huYXNleEdHY2RJZEM4ZnhnbkNXaHdJWWF4Y0FjTnhwb1ZwQlVIdHFwc0NhWEErSHBBeFVGUUxva25nbGhPSGlIaEJFd0VScUN2RHdzcWtIWWRDZktRRHlvRm1VRXVXNW56WWVJQkRlVnVYeGFMSXdEWWVPY0I4blE0anprU25sMktnV2loZHBpbmFoaHpGSVgyRmFoYVlBQXFUaThKV1BCa2h5aEM0dFcwNmhSeGdTMGFnQUNPZGlSRkFwRHpuQXVVRGtwcGpWUkt1Q2hUY3ZYR1AxTTRpVjgxVFVmeWZxNkhZUzZUakFSTFBCQU9CeGs1MEliaEFaaWVXd2J3d3JDY2JiUXdZQjdhbDQydkxPTGF6dEdFVEJYQXBXd3UyZDdsczgxYXlBQVRPbDBhY0lvQ1orcmRUajNRcW42bUhJUnJ3dElJMHpMZ2ZSZ3dRRU9kUENiVWdqVVNBMEU0VVBUbjBGRHc1RC1VLXJPWWxkajJuWEZkMXg2RmNWUER2V1ZGWEJUd2xZMWVOZFZVbjZUVXRkUzdXay0yZzA4QUFCb3otZ0FDVEFEOXhCLWMwbFVFUGRuNEEtZFA1YUh6WTFLV0xNRzBRRDB1VnJMbFh5OHJhR1RhTzAyR1hOQnBaRXRLMXJldVBCYlR0SjNyUWRSMjdVNVoxUVJkZzdwVVRPVmstbElCRlc2QURNdFBzcFYxTk16cFVuMVd6eld0VnpYVzg2WTcyWXdONDAzSHpJc3dIbUJaMEtsLWhLN3pCdnNFYnMzellhNXVyZXRtMk8zYiswOElkdHVuV2xsMmlvT25zazNINDJVMjZBQXNRY2gtN1lmSGl6Q0FOZEhuTWRlM1NsOC0zd3ZBQm40SFoxRGVjcC16SXZ0aUNPeDBXZXp4ejFucnc1ekFTOUtRWFNDeXNiSmRtend5M2wxYk52SFc4MjBjUHdDQi1NSHdWN2RDRHYxNjhEOVB5LWxVTitkSnVzNXJvNWpsajNSNkdGbnFVRmVoOUw2T1pWWVN3MW5BY0JQQVFZZ0FBQ0xxVCtsRGVrT1JmQ2pUNkpndXcyRC1DNEtjRHdKR29KVVlRSFJ2ZzZHc2hUQmNSSVRBQjBHTjhhRXl5cDJMMlBNTzYreXB2V1h1OU11NEQxRWhIVm1NVlI1dFhIdDdaZWZOaEV6d1FlcktXeUR0WjNTN2dyUSthRkZILVdVVjNWUmZwMUY2eWdzZkl1SnNGcGwwdGh0WlN1b3VTTkRBSFJRdXNvcjYxMmRvM2QyemRSSGdteW0zR1JVRk82OEZXSUkzRTlZUkdaWEJMVVllVWNPWlNPNW5sWmVwZ1FuK0ZXRW5JeEZNUUI5WG9mbkdNamlacG1OTHBmQzJGZHJaVjNmcC1PK3JqQUh1SWxDM1RoeE5leStMU1g3WGdXeHlxdjJDYUU5QzRUSTRTT2liSEJwZmlRQ0pKZ0YzSVpIU2h3Z0RKSUxUSnk4VEduMkxxYlJhQlRyNVdOdms3R3VkZHlsZERjVUNLNmc1ZEJjRXZ0R0tFc0lBQWNRa29RQUI1WVExbk9RQWFsdVU1RDRVRm94M2dmTGxCQ1pndlRTRjlMRTE4QUVQeWZuZWorZEtuVGpUZVBxVHd5ZVRTZUFpeWdEb1ZwSWQ2eWFQRGwwOFI3TVk3U01oVXBmbVF5UmF2UHNibGI4R2pVbStRb1BlQWx4VlB3Z1JKY2VZQVUwNWw1SXZsZlN4bGN2N3JKS1h2WG1OdzNaS1hTaTdES29LT3htSHd2WmNRY0I5eTRRVkt1S3hUemp3N200SHVkVVg1VEM1WEZVNFhDeFFmd2ZPWXFxaVZOa0NBK1d6THdaQVBvendLbXJJYW00WmxMNUUxMWVxLVZSS2VBQUVKWVROazNNdmFNOEJjcEhBZ1Y0enNkcWZqNnBZdnNaQW9KZWI3TTZLK0hNeHlHYm5KNEJjdUVzU0RVOENnUGN4NVhLZUFtdTdMaVc1dnF3WCt1S21xd05wQUNDZmlnRCtTMVlWZVpack5iQ1o0TmJjUUFDb0dadW9zSmZMMXhVQ0NUSkJWczhhOHJQRDlyUVNLeUljQUcybUMxYkNCdEhqandXRGJVakE0SEI0UW1tbXBRRTBIQXlBQUZrbkFFQlFLZ1o0ZExEREVVb0lsV3BBYU5XeUFiVVNCdHNnUlVrQkJMRXhLWGt0QTl1akhCQlUtYlBuN0crWHNOVmNRVEpmRDh1NWZtQUJ4VTFxQWlRaXdiVm9Nd1BCTUh3aFlSd2JzUEI1enFVNk84LXRDUmVnS0RjTW9YZ094Y2pjVU5QR2lBUEFRU3lsME5DRVc4Nzd4THY0RkVFSVpoNkI4ajJBQWVUakY0WElwQTZNaEdlSEJQZVBBYU1JZTdOQ1V3T3gxZ2JFVlhFVXdhNW5oekNnRFFCa3BIcENPUXVTNE5jWmdvWUFFMTFLM0FvTmJJS0hBQk9McUV5eVVFdUpjcXdHUURHTTFvSUdnVU1JRHdOOHpKZ1NHWlEyNUhnQ0FEQlpxTUJja2paSFVBVWFvN0FHalpodU9NZGxMNk5qSEc4amNkazdHUGpPaEJPSm1FeXE0cWxuR1BTZWVPdldVcnhWTVFIVTN6V2MtS3pwYWhvTFloODlLOTByUmNiSzIwZUhsaFNEeU01MGlaZ0NERHphczhBQTVGRFRyMzhqSjdIK004TnFxQWpCV09HMFlGMWZSaFJ3SmxQYTNnRHMydWN5NnoxdnI0NEJ2UENHM3NVYkc1eHZPdGhINEVBcngwcUFjK0RzUnJld2JEZUE0TEFaYi1oZXMxejFaNEx3MTJZQzNaZ0wxck1XaHAwRUJCSHhYUWpobHAwQjlQT2Q0QXE5QUhLamJ3R04tSmdmQnBnS0dsRzVWS3h4bzNCYWxOWkl5U1BMQnpjTzR2QXZBS2czUTBFRXdyRXd2RUo2Q1BjWkxEQjdXYlVObmd0eUdaSGFFcUZUOE1PSUR6akxhQk5uSE92QS1nbmFnN25uNWVleUVGK1dpdFlPZEN6aE85YklIN1BtZVJpKzlVbTQ2OWxpYnozUUFOMGlPOEVCdkE3Q2EtRUFxZlhhNWpjV3AxMHA1WUNvRHZUcHVCR3c1MGJ6VnhvVFdjbE5hYmF0R3V0bllDM3NJOWVSQjRBQVVnWnFzU3QxcmxxZTU0R3VhNXpaZVlxNFZLb0hhOFBoV0pIWkNDZmtJNHQ0NFF0MGo2czlPZUNkYmtKMXhqS2U2QnA5UUhJQ3N6WW5JTTVWNVdpUXdWbzg3RmotSDVBaWZEREo5VC1SRFBPZk92VmdMNEtkdlo0eSt2U096bjZ2b1VmY0c3cmVQMm1HZW5KdHNyRUgwS2R3T0NPQllod05pNCtlMGg2bngtSGd6WTNkQWpqQkZoa2xiSmVEbjVUY2FYbytGZEs4elYrbjBQNm5PQVNVQ0dNTUJBM2h1K2pJMGNnWXJReG5oOWRZa3NNbEY2R3NONmFtV3NHYkhnZlhCNlZCR3NXUWVzVllXUU1rVlllc0x1UkFrQWl0TTNmWEdtV0VUOE1rVkFuZ0RZRTVPQWdBVGxBTHdQOWdKa0hHakIrSHNYMTJTaFRBQ3lvRG9KQ2lvSnpCMkNVRXN6Z0dZUC0wLUFRSVpuOW53S1FNRU1yQzdnb01OVnQwaHhUUVZDN2tkeGMyLXhmei16dVFlWDN5TTNkU1Vob0s0TWlHU2crU2dRckVtU2JGQUpBUEFKUHdvVEJFY0V2bllMSUU0TzRMTUZnRG1Ec0QtMmVBME9ZS2NnQUI5WENhZzh4TkR4QnRDZDhSa1JRZUJaMGVBUmtVMGpnU05tbzBzc2h0aGxnaUpJbFFwTEQ4aDRkdkRrcGpSVFFmc25DdkNYREsxSEJkQW1DdENTSUFES2N5eG9GOUNteFpBakRteEswb0NUUXpRbzFjamtqSElxakloM29hajBqbkQ4amFZY2k4aWZER2lpc3BjN1ItSlVFb0RaQXNEWkFFanJEOGlDQU1EcjhaaEl3a0o4Vkh4bnhuaGhqSURtalpBZDRJSVA4Y3c1NEZEeUZZUnFqSEI0ZFFSRFZQVlg5Z1pUQjE1dXhkangxWndKQ2prRlJrY3BDRTBkamY4bkFsRHRkeHBYalVqYWkrWlhpNEJZVkZZZVVxMVdEZUF2aTRCWUEycGdacGlnUTdqN2RYVlpDWGpYOTNpVkNROUxrd0pkaWpna2NQaWxJd1NJVFBBMGp6UTA1WjVYOU9kb01vQ0ZRUllvRFNTU2gwNFNUeTB5VG1pS1RnQXNEcVRhUy05U1N6QWNoZGdGUUFBeU5rcHdNdFc1RUNMN1BtSHRIUVd2WEVGUW00WEVnSWZFbjQtazB0ZWtzd2NrMkVTa3lJTFdla21rNGs5a3BVckFwa2xrelVoVWprcmsrYkhnQUFPWDRCQ0JDQktGRkpQejZNSEZ4MnN3S01LMEhBQUdJN0NmQ3pWVEJVd3pBaFFRQWI4Y2NpOWE0LXRwQXFWYXhvU3ZoeXd3SXM0bVNOanM1cmNlQlhTc0pZQmNRTFNyVGQ4QXpJRHJzV1FIaDRBT0EtZ0doRFFodEtBZUI4enNTMElvejlkSzBiZ3pTd3dZVmdBT0pmdCtJQWN2anY1bnNic2FwRHRGZGw0RlR3VFpTcnNidHV0ZVpldHo4S1psNTRZMnBCUkw0eXlwVGp3QVpkOE1BTTBvSk5JMzg0d1F5NkFlMXNWYTRqOEV5bEo1ekt4RnpsNGxJMEFTMWVOMXpOenNVVnl6ejVJTnpxenNWRDgrUmo5TXk5eVE1M3BEeXR6bHp1STM4MnBFTnQ1TTVwQlpBMXlienlpSzg3eWxJSHlJQW56WmlQemRONlotWjN5WUt2Z3J5ZnlYd0docnQ2MDdSVnp6elhoQUwxenlqVmdtY2x6andJS29LaUw1eXU0RUxFTGI5VHlnS0JKYnlpS2dRcnphTEJJR0t2Z1R5c0tieUx5Vll2enJ5Nkt1SzBJU0xkeTBKNXo2eEtMRUw5Y0ZRMEtvQU1LYUxzS3dLdEVlS1VLLWxIUkF3Z0pxQllwQlJuZ2VUTGpuUlhpUml0ZGNMZ0tXMUNLanlCS2R5aUtpS3JKY0l4S1lMQktpTFJ5U3RCeDFkc3lWd0R3dEpaeW96OHp2MGlOU0pHaHBMMkxlS0lJTHpjeTFJQ3lGcG5ndkw3OURRTHoyRHk4K1Zad1hTZ1Jvd254eUFGUUVRZUFpcGRoRmdsd3d4LWhUQnVKZEF5UVRsaFF6QjloVHc5MXlxSUMzMVlSMHJpUU14bmhQd1VxSUJRSUd6NXdwQWlSVEFJQm41cVFJZ0ZvTEJ3ZzloU0F5UjdnK1F3QlRCbjBUaWN3aklDajBxQUF4QWlCcXVDVUNWTEt3aFBHZ1lVUTFVWUNjSm9Gb1R5WmZEb1ZmSzRoRVF5QmE2YTQ3QVlvRE9DVDdHLUpDVk1kLVdjUjA4cWhVUks3VU5xNWtBTEdvSktQSWMwdXNsRWtzbFlyQXl0ZTRSNFhnV3NzMVJ0RTB3MUhRTUdsZ29FV2NLTXgtRDhkUy1rVFNtR25nUnRIUzNZMlFTc3JYUTFaeXFBRmtGY3krR01JMFhnUHZUb1J0ZTRIZ2RLY205RzlpNG0ybXltenlhbXcxS01xU3krUjZvTXBtK2loMHJtbEM0bW5Hbm8yUVJtKzRiR2tzdU1FT2RLZkdsa1dLNHNzbXNNZEtGNm9hRUVnVFo4TktwVURLbllVZ2JLOHF2S2tBQXFvcWtxc3EraVNxeWEzZ2FxeFVSRU9xcE1CcXBxbHE5cWRxN0dicStUUXNySWZxcHJJYWthb2ljYWlBNmE5V3hFZWFnSFQ4SmFoaEVBSDB2MDlLTGF0Q3VnT2lWb2ZhNlFRNjNTcFVFNmdITTZ3MWFYSzZyVVJ5aS1JQTZCTUFXQVdRU0FaWWROUWNhWGNuWW5mN0RnTW5JbklvOGxHblMrSXUybWZPejRCblNzWWZCblp1NjY2QzItYjBINUxxY1lwSTdna3VwS3FhOVNBNEhRM084dldRZjJDQS1YTVdzOFpZVm0zUVMrZlpPYUZrSGZQZlVLWUxCdldFU1pTdGU4TlF0Q0NTdk5XdWw2VW91c0Z0SnNNVTB3Z2lDdzVZRGd3ZXlZMndwY1QwOE1mWEV5b0VjVW9LU1VyZWc0SGV3VlhRbUJhSWgrNUFCbzQwUTRoSEh0WSs0QjFhMEI3Z3N0UCs1WUNNbTRVY281R0FUU1o2dFU4UWZlUG1NMjBzalNiaVRCNEFiZTVZSEI5T2k2ejRCQnpTV1FkU1VnVFNDTXM2Unk5S2xZY1RBRVhBRUFGb2ZDWkFUQVVBZk1oYUFnSGhqaHJJTGg4RW5kT1FUQUpLVkFQQVRocUFVQmtnQ0Fka0NScnlhUjRSMlIwUmlBZEJKUitnb1JtQUVSK1IyYXJScVJuUnZSbmRRUVF4bFIzUnRSK1JqZGN4NHhxeG5kVlFXeG1SdVJuZGZnV3h3aUNXQWdEZ1pvZGVCVE9NRGdaWVd4cng2Z2NnQlRSQUY3QWJCb2xnYXNaWURZV2ErSitKeFJ2QWNzUXlXVVJxY1ZDZ05BRmdkNmVzRUFjS0VBQWdlY1dnU0lJS0hoLUpzOGRYZVRKd01wclFMUUlBQQ==" target="_blank">link</a>.
