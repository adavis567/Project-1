#include "reservationManager.h"
#include <iostream>

using namespace std;

ReservationManager::ReservationManager() {
    head = nullptr;
    reservationCount = 0;
}

ReservationManager::~ReservationManager() {
    clear();
}

bool ReservationManager::insertReservation(const Reservation& reservation) {
    if (reservationExists(reservation.getReservationID())) {
        return false;
    }

    Node* newNode = new Node(reservation);

    if (head == nullptr) {
        head = newNode;
    }
    else {
        Node* current = head;

        while (current->next != nullptr) {
            current = current->next;
        }

        current->next = newNode;
    }

    reservationCount++;
    return true;
}

bool ReservationManager::removeReservation(int reservationID) {
    if (head == nullptr) {
        return false;
    }

    if (head->reservation.getReservationID() == reservationID) {
        Node* temp = head;
        head = head->next;

        delete temp;
        reservationCount--;

        return true;
    }

    Node* current = head;

    while (current->next != nullptr) {
        if (current->next->reservation.getReservationID() == reservationID) {
            Node* temp = current->next;
            current->next = current->next->next;

            delete temp;
            reservationCount--;

            return true;
        }

        current = current->next;
    }

    return false;
}

Reservation* ReservationManager::findReservation(int reservationID) {
    Node* current = head;

    while (current != nullptr) {
        if (current->reservation.getReservationID() == reservationID) {
            return &current->reservation;
        }

        current = current->next;
    }

    return nullptr;
}

void ReservationManager::displayReservations() const {
    if (head == nullptr) {
        cout << "No active reservations." << endl;
        return;
    }

    Node* current = head;

    cout << "\n===== Active Reservations =====" << endl;

    while (current != nullptr) {
        current->reservation.display();
        cout << "-----------------------------" << endl;

        current = current->next;
    }
}

bool ReservationManager::reservationExists(int reservationID) const {
    Node* current = head;

    while (current != nullptr) {
        if (current->reservation.getReservationID() == reservationID) {
            return true;
        }

        current = current->next;
    }

    return false;
}

bool ReservationManager::studentHasReservation(int studentID) const {
    Node* current = head;

    while (current != nullptr) {
        if (current->reservation.getStudentID() == studentID) {
            return true;
        }

        current = current->next;
    }

    return false;
}

bool ReservationManager::resourceIsReserved(string resourceID) const {
    Node* current = head;

    while (current != nullptr) {
        if (current->reservation.getResourceID() == resourceID) {
            return true;
        }

        current = current->next;
    }

    return false;
}

int ReservationManager::getReservationCount() const {
    return reservationCount;
}

bool ReservationManager::isEmpty() const {
    return head == nullptr;
}

void ReservationManager::clear() {
    Node* current = head;

    while (current != nullptr) {
        Node* temp = current;
        current = current->next;

        delete temp;
    }

    head = nullptr;
    reservationCount = 0;
}
