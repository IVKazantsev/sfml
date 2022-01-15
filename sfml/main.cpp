#include <SFML/Graphics.hpp>

using namespace sf;

////////////////////////////////////////////////////����� ������////////////////////////////////////////////////////
class Player//����� ������
{ 
public:
    float x, y, w, h, dx, dy, speed; //���������� ������, ������, ������, ���������, ���� ��������
    int dir; //����������� �������� ������
    String File; //���� � �����������
    Image image; //�����������
    Texture texture; //��������
    Sprite sprite; //������
    Player(String F, float X, float Y, float W, float H) //����������� � �����������
    {
        dx = 0; dy = 0; speed = 0; dir = 0;
        File = F; //��� �����
        w = W; h = H; //������ � ������
        image.loadFromFile("images/" + File); //���������� � image �����������
        texture.loadFromImage(image); //���������� ����������� � ��������
        sprite.setTexture(texture); //�������� ������ ���������
        x = X; y = Y; //���������� ��������� �������
        sprite.setTextureRect(IntRect(0, 1529, w, h)); //������ ������� ���� �������������
    }
    void update(float time) //������� ���������� �������� ���������
    {
        switch (dir) //��������� � ����������� �� �����������
        {
        case 0: dx = speed; dy = 0; break;//�������� ������
        case 1: dx = -speed; dy = 0; break;//�������� �����
        }

        x += dx * time; //��������� �� ����� = �������� ���������, ��������
        y += dy * time;

        speed = 0; //�������� ��������, ����� �������� �����������
        sprite.setPosition(x, y); //���������� ������� ������ � ������� x y
    }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    RenderWindow window(VideoMode(1400, 900), "Game");

    Player p("hero.png", 250, 250, 165, 228);

    
    float CurrentFrame = 0; //������� ����
    Clock clock; //�����

    while (window.isOpen())
    {
        //�����//
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

        ////////////////////////////////////////////////////�������� ������////////////////////////////////////////////////////
        if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) //�������� �����
        {
            p.dir = 1; p.speed = 0.3; //����������� � �������� ��������
            CurrentFrame += 0.02 * time; //�������� ��������
            if (CurrentFrame > 12) CurrentFrame -= 12; //����� ������
            p.sprite.setTextureRect(IntRect(165 * int(CurrentFrame) + 165, 65, -165, 228)); //��������� ��������
        }

        else if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) //�������� ������
        {
            p.dir = 0; p.speed = 0.3; //����������� � �������� ��������
            CurrentFrame += 0.02 * time; //�������� ��������
            if (CurrentFrame > 12) CurrentFrame -= 12; //����� ������
            p.sprite.setTextureRect(IntRect(165 * int(CurrentFrame), 65, 165, 228)); //��������� ��������
        }
        else p.sprite.setTextureRect(IntRect(0, 1529, 165, 228)); //������������� ������

        p.update(time);//�������� ����� � �������� ��������� ������� update. ��������� ����� �������� ����� ���������
       ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        window.clear(Color(255,255,255));
        window.draw(p.sprite);
        window.display();
    }

    return 0;
}