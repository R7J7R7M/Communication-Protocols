//preprocessors
#define portD_ddr_register 0x2A
#define portB_ddr_register 0x24
#define portC_ddr_register 0x27
#define portD_data_register 0x29
#define portB_data_register 0x25
#define portC_data_register 0x26
#define delay_time 1000
#define SDA 0
#define CLK 1
volatile char output;
volatile char i=7;
volatile char in_data,in_clock;
// function used inside
void init_port(void);
volatile char inportD(volatile char);
void outportB(volatile char,volatile char);
void TWI_reciever(void);

void setup() {
  // put your setup code here, to run once:
  init_port();
  
  //start bit
  while(1){
      in_clock = inportD(CLK);
      while(in_clock == 0x02){
        in_data = inportD(SDA);
        if(in_data == 0x00){
          TWI_reciever();
        }
       in_clock = inportD(CLK);
      }
    }
    
}
void TWI_reciever()
{
  while(i!=0){
  in_clock = inportD(CLK);
  while(in_clock == 0x00){
    in_clock = inportD(CLK);
    while(in_clock == 0x02){
      in_clock = inportD(CLK);
      if(in_clock == 0x00){
        in_data = inportD(SDA);
        outportB(in_data,i);
        i--;
      }
    }
  }
  }
}

void init_port(void)
{
  char *portD_ddr = (char *) portD_ddr_register;
  char *portB_ddr = (char *) portB_ddr_register;
  

  *portD_ddr = 0x00;
  *portB_ddr = 0xFF;
  
}
volatile char inportD(volatile char pin)
{
  volatile char *portD_data = (volatile char *) portD_data_register;
  volatile char data;
  data = *portD_data;
  data = data & (0x01 << pin);
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
  *portB_data = output;
 
}
//void outportC(volatile char data)
//{
//  volatile char *portC_data = (volatile char *) portC_data_register;
//  *portC_data = data;
//}
void loop() {
  // put your main code here, to run repeatedly:

}
