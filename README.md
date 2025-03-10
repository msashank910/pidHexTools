# pidOffsetToHex

**pidOffsetToHex** is a lightweight C++ utility designed to extract ASLR (Address Space Layout Randomization) offsets for a running process in Linux. It reads the base address from `/proc/<pid>/maps` and can compute absolute addresses given a relative address from disassembly.

---

## 🛠 Features
- **Extracts ASLR offsets:** Retrieves the base address of a process using its PID.
- **Computes absolute addresses:** Optionally takes a second argument as a relative address and returns the absolute address.
- **Command-line utility:** Simple to use via terminal commands.

---

## 🚀 Usage
Compile the program:

    cd pidOffsetToHex
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
