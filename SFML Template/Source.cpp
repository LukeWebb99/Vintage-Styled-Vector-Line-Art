#include <SFML/Graphics.hpp>
#include <windows.h>
#include <iostream>
using namespace std;

void Stealth()
{
	HWND Stealth;
	AllocConsole();
	Stealth = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(Stealth, 0);
}

float x1(float t) {
	return sin(t/10) * 100 + cos(t / 5) * 20;
}

float y1(float t) {
	return cos(t/10)*100 + cos(t / 6) * 2;
}

float x2(float t) {
	return sin(t / 10) * 200 - sin(t) * 5;
}

float y2(float t) {
	return cos(t / 20) * 200 - cos(t/12) * 20;
}

class Line
{
public:
	Line(float number) {
		T = number;
	};

	float T;
	void update() {
		T += 0.2; 
	};
	void draw(sf::RenderTarget &window) {
		sf::VertexArray line(sf::Lines, 2);
		line[0].position = sf::Vector2f(250 + x1(T), 250 + y1(T));
		line[1].position = sf::Vector2f(250 + x2(T), 250 + y2(T));
		window.draw(line);
	}

};

int main()
{

	Stealth();

	sf::ContextSettings setting;
	//setting.antialiasingLevel = 16;
	sf::RenderWindow window(sf::VideoMode(500, 500), "Window", 0, setting);
	//window.setFramerateLimit(60);

	std::vector<Line> lines;

	for (int i = 0; i < 10; i++) {
		lines.push_back(Line(i));
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		for (int i = 0; i < lines.size(); i++) {
			lines[i].update();
		}

		window.clear(sf::Color().Transparent);

		for (int i = 0; i < lines.size(); i++) {
			lines[i].draw(window);
		}

		window.display();
	}

	return NULL;
}


