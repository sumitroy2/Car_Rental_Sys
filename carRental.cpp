/*You are required to implement a car rental system in C++ language using Object-Oriented
Programming concepts. Implement the system on command line interface.
List of basic functionalities:
1. Keep records of cars rented per customer/employee.
2. A customer is given a car if his/her customer_record is good enough. A customer_record
is updated based on several factors:
a. Car returned later than return_date.
b. Damage caused to the car. The condition in which the car has been returned.
c. The same will be for employees i.e. employee_record.
3. Maintain different databases for customers, employees, and cars.
4. Maintain three different classes for customers, employees, and manager.
a. A customer can see all the available cars. Can browse all the cars he is currently
renting. Can rent a limited number of cars as per his/her customer_record.
(Optional: If a customer is new, register him with an average customer_record
value). A fine will be imposed per day from the day of return.
b. An employee can see all the available cars. Can browse all the cars he/she is
currently renting. Can rent a limited number of cars as per his/her
employee_record. They are given a 15% discount on all cars. A fine will be
imposed per day from the day of return.
c. A manager can add/update/delete any customer or employee. Can also
update/delete/add cars in the store. Can see all the cars and who they are rented to.
5. Every method must be present in its appropriate class. Try to make use of both the private
and public functionalities for attributes. Prudently use inheritance, polymorphism, data
abstraction, and other concepts of OOPs. Start with atleast 5 cars, 5 customers, 5
employees and 1 manager. Feel free to choose default value(s) for other parameters.
6. For reference, you can check out the block diagram given on the next page.
7. The databases should be in csv format and you should have add, read, insert and delete functionalities.*/

#include <bits/stdc++.h>
using namespace std;

void read(string filename, vector<vector<string>> &data)
{
    ifstream file(filename);
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string word;
        vector<string> row;
        while (getline(ss, word, ','))
        {
            row.push_back(word);
        }
        data.push_back(row);
    }
}

void update(string filename, vector<vector<string>> &data)
{
    ofstream file(filename);
    for (int i = 0; i < data.size(); i++)
    {
        for (int j = 0; j < data[i].size(); j++)
        {
            file << data[i][j];
            if (j != data[i].size() - 1)
            {
                file << ",";
            }
        }
        file << endl;
    }
}

void insert(string filename, vector<vector<string>> &data, vector<string> row)
{
    ofstream file(filename, ios::app);
    for (int i = 0; i < row.size(); i++)
    {
        file << row[i];
        if (i != row.size() - 1)
        {
            file << ",";
        }
    }
    file << endl;
}

void deleteRow(string filename, vector<vector<string>> &data, int row)
{
    data.erase(data.begin() + row);
    update(filename, data);
}

class User
{
private:
    string password;

public:
    string username;
    string id;
    string userType;
    int record;
    int fine;
    int amount;
    int total;
    vector<string> rentedCars;
    void menu();
    void signup();
    void login();
    void logout();
    void displayAvailableCars();
    void rentCar(string id, string carModel);
    void returnCar(string id, string carModel);
    void getFine(string id);
    void clearFine(string id);
};

class Customer : public User
{
public:
    Customer()
    {
        userType = "3";
    }
    Customer(string username, string id, int customer_record, int fine, int amount, int total, vector<string> rentedCars)
    {
        this->username = username;
        this->id = id;
        this->userType = "3";
        this->record = customer_record;
        this->fine = fine;
        this->amount = amount;
        this->total = total;
        this->rentedCars = rentedCars;
    }
    void customerMenu();
};

class Employee : public User
{
public:
    Employee()
    {
        userType = "2";
    }
    Employee(string username, string id, int employee_record, int fine, int amount, int total, vector<string> rentedCars)
    {
        this->username = username;
        this->id = id;
        this->userType = "2";
        this->record = employee_record;
        this->fine = fine;
        this->amount = amount;
        this->total = total;
        this->rentedCars = rentedCars;
    }
    void employeeMenu();
};

