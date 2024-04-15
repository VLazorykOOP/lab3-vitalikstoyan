/1.3*Створити клас типу – прямокутник ( поля : висота, ширина, колір). У класі визначити
o конструктори ( не менше двох);
o функції-члени обчислення площі, периметру;
o функції-члени встановлення висоти, ширини, кольору, функції встановлення полів
класу повинні перевіряти коректність параметрів, що задаються;
o функції-члени що повертають значення полів;
o функцію друку.
Написати програму тестування всіх можливостей цього класу.*/

#include <iostream>
#include <string>

class Rectangle {
    double height; // Висота прямокутника
    double width; // Ширина прямокутника
    std::string color; // Колір прямокутника
    const int k;
    static int st;
public:
    // Конструктор за замовчуванням, ініціалізує всі поля нульовими значеннями
    Rectangle() : height(0), width(0), color("white"),k(1) {}

    // Конструктор, який приймає параметри висоти, ширини і кольору
    Rectangle(double h, double w, const std::string& c, int ki) : height(h), width(w), color(c), k(ki) {}

    // Методи для встановлення висоти, ширини та кольору з перевіркою на коректність параметрів
    void setHeight(double h) {
        if (h > 0) {
            height = h;
        }
        else {
            std::cerr << "Error: Height must be positive\n";
        }
    }

    void setWidth(double w) {
        if (w > 0) {
            width = w;
        }
        else {
            std::cerr << "Error: Width must be positive\n";
        }
    }

    void setColor(const std::string& c) {
        color = c;
    }

    // Методи для отримання значень висоти, ширини та кольору
    double getHeight() const {
        return height;
    }

    double getWidth() const {
        return width;
    }

    std::string getColor() const {
        return color;
    }

    // Методи для обчислення площі та периметру
    double getArea() const {
        return height * width;
    }

    double getPerimeter() const {
        return 2 * (height + width);
    }

int  Rectangle::st =1; 
    // Метод для виведення інформації про прямокутник
    void printInfo() const {
        std::cout << "Rectangle Info:\n";
        std::cout << "Height: " << height << std::endl;
        std::cout << "Width: " << width << std::endl;
        std::cout << "Color: " << color << std::endl;
        std::cout << "Area: " << getArea() << std::endl;
        std::cout << "Perimeter: " << getPerimeter() << std::endl;
    }
};

int main() {
    // Створення прямокутника з параметрами і виведення інформації про нього
    Rectangle rect1(5.0, 3.0, "blue");
    rect1.printInfo();

    // Створення прямокутника з використанням конструктора за замовчуванням
    Rectangle rect2;
    rect2.setHeight(8.0);
    rect2.setWidth(4.0);
    rect2.setColor("red");
    rect2.printInfo();

    return 0;
}

/*2.3Створити тип даних - клас вектор, який має вказівник на double, число елементів і змінну
стану. У класі визначити
o конструктор без параметрів( виділяє місце для одного елемента та інінціалізує
його в нуль);
o конструктор з одним параметром - розмір вектора( виділяє місце та інінціалізує
масив значенням нуль);
o конструктор із двома параметрами - розмір вектора та значення
ініціалізації(виділяє місце (значення перший аргумент) та інінціалізує значенням
другого аргументу);
o конструктор копій та операцію присвоєння; // !!!
o деструктор звільняє пам'ять;
o визначити функцію, яка присвоює елементу масиву деяке значення (параметр за
замовчуванням);
o функцію яка одержує деякий елемент масиву;
o визначити функції друку, додавання, віднімання, які здійснюють ці арифметичні
операції з даними цього класу, множення та ділення на скаляр типу double;
o визначити функції порівняння: більше, менше або рівно, які повертають true або
false.
У змінну стани встановлювати код помилки, коли не вистачає пам'яті, виходить за межі масиву.
Передбачити можливість підрахунку числа об'єктів даного типу. Написати програму тестування
всіх можливостей цього класу.*/

#include <iostream>

enum VectorState {
    OK,
    MEMORY_ERROR,
    INDEX_OUT_OF_BOUNDS
};

class Vector {
private:
    double* elements;
    int size;
    mutable VectorState state; // Додано mutable тут

public:
    // Конструктор без параметрів
    Vector() : size(1), state(OK) {
        elements = new double[size];
        if (!elements) state = MEMORY_ERROR;
        else elements[0] = 0.0;
    }

