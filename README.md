# ExistOS Connection Suite

## [查看中文版本](README_CN.md)

## Notice
Currently, this program only supports Chinese interface and interaction. Multilingual support may be added in the future.

## Introduction
The ExistOS Connection Suite is a Qt-based application designed to connect, manage, and update HP39GII devices. It provides a user - friendly interface for device connection, disconnection, renaming, updating, and viewing device properties. However, many of the logical functions are yet to be implemented, and the current version is mainly a UI prototype.

## Features
- **Device Connection**: Connect to HP39GII devices.
- **Device Disconnection**: Disconnect from connected devices.
- **Device Renaming**: Rename connected devices.
- **Firmware Update**: Update the firmware of connected devices.
- **Device Properties**: View the properties of connected devices.

## Project Structure
- `main.cpp`: The entry point of the application.
- `mainwindow.*`: The main window of the application, including UI and logic.
- `connectwindow.*`: The window for connecting devices.
- `disconnectwindow.*`: The window for disconnecting devices.
- `update.*`: The window for updating device firmware.
- `about.*`: The window for showing about information.
- `image/`: Contains all the icons used in the application.

## Getting Started
### Prerequisites
- Qt development environment
- Python (required for update checking and updating processes)

### Build and Run
1. Open the `HP39GII_ExistOS_Connect.pro` file in Qt Creator.
2. Configure the build environment.
3. Build and run the application.