#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <iomanip>
#include "QL_SV.h"
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
using namespace std;

QL_SV::QL_SV()
{
	_listofstd = nullptr;
	_n = 0;
}

QL_SV::~QL_SV()
{
    if (_listofstd != nullptr) 
    {
        for (int i = 0; i < _n; i++) 
        {
            delete _listofstd[i];
        }
        delete[] _listofstd;
    }
}
void QL_SV::setNumber(int n)
{
    _n = n;
}
int QL_SV::n()
{
    return _n;
}

QL_SV::QL_SV(const QL_SV& other)
{
    _n = other._n;
    _listofstd = new Student * [_n];
    for (int i = 0; i < _n; i++)
    {
        _listofstd[i] = new Student(*other._listofstd[i]);
    }
}

void QL_SV::inputList()
{
    _listofstd = new Student * [_n];

    for (int i = 0; i < _n; i++)
    {
        cout << "Nhap sinh vien thu " << i + 1 << ": " << endl;
        //Input Student data
        _listofstd[i] = new Student();
        _listofstd[i]->inputStudent();
        cout << endl;
    }
}

void QL_SV::outputList()
{
    // set column width for each field
    const int NAME_WIDTH = 25;
    const int ID_WIDTH = 15;
    const int BIRTHDAY_WIDTH = 15;
    const int MARKS_WIDTH = 10;
    const int GPA_WIDTH = 10;

    // print the header row
    cout << "=========================================================================================================" << endl;
    cout << setw(NAME_WIDTH) << left << "Ho va ten" << setw(ID_WIDTH) << left << "MSSV"
        << setw(BIRTHDAY_WIDTH) << left << "Ngay sinh" << setw(MARKS_WIDTH) << left << "Diem BT"
        << setw(MARKS_WIDTH) << left << "Diem GK" << setw(MARKS_WIDTH) << left << "Diem CK"
        << setw(GPA_WIDTH) << left << "GPA" << endl;
    cout << "=========================================================================================================" << endl;
    for (int i = 0; i < _n; i++)
    {
        _listofstd[i]->outputStudent();
    }
    cout << "=========================================================================================================" << endl;
}

void QL_SV::insertStudent(const Student &s) 
{
    Student** newList = new Student * [_n + 1]; 

    for (int i = 0; i < _n; i++) {
        newList[i] = _listofstd[i]; // copy existing students to new list
    }

    newList[_n] = new Student(s); // add the new student to the end of the new list

    // free memory used by old list
    delete[] _listofstd;

    // update list pointer and size
    _listofstd = newList;
    _n++;
}

QL_SV& QL_SV::operator=(const QL_SV& other)
{
    if (_listofstd != nullptr)
    {
        for (int i = 0; i < _n; i++)
        {
            delete _listofstd[i];
        }
        delete[]_listofstd;
    }
    if (this != &other)
    {
        _n = other._n;
        _listofstd = new Student * [_n];
        for (int i = 0; i < other._n; i++)
        {
            _listofstd[i] = new Student(*other._listofstd[i]);
        }
    }
    return *this;
}

void QL_SV::readFileToList(char* filename)
{
    ifstream reader;
    reader.open(filename, ios::in);

    if (reader.is_open())
    {
        char line[1000];
        while (reader.getline(line, 1000)) 
        {
            if (strlen(line) == 0)
            {
                break;
            }
            char* name;
            char* id;
            char* dateOfBirth;
            float exerciseMark;
            float midtermMark;
            float finaltermMark;

            char* token = strtok(line, ",");
            name = new char[strlen(token) + 1];
            strcpy(name, token);

            token = strtok(NULL, ",");
            id = new char[strlen(token) + 1];
            strcpy(id, token);

            token = strtok(NULL, ",");
            dateOfBirth = new char[strlen(token) + 1];
            strcpy(dateOfBirth, token);

            token = strtok(NULL, ",");
            exerciseMark = atof(token);

            token = strtok(NULL, ",");
            midtermMark = atof(token);

            token = strtok(NULL, "\n");
            finaltermMark = atof(token);

            Student s(name, id, dateOfBirth, exerciseMark, midtermMark, finaltermMark);
            insertStudent(s);
        }
        cout << "Student List successfully loaded!" << endl;
    }
    else
    {
        throw exception("Cannot open file");
    }
    reader.close();
}

void QL_SV::writeListToFile(char* filename)
{
    ofstream writer;
    writer.open(filename, ios::out);
    if (writer.is_open())
    {
        for (int i = 0; i < _n; i++)
        {
            char* buffer = new char[300];
            sprintf(buffer, "%s,%s,%s,%.2f,%.2f,%.2f\n", _listofstd[i]->name(), _listofstd[i]->id(), _listofstd[i]->birth(), _listofstd[i]->excercise(), _listofstd[i]->midterm(), _listofstd[i]->finalterm());
            writer << buffer;
            delete[]buffer;
        }
        cout << "Data successfully written into file" << endl;
    }
    else
    {
        throw exception("Cannot open file");
    }
    writer.close();
}

void QL_SV::deleteListData()
{
    if (_listofstd != nullptr)
    {
        for (int i = 0; i < _n; i++)
        {
            delete _listofstd[i];
        }
        delete[] _listofstd;
    }
    _listofstd = nullptr;
    _n = 0;
}

