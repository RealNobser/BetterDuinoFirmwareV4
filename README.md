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
|MarcDuino V1.5 Rev3  |YES  |



<!--stackedit_data:
eyJoaXN0b3J5IjpbLTEzMDIzMzAsNzIwMDQwOTk0LC0yMTk3Mz
kyMThdfQ==
-->