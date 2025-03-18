#ifndef HOARD_H
#define HOARD_H

#include <vector>

#ifdef _WIN32 // Windows-specific code
#include <sysinfoapi.h>
int getSystemPageSize() {
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    return sysInfo.dwPageSize;
}
#else // Linux/Unix-specific code
#include <unistd.h>
int getSystemPageSize() {
    return sysconf(_SC_PAGE_SIZE);
}
#endif


#define SUPERMULPAGESIZE 1   // superblock is the size of 1 system page

class hoard {
    
private:
    globalHeap;
    std::vector<heap> heaps;
    int pageSize;
public:
    hoard() = delete;                        // delete default constructor
    hoard(const hoard&) = delete;            // delete copy constructor
    hoard(hoard&&) = delete;                 // delete move constructor
    hoard& operator=(const hoard&) = delete; // delete copy assignment operator
    hoard& operator=(hoard&&) = delete;      // delete move assignment operator

    hoard() {
        // determine system page size
        int pageSize = getSystemPageSize();
        
    }
    ~hoard() {
        
    }
    block* malloc(void* object) {
        // lock appropriate heap for thread that is calling malloc
        
    }
    void free(block* blockToFree) {
        // lock appropriate superBlock containing blockToFree
        
        // lock appropriate heap for thread that is calling free
        
    }
};

class heap {
private:
    std::vector<bin> fullnessBins;    
public:

};

struct bin {
    superBlock* start;
    superBlock* end;
};

class superBlock {
private:
    superBlock* next;
    superBlock* prev;
    std::vector<block> freeList;   // we maintain freeList in LIFO order
    size_t sizeOfSuperBlock;
    float fullness;
public:
    superBlock(size_t sizeOfSingleObject, size_t sizeOfPage) {
        // call malloc() here to allocate memory for the block
        // run through blocks and put on the freeList
    }
    void setNext(superBlock* newNext) {
        next = newNext;
    }
    superBlock* getNext() {
        return next;
    }
    void setPrev(superBlock* newPrev) {
        prev = newPrev;
    }
    superBlock* getPrev() {
        return prev;
    }
    block* malloc(void* object) {
        // take block off front of freeList, maintaining LIFO order
        // adjust fullness up
    }
    void free(block* blockToFree) {
        // push freed block on front of freeList, maintaining LIFO order
        // adjust fullness down
    }
    float getFullness() {
        return fullness;
    }
};

struct block {
    void* address;
    superBlock* superBlock;
};

#endif