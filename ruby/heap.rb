require 'profile'

def maxHeapify(a, i, heapsize)
  if heapsize > a.length
    return -1
  end
  largest = i
  while i < heapsize
    left = 2 * i + 1
    if left < heapsize and a[left] > a[i]
      largest = left
    end
    right = left + 1
    if right < heapsize and a[largest] < a[right]
      largest = right
    end
    
    if largest == i
      return -1
    end
    
    tmp = a[largest]
    a[largest] = a[i]
    a[i] = tmp
    i = largest
  end  
end

def buildMaxHeap(a)
  i = a.length / 2 - 1
  while i >= 0
    maxHeapify(a, i, a.length)
    i = i - 1
  end
end

def heapSort(a)
  buildMaxHeap(a)
  i = a.length - 1
  while i > 0
    tmp = a[i]
    a[i] = a[0]
    a[0] = tmp
    maxHeapify(a, 0, i)
    i = i - 1
  end
end

arr = [5, 3, 17, 10, 84, 19, 6, 22, 9]
2000.times do |i|
  arr << Random.rand(8000)
end
#arr = 0
#buildMaxHeap(arr)
heapSort(arr)
#puts arr