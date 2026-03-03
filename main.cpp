#include <iostream>
#include <vector>
#include <iomanip>

using std::cin;
using std::cout;
using std::endl;


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
        std::cout << "[";
        for (size_t i = 0; i < vec.size(); ++i) {
            std::cout << vec[i];
            if (i < vec.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;
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

int main()
{
    OddEvenSeparator ods;
    ods.add_number(1);

    cout << "Четные числа: ";
    ods.even();

    cout << "Нечетные числа: ";
    ods.odd();

    return 0;
}
