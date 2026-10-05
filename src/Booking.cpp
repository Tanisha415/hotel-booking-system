#include "Booking.h"
#include <iostream>
#include <iomanip>

Booking::Booking() : bookingId(0), guestId(0), roomNumber(0), checkInDate(""), checkOutDate(""),
                     numberOfGuests(0), status("CONFIRMED"), totalAmount(0.0) {}

Booking::Booking(int bId, int gId, int rNum, std::string in, std::string out, int guests, std::string s, double total)
    : bookingId(bId), guestId(gId), roomNumber(rNum), checkInDate(in), checkOutDate(out),
      numberOfGuests(guests), status(s), totalAmount(total) {}

int Booking::getBookingId() const { return bookingId; }
int Booking::getGuestId() const { return guestId; }
int Booking::getRoomNumber() const { return roomNumber; }
std::string Booking::getCheckInDate() const { return checkInDate; }
std::string Booking::getCheckOutDate() const { return checkOutDate; }
int Booking::getNumberOfGuests() const { return numberOfGuests; }
std::string Booking::getStatus() const { return status; }
double Booking::getTotalAmount() const { return totalAmount; }

void Booking::setStatus(std::string s) { status = s; }
void Booking::setTotalAmount(double amount) { totalAmount = amount; }

void Booking::display() const {
    std::cout << "Booking #" << bookingId
              << " | Guest ID: " << guestId
              << " | Room #" << roomNumber
              << " | " << checkInDate << " to " << checkOutDate
              << " | Guests: " << numberOfGuests
              << " | Status: " << status
              << " | Total: $" << std::fixed << std::setprecision(2) << totalAmount << "\n";
}

void Booking::displayBill() const {
    std::cout << "\n=====================================\n";
    std::cout << "           BILL / INVOICE\n";
    std::cout << "=====================================\n";
    std::cout << "Booking ID       : " << bookingId << "\n";
    std::cout << "Room Number      : " << roomNumber << "\n";
    std::cout << "Check-in Date    : " << checkInDate << "\n";
    std::cout << "Check-out Date   : " << checkOutDate << "\n";
    std::cout << "Number of Guests : " << numberOfGuests << "\n";
    std::cout << "-------------------------------------\n";
    std::cout << "TOTAL AMOUNT     : $" << std::fixed << std::setprecision(2) << totalAmount << "\n";
    std::cout << "=====================================\n";
}
