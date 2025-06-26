#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <climits>
#include <limits>
#include <algorithm>
#include <cctype>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <fstream>
#include <cstdio>
#include <conio.h>
#include <map>

const int INF = INT_MAX;
const int N = 25; // Number of stations

using namespace std;
class metrostation;

void mainMenu(vector<metrostation> station);
void userMenu(vector<metrostation> station);
void staffMenu(vector<metrostation> station);

string getHiddenPassword() {
    string password = "";
    char ch;

    while (true) {
        ch = _getch();

        if (ch == 13) {
            cout << endl;
            break;
        }

        else if (ch == 8) {
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        }

        else {
            password += ch;
            cout << '*';
        }
    }

    return password;
}

COORD coord = {0,0};
void gotoxy(int a, int b)
{
    coord.X = a;
    coord.Y = b;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void design(int x, int y)
{
    for (int i = 0; i <= x; i++)
        cout<<(char)y;
}
class metrostation
{
    private:
      string station_id;
      string station_name;
      string linecolor;
      bool hasWashroom;
      bool hasParking;
      int numbering;
      vector<pair<int, int>> neighbors; // Neighbors with distance
      public:
      metrostation(){}
      metrostation(string id,string n,string lc,bool w,bool p,int no)
      {
        station_id=id;
        station_name=n;
        linecolor=lc;
        hasWashroom=w;
        hasParking=p;
        numbering=no;
      }

       void addNeighbor(int neighborStationId, int distance)
      {
          neighbors.push_back({neighborStationId, distance});
      }

      vector<pair<int, int>> getNeighbors() const
      {
          return neighbors;
      }

      string getStationID()
      {
          return station_id;
      }
      string getStation_name() const
      {
          return station_name;
      }
      bool haswashroom() const {
        return hasWashroom;
    }
    bool hasparking() const {
        return hasParking;

    }
    int getDegree() const {
        return neighbors.size();}

string findNearestStationWithParking(const string& startID, vector<metrostation>& stations) {
        // Create a map to relate station IDs to their indices
        unordered_map<string, int> stationIndexMap;
        for (int i = 0; i < stations.size(); i++) {
            stationIndexMap[stations[i].getStationID()] = i;  // Map each station ID to its index
        }

        // Check if the start station ID exists in the map
        if (stationIndexMap.find(startID) == stationIndexMap.end()) {
            return "Invalid Station ID";  // Return error message for invalid start station
        }

        int startIndex = stationIndexMap[startID];  // Get the index of the starting station
        vector<bool> visited(stations.size(), false);  // Track visited stations
        queue<int> q;  // Queue for BFS

        q.push(startIndex);  // Start BFS from the starting station
        visited[startIndex] = true;

        while (!q.empty()) {
            int currentStationIndex = q.front();  // Get the station index from the front of the queue
            q.pop();

            // Check if the current station has parking
            if (stations[currentStationIndex].hasparking()) {
                return stations[currentStationIndex].getStation_name();  // Return the station ID if it has parking
            }

            // Explore the neighbors
            for (auto neighbor : stations[currentStationIndex].getNeighbors()) {
                int nextStationIndex = neighbor.first;  // Get the neighbor's index

                if (!visited[nextStationIndex]) {
                    visited[nextStationIndex] = true;
                    q.push(nextStationIndex);  // Add the neighbor to the queue
                }
            }
        }

        return "No nearby station with parking found";  // If no station with parking is found
    }


string findNearestStationWithWashroom(const string& startID, vector<metrostation>&station) {
        // Create a map to relate station IDs to their indices
        unordered_map<string, int> stationIndexMap;
        for (int i = 0; i < station.size(); i++) {
            stationIndexMap[station[i].getStationID()] = i;  // Map each station ID to its index
        }

        // Check if the start station ID exists in the map
        if (stationIndexMap.find(startID) == stationIndexMap.end()) {
            return "Invalid Station ID";  // Return error message for invalid start station
        }

        int startIndex = stationIndexMap[startID];  // Get the index of the starting station
        vector<bool> visited(station.size(), false);  // Track visited stations
        queue<int> q;  // Queue for BFS

        q.push(startIndex);  // Start BFS from the starting station
        visited[startIndex] = true;

        while (!q.empty()) {
            int currentStationIndex = q.front();  // Get the station index from the front of the queue
            q.pop();

            // Check if the current station has a washroom
            if (station[currentStationIndex].haswashroom()) {
                return station[currentStationIndex].getStation_name();  // Return the station ID if it has a washroom
            }

            // Explore the neighbors
            for (auto neighbor : station[currentStationIndex].getNeighbors()) {
                int nextStationIndex = neighbor.first;  // Get the neighbor's index

                if (!visited[nextStationIndex]) {
                    visited[nextStationIndex] = true;
                    q.push(nextStationIndex);  // Add the neighbor to the queue
                }
            }
        }

        return "No nearby station with a washroom found";  // If no station with a washroom is found

    }


int stationcheck(vector<metrostation>station, string search_Id)
  {
    for (int i = 0; i < station.size(); i++) {
        if (station[i].station_id == search_Id) {
            return 1;
        }
    }
    return -1;
  }


void displaystation(vector<metrostation>station)
      {
        system("color f4");
            gotoxy(26, 4);
            design(15, 175);
        cout << "====================================\n";
        cout << "         AVAILABLE STATIONS         \n";
        cout << "====================================\n";
        cout<<"S.No  S.id    S.name"<<endl;
        for(int i=0;i<station.size();i++)
        {
        cout<<i+1<<")    "<<station[i].station_id<<" :  "<<station[i].station_name<<endl;
        }
        cout << "------------------------------------\n\n";
      }

void stationinfo(vector<metrostation>station,string sid)
    {
        for(int i=0;i<station.size();i++)
        {
            if(sid==station[i].station_id)
            {
                cout << "====================================\n";
                cout << "      STATION INFORMATION\n";
                cout << "====================================\n";
                cout<<"Station no.: "<<i+1<<endl;
                cout<<"Station id: "<<station[i].station_id<<endl;
                cout<<"Station name: "<<station[i].station_name<<endl;
                cout<<station[i].linecolor<<" "<<"line"<<endl;
                if(station[i].hasWashroom==true)
                cout<<"Washrooms are present."<<endl;
                else
                cout<<"Washrooms are not present."<<endl;
                if(station[i].hasParking==true)
                cout<<"Parking is present."<<endl;
                else
                cout<<"Parking is not present."<<endl;
                // Display neighbors
                  cout << "Neighbors and distances:\n";
                  for (auto neighbor : station[i].getNeighbors())
                  {
                      cout << "Station No. : " << neighbor.first+1 << " Distance: " << neighbor.second << " km" << endl;
                  }
                cout << "------------------------------------\n\n";
                //found=true;
                gotoxy(84,30);
        cout<<"Press any key to go back to menu()........";
        getch();
        system("cls");
        userMenu(station);
        return;
            }
        }
    }
};


vector<metrostation>station;


string toUpperCase(string str) {
    for (int i = 0; i < str.length(); i++) {
        str[i] = toupper(str[i]);
    }
    return str;
}


pair<vector<string>, int> findShortestPath(const vector<metrostation>& stations, int startIndex, int endIndex) {
    int n = stations.size();
    vector<int> distance(n, numeric_limits<int>::max()); // Distance from start to each station
    vector<int> previous(n, -1); // Track previous station for path reconstruction
    vector<bool> visited(n, false); // Track visited stations
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // Min-heap

    // Start with the source station
    distance[startIndex] = 0;
    pq.push(make_pair(0, startIndex));

    while (!pq.empty()) {
        int current = pq.top().second;
        pq.pop();

        // If this station is already visited, skip it
        if (visited[current]) {
            continue;
        }
        visited[current] = true;

        // Explore neighbors
        for (auto& neighbor : stations[current].getNeighbors()) {
            int neighborIndex = neighbor.first;
            int weight = neighbor.second;

            // If a shorter path to the neighbor is found
            if (distance[current] + weight < distance[neighborIndex]) {
                distance[neighborIndex] = distance[current] + weight;
                previous[neighborIndex] = current; // Track the previous station
                pq.push(make_pair(distance[neighborIndex], neighborIndex));
            }
        }
    }

    // Reconstruct the path
    vector<string> path;
    if (distance[endIndex] == numeric_limits<int>::max()) {
        return make_pair(path, -1); // No path found
    }

    for (int at = endIndex; at != -1; at = previous[at]) {
        path.push_back(stations[at].getStation_name()); // Get the station name
    }
    reverse(path.begin(), path.end()); // Reverse to get the correct order

    return make_pair(path, distance[endIndex]); // Return path and distance
}


void initstations()
{
    station.push_back(metrostation("NEC","Noida Electronic City","Blue",false,true,0));
    station.push_back(metrostation("N62","Noida Sector 62","Blue",false,false,1));
    station.push_back(metrostation("N52","Noida Sector 52","Blue",true,false,2));
    station.push_back(metrostation("NCC","Noida City Center","Blue",true,true,3));
    station.push_back(metrostation("BG","Botanical Garden","Blue",true,true,4));
    station.push_back(metrostation("GC","Golf Course","Blue",false,false,5));
    station.push_back(metrostation("N18","Noida Sector 18","Blue",true,true,6));
    station.push_back(metrostation("AK","Akshardham","Blue",true,true,7));
    station.push_back(metrostation("YB","Yamuna Bank","Blue",false,true,8));
    station.push_back(metrostation("IP","Indraprastha","Blue",false,false,9));
    station.push_back(metrostation("MH","Mandi House","Blue , Violet",false,true,10));
    station.push_back(metrostation("BR","Barakhamba Road","Blue",false,false,11));
    station.push_back(metrostation("RC","Rajiv Chowk","Blue , Yellow",true,true,12));
    station.push_back(metrostation("KB","Karol Bagh","Blue , Violet",true,true,13));
    station.push_back(metrostation("PN","Patel Nagar","Blue",true,false,14));
    station.push_back(metrostation("ITO","ITO","Violet",false,true,15));
    station.push_back(metrostation("DG","Delhi Gate","Violet",false,false,16));
    station.push_back(metrostation("JAM","Jama Masjid","VIOLET",true,false,17));
    station.push_back(metrostation("LQ","LaL Quila","Violet",true,false,18));
    station.push_back(metrostation("KG","Kashmere Gate","Yellow , Violet",true,true,19));
    station.push_back(metrostation("CL","Civil Line","Yellow",false,true,20));
    station.push_back(metrostation("GTB","GTB","Yellow",true,false,21));
    station.push_back(metrostation("NDL","New Delhi","Yellow",true,true,22));
    station.push_back(metrostation("CB","Chawri Bazar","Yellow",false,false,23));
    station.push_back(metrostation("CC","Chandni Chowk","Yellow",true,true,24));
}

class Card {
public:
    string Card_ID;
    double balance;

public:
    Card(string id, double initial_balance);
    void recharge_card(double amount);
    void display_card_info();
    void pay_fare(double fare);
    void update_card_in_file(); // Function to update card in the file
};

Card::Card(string id, double initial_balance) : Card_ID(id), balance(initial_balance) {}

// Function to update the card information in cards.txt
void Card::update_card_in_file() {
    vector<Card> cards;

    // Step 1: Load all cards from the file
    ifstream file("cards.txt");
    if (file.is_open()) {
        string id;
        double bal;
        while (file >> id >> bal) {
            cards.push_back(Card(id, bal));
        }
        file.close();
    } else {
        cout << "Error opening cards.txt for updating card information." << endl;
        return;
    }

    // Step 2: Find the card in the vector and update its balance
    for (int i = 0; i < cards.size(); ++i) {
        if (cards[i].Card_ID == Card_ID) {
            cards[i].balance = balance;  // Update balance
            break;
        }
    }

    // Step 3: Rewrite all cards to the file
    ofstream outFile("cards.txt");
    if (outFile.is_open()) {
        for (const auto &card : cards) {
            outFile << card.Card_ID << " " << card.balance << endl;
        }
        outFile.close();
    } else {
        cout << "Error opening cards.txt for writing updated card information." << endl;
    }
}
void Card::recharge_card(double amount) {
    system("cls"); // Clear the screen
    balance += amount;
    // Create a border for styling
    for (int i = 10; i < 110; i++) {
        gotoxy(i, 9);
        cout << "=";
        gotoxy(i, 19);
        cout << "=";
    }
    for (int i = 10; i < 19; i++) {
        gotoxy(10, i);
        cout << "|";
        gotoxy(109, i);
        cout << "|";
    }

    // Display header
    gotoxy(44, 11);
    cout << "* CARD RECHARGE SUCCESSFUL *";

    gotoxy(44, 13);
    cout << "Amount Added: " << amount;

    gotoxy(44, 14);
    cout << "New Balance: " << balance;

    gotoxy(44, 16);
    cout << "Card Updated Successfully!";
    update_card_in_file();

    gotoxy(44, 22);
    cout << "Press any key to go back to menu()........";
    getch();
    system("cls");
    userMenu(station);
}

void Card::pay_fare(double fare) {
    system("cls"); // Clear the screen

    // Draw a simple border
    for (int i = 10; i < 110; i++) {
        gotoxy(i, 10);
        cout << "=";
        gotoxy(i, 17);
        cout << "=";
    }

    for (int i = 11; i < 17; i++) {
        gotoxy(10, i);
        cout << "|";
        gotoxy(109, i);
        cout << "|";
    }

    // Display header
    gotoxy(44, 11);
    cout << "* FARE PAYMENT *";

    if (fare > balance) {
        // Insufficient balance message
        gotoxy(44, 13);
        cout << "Insufficient balance!";
        gotoxy(44, 14);
        cout << "Please recharge your card.";
    } else {
        // Fare deducted message
        gotoxy(44, 13);
        cout<<"initial balance in card: "<<balance;
        balance -= fare;
        gotoxy(44, 14);
        cout << "Fare deducted: " << fare;
        gotoxy(44, 15);
        cout << "Remaining Balance: " << balance;

        // Update card details in the file
        update_card_in_file();
    }

    // Footer instructions
    gotoxy(44, 19);
    cout << "Press any key to go back to menu()........";

    // Await user input and return to the menu
    getch();
    system("cls");
    userMenu(station);
}


void Card::display_card_info() {
    system("cls"); // Clear the screen
    // Create a border
    for (int i = 10; i < 110; i++) {
        gotoxy(i, 10);
        cout << "=";
        gotoxy(i, 16);
        cout << "=";
    }
    for (int i = 11; i < 16; i++) {
        gotoxy(10, i);
        cout << "|";
        gotoxy(109, i);
        cout << "|";
    }


    gotoxy(44, 11);
    cout << "* CARD INFORMATION *";


    gotoxy(44, 13);
    cout << "Card ID: " << Card_ID;

    gotoxy(44, 14);
    cout << "Balance: " << balance;


    gotoxy(44, 15);
    cout << "--------------------------";

    gotoxy(40, 17);
    cout << "Press any key to go back to the main menu().....";


    getch();
    system("cls");
    userMenu(station);
}


int check(const string &search_Id) {
    ifstream file("cards.txt");
    string id;
    double balance;
    int index = -1;
    int count = 0;

    while (file >> id >> balance) {
        if (id == search_Id) {
            index = count;
            break;
        }
        count++;
    }

    file.close();
    return index;
}

Card get_card_by_index(int index) {
    ifstream file("cards.txt");
    string id;
    double balance;
    int count = 0;
    while (file >> id >> balance) {
        if (count == index) {
            return Card(id, balance);
        }
        count++;
    }
    file.close();
    return Card("", 0.0); // Return an empty card if not found
}

// Function to handle staff login
int staffLogin() {
    string username, enteredUsername, password, enteredPassword;
    bool isLoggedIn = false;

    system("cls");
    system("color f4");

    gotoxy(0, 2);
    design(130, 170);
    gotoxy(55, 4);
    cout << "WELCOME TO STAFF LOGIN";
    gotoxy(0, 6);
    design(130, 170);
    Sleep(1000);

    gotoxy(44, 9);
    cout << "Enter your USERNAME: ";
    cin >> enteredUsername;

    gotoxy(44, 11);
    cout << "Enter your PASSWORD: ";
    enteredPassword = getHiddenPassword();

    // Open file to read staff credentials
    ifstream file("staff_logins.txt");
    if (!file.is_open()) {
        gotoxy(44, 13);
        cout << "Error opening 'staff_logins.txt'. Make sure the file exists.";
        return -1;
    }

    // Check if credentials match
    while (file >> username >> password) {
        if (username == enteredUsername && password == enteredPassword) {
            gotoxy(67, 15);
            cout << "Logging you in, please wait";
            for (int i = 0; i < 6; i++) {
                cout << ".";
                Sleep(500);
            }

            system("CLS");
            staffMenu(station); // assuming station is globally accessible
            isLoggedIn = true;
            break;
        }
    }

    file.close();

    if (!isLoggedIn) {
        cout << "\n\t\t\tIncorrect username or password!\n";
        system("pause");
        staffLogin(); // Retry login
    }

    return isLoggedIn;
}


// Function to handle staff signup
void staffSignup() {
  string newUsername, newPassword, confirmPassword;
  bool usernameExists;
  system("color f4");
  gotoxy(0, 2);
  design(130, 170);
  gotoxy(55, 4);
  cout << "WELCOME TO STAFF SIGNUP" << endl;
  gotoxy(0, 6);
  design(130, 170);

  do {
      usernameExists = false;
      gotoxy(44, 9);
      cout << "Enter a USERNAME: ";
      cin >> newUsername;

      // Check if the username already exists
      ifstream fileIn("staff_logins.txt");
      if (fileIn.is_open()) {
          string username, password;
          while (fileIn >> username >> password) {
              if (username == newUsername) {
                  usernameExists = true;
                  cout << "\n\t\t\tSorry, this USERNAME already exists!" << endl;
                  break;
              }
          }
          fileIn.close(); // Close the input file
      }

  } while (usernameExists); // Keep asking for a unique username

  // Ask for password and confirmation
  gotoxy(44, 11);
  cout << "Enter your PASSWORD: ";
  newPassword = getHiddenPassword();
  gotoxy(44, 12);
  cout << "Re-enter your PASSWORD: ";
  confirmPassword = getHiddenPassword();

  while (newPassword != confirmPassword) {
      cout << "\n\t\t\tPasswords do not match! Please try again.\n";
      cout << "Enter your PASSWORD: ";
      newPassword = getHiddenPassword();
      cout << "Re-enter your PASSWORD: ";
      confirmPassword = getHiddenPassword();
  }

  // Save the new staff credentials to the file
  ofstream fileOut("staff_logins.txt", ios::app); // Appending new data
  if (!fileOut.is_open()) {
      cout << "\nError opening file for writing!\n";
      return;
  }
  fileOut << newUsername << " " << newPassword << endl; // Writing to the file
  fileOut.close();

  // Simulate account creation with a delay
  cout << "\n\t\t\tCreating your new account";
  for (int i = 0; i < 6; i++) {
      cout << ".";
      Sleep(500);
  }
  cout << "\n\n\t\t\tCongratulations! Your account has been created successfully!\n";
  Sleep(1000);
  system("CLS");
}

int userLogin() {
    string username, enteredUsername, password, enteredPassword;
    bool isLoggedIn = false;
    system("cls");
    system("color f4");
    gotoxy(0, 2);
    design(130, 170);
    gotoxy(55, 4);
    cout << "WELCOME TO LOGIN" << endl;
    gotoxy(0, 6);
    design(130, 170);
    Sleep(1000);
    gotoxy(44, 9);
    cout << "Enter your USERNAME: ";
    cin >> enteredUsername;
    gotoxy(44, 11);
    cout << "Enter your PASSWORD: ";
    enteredPassword = getHiddenPassword();

    // Open file to read user credentials
    ifstream file("user_logins.txt");
    if (!file.is_open()) {
        cout << "\nError opening file! Make sure 'user_logins.txt' exists.\n";
        return -1;
    }

    // Check if the entered username and password exist in the file
    while (file >> username >> password) {
        if (username == enteredUsername && password == enteredPassword) {
           // cout << "\n\t\t\tYou have successfully logged in!\n";
           gotoxy(67, 15);
           cout << "Logging you in, please wait";
            for (int i = 0; i < 6; i++) {
            cout << ".";
            Sleep(500);
        }

            system("CLS");
            userMenu(station);
            isLoggedIn = true;

            break;
        }
    }
    file.close();

    if (!isLoggedIn) {
        cout << "\n\t\t\tIncorrect username or password!\n";

        system("pause");
        userLogin();
    }

    return isLoggedIn;
}

// Function to handle user signup
void userSignup() {
    system("cls");
    string newUsername, newPassword, confirmPassword;
    bool usernameExists;
    system("color f4");
    gotoxy(0, 2);
    design(130, 170);
    gotoxy(55, 4);
    cout << "WELCOME TO SIGNUP" << endl;
     gotoxy(0, 6);
    design(130, 170);


    do {
        usernameExists = false;
        gotoxy(44, 9);
        cout << "Enter a USERNAME: ";
        cin >> newUsername;

        // Clear any previous message
        gotoxy(44, 10);
        cout << "                                          ";

        // Check for existing usernames
        ifstream fileIn("user_logins.txt");
        if (fileIn.is_open()) {
            string username, password;
            while (fileIn >> username >> password) {
                if (username == newUsername) {
                    usernameExists = true;
                    gotoxy(44, 10);
                    cout << "Username already exists! Try again.";
                    Sleep(1500);
                    gotoxy(44, 9);
                    cout << "                                          "; // clear line
                    break;
                }
            }
            fileIn.close();
        }
    } while (usernameExists);



    // Ask for password and confirmation
    gotoxy(44, 11);
    cout << "Enter your PASSWORD: ";
    newPassword = getHiddenPassword();
    gotoxy(44, 12);
    cout << "Re-enter your PASSWORD: ";
    confirmPassword = getHiddenPassword();

    while (newPassword != confirmPassword) {
        cout << "\n\t\t\tPasswords do not match! Please try again.\n";
        cout << "Enter your PASSWORD: ";
        cin >> newPassword;
        cout << "Re-enter your PASSWORD: ";
        cin >> confirmPassword;
    }

    // Save the new user credentials to the file
    ofstream fileOut("user_logins.txt", ios::app); // Appending new data
    if (!fileOut.is_open()) {
        cout << "\nError opening file for writing!\n";
        return;
    }
    fileOut << newUsername << " " << newPassword << endl; // Writing to the file
    fileOut.close();

    // Simulate account creation with a delay
    cout << "\n\t\t\tCreating your new account";
    for (int i = 0; i < 6; i++) {
        cout << ".";
        Sleep(500);
    }
    cout << "\n\n\t\t\tCongratulations! Your account has been created successfully!\n";
    Sleep(1000);
    system("CLS");
}


class Stack {
private:
    vector<string> stackData; // Vector to store stack data
public:
    void push(string stationId) {
        stackData.push_back(stationId);
    }

    void pop() {
        if (!isEmpty()) {
            stackData.pop_back();
        }
    }

    string peek() {
        if (!isEmpty()) {
            return stackData.back();
        }
        return "";
    }

    bool isEmpty() {
        return stackData.empty();
    }

    void clear() {
        stackData.clear();
    }
};
void metromap()
{   system("cls");
    system("color 8f");
    gotoxy(44,1);
    cout << "====================================";
    gotoxy(44,2);
    cout << "         METRO STATION MAP\n";
    gotoxy(44,3);
    cout << "====================================";
    cout<<endl;

    cout << "   Noida Electronic\n";
    cout << "           City <-> Noida Sec-62 <-> Noida Sec-52 <-> Noida city center <-> Botanical\n";
    cout << "                                                                             ^\n";
    cout << "                                                                             |\n";
    cout << "                                                                             v\n";
    cout << "        Indraprastha <-> Yamuna Bank <-> Akshardham <-> Noida Sec 18 <-> Golf Course\n";
    cout << "           ^\n";
    cout << "           |\n";
    cout << "           v\n";
    cout << "        Mandi House <-> Barakhamba <-> Rajiv Chowk <-> Karol Bagh <-> Patel Nagar.\n";
    cout << "              ^                             ^\n";
    cout << "              |                             |\n";
    cout << "              v                             v\n";
    cout << "             ITO                       New Delhi\n";
    cout << "              ^                             ^\n";
    cout << "              |                             |\n";
    cout << "              v                             v\n";
    cout << "          Delhi Gate                Chawri Bazaar\n";
    cout << "             ^                         ^\n";
    cout << "             |                        /\n";
    cout << "             v                       v\n";
    cout << "         Jama Masjid        Chandni Chowk\n";
    cout << "             ^                  ^\n";
    cout << "             |                 /\n";
    cout << "             v                v\n";
    cout << "         Lal Quila <-> Kashmere Gate <-> Civil Lines <-> GTB Nagar\n";
    cout<<endl<<endl;
    gotoxy(60,40);
    cout<<"Press any key to go back to menu()........";
    getch();
    system("cls");
    userMenu(station);

}
// Function to perform DFS and find all paths
void findAllPathsDFS(int current, int destination, vector<metrostation> &stations, vector<int> &visited, vector<int> &path, vector<vector<int>> &allPaths)
{
    // Mark the current station as visited
    visited[current] = 1;
    path.push_back(current);

    if (current == destination)
    {
        // If destination is reached, save the path
        allPaths.push_back(path);
    }
    else
    {
        // Explore the neighbors
        for (auto neighbor : stations[current].getNeighbors())
        {
            int nextStation = neighbor.first;
            if (!visited[nextStation])
            {
                findAllPathsDFS(nextStation, destination, stations, visited, path, allPaths);
            }
        }
    }

    // Backtrack: Unmark the current station and remove it from the current path
    visited[current] = 0;
    path.pop_back();
}

// Wrapper function to find all paths between two stations
vector<vector<int>> findAllPaths(int source, int destination, vector<metrostation> &stations)
{
    vector<vector<int>> allPaths;
    vector<int> path;
    vector<int> visited(stations.size(), 0); // To keep track of visited stations during DFS

    findAllPathsDFS(source, destination, stations, visited, path, allPaths);

    return allPaths;
}

void preparelist(vector<metrostation> &stations)
{
    // Add neighbors for each station by their index in the vector (assuming the index represents the station ID)
    stations[0].addNeighbor(1, 4);

    stations[1].addNeighbor(0, 4);
    stations[1].addNeighbor(2, 6);

    stations[2].addNeighbor(1, 6);
    stations[2].addNeighbor(3, 1);

    stations[3].addNeighbor(2, 1);
    stations[3].addNeighbor(4, 2);

    stations[4].addNeighbor(3, 2);
    stations[4].addNeighbor(5, 8);

    stations[5].addNeighbor(4, 8);
    stations[5].addNeighbor(6, 5);

    stations[6].addNeighbor(5, 5);
    stations[6].addNeighbor(7, 8);

    stations[7].addNeighbor(6, 8);
    stations[7].addNeighbor(8, 6);

    stations[8].addNeighbor(7, 6);
    stations[8].addNeighbor(9, 3);

    stations[9].addNeighbor(8 , 3);
    stations[9].addNeighbor(10, 6);

    stations[10].addNeighbor(9 , 6);
    stations[10].addNeighbor(11, 6);
    stations[10].addNeighbor(15, 7);

    stations[11].addNeighbor(10, 6);
    stations[11].addNeighbor(12, 7);

    stations[12].addNeighbor(11, 7);
    stations[12].addNeighbor(22, 8);
    stations[12].addNeighbor(13, 4);

    stations[13].addNeighbor(12, 4);
    stations[13].addNeighbor(14, 6);

    stations[14].addNeighbor(13, 6);

    stations[15].addNeighbor(10, 7);
    stations[15].addNeighbor(16, 7);

    stations[16].addNeighbor(15, 7);
    stations[16].addNeighbor(17, 8);

    stations[17].addNeighbor(16, 8);
    stations[17].addNeighbor(18, 3);

    stations[18].addNeighbor(17, 3);
    stations[18].addNeighbor(19, 8);

    stations[19].addNeighbor(18, 8);
    stations[19].addNeighbor(24, 4);
    stations[19].addNeighbor(20, 6);

    stations[20].addNeighbor(19, 6);
    stations[20].addNeighbor(21, 7);

    stations[21].addNeighbor(20, 7);

    stations[22].addNeighbor(12, 8);
    stations[22].addNeighbor(23, 5);

    stations[23].addNeighbor(22, 5);
    stations[23].addNeighbor(24, 8);

    stations[24].addNeighbor(23, 8);
    stations[24].addNeighbor(19, 4);

}

vector<metrostation> stations;
vector<vector<pair<int, int>>> eulerAdj(N);
int dist[N][N];
int nextNode[N][N];
vector<int> eulerianPath;

void addEdge(int u, int v, int w) {
    stations[u].addNeighbor(v, w);
    stations[v].addNeighbor(u, w);
    eulerAdj[u].emplace_back(v, w);
    eulerAdj[v].emplace_back(u, w);
}

void floydWarshall() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            dist[i][j] = (i == j) ? 0 : INF;
            nextNode[i][j] = -1;
        }

    for (int u = 0; u < N; ++u)
        for (auto& e : stations[u].getNeighbors()) {
            int v = e.first;
            int w = e.second;
            dist[u][v] = w;
            nextNode[u][v] = v;
        }

    for (int k = 0; k < N; ++k)
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    nextNode[i][j] = nextNode[i][k];
                }
}

