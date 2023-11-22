 
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <string>
#include <algorithm>

using namespace std;

namespace CabAggregator {

    // Base class for User
    class User {
    public:
        User(string name, string phoneNumber, string email)
            : name(name), phoneNumber(phoneNumber), email(email) {}

        virtual ~User() = default;

        virtual void displayDetails() const {
            cout << "Name: " << name << "\nPhone Number: " << phoneNumber << "\nEmail: " << email << "\n";
        }

    protected:
        string name;
        string phoneNumber;
        string email;
    };

    // Driver class inheriting from User
    class Driver : public User {
    public:
        Driver(string name, string phoneNumber, string email,
               string transportMode, string vehicleNumber)
            : User(name, phoneNumber, email), transportMode(transportMode), vehicleNumber(vehicleNumber), available(true) {
                // Incrementing driver count on creation
                driverCount++;
            }

        void displayDetails() const override {
            User::displayDetails();
            cout << "Transport Mode: " << transportMode << "\nVehicle Number: " << vehicleNumber << "\n";
            cout << "Availability: " << (available ? "Available" : "Not Available") << "\n";
        }

        // Function to check if the driver is available
        bool isAvailable() const {
            return available;
        }

        // Set the availability of the driver
        void setAvailability(bool status) {
            available = status;
        }

        // Static member for counting drivers
        static int driverCount;

        // Static method to get driver count
        static int getDriverCount() {
            return driverCount;
        }

        // Friend function to access private members
        friend void showDriverCount();

    private:
        string transportMode;
        string vehicleNumber;
        bool available;
    };

    // Initializing static member
    int Driver::driverCount = 0;

    // Function to show driver count using friend function
    void showDriverCount() {
        cout << "Total Drivers: " << Driver::getDriverCount() << endl;
    }

    // Vector of drivers
    vector<Driver> drivers;

    // Lambda function to display driver details
    auto displayDriverDetails = [](const Driver& driver) {
        driver.displayDetails();
    };

    // Function to check driver availability for a trip
    void checkDriverAvailability(const Driver& driver) {
        if (driver.isAvailable()) {
            cout << "Driver is available for the trip.\n";
        } else {
            cout << "Driver is not available for the trip.\n";
        }
    }
    // Function to read driver details from CSV file and populate the vector
    void readDriverDetailsFromFile(const string& filename) {
    ifstream driverFile(filename);
    if (!driverFile.is_open()) {
        cerr << "Error opening the drivers file." << endl;
        return;
    }

    string line;
    while (getline(driverFile, line)) {
        stringstream ss(line);
        string name, phoneNumber, email, transportMode, vehicleNumber;
        getline(ss, name, ',');
        getline(ss, phoneNumber, ',');
        getline(ss, email, ',');
        getline(ss, transportMode, ',');
        getline(ss, vehicleNumber, ',');

        Driver driver(name, phoneNumber, email, transportMode, vehicleNumber);
        drivers.push_back(driver);
    }

    driverFile.close();
}


}
namespace MyFileIO {
    using namespace std;

    struct User1 {
        string username;
        string password;
        string phone_no;
    };

     struct Driver1{
        string username;
        string password;
        string phone_no;
        string license_no;
    };

    vector<User1> readUsersFromFile(const string& filename) {
    vector<User1> users;
    ifstream file(filename);

    if (!file.is_open()) {
        throw runtime_error("Failed to open the file.");
    }

    string line;
    while (getline(file, line)) {
        size_t commaPos = line.find(",");
        if (commaPos != string::npos) {
            User1 user;
            user.username = line.substr(0, commaPos);

            // Check if there's another comma after the username
            size_t secondCommaPos = line.find(",", commaPos + 1);
            if (secondCommaPos != string::npos) {
                // If there's another comma, extract the password and phone number
                user.password = line.substr(commaPos + 1, secondCommaPos - commaPos - 1);
                user.phone_no = line.substr(secondCommaPos + 1);
            } else {
                user.password = line.substr(commaPos + 1);
            }

            users.push_back(user);
        }
    }
    file.close();
    return users;
    }

