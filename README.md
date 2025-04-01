Учебный проект до дисциплине "Объектное ориентированное программирование С++".
Программный код основан на некоторых идеях ООП, такие как инкапсуляции и абстракции. 
Система управления студентами, группами и дисциплинами
Описание проекта
Этот проект представляет собой систему управления студентами, учебными группами и дисциплинами, написанную на C++. Программа позволяет:

Создавать студентов с информацией о имени и возрасте

Объединять студентов в учебные группы

Назначать студентам дисциплины и выставлять оценки

Вычислять средние баллы как для отдельных студентов, так и для групп в целом

Структура классов
Класс Student
Представляет студента с основными характеристиками:

Имя и возраст

Учебная группа

Список изучаемых дисциплин

Основные методы:

GetAverageGrade() - вычисляет средний балл по всем дисциплинам

Show() - выводит полную информацию о студенте

Методы для добавления дисциплин и отображения оценок

Класс Discipline
Представляет учебную дисциплину:

Название дисциплины

Журнал оценок для каждого студента

Основные методы:

AddGrade() - добавление оценки студенту

GetAverageGrade() - вычисление среднего балла для конкретного студента

Методы для отображения списка студентов и их оценок

Класс Group
Представляет учебную группу:

Название группы

Список студентов в группе

Основные методы:

CalculateGroupAverage() - вычисляет средний балл группы

ShowStudents() - выводит список студентов группы

ShowGroupAverage() - отображает средний балл группы

Пример использования
В функции main() приведен пример работы с системой:

Создаются 4 студента

Создаются 2 учебные группы

Студенты распределяются по группам

Создаются 5 дисциплин

Студентам назначаются дисциплины

Выставляются оценки

Выводится информация о студентах, группах и дисциплинах
