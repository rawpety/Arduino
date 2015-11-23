String sensor;
String value;

const int motor1 = 6;
const int motor2 = 9;
const int motor3 = 10;
const int motor4 = 11;

void setup() {                
  Serial.begin(57600);
}

void loop() {
  if (Serial.available()) {
//    Serial.write(Serial.read());
      int sensor = Serial.read();
      int value = 254;

      delay(1);
      if(Serial.available())
      {
        value = Serial.read();
        int mapSensorVal = constrain(fscale(5,40,255,0,value,5),0,255);
        if(sensor==1)
        {
            analogWrite(motor1, mapSensorVal);
        }
        else if(sensor==2)
        {
            analogWrite(motor2, mapSensorVal);
        }
        else if(sensor==3)
        {
            analogWrite(motor3, mapSensorVal);
        }
        else if(sensor==4)
        {
            analogWrite(motor4, mapSensorVal);
        }
        
        Serial.print("Sensor: ");
        Serial.print(sensor, DEC);
        Serial.print(" Valor: ");
        Serial.print(value);
        Serial.print(" Motor: ");
        Serial.println(mapSensorVal);
      }

  }
}

float fscale( float originalMin, float originalMax, float newBegin, float
newEnd, float inputValue, float curve){

  float OriginalRange = 0;
  float NewRange = 0;
  float zeroRefCurVal = 0;
  float normalizedCurVal = 0;
  float rangedValue = 0;
  boolean invFlag = 0;


  // condition curve parameter
  // limit range

  if (curve > 10) curve = 10;
  if (curve < -10) curve = -10;

  curve = (curve * -.1) ; // - invert and scale - this seems more intuitive - postive numbers give more weight to high end on output 
  curve = pow(10, curve); // convert linear scale into lograthimic exponent for other pow function

  /*
   Serial.println(curve * 100, DEC);   // multply by 100 to preserve resolution  
   Serial.println(); 
   */

  // Check for out of range inputValues
  if (inputValue < originalMin) {
    inputValue = originalMin;
  }
  if (inputValue > originalMax) {
    inputValue = originalMax;
  }

  // Zero Refference the values
  OriginalRange = originalMax - originalMin;

  if (newEnd > newBegin){ 
    NewRange = newEnd - newBegin;
  }
  else
  {
    NewRange = newBegin - newEnd; 
    invFlag = 1;
  }

  zeroRefCurVal = inputValue - originalMin;
  normalizedCurVal  =  zeroRefCurVal / OriginalRange;   // normalize to 0 - 1 float

  /*
  Serial.print(OriginalRange, DEC);  
   Serial.print("   ");  
   Serial.print(NewRange, DEC);  
   Serial.print("   ");  
   Serial.println(zeroRefCurVal, DEC);  
   Serial.println();  
   */

  // Check for originalMin > originalMax  - the math for all other cases i.e. negative numbers seems to work out fine 
  if (originalMin > originalMax ) {
    return 0;
  }

  if (invFlag == 0){
    rangedValue =  (pow(normalizedCurVal, curve) * NewRange) + newBegin;

  }
  else     // invert the ranges
  {   
    rangedValue =  newBegin - (pow(normalizedCurVal, curve) * NewRange); 
  }

  return rangedValue;
}
