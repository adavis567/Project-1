#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>
using namespace std;

class Reservation {
private:
    int reservationID;
    int studentID;
    string studentName;
    string resourceID;
    string reservationDate;

public:
    Reservation();
    Reservation(int reservationID, int studentID, string studentName,
                string resourceID, string reservationDate);

    int getReservationID() const;
    int getStudentID() const;
    string getStudentName() const;
    string getResourceID() const;
    string getReservationDate() const;

    void setReservationID(int reservationID);
    void setStudentID(int studentID);
    void setStudentName(string studentName);
    void setResourceID(string resourceID);
    void setReservationDate(string reservationDate);

    void display() const;
};

#endif
