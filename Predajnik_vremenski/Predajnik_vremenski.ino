#define laserPin 5

double ONE_time = 10;
double ZERO_time = 60;
double pTime = 30;

int x = 0;
int b[8];
int y;
int i = 0;

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
    
    for (int i=7; i>=0; i--) {
      
      byte state = bitRead(x, i);
      if(state == 0){
        nula();
        //Serial.println(0);
      }
      else{
        kec(); 
        //Serial.println(1);
      }      
    }
    delay(200);    
  }  
}


double t1;

void nula(){ 
  t1 = milis;
  PORTD |= 0b00100000;
  while((milis - t1) < ZERO_time){}
  PORTD ^= 0b00100000;
  pauza();
}

void kec(){ 
  t1 = milis;
  PORTD |= 0b00100000;
  while((milis - t1) < ONE_time){}
  PORTD ^= 0b00100000;
  pauza();
}

void pauza(){
  t1 = milis;
  while((milis - t1) < pTime){} 
}


ISR(TIMER1_COMPA_vect){          
  milis ++; 
}

  
