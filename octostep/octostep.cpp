/*

	created by Sebastian M. Strauch 2016 to control three boards of each 8 stepsticks controlled by MCP23017 to minimize connections
	
	loosely based on quadstep by Aaron Weiss, SparkFun electronics 2011

*/

//#include "WProgram.h"
#include "Arduino.h"
#include "octostep.h"
#include "Wire.h"

#define sbi(var, mask)   ((var) |= (uint8_t)(1 << mask))
#define cbi(var, mask)   ((var) &= (uint8_t)~(1 << mask))

#define STEPMIN	800 //used to be 800

octostep::octostep()
{
  pinMode(11, OUTPUT); //PB5

  cbi(PORTB, 5);

  Serial.begin(9600);
  Serial.println("object created");
}

void octostep::init()
{
  Wire.begin();
  
  //Board 1
  Wire.beginTransmission(0x20);
  Wire.write(0x0A); // IOCONA register
  Wire.write(0x20); // disables sequential op mode
  Wire.endTransmission();

  Wire.beginTransmission(0x20);
  Wire.write(0x0B); // IOCONB register
  Wire.write(0x20); // disables sequential op mode
  Wire.endTransmission();

  Wire.beginTransmission(0x20);
  Wire.write(0x00); // IODIRA register
  Wire.write(0x00); // set all of port A to outputs, then toggles automatically to IODIRB
  Wire.write(0x00); // set all of port B to outputs
  Wire.endTransmission();
  
  Wire.beginTransmission(0x20);
  Wire.write(0x14); // OLATA
  Wire.write(0xFF); // port A, then toggles automatically to OLATB
  Wire.write(0xFF); // port B
  Wire.endTransmission();
  
  Serial.println("0x20 initialized");

  Wire.beginTransmission(0x21);
  Wire.write(0x0A); // IOCONA register
  Wire.write(0x20); // disables sequential op mode
  Wire.endTransmission();

  Wire.beginTransmission(0x21);
  Wire.write(0x0B); // IOCONB register
  Wire.write(0x20); // disables sequential op mode
  Wire.endTransmission();

  Wire.beginTransmission(0x21);
  Wire.write(0x00); // IODIRA register
  Wire.write(0x00); // set all of port A to outputs, then toggles automatically to IODIRB
  Wire.write(0x00); // set all of port B to outputs
  Wire.endTransmission();
  
  Wire.beginTransmission(0x21);
  Wire.write(0x14); // OLATA
  Wire.write(0xFF); // port A, then toggles automatically to OLATB
  Wire.write(0xFF); // port B
  Wire.endTransmission();
  
   Serial.println("0x21 initialized");
   
   //Board2
  Wire.beginTransmission(0x22);
  Wire.write(0x0A); // IOCONA register
  Wire.write(0x20); // disables sequential op mode
  Wire.endTransmission();

  Wire.beginTransmission(0x22);
  Wire.write(0x0B); // IOCONB register
  Wire.write(0x20); // disables sequential op mode
  Wire.endTransmission();

  Wire.beginTransmission(0x22);
  Wire.write(0x00); // IODIRA register
  Wire.write(0x00); // set all of port A to outputs, then toggles automatically to IODIRB
  Wire.write(0x00); // set all of port B to outputs
  Wire.endTransmission();
  
  Wire.beginTransmission(0x22);
  Wire.write(0x14); // OLATA
  Wire.write(0xFF); // port A, then toggles automatically to OLATB
  Wire.write(0xFF); // port B
  Wire.endTransmission();

  Wire.beginTransmission(0x23);
  Wire.write(0x0A); // IOCONA register
  Wire.write(0x20); // disables sequential op mode
  Wire.endTransmission();

  Wire.beginTransmission(0x23);
  Wire.write(0x0B); // IOCONB register
  Wire.write(0x20); // disables sequential op mode
  Wire.endTransmission();

  Wire.beginTransmission(0x23);
  Wire.write(0x00); // IODIRA register
  Wire.write(0x00); // set all of port A to outputs, then toggles automatically to IODIRB
  Wire.write(0x00); // set all of port B to outputs
  Wire.endTransmission();
  
  Wire.beginTransmission(0x23);
  Wire.write(0x14); // OLATA
  Wire.write(0xFF); // port A, then toggles automatically to OLATB
  Wire.write(0xFF); // port B
  Wire.endTransmission();
  
  
     //Board3
  Wire.beginTransmission(0x24);
  Wire.write(0x0A); // IOCONA register
  Wire.write(0x20); // disables sequential op mode
  Wire.endTransmission();

  Wire.beginTransmission(0x24);
  Wire.write(0x0B); // IOCONB register
  Wire.write(0x20); // disables sequential op mode
  Wire.endTransmission();

  Wire.beginTransmission(0x24);
  Wire.write(0x00); // IODIRA register
  Wire.write(0x00); // set all of port A to outputs, then toggles automatically to IODIRB
  Wire.write(0x00); // set all of port B to outputs
  Wire.endTransmission();
  
  Wire.beginTransmission(0x24);
  Wire.write(0x14); // OLATA
  Wire.write(0xFF); // port A, then toggles automatically to OLATB
  Wire.write(0xFF); // port B
  Wire.endTransmission();

  Wire.beginTransmission(0x25);
  Wire.write(0x0A); // IOCONA register
  Wire.write(0x20); // disables sequential op mode
  Wire.endTransmission();

  Wire.beginTransmission(0x25);
  Wire.write(0x0B); // IOCONB register
  Wire.write(0x20); // disables sequential op mode
  Wire.endTransmission();

  Wire.beginTransmission(0x25);
  Wire.write(0x00); // IODIRA register
  Wire.write(0x00); // set all of port A to outputs, then toggles automatically to IODIRB
  Wire.write(0x00); // set all of port B to outputs
  Wire.endTransmission();
  
  Wire.beginTransmission(0x25);
  Wire.write(0x14); // OLATA
  Wire.write(0xFF); // port A, then toggles automatically to OLATB
  Wire.write(0xFF); // port B
  Wire.endTransmission();
  
}

