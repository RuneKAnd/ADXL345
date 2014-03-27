// Accelerometer ADXL345
#include <Wire.h> // I2C library, gyroscope
#include <Functions.h>
#define ACC (0xA7>>1)    //ADXL345 ACC address
#define Functions
const int Xcorrection = 0;    //Determine these by zeroing their values when they are not the axis measuring gravity
const int Ycorrection = 271;
const int Zcorrection = -906;
void setup(){
Serial.begin(115200);
Wire.begin();
initAcc();
}

void loop(){
int hx,hy,hz;
int acc[3];
getAccelerometerData(acc);
hx = acc[0];
hy = acc[1];
hz = acc[2];

Serial.print(" X="); Serial.print(hx);
Serial.print(" Y="); Serial.print(hy);
Serial.print(" Z="); Serial.print(hz);
Serial.println(" ");
delay(50); 
}

void initAcc() {
//Turning on the ADXL345
writeTo(ACC, 0x2D, 0x08);  //Power-saving features control
writeTo(ACC, 0x31, 0x0B);  //Data format control
writeTo(ACC, 0x2C, 0x0A);  //Data rate and power mode control
writeTo(ACC, 0x1E, 0x28);  //X-Axis offset
writeTo(ACC, 0x1F, 0x00);  //Y-Axis offset
writeTo(ACC, 0x20, 0x00);  //Z-Axis offset
//by default the device is in +-2g range reading
}

void getAccelerometerData(int * result) {
int regAddress = 0x32;    //first axis-acceleration-data register on the ADXL345
byte buff[6];
readFrom(ACC, regAddress, 6, buff); //read the acceleration data from the ADXL345
//each axis reading comes in 10 bit resolution, ie 2 bytes.  Least Significat Byte first!!
//thus we are converting both bytes in to one int
result[0] = ((((int)buff[1]) << 8) | buff[0])+ Xcorrection;   
result[1] = ((((int)buff[3]) << 8) | buff[2])+ Ycorrection;
result[2] = ((((int)buff[5]) << 8) | buff[4])+ Zcorrection;
}


void writeTo(int DEVICE, unsigned char address, unsigned char val) {
 Wire.beginTransmission(DEVICE); //start transmission to ACC 
 Wire.write(address);        // send register address
 Wire.write(val);        // send value to write
 Wire.endTransmission(); //end transmission
}


//reads num bytes starting from address register on ACC in to buff array
void readFrom(int DEVICE, unsigned char address, int num, unsigned char buff[]) {
Wire.beginTransmission(DEVICE); //start transmission to ACC 
Wire.write(address);        //sends address to read from
Wire.endTransmission(); //end transmission
Wire.beginTransmission(DEVICE); //start transmission to ACC
Wire.requestFrom(DEVICE, num);    // request 6 bytes from ACC
int i = 0;
while(Wire.available())    //ACC may send less than requested (abnormal)
  { 
  buff[i] = Wire.read(); // receive a byte
  i++;
  }
Wire.endTransmission(); //end transmission
}


