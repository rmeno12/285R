#include "../header files/initOp"

void opcontrol()
{
  l.reset();
  l.setMaxVelocity(125);

  while(ONLINE)
  {
    flywheel.setTarget(170);
    doArcade();

    lazyMode();
    ballControl();
    lControl();
  }
}