vector<int> getPath(int u, int v) {
    if (nextNode[u][v] == -1) return {};
    vector<int> path = {u};
    while (u != v) {
        u = nextNode[u][v];
        path.push_back(u);
    }
    return path;
}

vector<int> findOddDegreeVertices() {
    vector<int> odd;
    for (int i = 0; i < N; ++i)
        if (stations[i].getDegree() % 2 != 0)
            odd.push_back(i);
    return odd;
}

int minCostMatching(vector<int>& odd, int mask, unordered_map<int, int>& memo) {
    if (mask == 0) return 0;
    if (memo.count(mask)) return memo[mask];

    int first = -1;
    for (int i = 0; i < odd.size(); ++i) {
        if (mask & (1 << i)) {
            first = i;
            break;
        }
    }

    int minCost = INF;
    for (int j = first + 1; j < odd.size(); ++j) {
        if (mask & (1 << j)) {
            int newMask = mask ^ (1 << first) ^ (1 << j);
            int cost = dist[odd[first]][odd[j]] + minCostMatching(odd, newMask, memo);
            minCost = min(minCost, cost);
        }
    }

    return memo[mask] = minCost;
}

int totalOriginalCost() {
    int total = 0;
    vector<vector<bool>> visited(N, vector<bool>(N, false));
    for (int u = 0; u < N; ++u) {
        for (auto& e : stations[u].getNeighbors()) {
            int v = e.first;
            if (!visited[u][v]) {
                total += e.second;
                visited[u][v] = visited[v][u] = true;
            }
        }
    }
    return total;
}

