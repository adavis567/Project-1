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
void CancellationHistory::displayHistory() const
{
    if (cancellationStack.empty())
{
    cout << "Cancellation history is empty." << endl;
    return;
}
stack<Reservation> temp = cancellationStack;

while (!temp.empty())
{
    temp.top().display();
    temp.pop();
}
bool CancellationHistory::isEmpty() const
{
    return cancellationStack.empty();
}

