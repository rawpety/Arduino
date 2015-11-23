//...........................................................
// this code Based on : http://playground.arduino.cc/Main/MaxSonar
int pw_pin1=7;
int pw_pin2=6;
int arraysize = 9;
int array1[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0};
long inch1;
int exact_cm_value1;
int array2[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0};
long inch2;
int exact_cm_value2;
const int analogOutPin1 = 9;
const int analogOutPin2 = 8;

int outputValue1 = 0; 
int outputValue2 = 0; 
     
void setup() {
  // put your setup code here, to run once:
   pinMode(pw_pin1, INPUT);
   pinMode(pw_pin2, INPUT);
   Serial.begin(9600);
}
void sensorRead(int sensor, long inch,int array[]){
  for(int i = 0; i < arraysize; i++)
  {           
    inch = pulseIn(sensor, HIGH);
    array[i] = inch/58;
    delay(10);
  }
}
void array_arrangment(int *a,int n){
//  Author: Bill Gentles, Nov. 12, 2010)
   for (int i = 1; i < n; ++i)
  {
    int j = a[i];
    int k;
    for (k = i - 1; (k >= 0) && (j < a[k]); k--)
    {
      a[k + 1] = a[k];
    }
    a[k + 1] = j;
  }
}

int filter(int *a,int n){
int i = 0;
  int count = 0;
  int maxCount = 0;
  int filter = 0;
  int median;
  int prevCount = 0;
  while(i<(n-1)){
    prevCount=count;
    count=0;
    while(a[i]==a[i+1]){
      count++;
      i++;
    }
    if(count>prevCount && count>maxCount){
      filter=a[i];
      maxCount=count;
      median=0;
    }
    if(count==0){
      i++;
    }
    if(count==maxCount){//If the dataset has 2 or more modes.
      median=1;
    }
    if(filter==0||median==1){//Return the median if there is no mode.
      filter=a[(n/2)];
    }

    return filter;
   
  } 
}
void loop() {
  // put your main code here, to run repeatedly:
  sensorRead(pw_pin1,inch1,array1);
  
  array_arrangment(array1,arraysize);
  exact_cm_value1= filter(array1,arraysize);
  Serial.print("The distance 1 = ");
  Serial.print(exact_cm_value1);
  Serial.println(" cm ");

  outputValue1 = map(exact_cm_value1, 14, 70, 255, 0); 
  if(outputValue1 > 0)
    analogWrite(analogOutPin1, outputValue1);
   else
    analogWrite(analogOutPin1, 0);

  Serial.print("out 1 = ");
  Serial.println(outputValue1);
  
  
  sensorRead(pw_pin2, inch2,array2);
  
  array_arrangment(array2,arraysize);
  exact_cm_value2= filter(array2,arraysize);
  Serial.print("The distance 2 = ");
  Serial.print(exact_cm_value2);
  Serial.println(" cm ");
  
  outputValue2 = map(exact_cm_value2, 14, 70, 255, 0); 
  if(outputValue2 > 0)
    analogWrite(analogOutPin2, outputValue2);
   else
    analogWrite(analogOutPin2, 0);

  Serial.print("out 2 = ");
  Serial.println(outputValue2);
  
 
}
