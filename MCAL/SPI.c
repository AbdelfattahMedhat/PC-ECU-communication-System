#include "STDTYPES.h"
#include "MemMap.h"
#include "Utils.h"
#include "spi.h"

typedef enum
{
	SLAVE,
	MASTER=0x40,
	CLEAR_MSTR_SLV_BIT=0xbf
	}spi_mode_type;

void spi_init(spi_mode_type mode,spi_clock_polarity_type )
{
// spi enable
	SET_BIT(SPCR,SPE);
// MASTER OR SLAVE SELECT
SPCR&=CLEAR_MSTR_SLV_BIT;
SPCR|=mode;	
}

u8 spi_send_receive(u8 data);

typedef enum
{
	SPI_DISABLE,
	SPI_ENABLE=0X80,
	CLEAR_INTERRUPT_BIT=0X7F
	}spi_interrupt_type;
	


void spi_enterrupt_control(spi_interrupt_type state)
{
	SPCR&=CLEAR_INTERRUPT_BIT;
	SPCR|=state;
}