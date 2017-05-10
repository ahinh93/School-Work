INSERT INTO ORDERS (ORDER#, CUSTOMER#, ORDERDATE)
	VALUES (1021, 1009, TO_DATE('2009-07-20','YYYY-MM-DD'));
	
UPDATE ORDERS 
	SET SHIPZIP = '33222'
	WHERE ORDER# = 1017;

SAVEPOINT JOSE;

INSERT INTO ORDERS (ORDER#, CUSTOMER#, ORDERDATE)
	VALUES (1022, 2000, TO_DATE('2009-08-06','YYYY-MM-DD'));
	
/*
	The foreign key Customer# does not have a matching primary key.
*/	
	
DELETE FROM ORDERS
	WHERE ORDER# = 1005;
	
ROLLBACK TO JOSE;


CREATE TABLE CATEGORY
	(CATCODE VARCHAR2(3,0),
	CATDESC VARCHAR2(11,0),
		CONSTRAINT CATEGORY_CATCODE_#pk PRIMARY KEY(CATCODE));
		
INSERT INTO CATEGORY (CATCODE, CATDESC)
	VALUES ('BUS', 'BUSINESS');
	
INSERT INTO CATEGORY (CATCODE, CATDESC)
	VALUES ('CHN', 'CHILDREN');
	
INSERT INTO CATEGORY (CATCODE, CATDESC)
	VALUES ('COK', 'COOKING');
	
INSERT INTO CATEGORY (CATCODE, CATDESC)
	VALUES ('COM', 'COMPUTER');
	
INSERT INTO CATEGORY (CATCODE, CATDESC)
	VALUES ('FAL', 'FAMILY LIFE');
	
INSERT INTO CATEGORY (CATCODE, CATDESC)
	VALUES ('FIT', 'FITNESS');
	
INSERT INTO CATEGORY (CATCODE, CATDESC)
	VALUES ('SEH', 'SELF HELP');
	
INSERT INTO CATEGORY (CATCODE, CATDESC)
	VALUES ('LIT', 'LITERATURE');

ALTER TABLE BOOKS
	ADD(Catcode VARCHAR2(50));
	
ALTER TABLE BOOKS
	ADD CONSTRAINT BOOKS_Catcode_#fk FOREIGN KEY(Catcode)
	REFERENCES CATEGORY(CATCODE);

UPDATE BOOKS
	SET Catcode = 'BUS'
	WHERE CATEGORY = 'BUSINESS';
UPDATE BOOKS
	SET Catcode = 'CHN'
	WHERE CATEGORY = 'CHILDREN';
UPDATE BOOKS
	SET Catcode = 'COK'
	WHERE CATEGORY = 'COOKING';
UPDATE BOOKS
	SET Catcode = 'COM'
	WHERE CATEGORY = 'COMPUTER';
UPDATE BOOKS
	SET Catcode = 'FAL'
	WHERE CATEGORY = 'FAMILY LIFE';
UPDATE BOOKS
	SET Catcode = 'FIT'
	WHERE CATEGORY = 'FITNESS';
UPDATE BOOKS
	SET Catcode = 'SEH'
	WHERE CATEGORY = 'SELF HELP';
UPDATE BOOKS
	SET Catcode = 'LIT'
	WHERE CATEGORY = 'LITERATURE';
	
COMMIT;

ALTER TABLE BOOKS
DROP COLUMN CATEGORY;
	
	


	


