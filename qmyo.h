#ifndef QMYO_H
#define QMYO_H

#include <QObject>
#include <QTimer>
#include "include/myo/myo.hpp"
#include "myodatacollector.h"
#include "qmyo_global.h"

class QMYOSHARED_EXPORT QMyo : public QObject
{
    Q_OBJECT
public:
    QMyo(std::string appName, QObject *parent = 0);
    void searchForMyo(int mili);
    void start();
    void stop();

    MyoDataCollector collector;

private slots:
    void hubCallback();

private:
    myo::Myo* myo;
    myo::Hub hub;
    QTimer hubEventTimer;

signals:
    void MyoFound();
};

#endif // QMYO_H
