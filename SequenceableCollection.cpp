#include "SequenceableCollection.h"
#include <cstring>  // For memcpy
#include <stdexcept>

// Default constructor
SequenceableCollection::SequenceableCollection() {
    _regionSize = 8;
    _data = new int[_regionSize];
    _start = 3;
    _end = 2;  // Indicates an empty collection
}

// Constructor with an initial element
SequenceableCollection::SequenceableCollection(int initialElement) {
    _regionSize = 8;
    _data = new int[_regionSize];
    _start = 3;
    _end = 3;
    _data[_start] = initialElement;
}

// Copy constructor (deep copy)
SequenceableCollection::SequenceableCollection(const SequenceableCollection& other) {
    _regionSize = other._regionSize;
    _start = other._start;
    _end = other._end;
    _data = new int[_regionSize];
    std::memcpy(_data, other._data, sizeof(int) * _regionSize);
}

// Destructor
SequenceableCollection::~SequenceableCollection() {
    delete[] _data;
}

// Returns the size of the allocated region
int SequenceableCollection::basicSize() const {
    return _regionSize;
}

// Returns the number of elements stored
int SequenceableCollection::size() const {
    if (_start > _end)
        return 0;
    return _end - _start + 1;
}

// Inserts x at index i
SequenceableCollection& SequenceableCollection::insertAt(int i, int x) {
    int currentSize = size();
    if (i < 0 || i > currentSize) {
        // Invalid index, do nothing
        return *this;
    }

    // Check if we need to grow the region
    if (_start == 0 && _end == _regionSize - 1) {
        grow();
    }

    // Special case when the collection is empty
    if (currentSize == 0) {
        _start = _end = 3;  // As per initial requirement
        _data[_start] = x;
        return *this;
    }

    int physicalIndex = _start + i;

    // Decide whether to shift elements left or right
    if (i <= currentSize / 2) {
        // Closer to start, shift elements to the left
        if (_start > 0) {
            _start--;
            for (int idx = _start; idx < physicalIndex; idx++) {
                _data[idx] = _data[idx + 1];
            }
            _data[physicalIndex - 1] = x;
        } else {
            // Shift elements to the right
            for (int idx = _end; idx >= physicalIndex; idx--) {
                _data[idx + 1] = _data[idx];
            }
            _end++;
            _data[physicalIndex] = x;
        }
    } else {
        // Closer to end, shift elements to the right
        if (_end < _regionSize - 1) {
            _end++;
            for (int idx = _end; idx > physicalIndex; idx--) {
                _data[idx] = _data[idx - 1];
            }
            _data[physicalIndex] = x;
        } else {
            // Shift elements to the left
            for (int idx = _start; idx < physicalIndex; idx++) {
                _data[idx - 1] = _data[idx];
            }
            _start--;
            _data[physicalIndex - 1] = x;
        }
    }

    return *this;
}

// Finds x and returns its index, or -1 if not found
int SequenceableCollection::find(int x) const {
    int s = size();
    for (int i = 0; i < s; i++) {
        if (_data[_start + i] == x) {
            return i;
        }
    }
    return -1;
}

// Removes element at index i
SequenceableCollection& SequenceableCollection::removeAt(int i) {
    int currentSize = size();
    if (i < 0 || i >= currentSize) {
        // Invalid index, do nothing
        return *this;
    }

    int physicalIndex = _start + i;

    // Decide whether to shift elements left or right
    if (i < currentSize / 2) {
        // Shift elements right to fill the gap
        for (int idx = physicalIndex; idx > _start; idx--) {
            _data[idx] = _data[idx - 1];
        }
        _start++;
    } else {
        // Shift elements left to fill the gap
        for (int idx = physicalIndex; idx < _end; idx++) {
            _data[idx] = _data[idx + 1];
        }
        _end--;
    }

    return *this;
}

// Applies function fn to each element
SequenceableCollection& SequenceableCollection::iterate(int (*fn)(int)) {
    int s = size();
    for (int i = 0; i < s; i++) {
        _data[_start + i] = fn(_data[_start + i]);
    }
    return *this;
}

// Doubles the storage region size
void SequenceableCollection::grow() {
    int newRegionSize = _regionSize * 2;
    int* newData = new int[newRegionSize];
    int currentSize = size();

    // Place elements in the middle of the new region
    int newStart = (newRegionSize - currentSize) / 2;
    for (int i = 0; i < currentSize; i++) {
        newData[newStart + i] = _data[_start + i];
    }

    delete[] _data;
    _data = newData;
    _regionSize = newRegionSize;
    _start = newStart;
    _end = newStart + currentSize - 1;
}

// Returns the element at logical index i
int SequenceableCollection::getElementAt(int i) const {
    int currentSize = size();
    if (i < 0 || i >= currentSize) {
        throw std::out_of_range("Index out of bounds");
    }
    return _data[_start + i];
}

// Returns _start
int SequenceableCollection::getStartIndex() const {
    return _start;
}

// Returns _end
int SequenceableCollection::getEndIndex() const {
    return _end;
}

// Returns physical index for a given logical index
int SequenceableCollection::getPhysicalIndex(int logicalIndex) const {
    if (logicalIndex < 0 || logicalIndex >= size()) {
        throw std::out_of_range("Logical index out of bounds");
    }
    return _start + logicalIndex;
}