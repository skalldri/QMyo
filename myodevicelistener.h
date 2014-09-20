#ifndef MYODEVICELISTENER_H
#define MYODEVICELISTENER_H

#include <QObject>
#include <QTimer>
#include "include/myo/myo.hpp"
#include "myodatacollector.h"
#include "constants.h"

class MyoDeviceListener : public QObject
{
    Q_OBJECT
public:
    explicit MyoDeviceListener(QObject *parent = 0);
    void searchForMyo(int mili);
    void start();
    void stop();

    MyoDataCollector collector;

signals:
    void MyoFound();

public slots:
    void hubCallback();

private:
    myo::Myo* myo;
    myo::Hub hub;
    QTimer hubEventTimer;

};

#endif // MYODEVICELISTENER_H
