#pragma once

#include "gfx/seadFrameBuffer.h"
#include "math/seadVectorFwd.h"

namespace sead
{
class Color4f;
class DisplayBuffer;
class DrawContext;
class Heap;

class FrameBufferNvn : public FrameBuffer
{
    SEAD_RTTI_OVERRIDE(FrameBufferNvn, FrameBuffer)

public:
    ~FrameBufferNvn() override;
    void clear(DrawContext*, u32, const Color4f&, f32, u32) const override;
    void copyToDisplayBuffer(DrawContext*, const DisplayBuffer*) const override;
    void create(Heap*, const Vector2f&, u32, u32);

protected:
    void bindImpl_(DrawContext*) const override;

private:
    // TODO
};

class DisplayBufferNvn : public DisplayBuffer
{
    SEAD_RTTI_OVERRIDE(DisplayBufferNvn, DisplayBuffer)

public:
    DisplayBufferNvn();
    void presentTextureAndAcquireNext();
    void waitAcquireDone();
    void setPresentInterval(u8);
    void setTripleBuffer(bool);
    void setWindowCrop(s32, s32, s32, s32);
    void getWindowCrop(s32*, s32*, s32*, s32*) const;
    void applyChangeWindowCrop();

protected:
    void initializeImpl_(Heap*);

private:
    // TODO
};

}  // namespace sead
