# 1.14 Подсчёт слов в строке (wcount.c)
Составьте функцию wcount, вычисляющую количество слов в строке. Слово — это подстрока, не содержащая пробелов. Слова разделяются произвольным количеством пробелов. Кроме того, строка может начинаться и заканчиваться произвольным количеством пробелов. Объявление функции должно выглядеть как
```
int wcount(char *s)
{
        ...
}
```
Итоговую программу, содержащую как функцию wcount, так и функцию main, демонстрирующую работоспособность функции wcount, нужно назвать wcount.c. Строка должна считываться из стандартного потока ввода с помощью функции gets или fgets, минимальный размер буфера — $1000$ символов, включая концевой нуль.

Примечание. Функция fgets, в отличие от gets, добавляет \n в конец прочитанной строки.
