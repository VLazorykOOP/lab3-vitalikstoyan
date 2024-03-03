#include <iostream>
#include <stdexcept>
#include <print>
// стоян віталій 13варіант
class Vector {
private:
    double* elements;
    int size;// змінна яка визначає кількість елементів у векторі
    int state;//змінна яка використовується для визначення стану вектора

public:
    // Конструктор без параметрів
    Vector() : elements(new double[1]), size(1), state(0) {
        elements[0] = 0.0;
    }

    // Конструктор з одним параметром - розмір вектора
    Vector(int newSize) : elements(new double[newSize]), size(newSize), state(0) {
        for (int i = 0; i < size; ++i) {
            elements[i] = 0.0;
        }
    }

    // Конструктор із двома параметрами - розмір вектора та значення ініціалізації
    Vector(int newSize, double initValue) : elements(new double[newSize]), size(newSize), state(0) {
        for (int i = 0; i < size; ++i) {
            elements[i] = initValue;
        }
    }

    // Конструктор копій та операцію присвоєння
    Vector(const Vector& other) : elements(new double[other.size]), size(other.size), state(other.state) {
        for (int i = 0; i < size; ++i) {
            elements[i] = other.elements[i];
        }
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] elements;
            size = other.size;
            state = other.state;
            elements = new double[size];
            for (int i = 0; i < size; ++i) {
                elements[i] = other.elements[i];
            }
        }
        return *this;
    }

    // Деструктор
    ~Vector() {
        delete[] elements;
    }
     
    // Функція присвоює елементу масиву деяке значення
    void setElement(int index, double value = 0.0) {
        if (index < 0 || index >= size) {
            state = -1; // Помилка: виходить за межі масиву
            return;
        }
        elements[index] = value;
        state = 0;
    }

    // Функція одержує деякий елемент масиву
    double getElement(int index)  {
        if (index < 0 || index >= size) {
            state = -1; // Помилка: виходить за межі масиву
            return 0.0; // Значення за замовчуванням
        }
        state = 0;
        return elements[index];
    }

    // Функція друку
    void print() const {
        for (int i = 0; i < size; ++i) {
            std::cout << elements[i] << " ";
        }
        std::cout << std::endl;
    }

    // Функції додавання, віднімання, множення та ділення на скаляр типу double
    Vector add(const Vector& other) const {
        if (size != other.size) {
            throw std::invalid_argument("Розміри векторів не співпадають");
        }

        Vector result(size);
        for (int i = 0; i < size; ++i) {
            result.elements[i] = elements[i] + other.elements[i];
        }
        return result;
    }

    Vector subtract(const Vector& other) const {
        if (size != other.size) {
            throw std::invalid_argument("Розміри векторів не співпадають");
        }

        Vector result(size);
        for (int i = 0; i < size; ++i) {
            result.elements[i] = elements[i] - other.elements[i];
        }
        return result;
    }

    Vector multiply(double scalar) const {
        Vector result(size);
        for (int i = 0; i < size; ++i) {
            result.elements[i] = elements[i] * scalar;
        }
        return result;
    }

    Vector divide(double scalar) const {
        if (scalar == 0.0) {
            throw std::invalid_argument("Ділення на нуль неможливе");
        }

        Vector result(size);
        for (int i = 0; i < size; ++i) {
            result.elements[i] = elements[i] / scalar;
        }
        return result;
    }

    // Функції порівняння
    bool operator>(const Vector& other) const {
        if (size != other.size) {
            throw std::invalid_argument("Розміри векторів не співпадають");
        }

        for (int i = 0; i < size; ++i) {
            if (elements[i] <= other.elements[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator<(const Vector& other) const {
        if (size != other.size) {
            throw std::invalid_argument("Розміри векторів не співпадають");
        }

        for (int i = 0; i < size; ++i) {
            if (elements[i] >= other.elements[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator==(const Vector& other) const {
        if (size != other.size) {
            throw std::invalid_argument("Розміри векторів не співпадають");
        }

        for (int i = 0; i < size; ++i) {
            if (elements[i] != other.elements[i]) {
                return false;
            }
        }
        return true;
    }

    // Підрахунок числа об'єктів даного типу
    static int getCount() {
        return count;
    }

private:
    static int count; // Статична змінна для підрахунку числа об'єктів даного типу
};

int Vector::count = 0;

// Програма тестування
int main() {
    // Тестування конструкторів і функцій класу
    Vector v1; // Конструктор без параметрів
    v1.print(); // Виводимо вектор: 0.0

    Vector v2(5); // Конструктор з одним параметром
    v2.print(); // Виводимо вектор: 0.0 0.0 0.0 0.0 0.0

    Vector v3(3, 2.5); // Конструктор із двома параметрами
    v3.print(); // Виводимо вектор: 2.5 2.5 2.5

    Vector v4 = v3; // Конструктор копій
    v4.print(); // Виводимо вектор: 2.5 2.5 2.5

    Vector v5;
    v5 = v2; // Операція присвоєння
    v5.print(); // Виводимо вектор: 0.0 0.0 0.0 0.0 0.0

    // Тестування функцій для роботи з елементами вектору
    v2.setElement(2, 3.7);
    v2.print(); // Виводимо вектор: 0.0 0.0 3.7 0.0 0.0

    double value = v2.getElement(2);
    std::cout << "Елемент за індексом 2: " << value << std::endl; // Виводимо: 3.7

    // Тестування арифметичних операцій
    Vector sum = v2.add(v3);
    sum.print(); // Виводимо вектор: 2.5 2.5 6.2 0.0 0.0

    Vector diff = v2.subtract(v3);
    diff.print(); // Виводимо вектор: -2.5 -2.5 -3.7 0.0 0.0

    Vector product = v3.multiply(2.0);
    product.print(); // Виводимо вектор: 5.0 5.0 5.0

    Vector quotient = v3.divide(2.0);
    quotient.print(); // Виводимо вектор: 1.25 1.25 1.25

    // Тестування функцій порівняння
    if (v2 > v3) {
        std::cout << "v2 більший за v3" << std::endl;
    }
    else {
        std::cout << "v2 не більший за v3" << std::endl;
    }

    if (v2 < v3) {
        std::cout << "v2 менший за v3" << std::endl;
    }
    else {
        std::cout << "v2 не менший за v3" << std::endl;
    }

    if (v2 == v3) {
        std::cout << "v2 рівний v3" << std::endl;
    }
    else {
        std::cout << "v2 не рівний v3" << std::endl;
    }

    // Підрахунок числа об'єктів даного типу
    std::cout << "Кількість об'єктів класу Vector: " << Vector::getCount() << std::endl;

    return 0;
}
