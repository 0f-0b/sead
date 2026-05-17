#include "gfx/nvn/seadGraphicsNvn.h"

#include <nvn/nvn_FuncPtrInline.h>
#include "gfx/nvn/seadFrameBufferNvn.h"

namespace nn::os
{
Tick ConvertToTick(TimeSpan time_span);
}

namespace sead
{

GraphicsNvn::GraphicsNvn(const CreateArg& arg)
    : mNvnDevice(arg.device), _0x110(arg._0x8), _0x201(arg._0xc), _0x202(arg._0xd)
{
    nvnDeviceSetWindowOriginMode(mNvnDevice, NVN_WINDOW_ORIGIN_MODE_UPPER_LEFT);
}

void GraphicsNvn::defaultNvnDebugCallback_(const NvnDebugCallbackParam&) {}

void GraphicsNvn::initializeDrawLockContext(Heap* heap)
{
    Graphics::initializeDrawLockContext(heap);
}

s32 GraphicsNvn::getNewSamplerId()
{
    return mNextSamplerId.increment();
}

s32 GraphicsNvn::getNewTextureId()
{
    return mNextTextureId.increment();
}

void GraphicsNvn::setDisplayBufferWindowCrop(s32 _w1, s32 _w2, s32 _w3, s32 _w4)
{
    mDisplayBuffer->setWindowCrop(_w1, _w2, _w3, _w4);
}

void GraphicsNvn::getDisplayBufferWindowCrop(s32* _x1, s32* _x2, s32* _x3, s32* _x4) const
{
    mDisplayBuffer->getWindowCrop(_x1, _x2, _x3, _x4);
}

void GraphicsNvn::registerQueue(NVNqueue* queue)
{
    mQueue = queue;
}

void GraphicsNvn::registerDefaultCommandBuffer(NVNcommandBuffer* command_buffer)
{
    mDefaultCommandBuffer = command_buffer;
}

void GraphicsNvn::registerDisplayBufferNvn(DisplayBufferNvn* display_buffer)
{
    mDisplayBuffer = display_buffer;
}

void GraphicsNvn::applyDeferredFinalizes()
{
    if (_0x201)
        nvnDeviceApplyDeferredFinalizes(mNvnDevice, 5);
}

void GraphicsNvn::nvnDebugCallback(NVNdebugCallbackSource source, NVNdebugCallbackType type, s32 id,
                                   NVNdebugCallbackSeverity severity, const char* message, void*)
{
    if (GraphicsNvn* graphics = static_cast<GraphicsNvn*>(instance()))
    {
        NvnDebugCallbackParam param = {source, type, id, severity, message};
        if (graphics->mNvnDebugCallback)
            graphics->mNvnDebugCallback->invoke(param);
    }
}

nn::os::Tick GraphicsNvn::convertGPUTimeStampToSystemTick(const NVNcounterData* counter_data)
{
    NVNdevice* device = static_cast<GraphicsNvn*>(instance())->mNvnDevice;
    u64 nanoseconds = nvnDeviceGetTimestampInNanoseconds(device, counter_data);
    return nn::os::ConvertToTick(nn::TimeSpan::FromNanoSeconds(nanoseconds));
}

u32 GraphicsNvn::convertNvnDebugLevel(u32 debug_level)
{
    switch (debug_level)
    {
    case 0:
        return 32;
    case 1:
        return 64;
    case 2:
        return 1;
    case 3:
        return 4;
    case 4:
        return 1;
    default:
        return 32;
    }
}

void GraphicsNvn::setViewportImpl(f32, f32, f32, f32) {}

void GraphicsNvn::setScissorImpl(f32, f32, f32, f32) {}

void GraphicsNvn::setDepthTestEnableImpl(bool) {}

void GraphicsNvn::setDepthWriteEnableImpl(bool) {}

void GraphicsNvn::setDepthFuncImpl(DepthFunc) {}

bool GraphicsNvn::setVBlankWaitIntervalImpl(u32 interval)
{
    mVBlankWaitInterval = interval;
    return true;
}

void GraphicsNvn::setCullingModeImpl(CullingMode) {}

void GraphicsNvn::setBlendEnableImpl(bool) {}

void GraphicsNvn::setBlendEnableMRTImpl(u32, bool) {}

void GraphicsNvn::setBlendFactorImpl(BlendFactor, BlendFactor, BlendFactor, BlendFactor) {}

void GraphicsNvn::setBlendFactorMRTImpl(u32, BlendFactor, BlendFactor, BlendFactor, BlendFactor) {}

void GraphicsNvn::setBlendEquationImpl(BlendEquation, BlendEquation) {}

void GraphicsNvn::setBlendEquationMRTImpl(u32, BlendEquation, BlendEquation) {}

void GraphicsNvn::setBlendConstantColorImpl(const Color4f&) {}

void GraphicsNvn::waitForVBlankImpl() {}

void GraphicsNvn::setColorMaskImpl(bool, bool, bool, bool) {}

void GraphicsNvn::setColorMaskMRTImpl(u32, bool, bool, bool, bool) {}

void GraphicsNvn::setAlphaTestEnableImpl(bool) {}

void GraphicsNvn::setAlphaTestFuncImpl(AlphaFunc, f32) {}

void GraphicsNvn::setStencilTestEnableImpl(bool) {}

void GraphicsNvn::setStencilTestFuncImpl(StencilFunc, s32, u32) {}

void GraphicsNvn::setStencilTestOpImpl(StencilOp, StencilOp, StencilOp) {}

void GraphicsNvn::setPolygonModeImpl(PolygonMode, PolygonMode) {}

void GraphicsNvn::setPolygonOffsetEnableImpl(bool, bool, bool) {}

}  // namespace sead
