#include <bits/stdc++.h>
#include <ctime>
using namespace std;

// === Colors ===
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"

struct Vehicle {
    string plateNumber;
    string carName;
    string type;     // Car, Bike, Truck, Bus
    bool incoming;   // true = incoming, false = outgoing
    string timestamp; // time logged
};

struct City {
    string name;
    vector<Vehicle> vehicles;
};

vector<City> cities;
vector<string> blacklist = {"PB10AB9999", "CH01XYZ1234"}; // example blacklisted plates

// === Helper ===
void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

City* findCity(const string& name) {
    for (auto& c : cities) {
        if (c.name == name) return &c;
    }
    return nullptr;
}

string getTimestamp() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char buf[20];
    sprintf(buf, "%02d:%02d:%02d", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
    return string(buf);
}

int getHourFromTimestamp(const string& ts) {
    return stoi(ts.substr(0, 2)); // extract hour (first 2 chars)
}

// === Record Vehicle ===
void recordVehicle() {
    string cityName;
    cout << "Enter city name: ";
    cin >> ws;
    getline(cin, cityName);

    City* city = findCity(cityName);
    if (!city) {
        cities.push_back({cityName, {}});
        city = &cities.back();
    }

    Vehicle v;
    cout << "Enter plate number: ";
    cin >> v.plateNumber;
    cout << "Enter car name: ";
    cin >> ws;
    getline(cin, v.carName);

    cout << "Select vehicle type (1-Car, 2-Bike, 3-Truck, 4-Bus): ";
    int typeChoice;
    cin >> typeChoice;
    switch (typeChoice) {
        case 1: v.type = "Car"; break;
        case 2: v.type = "Bike"; break;
        case 3: v.type = "Truck"; break;
        case 4: v.type = "Bus"; break;
        default: v.type = "Unknown";
    }

    cout << "Incoming (1) or Outgoing (0): ";
    cin >> v.incoming;

    v.timestamp = getTimestamp();
    city->vehicles.push_back(v);

    cout << "Vehicle added to " << cityName << " ✅ at " << v.timestamp << "\n";

    // Check blacklist
    if (find(blacklist.begin(), blacklist.end(), v.plateNumber) != blacklist.end()) {
        cout << RED << "⚠ ALERT: Blacklisted vehicle detected! (" 
             << v.plateNumber << " in " << cityName << ")" << RESET << "\n";
    }
}

// === Analytics ===
struct CityStats {
    string name;
    int entries;
    int totalIncoming;
    int totalOutgoing;
};

vector<CityStats> collectStats() {
    vector<CityStats> statsList;
    for (auto& city : cities) {
        int in = 0, out = 0;
        for (auto& v : city.vehicles) {
            if (v.incoming) in++;
            else out++;
        }
        statsList.push_back({city.name, (int)city.vehicles.size(), in, out});
    }
    sort(statsList.begin(), statsList.end(), [](auto& a, auto& b) {
        return (a.totalIncoming + a.totalOutgoing) > (b.totalIncoming + b.totalOutgoing);
    });
    return statsList;
}

