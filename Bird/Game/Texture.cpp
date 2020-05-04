#include "../Game/Texture.h"
#include "../Game/Renderer.h"
#include <SDL_image.h>
namespace Game {
    void Texture::LoadTexture(Renderer* renderer_, std::string path_)
    {
        m_Texture = IMG_LoadTexture(renderer_->GetNativeRenderer(), path_.c_str());

        if (m_Texture == nullptr)
        {
          std::cerr<<"Unable to load texture: "<<path_<<" SDL_Image returned error"<<IMG_GetError();
        }
    }

    Texture::~Texture()
    {
        if (m_Texture)
        {
            SDL_DestroyTexture(m_Texture);
        }
    }
}
