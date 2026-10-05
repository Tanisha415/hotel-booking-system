CXX = g++
CXXFLAGS = -std=c++17 -Isrc

TARGET = hotel.exe

SOURCES = src/main.cpp src/HotelSystem.cpp src/Room.cpp src/Guest.cpp src/Booking.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)
	@echo Build complete. Run with: $(TARGET)

clean:
	del $(TARGET) 2>nul
	@echo Cleaned build artifacts.

run: all
	$(TARGET)
