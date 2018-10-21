#ifndef SRALLOC_H
#define	SRALLOC_H

unsigned char * SRAMalloc(unsigned char nBytes);
void SRAMfree(unsigned char * pSRAM);
void SRAMInitHeap(void);

#endif
