#include <iostream>
#include "ReservationHistory.h" // ReservationHistory class definition

// ReservationHistory default constructor
ReservationHistory::ReservationHistory( ReservationDatabase &theReservationDatabase,
                                        SouthboundTimetable &theSouthboundTimetable,
                                        NorthboundTimetable &theNorthboundTimetable )
   : reservationDatabase( theReservationDatabase ),
     southboundTimetable( theSouthboundTimetable ),
     northboundTimetable( theNorthboundTimetable )
{
} // end ReservationHistory default constructor

void ReservationHistory::execute()
{
	string id, RNum;
	cout << "\nEnter the ID Number : ";
	cin >> id;
	cout << "\nEnter the Reservation Number : ";
	cin >> RNum;
	if (reservationDatabase.searchReservation(id, RNum) == nullptr)
	{
		cout << "\nReservation record not found!" << endl;
		return;
	}
	else
	{
		reservationDatabase.searchReservation(id, RNum)->displayReservationDetails();
		bool subExit = false;
		while (!subExit)
		{
			int subSelection = enterChoice();
			switch (subSelection)
			{
			case 1:
				reservationDatabase.cancelReservation(reservationDatabase.searchReservation(id, RNum));
				break;
			case 2:
				reservationDatabase.reduceSeats(reservationDatabase.searchReservation(id, RNum));
				break;
			case 3:
				subExit = true;
				break;
			default:
				break;
			}
		}
	}
}

int ReservationHistory::enterChoice()
{
   cout << "\nEnter Your Choice\n"
      << "1. Cancellation\n"
      << "2. Reduce\n"
      << "3. Back to Main Menu\n? ";

   int menuChoice;
   cin >> menuChoice;
   return menuChoice;
}