#include "../header files/initRobot"

Controller joystick;

ControllerButton btnShoot												(ControllerDigital::R2);
ControllerButton btnBallIntake									(ControllerDigital::R1);
ControllerButton btnReverseBallSystem						(ControllerDigital::L1);
ControllerButton btnDoubleShot                  (ControllerDigital::X );

ControllerButton btnLUsager                     (ControllerDigital::L2);         //> 'L' refers to the robot's arm which was in the shape of an 'L' in its ealy days

ControllerButton btnLazyMode										(ControllerDigital::up);

bool ballIntakeToggle {false};
bool lazy             {false};
bool doubleShot       {false};
bool lUsage           {false};

void lControl ()
{
  if (btnLUsager.changedToPressed())
    lUsage = !lUsage;

  if (lUsage)
  {
    l.moveAbsolute(-280, 200);
  }
  else
  {
    l.moveAbsolute(0, 200);
  }
}

void ballControl ()
{
  if (btnBallIntake.changedToPressed())
    ballIntakeToggle = !ballIntakeToggle;

  if (btnDoubleShot.changedToPressed())
  {
    doubleShot = true;
    joystick.setText(0, 0, "Double Shot On");
  }

  if (btnShoot.isPressed())
  {
    ballIndexer.moveVelocity(200);
    ballIntake.moveVelocity (600);
    if (doubleShot)
      doubleShotControl();
  }
  else if (btnReverseBallSystem.isPressed())
  {
    ballIndexer.moveVelocity(-200);
    ballIntake.moveVelocity (-600);
  }
  // else if(ballIntakeToggle)
  // {
  //   ballIntake.setTarget  (200);
  //   ballIndexer.setTarget (0);
  // }
  // else
  // {
  //   ballIndexer.setTarget	(0);
  //   ballIntake.setTarget	(0);
  // }
  else if(btnBallIntake.isPressed())
  {
    ballIndexer.moveVelocity(0);
    ballIntake.moveVelocity (600);
  }
  else
  {
    ballIndexer.moveVelocity(0);
    ballIntake.moveVelocity	(0);
  }
}

void doubleShotControl ()
{
  if (flywheel.getTargetVelocity() - flywheel.getActualVelocity() > 15 && doubleShot)
  {
    doubleShot = false;

    ballIntake.moveVelocity(0);
    ballIndexer.moveVelocity(0);

    flywheel.moveVelocity(140);
    while (flywheel.getActualVelocity() <= 138)
      pros::Task::delay(10);

    ballIntake.moveVelocity(600);
    ballIndexer.moveVelocity(200);

    pros::Task::delay(500);

    joystick.clearLine(0);
  }
}

void lazyMode ()
{
  driveL.tarePosition();
  driveR.tarePosition();

  driveL.setBrakeMode(AbstractMotor::brakeMode::hold);
  driveR.setBrakeMode(AbstractMotor::brakeMode::hold);

  pros::Task::delay(500);

  driveL.moveAbsolute(0, 200);
  driveR.moveAbsolute(0, 200);
}

void doArcade ()
{
  if (!lazy)
  {
    driveL.setBrakeMode(AbstractMotor::brakeMode::coast);
    driveR.setBrakeMode(AbstractMotor::brakeMode::coast);
    drive.arcade
    (
      joystick.getAnalog(ControllerAnalog::leftY),
      joystick.getAnalog(ControllerAnalog::rightX)
    );
  }
  else
    lazyMode();
}

void doTank ()
{
  if (!lazy)
  {
    driveL.setBrakeMode(AbstractMotor::brakeMode::coast);
    driveR.setBrakeMode(AbstractMotor::brakeMode::coast);
    drive.tank
    (
      joystick.getAnalog(ControllerAnalog::leftY),
      joystick.getAnalog(ControllerAnalog::rightY)
    );
  }
  else
    lazyMode();
}
