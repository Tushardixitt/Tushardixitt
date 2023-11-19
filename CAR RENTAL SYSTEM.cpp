#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <cstdlib>
#include <ctime>

using namespace std;

struct User {
    string username;
    string password;
};

struct Car {
    string carDetails;
    string carName;
    string model;
    string companyType;
    string transmission;
    int year;
    string fuelType;
    int rentFee;
};

map<string, User> users;
map<string, User> admins;
map<string, Car> cars;
map<string, Car> rentedCars;

// Function to display text centered on the console
void displayCenteredText(const string& text) {
    int width = 80;
    int textWidth = text.length();

    if (textWidth >= width) {
        cout << text << endl;
    } else {
        int padding = (width - textWidth) / 2;
        cout << setw(padding + textWidth) << text << endl;
    }
}

void adminSignUp() {
    string username, password;

    cout << "Enter admin username: ";
    cin >> username;
    cout << "Enter admin password: ";
    cin >> password;

    admins[username] = {username, password};
    cout << "Admin signed up successfully!" << endl;
}

bool adminLogin() {
    string username, password;

    cout << "Enter admin username: ";
    cin >> username;
    cout << "Enter admin password: ";
    cin >> password;

    if (admins.find(username) != admins.end() && admins[username].password == password) {
        cout << "Admin login successful!" << endl;
        return true;
    } else {
        cout << "Invalid admin credentials!" << endl;
        return false;
    }
}
void addCar() {
    string carName, model, companyType, transmission, fuelType;
    int year;

    cout << "Enter car name: ";
    cin.ignore();
    getline(cin, carName);
    cout << "Enter car model: ";
    getline(cin, model);
    cout << "Enter car company type: ";
    getline(cin, companyType);
    cout << "Enter car transmission: ";
    getline(cin, transmission);
    cout << "Enter car year: ";
    cin >> year;
    cout << "Enter car fuel type: ";
    cin.ignore();
    getline(cin, fuelType);

    cars[carName] = {carName, model, companyType, transmission};
    cout << "Car added successfully!" << endl;
}

void deleteCar() {
    if (cars.empty()) {
        cout << "No cars available for deletion!" << endl;
        return;
    }

    cout << "Cars available for deletion:" << endl;
    for (const auto& car : cars) {
        cout << "Car Name: " << car.second.carName << ", Details: " << car.second.carDetails << endl;
    }

    string carName;
    cout << "Enter car name to delete: ";
    cin.ignore();
    getline(cin, carName);

    auto it = cars.find(carName);
    if (it != cars.end()) {
        cars.erase(it);
        cout << "Car deleted successfully!" << endl;
    } else {
        cout << "Car not found!" << endl;
    }
}

void carDetails() {
    if (cars.empty()) {
        cout << "No cars available!" << endl;
        return;
    }

    cout << "Car Details:" << endl;
    for (const auto& car : cars) {
        cout << "Car Name: " << car.second.carName << ", Details: " << car.second.carDetails << endl;
    }
}
void rentCar(const string& username) {
    string carName;
    int rentDays; 

    cout << "Enter the name of the car you want to rent: ";
    cin.ignore();
    getline(cin, carName);

    if (cars.find(carName) != cars.end()) {
        cout << "Enter the number of days you want to rent the car: ";
        cin >> rentDays;

        Car rentedCar = cars[carName];
        srand(time(0)); 
        rentedCar.rentFee = (rand() % 100 + 50) * rentDays; // Rent fee is calculated for the total number of days

        rentedCars[carName] = rentedCar;
        cars.erase(carName);
        cout << "Car rented successfully for " << rentDays << " days! Total Rent fee: $" << rentedCar.rentFee << endl;
    } else {
        cout << "Car not available!" << endl;
    }
}

void viewAvailableCars() {
    if (cars.empty()) {
        cout << "No cars available!" << endl;
        return;
    }

    cout << "Available Cars:" << endl;
    for (const auto& car : cars) {
        cout << "Car Name: " << car.second.carName << ", Details: " << car.second.carDetails << endl;
    }
}

