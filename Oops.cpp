#include <iostream>
#include <vector>
#include <string>
using namespace std;

// MenuItem class to represent a menu item
class MenuItem {
public:
    string name;
    double price;

    MenuItem(string n, double p) : name(n), price(p) {}
};

// Base class: Restaurant
class Restaurant {
protected:
    vector<MenuItem*> menu;  // Menu items
    vector<int> orders;      // List of ordered item indices

public:
    // Add a menu item
    void addMenuItem(int index, MenuItem* item) {
        if (index < menu.size()) {
            menu[index] = item;
        } else {
            menu.push_back(item);
        }
    }

    // Display the menu
    void displayMenu() const {
        cout << "Menu:" << endl;
        for (int i = 0; i < menu.size(); i++) {
            cout << i + 1 << ". " << menu[i]->name << " - $" << menu[i]->price << endl;
        }
    }

    // Take an order from the customer
    void takeOrder() {
        int choice;
        displayMenu();
        cout << "Enter the item number to order: ";
        cin >> choice;
        if (choice > 0 && choice <= menu.size()) {
            orders.push_back(choice - 1);
            cout << "Order placed for: " << menu[choice - 1]->name << endl;
        } else {
            cout << "Invalid choice. Try again." << endl;
        }
    }

    // Display all the orders
    void displayOrders() const {
        cout << "Orders:" << endl;
        for (int order : orders) {
            cout << menu[order]->name << endl;
        }
    }
};

// Derived class: Steakhouse inherits from Restaurant
class Steakhouse : public Restaurant {
public:
    // Constructor for Steakhouse
    Steakhouse() {
        cout << "Welcome to the Steakhouse!" << endl;
    }

    // Special function for steak of the day
    void steakOfTheDay() const {
        cout << "Today's special steak is the Wagyu Ribeye!" << endl;
    }
};

// Main function
int main() {
    Steakhouse steakhouse;

    // Adding menu items
    steakhouse.addMenuItem(1, new MenuItem("Ribeye Steak", 25.99));
    steakhouse.addMenuItem(2, new MenuItem("Filet Mignon", 29.99));
    steakhouse.addMenuItem(3, new MenuItem("T-Bone Steak", 22.99));
    steakhouse.addMenuItem(4, new MenuItem("Grilled Chicken", 18.99));

    int choice;

    while (true) {
        cout << "\n1. Display Menu" << endl;
        cout << "2. Take Order" << endl;
        cout << "3. Display Orders" << endl;
        cout << "4. Steak of the Day" << endl;  // New feature for Steakhouse
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                steakhouse.displayMenu();
                break;
            case 2:
                steakhouse.takeOrder();
                break;
            case 3:
                steakhouse.displayOrders();
                break;
            case 4:
                steakhouse.steakOfTheDay();  // Unique function for Steakhouse
                break;
            case 5:
                cout << "Exiting the program. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
