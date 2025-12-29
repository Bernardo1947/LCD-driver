/*
 * File:        lcd.h
 * Author:      Dennis Bernardo
 *
 * Created on:  25th January de 2025, 19:18
 * Description: Header file to interface with 16x2 LCDs
 *
 * Only the instruction register (IR) and the data register (DR) can be controlled, so this driver only interface
 * with these two registers.
 * The signals sent to the internal LCD controller is determined by the signals from pins RS, (R/~W), EN and the data
 * bus (DB0 to DB7 or DB4 to DB7)
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

#define LCD_DATA_PORT                               PORTD
#define LCD_DATA_VALUE                              TRISD
#define LCD_CTRL_PORT                               PORTE
#define LCD_CTRL_VALUE                              TRISE

#define LCD_RW                                      PORTEbits.RE0
#define LCD_EN                                      PORTEbits.RE1
#define LCD_RS                                      PORTEbits.RE2


#define                                             LCD_START(NP, NR, ND) (NP | NR | ND | 0x20)
#define LCD_CLEAR                                   (unsigned char) 0x01
#define LCD_RETURN_HOME                             (unsigned char) 0x02
#define LCD_DISPLAY_OFF                             (unsigned char) 0x08
#define LCD_DISPLAY_ON_CURSOR_OFF                   (unsigned char) 0x0C
#define LCD_DISPLAY_ON_CURSOR_ON                    (unsigned char) 0x0E
#define LCD_DISPLAY_ON_CURSOR_BLINK                 (unsigned char) 0x0F
#define LCD_SET_ENTRY_MOD                           (unsigned char) 0x06
#define LCD_SHIFT_RIGHT                             (unsigned char) 0x1C
#define LCD_SHIFT_LEFT                              (unsigned char) 0x18
#define LCD_CURSOR_RIGHT                            (unsigned char) 0x14
#define LCD_CURSOR_LEFT                             (unsigned char) 0x10

#define DATA_LENGTH_8_PINS                          0x10
#define DATA_LENGTH_4_PINS                          0x00
#define DISPLAY_2_ROWS                              0x08
#define DISPLAY_1_ROW                               0x00
#define DOTS_10                                     0x04
#define DOTS_8                                      0x00


/* LCD initialization functions */

void lcd_init(char, char, char);

/* LCD display's settings functions */
void lcd_clear(void);
void lcd_cursor_on(void);
void lcd_cursor_blink_off(void);
void lcd_cursor_blink_on(void);
void lcd_cursor_off(void);
void shift_cursor_left(int);
void shift_cursor_right(int);
void lcd_set_position(int, int);

/* LCD display's data writing functions */
int lcd_write_str(char *);
int lcd_write_char(unsigned char);
int lcd_write_int(int);

/* Static functions to communicate with the LCD driver HD44780 */
static void lcd_command(unsigned char);
static void lcd_send_data(unsigned char);

#endif	/* LCD_H */

