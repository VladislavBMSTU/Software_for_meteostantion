#include <stdbool.h>
#include "nrf.h"
#include "nrf_drv_gpiote.h"
#include "app_error.h"
#include "boards.h"

#define LED1 7
#define Button1 5

void input_pin_handle(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
  nrf_gpio_pin_toggle(LED1);  // Переключение светодиода
}



void gpio_init()
{
    
  ret_code_t err_code;  // hold err value
  
  err_code = nrf_drv_gpiote_init(); // Иницилизация GPIO
  APP_ERROR_CHECK(err_code);  // Проверка ошибок
  
  nrf_gpio_cfg_output(LED1);  // Светодиод на выход
  nrf_gpio_pin_set(LED1); // Выкл светодиод
  
  nrf_drv_gpiote_in_config_t in_config = GPIOTE_CONFIG_IN_SENSE_HITOLO(true); // (true) - до 16МГц, (false) - низкочастотные
  in_config.pull = NRF_GPIO_PIN_PULLUP;
  
  err_code = nrf_drv_gpiote_in_init(Button1, &in_config, input_pin_handle);
  APP_ERROR_CHECK(err_code);
  
  nrf_drv_gpiote_in_event_enable(Button1, true);
  
  
}


/**
 * @brief Function for application main entry.
 */

int main(void)
{
    gpio_init();

    while (true)
    {
        // Do nothing.
    }
}


/** @} */
