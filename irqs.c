#INT_EXT
void interrupcion_ext()
{
    data=getc();
    buffer_color[cr] = data;
    //putc(data);
    if (data==0xD)
        flag_color=TRUE;
    else
        cr++;//cr=(cr+1)%sizeof(buffer_color);
    
}

#int_TIMER0 //la siguiente funci�n tiene que ser la de interrupci�n del TMR0
void  TIMER0_isr(void) //function interrupci�n TMR0
{
    RA2 = ~RA2; //RB3 = !RB3 //output_toggle(PIN_B0);
    mode ++;
    if(mode == 9) {
        mode = 0;
        flag_break = true;
    }
    set_TIMER0(0xFF);
}
