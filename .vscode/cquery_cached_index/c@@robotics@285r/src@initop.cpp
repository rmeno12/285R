#include "../header files/initOp"

Controller joystick;

ControllerButton btnShoot												(ControllerDigital::R1);
ControllerButton btnBallIntake									(ControllerDigital::R2);
ControllerButton btnReverseBallSystem						(ControllerDigital::L2);

ControllerButton btnLU													(ControllerDigital::up);         //> 'L' refers to the robot's arm which was in the shape of an 'L' in its ealy days
ControllerButton btnLD													(ControllerDigital::down);       //> 'L' refers to the robot's arm which was in the shape of an 'L' in its ealy days

ControllerButton btnLazyMode										(ControllerDigital::L1);

AsyncVelIntegratedController ballIndexer            = AsyncControllerFactory::velIntegrated(-7);
AsyncVelIntegratedController ballIntake             = AsyncControllerFactory::velIntegrated(-6);
AsyncVelIntegratedController flywheel               = AsyncControllerFactory::velIntegrated(+5);
AsyncVelIntegratedController l                      = AsyncControllerFactory::velIntegrated(-8);

ChassisControllerIntegrated drive = ChassisControllerFactory::create
 (
   {1, 2},
   {-3, -4},
   AbstractMotor::gearset::green,
   {4_in, 9.78_in}
);

bool ballIntakeToggle {true};
bool lazy             {false};

void lControl ()
{
  if (btnLU.isPressed())
    l.setTarget(+125);
  else if (btnLD.isPressed())
    l.setTarget(-125);
  else
    l.setTarget(0);
}

void ballControl ()
{
  if (btnBallIntake.changedToPressed())
    ballIntakeToggle = !ballIntakeToggle;

  if (btnShoot.isPressed())
  {
    ballIndexer.setTarget	(+200);
    ballIntake.setTarget	(+200);
  }
  else if (btnReverseBallSystem.isPressed())
  {
    ballIndexer.setTarget(-200);
    ballIntake.setTarget(-200);
  }
  else if(ballIntakeToggle)
  {
    ballIntake.setTarget(200);
    ballIndexer.setTarget(0);
  }
  else
  {
    ballIndexer.setTarget	(0);
    ballIntake.setTarget	(0);
  }
}

void brakeControl ()
{
  if (btnLazyMode.changedToPressed())
    lazy = !lazy;
  if (lazy)
    drive.setBrakeMode(AbstractMotor::brakeMode::hold);
  else
    drive.setBrakeMode(AbstractMotor::brakeMode::coast);
}

void doArcade ()
{
  drive.arcade
  (
    joystick.getAnalog(ControllerAnalog::leftY),
    joystick.getAnalog(ControllerAnalog::rightY)
  );
}

void doTank ()
{
  drive.tank
  (
    joystick.getAnalog(ControllerAnalog::leftY),
    joystick.getAnalog(ControllerAnalog::rightY)
  );
}
