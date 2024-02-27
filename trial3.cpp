#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

class Student {
public:
    std::string rollNo;
    std::string name;
    std::string address;
    int age;
    std::string className;
    int mathMarks;
    int scienceMarks;
    int socialMarks;
    int computerScienceMarks;
    int totalMarks;

    Student(const std::string& rollNo, const std::string& name, const std::string& address, int age,
            const std::string& className, int mathMarks, int scienceMarks, int socialMarks, int computerScienceMarks)
            : rollNo(rollNo), name(name), address(address), age(age), className(className),
              mathMarks(mathMarks), scienceMarks(scienceMarks), socialMarks(socialMarks),
              computerScienceMarks(computerScienceMarks), totalMarks(mathMarks + scienceMarks + socialMarks + computerScienceMarks) {}
};

class HashTable {
private:
    static const int TABLE_SIZE = 100;

    struct Node {
        std::string rollNo;
        Student* student;
        Node* next;

        Node(const std::string& rollNo, Student* student) : rollNo(rollNo), student(student), next(nullptr) {}
    };

    std::vector<Node*> table;

    int hashFunction(const std::string& rollNo) const {
        int hashValue = 0;
        for (char c : rollNo) {
            hashValue += c;
        }
        return hashValue % TABLE_SIZE;
    }

public:
    HashTable() {
        table.resize(TABLE_SIZE, nullptr);
    }

    ~HashTable() {
        for (Node* node : table) {
            while (node != nullptr) {
                Node* temp = node;
                node = node->next;
                delete temp->student;
                delete temp;
            }
        }
    }

