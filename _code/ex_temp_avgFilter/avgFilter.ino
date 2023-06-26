#define NUM 10
struct avgFilter
{
  float sum = 0.0;
  float data[NUM];
  int index = 0;

  void initData(void)
  {
    for (int i=0 ; i<NUM ; i++)
      data[i] = 0.0;    
  }

  float filteredData(float newData)
  {
    sum = sum - data[index];
    data[index] = newData;
    sum = sum + data[index];
    index++;
  
    if(index >= NUM) index = 0;
  
    return sum/NUM;
  }
};


avgFilter Temp;
int temp = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  float filteredData = 0.0;
  for (int i=0 ; i<NUM ; i++)
  {
    float valADC = analogRead(temp);
    float tempDegree = 320*valADC / 1024 - 50;
    //Serial.print("rawTemp,");
    Serial.print(tempDegree);
    filteredData = Temp.filteredData(tempDegree);
    Serial.print(",");
    Serial.println(filteredData);
  }
  delay(100);
  
}
