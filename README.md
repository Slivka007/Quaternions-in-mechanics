# Решение задач механики на C++ 
- Поиск собственных значений тензора инерции двумя способами
- Поиск собственного базиса тензора инерции твердого тела
- Диагонализирование тензораи инерции твёрдого тела
- Расчёт положения твёрдого тела в случае Эйлера из начальных параметров
- Реализация метода Рунге-Кутты четвёртого порядка
- Реализация мотода Якоби для поиска собственных векторов и собственных значений матрицы
- Реализация класса геометрических векторов
- Реализация класса кватернионов
- Реализация поворота вектора вокруг оси с помощью кватернионов

## Содержание
- [Полезные ссылки](#полезные-ссылки)
- [Установка](#установка)
- [Комментарии к коду](#комментарии-к-коду)
- [Контакты](#контакты)

## Полезные ссылки
- [Тензор инерции](https://ru.wikipedia.org/wiki/Тензор_инерции)
- [Уравнения Эйлера](https://ru.wikipedia.org/wiki/Уравнения_Эйлера)
- [Линейная алгебра. Э.Б.Винберг](https://mathprofi.com/uploads/files/2581_f_41_e.b.vinberg-kurs-algebry-2-e-izd.pdf)
- [Поворот вектора с помощью кватернионов](https://habr.com/ru/articles/255005/)
- [Метод Рунге-Кутты](https://www.codesansar.com/numerical-methods/runge-kutta-rk-fourth-order-using-cpp-output.htm)
- [Метод Якоби](http://prografix.narod.ru/rus_jacobi.html#:~:text=Идея%20метода%20Якоби%20состоит%20в,приводит%20к%20сходимости%20процесса%20диагональности.)

## Установка
Для запуска необходим установленный Cline иди g++.

Для установки необходимо клонировать репозиторий
```sh
$ git clone git@github.com:Slivka007/Quaternions-in-mechanics.git
```
И запустить в через командную строку или среду для программирования на c++.

## Комментарии к коду 
### RigidBody.hpp
В этом файле реализован класс твёрдого тела. Реализовам метод Рунге-Кутты для численного дифференцирования уравнений Эйлера. 
### math.hpp
В этом файле находится класс матриц 3 на 3 для которых реализован метод Якоби для вычисления собственных значений и векторов матрицы. Также реализована другая функция поиска собственных значений матрицы для оптимизации решений в вырожденных случая, когда метод Якоби долго работает. 
### quaternions.hpp
В этом файле релизован класс кватернионов с их полной алгеброй. Также реализованы методы для поворота векторов с помощью кватернионов. 
### vector.hpp
В этом файле релизован класс геометрических векторов с их основными операциями. 

## Контакты
Пишите мне в телеграмме @Slivka_physics


