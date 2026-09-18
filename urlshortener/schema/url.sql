CREATE TABLE url
(
    id       INT(11)      AUTO_INCREMENT NOT NULL,
    short    VARCHAR(255)                NOT NULL,
    expanded VARCHAR(255)                NOT NULL,
    PRIMARY KEY (id)
) DEFAULT CHARACTER SET utf8mb4
  COLLATE `utf8mb4_unicode_ci`
  ENGINE = InnoDB;
