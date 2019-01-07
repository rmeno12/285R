#include "initRobot.hpp"
#include <valarray>

class AngleTracker
{
  private:
    double absTheta;
    double leftDist;
    double rightDist;

    double deltaL = 0;
    double deltaR = 0;

    double lastL = 0;
    double lastR = 0;

    std::valarray<std::int32_t> sensorVals;

  public:
    AngleTracker(ChassisController drive, double left, double right, double initialTheta = 0)
    {
      leftDist = left;
      rightDist = right;
      absTheta = initialTheta;
      sensorVals = drive.getSensorVals();
    }

    void track()
    {
      sensorVals = drive.getSensorVals();

      deltaL = sensorVals[0] - lastL;
      deltaR = sensorVals[1] - lastR;

      absTheta += - (deltaL - deltaR) / (leftDist + rightDist);

      lastL = sensorVals[0];
      lastR = sensorVals[1];
    }

    double getAngle(bool radians = true) {return absTheta;}
};
