# 🛠️ pidHexTools 🔍🔢  

**pidHexTools** is a lightweight C++ utility for working with **process ASLR offsets** and **hexadecimal calculations**. It retrieves base addresses for a running process in Linux and optionally computes absolute addresses. If no arguments are provided, it enters an **interactive hex calculator mode** for basic hex arithmetic.

---

## ⚙️ Requirements  

- **Operating System**: Linux (x86-64 architecture)  
- **Compiler**: `g++` with **C++20** support  
- **Permissions**: Requires appropriate permissions to access `/proc/<pid>/maps` (**root privileges** may be needed for certain processes)  

---

## 🛠 Features  

✔️ **Extracts ASLR Offsets** – Retrieves the base address of a process using its **PID**.  
✔️ **Computes Absolute Addresses** – Optionally takes a **relative hex offset** and returns the absolute address.  
✔️ **Interactive Hex Calculator Mode** – If run **without arguments**, it enters an interactive mode for hexadecimal arithmetic.  
✔️ **Command-Line Utility** – Simple, lightweight, and easy to use in terminal commands.  

---

## 📥 Installation  

Clone the repository:  

    git clone https://github.com/yourusername/pidHexTools.git
    d pidHexTools

Compile the program using make:

    make

Alternatively, compile manually with g++:

    g++ -std=c++20 -o pidHexTools pidHexTools.cpp

---

## 🚀 Usage
General Syntax

    sudo ./pidHexTools <flags> [arguments]

Flags:

    -c → Runs in hexadecimal calculator mode (no arguments required).
    -h → Displays the help message.
    -p <PID> → Retrieves the ASLR base address of a process using its PID.
    -f <FILE> → Searches for the base address of a file mapped in /proc/<pid>/maps.
    -o <OFFSET> → Computes the absolute address from a relative hex offset.

### Modes of Operation

#### 1️⃣ Hexadecimal Calculator Mode

Runs with -c and allows basic hex arithmetic.

    ./pidHexTools -c

#### 2️⃣ ASLR Address Resolution Mode

Retrieves the ASLR base address of a running process and optionally computes absolute addresses.

    sudo ./pidHexTools -p <PID>

or

    sudo ./pidHexTools -f <FILEPATH>

Optional relative hex offset calculation:

    sudo ./pidHexTools -p <PID> -o 0x5abc

or

    sudo ./pidHexTools -f /usr/lib/libexample.so -o 0x2000

---

## 📌 Examples

Extract the ASLR base address:

    sudo ./pidHexTools -p 1234

or

    sudo ./pidHexTools -f ./libexample.so

Compute an absolute address from a relative one:

    sudo ./pidHexTools -p 1234 -o 0x1000

Start hexadecimal calculator mode:

    ./pidHexTools -c

Display the help message:

    ./pidHexTools -h

---

## 🛡 License

This project is licensed under the MIT License. See the LICENSE file for details.