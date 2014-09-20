QMyo
====

A Qt Library that turns enables signal and slot connections to the Myo API.

Usage
=====

Build the library using Qt Creator. All the files needed to compile (the Myo library and header files) are included in this Github.

Next, include the header files in your project and link against the library.

To use the library, instantiate a QMyo. Then call ```searchForMyo()``` on the new object to try and find a Myo to connect to. Finally, call ```start()``` on the instance of QMyo to start the event loop that will generate Myo signals.

To register for signals, you connec to connect to QMyo.collector. For example, to register for signals when a Myo is connected, use the following code snippet:

```
QMyo myo("com.some.app.name");
QObject::connect(&myo.collector, SIGNAL(Connect(myo::Myo*, uint64_t, myo::FirmwareVersion)), this, SLOT(onMyoConnect(myo::Myo*, uint64_t, myo::FirmwareVersion)));
```

The signals are designed to mimic the Myo API as closely as possible.
