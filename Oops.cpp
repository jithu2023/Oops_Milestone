#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <limits>

using namespace std;

// Menu Item Class
class MenuItem {
private:
    string name;
    double price;
public:
    // Constructor
    MenuItem(string name, double price) : name(name), price(price) {}

    string getName() const {
        return name;
    }

    double getPrice() const {
        return price;
    }
};

// Order Class
class Order {
private:
    int orderId;
    vector<MenuItem*> items;
public:
    // Constructor
    Order(int orderId) : orderId(orderId) {}
    
    // Destructor to free dynamically allocated memory
    ~Order() {
        for (auto item : items) {
            delete item;
        }
    }

    void addItem(MenuItem* item) {
        items.push_back(item);
    }

    double getTotal() const {
        double total = 0.0;
        for (const auto& item : items) {
            total += item->getPrice();
        }
        return total;
    }

    void displayOrder() const {
        cout << "Order ID: " << orderId << endl;
        cout << "Items:" << endl;
        for (const auto& item : items) {
            cout << "- " << item->getName() << " ($" << item->getPrice() << ")" << endl;
        }
        cout << "Total: $" << getTotal() << endl;
    }
};

// Restaurant Class
class Restaurant {
private:
    map<int, MenuItem*> menu;
    map<int, Order*> orders;
    int nextOrderId;
public:
    // Constructor
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

    void addMenuItem(int id, MenuItem* item) {
        menu[id] = item;
    }

    void displayMenu() const {
        cout << "\n--- Steakhouse Menu ---" << endl;
        for (const auto& item : menu) {
            cout << item.first << ". " << item.second->getName() << " - $" << item.second->getPrice() << endl;
        }
        cout << "------------------------\n" << endl;
    }

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
