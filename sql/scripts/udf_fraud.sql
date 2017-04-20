-- Fraud dataset
CREATE TABLE fraud(step integer, type string, amount real, nameOrig string, oldbalanceOrg real, newbalanceOrg real, nameDest string, oldbalanceDest real, newbalanceDest real, isFraud integer, isFlaggedFraud integer);
--COPY 6362621 RECORDS INTO fraud FROM '/home/kkara/Projects/doppiodb/DATASETS/fraud.csv' USING DELIMITERS ',','\n','"' NULL AS '';
--COPY 1000 RECORDS INTO fraud FROM '/home/kkara/Projects/doppiodb/DATASETS/fraud.csv' USING DELIMITERS ',','\n','"' NULL AS '';

COPY 1000000 RECORDS INTO fraud FROM '/media/storage/doppiodb/DATASETS/fraud.csv' USING DELIMITERS ',','\n','"' NULL AS '';
--COPY 1000 RECORDS INTO fraud FROM '/media/storage/doppiodb/DATASETS/fraud.csv' USING DELIMITERS ',','\n','"' NULL AS '';

DECLARE amount_max real, oldbalanceOrg_max real, newbalanceOrg_max real, oldbalanceDest_max real, newbalanceDest_max real;
SELECT max(amount) INTO amount_max FROM fraud;
SELECT max(oldbalanceOrg) INTO oldbalanceOrg_max FROM fraud;
SELECT max(newbalanceOrg) INTO newbalanceOrg_max FROM fraud;
SELECT max(oldbalanceDest) INTO oldbalanceDest_max FROM fraud;
SELECT max(newbalanceDest) INTO newbalanceDest_max FROM fraud;
UPDATE fraud SET isfraud = -1 WHERE isfraud = 0;
UPDATE fraud SET amount = amount/amount_max;
UPDATE fraud SET oldbalanceOrg = oldbalanceOrg/oldbalanceOrg_max;
UPDATE fraud SET newbalanceOrg = newbalanceOrg/newbalanceOrg_max;
UPDATE fraud SET oldbalanceDest = oldbalanceDest/oldbalanceDest_max;
UPDATE fraud SET newbalanceDest = newbalanceDest/newbalanceDest_max;

--SELECT sgdsw_column(5, 10, 18, amount, oldbalanceOrg, newbalanceOrg, oldbalanceDest, newbalanceDest, amount, amount, amount, amount, amount, amount, amount, amount, amount, amount, isFraud) FROM fraud WHERE type = 'TRANSFER';
--SELECT sgdsw_column(5, 10, 18, amount, oldbalanceOrg, newbalanceOrg, oldbalanceDest, newbalanceDest, amount, amount, amount, amount, amount, amount, amount, amount, amount, amount, isFraud) FROM fraud;
--SELECT sgdfpga_column(5, 10, 18, 1, amount, oldbalanceOrg, newbalanceOrg, oldbalanceDest, newbalanceDest, amount, amount, amount, amount, amount, amount, amount, amount, amount, amount, isFraud) FROM fraud;

--SELECT infersw_column(5, amount, oldbalanceOrg, newbalanceOrg, oldbalanceDest, newbalanceDest, amount, amount, amount, amount, amount, amount, amount, amount, amount, amount) FROM fraud;

--DELETE FROM fraud;
--DROP TABLE fraud;