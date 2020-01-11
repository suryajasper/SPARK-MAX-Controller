/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <frc/TimedRobot.h>
#include "rev/CANSparkMax.h"

using namespace std;

class Robot : public frc::TimedRobot {
  /**
   * SPARK MAX controllers are intialized over CAN by constructing a CANSparkMax object
   * 
   * The CAN ID, which can be configured using the SPARK MAX Client, is passed as the
   * first parameter
   * 
   * The motor type is passed as the second parameter. Motor type can either be:
   *  rev::CANSparkMax::MotorType::kBrushless
   *  rev::CANSparkMax::MotorType::kBrushed
   * 
   * The example below initializes four brushless motors with CAN IDs 1, 2, 3 and 4. Change
   * these parameters to match your setup
   */
  static const int leftLeadDeviceID = 1, leftFollowDeviceID = 2, rightLeadDeviceID = 3, rightFollowDeviceID = 4;
  
  rev::CANSparkMax m_leftLeadMotor{leftLeadDeviceID, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax m_rightLeadMotor{rightLeadDeviceID, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax m_leftFollowMotor{leftFollowDeviceID, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax m_rightFollowMotor{rightFollowDeviceID, rev::CANSparkMax::MotorType::kBrushless};

  rev::CANAnalog m_leftAnalog = m_leftLeadMotor.GetAnalog();
  rev::CANAnalog m_rightAnalog = m_rightLeadMotor.GetAnalog();

  std::vector<std::string> errors = {};
  
 public:
  void RobotInit() {
    /**
     * The RestoreFactoryDefaults method can be used to reset the configuration parameters
     * in the SPARK MAX to their factory default state. If no argument is passed, these
     * parameters will not persist between power cycles
     */
    m_leftLeadMotor.RestoreFactoryDefaults();
    m_rightLeadMotor.RestoreFactoryDefaults();
    m_leftFollowMotor.RestoreFactoryDefaults();
    m_rightFollowMotor.RestoreFactoryDefaults();
    
    /**
     * In CAN mode, one SPARK MAX can be configured to follow another. This is done by calling
     * the Follow() method on the SPARK MAX you want to configure as a follower, and by passing
     * as a parameter the SPARK MAX you want to configure as a leader.
     * 
     * This is shown in the example below, where one motor on each side of our drive train is
     * configured to follow a lead motor.
     */
    m_leftFollowMotor.Follow(m_leftLeadMotor);
    m_rightFollowMotor.Follow(m_rightLeadMotor);
  }

  void moveForward(double speed) {
    m_leftLeadMotor.Set(speed);
    m_rightLeadMotor.Set(speed);
  }

  void moveBackward(double speed) {
    m_leftLeadMotor.Set(-speed);
    m_rightLeadMotor.Set(-speed);
  }

  void turnLeft(double rotSpeed) {
    m_leftLeadMotor.Set(-rotSpeed);
    m_rightLeadMotor.Set(rotSpeed);
  }

  void turnRight(double rotSpeed) {
    m_leftLeadMotor.Set(rotSpeed);
    m_rightLeadMotor.Set(-rotSpeed);
  }
  
  void stop() {
    m_leftLeadMotor.StopMotor();
    m_rightLeadMotor.StopMotor();
  }

  bool isMovingForward() {
    bool posVoltage = m_leftAnalog.GetVoltage() > 0 && 
                      m_rightAnalog.GetVoltage() > 0;

    return posVoltage;
  }

  bool isMovingBackward() {
    bool negVoltage = m_leftAnalog.GetVoltage() < 0 && 
                      m_rightAnalog.GetVoltage() < 0;

    return negVoltage;
  }

  bool isTurningLeft() {
    double leftVoltage = m_leftAnalog.GetVoltage();
    double rightVoltage = m_rightAnalog.GetVoltage();
    
    bool leftTurn = (leftVoltage < 0 && rightVoltage > 0);
    return leftTurn;
  }

  bool isTurningRight() {
    double leftVoltage = m_leftAnalog.GetVoltage();
    double rightVoltage = m_rightAnalog.GetVoltage();

    bool rightTurn = (leftVoltage > 0 && rightVoltage < 0);
    return rightTurn;
  }

  void TeleopPeriodic() {

    // testing forward motion
    moveForward(1);
    if (!isMovingForward())
      errors.push_back("Forward test failed");
    stop();

    // testing backward motion
    moveBackward(1);
    if (!isMovingBackward())
      errors.push_back("Backward test failed");
    stop();

    // testing left turns
    turnLeft(1);
    if (!isTurningLeft())
      errors.push_back("Left turn test failed");
    stop();

    // testing right turns
    turnRight(1);
    if (!isTurningRight())
      errors.push_back("Right turn test failed");
    stop();

  }
};

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
