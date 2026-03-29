#include <iostream>
#include <vector>
using namespace std;

class Employee {
private:
    int empID;
    string name;
    double basicPay;
    int otHours;
    static constexpr double otRate = 200.0;

public:
    Employee(int id, string n, double bp, int ot) {
        empID = id;
        name = n;
        basicPay = bp;
        otHours = ot;
    }

    Employee() {}

    int getID() { return empID; }
    string getName() { return name; }

    void setOT(int ot) {
        if (ot >= 0)
            otHours = ot;
        else
            cout << "Invalid OT hours!\n";
    }

    double calculateGross() {
        return basicPay + (otHours * otRate);
    }

    double calculateTax() {
        double g = calculateGross();
        if (g < 20000) return g * 0.05;
        else if (g <= 50000) return g * 0.10;
        else return g * 0.20;
    }

    double calculateNet() {
        return calculateGross() - calculateTax();
    }

    void displayPayslip() {
        cout << "\n--- Salary Slip ---\n";
        cout << "ID: " << empID << endl;
        cout << "Name: " << name << endl;
        cout << "Gross: " << calculateGross() << endl;
        cout << "Tax: " << calculateTax() << endl;
        cout << "Net: " << calculateNet() << endl;
    }
};

class PayrollSystem {
private:
    vector<Employee> employees;

public:
    void addEmployee() {
        int id, ot;
        string name;
        double basic;

        cout << "Enter Emp ID: ";
        cin >> id;

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
            cout << "Invalid input!\n";
            return;
        }

        employees.push_back(Employee(id, name, basic, ot));
        cout << "Employee added!\n";
    }

    void updateOT() {
        int id, ot;
        cout << "Enter Emp ID: ";
        cin >> id;

        for (auto &e : employees) {
            if (e.getID() == id) {
                cout << "Enter new OT: ";
                cin >> ot;
                e.setOT(ot);
                cout << "Updated!\n";
                return;
            }
        }

        cout << "Employee not found!\n";
    }

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

    void totalPayout() {
        double total = 0;
        for (auto &e : employees) {
            total += e.calculateNet();
        }
        cout << "Total Payout: " << total << endl;
    }

    void highestPaid() {
        if (employees.empty()) {
            cout << "No employees!\n";
            return;
        }

        Employee maxEmp = employees[0];

        for (auto &e : employees) {
            if (e.calculateNet() > maxEmp.calculateNet()) {
                maxEmp = e;
            }
        }

        cout << "\nHighest Paid Employee:\n";
        maxEmp.displayPayslip();
    }
};

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
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: ps.addEmployee(); break;
            case 2: ps.updateOT(); break;
            case 3: ps.generatePayslip(); break;
            case 4: ps.totalPayout(); break;
            case 5: ps.highestPaid(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}