class Manager : public User
{
public:
    Manager()
    {
        userType = "1";
    }
    void addCar();
    void updateCar();
    void deleteCar();
    void addCE();
    void updateCE();
    void deleteCE();
    void managerMenu();
    void displayRentedCars();
    void displayAllCars();
};

class Car
{
public:
    string carModel;
    string carNumber;
    string carColor;
    int carPrice;
    int carFine;
    int carCondition;
    int carAvailability;
    void addCar();
    void updateCar();
    void deleteCar();
    void displayRentedCars();
    void displayAllCars();
};

void User::menu()
{
    cout << "1. Signup\n2. Login\n3. Exit\n";
    string choice;
    cin >> choice;
    if (choice == "1")
    {
        signup();
    }
    else if (choice == "2")
    {
        login();
    }
    else if (choice == "3")
    {
        cout << "Thanks for using our automated Car Rental system.\n";
        exit(0);
    }
    else
    {
        cout << "Invalid choice\n";
        menu();
    }
}

void User::signup()
{
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    cout << "Enter id: ";
    cin >> id;
    cout << "Enter user type: 1 for manager, 2 for employee and 3 for customer\n";
    cin >> userType;
    while (userType != "1" && userType != "2" && userType != "3")
    {
        cout << "Invalid user type\n";
        cout << "Enter again: 1 for manager, 2 for employee and 3 for customer\n";
        cin >> userType;
    }
    cout << "Signup successful\n";
    if (userType == "1")
    {
        vector<vector<string>> data;
        read("managers.csv", data);
        vector<string> row;
        row.push_back(username);
        row.push_back(password);
        row.push_back(id);
        insert("managers.csv", data, row);
    }
    else if (userType == "2")
    {
        vector<vector<string>> data;
        read("employees.csv", data);
        vector<string> row;
        row.push_back(username);
        row.push_back(password);
        row.push_back(id);
        row.push_back("500"); // employee record
        row.push_back("0");   // fine
        row.push_back("0");   // amount
        row.push_back("0");   // total
        row.push_back(" ");   // rented cars
        insert("employees.csv", data, row);
    }
    else if (userType == "3")
    {
        vector<vector<string>> data;
        read("customers.csv", data);
        vector<string> row;
        row.push_back(username);
        row.push_back(password);
        row.push_back(id);
        row.push_back("500"); // customer record
        row.push_back("0");   // fine
        row.push_back("0");   // amount
        row.push_back("0");   // total
        row.push_back(" ");   // rented cars
        insert("customers.csv", data, row);
    }
    menu();
}

void User::login()
{
    cout << "Enter username: ";
    string u;
    cin >> u;
    cout << "Enter password: ";
    string p;
    cin >> p;
    cout << "Enter user type: 1 for manager, 2 for employee and 3 for customer\n";
    string t;
    cin >> t;
    vector<vector<string>> data;
    if (t == "1")
    {
        read("managers.csv", data);
    }
    else if (t == "2")
    {
        read("employees.csv", data);
    }
    else if (t == "3")
    {
        read("customers.csv", data);
    }
    else
    {
        cout << "Invalid user type\n";
        menu();
    }
    int flag = 0;
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i][0] == u && data[i][1] == p)
        {
            flag = 1;
            cout << "Login successful\n";
            if (t == "1")
            {
                Manager m;
                m.managerMenu();
            }
            else if (t == "2")
            {
                vector<string> rentedCars;
                for (int j = 7; j < data[i].size(); j++)
                    rentedCars.push_back(data[i][j]);
                // cout << "Username: " << data[i][0] << "\tID: " << data[i][2] << "\tRecord: " << data[i][3] << endl;
                Employee e(data[i][0], data[i][2], stoi(data[i][3]), stoi(data[i][4]), stoi(data[i][5]), stoi(data[i][6]), rentedCars);
                e.employeeMenu();
            }
            else if (t == "3")
            {
                vector<string> rentedCars;
                for (int j = 7; j < data[i].size(); j++)
                    rentedCars.push_back(data[i][j]);
                Customer c(data[i][0], data[i][2], stoi(data[i][3]), stoi(data[i][4]), stoi(data[i][5]), stoi(data[i][6]), rentedCars);
                c.customerMenu();
            }
        }
    }
    if (flag == 0)
    {
        cout << "Invalid username or password\n";
        menu();
    }
}

