#pragma once
#include"OpenGL-Main.h"
class Noise
{
public:
	Noise();
	~Noise();
	GLubyte* noiseMap;
	GLuint heightMapTextureID;
	GLubyte* generateNoiseMap(int texture_width = 0, int texture_height = 0,float freq=0.001,float scale=1);
	void loadToSoil(GLubyte* noiseMap);
	void MakeNoiseAndBind(int width , int height ,float freq,float scale);

	int w, h; 
};

