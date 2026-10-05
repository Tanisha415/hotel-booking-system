#include "Guest.h"
#include <iostream>
#include <iomanip>

Guest::Guest() : guestId(0), name(""), phone(""), email(""), address(""), username(""), password("") {}

Guest::Guest(int id, std::string n, std::string p, std::string e, std::string a, std::string u, std::string pwd)
    : guestId(id), name(n), phone(p), email(e), address(a), username(u), password(pwd) {}

int Guest::getGuestId() const { return guestId; }
std::string Guest::getName() const { return name; }
std::string Guest::getPhone() const { return phone; }
std::string Guest::getEmail() const { return email; }
std::string Guest::getAddress() const { return address; }
std::string Guest::getUsername() const { return username; }
std::string Guest::getPassword() const { return password; }

void Guest::display() const {
    std::cout << "Guest ID: " << guestId
              << " | Name: " << name
              << " | Phone: " << phone
              << " | Email: " << email << "\n";
}
