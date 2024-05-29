#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <vector>
#include <unordered_map>

/* Array98: Дан цілочисельний масив розміру N. Видалити з масиву всі однакові елементи, залишивши їх останні входження. */
/* Matrix33: Дана цілочисельна матриця розміру M × N. Знайти номер останньої з її рядків, що містять тільки парні числа. Якщо таких рядків немає, то вивести 0. */
/* Sort14: Метод сортування: Бульбашкова, Порядок: Зменшення, Тип елементів: Дійсний */

using namespace std;

void array98();
void get_nums();
bool checkfiles(const string &in, const string &out);
void searchPair(vector<int> &arr, const string &output);

void matrix33();
bool checkfile(const string &in);
void fillArray(const string &f_in, vector<vector<int>> &matrix, int rows, int cols);
void searchPairRows(vector<vector<int>> &matrix, int rows, int cols, const string &f_out);

void sort14();
void bubbleSort(vector<double> &arr);

int main() {
    srand(time(NULL));

    int choice = 0;

    while (choice != 4) {
        cout << "Choose the task! : "
             << "\n1. Array#98"
             << "\n2. Matrix#33"
             << "\n3. Sort#14"
             << "\n4. Exit" << endl;

        cin >> choice;

        switch (choice) {
            case 1: {
                array98(); // Задание array98
                break;
            }
            case 2: {
                matrix33(); // Задание matrix33
                break;
            }
            case 3: {
                sort14(); // Задание sort14
                break;
            }
            case 4: {
                cout << "Program is end!";
                break;
            }
            default: {
                cout << "Wrong one, try again";
            }
        }
    }
}

// Задание Array98
void array98() {
    get_nums();
}

void get_nums() {
    string filename_in = "array_in_98.txt";
    string filename_out = "array_out_98.txt";

    ifstream f;
    if (checkfiles(filename_in, filename_out)) {
        f.open(filename_in);

        int size;
        f >> size;

        vector<int> arr(size);
        for (int i = 0; i < size; ++i) {
            f >> arr[i];
        }

        for (int i = 0; i < size; ++i) {
            cout << "arr[" << i << "] = " << arr[i] << endl;
        }

        searchPair(arr, filename_out);

    } else {
        cout << "Помилка, файл не знайдено";
    }
}

bool checkfiles(const string &in, const string &out) {
    ifstream f_in(in);
    ofstream f_out(out);

    return f_in.is_open() && f_out.is_open();
}

void searchPair(vector<int> &arr, const string &filename_out) {
    unordered_map<int, int> last_occurrence;
    for (int i = 0; i < arr.size(); ++i) {
        last_occurrence[arr[i]] = i;
    }

    vector<int> result(arr.size(), 0);
    for (const auto &kv : last_occurrence) {
        result[kv.second] = kv.first;
    }

    ofstream outp(filename_out);
    if (!outp) {
        cerr << "Неможливо вiдкрити файл!" << endl;
        exit(1);
    } else {
        outp << "Новий масив: " << endl;
        for (int i = 0; i < result.size(); ++i) {
            if (result[i] != 0) {
                outp << result[i] << " ";
            }
        }
        outp << endl; // добавление перевода строки
    }
}
// Конец Array98

// Задание Matrix33
void matrix33() {
    string filename_in = "matrix_in_33.txt";
    string filename_out = "matrix_out_33.txt";

    ifstream f;
    if (checkfile(filename_in)) {
        f.open(filename_in);

        int rows, cols;
        f >> rows >> cols;

        if (rows > 20 || cols > 20) {
            cout << "Розмір рядків і колонок не може бути більше за 20" << endl;
            exit(0);
        } else {
            vector<vector<int>> matrix(rows, vector<int>(cols));
            fillArray(filename_in, matrix, rows, cols);
            searchPairRows(matrix, rows, cols, filename_out);
        }
    } else {
        cout << "Помилка, файл не знайдено";
    }
}

void fillArray(const string &f_in, vector<vector<int>> &matrix, int rows, int cols) {
    ifstream f(f_in);
    string out;
    getline(f, out); // Пропускаем первую строку с размерами
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            f >> matrix[i][j];
        }
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
}

bool checkfile(const string &in) {
    ifstream f_in(in);
    return f_in.is_open();
}

void searchPairRows(vector<vector<int>> &matrix, int rows, int cols, const string &f_out) {
    int last_row = 0;
    for (int i = 0; i < rows; ++i) {
        bool all_even = true;
        for (int j = 0; j < cols; ++j) {
            if (matrix[i][j] % 2 != 0) {
                all_even = false;
                break;
            }
        }
        if (all_even) {
            last_row = i + 1; // Переход к 1-индексации
        }
    }

    ofstream outp(f_out, ios::app);
    if (!outp) {
        cerr << "Неможливо вiдкрити файл!" << std::endl;
        exit(1);
    } else {
        if (last_row != 0) {
            outp << "Рядок #" << last_row << " має усі парні числа" << endl;
        } else {
            outp << "У цьому масиві немає жодного рядка з парними числами" << endl;
        }
    }
}

// Конец Matrix33

// Задание Sort14
void sort14() {
    string filename_in = "sort_in_14.txt";
    string filename_out = "sort_out_14.txt";

    ifstream f;
    if (checkfile(filename_in)) {
        f.open(filename_in);

        vector<double> arr;
        double num;
        while (f >> num) {
            arr.push_back(num);
        }

        for (double val : arr) {
            cout << val << " ";
        }
        cout << "\n";

        bubbleSort(arr);

        ofstream outp(filename_out);
        if (!outp) {
            cerr << "Неможливо вiдкрити файл!" << std::endl;
            exit(1);
        } else {
            outp << "Відсортований масив: ";
            for (double val : arr) {
                outp << val << " ";
            }
            outp << endl; // добавление перевода строки
        }
    } else {
        cout << "Помилка, файл не знайдено";
    }
}

void bubbleSort(vector<double> &arr) {
    int n = arr.size();
    bool swapped;
    for (int i = 0; i < n - 1; ++i) {
        swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] < arr[j + 1]) { // Сортировка по убыванию
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
        cout << "\nIteration: " << i + 1; // просмотр количества итераций
    }

    cout << "\n";
    for (double val : arr) {
        cout << val << " ";
    }
    cout << endl; // добавление перевода строки
}

// Конец Sort14

