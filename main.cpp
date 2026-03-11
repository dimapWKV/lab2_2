#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <string>
#include <sstream>
#include <windows.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::stringstream;

class Bell
{
    private:
    bool next_ding;

    public:
    Bell(): next_ding(true) {}

    void sound()
    {
        if (next_ding)
        {
            cout << "ding" << endl;

        } else
        {
            cout << "dong" << endl;
        }

        next_ding = !next_ding;
    };
};


class OddEvenSeparator
{
private:
    std::vector<int> numbers;

    void print_vector(const std::vector<int>& vec) {
        for (size_t i = 0; i < vec.size(); ++i) {
            std::cout << vec[i];
            if (i < vec.size() - 1) {
                std::cout << ", ";
            }
        }

    }

public:
    void add_number(int number) {
        numbers.push_back(number);
    }

    void even() {
        std::vector<int> even_numbers;

        for (int num : numbers) {
            if (num % 2 == 0) {
                even_numbers.push_back(num);
            }
        }

        print_vector(even_numbers);
    }

    void odd() {
        std::vector<int> odd_numbers;

        for (int num : numbers) {
            if (num % 2 != 0) {
                odd_numbers.push_back(num);
            }
        }

        print_vector(odd_numbers);
    }
};

class Table {
private:
    std::vector<int> data;
    int rows;
    int cols;

public:
    Table(int rows, int cols) : rows(rows), cols(cols) {
        data.resize(rows * cols, 0);
    }

    int get_value(int row, int col) const {
        return data[row * cols + col];
    }

    void set_value(int row, int col, int value) {
        data[row * cols + col] = value;
    }

    int n_rows() const {
        return rows;
    }

    int n_cols() const {
        return cols;
    }

    void print() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::cout << std::setw(4) << data[i * cols + j];
                if (j < cols - 1) {
                    std::cout << " ";
                }
            }
            std::cout << std::endl;
        }
    }

    double average() const {
        if (rows == 0 || cols == 0) {
            return 0.0;
        }

        long long sum = 0;
        for (int val : data) {
            sum += val;
        }

        return static_cast<double>(sum) / (rows * cols);
    }
};

class Complex {
private:
    double re;
    double im;

public:
    // Конструкторы
    Complex() : re(0), im(0) {}

    Complex(double x, double y) : re(x), im(y) {}

    // Сеттеры
    void set_re(double re) {
        this->re = re;
    }

    void set_im(double im) {
        this->im = im;
    }

    // Геттеры
    double get_re() const {
        return re;
    }

    double get_im() const {
        return im;
    }

    // Модуль комплексного числа
    double abs() const {
        return std::sqrt(re * re + im * im);
    }

    // Аргумент комплексного числа
    double arg() const {
        return std::atan2(im, re);
    }

    // Алгебраическая форма
    string to_string() const {
        stringstream ss;
        ss << std::fixed << std::setprecision(2);

        if (re == 0 && im == 0) {
            ss << "0";
        }
        else if (re == 0) {
            ss << im << "i";
        }
        else if (im == 0) {
            ss << re;
        }
        else {
            ss << re;
            ss << ((im > 0) ? " + " : " - ");
            ss << std::fabs(im) << "i";
        }

        return ss.str();
    }

    // Тригонометрическая форма
    string to_string_trig() const {
        stringstream ss;
        ss << std::fixed << std::setprecision(2);

        double r = abs();
        double phi = arg();

        if (r == 0) {
            ss << "0";
        }
        else {
            ss << r << " * (cos(" << phi << ") + i*sin(" << phi << "))";
        }

        return ss.str();
    }

    // Экспоненциальная форма
    string to_string_exp() const {
        stringstream ss;
        ss << std::fixed << std::setprecision(2);

        double r = abs();
        double phi = arg();

        if (r == 0) {
            ss << "0";
        }
        else {
            ss << r << " * e^(";
            ss << ((phi >= 0) ? "i*" : "-i*");
            ss << std::fabs(phi) << ")";
        }

        return ss.str();
    }

    // Арифметические операции
    Complex add(const Complex& z) const {
        return Complex(re + z.re, im + z.im);
    }

    Complex sub(const Complex& z) const {
        return Complex(re - z.re, im - z.im);
    }

    Complex mult(const Complex& z) const {
        return Complex(
            re * z.re - im * z.im,
            re * z.im + im * z.re
        );
    }

    Complex div(const Complex& z) const {
        double denominator = z.re * z.re + z.im * z.im;

        // Защита от деления на ноль
        if (denominator == 0) {
            cout << "Ошибка: деление на ноль!" << endl;
            return Complex(0, 0);
        }

        return Complex(
            (re * z.re + im * z.im) / denominator,
            (im * z.re - re * z.im) / denominator
        );
    }

