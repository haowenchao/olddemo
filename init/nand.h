#ifndef _NAND_H_
#define _NAND_H_

void nand_init(void);
void nand_read(unsigned char *, unsigned int, int);
void nand_read_id(void);
void nand_write(unsigned char *, unsigned int, int);

#endif

