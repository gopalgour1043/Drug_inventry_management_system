#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

// Structure to store user credentials
struct User
{
    string username;
    string password;
    string role; // "admin" or "employee"
};

// Sample users (you can expand this or load from a file for a real application)
vector<User> users = {
    {"admin", "admin123", "admin"},
    {"employee1", "emp123", "employee"},
    {"employee2", "emp456", "employee"}};

// Function to handle user login
bool login(string &role)
{
    system("cls");
    string username, password;
    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;

    // Verify credentials
    for (const auto &user : users)
    {
        if (user.username == username && user.password == password)
        {
            role = user.role;
            return true;
        }
    }
    cout << "Invalid username or password. Please try again.\n";
    return false;
}

class Medicine
{
private:
    // Structure to store medicine details
    struct MedicineInfo
    {
        string name;
        int quantity;
        string expiryDate;
        double price;
    };

    // Vector to store all medicines in stock
    vector<MedicineInfo> inventory;

public:
    // Constructor to add sample medicines (you can modify this or load from file)
    Medicine()
    {
        inventory.push_back({"Paracetamol", 100, "2025-12-31", 5.99});
        inventory.push_back({"Amoxicillin", 50, "2024-11-20", 12.50});
        inventory.push_back({"Ibuprofen", 200, "2026-01-15", 8.75});
    }

    // Function to view current stock
    void viewStock()
    {
        system("cls");
        if (inventory.empty())
        {
            cout << "No medicines available in the stock.\n";
            return;
        }

        cout << " ____________________________ Current Stock ____________________________\n";
        cout << left << setw(20) << "Medicine Name" << setw(10) << "Quantity"
             << setw(15) << "Expiry Date" << setw(10) << "Price" << endl;
        cout << "-----------------------------------------------------------------------\n";

        for (const auto &med : inventory)
        {
            cout << left << setw(20) << med.name << setw(10) << med.quantity
                 << setw(15) << med.expiryDate << setw(10) << med.price << endl;
        }
        cout << "-----------------------------------------------------------------------\n";
    }

    // Function to view expiry date
    void viewExpiry()
    {
        system("cls");
        if (inventory.empty())
        {
            cout << "No medicines available in the stock.\n";
            return;
        }

        cout << " ____________________________ Current Stock ____________________________\n";
        cout << left << setw(20) << "Medicine Name" << setw(10) << "Quantity"
             << setw(15) << "Expiry Date" << setw(10) << endl;
        cout << "-----------------------------------------------------------------------\n";

        for (const auto &med : inventory)
        {
            cout << left << setw(20) << med.name << setw(10) << med.quantity
                 << setw(15) << med.expiryDate << setw(10) << endl;
        }
        cout << "-----------------------------------------------------------------------\n";
    }

    // function to add medicine
    void Addmedicine()
    {
        while (true)
        {
            string name;
            int quantity;
            string expiry_date;
            float price;
            cout << "Enter medicine name: ";
            cin >> name;
            cout << "Enter quantity: ";
            cin >> quantity;
            while (quantity <= 0)
            {
                cout << "Invalid quantity. Please enter a positive integer: ";
                cin >> quantity;
            }
            cout << "Enter expiry date (yyyy-dd-mm format): ";
            cin >> expiry_date;
            cout << "Enter price: ";
            cin >> price;
            while (price < 0)
            {
                cout << "Invalid price. Please enter a non-negative value: ";
                cin >> price;
            }
            inventory.push_back({name, quantity, expiry_date, price});

            cout << "Medicine added successfully...\n";
            cout << "Want to add more medicine? Enter 0 for No, 1 for Yes: ";
            int temp;
            cin >> temp;
            if (temp == 0)
                break;
        }
    }

    // fucntion to remove medicine
    void RemoveMedicine()
    {
        while (true)
        {
            string name;
            int quantity;
            cout << "Enter medicine name: ";
            cin >> name;
            cout << "Enter quantity: ";
            cin >> quantity;

            bool medicineFound = false;

            for (auto it = inventory.begin(); it != inventory.end(); ++it)
            {
                // Access tuple elements directly using structured bindings
                auto &[itemName, itemQuantity, itemExpiryDate, itemPrice] = *it;

                if (itemName == name)
                {
                    medicineFound = true;
                    if (itemQuantity >= quantity)
                    {
                        itemQuantity -= quantity;
                        if (itemQuantity == 0)
                        {
                            inventory.erase(it);
                        }
                    }
                    else
                    {
                        cout << "Not enough quantity to remove. Current quantity: " << itemQuantity << endl;
                    }
                    break;
                }
            }

            if (!medicineFound)
            {
                cout << "Medicine not found in inventory." << endl;
            }
            else
            {
                cout << "Medicine removed successfully.\n";
            }

            cout << "Do you want to remove more medicine? Enter 0 for No, 1 for Yes: ";
            int temp;
            cin >> temp;
            if (temp == 0)
                break;
        }
    }

