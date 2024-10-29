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
            delete item;  // Ensure memory allocated for MenuItem is released
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
            total += item->getPrice();  // Accumulate the price of each item
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
// Base class: Restaurant
class Restaurant {
private:
    map<int, MenuItem*> menu;     // Map of menu items with ID as key
    map<int, Order*> orders;      // Map of orders with order ID as key
    int nextOrderId;              // ID for the next order

    static int totalOrders;       // Static variable to track total orders across all instances
protected:
    vector<MenuItem*> menu;  // Menu items
    vector<int> orders;      // List of ordered item indices

public:
    // Constructor to initialize Restaurant
    Restaurant() : nextOrderId(1) {}

    // Destructor to free dynamically allocated memory
    ~Restaurant() {
        for (auto& item : menu) {
            delete item.second;  // Clean up MenuItem pointers
        }

        for (auto& order : orders) {
            delete order.second;  // Clean up Order pointers
        }
    }

    // Add a menu item to the menu
    void addMenuItem(int id, MenuItem* item) {
        menu[id] = item;  // Store MenuItem in the menu map
    }

    // Static function to get the total number of orders placed across all restaurants
    static int getTotalOrders() {
        return totalOrders;  // Return the total orders counter
    }

    // Display the menu to the user
    void displayMenu() const {
        cout << "\n--- Restaurant Menu ---" << endl;
        for (const auto& item : menu) {
            cout << item.first << ". " << item.second->getName() << " - $" << item.second->getPrice() << endl;
        }
        cout << "------------------------\n" << endl;
    }

    // Take a new order from the user
    void takeOrder() {
        int orderId = nextOrderId++;  // Get a new order ID
        Order* order = new Order(orderId);  // Create a new Order object
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

            if (itemId == 0) break;  // Exit loop if user finishes

            if (menu.find(itemId) != menu.end()) {
                order->addItem(menu[itemId]);  // Add item to order if valid
                cout << menu[itemId]->getName() << " added to the order." << endl;
            } else {
                cout << "Invalid item ID! Please try again." << endl;
            }
        }

        if (order->getTotal() > 0) {
            orders[orderId] = order;  // Store the order in the orders map
            ++totalOrders;  // Increment the static order counter
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
            order.second->displayOrder();  // Display each order
            cout << "-----------------------" << endl;
        }
    }
};
//frfr

// Initialize the static member variable
int Restaurant::totalOrders = 0;

// Derived class: Steakhouse inherits from Restaurant
class Steakhouse : public Restaurant {
public:
    // Constructor for Steakhouse
    Steakhouse() {
        cout << "Welcome to the Steakhouse!" << endl;  // Welcome message
    }

    // Special function for steak of the day
    void steakOfTheDay() const {
        cout << "Today's special steak is the Wagyu Ribeye!" << endl;  // Daily special
    }
};

// Main function
int main() {
    Restaurant restaurant;
    Steakhouse steakhouse;

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
        cout << "4. Get Total Orders" << endl;  // New option to get total orders
        cout << "5. Steak of the Day" << endl;  // New feature for Steakhouse
        cout << "6. Exit" << endl;  // Corrected option number
        cout << "Enter your choice: ";
        cin >> choice;

        // Validate input
        while (cin.fail() || choice < 1 || choice > 6) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice! Please enter a number between 1 and 6: ";
            cin >> choice;
        }

        switch (choice) {
            case 1:
                restaurant.displayMenu();  // Display restaurant menu
                steakhouse.displayMenu();  // Display steakhouse menu
                break;
            case 2:
                restaurant.takeOrder();  // Take order at restaurant
                steakhouse.takeOrder();  // Take order at steakhouse
                break;
            case 3:
                restaurant.displayOrders();  // Display orders from restaurant
                steakhouse.displayOrders();  // Display orders from steakhouse
                break;
            case 4:
                cout << "Total orders placed: " << Restaurant::getTotalOrders() << endl;  // Show total orders
                break;
            case 5:
                steakhouse.steakOfTheDay();  // Show today's special from steakhouse
                break;
            case 6:
                cout << "Exiting the program. Goodbye!" << endl;  // Exit message
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;  // Handle invalid choices
        }
    }
}
