#include <stdint.h>
#include "hal.h"
#include <FreeRTOS.h>
#include <semphr.h>
#include "stm32g4/uart.h"

#define NOCHAR '\0'

static StaticSemaphore_t uart_mutex_buffer;
SemaphoreHandle_t uart_mutex;

static uart_t *serial_port = NULL;


int cli_uart_init(uart_t *port) {
    
    uart_mutex = xSemaphoreCreateMutexStatic(&uart_mutex_buffer);
    if (uart_mutex == NULL) {
        // Error Creating UART Mutex
        while(1);
    }

    serial_port = port;

    return 0;
}

int cli_uart_putc(char tx_char) {
    
    int status = 0;
    if (xSemaphoreTake(uart_mutex, 10) == pdTRUE) {
        status = uart_write(serial_port, (uint8_t *) &tx_char, 1);
        xSemaphoreGive(uart_mutex);
    }
    return status;
}

char cli_uart_getc(void) {
    int status = 0;
    char readchar = NOCHAR;
    if (xSemaphoreTake(uart_mutex, 10) == pdTRUE) {
        status = uart_read(serial_port, (uint8_t *) &readchar, 1);
        xSemaphoreGive(uart_mutex);
    }
    return readchar;
}