#pragma once

#include <basis/seadTypes.h>

namespace sead
{

class GraphicsContextMRT
{
public:
    GraphicsContextMRT();
    virtual ~GraphicsContextMRT() = default;

    void _setValues()
    {
        _0x8 = 0;
        _0x18 = 2;
        _0x14 |= 1;
        _0x20 = 2;
        _0x28 = 1;
        _0xe8 = false;
        _0xf4 = 0xff;
    }

private:
    s16 _0x8;
    s32 _0xc;
    s32 _0x10;
    s32 _0x14;
    s32 _0x18;
    s32 _0x1c;
    s32 _0x20;
    s32 _0x24;
    s32 _0x28;
    void* _padding_0x30[0x17];
    bool _0xe8;
    s32 _0xec;
    s32 _0xf0;
    s32 _0xf4;
    void* _padding_0xf8[0x6];
};

static_assert(sizeof(GraphicsContextMRT) == 0x128);

}  // namespace sead
