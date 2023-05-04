#include <12f675.H>
#use delay(clock=4M)

#FUSES NOWDT                 //El perro encerrado en la caseta
#FUSES INTRC_IO              //reloj interno del pic
#FUSES NOCPD                 //No EE proteccion
#FUSES NOMCLR                //No Master Clear
#FUSES NOPUT                 // Espera un tiempo al encenderse para que se estabilice la tension
#FUSES NOBROWNOUT            //Reset cuando baja la tension a niveles no seguros

#byte PA=0x05
void devolverMotor();
void generarDescarga();

int descarga=0,devolver=0,i=0; 

  void main ()//ARRANQUE DEL PROGRAMA
{
   set_tris_A(0b00001100);//CONFIGURO LOS BIT DEL PUERTO Gp0 y Gp1 como salidas 
  PA=0;//MANDO EL PUERTO A TODOS OFF PARA EVITAR ERRORES DE ARRANQUE

  descarga=pin_a2;// descarga es la variable que guarda lo que entra por el bit a2 que viene del relé de Komttech ----> Sí es un cero se dispara de lo contrario se mantiene
  devolver=pin_a3;// descarga es la variable que guarda lo que entra por el bit a3 Botón devolver
 
//Devuelvo actuador siempre al inicializar el programa
  output_Low(pin_a1);// apago el rele de devolver
  output_Low(pin_a0);// apago el rele de disparo
 for(i=0;i<2;i++)
 {
 devolverMotor();
 }
 PA=0b00000000;

while(true)
{       
 //Pregunto por entradas
 //entro en un condicional, si se activo una entrada
 //do
// {
               //descarga==1;// limpio variable descarga
               delay_ms(1000);
               descarga=input(pin_a2);
               if (input( descarga )==0)
               {
               delay_ms(1000);
               descarga=input(pin_a2);
               delay_ms(1000);
               if(descarga==0)
               {
               do
               {
                 //delay_ms(500); 
                 generarDescarga();
                 delay_ms(100); 
                 }while(descarga==1);         
               }
               }
               else
               {
               PA=0b00000000;
               }
               if (input( descarga )==1)
               {
               do
               {
                 PA=0b00000000;
               }while(descarga==0);
               }
               
               if (input(devolver)==0)
               {
               
               devolverMotor();
               }
               
                if (input( descarga )==1 && input(devolver)==1)
               {
               PA=0b00000000;
               }
// }(devolver==0)


}//Cierre infinito
 
}//FIN MAIN

//FUNCIONES
//DEVOLVER

//Devolver Motor

void devolverMotor()
{
 //delay_ms(500); 
// output_Low(pin_a0);//primero apago el rele de disparo
delay_ms(500);
 output_High(pin_a1);// Sentido devolver
 delay_ms(7000); //Devuelvo por 7 seg
 
}

//Función Descarga

void generarDescarga()
{
 delay_ms(50); 
 //output_Low(pin_a1);//primero apago el rele de devolver
 //delay_ms(50);
 //output_High(pin_a0);// Activo relé de disparo
  PA=0b00000001;
 delay_ms(5000);    
}

