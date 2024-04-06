#include <iostream>
#include <stdexcept>

class Vector {
private:
    double* elements;  // Вказівник на масив елементів
    int size;          // Розмір вектора
    static int count;  // Статичне поле для підрахунку кількості створених об'єктів

public:
    // Конструктори та деструктор Vector
    Vector() : elements(new double[1]), size(1) {
        elements[0] = 0.0;
        count++;
    }

    Vector(int newSize) : elements(new double[newSize]), size(newSize) {
        for (int i = 0; i < size; ++i) {
            elements[i] = 0.0;
        }
        count++;
    }

    Vector(int newSize, double initValue) : elements(new double[newSize]), size(newSize) {
        for (int i = 0; i < size; ++i) {
            elements[i] = initValue;
        }
        count++;
    }

    Vector(const Vector& other) : elements(new double[other.size]), size(other.size) {
        for (int i = 0; i < size; ++i) {
            elements[i] = other.elements[i];
        }
        count++;
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] elements;
            size = other.size;
            elements = new double[size];
            for (int i = 0; i < size; ++i) {
                elements[i] = other.elements[i];
            }
        }
        return *this;
    }

    ~Vector() {
        delete[] elements;
        count--;
    }

    // Методи для роботи з елементами вектора
    void setElement(int index, double value = 0.0) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        elements[index] = value;
    }

    double getElement(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return elements[index];
    }

    void print() const {
        for (int i = 0; i < size; ++i) {
            std::cout << elements[i] << " ";
        }
        std::cout << std::endl;
    }

    // Методи для виконання операцій над векторами
    Vector add(const Vector& other) const {
        if (size != other.size) {
            throw std::invalid_argument("Vector sizes do not match");
        }

        Vector result(size);
        for (int i = 0; i < size; ++i) {
            result.elements[i] = elements[i] + other.elements[i];
        }
        return result;
    }

    Vector subtract(const Vector& other) const {
        if (size != other.size) {
            throw std::invalid_argument("Vector sizes do not match");
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
            throw std::invalid_argument("Division by zero");
        }

        Vector result(size);
        for (int i = 0; i < size; ++i) {
            result.elements[i] = elements[i] / scalar;
        }
        return result;
    }

    // Перевантаження операторів для порівняння векторів
    bool operator>(const Vector& other) const {
        if (size != other.size) {
            throw std::invalid_argument("Vector sizes do not match");
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
            throw std::invalid_argument("Vector sizes do not match");
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
            throw std::invalid_argument("Vector sizes do not match");
        }

        for (int i = 0; i < size; ++i) {
            if (elements[i] != other.elements[i]) {
                return false;
            }
        }
        return true;
    }

    // Статичний метод для отримання кількості створених об'єктів
    static int getCount() {
        return count;
    }
};

// Ініціалізація статичної змінної count
int Vector::count = 0;

int main() {
    // Створення об'єктів класу Vector з різними конструкторами
    Vector v1;
    v1.print();

    Vector v2(5);
    v2.print();

    Vector v3(3, 2.5);
    v3.print();

    Vector v4 = v3;
    v4.print();

    v2.setElement(2, 3.7);
    v2.print();

    double value = v2.getElement(2);
    std::cout << "Element at index 2: " << value << std::endl;

    // Виклик методів класу та обробка винятків за допомогою блоків try-catch
    try {
        Vector sum = v2.add(v3);
        sum.print();
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    try {
        Vector diff = v2.subtract(v3);
        diff.print();
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    try {
        Vector product = v3.multiply(2.0);
        product.print();
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    try {
        Vector quotient = v3.divide(2.0);
        quotient.print();
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    try {
        if (v2 > v3) {
            std::cout << "v2 is greater than v3" << std::endl;
        }
        else {
            std::cout << "v2 is not greater than v3" << std::endl;
        }
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    try {
        if (v2 < v3) {
            std::cout << "v2 is less than v3" << std::endl;
        }
        else {
            std::cout << "v2 is not less than v3" << std::endl;
        }
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    try {
        if (v2 == v3) {
            std::cout << "v2 is equal to v3" << std::endl;
        }
        else {
            std::cout << "v2 is not equal to v3" << std::endl;
        }
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // Виведення кількості створених об'єктів класу Vector
    std::cout << "Number of Vector objects: " << Vector::getCount() << std::endl;

    return 0;
}
