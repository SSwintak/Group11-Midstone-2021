#ifndef IMAGETEXTURE_H
#define IMAGETEXTURE_H


#include "Vector.h"
#include "VMath.h"
#include "SDL_image.h"
#include <iostream>
#include <string>

using namespace std;
using namespace MATH;

class ImageTexture {
private:
	SDL_Surface* image;
	SDL_Texture* texture;
	Vec3 imageSizeWorldCoords;
	string imageName;

public:
	ImageTexture();
	~ImageTexture();
	ImageTexture(string imageName_);
	string getimageName() { return imageName; }
	void setimageName(string imageName_) { imageName = imageName_; }
	void setImage(SDL_Surface* image_) { image = image_; }
	SDL_Surface* getImage() { return image; }
	void setTexture(SDL_Texture* texture_) { texture = texture_; }
	SDL_Texture* getTexture() { return texture; }

	void setImageSizeWorldCoords(Vec3 imageSizeWorldCoords_) {
		imageSizeWorldCoords.x = imageSizeWorldCoords_.x;
		imageSizeWorldCoords.y = imageSizeWorldCoords_.y;
		imageSizeWorldCoords.z = imageSizeWorldCoords_.z;
		imageSizeWorldCoords = imageSizeWorldCoords_;
	}
	Vec3 getImageSizeWorldCoords() { return imageSizeWorldCoords; }

};

#endif

