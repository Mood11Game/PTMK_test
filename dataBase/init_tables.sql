-- Этот файл выполнять подключённым к ptmk_test_db

CREATE TABLE employees (
    id SERIAL PRIMARY KEY,
    last_name VARCHAR(100),
    first_name VARCHAR(100),
    middle_name VARCHAR(100),
    birth_date DATE,
    gender VARCHAR(10)
);

INSERT INTO employees (last_name, first_name, middle_name, birth_date, gender)
VALUES ('Ivanov', 'Petr', 'Sergeevich', '2000-05-14', 'Male');

SELECT * FROM employees;


