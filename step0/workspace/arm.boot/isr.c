//
// Created by thomas on 26/01/2021.
//
#include "isr.h"
#include "kprintf.h"
#include "uart.h"

volatile unsigned char buffer[MAX_CHARS];
volatile int head = 0;
volatile int tail = 0;

void isr() {
    unsigned char value;
    int code = 1;
    if (!uart_receive(UART0, &value)) {
        kprintf("erreur");
    }
    while (code) {
        int next = (head + 1) % MAX_CHARS;
        if (next == tail) return;
        buffer[head] = value;
        head = next;
        code = uart_receive(UART0, &value);
    }

}