    // Конструктор з одним параметром - розмір вектора
    Vector(int s) : size(s), state(OK) {
        elements = new double[size];
        if (!elements) state = MEMORY_ERROR;
        else {
            for (int i = 0; i < size; ++i) {
                elements[i] = 0.0;
            }
        }
    }

    // Конструктор з двома параметрами - розмір вектора та значення ініціалізації
    Vector(int s, double initValue) : size(s), state(OK) {
        elements = new double[size];
        if (!elements) state = MEMORY_ERROR;
        else {
            for (int i = 0; i < size; ++i) {
                elements[i] = initValue;
            }
        }
    }

    // Конструктор копій
    Vector(const Vector& other) : size(other.size), state(other.state) {
        elements = new double[size];
        if (!elements) state = MEMORY_ERROR;
        else {
            for (int i = 0; i < size; ++i) {
                elements[i] = other.elements[i];
            }
        }
    }

    // Оператор присвоєння
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] elements;
            size = other.size;
            state = other.state;
            elements = new double[size];
            if (!elements) state = MEMORY_ERROR;
            else {
                for (int i = 0; i < size; ++i) {
                    elements[i] = other.elements[i];
                }
            }
        }
        return *this;
    }

    // Деструктор
    ~Vector() {
        delete[] elements;
    }

    // Функція, яка присвоює елементу масиву деяке значення (параметр за замовчуванням)
    void setElement(int index, double value = 0.0) {
        if (index >= 0 && index < size) {
            elements[index] = value;
        }
        else {
            state = INDEX_OUT_OF_BOUNDS;
        }
    }

    // Функція, яка повертає значення елементу масиву
    double getElement(int index) const {
        if (index >= 0 && index < size) {
            return elements[index];
        }
        else {
            state = INDEX_OUT_OF_BOUNDS;
            return 0.0; // Повертаємо 0.0 у випадку виходу за межі масиву
        }
    }

    // Функція друку
    void print() const {
        for (int i = 0; i < size; ++i) {
            std::cout << elements[i] << " ";
        }
        std::cout << std::endl;
    }

    // Функція додавання
    Vector add(const Vector& other) const {
        if (size != other.size) {
            std::cerr << "Cannot add vectors with different sizes!" << std::endl;
            return *this;
        }

        Vector result(size);
        for (int i = 0; i < size; ++i) {
            result.elements[i] = elements[i] + other.elements[i];
        }
        return result;
    }

    // Функція віднімання
    Vector subtract(const Vector& other) const {
        if (size != other.size) {
            std::cerr << "Cannot subtract vectors with different sizes!" << std::endl;
            return *this;
        }

        Vector result(size);
        for (int i = 0; i < size; ++i) {
            result.elements[i] = elements[i] - other.elements[i];
        }
        return result;
    }

    // Функція множення на скаляр
    Vector multiply(double scalar) const {
        Vector result(size);
        for (int i = 0; i < size; ++i) {
            result.elements[i] = elements[i] * scalar;
        }
        return result;
    }

    // Функція ділення на скаляр
    Vector divide(double scalar) const {
        if (scalar == 0) {
            std::cerr << "Division by zero!" << std::endl;
            return *this;
        }

        Vector result(size);
        for (int i = 0; i < size; ++i) {
            result.elements[i] = elements[i] / scalar;
        }
        return result;
    }

    // Функція порівняння
    bool operator==(const Vector& other) const {
        if (size != other.size) return false;

        for (int i = 0; i < size; ++i) {
            if (elements[i] != other.elements[i]) return false;
        }

        return true;
    }

    bool operator!=(const Vector& other) const {
        return !(*this == other);
    }

    bool operator<(const Vector& other) const {
        if (size != other.size) return false;

        for (int i = 0; i < size; ++i) {
            if (elements[i] >= other.elements[i]) return false;
        }

        return true;
    }

    bool operator>(const Vector& other) const {
        if (size != other.size) return false;

        for (int i = 0; i < size; ++i) {
            if (elements[i] <= other.elements[i]) return false;
        }

        return true;
    }

    bool operator<=(const Vector& other) const {
        return (*this < other || *this == other);
    }

    bool operator>=(const Vector& other) const {
        return (*this > other || *this == other);
    }
};
int main() {
    // Тут можна викликати функції для тестування класу Vector
    return 0;
}
    


