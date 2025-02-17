#include "sorts.h"

long long BubbleSort::callSort(int *arr, const int &SIZE) {
  auto sortStart = std::chrono::high_resolution_clock::now();
  bool stop;
  do {
    stop = true;
    for (int i = 0; i < SIZE; ++i) {
      if (arr[i] > arr[i + 1]) {
        std::swap(arr[i], arr[i + 1]);
        stop = false;
      }
    }

  } while (!stop);
  auto sortStop = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::nanoseconds>(sortStop -
                                                              sortStart)
      .count();
}

long long SelectionSort::callSort(int *arr, const int &SIZE) {
  auto sortStart = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < SIZE; ++i) {
    int min = i;
    for (int j = i + 1; j < SIZE; ++j) {
      if (arr[j] < arr[min]) {
        min = j;
      }
    }
    if (min != i) {
      std::swap(arr[min], arr[i]);
    }
  }
  auto sortStop = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::nanoseconds>(sortStop -
                                                              sortStart)
      .count();
}

long long InsertionSort::callSort(int *arr, const int &SIZE) {
  auto sortStart = std::chrono::high_resolution_clock::now();
  for (int i = 1; i < SIZE; ++i) {
    int val = arr[i], j = i - 1;
    while (j >= 0 && arr[j] > val) {
      arr[j + 1] = arr[j];
      --j;
    }
    arr[j + 1] = val;
  }
  auto sortStop = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::nanoseconds>(sortStop -
                                                              sortStart)
      .count();
}

void merge(int *arr, const int &start, const int &middle, const int &end) {
  int n1 = middle - start + 1;
  int n2 = end - middle;

  int arr1[n1], arr2[n2];
  for (int i = 0; i < n1; ++i) {
    arr1[i] = arr[start + i];
  }
  for (int i = 0; i < n2; ++i) {
    arr2[i] = arr[middle + 1 + i];
  }

  int i1 = 0, i2 = 0, i3 = start;

  while (i1 < n1 && i2 < n2) {
    if (arr1[i1] < arr2[i2]) {
      arr[i3] = arr1[i1];
      i1++;
    } else {
      arr[i3] = arr2[i2];
      ++i2;
    }
    ++i3;
  }

  while (i1 < n1) {
    arr[i3] = arr1[i1];
    ++i1;
    ++i3;
  }

  while (i2 < n2) {
    arr[i3] = arr2[i2];
    ++i2;
    ++i3;
  }
}

void mergeSort(int *arr, const int start, const int end) {
  if (start < end) {
    int middle = start + (end - start) / 2;
    mergeSort(arr, start, middle);
    mergeSort(arr, middle + 1, end);
    merge(arr, start, middle, end);
  }
  return;
}

long long MergeSort::callSort(int *arr, const int &SIZE) {
  auto sortStart = std::chrono::high_resolution_clock::now();
  mergeSort(arr, 0, SIZE - 1);
  auto sortStop = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::nanoseconds>(sortStop -
                                                              sortStart)
      .count();
}

int lomutoPartition(int *arr, const int &start, const int &end) {
  int pivot = arr[end];
  int i = start - 1;

  for (int j = start; j <= end - 1; ++j) {
    if (arr[j] < pivot) {
      ++i;
      std::swap(arr[i], arr[j]);
    }
  }
  std::swap(arr[i + 1], arr[end]);

  return i + 1;
}

int hoarePartition(int *arr, const int &start, const int &end) {
  int pivot = arr[start];
  int i = start - 1, j = end + 1;

  while (true) {
    do {
      ++i;
    } while (arr[i] < pivot);

    do {
      --j;
    } while (arr[j] > pivot);

    if (i >= j)
      return j;

    std::swap(arr[i], arr[j]);
  }
}

void lomutoQuickSort(int *arr, const int &start, const int &end) {
  if (start < end) {
    int pi = lomutoPartition(arr, start, end);

    lomutoQuickSort(arr, start, pi - 1);
    lomutoQuickSort(arr, pi + 1, end);
  }
  return;
}

void hoareQuickSort(int *arr, const int &start, const int &end) {
  if (start < end) {
    int pi = hoarePartition(arr, start, end);

    hoareQuickSort(arr, start, pi);
    hoareQuickSort(arr, pi + 1, end);
  }
  return;
}

long long LomutoQuickSort::callSort(int *arr, const int &SIZE) {
  auto sortStart = std::chrono::high_resolution_clock::now();
  lomutoQuickSort(arr, 0, SIZE - 1);
  auto sortStop = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::nanoseconds>(sortStop -
                                                              sortStart)
      .count();
}

long long HoareQuickSort::callSort(int *arr, const int &SIZE) {
  auto sortStart = std::chrono::high_resolution_clock::now();
  hoareQuickSort(arr, 0, SIZE - 1);
  auto sortStop = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::nanoseconds>(sortStop -
                                                              sortStart)
      .count();
}

bool sorted(int *arr, const int &SIZE) {
  for (int i = 0; i < SIZE - 1; ++i) {
    if (arr[i] > arr[i + 1]) {
      return false;
    }
  }
  return true;
}
