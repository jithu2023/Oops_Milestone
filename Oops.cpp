#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <limits>

using namespace std;

// Abstract base class defining the interface for Restaurants
class RestaurantInterface {
public:
    virtual void displaySpecial() const = 0; // Pure virtual function
    virtual ~RestaurantInterface() = default;
};

// MenuItem Class to represent an item on the menu
class MenuItem {
private:
    string name;
    double price;

public:
    MenuItem(string name, double price) : name(name), price(price) {}

    string getName() const {
        return this->name;
    }

    double getPrice() const {
        return this->price;
    }
};

// Order Class to represent a customer order
class Order {
private:
    int orderId;
    vector<MenuItem*> items;

public:
    Order(int orderId) : orderId(orderId) {}

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
        cout << "Order ID: " << this->orderId << endl;
        cout << "Items:" << endl;
        for (const auto& item : items) {
            cout << "- " << item->getName() << " ($" << item->getPrice() << ")" << endl;
        }
        cout << "Total: $" << this->getTotal() << endl;
    }
};

// Restaurant Class inheriting from RestaurantInterface
class Restaurant : public RestaurantInterface {
private:
    map<int, MenuItem*> menuById;
    map<string, MenuItem*> menuByName;
    map<int, Order*> orders;
    int nextOrderId;
    static int totalOrders;

public:
    Restaurant() : nextOrderId(1) {}

    ~Restaurant() {
        for (auto& item : menuById) {
            delete item.second;
        }
        for (auto& order : orders) {
            delete order.second;
        }
    }

    void addMenuItem(int id, MenuItem* item) {
        menuById[id] = item;
    }

    void addMenuItem(string name, MenuItem* item) {
        menuByName[name] = item;
    }

    static int getTotalOrders() {
        return totalOrders;
    }

    void displayMenu() const {
        cout << "\n--- Restaurant Menu by ID ---" << endl;
        for (const auto& item : menuById) {
            cout << item.first << ". " << item.second->getName() << " - $" << item.second->getPrice() << endl;
        }

        cout << "\n--- Restaurant Menu by Name ---" << endl;
        for (const auto& item : menuByName) {
            cout << item.first << ": " << item.second->getName() << " - $" << item.second->getPrice() << endl;
        }
    }

    void takeOrder() {
        int orderId = nextOrderId++;
        Order* order = new Order(orderId);
        int itemId;
        cout << "\nEnter item IDs to add to order (0 to finish):" << endl;

        while (true) {
            cout << "Item ID: ";
            cin >> itemId;
            if (itemId == 0) break;
            if (menuById.find(itemId) != menuById.end()) {
                order->addItem(menuById[itemId]);
                cout << menuById[itemId]->getName() << " added to the order." << endl;
            } else {
                cout << "Invalid item ID! Please try again." << endl;
            }
        }

        if (order->getTotal() > 0) {
            orders[orderId] = order;
            ++totalOrders;
            cout << "\nOrder placed successfully!\n" << endl;
        } else {
            delete order;
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

    // Implementation of the pure virtual function
    void displaySpecial() const override {
        cout << "Today's special is Chef's Surprise!" << endl;
    }
};

int Restaurant::totalOrders = 0;

// Steakhouse Class inheriting from Restaurant and implementing displaySpecial
class Steakhouse : public Restaurant {
public:
    Steakhouse() {
        cout << "Welcome to the Steakhouse!" << endl;
    }

    void steakOfTheDay() const {
        cout << "Today's special steak is the Wagyu Ribeye!" << endl;
    }

    void displaySpecial() const override {
        cout << "Today's special at Steakhouse is Wagyu Ribeye!" << endl;
    }
};

int main() {
    Restaurant restaurant;
    Steakhouse steakhouse;

    // Adding menu items
    restaurant.addMenuItem(1, new MenuItem("Ribeye Steak", 25.99));
    restaurant.addMenuItem(2, new MenuItem("Filet Mignon", 29.99));
    restaurant.addMenuItem("Special Sirloin", new MenuItem("Sirloin Steak", 19.99));

    int choice;

    while (true) {
        cout << "1. Display Menu" << endl;
        cout << "2. Take Order" << endl;
        cout << "3. Display Orders" << endl;
        cout << "4. Get Total Orders" << endl;
        cout << "5. Steak of the Day" << endl;
        cout << "6. Display Special" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                restaurant.displayMenu();
                steakhouse.displayMenu();
                break;
            case 2:
                restaurant.takeOrder();
                steakhouse.takeOrder();
                break;
            case 3:
                restaurant.displayOrders();
                steakhouse.displayOrders();
                break;
            case 4:
                cout << "Total orders placed: " << Restaurant::getTotalOrders() << endl;
                break;
            case 5:
                steakhouse.steakOfTheDay();
                break;
            case 6:
                steakhouse.displaySpecial();
                break;
            case 7:
                cout << "Exiting the program. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}
