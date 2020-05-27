#include <LiquidCrystal.h>

#define WIZNET_W5100  1

#include <Ethernet.h>
#include <LiquidCrystal.h>

//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

IPAddress ModbusDeviceIP(192, 168, 0, 244);  // Put IP Address of PLC here
IPAddress moduleIPAddress(192, 168, 0, 240);  // Assign Anything other than the PLC IP Address

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xE1 };


#include <ModbusTCP.h>

ModbusTCP node(255);                            // Unit Identifier.

int pinBotao_liga = 21; //Declara pino do botao liga
int pinBotao_emergencia = 20; //Declara pino do botao emergencia
int pinBotao_next = 22;
int pinPotenciometro = A15; //Declara pino potenciometro
int teste = 0;
bool ligado = false;
float kp = 0.7;//31.2;
float ki = 0.1;//0.167;
float kd = 0.0;
float error;
int botao_liga = 1;
int botao_emergencia;
int var = 1;
int next;
int page = 1;
float flow;
float rotation;
float opening;
float setPoint;

unsigned int f_2uint_int1(float float_number) {             // split the float and return first unsigned integer

  union f_2uint {
    float f;
    uint16_t i[2];
  };

  union f_2uint f_number;
  f_number.f = float_number;

  return f_number.i[0];
}

unsigned int f_2uint_int2(float float_number) {            // split the float and return second unsigned integer

  union f_2uint {
    float f;
    uint16_t i[2];
  };

  union f_2uint f_number;
  f_number.f = float_number;

  return f_number.i[1];
}

float f_2uint_float(unsigned int uint1, unsigned int uint2) {    // reconstruct the float from 2 unsigned integers

  union f_2uint {
    float f;
    uint16_t i[2];
  };

  union f_2uint f_number;
  f_number.i[0] = uint1;
  f_number.i[1] = uint2;

  return f_number.f;

}

//Define os pinos que serão utilizados para ligação ao display
LiquidCrystal lcd(12, 13, 7, 6, 5, 4);

void setup()
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("MF OFF");

  pinMode(pinPotenciometro, INPUT); //potenciometro
  pinMode(pinBotao_liga, INPUT); //botao digital
  pinMode(pinBotao_emergencia, INPUT); //botao digital
  pinMode(pinBotao_next, INPUT); //botao digital

  delay(1000);

  Ethernet.begin(mac, moduleIPAddress);
  node.setServerIPAddress(ModbusDeviceIP);

  delay(1000);                                // To provide sufficient time to initialize.
}


void loop()
{
  if (var == 1) {
    int botao_liga = digitalRead(pinBotao_liga);
    int botao_emergencia = digitalRead(pinBotao_emergencia);
    int botao_next = digitalRead(pinBotao_next);
    //String readString;
    delay(1000);
    float potenciometro = analogRead(pinPotenciometro);

    setPoint = map(potenciometro, 0, 1023, 0, 900);




    if (botao_liga == 0)
    {
      node.writeSingleRegister(9100, 1);                  // Write single register
      ligado = true;
      lcd.setCursor(3, 0);
      lcd.print("ON ");
      teste = 11;
      //    Serial.println(teste);
    }

    if (botao_emergencia == 0)
    {
      node.writeSingleRegister(9100, 2);                  // Write single register
      ligado = false;

      //Kp
      unsigned int aux_Kp1, aux_Kp2;
      aux_Kp1 = f_2uint_int1(kp);
      aux_Kp2 = f_2uint_int2(kp);
      node.writeSingleRegister(52484, aux_Kp1);
      node.writeSingleRegister(52485, aux_Kp2);

      //Ki
      unsigned int aux_Ki1, aux_Ki2;
      aux_Ki1 = f_2uint_int1(ki);
      aux_Ki2 = f_2uint_int2(ki);
      node.writeSingleRegister(52486, aux_Ki1);
      node.writeSingleRegister(52487, aux_Ki2);

      //Kd
      //unsigned int aux_Kd1, aux_Kd2;
      //aux_Kd1 = f_2uint_int1(kd);
      //aux_Kd2 = f_2uint_int2(kd);
      //node.writeSingleRegister(52488, aux_Kd1);
      //node.writeSingleRegister(52489, aux_Kd2);


    }


    float pid;

    if (ligado == true)
    {
      uint8_t result;
      result = node.readHoldingRegisters(53600, 2);    // Read Holding Registers 52000
      unsigned int aux_flow1, aux_flow2;
      aux_flow1 = node.getResponseBuffer(0);
      aux_flow2 = node.getResponseBuffer(1);

      flow = f_2uint_float(aux_flow1, aux_flow2);

      node.clearResponseBuffer();

      uint8_t Rotation;
      Rotation = node.readHoldingRegisters(52008, 2);    // Read Holding Registers 52000
      unsigned int aux_rotation1, aux_rotation2;
      aux_rotation1 = node.getResponseBuffer(0);
      aux_rotation2 = node.getResponseBuffer(1);

      rotation = f_2uint_float(aux_rotation1, aux_rotation2);

      node.clearResponseBuffer();

      uint8_t Opening;
      Opening = node.readHoldingRegisters(52480, 2);    // Read Holding Registers 52000
      unsigned int aux_opening1, aux_opening2;
      aux_opening1 = node.getResponseBuffer(0);
      aux_opening2 = node.getResponseBuffer(1);

      opening = f_2uint_float(aux_opening1, aux_opening2);

      node.clearResponseBuffer();


      unsigned int aux_setPoint1, aux_setPoint2;
      aux_setPoint1 = f_2uint_int1(setPoint);
      aux_setPoint2 = f_2uint_int2(setPoint);
      node.writeSingleRegister(52482, aux_setPoint1);                  // Write single register 52483 52402
      node.writeSingleRegister(52483, aux_setPoint2);                  // Write single register 52403

      error = ((setPoint - flow) / setPoint) * 100;

      if (error < 0 ) {
        error = error * (-1);
      }




    }
    lcd.setCursor(8, 0);
    lcd.print("SP:");
    lcd.print(setPoint);

    lcd.setCursor(0, 1);
    lcd.print("PV:");
    lcd.print(opening); 
      
    lcd.setCursor(7, 1);
    lcd.print(" MV:");
    lcd.print(flow);  
    var = 0;
  }
  else {



    Serial.println(String("entrei") + " " + String(flow) + " " + String(setPoint) + " " + String(rotation) + " " + String(opening));
    //while(Serial.available()){
    //if (Serial.available() > 0)
    //{
    //  //Serial.println(String(flow));
    //  char c = Serial.read();
    //  //Serial.println(c);
    //  //readString = c;
    //if ( c == '1') {
    //    digitalWrite(LED_BUILTIN, HIGH);
    //    botao_liga = 0;
    //    //botao_emergencia = 1;
    //}
    //  else if (c == '0') {
    //    digitalWrite(LED_BUILTIN, LOW);
    //    botao_liga = 1;
    //    //botao_emergencia = 0;
    //  }
    //}
    var = 1;
  }

}
