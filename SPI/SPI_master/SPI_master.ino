#include"atmega328p_port_init.h"

//function used
void init_port(void);
volatile char inportD(volatile char);
void outportB(volatile char,volatile char);
void outportC(volatile char,volatile char);
volatile char inportB();

//Global varibles
volatile int wait = 5;
volatile char indata,output,outputC;
volatile char data = 0x55;


void setup() {
  // put your setup code here, to run once:
  init_port();
  outportB(0x01,3);
  outportB(0x01,4);
  outportB(0x01,5);
  delay(1);
  

  //CPol=0 Cphase=0
  //fullduplex communication
  while(1){
    indata = inportD(0); // to select the first slave node
    while(indata == 0x00){
      indata = inportD(0);
      if(indata == 0x01){
        // selecting node 1
        outportB(0x00,3);
        delay(1);
        SPI_sender(data);
      }
    }
  }
}
void SPI_sender(char data)
{
  volatile char i,j,last_bit;
  for(i=7;i>=0;i--){
    j = data >> i;
    last_bit = j & 0x01;
    outportB(last_bit,1);
    delay(1);
    clock_pulse();
    delay(1);
    
  }
  //stopbit 
  outportB(0x01,3);
}
void clock_pulse()
{
  volatile char input;
  static char i;
  outportB(0x00,0);
  delay(wait);
  outportB(0x01,0);
  input = inportB();
  sampling(input,i);
  i++;
  delay(wait);
  outportB(0x00,0);
  delay(wait);
 
}
void sampling(volatile char data,volatile char pin)
{
  volatile char *portC_data = (volatile char *) portC_data_register;
   if( data == 0x01){
    outputC |= data<<pin;
  }
  else if(data == 0x00){
    outputC &= ~((0x01<<pin));
  }
  *portC_data = outputC;
}
void init_port(void)
{
  char *portD_ddr = (char *) portD_ddr_register;
  char *portB_ddr = (char *) portB_ddr_register;
  char *portC_ddr = (char *) portC_ddr_register;

  *portD_ddr = 0x00;
  *portB_ddr = 0xFB;
  *portC_ddr = 0xFF;
}

void outportB(volatile char data , volatile char pin)
{
  volatile char *portB_data = (volatile char *) portB_data_register;
  if( data == 0x01){
    output |= data<<pin;
  }
  else if(data == 0x00){
    output &= ~((0x01<<pin));
  }
  *portB_data = output;
 
}
volatile char inportB(void)
{
  volatile char *portB_data = (volatile char *) portB_input_register;
  volatile char data;
  data = *portB_data;
  data = data >> 2;
  data = data & 0x01;
  return data;
}
volatile char inportD(volatile char pin)
{
  volatile char *portD_data = (volatile char *) portD_input_register;
  volatile char data;
  data = *portD_data;
  data = data & (0x01 << pin);
  return data;
}
void loop() {
  // put your main code here, to run repeatedly:

}
