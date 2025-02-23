# Учебный репозиторий

### Рабочие ветки:
- Основы программной инженерии: https://github.com/Ms1black/educational-repository/tree/fundamentals-of-software-engineering
- Высокоуровневое программирование: https://github.com/Ms1black/educational-repository/tree/high-level-programming
- Ознакомительная практика: https://github.com/Ms1black/educational-repository/tree/introductory-practice
- Объектно-ориентированное программирование: https://github.com/Ms1black/educational-repository/tree/object-oriented-programming

----

### Старт

перед началом работы в репозитории в аудитории стоит убедиться, что на ПК настроен git config (его настраивают один раз):

`git config --list`

если нет, то прописываем в конфиге свой юзейрнейм и почту, !!!!! адрес должен совпадать с тем, на который зарегистрирован аккаунт в Гитхабе:

` git config --global user.name "ЮЗЕРНЕЙМ" `

` git config --global user.email ПОЧТА@example.com `

для работы с данным репозиторием локально в консоли переходим в нужную рабочую область и клонируем удаленный репозиторий:

`git clone https://github.com/Ms1black/educational-repository.git`

------
### Требования к коммитам

- Тип коммита должен быть только в ___нижнем регистре___ (feat, fix, refactor, docs, style, chore и т.д.)
- Должен использоваться ___present tense___ ("add feature" not "added feature")
- Должен использоваться ___imperative mood___ ("move cursor to..." not "moves cursor to...")

### Примеры имен коммитов

`init:` - используется для начала проекта/таска. Примеры: 

    init: start youtube-task
    init: start mentor-dashboard task

`feat:` - это реализованная новая функциональность из технического задания (добавил поддержку зумирования, добавил footer, добавил карточку продукта). Примеры:

    feat: add basic page layout
    feat: implement search box
    feat: implement request to youtube API
    feat: implement swipe for horizontal list
    feat: add additional navigation button
    feat: add banner
    feat: add social links
    feat: add physical security section
    feat: add real social icons

`fix:` - исправил ошибку в ранее реализованной функциональности. Примеры:

    fix: implement correct loading data from youtube
    fix: change layout for video items to fix bugs
    fix: relayout header for firefox
    fix: adjust social links for mobile
    fix: array parsing issue when multiple spaces were contained in string

`refactor:` - новой функциональности не добавлял/поведения не менял. Файлы в другие места положил, удалил, добавил. Улучшил алгоритм, без изменения функциональности. Примеры:

    refactor: change structure of the project
    refactor: rename vars for better readability

`docs:` - используется при работе с документацией/readme проекта. Примеры:

    docs: update readme with additional information
    docs: update description of run() method

`style:` - используется при изменениях стиля и оформления кода. Примеры:

    style: remove trailing white spaces
    style: add missing semi-colons
    style: format code with prettier

`chore:` - используется, когда не меняются исходные файлы и файлы тестов. Примеры:

    chore: add .editorconfig file for uniform code formatting  
    chore: rename environment variable file to .env.example


-------



### Вспомогательные команды


Просмотр истории ветки
: `git log`


Сортировка истории ветки по автору
: `git log --author="Имя автора"`

Получить последнюю версию удаленного репозитория
:`git pull` 

> [!CAUTION]
> Вызов команды `git pull` сотрёт все незафиксированные изменения!
