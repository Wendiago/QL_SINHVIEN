#include <iostream>
#include <string>
#include <iomanip>
#include "Menu.h"
#include <exception>
using namespace std;

Menu::Menu()
{
	_choice = INT16_MAX;
	_isStdListLoaded = false;
	_isDataWrittenToFile = false;
}
void Menu::display()
{
	//Declare temporal filename for update
	char* tempFile = new char[50];
	char* fileName = new char[50];

	//Program flag
	string answer;
	do
	{
		cout << "\n----------------------------------------------------------------------" << endl;
		cout << "|                            MENU                                    |" << endl;
		cout << "----------------------------------------------------------------------" << endl;
		cout << "|1. Input student list from keyboard                                 |" << endl;
		cout << "|2. Display student list                                             |" << endl;
		cout << "|3. Write data into txt file                                         |" << endl;
		cout << "|4. Read data from txt file                                          |" << endl;
		cout << "|5. Add student and update file                                      |" << endl;
		cout << "|6. Caculate avarage GPA of all student                              |" << endl;
		cout << "|7. Print students with below average GPA and export data to file    |" << endl;
		cout << "|8. Display student list with academic performance                   |" << endl;
		cout << "|9. Display student whose birthday is today                          |" << endl;
		cout << "|0. Exit                                                             |" << endl;
		cout << "----------------------------------------------------------------------" << endl;

		//Select option
		cout << "Please select an option: ";
		cin >> _choice;
		cin.ignore();

		switch (_choice)
		{
		case 1:
			//Enter number of student, check if it's valid then input information
			if (_isStdListLoaded == false)
			{
				int numOfStd;
				do
				{
					cout << "Enter number of students in the list: ";
					cin >> numOfStd;
					cin.ignore();

					if (numOfStd > 0)
					{
						_listOfStd.setNumber(numOfStd);
						_listOfStd.inputList();
						_isStdListLoaded = true;
						cout << "Student list successfully loaded!" << endl;
					}
					else //Check if number of student entered is valid
					{
						cout << "Number of students cannot less than or equal to zero! Please enter again" << endl;
					}
				} while (numOfStd < 0);
			}
			else //Data had been entered from somewhere else. Input student list again would ovewrite the old list
			{
				_listOfStd.deleteListData();
				int numOfStd;
				do
				{
					cout << "Enter number of students in the list: ";
					cin >> numOfStd;
					cin.ignore();

					if (numOfStd > 0)
					{
						_listOfStd.setNumber(numOfStd);
						_listOfStd.inputList();
						_isStdListLoaded = true;
						cout << "Student list successfully loaded!" << endl;
					}
					else //Check if number of student entered is valid
					{
						cout << "Number of students cannot less than or equal to zero! Please enter again" << endl;
					}
				} while (numOfStd < 0);
			}
			break;
		case 2:
			if (_isStdListLoaded == false)
			{
				cout << "Student list is not loaded. Please input it first before using this utility" << endl;
			}
			else
			{
				cout << "\n---------------------------- Student list ----------------------------------" << endl;
				_listOfStd.outputList();
				cout << endl;
			}
			break;
		case 3:
			if (_isStdListLoaded == false)
			{
				cout << "Student list is not loaded. Please input it first before using this utility" << endl;
			}
			else
			{
				//Write data into file
				char* fileForWritten = new char[50];
				cout << "Enter name of the file you want to write data down: ";
				cin.getline(fileForWritten, 50);

				try
				{
					_listOfStd.writeListToFile(fileForWritten);
					//Update the flag notify that data has been written into a file for updating later
					_isDataWrittenToFile = true;
				}
				catch (exception ex)
				{
					cout << ex.what() << endl;
				}

				//Deallocate
				delete[]fileForWritten;
			}
			break;
		case 4:
			//Read data from files
			if (_isStdListLoaded == true) //If list of student has been entered from keyboard before, delete the list and read data again from file
			{
				_listOfStd.deleteListData();
			}
			//Enter fileName to work with
			cout << "Enter file name to read student list from: ";
			cin.getline(fileName, 50);

			//Copy fileName to tempFile for later use
			strcpy(tempFile, fileName);

			//Read data
			try
			{
				_listOfStd.readFileToList(fileName);
				_isStdListLoaded = true;
				_isDataWrittenToFile = true;
			}
			catch (exception ex)
			{
				cout << ex.what() << endl;
			}

			//Deallocate
			delete[]fileName;
			break;
		case 5:
			if (_isStdListLoaded == false)
			{
				cout << "Student list is not loaded. Please input it first before using this utility" << endl;
			}
			else if (_isDataWrittenToFile == false)
			{
				cout << "You haven't write data into file so that you cannot update the file" << endl;
			}
			else
			{
				//Enter number of students to add
				int num;
				do
				{
					cout << "Enter number of students to add to the list: ";
					cin >> num;
					cin.ignore();

					if (num > 0)
					{
						_listOfStd.addStudent(num, tempFile);
						cout << "Added successfully, " << tempFile << " has been updated" << endl;
					}
					else
					{
						cout << "Number of students cannot less than or equal to zero! Please enter again" << endl;
					}
				} while (num < 0);
			}
			break;
		case 6:
			if (_isStdListLoaded == false)
			{
				cout << "Student list is not loaded. Please input it first before using this utility" << endl;
			}
			else
			{
				float aveGPA = _listOfStd.averageGPA();
				cout << "Average GPA of all students is " << fixed << setprecision(3) << aveGPA << endl;
			}
			break;
		case 7:
			if (_isStdListLoaded == false)
			{
				cout << "Student list is not loaded. Please input it first before using this utility" << endl;
			}
			else
			{
				//Display students whose GPA are below average GPA
				_listOfStd.outputListWithBelowAverageGPA();

				//Enter filename
				char* newfile = new char[51];
				cout << "Enter filename to export: ";
				cin.getline(newfile, 50);

				//Export to file
				try
				{
					_listOfStd.writeBelowAverageStd(newfile);
					cout << "Export to file successfully" << endl;
				}
				catch (exception ex)
				{
					cout << ex.what() << endl;
				}
				
				//Deallocate
				delete[]newfile;
			}
			break;
		case 8:
			if (_isStdListLoaded == false)
			{
				cout << "Student list is not loaded. Please input it first before using this utility" << endl;
			}
			else
			{
				//Display student list with academic performance
				cout << "--------------------------------------------- Student list ----------------------------------------------------" << endl;
				_listOfStd.outputListWithAcademicPerformance();
			}
			break;
		case 9:
			if (_isStdListLoaded == false)
			{
				cout << "Student list is not loaded. Please input it first before using this utility" << endl;
			}
			else
			{
				//Display students whose birthday is today
				cout << "--------------------------------------------- Student list -----------------------------------------------------" << endl;
				_listOfStd.outputStudentWhoseBirthdayIsToday();
			}
			break;
		case 0:
			cout << "Exit";
			exit(8);
			break;
		default:
			cout << "Invalid choice. Please try again";
			break;
		}

		//Determine if user want to continue or not
		do
		{
			cout << "Want to continue? If not, type 'no', else type 'yes': ";
			getline(cin, answer);

			if (answer == "no")
			{
				cout << "Exit program" << endl;
				exit(8);
			}
			else if (answer != "no" && answer != "yes")
			{
				cout << "Invalid choice. Try again" << endl;
			}
		} while (answer != "no" && answer != "yes");
	} while (answer == "yes");
	delete[]tempFile;
}