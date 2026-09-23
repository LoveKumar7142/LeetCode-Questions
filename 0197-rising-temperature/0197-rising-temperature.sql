# Write your MySQL query statement below
-- select w1.id AS id
-- from Weather w1
-- join Weather w2
--     on DATEDIFF(w1.recordDate,w2.recordDate) = 1
-- Where w1.temperature > w2.temperature


SELECT id
FROM Weather AS w1
WHERE temperature > (
    SELECT temperature 
    FROM Weather AS w2
    WHERE w2.recordDate = DATE_SUB(w1.recordDate, INTERVAL 1 DAY)
);