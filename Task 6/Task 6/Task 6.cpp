#include <iostream>
#include <stdexcept>

using namespace std;

class Vector {
private:
    int* elements;
    size_t size;

public:

    Vector() : elements(nullptr), size(0) {}

    Vector(const int* inputElements, size_t inputSize) : size(inputSize) {
        elements = new int[size];
        for (size_t i = 0; i < size; i++) {
            elements[i] = inputElements[i];
        }
    }

    ~Vector() {
        delete[] elements;
    }

    void pushBack(int element) {
        int* newElements = new int[size + 1];
        for (size_t i = 0; i < size; i++) {
            newElements[i] = elements[i];
        }
        newElements[size] = element;

        delete[] elements;
        elements = newElements;
        size++;
    }

    void pushFront(int element) {
        int* newElements = new int[size + 1];
        newElements[0] = element;
        for (size_t i = 0; i < size; i++) {
            newElements[i + 1] = elements[i];
        }

        delete[] elements;
        elements = newElements;
        size++;
    }

    void insertAt(size_t index, int element) {
        if (index > size) {
            throw out_of_range("Индекс вне диапазона");
        }

        int* newElements = new int[size + 1];
        for (size_t i = 0; i < index; i++) {
            newElements[i] = elements[i];
        }
        newElements[index] = element;
        for (size_t i = index; i < size; i++) {
            newElements[i + 1] = elements[i];
        }

        delete[] elements;
        elements = newElements;
        size++;
    }

    void removeAt(size_t index) {
        if (index >= size) {
            throw out_of_range("Индекс вне диапазона");
        }

        int* newElements = new int[size - 1];
        for (size_t i = 0; i < index; i++) {
            newElements[i] = elements[i];
        }
        for (size_t i = index + 1; i < size; i++) {
            newElements[i - 1] = elements[i];
        }

        delete[] elements;
        elements = newElements;
        size--;
    }

    bool operator==(const Vector& other) const {
        if (size != other.size) {
            return false;
        }

        for (size_t i = 0; i < size; i++) {
            if (elements[i] != other.elements[i]) {
                return false;
            }
        }

        return true;
    }

    Vector operator+(const Vector& other) const {
        if (size != other.size) {
            throw invalid_argument("Для добавления векторы должны иметь одинаковый размер.");
        }

        Vector result;
        result.size = size;
        result.elements = new int[size];

        for (size_t i = 0; i < size; i++) {
            result.elements[i] = elements[i] + other.elements[i];
        }

        return result;
    }

    Vector operator*(const Vector& other) const {
        if (size != other.size) {
            throw invalid_argument("Векторы должны иметь одинаковый размер для умножения");
        }

        Vector result;
        result.size = size;
        result.elements = new int[size];

        for (size_t i = 0; i < size; i++) {
            result.elements[i] = elements[i] * other.elements[i];
        }

        return result;
    }

    friend ostream& operator<<(ostream& os, const Vector& vector);
};

ostream& operator<<(ostream& os, const Vector& vector) {
    os << '[';
    for (size_t i = 0; i < vector.size; i++) {
        os << vector.elements[i];
        if (i < vector.size - 1) {
            os << ", ";
        }
    }
    os << ']';
    return os;
}

int main() {
    setlocale(LC_ALL, "rus");

    try {

        int arr1[] = { 1, 2, 3 };
        int arr2[] = { 4, 5, 6 };

        Vector v1(arr1, 3);
        Vector v2(arr2, 3);

        cout << "v1: " << v1 << endl;
        cout << "v2: " << v2 << endl;

        Vector v3 = v1 + v2;
        cout << "v1 + v2: " << v3 << endl;

        Vector v4 = v1 * v2;
        cout << "v1 * v2: " << v4 << endl;

        v1.pushBack(4);
        cout << "После добавления в начало: " << v1 << endl;

        v2.removeAt(1);
        cout << "После удаления в v2: " << v2 << endl;

        v3.insertAt(2, 8);
        cout << "После доваления в середину in v3: " << v3 << endl;

    }
    catch (const exception& e) {
        cerr << "Исключение: " << e.what() << endl;
    }

    return 0;
}