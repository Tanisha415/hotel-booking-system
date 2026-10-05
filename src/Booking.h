#ifndef BOOKING_H
#define BOOKING_H

#include <string>

class Booking {
private:
    int bookingId;
    int guestId;
    int roomNumber;
    std::string checkInDate;
    std::string checkOutDate;
    int numberOfGuests;
    std::string status; // CONFIRMED, CANCELLED, CHECKED_OUT
    double totalAmount;

public:
    Booking();
    Booking(int bId, int gId, int rNum, std::string in, std::string out, int guests, std::string s, double total);

    int getBookingId() const;
    int getGuestId() const;
    int getRoomNumber() const;
    std::string getCheckInDate() const;
    std::string getCheckOutDate() const;
    int getNumberOfGuests() const;
    std::string getStatus() const;
    double getTotalAmount() const;

    void setStatus(std::string s);
    void setTotalAmount(double amount);

    void display() const;
    void displayBill() const;
};

#endif