    // Function to update the quantity of an item in the inventory
    void updateQuantity()
    {
        string medicineName;
        int newQuantity;
        bool found = false;

        cout << "Enter the name of the medicine to update: ";
        cin >> medicineName;

        for (auto &medicine : inventory)
        {
            if (medicine.name == medicineName)
            {
                cout << "Current Quantity: " << medicine.quantity << endl;
                cout << "Enter new quantity: ";
                cin >> newQuantity;

                medicine.quantity = newQuantity;
                cout << "Quantity updated successfully.\n";
                found = true;
                break;
            }
        }

        if (!found)
        {
            cout << "Medicine not found in inventory.\n";
        }
    }

    // Function to return a medicine and calculate the return price
    void returnMedicine()
    {
        string medicineName;
        int returnQuantity;
        bool found = false;

        cout << "Enter the name of the medicine to return: ";
        cin >> medicineName;

        for (auto &medicine : inventory)
        {
            if (medicine.name == medicineName)
            {
                cout << "Current Quantity: " << medicine.quantity << endl;
                cout << "Enter the quantity of medicine to return: ";
                cin >> returnQuantity;

                if (returnQuantity <= 0)
                {
                    cout << "Invalid quantity. The return quantity must be positive.\n";
                    return;
                }

                double returnPrice = returnQuantity * medicine.price;

                medicine.quantity += returnQuantity;
                cout << "Medicine returned successfully. Updated Quantity: " << medicine.quantity << endl;
                cout << "Total Return Price: $" << returnPrice << endl;
                found = true;
                break;
            }
        }

        if (!found)
        {
            cout << "Medicine not found in inventory.\n";
        }
    }

    // Function to create a bill by adding medicines and showing the total price
    void createBill()

    {
        vector<MedicineInfo> selectedMedicines;
        string medicineName;
        int quantity;
        char choice;
        double totalBill = 0.0;

        do
        {
            bool found = false;
            cout << "Enter the name of the medicine to add to the bill: ";
            cin >> medicineName;

            for (auto &medicine : inventory)
            {
                if (medicine.name == medicineName)
                {
                    found = true;
                    cout << "Current Quantity Available: " << medicine.quantity << endl;
                    cout << "Enter quantity to purchase: ";
                    cin >> quantity;

                    if (quantity <= 0 || quantity > medicine.quantity)
                    {
                        cout << "Invalid quantity. Please enter a valid quantity.\n";
                    }
                    else
                    {

                        medicine.quantity -= quantity;

                        MedicineInfo selectedMedicine = {medicine.name, quantity, medicine.expiryDate, medicine.price};
                        selectedMedicines.push_back(selectedMedicine);

                        double itemTotal = quantity * medicine.price;
                        totalBill += itemTotal;

                        cout << "Added " << quantity << " of " << medicine.name << " to the bill. Total: $" << fixed << setprecision(2) << itemTotal << endl;
                    }
                    break;
                }
            }

            if (!found)
            {
                cout << "Medicine not found in inventory.\n";
            }

            cout << "Do you want to add another medicine? (y/n): ";
            cin >> choice;
        } while (choice == 'y' || choice == 'Y');

        cout << "\n------------------- Bill -------------------\n";
        cout << left << setw(20) << "Medicine Name" << setw(10) << "Quantity" << setw(15) << "Unit Price" << setw(10) << "Total" << endl;
        cout << "-------------------------------------------------------------\n";

        for (const auto &medicine : selectedMedicines)
        {
            double itemTotal = medicine.quantity * medicine.price;
            cout << left << setw(20) << medicine.name << setw(10) << medicine.quantity
                 << setw(15) << fixed << setprecision(2) << medicine.price
                 << setw(10) << itemTotal << endl;
        }

        cout << "-------------------------------------------------------------\n";
        cout << "Total Bill Amount: $" << fixed << setprecision(2) << totalBill << endl;
        cout << "-------------------------------------------------------------\n";
    }
    // Function to convert a string to lowercase for case-insensitive search
    string toLowerCase(const string &str)
    {
        string lowerStr = str;
        transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), [](unsigned char c)
                  { return tolower(c); });
        return lowerStr;
    }
    // Function to search for medicines in the inventory
    void searchItem()
    {
        string searchTerm;
        cout << "Enter medicine name to search: ";
        cin >> searchTerm;

        // Debug: Print the entered search term to ensure it's being captured correctly
        cout << "Debug: You entered: '" << searchTerm << "'" << endl;

        // Ensure the search term is not empty or just spaces
        if (searchTerm.empty() || searchTerm.find_first_not_of(' ') == string::npos)
        {
            cout << "Search term cannot be empty or just spaces. Please enter a valid name." << endl;
            return;
        }

        string search = toLowerCase(searchTerm);
        bool found = false;

        // Search through the inventory for matching items
        for (const auto &medicine : inventory)
        {
            if (toLowerCase(medicine.name).find(search) != string::npos)
            {
                cout << "Name: " << medicine.name
                     << ", Quantity: " << medicine.quantity
                     << ", Expiry Date: " << medicine.expiryDate
                     << ", Price: $" << medicine.price << endl;
                found = true;
            }
        }

        if (!found)
        {
            cout << "No medicines found matching the search term: " << searchTerm << endl;
        }
    }
};
// Admin section
void adminMenu(Medicine &medicineManager)
{
    string role;
    if (login(role) && role == "admin")
    {
        system("cls");
        while (true)
        {
            int choice;
            cout << " ____________________________ Admin Menu ____________________________\n";
            cout << "|                                                                   |\n";
            cout << "|        1. View Stock                                              |\n";
            cout << "|        2. Remove Medicine                                         |\n";
            cout << "|        3. Add Medicine                                            |\n";
            cout << "|        4. View Expiry Date                                        |\n";
            cout << "|        5. Return to Main Menu                                     |\n";
            cout << "|___________________________________________________________________|\n";
            cout << "---------------------------------------------------------------------\n";
            cout << "Enter the Choice : ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                medicineManager.viewStock();
                break;
            case 2:
                medicineManager.RemoveMedicine();
                break;
            case 3:
                medicineManager.Addmedicine();
                break;
            case 4:
                medicineManager.viewExpiry();
                break;
            case 5:
                cout << "Returning to Main Menu...\n";
                return; // Return to the main menu
            default:
                cout << "Invalid Input. Please enter a valid choice.\n";
                break;
            }
        }
    }
    else
    {
        cout << "Unauthorized access or failed login.\n";
    }
}

