// ReservationDatabase.cpp
// Member-function definitions for class ReservationDatabase.
#include <iostream>
#include <fstream>
using namespace std;
#include "ReservationDatabase.h" // ReservationDatabase class definition

// ReservationDatabase default constructor loads reservations from the file Reservation details.dat
ReservationDatabase::ReservationDatabase()
{
   loadReservations();
}

// ReservationDatabase destructor stores reservations into the file Reservation details.dat
ReservationDatabase::~ReservationDatabase()
{
   storeReservations();
}

vector< Reservation >::iterator ReservationDatabase::searchReservation(string idNumber, string reservationNumber)
{
	vector< Reservation >::iterator it = reservations.begin();
	if (reservations.size() == 0)
			return nullptr;
	else
	{
		for (; it != end(); ++it)
			if (it->getIdNumber() == idNumber && it->getReservationNumber() == reservationNumber)
				return it;
	}
	return nullptr;
}

vector< Reservation >::iterator ReservationDatabase::end()
{
   return reservations.end();
}

void ReservationDatabase::displayReservation( vector< Reservation >::iterator it )
{
   it->displayReservationDetails();
}

void ReservationDatabase::cancelReservation(vector< Reservation >::iterator it)
{
	if (it == nullptr) 
	{
		cout<< "\nNo reservation records." << endl;
		return;
	}
	vector<Reservation>::iterator it2 = it;
	++it2;
	for (; it2 != reservations.end(); ++it, ++it2)
		(*it) = (*it2);
	reservations.pop_back();
	cout << "\nReservation Cancelled!" << endl;
}

void ReservationDatabase::addReservation( Reservation reservation )
{
   reservations.push_back( reservation );
}

void ReservationDatabase::reduceSeats(vector<Reservation>::iterator it)
{
	if (it == nullptr)
	{
		cout << "\nNo reservation records." << endl;
		return;
	}
	it->displayReservationDetails();
	int adR, conR;
	cout << "\nHow many adult tickets to cancel¡H ";
	cin >> adR;
	cout << "\nHow many concession tickets to cancel¡H ";
	cin >> conR;
	if (adR > it->getAdultTickets() || conR > it->getConcessionTickets())
	{
		cout << "\nNot enough to reduce. Please try again." << endl;
		reduceSeats(it);
	}
	else
	{
		it->setAdultTickets(it->getAdultTickets() - adR);
		it->setConcessionTickets(it->getConcessionTickets() - conR);
		it->displayReservationDetails();
		cout << "\nYou have successfully reduced the number of tickets!" << endl;
	}
	if (it->getAdultTickets() == 0 && it->getConcessionTickets() == 0)
		cancelReservation(it);
}

void ReservationDatabase::loadReservations()
{
	fstream history("Reservation details.dat", ios::in | ios::binary);
	if (!history)
	{
		cout << "\nFile Reservation detail.dat can't open!" << endl;
		exit(0);
	}
	while (!history.eof())
	{
		Reservation tmp;
		history.read(reinterpret_cast<char*>(&tmp), sizeof(Reservation));
		reservations.push_back(tmp);
	}

	history.clear();
	history.close();
}
void ReservationDatabase::storeReservations()
{
	fstream update("Reservation details.dat", ios::out | ios::binary);
	if (!update)
	{
		cout << "\nFile Reservation detail.dat can't open!" << endl;
		exit(0);
	}

	for (int i = 0; i < reservations.size(); i++)
		update.write(reinterpret_cast<char*>(&reservations[i]), sizeof(Reservation));

	update.clear();
	update.close();
}