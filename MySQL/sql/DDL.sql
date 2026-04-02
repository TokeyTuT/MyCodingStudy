DROP DATABASE IF EXISTS Student;

show DATABASES;

CREATE DATABASE test1;

USE test1;
CREATE TABLE Student(
    id INT PRIMARY KEY,
    name  VARCHAR(50),
    major VARCHAR(100),
    gpa DOUBLE,
    create_at  TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

show TABLES;

desc Student;

ALTER TABLE Student RENAME COLUMN name TO new_name;

ALTER TABLE Student ADD COLUMN name VARCHAR(50);

ALTER TABLE Student DROP COLUMN new_name;

DROP TABLE Student;

show TABLES;

