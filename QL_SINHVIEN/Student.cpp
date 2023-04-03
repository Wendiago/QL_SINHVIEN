#include <iostream>
#include <fstream>
#include <iomanip>
#include "Student.h"
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
using namespace std;

Student::Student()
{
	_name = nullptr;
	_id = nullptr;
	_birthday = nullptr;
	for (int i = 0; i < 3; i++)
	{
		_marks[i] = 0.0;
	}
	_gpa = 0.0;
	_academicPerformance = nullptr;
}
Student::Student(char* name, char* id, char* birth, float excercise, float midterm, float finalterm)
{
	_name = new char[strlen(name) + 1];
	strcpy(_name, name);

	_id = new char[strlen(id) + 1];
	strcpy(_id, id);

	_birthday = new char[strlen(birth) + 1];
	strcpy(_birthday, birth);

	_marks[0] = excercise;
	_marks[1] = midterm;
	_marks[2] = finalterm;
	_gpa = excercise * 0.25 + midterm * 0.25 + finalterm * 0.5;

	evaluateAcademicPerformance(_gpa);
}
Student::Student(const Student& s)
{
	_name = new char[strlen(s.name()) + 1];
	strcpy(_name, s.name());

	_id = new char[strlen(s.id()) + 1];
	strcpy(_id, s.id());

	_birthday = new char[strlen(s.birth()) + 1];
	strcpy(_birthday, s.birth());

	_marks[0] = s.excercise();
	_marks[1] = s.midterm();
	_marks[2] = s.finalterm();
	_gpa = s.gpa();

	_academicPerformance = new char[strlen(s._academicPerformance) + 1];
	strcpy(_academicPerformance, s.academicPerformance());
}
Student::~Student()
{
	delete[]_name;
	delete[]_id;
	delete[]_birthday;
	delete[]_academicPerformance;
}
void Student::setName(char* name)
{
	_name = new char[strlen(name) + 1];
	strcpy(_name, name);
}
void Student::setId(char* id)
{
	_id = new char[strlen(id) + 1];
	strcpy(_id, id);
}
void Student::setBirthDay(char* birth)
{
	_birthday = new char[strlen(birth) + 1];
	strcpy(_birthday, birth);
}

