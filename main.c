/*
 * File:   main.c
 * Author: dell
 *
 * Created on February 28, 2020, 9:06 PM
 */


#include <xc.h>
#include"config.h"
#include"USART_Header_File.h"

char data;
void Int_Ext(void);

void main(void) {
    OSCCON=0x72;
    ADCON1bits.PCFG = 0b1111;
    TRISAbits.RA0 = 0;
    Int_Ext();
    
    USART_Init(9600);   //Inicializacion del UART A 9600
    USART_SendString("Hola Mundo"); //ENVIANDO UN HOLA MUNDO
    __delay_ms(500);
    
            while(1){
                data = USART_ReceiveChar();
                if (data == 'A'){
                    PORTAbits.RA0 = ~PORTAbits.RA0;
                }
            
            }
}

void Int_Ext(void){
    TRISBbits.RB0 = 1;
    INTCONbits.INT0IE = 1; // Habilitar INT0 
    INTCONbits.INT0IF = 0; //FLag 0
    INTCON2bits.INTEDG0 = 0; //Flanco descendete
    INTCONbits.GIE = 1;
}

void __interrupt(low_priority) Interruptions(void){
    if (INTCONbits.INT0F){
        PORTAbits.RA0 = ~PORTAbits.RA0;
        INTCONbits.INT0F = 0;
    }

}