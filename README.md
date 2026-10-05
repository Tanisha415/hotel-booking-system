# Hotel Booking Management System

A simple **console-based Hotel Booking Management System** developed in
**C++17** using Object-Oriented Programming and file handling.

## 1. Project Overview

The Hotel Booking Management System provides a menu-driven way to manage
hotel rooms, customers, bookings, cancellations, and bills.

The project is designed as an academic C++ project to demonstrate:

-   Object-Oriented Programming
-   Classes and objects
-   Encapsulation
-   Vectors
-   File handling
-   Basic authentication
-   Booking and room-status management

The application runs through a terminal/console and does not require a
database.

## 2. Main Features

### Customer Features

-   Customer registration
-   Customer login
-   View available rooms
-   Book a room
-   View personal bookings
-   Cancel a booking
-   View bill
-   Logout

### Admin Features

-   Admin login
-   View all rooms
-   Add a room
-   Remove an available room
-   View all bookings
-   Logout

## 3. Technologies Used

  Technology       Purpose
  ---------------- ----------------------------------------------
  C++17            Application development
  OOP              Organizing the system into classes
  `vector`         Storing rooms, guests and bookings in memory
  `ifstream`       Reading saved data
  `ofstream`       Writing saved data
  `getline()`      Reading file/input lines
  `stringstream`   Parsing comma-separated records
  GCC/G++          Compiling the project

## 4. Project Structure

``` text
hotel-booking-system/
│
├── src/
│   ├── main.cpp
│   ├── HotelSystem.cpp
│   ├── HotelSystem.h
│   ├── Room.cpp
│   ├── Room.h
│   ├── Guest.cpp
│   ├── Guest.h
│   ├── Booking.cpp
│   ├── Booking.h
│   ├── Billing.cpp
│   └── Billing.h
│
├── data/
│   └── (project data directory)
│
├── tests/
│   └── test_cases.md
│
├── rooms.dat
├── guests.dat
├── bookings.dat
├── README.md
├── LICENSE
├── Makefile
└── .gitignore
```

## 5. Class Design

### `Room`

Stores information about a hotel room:

-   Room number
-   Room type
-   Price per night
-   Capacity
-   Room status

Example room types:

-   Standard
-   Deluxe
-   Suite

### `Guest`

Stores customer information:

-   Guest ID
-   Name
-   Phone
-   Email
-   Address
-   Username
-   Password

### `Booking`

Stores reservation information:

-   Booking ID
-   Guest ID
-   Room number
-   Check-in date
-   Check-out date
-   Number of guests
-   Booking status
-   Total amount

### `HotelSystem`

Acts as the main controller of the application.

It manages:

-   Rooms
-   Guests
-   Bookings
-   Registration
-   Login
-   Room management
-   Booking creation
-   Booking cancellation
-   Billing

### `Billing`

Provides billing-related functionality used by the booking system.

## 6. File Handling

The project uses files instead of a database for persistent storage.

The current application uses:

``` text
rooms.dat
guests.dat
bookings.dat
```

`ofstream` is used to save data, while `ifstream` is used to load data
when the application starts.

The application uses `getline()` and `stringstream` to read and parse
stored records.

This allows room, guest and booking information to remain available
after the program is closed and opened again.

## 7. Application Flow

``` text
Start Program
      |
      v
Main Menu
      |
      +-------------------+
      |                   |
      v                   v
Customer              Admin
      |                   |
      v                   v
Register/Login       Admin Login
      |
      v
Customer Menu
      |
      +--> View Rooms
      |
      +--> Book Room
      |
      +--> My Bookings
      |
      +--> Cancel Booking
      |
      +--> View Bill
      |
      +--> Logout
```

## 8. Booking Workflow

1.  Customer logs in.
2.  Customer views available rooms.
3.  Customer selects a room.
4.  Customer enters check-in and check-out dates.
5.  Customer enters the number of guests.
6.  The system checks room availability.
7.  A booking ID is generated.
8.  The booking is stored.
9.  The room status changes to `RESERVED`.
10. Booking information is saved to the data file.

## 9. Room Management

The initial system provides five rooms:

  Room   Type         Price   Capacity
  ------ ---------- ------- ----------
  101    Standard     \$100          2
  102    Standard     \$100          2
  201    Deluxe       \$150          3
  202    Deluxe       \$150          3
  301    Suite        \$250          4

Room status can be:

``` text
AVAILABLE
RESERVED
```

## 10. Billing

The current billing calculation applies a **12% tax** to the room
subtotal.

Conceptually:

``` text
Subtotal = Price per night × Number of nights
Tax      = Subtotal × 12%
Total    = Subtotal + Tax
```

> Note: In the current implementation, the night-calculation function is
> simplified and currently returns one night. Date-based night
> calculation can be added as a future enhancement.

## 11. Admin Login

The current application uses the following demo administrator
credentials:

``` text
Username: admin
Password: admin123
```

For a production application, administrator credentials should be stored
securely rather than hard-coded.

## 12. How to Compile

From the project root:

### Windows PowerShell

``` powershell
g++ -std=c++17 src/main.cpp src/HotelSystem.cpp src/Room.cpp src/Guest.cpp src/Booking.cpp -o hotel.exe
```

Run:

``` powershell
.\hotel.exe
```

### Linux / Ubuntu

``` bash
g++ -std=c++17 src/main.cpp src/HotelSystem.cpp src/Room.cpp src/Guest.cpp src/Booking.cpp -o hotel
```

Run:

``` bash
./hotel
```

## 13. Example Main Menu

``` text
===========================================
       HOTEL BOOKING SYSTEM
===========================================
1. Customer Registration
2. Customer Login
3. Admin Login
4. View Available Rooms
5. Exit
===========================================
Enter your choice:
```

## 14. Testing Performed

The application has been tested for:

-   Displaying available rooms
-   Customer registration
-   Customer login
-   Viewing rooms after login
-   Creating a room booking
-   Generating a booking ID
-   Returning to the customer menu
-   Exiting the application

Example successful booking:

``` text
Room Number: 202
Check-in Date: 2026-10-06
Check-out Date: 2026-10-08
Number of Guests: 2

[SUCCESS] Booking created.
Booking ID: 1000
Total Amount: $168.00
```

## 15. Future Enhancements

Possible improvements include:

-   Accurate calculation of nights from check-in/check-out dates
-   Password hashing and stronger authentication
-   Database integration using MySQL or SQLite
-   Online payment support
-   Graphical or web-based interface
-   Better input validation
-   Room search and filtering
-   Booking reports
-   Improved invoice generation

## 16. Limitations

-   The application is currently console-based.
-   Data is stored in local files rather than a database.
-   Administrator credentials are currently hard-coded.
-   Date-based night calculation is simplified in the current
    implementation.
-   The system is intended for academic/demo use rather than production
    deployment.

## 17. Project Link

GitHub Repository:

**https://github.com/Tanisha415/hotel-booking-system**

## 18. Conclusion

The Hotel Booking Management System demonstrates how C++ Object-Oriented
Programming can be used to build a practical hotel management
application.

The project combines classes, objects, vectors, file handling,
authentication, room management, booking operations and billing into a
single console-based system.

It provides a simple foundation that can later be extended with database
storage, secure authentication, accurate date processing and a graphical
or web interface.
