#ifndef MY2C_H
#define	MY2C_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdint.h>

void MY2C_init(void);

void MY2C_write(uint8_t address, uint8_t cmd);

void MY2C_read(uint8_t address, uint8_t *data, uint8_t len);

void MY2C_readNByteRegister(uint8_t address, uint8_t reg, uint8_t *data, uint8_t len);
    
uint16_t MY2C_read2ByteRegister(uint8_t address, uint8_t reg);

#ifdef	__cplusplus
}
#endif

#endif	/* MY2C_H */

