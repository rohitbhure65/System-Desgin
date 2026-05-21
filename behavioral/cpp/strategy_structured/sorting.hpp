#pragma once
#include <vector>
#include <algorithm>
#include <memory>

class SortingStrategy {
public:
    virtual ~SortingStrategy() = default;
    virtual void sort(std::vector<int>& data) = 0;
};

class BubbleSort : public SortingStrategy {
public:
    void sort(std::vector<int>& data) override {
        std::cout << "Using Bubble Sort..." << std::endl;
        int n = data.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (data[j] > data[j + 1]) {
                    std::swap(data[j], data[j + 1]);
                }
            }
        }
    }
};

class QuickSort : public SortingStrategy {
public:
    void sort(std::vector<int>& data) override {
        std::cout << "Using Quick Sort..." << std::endl;
        quickSort(data, 0, data.size() - 1);
    }
    
private:
    void quickSort(std::vector<int>& data, int low, int high) {
        if (low < high) {
            int pi = partition(data, low, high);
            quickSort(data, low, pi - 1);
            quickSort(data, pi + 1, high);
        }
    }
    
    int partition(std::vector<int>& data, int low, int high) {
        int pivot = data[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (data[j] < pivot) {
                i++;
                std::swap(data[i], data[j]);
            }
        }
        std::swap(data[i + 1], data[high]);
        return i + 1;
    }
};

class MergeSort : public SortingStrategy {
public:
    void sort(std::vector<int>& data) override {
        std::cout << "Using Merge Sort..." << std::endl;
        mergeSort(data, 0, data.size() - 1);
    }
    
private:
    void mergeSort(std::vector<int>& data, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(data, left, mid);
            mergeSort(data, mid + 1, right);
            merge(data, left, mid, right);
        }
    }
    
    void merge(std::vector<int>& data, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;
        
        std::vector<int> L(n1), R(n2);
        
        for (int i = 0; i < n1; i++) L[i] = data[left + i];
        for (int j = 0; j < n2; j++) R[j] = data[mid + 1 + j];
        
        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                data[k++] = L[i++];
            } else {
                data[k++] = R[j++];
            }
        }
        
        while (i < n1) data[k++] = L[i++];
        while (j < n2) data[k++] = R[j++];
    }
};

class Sorter {
private:
    std::unique_ptr<SortingStrategy> strategy;
    
public:
    void setSortingStrategy(std::unique_ptr<SortingStrategy> strat) {
        strategy = std::move(strat);
    }
    
    void sortData(std::vector<int>& data) {
        std::cout << "\nOriginal data: ";
        for (int num : data) std::cout << num << " ";
        std::cout << std::endl;
        
        if (strategy) {
            strategy->sort(data);
        } else {
            std::cout << "No sorting strategy selected" << std::endl;
        }
        
        std::cout << "Sorted data: ";
        for (int num : data) std::cout << num << " ";
        std::cout << std::endl;
    }
};
