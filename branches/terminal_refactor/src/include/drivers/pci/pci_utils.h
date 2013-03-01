/**
 * @file
 *
 * @brief
 *
 * @date 28.06.2011
 * @author Anton Bondarev
 */

#ifndef PCI_UTILS_H_
#define PCI_UTILS_H_

#include <stdint.h>

extern int pci_is_supported(void);

extern uint32_t pci_read_config8(uint32_t bus, uint32_t dev_fn,
				uint32_t where, uint8_t *value);

extern uint32_t pci_read_config16(uint32_t bus, uint32_t dev_fn,
				uint32_t where, uint16_t *value);

extern uint32_t pci_read_config32(uint32_t bus, uint32_t dev_fn,
				uint32_t where, uint32_t *value);

extern uint32_t pci_write_config8(uint32_t bus, uint32_t dev_fn,
				uint32_t where, uint8_t value);

extern uint32_t pci_write_config16(uint32_t bus, uint32_t dev_fn,
				uint32_t where, uint16_t value);

extern uint32_t pci_write_config32(uint32_t bus, uint32_t dev_fn,
				uint32_t where, uint32_t value);

#endif /* PCI_UTILS_H_ */
