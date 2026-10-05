#ifndef BILLING_H
#define BILLING_H

#include <string>
#include <vector>
#include "Booking.h"
#include "Room.h"
#include "Guest.h"

struct ServiceCharge {
    std::string serviceName;
    double cost;
};

class Billing {
private:
    static constexpr double TAX_RATE = 0.12; // 12% Hotel Occupancy / GST tax

public:
    static int calculateNights(const std::string& checkIn, const std::string& checkOut);
    static double calculateSubtotal(double pricePerNight, int nights, const std::vector<ServiceCharge>& services);
    static double calculateTax(double subtotal);
    static double calculateGrandTotal(double subtotal, double tax);

    static void generateInvoice(const Booking& booking, const Guest& guest, const Room& room,
                                const std::vector<ServiceCharge>& services = {});
};

#endif // BILLING_H
