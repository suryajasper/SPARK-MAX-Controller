/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>
#include <iostream>
#include <fstream>

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

  void writeToFile(string info);

  void move(int leftMotorOutput, int rightMotorOutput);
  void stop();
  
 private:
  static const int leftLeadDeviceID = 1, leftFollowDeviceID = 2, rightLeadDeviceID = 3, rightFollowDeviceID = 4;
  // the spark max motors
  rev::CANSparkMax* m_leftLeadMotor = new rev::CANSparkMax(leftLeadDeviceID, rev::CANSparkMax::MotorType::kBrushless);
  rev::CANSparkMax* m_rightLeadMotor = new rev::CANSparkMax(rightLeadDeviceID, rev::CANSparkMax::MotorType::kBrushless);
  rev::CANSparkMax* m_leftFollowMotor = new rev::CANSparkMax(leftFollowDeviceID, rev::CANSparkMax::MotorType::kBrushless);
  rev::CANSparkMax* m_rightFollowMotor = new rev::CANSparkMax(rightFollowDeviceID, rev::CANSparkMax::MotorType::kBrushless);

  // encoders to track velocity of each motor (positive or negative rpm)
  rev::CANEncoder m_leftEncoder = m_leftLeadMotor->GetEncoder();
  rev::CANEncoder m_rightEncoder = m_rightLeadMotor->GetEncoder();

  ofstream motorData; // used to write to the text file
  string filePath = "motorData.txt"; // link to text file that stores the match data
};
