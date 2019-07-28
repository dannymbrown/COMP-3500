/*
 *@author Danny Brown dmb0057@auburn.edu
 *@file vmm.cpp
 *@description Project 6
 */

#include "tlb.cpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
/* offset is used to address the location within a page */
#define OFFSET_BITS 8
/* mask is used to extract the offset from a logical address */
#define OFFSET_MASK 0xFF

#define EMPTY_PAGE 3435973836
#define NUM_PAGES 256
#define NUM_FRAMES 256
#define PAGE_SIZE 256
#define FRAME_SIZE 256
#define TLB_SIZE 16
#define LOGIC_ADDR_LIST_SIZE 1024

/* There is no byte data type in C */
typedef unsigned char byte;

/* new data type of pages, frames, and offset */
typedef unsigned int page_t;
typedef unsigned int frame_t;
typedef unsigned int offset_t;
typedef unsigned int laddress_t;
typedef unsigned int paddress_t;
typedef char physical_memory_t[NUM_FRAMES][PAGE_SIZE];
typedef vector<laddress_t> logicAddressList_t;
typedef vector<paddress_t> physAddressList_t;
typedef frame_t pageTable_t[NUM_PAGES];

/*
 * In C language, there is no binary format in printf
 * You must implement the following functions to print binary format
 * itob16() and itob8() are modified from itob() by Xiao Qin.
 */
char *itob(int x);
char *itob16(int x);
char *itob8(int x);

//-------------------------------------------------------------//
//------------------------Function Prototypes------------------//
//-------------------------------------------------------------//

void welcome_message(void);
int loadLogicalAdresses(vector<laddress_t> *logicalAddressList);
void getLogicalAddress(laddress_t address, page_t *pageNum, offset_t *offset);
void loadPhysicalMemory(page_t pageNum, const char *backingStoreFileName,
                        physical_memory_t physical_memory, frame_t *frameNum);

void createPhysicalAddress(frame_t f_num, offset_t off,
                           paddress_t *physical_addr);

//-------------------------------------------------------------//
//------------------------Program Operations-------------------//
//-------------------------------------------------------------//

int main(int argc, char const *argv[]) {
  // Initialization
  pageTable_t ptable;
  // Address Lists
  logicAddressList_t logicAddressList;
  physAddressList_t physAddressList;
  // TLB
  tlb tlb;
  // Flags
  bool tlbHit;
  bool pageFault;
  bool display = false;
  bool fifo = false;
  bool lru = false;
  // Trackers
  float faults = 0.0;
  float hits = 0.0;
  // Addresses
  laddress_t logicAddress;
  paddress_t physicalAddress;
  // PageNum FrameNum Offset
  page_t pageNum;
  frame_t frameNum;
  offset_t offset;
  // Backing store
  const char backing_store_file_name[] = "BACKING_STORE";
  // Welcome Message
  welcome_message();
  std::string display_choice;
  std::cout << "Display physical addresses? [y or n] ";
  std::cin >> display_choice;
  if (display_choice == "y" || display_choice == "Y") {
    display = true;
  }
  std::cout << '\n';

  // Choose FIFO or LRU
  int replacement_choice;
  std::cout << "Choose TLB Replacement Strategy [1: FIFO, 2: LRU]: ";
  std::cin >> replacement_choice;
  if (replacement_choice == 1) {
    fifo = true;
  } else if (replacement_choice == 2) {
    lru = true;
  }
  std::cout << '\n';

  // Initiaze Page Table and TLB
  initializePageTable(ptable);
  inititializeTLB(&tlb);
  // Load the logical addresses from the test file
  int count = loadLogicalAdresses(&logicAddressList);
  for (int i = 0; i < count; i++) {
    physical_memory_t physical_memory;
    getLogicalAddress(logicAddressList[i], &pageNum, &offset);
    loadPhysicalMemory(pageNum, backing_store_file_name, physical_memory,
                       &frameNum);
    searchTLB(&pageNum, &tlbHit, &frameNum, &tlb);
    if (tlbHit) {
      physicalAddress = (frameNum * FRAME_SIZE) + offset;
      physAddressList.push_back(physicalAddress);
      hits++;
    } else {
      if (!pageFault) {
        physicalAddress = (pageNum * PAGE_SIZE) + offset;
        physAddressList.push_back(physicalAddress);
        faults++;
        if (fifo) {
        } else if (lru) {
          // replace_lru(page_num, frame_num, &sys_tlb);
        }
      }
    }
  }
  if (display) {
    for (int i = 0; i < count; i++) {
      std::cout << "Virtual Address: " << logicAddressList[i]
                << "; Physical Address: " << physAddressList[i] << endl;
    }
  }
  return 0;
}

void welcome_message(void) {
  printf("Welcome to Danny's VM Simulator\n");
  printf("Number of logical pages: %d\n", NUM_PAGES);
  printf("Number of physical frames: %d\n", NUM_FRAMES);
  printf("Page size: %d\n", PAGE_SIZE);
  printf("TLB size: %d\n", TLB_SIZE);
}

/*
Loads logical addresses into Vector
*/
int loadLogicalAdresses(vector<laddress_t> *logicalAddressList) {
  int count = 0;
  ifstream instream("InputFile.txt");
  if (instream.fail()) {
    std::cout << "ERROR: Could Not Open File" << '\n';
    exit(1);
  }
  unsigned int next;
  while (!instream.eof()) {
    instream >> next;
    logicalAddressList->push_back(next);
    count++;
  }
  instream.close();
  return count;
}

void getLogicalAddress(laddress_t address, page_t *pageNum, offset_t *offset) {
  *pageNum = address >> OFFSET_BITS;
  *offset = address & OFFSET_MASK;
}

void loadPhysicalMemory(page_t pageNum, const char *backingStoreFileName,
                        physical_memory_t physical_memory, frame_t *frameNum) {
  FILE *file = fopen(backingStoreFileName, "r");
  fpos_t pos;
  char one_byte;
  if (file == 0) {
    printf("Could not open file: %s.\n", backingStoreFileName);
  } else {
    if (file == 0) {
      printf("Could not open file: %s.\n", backingStoreFileName);
    }
  }
}

void createPhysicalAddress(frame_t frame_num, offset_t offsett,
                           paddress_t *physical_address) {
  *physical_address = frame_num * FRAME_SIZE + offsett;
}
