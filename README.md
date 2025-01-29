# LCD-driver description
LCD driver to connect to microcontrollers.

Be aware it is written for PIC microcontrollers, but can be used in another families as well.

# Driver information

This driver is completely supported for PIC microcontrollers from any PIC1x family. May be used in 32 bits microcontrollers too. To use it in other microcontrollers, please refer to the [this section.](#how-to-use-this-driver-in-any-microcontroller)

## Functions Description

All the functions developed in the driver are described in details here:

### lcd_init()

Initialize the LCD, setting it as 8-bit data and with 2 rows. (Will be improved in the future to support more display's size and to support 4-bit format data too)

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

# Current commit's message

