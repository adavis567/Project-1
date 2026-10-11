#include "ResourceSorter.h"

bool ResourceSorter::compare(const Resource& a, const Resource& b,
							const std::string& criteria) {
  if (criteria == "name")
	return a.getName() < b.getName();
  if (criteria == "type")
    return a.getType() < b.getType();
  if (criteria == "availability")
    return a.getAvailability() > b.getAvailability();
  return a.getID() < b.getID();
}

void ResourceSorter::merge(std::vector<Resource>& resources,
                          int left, int mid, int right,
                          const std::string& criteria) {
  int n1 = mid - left + 1;
  int n2 = right - mid;
  std::vector<Resource> L(n1);
  std::vector<Resource> R(n2);

  for (int i = 0; i < n1; i++)
    L[i] = resources[left + i];
  for (int j = 0; j < n2; j++)
    R[j] = resources[mid + 1 + j];
  int i = 0, j = 0, k = left;

  while (i < n1 && j < n2) {
      if (compare(L[i], R[j], criteria)) {
          resources[k] = L[i];
          i++;
      } else {
          resources[k] = R[j];
          j++;
      }
      k++;
  }

  while (i < n1) {
      resources[k] = L[i];
      i++;
      k++;
  }

  while (j < n2) {
      resources[k] = R[j];
      j++;
      k++;
  }
}

void ResourceSorter::mergeSortHelper(std::vector<Resource>& resources,
                                    int left, int right, const std::string& criteria) {
  if (left < right) {
      int mid = left + (right - left) / 2;
      mergeSortHelper(resources, left, mid, criteria);
      mergeSortHelper(resources, mid + 1, right, criteria);

      merge(resources, left, mid, right, criteria);
  }
}

void ResourceSorter::mergeSort(std::vector<Resource>& resources,
                              const std::string& criteria) {
  if (resources.empty()) return;
  mergeSortHelper(resources, 0, resources.size() - 1, criteria);
}
