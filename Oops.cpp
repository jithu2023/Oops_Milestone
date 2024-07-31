#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <limits>
#include <array>

using namespace std;

// Menu Item Class
class MenuItem {
private:
    string name;
    double price;
public:
    // Default constructor
    MenuItem() : name(""), price(0.0) {}

    MenuItem(string name, double price) : name(name), price(price) {}

    string getName() const {
        return this->name;
    }

    double getPrice() const {
        return this->price;
    }
};

// Order Class
class Order {
private:
    int orderId;
    vector<MenuItem> items;
public:
    // Default constructor
    Order() : orderId(0) {}

    Order(int orderId) : orderId(orderId) {}

    void addItem(MenuItem item) {
        this->items.push_back(item);
    }

    double getTotal() const {
        double total = 0.0;
        for (const auto& item : this->items) {
            total += item.getPrice();
        }
        return total;
    }

    void displayOrder() const {
        cout << "Order ID: " << this->orderId << endl;
        cout << "Items:" << endl;
        for (const auto& item : this->items) {
            cout << "- " << item.getName() << " ($" << item.getPrice() << ")" << endl;
        }
        cout << "Total: $" << this->getTotal() << endl;
    }
};

// Restaurant Class
class Restaurant {
private:
    map<int, MenuItem> menu;
    map<int, Order> orders;
    int nextOrderId;
public:
    Restaurant() : nextOrderId(1) {}

    void addMenuItem(int id, MenuItem item) {
        this->menu[id] = item;
    }

    void displayMenu() const {
        cout << "\n--- Steakhouse Menu ---" << endl;
        for (const auto& item : this->menu) {
            cout << item.first << ". " << item.second.getName() << " - $" << item.second.getPrice() << endl;
        }
        cout << "------------------------\n" << endl;
    }

    void takeOrder() {
        int orderId = this->nextOrderId++;
        Order order(orderId);
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

            if (this->menu.find(itemId) != this->menu.end()) {
                order.addItem(this->menu[itemId]);
                cout << this->menu[itemId].getName() << " added to the order." << endl;
            } else {
                cout << "Invalid item ID! Please try again." << endl;
            }
        }

        if (order.getTotal() > 0) {
            this->orders[orderId] = order;
            cout << "\nOrder placed successfully!\n" << endl;
        } else {
            cout << "\nNo items were added to the order.\n" << endl;
        }
    }

    void displayOrders() const {
        if (this->orders.empty()) {
            cout << "\nNo orders have been placed yet.\n" << endl;
            return;
        }

        cout << "\n--- All Orders ---" << endl;
        for (const auto& order : this->orders) {
            order.second.displayOrder();
            cout << "-----------------------" << endl;
        }
        cout << "------------------------\n" << endl;
    }
};

int main() {
    Restaurant restaurant;

    // Add menu items (steak varieties)
    array<MenuItem, 5> menuItems = {
        MenuItem("Ribeye Steak", 25.99),
        MenuItem("Filet Mignon", 29.99),
        MenuItem("New York Strip", 22.99),
        MenuItem("T-Bone Steak", 27.99),
        MenuItem("Sirloin Steak", 19.99)
    };

    for (size_t i = 0; i < menuItems.size(); ++i) {
        restaurant.addMenuItem(i + 1, menuItems[i]);
    }

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
                cout << "Exiting program. Thank you!" << endl;
                exit(0);
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