/////////////////////////////////////////////////////////
///////   Motor settings  ///////////////////////////////
/////////////////////////////////////////////////////////
void octostep::motor_go(int motnum, int step_size, int number_of_steps, int torque)
{
  _torque = torque;

  switch (motnum) {
    case 1:
      _mot_exp_addr = 0x20;
      _mot_num = 0x7F;
      break;

    case 2:
      _mot_exp_addr = 0x20;
      _mot_num = 0xBF;
      break;

    case 3:
      _mot_exp_addr = 0x20;
      _mot_num = 0xDF;
      break;

    case 4:
      _mot_exp_addr = 0x20;
      _mot_num = 0xEF;
      break;

    case 5:
      _mot_exp_addr = 0x20;
      _mot_num = 0xF7;
      break;

    case 6:
      _mot_exp_addr = 0x20;
      _mot_num = 0xFB;
      break;

    case 7:
      _mot_exp_addr = 0x20;
      _mot_num = 0xFD;
      break;

    case 8:
      _mot_exp_addr = 0x20;
      _mot_num = 0xFE;
      break;

    case 9:
      _mot_exp_addr = 0x22;
      _mot_num = 0x7F;
      break;

    case 10:
      _mot_exp_addr = 0x22;
      _mot_num = 0xBF;
      break;

    case 11:
      _mot_exp_addr = 0x22;
      _mot_num = 0xDF;
      break;

    case 12:
      _mot_exp_addr = 0x22;
      _mot_num = 0xEF;
      break;

    case 13:
      _mot_exp_addr = 0x22;
      _mot_num = 0xF7;
      break;

    case 14:
      _mot_exp_addr = 0x22;
      _mot_num = 0xFB;
      break;

    case 15:
      _mot_exp_addr = 0x22;
      _mot_num = 0xFD;
      break;

    case 16:
      _mot_exp_addr = 0x22;
      _mot_num = 0xFE;
      break;
	  
    case 17:
      _mot_exp_addr = 0x24;
      _mot_num = 0x7F;
      break;

    case 18:
      _mot_exp_addr = 0x24;
      _mot_num = 0xBF;
      break;

    case 19:
      _mot_exp_addr = 0x24;
      _mot_num = 0xDF;
      break;

    case 20:
      _mot_exp_addr = 0x24;
      _mot_num = 0xEF;
      break;

    case 21:
      _mot_exp_addr = 0x24;
      _mot_num = 0xF7;
      break;

    case 22:
      _mot_exp_addr = 0x24;
      _mot_num = 0xFB;
      break;

    case 23:
      _mot_exp_addr = 0x24;
      _mot_num = 0xFD;
      break;

    case 24:
      _mot_exp_addr = 0x24;
      _mot_num = 0xFE;
      break;
	  
  }


// sets direction of rotation
if (number_of_steps > 0)
  {
    _mot_comm_set = 0xFF;
  }
  else if (number_of_steps < 0)
  {
    _mot_comm_set = 0x7F;
  }

  number_of_steps = abs(number_of_steps);

  // check to see what step size was selected
  if (step_size == 1)
  {
    //sets speed
    current_control(1);

    //digitalWrite(_b_ms_11, LOW);
    //digitalWrite(_b_ms_12, LOW);
    //digitalWrite(_b_ms_13, LOW);
    //to translate that to the MCP-mediated solution, the proper values have to be subtracted from _mot_comm_set: byte structure is DIR MS1 MS2 MS3 RST NC NC NC.
    //So, if a ms-pin used to be high, nought is to subtracted, while a low is achieved by subtracting a bit from _mot_comm_set. Here, it is 1111 1111 - 0111 0000 or 0xFF - 0x70.

    _mot_comm_set = _mot_comm_set - 0x70;
	
	Serial.print("motor command set: ");
	Serial.println(_mot_comm_set, HEX);
	Serial.print("motor number: ");
	Serial.println(_mot_num, HEX);
	Serial.println(" ");

    Wire.beginTransmission(_mot_exp_addr);
    Wire.write(0x14);
    Wire.write(_mot_comm_set);
/*	Wire.endTransmission();
	delay(10);
    Wire.beginTransmission(_mot_exp_addr);
    Wire.write(0x15);*/
    Wire.write(_mot_num);
    Wire.endTransmission();
	delay(100);

    for (int i = 1; i <= number_of_steps; i++)
    {
      //low to high transition moves one step
      sbi(PORTB, 5);
      delayMicroseconds(step1); //high time
      cbi(PORTB, 5);
      delayMicroseconds(step1); // low time
    }
    cbi(PORTB, 5);

    Wire.beginTransmission(_mot_exp_addr);
    Wire.write(0x14);
    Wire.write(0xFF);//all high
/*	Wire.endTransmission();
	delay(10);
    Wire.beginTransmission(_mot_exp_addr);
    Wire.write(0x15);*/
    Wire.write(0xFF);//all high, motors off
    Wire.endTransmission();
  }
  else if (step_size == 2)
  {
    //sets speed
    current_control(2);

    //digitalWrite(_b_ms_11, HIGH);
    //digitalWrite(_b_ms_12, LOW);
    //digitalWrite(_b_ms_13, LOW);

    _mot_comm_set = _mot_comm_set - 0x30;
	
	Serial.print("motor command set: ");
	Serial.println(_mot_comm_set, HEX);
	Serial.print("motor number: ");
	Serial.println(_mot_num, HEX);
	Serial.println(" ");

    Wire.beginTransmission(_mot_exp_addr);
    Wire.write(0x14);
    Wire.write(_mot_comm_set);
/*	Wire.endTransmission();
	delay(10);
    Wire.beginTransmission(_mot_exp_addr);
    Wire.write(0x15);*/
    Wire.write(_mot_num);
    Wire.endTransmission();
	delay(100);

    for (int i = 1; i <= number_of_steps; i++)
    {
      //low to high transition moves one step
      sbi(PORTB, 5);
      delayMicroseconds(step2);
      cbi(PORTB, 5);
      delayMicroseconds(step2);
    }
    cbi(PORTB, 5);

    Wire.beginTransmission(_mot_exp_addr);
    Wire.write(0x14);
    Wire.write(0xFF);//all high
/*	Wire.endTransmission();
	delay(10);
    Wire.beginTransmission(_mot_exp_addr);
    Wire.write(0x15);*/
    Wire.write(0xFF);//all high, motors off
    Wire.endTransmission();

  }
  else if (step_size == 4)
  {
    //sets speed
    current_control(4);

    //digitalWrite(_b_ms_11, LOW);
    //digitalWrite(_b_ms_12, HIGH);
    //digitalWrite(_b_ms_13, LOW);

    _mot_comm_set = _mot_comm_set - 0x50;

    Wire.beginTransmission(_mot_exp_addr);
    Wire.write(0x14);
    Wire.write(_mot_comm_set);
/*	Wire.endTransmission();
	delay(10);
    Wire.beginTransmission(_mot_exp_addr);
    Wire.write(0x15);*/
    Wire.write(_mot_num);
	Wire.endTransmission();
	delay(100);
	
    for (int i = 1; i <= number_of_steps; i++)
    {
      //low to high transition moves one step
      sbi(PORTB, 5);
      delayMicroseconds(step4);
      cbi(PORTB, 5);
      delayMicroseconds(step4);
    }
    cbi(PORTB, 5);

    Wire.beginTransmission(_mot_exp_addr);
    Wire.write(0x14);
    Wire.write(0xFF);//all high
/*	Wire.endTransmission();
	delay(10);
    Wire.beginTransmission(_mot_exp_addr);
    Wire.write(0x15);*/
    Wire.write(0xFF);//all high, motors off
    Wire.endTransmission();

  }
  else if (step_size == 8)
  {
    //sets speed
    current_control(8);

    //digitalWrite(_b_ms_11, HIGH);
    //digitalWrite(_b_ms_12, HIGH);
    //digitalWrite(_b_ms_13, LOW);

    _mot_comm_set = _mot_comm_set - 0x10;

    Wire.beginTransmission(_mot_exp_addr);
    Wire.write(0x14);
    Wire.write(_mot_comm_set);
/*	Wire.endTransmission();
	delay(10);
    Wire.beginTransmission(_mot_exp_addr);
    Wire.write(0x15);*/
    Wire.write(_mot_num);
    Wire.endTransmission();
	delay(100);

    for (int i = 1; i <= number_of_steps; i++)
    {
      //low to high transition moves one step
      sbi(PORTB, 5);
      delayMicroseconds(step8);
      cbi(PORTB, 5);
      delayMicroseconds(step8);
    }
    cbi(PORTB, 5);

    Wire.beginTransmission(_mot_exp_addr);
    Wire.write(0x14);
    Wire.write(0xFF);//all high
/*	Wire.endTransmission();
	delay(10);
    Wire.beginTransmission(_mot_exp_addr);
    Wire.write(0x15);*/
    Wire.write(0xFF);//all high, motors off
    Wire.endTransmission();

  }
  else if (step_size == 16)
  {
    //sets speed
    current_control(16);

    //digitalWrite(_b_ms_11, HIGH);
    //digitalWrite(_b_ms_12, HIGH);
    //digitalWrite(_b_ms_13, HIGH);

    _mot_comm_set = _mot_comm_set - 0x00;

    Wire.beginTransmission(_mot_exp_addr);
    Wire.write(0x14);
    Wire.write(_mot_comm_set);
/*	Wire.endTransmission();
	delay(10);
    Wire.beginTransmission(_mot_exp_addr);
    Wire.write(0x15);*/
    Wire.write(_mot_num);
    Wire.endTransmission();
	delay(100);

    for (int i = 1; i <= number_of_steps; i++)
    {
      //low to high transition moves one step
      sbi(PORTB, 5);
      delayMicroseconds(step16);
      cbi(PORTB, 5);
      delayMicroseconds(step16);
    }
    cbi(PORTB, 5);

    Wire.beginTransmission(_mot_exp_addr);
    Wire.write(0x14);
    Wire.write(0xFF);//all high
/*	Wire.endTransmission();
	delay(10);
    Wire.beginTransmission(_mot_exp_addr);
    Wire.write(0x15);*/
    Wire.write(0xFF);//all high, motors off
    Wire.endTransmission();
  }

}

void octostep::current_control(int step)
{
  if (step == 1)
  {
    step1 = STEPMIN + (_torque * 260);
  }
  else if (step == 2)
  {
    step2 = (STEPMIN + (_torque * 260)) / 2;
  }
  else if (step == 4)
  {
    step4 = (STEPMIN + (_torque * 260)) / 4;
  }
  else if (step == 8)
  {
    step8 = (STEPMIN + (_torque * 260)) / 8;
  }
  else if (step == 16)
  {
    step16 = (STEPMIN + (_torque * 260)) / 16;
  }
}

void pcrmot::switchvalve(int mcp_address, int valvekombiA, int valvekombiB)
{
	Wire.beginTransmission(mcp_address);
	Wire.write(0x14);
	Wire.write(valvekombiA);
	Wire.endTransmission();
	Wire.beginTransmission(mcp_address);
	Wire.write(0x15);
	Wire.write(valvekombiB);
	Wire.endTransmission();
}

