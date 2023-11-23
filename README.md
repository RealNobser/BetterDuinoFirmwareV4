# MarcDuinoV4

## What is the MarcDuino system?
(from https://www.curiousmarc.com/r2-d2/marcduino-system):

"The MarcDuino system controls the animatronics of an R2 (dome panels, light and sound). It currently controls 10 dome panels, an "MP3 Trigger" sound board, dome "Teeces" lights and holoprojectors light and movements, and I2C gizmos you can add-in yourself. It has lots of pre-programmed effects making all these act together.

The system is centered around the MarcDuino boards which sit in the R2. There are two kinds, the Master and the Slave board, which are very similar to each other." - CuriousMarc

## What is MarcDuinoV4
The MarcDuinoV4 software is a **firmware replacement** for the original MarcDuino V1.5Rev3 boards. 

Details about the **boards** can be found here:
https://www.curiousmarc.com/r2-d2/marcduino-system/marcduino-boards/marcduino-v1-5

The **original firmware** can be found here:
https://www.curiousmarc.com/r2-d2/marcduino-system/marcduino-software-reference

There also is a **spinoff** of Marcs firmware also known as **MarcDuinoMain V3** and **MarcDuinoClient V3**:
https://github.com/nhutchison/MarcDuinoMain
https://github.com/nhutchison/MarcDuinoClient

***MarcDuinoV4 has nothing to do with the original firmware made by Marc nor with the spinoff made by Neil! So if you have any questions about MarcDuinoV4 don't ask any of them!***

## Why MarcDuinoV4?
The last update to the original firmware was in 2018. Neil's last update was a minor change in mid-2022. His V3 software has about 80% of the original source in common, adding some features for the latest MarcDuino boards (servo controllers and EXT/AUX pin controllers). He also added the nice feature of saving settings to EEPROM at runtime. But the code also has some glitches and bugs and is based on outdated Arduino libraries. I started 2023 after the whole Arduino framework and community has made really great progress in the last 5 years.

The MarcDuinoV4 code has completely been rewritten from scratch. I took Neils idea of the EEPROM storage a step further, so nearly ***any*** setting is stored there. Including per-servo position settings. I also added the new panel animation of Tim Hebel who is also using a modified MarcDuino V3 firmware (https://github.com/Eebel/SHADOW_MD_EEBEL),

## Lets get started
### Supported Boards
|Board|Support|
|--|--|
|MarcDuino V1.5 Rev3|YES|
|MarcDuino V1.5 Rev2|not yet, but planned, tests  pending|
|MarcDuino V1 | NO |
|MarcDuino V2 | NO |
### Uploading firmware using *.hex files
- Download the latest hex-Files from the GitHub Repository: https://github.com/RealNobser/MarcDuinoV4/releases
- ... (to be defined)

### Development Environment
* Visual Studio Code: https://code.visualstudio.com/download
* PlatformIO Extension: https://platformio.org/install/ide?install=vscode

### Building and uploading firmware using Visual Studio Code
- Clone the GitHub repository using Visual Studio Code (Source Control / Clone Repository)
- Open local folder
- Edit the file "platformio.ini" to match the serial port of your programmer:
`upload_port = /dev/cu.usbmodem141201` (example)
- build the code (PlatformIO / ATmega328P / General / Build)
- upload the code (PlatformIO / ATmega328P / General / Upload)

<!--stackedit_data:
eyJoaXN0b3J5IjpbLTM0MTc3MjIzOCwxNjMyNDM4MjEsLTEwNj
Q0NTE0NzQsNTg2MzgwODI5LC0xODcwNzMwNTA3LC0yMTMzODAz
NjkyLDcyMDA0MDk5NCwtMjE5NzM5MjE4XX0=
-->