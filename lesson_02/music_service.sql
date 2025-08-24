create table if not exists genre (
id SERIAL primary key,
name VARCHAR(100) not null
);

create table if not exists executor (
id SERIAL primary key,
name VARCHAR(120) not null
);

create table if not exists album (
id SERIAL primary key,
name VARCHAR(120) not null,
year INTEGER not NULL
);

create table if not exists track (
id SERIAL primary key,
name VARCHAR(120) not null,
duration INTEGER not null,
album_id INTEGER references album(id)
);

create table if not exists GENREEXECUTOR (
genre_id INTEGER references genre(id),
executor_id INTEGER references executor(id),
constraint pk primary key (genre_id,executor_id)
);

create table if not exists ALBUMEXECUTOR (
album_id INTEGER references album(id),
executor_id INTEGER references executor(id),
constraint alexcut_pk primary key (album_id,executor_id)
);

create table if not exists collection (
id SERIAL primary key,
name VARCHAR(120) not null,
year INTEGER not NULL
);

create table if not exists COLLECTIONTRACK (
track_id INTEGER references track(id),
collection_id INTEGER references collection(id),
constraint coltrack_pk primary key (track_id,collection_id)
);
