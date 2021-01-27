//
// Created by thomas on 26/01/2021.
//
#include "uart.h"

/**
 * Receive a character from the given uart, this is a non-blocking call.
 * Returns 0 if there are no character available.
 * Returns 1 if a character was read.
 */
int uart_receive(int uart, unsigned char *s) {
    unsigned short* uart_fr = (unsigned short*) (uart + UART_FR);
    unsigned short* uart_dr = (unsigned short*) (uart + UART_DR);
    if (*uart_fr & UART_RXFE)
        return 0;
    *s = (*uart_dr & 0xff);
    return 1;
}

/**
 * Sends a character through the given uart, this is a blocking call.
 * The code spins until there is room in the UART TX FIFO queue to send
 * the character.
 */
void uart_send(int uart, unsigned char s) {
    unsigned short* uart_fr = (unsigned short*) (uart + UART_FR);
    unsigned short* uart_dr = (unsigned short*) (uart + UART_DR);
    while (*uart_fr & UART_TXFF)
        ;
    *uart_dr = s;
}

/**
 * This is a wrapper function, provided for simplicity,
 * it sends a C string through the given uart.
 */
void uart_send_string(int uart, const unsigned char *s) {
    while (*s != '\0') {
        uart_send(uart, *s);
        s++;
    }
}

/*
 * Function to enable vic
 */
void vic_irq_enable() {
    int* vic_addr = (int*)(PICIntEnable);
    *(vic_addr) =  UART0_IRQ_MASK;
}

void uart_irq_enable() {
    int* uart_addr = (int*)(UART0 + UART_IMSC);
    *(uart_addr) =  UART_RXRIS;
}