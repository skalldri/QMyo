#include "qmyo.h"

QMyo::QMyo(std::string name, QObject *parent) :
    QObject(parent),
    myo(NULL),
    hub(name),
    hubEventTimer(this)
{
    hub.addListener(&collector);
    // Make the timer run forever
    hubEventTimer.setSingleShot(false);
    hubEventTimer.setInterval(1000 / 20);
    QObject::connect(&hubEventTimer, SIGNAL(timeout()), this, SLOT(hubCallback()));
}

// Will start a search for a Myo that lasts the input number of miliseconds
void QMyo::searchForMyo(int mili)
{
    myo = hub.waitForMyo(mili);

    if(myo != NULL)
    {
        qDebug("Found a Myo!");
        emit MyoFound();
    }
}

// Starts the Myo event loop
void QMyo::start()
{
    hubEventTimer.start(1000 / 20);
}

// Stops the Myo event loop
void QMyo::stop()
{
    hubEventTimer.stop();
}

// The function that runs the hub
void QMyo::hubCallback()
{
    hub.run(5);
}
