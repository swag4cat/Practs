#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <numeric>
#include <map>


#include "RunTasks.h"

//----------------------------------------------------------------------------------------
void runTask1() {
    struct TipInfo {
        std::string employeeName;
        double rubles;
    };

    std::vector<TipInfo> employees = {
        {"Анна", 1500},
        {"Иван", 2300},
        {"Мария", 800},
        {"Павел", 1200}
    };

    double exchangeRate = 0.012;

    std::vector<std::pair<std::string, double>> tipsInUsd(employees.size());

    std::transform(employees.begin(), employees.end(), tipsInUsd.begin(),
                   [exchangeRate](const TipInfo& tip) {
                       return std::make_pair(tip.employeeName, tip.rubles * exchangeRate);
                   });

    std::cout << "Чаевые в долларах:\n";
    for (const auto& [name, usd] : tipsInUsd) {
        std::cout << name << ": " << std::fixed << std::setprecision(2) << usd << " $\n";
    }

    auto richest = std::max_element(employees.begin(), employees.end(),
                                    [](const TipInfo& a, const TipInfo& b) {
                                        return a.rubles < b.rubles;
                                    });

    if (richest != employees.end()) {
        std::cout << "\nСамый богатый сотрудник по чаевым: "
        << richest->employeeName << " (" << richest->rubles << " руб.)\n";
    }
}

