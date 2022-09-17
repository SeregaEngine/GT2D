#ifndef GTTASK_H_
#define GTTASK_H_

// Tasks send commands to Actors
class GT_Task
{
public:
    virtual void Handle() = 0;
};

#endif // GTTASK_H_