void dfsEuler(int u) {
    while (!eulerAdj[u].empty()) {
        auto edge = eulerAdj[u].back();
        eulerAdj[u].pop_back();
        int v = edge.first;

        auto& nbr = eulerAdj[v];
        for (auto it = nbr.begin(); it != nbr.end(); ++it) {
            if (it->first == u) {
                nbr.erase(it);
                break;
            }
        }

        dfsEuler(v);
    }
    eulerianPath.push_back(u);
}

void prepareStations() {
    stations.clear();  // ← This is crucial to avoid adding duplicate stations and edges!

    vector<string> names = {
        "Noida Electronic City", "Noida Sector 62", "Noida Sector 52", "Noida City Center",
        "Botanical Garden", "Golf Course", "Noida Sector 18", "Akshardham", "Yamuna Bank",
        "Indraprastha", "Mandi House", "Barakhamba Road", "Rajiv Chowk", "Karol Bagh",
        "Patel Nagar", "ITO", "Delhi Gate", "Jama Masjid", "Lal Quila", "Kashmere Gate",
        "Civil Lines", "GTB Nagar", "New Delhi", "Chawri Bazar", "Chandni Chowk"
    };

    for (int i = 0; i < names.size(); ++i) {
        string id = "S" + to_string(i);
        stations.emplace_back(id, names[i], "Blue", true, (i % 2 == 0), i);
    }

    // Now you can safely call addEdge, because stations are clean.
    addEdge(0, 1, 4); addEdge(1, 2, 6); addEdge(2, 3, 1); addEdge(3, 4, 2);
    addEdge(4, 5, 8); addEdge(5, 6, 5); addEdge(6, 7, 8); addEdge(7, 8, 6);
    addEdge(8, 9, 3); addEdge(9, 10, 6); addEdge(10, 11, 6); addEdge(10, 15, 7);
    addEdge(11, 12, 7); addEdge(12, 13, 4); addEdge(12, 22, 8); addEdge(13, 14, 6);
    addEdge(15, 16, 7); addEdge(16, 17, 8); addEdge(17, 18, 3); addEdge(18, 19, 8);
    addEdge(19, 24, 4); addEdge(19, 20, 6); addEdge(20, 21, 7); addEdge(22, 23, 5); addEdge(23, 24, 8);
}


