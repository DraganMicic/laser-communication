#define laserPin 5

double BIT_time = 50;

int x = 0;
int b[8];
int y;
int i = 0;


double t_poc;

volatile double milis;

void setup() {
  pinMode(laserPin, OUTPUT);
  Serial.begin(115200);

  TCCR1A = 0b00000000;
  TCCR1B = 0b00001011;
  TCNT1 = 0;
  OCR1A = 25;
  TIMSK1 = 0b00000010;
}

void loop() {

  //Serial.println(milis);
  if (Serial.available() > 0) {
    
    x = Serial.read();
    t_poc = milis;
    start();
    
    for (int i=7; i>=0; i--) {
      
      byte state = bitRead(x, i);
      if(state == 0){
        nula();
        
        Serial.println("0");
      }
      else{
        kec(); 
        Serial.println("1");
      }      
    } 
    PORTD = 0b00000000;
    //delay(4);
    Serial.println(milis-t_poc);   
  }  
}


double t1;

void nula(){ 
  t1 = milis;
  PORTD = 0b00000000;
  while((milis - t1) < BIT_time){}
}

void kec(){ 
  t1 = milis;
  PORTD = 0b00100000;
  while((milis - t1) < BIT_time){}
}

void start(){ 
  
  t1 = milis;
  PORTD = 0b00000000;
  while((milis - t1) < BIT_time){}
  
  t1 = milis;
  PORTD = 0b00100000;
  while((milis - t1) < BIT_time){}

  t1 = milis;
  PORTD = 0b00000000;
  while((milis - t1) < BIT_time){}
}

ISR(TIMER1_COMPA_vect){          
  milis ++; 
}

  
