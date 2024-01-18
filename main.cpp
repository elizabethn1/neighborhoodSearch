/*************************************************************************
 * This program analyzes and displays data about restaurant inspections.
 * Users have the option to display overall inspection information,
 * display risk percentages, display passing numbers by neighborhood,
 * search for restaurant by name, or quit.
 * Class: CS 141, Fall 2023
 * System: Zybook Lab
 * @author Elizabeth Ng
 * @version October 30, 2023
 ************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// Restaurant class
class Restaurant {
    public:
        // Restaurant constructor
        Restaurant(string myName, string myAddress, string myInspectionDate, string myRisk, string myInspectionGrade, string myNeighborhood);

        // Restaurant accessors
        string getName() const;
        string getAddress() const;
        string getInspectionDate() const;
        string getRisk() const;
        string getInspectionGrade() const;
        string getNeighborhood() const;

        // Private data members
    private:
        string name;
        string address;
        string inspectionDate;
        string risk;
        string inspectionGrade;
        string neighborhood;
};

// Restaurant constructor
Restaurant::Restaurant(string myName, string myAddress, string myInspectionDate, string myRisk, string myInspectionGrade, string myNeighborhood) {
    name = myName;
    address = myAddress;
    inspectionDate = myInspectionDate;
    risk = myRisk;
    inspectionGrade = myInspectionGrade;
    neighborhood = myNeighborhood;
}

/*
 * Description: Restaurant accessor for name.
 * Input: N/A
 * Output: name (a private data member of the Restaurant class)
 */
string Restaurant::getName() const {
    return name;
}

/*
 * Description: Restaurant accessor for address
 * Input: N/A
 * Output: address (a private data member of the Restaurant class)
 */
string Restaurant::getAddress() const {
    return address;
}

/*
 * Description: Restaurant accessor for inspectionDate
 * Input: N/A
 * Output: inspectionDate (a private data member of the Restaurant class)
 */
string Restaurant::getInspectionDate() const {
    return inspectionDate;
}

/*
 * Description: Restaurant accessor for risk
 * Input: N/A
 * Output: risk (a private data member of the Restaurant class)
 */
string Restaurant::getRisk() const {
    return risk;
}

/*
 * Description: Restaurant accessor for inspectionGrade
 * Input: N/A
 * Output: inspectionGrade (a private data member of the Restaurant class)
 */
string Restaurant::getInspectionGrade() const {
    return inspectionGrade;
}

/*
 * Description: Restaurant accessor for neighborhood
 * Input: N/A
 * Output: neighborhood (a private data member of the Restaurant class)
 */
string Restaurant::getNeighborhood() const {
    return neighborhood;
}

/*
 * Description: Displays the main menu.
 * Inputs: N/A
 * Outputs: This function is of type void, so it doesn't return anything. However, it prints the main menu.
 */
void mainMenu() {
    cout << "Select a menu option: " << endl;
    cout << "   1. Display overall inspection information" << endl;
    cout << "   2. Display risk percentages" << endl;
    cout << "   3. Display passing numbers by neighborhood" << endl;
    cout << "   4. Search for restaurant by name" << endl;
    cout << "   5. Exit" << endl;
    cout << "Your choice: ";
}

/*
 * Description: Displays overall inspection information. (Choice 1)
 * Input: restaurantList (a vector that contains objects of the Restaurant class)
 * Output: This function is of type void, so it doesn't return anything. However, it prints overall inspection information based on restaurantList.
 */
