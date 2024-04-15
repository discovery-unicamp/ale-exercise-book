## ALE Peripherals MMIO Manual

### Canvas

| **Address**                     | **Size** | **Description**                                                                                                                                                       |
| :------------------------------ | :------- | :-------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| base+0x00                       | byte     | Storing “1” triggers the canvas to write an array of up to 504 bytes representing up to 126 pixels to the screen. The register is set to 0 when writing is completed. |
| base+0x02                       | half     | Array size (in bytes).                                                                                                                                                |
| base+0x04                       | word     | The initial position to write the array on the canvas. The canvas is represented as a 512x512x4-byte one-dimensional array representing 512x512 pixels.               |
| base+0x08</br>to</br>base+0x200 | word     | 504-byte array representing up to 126 pixels. Each pixel takes 4 bytes, one byte for each value: Red, Green, Blue, and Alpha (in this order).                         |

### General Purpose Timer

| **Address** | **Size** | **Description**                                                                                                                                                                                      |
| :---------- | :------- | :--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| base+0x00   | byte     | Storing “1” triggers the GPT device to start reading the current system time. The register is set to 0 when the reading is completed.                                                                |
| base+0x04   | word     | Stores the time (in milliseconds) at the moment of the last reading by the GPT.                                                                                                                      |
| base+0x08   | word     | Storing _v_ > 0 programs the GPT to generate an external interruption after v milliseconds. It also sets this register to 0 after _v_ milliseconds (immediately before generating the interruption). |

### MIDI Synthesizer

| **Address** | **Size** | **Description**                                                                             |
| :---------- | :------- | :------------------------------------------------------------------------------------------ |
| base+0x00   | byte     | Storing _ch_ ≥ 0 triggers the synthesizer to start playing a MIDI note in the channel _ch_. |
| base+0x02   | short    | Instrument ID.                                                                              |
| base+0x04   | byte     | Note.                                                                                       |
| base+0x05   | byte     | Note velocity.                                                                              |
| base+0x06   | short    | Note duration.                                                                              |

### Self Driving Car

| **Address** | **Size**       | **Description**                                                                                                                                            |
| :---------- | :------------- | :--------------------------------------------------------------------------------------------------------------------------------------------------------- |
| base+0x00   | byte           | Storing “1” triggers the GPS device to start reading the coordinates and rotation of the car. The register is set to 0 when the reading is completed.      |
| base+0x01   | byte           | Storing “1” triggers the Line Camera device to capture an image. The register is set to 0 when the capture is completed.                                   |
| base+0x02   | byte           | Storing “1” triggers the Ultrasonic Sensor device to measure the distance in front of the car. The register is set to 0 when the measurement is completed. |
| base+0x04   | word           | Stores the Euler angle X of the car rotation at the moment of the last reading by the GPS.                                                                 |
| base+0x08   | word           | Stores the Euler angle Y of the car rotation at the moment of the last reading by the GPS.                                                                 |
| base+0x0C   | word           | Stores the Euler angle Z of the car rotation at the moment of the last reading by the GPS.                                                                 |
| base+0x10   | word           | Stores the X-axis of the car position at the moment of the last reading by the GPS.                                                                        |
| base+0x14   | word           | Stores the Y-axis of the car position at the moment of the last reading by the GPS.                                                                        |
| base+0x18   | word           | Stores the Z-axis of the car position at the moment of the last reading by the GPS.                                                                        |
| base+0x1C   | word           | Stores the distance (in centimeters) between the Ultrasonic sensor and the nearest obstacle. Returns -1 if there’s no obstacle within 20m.                 |
| base+0x20   | byte           | Sets the steering wheel direction. Negative values indicate steering to the left, positive values indicate steering to the right.                          |
| base+0x21   | byte           | Sets the engine direction.</br>1: forward.</br>0: off.</br>-1: backward.                                                                                   |
| base+0x22   | byte           | Sets the hand break. (1 = enabled)                                                                                                                         |
| base+0x24   | 256-byte array | Stores the image captured by the Line Camera. Each byte represents the luminance of a pixel.                                                               |

### Serial Port

The serial port is connected to the terminal (stdout and stdin).

| **Address** | **Size** | **Description**                                                                                                                                     |
| :---------- | :------- | :-------------------------------------------------------------------------------------------------------------------------------------------------- |
| base+0x00   | byte     | Storing “1” triggers the serial port to write (to the stdout) the byte stored at base+0x01. The register is set to 0 when writing is completed.     |
| base+0x01   | byte     | Byte to be written. ID                                                                                                                              |
| base+0x02   | byte     | Storing “1” triggers the serial port to read (from the stdin) a byte and store it at base+0x03. The register is set to 0 when reading is completed. |
| base+0x03   | byte     | Byte read. Null when stdin is empty.                                                                                                                |
