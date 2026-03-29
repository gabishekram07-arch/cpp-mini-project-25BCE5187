#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Employee {
private:
    int empID;
    string name;
    double basicPay;
    int otHours;

    // FIX: static constant (shared across all objects)
    static constexpr double otRate = 200.0;

public:
    // Constructor
    Employee(int id, string n, double bp, int ot) {
        empID = id;
        name = n;
        basicPay = bp;
        otHours = ot;
    }

    // Default constructor
    Employee() {}

    // Getters
    int getID() { return empID; }
    string getName() { return name; }
    double getBasicPay() { return basicPay; }
    int getOT() { return otHours; }

    // Setter
    void setOT(int ot) {
        if (ot >= 0)
            otHours = ot;
        else
            cout << "Invalid OT hours!\n";
    }

    // Salary Calculations
    double calculateGross() {
        return basicPay + (otHours * otRate);
    }

    double calculateTax() {
        double gross = calculateGross();
        if (gross < 20000)
            return gross * 0.05;
        else if (gross <= 50000)
            return gross * 0.10;
        else
            return gross * 0.20;
    }

    double calculateNet() {
        return calculateGross() - calculateTax();
    }

    // Display payslip
    void displayPayslip() {
        cout << "\n--- Salary Slip ---\n";
        cout << "Emp ID: " << empID << endl;
        cout << "Name: " << name << endl;
        cout << "Basic Pay: " << basicPay << endl;
        cout << "OT Hours: " << otHours << endl;
        cout << "Gross Salary: " << calculateGross() << endl;
        cout << "Tax: " << calculateTax() << endl;
        cout << "Net Salary: " << calculateNet() << endl;
    }

    // Save to file
    void saveToFile(ofstream &out) {
        out << empID << " " << name << " " << basicPay << " " << otHours << endl;
    }
};

class PayrollSystem {
private:
    vector<Employee> employees;

public:
    // Add Employee
    void addEmployee() {
        int id, ot;
        string name;
        double basic;

        cout << "Enter Emp ID: ";
        cin >> id;

        // Check uniqueness
        for (auto &e : employees) {
            if (e.getID() == id) {
                cout << "EmpID already exists!\n";
                return;
            }
        }

        cout << "Enter Name: ";
        cin >> name;

        cout << "Enter Basic Pay: ";
        cin >> basic;

        cout << "Enter OT Hours: ";
        cin >> ot;

        if (basic < 0 || ot < 0) {
            cout << "Invalid input! Salary/OT must be non-negative.\n";
            return;
        }

        employees.push_back(Employee(id, name, basic, ot));
        cout << "Employee added successfully!\n";
    }

    // Update OT
    void updateOT() {
        int id, ot;
        cout << "Enter Emp ID: ";
        cin >> id;

        for (auto &e : employees) {
            if (e.getID() == id) {
                cout << "Enter new OT hours: ";
                cin >> ot;
                e.setOT(ot);
                cout << "Updated successfully!\n";
                return;
            }
        }

        cout << "Employee not found!\n";
    }

    // Generate Payslip
    void generatePayslip() {
        int id;
        cout << "Enter Emp ID: ";
        cin >> id;

        for (auto &e : employees) {
            if (e.getID() == id) {
                e.displayPayslip();
                return;
            }
        }

        cout << "Employee not found!\n";
    }

    // Total payout
    void totalPayout() {
        double total = 0;
        for (auto &e : employees) {
            total += e.calculateNet();
        }
        cout << "Total Salary Payout: " << total << endl;
    }

    // Highest paid employee (FIXED WORKING)
    void highestPaid() {
        if (employees.empty()) {
            cout << "No employees!\n";
            return;
        }

        Employee maxEmp = employees[0];

        for (auto &e : employees) {
            if (e.calculateNet() > maxEmp.calculateNet()) {
                maxEmp = e;  // ✅ now works
            }
        }

        cout << "\nHighest Paid Employee:\n";
        maxEmp.displayPayslip();
    }

    // Save to file
    void saveData() {
        ofstream out("employees.txt");
        if (!out) {
            cout << "Error opening file!\n";
            return;
        }

        for (auto &e : employees) {
            e.saveToFile(out);
        }

        out.close();
        cout << "Data saved successfully!\n";
    }
};

// Main
int main() {
    PayrollSystem ps;
    int choice;

    do {
        cout << "\n--- Payroll System ---\n";
        cout << "1. Add Employee\n";
        cout << "2. Update OT\n";
        cout << "3. Generate Payslip\n";
        cout << "4. Total Payout\n";
        cout << "5. Highest Paid Employee\n";
        cout << "6. Save Data\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: ps.addEmployee(); break;
            case 2: ps.updateOT(); break;
            case 3: ps.generatePayslip(); break;
            case 4: ps.totalPayout(); break;
            case 5: ps.highestPaid(); break;
            case 6: ps.saveData(); break;
            case 7: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}
