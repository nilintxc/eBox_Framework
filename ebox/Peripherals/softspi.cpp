#include "softspi.h"
SOFTSPI::SOFTSPI(GPIO* sckPin,GPIO* misoPin,GPIO* mosiPin)
{
	_mosiPin = mosiPin;
	_misoPin = misoPin;
	_sckPin =  sckPin;
	
//	_bitOrder = MSBFIRST;
//	_mode = SPI_MODE0;
//	_spidelay = 0;

}
void SOFTSPI::begin(SPICONFIG* spiConfig)
{

	pMode(_sckPin,_OPP);
	pMode(_misoPin,_INPUT);
	pMode(_mosiPin,_OPP);
	
	config(spiConfig);
	switch(_mode)
	{
		case SPI_MODE0:
				dgWrite(_sckPin,0);
				break;
		case SPI_MODE1:
				dgWrite(_sckPin,0);		
				break;
		case SPI_MODE2:
				dgWrite(_sckPin,1);		
				break;
		case SPI_MODE3:
				dgWrite(_sckPin,1);		
				break;			
	}
}
void SOFTSPI::config(SPICONFIG* spiConfig)
{
	currentDevNum = spiConfig->devNum;
	_mode = spiConfig->mode;
	_bitOrder = spiConfig->bitOrder;
	switch(spiConfig->prescaler)
	{
		case SPI_BaudRatePrescaler_2:
			_spidelay = 0;
			break;
		case SPI_BaudRatePrescaler_4:
			_spidelay = 1;
			break;
		case SPI_BaudRatePrescaler_8:
			_spidelay = 2;
			break;
		case SPI_BaudRatePrescaler_16:
			_spidelay = 4;
			break;
		case SPI_BaudRatePrescaler_32:
			_spidelay = 8;
			break;
		case SPI_BaudRatePrescaler_64:
			_spidelay = 16;
			break;
		case SPI_BaudRatePrescaler_128:
			_spidelay = 32;
			break;
		case SPI_BaudRatePrescaler_256:
			_spidelay = 64;
			break;
		default:
			_spidelay = spiConfig->prescaler;
			break;
	}
}
uint8_t SOFTSPI::readConfig(void)
{
	return currentDevNum; 
}
uint8_t SOFTSPI::transfer(uint8_t data)
{
	uint8_t i;
	uint8_t RcvData = 0 ;
	switch(_mode)
	{
		case SPI_MODE0:
			//时钟空闲输出：0；
			//第一个是上升沿：读取数据；
			//第二个是下降沿：输出数据；
				for (i = 0; i < 8; i++)  {
					if (_bitOrder == SPI_BITODER_LSB)
					{
						RcvData |= dgRead(_misoPin)<<i;
						dgWrite(_mosiPin, !!(data & (1 << i)));
					}
					else
					{				
						RcvData |= (dgRead(_misoPin)<<(7-i));
						dgWrite(_mosiPin, !!(data & (1 << (7 - i))));
					}
					delay_us(_spidelay);
					dgWrite(_sckPin,1);
					delay_us(_spidelay);
					dgWrite(_sckPin,0);
				}
				break;
		case SPI_MODE1:
			//时钟空闲输出：0；
			//第一个是上升沿：输出数据；
			//第二个是下降沿：读取数据；
				for (i = 0; i < 8; i++)  {
					///////////////////上升沿输出//////////
					if (_bitOrder == SPI_BITODER_LSB)
					{
						dgWrite(_mosiPin, !!(data & (1 << i)));
					}
					else
					{				
						RcvData |= (dgRead(_misoPin)<<(7-i));
						dgWrite(_mosiPin, !!(data & (1 << (7 - i))));
					}
					delay_us(_spidelay);
					dgWrite(_sckPin,1);
					/////////////////下降沿采样////////////
					delay_us(_spidelay);
					dgWrite(_sckPin,0);
					if (_bitOrder == LSBFIRST)
					{
						dgWrite(_mosiPin, !!(data & (1 << i)));
					}
					else
					{				
						RcvData |= (dgRead(_misoPin)<<(7-i));
						dgWrite(_mosiPin, !!(data & (1 << (7 - i))));
					}	
				}
				break;

		case SPI_MODE2:
			//时钟空闲输出：1；
			//第一个是下降沿：读取数据；
			//第二个是上升沿：输出数据；
				for (i = 0; i < 8; i++)  {
					dgWrite(_sckPin,0);
					delay_us(_spidelay);
					if (_bitOrder == SPI_BITODER_LSB)
					{
						RcvData |= dgRead(_misoPin)<<i;
						dgWrite(_mosiPin, !!(data & (1 << i)));
					}
					else
					{				
						RcvData |= (dgRead(_misoPin)<<(7-i));
						dgWrite(_mosiPin, !!(data & (1 << (7 - i))));
					}
					delay_us(_spidelay);
					dgWrite(_sckPin,1);
				}
				break;
				
		case SPI_MODE3:
			//时钟空闲输出：1；
			//第一个是下降沿：输出数据；
			//第二个是上升沿：读取数据；
				for (i = 0; i < 8; i++)  {
					///////////////////下降沿沿输出
					dgWrite(_sckPin,0);
					delay_us(_spidelay);
					if (_bitOrder == SPI_BITODER_LSB)
					{
						dgWrite(_mosiPin, !!(data & (1 << i)));
					}
					else
					{				
						RcvData |= (dgRead(_misoPin)<<(7-i));
						dgWrite(_mosiPin, !!(data & (1 << (7 - i))));
					}
					/////////////////上升沿采样////////////
					dgWrite(_sckPin,1);
					delay_us(_spidelay);
					if (_bitOrder == LSBFIRST)
					{
						dgWrite(_mosiPin, !!(data & (1 << i)));
					}
					else
					{				
						RcvData |= (dgRead(_misoPin)<<(7-i));
						dgWrite(_mosiPin, !!(data & (1 << (7 - i))));
					}	
				}
				break;
		}
				return RcvData;
}








