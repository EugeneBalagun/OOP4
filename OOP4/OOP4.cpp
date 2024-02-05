#include <iostream>

#ifdef USE_STL
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#endif

template <typename T>
class MyVector {
private:
    T* array;
    size_t capacity;
    size_t size;
public:
    MyVector() : capacity(10), size(0) {
        array = new T[capacity];
    }

    ~MyVector() {
        delete[] array;
    }

    void push_back(const T& value) {
        if (size >= capacity) {
            capacity *= 2;
            T* newArray = new T[capacity];
            std::copy(array, array + size, newArray);
            delete[] array;
            array = newArray;
        }
        array[size++] = value;
    }

    T& operator[](size_t index) {
        if (index < size) {
            return array[index];
        }
        else {
            throw std::out_of_range("Index out of range");
        }
    }

    size_t getSize() const {
        return size;
    }

    void print() const {
        for (size_t i = 0; i < size; ++i) {
            std::cout << array[i] << " ";
        }
        std::cout << std::endl;
    }

#ifdef USE_STL
    void sortAscendingSTL() {
        std::vector<T> temp(array, array + size);
        std::sort(temp.begin(), temp.end());
        std::copy(temp.begin(), temp.end(), array);
    }

    void readFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open file: " << filename << std::endl;
            return;
        }

        T value;
        while (file >> value) {
            push_back(value);
        }

        file.close();
    }
#endif

    void sortAscending() {
        for (size_t i = 0; i < size - 1; ++i) {
            for (size_t j = i + 1; j < size; ++j) {
                if (array[i] > array[j]) {
                    T temp = array[i];
                    array[i] = array[j];
                    array[j] = temp;
                }
            }
        }
    }

    void replaceElement(size_t index, const T& value) {
        if (index < size) {
            array[index] = value;
        }
        else {
            throw std::out_of_range("Index out of range");
        }
    }
};

void printMenu() {
    std::cout << "\nMenu:\n";
    std::cout << "1. Add element to the end of the vector\n";
    std::cout << "2. Access element by index\n";
    std::cout << "3. Get the size of the vector\n";
    std::cout << "4. Print all elements of the vector\n";
#ifdef USE_STL
    std::cout << "5. Sort the vector using STL in ascending order\n";
#endif
    std::cout << "6. Sort the vector without using STL in ascending order\n";
#ifdef USE_STL
    std::cout << "7. Read vector from file\n";
#endif
    std::cout << "8. Replace element at index\n";
    std::cout << "9. Exit\n";
    std::cout << "Choose an option: ";
}

int main() {
    MyVector<int> vec;
    int choice;
    int element;
    int index;

    do {
        printMenu();
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Enter element to add: ";
            std::cin >> element;
            vec.push_back(element);
            std::cout << "Element added.\n";
            break;
        case 2:
            std::cout << "Enter index to access element: ";
            std::cin >> index;
            try {
                std::cout << "Element at index " << index << ": " << vec[index] << std::endl;
            }
            catch (const std::out_of_range&) {
                std::cerr << "Error: Index out of range" << std::endl;
            }
            break;
        case 3:
            std::cout << "Size of the vector: " << vec.getSize() << std::endl;
            break;
        case 4:
            std::cout << "Vector elements: ";
            vec.print();
            break;
#ifdef USE_STL
        case 5:
            std::cout << "Sorting the vector using STL in ascending order...\n";
            vec.sortAscendingSTL();
            std::cout << "Vector sorted.\n";
            break;
#endif
        case 6:
            std::cout << "Sorting the vector without using STL in ascending order...\n";
            vec.sortAscending();
            std::cout << "Vector sorted.\n";
            break;
#ifdef USE_STL
        case 7: {
            std::string filename;
            std::cout << "Enter the name of the file: ";
            std::cin >> filename;
            vec.readFromFile(filename);
            std::cout << "Vector read from file.\n";
            break;
        }
#endif
        case 8: {
            std::cout << "Enter index of the element to replace: ";
            std::cin >> index;
            std::cout << "Enter the new value: ";
            std::cin >> element;
            try {
                vec.replaceElement(index, element);
                std::cout << "Element replaced.\n";
            }
            catch (const std::out_of_range&) {
                std::cerr << "Error: Index out of range" << std::endl;
            }
            break;
        }
        case 9:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 9);

    return 0;
}
