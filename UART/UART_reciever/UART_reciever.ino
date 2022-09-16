char inport(void);
void outport(char);
void init_port(void);
char UART_reciever(void);
volatile char data,input;
volatile long wait=5;
int arr[8];
void setup() {
  // put your setup code here, to run once:
  init_port();
  while(1){
    input = inport();
    while(input == 0x00){
      input =inport();
      if(input == 0x01){ 
        delay1(1);
         data = UART_reciever();
         outport(data);
      }
    }
  }
    
  
  
}
char UART_reciever(void)
{
  delay1(wait);
  volatile char i,j;
  // recieving 8 bit data
  for(i=0;i<8;i++){
    input = inport();
    outportC(input);
    arr[i]=input;
    delay1(wait);
  }
  input = inport();
  if(input == 0x00){
    outportC(0x0F);
    j = conversion(arr);
    return j;
  }
  else{
    return 0;
  }
   
  
}
char conversion(int *arr)
{
  volatile char i,sum=0;
  for(i=0;i<8;i++){
    if(arr[i] == 0){
      continue;
    }
    else if(arr[i] != 0){
      sum = sum + power(i);
    }
  }
  return sum;
}
char power(int i)
{
  char k,answer=1;
  for(k=0;k<i;k++){
    answer=2*answer;
  }
  return answer;
}

void init_port()
{
  char *portD_ddr = (char *)0x2A;
  *portD_ddr = 0x00;
  char *portB_ddr = (char *)0x24;
  *portB_ddr = 0xFF;
  char *portC_ddr = (char *)0x27;
  *portC_ddr = 0xFF;
}
void outport(char data)
{
  volatile char *portB_data = (char *) 0x25;
  *portB_data = data;
}
void outportC(char data)
{
  volatile char *portC_data = (char *) 0x28;
  *portC_data = data;
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
