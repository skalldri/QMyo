#include "myodevicelistener.h"

MyoDeviceListener::MyoDeviceListener(QObject *parent) :
    QObject(parent),
    myo(NULL),
    hub(APP_NAME),
    hubEventTimer(this)
{
    hub.addListener(&collector);
    // Make the timer run forever
    hubEventTimer.setSingleShot(false);
    hubEventTimer.setInterval(1000 / 20);
    QObject::connect(&hubEventTimer, SIGNAL(timeout()), this, SLOT(hubCallback()));
}

// Will start a search for a Myo that lasts the input number of miliseconds
void MyoDeviceListener::searchForMyo(int mili)
{
    myo = hub.waitForMyo(mili);

    if(myo != NULL)
    {
        qDebug("Found a Myo!");
        emit MyoFound();
    }
}

// Starts the Myo event loop
void MyoDeviceListener::start()
{
    hubEventTimer.start(1000 / 20);
}

// Stops the Myo event loop
void MyoDeviceListener::stop()
{
    hubEventTimer.stop();
}

// The function that runs the hub
void MyoDeviceListener::hubCallback()
{
    hub.run(5);
}
