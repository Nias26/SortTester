#include <chrono>
#include <iostream>
#include <random>
#include <thread>

#define SIZE 10000

void bsort1(int arr[], int *tResult) {
  auto bsortT1Start = std::chrono::high_resolution_clock::now();
  bool stop;
  do {
    stop = true;
    for (int i = 0; i < SIZE - 1; ++i) {
      if (arr[i] > arr[i + 1]) {
        int temp = arr[i];
        arr[i] = arr[i + 1];
        arr[i + 1] = temp;
        stop = false;
      }
    }
  } while (!stop);
  auto bsortT1Stop = std::chrono::high_resolution_clock::now();
  *tResult = std::chrono::duration_cast<std::chrono::nanoseconds>(bsortT1Stop -
                                                                  bsortT1Start)
                 .count();
}

void bsort2(int arr[], int *tResult) {
  auto bsortT2Start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < SIZE; ++i) {
    for (int j = 0; j < SIZE - 1; ++j) {
      if (arr[j] > arr[j + 1]) {
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
  auto bsortT2Stop = std::chrono::high_resolution_clock::now();
  *tResult = std::chrono::duration_cast<std::chrono::nanoseconds>(bsortT2Stop -
                                                                  bsortT2Start)
                 .count();
}

int main() {
  for (int m = 0; m < 5; ++m) {
    std::cout << "Test n." << m + 1 << std::endl;
    int num1[SIZE];
    int num2[SIZE];

    int result1, result2;

    auto seed = std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::system_clock::now().time_since_epoch())
                    .count();
    std::mt19937 mtG(seed);
    std::uniform_int_distribution<int> rand(1, 100);
    for (int i = 0; i < SIZE; ++i) {
      num1[i] = rand(mtG);
      num2[i] = num1[i];
    }

    std::thread t1(bsort1, num1, &result1);
    std::thread t2(bsort2, num2, &result2);
    t1.join();
    t2.join();

    std::cout << "Bsort1: ";
    std::cout << std::endl << "Time: " << result1 << "ns" << std::endl;

    std::cout << "Bsort2: ";
    std::cout << std::endl << "Time: " << result2 << "ns" << std::endl;

    std::cout << std::endl;
  }
  return 0;
}
