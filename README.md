# Hotel Booking Management System Using C++17 and Linux System Programming

[![Language](https://img.shields.io/badge/Language-C%2B%2B17%20%7C%20C-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B17)
[![Platform](https://img.shields.io/badge/Platform-Linux%20%28Ubuntu%29-orange.svg)](https://ubuntu.com)
[![Standard](https://img.shields.io/badge/Standard-POSIX-green.svg)](https://pubs.opengroup.org/onlinepubs/9699919799/)
[![License](https://img.shields.io/badge/License-MIT-brightgreen.svg)](LICENSE)

---

## 1. Project Title
**Hotel Booking Management System Using C++ and Linux System Programming**  
*A Capstone Project demonstrating C++17 Object-Oriented Software Architecture, POSIX Systems Programming, Inter-Process Communication, and Linux Character Device Drivers.*

---

## 2. Project Overview
The **Hotel Booking Management System** is a robust, modular, and performant Command-Line Interface (CLI) application developed exclusively for Linux operating systems. Designed for evaluation in an academic viva and demonstration setting, the project bridges the gap between high-level business software engineering and low-level Linux systems programming.

It provides complete hotel inventory management, customer profiling, reservation handling, check-in/out workflows, and automated invoice calculation, while natively implementing core POSIX concepts:
- **Discretionary Access Control (`chmod 0600`)** on sensitive guest files.
- **Multithreading (`std::thread`, `std::mutex`)** separating the interactive menu from a background telemetry worker.
- **Inter-Process Communication (IPC)** via POSIX Named Pipes (FIFO `/tmp/hotel_stats_fifo`).
- **Process Creation (`fork()`, `exec()`, `waitpid()`)** for automated data backups.
- **Linux Character Device Driver** module (`/dev/hotel_status`) demonstrating user-to-kernel boundary interaction.

---

## 3. Problem Statement
Commercial hotel applications often require hefty external database engines and browser runtimes, making them poorly suited for lightweight embedded Linux terminals, point-of-sale (POS) systems, or environments where real-time OS-level telemetry and security controls are critical. Furthermore, standard academic projects often implement basic CRUD operations without demonstrating systems programming concepts. 

This project solves this by delivering an end-to-end, zero-dependency, crash-resilient hotel management solution engineered directly on top of the Linux kernel and POSIX API.

---

## 4. Objectives
1. **Core Business Automation**: Manage rooms, guest identities, reservation life cycles, check-in, check-out, and tax invoicing.
2. **Systems Programming Rigor**: Showcase POSIX file permissions, multithreaded concurrency with mutex synchronization, signal handling, and process management.
3. **External Inter-Process Telemetry**: Enable external daemons to read live occupancy metrics using a Linux Named Pipe without disturbing front-desk operators.
4. **Kernel-Space Demonstration**: Provide a dedicated Linux Character Device Driver module to explain Virtual File System (VFS) operations (`open`, `read`, `write`, `release`) and user-kernel memory isolation (`copy_to_user`, `copy_from_user`).
5. **Academic Viva Readiness**: Designed for an effortless, impressive **5–10 minute viva demonstration** with pre-populated demo sample data.

---

## 5. Features
- **Room Management**: Add, update, delete, view, and search rooms across 4 classes (`Single`, `Double`, `Deluxe`, `Suite`) with dynamic state tracking (`Available`, `Reserved`, `Occupied`, `Maintenance`).
- **Guest Management**: Registration, profile updates, and search by Name, Phone, or Government ID.
- **Booking Management**: Intelligent booking engine preventing double-bookings and over-capacity allocations.
- **Fast Check-In & Check-Out**: Real-time status transitions with itemized add-on billing (dining, laundry, spa, transit).
- **Billing & Invoicing**: Automated calculation of nights, room rates, services, and 12% statutory taxes.
- **Data Persistence**: File-backed storage with automatic serialization and deserialization.
- **Live Statistics & IPC Stream**: Real-time room counts streamed to `/tmp/hotel_stats_fifo`.
- **System Audit Logging**: Thread-safe logging to `data/hotel.log` stamped with ISO dates, log levels, and thread IDs.
- **Automated Data Backup**: Uses `fork()` and `tar` to produce compressed `.tar.gz` archives.
- **Linux Kernel Device Driver**: Direct interaction with `/dev/hotel_status`.

---

## 6. Technologies Used
- **Programming Languages**: C++17 (Application Core), C (Linux Kernel Module).
- **Operating System**: Linux (Ubuntu 20.04 / 22.04 / 24.04 LTS recommended).
- **Build System**: GNU Make.
- **Compiler**: GCC / G++ (v9.0 or later).
- **Concurrency**: POSIX threads (`pthread`, `std::thread`, `std::mutex`).
- **IPC Mechanism**: POSIX Named Pipe (FIFO).
- **Kernel Subsystem**: Linux Virtual File System (VFS), Misc Device Subsystem.

---

## 7. Linux Concepts Used
| Concept | Code File | Purpose & Explanation |
|---|---|---|
| **File Permissions (`chmod`)** | `src/FileManager.cpp` | Enforces `0600` permissions on `guests.dat` to protect confidential guest data from unauthorized users. |
| **Multithreading** | `src/HotelSystem.cpp` | Separates user CLI interactions from an asynchronous background monitoring thread. |
| **Mutex Locks (`std::mutex`)** | `src/Logger.cpp`, `src/HotelSystem.cpp` | RAII mutex locks (`std::lock_guard`) eliminate race conditions and guarantee thread safety. |
| **Process Lifecycle (`fork`/`exec`)** | `src/FileManager.cpp` | Child process created via `fork()` transforms into `tar` using `execlp()` while parent waits via `waitpid()`. |
| **Named Pipe / FIFO** | `src/HotelSystem.cpp` | Inter-Process Communication at `/tmp/hotel_stats_fifo` allows external processes to stream live metrics. |
| **Signal Handling** | `src/main.cpp` | Traps `SIGINT` (Ctrl+C) and `SIGTERM` to perform an orderly data flush before exit. |
| **Character Device Driver** | `driver/hotel_status_driver.c` | Virtual device `/dev/hotel_status` exchanging metrics across user/kernel boundary. |

---

## 8. System Architecture

```text
+-----------------------------------------------------------------------------+
|                                USER SPACE                                   |
|                                                                             |
|   +---------------------------------------------------------------------+   |
|   |                       Main CLI Terminal Menu                        |   |
|   +---------------------------------------------------------------------+   |
|                                      |                                      |
|                                      v                                      |
|   +---------------------------------------------------------------------+   |
|   |                   HotelSystem Facade Controller                     |   |
|   |      (Manages Rooms, Guests, Bookings, Billing, & Synchronization)   |   |
|   +---------------------------------------------------------------------+   |
|           |                          |                         |            |
|           v                          v                         v            |
|    +--------------+           +--------------+          +--------------+    |
|    |  Room Engine |           | Guest Engine |          | Booking/Bill |    |
|    +--------------+           +--------------+          +--------------+    |
|           |                          |                         |            |
|           +--------------------------+-------------------------+            |
|                                      |                                      |
|                     +----------------+----------------+                     |
|                     |                                 |                     |
|                     v                                 v                     |
|        +-------------------------+       +-------------------------+        |
|        |     FileManager (POSIX) |       |  Thread-Safe Logger     |        |
|        | (chmod 0600, fork/tar)  |       |  (Mutex Guarded)        |        |
|        +-------------------------+       +-------------------------+        |
|                     |                                 |                     |
|                     v                                 v                     |
|           data/*.dat (Storage)                data/hotel.log                |
|                                                                             |
|                     +---------------------------------+                     |
|                     | Background Worker (std::thread) |                     |
|                     +---------------------------------+                     |
|                                     |                                       |
|                +--------------------+--------------------+                  |
|                |                                         |                  |
|                v                                         v                  |
|    [ POSIX FIFO: /tmp/hotel_stats_fifo ]     [ Character Device: /dev/hotel_status ]
+----------------|-----------------------------------------|------------------+
                 v                                         v
       (External terminal)                     +=======================+
                                               |     KERNEL SPACE      |
                                               | hotel_status_driver.ko|
                                               |  - copy_to_user()     |
                                               |  - copy_from_user()   |
                                               +=======================+
```

---

## 9. Project Structure

```text
hotel-booking-system/
├── Makefile                     # Root build configuration
├── LICENSE                      # MIT Open-Source License
├── README.md                    # Comprehensive master documentation
├── .gitignore                   # Git artifact exclusion rules
├── src/                         # Application source and header files
│   ├── main.cpp                 # CLI menu and signal handlers
│   ├── HotelSystem.h            # Central controller facade
│   ├── HotelSystem.cpp
│   ├── Room.h                   # Room entity declaration
│   ├── Room.cpp
│   ├── Guest.h                  # Guest entity declaration
│   ├── Guest.cpp
│   ├── Booking.h                # Booking lifecycle entity
│   ├── Booking.cpp
│   ├── Billing.h                # Tariff and tax calculations
│   ├── Billing.cpp
│   ├── FileManager.h            # POSIX filesystem manager
│   ├── FileManager.cpp
│   ├── Logger.h                 # Thread-safe logging singleton
│   └── Logger.cpp
├── data/                        # Persistent storage directory
│   ├── rooms.dat                # Delimited room records
│   ├── guests.dat               # Secured guest records (chmod 0600)
│   ├── bookings.dat             # Active and past reservations
│   └── hotel.log                # Real-time system audit log
├── driver/                      # Linux Kernel Character Device Module
│   ├── hotel_status_driver.c    # Character driver implementation
│   ├── Makefile                 # Kernel module build script
│   └── README.md                # Driver architectural documentation
├── docs/                        # Complete technical and viva guides
│   ├── architecture.md          # Architectural deep-dive
│   ├── installation.md          # Build and deployment instructions
│   ├── user-guide.md            # Interactive CLI user manual
│   ├── linux-concepts.md        # Detailed Linux OS concepts explanation
│   ├── device-driver.md         # Kernel module documentation
│   ├── viva-questions.md        # 35 likely viva questions and answers
│   └── presentation.md          # 10-slide presentation and speech script
└── tests/
    └── test_cases.md            # Functional & system test matrices
```

---

## 10. Installation
Ensure an Ubuntu/Debian environment with essential build utilities:

```bash
sudo apt update
sudo apt install -y build-essential linux-headers-$(uname -r) git
```

---

## 11. Compilation
Build the complete project using GNU Make:

```bash
cd hotel-booking-system
make
```

---

## 12. Execution
Run the compiled binary:

```bash
./hotel_booking
```

---

## 13. Device Driver Setup
To compile, load, and test the Linux Character Device Driver:

```bash
# Compile the driver module
make driver

# Insert the module into the Linux kernel
sudo insmod driver/hotel_status_driver.ko

# Verify module insertion and device node
lsmod | grep hotel_status
ls -l /dev/hotel_status

# Read live metrics from the kernel buffer
cat /dev/hotel_status

# Remove module after testing
sudo rmmod hotel_status_driver
```

---

## 14. Sample Usage
Upon launching the CLI menu:
1. Select `11` to load the built-in demo dataset.
2. Select `1` $\rightarrow$ `1` to view loaded rooms.
3. Select `3` $\rightarrow$ `2` to create a new reservation.
4. Select `4` to check in the guest (Room state updates to `Occupied`).
5. Select `5` to check out the guest, add laundry/dining charges, and generate the final bill.
6. Select `7` to inspect live occupancy statistics.
7. Open a separate terminal and run `cat /tmp/hotel_stats_fifo` to view the IPC stream!

---

## 15. Testing
The project includes a comprehensive test suite documented in [tests/test_cases.md](tests/test_cases.md).
To run basic functional tests:
```bash
# 1. Clean build verification
make clean && make

# 2. Verify file permissions
ls -l data/guests.dat
# Expected: -rw------- (0600)

# 3. Verify process backup
# Inside application: choose Option 10
tar -ztvf data/hotel_backup.tar.gz
```

---

## 16. Expected Output

### Invoice Output (Check-Out)
```text
=======================================================
                  HOTEL INVOICE / RECEIPT              
=======================================================
 Booking Reference ID : 1001
 Guest Name           : Alice Johnson
 Contact Phone        : +1-555-0101
 Room Number & Type   : Room #201 (Double)
 Duration of Stay     : 2026-10-10 to 2026-10-13 (3 nights)
 Number of Occupants  : 2
-------------------------------------------------------
 Item Description                 Rate/Cost      Total
-------------------------------------------------------
 Room Tariff ( 3 nights @ $120.00)     $  360.00
 Service: Airport Shuttle                      $   40.00
-------------------------------------------------------
 Subtotal:                                      $  400.00
 Hotel Tax (12%):                               $   48.00
=======================================================
 FINAL AMOUNT DUE / PAID:                       $  448.00
=======================================================
```

---

## 17. Limitations
- **CLI Interface**: Designed strictly for terminal environments; does not offer a graphical desktop or web browser interface.
- **Local Filesystem Persistence**: Uses delimited text files rather than distributed database clusters.
- **Single-Node Execution**: Intended to run on a single Linux host machine.

---

## 18. Future Enhancements
1. **Network Sockets**: Implement a POSIX BSD socket server allowing multiple remote front-desk terminals to connect concurrently.
2. **ACID Transaction Engine**: Integrate an embedded SQLite3 or LMDB database engine for atomic transactions.
3. **Hardware Keycard Dispenser Driver**: Expand the character driver to control a physical smart-card hardware reader.

---

## 19. GitHub Repository Instructions
To push this project to your GitHub account:

```bash
git init
git add .
git commit -m "Initial commit: Complete Hotel Booking Management System (Linux/C++17)"
git branch -M main
git remote add origin https://github.com/<your-username>/hotel-booking-system.git
git push -u origin main
```

---

## 20. Team & Author Information
- **Project**: Capstone Project - Operating Systems & Systems Programming
- **Technology Stack**: C++17, C, Linux POSIX API, Linux Kernel 5.x/6.x
- **Academic Mentor**: Technical Training Faculty
