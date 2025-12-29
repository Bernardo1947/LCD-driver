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


/*
 * @description:    Initialize the LCD, setting all the proper settings received
 * @params:         (char) pins - Number of pins used, receives 4 or 8. Default is 4 pins
 *                  (char) rows - Number of rows used, 2 or 1. Default is 1 row
 *                  (char) dots - Number of dots to be used on each character, may be 10 or 8. Default is 8 dots
 *
 */
static unsigned char data_length = 0;

void lcd_init(char pins, char rows, char dots) {
    /* Set the parameters according to the LCD driver */
    data_length = pins == (char) 8 ? DATA_LENGTH_8_PINS : DATA_LENGTH_4_PINS;
    char display_rows = rows == (char) 2 ? DISPLAY_2_ROWS : DISPLAY_1_ROW;
    char dot_format = dots == (char) 10 ? DOTS_10 : DOTS_8;

    /* Disable AD channel in order to PORTE pins work as GPIO */
    ADCON1 = 0x06;
    LCD_DATA_PORT = LCD_CTRL_PORT = 0;
    LCD_DATA_VALUE = LCD_CTRL_VALUE = 0;

    /* The busy state after initializing the LCD lasts for 15ms, so 20ms is used to ensure unexpected errors */
    __delay_ms(20);
    /* The following commands are defined in the LCD driver HD44780 for the properly initialization */
    lcd_command(LCD_START(data_length, display_rows, dot_format));
    __delay_ms(5);
    lcd_command(LCD_START(data_length, display_rows, dot_format));
    __delay_us(200);
    lcd_command(LCD_START(data_length, display_rows, dot_format));

    lcd_command(LCD_DISPLAY_OFF);
    lcd_command(LCD_CLEAR);
    __delay_ms(2);
    lcd_command(LCD_SET_ENTRY_MOD);
    lcd_command(LCD_DISPLAY_ON_CURSOR_ON);
}

/*
 * @description:    Clear the LCD current data displayed
 */
void lcd_clear(void) {
    lcd_command(LCD_CLEAR);
    __delay_ms(2);
}

/*
 * @description:    Turns on the cursor
 */
void lcd_cursor_on(void) {
    lcd_command(LCD_DISPLAY_ON_CURSOR_ON);
}

/*
 * @description:    Turns off the cursor
 */
void lcd_cursor_off(void) {
    lcd_command(LCD_DISPLAY_ON_CURSOR_OFF);
}

/*
 * @description:    Turns on the cursor blink
 */
void lcd_cursor_blink_on(void) {
    lcd_command(LCD_DISPLAY_ON_CURSOR_BLINK);
}

/*
 * @description:    Turns off the cursor blink
 */
void lcd_cursor_blink_off(void) {
    lcd_command(LCD_DISPLAY_ON_CURSOR_ON);
}

/*
 * @description:    Shift the cursor to the left by amount characters. Must be aware to move inside the LCD boundaries
 * @params:         (int) amount - Amount of characters to be shifted to the left
 */
void shift_cursor_left(int amount) {
    while (amount--)
        lcd_command(LCD_CURSOR_LEFT);
}

/*
 * @description:    Shift the cursor to the right by amount characters. Must be aware to move inside the LCD boundaries
 * @params:         (int) amount            Amount of characters to be shifted to the right
 */
void shift_cursor_right(int amount) {
    while (amount--)
        lcd_command(LCD_CURSOR_RIGHT);
}

/*
 * @description:    Set position on LCD. Restricted to the LCD boundaries
 * @params:         (int) row               Row of the LCD (first row begins at 1)
 *                  (int) column            Column of the LCD (first column begins at 1)
 */
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

/*
 * @description:    Send a string to the LCD, starting from its current position
 * @params :        (char*) str             String to be sent to the display
 * @return:         Return an integer related to the amount of characters sent to the display
 */
int lcd_write_str(char *str) {
    LCD_RS = 1;
    int idx = 0;
    while (*(str + idx))
        lcd_write_char(*(str + idx++));
    return idx;
}

/*
 * @description:    Send a character to the LCD
 * @params :        (unsigned char) ch      Character to be sent to the display
 * @return:         Returns the character sent in int form
 */
int lcd_write_char(unsigned char ch) {
    LCD_RS = 1;
    lcd_send_data(ch);
    return ch;
}

/*
 * @description:    Send an integer to the display. Be aware of this function usage, as it consumes more memory in
 *                  limited devices
 * @params :        (int) integer           Integer to be sent to the display
 * @return:         Returns the integer sent
 */
int lcd_write_int(int integer) {
    LCD_RS = 1;
    char text[6];
    sprintf(text, "%d", integer);
    lcd_write_str(text);
    return integer;
}

/*
 * @description:    Execute a command from LCD's internal functions. RS pin must be 0 when the byte is sent. This
 * function must not be used outside this file
 * @params :        (unsigned char) byte    Command to be sent to the display. Usually one of the macros defined
 */
static void lcd_command(unsigned char byte) {
    LCD_RS = 0;
    LCD_RW = 0;
    lcd_send_data(byte);
}

/*
 * @description:    Send a data byte to the LCD on the current position. RS pin must be 1 when the byte is sent. * This function must not be used outside this file
 * @params :        (unsigned char) byte    Data to be sent to the display or to execute a command
 */
static void lcd_send_data(unsigned char byte) {
    if (data_length == DATA_LENGTH_8_PINS) {
        LCD_DATA_PORT = byte;
        LCD_EN = 1;
        __delay_us(40);
        LCD_EN = 0;
    } else {
        LCD_DATA_PORT = byte & 0xF0;
        LCD_EN = 1;
        __delay_us(40);
        LCD_EN = 0;
        __delay_us(100);
        LCD_DATA_PORT = (byte << 4) & 0xF0;
        LCD_EN = 1;
        __delay_us(40);
        LCD_EN = 0;
    }
}