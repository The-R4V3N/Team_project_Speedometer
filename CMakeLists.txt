# @brief CMake minimum required version and project name
cmake_minimum_required(VERSION 3.22)
project(GROUP-A)

# @brief Set C++ standard to 17 and enable C++ standard requirement
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# @brief Enable UART communication protocol
set(UARTCOM OFF) #Set to "ON" to use UART communication protocol, otherwise set it to "OFF" to use TCP communication protocol.

# @brief Set client directory and headers and sources
set(CLIENT_DIR client/desktop)
set(CLIENT_HEADERS shared/setting.h ${CLIENT_DIR}/include/window.h ${CLIENT_DIR}/include/canvas.h ${CLIENT_DIR}/include/comservice.h) 
set(CLIENT_SOURCES ${CLIENT_DIR}/main.cpp ${CLIENT_DIR}/src/window.cpp ${CLIENT_DIR}/src/canvas.cpp ${CLIENT_DIR}/src/comservice.cpp)
set(CLIENT_LIBRARIES Qt6::Core Qt6::Widgets Qt6::Multimedia)

# @brief Set server directory and headers and sources
set(SERVER_DIR server/desktop)
set(SERVER_HEADERS shared/setting.h ${SERVER_DIR}/include/window.h ${SERVER_DIR}/include/comservice.h)
set(SERVER_SOURCES ${SERVER_DIR}/main.cpp ${SERVER_DIR}/src/window.cpp ${SERVER_DIR}/src/comservice.cpp)
set(SERVER_LIBRARIES Qt6::Core Qt6::Widgets)

# @brief Set the UART variable to "ON" to use UART communication protocol, otherwise set it to "TCP" to use TCP communication protocol.
if (${UARTCOM} MATCHES ON)
    add_compile_definitions(UARTCOM) 

    set(CLIENT_LIBRARIES ${CLIENT_LIBRARIES} Qt6::SerialPort)
    set(CLIENT_HEADERS ${CLIENT_HEADERS} ${CLIENT_DIR}/include/uartservice.h)
    set(CLIENT_SOURCES ${CLIENT_SOURCES} ${CLIENT_DIR}/src/uartservice.cpp)

    set(SERVER_LIBRARIES ${SERVER_LIBRARIES} Qt6::SerialPort)
    set(SERVER_HEADERS ${SERVER_HEADERS} ${SERVER_DIR}/include/uartservice.h)
    set(SERVER_SOURCES ${SERVER_SOURCES} ${SERVER_DIR}/src/uartservice.cpp)

else()
    set(CLIENT_HEADERS ${CLIENT_HEADERS} ${CLIENT_DIR}/include/tcpservice.h)
    set(CLIENT_SOURCES ${CLIENT_SOURCES} ${CLIENT_DIR}/src/tcpservice.cpp)

    set(SERVER_HEADERS ${SERVER_HEADERS} ${SERVER_DIR}/include/tcpservice.h)
    set(SERVER_SOURCES ${SERVER_SOURCES} ${SERVER_DIR}/src/tcpservice.cpp)
endif()

# @brief Find Qt6 Core and Widgets packages
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Multimedia SerialPort)

# @brief Add server executable and link libraries
add_executable(server ${SERVER_HEADERS} ${SERVER_SOURCES})
target_link_libraries(server PUBLIC ${SERVER_LIBRARIES})
target_include_directories(server PUBLIC shared ${SERVER_DIR}/include)

# @brief Add client executable and link libraries
add_executable(client ${CLIENT_HEADERS} ${CLIENT_SOURCES})
target_link_libraries(client PUBLIC ${CLIENT_LIBRARIES})
target_include_directories(client PUBLIC shared ${CLIENT_DIR}/include)


# Add custom target for building firmware for the ESP32
# cmake --build . --target build_server_firmware

add_custom_target(build_server_firmware
    COMMAND pio run
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/server/esp32
    COMMENT "Building firmware for ESP32...(server)"
)

# Add custom target for uploading firmware to the ESP32
# cmake --build . --target upload_server_firmware

add_custom_target(upload_server_firmware
    COMMAND pio run -t upload
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/server/esp32
    COMMENT "Uploading firmware to ESP32..."
)

# Add custom target for building firmware for the client
# cmake --build . --target build_client_firmware

add_custom_target(build_client_firmware
    COMMAND pio run
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/client/esp32
    COMMENT "Building firmware for ESP32...(client)"
)

# Add custom target for uploading firmware to the client
# cmake --build . --target upload_client_firmware

add_custom_target(upload_client_firmware
    COMMAND pio run -t upload
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/client/esp32
    COMMENT "Uploading firmware to ESP32...(client)"
)

# @brief Use the code snippet down below in the terminal to run the compile and run the project!
# @code
# rm -r * && cmake .. && make && ./server && ./client
# @endcode

