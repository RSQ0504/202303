-- Q1.1
CREATE TABLE Doctors(
    did CHAR(10),
    PRIMARY KEY (did)
)
CREATE TABLE Patients(
    pid CHAR(10),
    PRIMARY KEY (pid)
)
CREATE TABLE Record(
    did CHAR(10),
    pid CHAR(10),
    info CHAR(10),
    data_of_attend DATE,
)

-- Q1.2
CREATE TABLE Doctors(
    did CHAR(10),
    PRIMARY KEY (did)
)
CREATE TABLE Patients(
    pid CHAR(10),
    PRIMARY KEY (pid)
)
CREATE TABLE Record(
    did CHAR(10),
    pid CHAR(10),
    info CHAR(10),
    data_of_attend DATE,
    PRIMARY KEY (pid),
)

-- Q1.3
CREATE TABLE Doctors(
    did CHAR(10),
    PRIMARY KEY (did)
)
CREATE TABLE Patients(
    pid CHAR(10),
    PRIMARY KEY (pid)
)
CREATE TABLE Record(
    did CHAR(10) NOT NULL,
    pid CHAR(10),
    info CHAR(10),
    data_of_attend DATE,

    PRIMARY KEY (pid),
)

-- Q 1.4
CREATE TABLE Doctors(
    did CHAR(10),
    PRIMARY KEY (did)
)
CREATE TABLE Patients(
    pid CHAR(10),
    PRIMARY KEY (pid)
)
CREATE TABLE Record(
    did CHAR(10),
    pid CHAR(10) NOT NULL,
    info CHAR(10),
    data_of_attend DATE,
    PRIMARY KEY (pid),
    FOREIGN KEY (did) REFERENCES Doctors
)

-- Q 1.5
CREATE TABLE Record_Merge_Doctor(
    did CHAR(10),
    pid CHAR(10) Not NULL,
    info CHAR(10),
    data_of_attend DATE,
    PRIMARY KEY (did),
)
CREATE TABLE Patients(
    pid CHAR(10),
    PRIMARY KEY (pid)
)

-- Q 1.6
CREATE TABLE Doctors(
    did CHAR(10),
    PRIMARY KEY (did)
)
CREATE TABLE Patients(
    pid CHAR(10),
    Name CHAR(10),
    Age CHAR(10),
    Address CHAR(10),

    PRIMARY KEY (pid),
    UNIQUE (Name,Address),
    UNIQUE (Name,Age)
)
CREATE TABLE Record(
    did CHAR(10),
    pid CHAR(10),
    info CHAR(10),
    data_of_attend DATE,
)