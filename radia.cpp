#include <iostream>
#include <string.h>
#define max 100
using namespace std;

class Room {
protected:
    char type;
    char stype;
    char ac;
    int roomNumber;
    int rent;
    int status;

public:
    Room() {
        roomNumber = 0;
        rent = 0;
        status = 0;
        type = 'N';
        stype = 'S';
        ac = 'N';
    }

    virtual void displayRoomDetails() const {
        cout << "\nRoom Number: " << roomNumber;
        cout << "\nType AC/Non-AC (A/N): " << ac;
        cout << "\nType Comfort (S/N): " << type;
        cout << "\nType Size (B/S): " << stype;
        cout << "\nRent: " << rent;
    }

    Room addRoom(int rno,Room&room) {

        room.roomNumber = rno;
        cout << "\nType AC/Non-AC (A/N): ";
        cin >> room.ac;
        cout << "\nType Comfort (S/N): ";
        cin >> room.type;
        cout << "\nType Size (B/S): ";
        cin >> room.stype;
        cout << "\nDaily Rent: ";
        cin >> room.rent;
        room.status = 0;

        cout << "\nRoom Added Successfully!";
        cin.get();
        return room;
    }

    void searchRoom(int rno, Room rooms[], int count) const {
        bool found = false;
        for (int i = 0; i < count; i++) {
            if (rooms[i].getRoomNumber() == rno) {
                found = true;
                cout << "\nRoom Details\n";
                if (rooms[i].getStatus() == 1) {
                    cout << "\nRoom is Reserved";
                } else {
                    cout << "\nRoom is Available";
                }
                rooms[i].displayRoomDetails();
                cin.get();
                break;
            }
        }
        if (!found) {
            cout << "\nRoom not found";
            cin.get();
        }
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
    CustomerRoom() : paymentAdvance(0.0), bookingID(0) {
        strcpy(customerName, "");
        strcpy(customerAddress, "");
        strcpy(customerPhone, "");
        strcpy(from_date, "");
        strcpy(to_date, "");
    }

    void checkIn(int rno, Room rooms[], int &count) {
        bool found = false;
        for (int i = 0; i < count; i++) {
            if (rooms[i].getRoomNumber() == rno) {
                found = true;
                if (rooms[i].getStatus() == 1) {
                    cout << "\nRoom is Already Booked.";
                    cin.get();
                    return;
                }
                cout << "\nEnter Booking ID: ";
                cin >> bookingID;
                cout << "\nEnter Customer Name: ";
                cin >> customerName;
                cout << "\nEnter Address: ";
                cin >> customerAddress;
                cout << "\nEnter Phone: ";
                cin >> customerPhone;
                cout << "\nEnter From Date: ";
                cin >> from_date;
                cout << "\nEnter To Date: ";
                cin >> to_date;
                cout << "\nEnter Advance Payment: ";
                cin >> paymentAdvance;
                rooms[i].setStatus(1);
                cout << "\nCustomer Checked-In Successfully!";
                cin.get();
                break;
            }
        }
        if (!found) {
            cout << "\nRoom Not Found.";
            cin.get();
        }
    }

    void displayRoomDetails() const  {
        Room::displayRoomDetails();
        if (status == 1) {
            cout << "\nCustomer Name: " << customerName;
            cout << "\nAddress: " << customerAddress;
            cout << "\nPhone: " << customerPhone;
            cout << "\nFrom Date: " << from_date;
            cout << "\nTo Date: " << to_date;
            cout << "\nAdvance Payment: " << paymentAdvance;
        }
    }
};

int main() {
    int opt, rno;
    Room rooms[max];
    int count = 0;
    CustomerRoom crm;

    do {
        system("cls");
        cout << "\n### Hotel Management System ###";
        cout << "\n1. Manage Rooms";
        cout << "\n2. Check-In";
        cout << "\n3. Exit";
        cout << "\n\nEnter Option: ";
        cin >> opt;

        switch (opt) {
            case 1: {
                int choice;
                do {
                    system("cls");
                    cout << "\n### Manage Rooms ###";
                    cout << "\n1. Add Room";
                    cout << "\n2. Search Room";
                    cout << "\n3. Back to Main Menu";
                    cout << "\n\nEnter Option: ";
                    cin >> choice;

                    if (choice == 1) {
                        cout << "\nEnter Room Number: ";
                        cin >> rno;
                        bool exists = false;
                        for (int i = 0; i < count; i++) {
                            if (rooms[i].getRoomNumber() == rno) {
                                exists = true;
                                break;
                            }
                        }
                        if (exists) {
                            cout << "\nRoom Number Already Exists!";
                            cin.get(); // Wait for user input
                        } else {
                       rooms[count].addRoom(rno, rooms[count]);
                            count++;
                        }
                    } else if (choice == 2) {
                        cout << "\nEnter Room Number: ";
                        cin >> rno;
                        rooms[0].searchRoom(rno, rooms, count);
                    }
                } while (choice != 3);
                break;
            }

            case 2:
                if (count == 0) {
                    cout << "\nNo Room Data Available. Please Add Rooms First.";
                    cin.get(); // Wait for user input
                } else {
                    cout << "\nEnter Room Number: ";
                    cin >> rno;
                    crm.checkIn(rno, rooms, count);
                }
                break;

            case 3:
                cout << "\nThank You for Using the Software!";
                break;

            default:
                cout << "\nPlease Enter Correct Option.";
                break;
        }
    } while (opt != 3);

    return 0;
}
