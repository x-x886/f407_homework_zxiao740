//in taskled.cpp
#include "main.h"
#include "tx_api.h"

TX_THREAD led_thread;
uint8_t led_thread_stack[1024]={0};

[[noreturn]] void led_thread_entry(ULONG thread_input){

    UNUSED(thread_input);

    while (1) {
        // Implement the LED control functionality here
        HAL_GPIO_WritePin(GPIOH, GPIO_PIN_10, GPIO_PIN_SET);
        HAL_Delay(100);
        HAL_GPIO_WritePin(GPIOH, GPIO_PIN_10, GPIO_PIN_RESET);
        HAL_Delay(100);
        tx_thread_sleep(1);
    }
}
// in taskbooster.cpp
#include "taskbooster.hpp"

#include "main.h"
#include "tx_api.h"

extern TX_THREAD led_thread;
extern uint8_t led_thread_stack[1024];
extern void led_thread_entry(ULONG thread_input);

#define TX_NAME(s) const_cast<CHAR*>(s)
extern "C" void taskbooster(void)
{
    // Implement the task booster functionality here  
    tx_thread_create(&led_thread, TX_NAME("LED Thread"), led_thread_entry, 0x1234,
                     led_thread_stack, sizeof(led_thread_stack),
                     10, 10, TX_NO_TIME_SLICE, TX_AUTO_START);
}