void patrol_route() {
    // Reset global or static structures
    system("cls");
    eulerianPath.clear();
    eulerAdj.assign(N, vector<pair<int, int>>());  // or your graph size
    unordered_map<int, int> memo;

    prepareStations();
    floydWarshall();

    int originalCost = totalOriginalCost();
    vector<int> odd = findOddDegreeVertices();
    int mask = (1 << odd.size()) - 1;
    int extraCost = minCostMatching(odd, mask, memo);
    int totalCPPcost = originalCost + extraCost;

    // Add duplicate edges to make graph Eulerian
    mask = (1 << odd.size()) - 1;
    while (mask) {
        int i = 0;
        while (!(mask & (1 << i))) ++i;
        int u = odd[i];
        for (int j = i + 1; j < odd.size(); ++j) {
            if (!(mask & (1 << j))) continue;
            int v = odd[j];
            int newMask = mask ^ (1 << i) ^ (1 << j);
            int pairCost = dist[u][v];
            if (extraCost == pairCost + minCostMatching(odd, newMask, memo)) {
                vector<int> path = getPath(u, v);
                for (int k = 0; k + 1 < path.size(); ++k) {
                    eulerAdj[path[k]].emplace_back(path[k + 1], 0);
                    eulerAdj[path[k + 1]].emplace_back(path[k], 0);
                }
                mask = newMask;
                extraCost -= pairCost;
                break;
            }
        }
    }

    dfsEuler(0);
    reverse(eulerianPath.begin(), eulerianPath.end());

    cout << "\n========== METRO PATROL ROUTE SOLUTION ==========\n";
    cout << "\nTotal cost of existing metro routes: " << originalCost;
    cout << "\nAdditional distance to ensure all routes are covered in a circuit: " << memo[(1 << odd.size()) - 1];
    cout << "\n-------------------------------------------------";
    cout << "\nTotal distance of optimized patrol route: " << totalCPPcost;

    cout << "\n\nOptimized Patrol Route (covers all tracks at least once):\n";
    for (int i = 0; i < eulerianPath.size(); ++i) {
        cout << stations[eulerianPath[i]].getStation_name();
        if (i != eulerianPath.size() - 1) cout << " -> ";
    }

    cout << "\n\nTotal stations visited (with revisits): " << eulerianPath.size();
    cout << "\n=================================================\n";

}

