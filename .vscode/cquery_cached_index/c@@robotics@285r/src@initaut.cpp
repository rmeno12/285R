#include "../header files/initRobot"

AsyncMotionProfileController profile = AsyncControllerFactory::motionProfile
(
   1.25,
   2.0,
   5.0,
   drive
);

const bool right {1};
const bool left  {0};

void shoot ()
{
  ballIntake.moveVelocity(200);
  ballIndexer.moveVelocity(200);

  pros::Task::delay(500);

  ballIntake.moveVelocity(0);
  ballIndexer.moveVelocity(0);
}

void turn (bool direction)
{
  if (direction)
  drive.turnAngle(90_deg);
  else
  drive.turnAngle(-90_deg);
}
