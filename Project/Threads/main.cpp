#include <stdio.h>
#include <thread>
#include <mutex>

int gInt = 0;
std::mutex gMutex;

void threadEnter(void* userdata)
{
    gInt = 1;
}

int main()
{
    std::thread Thread1(threadEnter, nullptr);

    gMutex.lock();
    {
        printf("%d\n", gInt);
    }
    gMutex.unlock();

    Thread1.join();

    return 0;
}