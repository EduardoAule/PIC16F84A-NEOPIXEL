//*****************************************************************************
// For NeoPixel
unsigned int8 NeoGreen [NUMPIXELS];
unsigned int8 NeoBlue [NUMPIXELS];
unsigned int8 NeoRed [NUMPIXELS];
//cuando se defina como const para almacenarse en ROM, especificar el
//tama�o completo del array fila-col
const unsigned  int8  rainbow[3][8] = {
  { 255,  255, 255,   0,    0,    0, 159, 255 },
  { 0,     69, 233, 255,  176,    0,   0, 255 },
  { 0,      0,   0,   0,  255,  255, 255, 255 }
};
unsigned int8 temp;

int8 i = 0;
//usado en los for
/*
unsigned int8 NeoPixel;
signed int8 BitCount;
int8 i=0;*/
//serial
unsigned char data;
unsigned char buffer_color[4] ={ 0, 32, 128, 0 };
int8 cr=0;
int1 flag_color=FALSE;
//int1 flag_btn = FALSE;

int8 mode = 0;

unsigned int8 tempR;
unsigned int8 tempG;
unsigned int8 tempB;
//flag para salir de los for()
//del ultimo modo
int1 flag_break = FALSE;

