./monetdbd create DBFARM
./monetdbd start DBFARM
./monetdb create test
./monetdb set nthreads=1 test
./monetdb release test
rlwrap ./mclient -u monetdb -d test
./monetdbd stop DBFARM

CREATE TABLE percolator_column (a1 real, a2 real, a3 real, a4 real, a5 real, a6 real, a7 real, a8 real, a9 real, a10 real, a11 real, a12 real, a13 real, a14 real, a15 real, b real);
COPY 87322 RECORDS INTO percolator_column from '/home/kkara/Projects/DataGenerator/percolator_column.tbl' USING DELIMITERS '|';
COPY 100 RECORDS INTO percolator_column from '/home/kkara/Projects/DataGenerator/percolator_column.tbl' USING DELIMITERS '|';

CREATE TABLE percolator_row (ab real);
COPY 1397152 RECORDS INTO percolator_row from '/home/kkara/Projects/DataGenerator/percolator_row.tbl' USING DELIMITERS '|';
COPY 1600 RECORDS INTO percolator_row from '/home/kkara/Projects/DataGenerator/percolator_row.tbl' USING DELIMITERS '|';

select sgdfpga_column(4, 18, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, b) from percolator_column;
select sgdsw_column(4, 18, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, b) from percolator_column;

select sgdfpga_row(15, 4, 18, ab) from percolator_row;
select sgdsw_row(15, 4, 18, ab) from percolator_row;

CREATE TABLE employee (id integer, age integer, salary integer);
COPY 80000 RECORDS INTO employee from '/home/kkara/Projects/DataGenerator/employee.tbl' USING DELIMITERS '|';

select count(*) from (select hwselection(age, '=', 26, 26) from employee) as sub;
select count(*) from employee where age = 26;