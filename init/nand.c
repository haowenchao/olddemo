#define NFCONF	(*(volatile unsigned long*)0x4E000000)
#define NFCONT	(*(volatile unsigned long*)0x4E000004)
#define NFSTAT	(*(volatile unsigned char*)0x4E000020)
#define NFCMD	(*(volatile unsigned char*)0x4E000008)
#define NFADDR	(*(volatile unsigned char*)0x4E00000C)
#define NFDATA	(*(volatile unsigned char*)0x4E000010)

#define TACLS   0
#define TWRPH0  1
#define TWRPH1  0

//select nand 
static void nand_select_chip(void)
{
    NFCONT &= ~(1<<1);	
}

//disselect nand 
static void nand_deselect_chip(void)
{
    NFCONT |= (1<<1);	
}

//wait nand ready
static void nand_wait_idle(void)
{
	while (!(NFSTAT & 1));
}

//write command 
static void nand_write_cmd(unsigned char cmd)
{
	NFCMD = cmd;
}

//send address
static void nand_write_addr(unsigned char addr)
{
	NFADDR = addr;
}

//read data
static unsigned char nand_read_data(void)
{
	return NFDATA;
}

//reset nand flash
static void nand_reset(void)
{
	nand_select_chip();
	nand_write_cmd(0xff);  
	nand_wait_idle();
	nand_deselect_chip();
}

//init nand flash
void nand_init(void)
{
	//set time 
	//TACLS		[13:12]
	//TWRPH0	[10:8]
	//TWRHP1	[6:4]
	NFCONF = (TACLS << 12) | (TWRPH0 <<8 ) | (TWRPH1 << 4);

	NFCONT = (1<<4)|(1<<1)|(1<<0);

	//reset nand
	nand_reset();
}

//read nand flash ID
void nand_read_id(char *buff)
{
	int i = 0;

	//select nand 
	nand_select_chip();

	//send command 0x90
	nand_write_cmd(0x90);

	//send address 0x0
	nand_write_addr(0x0);

	//read data£¬manufacturer code(ECh), and the device code and 3rd, 4th, 5th cycle ID respectively
	//0xec, 0xda, 0x10, 0x15, 0x44
	for(i = 0; i < 5; i++)
	{
		*(buff + i) = nand_read_data();
	}
	
	//disselect
	nand_deselect_chip();
}

void nand_write(char *buff, unsigned int addr, int size)
{
	int i = 0;
	unsigned int col = addr % 2048;
	unsigned int row = addr / 2048;

	//select nand 
	nand_select_chip();

	do{
		//send command 0x0
		nand_write_cmd(0x80);

		//send address
		nand_write_addr((unsigned char)(col & 0xff));
		nand_write_addr((unsigned char)((col >> 8) & 0x0f));
		nand_write_addr((unsigned char)(row  & 0xff));
		nand_write_addr((unsigned char)((row >> 8) & 0xff));
		nand_write_addr((unsigned char)((row >> 16) & 0x1));

		//write data
		for(; (col < 2048) && (i < size); col++)
		{
			NFDATA = *(buff + i);
			i++;
		}
		nand_write_cmd(0x10);

		nand_wait_idle();

		col = 0;
		row++;
	}while(i < size);

	//disselect
	nand_deselect_chip();
}

void nand_read(char *buff, unsigned int addr, int size)
{
	int i = 0;
	unsigned int col = addr % 2048;
	unsigned int row = addr / 2048;

	//select nand 
	nand_select_chip();

	do{
		//send command 0x0
		nand_write_cmd(0x0);

		//send address
		nand_write_addr((unsigned char)(col & 0xff));
		nand_write_addr((unsigned char)((col >> 8) & 0x0f));
		nand_write_addr((unsigned char)(row  & 0xff));
		nand_write_addr((unsigned char)((row >> 8) & 0xff));
		nand_write_addr((unsigned char)((row >> 16) & 0x1));

		//send command 0x30
		nand_write_cmd(0x30);

		nand_wait_idle();

		//read data
		for(; (col < 2048) && (i < size); col++)
		{
			*(buff + i) = NFDATA;
			i++;
			addr++;
		}

		col = 0;
		row++;
	}while(i < size);

	//disselect
	nand_deselect_chip();
}

