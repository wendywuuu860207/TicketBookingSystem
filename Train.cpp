// Train.cpp
// Member-function definitions for class Train.
#include "Train.h" // Train class definition

// Train default constructor initializes data members
Train::Train( string theTrainNumber, string *theDepartureTimes )
{
   setTrainNumber( theTrainNumber );
   setDepartureTimes( theDepartureTimes );
} // end Train default constructor

string Train::getTrainNumber()
{
   return trainNumber;
}

string Train::getDepartureTimes( int station )
{
   return departureTimes[ station ];
}

//assignment
void Train::setTrainNumber(string theTrainNumber)
{
	strcpy_s(trainNumber, theTrainNumber.c_str());
}
//assignment
void Train::setDepartureTimes(string *theDepartureTimes)
{
	if (theDepartureTimes != NULL)
	{
		for (int i = 0; i < 13; i++)
			strcpy_s(departureTimes[i], theDepartureTimes[i].c_str());
	}
}