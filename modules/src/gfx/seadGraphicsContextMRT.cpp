#include "gfx/seadGraphicsContextMRT.h"

#include <nvn/nvn_FuncPtrInline.h>
#include "nvn/nvn.h"

namespace sead
{

GraphicsContextMRT::GraphicsContextMRT()
{
    mColorMask = 0xffffffff;
}

void GraphicsContextMRT::apply(DrawContext* ctx) const
{
    NVNcommandBuffer* command_buffer = ctx->getNvnCommandBuffer();
    NVNblendState blend;
    NVNcolorState color;
    nvnBlendStateSetDefaults(&blend);
    nvnColorStateSetDefaults(&color);
    for (s32 i = 0; i < 8; ++i)
    {
        bool blend_enable = mBlendEnableMask & (1 << i);
        nvnColorStateSetBlendEnable(&color, i, blend_enable);
        if (blend_enable)
        {
            nvnBlendStateSetBlendTarget(&blend, i);
            nvnBlendStateSetBlendFunc(&blend,
                                      static_cast<NVNblendFunc>(mBlendState[i].src_color_factor),
                                      static_cast<NVNblendFunc>(mBlendState[i].dst_color_factor),
                                      static_cast<NVNblendFunc>(mBlendState[i].src_alpha_factor),
                                      static_cast<NVNblendFunc>(mBlendState[i].dst_alpha_factor));
            nvnBlendStateSetBlendEquation(
                &blend, static_cast<NVNblendEquation>(mBlendState[i].color_equation),
                static_cast<NVNblendEquation>(mBlendState[i].alpha_equation));
            nvnCommandBufferBindBlendState(command_buffer, &blend);
        }
    }
    nvnColorStateSetLogicOp(&color, NVN_LOGIC_OP_COPY);
    nvnCommandBufferBindColorState(command_buffer, &color);
    nvnCommandBufferSetBlendColor(command_buffer,
                                  reinterpret_cast<const float*>(&mBlendConstantColor));
    NVNchannelMaskState channel_mask;
    for (s32 i = 0; i < 8; ++i)
    {
        u32 mask = mColorMask >> (i * 4);
        bool r = mask & 1;
        bool g = mask & 2;
        bool b = mask & 4;
        bool a = mask & 8;
        nvnChannelMaskStateSetChannelMask(&channel_mask, i, r, g, b, a);
    }
    nvnCommandBufferBindChannelMaskState(command_buffer, &channel_mask);
    NVNdepthStencilState depth_stencil;
    nvnDepthStencilStateSetDepthTestEnable(&depth_stencil, mDepthTestEnable);
    nvnDepthStencilStateSetDepthWriteEnable(&depth_stencil, mDepthWriteEnable);
    nvnDepthStencilStateSetDepthFunc(&depth_stencil, static_cast<NVNdepthFunc>(mDepthFunc));
    nvnDepthStencilStateSetStencilTestEnable(&depth_stencil, mStencilTestEnable);
    nvnDepthStencilStateSetStencilFunc(&depth_stencil, NVN_FACE_FRONT_AND_BACK,
                                       static_cast<NVNstencilFunc>(mStencilFunc));
    nvnDepthStencilStateSetStencilOp(&depth_stencil, NVN_FACE_FRONT_AND_BACK,
                                     static_cast<NVNstencilOp>(mStencilFailOp),
                                     static_cast<NVNstencilOp>(mStencilDepthFailOp),
                                     static_cast<NVNstencilOp>(mStencilDepthPassOp));
    nvnCommandBufferBindDepthStencilState(command_buffer, &depth_stencil);
    if (mStencilTestEnable)
    {
        nvnCommandBufferSetStencilValueMask(command_buffer, NVN_FACE_FRONT_AND_BACK,
                                            mStencilValueMask);
        nvnCommandBufferSetStencilMask(command_buffer, NVN_FACE_FRONT_AND_BACK, 0xff);
        nvnCommandBufferSetStencilRef(command_buffer, NVN_FACE_FRONT_AND_BACK, mStencilRef);
    }
    NVNpolygonState polygon;
    nvnPolygonStateSetCullFace(&polygon, static_cast<NVNface>(mCullingMode));
    nvnPolygonStateSetFrontFace(&polygon, NVN_FRONT_FACE_CCW);
    nvnPolygonStateSetPolygonMode(&polygon, static_cast<NVNpolygonMode>(mPolygonMode));
    nvnPolygonStateSetPolygonOffsetEnables(&polygon, mPolygonOffsetEnable ? 4 : 0);
    nvnCommandBufferBindPolygonState(command_buffer, &polygon);
}

void GraphicsContextMRT::applyAlphaTest(DrawContext*) const {}

void GraphicsContextMRT::applyDepthAndStencilTest(DrawContext* ctx) const
{
    NVNdepthStencilState depth_stencil;
    nvnDepthStencilStateSetDepthTestEnable(&depth_stencil, mDepthTestEnable);
    nvnDepthStencilStateSetDepthWriteEnable(&depth_stencil, mDepthWriteEnable);
    nvnDepthStencilStateSetDepthFunc(&depth_stencil, static_cast<NVNdepthFunc>(mDepthFunc));
    nvnDepthStencilStateSetStencilTestEnable(&depth_stencil, mStencilTestEnable);
    nvnDepthStencilStateSetStencilFunc(&depth_stencil, NVN_FACE_FRONT_AND_BACK,
                                       static_cast<NVNstencilFunc>(mStencilFunc));
    nvnDepthStencilStateSetStencilOp(&depth_stencil, NVN_FACE_FRONT_AND_BACK,
                                     static_cast<NVNstencilOp>(mStencilFailOp),
                                     static_cast<NVNstencilOp>(mStencilDepthFailOp),
                                     static_cast<NVNstencilOp>(mStencilDepthPassOp));
    nvnCommandBufferBindDepthStencilState(ctx->getNvnCommandBuffer(), &depth_stencil);
    if (mStencilTestEnable)
    {
        nvnCommandBufferSetStencilValueMask(ctx->getNvnCommandBuffer(), NVN_FACE_FRONT_AND_BACK,
                                            mStencilValueMask);
        nvnCommandBufferSetStencilMask(ctx->getNvnCommandBuffer(), NVN_FACE_FRONT_AND_BACK, 0xff);
        nvnCommandBufferSetStencilRef(ctx->getNvnCommandBuffer(), NVN_FACE_FRONT_AND_BACK,
                                      mStencilRef);
    }
}

void GraphicsContextMRT::applyColorMask(DrawContext* ctx) const
{
    NVNchannelMaskState channel_mask;
    for (s32 i = 0; i < 8; ++i)
    {
        u32 mask = mColorMask >> (i * 4);
        bool r = mask & 1;
        bool g = mask & 2;
        bool b = mask & 4;
        bool a = mask & 8;
        nvnChannelMaskStateSetChannelMask(&channel_mask, i, r, g, b, a);
    }
    nvnCommandBufferBindChannelMaskState(ctx->getNvnCommandBuffer(), &channel_mask);
}

void GraphicsContextMRT::applyBlendAndFastZ(DrawContext* ctx) const
{
    NVNcommandBuffer* command_buffer = ctx->getNvnCommandBuffer();
    NVNblendState blend;
    NVNcolorState color;
    nvnBlendStateSetDefaults(&blend);
    nvnColorStateSetDefaults(&color);
    for (s32 i = 0; i < 8; ++i)
    {
        bool blend_enable = mBlendEnableMask & (1 << i);
        nvnColorStateSetBlendEnable(&color, i, blend_enable);
        if (blend_enable)
        {
            nvnBlendStateSetBlendTarget(&blend, i);
            nvnBlendStateSetBlendFunc(&blend,
                                      static_cast<NVNblendFunc>(mBlendState[i].src_color_factor),
                                      static_cast<NVNblendFunc>(mBlendState[i].dst_color_factor),
                                      static_cast<NVNblendFunc>(mBlendState[i].src_alpha_factor),
                                      static_cast<NVNblendFunc>(mBlendState[i].dst_alpha_factor));
            nvnBlendStateSetBlendEquation(
                &blend, static_cast<NVNblendEquation>(mBlendState[i].color_equation),
                static_cast<NVNblendEquation>(mBlendState[i].alpha_equation));
            nvnCommandBufferBindBlendState(command_buffer, &blend);
        }
    }
    nvnColorStateSetLogicOp(&color, NVN_LOGIC_OP_COPY);
    nvnCommandBufferBindColorState(command_buffer, &color);
}

void GraphicsContextMRT::applyBlendConstantColor(DrawContext* ctx) const
{
    nvnCommandBufferSetBlendColor(ctx->getNvnCommandBuffer(),
                                  reinterpret_cast<const float*>(&mBlendConstantColor));
}

void GraphicsContextMRT::applyCullingAndPolygonModeAndPolygonOffset(DrawContext* ctx) const
{
    NVNpolygonState polygon;
    nvnPolygonStateSetCullFace(&polygon, static_cast<NVNface>(mCullingMode));
    nvnPolygonStateSetFrontFace(&polygon, NVN_FRONT_FACE_CCW);
    nvnPolygonStateSetPolygonMode(&polygon, static_cast<NVNpolygonMode>(mPolygonMode));
    nvnPolygonStateSetPolygonOffsetEnables(&polygon, mPolygonOffsetEnable ? 4 : 0);
    nvnCommandBufferBindPolygonState(ctx->getNvnCommandBuffer(), &polygon);
}

}  // namespace sead
