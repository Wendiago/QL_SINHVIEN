#pragma once
#include <iostream>
#include "QL_SV.h"
#include "Student.h"
using namespace std;

class Menu {
private:
	QL_SV _listOfStd;
	int _choice;
	bool _isStdListLoaded;
	bool _isDataWrittenToFile;
public:
	Menu();
public:
	void display();
};