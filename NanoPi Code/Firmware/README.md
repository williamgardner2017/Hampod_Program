# Hampod Firmware #

## Description ##

This section of the repo is contains all of the code for the Firmware. In the scope of this repo, code is considered Firmware if it controls GPIO pins on the board or if it coordinates with other programs (except Hamlib which is Software controlled). <br>

## Communication ##

The Firmware will idle until a command is sent to it. This is accomplished though the use of named pipes. The two pipes that are used for communication are Firmware_i and Firmware_o. These stand for Firmware in and Firmware out and are from the perspective of the Firmware 
(Firmware_i is the input to the Firmware and Firmware_o is output from the Firmware). <br>
Data is sent through the pipes in a packet formwat which is listed in the following table.

||Type|data length (bytes)|tag|data|
| :---: | :---: | :---: | :---: | :---: |
|Size (bytes)|4|2|2|0-65535|
|Description|The type of packet (keypad, audio, config)|Length of data field in bytes| Tag value for packet. Assigned by the software and can be anything from 0-65535 inclusive.| Additional data from the packet. In practice it is mostly strings but any data can go here.|

## Structure ##
The firmware is broken into three seperate processes: the Firmware controller, keypad code, and audio code. Each process comprises two threads, one that encodes/decodes packets and one that performs actions based off of the decoded packet. The Firmware was designed this way to minimize the amount of blocking. <br>
Every packet sent to the Firmware will get a response packet back from the Firmware except during startup.

### Firmware controller ###
This is the code that the software interacts with. The controller will decode packets to figure out which process the packet is for, if any. Packets that are designated as `config` will change the related instruction in the controller code. Invalid packets are discarded and not forwarded to anything.

### Keypad ###
This code reads the keypad and sends back the read key. The value for a read key is `0-15` inclusive. If no key is pressed or multiple keys are pressed, then the keypad code will return `-1`. The following table corresponds to which value maps to the keys. The numbers in codeblocks (`This format`) correspond to the 
value the code returns.

||Column 1| Column 2| Column 3| Column 4|
|:-:|:-:|:-:|:-:|:-:|
|Row 1|1: `0`|2: `1`|3: `2`|A: `3`|
|Row 2|4: `4`|5: `5`|6: `6`|B: `7`|
|Row 3|7: `8`|8: `9`|9: `10`|C: `11`|
|Row 4|*: `12`|0: `13`|#: `14`|D: `14`|

A properly formatted packet will conatin a lowercase `r` in the data field. More data could follow but the keypad code only cares about the first character in the data field. Subsequent data after the first charater are ignored.

### Audio ###

## Building & Running ##
To build the Firmware, run `make` in this directory to generate the `elf` file. Run `make debug` to get the debug version of the Firmware, which has debug print statements as well as including the debugging symbols for the code. <br>

