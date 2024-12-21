#include "SequenceableCollection.cpp"
#include <iostream>
#include "SequenceableCollection.h"

#include <iostream>
#include "SequenceableCollection.h"

// Function to apply in iterate method (e.g., doubling the value)
int doubleValue(int x) {
    return x * 2;
}

// Updated helper function to display the collection
void displayCollection(const SequenceableCollection& sc) {
    int size = sc.size();
    std::cout << "Collection size: " << size << std::endl;
    std::cout << "Allocated region size (basicSize): " << sc.basicSize() << std::endl;
    std::cout << "Start index (_start): " << sc.getStartIndex() << std::endl;
    std::cout << "End index (_end): " << sc.getEndIndex() << std::endl;
    std::cout << "Elements and indices:" << std::endl;
    for (int i = 0; i < size; ++i) {
        int physicalIndex = sc.getPhysicalIndex(i);
        int element = sc.getElementAt(i);
        std::cout << "  Logical index " << i << " maps to physical index " << physicalIndex
                  << " with element " << element << std::endl;
    }
    std::cout << std::endl;
}


int main() {
    // Test default constructor
    SequenceableCollection scDefault;
    std::cout << "After default construction:" << std::endl;
    displayCollection(scDefault);

    // Test constructor with initial element
    SequenceableCollection scInitial(5);
    std::cout << "\nAfter constructing with initial element 5:" << std::endl;
    displayCollection(scInitial);

    // Insert elements
    scInitial.insertAt(0, 10).insertAt(1, 15).insertAt(2, 20);
    std::cout << "\nAfter inserting 10 at position 0, 15 at position 1, and 20 at position 2:" << std::endl;
    displayCollection(scInitial);

    // Test find method
    int index = scInitial.find(15);
    std::cout << "\nFinding element 15: ";
    if (index != -1) {
        std::cout << "Found at index " << index << std::endl;
    } else {
        std::cout << "Not found" << std::endl;
    }

    // Test insert at beginning
    scInitial.insertAt(0, 25);
    std::cout << "\nAfter inserting 25 at position 0:" << std::endl;
    displayCollection(scInitial);

    // Test insert at end
    scInitial.insertAt(scInitial.size(), 30);
    std::cout << "\nAfter inserting 30 at the end:" << std::endl;
    displayCollection(scInitial);

    // Test removeAt method
    scInitial.removeAt(2);
    std::cout << "\nAfter removing element at index 2:" << std::endl;
    displayCollection(scInitial);

    // Test iterate method
    scInitial.iterate(doubleValue);
    std::cout << "\nAfter doubling each element using iterate:" << std::endl;
    displayCollection(scInitial);

    // Test copy constructor
    SequenceableCollection scCopy(scInitial);
    std::cout << "\nAfter copying scInitial to scCopy:" << std::endl;
    displayCollection(scCopy);

    // Modify scCopy and show that scInitial remains unchanged
    scCopy.insertAt(1, 100);
    std::cout << "\nAfter inserting 100 at index 1 in scCopy:" << std::endl;
    std::cout << "scCopy:" << std::endl;
    displayCollection(scCopy);
    std::cout << "scInitial (should be unchanged):" << std::endl;
    displayCollection(scInitial);

    // Test grow method implicitly by adding many elements

    scDefault.insertAt(scDefault.size(), 33);
    scDefault.insertAt(0, 222);
    scDefault.insertAt(0, 444);
    scDefault.insertAt(0, 343);
    scDefault.insertAt(0, 192);
    scDefault.insertAt(0, 777);
    scDefault.insertAt(0, 111);
    scDefault.insertAt(0, 333);
    scDefault.insertAt(0, 555);
    scDefault.insertAt(20, 222);
    std::cout << "\nAfter inserting elements into scDefault to trigger grow:" << std::endl;
    displayCollection(scDefault);

    // Test destructor (will be called automatically at the end of main)
    std::cout << "\nEnd of tests. Destructors will be called automatically." << std::endl;

    return 0;
}


























// insertAt(0, X)

// _ _ _ X _ _ _ _
// _ _ _ 0 _ _ _ _  logical region
// 0 1 2 3 4 5 6 7 physical region
// start and end point at physical region 3

// insertAt(0, Y)
// _ _ _ Y X _ _ _
// _ _ _ 0 1 _ _ _  logical region
// 0 1 2 3 4 5 6 7 physical region
// start points at physical region 3 and end point at physical region 4

// insertAt(1, Z)
// _ _ _ Y Z X _ _
// _ _ _ 0 1 2 _ _  logical region
// 0 1 2 3 4 5 6 7 physical region
// start points at physical region 3 and end point at physical region 5

// insertAt(0, A)
// _ _ A Y Z X _ _
// _ _ 0 1 2 3 _ _  logical region
// 0 1 2 3 4 5 6 7 physical region
// start points at physical region 2 and end point at physical region 5

// Initially you are allowed to insert at logical region 0 but after that you are only allowed to insert where elements are




