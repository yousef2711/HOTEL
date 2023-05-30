#include <iostream>
#include <string>
using namespace std;

class person {
    string name;
    string IDroom;
    person* left;
    person* right;

public:
    person(string n, string id) {
        
        name = n;
        IDroom = id;
        right = NULL;
        left = NULL;
    }

    person* getRight() {
        return right;
    }

    person* getLeft() {
        return left;
    }

    string getName() {
        return name;
    }

    string getIDroom() {
        return IDroom;
    }
    void setName(const string& n) {
        name = n;
    }

    void setIDroom(const string& ID)  {
        IDroom = ID;
    }

    void setLeft(person* l) {
        left = l;
    }

    void setRight(person* r) {
        right = r;
    }
};

class binarysearchtree {
    person* root;

    person* recInsert(person* current, string n, string p) {
        if (!current) {
            person* node = new person(n, p);
            current = node;
            return current;
        }

        if (n < current->getName()) {
            current->setLeft(recInsert(current->getLeft(), n, p));
        }
        else if (n > current->getName()) {
            current->setRight(recInsert(current->getRight(), n, p));
        }

        return current;
    }

    void recPrint(person* x) {
        if (!x) {
            return;
        }

        recPrint(x->getLeft());
        cout << x->getName() << ":" << x->getIDroom() << endl;
        recPrint(x->getRight());
    }

    person* recSearch(person* current, string name) {
        if (!current) {
            return NULL;
        }

        if (current->getName() == name) {
            return current;
        }
        else if (name < current->getName()) {
            return recSearch(current->getLeft(), name);
        }
        else {
            return recSearch(current->getRight(), name);
        }
    }

    person* recRemove(person* current, string n) {
        if (!current) {
            return NULL;
        }

        if (n < current->getName()) {
            current->setLeft(recRemove(current->getLeft(), n));
        }
        else if (n > current->getName()) {
            current->setRight(recRemove(current->getRight(), n));
        }
        else {
            if (!current->getLeft() && !current->getRight()) {
                delete current;
                return NULL;
            }
            else if (!current->getLeft() || !current->getRight()) {
                person* temp = current->getLeft() ? current->getLeft() : current->getRight();
                delete current;
                return temp;
            }
            else {
                person* temp = current->getRight();
                while (temp->getLeft()) {
                    temp = temp->getLeft();
                }
                current->setRight(recRemove(current->getRight(), temp->getName()));
                current->setName(temp->getName());
                current->setIDroom(temp->getIDroom());
            }
        }

        return current;
    }

public:
    binarysearchtree() {
        root = NULL;
    }

    void addNode(string n, string p) {
        if (!root) {
            person* x = new person(n, p);
            root = x;
            return;
        }

        recInsert(root, n, p);
    }

    person* search(string n) {
        return recSearch(root, n);
    }

    void removeContact(string n) {
        root = recRemove(root, n);
    }

    void print() {
        recPrint(root);
    }
};

int main() {
    binarysearchtree t;
    string name, ID;
    int choice;

    do {
        cout << "Enter your choice:" << endl;
        cout << "1. Add a client" << endl;
        cout << "2. Search for a client" << endl;
        cout << "3. Remove a client" << endl;
        cout << "4. Print all client" << endl;
        cout << "5. Exit" << endl;
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter room ID: ";
            cin >> ID;
            t.addNode(name, ID);
            break;
        case 2:
            cout << "Enter name to search: ";
            cin >> name;
            person* p;
            p = t.search(name);
            if (p) {
                cout << "Client found: " << p->getName() << ": " << p->getIDroom() << endl;
            }
            else {
                cout << "Client not found." << endl;
            }
            break;
        case 3:
            cout << "Enter name to remove: ";
            cin >> name;
            t.removeContact(name);
            break;
        case 4:
            cout << "Clients:" << endl;
            t.print();
            break;
        case 5:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }

    } while (choice != 5);

    return 0;
}
