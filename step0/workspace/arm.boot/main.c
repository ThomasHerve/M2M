#include "main.h"
#include "kprintf.h"
#include "uart.h"
#include "isr.h"



/*
 * Define ECHO_ZZZ to have a periodic reminder that this code is polling
 * the UART, actively. This means the processor is running continuously.
 * Polling is of course not the way to go, the processor should halt in
 * a low-power state and wake-up only to handle an interrupt from the UART.
 * But this would require setting up interrupts...
 */
#define ECHO_ZZZ

/**
 * This is the C entry point, upcalled once the hardware has been setup properly
 * in assembly language, see the startup.s file.
 */
void _irqs_setup(void);
void _irqs_enable(void);
void _copy_vector(void);
void _wfi(void);


void c_entry() {
    _copy_vector();
    _irqs_setup();
    uart_irq_enable();
    vic_irq_enable();
    _irqs_enable();

  uart_send_string(UART0, "\nHello world!\n");
  uart_send_string(UART0, "\nQuit with \"C-a c\" and then type in \"quit\".\n");
  int eol = 0;
    for (;;) {
        while (eol != head) {
            kprintf("%c", buffer[eol]);
            eol = (eol + 1) % MAX_CHARS;
        }
        _wfi();
    }
}