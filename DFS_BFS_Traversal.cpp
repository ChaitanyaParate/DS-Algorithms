#include <iostream>
#include <string>
using namespace std;

class Stack;
class Queue;
class Graph;

class Node {
private:
    int id;
    string name;
    Node* next;
public:
    Node(int id = -1, string name = "") : id(id), name(name), next(nullptr) {}
    int getId() const { return id; }
    string getName() const { return name; }
    Node* getNext() const { return next; }
    void setNext(Node* node) { next = node; }
    friend class Graph;
};

class Queue {
    int a[20];
    int front, rear;
public:
    Queue() : front(-1), rear(-1) {}
    void insert(int);
    int del();
    bool isEmpty();
};

void Queue::insert(int temp) {
    if (rear < 19) {
        rear++;
        a[rear] = temp;
    }
    else {
        cout << "Queue Overflow\n";
    }
}

int Queue::del() {
    if (!isEmpty()) {
        front++;
        return a[front];
    }
    else {
        cout << "Queue Underflow\n";
        return -1;
    }
}

bool Queue::isEmpty() {
    return front == rear;
}

class Stack {
    int b[30];
    int top_index;
public:
    Stack() : top_index(-1) {}
    void push(int);
    int pop();
    bool isEmpty();
};

void Stack::push(int temp) {
    if (top_index < 29) {
        top_index++;
        b[top_index] = temp;
    }
    else {
        cout << "Stack Overflow\n";
    }
}

int Stack::pop() {
    if (!isEmpty()) {
        int z = b[top_index];
        top_index--;
        return z;
    }
    else {
        cout << "Stack Underflow\n";
        return -1;
    }
}

bool Stack::isEmpty() {
    return top_index == -1;
}

class Graph {
private:
    Node* head[20];
    bool visited[20];
    int numUsers;
public:
    Graph() : numUsers(0) {
        for(int i = 0; i < 20; i++) {
            head[i] = nullptr;
            visited[i] = false;
        }
    }
    void create_AL();
    void display_AL();
    void resetVisited();
    void BFS(int start);
    void recursive_DFS(int start);
    void non_recursive_DFS(int start);
    int getNumUsers() const { return numUsers; }
};

void Graph::create_AL() {
    char ch;
    cout << "Enter the number of friends (max 20): ";
    cin >> numUsers;
   

    for(int i = 0; i < numUsers; i++) {
        string name;
        cout << "Enter name of user " << i << ": ";
        cin >> name;
        head[i] = new Node(i, name);
    }

    for(int i = 0; i < numUsers; i++) {
        cout << "Does user " << head[i]->getName() << " have any friends? (y/n): ";
        cin >> ch;
        while(ch == 'y' || ch == 'Y') {
            int friend_id;
            cout << "Enter friend's user ID (0 to " << numUsers-1 << "): ";
            cin >> friend_id;
            if(friend_id < 0 || friend_id >= numUsers) {
                cout << "Invalid user ID. Please try again.\n";
            }
            else {
                Node* newFriend = new Node(friend_id, head[friend_id]->getName());
                if(head[i]->next == nullptr) {
                    head[i]->next = newFriend;
                }
                else {
                    Node* temp = head[i]->next;
                    while(temp->next != nullptr) {
                        temp = temp->next;
                    }
                    temp->next = newFriend;
                }
                cout << "Any another friend for user " << head[i]->getName() << "? (y/n): ";
                cin >> ch;
            }
        }
    }
}

void Graph::display_AL() {
    cout << "\nAdjacency List of the Graph:\n";
    for(int i = 0; i < numUsers; i++) {
        cout << "User " << head[i]->getName() << " (ID: " << head[i]->getId() << ") has friends: ";
        Node* temp = head[i]->getNext();
        if(temp == nullptr) {
            cout << "No friends";
        }
        else {
            while(temp != nullptr) {
                cout << head[temp->getId()]->getName() << " (ID: " << temp->getId() << "), ";
                temp = temp->getNext();
            }
        }
        cout << "\n";
    }
}

void Graph::BFS(int start) {
    if(start < 0 || start >= numUsers) {
        cout << "Invalid start node.\n";
        return;
    }

    Queue q;
    q.insert(start);
    visited[start] = true;

    while(!q.isEmpty()) {
        int current = q.del();
        if(current != -1) {
            cout << "Visited User: " << head[current]->getName() << " (ID: " << current << ")\n";
            Node* temp = head[current]->getNext();
            while(temp != nullptr) {
                if(!visited[temp->getId()]) {
                    q.insert(temp->getId());
                    visited[temp->getId()] = true;
                }
                temp = temp->getNext();
            }
        }
    }
}

void Graph::recursive_DFS(int start) {
    if(start < 0 || start >= numUsers) {
        cout << "Invalid start node.\n";
        return;
    }
    visited[start] = true;
    cout << "Visited User: " << head[start]->getName() << " (ID: " << start << ")\n";
    Node* temp = head[start]->getNext();
    while(temp != nullptr) {
        if(!visited[temp->getId()]) {
            recursive_DFS(temp->getId());
        }
        temp = temp->getNext();
    }
}

void Graph::non_recursive_DFS(int start) {
    if(start < 0 || start >= numUsers) {
        cout << "Invalid start node.\n";
        return;
    }

    Stack s;
    s.push(start);

    while(!s.isEmpty()) {
        int current = s.pop();
        if(!visited[current]) {
            cout << "Visited User: " << head[current]->getName() << " (ID: " << current << ")\n";
            visited[current] = true;
            Node* temp = head[current]->getNext();
            while(temp != nullptr) {
                if(!visited[temp->getId()]) {
                    s.push(temp->getId());
                }
                temp = temp->getNext();
            }
        }
    }
}

void Graph::resetVisited() {
    for(int i = 0; i < numUsers; i++) {
        visited[i] = false;
    }
}

int main(){
    Graph g;
    int choice, startNode;

    g.create_AL();
    g.display_AL();

    while(true) {
        
        cout << "\nChoose an option:\n";
        cout << "1. Recursive DFS\n";
        cout << "2. Non-Recursive DFS\n";
        cout << "3. BFS\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        /*cout << "1. Recursive DFS\n";
        cout << "2. Non-Recursive DFS\n";*/
        cout << "Enter your choice: ";
        cin >> choice;

        if(choice == 4) {
            cout << "Exiting...\n";
            break;
        }

        cout << "Enter the start node ID (0 to " << (g.getNumUsers() - 1) << "): ";
        cin >> startNode;

        switch(choice) {
            case 1:
                cout << "\nRecursive DFS Traversal:\n";
                g.resetVisited();
                g.recursive_DFS(startNode);
                break;
            case 2:
                cout << "\nNon-Recursive DFS Traversal:\n";
                g.resetVisited();
                g.non_recursive_DFS(startNode);
                break;
            case 3:
                cout << "\nBFS Traversal:\n";
                g.resetVisited();
                g.BFS(startNode);
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
