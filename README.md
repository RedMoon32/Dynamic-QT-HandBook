# QT handbook

### Описание

Этот проект - реализация динамического справочника на QT.
В ТЗ требовалось сделать лишь отображение информации из классов ```Company``` 
и ```Country```, но я пошел шире и теперь любой инстанс класса наследуемый из класса
```TableAttributable``` будет показан в таблице справочника: в таблице будут показаны
все ```Q_PROPERTY``` значения данного класса которые могут быть конвертированы в ```QSTRING``` или являются ссылками на ```TableAttributable``` (в этом случае будет показан ```ключевой-аттрибут``` вложенного объекта - первый аттрибут имеющий в названии ```name``` -  т.е. для страны в колонке ``` CompanyCountry``` будет показан ```CountryName```).

Справочник поддерживает добавление, удаление, и изменение ячеек таблицы. В случае 
если ячейка является ссылка на ```TableAttributable``` - в качестве измененного объекта будет предложен выпадающий список с листом из названий primary-аттрибута объекта (свойство-имени).

Также справочник поддерживает конвертацию таблицы (массива ```TableAttributable*```в  html-файл), все поля всех ```Q_PROPERTY``` объект , являющиеся ссылками на ```TableAttributable``` будут показаны во всплывающм окне при клике на ряд

### Важно:
После build-a и перед неподсредственным запуском программы убедитесь что файл ***template.html*** лежит в build-директории, если его там нет скопируйте этот файл из папки этого проекта (хотя этот файл прописан в ```DISTFILES``` в конфигурации проекта в моем случае QT не копировал этот файл в build-папку)

 ### Использование
 
 Итак чтобы отобразить ваш собственный класс в справочнике необходимо:
 1) Отнаследовать его от ```TableAttributable``` (конструктор не принимающий параметры должен быть публичным)
 2) Передать лист с данными в методе ```MainWindow::setUpTable```: ```td = new TableDataModel((QList<TableAttributable*> &) YOUR_LIST, this);```
 3) Изменить добавление нового класса в справочнике на ваш в метод (так пришлось сделать из за того что ```Q_OBJECT``` не поддерживают темплейтинг) ``` MainWindow::createNewCountry```: ```td->insertRows<YOUR_CLASS>(0,1,QModelIndex());```
 4) Добавить в класс ```DataModel``` ```Q_PROPERTY``` с названием вашего класса, заканчивающимся на ```_List``` для динамического получение данных, например : ```Q_PROPERTY(const QList<Country*>& YOUR_CLASS_List READ  getCountryList)```

### Дополнительно
Местами код может показаться вам странным или кринжовым и я вас понимаю, но если начал писать полиморфный код то остановиться уже поздно))0)
### Скриншоты
(Если по каким то причинам вам не хочется запускать код)
![program](https://github.com/RedMoon32/Dynamic-QT-HandBook/blob/master/images/1.jpg)
![html](https://github.com/RedMoon32/Dynamic-QT-HandBook/blob/master/images/2.jpg)
