#pragma once

#include <nvn/nvn.h>
#include "gfx/seadColor.h"
#include "gfx/seadDrawLockContext.h"
#include "heap/seadDisposer.h"

namespace sead
{

class Graphics : public IDisposer
{
public:
    enum PolygonMode
    {
        cPolygonMode_Point = NVN_POLYGON_MODE_POINT,
        cPolygonMode_Line = NVN_POLYGON_MODE_LINE,
        cPolygonMode_Fill = NVN_POLYGON_MODE_FILL,
    };

    enum CullingMode
    {
        cCullingMode_None = NVN_FACE_NONE,
        cCullingMode_Front = NVN_FACE_FRONT,
        cCullingMode_Back = NVN_FACE_BACK,
        cCullingMode_FrontAndBack = NVN_FACE_FRONT_AND_BACK,
    };

    enum AlphaFunc
    {
        cAlphaFunc_Never = NVN_ALPHA_FUNC_NEVER,
        cAlphaFunc_Less = NVN_ALPHA_FUNC_LESS,
        cAlphaFunc_Equal = NVN_ALPHA_FUNC_EQUAL,
        cAlphaFunc_LessEqual = NVN_ALPHA_FUNC_LEQUAL,
        cAlphaFunc_Greater = NVN_ALPHA_FUNC_GREATER,
        cAlphaFunc_NotEqual = NVN_ALPHA_FUNC_NOTEQUAL,
        cAlphaFunc_GreaterEqual = NVN_ALPHA_FUNC_GEQUAL,
        cAlphaFunc_Always = NVN_ALPHA_FUNC_ALWAYS,
    };

    enum DepthFunc
    {
        cDepthFunc_Never = NVN_DEPTH_FUNC_NEVER,
        cDepthFunc_Less = NVN_DEPTH_FUNC_LESS,
        cDepthFunc_Equal = NVN_DEPTH_FUNC_EQUAL,
        cDepthFunc_LessEqual = NVN_DEPTH_FUNC_LEQUAL,
        cDepthFunc_Greater = NVN_DEPTH_FUNC_GREATER,
        cDepthFunc_NotEqual = NVN_DEPTH_FUNC_NOTEQUAL,
        cDepthFunc_GreaterEqual = NVN_DEPTH_FUNC_GEQUAL,
        cDepthFunc_Always = NVN_DEPTH_FUNC_ALWAYS,
    };

    enum StencilFunc
    {
        cStencilFunc_Never = NVN_STENCIL_FUNC_NEVER,
        cStencilFunc_Less = NVN_STENCIL_FUNC_LESS,
        cStencilFunc_Equal = NVN_STENCIL_FUNC_EQUAL,
        cStencilFunc_LessEqual = NVN_STENCIL_FUNC_LEQUAL,
        cStencilFunc_Greater = NVN_STENCIL_FUNC_GREATER,
        cStencilFunc_NotEqual = NVN_STENCIL_FUNC_NOTEQUAL,
        cStencilFunc_GreaterEqual = NVN_STENCIL_FUNC_GEQUAL,
        cStencilFunc_Always = NVN_STENCIL_FUNC_ALWAYS,
    };

    enum StencilOp
    {
        cStencilOp_Keep = NVN_STENCIL_OP_KEEP,
        cStencilOp_Zero = NVN_STENCIL_OP_ZERO,
        cStencilOp_Replace = NVN_STENCIL_OP_REPLACE,
        cStencilOp_Increment = NVN_STENCIL_OP_INCR,
        cStencilOp_Decrement = NVN_STENCIL_OP_DECR,
        cStencilOp_Invert = NVN_STENCIL_OP_INVERT,
        cStencilOp_IncrementWrap = NVN_STENCIL_OP_INCR_WRAP,
        cStencilOp_DecrementWrap = NVN_STENCIL_OP_DECR_WRAP,
    };

    enum BlendEquation
    {
        cBlendEquation_Add = NVN_BLEND_EQUATION_ADD,
        cBlendEquation_Subtract = NVN_BLEND_EQUATION_SUB,
        cBlendEquation_ReverseSubtract = NVN_BLEND_EQUATION_REVERSE_SUB,
        cBlendEquation_Min = NVN_BLEND_EQUATION_MIN,
        cBlendEquation_Max = NVN_BLEND_EQUATION_MAX,
    };

