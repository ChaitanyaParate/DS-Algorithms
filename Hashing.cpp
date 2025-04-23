#include <iostream>
#include <string>
using namespace std;

const int SIZE = 10;

class Student {
public:
    int roll_no;
    string name;
    float marks;
    bool occupied;

    Student() {
        roll_no = -1;
        name = "";
        marks = 0.0;
        occupied = false;
    }

    void input() {
        cout << "Enter roll no: ";
        cin >> roll_no;
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter marks: ";
        cin >> marks;
        occupied = true;
    }

    void display(int index) const {
        if (occupied) {
            cout << index << "\t\t" << roll_no << "\t\t" << name << "\t" << marks << "\n";
        } else {
            cout << index << "\t\t---\t\t---\t---\n";
        }
    }

    void modify() {
        cout << "Enter new name: ";
        cin >> name;
        cout << "Enter new marks: ";
        cin >> marks;
        cout << "Record modified.\n";
    }
};

class HashTable {
    Student table[SIZE];

public:
    int hash(int roll_no) {
        return roll_no % SIZE;
    }

    void insert(Student s, bool withReplacement) {
        int index = hash(s.roll_no);

        if (!table[index].occupied) {
            table[index] = s;
            return;
        }

        if (withReplacement && hash(table[index].roll_no) != index) {
            Student temp = table[index];
            table[index] = s;
            reinsert(temp);
            return;
        }

        int i = (index + 1) % SIZE;
        while (i != index) {
            if (!table[i].occupied) {
                table[i] = s;
                return;
            }
            i = (i + 1) % SIZE;
        }

        cout << "Hash table is full. Cannot insert.\n";
    }

    void reinsert(Student s) {
        int index = hash(s.roll_no);
        int i = index;

        do {
            if (!table[i].occupied) {
                table[i] = s;
                return;
            }
            i = (i + 1) % SIZE;
        } while (i != index);

        cout << "Hash table is full. Cannot reinsert.\n";
    }

    void display() {
        cout << "\nIndex\t\tRoll No\t\tName\tMarks\n";
        for (int i = 0; i < SIZE; i++) {
            table[i].display(i);
        }
    }

    void search(int roll_no) {
        int index = hash(roll_no);
        int i = index;

        do {
            if (table[i].occupied && table[i].roll_no == roll_no) {
                cout << "\nRecord Found: " << table[i].roll_no << ", " << table[i].name << ", " << table[i].marks << "\n";
                return;
            }
            i = (i + 1) % SIZE;
        } while (i != index);

        cout << "\nRecord not found.\n";
    }

    void modify(int roll_no) {
        int index = hash(roll_no);
        int i = index;

        do {
            if (table[i].occupied && table[i].roll_no == roll_no) {
                table[i].modify();
                return;
            }
            i = (i + 1) % SIZE;
        } while (i != index);

        cout << "Record not found.\n";
    }
};

int main() {
    HashTable ht;
    int choice;
    bool withReplacement;
    cout << "Use linear probing with replacement? (1 = Yes, 0 = No): ";
    cin >> withReplacement;

    do {
        cout << "\nMenu:\n1. Create Database\n2. Display\n3. Add Record\n4. Search Record\n5. Modify Record\n6. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int n;
                cout << "Enter number of students to add: ";
                cin >> n;
                for (int i = 0; i < n; i++) {
                    Student s;
                    s.input();
                    ht.insert(s, withReplacement);
                }
                break;
            }
            case 2:
                ht.display();
                break;
            case 3: {
                Student s;
                s.input();
                ht.insert(s, withReplacement);
                break;
            }
            case 4: {
                int r;
                cout << "Enter roll no to search: ";
                cin >> r;
                ht.search(r);
                break;
            }
            case 5: {
                int r;
                cout << "Enter roll no to modify: ";
                cin >> r;
                ht.modify(r);
                break;
            }
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid option!\n";
        }
    } while (choice != 6);

    return 0;
}
