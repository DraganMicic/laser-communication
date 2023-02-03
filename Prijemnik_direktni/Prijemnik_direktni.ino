#define fotoR 0

volatile int adcReading;
volatile boolean adcDone;
boolean adcStarted;
volatile bool in = true; 

double BIT_time = 50;
int treshold = 80;
int ada = 10;


void setup() {
  pinMode(fotoR,INPUT);
  Serial.begin(115200);

  TCCR1A = 0b00000000;
  TCCR1B = 0b00001011;
  TCNT1 = 0;
  OCR1A = 25;
  TIMSK1 = 0b00000010;

  delay(50);

  Serial.println("A");
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

bool bajt_tok = false;
double a_prosek;

double t_poc;

void loop() {
  
  if(!bajt_tok){
    //Serial.println("Ada");
    adcReading = analogRead(fotoR);
    while(!(adcReading>=treshold)){
      adcReading=analogRead(fotoR);
    }
    t_poc = milis;
    //Serial.println("cekam 0");
    t1=milis;
    adcReading = analogRead(fotoR);
    while(adcReading>=treshold){
      adcReading=analogRead(fotoR);
      }
    //Serial.println("cekam 1");
    BIT_time = milis-t1;
    //Serial.println(BIT_time);
    //t1=milis;
    //while(milis-t1 <= (BIT_time)){}
    bajt_tok = true;
  }

  if(bajt_tok){
     
    t_poc = milis;
    //Serial.println("uso");
    t1=milis;
    while(milis-t1 <= (BIT_time/2)){}
    for(int i = 0; i<8; i++){
      //Serial.println(milis-t_poc);
      t1=milis;
      while(milis-t1 <= (BIT_time)-ada){}
      adcReading=analogRead(fotoR);
      if(adcReading>=treshold){
        //Serial.println(1);
        bajt += 1 * twoStep;
        twoStep=twoStep/2;       
      }else{
        //Serial.println(0);
        twoStep=twoStep/2;    
      }        
    }
    
    //Serial.println(milis - t_poc);
    twoStep = 128;    
    charWord = bajt;
    Serial.print(charWord);  
    bajt=0;  
    t1=milis;
    while(milis-t1 <= (BIT_time/2)){}
    //delay(4);
    bajt_tok = false;     
    //delay(20);

    
  }
  
}

ISR(TIMER1_COMPA_vect){          
  milis ++; 
}


  
