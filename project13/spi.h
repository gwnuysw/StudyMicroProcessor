#ifndef SPI_H
#define SPI_H
void spi_init();
void spi_select();
void spi_release();
void spi_write(uint8_t data);
#endif
