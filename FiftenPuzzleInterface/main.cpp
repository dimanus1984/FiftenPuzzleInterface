#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
	srand(time(NULL));
	RenderWindow window(VideoMode(512, 512), "15-Puzzle!");

	window.setFramerateLimit(60);

	Texture texture;
	texture.loadFromFile("images/15.png");
	int blockWidht = 128;

	const int arraySize = 6;
	int array[arraySize][arraySize];

	// Массив спрайтов
	Sprite sprite[17];

	/////////////////////////////////////////////////////////////////////////////////


	// Создаем спрайты соответствующих чисел и заполняем ячейки игрового поля
	int n = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			n++;
			sprite[n].setTexture(texture);
			sprite[n].setTextureRect(IntRect(i*blockWidht, j*blockWidht, blockWidht, blockWidht));
			array[i + 1][j + 1] = n;
		}

	/////////////////////////////////////////////////////////////////////////////////

	// Главный цикл приложения: выполняется, пока открыто окно
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonPressed)
			{
				if (event.key.code == Mouse::Left)
				{
					Vector2i position = Mouse::getPosition(window);
					int x = position.x / blockWidht + 1;
					int y = position.y / blockWidht + 1;

					// Переменные для задания смещения...
					int dx = 0; //...горизонтального...
					int dy = 0; //...и вертикального.

					// Если справа пустое место
					if (array[x + 1][y] == 16) { dx = 1; dy = 0; };

					// Если снизу пустое место
					if (array[x][y + 1] == 16) { dx = 0; dy = 1; };

					// Если сверху пустое место
					if (array[x][y - 1] == 16) { dx = 0; dy = -1; };

					// Если слева пустое место
					if (array[x - 1][y] == 16) { dx = -1; dy = 0; };

					// Меняем местами пустую клетку с выбранным блоком
					int temp = array[x][y];
					array[x][y] = 16;
					array[x + dx][y + dy] = temp;

					// Ставим пустой блок на место выбранного пользователем блока
					sprite[16].move(-dx * blockWidht, -dy * blockWidht);
					// Скорость анимации
					float speed = 6;
					for (int i = 0; i < blockWidht; i += speed)
					{
						// Двигаем выбранный блок
						sprite[temp].move(speed*dx, speed*dy);
						// Отрисовываем пустой блок
						window.draw(sprite[16]);
						// Отрисовываем выбранный блок
						window.draw(sprite[temp]);
						// Отображаем всю композицию в окне
						window.display();
					}
				}

			}
		}
		window.clear(Color::White);

	/////////////////////////////////////////////////////////////////////////////////

		// Установка каждого спрайта на свое место + Отрисовка спрайта
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				// Считываем значение ячейки игрового поля…
				int n = array[i + 1][j + 1];
				// …и устанавливаем на нее соответствующий спрайт
				sprite[n].setPosition(i*blockWidht, j*blockWidht);
				// Отрисовка спрайта
				window.draw(sprite[n]);
			}

	/////////////////////////////////////////////////////////////////////////////////

		window.display();
	}
	return 0;
}