void User::logout()
{
    cout << "Logout successful\n";
    menu();
}

void User::displayAvailableCars()
{
    vector<vector<string>> data;
    read("cars.csv", data);
    cout << "Car Model\tCar Number\tCar Color\tCar Price\tCar Fine\tCar Condition\n";
    // cout << data.size() << " " << data[0].size() << endl;
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i][6] == "1")
        {
            for (int j = 0; j < 6; j++)
            {
                cout << data[i][j] << "\t        ";
            }
            cout << endl;
        }
    }
    // cout << "Username: " << username << " User Type: " << userType << endl;
    if (userType == "3")
    {
        Customer c(this->username, this->id, this->record, this->fine, this->amount, this->total, this->rentedCars);
        c.customerMenu();
    }
    else if (userType == "2")
    {
        Employee c(this->username, this->id, this->record, this->fine, this->amount, this->total, this->rentedCars);
        c.employeeMenu();
    }
    else if (userType == "1")
    {
        Manager m;
        m.managerMenu();
    }
}

void User::rentCar(string id, string carModel)
{
    vector<vector<string>> data;
    int flag = 0;
    read("cars.csv", data);
    if (((rentedCars.size() + 1) * 100 > record) || record < 0)
    {
        flag = 2;
        cout << "You have reached the limit of cars you can rent\n";
    }
    else
    {
        for (int i = 0; i < data.size(); i++)
        {
            if (data[i][0] == carModel)
            {
                if (data[i][6] == "1")
                {
                    flag = 1;
                    data[i].push_back(username);
                    data[i][6] = "0";
                    update("cars.csv", data);
                    rentedCars.push_back(carModel);
                    cout << "Car rented successfully\n";
                    cout << "Due Date: ";
                    time_t t = std::time(0);
                    tm *now = std::localtime(&t);
                    if (now->tm_mday > 24)
                        cout << (now->tm_year + 1900) << '-' << (now->tm_mon + 2) << '-' << now->tm_mday - 24 << "\n";
                    else
                        cout << (now->tm_year + 1900) << '-' << (now->tm_mon + 1) << '-' << now->tm_mday + 7 << "\n";
                    if (userType == "3")
                        cout << "Price: " << data[i][3] << "\tFine per day: " << data[i][4] << endl;
                    else
                        cout << "Price: " << data[i][3] << "\tFine per day: " << data[i][4] << "\tDiscount: " << (stoi(data[i][3]) * 0.15) << endl;
                    vector<vector<string>> data;
                    read(userType == "3" ? "customers.csv" : "employees.csv", data);
                    for (int i = 0; i < data.size(); i++)
                    {
                        if (data[i][2] == id)
                        {
                            data[i].push_back(carModel);
                            update(userType == "3" ? "customers.csv" : "employees.csv", data);
                        }
                    }
                }
                else
                {
                    flag = 3;
                    cout << "Specified Car is not available\n";
                }
            }
        }
    }
    if (flag == 0)
        cout << "Specified Car not found\n";
    if (userType == "3")
    {
        Customer c(this->username, this->id, this->record, this->fine, this->amount, this->total, this->rentedCars);
        c.customerMenu();
    }
    else if (userType == "2")
    {
        Employee c(this->username, this->id, this->record, this->fine, this->amount, this->total, this->rentedCars);
        c.employeeMenu();
    }
}

