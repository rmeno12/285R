#include "../header files/initAut"
#include "../header files/waypoints"

void autonomous()
{
  profile.generatePath({initRed, redBall}, "Ball");
  profile.setTarget("Ball", FWD);
  profile.waitUntilSettled();

  // sup
}
