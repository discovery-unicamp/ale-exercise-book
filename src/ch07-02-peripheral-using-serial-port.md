## Accessing Peripherals - Using Serial Port

### Instructions

In this activity, you will communicate with the Serial Port device via MMIO. You will need to read a stream of bytes from the Serial Port and then perform an operation on top of the data read.

Interactions with Serial Port can be done through two memory addresses:

- **base+0x00**: storing the value 1 triggers a write, writing the byte that is stored at base+0x01. The byte at base+0x00 is set to 0 when write is complete.
- **base+0x02**: storing the value 1 triggers a read, reading one byte and storing it at base+0x03. The byte at base+0x02 is set to 0 when read is complete.

There will be 4 different sets of operations to perform:

- **Operation** 1: read a string and write it back to Serial Port
  - **Input**: <mark style="background:transparent;color: darkred">1\n</mark><mark style="background:transparent;color: green">{string with variable size}\n</mark>
  - **Output**: <mark style="background:transparent;color: green">{string with variable size}\n</mark>
- **Operation 2**: read a string and write it back to Serial Port reversed
  - **Input**: <mark style="background:transparent;color: darkred">2\n</mark><mark style="background:transparent;color: green">{string with variable size}\n
  - **Output**: <mark style="background:transparent;color: green">{string with variable size reversed}\n</mark>
- **Operation 3**: read a number in decimal representation and write it back in hexadecimal representation. Use uppercase letters.
  - **Input**: <mark style="background:transparent;color: darkred">3\n</mark><mark style="background:transparent;color: green">{decimal number with variable size}\n
  - **Output**: <mark style="background:transparent;color: green">{number in hexadecimal}\n</mark>
