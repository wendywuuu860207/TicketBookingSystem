#include <iostream>
#include "ReservationHistory.h" // ReservationHistory class definition
#include "MakingReservation.h" // MakingReservation class definition

string departureTimes[ 37 ] = { "",
   "06:00", "06:30", "07:00", "07:30", "08:00", "08:30", "09:00", "09:30",
   "10:00", "10:30", "11:00", "11:30", "12:00", "12:30", "13:00", "13:30",
   "14:00", "14:30", "15:00", "15:30", "16:00", "16:30", "17:00", "17:30",
   "18:00", "18:30", "19:00", "19:30", "20:00", "20:30", "21:00", "21:30",
   "22:00", "22:30", "23:00", "23:30" };

int enterChoice();

int main()
{
   cout << "Taiwan High Speed Rail Booking System\n";

   SouthboundTimetable southboundTimetable;
   NorthboundTimetable northboundTimetable;
   ReservationDatabase reservationDatabase;
   MakingReservation makingReservation( reservationDatabase, southboundTimetable, northboundTimetable );
   ReservationHistory reservationHistory( reservationDatabase, southboundTimetable, northboundTimetable );

   int choice;
   while ( ( choice = enterChoice() ) != 3 )
   {
      switch ( choice )
      {
      case 1:
         makingReservation.execute();
         break;
      case 2:
         reservationHistory.execute();
         break;
      default:
         cerr << "Incorrect Choice" << endl;
         break;
      }
   }

   system("pause");
}

int enterChoice()
{
   cout << "\nEnter Your Choice\n"
      << "1. Booking\n"
      << "2. Booking History\n"
      << "3. End Program\n? ";

   int menuChoice;
   cin >> menuChoice;
   return menuChoice;
}