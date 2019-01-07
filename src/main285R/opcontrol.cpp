#include "initRobot.hpp"

void opcontrol()
{
  l.tarePosition();
  while(ONLINE)
  {
    flywheel.moveVelocity(190);

    if (btnLazyMode.changedToPressed())
      lazy = !lazy;

    doArcade();
    // lazyModeFn();
    doubleShotControl();
    ballControl();
    lControl();
  }
}