void clean_metro_tracks() {
    // Reset global or static structures
    system("cls");
    eulerianPath.clear();
    eulerAdj.assign(N, vector<pair<int, int>>());  // or your graph size
    unordered_map<int, int> memo;

    prepareStations();
    floydWarshall();

    int originalCost = totalOriginalCost();
    vector<int> odd = findOddDegreeVertices();
    int mask = (1 << odd.size()) - 1;
    int extraCost = minCostMatching(odd, mask, memo);
    int totalCPPcost = originalCost + extraCost;

    // Add duplicate edges to make graph Eulerian
    mask = (1 << odd.size()) - 1;
    while (mask) {
        int i = 0;
        while (!(mask & (1 << i))) ++i;
        int u = odd[i];
        for (int j = i + 1; j < odd.size(); ++j) {
            if (!(mask & (1 << j))) continue;
            int v = odd[j];
            int newMask = mask ^ (1 << i) ^ (1 << j);
            int pairCost = dist[u][v];
            if (extraCost == pairCost + minCostMatching(odd, newMask, memo)) {
                vector<int> path = getPath(u, v);
                for (int k = 0; k + 1 < path.size(); ++k) {
                    eulerAdj[path[k]].emplace_back(path[k + 1], 0);
                    eulerAdj[path[k + 1]].emplace_back(path[k], 0);
                }
                mask = newMask;
                extraCost -= pairCost;
                break;
            }
        }
    }

    dfsEuler(0);
    reverse(eulerianPath.begin(), eulerianPath.end());

    cout << "\n========== CLEAN METRO TRACKS ROUTE SOLUTION ==========\n";
    cout << "\nTotal cost of existing metro tracks: " << originalCost;
    cout << "\nAdditional distance to ensure all tracks are cleaned in a circuit: " << memo[(1 << odd.size()) - 1];
    cout << "\n--------------------------------------------------------";
    cout << "\nTotal distance of optimized cleaning route: " << totalCPPcost;

    cout << "\n\nOptimized Cleaning Route (covers all tracks at least once):\n";
    for (int i = 0; i < eulerianPath.size(); ++i) {
        cout << stations[eulerianPath[i]].getStation_name();
        if (i != eulerianPath.size() - 1) cout << " -> ";
    }

    cout << "\n\nTotal stations visited (with revisits): " << eulerianPath.size();
    cout << "\n========================================================\n";


}