void User::returnCar(string id, string carModel)
{
    int flag = 0;
    vector<vector<string>> data;
    read("cars.csv", data);
    for (int j = 0; j < rentedCars.size(); j++)
    {
        if (rentedCars[j] == carModel)
        {
            for (int i = 0; i < data.size(); i++)
            {
                if (data[i][0] == carModel)
                {
                    if (data[i][6] == "0")
                    {
                        flag = 1;
                        data[i][7] = "";
                        data[i][6] = "1";
                        update("cars.csv", data);
                        cout << "No of days car was rented: ";
                        int days;
                        cin >> days;
                        while (days < 0)
                        {
                            cout << "Invalid days\n";
                            cout << "No of days car was rented: ";
                            cin >> days;
                        }
                        cout << "Car condition: 1 for good, 2 for average and 3 for bad\n";
                        int condition;
                        cin >> condition;
                        while (condition < 1 || condition > 3)
                        {
                            cout << "Invalid condition\n";
                            cout << "Car condition: 1 for good, 2 for average and 3 for bad\n";
                            cin >> condition;
                        }
                        amount = days * stoi(data[i][3]);
                        if (userType == "2")
                            amount -= (amount * 0.15);
                        if (days > 7)
                        {
                            fine = (days - 7) * stoi(data[i][4]);
                            record -= (days - 7) * 5;
                        }
                        if (condition == 2)
                        {
                            record -= 100;
                        }
                        else if (condition == 3)
                        {
                            record -= 200;
                        }
                        total = amount + fine;
                        rentedCars.erase(rentedCars.begin() + j);
                        cout << "Amount: " << amount << "\tFine: " << fine << "\tTotal: " << total << "\n";
                        cout << "Car returned successfully\n";
                        vector<vector<string>> data;
                        read(userType == "3" ? "customers.csv" : "employees.csv", data);
                        // update the record, fine, amount, total and remove the rented Car model in the csv file
                        for (int i = 0; i < data.size(); i++)
                        {
                            if (data[i][2] == id)
                            {
                                data[i][3] = to_string(record);
                                data[i][4] = to_string(fine);
                                data[i][5] = to_string(amount);
                                data[i][6] = to_string(total);
                                for (int j = 7; j < data[i].size(); j++)
                                {
                                    if (data[i][j] == carModel)
                                    {
                                        data[i].erase(data[i].begin() + j);
                                        break;
                                    }
                                }
                                update(userType == "3" ? "customers.csv" : "employees.csv", data);
                            }
                        }
                    }
                }
            }
        }
    }
    if (flag == 0)
        cout << "Specified Car not rented by the customer\n";
    if (userType == "3")
    {
        Customer c(this->username, this->id, this->record, this->fine, this->amount, this->total, this->rentedCars);
        c.customerMenu();
    }
    else if (userType == "2")
    {
        Employee c(this->username, this->id, this->record, this->fine, this->amount, this->total, this->rentedCars);
        c.employeeMenu();
    }
}

void User::getFine(string id)
{
    vector<vector<string>> data;
    if (userType == "3")
    {
        read("customers.csv", data);
    }
    else if (userType == "2")
    {
        read("employees.csv", data);
    }
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i][2] == id)
        {
            cout << "Fine: " << data[i][4] << "\n";
        }
    }
    if (userType == "3")
    {
        Customer c(this->username, this->id, this->record, this->fine, this->amount, this->total, this->rentedCars);
        c.customerMenu();
    }
    else if (userType == "2")
    {
        Employee c(this->username, this->id, this->record, this->fine, this->amount, this->total, this->rentedCars);
        c.employeeMenu();
    }
}

void User::clearFine(string id)
{
    vector<vector<string>> data;
    if (userType == "3")
    {
        read("customers.csv", data);
    }
    else if (userType == "2")
    {
        read("employees.csv", data);
    }
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i][2] == id)
        {
            data[i][4] = "0";
            if (userType == "3")
                update("customers.csv", data);
            else if (userType == "2")
                update("employees.csv", data);
            cout << "Fine cleared successfully\n";
        }
    }
    if (userType == "3")
    {
        Customer c(this->username, this->id, this->record, this->fine, this->amount, this->total, this->rentedCars);
        c.customerMenu();
    }
    else if (userType == "2")
    {
        Employee c(this->username, this->id, this->record, this->fine, this->amount, this->total, this->rentedCars);
        c.employeeMenu();
    }
}

