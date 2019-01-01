#include "../header files/initOp"

Controller joystick;

ControllerButton btnShoot												(ControllerDigital::R1);
ControllerButton btnBallIntake									(ControllerDigital::R2);
ControllerButton btnReverseBallSystem						(ControllerDigital::L2);

// ControllerButton btnLU													(ControllerDigital::up);         //> 'L' refers to the robot's arm which was in the shape of an 'L' in its ealy days
// ControllerButton btnLD													(ControllerDigital::down);       //> 'L' refers to the robot's arm which was in the shape of an 'L' in its ealy days
ControllerButton btnLUsager                     (ControllerDigital::L1);         //> 'L' refers to the robot's arm which was in the shape of an 'L' in its ealy days

ControllerButton btnLazyMode										(ControllerDigital::up);

AsyncVelIntegratedController ballIndexer            = AsyncControllerFactory::velIntegrated(+5);
AsyncVelIntegratedController ballIntake             = AsyncControllerFactory::velIntegrated(-4);
AsyncVelIntegratedController flywheel               = AsyncControllerFactory::velIntegrated(+6);
AsyncPosIntegratedController l                      = AsyncControllerFactory::posIntegrated(-7);

ChassisControllerIntegrated drive = ChassisControllerFactory::create
 (
   {-1, -2},
   {10, 9},
   AbstractMotor::gearset::green,
   {4_in, 9.78_in}
);

bool ballIntakeToggle {false};
bool lazy             {false};

bool lUsage            {0};

void lControl ()
{
  if (btnLUsager.changedToPressed())
    lUsage = !lUsage;

  else if(lUsage)
  {
    l.setTarget           (-280);
  }
  else
  {
    l.setTarget	          (13);
  }
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

void lazyMode ()
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
    joystick.getAnalog(ControllerAnalog::rightX)
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
