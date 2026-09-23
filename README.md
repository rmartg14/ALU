# ALU – Arithmetic Logic Unit Simulator

A desktop application that simulates the basic behaviour of an **Arithmetic Logic Unit (ALU)**.

The project was developed in **C++** using the **Qt framework**. It provides a graphical interface to enter numeric values, convert them between different representations, and perform arithmetic or logic-oriented operations through a simple educational interface.

> This repository is maintained as an academic project focused on practising C++, modular program design, binary representation, GUI development, and the separation of presentation logic from computational logic.

## Overview

An Arithmetic Logic Unit is a fundamental component of a CPU. It is responsible for performing arithmetic calculations and logical operations on binary data.

This application provides a graphical simulation of that concept. The user interacts with a Qt desktop interface, while the underlying classes handle:

- Numeric input processing.
- Conversion between numeric representations.
- Arithmetic and logical operations.
- Formatting and displaying results.
- GUI event handling through Qt signals and slots.

The project was built with **Qt Widgets** and uses the **qmake** build system.

## Features

- Desktop graphical user interface built with Qt Widgets.
- Input and output management through a main application window.
- Numeric conversion support through a dedicated conversion module.
- Arithmetic and logic-related calculations implemented in a separate operations module.
- Modular C++ structure using headers and implementation files.
- Event-driven interaction using Qt's signals and slots mechanism.
- qmake project configuration for compilation and execution from Qt Creator or the command line.

## Project Structure

```text
.
└── ALU/
    ├── ALU.pro              # qmake project configuration
    ├── ALU.pro.user         # Local Qt Creator user settings
    ├── main.cpp             # Application entry point
    ├── mainwindow.h         # Main window declaration
    ├── mainwindow.cpp       # Main window behaviour and UI event handling
    ├── mainwindow.ui        # Qt Designer interface definition
    ├── operaciones.h        # Arithmetic and logical operation declarations
    ├── operaciones.cpp      # Arithmetic and logical operation implementations
    ├── conversor.h          # Numeric conversion declarations
    └── conversor.cpp        # Numeric conversion implementations
```

## Architecture

The project follows a simple layered organisation in which the graphical interface delegates computational work to specialised modules.

### Application Entry Point

`main.cpp` creates the Qt application instance and launches the main window.

Its responsibility is limited to application startup, keeping the program bootstrap separate from the user-interface and operation logic.

### User Interface

The graphical interface is defined through three files:

- `mainwindow.ui` contains the visual layout created with **Qt Designer**.
- `mainwindow.h` declares the `MainWindow` class and its interface.
- `mainwindow.cpp` implements the interaction logic associated with interface controls and user actions.

The main window acts as the connection point between the interface and the internal calculation modules. It receives user input, invokes the necessary conversion or operation functions, and displays the resulting values.

### Operations Module

The `operaciones` module contains the core arithmetic and logic-related functionality:

- `operaciones.h` declares the available operations.
- `operaciones.cpp` implements the corresponding algorithms.

Keeping this logic outside `MainWindow` avoids mixing GUI code with computational code. This makes the operations easier to understand, maintain, and extend independently of the graphical interface.

### Conversion Module

The `conversor` module is responsible for numerical representation conversion:

- `conversor.h` declares the conversion-related interface.
- `conversor.cpp` implements the conversion logic.

This separation is particularly useful in an ALU-oriented project, where internal binary representations and display formats are essential to understanding how operations are processed.

## Technologies

| Technology | Purpose |
|---|---|
| C++ | Main implementation language |
| Qt | Cross-platform application framework |
| Qt Widgets | Desktop graphical user interface |
| Qt Designer | Visual UI design through `mainwindow.ui` |
| qmake | Project configuration and build generation |
| Qt Creator | Recommended development environment |

## Build and Run

### Prerequisites

To build the project, install:

- A C++ compiler compatible with the installed Qt version.
- Qt, including the Qt Widgets module.
- qmake, normally included with Qt.
- Optionally, Qt Creator for the easiest development workflow.

### Using Qt Creator

1. Open `ALU/ALU.pro` with Qt Creator.
2. Configure a valid desktop Qt kit.
3. Build the project.
4. Run the application from Qt Creator.

### Using the Command Line

From the `ALU/` directory, generate the Makefile with qmake:

```bash
qmake ALU.pro
```

Then compile the project:

```bash
make
```

On Windows with a MinGW-based Qt installation, the compilation command may be:

```bash
mingw32-make
```

After a successful build, run the generated executable from the build directory.

## Development Notes

- `ALU.pro.user` contains machine-specific Qt Creator configuration and is not required to build the project on another computer. It can be regenerated locally by Qt Creator.
- The project does not include an automated test suite in the repository.
- The main focus is the implementation of ALU-related operations and their integration into a desktop GUI, rather than a command-line interface or web application.
- The code is organised into `.h` declaration files and `.cpp` implementation files, following common C++ development practices.

## Educational Goals

This project was created to practise several core software-development concepts:

- C++ program structure.
- Header and implementation file separation.
- Function and module decomposition.
- Graphical application development with Qt.
- Event-driven programming.
- Qt signals and slots.
- Integration of Qt Designer layouts with C++ code.
- Numeric data representation and conversion.
- Arithmetic and logic operation implementation.
- Build configuration with qmake.

## License

This repository is an academic project. No explicit licence has been defined.
