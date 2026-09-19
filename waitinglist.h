#ifndef WAITINGLIST_H
#define WAITINGLIST_H

#include <string>
#include <iostream>

struct WaitingNode {
  std::string studentID;
  std::string studentName;
  std::string resourceID;
  WaitingNode* next;

  WaitingNode(const std::string& sid, const std::string& sname,
              const std::string& rid)
    : studentID(sid), studentName(sname), resourceID(rid), next(nullptr) {}
};

class WaitingList {
private: 
  WaitingNode* front;
  WaitingNode* rear;
public:
  WaitingList();
  bool isEmpty() const;
  void enqueue(const std::string& studentID,
              const std::string& studentName,
              const std::string& resourceID);
  void dequeue();
  WaitingNode* peek() const;
  void display() const;
};
#endif
