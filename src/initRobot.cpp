#include "../header files/initRobot"

Motor ballIntake  (4, true,  AbstractMotor::gearset::blue );
Motor ballIndexer (5, false, AbstractMotor::gearset::green);
Motor flywheel    (6, false, AbstractMotor::gearset::green);
Motor l           (7, true,  AbstractMotor::gearset::green);

ChassisControllerIntegrated drive = ChassisControllerFactory::create
(
   {1, -2},
   {-10, 9},
   AbstractMotor::gearset::green,
   {4_in, 9.78_in}
);

MotorGroup driveL = MotorGroup({1, -2});
MotorGroup driveR = MotorGroup({9, -10});
