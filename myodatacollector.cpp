#include "myodatacollector.h"

MyoDataCollector::MyoDataCollector()
{
}

// onOrientationData() is called whenever the Myo device provides its current orientation, which is represented
// as a unit quaternion.
void MyoDataCollector::onOrientationData(myo::Myo* myo, uint64_t timestamp, const myo::Quaternion<float>& quat)
{
    emit OrientationData(myo, timestamp, quat);

    using std::atan2;
    using std::asin;
    using std::sqrt;
    // Calculate Euler angles (roll, pitch, and yaw) from the unit quaternion.
    float roll = atan2(2.0f * (quat.w() * quat.x() + quat.y() * quat.z()),
                       1.0f - 2.0f * (quat.x() * quat.x() + quat.y() * quat.y()));
    float pitch = asin(2.0f * (quat.w() * quat.y() - quat.z() * quat.x()));
    float yaw = atan2(2.0f * (quat.w() * quat.z() + quat.x() * quat.y()),
                    1.0f - 2.0f * (quat.y() * quat.y() + quat.z() * quat.z()));
    // Convert the floating point angles in radians to a scale from 0 to 20.
    roll_w = static_cast<int>((roll + (float)M_PI)/(M_PI * 2.0f) * 18);
    pitch_w = static_cast<int>((pitch + (float)M_PI/2.0f)/M_PI * 18);
    yaw_w = static_cast<int>((yaw + (float)M_PI)/(M_PI * 2.0f) * 18);
}

void MyoDataCollector::onAccelerometerData(myo::Myo *myo, uint64_t timestamp, const myo::Vector3< float > &accel)
{
    emit AccelerometerData(myo, timestamp, accel);
}

void MyoDataCollector::onGyroscopeData(myo::Myo *myo, uint64_t timestamp, const myo::Vector3< float > &gyro)
{
    emit GyroscopeData(myo, timestamp, gyro);
}

void MyoDataCollector::onRssi(myo::Myo *myo, uint64_t timestamp, int8_t rssi)
{
    emit Rssi(myo, timestamp, rssi);
}

// onPose() is called whenever the Myo detects that the person wearing it has changed their pose, for example,
// making a fist, or not making a fist anymore.
void MyoDataCollector::onPose(myo::Myo* myo, uint64_t timestamp, myo::Pose pose)
{
    qDebug(pose.toString().c_str());
    emit Pose(myo, timestamp, pose);

    currentPose = pose;
    // Vibrate the Myo whenever we've detected that the user has made a fist.
    if (pose == myo::Pose::fist) {
        myo->vibrate(myo::Myo::vibrationMedium);
    }
}

// onArmRecognized() is called whenever Myo has recognized a setup gesture after someone has put it on their
// arm. This lets Myo know which arm it's on and which way it's facing.
void MyoDataCollector::onArmRecognized(myo::Myo* myo, uint64_t timestamp, myo::Arm arm, myo::XDirection xDirection)
{
    emit ArmRecognized(myo, timestamp, arm, xDirection);
    onArm = true;
    whichArm = arm;
}

// onArmLost() is called whenever Myo has detected that it was moved from a stable position on a person's arm after
// it recognized the arm. Typically this happens when someone takes Myo off of their arm, but it can also happen
// when Myo is moved around on the arm.
void MyoDataCollector::onArmLost(myo::Myo* myo, uint64_t timestamp)
{
    emit ArmLost(myo, timestamp);
    onArm = false;
}

void MyoDataCollector::onConnect(myo::Myo* myo, uint64_t timestamp, myo::FirmwareVersion firmwareVersion)
{
    emit Connect(myo, timestamp, firmwareVersion);
}

void MyoDataCollector::onDisconnect(myo::Myo* myo, uint64_t timestamp)
{
    emit Disconnect(myo, timestamp);
}
