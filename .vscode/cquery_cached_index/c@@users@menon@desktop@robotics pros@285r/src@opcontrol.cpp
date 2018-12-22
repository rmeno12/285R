#include "headers/opcontrol.hpp"

void opcontrol()
{
	while(true)
	{
		drive.tank(joystick.getAnalog(ControllerAnalog::leftY), joystick.getAnalog(ControllerAnalog::rightY));
		flywheel.setTarget(150);

		lControl();

		ballControl();

		brakeControl();
	}
}