void showAnalytics() {
    if (cities.empty()) {
        cout << "No data recorded yet.\n";
        return;
    }

    auto statsList = collectStats();

    clearScreen();
    cout << "=== Analytics Summary (All Cities Leaderboard) ===\n\n";
    cout << left << setw(15) << "City"
         << setw(10) << "Entries"
         << setw(15) << "Incoming"
         << setw(15) << "Outgoing"
         << setw(10) << "In %"
         << setw(10) << "Out %"
         << "Vehicle Types\n";
    cout << string(100, '-') << endl;

    for (auto& city : cities) {
        int cars=0, bikes=0, trucks=0, buses=0;

        for (auto& v : city.vehicles) {
            if (v.type == "Car") cars++;
            else if (v.type == "Bike") bikes++;
            else if (v.type == "Truck") trucks++;
            else if (v.type == "Bus") buses++;
        }

        int total = (int)city.vehicles.size();
        int incoming=0, outgoing=0;
        for (auto& v : city.vehicles) {
            if (v.incoming) incoming++;
            else outgoing++;
        }

        double inPerc = (total > 0) ? (100.0 * incoming / total) : 0;
        double outPerc = (total > 0) ? (100.0 * outgoing / total) : 0;

        cout << left << setw(15) << city.name
             << setw(10) << total
             << setw(15) << incoming
             << setw(15) << outgoing
             << setw(9) << fixed << setprecision(1) << inPerc << "%"
             << setw(9) << fixed << setprecision(1) << outPerc << "%";

        cout << "Cars:" << cars << " Bikes:" << bikes
             << " Trucks:" << trucks << " Buses:" << buses << "\n";
    }

    // === Peak Hour Detection ===
    map<int,int> hourTraffic;
    for (auto& city : cities) {
        for (auto& v : city.vehicles) {
            int hr = getHourFromTimestamp(v.timestamp);
            hourTraffic[hr]++;
        }
    }

    int peakHour = -1, maxCount = 0;
    for (auto& h : hourTraffic) {
        if (h.second > maxCount) {
            peakHour = h.first;
            maxCount = h.second;
        }
    }

    if (peakHour != -1) {
        cout << "\nPeak Hour: " << peakHour << ":00 with "
             << maxCount << " vehicles recorded 🚗🚦\n";
    }

    // === Traffic Bar Chart ===
    cout << "\n=== Traffic Bar Chart (Incoming vs Outgoing + Total) ===\n";
    int maxTraffic = 0;
    for (auto& city : cities) {
        int total = (int)city.vehicles.size();
        maxTraffic = max(maxTraffic, total);
    }

    for (auto& city : cities) {
        int incoming=0, outgoing=0;
        for (auto& v : city.vehicles) {
            if (v.incoming) incoming++;
            else outgoing++;
        }

        int total = incoming + outgoing;
        int inBar = (maxTraffic > 0) ? (30 * incoming / maxTraffic) : 0;
        int outBar = (maxTraffic > 0) ? (30 * outgoing / maxTraffic) : 0;
        int totalBar = (maxTraffic > 0) ? (50 * total / maxTraffic) : 0;

        cout << left << setw(15) << city.name << " | "
             << GREEN << string(inBar, '#') << RESET << " (" << incoming << ") "
             << RED << string(outBar, '=') << RESET << " (" << outgoing << ")\n";

        cout << string(17, ' ') << "   "
             << YELLOW << string(totalBar, '*') << RESET
             << " (" << total << ")\n";
    }
}

// === Show logs for a city ===
void showCityLogs() {
    string cityName;
    cout << "Enter city name: ";
    cin >> ws;
    getline(cin, cityName);

    City* city = findCity(cityName);
    if (!city) {
        cout << "City not found!\n";
        return;
    }

    cout << "\n=== Vehicle Logs (" << city->name << ") ===\n";
    if (city->vehicles.empty()) {
        cout << "No vehicles recorded.\n";
        return;
    }

    for (auto& v : city->vehicles) {
        cout << v.timestamp << " | " << v.plateNumber << " | " << v.carName
             << " | " << v.type << " | " 
             << (v.incoming ? "Incoming" : "Outgoing") << "\n";
    }
}

// === Search by Plate Number ===
void searchVehicle() {
    string plate;
    cout << "Enter plate number to search: ";
    cin >> plate;

    bool found = false;
    for (auto& city : cities) {
        for (auto& v : city.vehicles) {
            if (v.plateNumber == plate) {
                cout << "Found in " << city.name << " → "
                     << v.carName << " (" << v.type << ") "
                     << (v.incoming ? "Incoming" : "Outgoing")
                     << " at " << v.timestamp << "\n";
                found = true;
            }
        }
    }
    if (!found) cout << "Vehicle not found in any city.\n";
}

// === Main Menu ===
int main() {
    int choice;
    while (true) {
        cout << "\n=== Smart Traffic Management ===\n";
        cout << "1. Record Vehicle\n";
        cout << "2. Show Analytics\n";
        cout << "3. Show City Vehicle Logs\n";
        cout << "4. Search Vehicle by Plate\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: recordVehicle(); break;
            case 2: showAnalytics(); break;
            case 3: showCityLogs(); break;
            case 4: searchVehicle(); break;
            case 5: return 0;
            default: cout << "Invalid choice!\n";
        }
    }
}

// Smart Traffic System by tanvib12  //