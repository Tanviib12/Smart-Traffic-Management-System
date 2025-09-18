# Smart-Traffic-Management-System
🚦 Smart Traffic Management System in C++ — log vehicles with plate, name, type, direction &amp; timestamp across multiple cities. Features blacklist detection, analytics dashboard, peak hour detection, and ASCII charts for real-time traffic insights.


Smart Traffic Management System 🚗🚦

A C++17 console-based application for recording and analyzing real-time traffic across multiple cities. This project demonstrates how smart city traffic monitoring can be simulated using data structures, timestamps, and visualization.


✨ Features

1. Dynamic City Support → Add and track any city without hardcoding.

• Vehicle Logging → Records:

• Plate Number

• Vehicle Name

• Vehicle Type (Car, Bike, Truck, Bus)

• Direction (Incoming / Outgoing)

• Timestamp (hh:mm:ss)

2. Blacklist Detection → Alerts on flagged vehicles.

3. Analytics Dashboard →

• City-wise leaderboard ranked by traffic

• Incoming vs Outgoing % breakdown

• Vehicle type distribution

• Peak hour detection 🚦

• ASCII bar charts for traffic visualization


🛠 Tech Stack

• Language: C++17

• Core Concepts: OOP, STL (vector, map, algorithm), Timestamps (ctime)

• Visualization: Console-based ASCII charts with colors


📊 Example Insights

 === Analytics Summary (All Cities Leaderboard) ===
City          Entries   Incoming   Outgoing   In %    Out %    Vehicle Types
---------------------------------------------------------------------------
Shirpur       43        25         18         58.1%   41.9%    Cars:23 Bikes:12 Trucks:5 Buses:3

Peak Hour: 17:00 with 34 vehicles recorded 🚦



🎯 Why This Project?
This project is a practical demonstration of:

• Real-world traffic management simulation

• Hands-on use of STL and data structures

• Data analysis & visualization in C++

• Building modular and extendable systems


🚀 Future Improvements

• Integration with GPS or IoT sensor data

• Web-based dashboard with interactive charts

• AI-driven congestion prediction


📌 How to Run

g++ main.cpp -o traffic
./traffic

or Run the main.cpp file in VS Code (Personal Recommendation)

📷 Preview

<img width="2780" height="574" alt="Smart Traffic System (1)" src="https://github.com/user-attachments/assets/4680b4e7-56bb-48d7-ab92-4b23d0b2288f" />

<img width="2715" height="949" alt="Smart Traffic System (2)" src="https://github.com/user-attachments/assets/e2f25561-15b7-411f-956a-09ff8ee96aba" />

<img width="942" height="413" alt="Smart Traffic System (3)" src="https://github.com/user-attachments/assets/d51c0995-ddce-4840-bc74-5b4ff563a12e" />

<img width="1416" height="345" alt="Smart Traffic System (4)" src="https://github.com/user-attachments/assets/e6bf63d6-e71a-4d78-b50f-763f247624a9" />


📜 License

This project is open-source and available under the MIT License.