    void writeToCSV(const string& filename, const string& data) {
        try {
            ofstream file;
            file.open(filename, ios::out | ios::app); // Open in append mode

            if (!file.is_open()) {
                throw runtime_error("Failed to open the file.");
            }

            file << data << endl;
            file.close();
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
            throw; // Re-throw the exception to the caller
        }
    }
    vector<Driver1> readDriversFromFile(const string& filename) {
    vector<Driver1> users;
    ifstream file(filename);

    if (!file.is_open()) {
        throw runtime_error("Failed to open the file.");
    }

    string line;
    while (getline(file, line)) {
        size_t commaPos = line.find(",");
        if (commaPos != string::npos) {
            Driver1 user;
            user.username = line.substr(0, commaPos);

            // Check if there's another comma after the username
            size_t secondCommaPos = line.find(",", commaPos + 1);
            if (secondCommaPos != string::npos) {
                // If there's another comma, extract the password and phone number
                user.password = line.substr(commaPos + 1, secondCommaPos - commaPos - 1);
                user.phone_no = line.substr(secondCommaPos + 1);
            } else {
                user.password = line.substr(commaPos + 1);
            }

            users.push_back(user);
        }
    }
    file.close();
   return users;
}
void writeToCSV_driver(const string& filename, const string& data) {
        try {
            ofstream file;
            file.open(filename, ios::out | ios::app); // Open in append mode

            if (!file.is_open()) {
                throw runtime_error("Failed to open the file.");
            }

            file << data << endl;
            file.close();
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
            throw; // Re-throw the exception to the caller
        }
    }

}
namespace FeedbackNamespace {
    class FeedbackException : public exception {
    public:
        FeedbackException(const string& message) : message_(message) {}
        const char* what() const noexcept override { return message_.c_str(); }

    private:
        string message_;
    };

    class Feedback {
    public:
    Feedback(const string& comment, int rating)
        : comment_(comment), rating_(rating) {
        if (rating < 1 || rating > 5) {
            throw FeedbackException("Rating should be between 1 and 5.");
        }
    }

    virtual void printFeedback() const {
        cout << "Comment: " << comment_ << "\nRating: " << rating_ << "\n";
    }

    string getComment() const { return comment_; }
    int getRating() const { return rating_; }

protected:
    string comment_;
    int rating_;
};


    class DriverFeedback : public Feedback {
    public:
        DriverFeedback(const string& comment, int rating)
            : Feedback(comment, rating) {}

        void printFeedback() const override {
            Feedback::printFeedback();
            cout << "Driver Feedback\n";
        }
    };

    class PassengerFeedback : public Feedback {
    public:
        PassengerFeedback(const string& comment, int rating)
            : Feedback(comment, rating) {}

        void printFeedback() const override {
            Feedback::printFeedback();
            cout << "Passenger Feedback\n";
        }
    };

    void writeFeedbackToCSV(const Feedback* feedback, ofstream& file) {
        file << feedback->getComment() << "," << feedback->getRating() << ",";
        if (dynamic_cast<const DriverFeedback*>(feedback)) {
            file << "Driver Feedback\n";
        } else if (dynamic_cast<const PassengerFeedback*>(feedback)) {
            file << "Passenger Feedback\n";
        }
    }
}

using namespace std;
using namespace CabAggregator;
using namespace MyFileIO;
using namespace FeedbackNamespace;

class Payment {
private:
    int opt;
    static const string options[2];

public:
    Payment(int fee) {
        do {
            cout << "Please choose a payment option for your ride" << endl;
            for (int i = 0; i < 2; i++) {
                cout << i + 1 << ". " << options[i] << endl;
            }
            cin >> opt;

            auto printPaymentDetails = [&]() {
                cout << "Amount: " << fee << " Rs" << endl; //lambda func-captures variable from surroundinf scope with ref
            };

            if (opt == 1) {
                cout << "You have chosen to pay using UPI" << endl;
                cout << "UPI ID: xxxxxxxx@oksbi" << endl;
                printPaymentDetails();
            } else if (opt == 2) {
                cout << "You have chosen to pay using Cash" << endl;
                printPaymentDetails();
            } else {
                cout << "Invalid payment option. Please choose 1 or 2." << endl;
                continue;
            }
        } while (opt != 1 && opt != 2);
    }
};

