#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Passenger {
public:
    int ticketNo;
    string name;
    int age;
    string gender;
    string source;
    string destination;

    void input(int tNo) {
        ticketNo = tNo;
        cin.ignore();
        cout << "\nEnter Passenger Name: ";
        getline(cin, name);

        cout << "Enter Age: ";
        cin >> age;

        cout << "Enter Gender: ";
        cin >> gender;

        cout << "Enter Source Station: ";
        cin >> source;

        cout << "Enter Destination Station: ";
        cin >> destination;
    }

    void display() {
        cout << "\nTicket No: " << ticketNo;
        cout << "\nName: " << name;
        cout << "\nAge: " << age;
        cout << "\nGender: " << gender;
        cout << "\nFrom: " << source;
        cout << "\nTo: " << destination;
        cout << "\n---------------------------";
    }
};

int generateTicketNo() {
    ifstream file("reservations.txt");
    string line;
    int count = 1000;

    while (getline(file, line))
        count++;

    file.close();
    return count;
}

void bookTicket() {
    Passenger p;
    ofstream file("reservations.txt", ios::app);

    int ticketNo = generateTicketNo();
    p.input(ticketNo);

    file << ticketNo << "," << p.name << "," << p.age << ","
         << p.gender << "," << p.source << ","
         << p.destination << endl;

    file.close();

    cout << "\nTicket Booked Successfully!";
    cout << "\nYour Ticket Number is: " << ticketNo << endl;
}

void viewReservations() {
    ifstream file("reservations.txt");
    string line;

    cout << "\n===== Reservation List =====\n";
    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
}

void searchPassenger() {
    ifstream file("reservations.txt");
    string line, name;
    bool found = false;

    cin.ignore();
    cout << "\nEnter Passenger Name to Search: ";
    getline(cin, name);

    while (getline(file, line)) {
        if (line.find(name) != string::npos) {
            cout << line << endl;
            found = true;
        }
    }

    if (!found)
        cout << "Passenger not found!\n";

    file.close();
}

void cancelTicket() {
    ifstream file("reservations.txt");
    ofstream temp("temp.txt");
    string line;
    int ticketNo;
    bool found = false;

    cout << "\nEnter Ticket Number to Cancel: ";
    cin >> ticketNo;

    while (getline(file, line)) {
        if (line.find(to_string(ticketNo)) == string::npos) {
            temp << line << endl;
        } else {
            found = true;
        }
    }

    file.close();
    temp.close();

    remove("reservations.txt");
    rename("temp.txt", "reservations.txt");

    if (found)
        cout << "Ticket Cancelled Successfully!\n";
    else
        cout << "Ticket Not Found!\n";
}

int main() {
    int choice;

    do {
        cout << "\n====== Railway Reservation System ======\n";
        cout << "1. Book Ticket\n";
        cout << "2. View All Reservations\n";
        cout << "3. Search Passenger\n";
        cout << "4. Cancel Ticket\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            bookTicket();
            break;
        case 2:
            viewReservations();
            break;
        case 3:
            searchPassenger();
            break;
        case 4:
            cancelTicket();
            break;
        case 5:
            cout << "Exiting Program...\n";
            break;
        default:
            cout << "Invalid Choice!\n";
        }
    } while (choice != 5);

    return 0;
}