void mainMenu(vector<metrostation> station) {
  int userType;
  while (true) {
      system("cls");
      gotoxy(50, 10);
      cout << "[1]. User";
      gotoxy(50, 11);
      cout << "[2]. Staff";
      gotoxy(50, 12);
      cout << "[3]. Exit";
      gotoxy(50, 14);
      cout << "Enter your choice: ";
      cin >> userType;
        system("cls");
      switch (userType) {
          case 1: // User
              int userChoice;

              gotoxy(50, 15);  // Horizontal alignment at 40 and vertical spacing at 20
        cout << "1. Login";
        gotoxy(50, 17);
        cout << "2. Signup";
        gotoxy(50, 19);
        cout << "Enter your choice: ";
        cin >> userChoice;
              if (userChoice == 1) {
                  userLogin(); // Call user login function
              } else if (userChoice == 2) {
                  system("cls");
                  userSignup(); // Call user signup function
              } else {

                  cout << "Invalid choice! Please try again.\n";
              Sleep(1000);


              }
              break;
          case 2: // Staff
              int staffChoice;
              gotoxy(50, 15);
              cout << "1. Login";
        gotoxy(50, 17);
        cout << "2. Signup";
        gotoxy(50, 19);
        cout << "Enter your choice: ";
              cin >> staffChoice;
              if (staffChoice == 1) {

                  staffLogin(); // Call staff login function
              } else if (staffChoice == 2) {
                  system("cls");
                  staffSignup(); // Call staff signup function
              } else {
                  cout << "Invalid choice! Please try again.\n";
              Sleep(1000);
              }
              break;
          case 3:
              cout << "\nExiting the program. Goodbye!\n";
              exit(0);
          default:
              cout << "Invalid choice! Please try again.\n";
              Sleep(1000);
              mainMenu(station);

      }
  }
}
//--------------------------------------------------------------------------------------

