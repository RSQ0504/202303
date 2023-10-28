# Q1

## Q 1.1

List items available in both “red” and “blue”.

### $\pi_{item}(\sigma_{color = red}(Types)\cap\sigma_{color = blue}(Types))$

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

# Q1

## Q 1.1

List items available in both “red” and “blue”.

```sql
SELECT t.item
FROM Types t
WHERE t.color = 'blue' AND t.color = 'red'
```

## Q 1.2

List the name of the employees making at least as much as “Jane”. If there are several employees named ”Jane”, which Jane’s salary is used in this comparison in your answer?

```sql
SELECT E1.name
FROM Employee E1, Employee E2
WHERE E1.salary >= E2.salary AND E2.name = 'Jane'
```

## Q 1.3

Find the largest salary paid to any employees.

```sql
SELECT MAX(salary)
FROM Employee;
```

## Q 1.4

What departments sell every item with a red color.

```sql
SELECT s.dept
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

## Q 1.5

What departments sell only items with a red color, in other words, what departments do not sell any item with a non-red color.

```sql
SELECT s.dept
FROM sales s
EXCEPT
SELECT s.dept
FROM sales s
WHERE s.item NOT IN (
  SELECT t.item 
  FROM types t 
  WHERE t.color = 'red'
)
```