void choice1 (vector<Restaurant>& restaurantList) {
    int vectorSize = restaurantList.size();
    int numRestaurants = 0;
    int numPassed = 0;

    int index = 0; // Keeps track of the index of the restaurant that has the most recent inspection passing

    // Assigns the index variable with the index of the first restaurant in the list that passed an inspection
    for (int a = 0; a < vectorSize; ++a) {
        if (restaurantList.at(a).getInspectionGrade() != "Fail") {
            index = a;
            break;
        }
    }

    // Gets the substrings of a Restaurant object's date (starting at the index variable) to determine month, day, and year
    string month = restaurantList.at(index).getInspectionDate().substr(0, 2);
    string day = restaurantList.at(index).getInspectionDate().substr(3, 2);
    string year = restaurantList.at(index).getInspectionDate().substr(6, 4);

    // Stores the month, day, and year into variables of type int
    int monthNum = stoi(month);
    int dayNum = stoi(day);
    int yearNum = stoi(year);

    for (int i = 0; i < vectorSize; ++i) {
        numRestaurants += 1; // Keeps track of the number of restaurants

        if ((restaurantList.at(i).getInspectionGrade() == "Pass") || (restaurantList.at(i).getInspectionGrade() == "Conditional")) {
            numPassed += 1; // Keeps track of the number restaurants that passed, including those that passed with conditions

            // Gets the substrings of a Restaurant object's date (starting at the index variable) to determine month, day, and year. This is a temporary variable.
            string tempMonth = restaurantList.at(i).getInspectionDate().substr(0, 2);
            string tempDay = restaurantList.at(i).getInspectionDate().substr(3, 2);
            string tempYear = restaurantList.at(i).getInspectionDate().substr(6, 4);

            // Stores the month, day, and year into variables of type int. This is a temporary variable.
            int tempMonthNum = stoi(tempMonth);
            int tempDayNum = stoi(tempDay);
            int tempYearNum = stoi(tempYear);

            // Determines the most recent passing inspection date of a restaurant and the name of that restaurant
            if (tempYearNum > yearNum) {
                monthNum = tempMonthNum;
                dayNum = tempDayNum;
                yearNum = tempYearNum;
                index = i;
            }
            else if (tempYearNum == yearNum) {
                if (tempMonthNum > monthNum) {
                    monthNum = tempMonthNum;
                    dayNum = tempDayNum;
                    yearNum = tempYearNum;
                    index = i;
                }
                else if (tempMonthNum == monthNum) {
                    if (tempDayNum > dayNum) {
                        monthNum = tempMonthNum;
                        dayNum = tempDayNum;
                        yearNum = tempYearNum;
                        index = i;
                    }
                }
            }
        }
    }

    // Display overall inspection information
    cout << "Number of restaurants: " << numRestaurants << endl;
    cout << "Number that pass: " << numPassed << endl;
    cout << "Most recent passing inspection was of " << restaurantList.at(index).getName() << " on " << restaurantList.at(index).getInspectionDate() << endl;
    cout << endl;
}

/*
 * Description: Displays risk percentages. (Choice 2)
 * Input: restaurantList (a vector that contains objects of the Restaurant class)
 * Output: This function is of type void, so it doesn't return anything. However, it prints risk percentages based on restaurantList.
 */
void choice2 (vector<Restaurant>& restaurantList) {
    int vectorSize = restaurantList.size();
    double highRisk = 0.0;
    double mediumRisk = 0.0;
    double lowRisk = 0.0;
    int numRestaurants = 0;

    // Keeps track of the number of high risk, medium risk, and low risk restaurants
    for (int j = 0; j < vectorSize; ++j) {
        numRestaurants += 1;
        if (restaurantList.at(j).getRisk() == "H") {
            highRisk += 1;
        }
        else if (restaurantList.at(j).getRisk() == "M") {
            mediumRisk += 1;
        }
        else if (restaurantList.at(j).getRisk() == "L") {
            lowRisk += 1;
        }
    }

    // Displays percentages of high risk, medium risk, and low risk restaurants
    cout << "High risk: " << fixed << setprecision(1) << (highRisk/numRestaurants) * 100 << "%" << endl;
    cout << "Medium risk: " << fixed << setprecision(1) << (mediumRisk/numRestaurants) * 100 << "%" << endl;
    cout << "Low risk: " << fixed << setprecision(1) << (lowRisk/numRestaurants) * 100 << "%" << endl;
    cout << endl;
}

/*
 * Description: Displays passing numbers by neighborhood. (Choice 3)
 * Input: restaurantList (a vector that contains objects of the Restaurant class)
 * Output: This function is of type void, so it doesn't return anything. However, it prints passing numbers by neighborhood based on restaurantList.
 */
