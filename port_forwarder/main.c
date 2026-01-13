#include "hardware/pio.h"
#include "port_forward.pio.h"

void port_forward_init()
{
    PIO pio;
    uint sm;
    // from, to 12, 13
    uint offset;
    bool success = pio_claim_free_sm_and_add_program_for_gpio_range(&port_forward_program, &pio, &sm, &offset, 22, 4, true);
    hard_assert(success);
    port_forward_program_init(pio, sm, offset, 22, 25);
}

int main()
{
    port_forward_init();

    while (true)
    {
        sleep(1000);
    }
}