
void mode_SingleColor(int8 c)
{
    for(i = 0; i < NUMPIXELS; i++)
    {
        NeoRed[i] = rainbow[0][c];
        NeoGreen[i] = rainbow[1][c];
        NeoBlue[i] = rainbow[2][c];
    }

    NeoDraw();
    delay_ms(40);
}

void mode_RGB()
{
    
    tempR = 0; tempG = 0; tempB = 0;
    for(int rgb  = 0; rgb < 3; rgb++)
        for(int16 temp = 1; temp < 256; temp++)
        {
            if(rgb  == 0)
                tempR = temp;
            else 
                if(rgb == 1)
                    tempG = temp;
                else
                    tempB = temp;
            for(i = 0; i < NUMPIXELS; i++)
            {
                NeoRed[i] = tempR;
                NeoGreen[i] = tempG;
                NeoBlue[i] = tempB;
                //delay_ms(100);
            }

            NeoDraw();
            if(flag_break){
                break;
            }
            delay_ms(50);
        }

    for(int rgb  = 0; rgb < 3; rgb++)
        for(temp = 255; temp > 0; temp--) {
            if(rgb  == 0)
                tempR = temp;
            else 
            if(rgb == 1)
                tempG = temp;
            else
                tempB = temp;
            for(i = 0; i < NUMPIXELS; i++) {
                NeoRed[i] = tempR;
                NeoGreen[i] = tempG;
                NeoBlue[i] = tempB;
                //delay_ms(100);
            }

            NeoDraw();
            if(flag_break) {
                break;
            }

            delay_ms(50);
        }

    flag_break = FALSE;
}


