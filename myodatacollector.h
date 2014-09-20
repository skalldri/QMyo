#ifndef MYODATACOLLECTOR_H
#define MYODATACOLLECTOR_H

#define _USE_MATH_DEFINES
#include <cmath>
#include <QObject>
#include "include/myo/myo.hpp"

class MyoDataCollector : public QObject, public myo::DeviceListener
{
    Q_OBJECT
public:
    MyoDataCollector();
    void onOrientationData(myo::Myo* myo, uint64_t timestamp, const myo::Quaternion<float>& quat);
    void onAccelerometerData(myo::Myo *myo, uint64_t timestamp, const myo::Vector3< float > &accel);
    void onGyroscopeData(myo::Myo *myo, uint64_t timestamp, const myo::Vector3< float > &gyro);
    void onRssi(myo::Myo *myo, uint64_t timestamp, int8_t rssi);
    void onPose(myo::Myo* myo, uint64_t timestamp, myo::Pose pose);
    void onArmRecognized(myo::Myo* myo, uint64_t timestamp, myo::Arm arm, myo::XDirection xDirection);
    void onArmLost(myo::Myo* myo, uint64_t timestamp);
    void onConnect(myo::Myo* myo, uint64_t timestamp, myo::FirmwareVersion firmwareVersion);
    void onDisconnect(myo::Myo* myo, uint64_t timestamp);

private:
    // These values are set by onArmRecognized() and onArmLost() above.
    bool onArm;
    myo::Arm whichArm;
    // These values are set by onOrientationData() and onPose() above.
    int roll_w, pitch_w, yaw_w;
    myo::Pose currentPose;

signals:
    void Connect(myo::Myo* myo, uint64_t timestamp, myo::FirmwareVersion firmwareVersion);
    void Disconnect(myo::Myo* myo, uint64_t timestamp);
    void OrientationData(myo::Myo*, uint64_t, const myo::Quaternion<float> quat);
    void AccelerometerData(myo::Myo *myo, uint64_t timestamp, const myo::Vector3< float > accel);
    void GyroscopeData(myo::Myo *myo, uint64_t timestamp, const myo::Vector3< float > gyro);
    void Rssi(myo::Myo *myo, uint64_t timestamp, int8_t rssi);
    void Pose(myo::Myo* myo, uint64_t timestamp, myo::Pose pose);
    void ArmRecognized(myo::Myo* myo, uint64_t timestamp, myo::Arm arm, myo::XDirection xDirection);
    void ArmLost(myo::Myo* myo, uint64_t timestamp);

};

#endif // MYODATACOLLECTOR_H