void choice3 (vector<Restaurant>& restaurantList) {
    cout << "Neighborhood";
    cout << "              Passed";
    cout << " Cond. Pass";
    cout << "    Failed" << endl;
    cout << "============";
    cout << "              ======";
    cout << " ==========";
    cout << "    ======" << endl;

    vector <string> neighborhoodList; // A vector that contains unique neighborhood names

    int restaurantSize = restaurantList.size();

    neighborhoodList.push_back(restaurantList.at(0).getNeighborhood());

    // Add unique neighborhoods to the neighborhoodList vector
    for (int i = 1; i < restaurantSize; ++i) {
        string neighborhoodName = restaurantList.at(i).getNeighborhood();
        int counter = 0;
        int size1 = neighborhoodList.size();

        for (int j = 0; j < size1; ++j) {
            if (neighborhoodList.at(j) == neighborhoodName) {
                counter += 1;
            }
        }

        if (counter == 0) {
            neighborhoodList.push_back(neighborhoodName);
        }
    }

    int neighborhoodSize = neighborhoodList.size();

    // Keeps track of the number of restaurant passes, conditionals, and fails for each neighborhood
    for (int k = 0; k < neighborhoodSize; ++k) {
        int pass = 0;
        int conditional = 0;
        int fail = 0;

        int listSize = restaurantList.size();

        for (int l = 0; l < listSize; ++l) {
            if (neighborhoodList.at(k) == restaurantList.at(l).getNeighborhood()) {
                if (restaurantList.at(l).getInspectionGrade() == "Pass") {
                    pass += 1;
                }
                else if (restaurantList.at(l).getInspectionGrade() == "Conditional") {
                    conditional += 1;
                }
                else if (restaurantList.at(l).getInspectionGrade() == "Fail") {
                    fail += 1;
                }
            }
        }

        int spacing1 = 32 - neighborhoodList.at(k).size();
        int spacing2 = 11;
        int spacing3 = 10;

        // Displays the passing numbers for a neighborhood
        cout << neighborhoodList.at(k) << setw(spacing1) << pass << setw(spacing2) << conditional << setw(spacing3) << fail << endl;
    }
    cout << endl;
}

/*
 * Description: Searches for restaurant by name. (Choice 4)
 * Input: restaurantList (a vector that contains objects of the Restaurant class)
 * Output: This function is of type void, so it doesn't return anything. However, it prints restaurants and their info
 * based on a search that the user makes and the restaurants that are contained in restaurantList
 */
void choice4 (vector<Restaurant>& restaurantList) {
    string keyword;
    cout << "Enter restaurant to search for: "; // Prompts user for a restaurant to search for
    cin.ignore();
    getline(cin, keyword);

    int restaurantSize = restaurantList.size();
    string uppercaseName = "";
    int keywordSize = keyword.size();

    // Makes each character of the keyword uppercase
    for (int m = 0; m < keywordSize; ++m) {
        uppercaseName += (toupper(keyword.at(m)));
    }

    keyword = uppercaseName;

    // Display information about each restaurant that contains the keyword in its name
    for (int n = 0; n < restaurantSize; ++n) {
        if (restaurantList.at(n).getName().find(keyword) != string::npos) {
            cout << "Restaurant: " << restaurantList.at(n).getName() << endl;
            cout << "Address: " << restaurantList.at(n).getAddress() << endl;
            cout << "Inspection Date: " << restaurantList.at(n).getInspectionDate() << endl;
            cout << "Inspection Result: " << restaurantList.at(n).getInspectionGrade() << endl;
            cout << endl;
        }
    }
    cout << endl;
}

int main() {
    vector <Restaurant> myList; // A vector that contains Restaurant objects

    ifstream inFS; //Input file stream
    string fileString;
    string fileName;

    // Prompt user for a file to use
    cout << "Enter the data file to use: ";
    cin >> fileName;

    inFS.open(fileName);

    if (!inFS.is_open()) {
        cout << "Could not open the file." << endl;
        return 1;
    }

    // Access and store the contents of the file into a vector
    while (!inFS.eof()) {
        string name;
        string address;
        string inspectionDate;
        string risk;
        string inspectionGrade;
        string neighborhood;

        getline(inFS, name, ',');
        getline(inFS, address, ',');
        getline(inFS, inspectionDate, ',');
        getline(inFS, risk, ',');
        getline(inFS, inspectionGrade, ',');
        getline(inFS, neighborhood);

        // Create a Restaurant object
        Restaurant currentRestaurant (name, address, inspectionDate, risk, inspectionGrade, neighborhood);

        // Add a Restaurant object to a vector
        myList.push_back(currentRestaurant);
    }

    if (!inFS.eof()) {
        cout << "Input failure before reaching end of file." << endl;
    }

    // Done with file, so close it
    inFS.close();

    // Display the main menu
    mainMenu();

    int choice;
    cin >> choice;

    while (choice != 5) {
        // Display overall inspection information
        if (choice == 1) {
            cout << endl;
            choice1(myList);
            mainMenu();
            cin >> choice;
        }
            // Display risk percentages
        else if (choice == 2) {
            cout << endl;
            choice2(myList);
            mainMenu();
            cin >> choice;
        }
            // Display passing numbers by neighborhood
        else if (choice == 3) {
            cout << endl;
            choice3(myList);
            mainMenu();
            cin >> choice;
        }
            // Search for restaurant by name
        else if (choice == 4) {
            cout << endl;
            choice4(myList);
            mainMenu();
            cin >> choice;
        }
            // Quit
        else if (choice == 5) {
            break;
        }
    }

    return 0;
}
