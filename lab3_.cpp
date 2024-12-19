

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Document {
public:
    Document(const std::string& lineContent) : line(lineContent) {}
    std::string line;
};

std::vector<Document> readDataFromFile(const std::string& filename) {
    std::vector<Document> documents;
    try {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Файл не найден.");
        }
        std::string line;
        while (std::getline(file, line)) {
            documents.emplace_back(line);
        }
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
    return documents;
}

void viewData(const std::vector<Document>& documents) {
    for (size_t i = 0; i < documents.size(); ++i) {
        std::cout << (i + 1) << ": " << documents[i].line << std::endl;
    }
}

void editData(std::vector<Document>& documents) {
    viewData(documents);
    std::cout << "Введите номер строки для редактирования: ";
    int index;
    std::cin >> index;
    index--; // Convert to zero-based index
    if (index >= 0 && index < static_cast<int>(documents.size())) {
        std::string newLine;
        std::cout << "Введите новую строку: ";
        std::cin.ignore(); // Ignore the newline left in the input buffer
        std::getline(std::cin, newLine);
        documents[index].line = newLine;
    } else {
        std::cout << "Неверный номер строки." << std::endl;
    }
}

void calculateData(const std::vector<Document>& documents) {
    std::cout << "Количество строк: " << documents.size() << std::endl;
}

void saveDataToFile(const std::vector<Document>& documents, const std::string& newFilename) {
    std::ofstream file(newFilename);
    for (const auto& doc : documents) {
        file << doc.line << std::endl;
    }
    std::cout << "Данные сохранены в файл " << newFilename << "." << std::endl;
}

void mainMenu() {
    std::vector<Document> documents;
    while (true) {
        std::cout << "\n--- Меню ---" << std::endl;
        std::cout << "1. Чтение данных из файла" << std::endl;
        std::cout << "2. Просмотр данных" << std::endl;
        std::cout << "3. Корректировка данных" << std::endl;
        std::cout << "4. Вычисления" << std::endl;
        std::cout << "5. Сохранение данных в новый файл" << std::endl;
        std::cout << "6. Выход" << std::endl;

        std::cout << "Выберите действие (1-6): ";
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string filename;
                std::cout << "Введите имя файла для чтения: ";
                std::cin >> filename;
                documents = readDataFromFile(filename);
                break;
            }
            case 2:
                viewData(documents);
                break;
            case 3:
                editData(documents);
                break;
            case 4:
                calculateData(documents);
                break;
            case 5: {
                std::string newFilename;
                std::cout << "Введите имя нового файла для сохранения: ";
                std::cin >> newFilename;
                saveDataToFile(documents, newFilename);
                break;
            }
            case 6:
                std::cout << "Выход из программы." << std::endl;
                return;
            default:
                std::cout << "Неверный выбор. Попробуйте еще раз." << std::endl;
                break;
        }
    }
}

int main() {
    mainMenu();
    return 0;
}