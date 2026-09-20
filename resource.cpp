#include "Resource.h"

Resource::Resource()
  : resourceID(""), resourceName(""), resourceType(""), isAvailable(true) {}
Resource::Resource(const std::string& id, const std::string& name,
                    const std::string& type, bool available)
  : resourceID(id), resourceName(name), resourceType(type), isAvailable(available) {}
std::string Resource::getID() const { return resourceID; }
std::string Resource::getName() const {return resourceName; }
std::string Resource::getType() const { return resourceType; }
bool Resource::getAvailability() const { return isAvailable; }

void Resource::setAvailability(bool status) {
  isAvailable = status;
}

void Resource::display() const {
  std::cout << resourceID << " | " 
            << resourceName << " | "
            << resourceType << " | "
            << (isAvailable ? "Available" : "Unavailable")
            << std::endl;
}
