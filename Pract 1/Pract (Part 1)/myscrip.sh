#!/bin/bash

echo "Выберите вариант:"
echo "1. Календарь текущего месяца"
echo "2. Календарь для конкретного месяца и года"
read -p "Ваш выбор: " choice

if [ "$choice" == "1" ]; then
    cal
elif [ "$choice" == "2" ]; then
    read -p "Введите год: " year
    read -p "Введите месяц (1-12): " month
    cal $month $year
else
    echo "Неверный выбор"
fi
