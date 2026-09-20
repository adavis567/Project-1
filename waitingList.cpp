#include "waitinglist.h"

using namespace std;

WaitingList::WaitingList()
    : front(nullptr), rear(nullptr)
{
}

WaitingList::~WaitingList()
{
    clear();
}

bool WaitingList::isEmpty() const
{
    return front == nullptr;
}

void WaitingList::enqueue(int reservationID,
                          const string& studentID,
                          const string& studentName,
                          const string& resourceID,
                          const string& reservationDate)
{
    WaitingNode* newNode = new WaitingNode(
        reservationID,
        studentID,
        studentName,
        resourceID,
        reservationDate
    );

    if (isEmpty())
    {
        front = rear = newNode;
    }
    else
    {
        rear->next = newNode;
        rear = newNode;
    }
}

void WaitingList::dequeue()
{
    if (isEmpty())
    {
        cout << "Waiting list is empty." << endl;
        return;
    }

    WaitingNode* temp = front;
    front = front->next;

    if (front == nullptr)
    {
        rear = nullptr;
    }

    delete temp;
}

WaitingNode* WaitingList::peek() const
{
    return front;
}

void WaitingList::display() const
{
    if (isEmpty())
    {
        cout << "Waiting list is empty." << endl;
        return;
    }

    cout << "\n===== Waiting List =====" << endl;

    WaitingNode* current = front;

    while (current != nullptr)
    {
        cout << "Reservation ID: " << current->reservationID << endl;
        cout << "Student ID: " << current->studentID << endl;
        cout << "Student Name: " << current->studentName << endl;
        cout << "Resource ID: " << current->resourceID << endl;
        cout << "Reservation Date: " << current->reservationDate << endl;
        cout << "-----------------------------" << endl;

        current = current->next;
    }
}

void WaitingList::clear()
{
    while (!isEmpty())
    {
        dequeue();
    }
}