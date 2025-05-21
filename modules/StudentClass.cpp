#include "functions.h"
#include "StudentClass.h"
#include <unistd.h>
#include <limits.h>


inline ::ostream& operator<<(::ostream& os, ::Vector<StudentClass>& students) {
    os << left << setw(15) << "Pavardė"
       << setw(10) << "Vardas"
       << setw(15) << "Galutinis (Vid.)"<< '\n';

    os << setfill('-') << setw(55) << "-" << setfill(' ') << '\n';

    for (const auto& student : students) {
        os << student << '\n';
    }

    return os;
}

  ::Vector<StudentClass> StudentClass::addStudentsObjects(::Vector<StudentClass> students) {
    char answer;
    cout << "Ar norite pridėti naują studentą? (t/n) ";
    cin >> answer;

    while (tolower(answer) == 't') {
        cout << "Įveskite studento duomenis (vardas, pavardė, pažymiai už ND, egzamino pažymys): "<<endl;

        StudentClass student;
        cin.ignore();
        cin >> student;
        students.push_back(student);

        cout << "Ar norite pridėti naują studentą? (t/n) ";
        cin >> answer;
    }

    return students;
}


double StudentClass::averageClass(const StudentClass &student) {
    const auto& grades = student.getGrades();

    if (grades.empty()) {
        return 0.0;
    }

    auto b = grades.begin();
    auto e = grades.end();

    if (!b || !e || b > e) {
        std::cerr << "[ERROR] averageClass: Invalid vector pointers. begin=" <<b
                  << ", end=" << e << std::endl;
        return 0.0;
    }

    double sum = std::accumulate(b, e, 0.0);
    double average = sum / grades.size();

    return average;
}


double StudentClass::medianClass(StudentClass &student) {
    if (student.getGrades().empty()) {
        return 0.0;
    }
    Vector<double> sorted_grades =student.getGrades();
    sort(sorted_grades.begin(), sorted_grades.end());

    size_t middle = sorted_grades.size() / 2;

    if (sorted_grades.size() % 2 == 0) {
        return (sorted_grades[middle - 1] + sorted_grades[middle]) / 2.0;
    } else {
        return sorted_grades[middle];
    }
}

double StudentClass::calculateFinalGradesMedianClass(StudentClass &student) {
    double median_grade = medianClass(student);
    return median_grade * 0.4 + student.getExamGrades() * 0.6;
}

void StudentClass::calculateFinalGradesAverageClass(StudentClass &student) {
    double average_grade = averageClass(student);
    double finalGrade = average_grade * 0.4 + student.getExamGrades() * 0.6;
    student.setFinalGrade(finalGrade);
}

void StudentClass::printStudentListClass(Vector<StudentClass> &students) {
    cout << students;
}

void StudentClass::generateGradesClass(Vector<StudentClass> &students) {
    static bool seeded = false;
    if (!seeded) {
        srand(time(0));
        seeded = true;
    }

    for (auto &student : students) {
        int grades_number = 5;
        student.clearGrades();
        for (int i = 0; i < grades_number; ++i) {
            Vector<double> newGrades = student.getGrades();
            newGrades.push_back(rand() % 10 + 1);
            student.setGrades(newGrades);
        }
        student.setExamGrades(rand() % 10 + 1);
        calculateFinalGradesAverageClass(student);
    }
}

Vector<string> StudentClass::loadFromFileClass(const string &filename) {
    Vector<string> list;
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            list.push_back(line);
        }
        file.close();
    }
    return list;
}

void StudentClass::writeStudentsToFile(const Vector<StudentClass>& students, const string& filename) {
    ofstream outputFile(filename);

    if (!outputFile.is_open()) {
        cerr << "Klaida: failo negalima atidaryti " << filename << endl;
        return;
    }

    for (auto it = students.cbegin(); it != students.cend(); ++it) {
        outputFile << *it << endl;
    }

    outputFile.flush();
    outputFile.close();
}

