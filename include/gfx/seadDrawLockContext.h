#pragma once

#include "hostio/seadHostIONode.h"
#include "thread/seadCriticalSection.h"

namespace sead
{

class DrawLockContext : public hostio::Node
{
public:
    DrawLockContext();

    void initialize(Heap* heap);
    void lock();
    void unlock();
    void genMessage(hostio::Context* context);

private:
    u32 _8 = 0;
    CriticalSection mCriticalSection{};
    void* _padding[0x2];
};

static_assert(sizeof(DrawLockContext) == 0x60);

}  // namespace sead
