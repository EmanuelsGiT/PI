-- CREATES USER 'ras-7b' with password 'ras-7b'

CREATE USER 'ras-7b'@'localhost' IDENTIFIED BY 'ras-7b';
GRANT ALL PRIVILEGES ON * . * TO 'ras-7b'@'localhost';
FLUSH PRIVILEGES;
