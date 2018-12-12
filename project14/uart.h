#ifndef UART_H
#define UART_H
void uart_init();
int uart_putchar(char ch, FILE *stream);
int uart_getchar(FILE *stream);
#endif
