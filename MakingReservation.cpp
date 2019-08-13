// MakingReservation.cpp
// Member-function definitions for class MakingReservation.
#include <iostream>
#include <iomanip>
#include "MakingReservation.h" // MakingReservation class definition

extern string departureTimes[ 37 ];

// MakingReservation constructor
MakingReservation::MakingReservation( ReservationDatabase &theReservationDatabase,
                                      SouthboundTimetable &theSouthboundTimetable,
                                      NorthboundTimetable &theNorthboundTimetable )
   : reservationDatabase( theReservationDatabase ),
     southboundTimetable( theSouthboundTimetable ),
     northboundTimetable( theNorthboundTimetable )
{
} // end MakingReservation constructor

void MakingReservation::execute()
{
   int departureTime;

   inputReservationDetails( departureTime );

   chooseTrain( departureTime ); // displays timetables for 5 coming trains, then let user choose a train

   inputContactPersonInfo();

   reservation.displayReservationDetails();

   reservationDatabase.addReservation( reservation );

   cout << "\nReservation Completed!\n\n";
}
// inputs originStation, destinationStation, carClass,
// date, departureTime, adultTickets and concessionTickets
void MakingReservation::inputReservationDetails(int &departureTime)
{
	char stations[13][10] = { "", "Nangang", "Taipei", "Banqiao", "Taoyuan", "Hsinchu", "Miaoli",
		"Taichung", "Changhua", "Yunlin", "Chiayi", "Tainan", "Zuoying" };
	char car[3][13] = { "", "Standard Car", "Business Car" };

	int tmpInt;
	cout << "\nOrigin Station" << endl;
	for (int i = 1; i < 13; i++)
		cout << setw(2) << i << '.' << stations[i] << endl;
	cout << "?";
	cin >> tmpInt;
	reservation.setOriginStation(tmpInt);
	cout << "\nDestination Station" << endl;
	for (int i = 1; i < 13; i++)
		cout << setw(2) << i << '.' << stations[i] << endl;
	cout << "?";
	cin >> tmpInt;
	if (reservation.getOriginStation() == tmpInt)
	{
		cout << "\nDestination station can't same as origin station. Please try again." << endl;
		inputReservationDetails(departureTime);
	}
	reservation.setDestinationStation(tmpInt);

	cout << "\nCar Class" << endl << "1. " << car[1] << endl << "2. " << car[2] << endl << "? ";
	cin >> tmpInt;
	while (tmpInt != 1 && tmpInt != 2)
	{
		cout << "\nWrong value of the car class. Please try again." << endl;
		cout << "\nCar Class" << endl << "1. " << car[1] << endl << "2. " << car[2] << endl << "? ";
		cin >> tmpInt;
	}
	reservation.setCarClass(tmpInt);

	string dd = "";
	cout << "\nDeparture Date: ";
	cin >> dd;
	reservation.setDate(dd);

	cout << endl;
	for (int i = 1; i < 35; i++)
		cout << setw(2) << i << ". " << departureTimes[i] << endl;
	cout << "\nEnter Departure Time Code: ";
	cin >> departureTime;
	while (departureTime < 1 || departureTime > 34)
	{
		cout << "\nWrong value of the time code. Please try again." << endl;
		for (int i = 1; i < 35; i++)
			cout << setw(2) << i << ". " << departureTimes[i] << endl;
		cout << "\nEnter Departure Time Code: ";
		cin >> departureTime;
	}
	cout << "\nHow many adult tickets? ";
	cin >> tmpInt;
	while (tmpInt < 0)
	{
		cout << "\nValue of tickets can't less than zero. Please try again." << endl;
		cout << "\nHow many adult tickets? ";
		cin >> tmpInt;
	}
	reservation.setAdultTickets(tmpInt);
	cout << "\nHow many concession tickets? ";
	cin >> tmpInt;
	while (tmpInt < 0)
	{
		cout << "\nValue of tickets can't less than zero. Please try again." << endl;
		cout << "\nHow many concession tickets? ";
		cin >> tmpInt;
	}
	reservation.setConcessionTickets(tmpInt);	
}
// displays timetables for 5 coming trains, then let user choose a train
void MakingReservation::chooseTrain(int departureTime)
{
	string Tnum = "";
	if (reservation.getOriginStation() < reservation.getDestinationStation())
		southboundTimetable.displayComingTrains(departureTime, reservation.getOriginStation(), reservation.getDestinationStation());
	else
		northboundTimetable.displayComingTrains(departureTime, reservation.getOriginStation(), reservation.getDestinationStation());
	cout << "\nEnter Train Number: ";
	cin >> Tnum;
	reservation.setTrainNumber(Tnum);
}
// inputs idNumber and phone, and randomly generate reservationNumber
void MakingReservation::inputContactPersonInfo()
{
	cout << "\nEnter Contact Person Information" << endl;
	string tmp = "";
	cout << "\nID Number : ";
	cin >> tmp;
	reservation.setIdNumber(tmp);
	cout << "Phone Number : ";
	cin >> tmp;
	reservation.setPhone(tmp);
	srand(static_cast< unsigned int >(time(0)));
	string randonNum = "";
	for (int k = 0; k < 8; k++)
		randonNum += rand() % 10 + '0';
	reservation.setReservationNumber(randonNum);
	cout << "\nReservation Number: " << randonNum << endl;
}