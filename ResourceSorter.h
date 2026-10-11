#ifndef RESOURCESORTER_H
#define RESOURCESORTER_H

#include <vector>
#include "Resource.h"

class ResourceSorter {
public:
  static void mergeSort(std::vector<Resource>& resources,
                        const std::string& criteria);
private:
  static void merge(std::vector<Resource>& resources,
                    int left, int mid, int right,
                    const std::string& criteria);
  static bool compare(const Resource& a, const Resource& b,
                      const std::string& criteria);
  static void mergeSortHelper(std::vector<Resource>& resources,
                              int left, int right,
                              const std::string& criteria);
};
#endif
