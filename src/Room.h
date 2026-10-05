#ifndef ROOM_H
#define ROOM_H

#include <string>

class Room {
private:
    int roomNumber;
    std::string type;
    double price;
    int capacity;
    std::string status; // AVAILABLE, RESERVED, OCCUPIED

public:
    Room();
    Room(int number, std::string t, double p, int cap, std::string s = "AVAILABLE");

    int getRoomNumber() const;
    std::string getType() const;
    double getPrice() const;
    int getCapacity() const;
    std::string getStatus() const;
    bool isAvailable() const;

    void setType(std::string t);
    void setPrice(double p);
    void setCapacity(int cap);
    void setStatus(std::string s);

    void display() const;
};

#endif
