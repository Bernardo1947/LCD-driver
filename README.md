# LCD-driver description
LCD driver to connect to microcontrollers.

Be aware it is written for PIC microcontrollers, but can be used in another families as well.










# Driver information

This driver is completely supported for PIC microcontrollers from any PIC1x family. May be used in 32 bits microcontrollers too. To use it in other microcontrollers, please refer to the [this section.](#how-to-use-this-driver-in-any-microcontroller)

## Driver Functions Description

All the functions developed in the driver and available to be used are described in details here:





### void lcd_init (char pins, char row, char dots)

Start the LCD, executing the routine to properly initialize it. These settings include 4 or 8-bit data, 1 or 2 rows, and if each character will have 5x8 or 5x10 dots. This function must be executed only once and before any other functions.

**Parameters**

* (char) **pins** - Number of pins used, receives 4 or 8. Default is 4 pins.
* (char) **rows** - Number of rows used, 2 or 1. Default is 1 row.
* (char) **dots** - Number of dots to be used on each character, may be 10 or 8. Default is 8 dots.

### void lcd_clear (void)

Clear the LCD's current displayed data.


### void lcd_cursor_on (void)

Turn on LCD's cursor.


### void lcd_cursor_off (void)

Turn off LCD's cursor.


### void lcd_cursor_blink_on (void)

Turn on LCD's cursor blinking.


### void lcd_cursor_blink_off (void)

Turn off LCD's cursor blinking.


### void shift_cursor_left (int amount)

Shift the cursor to the left by amount characters. Must be aware to move inside the LCD boundaries.

**Parameters**

* (int) **amount** - Amount of characters to be shifted to the left.


### void shift_cursor_right (int amount)

Shift the cursor to the right by amount characters. Must be aware to move inside the LCD boundaries.

**Parameters**

* (int) **amount** - Amount of characters to be shifted to the right.


### void lcd_set_position (int row, int column)

Set position on LCD. Restricted to the LCD boundaries. If an invalid number is sent on any of the parameters, the respective parameter will be set to 1.

**Parameters**

* (int) **row** - Row of the LCD (first row begins at 1).
* (int) **column** - Column of the LCD (first column begins at 1).

**Return**

Return an integer related to the amount of characters sent to the display.


### int lcd_write_str (char *str)

Send a string to the LCD, starting from its current position. The string must be in char* format. If the string is longer than the remaining line space, the LCD's display will show an unexpected text. RS pin must be 1 before sending the data.

**Parameters**

* (char*) **str** - String to be sent to the display.

**Return**

Return an integer related to the amount of characters sent to the display.


### lcd_write_char (unsigned char ch)

Send a character to the LCD. Must be aware of the current LCD's cursor position. RS pin must be 1 before sending the data.


**Parameters**

* (unsigned char) **ch** - Character to be sent to the display.

**Return**

Returns the character sent in int form.


### lcd_write_int (int integer)

Send an integer to the display. Be aware of this function usage, as it consumes a higher memory amount in limited devices due to the C standard library **stdio** used on its implementation. The resulted string sent will depend from how many digits the number has, up to 5 characters. RS pin must be 1 before sending the data.


**Parameters**

* (int) **integer** - Integer to be sent to the display.

**Return**

Returns the integer sent





## Static Functions Definitions

The static functions (or functions available to be used only the current's file (lcd.c)) are described here. These functions should not be changed to normal functions, as these ones are only used internally by the driver functions.


### static void lcd_command (unsigned char byte)

Execute a command from LCD's internal functions. RS pin must be 0 when the byte is sent in order to send a command, writing a byte in the LCD HD44780 driver's internal register IR (instruction register).

This function must not be used outside this file.

**Parameters**

* (unsigned char) **byte** - Byte related to the command sent to the LCD HD44780 driver.


### static void lcd_send_data (unsigned char byte)

Send a data byte to the LCD on the current position. RS pin must be 0 or 1 when the byte is sent, depending from which register must be written. For IR (instruction register), RS must be 0; for DR (data register), RS must be 1.

This function must not be used outside this file.

**Parameters**

* (unsigned char) **byte** - Data to be sent to the display or to execute a command





## Macros 

All the macros defined in the header file are described in the table below:

| Macro name    | Function |
| ------------- | ------- |
|        |    |
|       |      |
|          |     |




# How to use this driver in any microcontroller

* Connect two GPIOs to the RS and E pins from the LCD

* Refactor the following code lines in the header lcd.h file

    ```
    #define LCD_EN                                      PORTEbits.RE1
    #define LCD_RS                                      PORTEbits.RE2
    ```

    ```
    #define LCD_EN                                      <PIN1>
    #define LCD_RS                                      <PIN2>
    ```

*  Connect all pins from a 8-pins-port and address it, refactoring the line:

    ```
    #define LCD_PORT                                    PORTD
    ```
    ```
    #define LCD_PORT                                    <PORT_NAME>
    ```