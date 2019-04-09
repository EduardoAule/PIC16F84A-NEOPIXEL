#include <16F84A.h>
//#device ANSI  //CCS with the ANSI declaration, is 99% compatible with ANSI-C90
//After enabling the ANSI compiler I noticed that the "const" keyword no more meant 
//"put this variable into program memory" but they were put into RAM instead.
//The solution was to apply another pragma:
//#DEVICE CONST=ROM 
#fuses HS,NOWDT,NOPROTECT,NOPUT //para version de 12MHz 
//NOPUT No Power Up Timer, tiempo de espera para estabilizacion de alimentacion
#use delay(clock=20MHz, crystal=20MHz)//se admite internal en lugar de clock
#use rs232(baud=9600,parity=N,xmit=PIN_B1,rcv=PIN_B0,bits=8)
#use FAST_IO(A)
#define NeoPin PIN_A3
#define NUMPIXELS 5
#include "ports.h"
#include "vars.h"
#include "NeoPixel.h"
#include "irqs.h"
#include "functions.h"
//The RA4/T0CKI Schmitt Trigger input and an open drain output
//Input/output or external clock input for TMR0.
//Output is open drain type.
//segun la formula mi Frecuencia de Reloj Externo sera de 1 Hz, el cual es dado
//por mi boton al pulsarlo, por lo que uso RTCC_DIV_1 ya que este divide 
//la frecuencia de entrada en 1
//RESET_CPU(), reinicia el cpu al principio del programa pero NO borra variables
/*Cuando se llama a la funci�n reset_cpu () en un chip 16F, salta a la direcci�n 0x0000. 
La pila es de 8 de profundidad y es circular. El puntero de pila es un contador modulo-8. 
El valor inicial del puntero de pila al inicio de un programa no importa.
*/
void main()
{
    set_tris_b(0x01);   //int_ext=RX
    set_tris_a(0x10);
    //port_b_pullups(true);
    setup_timer_0(RTCC_EXT_L_TO_H | RTCC_DIV_1);
    enable_interrupts(INT_TIMER0);
    enable_interrupts(INT_EXT_H2L); //ext_int_edge(H_TO_L);
    enable_interrupts(global);
    set_TIMER0(0xFF);   //init timer with last value
    output_high(PIN_A2);    delay_ms(50);
    output_low(PIN_A2);    /*delay_ms(300);
    output_high(PIN_A2);    delay_ms(300);
    output_low(PIN_A2);    delay_ms(300);
    output_high(PIN_A2);    delay_ms(300);
    output_low(PIN_A2);    delay_ms(300);*/
    putc('E');
    //putc(rainbow[0][0]);putc(rainbow[1][0]);putc(rainbow[2][0]);
    //putc(rainbow[0][1]);putc(rainbow[1][1]);putc(rainbow[2][1]);//
    while(TRUE)
    {
        switch(mode) {
            case 0:
                mode_SingleColor(0);
            break;
            case 1:
                mode_SingleColor(1);
            break;
            case 2:
                mode_SingleColor(2);
            break;
            case 3:
                mode_SingleColor(3);
            break;
            case 4:
                mode_SingleColor(4);
            break;
            case 5:
                mode_SingleColor(5);
            break;
            case 6:
                mode_SingleColor(6);
            break;
            case 7:
                mode_SingleColor(7);
            break;
            case 8:
                mode_RGB();
            break;
            //default:
            //mode = 0;
        }
        if(flag_color){
      //putc('c');
            mode = -1; //para evitar el switch
            for(int8 i=0; i<NUMPIXELS; i++) {
                NeoRed[i] = buffer_color[0];
                NeoGreen[i] = buffer_color[1];
                NeoBlue[i] = buffer_color[2];
            }
            NeoDraw ();
            delay_ms (100);
            flag_color = FALSE;
            cr = 0;
        }
        //putc(data);
        if(data=='R') {
            data = 0x00;
            putc('r');
            RESET_CPU();
        }
    //delay_ms(100);
    }   //while
}   //main
