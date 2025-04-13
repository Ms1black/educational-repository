#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <clocale>
#include <cwchar>
#include <locale>

#define PI 3.14159265

struct GradeData {
    int count;
    sf::Color color;
    const wchar_t* label;
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

        // Легенда
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

    GradeData grades[] = {
        { excellent, sf::Color::Green, L"Отлично" },
        { good, sf::Color::Blue, L"Хорошо" },
        { satisfactory, sf::Color::Yellow, L"Удовлетворительно" },
        { unsatisfactory, sf::Color::Red, L"Неудовлетворительно" }
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
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(30, 30, 30));
        drawPieChart(window, grades, 4, sf::Vector2f(500, 400), 200, font);
        window.display();
    }

    return 0;
}
