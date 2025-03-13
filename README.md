# pidHexTools 🔍🔢

**pidHexTools** is a lightweight C++ utility for working with process ASLR offsets and hexadecimal calculations. It retrieves base addresses for a running process in Linux and optionally computes absolute addresses. Additionally, if no command-line arguments are provided, it enters interactive hex calculator mode for basic hex arithmetic.

---

⚙️ Requirements

    Operating System: Linux (x86-64 bit architecture)
    Compiler: g++ with C++20 support
    Permissions: Requires appropriate permissions to access /proc/<pid>/maps (typically run as root for system processes)


## 🛠 Features
- **Extracts ASLR offsets** – Retrieves the base address of a process using its PID.
- **Computes absolute addresses** – Optionally takes a second argument as a relative address and returns the absolute address.
- **Interactive Hex Calculator Mode** – If run without arguments, enters an interactive mode for hexadecimal arithmetic.
- **Command-line utility** – Simple to use via terminal commands.

---

📥 Installation

Clone the repository:

    git clone https://github.com/yourusername/pidHexTools.git
    cd pidHexTools

🚀 Usage

Compile the program:

    make

Run via:

    sudo ./pidHexTools <pid> [relative_hex_address]
or

    ./pidHexTools

Examples:

Extract the ASLR offset:

    sudo ./pidHexTools 1234

Get absolute address from a relative address:

    sudo ./pidHexTools 1234 5abc

Enter hexadecimal calculator mode:

    ./pidHexTools

🛡 License

This project is licensed under the MIT License. See the LICENSE file for details.
