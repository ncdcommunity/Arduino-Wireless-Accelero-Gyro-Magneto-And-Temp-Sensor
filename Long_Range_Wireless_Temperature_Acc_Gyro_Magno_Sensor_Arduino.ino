///this code is written and tested for ncd.io IoT Long Range Wireless Accelero, Gyro, Magneto And Temp Sensor with arduino due
///sensor data structure can be found here https://ncd.io/long-range-iot-wireless-accelerometer-gyroscope-magneto-temperature-sensor-product-manual/
/// sensor can be found here https://store.ncd.io/product/long-range-iot-wireless-accelerometer-gyroscope-magneto-sensor/

  uint8_t data[54];
  int k = 10;
  int i;
void setup()
{
  Serial1.begin(9600);
  Serial.begin(9600);
  Serial.println("ncd.io IoT Arduino Wireless Accelero, Gyro, Magneto And Temperature Sensor");
}

void loop()
{
  
  if (Serial1.available())
  {
    data[0] = Serial1.read();
    delay(k);
   if(data[0]==0x7E)
    {
    while (!Serial1.available());
    for ( i = 1; i< 54; i++)
      {
      data[i] = Serial1.read();
      delay(1);
      }
    if(data[15]==0x7F)  /////// to check if the recive data is correct
      {
  if(data[22]==0x05)  //////// make sure the sensor type is correct
  {
  int16_t acc_x = ((uint16_t)(((data[24])<<16) + ((data[25])<<8) + (data[26]))/100);
  int16_t acc_y = ((uint16_t)(((data[27])<<16) + ((data[28])<<8) + (data[29]))/100);
  int16_t acc_z = ((uint16_t)(((data[30])<<16) + ((data[31])<<8) + (data[32]))/100);

  int16_t mag_x = ((uint16_t)(((data[33])<<16) + ((data[34])<<8) + (data[35]))/100);
  int16_t mag_y = ((uint16_t)(((data[36])<<16) + ((data[37])<<8) + (data[38]))/100);
  int16_t mag_z = ((uint16_t)(((data[39])<<16) + ((data[40])<<8) + (data[41]))/100);

  int16_t dps_x = ((uint16_t)(((data[42])<<16) + ((data[43])<<8) + (data[44])));
  int16_t dps_y = ((uint16_t)(((data[45])<<16) + ((data[46])<<8) + (data[47])));
  int16_t dps_z = ((uint16_t)(((data[48])<<16) + ((data[49])<<8) + (data[50])));

  
  int cTemp = ((((data[51]) * 256) + data[52]));
  float battery = ((data[18] * 256) + data[19]);
  float voltage = 0.00322 * battery;
  Serial.print("Sensor Number  ");
  Serial.println(data[16]);
  Serial.print("Sensor Type  ");
  Serial.println(data[22]);
  Serial.print("Firmware Version  ");
  Serial.println(data[17]);
  Serial.print("Temperature in Celsius :");
  Serial.print(cTemp);
  Serial.println(" C");
  
  Serial.print("Acceleration in X-axis :");
  Serial.print(acc_x);
  Serial.println(" mg");
  Serial.print("Acceleration in Y-axis :");
  Serial.print(acc_y);
  Serial.println(" mg");
  Serial.print("Acceleration in Z-axis :");
  Serial.print(acc_z);
  Serial.println(" mg");

  Serial.print("Magnetic Field in X-axis :");
  Serial.print(mag_x);
  Serial.println(" mgauss");
  Serial.print("Magnetic Field in Y-axis :");
  Serial.print(mag_y);
  Serial.println(" mgauss");
  Serial.print("Magnetic Field in Z-axis :");
  Serial.print(mag_z);
  Serial.println(" mgauss"); 

  Serial.print("Gyro Rate in X-axis :");
  Serial.print(dps_x);
  Serial.println(" mdps");
  Serial.print("Gyro Rate  in Y-axis :");
  Serial.print(dps_y);
  Serial.println(" mdps");
  Serial.print("Gyro Rate  in Z-axis :");
  Serial.print(dps_z);
  Serial.println(" mdps"); 

  
  Serial.print("ADC value:");
  Serial.println(battery);
  Serial.print("Battery Voltage:");
  Serial.print(voltage);
  Serial.println("\n");
  if (voltage < 1)
          {
    Serial.println("Time to Replace The Battery");
          }
  
        }
      }
else
{
      for ( i = 0; i< 54; i++)
    {
      Serial.print(data[i]);
      Serial.print(" , ");
      delay(1);
    }
}
    }
  }
 
}
