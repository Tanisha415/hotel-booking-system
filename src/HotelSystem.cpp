#include "HotelSystem.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

HotelSystem::HotelSystem() {
    loadData();
    if (rooms.empty()) {
        // Add default rooms
        rooms.push_back(Room(101, "Standard", 100.0, 2, "AVAILABLE"));
        rooms.push_back(Room(102, "Standard", 100.0, 2, "AVAILABLE"));
        rooms.push_back(Room(201, "Deluxe", 150.0, 3, "AVAILABLE"));
        rooms.push_back(Room(202, "Deluxe", 150.0, 3, "AVAILABLE"));
        rooms.push_back(Room(301, "Suite", 250.0, 4, "AVAILABLE"));
        saveData();
    }
}

HotelSystem::~HotelSystem() {
    saveData();
}

void HotelSystem::saveData() {
    std::ofstream roomFile("rooms.dat");
    for (const auto& r : rooms) {
        roomFile << r.getRoomNumber() << "," << r.getType() << ","
                 << r.getPrice() << "," << r.getCapacity() << "," << r.getStatus() << "\n";
    }
    roomFile.close();

    std::ofstream guestFile("guests.dat");
    for (const auto& g : guests) {
        guestFile << g.getGuestId() << "," << g.getName() << ","
                  << g.getPhone() << "," << g.getEmail() << ","
                  << g.getAddress() << "," << g.getUsername() << "," << g.getPassword() << "\n";
    }
    guestFile.close();

    std::ofstream bookingFile("bookings.dat");
    for (const auto& b : bookings) {
        bookingFile << b.getBookingId() << "," << b.getGuestId() << ","
                    << b.getRoomNumber() << "," << b.getCheckInDate() << ","
                    << b.getCheckOutDate() << "," << b.getNumberOfGuests() << ","
                    << b.getStatus() << "," << b.getTotalAmount() << "\n";
    }
    bookingFile.close();
}

void HotelSystem::loadData() {
    std::ifstream roomFile("rooms.dat");
    if (roomFile.is_open()) {
        std::string line;
        while (std::getline(roomFile, line)) {
            std::stringstream ss(line);
            std::string token;
            int num, cap;
            double price;
            std::string type, status;

            std::getline(ss, token, ','); num = std::stoi(token);
            std::getline(ss, type, ',');
            std::getline(ss, token, ','); price = std::stod(token);
            std::getline(ss, token, ','); cap = std::stoi(token);
            std::getline(ss, status, ',');

            rooms.push_back(Room(num, type, price, cap, status));
        }
        roomFile.close();
    }

    std::ifstream guestFile("guests.dat");
    if (guestFile.is_open()) {
        std::string line;
        while (std::getline(guestFile, line)) {
            std::stringstream ss(line);
            std::string token;
            int id;
            std::string name, phone, email, address, username, password;

            std::getline(ss, token, ','); id = std::stoi(token);
            std::getline(ss, name, ',');
            std::getline(ss, phone, ',');
            std::getline(ss, email, ',');
            std::getline(ss, address, ',');
            std::getline(ss, username, ',');
            std::getline(ss, password, ',');

            guests.push_back(Guest(id, name, phone, email, address, username, password));
        }
        guestFile.close();
    }

    std::ifstream bookingFile("bookings.dat");
    if (bookingFile.is_open()) {
        std::string line;
        while (std::getline(bookingFile, line)) {
            std::stringstream ss(line);
            std::string token;
            int bookingId, guestId, roomNumber, numGuests;
            std::string checkIn, checkOut, status;
            double total;

            std::getline(ss, token, ','); bookingId = std::stoi(token);
            std::getline(ss, token, ','); guestId = std::stoi(token);
            std::getline(ss, token, ','); roomNumber = std::stoi(token);
            std::getline(ss, checkIn, ',');
            std::getline(ss, checkOut, ',');
            std::getline(ss, token, ','); numGuests = std::stoi(token);
            std::getline(ss, status, ',');
            std::getline(ss, token, ','); total = std::stod(token);

            bookings.push_back(Booking(bookingId, guestId, roomNumber, checkIn, checkOut, numGuests, status, total));
        }
        bookingFile.close();
    }
}

int HotelSystem::calculateNights(std::string checkIn, std::string checkOut) {
    // Simplified: assume 1 night for now
    return 1;
}

double HotelSystem::calculateTotal(double pricePerNight, int nights) {
    double subtotal = pricePerNight * nights;
    double tax = subtotal * 0.12; // 12% tax
    return subtotal + tax;
}

Room* HotelSystem::findRoom(int roomNumber) {
    for (auto& r : rooms) {
        if (r.getRoomNumber() == roomNumber) return &r;
    }
    return nullptr;
}

Guest* HotelSystem::findGuest(int guestId) {
    for (auto& g : guests) {
        if (g.getGuestId() == guestId) return &g;
    }
    return nullptr;
}

Guest* HotelSystem::findGuestByUsername(std::string username) {
    for (auto& g : guests) {
        if (g.getUsername() == username) return &g;
    }
    return nullptr;
}

Booking* HotelSystem::findBooking(int bookingId) {
    for (auto& b : bookings) {
        if (b.getBookingId() == bookingId) return &b;
    }
    return nullptr;
}

