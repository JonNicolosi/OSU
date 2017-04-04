#1 Find all films with maximum length and minimum rental duration (compared to all other films). 
#In other words let L be the maximum film length, and let R be the minimum rental duration in the table film. You need to find all films with length L and rental duration R.
#You just need to return attribute film id for this query.

SELECT film_id
FROM  `film` 
WHERE rental_duration = ( 
SELECT MIN( rental_duration ) 
FROM film ) 
AND length = ( 
SELECT MAX( length ) 
FROM film )


#2 We want to find out how many actors have played in each film, so for each film return the film id, film title, and the number of actors who played in that film. Some films may have no actors, and your query does not need to return those films.

SELECT film.film_id, film.title, COUNT(film_actor.film_id) FROM film
INNER JOIN film_actor
ON film.film_id = film_actor.film_id
GROUP BY film.film_id

#3 Find the average length of films for each language. Your query should return every language even if there is no films in that language. language refers to attribute language_id (not attribute original_language_id)

SELECT film_id, language_id, AVG(length) FROM film
GROUP BY language_id

#4 We want to find out how many of each category of film KEVIN BLOOM has started in so return a table with category.name and the count
#of the number of films that KEVIN was in which were in that category order by the category name ascending (Your query should return every category even if KEVIN has been in no films in that category).

SELECT a.actor_id, a.first_name, a.last_name, c.name, COUNT(c.name)
FROM actor a 
INNER JOIN film_actor fa ON a.actor_id = fa.actor_id
INNER JOIN film f ON fa.film_id = f.film_id
INNER JOIN film_category fc ON f.film_id = fc.film_id
INNER JOIN category c ON fc.category_id=c.category_id
WHERE a.first_name = 'KEVIN' AND a.last_name = 'BLOOM'
ORDER by a.actor_id, c.name ASC

#5 Find the film title of all films which do not feature both SCARLETT DAMON and BEN HARRIS(so you will not list a film if both of these actors have played in that film, but if only one or none of these actors have played in a film, that film should be listed).
#Order the results by title, descending (use ORDER BY title DESC at the end of the query)
#Warning, this is a tricky one and while the syntax is all things you know, you have to think oustide
#the box a bit to figure out how to get a table that shows pairs of actors in movies


SELECT T1.title, T1.first_name, T1.last_name, T2.first_name, T2.last_name
FROM (

SELECT film.title, actor.first_name, actor.last_name
FROM actor
INNER JOIN film_actor ON actor.actor_id = film_actor.actor_id
INNER JOIN film ON film_actor.film_id = film.film_id
WHERE actor.first_name <>  'KIRSTEN'
AND actor.last_name <>  'PALTROW'
) AS T1
INNER JOIN (

SELECT film.title, actor.first_name, actor.last_name
FROM actor
INNER JOIN film_actor ON actor.actor_id = film_actor.actor_id
INNER JOIN film ON film_actor.film_id = film.film_id
WHERE actor.first_name <>  'WARREN'
AND actor.last_name <>  'NOLTE'
) AS T2 ON T1.title = T2.title
ORDER BY T1.title