Vector<StudentClass> StudentClass::readStudentsFileClass(const string& filename) {
    Vector<StudentClass> students;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Klaida: Nepavyko atidaryti failo: " << filename << endl;
        return students;
    }
    else{
      cout << "File opened" << endl;
      }



    while (true) {
    StudentClass tmp;
    if (!(file >> tmp)) break;
    students.push_back(std::move(tmp));

}

    file.close();
    return students;
}

Vector<StudentClass> StudentClass::generateRandomStudentsClass(int count) {
    Vector<StudentClass> students;

    for (int i = 1; i <= count; ++i) {
        StudentClass student;
        student.setName ("Vardas" + to_string(rand() % count + 1));
        student.setSurname("Pavarde" + to_string(rand() % count + 1));
        students.push_back(student);
    }
    return students;
}

Vector<StudentClass> StudentClass::testClass() {
    string filename;
    cout << "Kiek studentų norite pridėti? (10000/100000/1000000)" << endl;
    int n;
    cin >> n;
    while (n != 10000 && n != 100000 && n != 1000000) {
        cout << "Neteisinga įvestis, bandykite dar kartą" << endl;
        cin >> n;
    }
    auto start = high_resolution_clock::now();
    if (n == 10000) {
        filename.assign("studentai10000.txt");
    } else if (n == 100000) {
        filename.assign("studentai100000.txt");
    } else if (n == 1000000) {
        filename.assign("studentai1000000.txt");
    }
    Vector<StudentClass> students;
    ifstream file(filename);
    try {
        if (!file.is_open()) {
            throw runtime_error("Nepavyko atidaryti failo: " + filename);
        }

        string line, header;
        getline(file, header);
        while (getline(file, line)) {
            istringstream iss(line);
            StudentClass student;

            iss >> student.name >> student.surname;

            double grade;
            Vector<double> tempGrades;
            while (iss >> grade) {
                tempGrades.push_back(grade);
            }

            if (!tempGrades.empty()) {
                student.setExamGrades(static_cast<int>(tempGrades.back()));
                tempGrades.pop_back();
                student.setGrades(tempGrades);
            } else {
                cerr << "Warning: No grades found for student " << student.name << " " << student.surname << endl;
            }

            students.push_back(student);
        }

        file.close();

        auto stop = chrono::high_resolution_clock::now();
        auto duration_ms = ::chrono::duration_cast<::chrono::milliseconds>(stop - start);

        double duration_s = duration_ms.count() / 1000.0;
        printStudentListClass(students);

        cout << "Duration (seconds): " << duration_s << endl;
    } catch (const runtime_error &e) {
        cerr << "Klaida skaitant failą: " << e.what() << endl;
    }
    return students;
}

bool StudentClass::compareByNameClass(const StudentClass& a, const StudentClass& b) {
   return a.getName() < b.getName();


}

bool StudentClass::compareBySurnameClass(const StudentClass& a, const StudentClass& b) {
     return a.getSurname() < b.getSurname();

}

bool StudentClass::compareByAverageClass(const StudentClass& a, const StudentClass& b) {
    return a.getFinalGrade() < b.getFinalGrade();
}
Vector<StudentClass> StudentClass::sortByNameClass(Vector<StudentClass>& students) {
    // Custom sort function for your Vector class.
    for (size_t i = 0; i < students.size() - 1; ++i) {
        for (size_t j = i + 1; j < students.size(); ++j) {
            if (compareByNameClass(students[i], students[j])) {
                std::swap(students[i], students[j]);
            }
        }
    }
    return students;
}

Vector<StudentClass> StudentClass::sortBySurnameClass(Vector<StudentClass>& students) {
    // Custom sort function for your Vector class.
    for (size_t i = 0; i < students.size() - 1; ++i) {
        for (size_t j = i + 1; j < students.size(); ++j) {
            if (compareBySurnameClass(students[i], students[j])) {
                std::swap(students[i], students[j]);
            }
        }
    }
    printStudentListClass(students);
    return students;
}

