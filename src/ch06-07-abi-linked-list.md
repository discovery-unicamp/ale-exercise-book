## ABI-compliant Linked List Custom Search

### Instructions

In this activity, you must write a program in RISC-V assembly language that has a ABI-compliant function **int linked_list_search(Node \*head_node, int val)**, similar to the one implemented in [exercise 6.6](ch06-06-linked-list.md). Your code will be linked to a code in C that calls the **linked_list_search** function and expects the return value to be the index of the node where the sum of the values is equal to **val** or -1 in case there isn't such a node on the linked list.

In addition to **linked_list_search**, you will need to implement a few utility functions that will be required for this exercise and future ones.

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
- You can test your code using the simulator's assistant from this <a href="https://riscv-programming.org/ale/#select_url_content=TjRJZ3RnaGdsZ2RnK2dCd2djd0tZZ0Z3aEFHaEJBWndLZ0lCY0laUzRDQmpBSnlnVk14Q2pBUUhzN1NBQ1lBVlFDU2NBQktvQU5nbFIwY1BBSUpFUzVTbkFESzlScVFDK1BBR1owT1lIZ0IwUUFPZ0QwWURnQk1BcnVOUUVMaFltUXFrekFLd0tuak1OazV1UGdBWkRob0ljUUFsVkNEdFBRTWpVMHRyZTBkbkdnNFlHRlFhVWlnczcxOFFBRzUtUUs1ZVlCNWlNQWNJVWk0NFRNb0RjVWM2SGgxOVF4TnpLMXNISnd0YStzYTZJdE15bUg4YWNWY2VBRkVBRHdBMk9BQjJIbFJsMGxRWUd3SjVSWGNWZFFZbVlIOGVIaGF5T2pzOHJnQUtBRW9ybUJ1Ymdqc3BPamZwbDhlS1FBQllrTXgyS0E4QUM4UEJ5QUhjZUVKUkJJLXM5VEN0cERRU0tnZUtzekJzTVBJQUVLQ0FDMG1YWTRpZ0hoNElWZ0FHdFVEWTZVb2VBQmhPeGtYcXFWQVFPZzBFR21WN1RZeWtmeGltNk9YaDBXS1ZHRncxQ0lzSVJhSnk3Z0E2NWZVSGdsbzVQSUZHQUVNd0lMa2c1Nnl1SWlyVlMxQzhha3dKazJPRFVzZ0tuWEd0QTVPZ05WQXV4bk0tMWtPQXdXeE9UV2ZMN1MyNWh1QUFJM0VIRGpzbXBjZmppYmpnS2pkcmhkakFjZWs3ckJ4cDlCMWdwR2VBRVlBQXkxbkFBVmxyMWV0a1p1SG9oVURNRUJzenIyWkhScmErcG5aaGdRVUhtK1N5cGh3TnEraEFBbmpBYUR3NERDQUh4OFdkQXkyVk15eTl3YWx0QW9HWkd4K2hOSm92Zzd2TzBzMlF4d0d3TkNEUEIxT29Pa0FEYTFZQXVpbUE4NnJwZnBXZjY1dm0waEhzZVVwUUdtRjV4bGV4bzN2NmNZUmxCYmJGbVlaNjZCQURoVUxvNDc3QkFZQzRyQ0VEd3RBdkR0cFNZNk9NMFlhb1doN2FRbVlpYklNODdaa1BlZGlrTVNkaTZMb0VFbENZZzVBa3huYXNleEdHY2RJZEM4ZnhnbkNXaHdJWWF4Y0FjTnhwb1ZwQlVIdHFwc0NhWEErSHBBeFVGUUxva25nbGhPSGlIaEJFd0VScUN2RHdzcWtIWWRDZktRRHlvRm1VRXVXNW56WWVJQkRlVnVYeGFMSXdEWWVPY0I4blE0anprU25sMktnV2loZHBpbmFoaHpGSVgyRmFoYVlBQXFUaThKV1BCa2h5aEM0dFcwNmhSeGdTMGFnQUNPZGlSRkFwRHpuQXVVRGtwcGpWUkt1Q2hUY3ZYR1AxTTRpVjgxVFVmeWZxNkhZUzZUakFSTFBCQU9CeGs1MEliaEFaaWVXd2J3d3JDY2JiUXdZQjdhbDQydkxPTGF6dEdFVEJYQXBXd3UyZDdsczgxYXlBQVRPbDBhY0lvQ1orcmRUajNRcW42bUhJUnJ3dElJMHpMZ2ZSZ3dRRU9kUENiVWdqVVNBMEU0VVBUbjBGRHc1RC1VLXJPWWxkajJuWEZkMXg2RmNWUER2V1ZGWEJUd2xZMWVOZFZVbjZUVXRkUzdXay0yZzA4QUFCb3otZ0FDVEFEOXhCLWMwbFVFUGRuNEEtZFA1YUh6WTFLV0xNRzBRRDB1VnJMbFh5OHJhR1RhTzAyR1hOQnBaRXRLMXJldVBCYlR0SjNyUWRSMjdVNVoxUVJkZzdwVVRPVmstbElCRlc2QURNdFBzcFYxTk16cFVuMVd6eld0VnpYVzg2WTcyWXdONDAzSHpJc3dIbUJaMEtsLWhLN3pCdnNFYnMzellhNXVyZXRtMk8zYiswOElkdHVuV2xsMmlvT25zazNINDJVMjZBQXNRY2gtN1lmSGl6Q0FOZEhuTWRlM1NsOC0zd3ZBQm40SFoxRGVjcC16SXZ0aUNPeDBXZXp4ejFucnc1ekFTOUtRWFNDeXNiSmRtend5M2wxYk52SFh0MElPLVh6dU4rN1BrWmJhdkJ5ejNqMFljOWxDdlI5TDZPWlZZU3cxbkFiK1BBUVlnQUFDTHFUK2xEZWtPUmZDalQ2TEF1dzhELUNJS2NEd0pHb0pVWVFIUnNnNkdzaFRCY1F3VEFCMEdOOGFFeXlwMkwyUE1PNit5cHZXWHU5TXU0RDFFaEhWbU1WUjV0WEh0N1plZk4yRXp4QWVyS1c0RHRaM1M3Z3JRK2FGUkgtWEVWM1NSZnBwRjZ5Z3NmSXVKc0ZwbDB0aHRaU3VvdVNOREFIUlF1c29yNjEyZnVkSnVFb1c2ME9KcjJBUlVGTzY4RldLdzNFOVlPR1pYQkxVWWVVY09aOE81bmxaZXBnUEgrRldFbk5SRk1RQjlXSWZuR01waVpwYU5McGZDMkZkclpWM3ZvLU8rbGpYYldKbUxZOEUyVTI2T0tpWDdYZ1d4eXJCM3BoNDVPNGR2R1J4NGY0Mk9KU25FZ0ZDVEFMdTdUUEZBbE1HU1FXc1RsNGFOUHNYVTJpMFVuWHowYmZKMk5jNjdaSzZDLUlFVjFCeTZDNEpmYU1VSllRQUE0aEpRZ0FEeXdockRzZ0ExRWNweUh3b0xSanZBK1hLQ0V6QmVta0w2UUpyNEFJZmstTzlIODZWMEtGTG9jVWhoazh5azhCRmxBSFFsU1E3MWxrWFU0MFBpUjVOUDRYOHBTLU4ya2l5dWNZM0szNFpHUk44aFFlOHFMaXFmaEFwaTQ4d0FwckRLU1JmSyt1aks1UHhtUmt2ZXZNYmh1eVV1bEYyNzk5SEdtWXZoZXk0ZzREN2x3Z3FWY2Vqem5IaDNOd1BjNm92eW1GeWp5cHd1RmlnLWx1Y3hLVnZLYklFRGZoLUhneUFmUm5nVk5XTlZQQXpLWHlKa3FtVktyMFU4QUFJU3dtYkp1WmUwWjRDNVNPRC1iNTIxaXJTcCtDcWxpK3hrQ2dsNWlzem9yNGN3YklaanNuZ3V5NFNCTlZmcWs1Wno2VWFxMWJpSTVUcjJXZG1OZTYwZ0JCUHhRQi1IcW00TEtvS2F1N0NSUytCYnRVQUNvR2JXb3NKZmUxeFVDQjlNK2ZNOGFJclBETnFnWnl5SWNBUzJvRk1QSzJFWGJtNFhKekhCQlV6YTduN0FlWHNhVmNRVEpmRDh1NWZtQUJ4ZU5SSVJaZHEwR1lIZ3NENFFVSTROMkhnODUxS2RCdWMyaEl2UUZCdUdVTHdIWXVSdUtHbERSQUhnSUpaUzZHaENMSkdCd09Ed2pNUHdLSUlRekQwRDVIc0FBOG5HTHd1UlNBLXBDTThPQ2U4ZUQzbTNZbWJzMEpUQTdIV0JzTVZjUlRCcm1lSE1LQU5BR1NQdWtJNVhaTGcxeG1DaGdBVFhVcmNDZzFzZ29jRGc1K25kZTdRUzRseXJBWkFNWnRXZ2dhRGd3Z1BBM3pNbUJBeGc5YmtlQUlBTUFXb3d1eUgxUHRRQyt0OXNCNFBmdC1mKzJVdm9RTmdieUpCbkRzWVlNNkhnOHhtd3lHUURzWmdNZ2Y5V0huanIxbEs4RWpFQXlOODFuQ3lzNldvYUNHSWZDUzFBNWkxcEN2VlRzS1FlUWhPa1RNQVFZZWJWbmdBSElvYVJkZUdZSXlleC1qUERhcWdJd2VpVXRHRXRYMFlVUUNaUW10NEE3TUxuTW9zeGJpd2w2UXp4a3Q3RFN4dURMRnJZUitCQUs4ZEtjN1BnQmZBOHlid0hCWUFsZjhMRm11eXJQQmVHNnpBWHJNQll0WmkwQU9tb0lJK0s2RWNNdE9nUHA1enZGWlg2dFpnYUZUOG1XNTY4emVEeXFWaERSdVhWK3F5UmtqT2F5bTRkeGVCZUFWQUFXUWFDQ2VMaVlYZ1BkQkh1YkZoZzlybHVTendJNURObXRDVkNwK2JiRUI1eVp0QXFEOEhYZ2Z5OXNnVkR6OE1QWkFJNnpkbTFsT2haeXRldGt0c0hRUEl4VFpzVGNkZXl4TjdlWUFHNlJIZU5kSE1kZ0tmaUFWSFR0Y1RQZFhVOTRNVGhValhwczNIV3dHM2dRYVR0N0o0TnNxTnB5LVBabDREaFpZQ3BhZVJCNEFBVWdacXNQVkJybHAyQ2wydUE1elplYnM5aEtvSGE1bjR1SkhaQ0Nma0k0dDZTOXBqV1A3UEJJdHlFaS0razNkQXplb0RrQldac1RsLXZFNzFSSVlLMnVkZ0tqMXd3QTNQUXdERzlOLVJDMy0zSXZWbnQ0S2NQWjVYZXZXYTlicjNvVVpmMDloTThkUHROSmRPU3JaV0pYb1U3Z2NFY0N4RGdiRjA4TnBWOW5oK1BCbXhpNkJIR2RUREk5VVk4SEhtNXlkcC1LRWVXSk53bkdyeDAra25ZSndDU2dReGhnSUc4TVgwWkdqa0c1YUdNOGpxMlVmYkxQLUdzYjFxYTFseXp3T25EMUlFMWxrUFdWWXNneVNySHJGM0UtNi1zMnM1MzVFR21zSlB4a2d2endEWW16RDhBRTROOVAtOWdUUWMwWWZqR0owN0pRcGp5WlVCQUVoUi00NWc3QktBY1p3RGdGTDZmakg0TXorelA2bjZvR1ZoZHctNXZ3ODdySUtoZHdocGhxejRkb0w1T0RIS2k2aFQzZzJwS1FBRndHUkRKUzNKLXdWaDlKTmdiN3I1YjQ1cjZxNkNYdzBIZ0UxeWRLcllXQlZvQUNLeVVaQWQ2T3dSRXZpc2FMUStRR2NFQlNrSGV1YU9DWUlqZ2w4MEJZaDVtdEI0Z29oWmdzQWN3ZGdpK3p3UEJkQmprRGE2aHNoeUFXaE9ocG9CQTVveGgyaGprZXFqZ3VnWUJKaERCMktMMHpCVFlzZ2JCelllcXUrSm9ab0FhTGhWaGpob1VkTzcwZ1J0aFJoZVlvUnRNemhyaERoekttT1hlODZuNHUrc2dFUnNnNWhzQjhCMSsrTy1lU0VLS2o0ejR6d0dSdCs0Zzcwc2dPOEVFMCtPWWM4NCtpK0RPa1FsWXUyM3FJSWI4ZHFFK3dNcGc2ODNZalIzYUlBditRSU9CbTJCeUJCWUVBeGthVUEwYURlY0lFK1VSNW9mTUpCY0FRS2lzaktZVU4rSkIwc3NBYlV3TStSSXhxeXZPK3FPcUV4RFIyeFpCVk80MEt1Z3U1eDNSQjJWeFNrMnhjQXV4bmdOaFN4NmNFK0VPNjZ1K0NvSXN1KzN4SlFueGkrM3haZ0VSZnh3QUVSZ0p3SlRnb0pPUXV3Q29BQVpEQ1Jtak1TQkZObnpBMmpvRDdyaUhNVGNNOGE4WXNjOEduTFBGOFZtajhTMFJDUUNlU1VDYVNTQ2VTV0NYZmxTWGZ0Q1hTYkNReWZDUVZqd0FBSEw4QWhBaEFsQ1ltdDdPYXpqWFpjWkZwT2FEZ0FERWVoMmgycXBncVlaZ1FvSUEtZVYyanV0Y2MyMGcrS3RZQnhYdzVZWUVXY0VKTlIyY1hPUEFVcFdFc0F1SXZKLUpkZXFwTyszV0xJRHc4QUhBZndEUWhveVdsQVBBTHBqeGFFK3BkT0hCM0pZWWdLd0FIRXMyLUVDMjJ4Y1d3MlBXTlVUV0JPeThLSkx4QVFRMkkyWTJTa3NXaWhRNHk4OE1iVWdvbDgzcGVKeDRBTWRlR0FzYVVFbWtrK2NZbXBkQURhQ0t0Y3plcHBTa3habFlwWnk4U2thQTZhMEcxWnRaQ0tGWlhaOGtOWkhCU2tUZWZJTGVkcFRaSWM3MHJaZFo1WjNFaytiVXU2MjhtYzBnc2dWWkE1UGg3dVE1YUVJNUVBWTUrU001Tkc5TS1zMDVCNVh3ZlpDNUw0RFEzV3p3SFpsWjNacndxNTFaUGhxd2dPWlp4NE81ZTViNXhaWGNKNXA1QStuWmE1QWtnNWI1UUlmWmdGZ2tJRlh3dDUtWlFGUFpLc2M1TUZFRmJaMjVEWjQ1YUV4WjlZdjVwNWRPVzJqUVVBTjVkb2Q1QTVyNXlGczVuWkY1enlqb2dZUUUxQXNVZ296d2lKZlJ6b0pCbVJsT2o1NjVGYUpGZjVOd0g1VzVRMHBGY0c4bTFrcEFXRkI1dkZiNUhlcm1nNFpPRHBLNEI0V2toWitwTHBFNmQ2cEVlRkJGQUY5NUhCVHBha3JwQzB6d3lsUStob1BaMEJidXlSZzRrcFFJMFlUNDVBQ29DSVBBUlV1d2l3UzRZWS13cGczRXVnWklteXdvWmcrd3A0M20tbDIrdzZzSTlseElHWXp3bjRObEVBb0VJWjg0VWdSSXBnRUFDQTRXRVFDMEZnNFFld3BBWkk5d2ZJWUFwZ1dnMitSa1JhOWxBQVlnUkJGWEJLQkpLc1ZCeHBaazFtLUtNQk9FMERJVzBCMEdYdjBRaUlaT1ZVVlMxcWtaOEhCSDN2dWRiQ1RLbUZQcUtWa0c2UDVRcUpaZHFIRmN5UEpqVUVsSGtEeVVHWE1YNlMwYXhaVVhxdmNJOEx3SUdXV3B5Vy1Eb1B0ZklWbVVDUHFTUGgrTFJmeVBSU2RUd0tXa3hRTWJJT3RlSU9sREpWQUN5QldaZkRHRWFKLU9xYVd2Y0R3T2xISHAwS1dyZWQ5U0RmZFlEZWxQcVZlVkNMcHI5YmNQOWZjTURmOVJlZDlTOWNBVWpmeUZEWjVNOVo2WEdDSEc5YkphWlI2Wi1HR09sRE5meFZaVG1GRlhaVXFBNVRzS1FNNWY1VzVTQUI1VjVUNVg1ZlJJRlowVU9obVBUWWlHRlVtQkZWRlRGZTFQRmRqTWxkU0tsWWFPbFVGbGxUbFVSUGxZVlFSSUxUd0dWUXRwK0pWU1FpQUlxY3FlbEkxVmVYUUhSSzBDWG0xWWhzeFVxRjFRdGoxVy1GamdOVnFGSlRjSXdjOEdBTEFMSUpBTXNER29PRmptOWs5dk5od0s5bzlpdmppdDlwZkY3YlRPN1o4UDlwV01udjl0SFlOVnFQY2tQbjZGMURrWm9mQVQ3VFRid0Nzbk5DeUVtcUhTOUJ2djdOdm5UdmpXZUwzck9Dcm5uUWNEWFBYcUZFcHY3ckNIMG5xcFFZV1RoWVhhN1Y0WFdCV2syRmljb1dyYzhCblpZZkFib1V1SEtlR0hUbHhXRk5zRUZMaVkzUWNNM1Y4aVdCNGYtQnZpUGFFY2FJNEh0aUNBMnAzZHNNc0RBWm5TWWFpVXZjc0xxYm1qZnZwTnhOTmY4WkVQdkh6SHpid09wS1FKcEhmY0FFM2NzSS1mYlgxWkFqZmFRTElLLVpwTHFXZEZKZlpTc0doZ0NMZ0NBQzBQaE1nSmdLQUM2UXRBUUlnN0Exa1BBeThRUUJBSElKZ0VsS2dIZ0hBMUFKWVNRQkFPeUhnMTVJUXhnOFExZ3hBTkFoUThBZWd6QUpnNlF5VlF3d1Ewd3l3OWc0SU93MVE4d3pRNlEzZHJ3NXd3STlnNm9NSTBReVE5Zy13TUk0UkJMQVFCd00wT3ZQaG5HQndNc01Jd285UU9RUGhvZ0NOb2xxRVN3TldNc0JzQ1ZhWTZZK1EzZ09XSVpMS0kxRHloUUdnQ3dPOVBXQ0FPRkNBQVFQT0xRSkVFRklnNjQyZUdUbmhrNEQ0MW9Gb0VBQQ==" target="_blank">link</a>.