const string Payment::options[2] = {"GPay/UPI", "Cash"};

class View {
private:
    string roll, pick, drop, dist, time, fee, aut, ch, cab, auto_fee, cab_fee;

public:
    inline void displayPaths(ifstream &mystream) {
        string line;
        while (getline(mystream, line)) { //reads a line from mystream to var
            stringstream ss(line);//initialise object ss with line
            getline(ss, roll, ','); //from ss store in roll until delimiter ,
            getline(ss, pick, ',');
            getline(ss, drop, ',');
            cout << roll << ". Pickup: " << pick << "  Drop: " << drop << endl;
        }
    }

    string displaydetails(ifstream &mystream, int choice) {
        string line;
        while (getline(mystream, line)) {
            stringstream ss(line);
            getline(ss, roll, ',');
            int temp = stoi(roll);
            if (choice == temp) {
                getline(ss, pick, ',');
                getline(ss, drop, ',');
                getline(ss, dist, ',');
                getline(ss, time, ',');
                getline(ss, aut, ',');
                getline(ss, auto_fee, ',');
                getline(ss, cab, ',');
                getline(ss, cab_fee, ',');

                do {
                    cout << "Would you like to book a cab or an auto?" << endl;

                    cout << "Auto fee:" << auto_fee << endl;
                    cout << "Cab fee:" << cab_fee << endl;
                    cin >> ch;
                    if (ch == "auto" || ch == "Auto" ||ch=="a"||ch=="A") 
                    {
                        cout << "Pickup: " << pick << " Drop: " << drop << " Distance: " << dist << " km Duration: " << time << " min Fee: " << auto_fee << " Rs" << endl;
                        return auto_fee;
                    } else if (ch == "cab" || ch == "Cab"||ch=="c"||ch=="C") 
                    {
                        cout << "Pickup: " << pick << " Drop: " << drop << " Distance: " << dist << " km Duration: " << time << " min Fee: " << cab_fee << " Rs" << endl;
                        return cab_fee;
                    } else 
                    {
                        cout << "Invalid input, please choose auto or cab" << endl;
                    }

                } while (ch != "auto" && ch != "cab" && ch != "Cab" && ch != "Auto" &&ch!="C" && ch!="a" && ch!="A" && ch!="C");
            }
        }
        return "";
    }
};

class PaymentView : public View 
{
public:
    
    string displaydetails(ifstream &mystream, int choice)
    {
        string fees = View::displaydetails(mystream, choice); // Call the base class function
        int final_fees = stoi(fees);
        Payment obj1(final_fees);
        return fees;
    }
};

