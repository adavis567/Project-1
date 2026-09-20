#ifndef CANCELLATIONHISTORY_H
#define CANCELLATIONHISTORY_H

#include <stack>
#include "reservation.h"

using namespace std;

class CancellationHistory {
private:
    stack<Reservation> cancellationStack;

public:
    void addCancellation(const Reservation& reservation);
    bool undoCancellation(Reservation& reservation);
    void displayHistory() const;
    bool isEmpty() const;
};

#endif