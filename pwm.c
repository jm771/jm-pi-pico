/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "pwm.pio.h"
#include "pwm.h"

// Write `period` to the input shift register
void pio_pwm_set_period(PIO pio, uint sm, uint32_t period)
{
    pio_sm_set_enabled(pio, sm, false);
    pio_sm_put_blocking(pio, sm, period);
    pio_sm_exec(pio, sm, pio_encode_pull(false, false));
    pio_sm_exec(pio, sm, pio_encode_out(pio_isr, 32));
    pio_sm_set_enabled(pio, sm, true);
}

// Write `level` to TX FIFO. State machine will copy this into X.
void pio_pwm_set_level(PIO pio, uint sm, uint32_t level)
{
    pio_sm_put_blocking(pio, sm, level);
}

static PIO pio;
static uint offset;

void pwm_install_program()
{
    pio = pio0;
    offset = pio_add_program(pio0, &pwm_program);
}

// returns state machine
uint pwm_init(uint pin)
{
    uint sm = pio_claim_unused_sm(pio, true);
    pwm_program_init(pio, sm, offset, pin);
    pio_pwm_set_period(pio, sm, (1u << 16) - 1);

    return sm;
}

void pwm_set_level(uint sm, uint32_t level)
{
    printf("%lu\n", level);
    pio_pwm_set_level(pio, sm, level << 8);
}