//----------------------------------------------------------------------------------------
void runTask2() {
    struct Flight {
        std::string flightNumber;
        int duration;
        std::string city;
    };

    std::vector<Flight> flights = {
        {"SU101", 180, "Москва"},
        {"UT202", 95, "Казань"},
        {"AZ303", 240, "Сочи"},
        {"LH404", 120, "Москва"},
        {"DP505", 200, "Сочи"},
        {"FV606", 160, "Новосибирск"}
    };

    std::sort(flights.begin(), flights.end(),
              [](const Flight& a, const Flight& b) {
                  return a.duration < b.duration;
              });

    std::cout << "Рейсы по возрастанию длительности:\n";
    for (const auto& flight : flights) {
        std::cout << flight.flightNumber << " (" << flight.city << ") - "
        << flight.duration << " мин.\n";
    }

    std::cout << "\nГруппы рейсов в один и тот же город:\n";


    std::map<std::string, std::vector<std::string>> cityGroups;
    for (const auto& flight : flights) {
        cityGroups[flight.city].push_back(flight.flightNumber);
    }

    for (const auto& [city, flightNums] : cityGroups) {
        if (flightNums.size() > 1) {
            std::cout << "Город: " << city << " — рейсы: ";
            for (size_t i = 0; i < flightNums.size(); ++i) {
                std::cout << flightNums[i];
                if (i < flightNums.size() - 1) std::cout << ", ";
            }
            std::cout << "\n";
        }
    }
}
//----------------------------------------------------------------------------------------
void runTask3() {
    struct Employee {
        std::string name;
        int age;
    };

    std::vector<Employee> staff = {
        {"Алексей", 34},
        {"Виктор", 41},
        {"Наталья", 53},
        {"Елена", 29},
        {"Игорь", 58}
    };

    auto it = std::find_if(staff.begin(), staff.end(),
                           [](const Employee& emp) {
                               return emp.age > 50;
                           });

    if (it != staff.end()) {
        std::cout << "Первый сотрудник старше 50 лет: "
        << it->name << " (" << it->age << " лет)\n";
    } else {
        std::cout << "Сотрудников старше 50 лет не найдено.\n";
    }
}
//----------------------------------------------------------------------------------------
void runTask4() {
    struct Product {
        std::string name;
        double price;
    };

    std::vector<Product> products = {
        {"Смартфон", 15990},
        {"Наушники", 2990},
        {"Ноутбук", 48990},
        {"Клавиатура", 1990},
        {"Монитор", 10200}
    };

    auto it = std::partition(products.begin(), products.end(),
                             [](const Product& p) {
                                 return p.price > 10000;
                             });

    std::cout << "Премиальные предложения:\n";
    for (auto i = products.begin(); i != it; ++i) {
        std::cout << i->name << " - " << i->price << " руб.\n";
    }

    std::cout << "\nОбычные товары:\n";
    for (auto i = it; i != products.end(); ++i) {
        std::cout << i->name << " - " << i->price << " руб.\n";
    }
}
//----------------------------------------------------------------------------------------
void runTask5() {
    struct Order {
        int id;
        double amount;
    };

    std::vector<Order> orders = {
        {101, 12490.5},
        {102, 8720},
        {103, 15400.75},
        {104, 3330}
    };

    double total = std::accumulate(orders.begin(), orders.end(), 0.0,
                                   [](double sum, const Order& order) {
                                       return sum + order.amount;
                                   });

    std::cout << "Общая сумма заказов: " << std::fixed << std::setprecision(2)
    << total << " руб.\n";
}
//----------------------------------------------------------------------------------------
void runTask6() {
    struct Worker {
        std::string name;
        bool passedSafetyTraining;
    };

    std::vector<Worker> workers = {
        {"Андрей", true},
        {"Ольга", true},
        {"Дмитрий", true},
        {"Марина", false},
        {"Сергей", false}
    };

    bool allTrained = std::all_of(workers.begin(), workers.end(),
                                  [](const Worker& w) {
                                      return w.passedSafetyTraining;
                                  });

    if (allTrained) {
        std::cout << "Все сотрудники прошли инструктаж по технике безопасности.\n";
    } else {
        std::cout << "Некоторые сотрудники НЕ прошли инструктаж!\n";

        std::cout << "Список сотрудников без инструктажа:\n";
        std::for_each(workers.begin(), workers.end(),
                      [](const Worker& w) {
                          if (!w.passedSafetyTraining) {
                              std::cout << w.name << "\n";
                          }
                      });
    }

    int passedCount = std::count_if(workers.begin(), workers.end(),
                                    [](const Worker& w) {
                                        return w.passedSafetyTraining;
                                    });

    int failedCount = static_cast<int>(workers.size()) - passedCount;

    std::cout << "\nСтатистика:\n"
    << "Прошли инструктаж: " << passedCount << "\n"
    << "Не прошли: " << failedCount << "\n";
}
//----------------------------------------------------------------------------------------
void runTask7() {
    struct Student {
        std::string name;
        int mathGrade;
    };

    std::vector<Student> students = {
        {"Лена", 5},
        {"Игорь", 4},
        {"Таня", 5},
        {"Михаил", 3},
        {"Светлана", 5}
    };

    std::vector<Student> olympiadCandidates;

    std::copy_if(students.begin(), students.end(), std::back_inserter(olympiadCandidates),
                 [](const Student& s) {
                     return s.mathGrade == 5;
                 });

    std::cout << "Ученики, приглашённые на олимпиаду по математике:\n";
    for (const auto& s : olympiadCandidates) {
        std::cout << s.name << " (оценка: " << s.mathGrade << ")\n";
    }
}
//----------------------------------------------------------------------------------------
void runTask8() {
    struct User {
        std::string email;
        bool isSubscribed;
    };

    std::vector<User> users = {
        {"ivan@mail.com", true},
        {"olga@yandex.ru", false},
        {"petya@gmail.com", true},
        {"lena@rambler.ru", false}
    };

    users.erase(std::remove_if(users.begin(), users.end(),
                               [](const User& u) {
                                   return !u.isSubscribed;
                               }),
                users.end());

    std::cout << "Подписчики, оставшиеся в рассылке:\n";
    for (const auto& u : users) {
        std::cout << u.email << "\n";
    }
}
//----------------------------------------------------------------------------------------
void runTask9() {
    struct Vote {
        std::string username;
        std::string vote; // "like" или "dislike"
    };

    std::vector<Vote> votes = {
        {"alex", "like"},
        {"alex", "like"},
        {"alex", "dislike"},
        {"maria", "like"},
        {"maria", "like"},
        {"ivan", "dislike"},
        {"ivan", "dislike"},
        {"ivan", "dislike"}
    };

    auto end = std::unique(votes.begin(), votes.end(),
                           [](const Vote& a, const Vote& b) {
                               return a.username == b.username && a.vote == b.vote;
                           });

    votes.erase(end, votes.end());

    std::cout << "Очищенный список голосов:\n";
    for (const auto& v : votes) {
        std::cout << v.username << " - " << v.vote << "\n";
    }
}
//----------------------------------------------------------------------------------------
void runTask10() {
    struct InventoryItem {
        std::string name;
        bool checked;
    };

    std::vector<InventoryItem> items = {
        {"Ноутбук", false},
        {"Принтер", false},
        {"Монитор", false},
        {"Сканер", false}
    };

    std::for_each(items.begin(), items.end(),
                  [](InventoryItem& item) {
                      item.checked = true;
                      std::cout << "Товар \"" << item.name << "\" проверен.\n";
                  });
}
//----------------------------------------------------------------------------------------
