# pidOffsetToHex

**pidOffsetToHex** is a lightweight C++ utility designed to extract ASLR (Address Space Layout Randomization) offsets for a running process in Linux. It reads the base address from `/proc/<pid>/maps` and can compute absolute addresses given a relative address from disassembly.

---

⚙️ Requirements

    Operating System: Linux (x86-64 bit architecture)
    Compiler: g++ with C++20 support
    Permissions: Requires appropriate permissions to access /proc/<pid>/maps (typically run as root for system processes)


## 🛠 Features
- **Extracts ASLR offsets:** Retrieves the base address of a process using its PID.
- **Computes absolute addresses:** Optionally takes a second argument as a relative address and returns the absolute address.
- **Command-line utility:** Simple to use via terminal commands.

---

📥 Installation

Clone the repository:

    git clone https://github.com/yourusername/pidOffsetToHex.git
    cd pidOffsetToHex

🚀 Usage

Compile the program:

    make

Run via:

    ./pidOffsetToHex <pid> [relative_hex_address]

Examples:

Extract the ASLR offset:

    ./pidOffsetToHex 1234

Get absolute address from a relative address:

    ./pidOffsetToHex 1234 0x400

🛡 License

This project is licensed under the MIT License. See the LICENSE file for details.
