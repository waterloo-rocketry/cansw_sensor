#ifndef SPI_H
#define SPI_H

#include <stdint.h>

void spi_init();
void spi_write(uint8_t data);
uint8_t spi_read();
void chip_select_init();

void imu1_spi_select();
void imu1_spi_release();

void imu2_spi_select();
void imu2_spi_release();

void baro_spi_select();
void baro_spi_release();

#endif