void viewCarDetails() {
    if (cars.empty()) {
        cout << "No cars available!" << endl;
        return;
    }

    string carName;
    cout << "Enter the name of the car to view details: ";
    cin.ignore();
    getline(cin, carName);

    if (cars.find(carName) != cars.end()) {
        cout << "Car Details:" << endl;
        cout << "Car Name: " << cars[carName].carName << ", Details: " << cars[carName].carDetails << endl;
    } else {
        cout << "Car not found!" << endl;
    }
}

void returnCar(const string& username) {
    string carName;
    cout << "Enter the name of the car you want to return: ";
    cin.ignore();
    getline(cin, carName);

    if (rentedCars.find(carName) != rentedCars.end()) {
        cars[carName] = rentedCars[carName];
        rentedCars.erase(carName);
        cout << "Car returned successfully!" << endl;
    } else {
        cout << "Car not rented by this user!" << endl;
    }
}
void adminFunctionalities() {
    while (true) {
        int adminChoice;
        cout << "Admin Functionalities:" << endl;
        cout << "1. Add a Car" << endl;
        cout << "2. Delete a Car" << endl;
        cout << "3. Car Details" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> adminChoice;

        switch (adminChoice) {
            case 1:
                addCar();
                break;
            case 2:
                deleteCar();
                break;
            case 3:
                carDetails();
                break;
            case 4:
                return;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
        }
    }
}

void userFunctionalities(const string& username) {
    while (true) {
        int userChoice;
        cout << "User Functionalities:" << endl;
        cout << "1. Rent a Car" << endl;
        cout << "2. View Available Cars" << endl;
        cout << "3. View Car Details" << endl;
        cout << "4. Return a Rented Car" << endl;
        cout << "5. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> userChoice;

        switch (userChoice) {
            case 1:
                rentCar(username);
                break;
            case 2:
                viewAvailableCars();
                break;
            case 3:
                viewCarDetails();
                break;
            case 4:
                returnCar(username);
                break;
            case 5:
                return;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
        }
    }
}

void userSignUp() {
    string username, password;
    cin.ignore();

    cout << "Enter user username: ";
    getline(cin, username);
    cout << "Enter user password: ";
    getline(cin, password);

    users[username] = {username, password};
    cout << "User signed up successfully!" << endl;
}

bool userLogin(string& username) {
    string user, pass;
    cin.ignore();

    cout << "Enter user username: ";
    getline(cin, user);
    cout << "Enter user password: ";
    getline(cin, pass);

    for (auto& u : users) {
        if (u.second.username == user && u.second.password == pass) {
            cout << "User login successful!" << endl;
            username = user;
            return true;
        }
    }
    cout << "Invalid user credentials!" << endl;
    return false;
}

int main() {
    while (true) {
        system("clear");

        displayCenteredText("Car Rental System");
        cout << endl;

        cout << "Choose an option:" << endl;
        cout << "1. Admin" << endl;
        cout << "2. User" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                int adminChoice;
                cout << "Admin Menu:" << endl;
                cout << "1. Admin Login" << endl;
                cout << "2. Admin Sign Up" << endl;
                cout << "3. Exit" << endl;
                cout << "Enter your choice: ";
                cin >> adminChoice;

                switch (adminChoice) {
                    case 1:
                        if (adminLogin()) {
                            adminFunctionalities();
                        }
                        break;
                    case 2:
                        adminSignUp();
                        break;
                    case 3:
                        return 0;
                    default:
                        cout << "Invalid admin choice. Please enter a valid option." << endl;
                }
                break;
            }
            case 2: {
                string currentUser;
                int userChoice;
                cout << "User Menu:" << endl;
                cout << "1. User Login" << endl;
                cout << "2. User Sign Up" << endl;
                cout << "3. Exit" << endl;
                cout << "Enter your choice: ";
                cin >> userChoice;

                switch (userChoice) {
                    case 1:
                        if (userLogin(currentUser)) {
                            userFunctionalities(currentUser);
                        }
                        break;
                    case 2:
                        userSignUp();
                        break;
                    case 3:
                        return 0;
                    default:
                        cout << "Invalid user choice. Please enter a valid option." << endl;
                }
                break;
            }
            case 3:
                cout << "Exiting the program. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
        }

        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }

    return 0;
}
