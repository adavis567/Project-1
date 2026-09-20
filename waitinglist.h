#ifndef WAITINGLIST_H
#define WAITINGLIST_H

#include <string>
#include <iostream>

using namespace std;

struct WaitingNode {
    int reservationID;
    string studentID;
    string studentName;
    string resourceID;
    string reservationDate;
    WaitingNode* next;

    WaitingNode(int rid, const string& sid, const string& sname,
                const string& resource, const string& date)
        : reservationID(rid),
          studentID(sid),
          studentName(sname),
          resourceID(resource),
          reservationDate(date),
          next(nullptr) {}
};

class WaitingList {
private:
    WaitingNode* front;
    WaitingNode* rear;

public:
    WaitingList();
    ~WaitingList();

    bool isEmpty() const;

    void enqueue(int reservationID,
                 const string& studentID,
                 const string& studentName,
                 const string& resourceID,
                 const string& reservationDate);

    void dequeue();

    WaitingNode* peek() const;

    void display() const;

    void clear();
};

#endif