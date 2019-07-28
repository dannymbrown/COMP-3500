/*
 *@author Danny Brown dmb0057@auburn.edu
 *@file tlb.cpp
 *@description Project 6
 */

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

typedef struct {
  page_t pageNum;
  frame_t frameNum;
  bool valid;
  int age;
} tlbEntry;

typedef struct {
  tlbEntry tlb_entry[TLB_SIZE];
  unsigned int next;
} tlb;

typedef struct {
  char page[PAGE_SIZE];
  bool valid;
} frame;

//-------------------------------------------------------------//
//------------------------Function Prototypes------------------//
//-------------------------------------------------------------//

void replace_fifo(page_t pageNum, frame_t frameNum, tlb *tlb);
void inititializeTLB(tlb *tlb);
void searchTLB(page_t *pageNum, bool *isTlbHit, frame_t *frameNum,
               tlb *tlbSearch);
void initializePageTable(pageTable_t ptable);
void searchPageTable(page_t pageNum, bool *isPageFault, frame_t *frameNum,
                     pageTable_t *page_Table);
void replace_lru(page_t pageNum, frame_t frameNum, tlb *tlb);
void replace_fifo(page_t pageNum, frame_t frameNum, tlb *tlb);

/*
Initializes Page Table
*/
void initializePageTable(pageTable_t ptable) {
  for (int i = 0; i < NUM_PAGES; i++) {
    ptable[i] = 0;
  }
}

void inititializeTLB(tlb *tlb) {
  unsigned int i;
  tlb->next = 0;
  for (i = 0; i < TLB_SIZE; i++)
    tlb->tlb_entry[i].valid = false;
  tlb->tlb_entry[i].age = 0;
}

void searchTLB(page_t *pageNum, bool *isTlbHit, frame_t *frameNum,
               tlb *tlbSearch) {
  for (int i = 0; i < TLB_SIZE; i++) {
    tlbSearch->tlb_entry[i].age++;
  }
  for (int i = 0; i < TLB_SIZE; i++) {
    if (tlbSearch->tlb_entry[i].pageNum == *pageNum) {
      *isTlbHit = true;
      *frameNum = tlbSearch->tlb_entry[i].frameNum;
      tlbSearch->tlb_entry[i].age = 0;
    }
  }
  *isTlbHit = false;
}

void replace_lru(page_t pageNum, frame_t frameNum, tlb *tlb) {
  for (int i = 0; i < TLB_SIZE; i++) {
    if (tlb->tlb_entry[i].valid == false) {
      tlb->tlb_entry[i].pageNum = pageNum;
      tlb->tlb_entry[i].frameNum = frameNum;
      tlb->tlb_entry[i].valid = true;
    }
  }
  int oldest = 0;
  int index = 0;
  for (int i = 0; i < TLB_SIZE; i++) {
    if (oldest < tlb->tlb_entry[i].age) {
      oldest = tlb->tlb_entry[i].age;
      index = i;
    }
  }
  tlb->tlb_entry[index].pageNum = pageNum;
  tlb->tlb_entry[index].frameNum = frameNum;
  tlb->tlb_entry[index].age = 0;
  tlb->tlb_entry[index].valid = true;
}

void replace_fifo(page_t pageNum, frame_t frameNum, tlb *tlb) {
  for (int index = 0; index < TLB_SIZE; index++) {
    if (tlb->tlb_entry[index].valid == false) {
      tlb->tlb_entry[index].pageNum = pageNum;
      tlb->tlb_entry[index].frameNum = frameNum;
      tlb->tlb_entry[index].valid = true;
    }
  }
  tlb->tlb_entry[tlb->next].pageNum = pageNum;
  tlb->tlb_entry[tlb->next].frameNum = frameNum;
  tlb->tlb_entry[tlb->next].valid = true;
  if (tlb->next == 15) {
    tlb->next = 0;
  } else {
    tlb->next++;
  }
}

void searchPageTable(page_t pageNum, bool *isPageFault, frame_t *frameNum,
                     pageTable_t *page_Table) {}
