#include "STDTYPES.h"
#include "DIO_Interface.h"
#include "KeyPAd_interface.h"



const u8 KeypadCols[COLUMNS]={
	PIND2,
	PIND3,
	PIND4,
	PIND5
};

const u8 KeypadRows[ROWS]={
	PINB4,
	PINB5,
	PINB6,
	PINB7
};
const u8 keypadChar[ROWS][COLUMNS]={
	{'7','8','9','A'},
	{'4','5','6','B'},
	{'1','2','3','C'},
	{'c','0','=','D'}
};