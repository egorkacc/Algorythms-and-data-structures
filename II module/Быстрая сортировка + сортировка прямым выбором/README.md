# 2.8 Быстрая сортировка + сортировка прямым выбором (quicksort.c)
Составьте программу quicksort.c, осуществляющую сортировку массива целых чисел в порядке возрастания.

В программе должен быть реализован алгоритм быстрой сортировки, рекурсивную функцию которого нужно модифицировать таким образом, чтобы, во-первых, для последовательностей длиной меньше $m$ выполнялась сортировка прямым выбором, а во-вторых, глубина стека вызовов была равна $O\left(\lg n\right)$, где $n$ — размер массива.

Программа должна считывать со стандартного потока ввода размер массива $n$, число $m$ и значения элементов массива. В стандартный поток вывода должны выводиться элементы отсортированного массива.
