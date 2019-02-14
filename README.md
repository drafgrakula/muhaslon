﻿Проект "Муха-слон"

Создан в Eclipse Mars v.4.5.1, ОС Linux Mint v.17.2, GCC v.4.9.3
Юнит-тесты разработаны с помощью google tests
Автор: Владимир Потёмкин


Формат использования: 

	MuhaSlon <файл с исходным и конечным словами> <файл со словарём>

файлы должны быть в кодировке UTF-8 со стандартным разделителем строк Unix.


Описание.

В проекте использован шаблон "Компоновщик": слова из файла словаря организуются в иерархию в виде многоуровневого дерева с неограниченным количеством ветвей, в котором коренной узел представляет собой исходное слово, его дети первого уровня - слова из словаря, отличающиеся от коренного на одну букву и т.д.
Алгоритм поиска цепочки от исходного слова к конечному сводится к построению дерева с одновременным сравнением на равенство какого-либо из детей конечному слову. Построение дерева (и поиск) идет в горизонтальном направлении. То есть, вначале создаются все дети коренного узла, добавляются в очередь поиска, и среди них идёт поиск на конечное слово. Дальше создаются дети этих детей, все они добавляются в очередь и поиск идёт дальше среди них, и т.д., до тех пор, пока не будут перебраны все возможные варианты преобразования слов.
В отличие от вертикального создания дерева, горизонтальное всегда находит самую короткую цепочку в случае, если существуют несколько возможных вариантов. Алгоритм оптимизирован таким образом, что последний уровень иерархии (с конечным словом) не проверяется целиком. Это возможно благодаря тому, что создаваемый узел сразу проверяется на возможность появления у него в детях в следующем уровне искомого конечного слова.
Механизм перебора детей реализован в цикле (в отличие от рекурсии). Небольшое усложнение кода позволит избавиться от вероятных сбоев при обработке больших словарей, а также, в условиях нехватки ресурсов.
При нахождении конечного слова построение дерева прекращается. При небольшой модификации алгоритма можно добиться полного построения дерева и вывод всех возможных вариантов преобразования исходного слова в конечное.

