# 🚇 Metro System - C++ Project

## 📌 Description  
The **Metro System** is a comprehensive **C++ console-based application** that simulates the functionality of a modern metro transit system.  
The project is divided into two user modes — **User** and **Staff** — each offering tailored functionalities. It features a **login/signup system** for secure access, **metro map navigation**, **card management**, **utility-based station searches**, and **staff-specific operations** like patrolling and cleaning routes.
> 🎓 *Group Project developed as part of our college curriculum to simulate a functional metro transit system using graph algorithms, OOP, and console-based UI in C++.*  
> 🔧 Developed by a team of 4 — Shubhra, Akshat, Janvi, and Jitendra.

---

## 🧰 Features

### 🔐 Login & Signup  
- Secure authentication system allowing users and staff to register and login.

---

## 👤 Main Menu
[1] User  
[2] Staff  
[3] Exit

---

## 👥 User Menu
[1] Show Metro Map → View the full metro network  
[2] Show Station Details → Get information about a specific station  
[3] Display Card Info → View current metro card balance and usage  
[4] Recharge Card → Add money to your metro card  
[5] Pay Fare → Deduct fare from the card based on travel  
[6] Go Back to Previous Station → Return to the last visited station  
[7] Nearest Station with Washroom → Find closest station with a washroom  
[8] Nearest Station with Parking → Find closest station with parking facilities  
[9] All Paths Between Stations → List all possible paths between two selected stations  
[10] Shortest Path Between Stations → Calculate the optimal shortest path  
[11] Go to Main Menu → Return to the main menu

---

## 🛠️ Staff Menu
[1] Patrol Route → Generate a complete patrol route using Chinese Postman algorithm  
[2] Route Cleaning → Plan an efficient route for cleaning operations  
[3] Return to Main Menu → Navigate back to main menu

---

## 💡 Highlights

- 🗺️ **Graph-based route planning and pathfinding**  
- 💳 **Metro card management** with fare deduction and recharge  
- 🚻 **Nearest station search** (washroom, parking)  
- 👮 **Patrol route generation** for staff using advanced algorithms (e.g., Chinese Postman Problem)  
- ✨ **Interactive console interface** with `gotoxy()` for structured layout  

---

## 📁 Technologies Used

- **Language**: C++  
- **Data Structures**: Graphs, Maps, Queues  
- **Algorithms**: BFS, Dijkstra, Chinese Postman  
- **UI**: Console-based using `gotoxy()` for layout control  

---

## 👥 Contributors

| Name | GitHub Profile | Primary Responsibilities | Supported In |
|------|----------------|--------------------------|---------------|
|  **Shubhra Varshney** |  [@SV2111004](https://github.com/SV2111004) | 🔹 Implemented **Dijkstra's Algorithm** for shortest path<br>🔹 Designed and managed **station data structures** and **station info display** | ➕ Assisted **Jitendra** in integrating shortest path logic into **patrol route planning** |
|  **Akshat** | [@Akshat-1618](https://github.com/Akshat-1618) | 🔹 Implemented **All Paths feature** using DFS/BFS<br>🔹 Designed **user movement tracking** for going back to previous station | ➕ Helped **Janvi** in connecting travel actions with **fare deduction logic** |
|  **Janvi** |[@JanviArora24](https://github.com/JanviArora24) | 🔹 Developed **nearest washroom/parking station** finder using Priority Queue<br>🔹 Handled **login/signup system** and **metro card recharge/deduction** | ➕ Coordinated with **Akshat** for **card balance tracking** after station movement |
|  **Jitendra** | [@Jitendra-roy04](https://github.com/Jitendra-roy04) | 🔹 Implemented **Eulerian Circuit** algorithm (Fleury’s) for **maintenance/patrol routes**<br>🔹 Built and maintained the **metro graph structure** with edge weights | ➕ Worked with **Shubhra** to unify **shortest path** and **maintenance logic** |

---

### 🛠 Collaboration Overview:

- All contributors actively participated in planning, debugging, and refining features.  
- Code was regularly merged and reviewed to ensure quality and functionality.  
- Design decisions were made collectively, especially for integrating graph-based modules.

