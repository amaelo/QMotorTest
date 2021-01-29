#ifndef SIMULATOR_H
#define SIMULATOR_H

#define DBG_INDEX

#include <QObject>


class simulator : public QObject
{
    Q_OBJECT

public:
    simulator(int start, int stop);
    ~simulator();

    int Loop(int &val);
    void StopLoop();

public slots:
    void doLoop();

signals :
    void resultReady(const int &result);
    void loopAgain();

private:
    int index;
    int indexStart;
    int indexStop;
    int value;
    bool stopLoop;
};

#endif // SIMULATOR_H
