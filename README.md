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

[Speedometer-Server.webm](https://github.com/The-R4V3N/Team_project_Speedometer/assets/18666373/7e2d5595-6a1b-4c49-bcd5-09ec9b107a06)



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

- [simonahls](https://github.com/simonahls) - Implemented the Server and the ESP32 Micro-controller code.
- [isse89](https://github.com/isse89) - Implemented Server UART the Server.
- [Supraja493](https://github.com/Supraja493) - Implemented TCP and the Abstract class the client.

## Contributing

Contributions are welcome! If you have any ideas, suggestions, or improvements, please open an issue or submit a pull request.

## License

This project is licensed under the MIT License. Feel free to use and modify the code according to the terms of the license.
  
  ![The-R4V3N](https://github.com/The-R4V3N.png?size=50) More about me can be found on my [Website](https://www.oliver-joisten.se)
