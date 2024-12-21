# SequenceableCollection Class README

## Introduction

The `SequenceableCollection` class is a custom data structure designed to store integer numbers efficiently. It combines the advantages of arrays (direct access to elements) and linked lists (dynamic resizing). This README provides a comprehensive explanation of the class implementation, its methods, and how to use it effectively.

---

## Table of Contents

- [Features](#features)
- [Class Overview](#class-overview)
- [Internal Data Structure](#internal-data-structure)
- [Constructors and Destructor](#constructors-and-destructor)
- [Public Methods](#public-methods)
    - [`basicSize()`](#basicsize)
    - [`size()`](#size)
    - [`insertAt(int i, int x)`](#insertatint-i-int-x)
    - [`find(int x)`](#findint-x)
    - [`removeAt(int i)`](#removeatint-i)
    - [`iterate(int (*fn)(int))`](#iterateint-fnint)
    - [`getElementAt(int i)`](#getelementatint-i)
    - [Accessor Methods for Internal Indices](#accessor-methods-for-internal-indices)
- [Private Methods](#private-methods)
    - [`grow()`](#grow)
- [Usage Example](#usage-example)
- [Implementation Details](#implementation-details)
- [Notes](#notes)
- [Conclusion](#conclusion)

---

## Features

- **Contiguous Storage**: Elements are stored contiguously in memory, allowing direct access.
- **Dynamic Resizing**: The storage region can grow dynamically when needed.
- **Efficient Insertion and Removal**: Supports insertion and removal at any position with minimal shifting.
- **Internal Indices Access**: Provides methods to access internal indices for debugging and testing.
- **Deep Copy Support**: Implements a copy constructor for creating deep copies of instances.
- **Memory Management**: Ensures no memory leaks through proper use of constructors and destructors.

---

## Class Overview

The `SequenceableCollection` class is defined in two files:

- **Header File**: `SequenceableCollection.h`
- **Implementation File**: `SequenceableCollection.cpp`

---

## Internal Data Structure

The class uses a dynamically allocated array to store elements and maintains internal indices to manage the storage:

- **`int* _data`**: Pointer to the dynamically allocated array storing the elements.
- **`int _regionSize`**: The total size of the allocated region (`_data` array).
- **`int _start`**: The starting index of the region where elements are stored.
- **`int _end`**: The ending index of the region where elements are stored.

**Note**: The elements are stored between `_start` and `_end`, inclusive.

---

## Constructors and Destructor

### **Default Constructor**

```cpp
SequenceableCollection();
```

- Initializes an empty collection.
- Allocates an initial region of size 8.
- Sets `_start = 3` and `_end = 2`, indicating an empty collection.

### **Constructor with Initial Element**

```cpp
SequenceableCollection(int initialElement);
```

- Initializes a collection with one element.
- Allocates an initial region of size 8.
- Places `initialElement` at index `_start = _end = 3`.

### **Copy Constructor**

```cpp
SequenceableCollection(const SequenceableCollection& other);
```

- Creates a deep copy of another `SequenceableCollection` instance.
- Allocates a new array and copies all elements.

### **Destructor**

```cpp
~SequenceableCollection();
```

- Deallocates the dynamically allocated array to prevent memory leaks.

---

## Public Methods

### `basicSize()`

```cpp
int basicSize() const;
```

- **Description**: Returns the size of the allocated region (`_regionSize`).
- **Usage**: Useful to know the capacity of the collection before it needs to grow.

### `size()`

```cpp
int size() const;
```

- **Description**: Returns the number of elements currently stored in the collection.
- **Calculation**: `size = _end - _start + 1` (if `_start <= _end`), otherwise `0`.

### `insertAt(int i, int x)`

```cpp
SequenceableCollection& insertAt(int i, int x);
```

- **Description**: Inserts element `x` at logical index `i`.
- **Parameters**:
    - `int i`: Logical index where `x` will be inserted (0-based).
    - `int x`: The integer value to insert.
- **Behavior**:
    - Validates index `i` (must be between `0` and `size()`).
    - Determines whether to shift elements left or right based on `i`.
    - Adjusts `_start` and `_end` accordingly.
    - If the allocated region is full, calls `grow()` to double the region size.
- **Returns**: Reference to the modified collection to support chaining.
- **Example**:
  ```cpp
  SequenceableCollection sc;
  sc.insertAt(0, 10); // Inserts 10 at index 0
  sc.insertAt(1, 20); // Inserts 20 at index 1
  ```

### `find(int x)`

```cpp
int find(int x) const;
```

- **Description**: Searches for element `x` in the collection.
- **Parameters**:
    - `int x`: The integer value to search for.
- **Returns**:
    - The logical index of `x` if found.
    - `-1` if `x` is not in the collection.
- **Example**:
  ```cpp
  int index = sc.find(20);
  if (index != -1) {
      // Element found at index
  } else {
      // Element not found
  }
  ```

### `removeAt(int i)`

```cpp
SequenceableCollection& removeAt(int i);
```

- **Description**: Removes the element at logical index `i`.
- **Parameters**:
    - `int i`: Logical index of the element to remove (0-based).
- **Behavior**:
    - Validates index `i` (must be between `0` and `size() - 1`).
    - Determines whether to shift elements left or right to fill the gap.
    - Adjusts `_start` or `_end` accordingly.
- **Returns**: Reference to the modified collection to support chaining.
- **Example**:
  ```cpp
  sc.removeAt(1); // Removes element at index 1
  ```

### `iterate(int (*fn)(int))`

```cpp
SequenceableCollection& iterate(int (*fn)(int));
```

- **Description**: Applies a function `fn` to each element in the collection.
- **Parameters**:
    - `int (*fn)(int)`: A pointer to a function that takes an `int` and returns an `int`.
- **Behavior**:
    - Iterates through all elements and replaces each with the result of `fn(element)`.
- **Returns**: Reference to the modified collection to support chaining.
- **Example**:
  ```cpp
  int doubleValue(int x) { return x * 2; }
  sc.iterate(doubleValue); // Doubles each element in the collection
  ```

### `getElementAt(int i)`

```cpp
int getElementAt(int i) const;
```

- **Description**: Returns the element at logical index `i`.
- **Parameters**:
    - `int i`: Logical index of the element (0-based).
- **Returns**: The integer value at index `i`.
- **Throws**: `std::out_of_range` if `i` is out of bounds.
- **Example**:
  ```cpp
  int value = sc.getElementAt(0); // Gets the first element
  ```

#### **Accessor Methods for Internal Indices**

These methods are useful for debugging and testing, allowing you to access internal indices and mappings.

- **`getStartIndex()`**

  ```cpp
  int getStartIndex() const;
  ```

    - Returns the value of `_start`.

- **`getEndIndex()`**

  ```cpp
  int getEndIndex() const;
  ```

    - Returns the value of `_end`.

- **`getPhysicalIndex(int logicalIndex)`**

  ```cpp
  int getPhysicalIndex(int logicalIndex) const;
  ```

    - Converts a logical index to the corresponding physical index in `_data`.
    - **Parameters**:
        - `int logicalIndex`: The logical index to convert.
    - **Returns**: The physical index in the `_data` array.
    - **Throws**: `std::out_of_range` if `logicalIndex` is out of bounds.

---

## Private Methods

### `grow()`

```cpp
void grow();
```

- **Description**: Doubles the size of the allocated region when the collection is full.
- **Behavior**:
    - Allocates a new array of size `2 * _regionSize`.
    - Copies existing elements to the middle of the new array.
    - Updates `_start` and `_end` to reflect the new positions.
    - Deallocates the old array to prevent memory leaks.

---

## Usage Example

```cpp
#include <iostream>
#include "SequenceableCollection.h"

// Function to double a value
int doubleValue(int x) {
    return x * 2;
}

int main() {
    // Create a collection with initial element 5
    SequenceableCollection sc(5);

    // Insert elements
    sc.insertAt(0, 10);
    sc.insertAt(1, 15);
    sc.insertAt(2, 20);

    // Display elements and indices
    for (int i = 0; i < sc.size(); ++i) {
        int value = sc.getElementAt(i);
        int physicalIndex = sc.getPhysicalIndex(i);
        std::cout << "Logical Index: " << i
                  << ", Physical Index: " << physicalIndex
                  << ", Value: " << value << std::endl;
    }

    // Remove an element
    sc.removeAt(1);

    // Apply a function to each element
    sc.iterate(doubleValue);

    // Access internal indices
    std::cout << "Start Index (_start): " << sc.getStartIndex() << std::endl;
    std::cout << "End Index (_end): " << sc.getEndIndex() << std::endl;

    return 0;
}
```

**Expected Output**:

```
Logical Index: 0, Physical Index: 3, Value: 10
Logical Index: 1, Physical Index: 4, Value: 15
Logical Index: 2, Physical Index: 5, Value: 20
Logical Index: 3, Physical Index: 6, Value: 5
Start Index (_start): 3
End Index (_end): 6
```

---

## Implementation Details

### **Index Mapping**

- **Logical Index (`i`)**: The index used by the user, ranging from `0` to `size() - 1`.
- **Physical Index**: The actual index in the `_data` array where the element is stored.
- **Calculation**: `physicalIndex = _start + i`.

### **Insertion Logic**

- **When Inserting**:
    - **If Closer to Start**:
        - If there's space before `_start`, shift elements left.
        - Decrement `_start`.
    - **If Closer to End**:
        - If there's space after `_end`, shift elements right.
        - Increment `_end`.
- **When Region is Full**:
    - Call `grow()` to double the region size.

### **Removal Logic**

- **When Removing**:
    - **If Closer to Start**:
        - Shift elements right to fill the gap.
        - Increment `_start`.
    - **If Closer to End**:
        - Shift elements left to fill the gap.
        - Decrement `_end`.

### **Growth Strategy**

- The `grow()` method ensures that after resizing, elements are centered in the new array to maintain balance and provide space on both ends for future insertions.

### **Memory Management**

- The class ensures no memory leaks by:
    - Deleting the old array in `grow()`.
    - Deallocating `_data` in the destructor.

---

## Notes

- **Exception Handling**: The methods `getElementAt` and `getPhysicalIndex` throw `std::out_of_range` exceptions when invalid indices are provided.
- **Chaining Support**: Methods like `insertAt`, `removeAt`, and `iterate` return a reference to the collection to support method chaining.
- **Internal Indices**: Accessor methods for `_start`, `_end`, and physical index mapping are provided primarily for debugging and testing purposes.

---

