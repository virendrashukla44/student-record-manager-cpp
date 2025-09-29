#include <bits/stdc++.h>
using namespace std;

struct Student {
    int roll;
    string name;
    float marks;
};

void loadFromFile(vector<Student> &students, const string &filename) {
    students.clear();
    ifstream fin(filename);
    if (!fin.is_open()) return;
    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        // Expected format: roll|name|marks
        stringstream ss(line);
        string token;
        Student s;
        if (!getline(ss, token, '|')) continue;
        s.roll = stoi(token);
        if (!getline(ss, token, '|')) continue;
        s.name = token;
        if (!getline(ss, token, '|')) continue;
        s.marks = stof(token);
        students.push_back(s);
    }
    fin.close();
}

void saveToFile(const vector<Student> &students, const string &filename) {
    ofstream fout(filename);
    for (const auto &s : students) {
        fout << s.roll << '|' << s.name << '|' << s.marks << "\n";
    }
    fout.close();
}

int findStudentIndexByRoll(const vector<Student> &students, int roll) {
    for (size_t i = 0; i < students.size(); ++i)
        if (students[i].roll == roll) return (int)i;
    return -1;
}

void addStudent(vector<Student> &students) {
    Student s;
    cout << "Enter roll number: ";
    cin >> s.roll;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (findStudentIndexByRoll(students, s.roll) != -1) {
        cout << "A student with this roll already exists.\n";
        return;
    }
    cout << "Enter name: ";
    getline(cin, s.name);
    cout << "Enter marks (0 - 100): ";
    cin >> s.marks;
    students.push_back(s);
    cout << "Student added successfully.\n";
}

void displayAll(const vector<Student> &students) {
    if (students.empty()) {
        cout << "No student records available.\n";
        return;
    }
    cout << "Roll\tName\t\tMarks\n";
    cout << "---------------------------------\n";
    for (const auto &s : students) {
        cout << s.roll << '\t' << s.name << '\t' << s.marks << '\n';
    }
}

void searchByRoll(const vector<Student> &students) {
    int roll;
    cout << "Enter roll number to search: ";
    cin >> roll;
    int idx = findStudentIndexByRoll(students, roll);
    if (idx == -1) {
        cout << "Student not found.\n";
        return;
    }
    const Student &s = students[idx];
    cout << "Found: Roll: " << s.roll << ", Name: " << s.name << ", Marks: " << s.marks << "\n";
}

void updateStudent(vector<Student> &students) {
    int roll;
    cout << "Enter roll number to update: ";
    cin >> roll;
    int idx = findStudentIndexByRoll(students, roll);
    if (idx == -1) {
        cout << "Student not found.\n";
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter new name (leave blank to keep current): ";
    string name;
    getline(cin, name);
    if (!name.empty()) students[idx].name = name;
    cout << "Enter new marks (-1 to keep current): ";
    float marks;
    cin >> marks;
    if (marks >= 0) students[idx].marks = marks;
    cout << "Record updated.\n";
}

void deleteStudent(vector<Student> &students) {
    int roll;
    cout << "Enter roll number to delete: ";
    cin >> roll;
    int idx = findStudentIndexByRoll(students, roll);
    if (idx == -1) {
        cout << "Student not found.\n";
        return;
    }
    students.erase(students.begin() + idx);
    cout << "Student deleted.\n";
}

void sortByMarks(vector<Student> &students) {
    sort(students.begin(), students.end(), [](const Student &a, const Student &b){
        return a.marks > b.marks; // descending
    });
    cout << "Students sorted by marks (high -> low).\n";
}

int main() {
    vector<Student> students;
    const string filename = "students.txt";
    loadFromFile(students, filename);

    while (true) {
        cout << "\n--- Student Record Manager ---\n";
        cout << "1. Add student\n2. Display all\n3. Search by roll\n4. Update student\n5. Delete student\n6. Sort by marks\n7. Save & Exit\n8. Exit without saving\n";
        cout << "Choose option: ";
        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Try again.\n";
            continue;
        }
        switch (choice) {
            case 1: addStudent(students); break;
            case 2: displayAll(students); break;
            case 3: searchByRoll(students); break;
            case 4: updateStudent(students); break;
            case 5: deleteStudent(students); break;
            case 6: sortByMarks(students); break;
            case 7: saveToFile(students, filename); cout << "Saved. Exiting.\n"; return 0;
            case 8: cout << "Exiting without saving.\n"; return 0;
            default: cout << "Invalid option.\n";
        }
    }
    return 0;
}
