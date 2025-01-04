#include <iostream>
#include <cstring>
#define MAX_ROOMS 100
using namespace std;

class Room {
protected:
    char type;
    char stype;
    char ac;
    int roomNumber;
    int rent;
    int status; // 0 = available, 1 = reserved

public:
    Room() {
        roomNumber = 0;
        rent = 0;
        status = 0;
        type = 'N';
        stype = 'S';
        ac = 'N';
    }

    void initializeRoom(int rno, char acType, char comfortType, char sizeType, int dailyRent) {
        roomNumber = rno;
        ac = acType;
        type = comfortType;
        stype = sizeType;
        rent = dailyRent;
        status = 0; // Set as available by default
    }

    void displayRoomDetails() const {
        cout << "\nRoom Number: " << roomNumber;
        cout << "\nType AC/Non-AC (A/N): " << ac;
        cout << "\nType Comfort (S/N): " << type;
        cout << "\nType Size (B/S): " << stype;
        cout << "\nRent: " << rent;
        cout << "\nStatus: " << (status == 1 ? "Reserved" : "Available") << "\n";
    }

    int getRoomNumber() const {
        return roomNumber;
    }

    int getStatus() const {
        return status;
    }

    void setStatus(int stat) {
        status = stat;
    }
};

class CustomerRoom : public Room {
protected:
    char customerName[100];
    char customerAddress[100];
    char customerPhone[12];
    char from_date[20];
    char to_date[20];
    float paymentAdvance;
    int bookingID;

public:
    CustomerRoom() {
        paymentAdvance = 0.0;
        bookingID = 0;
        strcpy(customerName, "");
        strcpy(customerAddress, "");
        strcpy(customerPhone, "");
        strcpy(from_date, "");
        strcpy(to_date, "");
    }

    void checkIn(int rno, Room rooms[], int count) {
        bool found = false;
        for (int i = 0; i < count; i++) {
            if (rooms[i].getRoomNumber() == rno) {
                found = true;
                if (rooms[i].getStatus() == 1) {
                    cout << "\nRoom is Already Reserved.\n";
                    return;
                }

                // Input booking details
                cout << "\nEnter Booking Details:";
                cout << "\nBooking ID: ";
                cin >> bookingID;
                cin.ignore();
                cout << "Customer Name: ";
                cin.getline(customerName, 100);
                cout << "Address: ";
                cin.getline(customerAddress, 100);
                cout << "Phone: ";
                cin >> customerPhone;
                cout << "From Date: ";
                cin >> from_date;
                cout << "To Date: ";
                cin >> to_date;
                cout << "Advance Payment: ";
                cin >> paymentAdvance;

                rooms[i].setStatus(1); // Reserve the room
                cout << "\nCustomer Checked-In Successfully!\n";
                return;
            }
        }
        if (!found) {
            cout << "\nRoom Not Found.\n";
        }
    }
};

int main() {
    Room rooms[MAX_ROOMS];
    int roomCount = 0;

    int choice;
    do {
        system("cls");
        cout << "\n### Hotel Management System ###";
        cout << "\n1. Add Room";
        cout << "\n2. Search Room";
        cout << "\n3. Check-In";
        cout << "\n4. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
          
            case 1: {
                if (roomCount < MAX_ROOMS) {
                    int rno, rent;
                    char ac, type, size;

                    cout << "\nEnter Room Number: ";
                    cin >> rno;
                    cout << "Type AC/Non-AC (A/N): ";
                    cin >> ac;
                    cout << "Type Comfort (S/N): ";
                    cin >> type;
                    cout << "Type Size (B/S): ";
                    cin >> size;
                    cout << "Daily Rent: ";
                    cin >> rent;

                    bool exists = false;
                    for (int i = 0; i < roomCount; i++) {
                        if (rooms[i].getRoomNumber() == rno) {
                            exists = true;
                            break;
                        }
                    }

                    if (exists) {
                        cout << "\nRoom Number Already Exists.\n";
                    } else {
                        rooms[roomCount].initializeRoom(rno, ac, type, size, rent);
                        roomCount++;
                        cout << "\nRoom Added Successfully.\n";
                    }
                } else {
                    cout << "\nMaximum Room Limit Reached.\n";
                }
                break;
            }

            case 2: {
                int rno;
                cout << "\nEnter Room Number to Search: ";
                cin >> rno;

                bool found = false;
                for (int i = 0; i < roomCount; i++) {
                    if (rooms[i].getRoomNumber() == rno) {
                        found = true;
                        cout << "\nRoom Found:";
                        rooms[i].displayRoomDetails();
                        break;
                    }
                }
                if (!found) {
                    cout << "\nRoom Not Found.\n";
                }
                break;
            }

            case 3: {
                if (roomCount == 0) {
                    cout << "\nNo Rooms Available. Add Rooms First.\n";
                } else {
                    int rno;
                    cout << "\nEnter Room Number for Check-In: ";
                    cin >> rno;

                    CustomerRoom customer;
                    customer.checkIn(rno, rooms, roomCount);
                }
                break;
            }

            case 4:
                cout << "\nThank you for using the Hotel Management System.\n";
                break;

            default:
                cout << "\nInvalid Choice. Try Again.\n";
        }
        system("pause");
    } while (choice != 4);

    return 0;
}