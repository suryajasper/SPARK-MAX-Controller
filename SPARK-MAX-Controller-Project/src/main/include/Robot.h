/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>

#include <frc/TimedRobot.h>
#include <rev/CANSparkMax.h>
#include <frc/smartdashboard/SendableChooser.h>

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;

  void moveForward(double speed);
  void moveBackward(double speed);
  void turnLeft(double rotSpeed);
  void turnRight(double rotSpeed);

  void stop();

  bool isMovingForward();
  bool isMovingBackward();
  bool isTurningLeft();
  bool isTurningRight();
  
 private:
  static const int leftLeadDeviceID = 1, leftFollowDeviceID = 2, rightLeadDeviceID = 3, rightFollowDeviceID = 4;

  rev::CANSparkMax* m_leftLeadMotor = new rev::CANSparkMax(leftLeadDeviceID, rev::CANSparkMax::MotorType::kBrushles);
  rev::CANSparkMax* m_rightLeadMotor = new rev::CANSparkMax(rightLeadDeviceID, rev::CANSparkMax::MotorType::kBrushless);
  rev::CANSparkMax* m_leftFollowMotor = new rev::CANSparkMax(leftFollowDeviceID, rev::CANSparkMax::MotorType::kBrushless);
  rev::CANSparkMax* m_rightFollowMotor = new rev::CANSparkMax(rightFollowDeviceID, rev::CANSparkMax::MotorType::kBrushless);

  rev::CANAnalog* m_leftAnalog = m_leftLeadMotor->GetAnalog();
  rev::CANAnalog* m_rightAnalog = m_rightLeadMotor->GetAnalog();

  std::vector<std::string> errors = {};
};
