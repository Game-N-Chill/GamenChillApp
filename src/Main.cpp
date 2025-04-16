
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

int main(int ac, char **av)
{
    SDL_Surface* img1 = IMG_Load("Assets\\Images\\Characters\\Daisy\\default.png");
    SDL_Surface* img2 = IMG_Load("Assets\\Images\\Characters\\Luigi\\default.png");

    float scale = 0.5f;
    int totalWidth = img1->w + img2->w * scale;
    int maxHeight = (img1->h > img2->h * scale) ? img1->h : img2->h * scale;

    SDL_Surface* surface = SDL_CreateSurface(totalWidth, maxHeight, SDL_PIXELFORMAT_RGBA32);

    SDL_Rect dst1 = {0, 0, img1->w, img1->h};
    SDL_Rect dst2 = {img1->w, 0, static_cast<int>(img2->w * scale), static_cast<int>(img2->h * scale)};
    SDL_BlitSurface(img1, nullptr, surface, &dst1);
    SDL_BlitSurfaceScaled(img2, nullptr, surface, &dst2, SDL_SCALEMODE_LINEAR);

    IMG_SavePNG(surface, "test3.png");

    SDL_DestroySurface(img1);
    SDL_DestroySurface(img2);
    SDL_DestroySurface(surface);

    return 0;
}
