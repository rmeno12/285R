#include "../header files/initRobot"
#include "../header files/waypoints"

void autonomous()
{
  profile.generatePath({initRed, redBall}, "Ball");
  profile.setTarget("Ball", FWD);
  profile.waitUntilSettled();

  profile.generatePath({initRed, redBall}, "Ball");
  profile.setTarget("Ball", BWD);
  profile.waitUntilSettled();
}
