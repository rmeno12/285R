#include "headers/initOp"

void opcontrol()
{
  drive.arcade
  (
    joystick.getAnalog(ControllerAnalog::leftY),
    joystick.getAnalog(ControllerAnalog::rightY)
  );

  brakeControl();
  ballControl();
  lControl();
}
