//
// Created by thomas on 26/01/2021.
//

#ifndef M2M_ISR_H
#define M2M_ISR_H
#include "uart.h"

void isr();
extern volatile unsigned char buffer[MAX_CHARS];
extern volatile int head;
extern volatile int tail;


#endif //M2M_ISR_H
