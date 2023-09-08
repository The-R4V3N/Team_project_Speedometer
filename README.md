# <div align="center">Hey 👋, I'm The-R4V3N!</div>  

----

## <div align="center"> Connect with me  

<div align="center">
 <a href="https://github.com/The-R4V3N" target="_blank">
<img src=https://img.shields.io/badge/github-%2324292e.svg?&style=for-the-badge&logo=github&logoColor=white alt=github style="margin-bottom: 5px;" />
<a href="https://dev.to/ther4v3n" target="_blank">
<img src=https://img.shields.io/badge/dev.to-%2308090A.svg?&style=for-the-badge&logo=dev.to&logoColor=white alt=devto style="margin-bottom: 5px;" />
</a>
<a href="https://linkedin.com/in/oliver-joisten" target="_blank">
<img src=https://img.shields.io/badge/linkedin-%231E77B5.svg?&style=for-the-badge&logo=linkedin&logoColor=white alt=linkedin style="margin-bottom: 5px;" />
</a>
<a href="https://www.facebook.com/oliver.joisten" target="_blank">
<img src=https://img.shields.io/badge/facebook-%232E87FB.svg?&style=for-the-badge&logo=facebook&logoColor=white alt=facebook style="margin-bottom: 5px;" />
</a>

</a>  
</div>
  
## Welcome! Glad to see you here  

## Team_project_Speedometer

  ![License](https://img.shields.io/badge/license-MIT-blue.svg)

The `Team` project is a C++ application that uses Qt6 for its client and server desktop applications and allows for UART and TCP communication protocols.

[Speedometer/Server.webm](https://github.com/The-R4V3N/Team_project_Speedometer/assets/18666373/0624a7d9-fe47-4a98-9f1e-089d70114931)


## Prerequisites

- **CMake** version 3.22 or higher
- **Qt6** with the following components: Core, Widgets, Multimedia, and SerialPort
- **PlatformIO** (for building and uploading firmware to the ESP32)

## Building and Running

### Desktop Client and Server

To compile and run the client and server applications on the desktop:

```bash
rm -r * && cmake .. && make && ./server && ./client
```

### Firmware for ESP32
To build the firmware for the ESP32 server:

```bash
cmake --build . --target build_server_firmware
```

To upload the built firmware to the ESP32 server:

```bash
cmake --build . --target upload_server_firmware
```
To build the firmware for the ESP32 client:

```bash
cmake --build . --target build_client_firmware
```
To upload the built firmware to the ESP32 client:

```bash
cmake --build . --target upload_client_firmware
```
## Communication Protocols

By default, the TCP communication protocol is used. If you want to switch to the UART communication protocol, modify the `CMakeLists.txt`:

```bash
set(UARTCOM ON) # Switch this to ON for UART
```
## Directory Structure

- `client/desktop` - Contains the source code and headers for the desktop client application
- `server/desktop` - Contains the source code and headers for the desktop server application
- `client/esp32` - Contains the firmware code for the ESP32 client
- `server/esp32` - Contains the firmware code for the ESP32 server

## Dependencies

- **Qt6**: Used for building the GUI and handling multimedia components for both the client and server.
- **Qt6::SerialPort**: Used for UART communication when enabled.

## Contributions

Feel free to submit pull requests or raise issues if you find any.

## License

This project is licensed under the MIT License. Feel free to use and modify the code according to the terms of the license.
  
- 👨‍💻 All about me is at [My Website](https://www.oliver-joisten.se/)
