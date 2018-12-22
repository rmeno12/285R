#include "headers/autonomous.hpp"
#include "headers/nodes.hpp"


Controller joystickAut;

const bool tileColor {1};                     //> set to '1' if playing on red; set to '0' if playing as blue
const bool isComp    {true};

void autonomous()
{
  if (isComp && tileColor)
  {
    flywheelAut.setTarget(150);
    ballIntakeAut.setTarget(200);

    profile.generatePath({initRed, redBall}, "Ball");
    profile.setTarget("Ball", fwd);
    profile.waitUntilSettled();

    ballIntakeAut.setTarget(0);

    profile.setTarget("Ball", bwd);
    profile.waitUntilSettled();

    profile.generatePath({initRed, hpRed}, "High Flag");
    profile.setTarget("High Flag", fwd);
    profile.waitUntilSettled();
    turn (left);
    shoot();

    profile.generatePath({hRed, mRed}, "Mid Flag");
    profile.setTarget("Mid Flag", fwd);
    profile.waitUntilSettled();
    shoot();

    flywheelAut.setTarget(0);

    profile.generatePath({mRed, lRed}, "Low Flag");
    profile.setTarget("Low Flag", fwd);
    profile.waitUntilSettled();

    profile.generatePath({lRed, cppRed}, "Flip Cap p1");
    profile.setTarget("Flip Cap p1", bwd);
    profile.waitUntilSettled();
    turn (right);

    ballIntakeAut.setTarget(-200);                          //> In autonomous the robot will not go past here

    profile.generatePath({cpRed, cRed}, "Flip Cap p2");
    profile.setTarget("Flip Cap p2", fwd);
    profile.waitUntilSettled();

    ballIntakeAut.setTarget(0);

    profile.setTarget("Flip Cap p2", bwd);
    profile.waitUntilSettled();
  }
  else if (isComp && !tileColor)
  {
    driveAut.setMaxVelocity(100);

    flywheelAut.setTarget(160);
    ballIntakeAut.setTarget(200);
    profile.generatePath({Point{11_ft, 7_ft, 180_deg}, Point{7.5_ft, 7_ft, 180_deg}}, "Get Ball");
    profile.setTarget("Get Ball");
    profile.waitUntilSettled();
    ballIntakeAut.setTarget(0);
    driveAut.moveDistance(-3.2_ft);
    turn (right);
    shoot();

    profile.generatePath({Point{10.7_ft, 7_ft, 90_deg}, Point{10.7_ft, 9.1_ft, 90_deg}}, "Mid Flag");
    profile.setTarget("Mid Flag");
    profile.waitUntilSettled();
    shoot();
    flywheelAut.setTarget(0);

    profile.generatePath({Point{10.7_ft, 9.1_ft, 90_deg}, Point{11_ft, 10.4_ft, 90_deg}}, "Low Flag");
    profile.setTarget("Low Flag");
    profile.waitUntilSettled();
    driveAut.moveDistance(-1.4_ft);
    turn (left);

    ballIntakeAut.setTarget(-200);
    driveAut.setMaxVelocity(130);
    profile.generatePath({Point{11_ft, 9_ft, 180_deg}, Point{8_ft, 9_ft, 180_deg}}, "Flip Cap");
    profile.setTarget("Flip Cap");
    profile.waitUntilSettled();
    ballIntakeAut.setTarget(0);
    driveAut.moveDistance(-0.5_ft);
  }
  else if (!isComp)
  {
    driveAut.setMaxVelocity(100);

    flywheelAut.setTarget(160);
    ballIntakeAut.setTarget(200);
    profile.generatePath({Point{1_ft, 7_ft, 0_deg}, Point{4.5_ft, 7_ft, 0_deg}}, "Ball");
    profile.setTarget("Ball");
    profile.waitUntilSettled();
    ballIntakeAut.setTarget(0);
    driveAut.moveDistance(-3.2_ft);
    turn (left);
    shoot();

    profile.generatePath({Point{1.3_ft, 7_ft, 90_deg}, Point{1.3_ft, 9.1_ft, 90_deg}}, "Mid Flag");
    profile.setTarget("Mid Flag");
    profile.waitUntilSettled();
    shoot();
    flywheelAut.setTarget(0);

    profile.generatePath({Point{1.3_ft, 9.1_ft, 90_deg}, Point{1.0_ft, 10.4_ft, 90_deg}}, "Low Flag");
    profile.setTarget("Low Flag");
    profile.waitUntilSettled();
    driveAut.moveDistance(-1.4_ft);
    turn (right);

    ballIntakeAut.setTarget(-200);
    profile.generatePath({Point{1.0_ft, 9_ft, 0_deg}, Point{4_ft, 9_ft, 0_deg}}, "Center Low Flag Part 1");
    profile.setTarget("Center Low Flag Part 1");
    profile.waitUntilSettled();
    ballIntakeAut.setTarget(0);
    turn (left);
    joystickAut.setText(0, 0, "Reached line!");   /**********************************************************/
                                                  // !!!!!!!!!!!!!!!!! DEBUG LINE IS HERE !!!!!!!!!!!!!!!!! //
                                                  /*********************** To-Do List ***********************/
                                                  /*             moveTo vs. setTarget w/ struct             */
                                                  /*                   .executeSinglePath                   */
                                                  /*                       .getTarget                       */
                                                  /**********************************************************/

    profile.generatePath({Point{5_ft, 9_ft, 90_deg}, Point{5_ft, 10.4_ft, 90_deg}}, "Center Low Flag Part 2");
    profile.setTarget("Center Low Flag Part 2");
    profile.waitUntilSettled();
    driveAut.moveDistance(-1.4_ft);

    turn (right);

    ballIntakeAut.setTarget(-200);
    profile.generatePath({Point{5_ft, 9_ft, 0_deg}, Point{9_ft, 9_ft, 0_deg}}, "Evil Low Flag Part 1");
    profile.setTarget("Evil Low Flag Part 1");
    profile.waitUntilSettled();
    ballIntakeAut.setTarget(0);
    turn (left);
    profile.generatePath({Point{9_ft, 9_ft, 90_deg}, Point{9_ft, 10.4_ft, 90_deg}}, "Evil Low Flag Part 2");
    profile.setTarget("Evil Low Flag Part 2");
    profile.waitUntilSettled();
    driveAut.moveDistance(-1.4_ft);
    turn (right);

    profile.generatePath({Point{9_ft, 9_ft, 0_deg}, Point{10_ft, 9_ft, 0_deg}}, "King of the Hill Part 1");
    profile.setTarget("King of the Hill Part 1");
    profile.waitUntilSettled();
    turn (right);
    profile.generatePath({Point{10_ft, 9_ft, 270_deg}, Point{10_ft, 5_ft, 270_deg}}, "King of the Hill Part 2");
    profile.setTarget("King of the Hill Part 2");
    profile.waitUntilSettled();
    turn (right);
    driveAut.moveDistance(4.5_ft);
  }
}
