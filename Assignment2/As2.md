# Q1

## Q 1.1

List items available in both “red” and “blue”.

### $\pi_{item}(\sigma_{color = red}(Types))\cap\pi_{item}(\sigma_{color = blue}(Types))$

## Q 1.2

List the name of the employees making at least as much as “Jane”. If there are several employees named ”Jane”, which Jane’s salary is used in this comparison in your answer?

### $\pi_{name}(\sigma_{salary\geq\pi_{salary}(\sigma_{name=Jane}(Employee))}(Employee))$

If there are several employees named ”Jane”, the highest  Jane’s salary is used in this comparison.

## Q 1.3

Find the largest salary paid to any employees.

### $n = \pi_{name,salary}(Employee)$

### $C = P(C(1\rarr n1,2\rarr s1,3\rarr n2,4\rarr s2),n*n)$

### Solution: 

### $\pi_{name}(Employee)-\pi_{n1}(\sigma_{s1<s2}(C))$

## Q 1.4

What departments sell every item with a red color.

### $\pi_{dept,item}(Sales)/\pi_{item}(\sigma_{color=red}(Types))$

## Q 1.5

What departments sell only items with a red color, in other words, what departments do not sell any item with a non-red color.

### $\pi_{dept}(Sales⋈Types)-\pi_{dept}(Sales⋈\sigma_{color\neq red}(Types))$







# Q2

## Q 2.1

List items available in both “red” and “blue”.

```sql
SELECT t.item
FROM Types t
WHERE t.color = 'blue'
INTERSECT
SELECT t.item
FROM Types t
WHERE t.color = 'red'
```

## Q 2.2

List the name of the employees making at least as much as “Jane”. If there are several employees named ”Jane”, which Jane’s salary is used in this comparison in your answer?

```sql
SELECT E1.name
FROM Employee E1, Employee E2
WHERE E1.salary >= E2.salary AND E2.name = 'Jane'
```

## Q 2.3

Find the largest salary paid to any employees.

```sql
SELECT MAX(salary)
FROM Employee;
```

## Q 2.4

What departments sell every item with a red color.

```sql
SELECT DISTINCT s.dept
FROM sales s
WHERE NOT EXISTS (
    SELECT t.item
    FROM types t
    WHERE t.color = 'red'
    EXCEPT
    SELECT s1.item
  	FROM sales s1
    WHERE s1.dept = s.dept
)
```

## Q 2.5

What departments sell only items with a red color, in other words, what departments do not sell any item with a non-red color.

```sql
SELECT DISTINCT s.dept
FROM sales s
EXCEPT
SELECT DISTINCT s.dept
FROM sales s
WHERE s.item IN (
  SELECT t.item 
  FROM types t 
  WHERE t.color != 'red'
)
```

# Q3

## Q 3.1

Express query 1 in SQL without using INTERSECT

```sql
SELECT t.item
FROM Types t
WHERE t.color = 'blue' AND t.item IN (
  SELECT t1.item 
  FROM Types t1 
  WHERE t1.color = 'red'
)
```

## Q 3.2

Express query 2 in SQL using nested query

```sql
SELECT E1.name
FROM Employee E1
WHERE E1.salary >=(
	SELECT MAX(E2.salary)
  From Employee E2
  WHERE E2.name = "Jane"
)
```







## Q 3.3

Express query 3 without using EXCEPT

```sql
SELECT e.salary
FROM Employee e
WHERE e.salary = (
	SELECT MAX(e2.salary)
	FROM Employee e2;
)
```

## Q 3.4

Express query 5 without using EXCEPT

```sql
SELECT DISTINCT s.dept
FROM sales s
WHERE s.dept NOT IN (
	SELECT s1.dept
	FROM sales s1
	WHERE s1.item IN (
  	SELECT t.item 
  	FROM types t 
  	WHERE t.color != 'red'
	)
)
```

