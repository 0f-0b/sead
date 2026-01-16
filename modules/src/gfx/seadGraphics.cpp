#include "gfx/seadGraphics.h"

namespace sead
{

Graphics::DevicePosture Graphics::sDefaultDevicePosture = cDevicePosture_Same;
f32 Graphics::sDefaultDeviceZScale = 1;
f32 Graphics::sDefaultDeviceZOffset = 0;
Graphics* Graphics::sInstance = nullptr;

Graphics::Graphics() = default;

Graphics::~Graphics() = default;

void Graphics::initialize(Heap* heap)
{
    mDrawLockContext = new (heap) DrawLockContext;
    initializeDrawLockContext(heap);
    mDrawLockContext->lock();
    initializeImpl(heap);
    mDrawLockContext->unlock();
}

void Graphics::lockDrawContext()
{
    if (_0x20)
        _0x20(true);
    else
        mDrawLockContext->lock();
}

void Graphics::unlockDrawContext()
{
    if (_0x20)
        _0x20(false);
    else
        mDrawLockContext->unlock();
}

void Graphics::initHostIO() {}

void Graphics::initializeDrawLockContext(Heap* heap)
{
    mDrawLockContext->initialize(heap);
}

}  // namespace sead
