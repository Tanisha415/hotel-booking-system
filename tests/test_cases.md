# Comprehensive Test Plan & Verification Results

This document records the systematic functional, edge-case, and Linux system-level test cases for the **Hotel Booking Management System**.

---

## 1. Room Management Test Cases

| Test ID | Test Scenario | Input Data | Expected Result | Pass/Fail |
|---|---|---|---|---|
| **TC-RM-01** | Add new unique room | Number: 501, Type: Suite, Price: $400.00, Cap: 4 | Room created, added to inventory, persisted to `data/rooms.dat`. | **PASS** |
| **TC-RM-02** | Add duplicate room number | Number: 501 (already existing) | Error message displayed: `Room #501 already exists`. Duplication rejected. | **PASS** |
| **TC-RM-03** | Add room with invalid tariff | Number: 502, Price: -50.00 | Input validation rejects negative values and prompts again. | **PASS** |
| **TC-RM-04** | Search room by type | Search: "Deluxe" | Only rooms categorized as Deluxe are listed. | **PASS** |
| **TC-RM-05** | Delete room in use | Number: 201 (Status: Reserved) | System rejects deletion: `Cannot delete Room #201 because it is currently reserved or occupied`. | **PASS** |
| **TC-RM-06** | Delete available room | Number: 102 (Status: Available) | Room removed from memory and data file updated. | **PASS** |

---

## 2. Guest Management Test Cases

| Test ID | Test Scenario | Input Data | Expected Result | Pass/Fail |
|---|---|---|---|---|
| **TC-GM-01** | Register new guest | Name: "David Warner", Phone: "+1-555-0404", GovID: "PASS-D901" | Guest registered, assigned unique sequential ID, persisted to `data/guests.dat`. | **PASS** |
| **TC-GM-02** | Register duplicate guest | Phone: "+1-555-0101" (Already registered to Alice) | System detects duplicate phone/ID, alerts user, and returns existing Guest ID. | **PASS** |
| **TC-GM-03** | Search guest by name | Query: "Alice" | Returns Alice Johnson's complete profile. | **PASS** |
| **TC-GM-04** | Delete guest with active booking | Guest ID: 1 (Has active reservation) | System prevents deletion: `Cannot delete Guest #1 due to active bookings`. | **PASS** |

---

## 3. Booking & Workflow Test Cases

| Test ID | Test Scenario | Input Data | Expected Result | Pass/Fail |
|---|---|---|---|---|
| **TC-BK-01** | Create valid booking | Guest: 1, Room: 101, Dates: 2026-11-01 to 2026-11-04 (3 nights), Guests: 1 | Booking created (#1003), Room status changed to `Reserved`, bill computed. | **PASS** |
| **TC-BK-02** | Double booking prevention | Guest: 2, Room: 101 (Already Reserved) | Rejected: `Room #101 is not available (Current status: Reserved)`. | **PASS** |
| **TC-BK-03** | Over-capacity booking | Room: 101 (Capacity: 1), Number of Guests: 3 | Rejected: `Number of guests exceeds room capacity`. | **PASS** |
| **TC-BK-04** | Check-in guest | Booking ID: 1003 | Booking status becomes `CheckedIn`, Room 101 status becomes `Occupied`. | **PASS** |
| **TC-BK-05** | Cancel checked-in booking | Booking ID: 1003 | Rejected: `Cannot cancel Booking #1003 because the guest is already checked in`. | **PASS** |
| **TC-BK-06** | Cancel confirmed booking | Booking ID: 1001 (Confirmed) | Booking status becomes `Cancelled`, Room 201 immediately reverts to `Available`. | **PASS** |
| **TC-BK-07** | Check-out guest with services | Booking ID: 1002, Services: Spa ($50), Dining ($30) | Detailed invoice printed, Room 301 returned to `Available`, booking set to `CheckedOut`. | **PASS** |

---

## 4. Billing Test Cases

| Test ID | Test Scenario | Calculation Details | Expected Result | Pass/Fail |
|---|---|---|---|---|
| **TC-BL-01** | 1-night stay tariff | Room: $100/night, Nights: 1 | Subtotal: $100.00, Tax (12%): $12.00, Total: $112.00 | **PASS** |
| **TC-BL-02** | Multi-night with services | Room: $120/night, 3 nights ($360), Laundry: $20, Taxi: $40 | Subtotal: $420.00, Tax (12%): $50.40, Total: $470.40 | **PASS** |

---

## 5. Linux Systems & Persistence Test Cases

| Test ID | Test Scenario | Test Method | Expected Result | Pass/Fail |
|---|---|---|---|---|
| **TC-LX-01** | Data persistence on restart | Add room 999, exit app, restart app. | Room 999 is loaded automatically from `data/rooms.dat`. | **PASS** |
| **TC-LX-02** | Missing data files | Delete `data/*.dat`, start app. | App boots cleanly without crashing, creates empty collections, and logs warnings. | **PASS** |
| **TC-LX-03** | POSIX file permissions | Inspect `ls -l data/guests.dat` | Mode displays `-rw-------` (`0600`), readable only by the owner process. | **PASS** |
| **TC-LX-04** | Multithreading & Audit Log | Perform check-in, check `data/hotel.log` | Log entry present with current timestamp, thread ID, and `[INFO]` tag. | **PASS** |
| **TC-LX-05** | Linux IPC (Named Pipe) | Run app, in second terminal run `cat /tmp/hotel_stats_fifo` | Receives live formatted hotel metrics stream from background thread. | **PASS** |
| **TC-LX-06** | Process Fork & Backup | Select Option 10 ("Backup System Data") | Process forks, executes `tar -czf`, produces valid `data/hotel_backup.tar.gz`. | **PASS** |
| **TC-LX-07** | Kernel Device Driver | `insmod hotel_status_driver.ko` and `cat /dev/hotel_status` | Returns kernel-level status buffer and logs to `dmesg`. | **PASS** |
| **TC-LX-08** | POSIX Signal Handling | Press `Ctrl+C` during menu display | Intercepts `SIGINT`, flushes state safely to disk, exits cleanly. | **PASS** |
