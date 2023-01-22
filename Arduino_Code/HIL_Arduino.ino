// Create a union to easily convert float to byte
typedef union{
  float number;
  uint8_t bytes[4];
} FLOATUNION_t;

// Create the variables you want to receive
FLOATUNION_t myValue1;
FLOATUNION_t myValue2;
FLOATUNION_t myValue3;
FLOATUNION_t myValue4;

// Create the variables to send
FLOATUNION_t send1;
// LQR 3
float k[4] = {-1.4, -14.7, -121.7, -28.2};

void setup() {
  // initialize serial, use the same boudrate in the Simulink Config block
  Serial.begin(115200);

}
void loop(){
  if(Serial.available()){
    if(Serial.read() == 'A'){
    // Get the floats from serial
      myValue1.number = getFloat(); // Give your float a value
      myValue2.number = getFloat(); // Give your float a value
      myValue3.number = getFloat(); // Give your float a value
      myValue4.number = getFloat(); // Give your float a value
      delay(50);
    }
    if(Serial.read() == '\n'){
    
      float u = k[0]*myValue1.number + k[1]*myValue2.number + k[2]*myValue3.number + k[3]*myValue4.number;
      
      // Send some variables back
      send1.number = u;
      
      // Print header: Important to avoid sync errors!
      Serial.write('A'); 
      
      // Print float data
      for (int i=0; i<4; i++){
        Serial.write(send1.bytes[i]); 
      }
  
      // Print terminator
      Serial.print('\n');

      myValue1.number = 0; // Give your float a value
      myValue2.number = 0; // Give your float a value
      myValue3.number = 0; // Give your float a value
      myValue4.number = 0;
      
      // Use the same delay in the Serial Receive block
      delay(50);
    }
  }
}


float getFloat(){
    int cont = 0;
    FLOATUNION_t f;
    while (cont < 4 ){
        f.bytes[cont] = Serial.read() ;
        cont = cont +1;
    }
    return f.number;
}
