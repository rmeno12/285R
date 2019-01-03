#include "../header files/initOp"
#include <string>

Controller joystick;

ControllerButton btnDoubleShot                  (ControllerDigital::X);
ControllerButton btnShoot												(ControllerDigital::R2);

ControllerButton btnBallIntake									(ControllerDigital::R1);
ControllerButton btnReverseBallSystem						(ControllerDigital::L1);

ControllerButton btnL                           (ControllerDigital::L2);         //> 'L' refers to the robot's arm which was in the shape of an 'L' in its ealy days

ControllerButton btnLazyMode										(ControllerDigital::up);

AsyncVelIntegratedController ballIndexer            = AsyncControllerFactory::velIntegrated(+5);
AsyncVelIntegratedController ballIntake             = AsyncControllerFactory::velIntegrated(-4);
AsyncVelIntegratedController flywheel               = AsyncControllerFactory::velIntegrated(+6);
AsyncPosIntegratedController l                      = AsyncControllerFactory::posIntegrated(-7);

ChassisControllerIntegrated drive = ChassisControllerFactory::create
 (
   {1, -2},
   {-10, 9},
   AbstractMotor::gearset::green,
   {4_in, 9.78_in}
);

MotorGroup driveL = MotorGroup({1, -2});
MotorGroup driveR = MotorGroup({9, -10});

bool ballIntakeToggle {false};
bool lazy             {false};
bool doubleShot       {false};

bool lUsage            {0};

void lControl ()
{
  if (btnL.changedToPressed())
    lUsage = !lUsage;

  else if(lUsage)
  {
    l.setTarget           (-280);
  }
  else
  {
    l.setTarget	          (0);
  }
}

void ballControl ()
{
  if (btnBallIntake.changedToPressed())
    ballIntakeToggle = !ballIntakeToggle;

  if (btnDoubleShot.changedToPressed())
    doubleShot = true;

  if (btnShoot.isPressed())
  {
    ballIndexer.setTarget	(+200);
    ballIntake.setTarget	(+200);
    if (doubleShot)
      doubleShotControl();
  }
  else if (btnReverseBallSystem.isPressed())
  {
    ballIndexer.setTarget (-200);
    ballIntake.setTarget  (-200);
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
    ballIntake.setTarget  (200);
    ballIndexer.setTarget (0);
  }
  else
  {
    ballIndexer.setTarget	(0);
    ballIntake.setTarget	(0);
  }
}

void doubleShotControl ()
{
  std::string doing = "Doing Double Shot";

  if (flywheel.getError() > 15 && doubleShot)
  {
    doubleShot = false;
    joystick.setText(0, 0, doing);

    ballIntake.setTarget(0);
    ballIndexer.setTarget(0);

    flywheel.setTarget();
    flywheel.waitUntilSettled();

    ballIntake.setTarget(200);
    ballIndexer.setTarget(200);
    pros::Task::delay(1000);
    joystick.clearLine(0);
  }
}

void lazyModeFn ()
{
  driveL.tarePosition();
  driveR.tarePosition();

  driveL.setBrakeMode(AbstractMotor::brakeMode::hold);
  driveR.setBrakeMode(AbstractMotor::brakeMode::hold);

  pros::Task::delay(1000);

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
    lazyModeFn();
}

void doTank ()
{
  drive.tank
  (
    joystick.getAnalog(ControllerAnalog::leftY),
    joystick.getAnalog(ControllerAnalog::rightY)
  );
}
