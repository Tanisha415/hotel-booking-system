#include "Room.h"
#include <iostream>
#include <iomanip>

Room::Room() : roomNumber(0), type("Standard"), price(0.0), capacity(1), status("AVAILABLE") {}

Room::Room(int number, std::string t, double p, int cap, std::string s)
    : roomNumber(number), type(t), price(p), capacity(cap), status(s) {}

int Room::getRoomNumber() const { return roomNumber; }
std::string Room::getType() const { return type; }
double Room::getPrice() const { return price; }
int Room::getCapacity() const { return capacity; }
std::string Room::getStatus() const { return status; }
bool Room::isAvailable() const { return status == "AVAILABLE"; }

void Room::setType(std::string t) { type = t; }
void Room::setPrice(double p) { price = p; }
void Room::setCapacity(int cap) { capacity = cap; }
void Room::setStatus(std::string s) { status = s; }

void Room::display() const {
    std::cout << "Room #" << std::setw(4) << std::left << roomNumber
              << " | Type: " << std::setw(10) << type
              << " | Price: $" << std::setw(8) << std::fixed << std::setprecision(2) << price
              << " | Cap: " << std::setw(2) << capacity
              << " | Status: " << status << "\n";
}
