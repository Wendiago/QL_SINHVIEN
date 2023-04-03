#pragma once
#include <iostream>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
using namespace std;

class Student {
private:
	char* _name;
	char* _id;
	char* _birthday;
	float _marks[3];
	float _gpa;
	char* _academicPerformance;
public:
	Student();
	Student(char*, char*, char*, float, float, float);
	Student(const Student&);
	~Student();
public:
	//Setters
	void setName(char*);
	void setId(char*);
	void setBirthDay(char*);
	void setExcercise(float);
	void setMidTerm(float);
	void setFinalTerm(float);
	void setGPA(float);
	//Getters
	char* name() const;
	char* id() const;
	char* birth() const;
	float excercise() const;
	float midterm() const;
	float finalterm() const;
	float gpa() const;
	char* academicPerformance() const;
	int dayOfBirth();
	int monthOfBirth();
public:
	void inputStudent();
	void outputStudent();
	void updateFile(char* filename);
	void evaluateAcademicPerformance(float);
	void outputStudentWithAcademicPerformance();
};

