#ifndef GUEST_H
#define GUEST_H

#include <string>

class Guest {
private:
    int guestId;
    std::string name;
    std::string phone;
    std::string email;
    std::string address;
    std::string username;
    std::string password;

public:
    Guest();
    Guest(int id, std::string n, std::string p, std::string e, std::string a, std::string u, std::string pwd);

    int getGuestId() const;
    std::string getName() const;
    std::string getPhone() const;
    std::string getEmail() const;
    std::string getAddress() const;
    std::string getUsername() const;
    std::string getPassword() const;

    void display() const;
};

#endif
