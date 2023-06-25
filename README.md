# K-ary Leftist Max Heap

This project implements a k-ary leftist max heap data structure in C++. The k-ary leftist max heap is a variant of a binary max heap where each parent node can have up to k child nodes. It satisfies the leftist property, which ensures that the rank (or distance to the nearest leaf) of the left child of any node is greater than or equal to the rank of its right child.

## Features

- Insertion: Insert a new element into the heap, maintaining the leftist property and the max heap property.
- Deletion: Remove the maximum element (root node) from the heap, adjusting the tree structure to maintain the leftist and max heap properties.
- Find-Max: Retrieve the maximum element (root node) of the heap without removing it.
- Sort: Sorting Elements of an array or list using leftist max heap.
- Priority-List: Implementation of a Priority List using Max heap, Linked List and a Queue. 
## Usage

To use the k-ary leftist max heap in your C++ project, follow these steps:

1. Include the "DLL.h" header file and the "Heap.h" file in your project.
```cpp
#include "DLL.h"
#include "Heap.h"
 ```
2. Create a new instance of the Heap class, specifying the desired k-ary value. For example, to create a 3-ary leftist max heap:
```
Heap<int> heap(3); 
```
  
3. Use the available methods to interact with the heap. Some common operations include:
```cpp
// Insert elements
heap.insert(10);
heap.insert(20);
heap.insert(5);

// Delete the maximum element
heap.delete_Node(20);

// Find the maximum element without removing it
int maxElement = heap.findMax();
```
4. You can Customize the Heap class as needed for your specific use case. You can modify the implementation or add additional functionality according to your requirements.

### License
This project is licensed under the MIT License.

#### Contributing
Contributions to this project are welcome. If you encounter any issues or have suggestions for improvements, please open an issue or submit a pull request.

### Authors
Muhammad Zaim Akhtar