// Employee section
void employeeMenu(Medicine &medicineManager)
{

    system("cls");
    while (true)
    {
        int choice;
        cout << " ____________________________ Employee Menu ____________________________\n";
        cout << "|                                                                    |\n";
        cout << "|        1. View Inventory                                           |\n";
        cout << "|        2. Update Item Quantity                                     |\n";
        cout << "|        3. Search Items                                             |\n";
        cout << "|        4. Return Medicine                                          |\n";
        cout << "|        5. Create Bill                                              |\n";
        cout << "|        6. Return to Main Menu                                      |\n";
        cout << "|____________________________________________________________________|\n";
        cout << "----------------------------------------------------------------------\n";
        cout << "Enter the Choice : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            medicineManager.viewStock();
            break;

        case 2:
            medicineManager.updateQuantity();
            break;
        case 3:
            medicineManager.searchItem();
            break;
        case 4:
            medicineManager.returnMedicine();
            break;

        case 5:
            medicineManager.createBill();
            break;
        case 6:
            cout << "Returning to Main Menu...\n";
            return;
        default:
            cout << "Invalid Input. Please enter a valid choice.\n";
            break;
        }
        cout << endl;
    }
}

int main()
{
    system("cls");
    Medicine medicineManager;
    cout << "********************************************************************************" << endl;
    cout << "*                                                                              *" << endl;
    cout << "*                        WELCOME TO DRUG INVENTORY MANAGEMENT                  *" << endl;
    cout << "*                                                                              *" << endl;
    cout << "********************************************************************************" << endl;
    cout << endl
         << endl;

    while (1)
    {
        int mainchoice;
        cout << "Who are You ? (CHOOSE ONE) \n";
        cout << "______________________________" << endl;
        cout << "|                             |\n";
        cout << "|        1. Admin             |\n";
        cout << "|        2. Employee          |\n";
        cout << "|        3. Exit              |\n";
        cout << "|_____________________________|\n";
        cout << "-------------------------------\n";
        cout << "Enter Choice : ";
        cin >> mainchoice;

        switch (mainchoice)
        {
        case 1:
            adminMenu(medicineManager);
            break;
        case 2:
            employeeMenu(medicineManager);
            break;
        case 3:
            cout << "\nSEE YOU AGAIN... THANK YOU!!!\n\n";
            return 0;
        default:
            system("cls");
            cout << endl
                 << "Invalid Input" << endl
                 << endl;
            cout << "Enter Choice Again : " << endl;
            break;
        }
        cout << endl;
    }

    return 0;
}
