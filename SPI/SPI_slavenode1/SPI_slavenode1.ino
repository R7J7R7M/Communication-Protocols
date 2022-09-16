//preprocessor
#define portD_ddr_register 0x2A
#define portD_input_register 0x29
#define portD_data_register 0x2B
#define portB_ddr_register 0x24
#define portB_input_register 0x23
#define portB_data_register 0x25
#define portC_ddr_register 0x27
#define portC_data_register 0x28


//function used
void init_port(void);
volatile char inportD(volatile char);
void outportB(volatile char,volatile char);
void outportC(volatile char,volatile char);
void SPI_reciever(void);

//global variables 
volatile char data=0xA0;
volatile char outputC,outputB;
volatile char output;
void setup() {
  // put your setup code here, to run once:
  init_port();
  volatile char cs;
  while(1){
    cs = inportD(3);
    while(cs == 0x01){
       cs = inportD(3);
       if(cs == 0x00){
        SPI_reciever();
       }
    }
  }
  
}
void SPI_reciever()
{
  delay(1);
  volatile static int k;
  volatile char input;
  volatile char i,j,last_bit,clock_;
  for(i=7;i>=0;i--){
    j = data >> i;
    last_bit = j & 0x01;
    if(i!=7){
      delay(5);
    }
    outportD(last_bit,2);
    while(1){
        clock_ = inportD(0);
        while(clock_ == 0x00){
          clock_ = inportD(0);
          while(clock_ == 0x01){
            clock_ = inportD(0);
            if(clock_ == 0x00){
              input = inportD(1);
              sampling(input,k);
              k++;
              goto out;
            }
          }
        }
    }
    out:
    outportC(0x01,1);
    delay(1);
 }
}

void init_port(void)
{
  char *portD_ddr = (char *) portD_ddr_register;
  char *portB_ddr = (char *) portB_ddr_register;
  char *portC_ddr = (char *) portC_ddr_register;

  *portD_ddr = 0x04;
  *portB_ddr = 0xFF;
  *portC_ddr = 0xFF;
}
volatile char inportD(volatile char pin)
{
  volatile char *portD_data = (volatile char *) portD_input_register;
  volatile char data;
  data = *portD_data;
  data = data & (0x01 << pin);
  data = data >> pin;
  return data;
}
void outportD(volatile char data , volatile char pin)
{
  volatile char *portD_data = (volatile char *) portD_data_register;
  if( data == 0x01){
    output |= (data<<pin);
  }
  else if(data == 0x00){
    output &= ~((0x01<<pin));
  }
  *portD_data = output;
}
void outportC(volatile char data , volatile char pin)
{
  volatile char *portC_data = (volatile char *) portC_data_register;
  if( data == 0x01){
    outputC |= (data<<pin);
  }
  else if(data == 0x00){
    outputC &= ~((0x01<<pin));
  }
  *portC_data = outputC;
}
void sampling(volatile char data,volatile char pin)
{
  volatile char *portB_data = (volatile char *) portB_data_register;
  if( data == 0x01){
    outputB |= (data<<pin);
  }
  else if(data == 0x00){
    outputB &= ~((0x01<<pin));
  }
  *portB_data = outputB;
}
void loop() {
  // put your main code here, to run repeatedly:

}
