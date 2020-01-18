/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Robot.h>

using namespace std;

void Robot::RobotInit() {
  /**
   * The RestoreFactoryDefaults method can be used to reset the configuration parameters
   * in the SPARK MAX to their factory default state. If no argument is passed, these
   * parameters will not persist between power cycles
   */
  m_leftLeadMotor->RestoreFactoryDefaults();
  m_rightLeadMotor->RestoreFactoryDefaults();
  m_leftFollowMotor->RestoreFactoryDefaults();
  m_rightFollowMotor->RestoreFactoryDefaults();
  
  /**
   * In CAN mode, one SPARK MAX can be configured to follow another. This is done by calling
   * the Follow() method on the SPARK MAX you want to configure as a follower, and by passing
   * as a parameter the SPARK MAX you want to configure as a leader.
   * 
   * This is shown in the example below, where one motor on each side of our drive train is
   * configured to follow a lead motor.
   */
  m_leftFollowMotor->Follow(*m_leftLeadMotor);
  m_rightFollowMotor->Follow(*m_rightLeadMotor);
}

// overriding all functions of inherited class
void Robot::RobotPeriodic() {}
void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}
void Robot::TeleopInit() {}
void Robot::TestPeriodic() {}

/** Moves the robot by setting the velocity of the left and right motors
 *  velocity of the left and right motors are specified by the parameters
 *  Verifies that the robot is moving in the right direction and stores
 *  Successes and failures in a file
*/
void Robot::move(int leftOut, int rightOut) {

  m_leftLeadMotor->Set(leftOut);
  m_rightLeadMotor->Set(rightOut);

  double leftDir = m_leftEncoder.GetVelocity();
  double rightDir = m_rightEncoder.GetVelocity();

  string output = "SUCCESS";
  string stats = " lSet: " + std::to_string(leftOut ) + 
                 " rSet: " + std::to_string(rightOut) +
                 " lAct: " + std::to_string(leftDir ) + 
                 " rAct: " + std::to_string(rightDir);

  if (leftOut > rightOut && leftDir < rightDir)
    output = ("right FAIL");
  
  if (leftOut < rightOut && leftDir > rightDir)
    output = ("left FAIL");
  
  if (leftOut == rightOut && leftDir != rightDir) {
    if (leftOut < 0)
      output = ("back FAIL");
    else
      output = ("forward FAIL");
  }

  writeToFile(output + stats);

}

void Robot::stop() {
  m_leftLeadMotor->StopMotor();
  m_rightLeadMotor->StopMotor();
}

/** Takes a string as a parameter and writes it 
 * to the file where the match data is stored
*/
void Robot::writeToFile(string info) {
  motorData.open(filePath);

  if (motorData.is_open)
    motorData << info + "\n";

  motorData.close();
}

void Robot::TeleopPeriodic() {

  // testing forward motion
  move(1, 1);
  stop();

  // testing backward motion
  move(-1, -1);
  stop();

  // testing left turns
  move(-1, 1);
  stop();

  // testing right turns
  move(1, -1);
  stop();

}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
