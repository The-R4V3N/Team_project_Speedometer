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
  ![Lines of code](https://tokei.rs/b1/github/The-R4V3N/Team_project_Speedometer)


The `Team` project is a C++ application that uses Qt6 for its client and server desktop applications and allows for UART and TCP communication protocols.

## Table of Contents

- [Media](#media)
- [Features](#features)
- [Prerequisites](#prerequisites)
- [Building](#building)
- [Contributions](#contributions)
- [Contributing](#contributing)
- [License](#license)
- [Future of the project](#future)

## Media

Project Overview

![Overview](https://github.com/The-R4V3N/Team_project_Speedometer/assets/18666373/10b9a0d2-9970-4746-ad4c-bf8cc4520a9e)

Special Thanks to [nkkyviv](https://github.com/nkkyviv) for the Video!

https://github.com/The-R4V3N/Team_project_Speedometer/assets/18666373/f5bed22a-1edd-4351-b1b6-e38ea5e8c8d2

UML Class Diagram

![UML Diagram](https://github.com/The-R4V3N/Team_project_Speedometer/assets/18666373/7df1d3f3-ffb8-4d9d-8ae4-b9396a17386f)

# Features

This project showcases a Speedometer built using C++ and Qt6, accompanied by a server for remote control. It includes built-in features for monitoring temperature and battery levels, as well as turn signal lights and audible alerts. In the event of a disconnection between the server and client, a warning message will promptly notify the user."

## Prerequisites

- **CMake** version 3.22 or higher
- **Qt6** with the following components: Core, Widgets, Multimedia, and SerialPort
- **PlatformIO** (for building and uploading firmware to the ESP32)

## Building

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

- [simonahls](https://github.com/simonahls) - Implemented the Server and the ESP32 Micro-Controller code.
- [isse89](https://github.com/isse89) - Implemented Server gui UART Communication.
- [Supraja493](https://github.com/Supraja493) - Implemented TCP Communication and the Abstract class the client.
- [The-R4V3N](https://github.com/The-R4V3N) - Implemented Client gui and TCP Communication and ESP32 Micro-Controller.
- [nkkyviv](https://github.com/nkkyviv)  - Video creation and Editing

## Contributing

We welcome your contributions! If you have any ideas, suggestions, or improvements, please feel free to open an issue or submit a pull request. Before doing so, please review our [Code of Conduct.](https://github.com/The-R4V3N/Team_project_Speedometer/blob/master/CODE_OF_CONDUCT.md)

## License

This project is licensed under the MIT License. Feel free to use and modify the code according to the terms of the license.

## Future

In the future, this project will include additional features such as a digital clock displaying the current time and an engaging startup sequence.


  
![The-R4V3N](https://github.com/The-R4V3N.png?size=50) More about me can be found on my [Website](https://www.oliver-joisten.se)