- **Operation 4**: read a string that represents an algebraic expression, compute the expression and write the result to Serial Port.
  - **Input**: <mark style="background:transparent;color: darkred">4\n</mark><mark style="background:transparent;color: green">{number with variable size} {operator} {number with variable size}\n</mark>
  - **Output**: <mark style="background:transparent;color: green">{operation result in decimal representation}\n</mark>
  - Operator can be **+** (add) , **-** (sub), **\*** (mul) or **/** (div)

### Examples

| Test Case | Input                 | Output          |
| :-------- | :-------------------- | :-------------- |
| 1         | 1</br>Random String   | Random String   |
| 2         | 2</br>Reversed String | gnirtS desreveR |
| 3         | 3</br>1876            | 754             |
| 4         | 4</br>244 + 67        | 311             |
| 5         | 4</br>2340 / 50       | 46              |

### Notes and Tips

- Check the [ALE Peripheral MMIO Manual](appendix_ale-peripherals-mmio-manual.md#serial-port) for information about the Serial Port peripheral.
- You can debug your program reading from STDIN and writing to STDOUT. Before testing with the Assistant, the functions responsible for IO need to be changed in order to interact with the Serial Port.
- The final version of your program can't use syscalls except for the exit syscall.
- You can use the program stack to store strings with variable sizes.
- You can test your code using the simulator's assistant from this <a href="https://riscv-programming.org/ale/#select_url_content=TjRJZ3RnaGdsZ2RnK2dCd2djd0tZZ0Z3aEFHaEJBWndLZ0lCY0laUzRDQmpBSnlnVk14Q2pBUUhzN1NBQ1lBVlFDU2NBQktvQU5nbFIwY1BBSUpFUzVTbkFESzlScVFDK1BBR1owT1lIZ0IwUUFPZ0QwWURnQk1BcnVOUUVMaFltUXFrekFLd0tuak1OazV1UGdBWkRob0ljUUFsVkNEdFBRTWpVMHRyZTBkbkdnNFlHRlFhVWlnczcxOFFBRzUtUUs1ZUFta29TTVJLaE1NVGN3dFVBQTlTVkJoaUxPY2JWQUEzS0JvbkMycUdPcmlpdnhoLUduRlhIZ0JSTm9CMk9BQW1IbmJPbUJzQ2VVVjNGWFVHSm1CLUhoNU03dEk2T3p5dUFBb0FTZ3VZSzZ1Q095azZWN0tQcDlTQUFMRWhtT3hRSGdBWGg0T1FBN2p3aEtJSkw4bnFZVnRJYUNSVUR4Vm1ZTmhoNURRUm9vWU1nZUFBRkdvSVlIU1NJSEFDMGlPSVpKNHFocWtVcGxWTUx3QnhsSS1uNVYwY3ZEb3NRYU1QaFBEQ0VXaTR1NC0wdVFOQkJETU54eWVRSzNUTUNEc0JHQlR6RmNWNVN1RnFGNG1YNmNBQVJ1SU9OYlpPSW9OYWJYYnJRRFBqd1FXQ0lXWUlEWWJIQk9tUTBZRFBhWUFNS0dCQlFCYjVMS21IQ216NXdhRUFQajR5YzlSc3FaakY3Z1ZKckRucDRZdElkam9IMjlxclFPUVlORGdtWFlzZFFRYWNwRmVpdUxWeDBzaXpmRDAwSEVjRlFFRG80Z0Fub1M3blljVnBrMFhrOVh3VkEtUUcyeUgrNllBQ3J0bmdBUmg0VHdBanJPeUZxWG9uKzh2aU94SENQVDVFb0tRSnh1Ty0ycnFaOThaLUZFS0RZbWxVTzVZR1FIOVpsd0Q5bWotUFpBT0Fza3dLdmJ0UG1BYTVvekhWdGREc0dCTlN5UWtuZ2dIQnJSZWRNZUFnTXhnTEFWNW9SaGExeUlZU2ppUG5KREwyTFJkaTJYWDEtVURZTjN5UW5jOXkyRTh6M2pHQkx3Z3BDYjBDZTlVRWZKMFh6ZlVNUzArVXdOakFtSUJta2FvYkRaT0RRTUZjU2xNLUVCa0FDYmhWQjRmb0NERkRTb2dRZ3pESlFwc2tERk9CTU93a1M4SUlvaVNMSWlpcUtoR2k2TFlLaW1LVWxqUFRZejBPTlhMaUZLM0VCZHpJSGdBR1lqMVBkc0wwUXBUSkx2VnNaTHNKOTVKNHhURE5NWkt3UDNBQU9WWUFEWTdLVEpDak5XQUJXQUFXZXJJTWN0Q1hMY25DWUU4d2ppS2hETmZQby16QXI4eGorM0N6NUl1VkgwWXZYWXI0c1MzaFdyUzRUTXZzcUtWVE1XOEVHazJUbjFmWmJHdWFkci1BMlZyMW9BYWg0R3JWZzZzNnl2M2I5OUlhd3lCeWM5RFhLd3ZxQnU4NGJTS0NoanFKNFdqSnA0VUtTeG1xNDVxdWFLMTI0OXNTdkRCSzkyYWphTXF5TVNQcExIS0RyeW82aXBSeURUQXVtQU5tUzFxQUFZZUFzSGhtcHBwN1B2SnVyM3M2MUQyQiszcVBLUEx5aHBHa0h4dkI0V3B1WWhjUFUrRVZTMWlVY3FESUJoV1JoQUJ0VXdva0VWUUl3WkFBMVJObWprT2dhRkJUbzhnclZCOWRNQkFER1FPZ0lEQU1BUU5NQUJkWk1aYnR2WTRGZ1FORHhoWmNQWnNXQU94cDJRTm1JcGRkczRwYlNiNDlHa3JxN2I1dFZmYkRvS3VTVHBqejZBQU0zcGdBQVNZQWpYbDZoZEpWZ092YzktZG5mbmZ3czd4cFNzNExvdUlBVjB2eSs5dUFxNXJtQTY4NTc2ZXIrdm44TUdueXhiQmlHeHZGc0xKY0ZZc1pldFFoVzBWa0RvUjROV1FDQWlBYUFBYXk1SVBwRXRrQUZHcU1CYlFuUStuTHNUbzZCNGEyT0Z0KzNIZmdrQlhibjgxWlkwdWhxaExwWHlWVjB3eXdCQTRCU0hnMjhJaWtGVUlmQ2M0aHJSZ0NjQVFPUWg4VEpzRWdIUVpBWEFFQ3kzTEFnYXdOQVhadTNmdTNUMld3LWE3UURrSEo0SWNlQmh4TU94U09pMWthYmxqcXRYRVdWOGE3UlRrVE5PeDA0cG5TenFwZndCY0Y3ZjJYbVNNdS00SzZCZzJOWE1DdmMrRk4wR0pwSmViY0pFZDJrZDNPUm4wdXJjd0h1NUxVQU5CYkEwaGdGVVdrTm9ZUlJuck1OK29wVkVxRjlsNk1oLTRLRU1uM0RUTnhzaFhGdVBEblFoYVNOZUZLWDRrbFNxYkNkcGdrNFErYmhKTW1IWjNLb0l3dXRpcUQ3ZzBmWEVzamRnRExscEcwUnN0aFVDR2dTWjNGNHlTKzdkUXdvUGZSLU1SNUExR3NGSWFFMUo1UTJtcFl6ME1zT0MtQmJsd0E0LThRQTNVUGd5UStBQXFRK0ZnWFpTek5EWXoyclRPNnIzOWs0eWdUd1hGdUtvWjRtbVJabW1FSWtaTWtoRGl3VGtMbVFzOXhCNUZtck9sb1F1QWt6N0V6TDJCUXFoeVZqa0kzb1g0MDZBUzQ2OEFBSndoS1RudEtTWERDb1oyaVlaTE9GTW00YklRSjNIUUJkV2wwbElCMHN1WnpRVmR4NE1DaVpvS05oRlBrZWszYTdSclp3QUdKRVBKeUxPNnlITHBzb2xjS0Nsb3EwVnpaeXBTOUc0UXFZRElXeGk2azFJYVJMVmlmSnJHbGhCWEFWS3BDZG16STdQc3BaUnpSazhIZHR5OWFmTFZTN01GY3NqeElxQ0dpakpWc3k1Z2M1azNMdWRzMVVVZEdHOFdlU3cxeEh6N2xoTytSRTM1LWlBVkF2aVFTNUs0TGdDUXJ0dENyK3NMTm5WMFJkYXdNa3pXb1VvQlFYWmNXSzZBNHJ4Y1MwRnlVaVVTdEpac3dwc2lVbWVtMGRTMzZ0TCtyMHNNZFUwR0ppSjRzdk1iTkpweWtmSGF0WExvV0FkUjh3T0Y0RENWTVFOM2hLUnpOd1BNOHBTRHJ4NG5BVXQ0aFNERkdkdE1oNXpiVzN0dEZXTW5nRDkraXJ4cHYybmdVQmRCSGtSajJwd1phQ0FxeHBwMmdBaERDRlptWXpveTNnRHhUcFdxVnprWGJDMjJkYmJWU09ESkNDU0N1Z3VCSGhscENHRSs0U2pqcDRBQUhsaEcrQWdENm9BM1J1c1JhdG4xQjEyMkhUZEtWZTZaM2ZHUFNyS0F6c3gwOWtna09uRU1Jbmh3WjRQMHc1eEVHWlBDM2UyQWdMak5Vd2FRcld6d0JIMTVGcGdIVU9ETHRWNXdZNVVwZWVicFY0RWJNTFdLRnJZQ05kaHJlYUNzSHdzNEFIRUFPb0VKQVhPRFdnekE4QUFDSWNEaERBTzAtb2VBVGc0QldMMGU0Q09OQ01NZkpRSGh0aHRGeUZmTFV6NklBOEdCR0tYUVVJQzV3bTloSnN3LUFvZ2hEVkdLRnVxQUFEeTFvdkM1RklGWmtJVHhiVDJrS1JaQ1RVbU9EK2loS1lkbzZ3TmoxcmlLWU5NVHg1akRGM3JTTVVMd24wdURUR1lMT3lab1pNVm5sY0dWVHduNnlFZ0cwSDl5WXl5Y1o0QUFXUmJzQ013dWc3VFBBcXlDUE0tNURCVVJRN2xpQWJRZUJNaWZqd082KzRYakVUdWstS1dtWEFRQnFEZUlKNHJUOXl5RmFSc0diYlNuVnZHVExpbSsrWVIyaW9JR1owZ3hzandPdmFYUUpiU0VJalZCNERUREFrRTFzd2ltejFuZ3Mzb1BnenM5dk1keDJjVDduTzJkUzd0MkVDSGlaSGR5QzFwSHZQY1h0UTk3bjFQdlhaUTM5czZBUFJ4UGY3QzlsS29QREtmZnExVm1jMkZKdmZmcGw5c085MlljUURoOFdiTkpYS3l5M2ZVcUViVnhNblpQNkU4WEY0aER0ck40SFllbnE5NmRwZzU2T3hWQm4yaXJ6OEtVTExueEwwM3llRGU5Ymo2WDJWUS1WK3huSllaWVFEc0IxbUVMUE9RQUZJRHcxVEhSTy1taXVlQnBqdlNzeUNtVFY1QVYtdFZ4SUVaZ1JqaWpMVGhYSFdtU3VKdXdBY2prRTd0VVZ1NkEyOVFISVlPLVdidVpMSFJJYW9SdmVjd2xOeUJjM2hoTGZXNXlmaFhYZDBuYzB6ZDhiR1AtUWZlVUw5M2RBUC1ZVmZpRlhxanVpZjBuaTUreC11R3F1SHgyVHVMNnpreEt6ZjFLWHg0VHBTMmJpY2NkSjlud0VXaHFPMEpHMUtGWW9XdXk0QkFEY0l0eUJNQ2dGYVNKQWc0LWg5WkZIMTdBZ0VBNUNZQm5LZ1BBSStvRElBWHhBQ01LLTdocjluekFlZkpBSUNpYjM3T2RmYy1OLWI0QUdMbjRQeHZyZkotQkQzOHYwZjYtSit5dXY4UDhmeGZxaHYrUDdiNzhEZjVkQVFDMmhMd2NDTmkwZzd6V2djQnREZjRFQ1FIdUE3ejFEN3lCcjA2emdzQTB4ckEzNjRHNEc3NTRCQnl1UmlqSGd0b1VCb0FzQWJETlFnQmFCNEFFQVRpMENSRGlEVDRZREFDMEVnRDlCREFrZ3o3akMxRERoVEErQThGMmpNQVlCVUUxUmFBU0ZhQkFB" target="_blank">link</a>.
