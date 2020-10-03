#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main()
{

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Rect dest;
    unsigned int close = 0;
    int speed = 300;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {

        printf("Init failed: %s\n", SDL_GetError());

    }

    window = SDL_CreateWindow("TEST", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 320, 240, 0);

    if (!window)
    {

        printf("Window could not be created: %s\n", SDL_GetError());

    }

    renderer = SDL_CreateRenderer(window, 1, SDL_RENDERER_ACCELERATED);

    if (!renderer)
    {

        printf("Renderer could not be created: %s\n", SDL_GetError());

    }

    surface = IMG_Load("icon.png");

    if (!surface)
    {

        printf("Surface could not be created: %s\n", IMG_GetError());

    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (!texture)
    {

        printf("Texture could not be created: %s\n", SDL_GetError());

    }

    SDL_FreeSurface(surface);
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

    dest.w /= 6;
    dest.h /= 6;
    dest.x = (320 - dest.w) / 2;
    dest.y = (240 - dest.h) / 2;

    printf("Starting\n");

    while (!close)
    {

        SDL_Event event;

        while (SDL_PollEvent(&event))
        {

            switch (event.type)
            {

            case SDL_QUIT:
                close = 1;

                break;

            case SDL_KEYDOWN:
                printf("Keydown\n");

                switch (event.key.keysym.scancode)
                {

                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    dest.y -= speed / 30;

                    break;

                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    dest.x -= speed / 30;

                    break;

                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    dest.y += speed / 30;

                    break;

                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    dest.x += speed / 30;

                    break;

                default:
                    close = 1;

                    break;

                }

                break;

            }

        }

        if (dest.x + dest.w > 320)
            dest.x = 320 - dest.w;

        if (dest.x < 0)
            dest.x = 0;

        if (dest.y + dest.h > 240)
            dest.y = 240 - dest.h;

        if (dest.y < 0)
            dest.y = 0;

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, &dest);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / 60);

    }

    printf("Exiting\n");

    return 0;

}

