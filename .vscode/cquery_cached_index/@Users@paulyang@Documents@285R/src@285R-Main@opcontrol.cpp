#include "285R-Main/initRobot.hpp"

void opcontrol()
{
  l.tarePosition();
  while(ONLINE)
  {
    flywheel.moveVelocity(190);

    if (btnLazyMode.changedToPressed())
      lazy = !lazy;

    doArcade();

    doubleShotControl();
    ballControl();
    lControl();
  }
}
