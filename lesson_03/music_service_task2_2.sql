--Задание 2
--запросы по выводу данных
select (name),(duration) from track
where duration = (select MAX(duration) from track);

select (name) from track
where duration >= 210;

select (name) from collection
where year between 2018 and 2020;

select (name) from executor
where name not like ('% %');

select (name) from track
where name like '%My%' or name like '%Мой%';