/*

	created by Sebastian M. Strauch 2016 to control three boards of each 8 stepsticks controlled by MCP23017 to minimize connections
	
	loosely based on quadstep by Aaron Weiss, SparkFun electronics 2011

*/

#ifndef octostep_h
#define octostep_h

#if ARDUINO >= 100
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

class octostep {
  public:
	octostep();
    void motor_go(int motnum, int step_size, int number_of_steps, int torque);
	void init();
	void switchvalve(int mcp_address, int valvekombiA, int valvekombiB);
	//void stall(int motnum);
 
  private:
	void current_control(int step);
	int _torque;
	int step1;
	int step2;
	int step4;
	int step8;
	int step16;
	int _mot_exp_addr;
	int _sec_exp_addr;
	int _mot_comm_set;
	int _mot_num;
	int _sec_comm_a;
	int _sec_comm_b;
	
};//fucking important semicolon!
#endif

