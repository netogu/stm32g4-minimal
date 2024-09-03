#pragma once

#include <stdint.h>
#include "stm32g4/gpio.h"
#include "stm32g4xx.h"


#define UART_BUFFER_SIZE 256

typedef struct uart_fifo_s {
    uint8_t buffer[UART_BUFFER_SIZE];
    uint8_t head;
    uint8_t tail;
    uint8_t size;
} uart_fifo_t;

typedef struct uart_s {
    USART_TypeDef *instance;
    gpio_t tx_pin;
    gpio_t rx_pin;
    uart_fifo_t rx_fifo;
    uart_fifo_t tx_fifo;
    struct uart_config_s {
        uint32_t baudrate;
        enum uart_word_len_e {
            UART_DATA_BITS_8 = 0,
            UART_DATA_BITS_9 = 1,
            UART_DATA_BITS_7 = 2,
        } word_length;
        enum uart_stop_bits_e {
            UART_STOP_BITS_1 = 0,
            UART_STOP_BITS_2 = 2,
        } stop_bits;
        enum uart_parity_e {
            UART_PARITY_EVEN = 0,
            UART_PARITY_ODD = 1,
            UART_PARITY_NONE = 2,
        } parity;
        enum uart_mode_e {
            UART_MODE_RX = 0,
            UART_MODE_TX = 1,
            UART_MODE_RX_TX = 2,
        } mode;
        enum uart_flow_control_e {
            UART_FLOW_CONTROL_NONE = 0,
            UART_FLOW_CONTROL_RTS = 1,
            UART_FLOW_CONTROL_CTS = 2,
            UART_FLOW_CONTROL_RTS_CTS = 3,
        } flow_control;
    }config;
} uart_t;


void uart_init(uart_t *self);
void uart_init_dma(uart_t *self);
int uart_write(uart_t *self, uint8_t *data, uint16_t size);
int uart_read(uart_t *self, uint8_t *data, uint16_t size);
int uart_fifo_push(uart_fifo_t *self, uint8_t byte);
int uart_fifo_pop(uart_fifo_t *self, uint8_t *byte);