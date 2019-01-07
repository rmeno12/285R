#define _USE_MATH_DEFINES

#include "initRobot.hpp"
#include <valarray>
#include <cmath>

// std::valarray<std::int32_t> sensorValsBeta = drive.getSensorVals();

class AngleTracker
{
  private:
    double absTheta  {0};
    double leftDist  {0};
    double rightDist {0};

    double deltaL {0};
    double deltaR {0};

    double lastL {0};
    double lastR {0};

  public:
    AngleTracker (double left, double right, double initialTheta = 0)
    {
      leftDist = left;
      rightDist = right;
      absTheta = initialTheta;

      std::valarray<std::int32_t> sensorVals = drive.getSensorVals();
    }

    void track ()
    {
      std::valarray<std::int32_t> sensorVals = drive.getSensorVals();

      deltaL = sensorVals[0] - lastL;
      deltaR = sensorVals[1] - lastR;

      absTheta += - (deltaL - deltaR) / (leftDist + rightDist);

      lastL = sensorVals[0];
      lastR = sensorVals[1];
    }

    double getAngle (bool radians = true)
    {
      if (radians)
        return absTheta;
      else
        return absTheta * 180/M_PI;
    }
};

AngleTracker doesntMatter {0, 0, 1};
