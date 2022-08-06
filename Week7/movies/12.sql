SELECT title FROM movies WHERE id IN
(SELECT movie_id FROM stars WHERE person_id =
(SELECT id FROM people WHERE name = "Helena Bonham Carter") AND movie_id IN
(SELECT movie_id FROM stars WHERE person_id =
(SELECT id FROM people WHERE name = "Johnny Depp")));