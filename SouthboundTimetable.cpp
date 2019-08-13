// FlightSchedule.cpp
// Member-function definitions for class SouthboundTimetable.
#include <iostream>
#include <iomanip>
#include <fstream>
#include "SouthboundTimetable.h" // SouthboundTimetable class definition

extern string departureTimes[ 37 ];

// SouthboundTimetable default constructor loads southbound timetable from the file "Southbound timetable.dat"
SouthboundTimetable::SouthboundTimetable()
{
   loadSouthboundTimetable();
}

int SouthboundTimetable::getNumberOfTrains()
{
   return southboundTimetable.size();
}

vector<Train>::iterator SouthboundTimetable::searchTrain(string trainNumber)
{
	vector<Train>::iterator it = southboundTimetable.begin();
	for (int i = 0; i < southboundTimetable.size(); i++, ++it)
		if (strcmp(southboundTimetable[i].getTrainNumber().c_str(), trainNumber.c_str()) == 0)
			return it;
	cout << "\nThere don't exist the train. Please try again!" << endl;
	return nullptr;
}

void SouthboundTimetable::displayComingTrains(int departureTime, int originStation, int destinationStation)
{
	int fiveTrain = 1;
	bool havetrain = false;
	for (int i = 0; i < southboundTimetable.size(); i++)
	{
		bool trainMatch = false;
		string tmpO = southboundTimetable[i].getDepartureTimes(originStation);
		string tmpD = southboundTimetable[i].getDepartureTimes(destinationStation);
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

				cout << setw(8) << southboundTimetable[i].getTrainNumber() << setw(12) << tmpO << setw(9) << tmpD << endl;
				fiveTrain++;
				if (fiveTrain > 5)
					break;
			}
		}
	}
	if (!havetrain)
		cout << "\nSorry there didn't have the match train" << endl;
}

void SouthboundTimetable::loadSouthboundTimetable()
{
	fstream south("Southbound timetable.dat", ios::in | ios::binary);
	if (!south)
	{
		cout << "\nThe file \"Southbound timetable.dat\" can't open !" << endl;
		exit(0);
	}
	while (!south.eof())
	{
		Train currentT;
		south.read(reinterpret_cast<char*>(&currentT), sizeof(Train));
		if (south.eof())
			break;
		southboundTimetable.push_back(currentT);
	}
	south.clear();
	south.close();
}