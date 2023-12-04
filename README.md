# MarcDuino Firmware V4

## What is the MarcDuino system?
(from https://www.curiousmarc.com/r2-d2/marcduino-system):

"The MarcDuino system controls the animatronics of an R2 (dome panels, light and sound). It currently controls 10 dome panels, an "MP3 Trigger" sound board, dome "Teeces" lights and holoprojectors light and movements, and I2C gizmos you can add-in yourself. It has lots of pre-programmed effects making all these act together.

The system is centered around the MarcDuino boards which sit in the R2. There are two kinds, the Master and the Slave board, which are very similar to each other." - CuriousMarc

## What is MarcDuino Firmware V4?
The MarcDuinoFirmwareV4 software is a **firmware replacement** for the original MarcDuino V1.5Rev3 boards. 

Details about the **boards** can be found here:

https://www.curiousmarc.com/r2-d2/marcduino-system/marcduino-boards/marcduino-v1-5
https://astromech.net/forums/showthread.php?28414-Support-Thread-for-MarcDuino-v1-5-s

The **original firmware** can be found here:

https://www.curiousmarc.com/r2-d2/marcduino-system/marcduino-software-reference

There also is a **spinoff** of Marcs firmware also known as **MarcDuinoMain V3** and **MarcDuinoClient V3**:

https://github.com/nhutchison/MarcDuinoMain

https://github.com/nhutchison/MarcDuinoClient

***MarcDuinoFirmwareV4 has nothing to do with the original firmware made by Marc nor with the spinoff made by Neil! So if you have any questions about MarcDuino Firmware V4 don't ask any of them!***

Nevertheless: Read and understand, how the boards work, why there is a master and a slave board, how the boards are connected ->

 https://www.curiousmarc.com/r2-d2/marcduino-system
 https://astromech.net/forums/showthread.php?28414-Support-Thread-for-MarcDuino-v1-5-s

As soon as you are familiar with MarcDuino, come back here and proceed!

## Why MarcDuino Firmware V4?
The last update to the original firmware was in 2018. Neil's last update was a minor change in mid-2022. His V3 software has about 80% of the original source in common, adding some features for the latest MarcDuino boards (servo controllers and EXT/AUX pin controllers). He also added the nice feature of saving settings to EEPROM at runtime. But the code also has some glitches and bugs and is based on outdated Arduino libraries. I started 2023 after the whole Arduino framework and community has made really great progress in the last 5 years.

The MarcDuino Firmware V4 code has completely been rewritten from scratch. I took Neils idea of the EEPROM storage a step further, so nearly ***any*** setting is stored there. Including per-servo position settings. I also added the new panel animation of Tim Hebel who is also using a modified MarcDuino V3 firmware (https://github.com/Eebel/SHADOW_MD_EEBEL).

### New Features (excerpt)
- Support for MP3 Trigger, DF Mini Player and R2-D2 / Astromech Vocalizer (https://humancyborgrelations.com/)
- Identical firmware for Master and Slave
- Automatic configuration of Master and Slave at first startup
- per servo runtime settings for min/max and open/close positions
- switch to modern OOP software design and use of most recent common Arduino libraries
- fixed a lot of bugs at least of the V3 spinoff
- ...

## Lets get started
### Revision History
| Date | Rev | Description |
|--|--|--
| 2023-10-23|V0.9.0 RC1|First version for closed beta test group|

### Known MISSING functionality compared to the original source (will be released in the future)
- I2C command support
- RC-IN support

### Supported Boards
|Board|Support|
|--|--|
|MarcDuino V1.5 Rev3|YES|
|MarcDuino V1.5 Rev2|not yet, but planned, tests  pending|
|MarcDuino V1 | NO |
|MarcDuino V2 | NO |
|BenDuino boards (https://www.printed-droid.com/kb/benduino-system/) | not yet, but planned, tests pending|

### Compatibility Matrix
|Master/Salve|1.8|3.x|4.x|
|--|--|--|--|
|1.8|YES|YES|YES|
|3.x|YES|YES|YES|
|4.x|YES|YES|YES|

### Uploading firmware using *.hex files
- Download the latest hex-Files from the GitHub Repository: https://github.com/RealNobser/MarcDuinoFirmwareV4/releases
- Flash hex file with the following fuse settings (**incorrect fuse settings will lead to non functional boards or unintended EEPROM content reset!**):
	* efuse: 0x07
	* hfuse: 0xD7
	* lfuse: 0xFF
- **Recommended:** When not using the Arduino IDE take a look at avrdude
	* avrdude: https://github.com/MCUdude/avrdude
	* GUI for avrdude: https://blog.zakkemble.net/avrdudess-a-gui-for-avrdude/
	* some instructions: https://forum.arduino.cc/t/the-simplest-way-to-upload-a-compiled-hex-file-without-the-ide/401996

### Development Environment
* Visual Studio Code: https://code.visualstudio.com/download
* PlatformIO Extension: https://platformio.org/install/ide?install=vscode
* Recommended ISP programmers:
	* https://www.diamex.de/dxshop/USB-ISP-Programmer-fuer-AVR-STM32-LPC-ESP32-8266-Prog-S
	* https://www.diamex.de/dxshop/USB-ISP-Programmer-fuer-Atmel-AVR

### Building and uploading firmware using Visual Studio Code
- Clone the GitHub repository using Visual Studio Code (Source Control / Clone Repository)
- ![VSCode Clone 1](https://github.com/RealNobser/MarcDuinoFirmwareV4/blob/main/assets/Clone1.png)
- ![VSCode Clone 2](https://github.com/RealNobser/MarcDuinoFirmwareV4/blob/main/assets/Clone2.png)
- Open local folder
- Edit the file "platformio.ini" to match the serial port of your programmer:
`upload_port = /dev/cu.usbmodem141201` (example)
- build the code (PlatformIO / ATmega328P / General / Build)
- ![VSCode Build](https://github.com/RealNobser/MarcDuinoFirmwareV4/blob/main/assets/Build.png)
- upload the code (PlatformIO / ATmega328P / General / Upload)
- ![VSCode Upload](https://github.com/RealNobser/MarcDuinoFirmwareV4/blob/main/assets/Upload.png)

## MarcDuino Commands
### Format
Every command must start with one of these special characters (defined in the header file). The start character is recognized in the main loop:

#### Master
| **Start Command** | **Function** | **Master** | **Remark** |
| --- | --- | --- | --- |
| : | Pie panel command | YES | Slave only Subset and for Panel 12/13 |
| \* | Holo Projector (HP) commands | TO SLAVE via Serial\_Slave / suart | |
| @ | Display commands | TO SLAVE via Serial\_Slave / suart | |
| $ | Sound commands | YES | |
| ! | Alt1 alternate sound command, passed to suart2 after stripping | TO MP3 via Serial\_MP3 / suart2 | |
| % | Alt2 alternate HP board command, passed to suart without stripping | TO SLAVE via Serial\_Slave / suart | |
| # | MarcDuino Setup commands used to configure various settings on the MarcDuino | YES / TO SLAVE (to keep EEPROM in sync) | No sync of MarcDuino Type to Slave |
| & | I2C-Command | YES / TO I2C | |

#### Slave
| **Start Command** | **Function** | **Slave** | **Remark** |
| --- | --- | --- | --- |
| : | Pie panel command | YES | Slave only Subset and for Panel 12/13 |
| \* | Holo Projector (HP) commands | YES | |
| @ | Display commands, forwarded to JEDI controller on suart1 after stripping the '@' control character | TO TEECES via Serial\_Teeces / light\_suart / suart / suart1 | |
| $ | Sound commands | NO | |
| ! | Alt1 alternate display command, passed to suart after stripping | TO TEECES via Serial\_Teeces / light\_suart / suart suart1 | In normal use the Master MarcDuino catches these, so we don't see them |
| % | Alt2 expansion command, passed to suart2 after stripping | TO MAGIC via Serial\_Magic / slave\_suart / suart2 | |
| # | MarcDuino Setup commands used to configure various settings on the MarcDuino | YES | |
 

### Panel Commands
They must follow the syntax ":CCxx\\r" where CC=command , xx= two digit decimal number, \\r is carriage return.

| **Command** | **Function** | **Master** | **Slave** | **Remark** |
| --- | --- | --- | --- | --- |
| :SExx | launches sequences, see below | YES | YES | |
| :OPxx | open panel number xx=01-13. If xx=00, opens all panels (12/13 Slave only) | YES | YES | |
| :OP14 | open top panels | YES | NO | tbd |
| :OP15 | open bottom panels | YES | NO | tbd |
| :CLxx | close panel number xx=01-13, removes from RC if it was, stops servo. If xx=00, all panels, slow close. | YES | YES | |
| :RCxx | places panel xx=01-13 under RC input control. If xx=00, all panels placed on RC. | YES | NO | |
| :STxx | buzz kill/soft hold: removes panel from RC control AND shuts servo off to eliminate buzz. xx=00 all panels off RC servos off. | YES | YES | |
| :HDxx | RC hold: removes from RC, but does not turn servo off, keeps at last position. xx=00 all panels hold. | YES | NO | |

### Sequence Command Details
See sequence\_command, panel sequence matrices defined in panel\_sequences.h

| **Command** | **Function** | **Remark** |
| --- | --- | --- |
| | **Full (Move, Sound, Display…)** | |
| :SE00 | Close all panels (full speed), servo off - use as init only. Use CL00 for all soft close. | |
| :SE01 | Scream, with all panels open | |
| :SE02 | Wave, one panel at a time | |
| :SE03 | Fast (Smirk) back and forth wave | |
| :SE04 | Wave 2 (open progressively all panels, then close one by one) | |
| :SE05 | Beep Cantina (with marching ants panel action) | |
| :SE06 | Faint/Short Circuit | |
| :SE07 | Cantina dance (orchestral, rythmic panel dance) | |
| :SE08 | Leia | |
| :SE09 | Disco | |
| :SE10 | Quite Mode reset (panel close, stop holos, stop sounds) | |
| :SE11 | Full Awake Mode reset (panel close, random sound, holo movement, no holo lights) | |
| :SE12 | Top Panels to RC | |
| :SE13 | Mid Awake Mode reset (panel close, random sound, stop holos) | |
| :SE14 | Awake+ Mode reset ((panel close, random sound, holo movement, lights on) | |
| :SE15 | Screams no panels | |
| :SE16 | Panel Wiggle | |
| | | |
| | **Body Sequences** | |
| :SE30 | Utility ARM open and close sequence | |
| :SE31 | All Body Panels open and close sequence | |
| :SE32 | All Body Doors open and wiggle close sequence | |
| :SE33 | Body - Use Gripper | |
| :SE34 | Body - Use Interface Tool| |
| :SE35 | Body - Ping Pong Body Doors| |
| | | |
| | **Move Panels only** | |
| :SE51 | Scream, with all panels open | |
| :SE52 | Wave, one panel at a time | |
| :SE53 | Fast (Smirk) back and forth wave | |
| :SE54 | Wave 2 (open progressively all panels, then close one by one) | |
| :SE55 | Marching ants | |
| :SE56 | Faint/Short Circuit | |
| :SE57 | Rhythmic panel dance | |
| :SE58 | Panel Wave Bye Bye | |
| :SE59 | Open panels half way | |

### Holo Projector Commands
These commands are only processed by the MarcDuino Slave module

| **Command** | **Function** | **Remark** |
| --- | --- | --- |
| \*RDxx | Random Holo movement (xx=01 to 03). xx=00 and >3 all random. | |
| \*ONxx | Turns Holo Light on (xx=01 to 03). xx=00 or >3 all lights on | |
| \*OFxx | Turns Holo Lights off (xx=01 to 03). xx=00 turns all lights off | |
| \*RCxx | Holo vertical movement under RC control, horizontal centered (xx=01-03). 00 or >3 all RC | |
| \*TExx | Holo movement test (xx=01-03). Goes through a loop of holo movements to assist in adjusting holo servos mechanical setup. 00 or >3 all HPs to test | |
| \*STxx | stop/reset Holos random movement, turns lights off, and RC off. 00=all off | |
| \*HDxx | hold: stop holo, do not change light level. 00=all stopped | |
| \*MOxx | magic panel on. xx=01 to 98, on from 1 to 98 seconds.<br><br>* xx = 99 is on permanently<br> <br>* xx = 00 is off | |
| \*MFxx | magic panel flicker xx=1 to 99 flicker for 1 to 99 seconds. 00= off. | |
| \*H1xx<br><br>\*H2xx<br><br>\*H3xx<br><br>\*H0xx | Will turn on-board HP1, 2, 3, and all (HP0xx) for xx seconds.<br><br>* xx = 99 is on permanently<br> <br>* xx = 00 is off | |
| \*F1xx<br><br>\*F2xx<br><br>\*F3xx<br><br>\*F0xx | Will flicker on-board HP1, 2, 3, and all (F0xx) for xx seconds.<br><br>* xx = 99 is on permanently<br> <br>* xx = 00 is off | |

### Sound Commands

These commands are only processed by the MarcDuino Master module

| **Command** | **Function** | **Remark** |
| --- | --- | --- |
| $xyy | Play sound command by bank/sound numbers<br><br>* x=bank number<br> <br>* yy=sound number. If none, next sound is played in. | |
| $xy | Play sound command by bank/sound numbers, short version<br><br>* x=bank number<br> <br>* y=sound number. If none, next sound is played in. | |
| $C | random from 4 first banks | |
| $O | sound off | |
| $L | Leia message (bank 7 sound 1) | |
| $C | Cantina music (bank 9 sound 5) | |
| $c | Beep cantina (bank 9 sound 1) | |
| $S | Scream (bank 6 sound 1) | |
| $F | Faint/Short Circuit (bank 6 sound 3) | |
| $D | Disco (bank 9 sound 6) | |
| $s | stop sounds | |
| $+ | volume up | |
| $- | volume down | |
| $m | volume mid | |
| $f | volume max | |
| $p | volume min | |
| $W | Star Wars music (bank 9 sound 2) | |
| $w | Beep Star Wars music (bank 9 sound 7) | |
| $M | Imperial March (bank 9 sound 3) | |
| $i | Beep Imperial March (bank 9 sound 8) | |
| $B | Startup Sound | |

### Special Features

| **Command** | **Function** | **Remark** |
| --- | --- | --- |
| \*EOxx<br><br>TO SLAVE | Pull pin high/low on AUX1. Can be used to trigger a smoke machine as an example.<br><br>xx is the time in seconds.<br><br>* 00 - off<br> <br>* 01-98 is the time in seconds (don't use values >10 for smoke machines!)<br> <br>* 99 on permanently (again don't use for smoke machines) | will be executed on SLAVE only |
| :EOxx | Pull pin high/low on AUX1. Can be used to trigger a smoke machine as an example.<br><br>xx is the time in seconds.<br><br>* 00 - off<br> <br>* 01-98 is the time in seconds (don't use values >10 for smoke machines!)<br> <br>* 99 on permanently (again don't use for smoke machines) | will be executed on MASTER only<br><br>MarcDuino Firmware V4 and greater |

### Setup Commands
| **Command** | **Function** | **Remark** |
| --- | --- | --- |
| | **Servo Controls** | |
| #SD00 | Set global servo direction forward | |
| #SD01 | Set global servo direction reversed | |
| #SRxxy | Set individual servo to either forward or reversed xx=servo number y=direction<br><br>* Must be a 2 digit Servo number i.e. Servo 4 is 04<br> <br>* Must be either 0 or 1 to set the direction (0 normal, 1 reversed)<br> <br>* Use SDxx to globally set the Servo direction, then SRxxy to change individual servos. | depricated, removed in future releases |
| #SRxx | Set individual servo to reversed, xx=servo number<br><br>* Must be a 2 digit Servo number i.e. Servo 4 is 04<br> <br>* Use SDxx to globally set the Servo direction, then SRxxy to change individual servos. | MarcDuino Firmware V4 and greater |
| #SNxx | Set individual servo to normal, xx=servo number<br><br>* Must be a 2 digit Servo number i.e. Servo 4 is 04<br> <br>* Use SDxx to globally set the Servo direction, then SRxxy to change individual servos. | MarcDuino Firmware V4 and greater |
| #SVxx | Use individual servo settings (0 = no, 1 = yes) | MarcDuino Firmware V4 and greater |
| #SOxxdddd | Set Servo Degrees/Microseconds for Panel Open, dddd=0000-0180 deg, dddd > 0544 Microseconds | MarcDuino Firmware V4 and greater |
| #SCxxdddd | Set Servo Degrees/Microseconds for Panel Closed dddd=0000-0180 deg, dddd > 0544 Microseconds | MarcDuino Firmware V4 and greater |
| #SPxxddd | Set Servo Speed, ddd=0-255 | MarcDuino Firmware V4 and greater |
| | **Startup Sound Controls** | |
| #SSxx | Set startup sound<br><br>* #SS00 : Disable Startup Sound, and remove startup sound delay for fast boot of R2<br> <br>* #SS01 : Default Startup Sound in file 255<br> <br>* #SS02 : Alternate Startup Sound in file 254<br> <br>* #SS03 : Second Alternate Startup Sound in file 253 | depricated, removed in future releases |
| #SSxxx | Set startup sound<br><br>* #SS000 : Disable Startup Sound, and remove startup sound delay for fast boot of R2<br> <br>* #SSxxx : Set Startup Sound in file xxx | MarcDuino Firmware V4 and greater |
| #SQxx | Chatty / Silent mode<br><br>* #SQ00 : Default Chatty Mode<br> <br>* #SQ01 : Silent on startup | |
| #SMxx | Disable Random Sound<br><br>* #SM00 : Random Sound on <br> #SM01 : No Random Sound + Volume off <br> #SM02 : No Random Sound | What’s the difference between Chatty and Random Sounds (#SQxx)?<br><br>maybe depricated |
| #SXxx | Set Max Random Pause in seconds. - Maximum timespan between two random sounds | MarcDuino Firmware V4 and greater |
| #SYxx | Set Min Random Pause in seconds - Minimum timespan between two random sounds | MarcDuino Firmware V4 and greater |
| | **Panel Sequencer Controls** | |
| #STxx | Setup Delay time between Master and Slave Panel Sequence. Use this if the Slave panels are starting too soon. Values up to 250 are supported. Values are in ms. | maybe depricated |
| | **System Configuration and Management** | |
| #MDxx | Set MarcDuino Mode<br><br>* #MD00 : MarcDuino Dome Master<br> <br>* #MD01 : MarcDuino Dome Slave<br> <br>* #MD02 : MarcDuino Body Master<br> <br><br>MarcDuino will reboot immediately after setup and start up in new mode. | MarcDuino Firmware V4 and greater |
| #MPxx | Set MP3-Player Type<br><br>* #MP00 : SparkFun MP3 Trigger<br> <br>* #MP01 : DFPlayer<br> <br>* #MP02 : Vocalizer | MarcDuino Firmware V4 and greater |
| #MSxyy | Set maximum sounds per soundbank. x=1-9 (Soundbank), y=0-25 (max. Sounds) | MarcDuino Firmware V4 and greater |
| #HLxy | Set HoloLight x to High Active (y=1) or Low Active (y=0). x=0 → All Holo Lights | |
| #HOxxdddd | Set Holo HServo Degrees/Microseconds Max, dddd=0000-0180 deg, dddd > 0544 Microseconds | MarcDuino Firmware V4 and greater |
| #HCxxdddd | Set Holo HServo Degrees/Microseconds Min, dddd=0000-0180 deg, dddd > 0544 Microseconds | MarcDuino Firmware V4 and greater |
| #HPxxddd | Set Holo HServo Speed, ddd=0-255 | MarcDuino Firmware V4 and greater |
| #VOxxdddd | Set Holo VServo Degrees/Microseconds Max, dddd=0000-0180 deg, dddd > 0544 Microseconds | MarcDuino Firmware V4 and greater |
| #VCxxdddd | Set Holo VServo Degrees/Microseconds Min dddd=0000-0180 deg, dddd > 0544 Microseconds | MarcDuino Firmware V4 and greater |
| #VPxxddd | Set Holo VServo Speed, ddd=0-255 | MarcDuino Firmware V4 and greater |
| #DUxx | Dump EEPORM to serial<br><br>* #DUxx : value at address xx<br> <br>* #DUMP : dump complete EEPROM content | MarcDuino Firmware V4 and greater |
| #RSET | Restart MarcDuino | MarcDuino Firmware V4 and greater |
| #ADxx | Adjustment Mode: When setting up individual Servo settings, servo will positioned immediately<br><br>* #AD00 : Adjustment Mode Off<br> <br>* #AD01 : Adjustment Mode On | MarcDuino Firmware V4 and greater |

## EEPROM Memory Map
All the settings of the “Setup Commands” are stored in EEPROM. The corresponding Memory Map is described here. Default settings when EEPROM is empty are written in **bold** letter.

| **Address** | **Type** | **Content** | **Description** |
| --- | --- | --- | --- |
| 0x00 | byte | SW-/Config-Version | Version 4.0.x = 40, Version 4.1.x = 41, … |
| 0x01 | byte | MarcDuinoType | **0 = DomeMaster**<br><br>1 = DomeSlave<br><br>2 = BodyMaster |
| 0x02 | byte | Startup Sound | 0 = none<br><br>**1 = File255**<br><br>2 = File254<br><br>3 = File253<br><br>DEPRICATED by Startup Sound Nr |
| 0x03 | byte | Chatty/Silent Mode | **0 = Chatty**<br><br>1 = Silent |
| 0x04 | byte | MP3-Player-Type | **0 = SparkFun MP3-Trigger**<br><br>1 = DF-Mini Player |
| 0x05 | byte | Disable Random Sound | **0 = Random Sound**<br><br>1 = No Random Sound + Volume off<br><br>2 = No Random Sound<br><br>DEPRICATED, collision with Chatty/Silent mode switch |
| 0x06 | word | Slave Delay | Sequence Delay for Slave Sequence Start in ms |
| 0x07 | | Slave Delay | |
| 0x08 | | Number of Servos | |
| 0x09 | | Startup Sound Nr | obsoletes “Startup Sound”, **default 255** |
| 0x0a | | MinRandomPause in seconds | Minimal Pause between two Random sounds played, **default 6s** |
| 0x0b | | MaxRandomPause in seconds | MAximal Pause between two Random sounds played, **default 12s** |
| | | | |
| 0x11 - 0x19 | bytes | Max Sound Bank 1-9 | 1-25 Songs per Bank, default standard SD-Card-Layout (Bank-Sounds): **1-19, 2-18, 3-7, 4-4, 5-3, 6-3, 7-3, 8-6, 9-8** |
| 0x20 | byte | Global Servo Direction | **0 = Normal**<br><br>1 = Reverse |
| 0x21-0x2d | bytes | Servo1-Servo13 Servo Direction | **0 = Normal**<br><br>1 = Reverse |
| 0x30 | byte | Global Servo Speed | 0 = Minumum<br><br>**255 = Maximum** |
| 0x31-0x3d | bytes | Servo1-Servo13 Servo Speed | 0 = Minumum<br><br>**255 = Maximum** |
| 0x40 | word | Global Servo Open Position Degrees / Microseconds | 0 = 0 deg<br><br>180 = 180 deg<br><br>treat values less than 544 as angles in degrees (valid values in microseconds are handled as microseconds) |
| 0x42-0x5a | words | Servo1-Servo13 Servo Open Position Degrees | 0 = 0 deg<br><br>180 = 180 deg<br><br>treat values less than 544 as angles in degrees (valid values in microseconds are handled as microseconds) |
| 0x60 | word | Global Servo Closed Position Degrees | 0 = 0 deg<br><br>180 = 180 deg<br><br>treat values less than 544 as angles in degrees (valid values in microseconds are handled as microseconds) |
| 0x62-0x7a | words | Servo1-Servo13 Servo Close Position Degrees | 0 = 0 deg<br><br>180 = 180 deg<br><br>treat values less than 544 as angles in degrees (valid values in microseconds are handled as microseconds) |
| 0x80 | word | Global Servo Mid Position Degree | 0 = 0 deg<br><br>180 = 180 deg<br><br>treat values less than 544 as angles in degrees (valid values in microseconds are handled as microseconds) |
| 0x82-0x9a | words | Servo1-Serv013 Servo Mid Position Degree | 0 = 0 deg<br><br>180 = 180 deg<br><br>treat values less than 544 as angles in degrees (valid values in microseconds are handled as microseconds) |
| 0xa0 | word | Global Holo-Servo-H Direction | (0-Normal, 1-Reverse) |
| 0xa1 | word | Global Holo-Servo-V Direction | (0-Normal, 1-Reverse) |
| 0xa2 | word | Servo1 Holo1-Servo-H Direction | (0-Normal, 1-Reverse) |
| 0xa3 | word | Servo2 Holo1-Servo-V Direction | (0-Normal, 1-Reverse) |
| 0xa4 | word | Servo3 Holo2-Servo-H Direction | (0-Normal, 1-Reverse) |
| 0xa5 | word | Servo4 Holo2-Servo-V Direction | (0-Normal, 1-Reverse) |
| 0xa6 | word | Servo5 Holo3-Servo-H Direction | (0-Normal, 1-Reverse) |
| 0xa7 | word | Servo6 Holo3-Servo-V Direction | (0-Normal, 1-Reverse) |
| | | | |
| 0xb0 | word | Global Holo-Servo-H Min Position | Degree (0-180) / Microseconds (>=544) |
| 0xb2 | word | Global Holo-Servo-V Min Position | Degree (0-180) / Microseconds (>=544) |
| 0xb4 | word | Servo1 Holo1-Servo-H Min Position | Degree (0-180) / Microseconds (>=544) |
| 0xb6 | word | Servo2 Holo1-Servo-V Min Position | Degree (0-180) / Microseconds (>=544) |
| 0xb8 | word | Servo3 Holo2-Servo-H Min Position | Degree (0-180) / Microseconds (>=544) |
| 0xba | word | Servo4 Holo2-Servo-V Min Position | Degree (0-180) / Microseconds (>=544) |
| 0xbc | word | Servo5 Holo3-Servo-H Min Position | Degree (0-180) / Microseconds (>=544) |
| 0xbe | word | Servo6 Holo3-Servo-V Min Position | Degree (0-180) / Microseconds (>=544) |
| | | | |
| 0xc0 | word | Global Holo-Servo-H Max Position | Degree (0-180) / Microseconds (>=544) |
| 0xc2 | word | Global Holo-Servo-V Max Position | Degree (0-180) / Microseconds (>=544) |
| 0xc4 | word | Servo1 Holo1-Servo-H Max Position | Degree (0-180) / Microseconds (>=544) |
| 0xc6 | word | Servo2 Holo1-Servo-V Max Position | Degree (0-180) / Microseconds (>=544) |
| 0xc8 | word | Servo3 Holo2-Servo-H Max Position | Degree (0-180) / Microseconds (>=544) |
| 0xca | word | Servo4 Holo2-Servo-V Max Position | Degree (0-180) / Microseconds (>=544) |
| 0xcc | word | Servo5 Holo3-Servo-H Max Position | Degree (0-180) / Microseconds (>=544) |
| 0xce | word | Servo6 Holo3-Servo-V Max Position | Degree (0-180) / Microseconds (>=544) |
| | | | |
| 0xd1 | word | Holo1 Light | High Active (=1) or Low Active (=0) |
| 0xd2 | word | Holo2 Light | High Active (=1) or Low Active (=0) |
| 0xd3 | word | Holo3 Light | High Active (=1) or Low Active (=0) |
| | | | |
| 0xe0 | word | Global Holo-Servo-H Speed | (0-255) |
| 0xe1 | word | Global Holo-Servo-V Speed | (0-255) |
| 0xe2 | word | Servo1 Holo1-Servo-H Speed | (0-255) |
| 0xe3 | word | Servo2 Holo1-Servo-V Speed | (0-255) |
| 0xe4 | word | Servo3 Holo2-Servo-H Speed | (0-255) |
| 0xe5 | word | Servo4 Holo2-Servo-V Speed | (0-255) |
| 0xe6 | word | Servo5 Holo3-Servo-H Speed | (0-255) |
| 0xe7 | word | Servo6 Holo3-Servo-V Speed | (0-255) | 


<!--stackedit_data:
eyJoaXN0b3J5IjpbLTE4ODcxNjIzMDAsNjE3Mjk4Nzg4LDI3NT
kzNzI1NywtMTE3ODAwMzc5NiwzNzU5NzM5MzgsLTE3MzI3NjMw
NDIsMTM0OTU5ODI2NSwxMzc4Nzg1NTQ5LC0yMDAwOTE3NzYzLD
E2MzI0MzgyMSwtMTA2NDQ1MTQ3NCw1ODYzODA4MjksLTE4NzA3
MzA1MDcsLTIxMzM4MDM2OTIsNzIwMDQwOTk0LC0yMTk3MzkyMT
hdfQ==
-->
