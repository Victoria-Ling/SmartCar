#include "Myfile.h"

uint8 uart_buff;
uint8 fullcharge_flag = 0;

void send_data1(int16 dat)
{
    uint8 a[5];
    uint8 i=0;
    a[0] = dat / 256;
    a[1] = dat % 256;
    while(i < 2)
    {
        uart_write_byte(UART_7, a[i]);
        i++;
    }
}
void send_data2(int16 dat)
{
    uint8 a[5];
    uint8 i=0;
    a[0] = dat / 256;
    a[1] = dat % 256;
    while(i < 2)
    {
        uart_write_byte(UART_4,a[i]);
        i++;
    }
}

void receive_data2(void)
{
    if(fullcharge_flag == 0 && uart_query_byte(UART_4, &uart_buff))
    {
        if(uart_buff == 'a')
        {
            fullcharge_flag = 1;
        }
    }
}

void receive_data1(void)
{

}



void communicate(void)
{

}
