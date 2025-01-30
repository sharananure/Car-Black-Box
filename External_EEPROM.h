#ifndef External_EEPROM_H
#define External_EEPROM_H

#define SLAVE_READ_EEPROM		0xA1   // Read
#define SLAVE_WRITE_EEPROM		0xA0   // write

void write_external_eeprom(unsigned char address1,  unsigned char data);
unsigned char read_external_eeprom(unsigned char address1);

#endif