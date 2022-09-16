char inport(void);
void outport(char);
void init_port(void);
void UART_sender(char);
volatile char data,input;
volatile long wait=1;
void setup() {
  // put your setup code here, to run once:
  init_port();
  while(1){
   input=inport();
    while(input==0x00){
      input = inport();
    if(input == 0x01){
      UART_sender(0xFF);
     }
    if(input == 0x02){
      UART_sender(0x81);
     }
    }
  }
  
}
void UART_sender(volatile char data)
{
  volatile char i,j;
  //start bit
  outport(0x01);
  delay1(wait);
  //data
  for(i=0;i<8;i++){
    j=data>>i;
    outport(j);
    delay1(wait);
  }
  //stop bit
  outport(0x00);
  delay1(wait);
  
}
void init_port()
{
  char *portD_ddr = (char *)0x2A;
  *portD_ddr = 0x00;
  char *portB_ddr = (char *)0x24;
  *portB_ddr = 0xFF;
}
void outport(char data)
{
  volatile char *portB_data = (char *) 0x25;
  *portB_data = data;
}
char inport(void)
{
  volatile char  *portD_data = (char *) 0x29;
  volatile char data ;
  data = *portD_data;
  return data;
}
void delay1(char n)
{
  volatile long i;
  while(n){
    for(i=0;i<1000;i++);
    n--;
  }
}
void loop() {
  // put your main code here, to run repeatedly:

}
