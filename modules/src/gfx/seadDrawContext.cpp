#include "gfx/seadDrawContext.h"

#include "gfx/nvn/seadGraphicsNvn.h"

namespace sead
{

DrawContext::DrawContext()
{
    mCommandBuffer.ToData()->pNnDevice =
        static_cast<GraphicsNvn*>(Graphics::instance())->getNnDevice();
    mCommandBuffer.ToData()->pNvnCommandBuffer = nullptr;
    mCommandBuffer.ToData()->state =
        nn::gfx::CommandBufferImplData<nn::gfx::ApiVariationNvn8>::State_Begun;
}

}  // namespace sead
