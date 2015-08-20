#define midi_reset 12
#define qout  7
#define clk  8
#define load 9

int curNote1 = 0;
int curNote2 = 0;
int prevNote1 = 0;
int prevNote2 = 0;

void setup(){
  Serial.begin(31250);
  pinMode(midi_reset, OUTPUT);
  
  pinMode(qout, INPUT);
  pinMode(clk, OUTPUT);
  pinMode(load, OUTPUT);
  
  digitalWrite(load, HIGH);
  digitalWrite(clk, HIGH);
  digitalWrite(midi_reset, HIGH);
  delay(1000);
  setProg(1, 46);
}

void loop(){
   readData();
   playNotes();
}

void    playNotes(){
  if (prevNote1 == 0 && curNote1 == 1){
    playNote(67, 80);
  }
  if (prevNote2 == 0 && curNote2 == 1){
    playNote(81, 80);
}
}
void setProg(byte channel, byte instrument){
  Serial.write(0xc0 + channel);
  delay(10);
  Serial.write(instrument);
}

void playNote(byte note, byte velocity){
  // note off 
  Serial.write(0x80 +1);
   Serial.write(note);
   Serial.write(velocity);

// note on
   Serial.write(0x90 +1);
   Serial.write(note);
   Serial.write(velocity);
}

void readData(){
    //load
    digitalWrite(load, LOW);
    //delay(50);
    digitalWrite(load, HIGH);
    //delay(50);
    int c = digitalRead(qout);
    
    prevNote1 = curNote1;
    curNote1 = c;
    digitalWrite(clk, LOW);
    //delay(5);
    digitalWrite(clk, HIGH);
    //delay(5);
    int c2 = digitalRead(qout);
    prevNote2 =  curNote2;
    curNote2 = c2;
}
