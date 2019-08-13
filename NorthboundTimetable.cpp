// NorthboundTimetable.cpp
// Member-function definitions for class NorthboundTimetable.
#include <iostream>
#include <iomanip>
#include <fstream>
#include "NorthboundTimetable.h" // NorthboundTimetable class definition

extern string departureTimes[ 37 ];

// NorthboundTimetable default constructor loads northbound timetable from the file "Northbound timetable.dat"
NorthboundTimetable::NorthboundTimetable()
{
   loadNorthboundTimetable();
}

int NorthboundTimetable::getNumberOfTrains()
{
   return northboundTimetable.size();
}

vector<Train>::iterator NorthboundTimetable::searchTrain(string trainNumber)
{
	vector<Train>::iterator it = northboundTimetable.begin();
	for (int i = 0; i < northboundTimetable.size(); i++, ++it)
		if (strcmp(northboundTimetable[i].getTrainNumber().c_str(), trainNumber.c_str()) == 0)
			return it;
	cout << "\nThere doesn't exist the train. please try again!" << endl;
	return nullptr;
}

void NorthboundTimetable::displayComingTrains(int departureTime, int originStation, int destinationStation)
{
	int fiveTrain = 1;
	bool havetrain = false;
	originStation = 13 - originStation;
	destinationStation = 13 - destinationStation;
	for (int i = 0; i < northboundTimetable.size(); i++)
	{
		bool trainMatch = false;
		string tmpO = northboundTimetable[i].getDepartureTimes(originStation);
		string tmpD = northboundTimetable[i].getDepartureTimes(destinationStation);
		if (tmpD != "-" && tmpO != "-")
		{
			if (strncmp(departureTimes[departureTime].c_str(), tmpO.c_str(), 2) == 0)
			{
				if (departureTimes[departureTime][3] == '0')
					trainMatch = true;
				else
				{
					if (tmpO[3] > departureTimes[departureTime][3])
						trainMatch = true;
					else if (tmpO[3] == departureTimes[departureTime][3] && tmpO[4] >= departureTimes[departureTime][4])
						trainMatch = true;
				}
			}
			else if (departureTimes[departureTime][0] == tmpO[0] && departureTimes[departureTime][1] < tmpO[1])
				trainMatch = true;
			else if (departureTimes[departureTime][0] < tmpO[0])
				trainMatch = true;

			if (trainMatch)
			{
				havetrain = true;
				if (fiveTrain == 1)
					cout << endl << setw(8) << "Train No" << '.' << setw(11) << "Departure" << setw(9) << "Arrival" << endl;

				cout << setw(8) << northboundTimetable[i].getTrainNumber() << setw(12) << tmpO << setw(9) << tmpD << endl;
				fiveTrain++;
				if (fiveTrain > 5)
					break;
			}
		}
	}
	if (!havetrain)
		cout << "\nSorry there didn't have the match train" << endl;

}

void NorthboundTimetable::loadNorthboundTimetable()
{
	fstream north("Northbound timetable.dat", ios::in | ios::binary);
	if (!north)
	{
		cout << "\nThe file \"Southbound timetable.dat\" can't open !" << endl;
		exit(0);
	}
	while (!north.eof())
	{
		Train currentT;
		north.read(reinterpret_cast<char*>(&currentT), sizeof(Train));
		if (north.eof())
			break;
		northboundTimetable.push_back(currentT);
	}
	north.clear();
	north.close();
}