    // Перегрузка операторов для удобства
    Complex operator+(const Complex& z) const {
        return add(z);
    }

    Complex operator-(const Complex& z) const {
        return sub(z);
    }

    Complex operator*(const Complex& z) const {
        return mult(z);
    }

    Complex operator/(const Complex& z) const {
        return div(z);
    }

    // Операторы сравнения
    bool operator==(const Complex& z) const {
        return (re == z.re && im == z.im);
    }

    bool operator!=(const Complex& z) const {
        return !(*this == z);
    }
};

class Stock
{
private:
    struct Box {
        int id;
        int w;
        int v;

        Box() : id(-1), w(0), v(0) {}
        Box(int id_, int w_, int v_) : id(id_), w(w_), v(v_) {}
    };

    Box* boxes;
    int capacity;
    int count;
    int next_id;

    void resize() {
        int new_capacity = (capacity == 0) ? 1 : capacity * 2;
        Box* new_boxes = new Box[new_capacity];

        for (int i = 0; i < count; i++) {
            new_boxes[i] = boxes[i];
        }

        delete[] boxes;
        boxes = new_boxes;
        capacity = new_capacity;
    }

    void remove_at(int index) {
        if (index < 0 || index >= count) return;

        for (int i = index; i < count - 1; i++) {
            boxes[i] = boxes[i + 1];
        }

        count--;
    }

public:
    Stock() : boxes(nullptr), capacity(0), count(0), next_id(0) {}

    void Add(int w, int v) {
        if (count >= capacity) {
            resize();
        }

        boxes[count] = Box(next_id, w, v);
        count++;
        next_id++;
    }

    int GetByW(int min_w) {
        if (count == 0) return -1;

        int best_index = -1;

        for (int i = 0; i < count; i++) {
            if (boxes[i].w >= min_w) {
                if (best_index == -1 || boxes[i].id < boxes[best_index].id) {
                    best_index = i;
                }
            }
        }

        if (best_index == -1) return -1;

        int found_id = boxes[best_index].id;
        remove_at(best_index);
        return found_id;
    }

    int GetByV(int min_v) {
        if (count == 0) return -1;

        int best_index = -1;

        for (int i = 0; i < count; i++) {
            if (boxes[i].v >= min_v) {
                if (best_index == -1 || boxes[i].id < boxes[best_index].id) {
                    best_index = i;
                }
            }
        }

        if (best_index == -1) return -1;

        int found_id = boxes[best_index].id;
        remove_at(best_index);
        return found_id;
    }

    void PrintStock() const {
        cout << "Текущее содержимое склада:\n";
        cout << "ID\tгрузоподъемность\tобъем\n";
        for (int i = 0; i < count; i++) {
            cout << boxes[i].id << "\t"
                 << boxes[i].w << "\t\t\t"
                 << boxes[i].v << "\n";
        }
        cout << "Всего коробок: " << count << "\n\n";
    }

};

void testStock() {
    Stock stock;

    //Добавляем коробки
    stock.Add(10, 20);  // ID 0
    cout << "Добавлена коробка ID 0: w=10, v=20\n";
    stock.Add(5, 30);   // ID 1
    cout << "Добавлена коробка ID 1: w=5, v=30\n";

    stock.PrintStock();

    // Тест поиска по грузоподъемности
    int test_w[] = {5, 8, 10, 12, 20};
    for (int w : test_w) {
        int id = stock.GetByW(w);
        if (id != -1) {
            cout << "Запрос: min_w=" << w << " -> выдана коробка ID " << id << "\n";
        } else {
            cout << "Запрос: min_w=" << w << " -> коробок нет\n";
        }
    }
    cout << "\n";
    stock.PrintStock();

    // Добавляем еще коробку
    stock.Add(12, 18);  // ID 5
    cout << "Добавлена коробка ID 5: w=12, v=18\n";

    stock.PrintStock();

    // Тест поиска по объему
    int test_v[] = {15, 20, 25, 30, 35};
    for (int v : test_v) {
        int id = stock.GetByV(v);
        if (id != -1) {
            cout << "Запрос: min_v=" << v << " -> выдана коробка ID " << id << "\n";
        } else {
            cout << "Запрос: min_v=" << v << " -> коробок нет\n";
        }
    }
    cout << "\n";
    stock.PrintStock();

    // Тест поиска при нескольких подходящих коробках
    cout << "Добавляем коробку с одинаковыми параметрами:\n";
    stock.Add(10, 30);  // ID 7
    cout << "Добавлена коробка ID 7: w=10, v=30\n";

    stock.PrintStock();

    cout << "Запрос: min_w=10 (должна быть выдана ID 7 - самая старая):\n";
    int id = stock.GetByW(10);
    cout << "Выдана коробка ID " << id << "\n\n";

    stock.PrintStock();

    // Тест на пустом складе
    Stock empty_stock;
    cout << "Запрос к пустому складу:\n";
    cout << "GetByW(10) -> " << empty_stock.GetByW(10) << "\n";
    cout << "GetByV(10) -> " << empty_stock.GetByV(10) << "\n\n";
}

