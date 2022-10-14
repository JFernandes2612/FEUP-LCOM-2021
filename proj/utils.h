#ifndef _UTILS_PROJ
#define _UTILS_PROJ

#include <lcom/lcf.h>

/**
 * @brief Gets from @p port 8 bit information to @p value
 *
 * @param port port to get the information from
 * @param value return values for this input operation
 *
 * @return int 1 if it fails 0 otherwise
 */
int(util_sys_inb)(int port, uint8_t *value);

#endif
