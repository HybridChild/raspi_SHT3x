#include <stdio.h>  // printf

/* TO USE CONSOLE OUTPUT (printf) YOU MAY NEED TO ADAPT THE
 * INCLUDE ABOVE OR DEFINE IT ACCORDING TO YOUR PLATFORM.
 * #define printf(...)
 */

#include "sht3x.h"

int main(void)
{
    /* Initialize the i2c bus for the current platform */
    sensirion_i2c_init();

    /* Busy loop for initialization, because the main loop does not work without
     * a sensor.
     */
    while (sht3x_probe(SHT3X_I2C_ADDR_DFLT) != STATUS_OK)
    {
        printf("SHT sensor probing failed\n");
    }

    printf("SHT sensor probing successful\n");

    while (1)
    {
        int32_t temperature, humidity;
        /* Measure temperature and relative humidity and store into variables
         * temperature, humidity (each output multiplied by 1000).
         */
        int8_t ret = sht3x_measure_blocking_read(SHT3X_I2C_ADDR_DFLT,
                                                 &temperature, &humidity);
        if (ret == STATUS_OK)
        {
            printf("measured temperature: %0.2f degreeCelsius, "
                   "measured humidity: %0.2f percentRH\n",
                   temperature / 1000.0f, humidity / 1000.0f);
        }
        else
        {
            printf("error reading measurement\n");
        }

        sensirion_sleep_usec(1000000);
    }

    return 0;
}
