
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "app_uart.h"
#include "app_error.h"
#include "nrf_delay.h"
#include "nrf.h"
#include "bsp.h"
#include "nrf_uart.h"
#include "nrf_uarte.h"

#define UART_TX_BUFF_SIZE 128 // Размер буффера для UART_TX
#define UART_RX_BUFF_SIZE 128 // Размер буффера для UART_RX

#define UART_HWFC APP_UART_FLOW_CONTROL_DISABLED  // Отключает аппартаное управление потоком(так как мы не используем очень высокую скорость)


/**
 * @brief Function for main application entry.
 */

/*
void uart_err_handle(app_uart_evt_type_t * p)  // Обработчик ошибок UART
{
  
}
*/

int main(void)
{
  uint32_t err_code; // Код ошибки
  bsp_board_init(BSP_INIT_LEDS); // Инициализация светодиодов
  
  const app_uart_comm_params_t com_params =   // Констатнты для UART
  {
    RX_PIN_NUMBER,  // ПИН RX
    TX_PIN_NUMBER,  // ПИН TX
    RTS_PIN_NUMBER, // ПИН RTS
    CTS_PIN_NUMBER, // ПИН CTS
    UART_HWFC,      // Аппаратное управление потоком(отключаем)
    false,          // Чётность (приоритета нет)
    NRF_UART_BAUDRATE_115200 // Скорость передачи данных
  };
  
  APP_UART_FIFO_INIT(&com_params, UART_RX_BUFF_SIZE, UART_TX_BUFF_SIZE, 0, APP_IRQ_PRIORITY_LOWEST, err_code); // Инициализация UART
  /* (АДРЕСС, Размер буфера для приёма, размер буффера для передачи, Обработчик ошибок, низкий приоритет, код ошибки) */
  
  
  APP_ERROR_CHECK(err_code);  // Проверка на ошибку
  
  
  printf("Hello PC \r\n");
  
  while(true)
  {
    uint8_t aRead; // Переменная, отвечает за включение светодиодов
    
    while(app_uart_get(&aRead) != NRF_SUCCESS); // Зацикливаемся, пока не получим верно
    
    if(aRead == 't')  // Если отправляем t, то вкл
    {
      bsp_board_leds_on();
      printf("Leds ON! \r\n");
    }
    
    if(aRead == 'k') // Если отправляем k, то выкл
    {
      bsp_board_leds_off();
      printf("Leds OFF! \r\n");
    }
    
    
  }
  
}


/** @} */
