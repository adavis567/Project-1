#include "cancellationHistory.h"
#include <iostream>

using namespace std;
void CancellationHistory::addCancellation(const Reservation& reservation)
{
    cancellationStack.push(reservation);
}
bool CancellationHistory::undoCancellation(Reservation& reservation)
{
    if (cancellationStack.empty())
    {
        return false;
    }

    reservation = cancellationStack.top();
    cancellationStack.pop();

    return true;
}