Vector<StudentClass> StudentClass::sortByAverageClass(Vector<StudentClass>& students) {
    std::sort(students.begin(), students.end(), [](const StudentClass& a, const StudentClass& b) {
    return a.getFinalGrade() < b.getFinalGrade();
});
    return students;
}
void StudentClass::logDuration(const string &message, const high_resolution_clock::time_point &start, const high_resolution_clock::time_point &stop) {
    auto duration_ms = duration_cast<milliseconds>(stop - start);
    double duration_s = duration_ms.count() / 1000.0;
    cout << message << fixed << setprecision(10) << duration_s << " sec" << endl;
}

void StudentClass::generateStudentsFileClass(int numberOfStudents) {
    string filename = "students" + to_string(numberOfStudents) + ".txt";
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "Nepavyko sukurti failo: " << filename << endl;
        return;
    }

    auto start = high_resolution_clock::now();
    Vector<StudentClass> students = generateRandomStudentsClass(numberOfStudents);
    generateGradesClass(students);

    for (StudentClass &student : students) {
        file << student.getName() << " " << student.getSurname() << "       ";
        for (const double &grade : student.getGrades()) {
            file << grade << " ";
        }
        file << student.getExamGrades() << endl;
    }

    auto stop = high_resolution_clock::now();
    logDuration(filename + " sukūrimo laikas: ", start, stop);
    file.close();
}
void StudentClass::sortStudentsInFileClass(Vector<StudentClass> &students, int numberOfStudents) {
    string studentsFilename = "students" + to_string(numberOfStudents) + ".txt";
    auto startRead = high_resolution_clock::now();
    students = readStudentsFileClass(studentsFilename);
    auto stopRead = high_resolution_clock::now();
    logDuration(to_string(numberOfStudents) + " įrašų iš failo nuskaitymo laikas: ", startRead, stopRead);

    auto startSort = high_resolution_clock::now();
    students = sortByAverageClass(students);

    auto stopSort = high_resolution_clock::now();
    logDuration(to_string(numberOfStudents) + " įrašų rūšiavimo laikas: ", startSort, stopSort);

    Vector<StudentClass> vargsiukai;
    strategyThreeVector(students, vargsiukai, numberOfStudents);

    students.erase(students.begin(), students.end());
}

void StudentClass::strategyTwoVectorClass(Vector<StudentClass> &students, Vector<StudentClass> &vargsiukai, int num) {
    timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    int blogiukai = 0;

    for (int i = 0; i < num; i++) {
        if (students[i].getFinalGrade() < 5.00) {
            blogiukai++;
        }
    }
    vargsiukai.reserve(blogiukai);
    vargsiukai.assign_range(students.begin(), students.begin() + blogiukai);
    students.erase(students.begin(), students.begin() + blogiukai);

    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    double elapsed_seconds =
        (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    cout << to_string(num) + "  str 2 irasu dalijimas i vector: " << elapsed_seconds << "s" << endl;
}

void StudentClass::strategyThreeVector(Vector<StudentClass> &students, Vector<StudentClass> &vargsiukai, int num) {
    timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    Vector<StudentClass>::iterator bound;
    bound = stable_partition(students.begin(), students.end(), [](StudentClass &s) { return s.getFinalGrade() < 5.00; });
    vargsiukai.reserve(bound - students.begin());
    copy(students.begin(), bound, back_inserter(vargsiukai));
    students.erase(students.begin(), bound);

    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    double elapsed_seconds =
        (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    cout << to_string(num) + "  str 3 irasu dalijimas i vector: " << elapsed_seconds << "s" << endl;
    string kietekaiFilename = "kietekai" + to_string(num) + ".txt";
    string vargsiukaiFilename = "vargsiukai" + to_string(num) + ".txt";
    writeStudentsToFile(vargsiukai, vargsiukaiFilename);
    writeStudentsToFile(students, kietekaiFilename);
}

