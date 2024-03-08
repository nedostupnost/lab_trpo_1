#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Sleep.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace sf;

struct color {
    int r;
    int g;
    int b;
};

struct cordinate {
    double x;
    double y;
};

struct shape {
    struct cordinate cordinate;
    int radius;
    struct color color;
};

void start_info(void);

shape parser(std::string& wkt);

void checker_error(
        int rad, int cord_x, int cord_y, int color_r, int color_g, int color_b);

void program_stop(int type_error);

void figure_circle(void);

void star_printer(void);

int main()
{
    std::string geometry;

    start_info();

    std::getline(std::cin, geometry);

    std::istringstream iss(geometry);
    std::string sshape;
    iss >> sshape;
    try {
        if (sshape == "circle") {
            std::cout << "\nИдет обработка, подождите...\n" << std::endl;
        }
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }

    shape circle = parser(geometry);

    checker_error(
            circle.radius,
            circle.cordinate.x,
            circle.cordinate.y,
            circle.color.r,
            circle.color.g,
            circle.color.b);

    std::cout << "Информация успешно получена!" << std::endl;

    CircleShape circles(circle.radius);
    circles.setPosition(circle.cordinate.x, circle.cordinate.y);
    circles.setFillColor(Color(circle.color.r, circle.color.g, circle.color.b));

    std::cout << "Какого цвета вы хотите фон? Напишите его, в формате rgb, "
                 "через пробел"
              << std::endl;

    struct color background;

    std::cin >> background.r >> background.g >> background.b;

    checker_error(1, 1, 1, background.r, background.g, background.b);

    std::cout << "Информация успешно получена!" << std::endl;

    std::cout << "Хотите ли вы добавить контур окружности? " << std::endl;

    std::string agree;

    int outline;

    color outlines;

    std::cin >> agree;

    if (agree == "yeah" || agree == "yes" || agree == "yup" || agree == "Yes"
        || agree == "YES" || agree == "да" || agree == "ДА"
        || agree == "конечно" || agree == "конечно") {
        std::cout << "Хорошо, тогда введите размер контура и его цвет в "
                     "формате rgb: "
                  << std::endl;
        std::cin >> outline >> outlines.r >> outlines.g >> outlines.b;
        checker_error(1, 1, 1, outlines.r, outlines.g, outlines.b);

        std::cout << "Информация успешно получена!" << std::endl;

        circles.setOutlineThickness(outline);
        circles.setOutlineColor(Color(outlines.r, outlines.g, outlines.b));

    } else {
        std::cout << "\n...это был ваш выбор...\n" << std::endl;
    }

    star_printer();
    std::cout << "Периметр вашей окружености равен: "
              << float(2.0 * 3.14 * circle.radius) << std::endl;
    star_printer();
    std::cout << "Площадь окружности равна: "
              << float(3.14 * (circle.radius * circle.radius)) << std::endl;
    star_printer();
    std::cout << "\nНажмите enter для того, чтобы начать отрисовку "
                 "изображения"
              << std::endl;

    getchar();
    getchar();

    RenderWindow window(
            VideoMode(1500, 900), L"trpo_lab_voronov", Style::Titlebar);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear(Color(background.r, background.g, background.b));

        window.draw(circles);

        window.display();
    }
    return 0;
}

shape parser(std::string& wkt)
{
    std::istringstream iss(wkt);
    char tmp;
    std::string type;
    iss >> type >> tmp;

    if (type != "circle") {
        throw std::invalid_argument(
                "Ошибка: отстуствует ключевое слово \"circle\"");
    }

    if (tmp != '(') {
        throw std::invalid_argument("Ошибка: отсуствует символ '('");
    }

    shape circle;
    iss >> circle.cordinate.x >> circle.cordinate.y >> tmp;

    if (tmp != ',') {
        throw std::invalid_argument("Ошибка: отстуствует символ','");
    }

    iss >> circle.radius >> tmp;

    if (tmp != ',') {
        throw std::invalid_argument("Ошибка: отстуствует символ','");
    }

    iss >> circle.color.r >> circle.color.g >> circle.color.b;

    if (wkt[wkt.length() - 1] != ')') {
        throw std::invalid_argument("Ошибка: отстуствует символ ')'");
    }

    return circle;
}
void checker_error(
        int rad, int cord_x, int cord_y, int color_r, int color_g, int color_b)
{
    if (rad < 0) {
        program_stop(0);
    }
    if (cord_x < 0) {
        program_stop(1);
    }
    if (cord_y < 0) {
        program_stop(2);
    }
    if (color_r < 0 || color_g < 0 || color_b < 0) {
        program_stop(3);
    }
    if (color_r > 255 || color_g > 255 || color_b > 255) {
        program_stop(4);
    }
}

void program_stop(int type_error)
{
    switch (type_error) {
    case 0:
        std::cout << "Ошибка ввода: радиус не может быть меньше нуля"
                  << std::endl;
        exit(0);
        break;
    case 1:
        std::cout << "Ошибка ввода: координата X не может быть меньше нуля"
                  << std::endl;
        exit(0);
        break;
    case 2:
        std::cout << "Ошибка ввода: координата Y не может быть меньше нуля"
                  << std::endl;
        exit(0);
        break;
    case 3:
        std::cout << "Ошибка ввода: код цвета не может быть меньше нуля"
                  << std::endl;
        exit(0);
        break;
    case 4:
        std::cout << "Ошибка ввода: код цвета не может быть больше 255"
                  << std::endl;
        exit(0);
        break;
    }
}

void star_printer(void)
{
    for (int i = 0; i < 90; i++) {
        std::cout << '*';
    }
    std::cout << '\n';
}

void start_info(void)
{
    std::cout << "\nЗдравствуй, пользователь - это программа по рисованию "
                 "окружности!\nВот тебе небольшая сводка информации для "
                 "удобной работы с ней:\n1. Размер окна 1500 x 900\n2. Цвет "
                 "задается в формате rgb и не может иметь значение больше 255 "
                 "и меньше 0\n3. Фигура записывается в формате wkt\nпример: "
                 "circle (120.50 480.0, 250, 255 0 52)\n"
              << std::endl;

    std::cout << "Введите название фигуру, ее координаты, радиус и цвет : "
                 "______________________________________"
              << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b"
                 "\b\b\b\b\b\b\b\b";
}