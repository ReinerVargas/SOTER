#include <12F675.h>
#use delay(clock=4M)
#fuses NOPROTECT
#FUSES NOWDT                 //El perro activo
#FUSES INTRC_IO              //reloj interno del pic
#FUSES NOCPD                 //No EE proteccion
#FUSES NOMCLR                //No Master Clear
#FUSES NOPUT                 // Espera un tiempo al encenderse para que se estabilice la tension
#FUSES NOBROWNOUT 

// Definici�n de pines
#define GP0 PIN_A0
#define GP1 PIN_A1
#define GP2 PIN_A2
#define GP3 PIN_A3
#define GP4 PIN_A4
#define GP5 PIN_A5

// Variables globales
int watchdog_counter = 0;

// Funci�n de interrupci�n del perro guardi�n
#INT_RTCC
void watchdog_isr()
{
   output_high(GP4);
   output_high(GP2);
   delay_ms(10000); // Esperar 10 segundos
   output_low(GP4);
   output_low(GP2);
   watchdog_counter = 0; // Reiniciar contador del perro guardi�n
   reset_cpu(); // Reiniciar el microcontrolador
}

// Funci�n para activar GP0 durante 10 segundos
void activate_GP0()
{
   output_high(GP0);
   delay_ms(10000); // Esperar 10 segundos
   output_low(GP0);
}

// Funci�n para activar GP1 durante 10 segundos
void activate_GP1()
{
   output_high(GP1);
   delay_ms(10000); // Esperar 10 segundos
   output_low(GP1);
}

void main()
{
   // Configurar pines
   set_tris_a(0b00001100); // GP0, GP1, GP4, GP5 son salidas; GP2, GP3 son entradas
   output_a(0x00); // Apagar todas las salidas

   // Configurar perro guardi�n
   setup_counters(RTCC_INTERNAL, RTCC_DIV_256); // Configurar temporizador interno
   enable_interrupts(INT_RTCC); // Habilitar interrupci�n del perro guardi�n
   enable_interrupts(GLOBAL); // Habilitar interrupciones

   while(true)
   {
      // Activar GP0 durante 10 segundos al inicio
      activate_GP0();

      // Preguntar por el estado de GP2
      while(input(GP2))
      {
         // Si el contador del perro guardi�n llega a 500 (5 segundos), activar la interrupci�n del perro guardi�n
         if(watchdog_counter == 500)
         {
            enable_interrupts(INT_RTCC);
            break; // Salir del ciclo para ejecutar la interrupci�n del perro guardi�n
         }

         // Esperar 10 milisegundos y aumentar el contador del perro guardi�n
         delay_ms(10);
         watchdog_counter++;
      }

      // Si GP2 vale 0, activar GP1 durante 10 segundos
      if(!input(GP2))
      {
         activate_GP1(); //Llamado de la funci�n que dispara el actuador

         // Preguntar por el estado de GP3
         while(input(GP3))
         {
            // Si el contador del perro guardi�n llega a 500 (5 segundos), activar la interrupci�n del perro guardi�n
            if(watchdog_counter == 500)
            {
               enable_interrupts(INT_RTCC);
               break; // Salir del ciclo para ejecutar la interrupci�n del perro guardi�n
            }

            // Esperar 10 milisegundos y aumentar el contador del perro guardi�n
            delay_ms(10);
         }
      }
   }
}