int main() 
{   
      // Read driver details from the CSV file
    CabAggregator::readDriverDetailsFromFile("drivers.csv");
    cout << "Welcome:" << endl;
    cout << "1.User" << endl;
    cout << "2.Driver" << endl;
    int act;
    cin>>act;
    int temp=1;
    switch(act)
    {
        case 1:
        {
        {   
            while(temp)
            {
            using namespace MyFileIO;

            cout << "Choose an option:" << endl;
            cout << "1. Login" << endl;
            cout << "2. Sign up" << endl;

            int option;
            cin >> option;

            if (option == 1) {
                // Login
                try {
                    vector<User1> users = readUsersFromFile("user.csv");

                    string searchUsername, searchPassword;
                    cout << "Username: ";
                    cin >> searchUsername;
                    cout << "Password: ";
                    cin >> searchPassword;

                    bool found = false;
                    for (const User1& user : users) {
                        if (user.username == searchUsername) {
                            found = true;
                            if (searchPassword == user.password) {
                                cout << "Success! Logged in." << endl;temp=0;
                            } else {
                                cout << "Wrong Password" << endl;
                            }
                            break;
                        }
                    }

                    if (!found) {
                        cout << "Username not found." << endl;
                    }
                } catch (const exception& e) {
                    cerr << "Error: " << e.what() << endl;
                    return 1;
                }

            } else if (option == 2) {
                // Sign up
                try {
                    string username, password,phone_no;
                    cout << "Enter username: ";
                    cin >> username;
                    cout << "Enter password: ";
                    cin >> password;
                    cout << "Enter phone number: ";
                    cin >> phone_no;

                    string data = username + "," + password+","+phone_no;
                    writeToCSV("user.csv", data);

                    cout << "Successfully signed up!" << endl;temp=0;

                } catch (const exception& e) {
                    cerr << "Error: " << e.what() << endl;
                    return 1;
                }

            } else 
            {
                cout << "Invalid option. Exiting." << endl;
                return 1;
            }
            }
            ifstream inputTxt("input.txt");
            string csvFilePath;
            inputTxt >> csvFilePath;
            ifstream mystream(csvFilePath);
            if (!mystream.is_open()) {
                cerr << "Error opening the file." << endl;
                return 0;
            }

            cout << "Pickup and Drop Locations" << endl;
            View obj;
            obj.displayPaths(mystream);

            mystream.clear();
            mystream.seekg(0);

            int choice;
            cout << "Pick a path (enter a number): ";
            try {
                cin >> choice;
                if (cin.fail()) 
                {
                    throw runtime_error("Invalid input. Please enter a valid number.");
                }
            } 
            catch (const exception& e) 
            {
                cerr << "Error: " << e.what() << endl;
                mystream.close();
                return 1;
            }

            PaymentView paymentView;
            try {
                string fees = paymentView.displaydetails(mystream, choice);
                mystream.close();
                
            } 
            catch (const exception& e) 
            {
                cerr << "Error: " << e.what() << endl;
                mystream.close();
                return 1;
            }

            cout << "Rate your experience!" << endl;
            string comment;
            int rating;

            cout << "Enter feedback comment: ";
            cin.ignore(); 
            getline(cin, comment);
            cout << "Enter rating (1-5): ";
            cin >> rating;
            try {
            Feedback* feedback;
        
            feedback = new PassengerFeedback(comment, rating);
        

            ofstream feedbackFile("ride_feedback.csv", ios::app);
        if (!feedbackFile.is_open()) {
            cerr << "Error: Failed to open feedback file.\n";
            return 1;
        }
        FeedbackNamespace::writeFeedbackToCSV(feedback, feedbackFile);
        feedbackFile.close();

        feedback->printFeedback(); 

        delete feedback; // Clean up dynamically allocated memory

        } catch (const FeedbackNamespace::FeedbackException& e) {
        cerr << "Error: " << e.what() << "\n";
        }

            break;
        }
    }
        case 2:
        {
    while(temp)
            {
            using namespace MyFileIO;

            cout << "Choose an option:" << endl;
            cout << "1. Login" << endl;
            cout << "2. Sign up" << endl;

            int option;
            cin >> option;

            if (option == 1) {
                // Login
                try {
                    vector<Driver1> users = readDriversFromFile("drivers.csv");

                    string searchUsername, searchPassword;
                    cout << "Username: ";
                    cin >> searchUsername;
                    cout << "Password: ";
                    cin >> searchPassword;

                    bool found = false;
                    for (const Driver1& user : users) {
                        if (user.username == searchUsername) {
                            found = true;
                            if (searchPassword == user.password) {
                                cout << "Success! Logged in." << endl;temp=0;
                            } else {
                                cout << "Wrong Password" << endl;
                            }
                            break;
                        }
                    }

                    if (!found) {
                        cout << "Username not found." << endl;
                    }
                } catch (const exception& e) {
                    cerr << "Error: " << e.what() << endl;
                    return 1;
                }

            } else if (option == 2) {
                // Sign up
                try {
                    string username, password,phone_no,lic_no,email,vehicle;
                    cout << "Enter username: ";
                    cin >> username;
                    cout << "Enter password: ";
                    cin >> password;
                    cout << "Enter phone number: ";
                    cin >> phone_no;
                    cout<<"Enter email:";
                    cin>>email;
                    cout<<"Enter vehicle:";
                    cin>>vehicle;
                    cout << "Enter licence number: ";
                    cin >> lic_no;
                    string data = username + "," + password + "," +phone_no + ","+email+","+vehicle+","+lic_no;
                    writeToCSV("drivers.csv", data);

                    cout << "Successfully signed up!" << endl;temp=0;

                } catch (const exception& e) {
                    cerr << "Error: " << e.what() << endl;
                    return 1;
                }

            } else 
            {
                cout << "Invalid option. Exiting." << endl;
                return 1;
            }
            }

           
    using namespace CabAggregator;

    cout << "Driver Module:" << endl;
    cout << "1. Display Driver Details" << endl;
    cout << "2. Check Driver Availability" << endl;
    cout << "3. Set Driver Availability" << endl;
    cout << "4. Display Total Driver Count" << endl;

    int driverOption;
    cin >> driverOption;

    switch (driverOption) {
       /*  case 1:
            // Display Driver Details
            if (drivers.empty()) {
                cout << "No drivers available.\n";
            } else {
                cout << "Driver Details:\n";
                for_each(drivers.begin(), drivers.end(), displayDriverDetails);
            }
            break; */
            case 1:
    // Display Driver Details
    if (drivers.empty()) {
        cout << "No drivers available.\n";
    } else {
        // Prompt for a specific driver index
        cout << "Enter the index of the driver to display details: ";
        int driverIndex;
        cin >> driverIndex;

        if (driverIndex >= 0 && driverIndex < drivers.size()) {
            // Display details for the specific driver
            displayDriverDetails(drivers[driverIndex]);
        } else {
            cout << "Invalid driver index.\n";
        }
    }
    break;


        case 2:
            // Check Driver Availability
            if (drivers.empty()) {
                cout << "No drivers available.\n";
            } else {
                cout << "Enter the index of the driver to check availability: ";
                int driverIndex;
                cin >> driverIndex;

                if (driverIndex >= 0 && driverIndex < drivers.size()) {
                    checkDriverAvailability(drivers[driverIndex]);
                } else {
                    cout << "Invalid driver index.\n";
                }
            }
            break;

        /* case 3:
            // Set Driver Availability
            if (drivers.empty()) {
                cout << "No drivers available.\n";
            } else {
                cout << "Enter the index of the driver to set availability: ";
                int driverIndex;
                cin >> driverIndex;

                if (driverIndex >= 0 && driverIndex < drivers.size()) {
                    cout << "Enter availability (1 for available, 0 for not available): ";
                    bool availability;
                    cin >> availability;

                    drivers[driverIndex].setAvailability(availability);
                    cout << "Availability set successfully.\n";
                } else {
                    cout << "Invalid driver index.\n";
                }
            }
            break; */
        case 3:
    // Set Driver Availability
    if (drivers.empty()) {
        cout << "No drivers available.\n";
    } else {
        cout << "Enter the index of the driver to set availability: ";
        int driverIndex;
        cin >> driverIndex;

        try {
            if (driverIndex < 0 || driverIndex >= drivers.size()) {
                throw out_of_range("Invalid driver index.");
            }

            cout << "Enter availability (1 for available, 0 for not available): ";
            bool availability;
            cin >> availability;

            drivers.at(driverIndex).setAvailability(availability);
            cout << "Availability set successfully.\n";

        } catch (const exception& e) {
            cerr << "Error: " << e.what() << "\n";
        }
    }
    break;

        case 4:
            // Display Total Driver Count
            showDriverCount();
            break;

        default:
            cout << "Invalid option.\n";
            break;
    }
    cout << "Rate your experience!" << endl;
            string comment1;
            int rating1;

            cout << "Enter feedback comment: ";
            cin.ignore(); 
            getline(cin, comment1);
            cout << "Enter rating (1-5): ";
            cin >> rating1;
            try {
            Feedback* feedback1;
        
            feedback1 = new DriverFeedback(comment1, rating1);
        

            ofstream feedbackFile("ride_feedback.csv", ios::app);
            if (!feedbackFile.is_open()) {
            cerr << "Error: Failed to open feedback file.\n";
            return 1;
            }
            FeedbackNamespace::writeFeedbackToCSV(feedback1, feedbackFile);
            feedbackFile.close();

            feedback1->printFeedback(); 

            delete feedback1; // Clean up dynamically allocated memory

            } catch (const FeedbackNamespace::FeedbackException& e) {
            cerr << "Error: " << e.what() << "\n";
            }

            break;
        }

            
        default:
        {
            cout << "Invalid input\n" << endl;
            break;
        }
    }
        return 0;
}