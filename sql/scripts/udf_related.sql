./monetdbd create DBFARM
./monetdbd start DBFARM
./monetdb create sig
./monetdb set nthreads=1 sig
./monetdb release sig
rlwrap ./mclient -u monetdb -d sig
./monetdbd stop DBFARM

-- Percolator datasets
CREATE TABLE Proteins_Column (Bias real, deltLCn real, deltCn real, RefactoredXCorr real, NegLog10PValue real, PepLen real, Charge1 real, Charge2 real, Charge3 real, enzN real, enzC real, enzInt real, lnNumDSP real, dM real, absdM real, Label real);
COPY 87322 RECORDS INTO Proteins_Column FROM '/home/kkara/Projects/doppiodb/DATASETS/percolator_column.tbl' USING DELIMITERS '|';
COPY 30 RECORDS INTO Proteins_Column FROM '/home/kkara/Projects/doppiodb/DATASETS/percolator_column.tbl' USING DELIMITERS '|';

COPY 87322 RECORDS INTO Proteins_Column FROM '/media/storage/doppiodb/DATASETS/percolator_column.tbl' USING DELIMITERS '|';
COPY 30 RECORDS INTO Proteins_Column FROM '/media/storage/doppiodb/DATASETS/percolator_column.tbl' USING DELIMITERS '|';

select sgdfpga_column(15, 2, 18, 1, Bias, deltLCn, deltCn, RefactoredXCorr, NegLog10PValue, PepLen, Charge1, Charge2, Charge3, enzN, enzC, enzInt, lnNumDSP, dM, absdM, Label) FROM Proteins_Column;
select sgdsw_column(15, 10, 18, Bias, deltLCn, deltCn, RefactoredXCorr, NegLog10PValue, PepLen, Charge1, Charge2, Charge3, enzN, enzC, enzInt, lnNumDSP, dM, absdM, Label) FROM Proteins_Column;

select sgdfpga_column(15, 2, 18, 1, Bias, deltLCn, deltCn, RefactoredXCorr, NegLog10PValue, PepLen, Charge1, Charge2, Charge3, enzN, enzC, enzInt, lnNumDSP, dM, absdM, Label) FROM Proteins_Column;

DELETE FROM Proteins_Column;

CREATE TABLE Proteins_Row (allFeatures real);
COPY 1397152 RECORDS INTO Proteins_Row FROM '/home/kkara/Projects/doppiodb/DATASETS/percolator_row.tbl' USING DELIMITERS '|';
COPY 1600 RECORDS INTO Proteins_Row FROM '/home/kkara/Projects/doppiodb/DATASETS/percolator_row.tbl' USING DELIMITERS '|';

COPY 1397152 RECORDS INTO Proteins_Row FROM '/media/storage/doppiodb/DATASETS/percolator_row.tbl' USING DELIMITERS '|';
COPY 1600 RECORDS INTO Proteins_Row FROM '/media/storage/doppiodb/DATASETS/percolator_row.tbl' USING DELIMITERS '|';

SELECT sgdfpga_row(15, 50, 18, allFeatures) FROM Proteins_Row;
SELECT sgdsw_row(15, 50, 18, allFeatures) FROM Proteins_Row;


-- music dataset
CREATE TABLE music_row (ab real);
COPY 44516640 RECORDS INTO music_row FROM '/home/kkara/Projects/doppiodb/DATASETS/music_row.tbl' USING DELIMITERS '|';

COPY 44516640 RECORDS INTO music_row FROM '/media/storage/doppiodb/DATASETS/music_row.tbl' USING DELIMITERS '|';

select sgdfpga_row(91, 5, 12, ab) FROM music_row;
select sgdsw_row(91, 5, 12, ab) FROM music_row;

-- Salaries dataset
CREATE TABLE salaries(Id integer, EmployeeName string, JobTitle string, BasePay real, OvertimePay real, OtherPay real, Benefits real, TotalPay real, TotalPayBenefits real, Years real, Notes real, Agency string, Status string);
COPY 148655 RECORDS INTO salaries FROM '/home/kkara/Projects/doppiodb/DATASETS/salaries.csv' USING DELIMITERS ',','\n','"' NULL AS '';
COPY 160 RECORDS INTO salaries FROM '/home/kkara/Projects/doppiodb/DATASETS/salaries.csv' USING DELIMITERS ',','\n','"' NULL AS '';

COPY 148655 RECORDS INTO salaries FROM '/media/storage/doppiodb/DATASETS/salaries.csv' USING DELIMITERS ',','\n','"' NULL AS '';
COPY 160 RECORDS INTO salaries FROM '/media/storage/doppiodb/DATASETS/salaries.csv' USING DELIMITERS ',','\n','"' NULL AS '';

DELETE FROM salaries;

select regexfpga('MANAGER', jobtitle) FROM salaries;
select sgdfpga_column(7, 4, 18, 3, BasePay, OvertimePay, OtherPay, Benefits, TotalPay, TotalPayBenefits, Years, BasePay, BasePay, BasePay, BasePay, BasePay, BasePay, BasePay, BasePay, BasePay ) FROM salaries;
select sgdfpga_column(7, 4, 18, 3, BasePay, OvertimePay, OtherPay, Benefits, TotalPay, TotalPayBenefits, Years, BasePay, BasePay, BasePay, BasePay, BasePay, BasePay, BasePay, BasePay, regexfpga('MANAGER', jobtitle) ) FROM salaries;


-- Fraud dataset
CREATE TABLE fraud(step integer, type string, amount real, nameOrig string, oldbalanceOrg real, newbalanceOrig real, nameDest string, oldbalanceDest real, newbalanceDest real, isFraud integer, isFlaggedFraud integer);

-- Selection queries
CREATE TABLE employee (id integer, age integer, salary integer);
COPY 80000 RECORDS INTO employee FROM '/home/kkara/Projects/DataGenerator/employee.tbl' USING DELIMITERS '|';

select count(*) FROM (select hwselection(age, '=', 26, 26) FROM employee) as sub;
select count(*) FROM employee where age = 26;