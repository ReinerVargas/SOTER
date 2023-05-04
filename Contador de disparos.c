#include <12f675.H>
#use delay(clock=4M)
#FUSES NOWDT                 //El perro encerrado en la caseta
#FUSES INTRC_IO              //reloj interno del pic
#FUSES NOCPD                 //No EE proteccion
#FUSES NOMCLR                //No Master Clear
#FUSES NOPUT                 // Espera un tiempo al encenderse para que se estabilice la tension
#FUSES NOBROWNOUT 
#define GP0 PIN_A0      // Definir el pin GP0 como salida
#define GP1 PIN_A1      // Definir el pin GP1 como salida
#define GP4 PIN_A4      // Definir el pin GP4 como salida
#define GP5 PIN_A5      // Definir el pin GP5 como salida
#define GP2 PIN_A2      // Definir el pin GP2 como entrada
#define GP3 PIN_A3      // Definir el pin GP3 como entrada

void main()
{
    set_tris_a(0b00111000);      // Configurar los pines como entrada/salida
    output_low(GP0);         // Apagar GP0
    output_low(GP1);         // Apagar GP1
    output_low(GP4);         // Apagar GP4
    output_low(GP5);         // Apagar GP5

   // output_high(GP0);         // Activar GP0 durante 10 segundos
   // delay_ms(10000);
   // output_low(GP0);         // Apagar GP0

    while(true)
    {
       
            
           // do{
                delay_ms(500);
                output_high(GP0);      // Activar GP0 durante 10 segundos
                delay_ms(7000);
                output_low(GP0);      // Apagar GP0
                delay_ms(1000);
                output_high(GP1);      // Activar GP1 durante 10 segundos
                delay_ms(7000);
                output_low(GP1);      // Apagar GP1
                delay_ms(1000);
                output_high(GP4);     // Activo relé contador
                delay_ms(1000);
                output_low(GP4);
                delay_ms(1000);
                
              //  }while(i==599);
           
       
       
           // output_low(GP0);      // Apagar todas las salidas
          //  output_low(GP1);
          //  output_low(GP4);
          //  output_low(GP5);
        

        //output_toggle(GP5);      // Alternar el estado de GP5 cada segundo
        //delay_ms(1000);
    }
}
