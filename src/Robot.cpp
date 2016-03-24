#include "WPILib.h"

/**
 * This sample program shows how to control a motor using a joystick. In the operator
 * control part of the program, the joystick is read and the value is written to the motor.
 *
 * Joystick analog values range from -1 to 1 and speed controller inputs as range from
 * -1 to 1 making it easy to work together. The program also delays a short time in the loop
 * to allow other threads to run. This is generally a good idea, especially since the joystick
 * values are only transmitted from the Driver Station once every 20ms.
 */
class Robot : public IterativeRobot {
	Joystick r_stick;
	Joystick l_stick;

	// The motor to control with the Joystick.
	// This uses a Talon speed controller; use the Victor or Jaguar classes for
	//   other speed controllers.
	Talon r_motor;
	Talon l_motor;
	Talon fire_motor; // Laucnher sim motor left
	Talon fire_motor1; // launcher sim motor right
	Jaguar pickup_motor;
	Jaguar trigger_motor;


	int autoLoopCounter;



	// update every 0.005 seconds/5 milliseconds.
	double kUpdatePeriod = 0.005;

public:
	Robot() :
			r_stick(0), // Initialize Joystick on port 0.
			l_stick(1),
			r_motor(1),// Initialize the Talon on channel 0.
			l_motor(0),
			fire_motor(2),
			fire_motor1(3),
			pickup_motor(4),
			trigger_motor(5)
	{
	}
	/**
	 * Runs the motor from the output of a Joystick.
	 */
	void TeleopInit()
	{


	}
	void TeleopPeriodic() {
			// Set the motor controller's output.
			// This takes a number from -1 (100% speed in reverse) to +1 (100% speed forwards).
			r_motor.Set(r_stick.GetY());
			l_motor.Set(l_stick.GetY());

			float l_fire_speed = l_stick.GetZ();
			float r_fire_speed = r_stick.GetZ();

			if(l_fire_speed > 0.0)
			{
				l_fire_speed = 0.0;
			}
			if(r_fire_speed > 0.0)
			{
				r_fire_speed = 0.0;
			}

			fire_motor.Set(l_fire_speed);
			fire_motor1.Set(r_fire_speed);

			if(r_stick.GetTrigger())
			{
				//trigger_motor.Set(1);
				fire_motor.Set(l_fire_speed);
				fire_motor1.Set(r_fire_speed);
			}else{
				//trigger_motor.Set(0);
				fire_motor.Set(0);
				fire_motor1.Set(0);
			}

			if(l_stick.GetTrigger())
			{
				pickup_motor.Set(-0.7);
			}else{
				pickup_motor.Set(0);
			}

			Wait(kUpdatePeriod); // Wait 5ms for the next update.
		}


	void AutonomousInit()
	{

		autoLoopCounter = 0;

	}

	void AutonomousPeriodic()
	{

		fire_motor.Set(0);
		fire_motor1.Set(0);
		if(autoLoopCounter < 200) //Check if we've completed 100 loops (approximately 2 seconds)
		{
			l_motor.Set(-1.0);
			r_motor.Set(-1.0);
		} else {
			l_motor.Set(0);
			r_motor.Set(0);

		}



		autoLoopCounter++;



	}


};

START_ROBOT_CLASS(Robot)
