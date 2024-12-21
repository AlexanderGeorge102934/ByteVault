#ifndef SEQUENCEABLE_COLLECTION_H
#define SEQUENCEABLE_COLLECTION_H

class SequenceableCollection {
public:
    // Constructors
    SequenceableCollection();                            // Default constructor
    SequenceableCollection(int initialElement);          // Constructor with an initial element
    SequenceableCollection(const SequenceableCollection& other); // Copy constructor

    // Destructor
    ~SequenceableCollection();

    // Methods
    int basicSize() const;                               // Returns the allocated region size
    int size() const;                                    // Returns the number of stored elements

    SequenceableCollection& insertAt(int i, int x);      // Inserts x at index i
    int find(int x) const;                               // Finds x and returns its index
    SequenceableCollection& removeAt(int i);             // Removes element at index i
    SequenceableCollection& iterate(int (*fn)(int));     // Applies fn to each element

    // For testing
    int getElementAt(int i) const;                       // Used for testing Returns the element at logical index i
    // Accessor methods for internal indices
    int getStartIndex() const;                           // Returns _start
    int getEndIndex() const;                             // Returns _end
    int getPhysicalIndex(int logicalIndex) const;        // Returns physical index for logical index


private:
    int* _data;                                          // Pointer to the data array
    int _regionSize;                                     // Size of the allocated region
    int _start;                                          // Start index of stored elements
    int _end;                                            // End index of stored elements

    void grow();                                         // Doubles the storage region
};

#endif // SEQUENCEABLE_COLLECTION_H