int main()
{

    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    int choice;

    do {
        cout << "\n====== МЕНЮ ======\n";
        cout << "1. Тест Bell (звонок)\n";
        cout << "2. Тест OddEvenSeparator (четные/нечетные)\n";
        cout << "3. Тест Table (таблица)\n";
        cout << "4. Тест Complex (комплексные числа)\n";
        cout << "5. Тест Stock (склад)\n";
        cout << "0. Выход\n";
        cout << "Выберите пункт: ";
        cin >> choice;

        switch(choice) {
            case 1: {
                    Bell bell;

                    bell.sound();
                    bell.sound();
                    bell.sound();
                    bell.sound();
                    bell.sound();
                    bell.sound();
                    break;
            }

            case 2: {
                    OddEvenSeparator sep;
                    int count;
                    cout << "Введите количество чисел: ";
                    cin >> count;

                    cout << "Введите " << count << " чисел:\n";
                    for (int i = 0; i < count; i++) {
                        int num;
                        cin >> num;
                        sep.add_number(num);
                    }

                    cout << "Четные числа: ";
                    sep.even();

                    cout << "Нечетные числа: ";
                    sep.odd();
                    break;
            }

            case 3: {
                    int rows, cols;
                    cout << "Введите количество строк: ";
                    cin >> rows;
                    cout << "Введите количество столбцов: ";
                    cin >> cols;

                    Table table(rows, cols);

                    cout << "Введите " << rows * cols << " элементов таблицы:\n";
                    for (int i = 0; i < table.n_rows(); i++) {
                        for (int j = 0; j < table.n_cols(); j++) {
                            int value;
                            cin >> value;
                            table.set_value(i, j, value);
                        }
                    }

                    cout << "\nТаблица:\n";
                    table.print();

                    cout << "Среднее арифметическое: " << table.average() << "\n";

                    int r, c;
                    cout << "Введите индексы элемента для просмотра (строка столбец): ";
                    cin >> r >> c;
                    if (r >= 0 && r < table.n_rows() && c >= 0 && c < table.n_cols()) {
                        cout << "Элемент [" << r << "][" << c << "]: " << table.get_value(r, c) << "\n";
                    } else {
                        cout << "Неверные индексы!\n";
                    }
                    break;
            }

            case 4: {
                    double re1, im1, re2, im2;

                    cout << "Введите действительную и мнимую часть первого числа: ";
                    cin >> re1 >> im1;
                    Complex z1(re1, im1);

                    cout << "Введите действительную и мнимую часть второго числа: ";
                    cin >> re2 >> im2;
                    Complex z2(re2, im2);

                    cout << "\nz1 = " << z1.to_string() << "\n";
                    cout << "z2 = " << z2.to_string() << "\n\n";

                    cout << "Модуль z1: " << z1.abs() << "\n";
                    cout << "Аргумент z1: " << z1.arg() << " рад\n";
                    cout << "Модуль z2: " << z2.abs() << "\n";
                    cout << "Аргумент z2: " << z2.arg() << " рад\n\n";

                    cout << "Формы представления z1:\n";
                    cout << "  Алгебраическая: " << z1.to_string() << "\n";
                    cout << "  Тригонометрическая: " << z1.to_string_trig() << "\n";
                    cout << "  Экспоненциальная: " << z1.to_string_exp() << "\n\n";

                    cout << "Формы представления z2:\n";
                    cout << "  Алгебраическая: " << z2.to_string() << "\n";
                    cout << "  Тригонометрическая: " << z2.to_string_trig() << "\n";
                    cout << "  Экспоненциальная: " << z2.to_string_exp() << "\n\n";

                    cout << "Операции:\n";
                    cout << "z1 + z2 = " << (z1 + z2).to_string() << "\n";
                    cout << "z1 - z2 = " << (z1 - z2).to_string() << "\n";
                    cout << "z1 * z2 = " << (z1 * z2).to_string() << "\n";
                    cout << "z1 / z2 = " << (z1 / z2).to_string() << "\n";
                    break;
            }


            case 5: {
                testStock();
                break;
            }

            case 0: {
                cout << "Программа завершена.\n";
                break;
            }

            default: {
                cout << "Ошибка: неверный пункт меню!\n";
                break;
            }
        }

    } while (choice != 0);

    return 0;

}
