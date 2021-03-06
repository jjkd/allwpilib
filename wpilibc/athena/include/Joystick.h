/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008-2016. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <stdint.h>

#include <memory>
#include <string>
#include <vector>

#include "ErrorBase.h"
#include "GenericHID.h"

class DriverStation;

/**
 * Handle input from standard Joysticks connected to the Driver Station.
 * This class handles standard input that comes from the Driver Station. Each
 * time a value is requested the most recent value is returned. There is a
 * single class instance for each joystick and the mapping of ports to hardware
 * buttons depends on the code in the driver station.
 */
class Joystick : public GenericHID, public ErrorBase {
 public:
  static const int kDefaultXAxis = 0;
  static const int kDefaultYAxis = 1;
  static const int kDefaultZAxis = 2;
  static const int kDefaultTwistAxis = 2;
  static const int kDefaultThrottleAxis = 3;
  typedef enum {
    kXAxis,
    kYAxis,
    kZAxis,
    kTwistAxis,
    kThrottleAxis,
    kNumAxisTypes
  } AxisType;
  static const int kDefaultTriggerButton = 1;
  static const int kDefaultTopButton = 2;
  typedef enum { kTriggerButton, kTopButton, kNumButtonTypes } ButtonType;
  typedef enum { kLeftRumble, kRightRumble } RumbleType;
  typedef enum {
    kUnknown = -1,
    kXInputUnknown = 0,
    kXInputGamepad = 1,
    kXInputWheel = 2,
    kXInputArcadeStick = 3,
    kXInputFlightStick = 4,
    kXInputDancePad = 5,
    kXInputGuitar = 6,
    kXInputGuitar2 = 7,
    kXInputDrumKit = 8,
    kXInputGuitar3 = 11,
    kXInputArcadePad = 19,
    kHIDJoystick = 20,
    kHIDGamepad = 21,
    kHIDDriving = 22,
    kHIDFlight = 23,
    kHID1stPerson = 24
  } HIDType;
  explicit Joystick(int port);
  Joystick(int port, int numAxisTypes, int numButtonTypes);
  virtual ~Joystick() = default;

  Joystick(const Joystick&) = delete;
  Joystick& operator=(const Joystick&) = delete;

  int GetAxisChannel(AxisType axis) const;
  void SetAxisChannel(AxisType axis, int channel);

  float GetX(JoystickHand hand = kRightHand) const override;
  float GetY(JoystickHand hand = kRightHand) const override;
  float GetZ() const override;
  float GetTwist() const override;
  float GetThrottle() const override;
  virtual float GetAxis(AxisType axis) const;
  float GetRawAxis(int axis) const override;

  bool GetTrigger(JoystickHand hand = kRightHand) const override;
  bool GetTop(JoystickHand hand = kRightHand) const override;
  bool GetBumper(JoystickHand hand = kRightHand) const override;
  bool GetRawButton(int button) const override;
  int GetPOV(int pov = 0) const override;
  bool GetButton(ButtonType button) const;
  static Joystick* GetStickForPort(int port);

  virtual float GetMagnitude() const;
  virtual float GetDirectionRadians() const;
  virtual float GetDirectionDegrees() const;

  bool GetIsXbox() const;
  Joystick::HIDType GetType() const;
  std::string GetName() const;
  int GetPort() const;
  int GetAxisType(int axis) const;

  int GetAxisCount() const;
  int GetButtonCount() const;
  int GetPOVCount() const;

  void SetRumble(RumbleType type, float value);
  void SetOutput(int outputNumber, bool value);
  void SetOutputs(int value);

 private:
  DriverStation& m_ds;
  int m_port;
  std::vector<int> m_axes;
  std::vector<int> m_buttons;
  int m_outputs = 0;
  uint16_t m_leftRumble = 0;
  uint16_t m_rightRumble = 0;
};
