#include "WaitingList.h"

WaitingList::WaitingList() : front(nullptr), rear(nullptr) {}

bool WaitingList::isEmpty() const {
  return front == nullptr;
}

void WaitingList::enqueue(const std::string& studentID,
                          const std::string& studentName,
                          const std::string& resourceID) {
  WaitingNode* newNode = new WaitingNode(studentID, studentName, resourceID);
  if (isEmpty()) {
    front = rear = newNode;
  } else {
      rear->next = newNode;
      rear = newNode;
  }
}

void WaitingList::dequeue() {
  if (isEmpty()) {
      std::cout << "Waiting list is empty." << std::endl;
      return;
  }
  WaitingNode* temp = front;
  front = front->next;

  if (front == nullptr) {
      rear = nullptr;
  }
  delete temp;
}

void WaitingList::display() const {
  if (isEmpty()) {
      std::cout << "Waiting list is empty." << std::endl;
      return;
  }

  WaitingNode* curr = front;
  while (curr != nullptr) {
    std::cout << curr->studentID << " | "
              << curr->studentName << " | "
              << curr->resourceID << std::endl;
    curr = curr->next;
  }
}
int WaitingList::countByResource(const std::string& resourceID) const {
    int count = 0;
    WaitingNode* curr = front;

    while (curr != nullptr) {
        if (curr->resourceID == resourceID) {
            count++;
        }
        curr = curr->next;
    }

    return count;
}
