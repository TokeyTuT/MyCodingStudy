CREATE DATABASE IF NOT EXISTS test;
USE test;

CREATE TABLE IF NOT EXISTS Users(
    id INT PRIMARY KEY,
    username VARCHAR(50) DEFAULT ' ',
    password VARCHAR(50) DEFAULT ' ',
    age INT DEFAULT 0
);

desc Users;
ALTER TABLE Users MODIFY COLUMN id INT AUTO_INCREMENT;
ALTER TABLE Users MODIFY COLUMN username VARCHAR(50) NOT NULL UNIQUE ;
ALTER TABLE Users MODIFY COLUMN password VARCHAR(50) NOT NULL;

INSERT INTO Users (username, password, age) VALUES
('tokey','tokey0805',10),
('thr','thr20070805',10);

UPDATE Users SET username = 'tokeyNb',age = 20
where 1 = id;

SELECT * FROM Users;

# 备份数据表
CREATE TABLE copyed_Users SELECT * FROM Users;
SHOW TABLES;

INSERT INTO Users(username,password,age) VALUES('nihao','thr20070805',100);
INSERT INTO Users(username,password,age) VALUES('snhdfjs','thr20070805',50);

INSERT INTO copyed_Users SELECT * FROM Users where age > 50;

select * FROM copyed_Users;