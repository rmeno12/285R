#include "main.h"

// OpControl Initializations //
Controller joystick;
ControllerButton btnLU													(ControllerDigital::up);
ControllerButton btnLD													(ControllerDigital::down);

ControllerButton btnShoot												(ControllerDigital::R1);
ControllerButton btnBallIntake									(ControllerDigital::R2);
ControllerButton btnReverseBallSystem						(ControllerDigital::L2);

ControllerButton btnLazyMode										(ControllerDigital::L1);

auto drive = ChassisControllerFactory::create
 (
   {1, 2},
   {-3, -4},
   AbstractMotor::gearset::green,
   {4_in, 9.78_in}
);

auto ballIndexer            = AsyncControllerFactory::velIntegrated(-7);
auto ballIntake             = AsyncControllerFactory::velIntegrated(-6);
auto flywheel               = AsyncControllerFactory::velIntegrated(+5);
auto l                      = AsyncControllerFactory::velIntegrated(-8);

bool ballIntakeToggle {true};
bool lazy             {false};


// OpControl Control Functions //
void lControl()
{
  if (btnLU.isPressed())
    l.setTarget(+125);
  else if (btnLD.isPressed())
    l.setTarget(-125);
  else
    l.setTarget(0);
}

void ballControl()
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

void brakeControl()
{
  if (btnLazyMode.changedToPressed())
    lazy = !lazy;
  if (lazy)
    drive.setBrakeMode(AbstractMotor::brakeMode::hold);
  else
    drive.setBrakeMode(AbstractMotor::brakeMode::coast);
}
