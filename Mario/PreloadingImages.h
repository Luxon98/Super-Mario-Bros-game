#ifndef PreloadingImages_H
#define PreloadingImages_H

struct SDL_Surface;


void preloadBonusObjectsImages(SDL_Surface* display);

void preloadInanimateObjectImages(SDL_Surface* display);

void preloadLivingObjectImages(SDL_Surface* display);

void preloadTemporaryObjectImages(SDL_Surface* display);

void preloadAnimatedObjectImages(SDL_Surface* display);

void preloadOtherImages(SDL_Surface* display);

void preloadImages(SDL_Surface* display);

#endif //PreloadingImages_H