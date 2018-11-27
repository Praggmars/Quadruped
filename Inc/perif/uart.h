#pragma once

#include "util/fifo.h"
#include <functional>

namespace quad
{

class UART
{
	USART_TypeDef *m_uart;
	util::fifo<uint8_t, 64> m_inData;
	util::fifo<uint8_t, 64> m_outData;
	std::function<void(uint8_t *data, uint32_t len)> m_subscriber;

private:
	void StartDataTransmit();

public:
	UART(USART_TypeDef *uart);
	void SendData(uint8_t *data, uint32_t size);
	void SendData(uint8_t *str);
	void Subscribe(std::function<void(uint8_t *data, uint32_t len)> subscriber);
	void InterruptHandler();
};

}