void QL_SV::addStudent(int numOfStd, char* filename)
{
    for (int i = 0; i < numOfStd; i++)
    {
        Student newStd;
        newStd.inputStudent();
        insertStudent(newStd);
        newStd.updateFile(filename);
        cout << endl;
    }
}

float QL_SV::averageGPA()
{
    float sum = 0.0;
    for (int i = 0; i < _n; i++)
    {
        sum += _listofstd[i]->gpa();
    }
    return sum / _n;
}

void QL_SV::outputListWithBelowAverageGPA()
{
    // set column width for each field
    const int NAME_WIDTH = 25;
    const int ID_WIDTH = 15;
    const int BIRTHDAY_WIDTH = 15;
    const int MARKS_WIDTH = 10;
    const int GPA_WIDTH = 10;

    // print the header row
    cout << "=========================================================================================================" << endl;
    cout << setw(NAME_WIDTH) << left << "Ho va ten" << setw(ID_WIDTH) << left << "MSSV"
        << setw(BIRTHDAY_WIDTH) << left << "Ngay sinh" << setw(MARKS_WIDTH) << left << "Diem BT"
        << setw(MARKS_WIDTH) << left << "Diem GK" << setw(MARKS_WIDTH) << left << "Diem CK"
        << setw(GPA_WIDTH) << left << "GPA" << endl;
    cout << "=========================================================================================================" << endl;

    for (int i = 0; i < _n; i++)
    {
        if (_listofstd[i]->gpa() < averageGPA())
        {
            _listofstd[i]->outputStudent();
        }
    }
    cout << "=========================================================================================================" << endl;

}
void QL_SV::writeBelowAverageStd(char* filename)
{
    float avgGPA = averageGPA();
    ofstream fout(filename);
    if (fout.fail()) 
    {
        cout << "Error: Could not open file " << filename << " for writing." << endl;
        return;
    }
    for (int i = 0; i < _n; i++) 
    {
        if (_listofstd[i]->gpa() < this->averageGPA()) 
        {

            fout << _listofstd[i]->name() << "," << _listofstd[i]->id() << "," << _listofstd[i]->birth() << "," << _listofstd[i]->excercise() << "," << _listofstd[i]->midterm() << "," << _listofstd[i]->finalterm()<< endl;
        }
    }
    fout.close();
}

void QL_SV::rankingStudent()
{
    map<float, vector<Student>> gpaMap;
    for (int i = 0; i < _n; i++)
    {
        float gpa = _listofstd[i]->gpa();
        gpaMap[gpa].push_back(*_listofstd[i]);
    }
    int rank = 1;
    for (auto i = gpaMap.rbegin(); i != gpaMap.rend(); i++)
    {
        for (auto student : i->second)
        {
            cout << "Hang: " << rank << endl;
            student.outputStudent();
            rank++;
        }
    }
}

void QL_SV::outputListWithAcademicPerformance()
{
    // set column width for each field
    const int NAME_WIDTH = 25;
    const int ID_WIDTH = 15;
    const int BIRTHDAY_WIDTH = 15;
    const int MARKS_WIDTH = 10;
    const int GPA_WIDTH = 10;
    const int ACA_WIDTH = 10;

    // print the header row
    cout << "=========================================================================================================" << endl;
    cout << setw(NAME_WIDTH) << left << "Ho va ten" << setw(ID_WIDTH) << left << "MSSV"
        << setw(BIRTHDAY_WIDTH) << left << "Ngay sinh" << setw(MARKS_WIDTH) << left << "Diem BT"
        << setw(MARKS_WIDTH) << left << "Diem GK" << setw(MARKS_WIDTH) << left << "Diem CK"
        << setw(GPA_WIDTH) << left << "GPA" << setw(ACA_WIDTH) << left << "Hoc luc" << endl;
    cout << "=========================================================================================================" << endl;
    for (int i = 0; i < _n; i++)
    {
        _listofstd[i]->outputStudentWithAcademicPerformance();
    }
    cout << "=========================================================================================================" << endl;
}

void QL_SV::outputStudentWhoseBirthdayIsToday()
{
    // set column width for each field
    const int NAME_WIDTH = 25;
    const int ID_WIDTH = 15;
    const int BIRTHDAY_WIDTH = 15;
    const int MARKS_WIDTH = 10;
    const int GPA_WIDTH = 10;

    //Get current time
    time_t now = time(nullptr);
    struct tm local_time = *localtime(&now);

    //Flag to determine if the list has students whose birthdays are today or not
    bool isEmpty = true;
    

    // print the header row
    cout << "=========================================================================================================" << endl;
    cout << setw(NAME_WIDTH) << left << "Ho va ten" << setw(ID_WIDTH) << left << "MSSV"
        << setw(BIRTHDAY_WIDTH) << left << "Ngay sinh" << setw(MARKS_WIDTH) << left << "Diem BT"
        << setw(MARKS_WIDTH) << left << "Diem GK" << setw(MARKS_WIDTH) << left << "Diem CK"
        << setw(GPA_WIDTH) << left << "GPA" << endl;
    cout << "=========================================================================================================" << endl;

    for (int i = 0; i < _n; i++)
    {
        if (_listofstd[i]->dayOfBirth() == local_time.tm_mday && _listofstd[i]->monthOfBirth() == local_time.tm_mon + 1)
        {
            _listofstd[i]->outputStudent();
            isEmpty = false;
        }
    }
    cout << "=========================================================================================================" << endl;
    if (isEmpty == true)
    {
        cout << "There is no student whose birthday is today" << endl;
    }
}