#include <iostream>
#include <cstdlib>  
#define MAX_USERS 10  

using namespace std;

class MobileUser {
    long int mobileno;
    string name;
    long int billamount;

public:
    MobileUser() {
        mobileno = 0;
        name = "-";
        billamount = 0;
    }
    friend class Records;
};

class Records {
    MobileUser M[MAX_USERS];
    int n;

public:
    Records(int n1) {
        n = n1;
    }
    void accept();
    void display();
    int linear_search(long int key);
    int nonrec_binary_search(long int key);
    int rec_binary_search(long int key, int low, int high);
    void rec_quick(int low, int high);
    int partition(int low, int high);
    void adjust( int n1,int i);
    void heapsort();
};

void Records::accept() {
    cout << "Enter mobile number, name, and bill amount for " << n << " users:\n";
    for (int i = 0; i < n; i++) {
        cout << "User " << i + 1 << ":\n";
        cout << "Mobile Number: ";
        cin >> M[i].mobileno;
        cout << "Name: ";
        cin >> M[i].name;
        cout << "Bill Amount: ";
        cin >> M[i].billamount;
    }
}

void Records::display() {
    cout << "\n Mobile Number\tName \tBill Amount\n";
    for (int i = 0; i < n; i++) {
        cout << M[i].mobileno << "\t" << M[i].name << "\t" << M[i].billamount << endl;
    }
}

int Records::linear_search(long int key) {
    for (int i = 0; i < n; i++) {
        if (key == M[i].mobileno) {
            cout << "\n Mobile Number\tName \tBill Amount\n";
            cout << M[i].mobileno << "\t" << M[i].name << "\t" << M[i].billamount << endl;
            return i;
        }
    }
    return -1;
}

int Records::nonrec_binary_search(long int key) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (M[mid].mobileno == key) {
            cout << "\n Mobile Number\tName \tBill Amount\n";
            cout << M[mid].mobileno << "\t" << M[mid].name << "\t" << M[mid].billamount << endl;
            return mid;
        }
        if (M[mid].mobileno < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    cout << "Mobile number not found.\n";
    return -1;
}

int Records::rec_binary_search(long int key, int low, int high) {
    if (low > high) return -1;
    int mid = (low + high) / 2;
    if (M[mid].mobileno == key) {
        cout << "\n Mobile Number\tName \tBill Amount\n";
        cout << M[mid].mobileno << "\t" << M[mid].name << "\t" << M[mid].billamount << endl;
        return mid;
    }
    if (key < M[mid].mobileno) {
        return rec_binary_search(key, low, mid - 1);
    } else {
        return rec_binary_search(key, mid + 1, high);
    }
}

int Records::partition(int low, int high) {
    long int pivot = M[high].mobileno;
    int i = low ;
    for (int j = low; j < high; j++) {
        if (M[j].mobileno > pivot) {   
            swap(M[i], M[j]);
         i++;
        }
        
    }
    swap(M[i], M[high]);
    return i ;
}

void Records::rec_quick(int low, int high) {
    if (low < high) {
        int pi = partition(low, high);
        rec_quick(low, pi - 1);
        rec_quick(pi + 1, high);
        
    }
}

void Records::adjust(int n1, int i) {
    int j;
    MobileUser temp;
    while((2 * i + 1) <= n1) {
        j = 2 * i + 1;
        if(((j + 1) <= n1) && (M[j + 1].billamount > M[j].billamount)) {
            j++;
        }
        if(M[i].billamount >= M[j].billamount) {
            break;
        }
        else {
            temp = M[i];
            M[i] = M[j];
            M[j] = temp;
            i = j;
        }
    }
}

void Records::heapsort() {
    int i, n1 = n;
    MobileUser temp;
    for(i = (n1 / 2) - 1; i >= 0; i--) {
        adjust(n1 - 1, i);
    }
    while(n1 > 0) {
        temp = M[0];
        M[0] = M[n1 - 1];
        M[n1 - 1] = temp;
        n1--;
        adjust(n1 - 1, 0);
    }
}




int main() {
    int n;
    cout << "Enter number of mobile users: ";
    cin >> n;
    
    Records rec(n);
    int choice;
    
    do {
        cout << "\nMenu:\n";
        cout << "1. Accept Records\n";
        cout << "2. Display Records\n";
        cout << "3. Sort by Mobile Number using Quick Sort\n";
        cout << "4. Sort by Bill Amount using Heap Sort\n";
        cout << "5. Search by Mobile Number (Linear Search)\n";
        cout << "6. Search by Mobile Number (Non-Recursive Binary Search)\n";
        cout << "7. Search by Mobile Number (Recursive Binary Search)\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                rec.accept();
                break;
            case 2:
                rec.display();
                break;
            case 3:
                rec.rec_quick(0, n - 1);
                cout << "Records sorted by Mobile Number using Quick Sort:\n";
                rec.display();
                break;
            case 4:
                rec.heapsort();
                cout << "Records sorted by Bill Amount using Heap Sort:\n";
                rec.display();
                break;
            case 5: {
                long int key;
                cout << "Enter mobile number to search: ";
                cin >> key;
                int index = rec.linear_search(key);
                if (index == -1)
                    cout << "Mobile number not found.\n";
                break;
            }
            case 6: {
                long int key;
                cout << "Enter mobile number to search: ";
                cin >> key;
                int index = rec.nonrec_binary_search(key);
                if (index == -1)
                    cout << "Mobile number not found.\n";
                break;
            }
            case 7: {
                long int key;
                cout << "Enter mobile number to search: ";
                cin >> key;
                int index = rec.rec_binary_search(key, 0, n - 1);
                if (index == -1)
                    cout << "Mobile number not found.\n";
                break;
            }
            case 8:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 8);

    return 0;
}