-- CREATE DATABASE as3_354;

USE as3_354;

-- CREATE TABLE Employee (
--     eid CHAR(20) PRIMARY KEY,
--     name CHAR(20),
--     salary INT CHECK (salary >= 5000 AND salary <= 20000),
--     dept CHAR(20)
-- );

-- CREATE TABLE Sales (
--     dept CHAR(20),
--     item CHAR(20),
--     PRIMARY KEY (dept, item)
-- );

-- CREATE TABLE Types (
--     item CHAR(20),
--     color CHAR(20),
--     PRIMARY KEY (item, color)
-- );

-- INSERT INTO Employee (eid, name, salary, dept) VALUES
-- ('111', 'Jane', 8000, 'Household'),
-- ('222', 'Anderson', 8000, 'Toy'),
-- ('333', 'Morgan', 10000, 'Cosmetics'),
-- ('444', 'Lewis', 12000, 'Stationery'),
-- ('555', 'Nelson', 6000, 'Toy'),
-- ('666', 'Hoffman', 16000, 'Cosmetics');

-- INSERT INTO Sales (dept, item) VALUES
-- ('Stationery', 'pen'),
-- ('Cosmetics', 'lipstick'),
-- ('Toy', 'puzzle'),
-- ('Stationery', 'ink'),
-- ('Household', 'disk'),
-- ('Sports', 'skates'),
-- ('Toy', 'lipstick');

-- INSERT INTO Types (item, color) VALUES
-- ('pen', 'red'),
-- ('lipstick', 'red'),
-- ('pen', 'black'),
-- ('puzzle', 'black'),
-- ('ink', 'red'),
-- ('ink', 'blue');

-- -- 1.3.1
-- SELECT dept, MAX(salary)
-- FROM Employee
-- WHERE dept IN (
--         SELECT dept
--         FROM Sales
--         GROUP BY dept
--         HAVING COUNT(DISTINCT item) >= 2
--     )
-- GROUP BY dept;

-- -- 1.3.2
-- SELECT DISTINCT E.name
-- FROM Employee AS E
-- WHERE E.dept IN (
--     SELECT S.dept
--     FROM Sales AS S
--     WHERE S.item IN (
--         SELECT T.item
--         FROM Types AS T
--         WHERE T.color = 'Black'
--     )
-- );

-- -- 1.3.3
-- SELECT dept, AVG(salary)
-- FROM Employee
-- GROUP BY dept
-- HAVING AVG(salary) > (
--         SELECT AVG(salary)
--         FROM Employee
--         WHERE dept = 'Stationery'
--     );

-- -- 1.3.4
-- SELECT COUNT(DISTINCT dept)
-- FROM Employee
-- WHERE dept IN (SELECT dept
--                 FROM Employee
--                 GROUP BY dept
--                 HAVING AVG(salary) < (
--                         SELECT AVG(salary)
--                         FROM Employee
--                         WHERE dept = 'Stationery'
--                     ));

-- -- 1.3.5
-- SELECT dept
-- FROM Employee
-- GROUP BY dept
-- HAVING MIN(salary) >= 7000;

-- -- 1.3.6
-- SELECT dept
-- FROM Sales
-- WHERE item IN (
--     SELECT item
--     FROM Sales
--     WHERE dept = 'Cosmetics'
-- )
-- GROUP BY dept
-- HAVING COUNT(DISTINCT item) = (
--     SELECT COUNT(DISTINCT item)
--     FROM Sales
--     WHERE dept = 'Cosmetics'
-- );
