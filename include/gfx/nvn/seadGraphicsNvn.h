#pragma once

#include <nn/gfx/gfx_Common.h>
#include <nvn/nvn.h>

#include "gfx/seadGraphics.h"
#include "prim/seadDelegate.h"
#include "thread/seadAtomic.h"
#include "thread/seadCriticalSection.h"

namespace sead
{
class DisplayBufferNvn;

class GraphicsNvn : public Graphics
{
public:
    struct CreateArg
    {
        NVNdevice* device;
        s32 _0x8;
        bool _0xc;
        bool _0xd;
    };

    GraphicsNvn(const CreateArg& arg);

    void initializeDrawLockContext(Heap* heap) override;
    void initializeImpl(Heap* heap) override;
    s32 getNewSamplerId();
    s32 getNewTextureId();
    void setDisplayBufferWindowCrop(s32, s32, s32, s32);
    void getDisplayBufferWindowCrop(s32*, s32*, s32*, s32*) const;
    void registerQueue(NVNqueue* queue);
    void registerDefaultCommandBuffer(NVNcommandBuffer* command_buffer);
    void registerDisplayBufferNvn(DisplayBufferNvn* display_buffer);
    void applyDeferredFinalizes();
    static void nvnDebugCallback(NVNdebugCallbackSource, NVNdebugCallbackType, s32,
                                 NVNdebugCallbackSeverity, const char*, void*);
    static nn::os::Tick convertGPUTimeStampToSystemTick(const NVNcounterData*);
    static u32 convertNvnDebugLevel(u32);
    void setViewportImpl(f32, f32, f32, f32) override;
    void setScissorImpl(f32, f32, f32, f32) override;
    void setDepthTestEnableImpl(bool) override;
    void setDepthWriteEnableImpl(bool) override;
    void setDepthFuncImpl(DepthFunc) override;
    bool setVBlankWaitIntervalImpl(u32) override;
    void setCullingModeImpl(CullingMode) override;
    void setBlendEnableImpl(bool) override;
    void setBlendEnableMRTImpl(u32, bool) override;
    void setBlendFactorImpl(BlendFactor, BlendFactor, BlendFactor, BlendFactor) override;
    void setBlendFactorMRTImpl(u32, BlendFactor, BlendFactor, BlendFactor, BlendFactor) override;
    void setBlendEquationImpl(BlendEquation, BlendEquation) override;
    void setBlendEquationMRTImpl(u32, BlendEquation, BlendEquation) override;
    void setBlendConstantColorImpl(const Color4f&) override;
    void waitForVBlankImpl() override;
    void setColorMaskImpl(bool, bool, bool, bool) override;
    void setColorMaskMRTImpl(u32, bool, bool, bool, bool) override;
    void setAlphaTestEnableImpl(bool) override;
    void setAlphaTestFuncImpl(AlphaFunc, f32) override;
    void setStencilTestEnableImpl(bool) override;
    void setStencilTestFuncImpl(StencilFunc, s32, u32) override;
    void setStencilTestOpImpl(StencilOp, StencilOp, StencilOp) override;
    void setPolygonModeImpl(PolygonMode, PolygonMode) override;
    void setPolygonOffsetEnableImpl(bool, bool, bool) override;

    NVNdevice* getNvnDevice() const { return mNvnDevice; }

    nn::gfx::detail::DeviceImpl<nn::gfx::ApiVariationNvn8>* getNnDevice() const
    {
        return mNnDevice;
    }

    NVNtexturePool* getTexturePool() { return &mNvnTexturePool; }

    s32 getTextureSamplerID() const { return mTextureSamplerID; }

    CriticalSection* getCriticalSection2() { return &mCriticalSection2; }

private:
    struct NvnDebugCallbackParam
    {
        NVNdebugCallbackSource source;
        NVNdebugCallbackType type;
        s32 id;
        NVNdebugCallbackSeverity severity;
        const char* message;
    };

    void defaultNvnDebugCallback_(const NvnDebugCallbackParam&);

    NVNdevice* mNvnDevice;
    NVNqueue* mQueue = nullptr;
    NVNcommandBuffer* mDefaultCommandBuffer = nullptr;
    nn::gfx::detail::DeviceImpl<nn::gfx::ApiVariationNvn8>* mNnDevice = nullptr;
    DisplayBufferNvn* mDisplayBuffer = nullptr;
    NVNtexturePool mNvnTexturePool;
    void* _0x78;
    void* _0x80;
    void* _0x88;
    void* _0x90;
    void* _0x98;
    void* _0xa0;
    void* _0xa8;
    void* _0xb0;
    void* _0xb8;
    void* _0xc0;
    void* _0xc8;
    void* _0xd0;
    void* _0xd8;
    void* _0xe0;
    void* _0xe8;
    void* _0xf0;
    s32 mTextureSamplerID = 0;
    u32 mVBlankWaitInterval = 0;
    void* _0x100;
    Atomic<u32> mNextSamplerId = 0;
    Atomic<u32> mNextTextureId = 0;
    s32 _0x110;
    s32 _0x114 = 0x1000;
    CriticalSection mCriticalSection1;
    CriticalSection mCriticalSection2;
    CriticalSection mCriticalSection3;
    Delegate1<GraphicsNvn, const NvnDebugCallbackParam&> mDefaultNvnDebugCallback{
        this, &GraphicsNvn::defaultNvnDebugCallback_};
    Delegate1<GraphicsNvn, const NvnDebugCallbackParam&>* mNvnDebugCallback =
        &mDefaultNvnDebugCallback;
    bool _0x200 = false;
    bool _0x201;
    bool _0x202;
};
static_assert(sizeof(GraphicsNvn) == 0x208);

}  // namespace sead
