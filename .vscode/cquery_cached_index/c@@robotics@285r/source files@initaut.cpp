#include "../header files/initAut"

AsyncVelIntegratedController ballIntakeAut          = AsyncControllerFactory::velIntegrated(-6);
AsyncVelIntegratedController ballIndexerAut         = AsyncControllerFactory::velIntegrated(-7);
AsyncVelIntegratedController flywheelAut            = AsyncControllerFactory::velIntegrated(+5);
AsyncVelIntegratedController lAut                   = AsyncControllerFactory::velIntegrated(+8);

ChassisControllerIntegrated driveAut = ChassisControllerFactory::create
 (
   {1, 2},
   {-3, -4},
   AbstractMotor::gearset::green,
   {4_in, 9.78_in}
);

AsyncMotionProfileController profile = AsyncControllerFactory::motionProfile
(
   1.25,
   2.0,
   5.0,
   driveAut
);

const bool right {1};
const bool left  {0};

void shoot ()
{
  ballIntakeAut.setTarget(200);
  ballIndexerAut.setTarget(200);

  pros::Task::delay(500);

  ballIntakeAut.setTarget(0);
  ballIndexerAut.setTarget(0);
}

void turn (bool direction)
{
  if (direction)
  driveAut.turnAngle(90_deg);
  else
  driveAut.turnAngle(-90_deg);
}
