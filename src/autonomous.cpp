#include "headers/initAut"
#include "headers/waypoints"

void autonomous()
{
  profile.generatePath({initRed, redBall}, "Ball");
  profile.setTarget("Ball", FWD);
  profile.waitUntilSettled();

  // sup
}