void Customer::customerMenu()
{
    cout << "1. Display available cars\n2. Rent a car\n3. Return a car\n4. Get fine\n5. Clear fine\n6. Logout\n";
    string choice;
    cin >> choice;
    if (choice == "1")
    {
        displayAvailableCars();
    }
    else if (choice == "2")
    {
        cout << "Enter car model: ";
        string carModel;
        cin >> carModel;
        rentCar(id, carModel);
    }
    else if (choice == "3")
    {
        cout << "Enter car model: ";
        string carModel;
        cin >> carModel;
        returnCar(id, carModel);
    }
    else if (choice == "4")
    {
        getFine(id);
    }
    else if (choice == "5")
    {
        clearFine(id);
    }
    else if (choice == "6")
    {
        logout();
    }
    else
    {
        cout << "Invalid choice\n";
    }
    customerMenu();
}

void Employee::employeeMenu()
{
    cout << "1. Display available cars\n2. Rent a car\n3. Return a car\n4. Get fine\n5. Clear fine\n6. Logout\n";
    string choice;
    cin >> choice;
    if (choice == "1")
    {
        displayAvailableCars();
    }
    else if (choice == "2")
    {
        cout << "Enter car model: ";
        string carModel;
        cin >> carModel;
        rentCar(id, carModel);
    }
    else if (choice == "3")
    {
        cout << "Enter car model: ";
        string carModel;
        cin >> carModel;
        returnCar(id, carModel);
    }
    else if (choice == "4")
    {
        getFine(id);
    }
    else if (choice == "5")
    {
        clearFine(id);
    }
    else if (choice == "6")
    {
        logout();
    }
    else
    {
        cout << "Invalid choice\n";
    }
    employeeMenu();
}

void Manager::managerMenu()
{
    cout << "1. Add car\n2. Update car\n3. Delete car\n4. Add customer/employee\n5. Update customer/employee\n6. Delete customer/employee\n7. Display rented cars\n8. Display available cars\n9. Display all cars\n10. Logout\n";
    string choice;
    cin >> choice;
    if (choice == "1")
    {
        addCar();
    }
    else if (choice == "2")
    {
        updateCar();
    }
    else if (choice == "3")
    {
        deleteCar();
    }
    else if (choice == "4")
    {
        addCE();
    }
    else if (choice == "5")
    {
        updateCE();
    }
    else if (choice == "6")
    {
        deleteCE();
    }
    else if (choice == "7")
    {
        displayRentedCars();
    }
    else if (choice == "8")
    {
        displayAvailableCars();
    }
    else if (choice == "9")
    {
        displayAllCars();
    }
    else if (choice == "10")
    {
        logout();
    }
    else
    {
        cout << "Invalid choice\n";
        managerMenu();
    }
}

void Manager::addCar()
{
    Car c;
    c.addCar();
    managerMenu();
}

void Manager::updateCar()
{
    Car c;
    c.updateCar();
    managerMenu();
}

void Manager::deleteCar()
{
    Car c;
    c.deleteCar();
    managerMenu();
}

void Manager::addCE()
{
    cout << "Enter 1 for employee, 2 for customer: ";
    string addType;
    cin >> addType;
    while (addType != "1" && addType != "2")
    {
        cout << "Invalid choice\n";
        cout << "Enter again: 1 for employee, 2 for customer\n";
        cin >> addType;
    }
    cout << "Enter username: ";
    string username;
    cin >> username;
    cout << "Enter password: ";
    string password;
    cin >> password;
    cout << "Enter id: ";
    string id;
    cin >> id;
    vector<vector<string>> data;
    if (addType == "1")
        read("employees.csv", data);
    else if (addType == "2")
        read("customers.csv", data);
    else
    {
        cout << "Invalid choice\n";
        managerMenu();
    }
    vector<string> row;
    row.push_back(username);
    row.push_back(password);
    row.push_back(id);
    row.push_back("500"); // record
    row.push_back("0");   // fine
    row.push_back("0");   // amount
    row.push_back("0");   // total
    row.push_back(" ");   // rented cars
    insert(addType == "1" ? "employees.csv" : "customers.csv", data, row);
    cout << "Added successfully\n";
    managerMenu();
}