int HotelSystem::registerGuest(std::string name, std::string phone, std::string email, std::string address, std::string username, std::string password) {
    if (findGuestByUsername(username) != nullptr) {
        std::cout << "[ERROR] Username already exists.\n";
        return -1;
    }

    int newId = guests.size() + 1;
    guests.push_back(Guest(newId, name, phone, email, address, username, password));
    saveData();
    std::cout << "[SUCCESS] Guest registered. Guest ID: " << newId << "\n";
    return newId;
}

int HotelSystem::getGuestIdByUsername(std::string username) {
    Guest* g = findGuestByUsername(username);
    if (g != nullptr) {
        return g->getGuestId();
    }
    return -1;
}

std::string HotelSystem::getGuestPassword(std::string username) {
    Guest* g = findGuestByUsername(username);
    if (g != nullptr) {
        return g->getPassword();
    }
    return "";
}

bool HotelSystem::guestLogin(std::string username, std::string password) {
    Guest* g = findGuestByUsername(username);
    if (g != nullptr && g->getPassword() == password) {
        return true;
    }
    return false;
}

bool HotelSystem::adminLogin(std::string username, std::string password) {
    return (username == "admin" && password == "admin123");
}

void HotelSystem::viewAllRooms() {
    std::cout << "\n------------------ ALL ROOMS ------------------\n";
    for (const auto& r : rooms) {
        r.display();
    }
    std::cout << "------------------------------------------------\n";
}

void HotelSystem::viewAvailableRooms() {
    std::cout << "\n-------------- AVAILABLE ROOMS --------------\n";
    for (const auto& r : rooms) {
        if (r.isAvailable()) {
            r.display();
        }
    }
    std::cout << "-----------------------------------------------\n";
}

bool HotelSystem::addRoom(int roomNumber, std::string type, double price, int capacity) {
    if (findRoom(roomNumber) != nullptr) {
        std::cout << "[ERROR] Room already exists.\n";
        return false;
    }
    rooms.push_back(Room(roomNumber, type, price, capacity, "AVAILABLE"));
    saveData();
    std::cout << "[SUCCESS] Room added.\n";
    return true;
}

bool HotelSystem::removeRoom(int roomNumber) {
    Room* r = findRoom(roomNumber);
    if (r == nullptr) {
        std::cout << "[ERROR] Room not found.\n";
        return false;
    }
    if (!r->isAvailable()) {
        std::cout << "[ERROR] Cannot remove occupied/reserved room.\n";
        return false;
    }
    for (auto it = rooms.begin(); it != rooms.end(); ++it) {
        if (it->getRoomNumber() == roomNumber) {
            rooms.erase(it);
            saveData();
            std::cout << "[SUCCESS] Room removed.\n";
            return true;
        }
    }
    return false;
}

int HotelSystem::createBooking(int guestId, int roomNumber, std::string checkIn, std::string checkOut, int numGuests) {
    Room* r = findRoom(roomNumber);
    if (r == nullptr) {
        std::cout << "[ERROR] Room not found.\n";
        return -1;
    }
    if (!r->isAvailable()) {
        std::cout << "[ERROR] Room not available.\n";
        return -1;
    }

    int nights = calculateNights(checkIn, checkOut);
    double total = calculateTotal(r->getPrice(), nights);

    int bookingId = bookings.size() + 1000;
    bookings.push_back(Booking(bookingId, guestId, roomNumber, checkIn, checkOut, numGuests, "CONFIRMED", total));

    r->setStatus("RESERVED");
    saveData();

    std::cout << "[SUCCESS] Booking created. Booking ID: " << bookingId << "\n";
    std::cout << "Total Amount: $" << std::fixed << std::setprecision(2) << total << "\n";
    return bookingId;
}

void HotelSystem::viewAllBookings() {
    std::cout << "\n------------------ ALL BOOKINGS ------------------\n";
    for (const auto& b : bookings) {
        b.display();
    }
    std::cout << "----------------------------------------------------\n";
}

void HotelSystem::viewGuestBookings(int guestId) {
    std::cout << "\n-------------- YOUR BOOKINGS --------------\n";
    for (const auto& b : bookings) {
        if (b.getGuestId() == guestId) {
            b.display();
        }
    }
    std::cout << "---------------------------------------------\n";
}

bool HotelSystem::cancelBooking(int bookingId) {
    Booking* b = findBooking(bookingId);
    if (b == nullptr) {
        std::cout << "[ERROR] Booking not found.\n";
        return false;
    }
    if (b->getStatus() != "CONFIRMED") {
        std::cout << "[ERROR] Cannot cancel this booking.\n";
        return false;
    }

    b->setStatus("CANCELLED");
    Room* r = findRoom(b->getRoomNumber());
    if (r != nullptr) {
        r->setStatus("AVAILABLE");
    }
    saveData();
    std::cout << "[SUCCESS] Booking cancelled.\n";
    return true;
}

void HotelSystem::generateBill(int bookingId) {
    Booking* b = findBooking(bookingId);
    if (b == nullptr) {
        std::cout << "[ERROR] Booking not found.\n";
        return;
    }
    b->displayBill();
}
