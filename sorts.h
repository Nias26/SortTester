#ifndef H_SORTS
#define H_SORTS
#include <chrono>
#include <iostream>

class HAHAHA_ORA_NON_VEDRAI_NESSUN_SORT_HAHAHA {};

class Sort {
public:
  virtual long long callSort(int *arr, const int &SIZE) = 0;
  virtual std::string getSortName() const = 0;

protected:
  std::string sortName;
};

class BubbleSort : public Sort {
public:
  BubbleSort() { sortName = "Bubble Sort"; }
  long long callSort(int *arr, const int &SIZE) override;
  std::string getSortName() const override { return sortName; }
};

class SelectionSort : public Sort {
public:
  SelectionSort() { sortName = "Selection Sort"; }
  std::string sortName = "Selection Sort";
  long long callSort(int *arr, const int &SIZE) override;
  std::string getSortName() const override { return sortName; }
};

class InsertionSort : public Sort {
public:
  InsertionSort() { sortName = "Insertion Sort"; }
  std::string sortName = "Insertion Sort";
  long long callSort(int *arr, const int &SIZE) override;
  std::string getSortName() const override { return sortName; }
};

class MergeSort : public Sort {
public:
  MergeSort() { sortName = "Merge Sort"; }
  std::string sortName = "Merge Sort";
  long long callSort(int *arr, const int &SIZE) override;
  std::string getSortName() const override { return sortName; }
};

class LomutoQuickSort : public Sort {
public:
  LomutoQuickSort() { sortName = "Lomuto Quick Sort"; }
  std::string sortName = "Lomuto's Quick Sort";
  long long callSort(int *arr, const int &SIZE) override;
  std::string getSortName() const override { return sortName; }
};

class HoareQuickSort : public Sort {
public:
  HoareQuickSort() { sortName = "Hoare Quick Sort"; }
  std::string sortName = "Hoare's Quick Sort";
  long long callSort(int *arr, const int &SIZE) override;
  std::string getSortName() const override { return sortName; }
};

bool sorted(int *arr, const int &SIZE);

#endif
