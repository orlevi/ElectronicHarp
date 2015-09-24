#define midi_reset 10
#define data_in  2
#define clk  3
#define load 4
#define SENSORS_NUM  8

int curr_notes[SENSORS_NUM] = {0,0,0,0,0,0,0,0};
int prev_notes[SENSORS_NUM] = {0,0,0,0,0,0,0,0};

void setup(){
  Serial.begin(31250);
  pinMode(midi_reset, OUTPUT);
  
  pinMode(data_in, INPUT);
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
   //delay(1000);
}

void    playNotes(){
      for(int i=0; i<SENSORS_NUM; i++){
          if (prev_notes[i] == 0 && curr_notes[i] == 1){
                playNote(67+i, 80);
          }
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
      digitalWrite(load, LOW);
      //delay(50);
      digitalWrite(load, HIGH);
    for(int i=0; i<SENSORS_NUM; i++){
      prev_notes[i] = curr_notes[i];
      curr_notes[i] = digitalRead(data_in);
      digitalWrite(clk, LOW);
      //delay(50);
      digitalWrite(clk, HIGH);
      //delay(50);
      
    }
}
