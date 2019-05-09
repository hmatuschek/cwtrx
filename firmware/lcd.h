// Ansteuerung eines HD44780 kompatiblen LCD im 4-Bit-Interfacemodus
// http://www.mikrocontroller.net/articles/AVR-GCC-Tutorial/LCD-Ansteuerung
//

#ifndef __LCD_H__
#define __LCD_H__

#include <avr/io.h>
#include <stdint.h>

#define LCD_PORT   PORTD
#define LCD_DDR    DDRD
#define LCD_DB     PD0
#define LCD_RS     PD5
#define LCD_EN     PD6


/* Initialisierung: muss ganz am Anfang des Programms aufgerufen werden. */
void lcd_init(void);

/* LCD löschen */
void lcd_clear(void);

/* Cursor in die 1. Zeile, 0-te Spalte */
void lcd_home(void);

/* Cursor an eine beliebige Position */
void lcd_setcursor(uint8_t spalte, uint8_t zeile);

/* Ausgabe eines einzelnen Zeichens an der aktuellen Cursorposition */
void lcd_data(uint8_t data);

/* Ausgabe eines Strings an der aktuellen Cursorposition */
void lcd_string(const char *data);

/* Ausgabe eines Strings an der aktuellen Cursorposition */
void lcd_freq(uint32_t freq);

void lcd_print_uint16(uint16_t value, uint8_t width);
void lcd_print_pllcorr(int32_t value);
void lcd_print_int32(int32_t value, uint8_t width);

/* Definition eines benutzerdefinierten Sonderzeichens.
 * data muss auf ein Array[8] mit den Zeilencodes des zu definierenden Zeichens
 * zeigen. Später können diese mit lcd_data(0-7) aufgerufen werden */
void lcd_generatechar(uint8_t addr, const uint8_t *data);

/* Ausgabe eines Kommandos an das LCD. */
void lcd_command(uint8_t data);


#endif // __LCD_H__
