#include "Executor.hpp"
#include "Exceptions.hpp"
#include <iostream>

void Executor::addTask(std::unique_ptr<Task> task) {
    if (task) tasks.push_back(std::move(task));
}

void Executor::runAll(TaskLogger& logger) {
    std::cout << "--- Rozpoczynam wykonywanie zadan ---\n";
    
    for (const auto& task : tasks) {
        std::cout << "Wykonuje: " << task->name() << " ... ";
        try {
            double result = task->run();
            std::cout << "Wynik: " << result << '\n';
            logger.log(task->name(), true, 0);
        }
        catch (const MathException& e) {
            std::cerr << "Blad matematyczny! " << e.what() << '\n';
            logger.log(task->name(), false, 1);
        }
        catch (const FileException& e) {
            std::cerr << "Blad pliku! " << e.what() << '\n';
            logger.log(task->name(), false, 2);
        }
        catch (const FormatException& e) {
            std::cerr << "Blad formatu! " << e.what() << '\n';
            logger.log(task->name(), false, 3);
        }
        catch (const TaskException& e) {
            std::cerr << "Nieznany blad zadania! " << e.what() << '\n';
            logger.log(task->name(), false, 4);
        }
        catch (const std::exception& e) {
            std::cerr << "Krytyczny blad systemu! " << e.what() << '\n';
            logger.log(task->name(), false, 5);
        }
    }
}