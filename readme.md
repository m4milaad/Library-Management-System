# Library Management System in C

![Language](https://img.shields.io/badge/Language-C-blue.svg)
![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)

A simple, console-based Library Management System written entirely in C. This application provides essential functionalities for managing books and members in a small library. It's a great project for understanding file handling, data structures, and core programming concepts in C.

---

## 🚀 Features

This system is packed with the following features:

* **📚 Book Management**
    * **Add New Books**: Easily add new books to the library with a unique ID, name, and author.
    * **Search by Name**: Quickly find any book in the database by searching for its title.
    * **Search by Author**: List all available books written by a specific author.
    * **Display All Books**: View a formatted list of all books along with their current status (In Stock / Issued).

* **👥 Member Management**
    * **Add New Members**: Register new library members with a unique ID, name, and department.
    * **Display All Members**: View a complete list of all registered members and their details.

* **🔄 Transaction Handling**
    * **Issue Books**: Securely issue books to registered members, automatically updating the book's status and the member's available card count.
    * **Return Books**: Process book returns, updating records for both the book and the member.
    * **Stock Count**: Get a quick overview of the total number of books in stock versus those currently issued.

* **💾 Data Persistence**
    * All data is reliably stored in local binary files (`books.dat`, `members.dat`), ensuring that information is saved even after the program is closed.

---

## 📸 Screenshots

Here's a glimpse of the application in action.

**Main Menu**
*(A clean and intuitive menu to navigate through all the features.)*
![Main Menu Screenshot](https://i.imgur.com/your-main-menu-screenshot.png)

**Displaying All Records**
*(A well-formatted table showing all the books and members in the database.)*
![Display Records Screenshot](https://i.imgur.com/your-display-records-screenshot.png)

*(**Note**: You should replace the placeholder image links above with actual screenshots of your running application.)*

---

## 🛠️ Tech Stack

* **Language**: **C**
* **Compiler**: **GCC / MinGW / Clang**
* **Core Concepts**: File I/O (Binary), Structs, Pointers, Functions, and Console I/O.

---

## ⚙️ Getting Started

Follow these instructions to get a local copy of the project up and running on your machine.

### Prerequisites

You need a C compiler installed on your system.
* For **Windows**, you can use [MinGW](https://www.mingw-w64.org/) or the compiler included with Visual Studio.
* For **macOS** or **Linux**, you can use `gcc`, which is often pre-installed or can be installed via your package manager.

### Installation & Compilation

1.  **Clone the repository:**
    ```sh
    git clone [https://github.com/m4milaad/Library-Management-System.git](https://github.com/m4milaad/Library-Management-System.git)
    ```

2.  **Navigate to the project directory:**
    ```sh
    cd Library-Management-System
    ```

3.  **Compile the source code:**
    Open your terminal in the project directory and run the following command. This will create an executable file.

    ```sh
    gcc main.c -o library_management
    ```
    *On some systems, you might need to link the math library explicitly:*
    ```sh
    gcc main.c -o library_management -lm
    ```

### Running the Application

Once compiled, you can run the program from your terminal:

* On **macOS/Linux**:
    ```sh
    ./library_management
    ```
* On **Windows**:
    ```sh
    library_management.exe
    ```
The program will automatically create `books.dat` and `members.dat` if they don't exist.

---

## 📂 Project File Structure

The core logic of the application is contained within a single source file for simplicity.

```
.
├── main.c              # All source code for the application
├── books.dat           # Binary database file for storing book records (auto-generated)
└── members.dat         # Binary database file for storing member records (auto-generated)
```

---

## 🤝 How to Contribute

Contributions are what make the open-source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

To contribute to this project, please follow these steps:

1.  **Fork the Project**
2.  **Create your Feature Branch** (`git checkout -b feature/AmazingFeature`)
3.  **Commit your Changes** (`git commit -m 'Add some AmazingFeature'`)
4.  **Push to the Branch** (`git push origin feature/AmazingFeature`)
5.  **Open a Pull Request**

---

## 📄 License

This project is distributed under the MIT License. See the `LICENSE` file for more information.

---

## 👨‍💻 Author

**Milad Ajaz Bhat** - [m4milaad](https://github.com/m4milaad)

Project Link: [https://github.com/m4milaad/Library-Management-System](https://github.com/m4milaad/Library-Management-System)