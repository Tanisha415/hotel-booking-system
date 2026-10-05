#ifndef HOTELSYSTEM_H
#define HOTELSYSTEM_H

#include <vector>
#include <string>
#include "Room.h"
#include "Guest.h"
#include "Booking.h"

class HotelSystem {
private:
    std::vector<Room> rooms;
    std::vector<Guest> guests;
    std::vector<Booking> bookings;

    void saveData();
    void loadData();
    int calculateNights(std::string checkIn, std::string checkOut);
    double calculateTotal(double pricePerNight, int nights);

    Room* findRoom(int roomNumber);
    Guest* findGuest(int guestId);
    Guest* findGuestByUsername(std::string username);
    Booking* findBooking(int bookingId);

public:
    HotelSystem();
    ~HotelSystem();

    // Guest operations
    int registerGuest(std::string name, std::string phone, std::string email, std::string address, std::string username, std::string password);
    int getGuestIdByUsername(std::string username);
    std::string getGuestPassword(std::string username);
    bool guestLogin(std::string username, std::string password);
    bool adminLogin(std::string username, std::string password);

    // Room operations
    void viewAllRooms();
    void viewAvailableRooms();
    bool addRoom(int roomNumber, std::string type, double price, int capacity);
    bool removeRoom(int roomNumber);

    // Booking operations
    int createBooking(int guestId, int roomNumber, std::string checkIn, std::string checkOut, int numGuests);
    void viewAllBookings();
    void viewGuestBookings(int guestId);
    bool cancelBooking(int bookingId);
    void generateBill(int bookingId);
};

#endif
