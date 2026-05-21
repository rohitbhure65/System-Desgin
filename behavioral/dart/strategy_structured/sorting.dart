import 'interfaces.dart';

class BubbleSort implements SortingStrategy {
  @override
  void sort(List<int> data) {
    print('Using Bubble Sort...');
    final n = data.length;
    for (int i = 0; i < n - 1; i++) {
      for (int j = 0; j < n - i - 1; j++) {
        if (data[j] > data[j + 1]) {
          final temp = data[j];
          data[j] = data[j + 1];
          data[j + 1] = temp;
        }
      }
    }
  }
}

class QuickSort implements SortingStrategy {
  @override
  void sort(List<int> data) {
    print('Using Quick Sort...');
    _quickSort(data, 0, data.length - 1);
  }
  
  void _quickSort(List<int> data, int low, int high) {
    if (low < high) {
      final pi = _partition(data, low, high);
      _quickSort(data, low, pi - 1);
      _quickSort(data, pi + 1, high);
    }
  }
  
  int _partition(List<int> data, int low, int high) {
    final pivot = data[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
      if (data[j] < pivot) {
        i++;
        final temp = data[i];
        data[i] = data[j];
        data[j] = temp;
      }
    }
    final temp = data[i + 1];
    data[i + 1] = data[high];
    data[high] = temp;
    return i + 1;
  }
}

class MergeSort implements SortingStrategy {
  @override
  void sort(List<int> data) {
    print('Using Merge Sort...');
    _mergeSort(data, 0, data.length - 1);
  }
  
  void _mergeSort(List<int> data, int left, int right) {
    if (left < right) {
      final mid = left + (right - left) ~/ 2;
      _mergeSort(data, left, mid);
      _mergeSort(data, mid + 1, right);
      _merge(data, left, mid, right);
    }
  }
  
  void _merge(List<int> data, int left, int mid, int right) {
    final n1 = mid - left + 1;
    final n2 = right - mid;
    
    final L = data.sublist(left, left + n1);
    final R = data.sublist(mid + 1, mid + 1 + n2);
    
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
}

class Sorter {
  SortingStrategy? _strategy;
  
  void setSortingStrategy(SortingStrategy strategy) {
    _strategy = strategy;
  }
  
  void sortData(List<int> data) {
    print('\nOriginal data: ${data.join(' ')}');
    
    if (_strategy != null) {
      _strategy!.sort(data);
    } else {
      print('No sorting strategy selected');
    }
    
    print('Sorted data: ${data.join(' ')}');
  }
}
