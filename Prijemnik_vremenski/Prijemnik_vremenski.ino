#define fotoR A0

double ONE_time = 10;
double ZERO_time = 60;
double pTime = 30;
double toleranc = 20;
double ofset = 0;
int treshold = 980;

void setup() {
  pinMode(fotoR,INPUT);
  Serial.begin(115200);

  TCCR1A = 0b00000000;
  TCCR1B = 0b00001011;
  TCNT1 = 0;
  OCR1A = 25;
  TIMSK1 = 0b00000010;
  //Serial.println("da");
}


int b_sad = 0;
int b_pre = 0;
double t1 = 0;
double t = 0;
volatile double milis;

volatile int lop=0;
volatile byte bajt=0;
volatile char charWord;
volatile int twoStep =128 ;
volatile int a;

void loop() {
  a = analogRead(fotoR);
  //Serial.println(a);
  if(a>=treshold){
    b_sad=1;
    //Serial.println(1);
  }
  else{
    b_sad=0;
    //Serial.println(0);
  }
  
  if(b_sad == 1 && b_pre == 0){
      //Serial.print("t1");
      t1 = milis; 
  }
  
  if(b_sad == 0 && b_pre ==1){
    t = milis-t1;
    //Serial.println(t);

    if(t<=(ONE_time + ofset + toleranc) && t>=(ONE_time + ofset - toleranc)){
      bajt += 1 * twoStep;
      twoStep=twoStep/2;  
     //Serial.print ("//1");  
    }
    
    if(t<=(ZERO_time+ofset+toleranc) && t>=(ZERO_time+ofset-toleranc)){
      twoStep=twoStep/2; 
      //Serial.print("//0");
    }
    //Serial.println(" ");
    lop++; 
    //delay(1); 
  }

  if(lop==8){ 
      lop=0;
      twoStep = 128;    
      charWord = bajt;
      Serial.print(charWord);  
      bajt=0;  
  }      
  b_pre = b_sad;
}

ISR(TIMER1_COMPA_vect){          
  milis ++; 
}
