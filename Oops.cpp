#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <limits>

using namespace std;

// MenuItem Class to represent an item on the menu
class MenuItem {
private:
    string name;   // Name of the menu item
    double price;  // Price of the menu item

public:
    // Constructor to initialize MenuItem with name and price
    MenuItem(string name, double price) : name(name), price(price) {}

    // Getter for item name
    string getName() const {
        return this->name;
    }

    // Getter for item price
    double getPrice() const {
        return this->price;
    }
};

// Order Class to represent a customer order
class Order {
private:
    int orderId;                  // Unique identifier for the order
    vector<MenuItem*> items;      // List of items in the order

public:
    // Constructor to initialize Order with an ID
    Order(int orderId) : orderId(orderId) {}

    // Destructor to free dynamically allocated memory
    ~Order() {
        for (auto item : items) {
            delete item;
        }
    }

    // Add a MenuItem to the order
    void addItem(MenuItem* item) {
        items.push_back(item);
    }

    // Calculate the total price of the order
    double getTotal() const {
        double total = 0.0;
        for (const auto& item : items) {
            total += item->getPrice();
        }
        return total;
    }

    // Display the order details
    void displayOrder() const {
        cout << "Order ID: " << this->orderId << endl;
        cout << "Items:" << endl;
        for (const auto& item : items) {
            cout << "- " << item->getName() << " ($" << item->getPrice() << ")" << endl;
        }
        cout << "Total: $" << this->getTotal() << endl;
    }
};

// Restaurant Class to manage menu items and orders
class Restaurant {
private:
    map<int, MenuItem*> menu;     // Map of menu items with ID as key
    map<int, Order*> orders;      // Map of orders with order ID as key
    int nextOrderId;              // ID for the next order

public:
    // Constructor to initialize Restaurant
    Restaurant() : nextOrderId(1) {}

    // Destructor to free dynamically allocated memory
    ~Restaurant() {
        for (auto& item : menu) {
            delete item.second;
        }

        for (auto& order : orders) {
            delete order.second;
        }
    }

    // Add a MenuItem to the menu
    void addMenuItem(int id, MenuItem* item) {
        menu[id] = item;
    }

    // Display the menu to the user
    void displayMenu() const {
        cout << "\n--- Steakhouse Menu ---" << endl;
        for (const auto& item : menu) {
            cout << item.first << ". " << item.second->getName() << " - $" << item.second->getPrice() << endl;
        }
        cout << "------------------------\n" << endl;
    }

    // Take a new order from the user
    void takeOrder() {
        int orderId = nextOrderId++;
        Order* order = new Order(orderId);
        int itemId;
        cout << "\nEnter item IDs to add to order (0 to finish):" << endl;

        while (true) {
            cout << "Item ID: ";
            cin >> itemId;

            // Validate input
            while (cin.fail() || itemId < 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a valid item ID (0 to finish): ";
                cin >> itemId;
            }

            if (itemId == 0) break;

            if (menu.find(itemId) != menu.end()) {
                order->addItem(menu[itemId]);
                cout << menu[itemId]->getName() << " added to the order." << endl;
            } else {
                cout << "Invalid item ID! Please try again." << endl;
            }
        }

        if (order->getTotal() > 0) {
            orders[orderId] = order;
            cout << "\nOrder placed successfully!\n" << endl;
        } else {
            delete order; // Avoid memory leak by deleting the order if it's empty
            cout << "\nNo items were added to the order.\n" << endl;
        }
    }

    // Display all orders
    void displayOrders() const {
        if (orders.empty()) {
            cout << "\nNo orders have been placed yet.\n" << endl;
            return;
        }

        cout << "\n--- All Orders ---" << endl;
        for (const auto& order : orders) {
            order.second->displayOrder();
            cout << "-----------------------" << endl;
        }
    }
};

int main() {
    Restaurant restaurant;

    // Add menu items (steak varieties)
    restaurant.addMenuItem(1, new MenuItem("Ribeye Steak", 25.99));
    restaurant.addMenuItem(2, new MenuItem("Filet Mignon", 29.99));
    restaurant.addMenuItem(3, new MenuItem("New York Strip", 22.99));
    restaurant.addMenuItem(4, new MenuItem("T-Bone Steak", 27.99));
    restaurant.addMenuItem(5, new MenuItem("Sirloin Steak", 19.99));

    int choice;

    while (true) {
        cout << "1. Display Menu" << endl;
        cout << "2. Take Order" << endl;
        cout << "3. Display Orders" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        // Validate input
        while (cin.fail() || choice < 1 || choice > 4) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice! Please enter a number between 1 and 4: ";
            cin >> choice;
        }

        switch (choice) {
            case 1:
                restaurant.displayMenu();
                break;
            case 2:
                restaurant.takeOrder();
                break;
            case 3:
                restaurant.displayOrders();
                break;
            case 4:
                cout << "Exiting the program. Goodbye!" << endl;
                return 0;
        }
    }

    return 0;
}
