#include "simulator.h"

#include <QDebug>
#include <QThread>

simulator::simulator(int start, int stop)
{
    indexStart = start;
    index = indexStart;
    indexStop = stop;
    qDebug() << "simulator created : from " << start << " to " << stop;

    connect(this, &simulator::loopAgain, this, &simulator::doLoop);
    index = 0;
//    doLoop();
}

simulator::~simulator()
{
    qInfo() << "Simulator deleted";
}


int simulator::Loop(int &val)
{
#ifdef DBG_INDEX
    qDebug() << "Index : " << val;
#endif

    if (index < 100000) { return Loop(++val); }
    else { return 0; }
}


void simulator::doLoop()
{
    stopLoop = false;

    while (!stopLoop)
    {
        QThread::currentThread()->msleep(20);
        emit resultReady(++index);
#ifdef DBG_INDEX
//        qDebug() << "Index : " << ++index;
#endif
    }
}


void simulator::StopLoop()
{
    stopLoop = true;
}




