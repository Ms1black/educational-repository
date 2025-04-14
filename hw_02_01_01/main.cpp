#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <clocale>
#include <cwchar>
#include <locale>
#include <ctime> 

#define PI 3.14159265
#define SUBJECTS 5

struct GradeData {
    float count;
    sf::Color color;
    const wchar_t* label;
};

struct SubjectData {
    float baseValue;
    float amplitude;
    float phaseShift;
    sf::Color color;
    const wchar_t* label;
    float currentValue;
};

void drawPieChart(sf::RenderWindow& window, GradeData* data, int size, sf::Vector2f center, float radius, sf::Font& font) {
    int total = 0;
    for (int i = 0; i < size; ++i) total += data[i].count;

    float start_angle = 0;
    for (int i = 0; i < size; ++i) {
        float percent = static_cast<float>(data[i].count) / total;
        float angle = percent * 360;

        sf::ConvexShape sector;
        sector.setPointCount(100);
        sector.setFillColor(data[i].color);

        sector.setPoint(0, center);
        for (int j = 1; j < 100; ++j) {
            float theta = (start_angle + angle * j / 99) * PI / 180;
            float x = center.x + radius * std::cos(theta);
            float y = center.y + radius * std::sin(theta);
            sector.setPoint(j, sf::Vector2f(x, y));
        }

        window.draw(sector);

        sf::RectangleShape legend_color(sf::Vector2f(20, 20));
        legend_color.setPosition(50, 50 + i * 40);
        legend_color.setFillColor(data[i].color);

        sf::Text legend_text;
        legend_text.setFont(font);
        legend_text.setString(data[i].label);
        legend_text.setCharacterSize(20);
        legend_text.setPosition(80, 45 + i * 40);
        legend_text.setFillColor(sf::Color::White);

        window.draw(legend_color);
        window.draw(legend_text);

        start_angle += angle;
    }
}

int main() {

    int selectedSubject = 0;

    srand(time(nullptr));

    setlocale(LC_ALL, "ru_RU.UTF-8");
    std::locale::global(std::locale("ru_RU.UTF-8"));

    int excellent, good, satisfactory, unsatisfactory;

    std::wcout << L"Введите количество студентов, получивших 'отлично': ";
    std::wcin >> excellent;
    std::wcout << L"Введите количество студентов, получивших 'хорошо': ";
    std::wcin >> good;
    std::wcout << L"Введите количество студентов, получивших 'удовлетворительно': ";
    std::wcin >> satisfactory;
    std::wcout << L"Введите количество студентов, у которых двойка любимая оценка: ";
    std::wcin >> unsatisfactory;

   SubjectData subjects[] = {
    { 30, 10, 0.0f, sf::Color(rand() % 256, rand() % 256, rand() % 256), L"ООП" },
    { 25, 8, 1.0f, sf::Color(rand() % 256, rand() % 256, rand() % 256), L"Физика" },
    { 20, 5, 2.0f, sf::Color(rand() % 256, rand() % 256, rand() % 256), L"Мат.анализ" },
    { 15, 7, 3.0f, sf::Color(rand() % 256, rand() % 256, rand() % 256), L"Физра" },
    { 10, 6, 4.0f, sf::Color(rand() % 256, rand() % 256, rand() % 256), L"ВП" }
};

    GradeData grades[] = {
        { 1, subjects[0].color, subjects[0].label },
        { 1, subjects[1].color, subjects[1].label },
        { 1, subjects[2].color, subjects[2].label },
        { 1, subjects[3].color, subjects[3].label },
        { 1, subjects[4].color, subjects[4].label }
    };



    sf::RenderWindow window(sf::VideoMode(800, 800), L"Успеваемость студентов");
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        std::cerr << "\n\033[1;31mОшибка загрузки шрифта\033[0m\n";
        return -1;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Num1) selectedSubject = 0;
            if (event.key.code == sf::Keyboard::Num2) selectedSubject = 1;
            if (event.key.code == sf::Keyboard::Num3) selectedSubject = 2;
            if (event.key.code == sf::Keyboard::Num4) selectedSubject = 3;
            if (event.key.code == sf::Keyboard::Num5) selectedSubject = 4;

            if (event.key.code == sf::Keyboard::Add || event.key.code == sf::Keyboard::Equal)
                subjects[selectedSubject].baseValue += 1;

            if (event.key.code == sf::Keyboard::Hyphen)
                subjects[selectedSubject].baseValue -= 1;

            if (subjects[selectedSubject].baseValue < 1)
                subjects[selectedSubject].baseValue = 1;
        }
            if (event.type == sf::Event::Closed)
                window.close();
        }
        sf::Clock clock; 
        float t = clock.getElapsedTime().asSeconds();

        for (int i = 0; i < SUBJECTS; ++i) {
            subjects[i].currentValue = subjects[i].baseValue + std::sin(t + subjects[i].phaseShift) * subjects[i].amplitude;
            if (subjects[i].currentValue < 1.f)
                subjects[i].currentValue = 1.f;
            grades[i].count = subjects[i].currentValue;
        }

        window.clear(sf::Color(30, 30, 30));
        drawPieChart(window, grades, SUBJECTS, sf::Vector2f(500, 400), 200, font);
        sf::Text info;
        info.setFont(font);
        info.setCharacterSize(20);
        info.setFillColor(sf::Color::White);
        info.setString(L"Текущий предмет: " + std::wstring(subjects[selectedSubject].label));
        info.setPosition(50, 750);
        window.draw(info);


        window.display();
    }

    return 0;
}
