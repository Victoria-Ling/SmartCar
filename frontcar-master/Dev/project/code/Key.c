#include "Myfile.h"

unsigned char Key_Number = 0;
unsigned char Key_Switch = 0;

void Key_Scan(void)
{
    Key_Number = 0;

    gpio_set_level(C7, 1);
    gpio_set_level(A8, 0);
    gpio_set_level(B0, 0);
    if(gpio_get_level(B12) == 1)        {system_delay_ms(20); if(gpio_get_level(B12) == 1) {while(gpio_get_level(B12) == 1); Key_Number = 9; }}
    else if(gpio_get_level(D8) == 1)    {system_delay_ms(20); if(gpio_get_level(D8) == 1) {while(gpio_get_level(D8) == 1); Key_Number = 8; }}
    else if(gpio_get_level(C6) == 1)    {system_delay_ms(20); if(gpio_get_level(C6) == 1) {while(gpio_get_level(C6) == 1); Key_Number = 7; }}

    gpio_set_level(C7, 0);
    gpio_set_level(A8, 1);
    gpio_set_level(B0, 0);
    if(gpio_get_level(B12) == 1)        {system_delay_ms(20); if(gpio_get_level(B12) == 1) {while(gpio_get_level(B12) == 1); Key_Number = 6; }}
    else if(gpio_get_level(D8) == 1)    {system_delay_ms(20); if(gpio_get_level(D8) == 1) {while(gpio_get_level(D8) == 1); Key_Number = 5; }}
    else if(gpio_get_level(C6) == 1)    {system_delay_ms(20); if(gpio_get_level(C6) == 1) {while(gpio_get_level(C6) == 1); Key_Number = 4; }}

    gpio_set_level(C7, 0);
    gpio_set_level(A8, 0);
    gpio_set_level(B0, 1);
    if(gpio_get_level(B12) == 1)        {system_delay_ms(20); if(gpio_get_level(B12) == 1) {while(gpio_get_level(B12) == 1); Key_Number = 3; }}
    else if(gpio_get_level(D8) == 1)    {system_delay_ms(20); if(gpio_get_level(D8) == 1) {while(gpio_get_level(D8) == 1); Key_Number = 2; }}
    else if(gpio_get_level(C6) == 1)    {system_delay_ms(20); if(gpio_get_level(C6) == 1) {while(gpio_get_level(C6) == 1); Key_Number = 1; }}
}

void Key_ON(void)
{
    if(gpio_get_level(C6) == 1)    {system_delay_ms(20); if(gpio_get_level(C6) == 1) {while(gpio_get_level(C6) == 1); Key_Switch = !Key_Switch; }}
}