    void addStudent(const std::string& rollNo, const std::string& name, const std::string& address, int age,
                    const std::string& className, int mathMarks, int scienceMarks, int socialMarks, int computerScienceMarks) {
        int index = hashFunction(rollNo);
        Student* student = new Student(rollNo, name, address, age, className, mathMarks, scienceMarks, socialMarks, computerScienceMarks);
        Node* newNode = new Node(rollNo, student);

        if (table[index] == nullptr) {
            table[index] = newNode;
        } else {
            Node* current = table[index];
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    Student* retrieveRecord(const std::string& rollNo) const {
        int index = hashFunction(rollNo);
        Node* current = table[index];
        while (current != nullptr) {
            if (current->rollNo == rollNo) {
                return current->student;
            }
            current = current->next;
        }
        return nullptr;
    }

    void updateStudent(HashTable& hashTable) {
        std::string rollNo;
        std::cout << "Enter the Roll No of the student to update: ";
        std::cin >> rollNo;

        Student* student = hashTable.retrieveRecord(rollNo);
        if (student != nullptr) {
            int choice;
            std::cout << "Student found. Select the field to update:" << std::endl;
            std::cout << "1. Name" << std::endl;
            std::cout << "2. Address" << std::endl;
            std::cout << "3. Age" << std::endl;
            std::cout << "4. Class Name" << std::endl;
            std::cout << "5. Math Marks" << std::endl;
            std::cout << "6. Science Marks" << std::endl;
            std::cout << "7. Social Marks" << std::endl;
            std::cout << "8. Computer Science Marks" << std::endl;
            std::cout << "Enter your choice: ";
            std::cin >> choice;

            switch (choice) {
                case 1: {
                    std::string name;
                    std::cout << "Enter the new name: ";
                    std::cin.ignore();
                    std::getline(std::cin, name);
                    student->name = name;
                    break;
                }
                case 2: {
                    std::string address;
                    std::cout << "Enter the new address: ";
                    std::cin.ignore();
                    std::getline(std::cin, address);
                    student->address = address;
                    break;
                }
                case 3: {
                    int age;
                    std::cout << "Enter the new age: ";
                    std::cin >> age;
                    student->age = age;
                    break;
                }
                case 4: {
                    std::string className;
                    std::cout << "Enter the new class name: ";
                    std::cin.ignore();
                    std::getline(std::cin, className);
                    student->className = className;
                    break;
                }
                case 5: {
                    int mathMarks;
                    std::cout << "Enter the new math marks: ";
                    std::cin >> mathMarks;
                    student->mathMarks = mathMarks;
                    student->totalMarks = student->mathMarks + student->scienceMarks + student->socialMarks + student->computerScienceMarks;
                    break;
                }
                case 6: {
                    int scienceMarks;
                    std::cout << "Enter the new science marks: ";
                    std::cin >> scienceMarks;
                    student->scienceMarks = scienceMarks;
                    student->totalMarks = student->mathMarks + student->scienceMarks + student->socialMarks + student->computerScienceMarks;
                    break;
                }
                case 7: {
                    int socialMarks;
                    std::cout << "Enter the new social marks: ";
                    std::cin >> socialMarks;
                    student->socialMarks = socialMarks;
                    student->totalMarks = student->mathMarks + student->scienceMarks + student->socialMarks + student->computerScienceMarks;
                    break;
                }
                case 8: {
                    int computerScienceMarks;
                    std::cout << "Enter the new computer science marks: ";
                    std::cin >> computerScienceMarks;
                    student->computerScienceMarks = computerScienceMarks;
                    student->totalMarks = student->mathMarks + student->scienceMarks + student->socialMarks + student->computerScienceMarks;
                    break;
                }
                default:
                    std::cout << "Invalid choice." << std::endl;
                    return;
            }

            std::cout << "Student record updated successfully." << std::endl;
            std::cout << "Updated Details:" << std::endl;
            displayStudentDetails(*student);
        } else {
            std::cout << "Student not found with the given Roll No." << std::endl;
        }
    }

    void deleteStudent(HashTable& hashTable) {
        std::string rollNo;
        std::cout << "Enter the Roll No of the student to delete: ";
        std::cin >> rollNo;

        int index = hashFunction(rollNo);
        Node* current = table[index];
        Node* previous = nullptr;

        while (current != nullptr) {
            if (current->rollNo == rollNo) {
                if (previous == nullptr) {
                    table[index] = current->next;
                } else {
                    previous->next = current->next;
                }
                delete current->student;
                delete current;
                std::cout << "Student record deleted successfully." << std::endl;
                return;
            }
            previous = current;
            current = current->next;
        }

        std::cout << "Student not found with the given Roll No." << std::endl;
    }

    void displayStudentDetails(const Student& student) const {
        std::cout << "Roll No: " << student.rollNo << std::endl;
        std::cout << "Name: " << student.name << std::endl;
        std::cout << "Address: " << student.address << std::endl;
        std::cout << "Age: " << student.age << std::endl;
        std::cout << "Class Name: " << student.className << std::endl;
        std::cout << "Math Marks: " << student.mathMarks << std::endl;
        std::cout << "Science Marks: " << student.scienceMarks << std::endl;
        std::cout << "Social Marks: " << student.socialMarks << std::endl;
        std::cout << "Computer Science Marks: " << student.computerScienceMarks << std::endl;
        std::cout << "Total Marks: " << student.totalMarks << std::endl;
    }

    void displayAllRecords() const {
        for (const Node* node : table) {
            const Node* current = node;
            while (current != nullptr) {
                displayStudentDetails(*(current->student));
                std::cout << std::endl;
                current = current->next;
            }
        }
    }
    
    void loadRecordsFromFile(const std::string& fileName) {
        std::ifstream file(fileName);
        if (file.is_open()) {
            // Skip the header line
            std::string line;
            std::getline(file, line);

            while (std::getline(file, line)) {
                std::string rollNo, name, address, className;
                int age, mathMarks, scienceMarks, socialMarks, computerScienceMarks, totalMarks;

                std::istringstream iss(line);
                std::getline(iss, rollNo, ',');
                std::getline(iss, name, ',');
                std::getline(iss, address, ',');
                iss >> age;
                iss.ignore();
                std::getline(iss, className, ',');
                iss >> mathMarks;
                iss.ignore();
                iss >> scienceMarks;
                iss.ignore();
                iss >> socialMarks;
                iss.ignore();
                iss >> computerScienceMarks;
                iss.ignore();
                iss >> totalMarks;

                addStudent(rollNo, name, address, age, className, mathMarks, scienceMarks, socialMarks, computerScienceMarks);
            }

            file.close();
            std::cout << "Student records loaded from file successfully." << std::endl;
        } else {
            std::cout << "Unable to open the file." << std::endl;
        }
    }

    
    void storeRecordsToFile(const std::string& fileName) const {
        std::ofstream file(fileName);
        if (file.is_open()) {
            file << "Roll No,Name,Address,Age,Class Name,Math Marks,Science Marks,Social Marks,Computer Science Marks,Total Marks" << std::endl;

            for (const Node* node : table) {
                const Node* current = node;
                while (current != nullptr) {
                    file << current->student->rollNo << ","
                         << current->student->name << ","
                         << current->student->address << ","
                         << current->student->age << ","
                         << current->student->className << ","
                         << current->student->mathMarks << ","
                         << current->student->scienceMarks << ","
                         << current->student->socialMarks << ","
                         << current->student->computerScienceMarks << ","
                         << current->student->totalMarks << std::endl;
                    current = current->next;
                }
            }
            file.close();
            std::cout << "Student records stored in the file successfully." << std::endl;
        } else {
            std::cout << "Unable to open the file." << std::endl;
        }
    }
};

void addStudent(HashTable& hashTable) {
    std::string rollNo;
    std::cout << "Enter Roll No: ";
    std::cin >> rollNo;

    Student* student = hashTable.retrieveRecord(rollNo);
    if (student != nullptr) {
        std::cout << "Student with the given Roll No already exists." << std::endl;
    } else {
        std::string name, address, className;
        int age, mathMarks, scienceMarks, socialMarks, computerScienceMarks;

        std::cout << "Enter Name: ";
        std::cin.ignore();
        std::getline(std::cin, name);

        std::cout << "Enter Address: ";
        std::getline(std::cin, address);

        std::cout << "Enter Age: ";
        std::cin >> age;

        std::cout << "Enter Class Name: ";
        std::cin.ignore();
        std::getline(std::cin, className);

        std::cout << "Enter Math Marks: ";
        std::cin >> mathMarks;

        std::cout << "Enter Science Marks: ";
        std::cin >> scienceMarks;

        std::cout << "Enter Social Marks: ";
        std::cin >> socialMarks;

        std::cout << "Enter Computer Science Marks: ";
        std::cin >> computerScienceMarks;

        hashTable.addStudent(rollNo, name, address, age, className, mathMarks, scienceMarks, socialMarks, computerScienceMarks);
        std::cout << "Student added successfully." << std::endl;
    }
}

void searchStudent(const HashTable& hashTable) {
    std::string rollNo;
    std::cout << "Enter the Roll No of the student to search: ";
    std::cin >> rollNo;

    Student* student = hashTable.retrieveRecord(rollNo);
    if (student != nullptr) {
        std::cout << "Student found." << std::endl;
        hashTable.displayStudentDetails(*student);
    } else {
        std::cout << "Student not found with the given Roll No." << std::endl;
    }
}

void displayMenu() {
    std::cout << "************ Student Database System ************" << std::endl;
    std::cout << "1. Add Student" << std::endl;
    std::cout << "2. Search Student" << std::endl;
    std::cout << "3. Update Student" << std::endl;
    std::cout << "4. Delete Student" << std::endl;
    std::cout << "5. Display All Records" << std::endl;
    std::cout << "6. Store Records to File" << std::endl;
    std::cout << "7. Exit" << std::endl;
    std::cout << "************************************************" << std::endl;
    std::cout << "Enter your choice: ";
}

int main() {
HashTable hashTable;
hashTable.loadRecordsFromFile("records.csv");
std::string name, address, className;
int age, mathMarks, scienceMarks, socialMarks, computerScienceMarks;

    
    int choice;
    do {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                int numStudents;
                std::cout << "Enter the number of students to add: ";
                std::cin >> numStudents;
                std::cin.ignore();

   

    for (int i = 0; i < numStudents; i++) {
        std::string rollNo;
        std::cout << "Enter Roll No: ";
        std::cin >> rollNo;

        Student* student = hashTable.retrieveRecord(rollNo);
        if (student != nullptr) {
            std::cout << "Student with the given Roll No already exists." << std::endl;
        } else {
            
            std::cout << "Enter Name: ";
            std::cin.ignore();
            std::getline(std::cin, name);

            std::cout << "Enter Address: ";
            std::getline(std::cin, address);

            std::cout << "Enter Age: ";
            std::cin >> age;

            std::cout << "Enter Class Name: ";
            std::cin.ignore();
            std::getline(std::cin, className);

            std::cout << "Enter Math Marks: ";
            std::cin >> mathMarks;

            std::cout << "Enter Science Marks: ";
            std::cin >> scienceMarks;

            std::cout << "Enter Social Marks: ";
            std::cin >> socialMarks;

            std::cout << "Enter Computer Science Marks: ";
            std::cin >> computerScienceMarks;

            hashTable.addStudent(rollNo, name, address, age, className, mathMarks, scienceMarks, socialMarks, computerScienceMarks);
            std::cout << "Student added successfully." << std::endl;
        }
    }

                
                break;
            case 2:
                searchStudent(hashTable);
                break;
            case 3:
                hashTable.updateStudent(hashTable);
                break;
            case 4:
                hashTable.deleteStudent(hashTable);
                break;
            case 5:
                hashTable.displayAllRecords();
                break;
            case 6: {
    std::string fileName = "records.csv";
    hashTable.storeRecordsToFile(fileName);
    std::cout << "Records stored in records.csv successfully." << std::endl;


    break;
}

            case 7:
                std::cout << "Exiting the program." << std::endl;
                break;
            default:
                std::cout << "Invalid choice." << std::endl;
                break;
        }

        std::cout << std::endl;
    } while (choice != 7);

    return 0;
}
