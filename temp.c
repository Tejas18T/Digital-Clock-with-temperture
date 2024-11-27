program thermometer452

dim LCD_RS as sbit at RB4_bit
    LCD_EN as sbit at RB5_bit
    LCD_D4 as sbit at RB0_bit
    LCD_D5 as sbit at RB1_bit
    LCD_D6 as sbit at RB2_bit
    LCD_D7 as sbit at RB3_bit

    LCD_RS_Direction as sbit at TRISB4_bit
    LCD_EN_Direction as sbit at TRISB5_bit
    LCD_D4_Direction as sbit at TRISB0_bit
    LCD_D5_Direction as sbit at TRISB1_bit
    LCD_D6_Direction as sbit at TRISB2_bit
    LCD_D7_Direction as sbit at TRISB3_bit

dim ADCResult as longword
dim value as word[3]
dim vstring as string[3]

sub procedure GlobInit
    TRISB = 0
    PORTB = 0
    TRISA = 1
    ADCON1 = $4E
    LCD_Init
    LCD_Cmd(_LCD_CLEAR)
    LCD_Cmd(_LCD_CURSOR_OFF)
    LCD_Out(1, 1, "Temp:")
    LCD_Out(1, 15, "'C")
end sub

main:
     GlobInit
     while true
           ADCResult = (ADC_Read(0) * 500) >> 10
           value[0] = ADCResult div 100
           value[1] = (ADCResult div 10) mod 10
           value[2] = ADCResult mod 10
           vstring[0] = value[0] + 48
           vstring[1] = value[1] + 48
           vstring[2] = value[2] + 48
           LCD_Out(1, 10, vstring)
           delay_ms(50)
     wend
end.