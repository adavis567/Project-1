#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
#include <iostream>


class Rescource {
private:
  std::string resourceID;
  std::string resourceName;
  std::string resourceType;
  bool isAvailabe;
public:
  Resource();
  Resource(const std::string& id, const std::string& name,
            const std::string& type, bool available);

  std::string getID() const;
  std::string getName() const;
  std::string getType() const;
  bool getAvailablility() const;

  void setAvailability(bool status);
  void display() const;
};

#endif 
