#include <iostream>
#include <fstream>
#include <map>
using namespace std;

class Guest
{
public:
    string name, address, password;
    int days, room;
    long long int phone;
    char type;
    int foodBill;

    Guest() : phone(0), days(0), room(0), type('C'), foodBill(0) {}
};

class Hotel
{
    map<int, Guest> rooms;

    int roomCost(char t)
    {
        if (t == 'A')
            return 3000;
        if (t == 'B')
            return 2000;
        return 1000;
    }

    int assignRoom()
    {
        for (int i = 101; i <= 110; ++i)
            if (!rooms.count(i))
                return i;
        return -1;
    }

public:
    void showRoomTypes()
    {
        cout << "\n================================\n";
        cout << "        ROOM TYPES & RATES     \n";
        cout << "===================================\n";
        cout << "A. Deluxe Room     3000/day\n";
        cout << "B. Standard Room   2000/day\n";
        cout << "C. Economy Room    1000/day\n";
    }

    void bookRoom()
    {
        Guest g;
        cout << "Name: ";
        cin >> g.name;
        cout << "Address: ";
        cin >> g.address;
        cout << "Phone: ";
        cin >> g.phone;
        showRoomTypes();
        cout << "Room Type (A/B/C): ";
        cin >> g.type;
        cout << "Days of stay: ";
        cin >> g.days;

        g.password = to_string(g.phone);
        int r = assignRoom();
        if (r == -1)
        {
            cout << "No rooms available.\n";
            return;
        }
        cout << "\nBooking Room...\nAuto-assigned Room: " << r << "\n";
        cout << " Room " << r << " booked.\n🧾 Username: " << g.name
             << " | Password: " << g.password << "\n";
        g.room = r;
        rooms[r] = g;
    }

    void loginPortal()
    {
        string user, pass;
        cout << "\n Login Portal\nUsername: ";
        cin >> user;
        cout << "Password: ";
        cin >> pass;
        for (auto &pair : rooms)
        {
            Guest &g = pair.second;
            if (g.name == user && g.password == pass)
            {
                cout << " Welcome, " << g.name << "!\n";
                return;
            }
        }
        cout << " Login failed.\n";
    }

    void showRoom()
    {
        int r;
        cout << "\nEnter room number: ";
        cin >> r;
        if (!rooms.count(r))
        {
            cout << " Not booked.\n";
            return;
        }
        Guest g = rooms[r];
        cout << "\n📋 Guest Info\nName: " << g.name
             << "\nAddress: " << g.address
             << "\nPhone: " << g.phone;
        cout << "\nType: " << g.type << "\nDays: " << g.days
             << "\nFood Bill: ₹" << g.foodBill << "\n";
    }

    void listRooms()
    {
        cout << "\n🛏 Allotted Rooms:\n";
        for (auto &pair : rooms)
        {
            int r = pair.first;
            Guest &g = pair.second;
            cout << "Room " << r << ": " << g.name
                 << ", " << g.address << ", " << g.phone << "\n";
        }
    }

    void modifyRoom()
    {
        int r;
        cout << "\nEnter room number: ";
        cin >> r;
        if (!rooms.count(r))
        {
            cout << " Not booked.\n";
            return;
        }
        cout << "1.Name 2.Address 3.Phone 4.Days: ";
        int ch;
        cin >> ch;
        if (ch == 1)
            cin >> rooms[r].name;
        else if (ch == 2)
            cin >> rooms[r].address;
        else if (ch == 3)
            cin >> rooms[r].phone;
        else if (ch == 4)
            cin >> rooms[r].days;
        cout << " Updated.\n";
    }

