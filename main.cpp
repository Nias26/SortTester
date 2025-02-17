#include "sorts.h"
#include <cmath>
#include <future>
#include <iostream>
#include <random>

// Set arrays size
#define SIZE 10000

struct Obj {
  Sort *ptr = nullptr;
  Obj(Sort *ptr) : ptr{ptr} {}
};

struct Colors {
  inline static const std::string Red = "\x1b[31m";
  inline static const std::string Green = "\x1b[32m";
  inline static const std::string Yellow = "\x1b[33m";
  inline static const std::string Reset = "\x1b[0m";
};

int main() {
  // Random device seed
  std::random_device rd;
  // Mersenne Twister Engine
  std::mt19937 mtG(rd());
  // Generate numbers from 1 to 100
  std::uniform_int_distribution<> distrib(1, 100);
  // Set BoolAlpha
  std::cout << std::boolalpha;
  // Colors
  Colors Colors;

  int m;
  std::cout << "Numero di test da eseguire: ";
  std::cin >> m;

  // Initialize new arrays
  int *num1 = new int[SIZE];
  int *num2 = new int[SIZE];

  int choice[2];
  std::cout << "Seleziona il sort:" << std::endl
            << "1. BubbleSort" << std::endl
            << "2. SelectionSort" << std::endl
            << "3. InsertionSort" << std::endl
            << "4. MergeSort" << std::endl
            << "5. Lomuto's QuickSort" << std::endl
            << "6. Hoare's QuickSort" << std::endl;
  std::cout << "1 Sort-> ";
  std::cin >> choice[0];
  std::cout << "2 Sort-> ";
  std::cin >> choice[1];

  // Lambda to get sorts functions addresses
  auto selectSort = [](const int &choice) {
    switch (choice) {
    case 1: {
      BubbleSort *bSort = new BubbleSort;
      return Obj{bSort};
      break;
    }
    case 2: {
      SelectionSort *sSort = new SelectionSort;
      return Obj{sSort};
      break;
    }
    case 3: {
      InsertionSort *iSort = new InsertionSort;
      return Obj{iSort};
      break;
    }
    case 4: {
      MergeSort *mSort = new MergeSort;
      return Obj{mSort};
      break;
    }
    case 5: {
      LomutoQuickSort *lQSort = new LomutoQuickSort;
      return Obj{lQSort};
      break;
    }
    case 6: {
      HoareQuickSort *hQSort = new HoareQuickSort;
      return Obj{hQSort};
      break;
    }
    default: {
      std::cerr << "Scelta errata. Ora pagherai le conseguenze..." << std::endl;
      throw HAHAHA_ORA_NON_VEDRAI_NESSUN_SORT_HAHAHA();
    }
    }
  };

  Obj obj1 = selectSort(choice[0]);
  Obj obj2 = selectSort(choice[1]);

  // Main loop
  std::cout << std::endl;
  for (int i = 0; i < m; ++i) {
    std::cout << "Test n." << i + 1 << std::endl;

    // Fill the arrays
    for (int i = 0; i < SIZE; ++i) {
      num1[i] = distrib(mtG);
      num2[i] = num1[i];
    }

    // Start async threads
    auto sort1Time = std::async(&Sort::callSort, obj1.ptr, num1, SIZE);
    auto sort2Time = std::async(&Sort::callSort, obj2.ptr, num2, SIZE);

    // Wait for them to finish
    sort1Time.wait();
    sort2Time.wait();

    long long time1 = sort1Time.get();
    long long time2 = sort2Time.get();

    // Convert time from nanoseonds to milliseconds
    auto timeToMilliseconds = [](const long long &time) {
      return time / pow(10, 6);
    };

    // Get results and print to screen
    std::cout << Colors::Red << obj1.ptr->getSortName() << ":" << std::endl
              << Colors::Green << "\tTime: " << Colors::Reset << time1 << "ns, "
              << timeToMilliseconds(time1) << "ms" << std::endl
              << Colors::Yellow << "\tSorted? " << Colors::Reset
              << sorted(num1, SIZE) << std::endl
              << std::endl;

    std::cout << Colors::Red << obj2.ptr->getSortName() << ":" << std::endl
              << Colors::Green << "\tTime: " << Colors::Reset << time2 << "ns, "
              << timeToMilliseconds(time2) << "ms" << std::endl
              << Colors::Yellow << "\tSorted? " << Colors::Reset
              << sorted(num2, SIZE) << std::endl
              << std::endl;

    std::cout << "---------------------------------------" << std::endl;
  }

  // Clean up the mess
  delete[] num1;
  delete[] num2;
  num1 = nullptr;
  num2 = nullptr;

  delete obj1.ptr;
  delete obj2.ptr;
  obj1.ptr = nullptr;
  obj2.ptr = nullptr;

  return 0;
}
