# Bank-Management-System
# 🏦 Bank Management System (C++)

## 📋 Overview

This is a fully-featured **Bank Management System** developed in **C++** using the **four pillars of Object-Oriented Programming (OOP)**:
- Encapsulation
- Inheritance
- Abstraction
- Polymorphism

The system includes two user roles:
- **Customer**
- **Bank Manager**

Each role has its own features and access permissions, and data is persisted using **file handling**.

---

## 👨‍💼 Developers

- **Sajjad (f2024266540)**
- **Abdullah (f2024266508)**

---

## 🚀 Features

### ✅ Customer Panel
- Create an account (with strong password validation)
- Deposit money
- Withdraw money
- Transfer funds to another customer
- View transaction history
- Request a loan
- Check loan approval status
- Change account password
- View personal and account details

### ✅ Manager Panel
- View all customers
- View a customer’s transaction history
- Approve or reject loan requests
- Delete customer accounts
- View all pending loan requests
- View personal details

---

## 🛠️ Technologies Used

- **Language:** C++
- **Concepts:** OOP (all 4 pillars), STL (vectors), file I/O
- **Libraries:** `<iostream>`, `<fstream>`, `<string>`, `<vector>`, `<ctime>`, `<cstdlib>`

---

## 💾 Data Persistence

- Customer data stored in: `customers.txt`
- Transaction history stored in: `transactions.txt`
- Loan data stored in: `Loans.txt`

---

## 🔐 Password Validation Rules

Passwords must:
- Be between **8 to 16** characters
- **Not start** with a special character
- Contain **at least one uppercase letter**
- Contain **at least one digit**
- Contain **at least one special character** (`@`, `$`, `%`, `&`, `*`, `_`)

---

## 📦 How to Run

1. **Compile the program**
   ```bash
   g++ BankManagmentSystem.cpp -o BankSystem
