#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
#include <iostream>


class Resource {
private:
  std::string resourceID;
  std::string resourceName;
  std::string resourceType;
  bool isAvailable;
public:
  Resource();
  Resource(const std::string& id, const std::string& name,
            const std::string& type, bool available);

  std::string getID() const;
  std::string getName() const;
  std::string getType() const;
  bool getAvailability() const;

  void setAvailability(bool status);
  void display() const;
};

#endif 
