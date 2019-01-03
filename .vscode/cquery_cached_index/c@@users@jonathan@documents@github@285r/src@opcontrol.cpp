#include "../header files/initOp"

void opcontrol()
{
  l.reset();
  l.setMaxVelocity(125);
  // pros::Task lazyMode(lazyModeFn, (void*)"something", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "LazyMode");
  std::string rpm = "";
  while(ONLINE)
  {
    flywheel.setTarget(95);

    if (btnLazyMode.changedToPressed())
      lazy = !lazy;

    doArcade();
    // lazyModeFn();
    doubleShotControl();
    ballControl();
    lControl();
  }
}
