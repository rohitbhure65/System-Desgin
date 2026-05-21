import { SortingStrategy } from './interfaces';

export class BubbleSort implements SortingStrategy {
  sort(data: number[]): void {
    console.log('Using Bubble Sort...');
    const n = data.length;
    for (let i = 0; i < n - 1; i++) {
      for (let j = 0; j < n - i - 1; j++) {
        if (data[j] > data[j + 1]) {
          [data[j], data[j + 1]] = [data[j + 1], data[j]];
        }
      }
    }
  }
}

export class QuickSort implements SortingStrategy {
  sort(data: number[]): void {
    console.log('Using Quick Sort...');
    this.quickSort(data, 0, data.length - 1);
  }
  
  private quickSort(data: number[], low: number, high: number): void {
    if (low < high) {
      const pi = this.partition(data, low, high);
      this.quickSort(data, low, pi - 1);
      this.quickSort(data, pi + 1, high);
    }
  }
  
  private partition(data: number[], low: number, high: number): number {
    const pivot = data[high];
    let i = low - 1;
    for (let j = low; j < high; j++) {
      if (data[j] < pivot) {
        i++;
        [data[i], data[j]] = [data[j], data[i]];
      }
    }
    [data[i + 1], data[high]] = [data[high], data[i + 1]];
    return i + 1;
  }
}

export class MergeSort implements SortingStrategy {
  sort(data: number[]): void {
    console.log('Using Merge Sort...');
    this.mergeSort(data, 0, data.length - 1);
  }
  
  private mergeSort(data: number[], left: number, right: number): void {
    if (left < right) {
      const mid = left + Math.floor((right - left) / 2);
      this.mergeSort(data, left, mid);
      this.mergeSort(data, mid + 1, right);
      this.merge(data, left, mid, right);
    }
  }
  
  private merge(data: number[], left: number, mid: number, right: number): void {
    const n1 = mid - left + 1;
    const n2 = right - mid;
    
    const L = data.slice(left, left + n1);
    const R = data.slice(mid + 1, mid + 1 + n2);
    
    let i = 0, j = 0, k = left;
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

export class Sorter {
  private strategy: SortingStrategy | null = null;
  
  setSortingStrategy(strategy: SortingStrategy): void {
    this.strategy = strategy;
  }
  
  sortData(data: number[]): void {
    console.log('\nOriginal data: ' + data.join(' '));
    
    if (this.strategy) {
      this.strategy.sort(data);
    } else {
      console.log('No sorting strategy selected');
    }
    
    console.log('Sorted data: ' + data.join(' '));
  }
}
