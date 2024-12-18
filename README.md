# Задание
Разработать ассемблер и интерпретатор для учебной виртуальной машины (УВМ). Система команд УВМ представлена далее.

Для ассемблера необходимо разработать читаемое представление команд УВМ. Ассемблер принимает на вход файл с текстом исходной программы, путь к 142 которой задается из командной строки. Результатом работы ассемблера является бинарный файл в виде последовательности байт, путь к которому задается из командной строки. Дополнительный ключ командной строки задает путь к файлу-логу, в котором хранятся ассемблированные инструкции в духе списков “ключ=значение”, как в приведенных далее тестах.

Интерпретатор принимает на вход бинарный файл, выполняет команды УВМ и сохраняет в файле-результате значения из диапазона памяти УВМ. Диапазон также указывается из командной строки.

Форматом для файла-лога и файла-результата является csv.

Команды:

`MOV` - Копирует данные из одного операнда в другой. Один из операндов может быть указателем на память.
```
MOV R1, 5
MOV [0x1], R1
```


`PUSH` - Копирует данные из регистра, памяти или константы в стек.
```
PUSH -5
PUSH R1
```

`POP` - Извлекает данные из стека и записывает их в регистр или память.
```
POP R1
POP [0x1]
```

`XCHG` - Обменивает содержимое двух операндов. Один из них может быть указателем на память.
```
MOV R1, 10
MOV [0x1], 20
XCHG R1, [0x1]
```

`ADD` - Складывает два операнда и сохраняет результат в первом.
```
ADD R1, 5
ADD [R1], 10
```

`SUB` - Вычитает второй операнд из первого и сохраняет результат в первом.
```
SUB R1, 5
SUB [R1], -10
```

`INC` - Увеличивает значение в регистре или памяти на 1.

`DEC` - Уменьшает значение в регистре или памяти на 1.
```
INC R1
DEC R1
```

`MUL` - Умножает два операнда и сохраняет результат в первом.

`DIV` - Делит два операнда и сохраняет результат в первом.
```
MUL R1, 2
DIV R1, 2
```


`NEG` - смена знака
```
NEG R1
```

`ABS` - Заменяет на абсолютное знчение числа, записанном в регистре или памяти
```
MOV R0, -5
ABS R0
```

`AND`, `OR`, `XOR`, `NOT` - Выполняют логические операции побитно.
```
AND R0, R1
OR R0, R1
XOR R0, R1
NOT R0
```

# Структуа проекта
```
 ├── MyVirtualMachine
        ├── sources
          ├── ASM
            ├── AsmInterpreter.cpp
            └── AsmInterpreter.h
          ├── Logger
            ├── Logger.cpp
            └── Logger.h
          ├── Machine
            ├── Memory
              ├── Memory.cpp
              └── Memory.h
            ├── Processor
              ├── Processor.cpp
              └── Processor.h
            ├── Machine.cpp
            └── Machine.h
          ├── CommandStruct.h
          └── CommandStruct.cpp
        ├── CMakeLists.txt
        └── main.py
```

# Требования
 - OS: Windows x64
 - Компилятор: GCC
 - CMake 3.28+

# Сборка проекта
Сборка осущесвтляется как для обычного проекта CMake

# Пример использования
```
MyVirtualMachine <file_asm> <log_file> <res_file>
```
`<file_asm>` - путь к фалу с текстом исходной программы

`<log_file>` - путь к файлу логу (csv формат)

`<res_file>` - результат работы асемблера, представляющий из себя файл формата csv, содержащий байты команд

## Код исходной программы
```asm
mov R1, 3
push R1

mov R1, 4
push R1

pop R2
pop R3
add R3, R2
push R3

mov R1, 2
push R1

pop R2
pop R3
mul R3, R2
push R3

mov R1, 7
push R1

pop R2
pop R3
div R3, R2
push R3

mov ACC, R3
```

## Запуск программы
![изображение](https://github.com/user-attachments/assets/efee518a-f69f-46df-8f16-8ac3741c22e9)

## Результаты в файлах логах
### log.csv
```csv
Command,Operand1,Operand2
MOV,2,3
PUSH,2,0
MOV,2,4
PUSH,2,0
POP,3,0
POP,4,0
ADD,4,3
PUSH,4,0
MOV,2,2
PUSH,2,0
POP,3,0
POP,4,0
MUL,4,3
PUSH,4,0
MOV,2,7
PUSH,2,0
POP,3,0
POP,4,0
DIV,4,3
PUSH,4,0
MOV,0,4

```

### res.scv
```csv
10001010,00000001,00000010,00000000,00000000,00000000,00000011,00000000,00000000,00000000
01010000,00001111,00000010,00000000,00000000,00000000,00000000,00000000,00000000,00000000
10001010,00000001,00000010,00000000,00000000,00000000,00000100,00000000,00000000,00000000
01010000,00001111,00000010,00000000,00000000,00000000,00000000,00000000,00000000,00000000
01011000,00001111,00000011,00000000,00000000,00000000,00000000,00000000,00000000,00000000
01011000,00001111,00000100,00000000,00000000,00000000,00000000,00000000,00000000,00000000
00000001,00000000,00000100,00000000,00000000,00000000,00000011,00000000,00000000,00000000
01010000,00001111,00000100,00000000,00000000,00000000,00000000,00000000,00000000,00000000
10001010,00000001,00000010,00000000,00000000,00000000,00000010,00000000,00000000,00000000
01010000,00001111,00000010,00000000,00000000,00000000,00000000,00000000,00000000,00000000
01011000,00001111,00000011,00000000,00000000,00000000,00000000,00000000,00000000,00000000
01011000,00001111,00000100,00000000,00000000,00000000,00000000,00000000,00000000,00000000
11110110,00000000,00000100,00000000,00000000,00000000,00000011,00000000,00000000,00000000
01010000,00001111,00000100,00000000,00000000,00000000,00000000,00000000,00000000,00000000
10001010,00000001,00000010,00000000,00000000,00000000,00000111,00000000,00000000,00000000
01010000,00001111,00000010,00000000,00000000,00000000,00000000,00000000,00000000,00000000
01011000,00001111,00000011,00000000,00000000,00000000,00000000,00000000,00000000,00000000
01011000,00001111,00000100,00000000,00000000,00000000,00000000,00000000,00000000,00000000
11110111,00000000,00000100,00000000,00000000,00000000,00000011,00000000,00000000,00000000
01010000,00001111,00000100,00000000,00000000,00000000,00000000,00000000,00000000,00000000
10001010,00000000,00000000,00000000,00000000,00000000,00000100,00000000,00000000,00000000

```

# Тестирование
```asm
MOV R0, 5
MOV R1, -5
XCHG R0, R1

MOV [0x0], -1
ABS [0x0]

MOV [0x4], -2
NEG [0x4]

MOV[0x8], 2
INC[0x8]

MOV R2, 0x95
MOV R3, 0x6a
MOV R4, 0x95
MOV R5, 0

AND R3, R2
OR R4, R2
XOR R4, R2
NOT R5
```

Результат:
![изображение](https://github.com/user-attachments/assets/63482d5b-266b-4411-ba46-eb81334de5fd)

Экспериментальные результаты совпадают с теоретическими