void userMenu(vector<metrostation> station) {
    static Stack stationStack;
    static string currentStation = "";
    metrostation var;
    vector<Card> cards = {
        Card("card1", 10.0), Card("card2", 20.0),
        Card("card3", 30.0), Card("card4", 40.0)
    };
    int ch;
    string str, startID, searchId, result;
    double amount, fare;
    int index, sindex;

    while (true) {
        system("cls");
        gotoxy(44, 10);
        cout << "[1]. Show Metro Map";
        gotoxy(44, 11);
        cout << "[2]. Show station details";
        gotoxy(44, 12);
        cout << "[3]. Display Card Info";
        gotoxy(44, 13);
        cout << "[4]. Recharge Card";
        gotoxy(44, 14);
        cout << "[5]. Pay Fare";
        gotoxy(44, 15);
        cout << "[6]. Go back to previous station";
        gotoxy(44, 16);
        cout << "[7]. Nearest station with Washroom";
        gotoxy(44, 17);
        cout << "[8]. Nearest station with Parking";
        gotoxy(44, 18);
        cout << "[9]. All paths between two stations";
        gotoxy(44, 19);
        cout << "[10]. Shortest path between two stations";
        gotoxy(44, 20);
        cout << "[11]. Go to main menu";
        gotoxy(44, 22);
        cout << "Enter your choice: ";
        cin >> ch;

        switch (ch) {
            case 1:
                metromap(); break;
            case 2:
                system("cls");
                var.displaystation(station);
                do {
                    cout << "Enter station id: ";
                    cin >> str;
                    str = toUpperCase(str);
                    sindex = var.stationcheck(station, str);
                    if (sindex == -1) cout << "Invalid Station ID!\n";
                } while (sindex == -1);
                currentStation = str;
                if (!currentStation.empty()) stationStack.push(currentStation);
                var.stationinfo(station, currentStation);
                break;
            case 3:
                system("cls");
                do {
                    gotoxy(44, 10);
                    cout << "Enter your card ID: ";
                    cin >> searchId;
                    index = check(searchId);
                    if (index == -1) {
                        cout << "Card not found!\n";
                        Sleep(1000); system("cls");
                    }
                } while (index == -1);
                get_card_by_index(index).display_card_info();
                break;
            case 4:
                system("cls");
                do {
                    gotoxy(44, 10);
                    cout << "Enter your card ID: ";
                    cin >> searchId;
                    index = check(searchId);
                    if (index == -1) {
                        cout << "Card not found!\n";
                        Sleep(1000); system("cls");
                    }
                } while (index == -1);
                gotoxy(44, 10);
                cout << "Enter amount to recharge: ";
                cin >> amount;
                get_card_by_index(index).recharge_card(amount);
                break;
            case 5:
                system("cls");
                do {
                    gotoxy(44, 10);
                    cout << "Enter your card ID: ";
                    cin >> searchId;
                    index = check(searchId);
                    if (index == -1) {
                        cout << "Card not found!\n";
                        Sleep(1000); system("cls");
                    }
                } while (index == -1);
                gotoxy(44, 12);
                cout << "Enter fare: ";
                cin >> fare;
                get_card_by_index(index).pay_fare(fare);
                break;
            case 6:
                system("cls");
                if (!stationStack.isEmpty()) {
                    currentStation = stationStack.peek();
                    stationStack.pop();
                    cout << "Returning to: " << currentStation << "\n";
                    var.stationinfo(station, currentStation);
                } else {
                    cout << "No previous station.\n";
                }
                break;
            case 7:
            system("cls");
            gotoxy(5,2);
            design(120,177);
            gotoxy(55,4);
            cout<<"Nearest Metro station with washroom"<<endl;
            gotoxy(5,6);
            design(120,177);
            gotoxy(45,13);
            cout << "Enter Station ID to find the nearest station with a washroom: ";
            cin >> startID;  // Get user input
            startID=toUpperCase(startID);
           result = station[0].findNearestStationWithWashroom(startID, station);  // Find the nearest station with a washroom
        gotoxy(45,15);
            cout << "Nearest station with washroom from " << startID << ": " << result << endl;
            gotoxy(55,30);
                cout<<"Press any key to go back to menu()........";
                getch();
                system("cls");
                userMenu(station);;
            break;
    case 8:
    system("cls");
    gotoxy(5,2);
    design(120,177);
    gotoxy(55,4);
    cout<<"Nearest Metro station with Parking"<<endl;
    gotoxy(5,6);
    design(120,177);
    gotoxy(45,13);
    cout << "Enter Station ID to find the nearest station with a parking: ";
    cin >> startID;  // Get user input
    startID=toUpperCase(startID);
    result = station[0].findNearestStationWithParking(startID, station);  // Find the nearest station with a washroom
    gotoxy(45,15);
    cout << "Nearest station with parking from " << startID << ": " << result << endl;
    gotoxy(55,30);
    cout<<"Press any key to go back to menu()........";
    getch();
    system("cls");
    userMenu(station);
            break;
            case 9: {
                int source, destination;
                system("cls");
                var.displaystation(station);
                do {
                    cout << "Enter source station number: ";
                    cin >> source;
                    source--;
                    cout << "Enter destination station number: ";
                     cin >> destination;
                     destination--;
                     if(source < 0 || source > 24) cout<<"Please enter source according to the display ."<<endl;
        if(destination < 0 || destination > 24)  cout<<"Please enter destination according to the display ."<<endl;
                } while (source < 0 || destination < 0 || source > 24 || destination > 24);
                vector<vector<int>> paths = findAllPaths(source, destination, station);
                int pno = 1;
                for (auto path : paths) {
                    cout << "Path " << pno++ << ": ";
                    for (int idx : path) {
                        cout << station[idx].getStation_name();
                        if (idx != destination) cout << " -> ";
                    }
                    cout << "\n";
                }
                break;
            }
            case 10: {
                int source, destination;
                system("cls");
                var.displaystation(station);
                do {
                    cout << "Enter source station number: "; cin >> source; source--;
                    cout << "Enter destination station number: "; cin >> destination; destination--;
                } while (source < 0 || destination < 0 || source > 24 || destination > 24);
                auto result = findShortestPath(station, source, destination);
                vector<string> path = result.first;
                int distance = result.second;
                cout << "Shortest Distance: " << distance << " km\n";
                for (int i = 0; i < path.size(); ++i) {
                    cout << path[i];
                    if (i != path.size() - 1) cout << " -> ";
                }
                cout << "\n";
                break;
            }
            case 11:
                mainMenu(station);
                break;
            default:
                cout << "Invalid choice!\n";
        }
        cout << "\nPress any key to continue...\n";
        getch();
    }
}
//-------------------------------------------------------------------------------------------------

