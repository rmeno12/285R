#include "../header files/initOp"

void opcontrol()
{
  flywheel.setTarget(170);
  doArcade();

  brakeControl();
  ballControl();
  lControl();
}
