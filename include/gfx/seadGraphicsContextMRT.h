#pragma once

#include "gfx/seadColor.h"
#include "gfx/seadDrawContext.h"
#include "gfx/seadGraphics.h"
#include "prim/seadBitFlag.h"

namespace sead
{
class DrawContext;

class GraphicsContextMRT
{
public:
    struct BlendState
    {
        Graphics::BlendFactor src_color_factor = Graphics::cBlendFactor_SrcAlpha;
        Graphics::BlendFactor src_alpha_factor = Graphics::cBlendFactor_SrcAlpha;
        Graphics::BlendFactor dst_color_factor = Graphics::cBlendFactor_OneMinusSrcAlpha;
        Graphics::BlendFactor dst_alpha_factor = Graphics::cBlendFactor_OneMinusSrcAlpha;
        Graphics::BlendEquation color_equation = Graphics::cBlendEquation_Add;
        Graphics::BlendEquation alpha_equation = Graphics::cBlendEquation_Add;
    };

    static_assert(sizeof(BlendState) == 0x18);

    GraphicsContextMRT();
    virtual ~GraphicsContextMRT() = default;
    void apply(DrawContext* ctx) const;
    void applyAlphaTest(DrawContext* ctx) const;
    void applyDepthAndStencilTest(DrawContext* ctx) const;
    void applyColorMask(DrawContext* ctx) const;
    void applyBlendAndFastZ(DrawContext* ctx) const;
    void applyBlendConstantColor(DrawContext* ctx) const;
    void applyCullingAndPolygonModeAndPolygonOffset(DrawContext* ctx) const;

    void setDepthTestEnable(bool enable) { mDepthTestEnable = enable; }

    void setDepthWriteEnable(bool enable) { mDepthWriteEnable = enable; }

    void setBlendEnable(s32 target, bool enable) { mBlendEnableMask.changeBit(target, enable); }

    BlendState& getBlendState(s32 target) { return mBlendState[target]; }

    void set_0xe8(bool enable) { _0xe8 = enable; }

    void setColorMask(u32 mask) { mColorMask = mask; }

private:
    bool mDepthTestEnable = true;
    bool mDepthWriteEnable = true;
    Graphics::DepthFunc mDepthFunc = Graphics::cDepthFunc_LessEqual;
    Graphics::CullingMode mCullingMode = Graphics::cCullingMode_Back;
    BitFlag32 mBlendEnableMask = 0xff;
    BlendState mBlendState[8];
    Color4f mBlendConstantColor = {1, 1, 1, 1};
    bool _0xe8 = false;
    s32 _0xec = 5;
    s32 _0xf0 = 0;
    u32 mColorMask = 0xffffffff;
    bool mStencilTestEnable = false;
    Graphics::StencilFunc mStencilFunc = Graphics::cStencilFunc_Never;
    s32 mStencilRef = 0;
    u32 mStencilValueMask = 0xffffffff;
    Graphics::StencilOp mStencilFailOp = Graphics::cStencilOp_Keep;
    Graphics::StencilOp mStencilDepthFailOp = Graphics::cStencilOp_Keep;
    Graphics::StencilOp mStencilDepthPassOp = Graphics::cStencilOp_Keep;
    s32 _0x114 = -1;
    Graphics::PolygonMode mPolygonMode = Graphics::cPolygonMode_Fill;
    s32 _0x11c = 2;
    bool mPolygonOffsetEnable = false;
    bool _0x121 = false;
    bool _0x122 = false;
};

static_assert(sizeof(GraphicsContextMRT) == 0x128);

}  // namespace sead
