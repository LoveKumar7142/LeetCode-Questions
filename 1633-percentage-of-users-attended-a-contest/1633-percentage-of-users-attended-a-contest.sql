# Write your MySQL query statement below
-- SELECT r.contest_id,
--     ROUND(
--         (COUNT(r.user_id)*100/(SELECT COUNT(*) FROM Users)),2
--     ) AS percentage
-- FROM Users AS u
-- LEFT JOIN Register AS r
-- ON u.user_id = r.user_id
-- GROUP BY r.contest_id
-- HAVING percentage >0
-- ORDER BY percentage DESC , r.contest_id ASC;

SELECT 
    contest_id,
    ROUND(
        COUNT(user_id) * 100.0 / (SELECT COUNT(*) FROM Users),
        2
    ) AS percentage
FROM Register
GROUP BY contest_id
ORDER BY percentage DESC, contest_id ASC;
