#include <SFML/Graphics.hpp>

using namespace sf;

////////////////////////////////////////////////////КЛАСС ИГРОКА////////////////////////////////////////////////////
class Player//Класс игрока
{ 
public:
    float x, y, w, h, dx, dy, speed; //Координаты игрока, высота, ширина, ускорение, сама скорость
    int dir; //Направление движения игрока
    String File; //Файл с расширением
    Image image; //Изображение
    Texture texture; //Текстура
    Sprite sprite; //Спрайт
    Player(String F, float X, float Y, float W, float H) //Конструктор с параметрами
    {
        dx = 0; dy = 0; speed = 0; dir = 0;
        File = F; //Имя файла
        w = W; h = H; //Высота и ширина
        image.loadFromFile("images/" + File); //Запихиваем в image изображение
        texture.loadFromImage(image); //Закидываем изображение в текстуру
        sprite.setTexture(texture); //Заливаем спрайт текстурой
        x = X; y = Y; //Координата появления спрайта
        sprite.setTextureRect(IntRect(0, 1529, w, h)); //Задаем спрайту один прямоугольник
    }
    void update(float time) //Функция обновления движения персонажа
    {
        switch (dir) //Поведение в зависимости от направления
        {
        case 0: dx = speed; dy = 0; break;//Движение вправо
        case 1: dx = -speed; dy = 0; break;//Движение влево
        }

        x += dx * time; //Ускорение на время = смещение координат, движение
        y += dy * time;

        speed = 0; //Зануляем скорость, чтобы персонаж остановился
        sprite.setPosition(x, y); //Бесконечно выводим спрайт в позицию x y
    }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    RenderWindow window(VideoMode(1400, 900), "Game");

    Player p("hero.png", 250, 250, 165, 228);

    
    float CurrentFrame = 0; //Текущий кадр
    Clock clock; //Время

    while (window.isOpen())
    {
        //Время//
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;
        /////////

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        ////////////////////////////////////////////////////Движение игрока////////////////////////////////////////////////////
        if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) //Движение влево
        {
            p.dir = 1; p.speed = 0.3; //Направление и скорость движения
            CurrentFrame += 0.02 * time; //Скорость анимации
            if (CurrentFrame > 12) CurrentFrame -= 12; //Число кадров
            p.sprite.setTextureRect(IntRect(165 * int(CurrentFrame) + 165, 65, -165, 228)); //Изменение анимации
        }

        else if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) //Движение вправо
        {
            p.dir = 0; p.speed = 0.3; //Направление и скорость движения
            CurrentFrame += 0.02 * time; //Скорость анимации
            if (CurrentFrame > 12) CurrentFrame -= 12; //Число кадров
            p.sprite.setTextureRect(IntRect(165 * int(CurrentFrame), 65, 165, 228)); //Изменение анимации
        }
        else p.sprite.setTextureRect(IntRect(0, 1529, 165, 228)); //Останавливаем спрайт

        p.update(time);//Передаем время в качестве параметра функции update. благодаря этому персонаж может двигаться
       ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        window.clear(Color(255,255,255));
        window.draw(p.sprite);
        window.display();
    }

    return 0;
}