void Manager::updateCE()
{
    cout << "Enter 1 for employee, 2 for customer: ";
    string updateType;
    cin >> updateType;
    cout << "Enter id: ";
    string id;
    cin >> id;
    int flag = 0;
    vector<vector<string>> data;
    if (updateType == "1")
        read("employees.csv", data);
    else if (updateType == "2")
        read("customers.csv", data);
    else
    {
        cout << "Invalid choice\n";
        managerMenu();
    }
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i][2] == id)
        {
            flag = 1;
            cout << "Enter 1 to update username, 2 to update password, 3 to update id, 4 to update record, 5 to update fine, 6 to update amount, 7 to update total, 8 to exit\n";
            string choice;
            cin >> choice;
            if (choice == "1")
            {
                cout << "Enter username: ";
                cin >> data[i][0];
                update(updateType == "1" ? "employees.csv" : "customers.csv", data);
            }
            else if (choice == "2")
            {
                cout << "Enter password: ";
                cin >> data[i][1];
                update(updateType == "1" ? "employees.csv" : "customers.csv", data);
            }
            else if (choice == "3")
            {
                cout << "Enter id: ";
                cin >> data[i][2];
                update(updateType == "1" ? "employees.csv" : "customers.csv", data);
            }
            else if (choice == "4")
            {
                cout << "Enter record: ";
                cin >> data[i][3];
                update(updateType == "1" ? "employees.csv" : "customers.csv", data);
            }
            else if (choice == "5")
            {
                cout << "Enter fine: ";
                cin >> data[i][4];
                update(updateType == "1" ? "employees.csv" : "customers.csv", data);
            }
            else if (choice == "6")
            {
                cout << "Enter amount: ";
                cin >> data[i][5];
                update(updateType == "1" ? "employees.csv" : "customers.csv", data);
            }
            else if (choice == "7")
            {
                cout << "Enter total: ";
                cin >> data[i][6];
                update(updateType == "1" ? "employees.csv" : "customers.csv", data);
            }
            else if (choice == "8")
            {
                break;
            }
            else
            {
                cout << "Invalid choice\n";
            }
        }
    }
    if (flag == 0)
        cout << " Not found\n";
    else
        cout << "Updated successfully\n";
    managerMenu();
}

void Manager::deleteCE()
{
    cout << "Enter 1 for employee, 2 for customer: ";
    string delType;
    cin >> delType;
    while (delType != "1" && delType != "2")
    {
        cout << "Invalid choice\n";
        cout << "Enter again: 1 for employee, 2 for customer\n";
        cin >> delType;
    }
    cout << "Enter id: ";
    string id;
    cin >> id;
    int flag = 0;
    vector<vector<string>> data;
    if (delType == "1")
        read("employees.csv", data);
    else if (delType == "2")
        read("customers.csv", data);
    else
    {
        cout << "Invalid choice\n";
        managerMenu();
    }
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i][2] == id)
        {
            flag = 1;
            if (delType == "1")
                deleteRow("employees.csv", data, i);
            else if (delType == "2")
                deleteRow("customers.csv", data, i);
            cout << "Deleted successfully\n";
        }
    }
    if (flag == 0)
        cout << " Not found\n";
    managerMenu();
}
void Manager::displayRentedCars()
{
    Car c;
    c.displayRentedCars();
    managerMenu();
}

void Manager::displayAllCars()
{
    Car c;
    c.displayAllCars();
    managerMenu();
}

