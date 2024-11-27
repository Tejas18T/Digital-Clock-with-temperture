#include <p18f4550.h>
#include <delays.h>
#pragma config PBADEN = OFF
#define Sec_Unit_Digit PORTAbits.RA0 // Drive LED at the unit columm
// second.
#define Sec_Ten_Digit PORTAbits.RA1 // Drive LED at the ten columm
// second.
#define Min_Unit_Digit PORTAbits.RA2 // Drive LED at the unit columm
// minute.
#define Min_Ten_Digit PORTAbits.RA3 // Drive LED at the ten columm
// minute.
#define Hour_Unit_Digit PORTAbits.RA4 // Drive LED at the unit columm
// hour.
#define Hour_Ten_Digit PORTAbits.RA5 // Drive LED at the ten columm
// hour.
#define Data_Display PORTD // Data displayed.
#define SCL PORTBbits.RB1 // Clock of SPI.
#define SDI PORTBbits.RB0 // Data input of SPI mode
#define SDO PORTCbits.RC7 // Data output of SPI mode.
#define CE PORTCbits.RC2 // Enable the communication of SPI mode.
#define SCL_Direction TRISBbits.TRISB1 // Directions of SPI bus.
#define SDI_Direction TRISBbits.TRISB0 // ----------
#define SDO_Direction TRISCbits.TRISC7 // ----------
#define CE_Direction TRISCbits.TRISC2 // ----------
void Setup_RTC(void);
unsigned char SPI(unsigned char);
unsigned char Display(unsigned char k);
unsigned char data[7]; // Hold date and time
//=====================================================
void main()
{
unsigned char i, j;
unsigned char Hour_Ten, Hour_Unit;
unsigned char Min_Ten, Min_Unit;
unsigned char Sec_Ten, Sec_Unit;
ADCON1 = 0x0F; // PORTB is digital I/O.
TRISA = 0x00; // PORTA as output port
TRISD = 0x00; // PORTD as output port
SSPSTAT = 0; // Read at middle, send on active edge.
SSPCON1 = 0x22; // Master SPI enable, Fosc/64.
CE_Direction = 0; // CE is output.
SCL_Direction = 0; // SCL is output.
SDI_Direction = 1; // SDI is input.
SDO_Direction = 0; // SDO is ouput.
Sec_Unit_Digit = 0; // ********************
Sec_Ten_Digit = 0; // Erase all 6 LEDs.
Min_Unit_Digit = 0; //
Min_Ten_Digit = 0; //
Hour_Unit_Digit = 0; //
Hour_Ten_Digit = 0; // ********************
Setup_RTC(); // Initialize the first time.
while(1)
{
CE = 1; // Begin reading multibyte.
Delay100TCYx(50);
SPI(0x00); // Seconds register address.
for(i = 0;i < 7; i++)
{
data = SPI(0x00); // Get time/date and save.
}
CE = 0; // End of multibyte read.
Hour_Ten = data[2] >> 4;
Hour_Unit = data[2] & 0b00001111;
Min_Ten = data[1] >> 4;
Min_Unit = data[1] & 0b00001111;
Sec_Ten = data[0] >> 4;
Sec_Unit = data[0] & 0b00001111;
for (j = 0; j < 42 ; j++)
{
Data_Display = Display(Hour_Ten);
Hour_Ten_Digit = 1; // Display hours
Delay10TCYx(50); // Delay 100 us.
Hour_Ten_Digit = 0;
Data_Display = Display(Hour_Unit);
Hour_Unit_Digit = 1;
Delay10TCYx(50);
Hour_Unit_Digit = 0;
Data_Display = Display(Min_Ten);
Min_Ten_Digit = 1; // Display hours
Delay10TCYx(50);
Min_Ten_Digit = 0;
Data_Display = Display(Min_Unit);
Min_Unit_Digit = 1;
Delay10TCYx(50);
Min_Unit_Digit = 0;
Data_Display = Display(Sec_Ten);
Sec_Ten_Digit = 1; // Display hours
Delay10TCYx(50);
Sec_Ten_Digit = 0;
Data_Display = Display(Sec_Unit);
Sec_Unit_Digit = 1;
Delay10TCYx(50);
Sec_Unit_Digit = 0;
}
}
}
//=====================================================
// Initialize DS1306
void Setup_RTC()
{
CE = 1; // Enable the RTC.
Delay100TCYx(50); // Delay 1 ms.
SPI(0x8F); // Enable to write.
SPI(0x00); // Clear WP bit for write.
CE = 0; // End of single-byte write.
Delay100TCYx(50);
CE = 1; // Begin multibyte write.
SPI(0x80); // Enable write.
SPI(0x55); // Set up second.
SPI(0x58); // Set up minute.
SPI(0x17); // Set up hour.
SPI(0x03); // Set up day in week.
SPI(0x26); // Set up date.
SPI(0x01); // Set up month.
SPI(0x14); // Set up year.
CE = 0; // End of multibyte write.
Delay100TCYx(50);
}
//=====================================================
unsigned char SPI(unsigned char myByte)
{
SSPBUF = myByte; // Buffer register.
while(!SSPSTATbits.BF);
return SSPBUF;
}
//=====================================================
unsigned char Display(unsigned char k)
{
unsigned char Number;
unsigned char Code_Tab[ ] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92,0x82,
0xF8, 0x80, 0x90};
Number = Code_Tab[k]; // Select number to display.
return (Number);
}