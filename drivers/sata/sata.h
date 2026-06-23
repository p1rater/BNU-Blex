#ifndef DRIVERS_SATA_H
#define DRIVERS_SATA_H
#include "../../kernel_utils.h"
void ata_init(void);
int  ata_read_sectors(int drive, uint32_t lba, uint8_t count, uint16_t *buf);
int  ata_write_sectors(int drive, uint32_t lba, uint8_t count, const uint16_t *buf);
extern ata_drive_t ata_drives[ATA_MAX_DRIVES];
#endif
