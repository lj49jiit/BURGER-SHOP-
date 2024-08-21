#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <climits>
#include <unordered_set> // Include unordered_set for storing phone numbers

using namespace std;

const int infinity = INT_MAX;

class BurgerShop {
private:
    unordered_set<string> registeredNumbers; // Store registered phone numbers

public:
    string burgerName[4] = {"Cheese Burger", "Chicken Burger", "Veggie Burger", "Fish Burger"};
    int price[4] = {150, 200, 180, 250};

    // Function to register phone numbers
    void registerPhoneNumber(const string& phoneNumber) {
        registeredNumbers.insert(phoneNumber);
    }

    // Function to check if a phone number is registered and provide a discount
    double calculateDiscount(const string& phoneNumber, double bill) {
        const double discountPercentage = 0.1; // 10% discount for registered customers
        if (registeredNumbers.find(phoneNumber) != registeredNumbers.end()) {
            double discount = bill * discountPercentage;
            cout << "Congratulations! You have a 10% discount applied to your bill." << endl;
            return bill - discount;
        }
        return bill;
    }
};

string deliveryPoints[6] = {"My Burger Shop", "Noida", "Ghaziabad", "Mohan Nagar", "Location 4", "Location 5"};

vector<vector<int>> distanceMatrix = {
    {0, 4, 3, 2, 5, 7},
    {4, 0, 6, 2, 7, 3},
    {3, 6, 0, 6, 3, 2},
    {2, 2, 6, 0, 5, 8},
    {5, 7, 3, 5, 0, 4},
    {7, 3, 2, 8, 4, 0}
};

// Function to calculate shortest path using Dijkstra's algorithm
vector<int> dijkstra(int sourceNode) {
    int n = distanceMatrix.size();
    vector<int> distance(n, infinity);
    set<pair<int, int>> nodes;

    distance[sourceNode] = 0;
    nodes.insert({0, sourceNode});

    while (!nodes.empty()) {
        int u = nodes.begin()->second;
        nodes.erase(nodes.begin());

        for (int v = 0; v < n; ++v) {
            if (distance[u] + distanceMatrix[u][v] < distance[v]) {
                nodes.erase({distance[v], v});
                distance[v] = distance[u] + distanceMatrix[u][v];
                nodes.insert({distance[v], v});
            }
        }
    }

    return distance;
}

int main() {
    BurgerShop* myburgerShop = new BurgerShop();

    int option = -99;

    do {
        cout << "==============================" << endl;
        cout << "Welcome to My Burger Shop" << endl;
        cout << "1. Show Menu" << endl;
        cout << "2. Place order for Home Delivery Customer" << endl;
        cout << "3. Place order for Dine-in Customer" << endl;
        cout << "0. Exit" << endl;
        cout << "==============================" << endl;
        cout << "Enter your choice: ";
        cin >> option;

        switch (option) {
            case 1: { // Show Menu
                cout << "==============================" << endl;
                cout << "Menu" << endl;
                for (int i = 0; i < 4; ++i) {
                    cout << i + 1 << ". " << myburgerShop->burgerName[i] << " - " << myburgerShop->price[i] << " RS/_" << endl;
                }
                cout << "==============================" << endl;
                break;
            }

            case 2: { // Place order for Home Delivery Customer
                cout << "Available delivery locations: " << endl;
                for (int i = 1; i <= 5; i++) {
                    cout << i << ". " << deliveryPoints[i] << endl;
                }

                int deliveryLocation;
                cout << "Enter your delivery location (1-5): ";
                cin >> deliveryLocation;

                vector<int> distanceFromShop = dijkstra(0); // As Zero is our Source Node
                int distanceToDeliveryLocation = distanceFromShop[deliveryLocation];

                string name, phoneNumber;
                int age, quantity;
                vector<int> burgerIndices; // Store selected burger indices
                double bill = 0.0;

                cout << "Enter the name of the customer: ";
                cin >> name;
                cout << "Enter the age of the customer: ";
                cin >> age;
                cout << "Enter your phone number for registration: ";
                cin >> phoneNumber;
                myburgerShop->registerPhoneNumber(phoneNumber);

                int burgerIndex;
                char addMoreBurgers;
                do {
                    cout << "Enter the option for the burger: ";
                    cin >> burgerIndex;
                    burgerIndices.push_back(burgerIndex);
                    cout << "Add more burgers? (y/n): ";
                    cin >> addMoreBurgers;
                } while (addMoreBurgers == 'y' || addMoreBurgers == 'Y');

                int deliveryChargesPerKM = 50;
                int totalDistance = distanceToDeliveryLocation;
                int deliveryCharges = deliveryChargesPerKM * totalDistance;

                // Calculate total bill for selected burgers
                for (int index : burgerIndices) {
                    bill += myburgerShop->price[index - 1];
                }

                bill += deliveryCharges;

                cout << "Your order has been placed, " << name << ". ";
                cout << "Your total bill (including delivery charges) is: " << bill << " RS/_" << endl;
                cout << "Estimated delivery distance: " << totalDistance << " KM" << endl;
                cout << "Delivery charges: " << deliveryCharges << " RS/_" << endl;

                // Calculate discounted bill for registered customers
                double discountedBill = myburgerShop->calculateDiscount(phoneNumber, bill);
                cout << "Your discounted bill (if registered) is: " << discountedBill << " RS/_" << endl;
                break;
            }

            case 3: { // Place order for Dine-in Customer
                // Remaining code for dine-in order placement (similar to above)
                int dineInLocation;
                cout << "Available dine-in locations: " << endl;
                for (int i = 1; i <= 3; i++) {
                    cout << i << ". " << deliveryPoints[i] << endl;
                }

                cout << "Enter your dine-in location (1-3): ";
                cin >> dineInLocation;

                string name;
                int age, quantity, burgerIndex;
                double bill;

                cout << "Enter the name of the customer: ";
                cin >> name;
                cout << "Enter the age of the customer: ";
                cin >> age;
                cout << "Enter the quantity of the burger: ";
                cin >> quantity;
                cout << "Enter the option for the burger: ";
                cin >> burgerIndex;

                bill = quantity * myburgerShop->price[burgerIndex - 1];

                cout << "Your dine-in order has been placed, " << name << ". ";
                cout << "Your total bill is: " << bill << " RS/_" << endl;
                cout << "Please enjoy your meal at " << deliveryPoints[dineInLocation] << "." << endl;
                break;
            }

            case 0: // Exit
                cout << "Exiting the program. Thank you!" << endl;
                break;

            default:
                cout << "Invalid option. Please try again." << endl;
                break;
        }
    } while (option != 0);

    delete myburgerShop;

    return 0;
}
