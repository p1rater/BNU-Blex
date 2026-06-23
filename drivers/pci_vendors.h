/* pci_vendors.h – auto-generated from pci.ids */
#ifndef PCI_VENDORS_H
#define PCI_VENDORS_H
#include <stdint.h>
#define PCI_VENDOR_MAX 2503

const char* pci_vendor_name(uint16_t vendor_id);
int pci_vendor_count(void);
#endif