    enum BlendFactor
    {
        cBlendFactor_Zero = NVN_BLEND_FUNC_ZERO,
        cBlendFactor_One = NVN_BLEND_FUNC_ONE,
        cBlendFactor_SrcColor = NVN_BLEND_FUNC_SRC_COLOR,
        cBlendFactor_OneMinusSrcColor = NVN_BLEND_FUNC_ONE_MINUS_SRC_COLOR,
        cBlendFactor_SrcAlpha = NVN_BLEND_FUNC_SRC_ALPHA,
        cBlendFactor_OneMinusSrcAlpha = NVN_BLEND_FUNC_ONE_MINUS_SRC_ALPHA,
        cBlendFactor_DstAlpha = NVN_BLEND_FUNC_DST_ALPHA,
        cBlendFactor_OneMinusDstAlpha = NVN_BLEND_FUNC_ONE_MINUS_DST_ALPHA,
        cBlendFactor_DstColor = NVN_BLEND_FUNC_DST_COLOR,
        cBlendFactor_OneMinusDstColor = NVN_BLEND_FUNC_ONE_MINUS_DST_COLOR,
        cBlendFactor_SrcAlphaSaturate = NVN_BLEND_FUNC_SRC_ALPHA_SATURATE,
        cBlendFactor_Src1Color = NVN_BLEND_FUNC_SRC1_COLOR,
        cBlendFactor_OneMinusSrc1Color = NVN_BLEND_FUNC_ONE_MINUS_SRC1_COLOR,
        cBlendFactor_Src1Alpha = NVN_BLEND_FUNC_SRC1_ALPHA,
        cBlendFactor_OneMinusSrc1Alpha = NVN_BLEND_FUNC_ONE_MINUS_SRC1_ALPHA,
        cBlendFactor_ConstantColor = NVN_BLEND_FUNC_CONSTANT_COLOR,
        cBlendFactor_OneMinusConstantColor = NVN_BLEND_FUNC_ONE_MINUS_CONSTANT_COLOR,
        cBlendFactor_ConstantAlpha = NVN_BLEND_FUNC_CONSTANT_ALPHA,
        cBlendFactor_OneMinusConstantAlpha = NVN_BLEND_FUNC_ONE_MINUS_CONSTANT_ALPHA,
    };

    enum DevicePosture
    {
        cDevicePosture_Same = 0,
        cDevicePosture_RotateRight = 1,
        cDevicePosture_RotateLeft = 2,
        cDevicePosture_RotateHalfAround = 3,
        cDevicePosture_FlipX = 4,
        cDevicePosture_FlipY = 5,
        cDevicePosture_FlipXY = 3,
        cDevicePosture_Invalid = 4,
    };

    Graphics();
    ~Graphics() override;

    void initialize(Heap* heap);
    void lockDrawContext();
    void unlockDrawContext();
    void initHostIO();
    virtual void initializeDrawLockContext(Heap* heap);
    virtual void initializeImpl(Heap* heap) = 0;
    virtual void setViewportImpl(f32, f32, f32, f32) = 0;
    virtual void setScissorImpl(f32, f32, f32, f32) = 0;
    virtual void setDepthTestEnableImpl(bool) = 0;
    virtual void setDepthWriteEnableImpl(bool) = 0;
    virtual void setDepthFuncImpl(DepthFunc) = 0;
    virtual bool setVBlankWaitIntervalImpl(u32) = 0;
    virtual void setCullingModeImpl(CullingMode) = 0;
    virtual void setBlendEnableImpl(bool) = 0;
    virtual void setBlendEnableMRTImpl(u32, bool) = 0;
    virtual void setBlendFactorImpl(BlendFactor, BlendFactor, BlendFactor, BlendFactor) = 0;
    virtual void setBlendFactorMRTImpl(u32, BlendFactor, BlendFactor, BlendFactor, BlendFactor) = 0;
    virtual void setBlendEquationImpl(BlendEquation, BlendEquation) = 0;
    virtual void setBlendEquationMRTImpl(u32, BlendEquation, BlendEquation) = 0;
    virtual void setBlendConstantColorImpl(const Color4f&) = 0;
    virtual void waitForVBlankImpl() = 0;
    virtual void setColorMaskImpl(bool, bool, bool, bool) = 0;
    virtual void setColorMaskMRTImpl(u32, bool, bool, bool, bool) = 0;
    virtual void setAlphaTestEnableImpl(bool) = 0;
    virtual void setAlphaTestFuncImpl(AlphaFunc, f32) = 0;
    virtual void setStencilTestEnableImpl(bool) = 0;
    virtual void setStencilTestFuncImpl(StencilFunc, s32, u32) = 0;
    virtual void setStencilTestOpImpl(StencilOp, StencilOp, StencilOp) = 0;
    virtual void setPolygonModeImpl(PolygonMode, PolygonMode) = 0;
    virtual void setPolygonOffsetEnableImpl(bool, bool, bool) = 0;

    static Graphics* instance() { return sInstance; }
    static DevicePosture sDefaultDevicePosture;
    static f32 sDefaultDeviceZScale;
    static f32 sDefaultDeviceZOffset;

private:
    void (*_0x20)(bool) = nullptr;
    DrawLockContext* mDrawLockContext = nullptr;
    static Graphics* sInstance;
};

static_assert(sizeof(Graphics) == 0x30);

}  // namespace sead
