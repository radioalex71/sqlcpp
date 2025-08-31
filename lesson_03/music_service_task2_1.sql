--Задание 2
--Запросы по заполнению основных таблиц
insert into executor(id,name)
VALUES(1,'Смысловые галлюцинации'),(2,'Imperial orchestra'),(3,'Zodiac'),(4,'Бобунец Сергей');

insert into genre(id,name)
VALUES(1,'Рок'),(2,'Классика'),(3,'Электронная музыка'),(4,'Поп Рок');

insert into album(id,name,year)
VALUES(1,'Безмолвие','2024'),(2,'Interstellar','2020'),(3,'New Zodiac','2015');

insert into track(id,name,duration,album_id)
VALUES(1,'Апрель',200,1),(2,'Interstellar',300,2),(3,'My air',400,3),(4,'Глубина',180,1),(5,'James_Bond',500,2),(6,'Electro',400,3);

insert into collection(id,name,year)
VALUES(1,'Mix 1','2019'),(2,'Mix 2','2020'),(3,'Mix 3','2024'),(4,'Mix 4','2025');

--запросы по заполнению промежуточных таблиц
insert into genreexecutor(genre_id,executor_id)
VALUES(1,1),(2,2),(3,3),(1,4);

insert into albumexecutor(album_id,executor_id)
VALUES(1,1),(2,2),(3,3),(1,4);

insert into collectiontrack(track_id,collection_id)
VALUES(6,1),(2,2),(6,2),(1,3),(6,3),(2,3),(1,4),(2,4),(3,4),(5,4),(6,4);

--очистка данных в таблицах
--delete from album;
--delete from executor;
--delete from genre;
--delete from track;
--delete from albumexecutor;
--delete from genreexecutor;
--delete from collectiontrack;
