#pragma once
#include "../main.h"

#define RED 1
#define BLUE 0

#define FWD 0
#define BWD 1

#define ARCADE 1
#define TANK 0

#define ONLINE 1

extern ControllerButton btnShoot;
extern ControllerButton btnBallIntake;
extern ControllerButton btnReverseBallSystem;
extern ControllerButton btnDoubleShot;

extern ControllerButton btnLUsager;

extern ControllerButton btnLazyMode;
extern ControllerButton btnDriveStyle;

extern ChassisControllerIntegrated drive;
extern MotorGroup driveL;
extern MotorGroup driveR;

extern ChassisControllerIntegrated aut;
extern AsyncMotionProfileController profile;

extern Motor ballIntake;
extern Motor ballIndexer;
extern Motor flywheel;
extern Motor l;

extern bool ballIntakeToggle;
extern bool driveStyleToggle;
extern bool doubleShot;
extern bool lUsage;
extern bool lazy;

// Opertion Control Functions //
void lControl          ();
void ballControl       ();
void doubleShotControl ();

void lazyMode ();

void doArcade ();
void doTank   ();
void driveStyle();


// Autonomous Functions //
extern const bool right;
extern const bool left;

void shoot ();
void turn (bool direction);
