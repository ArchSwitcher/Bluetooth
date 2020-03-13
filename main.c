/* Interface HC-05 Bluetooth module with PIC18F4550
 * http://www.electronicwings.com
 */


#include <pic18f4550.h>
#include <xc.h>

#include "config.h"
#include "USART_Header_File.h"

#define _XTAL_FREQ 2000000

void main()
{   
    char data_in;               //char(caracter) sera utilizado para la recepcion BT
    OSCCON=0x72;               //Reloj interno a 8MHZ 0b1110010
    
    TRISDbits.RD0 = 0;         //PUERTO D salida 0 configurada como salida
    USART_Init(9600);         /* INICIALIZANDO BT A 9600Baudios*/ 
    __delay_ms(50);             //DELAY para darle tiempo de incio
    USART_SendString("LED"); /* Eviando para verificar que este bien*/
    
    while(1)
    {
        data_in = USART_ReceiveChar();  //Recibiendo los valores del bt
        
        if(data_in=='1')                //comparando
        {   
            PORTDbits.RD0 = 1;                    /* turn ON LED */
            USART_SendString("LED_ON"); /* send LED ON status to terminal */
        }
        else if(data_in=='2')
                
        {
            PORTDbits.RD0 = 0;                    /* turn OFF LED */
            USART_SendString("LED_OFF");/* send LED ON status to terminal */
        }
        else
        {
            USART_SendString(" select 1 or 2");/* send msg to select proper option */
        }
        __delay_ms(500);
    
    }
    
}