void Car::addCar()
{
    cout << "Enter car model: ";
    cin >> carModel;
    cout << "Enter car number: ";
    cin >> carNumber;
    cout << "Enter car color: ";
    cin >> carColor;
    cout << "Enter car price: ";
    cin >> carPrice;
    cout << "Enter car fine: ";
    cin >> carFine;
    cout << "Enter car condition: ";
    cin >> carCondition;
    carAvailability = 1;

    vector<vector<string>> data;
    read("cars.csv", data);
    vector<string> row;
    row.push_back(carModel);
    row.push_back(carNumber);
    row.push_back(carColor);
    row.push_back(to_string(carPrice));
    row.push_back(to_string(carFine));
    row.push_back(to_string(carCondition));
    row.push_back(to_string(carAvailability));
    insert("cars.csv", data, row);
    cout << "Car added successfully\n";
}

void Car::updateCar()
{
    cout << "Enter car number: ";
    cin >> carNumber;
    int flag = 0;
    vector<vector<string>> data;
    read("cars.csv", data);
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i][1] == carNumber)
        {
            flag = 1;
            // give the user the option to update some car details depending upon choice
            cout << "Enter 1 to update car model, 2 to update car number, 3 to update car color, 4 to update car price, 5 to update car fine, 6 to update car condition, 7 to update car availability, 8 to exit\n";
            string choice;
            cin >> choice;
            if (choice == "1")
            {
                cout << "Enter car model: ";
                cin >> carModel;
                data[i][0] = carModel;
                update("cars.csv", data);
            }
            else if (choice == "2")
            {
                cout << "Enter car number: ";
                cin >> carNumber;
                data[i][1] = carNumber;
                update("cars.csv", data);
            }
            else if (choice == "3")
            {
                cout << "Enter car color: ";
                cin >> carColor;
                data[i][2] = carColor;
                update("cars.csv", data);
            }
            else if (choice == "4")
            {
                cout << "Enter car price: ";
                cin >> carPrice;
                data[i][3] = to_string(carPrice);
                update("cars.csv", data);
            }
            else if (choice == "5")
            {
                cout << "Enter car fine: ";
                cin >> carFine;
                data[i][4] = to_string(carFine);
                update("cars.csv", data);
            }
            else if (choice == "6")
            {
                cout << "Enter car condition: ";
                cin >> carCondition;
                data[i][5] = to_string(carCondition);
                update("cars.csv", data);
            }
            else if (choice == "7")
            {
                cout << "Enter car availability: ";
                cin >> carAvailability;
                data[i][6] = to_string(carAvailability);
                update("cars.csv", data);
            }
            else if (choice == "8")
            {
                break;
            }
            else
            {
                cout << "Invalid choice\n";
            }
        }
    }
    if (flag == 0)
        cout << "Car not found\n";
    else
        cout << "Car updated successfully\n";
}

void Car::deleteCar()
{
    cout << "Enter car number: ";
    cin >> carNumber;
    int flag = 0;
    vector<vector<string>> data;
    read("cars.csv", data);
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i][1] == carNumber)
        {
            flag = 1;
            deleteRow("cars.csv", data, i);
            cout << "Car deleted successfully\n";
        }
    }
    if (flag == 0)
        cout << "Car not found\n";
}

void Car::displayRentedCars()
{
    vector<vector<string>> data;
    read("cars.csv", data);
    cout << "Car Model\tCar Number\tCar Color\tCar Price\tCar Fine\tCar Condition\tAvailable\tCar Rented To\n";

    for (int i = 0; i < data.size(); i++)
    {
        if (data[i][6] == "0")
        {
            for (int j = 0; j < (data[i].size()); j++)
            {
                cout << data[i][j] << "\t        ";
            }
            cout << endl;
        }
    }
}

void Car::displayAllCars()
{
    vector<vector<string>> data;
    read("cars.csv", data);
    cout << "Car Model\tCar Number\tCar Color\tCar Price\tCar Fine\tCar Condition\tAvailable\tCar Rented To\n";
    for (int i = 0; i < data.size(); i++)
    {
        for (int j = 0; j < (data[i].size()); j++)
        {
            cout << data[i][j] << "\t        ";
        }
        cout << endl;
    }
}

int main()
{
    User u;
    u.menu();
    return 0;
}