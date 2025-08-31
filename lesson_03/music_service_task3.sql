
--Задание 3
--Количество исполнителей в каждом жанре
select g.name, COUNT (ge.genre_id) from genre g
join genreexecutor ge on g.id = ge.genre_id
group by g.name
order by COUNT(ge.genre_id) DESC;

--Количество треков, вошедших в альбомы 2019–2020 годов
select al.name, al.year, COUNT (t.id) from album al
join track t on al.id = t.album_id 
where al.year between 2019 and 2020
group by al.name, al.year;

--Средняя продолжительность треков по каждому альбому
select al.name, AVG(t.duration) from album al
join track t on al.id = t.album_id
group by al.name
order by AVG(t.duration) DESC;

--Все исполнители, которые не выпустили альбомы в 2020 году
select ex.name from executor ex
join albumexecutor alex on ex.id = alex.executor_id
join album al on al.id = alex.album_id 
where al.year != 2020;

--Названия сборников, в которых присутствует исполнитель "Zodiac"
select col.name from collection col
join collectiontrack coltr on col.id = coltr.collection_id
join track t on t.id = coltr.track_id
join album al on al.id = t.album_id 
join albumexecutor alex on al.id = alex.album_id
join executor ex on ex.id = alex.executor_id
where ex.name LIKE 'Zodiac';

