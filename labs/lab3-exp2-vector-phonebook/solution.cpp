/*
 * COMP 2233 LAB 3 — EXPERIMENT 2 SOLUTION
 * Phone Book using C++ Vector
 *
 * Feynman: Vector = "Dinamik raf" — dolar dolmaz 2x büyür.
 *   push_back → O(1) amortized (nadiren realloc yapar)
 *   erase     → O(n) (arkasındaki elemanları kaydırır)
 *   sort      → Bubble sort ile O(n²) — surname, sonra name'e göre
 *
 * KEY COMPARISON vs. Array:
 *   Array:  Sabit boyut, overflow = kötü
 *   Vector: Dinamik boyut, auto-resize, STL fonksiyonları mevcut
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Contact {
    string name;
    string surname;
    string phone;
    string email;
    string birthday;
};

/* ─────────────────────────────────── HELPERS ─────────────────────────────── */

int read_int(const string &prompt) {
    string remainder;
    int value;
    cout << prompt;
    if (cin >> value) { getline(cin, remainder); return value; }
    if (cin.eof()) return 0;
    cin.clear();
    getline(cin, remainder);
    return -1;
}

void read_contact(Contact &c) {
    cout << "  Name: ";     getline(cin, c.name);
    cout << "  Surname: ";  getline(cin, c.surname);
    cout << "  Phone: ";    getline(cin, c.phone);
    cout << "  E-mail: ";   getline(cin, c.email);
    cout << "  Birthday (DD/MM/YYYY): "; getline(cin, c.birthday);
}

void print_contact(int pos, const Contact &c) {
    cout << "  [" << pos << "] "
         << c.surname << ", " << c.name
         << " | " << c.phone
         << " | " << c.email
         << " | " << c.birthday << "\n";
}

/* ─────────────────────────────────── OPERATIONS ─────────────────────────── */

/* ADD — O(1) amortized: push_back to end */
void add_contact(vector<Contact> &contacts) {
    Contact c;
    read_contact(c);
    contacts.push_back(c);  /* Vector handles memory automatically */
    cout << "  Contact added! Total: " << contacts.size() << "\n";
}

/* VIEW — O(n) */
void list_contacts(const vector<Contact> &contacts) {
    if (contacts.empty()) { cout << "  (Phone book is empty)\n"; return; }
    cout << "\n  === Phone Book (" << contacts.size() << " contacts) ===\n";
    for (size_t i = 0; i < contacts.size(); i++) {
        print_contact((int)i + 1, contacts[i]);
    }
}

/* REMOVE — O(n): find position + erase (shifts elements after) */
void remove_contact(vector<Contact> &contacts) {
    if (contacts.empty()) { cout << "  ERROR: Phone book is empty.\n"; return; }
    list_contacts(contacts);
    int pos = read_int("  Enter position to remove (1-based): ");
    if (pos < 1 || pos > (int)contacts.size()) {
        cout << "  ERROR: Invalid position.\n"; return;
    }
    cout << "  Removing: " << contacts[pos-1].name << " " << contacts[pos-1].surname << "\n";
    contacts.erase(contacts.begin() + (pos - 1));  /* erase at iterator */
    cout << "  Done. " << contacts.size() << " contacts remaining.\n";
}

/* UPDATE — O(1) access, then re-read fields */
void update_contact(vector<Contact> &contacts) {
    if (contacts.empty()) { cout << "  ERROR: Phone book is empty.\n"; return; }
    list_contacts(contacts);
    int pos = read_int("  Enter position to update (1-based): ");
    if (pos < 1 || pos > (int)contacts.size()) {
        cout << "  ERROR: Invalid position.\n"; return;
    }
    cout << "  Enter new details for position " << pos << ":\n";
    read_contact(contacts[pos - 1]);
    cout << "  Updated!\n";
}

/* SORT — O(n²) Bubble Sort by surname, then by name
 *
 * Bubble Sort logic:
 *   Compare adjacent pairs, swap if out of order.
 *   After each pass, the largest element "bubbles" to the end.
 *   n passes → O(n²) comparisons.
 *
 * Comparator: first compare surname, if equal compare name.
 */
void sort_contacts(vector<Contact> &contacts) {
    int n = (int)contacts.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            bool should_swap;
            int cmp = contacts[j].surname.compare(contacts[j+1].surname);
            if (cmp > 0) {
                should_swap = true;                    /* surname j > surname j+1 */
            } else if (cmp == 0) {
                should_swap = contacts[j].name > contacts[j+1].name; /* tie-break by name */
            } else {
                should_swap = false;
            }
            if (should_swap) {
                swap(contacts[j], contacts[j+1]);  /* STL swap for struct */
            }
        }
    }
    cout << "  Sorted by surname (then by name). O(n²) Bubble Sort.\n";
}

/* ─────────────────────────────────── MAIN ────────────────────────────────── */

int main() {
    vector<Contact> contacts;
    int choice;

    /* Seed with sample data */
    contacts.push_back({"Ali", "Demir", "0555-111", "ali@mail.com", "10/05/2000"});
    contacts.push_back({"Zeynep", "Arslan", "0544-222", "z@mail.com", "22/11/2001"});
    contacts.push_back({"Burak", "Arslan", "0533-333", "b@mail.com", "03/03/2002"});

    do {
        cout << "\n=== COMP 2233 LAB 3 - EXPERIMENT 2: PHONE BOOK (VECTOR) ===\n";
        cout << "1. Add Contact      [push_back O(1) amortized]\n";
        cout << "2. Remove Contact   [erase O(n)]\n";
        cout << "3. Update Contact   [access O(1)]\n";
        cout << "4. Sort Contacts    [Bubble Sort O(n²)]\n";
        cout << "5. View Contacts    [iterate O(n)]\n";
        cout << "0. Exit\n";
        choice = read_int("Choice: ");
        switch (choice) {
            case 1: add_contact(contacts);    break;
            case 2: remove_contact(contacts); break;
            case 3: update_contact(contacts); break;
            case 4: sort_contacts(contacts);  break;
            case 5: list_contacts(contacts);  break;
            case 0: cout << "Goodbye!\n";     break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
