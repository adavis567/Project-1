#ifndef RESERVATIONMANAGER_H
#define RESERVATIONMANAGER_H

#include "reservation.h"
#include <string>
using namespace std;

class ReservationManager {
private:
    struct Node {
        Reservation reservation;
        Node* next;

        Node(const Reservation& reservation) {
            this->reservation = reservation;
            next = nullptr;
        }
    };

    Node* head;
    int reservationCount;

public:
    ReservationManager();
    ~ReservationManager();

    bool insertReservation(const Reservation& reservation);
    bool removeReservation(int reservationID);
    Reservation* findReservation(int reservationID);
    void displayReservations() const;

    bool reservationExists(int reservationID) const;
    bool studentHasReservation(int studentID) const;
    bool resourceIsReserved(string resourceID) const;

    int getReservationCount() const;
    bool isEmpty() const;

    void clear();
};

#endif
