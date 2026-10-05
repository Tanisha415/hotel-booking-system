#include <iostream>
#include <limits>
#include "HotelSystem.h"

using namespace std;

void clearInput() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void displayMainMenu() {
    cout << "\n===========================================\n";
    cout << "       HOTEL BOOKING SYSTEM\n";
    cout << "===========================================\n";
    cout << "1. Customer Registration\n";
    cout << "2. Customer Login\n";
    cout << "3. Admin Login\n";
    cout << "4. View Available Rooms\n";
    cout << "5. Exit\n";
    cout << "===========================================\n";
    cout << "Enter your choice: ";
}

void displayCustomerMenu() {
    cout << "\n===========================================\n";
    cout << "         CUSTOMER MENU\n";
    cout << "===========================================\n";
    cout << "1. View Rooms\n";
    cout << "2. Book Room\n";
    cout << "3. My Bookings\n";
    cout << "4. Cancel Booking\n";
    cout << "5. View Bill\n";
    cout << "6. Logout\n";
    cout << "===========================================\n";
    cout << "Enter your choice: ";
}

void displayAdminMenu() {
    cout << "\n===========================================\n";
    cout << "          ADMIN MENU\n";
    cout << "===========================================\n";
    cout << "1. View All Rooms\n";
    cout << "2. Add Room\n";
    cout << "3. Remove Room\n";
    cout << "4. View All Bookings\n";
    cout << "5. Logout\n";
    cout << "===========================================\n";
    cout << "Enter your choice: ";
}

void customerMenu(HotelSystem& hotel, int guestId) {
    int choice;

    while (true) {
        displayCustomerMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                hotel.viewAvailableRooms();
                break;
            case 2: {
                int roomNumber, numGuests;
                string checkIn, checkOut;
                cout << "\n--- Book Room ---\n";
                cout << "Room Number: ";
                cin >> roomNumber;
                cout << "Check-in Date (YYYY-MM-DD): ";
                cin >> checkIn;
                cout << "Check-out Date (YYYY-MM-DD): ";
                cin >> checkOut;
                cout << "Number of Guests: ";
                cin >> numGuests;

                hotel.createBooking(guestId, roomNumber, checkIn, checkOut, numGuests);
                break;
            }
            case 3:
                hotel.viewGuestBookings(guestId);
                break;
            case 4: {
                int bookingId;
                cout << "\n--- Cancel Booking ---\n";
                cout << "Booking ID: ";
                cin >> bookingId;
                hotel.cancelBooking(bookingId);
                break;
            }
            case 5: {
                int bookingId;
                cout << "\n--- View Bill ---\n";
                cout << "Booking ID: ";
                cin >> bookingId;
                hotel.generateBill(bookingId);
                break;
            }
            case 6:
                cout << "\n[INFO] Logging out...\n";
                return;
            default:
                cout << "\n[ERROR] Invalid choice.\n";
        }

        cout << "\nPress ENTER to continue...";
        clearInput();
        cin.get();
    }
}

void adminMenu(HotelSystem& hotel) {
    int choice;

    while (true) {
        displayAdminMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                hotel.viewAllRooms();
                break;
            case 2: {
                int roomNumber, capacity;
                double price;
                string type;

                cout << "\n--- Add Room ---\n";
                cout << "Room Number: ";
                cin >> roomNumber;
                cout << "Type (Standard/Deluxe/Suite): ";
                cin >> type;
                cout << "Price per Night: ";
                cin >> price;
                cout << "Capacity: ";
                cin >> capacity;

                hotel.addRoom(roomNumber, type, price, capacity);
                break;
            }
            case 3: {
                int roomNumber;
                cout << "\n--- Remove Room ---\n";
                cout << "Room Number: ";
                cin >> roomNumber;
                hotel.removeRoom(roomNumber);
                break;
            }
            case 4:
                hotel.viewAllBookings();
                break;
            case 5:
                cout << "\n[INFO] Logging out...\n";
                return;
            default:
                cout << "\n[ERROR] Invalid choice.\n";
        }

        cout << "\nPress ENTER to continue...";
        clearInput();
        cin.get();
    }
}

int main() {
    HotelSystem hotel;

    int choice;

    while (true) {
        displayMainMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                string name, phone, email, address, username, password;
                cout << "\n--- Customer Registration ---\n";
                cout << "Name: ";
                clearInput();
                getline(cin, name);
                cout << "Phone: ";
                getline(cin, phone);
                cout << "Email: ";
                getline(cin, email);
                cout << "Address: ";
                getline(cin, address);
                cout << "Username: ";
                getline(cin, username);
                cout << "Password: ";
                getline(cin, password);

                hotel.registerGuest(name, phone, email, address, username, password);
                break;
            }
            case 2: {
                string username, password;
                cout << "\n--- Customer Login ---\n";
                cout << "Username: ";
                cin >> username;
                cout << "Password: ";
                cin >> password;

                int guestId = hotel.getGuestIdByUsername(username);
                if (guestId != -1 && hotel.getGuestPassword(username) == password) {
                    cout << "\n[SUCCESS] Login successful!\n";
                    customerMenu(hotel, guestId);
                } else {
                    cout << "\n[ERROR] Invalid username or password.\n";
                }
                break;
            }
            case 3: {
                string username, password;
                cout << "\n--- Admin Login ---\n";
                cout << "Username: ";
                cin >> username;
                cout << "Password: ";
                cin >> password;

                if (hotel.adminLogin(username, password)) {
                    cout << "\n[SUCCESS] Admin login successful!\n";
                    adminMenu(hotel);
                } else {
                    cout << "\n[ERROR] Invalid username or password.\n";
                }
                break;
            }
            case 4:
                hotel.viewAvailableRooms();
                break;
            case 5:
                cout << "\n===========================================\n";
                cout << "       THANK YOU FOR USING\n";
                cout << "       HOTEL BOOKING SYSTEM\n";
                cout << "===========================================\n";
                return 0;
            default:
                cout << "\n[ERROR] Invalid choice.\n";
        }

        cout << "\nPress ENTER to continue...";
        clearInput();
        cin.get();
    }

    return 0;
}
