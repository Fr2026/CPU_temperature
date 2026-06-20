#include <driver/gpio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <driver/temperature_sensor.h>


extern "C" void app_main(void)
{
    gpio_config_t io_conf = {
            .pin_bit_mask = (1ULL << GPIO_NUM_0),
            .mode = GPIO_MODE_INPUT,
            .pull_up_en = GPIO_PULLUP_ENABLE,
            .pull_down_en = GPIO_PULLDOWN_DISABLE,
            .intr_type = GPIO_INTR_DISABLE,
        };
    gpio_config(&io_conf);
    temperature_sensor_config_t t = {
        .range_min = 10,
        .range_max = 50,
    };
    temperature_sensor_handle_t temp_handle = NULL;
    ESP_ERROR_CHECK(temperature_sensor_install(&t, &temp_handle));
    temperature_sensor_enable(temp_handle);
    int count = 1;

    while (true)
    {
        int a = gpio_get_level(GPIO_NUM_0);
        if (a == 0){
            float tsens_out;
            temperature_sensor_get_celsius(temp_handle, &tsens_out);
            printf("第%d次 ",count);
            printf("CPU 温度： %.2f °C\n", tsens_out);
            count++;
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
    //temperature_sensor_uninstall(temp_handle); 
}