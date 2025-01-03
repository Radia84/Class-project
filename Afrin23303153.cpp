#include <iostream>
using namespace std;
class Room {
protected:
    int roomNumber;
    float rent;
    bool isBooked;
    string guestName;
    string guestPhone;
    float advancePayment;
public:
    Room(int roomNumber = 0, float rent = 0)
    : roomNumber(roomNumber), rent(rent), isBooked(false), guestName(""), guestPhone(""), advancePayment(0) {}
    virtual void displayRoom() {
    cout << "\nRoom Number: " << roomNumber;
    cout << "\nRent: " << rent;
    cout << "\nStatus: " << (isBooked ? "Booked" : "Available") << endl;
    }
    void bookRoom(const string& name, const string& phone, float advance) {
    guestName = name;
    guestPhone = phone;
    advancePayment = advance;
    isBooked = true;
    }
    virtual void checkOut() {
    if (isBooked) {
    float balance = rent - advancePayment;
    cout << "\nCheckout Details for Room Number " << roomNumber;
    cout << "\nCustomer Name: " << guestName;
    cout << "\nAmount Due: " << balance << endl;
    isBooked = false;
    guestName = "";
    guestPhone = "";
    advancePayment = 0;
        } else
        {
        cout << "\nRoom is not currently booked!" << endl;
        }
    }
    bool isRoomBooked() const { return isBooked; }
    int getRoomNumber() const { return roomNumber; }
};
class LuxuryRoom : public Room {
    string luxuryFeature;

public:
    LuxuryRoom(int roomNumber, float rent, const string& feature)
    : Room(roomNumber, rent), luxuryFeature(feature) {}
    void displayRoom() override {
    Room::displayRoom();
    cout << "Luxury Feature: " << luxuryFeature << endl;
    }
};
class HotelManagement {
    Room* rooms[10];
    int totalRooms;

public:
    HotelManagement() : totalRooms(0) {}
    void addRoom(Room* room) {
    if (totalRooms < 10) {
    rooms[totalRooms++] = room;
        }
        else
        {
        cout << "\nNo space for additional rooms!" << endl;
        }
    }
    void checkOut(int roomNumber) {
        for (int i = 0; i < totalRooms; i++) {
        if (rooms[i]->getRoomNumber() == roomNumber && rooms[i]->isRoomBooked()) {
        rooms[i]->checkOut();
        return;
            }
        }
        cout << "\nRoom is not booked or doesn't exist!" << endl;
    }
    void guestSummaryReport() {
        bool noGuests = true;
        cout << "\nGuest Summary Report:\n";
        for (int i = 0; i < totalRooms; i++) {
        if (rooms[i]->isRoomBooked()) {
        noGuests = false;
        rooms[i]->displayRoom();
            }
        }
        if (noGuests)
        {
        cout << "No guests currently checked in!\n";
        }
    }
};

int main() {
    HotelManagement hotel;
    hotel.addRoom(new Room(101, 1500));
    hotel.addRoom(new Room(102, 2000));
    hotel.addRoom(new LuxuryRoom(201, 5000, "Ocean View"));
    int choice;
    do {
    cout << "\nHotel Management System";
    cout << "\n1. Check-Out";
    cout << "\n2. Guest Summary Report";
    cout << "\n3. Exit";
    cout << "\nEnter your choice: ";
    cin >> choice;
        switch (choice)
        {
        case 1: {
        int roomNumber;
        cout << "\nEnter Room Number for Check-Out: ";
        cin >> roomNumber;
        hotel.checkOut(roomNumber);
        break;
            }
        case 2:
        hotel.guestSummaryReport();
        break;
        case 3:
        cout << "\nExiting system. Thank you!";
        break;
        default:
        cout << "\nInvalid choice! Please try again.";
        }
    } while (choice != 3);

    return 0;
}

