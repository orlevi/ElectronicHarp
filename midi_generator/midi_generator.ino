#define midi_reset 12

void setup(){
  Serial.begin(31250);
  pinMode(midi_reset, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(midi_reset, HIGH);
  delay(1000);
  
}

void loop(){
  digitalWrite(13, HIGH);
   for (int i=50;i <80; i++){
     setProg(1, 46);  
     playNote(i, 80);
     delay(200);
   }
   //playNote(20, 0x65);
   //delay(1500);
   //digitalWrite(13,LOW);
   //playNote(30, 0x65);
   //delay(1500);
}

void setProg(byte channel, byte instrument){
  Serial.write(0xc0 + channel);
  delay(10);
  Serial.write(instrument);
}

void playNote(byte note, byte velocity){
   Serial.write(0x90 +1);
   Serial.write(note);
   Serial.write(velocity);
}
