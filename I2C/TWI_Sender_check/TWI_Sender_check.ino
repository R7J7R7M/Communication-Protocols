//preprocessors
#define portD_ddr_register 0x2A
#define portB_ddr_register 0x24
#define portD_data_register 0x29
#define portB_data_register 0x25
#define push_button 0
#define delay_time 1000
#define SDA 0
#define CLK 1

// function used inside
void TWI_sender(char);
void init_port(void);
volatile char inportD(void);
void outportB(volatile char,volatile char );
volatile char output;
volatile char data_TWI = 0x55;
// global variables 
char indata;
char wait=6;
void setup()
{
  // put your setup code here, to run once:
  init_port();
  while(1){
     indata = inportD();
     while( indata == 0x00){
      indata = inportD();
      if(indata == 0x01){
        TWI_sender(data_TWI);
      }
     }
  }

}
void TWI_sender(char data)
{
  char last_bit;
  
  //start bit
  outportB(0x01,CLK);
  outportB(0x00,SDA);
  delay(wait);
  
  
  
  
  //data bits
  int i,j;
  for(i=7;i>=0;i--){
    j = data >> i;
    last_bit = j & 0x01;
    outportB(last_bit,SDA);
    clk_pulse_data();
    
  }
  //stop bit
  outportB(0x01,CLK);
  outportB(0x00,SDA);
  delay(wait);
  outportB(0x01,SDA);
  
}
void clk_pulse_data()
{
  outportB(0x00,CLK);
  delay(2);
  outportB(0x01,CLK);
  delay(2);
  outportB(0x00,CLK);
  delay(2);
}
void init_port(void)
{
  char *portD_ddr = (char *) portD_ddr_register;
  char *portB_ddr = (char *) portB_ddr_register;

  *portD_ddr = 0x00;
  *portB_ddr = 0xFF;
}
volatile char inportD(void)
{
  volatile char *portD_data = (volatile char *) portD_data_register;
  volatile char data;
  data = *portD_data;
  data = data & (0x01 << push_button);
  return data;
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
  *portB_data = ~output;
 
}
void delay1(char n)
{
  volatile long i;
  while(n){
    for(i=0;i<delay_time;i++);
    n--;
  }
}
void loop() {
  // put your main code here, to run repeatedly:

}
