#include "reservation.h"
#include <iostream>

using namespace std;

Reservation::Reservation() {
    reservationID = 0;
    studentID = 0;
    studentName = "";
    resourceID = "";
    reservationDate = "";
}

Reservation::Reservation(int reservationID, int studentID, string studentName,
                         string resourceID, string reservationDate) {
    this->reservationID = reservationID;
    this->studentID = studentID;
    this->studentName = studentName;
    this->resourceID = resourceID;
    this->reservationDate = reservationDate;
}

int Reservation::getReservationID() const {
    return reservationID;
}

int Reservation::getStudentID() const {
    return studentID;
}

string Reservation::getStudentName() const {
    return studentName;
}

string Reservation::getResourceID() const {
    return resourceID;
}

string Reservation::getReservationDate() const {
    return reservationDate;
}

void Reservation::setReservationID(int reservationID) {
    this->reservationID = reservationID;
}

void Reservation::setStudentID(int studentID) {
    this->studentID = studentID;
}

void Reservation::setStudentName(string studentName) {
    this->studentName = studentName;
}

void Reservation::setResourceID(string resourceID) {
    this->resourceID = resourceID;
}

void Reservation::setReservationDate(string reservationDate) {
    this->reservationDate = reservationDate;
}

void Reservation::display() const {
    cout << "Reservation ID: " << reservationID << endl;
    cout << "Student ID: " << studentID << endl;
    cout << "Student Name: " << studentName << endl;
    cout << "Resource ID: " << resourceID << endl;
    cout << "Reservation Date: " << reservationDate << endl;
}
