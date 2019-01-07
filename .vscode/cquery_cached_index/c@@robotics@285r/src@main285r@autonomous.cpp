#include "initRobot.hpp"
#include "waypoints.hpp"

void autonomous()
{
  profile.generatePath({initRed, redBall}, "Ball");
  profile.setTarget("Ball", FWD);
  profile.waitUntilSettled();

  profile.generatePath({initRed, redBall}, "Ball");
  profile.setTarget("Ball", BWD);
  profile.waitUntilSettled();
}
