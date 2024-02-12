

#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_

#define EEPROM_CURSOR 0
/************************eeprom_w_r********************/
#define EEPROM_ADDRESS EEAR
#define EEPROM_DATA EEDR
#define EEPROM_CONTROL EECR
/************************int_r_w_bits******************/
typedef enum
{
	EEPROM_READ,
	EEPROM_WRITE,
	EEPROM_READY_WRITE,
	EEPROM_INT_EN
	}EEPROM_CONTROL_t;
	/*
#define EEPROM_INT_EN 3
#define EEPROM_READY_WRITE 2
#define EEPROM_WRITE 1
#define EEPROM_READ 0
*/


typedef enum
{
	EEI_SET,
	EEI_CLR
	}eeprom_int_status_t;
void eeprom_init(void);
u8 eeprom_read(u16 address,u8 data);
void eeprom_write(u16 address,u8 data);



#endif /* EEPROM_INTERFACE_H_ */