void staffMenu(vector<metrostation> station) {
    int choice;
    while (true) {
        system("cls");
        gotoxy(50, 10);
        cout << "[1]. Patrol Route";
        gotoxy(50, 11);
        cout << "[2]. Route Cleaning";
        gotoxy(50, 12);
        cout << "[3]. Return to Main Menu";
        gotoxy(50, 14);
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                patrol_route();
                break;
            case 2:
                clean_metro_tracks();
                break;
            case 3:
                return;
            default:
                cout << "Invalid option!\n";
        }
        cout << "\nPress any key to continue...\n";
        getch();
    }
}

int main()
{
    initstations();
    preparelist(station);
    metrostation var;
    gotoxy(1,2);
    design(130,177);
    gotoxy(65, 3);
    cout << "METRO SYSTEM NOIDA";
gotoxy(1,4);
    design(130,177);




gotoxy(10, 7);
cout << "\t\tWelcome to the future of urban commuting!\n Discover a smarter, eco-friendly, and faster way to experience the dynamic city of Noida. Our advanced metro simulation captures the heartbeat of the city—connecting people, destinations, and opportunities effortlessly. Whether you're a daily rider or an explorer at heart, Noida Metro promises a journey that's safe, efficient, and truly memorable.";

gotoxy(10, 14);
cout << "Brought to you with  love, logic, and a lot of caffeine by:";

gotoxy(10, 15);
cout << " Shubhra    Akshat    Janvi    Jitendra";

gotoxy(10, 19);
cout << "============================================================";
gotoxy(10, 20);
cout << "        Press any key to begin your metro adventure...";

getch(); // Wait for a key press
mainMenu(station);
return 0;

}
