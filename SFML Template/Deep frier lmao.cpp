#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

const unsigned int W = 600;
const unsigned int H = 1000; // you can change this to full window size later


sf::Image img;

int Index(int x, int y) { return (x + y * W)*4; };

int main()
{
	sf::RenderWindow window(sf::VideoMode(W, H), "Window");


	img.loadFromFile("img.jpg");

	sf::Uint8* pixels = new sf::Uint8[W*H * 4];
	sf::Texture texture;
	texture.create(W, H);

	sf::Sprite sprite(texture); // needed to draw the texture on screen

	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++) {

			int index = (x + y * W);

			pixels[Index(x, y) + 0] = img.getPixel(x, y).r;
			pixels[Index(x, y) + 1] = img.getPixel(x, y).g;
			pixels[Index(x, y) + 2] = img.getPixel(x, y).b;
			pixels[Index(x, y) + 3] = img.getPixel(x, y).a;

		}
	}


	for (int y = 0; y < H-1; y++) {
		for (int x = 1; x < W-1; x++) {
			
			float oldR = img.getPixel(x, y).r;
			float oldG = img.getPixel(x, y).g;
			float oldB = img.getPixel(x, y).b;

			int factor = 1;
			int newR = round(factor * oldR / 255) * (255 / factor);
			int newG = round(factor * oldG / 255) * (255 / factor);
			int newB = round(factor * oldB / 255) * (255 / factor);

			pixels[Index(x, y) + 0] = newR;
			pixels[Index(x, y) + 1] = newG;
			pixels[Index(x, y) + 2] = newB;
			pixels[Index(x, y) + 3] = 255;

		    //oldpixel: = pixel[x][y]
			//newpixel : = find_closest_palette_color(oldpixel)
			//pixel[x][y] : = newpixel
			//quant_error : = oldpixel - newpixel
			//pixel[x + 1][y] : = pixel[x + 1][y] + quant_error * 7 / 16
			//pixel[x - 1][y + 1] : = pixel[x - 1][y + 1] + quant_error * 3 / 16
			//pixel[x][y + 1] : = pixel[x][y + 1] + quant_error * 5 / 16
			//pixel[x + 1][y + 1] : = pixel[x + 1][y + 1] + quant_error * 1 / 16
			
		}
	}


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		texture.update(pixels);
		window.clear();
		window.draw(sprite);
		window.display();
	}

	return NULL;
}