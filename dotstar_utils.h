#ifndef DOTSTAR_UTILS_H
#define DOTSTAR_UTILS_H

#include <stdint.h>
#include <stddef.h>

void dotstar_init();

void dotstar_write_pattern(uint32_t const *buffer, size_t len);

#endif