#pragma config(Motor,  port1,           linearR,   tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           shootL,    tmotorVex393_MC29,    openLoop, reversed)
#pragma config(Motor,  port3,           shootR,    tmotorVex393_MC29,    openLoop)
#pragma config(Motor,  port4,           lf,        tmotorVex393_MC29,    openLoop, reversed)
#pragma config(Motor,  port5,           rf,        tmotorVex393_MC29,    openLoop)
#pragma config(Motor,  port6,           rb,        tmotorVex393_MC29,    openLoop, reversed)
#pragma config(Motor,  port7,           lb,        tmotorVex393_MC29,    openLoop)
#pragma config(Motor,  port8,           scoop,     tmotorVex393_MC29,    openLoop)
#pragma config(Motor,  port9,           linearL,   tmotorVex393_MC29,    openLoop, reversed)
#pragma config(Motor,  port10,          lift,      tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"

//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "library.c"


// Teleop-only "library" functions:
const int joystickZero = 7; // Joysticks are very sensitive; it may be a bit off zero when they're not trying to move anything anyway (out of 127)

// Exponential function to map to the joystickValue
int joystickToMotor(int joystickValue)
{

	int motorValue;
	const int minimumValue = 4; // This value high = less control, less whining; this value low = more fine control, more whining, more magic blue smoke (out of 100)
	if (abs(joystickValue) < joystickZero)
	{
		motorValue = 0;
	}
	else
	{
		// We will play the piccolo
		const int motorMax = 100;
		int backwards = joystickValue < 0 ? -1 : 1;
		motorValue = (pow(1.05, abs(joystickValue)) / pow(1.05, 127)
			* (motorMax - minimumValue) + minimumValue) * backwards;
	}
	return motorValue;

}

// Reads button values to modify a motor value
int motorModifiers(int motorValue)
{

	if (driver1BtnR2 || driver2BtnR2)
	{
		// R2 to slow everything down to half
		motorValue /= 2;
	}

	return motorValue;

}

// Takes a joystick value, exponents it, and applies modifiers
int fullMotorValue(int joystickValue)
{

	return motorModifiers(joystickToMotor(joystickValue));

}


void pre_auton()
{

	// Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
	// Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts

}

task autonomous()
{

	//

}

task usercontrol()
{

	// Flags

	// Others
	int power;

	// Main loop:

	while (true)
	{
		// Button mapping:
		// Driver 1:
		// Tank Drive
		// Lift: L1/L2
		// Linear: L1/L2
		// Driver 2:
		// 50% shoot:  A
		// 70% shoot:  X
		// 100% shoot: Y

		getJoystickSettings(joystick);

		// Driver 1:

		// Tank Drive
		setLeft(fullMotorValue(driver1LeftStickY));
		setLeft(fullMotorValue(driver1RightStickY));

		// Linear
		power = 0;
		if (driver1BtnL1)
			power = 100;
		if (driver1BtnL2)
			power = -100;
		motor[linearL] = power;
		motor[linearR] = power;

		// Scoop
		power = 0;
		if (driver1BtnR1)
			power = 100;
		if (driver1BtnR2)
			power = -100;
		motor[scoop] = power;

		// Driver 2:

		// Shooting
		power = 0;
		if (driver2BtnA)
			power = 50;
		if (driver2BtnX)
			power = 75;
		if (driver2BtnY)
			power = 100;
		motor[shootL] = power;
		motor[shootR] = power;

		// Lift
		power = 0;
		if (driver2BtnL1)
			power = 100;
		if (driver2BtnL2)
			power = -50;
		motor[lift] = power;

		//motor[lf]` = 100;
		//motor[rf] = 100;
		//motor[lb] = 100;
		//motor[rb] = 100;
		//motor[scoop] = 100;
		//motor[linearL] = 100;
		//motor[linearR] = 100;
		//delay(1000000);

	}

	return;

}
