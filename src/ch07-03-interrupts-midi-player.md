## External Interrupts - MIDI Player

### Instructions

In this activity, you must implement a library that will be used by a [MIDI](https://en.wikipedia.org/wiki/MIDI) audio player. The peripherals used in this activity are the MIDI Synthesizer and General Purpose Timer (GPT), and their description can be found in the [ALE Peripheral MMIO Manual](appendix_ale-peripherals-mmio-manual.md).
Your library will have three main functionalities:

1. Implement a _\_start_ function, that initializes the program's stack (see Notes and Tips for more information on how to do that), sets interrupts, and calls the _main_ function (using the jal instruction), available in the provided application.
   - Note that the jal instruction will be used, as it won't be necessary to change execution mode. In future exercises, this may be necessary (and mret will be used instead of jal).
2. Program and handle external interrupts of a timer device (GPT).
   - The GPT interrupt handler must simply increment a global time counter (_\_system_time_), that needs to be initialized as zero and must store the system time in milliseconds. (System time is the time that has elapsed since the system has been booted).
   - We suggest programming GPT to generate interrupts every 100 ms, which is the value that must be incremented in _\_system_time_.
3. Provide a function “_play_note_” to access the MIDI Synthesizer peripheral through MMIO.
   - The function prototype is **void play_note(int ch, int inst, int note, int vel, int dur)**;
   - The parameters are:
     - ch: channel;
     - inst: instrument ID;
     - note: musical note;
     - vel: note velocity;
     - dur: note duration.

### Notes and Tips

- Check the [ALE Peripheral MMIO Manual](appendix_ale-peripherals-mmio-manual.md#midi-synthesizer) for information about the MIDI Synthesizer and General Purpose Timer peripherals.
- To allocate the stacks, you can declare two arrays in your program. When initializing the stack pointer (SP), remember that RISC-V stacks are full-descending.
- You must implement all the functions in a single file lib.s, in RISC-V assembly language.
- We provide our application in the file [midi-player.c](https://github.com/discovery-unicamp/ale-exercise-book/blob/main/reference_code/ch07-03/midi-player.c), that uses your library and mustn't be changed. This file must be uploaded with the .s library file.
- All functions must follow the ABI.
- All functions must be [_thread-safe_](https://en.wikipedia.org/wiki/Thread_safety). Right now, you **don't** need to understand this concept. Just ensure that your code **doesn't** use global variables (the only exceptions are the variables \_system_time, the program and ISR stacks). Use only local variables, allocated on the stack or on registers.
- **Simulator configuration**:
  - To receive external interrupts, set the “Bus Controller Frequency Scaling” on the "Hardware" tab to 1/2<sup>7</sup>.
  - Also on the "Hardware" tab, add the GPT, and after that, the Sound Synthesizer (MIDI), **in this order**.
- Before beginning to test the MIDI Synthesizer, check the volume of your browser and computer.
- You must access the peripherals through MMIO, just like Exercises [7.1](ch07-01-peripheral-controlling-the-car.md) and [7.2](ch07-02-peripheral-using-serial-port.md).
- Each device's base_addr can be seen on the table “Memory Map” in the "Hardware" tab.
- You can test your code using this <a href="https://riscv-programming.org/ale/#select_url_content=TjRJZ3RnaGdsZ2RnK2dCd2djd0tZZ0Z3aEFHaEJBWndLZ0lCY0laUzRDQmpBSnlnVk0yenhvSHNZQXpLWlRVZGt5aWNDLUVCMjY4NEpDQUVGTXBPZ0ZkVWJUajJUU0NFQU1JTGxxOGVxa3lBSXZwVnJKbW1RREVMaGlScTBRQWtnNnZPWkFXUTlIckxnREtmazRtMmdDcWZxZ3dFQUJHQURhbzFPeHdOQUFXcURRQTFySHNBQjZZWEJEeEJJWUVLV1FRMllqc3NLU29kSEFBYnNVcUxBQU1lUURzdHIyOWVuaDFjRngwcUFDT2NIUVVhQ3dBVEFDc0lBQytlQVFBbnJURkpmd3JJQUFtcUUxUU5LaWlHS0JvTUEzRmlFcDBDT3lsY0tSUVlBMEFkQUJXWjZBRThlek1EQUxBQnN1ekFVRDJVR29hMG9HV0lBQzhQdDh4SDhBWmd1c0NBQnhMSEZMSUE=" target="_blank">simulator setup</a>, but there isn't an assistant for this exercise.
