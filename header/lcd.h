/*
 * File:        lcd.h
 * Author:      Dennis Bernardo
 *
 * Created on:  25th January de 2025, 19:18
 * Description: Header file to interface with 16x2 LCDs
 *
 * Only the instruction register (IR) and the data register (DR) can be controlled, so this driver only interface
 * with these two registers.
 * The signals sent to the internal LCD controller is determined by the signals from pins RS, (R/~W) and the data bus
 * (DB0 to DB7)
 *
 * There are four categories of instructions allowed by the LCD controller:
 *      Designate functions, sunch as display format, data length, etc.
 *      Set internal RAM addresses
 *      Perfom data transfer with internal RAM
 *      Perform miscellaneous functions
 */

#ifndef LCD_H
#define	LCD_H

#ifndef _XTAL_FREQ
#define _XTAL_FREQ                                  4000000
#endif

#define LCD_EN                                      PORTEbits.RE1
#define LCD_RS                                      PORTEbits.RE2
#define LCD_PORT                                    PORTD


#define LCD_START                                   (unsigned char) 0x38
#define LCD_CLEAR                                   (unsigned char) 0x01
#define LCD_DISPLAY_OFF                             (unsigned char) 0x08
#define LCD_DISPLAY_ON                              (unsigned char) 0x0F
#define LCD_SET_ENTRY_MOD                           (unsigned char) 0x06
#define LCD_SHIFT_RIGHT                             (unsigned char) 0x1C
#define LCD_SHIFT_LEFT                              (unsigned char) 0x18


void lcd_init(void);
void lcd_command(unsigned char);
void lcd_clear(void);
void lcd_set_position(int, int);
int lcd_write_str(char *);
int lcd_write_char(unsigned char);
int lcd_write_int(int);
static void lcd_send_data(unsigned char);

#endif	/* LCD_H */

