-- CREATE DATABASE as3_354;

-- USE as3_354;

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

-- -- 3.1
-- SELECT dept, MAX(salary) AS max_salary
-- FROM Employee
-- WHERE dept IN (
--         SELECT dept
--         FROM Sales
--         GROUP BY dept
--         HAVING COUNT(DISTINCT item) >= 2
--     )
-- GROUP BY dept;

-- -- 3.2
-- SELECT DISTINCT E.name
-- FROM Employee AS E
-- JOIN Sales AS S ON E.dept = S.dept
-- JOIN Types AS T ON S.item = T.item
-- WHERE T.color = 'Black';

-- -- 3.3
-- SELECT dept, AVG(salary)
-- FROM Employee
-- GROUP BY dept
-- HAVING AVG(salary) > (
--         SELECT AVG(salary)
--         FROM Employee
--         WHERE dept = 'Stationery'
--     );