void Student::setExcercise(float excercise)
{
	_marks[0] = excercise;
}
void Student::setMidTerm(float midterm)
{
	_marks[1] = midterm;
}
void Student::setFinalTerm(float finalterm)
{
	_marks[2] = finalterm;
}
void Student::setGPA(float gpa)
{
	_gpa = gpa;
}
char* Student::name() const
{
	return _name;
}
char* Student::id() const
{
	return _id;
}
char* Student::birth() const
{
	return _birthday;
}
float Student::excercise() const
{
	return _marks[0];
}
float Student::midterm() const
{
	return _marks[1];
}
float Student::finalterm() const
{
	return _marks[2];
}
float Student::gpa() const
{
	return _marks[0] * 0.25 + _marks[1] * 0.25 + _marks[2] * 0.5;
}
char* Student::academicPerformance() const
{
	return _academicPerformance;
}
int Student::dayOfBirth()
{
	char* tempBirth = new char[strlen(_birthday) + 1];
	strcpy(tempBirth, this->birth());
	char* token = strtok(tempBirth,  "/");
	char* day = new char[strlen(token) + 1];
	strcpy(day, token);
	int day_int = atoi(day);
	delete[]token;
	delete[]day;
	return day_int;
}
int Student::monthOfBirth()
{
	char* tempBirth = new char[strlen(_birthday) + 1];
	strcpy(tempBirth, this->birth());

	char* month = new char[11];
	month = strtok(tempBirth, "/");
	month = strtok(NULL, "/");

	int month_int = atoi(month);

	return month_int;
}
void Student::inputStudent()
{
	char* tempName = new char[51];
	cout << "Nhap ten sinh vien: ";
	cin.getline(tempName, 50);
	_name = new char[strlen(tempName) + 1];
	strcpy(_name, tempName);
	delete[]tempName;

	char* tempId = new char[50];
	cout << "Nhap MSSV: ";
	cin.getline(tempId, 50);
	_id = new char[strlen(tempId) + 1];
	strcpy(_id, tempId);
	delete[]tempId;

	char* tempBirth = new char[50];
	cout << "Nhap ngay sinh: ";
	cin.getline(tempBirth, 50);
	_birthday = new char[strlen(tempBirth) + 1];
	strcpy(_birthday, tempBirth);
	delete[]tempBirth;

	float excercise, midterm, finalterm;
	cout << "Nhap diem bai tap: ";
	cin >> excercise;

	cout << "Nhap diem giua ki: ";
	cin >> midterm;

	cout << "Nhap diem cuoi ki: ";
	cin >> finalterm;

	_marks[0] = excercise;
	_marks[1] = midterm;
	_marks[2] = finalterm;

	_gpa = excercise * 0.25 + midterm * 0.25 + finalterm * 0.5;
	evaluateAcademicPerformance(_gpa);
	cin.ignore();
}
void Student::outputStudent()
{
	// set column width for each field
	const int NAME_WIDTH = 25;
	const int ID_WIDTH = 15;
	const int BIRTHDAY_WIDTH = 15;
	const int MARKS_WIDTH = 10;
	const int GPA_WIDTH = 10;

	// print the student information
	cout << setw(NAME_WIDTH) << left << _name << setw(ID_WIDTH) << left << _id
		<< setw(BIRTHDAY_WIDTH) << left << _birthday << setw(MARKS_WIDTH) << left << _marks[0]
		<< setw(MARKS_WIDTH) << left << _marks[1] << setw(MARKS_WIDTH) << left << _marks[2]
		<< setw(GPA_WIDTH) << left << _gpa << endl;
}

void Student::updateFile(char* filename)
{
	ofstream writer;
	writer.open(filename, ios::app); //Open file in append mode to write additional information into an existed .txt file
	if (writer.is_open())
	{
		char* buffer = new char[300];
		sprintf(buffer, "%s,%s,%s,%.2f,%.2f,%.2f", _name, _id, _birthday, _marks[0], _marks[1], _marks[2]);
		writer << endl;
		writer << buffer;
		delete[]buffer;
	}
	else
	{
		throw exception("Cannot open file");
	}
	writer.close();
}

void Student::evaluateAcademicPerformance(float gpa)
{
	if (gpa >= 8.0)
	{
		_academicPerformance = new char[5];
		strcpy(_academicPerformance, "Gioi");
	}
	else if (gpa >= 6.5 && gpa < 8.0)
	{
		_academicPerformance = new char[4];
		strcpy(_academicPerformance, "Kha");
	}
	else if (gpa < 6.5 && gpa >= 5.0)
	{
		_academicPerformance = new char[11];
		strcpy(_academicPerformance, "Trung Binh");
	}
	else
	{
		_academicPerformance = new char[4];
		strcpy(_academicPerformance, "Yeu");
	}
}

void Student::outputStudentWithAcademicPerformance()
{
	// set column width for each field
	const int NAME_WIDTH = 25;
	const int ID_WIDTH = 15;
	const int BIRTHDAY_WIDTH = 15;
	const int MARKS_WIDTH = 10;
	const int GPA_WIDTH = 10;
	const int ACA_WIDTH = 10;

	// print the student information
	cout << setw(NAME_WIDTH) << left << _name << setw(ID_WIDTH) << left << _id
		<< setw(BIRTHDAY_WIDTH) << left << _birthday << setw(MARKS_WIDTH) << left << _marks[0]
		<< setw(MARKS_WIDTH) << left << _marks[1] << setw(MARKS_WIDTH) << left << _marks[2]
		<< setw(GPA_WIDTH) << left << _gpa << setw(ACA_WIDTH) << left << _academicPerformance << endl;

}




