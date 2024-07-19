#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include<algorithm>



// Bubble Sort
void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Quick Sort
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Merge Sort
void merge(std::vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; ++i)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        }
        else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

void mergeSort(std::vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

std::vector<int> generateRandomVector(int size) 
{
    std::vector<int> arr(size);
    for (int i = 0; i < size; ++i)
    {
        arr[i] = rand() % size; 
    }
    return arr;
}

//Insertion Sort
void insertionSort(std::vector<int>& arr)
{
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;

        // Перемещаем элементы массива arr[0..i-1], которые больше чем key, на одну позицию вперед от текущей позиции

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

//Selection Sort
void selectionSort(std::vector<int>& arr) {
    int n = arr.size();
    // Проходим по всем элементам массива, кроме последнего
    for (int i = 0; i < n - 1; ++i) 
    {
        // Находим индекс наименьшего элемента в неотсортированной части
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        // Обмениваем наименьший элемент с первым элементом неотсортированной части
        std::swap(arr[minIndex], arr[i]);
    }
}

//Radix Sort
// Функция для нахождения максимального значения в массиве
int getMax(std::vector<int>& arr) {
    int max = arr[0];
    for (int i = 1; i < arr.size(); ++i) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

// Функция для поразрядной сортировки массива по указанному разряду (digit)
void countSort(std::vector<int>& arr, int exp) {
    int n = arr.size();
    std::vector<int> output(n);
    std::vector<int> count(10, 0); // массив для подсчета частоты цифр

    // Подсчет частоты цифр
    for (int i = 0; i < n; ++i) {
        count[(arr[i] / exp) % 10]++;
    }

    // Преобразование count[i] так, чтобы оно содержало
    // фактическую позицию этой цифры в output
    for (int i = 1; i < 10; ++i) {
        count[i] += count[i - 1];
    }

    // Построение output массива
    for (int i = n - 1; i >= 0; --i) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // Копирование отсортированных элементов в массив arr
    for (int i = 0; i < n; ++i) {
        arr[i] = output[i];
    }
}

// Основная функция для поразрядной сортировки массива
void radixSort(std::vector<int>& arr) {
    int max = getMax(arr);

    // Проводим сортировку для каждого разряда числа, начиная с младшего
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countSort(arr, exp);
    }
}

int main() {
    srand(time(0));

    int size = 10000;
    //int size{ 100000 };
    
    // Сортировка в обратном порядке с использованием лямбда-функции
    // std::vector<int> arr(size);
    //std::sort(arr.begin(), arr.end(), [](int a, int b) { return a > b; });
    //Сортировка массива
    //std::sort(arr.begin(),arr.end());

    std::vector<int> arr = generateRandomVector(size);
    std::vector<int> arr_copy1 = arr;
    std::vector<int> arr_copy2 = arr;
    std::vector<int> arr_copy3 = arr;
    std::vector<int> arr_copy4 = arr;
    std::vector<int> arr_copy5 = arr;

    // Bubble Sort
    auto start = std::chrono::steady_clock::now();
    bubbleSort(arr);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Bubble Sort Time:         " << elapsed_seconds.count() << "s\n";

    // Quick Sort
    start = std::chrono::steady_clock::now();
    quickSort(arr_copy1, 0, size - 1);
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    std::cout << "Quick Sort Time:          " << elapsed_seconds.count() << "s\n";

    // Merge Sort
    start = std::chrono::steady_clock::now();
    mergeSort(arr_copy2, 0, size - 1);
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    std::cout << "Merge Sort Time:          " << elapsed_seconds.count() << "s\n";

    //Inserion Sort

    start = std::chrono::steady_clock::now();
    insertionSort(arr_copy3);
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    std::cout << "Insertion Sort Time:      " << elapsed_seconds.count() << "s\n";

    //Selection Sort
    start = std::chrono::steady_clock::now();
    selectionSort(arr_copy4);
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    std::cout << "Selection Sort Time:      " << elapsed_seconds.count() << "s\n";

    //Radix Sort
    start = std::chrono::steady_clock::now();
    radixSort(arr_copy5);
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    std::cout << "Radix Sort Time:          " << elapsed_seconds.count() << "s\n";

    return 0;
}
