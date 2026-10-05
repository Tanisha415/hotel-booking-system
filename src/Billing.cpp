#include "Billing.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>

int Billing::calculateNights(const std::string& checkIn, const std::string& checkOut) {
    std::tm tmIn = {};
    std::tm tmOut = {};

    int y1, m1, d1, y2, m2, d2;
    char sep1, sep2, sep3, sep4;

    std::istringstream issIn(checkIn);
    std::istringstream issOut(checkOut);

    if ((issIn >> y1 >> sep1 >> m1 >> sep2 >> d1) &&
        (issOut >> y2 >> sep3 >> m2 >> sep4 >> d2)) {
        
        tmIn.tm_year = y1 - 1900;
        tmIn.tm_mon  = m1 - 1;
        tmIn.tm_mday = d1;
        tmIn.tm_hour = 12;

        tmOut.tm_year = y2 - 1900;
        tmOut.tm_mon  = m2 - 1;
        tmOut.tm_mday = d2;
        tmOut.tm_hour = 12;

        std::time_t timeIn = std::mktime(&tmIn);
        std::time_t timeOut = std::mktime(&tmOut);

        if (timeIn != -1 && timeOut != -1 && timeOut > timeIn) {
            double seconds = std::difftime(timeOut, timeIn);
            int days = static_cast<int>(seconds / (60 * 60 * 24));
            return (days > 0) ? days : 1;
        }
    }
    return 1; // Default fallback to 1 night
}

double Billing::calculateSubtotal(double pricePerNight, int nights, const std::vector<ServiceCharge>& services) {
    double total = pricePerNight * nights;
    for (const auto& s : services) {
        total += s.cost;
    }
    return total;
}

double Billing::calculateTax(double subtotal) {
    return subtotal * TAX_RATE;
}

double Billing::calculateGrandTotal(double subtotal, double tax) {
    return subtotal + tax;
}

void Billing::generateInvoice(const Booking& booking, const Guest& guest, const Room& room,
                             const std::vector<ServiceCharge>& services) {
    int nights = calculateNights(booking.getCheckInDate(), booking.getCheckOutDate());
    double roomTotal = room.getPricePerNight() * nights;
    double servicesTotal = 0.0;
    for (const auto& s : services) {
        servicesTotal += s.cost;
    }
    double subtotal = roomTotal + servicesTotal;
    double tax = calculateTax(subtotal);
    double grandTotal = calculateGrandTotal(subtotal, tax);

    std::cout << "\n=======================================================\n";
    std::cout << "                  HOTEL INVOICE / RECEIPT              \n";
    std::cout << "=======================================================\n";
    std::cout << " Booking Reference ID : " << booking.getBookingId() << "\n";
    std::cout << " Guest Name           : " << guest.getName() << "\n";
    std::cout << " Contact Phone        : " << guest.getPhone() << "\n";
    std::cout << " Room Number & Type   : Room #" << room.getRoomNumber()
              << " (" << room.getTypeString() << ")\n";
    std::cout << " Duration of Stay     : " << booking.getCheckInDate() << " to "
              << booking.getCheckOutDate() << " (" << nights << " night" << (nights > 1 ? "s" : "") << ")\n";
    std::cout << " Number of Occupants  : " << booking.getNumberOfGuests() << "\n";
    std::cout << "-------------------------------------------------------\n";
    std::cout << " Item Description                 Rate/Cost      Total\n";
    std::cout << "-------------------------------------------------------\n";
    std::cout << " Room Tariff (" << std::setw(2) << nights << " nights @ $"
              << std::fixed << std::setprecision(2) << room.getPricePerNight() << ")     $"
              << std::setw(8) << roomTotal << "\n";

    if (!services.empty()) {
        for (const auto& svc : services) {
            std::cout << " Service: " << std::setw(22) << std::left << svc.serviceName
                      << std::right << "          $" << std::setw(8) << svc.cost << "\n";
        }
    }

    std::cout << "-------------------------------------------------------\n";
    std::cout << " Subtotal:                                      $" << std::setw(8) << subtotal << "\n";
    std::cout << " Hotel Tax (12%):                               $" << std::setw(8) << tax << "\n";
    std::cout << "=======================================================\n";
    std::cout << " FINAL AMOUNT DUE / PAID:                       $" << std::setw(8) << grandTotal << "\n";
    std::cout << "=======================================================\n\n";
}
