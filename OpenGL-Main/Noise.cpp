#include "Noise.h"



Noise::Noise()
{
}


Noise::~Noise()
{
}

GLubyte * Noise::generateNoiseMap(int width, int height,float a,float b)
{
	width = w; 
	height = h; 
	GLubyte * data=new GLubyte[width * height * 4];
	float xFactor = 1.0f / (width - 1);
	float yFactor = 1.0f / (height - 1);
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			float x = xFactor * col;
			float y = yFactor * row;
			float sum = 0.0f;
			float freq = a;
			float scale = b;

			// Compute the sum for each octave
			for (int oct = 0; oct < 4; oct++) {
				glm::vec2 p(x * freq, y * freq);
				float val = glm::perlin(p) / scale;
				sum += val;
				float result = (sum + 1.0f) / 2.0f;

				// Store in texture buffer
				data[((row * width + col) * 4) + oct] =
					(GLubyte)(result * 255.0f);
				freq *= 2.0f;   // Double the frequency
				scale *= b;     // Next power of b
			}
		}
	}
	
	//delete[] noiseMap;
	for (int j = 0; j * 2 < h; ++j)
	{
		int index1 = j * w;
		int index2 = (h - 1 - j) * w;
		for (int i = w; i > 0; --i)
		{
			GLubyte temp = data[index1];
			data[index1] = data[index2];
			data[index2] = temp;
			++index1;
			++index2;
		}
	}
	return data;
}

void Noise::loadToSoil(GLubyte* noiseMap)
{
	
	/* 
	glGenTextures(1, &heightMapTextureID);

	glBindTexture(GL_TEXTURE_2D, heightMapTextureID);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, w, h);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0,w, h, GL_RGBA, GL_UNSIGNED_BYTE, noiseMap);

	delete[] noiseMap;
*/
	//free SOIL image data
	//delete[] noiseMap;
}

void Noise::MakeNoiseAndBind(int width, int height, float freq, float scale)
{
	noiseMap=generateNoiseMap(width, height, freq, scale);
	loadToSoil(noiseMap);
}