    void restaurant()
    {
        int r, persons, total = 0;
        cout << "\nRoom number: ";
        cin >> r;
        if (!rooms.count(r))
        {
            cout << " Not booked.\n";
            return;
        }

        cout << "\n🍴 MENU OPTIONS:\n";
        cout << "1. Breakfast\n2. Lunch\n3. Dinner\nChoice: ";
        int mealChoice;
        cin >> mealChoice;

        if (mealChoice == 1 || mealChoice == 2)
        {
            string meal = (mealChoice == 1 ? "Breakfast" : "Lunch");
            cout << "\n"
                 << meal << " Options:\n";
            cout << "1. Normal\n2. Unlimited\nChoice: ";
            int typeChoice;
            cin >> typeChoice;

            cout << "1. Veg\n2. Non-Veg\nChoice: ";
            int foodType;
            cin >> foodType;

            cout << "Persons: ";
            cin >> persons;

            int cost = 0;

            // Breakfast
            if (mealChoice == 1)
            {
                if (typeChoice == 1 && foodType == 1)
                    cost = 150;
                else if (typeChoice == 1 && foodType == 2)
                    cost = 199;
                else if (typeChoice == 2 && foodType == 1)
                    cost = 259;
                else if (typeChoice == 2 && foodType == 2)
                    cost = 359;
            }
            // Lunch
            else if (mealChoice == 2)
            {
                if (typeChoice == 1 && foodType == 1)
                    cost = 250;
                else if (typeChoice == 1 && foodType == 2)
                    cost = 350;
                else if (typeChoice == 2 && foodType == 1)
                    cost = 400;
                else if (typeChoice == 2 && foodType == 2)
                    cost = 550;
            }

            total = cost * persons;
            rooms[r].foodBill += total;
            cout << " " << meal << " ("
                 << (typeChoice == 1 ? "Normal" : "Unlimited") << " - "
                 << (foodType == 1 ? "Veg" : "Non-Veg")
                 << ") ordered for " << persons << " person(s). ₹"
                 << total << " added.\n";
        }

        else if (mealChoice == 3)
        {
            cout << "\nDinner: ₹1200 per person\nPersons: ";
            cin >> persons;
            total = 1200 * persons;
            rooms[r].foodBill += total;
            cout << " ₹" << total << " added for Dinner.\n";
        }

        else
        {
            cout << " Invalid choice.\n";
        }
    }

    void checkout()
    {
        int r;
        cout << "\nEnter room number: ";
        cin >> r;
        if (!rooms.count(r))
        {
            cout << " Not booked.\n";
            return;
        }

        Guest g = rooms[r];
        int rb = roomCost(g.type) * g.days, total = rb + g.foodBill;

        cout << "\n Checkout Summary\nRoom ₹" << rb
             << " + Food ₹" << g.foodBill
             << " = ₹" << total << "\n";

        // Create unique bill file
        string filename = "bill_" + to_string(r) + ".txt";
        ofstream out(filename);

        out << "=============================================\n";
        out << "║              HOTEL BILL RECEIPT           ║\n";
        out << "=============================================\n";
        out << "Guest Name   : " << g.name << "\n";
        out << "Room Number  : " << r << "\n";
        out << "Room Type    : " << g.type
            << " (" << (g.type == 'A' ? "Deluxe" : g.type == 'B' ? "Standard"
                                                                 : "Economy")
            << ")\n";
        out << "Days Stayed  : " << g.days << "\n";
        out << "Phone        : " << g.phone << "\n";
        out << "--------------------------------------------\n";
        out << "Room Charges : ₹" << rb << "\n";
        out << "Food Charges : ₹" << g.foodBill << "\n";
        out << "Total Bill   : ₹" << total << "\n";
        out << "--------------------------------------------\n";
        out << "Thank you for staying with us!\n";
        out.close();

        cout << "🧾 Bill generated and saved as: " << filename << "\n";
        rooms.erase(r);
        cout << " Checked out successfully.\n";
    }
};

int main()
{
    Hotel h;
    int ch;
    do
    {
        cout << "\n MENU:\n 1.Book\n 2.Login to your room\n 3.Info\n 4.List\n 5.Modify\n 6.Order Food\n 7.Checkout\n 8.Exit\nChoice: ";
        cin >> ch;
        if (ch == 1)
            h.bookRoom();
        else if (ch == 2)
            h.loginPortal();
        else if (ch == 3)
            h.showRoom();
        else if (ch == 4)
            h.listRooms();
        else if (ch == 5)
            h.modifyRoom();
        else if (ch == 6)
            h.restaurant();
        else if (ch == 7)
            h.checkout();
    } while (ch != 8);
    return 0;
}
