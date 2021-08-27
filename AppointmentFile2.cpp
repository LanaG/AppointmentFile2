//Svetlana Gulotta, CSIT 389, Assignment4
#include"Appt.h"//include header file Appt.h

#include<iostream>
#include<string>
#include<conio.h>
#include<fstream>

using namespace std;

void add(Appt *[], int);//1

void edit(Appt *[], int);//2

void sort(Appt *[], int);

void find(Appt *[], int);//3

void display(Appt *[], int);//4

void save(char[] , Appt *[], int);//5

void deleteAll(Appt *[], int); //6

void main()
{
	Appt *apptPnts[MAX] = { 0 };	// Allocate a pointer array and make each pointer point to null
	
	//an instance app to read to 
	Appt app;
	int choice;
	int count = 0;	// Appointment counter
	char yesno;
	char filename[30];
	bool isDeleted = false;
	
	cout << "Do you want to open a file?[y/n]: ";
	cin >> yesno;

	if (yesno == 'y' || yesno == 'Y')
	{
		cout << "\nEnter file name: ";
		cin >> filename;


			cout << "\nAttemptiing to read the file:\n";
			fstream file(filename, ios::in | ios::binary);

			if (!file)
			{
				cout << "\nError opening file.\n";
			}

			else
			{
				//find appothe number of appointment structures in the file
				file.seekg(0, ios::end);
				int size = (int)(file.tellg()) / sizeof(Appt);
				cout << "\nFile contains " << size << " appointments\n";
				file.seekg(0);//back to the begining

				//while the end of file is not reached, read its contents into app
				while (count < size && count < MAX)
				{
					file.read(reinterpret_cast <char*>(&app), sizeof(Appt));
					apptPnts[count] = new Appt;

					apptPnts[count]->date.month = app.date.month;
					apptPnts[count]->date.day = app.date.day;
					apptPnts[count]->date.year = app.date.year;
					
					apptPnts[count]->time.hour = app.time.hour;
					apptPnts[count]->time.minutes = app.time.minutes;

					apptPnts[count]->descr.description = app.descr.description;
					apptPnts[count]->descr.location = app.descr.location;
					count++;
				}

				display(apptPnts, count);

			} // else

			cout << "\nDone with file\n\n";
			file.close();
	}//if

	//repeat until user enters 7
	do
	{
		cout << "\nSelect one of the following actions:\n"
			<< "\n1. Add new appointment\n"
			<< "\n2. Edit an appoitment\n"
			<< "\n3. Show an appointment\n"
			<< "\n4. List all appointments\n"
			<< "\n5. Save all appointments to file\n"
			<< "\n6. Delete all appointments\n"
			<< "\n7. Quit\n"
			<< "\nEnter selection number: ";

		cin >> choice;

		switch (choice)
		{
			//add new appointment
		case 1:
			add(apptPnts, count);
			count++;
			break;

			//Edit an appointment
		case 2:
			edit(apptPnts, count);
			break;

			//Show an appointment
		case 3:
			sort(apptPnts, count);
			find(apptPnts, count);
			break;

			//List all appointments
		case 4:
			sort(apptPnts, count);
			display(apptPnts, count);
			break;

			//Save all appointments to file on my computer
		case 5:
			cout << "\nWhat do you want to call the file?\n";
			cin >> filename;
			save(filename, apptPnts, count);
			cout << "\nYour appointments are saved.\n";
			break;

			//Delete all appointments
		case 6:
			//If Delete all appointments is selected, 
			//the program must pass all pointers and size to a delete() function 
			//that will delete all structures created dynamically and set the pointers to NULL.
			deleteAll(apptPnts, count);
			isDeleted = true;
			cout << "\nAll appointments deleted from memory.\n";
			break;
		case 7:
			//Selecting Quit must pass all pointers and size to a delete() function 
			//that will delete all structures created dynamically, 
			//set the pointers to NULL and quit the program. 
			if(!isDeleted)//to avoid error of double deleting
			deleteAll(apptPnts, count);
			break;
		default:
			cout << "\nInvalid choice!";
		}//switch
	} while (choice != 7);

	cout << "\n\nPress any key to continue\n";
	_getch();

	exit(0); // Bypasses a compiler error during exit			
}//main