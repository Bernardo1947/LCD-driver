/*
 * File:        lcd.c
 * Author:      Dennis Bernardo
 *
 * Created on:  25th January de 2025, 19:18
 * Description:
 */

#include <xc.h>
#include <stdio.h>

#include "lcd.h"


void lcd_init(void) {
    ADCON1 = 0x06;
    TRISE = TRISD = 0;
    /* The busy state after initializing the LCD lasts for 15ms, so 20ms is used to ensure unexpected errors */
    __delay_ms(20);
    lcd_command(LCD_START);
    __delay_ms(5);
    lcd_command(LCD_START);
    __delay_us(200);
    lcd_command(LCD_START);
    lcd_command(LCD_DISPLAY_OFF);
    lcd_command(LCD_CLEAR);
    lcd_command(LCD_SET_ENTRY_MOD);
    lcd_command(LCD_DISPLAY_ON);

}


void lcd_command(unsigned char byte) {
    LCD_RS = 0;
    lcd_send_data(byte);
}


void lcd_clear(void) {
    lcd_command(LCD_CLEAR);
}


void lcd_set_position(int row, int column) {
    if (row < 1 || row > 2)
        row = 1;
    int display_position = (row - 1) * 0x40;
    if (column < 1 || column > 16)
        column = 1;
    display_position += column - 1;
    display_position |= 0x80;
    lcd_command((unsigned char) display_position);
}


int lcd_write_str(char *str) {
    LCD_RS = 1;
    int idx = 0;
    while (*(str + idx))
        lcd_write_char(*(str + idx++));
    return idx;
}


int lcd_write_char(unsigned char ch) {
    LCD_RS = 1;
    lcd_send_data(ch);
    return ch;
}


int lcd_write_int(int integer) {
    LCD_RS = 1;
    char text[10];
    sprintf(text, "%d", integer);
    lcd_write_str(text);
    return integer;
}


static void lcd_send_data(unsigned char byte) {
    LCD_PORT = byte;
    LCD_EN = 1;
    __delay_us(2000);
    LCD_EN = 0;
}