#pragma once
#include <iostream>
#include <fstream>
#include <string.h>
#include "Student.h"
#include <ctime>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
using namespace std;

class QL_SV {
private:
	Student** _listofstd;
	int _n; //So luong sinh vien
public:
	QL_SV();
	~QL_SV();
	QL_SV(const QL_SV&);
	QL_SV& operator=(const QL_SV&);
public:
	void setNumber(int);
	int n();
public:
	void inputList();
	void outputList();
	void deleteListData();
	void writeListToFile(char* fileName);
	void readFileToList(char* fileName);
	void insertStudent(const Student&);
	void addStudent(int numOfStd, char* fileName);
	float averageGPA();
	void outputListWithBelowAverageGPA();
	void writeBelowAverageStd(char* fileName);
	void rankingStudent();
	void outputListWithAcademicPerformance();
	void outputStudentWhoseBirthdayIsToday();
};