/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_SQL_Y_TAB_H_INCLUDED
# define YY_SQL_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int sqldebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    STRING = 258,
    X_BODY = 259,
    IDENT = 260,
    aTYPE = 261,
    ALIAS = 262,
    AGGR = 263,
    AGGR2 = 264,
    RANK = 265,
    sqlINT = 266,
    OIDNUM = 267,
    HEXADECIMAL = 268,
    INTNUM = 269,
    APPROXNUM = 270,
    USING = 271,
    GLOBAL = 272,
    CAST = 273,
    CONVERT = 274,
    CHARACTER = 275,
    VARYING = 276,
    LARGE = 277,
    OBJECT = 278,
    VARCHAR = 279,
    CLOB = 280,
    sqlTEXT = 281,
    BINARY = 282,
    sqlBLOB = 283,
    sqlDECIMAL = 284,
    sqlFLOAT = 285,
    TINYINT = 286,
    SMALLINT = 287,
    BIGINT = 288,
    HUGEINT = 289,
    sqlINTEGER = 290,
    sqlDOUBLE = 291,
    sqlREAL = 292,
    PRECISION = 293,
    PARTIAL = 294,
    SIMPLE = 295,
    ACTION = 296,
    CASCADE = 297,
    RESTRICT = 298,
    BOOL_FALSE = 299,
    BOOL_TRUE = 300,
    CURRENT_DATE = 301,
    CURRENT_TIMESTAMP = 302,
    CURRENT_TIME = 303,
    LOCALTIMESTAMP = 304,
    LOCALTIME = 305,
    LEX_ERROR = 306,
    USER = 307,
    CURRENT_USER = 308,
    SESSION_USER = 309,
    LOCAL = 310,
    LOCKED = 311,
    BEST = 312,
    EFFORT = 313,
    CURRENT_ROLE = 314,
    sqlSESSION = 315,
    sqlDELETE = 316,
    UPDATE = 317,
    SELECT = 318,
    INSERT = 319,
    LEFT = 320,
    RIGHT = 321,
    FULL = 322,
    OUTER = 323,
    NATURAL = 324,
    CROSS = 325,
    JOIN = 326,
    INNER = 327,
    COMMIT = 328,
    ROLLBACK = 329,
    SAVEPOINT = 330,
    RELEASE = 331,
    WORK = 332,
    CHAIN = 333,
    NO = 334,
    PRESERVE = 335,
    ROWS = 336,
    START = 337,
    TRANSACTION = 338,
    READ = 339,
    WRITE = 340,
    ONLY = 341,
    ISOLATION = 342,
    LEVEL = 343,
    UNCOMMITTED = 344,
    COMMITTED = 345,
    sqlREPEATABLE = 346,
    SERIALIZABLE = 347,
    DIAGNOSTICS = 348,
    sqlSIZE = 349,
    STORAGE = 350,
    ASYMMETRIC = 351,
    SYMMETRIC = 352,
    ORDER = 353,
    BY = 354,
    EXISTS = 355,
    ESCAPE = 356,
    HAVING = 357,
    sqlGROUP = 358,
    sqlNULL = 359,
    FROM = 360,
    FOR = 361,
    MATCH = 362,
    EXTRACT = 363,
    SEQUENCE = 364,
    INCREMENT = 365,
    RESTART = 366,
    MAXVALUE = 367,
    MINVALUE = 368,
    CYCLE = 369,
    NOMAXVALUE = 370,
    NOMINVALUE = 371,
    NOCYCLE = 372,
    NEXT = 373,
    VALUE = 374,
    CACHE = 375,
    GENERATED = 376,
    ALWAYS = 377,
    IDENTITY = 378,
    SERIAL = 379,
    BIGSERIAL = 380,
    AUTO_INCREMENT = 381,
    SCOLON = 382,
    AT = 383,
    XMLCOMMENT = 384,
    XMLCONCAT = 385,
    XMLDOCUMENT = 386,
    XMLELEMENT = 387,
    XMLATTRIBUTES = 388,
    XMLFOREST = 389,
    XMLPARSE = 390,
    STRIP = 391,
    WHITESPACE = 392,
    XMLPI = 393,
    XMLQUERY = 394,
    PASSING = 395,
    XMLTEXT = 396,
    NIL = 397,
    REF = 398,
    ABSENT = 399,
    EMPTY = 400,
    DOCUMENT = 401,
    ELEMENT = 402,
    CONTENT = 403,
    XMLNAMESPACES = 404,
    NAMESPACE = 405,
    XMLVALIDATE = 406,
    RETURNING = 407,
    LOCATION = 408,
    ID = 409,
    ACCORDING = 410,
    XMLSCHEMA = 411,
    URI = 412,
    XMLAGG = 413,
    FILTER = 414,
    UNION = 415,
    EXCEPT = 416,
    INTERSECT = 417,
    CORRESPONDING = 418,
    UNIONJOIN = 419,
    WITH = 420,
    DATA = 421,
    FILTER_FUNC = 422,
    NOT = 423,
    ALL = 424,
    ANY = 425,
    NOT_BETWEEN = 426,
    BETWEEN = 427,
    NOT_IN = 428,
    sqlIN = 429,
    NOT_LIKE = 430,
    LIKE = 431,
    NOT_ILIKE = 432,
    ILIKE = 433,
    OR = 434,
    SOME = 435,
    AND = 436,
    COMPARISON = 437,
    LEFT_SHIFT = 438,
    RIGHT_SHIFT = 439,
    LEFT_SHIFT_ASSIGN = 440,
    RIGHT_SHIFT_ASSIGN = 441,
    CONCATSTRING = 442,
    SUBSTRING = 443,
    POSITION = 444,
    SPLIT_PART = 445,
    UMINUS = 446,
    TEMP = 447,
    TEMPORARY = 448,
    STREAM = 449,
    MERGE = 450,
    REMOTE = 451,
    REPLICA = 452,
    ASC = 453,
    DESC = 454,
    AUTHORIZATION = 455,
    CHECK = 456,
    CONSTRAINT = 457,
    CREATE = 458,
    TYPE = 459,
    PROCEDURE = 460,
    FUNCTION = 461,
    AGGREGATE = 462,
    RETURNS = 463,
    EXTERNAL = 464,
    sqlNAME = 465,
    DECLARE = 466,
    CALL = 467,
    LANGUAGE = 468,
    ANALYZE = 469,
    MINMAX = 470,
    SQL_EXPLAIN = 471,
    SQL_PLAN = 472,
    SQL_DEBUG = 473,
    SQL_TRACE = 474,
    SQL_DOT = 475,
    PREPARE = 476,
    EXECUTE = 477,
    DEFAULT = 478,
    DISTINCT = 479,
    DROP = 480,
    FOREIGN = 481,
    RENAME = 482,
    ENCRYPTED = 483,
    UNENCRYPTED = 484,
    PASSWORD = 485,
    GRANT = 486,
    REVOKE = 487,
    ROLE = 488,
    ADMIN = 489,
    INTO = 490,
    IS = 491,
    KEY = 492,
    ON = 493,
    OPTION = 494,
    OPTIONS = 495,
    PATH = 496,
    PRIMARY = 497,
    PRIVILEGES = 498,
    PUBLIC = 499,
    REFERENCES = 500,
    SCHEMA = 501,
    SET = 502,
    AUTO_COMMIT = 503,
    RETURN = 504,
    ALTER = 505,
    ADD = 506,
    TABLE = 507,
    COLUMN = 508,
    TO = 509,
    UNIQUE = 510,
    VALUES = 511,
    VIEW = 512,
    WHERE = 513,
    sqlDATE = 514,
    TIME = 515,
    TIMESTAMP = 516,
    INTERVAL = 517,
    YEAR = 518,
    MONTH = 519,
    DAY = 520,
    HOUR = 521,
    MINUTE = 522,
    SECOND = 523,
    ZONE = 524,
    LIMIT = 525,
    OFFSET = 526,
    SAMPLE = 527,
    CASE = 528,
    WHEN = 529,
    THEN = 530,
    ELSE = 531,
    NULLIF = 532,
    COALESCE = 533,
    IF = 534,
    ELSEIF = 535,
    WHILE = 536,
    DO = 537,
    ATOMIC = 538,
    BEGIN = 539,
    END = 540,
    COPY = 541,
    RECORDS = 542,
    DELIMITERS = 543,
    STDIN = 544,
    STDOUT = 545,
    INDEX = 546,
    AS = 547,
    TRIGGER = 548,
    OF = 549,
    BEFORE = 550,
    AFTER = 551,
    ROW = 552,
    STATEMENT = 553,
    sqlNEW = 554,
    OLD = 555,
    EACH = 556,
    REFERENCING = 557,
    OVER = 558,
    PARTITION = 559,
    CURRENT = 560,
    EXCLUDE = 561,
    FOLLOWING = 562,
    PRECEDING = 563,
    OTHERS = 564,
    TIES = 565,
    RANGE = 566,
    UNBOUNDED = 567
  };
#endif
/* Tokens.  */
#define STRING 258
#define X_BODY 259
#define IDENT 260
#define aTYPE 261
#define ALIAS 262
#define AGGR 263
#define AGGR2 264
#define RANK 265
#define sqlINT 266
#define OIDNUM 267
#define HEXADECIMAL 268
#define INTNUM 269
#define APPROXNUM 270
#define USING 271
#define GLOBAL 272
#define CAST 273
#define CONVERT 274
#define CHARACTER 275
#define VARYING 276
#define LARGE 277
#define OBJECT 278
#define VARCHAR 279
#define CLOB 280
#define sqlTEXT 281
#define BINARY 282
#define sqlBLOB 283
#define sqlDECIMAL 284
#define sqlFLOAT 285
#define TINYINT 286
#define SMALLINT 287
#define BIGINT 288
#define HUGEINT 289
#define sqlINTEGER 290
#define sqlDOUBLE 291
#define sqlREAL 292
#define PRECISION 293
#define PARTIAL 294
#define SIMPLE 295
#define ACTION 296
#define CASCADE 297
#define RESTRICT 298
#define BOOL_FALSE 299
#define BOOL_TRUE 300
#define CURRENT_DATE 301
#define CURRENT_TIMESTAMP 302
#define CURRENT_TIME 303
#define LOCALTIMESTAMP 304
#define LOCALTIME 305
#define LEX_ERROR 306
#define USER 307
#define CURRENT_USER 308
#define SESSION_USER 309
#define LOCAL 310
#define LOCKED 311
#define BEST 312
#define EFFORT 313
#define CURRENT_ROLE 314
#define sqlSESSION 315
#define sqlDELETE 316
#define UPDATE 317
#define SELECT 318
#define INSERT 319
#define LEFT 320
#define RIGHT 321
#define FULL 322
#define OUTER 323
#define NATURAL 324
#define CROSS 325
#define JOIN 326
#define INNER 327
#define COMMIT 328
#define ROLLBACK 329
#define SAVEPOINT 330
#define RELEASE 331
#define WORK 332
#define CHAIN 333
#define NO 334
#define PRESERVE 335
#define ROWS 336
#define START 337
#define TRANSACTION 338
#define READ 339
#define WRITE 340
#define ONLY 341
#define ISOLATION 342
#define LEVEL 343
#define UNCOMMITTED 344
#define COMMITTED 345
#define sqlREPEATABLE 346
#define SERIALIZABLE 347
#define DIAGNOSTICS 348
#define sqlSIZE 349
#define STORAGE 350
#define ASYMMETRIC 351
#define SYMMETRIC 352
#define ORDER 353
#define BY 354
#define EXISTS 355
#define ESCAPE 356
#define HAVING 357
#define sqlGROUP 358
#define sqlNULL 359
#define FROM 360
#define FOR 361
#define MATCH 362
#define EXTRACT 363
#define SEQUENCE 364
#define INCREMENT 365
#define RESTART 366
#define MAXVALUE 367
#define MINVALUE 368
#define CYCLE 369
#define NOMAXVALUE 370
#define NOMINVALUE 371
#define NOCYCLE 372
#define NEXT 373
#define VALUE 374
#define CACHE 375
#define GENERATED 376
#define ALWAYS 377
#define IDENTITY 378
#define SERIAL 379
#define BIGSERIAL 380
#define AUTO_INCREMENT 381
#define SCOLON 382
#define AT 383
#define XMLCOMMENT 384
#define XMLCONCAT 385
#define XMLDOCUMENT 386
#define XMLELEMENT 387
#define XMLATTRIBUTES 388
#define XMLFOREST 389
#define XMLPARSE 390
#define STRIP 391
#define WHITESPACE 392
#define XMLPI 393
#define XMLQUERY 394
#define PASSING 395
#define XMLTEXT 396
#define NIL 397
#define REF 398
#define ABSENT 399
#define EMPTY 400
#define DOCUMENT 401
#define ELEMENT 402
#define CONTENT 403
#define XMLNAMESPACES 404
#define NAMESPACE 405
#define XMLVALIDATE 406
#define RETURNING 407
#define LOCATION 408
#define ID 409
#define ACCORDING 410
#define XMLSCHEMA 411
#define URI 412
#define XMLAGG 413
#define FILTER 414
#define UNION 415
#define EXCEPT 416
#define INTERSECT 417
#define CORRESPONDING 418
#define UNIONJOIN 419
#define WITH 420
#define DATA 421
#define FILTER_FUNC 422
#define NOT 423
#define ALL 424
#define ANY 425
#define NOT_BETWEEN 426
#define BETWEEN 427
#define NOT_IN 428
#define sqlIN 429
#define NOT_LIKE 430
#define LIKE 431
#define NOT_ILIKE 432
#define ILIKE 433
#define OR 434
#define SOME 435
#define AND 436
#define COMPARISON 437
#define LEFT_SHIFT 438
#define RIGHT_SHIFT 439
#define LEFT_SHIFT_ASSIGN 440
#define RIGHT_SHIFT_ASSIGN 441
#define CONCATSTRING 442
#define SUBSTRING 443
#define POSITION 444
#define SPLIT_PART 445
#define UMINUS 446
#define TEMP 447
#define TEMPORARY 448
#define STREAM 449
#define MERGE 450
#define REMOTE 451
#define REPLICA 452
#define ASC 453
#define DESC 454
#define AUTHORIZATION 455
#define CHECK 456
#define CONSTRAINT 457
#define CREATE 458
#define TYPE 459
#define PROCEDURE 460
#define FUNCTION 461
#define AGGREGATE 462
#define RETURNS 463
#define EXTERNAL 464
#define sqlNAME 465
#define DECLARE 466
#define CALL 467
#define LANGUAGE 468
#define ANALYZE 469
#define MINMAX 470
#define SQL_EXPLAIN 471
#define SQL_PLAN 472
#define SQL_DEBUG 473
#define SQL_TRACE 474
#define SQL_DOT 475
#define PREPARE 476
#define EXECUTE 477
#define DEFAULT 478
#define DISTINCT 479
#define DROP 480
#define FOREIGN 481
#define RENAME 482
#define ENCRYPTED 483
#define UNENCRYPTED 484
#define PASSWORD 485
#define GRANT 486
#define REVOKE 487
#define ROLE 488
#define ADMIN 489
#define INTO 490
#define IS 491
#define KEY 492
#define ON 493
#define OPTION 494
#define OPTIONS 495
#define PATH 496
#define PRIMARY 497
#define PRIVILEGES 498
#define PUBLIC 499
#define REFERENCES 500
#define SCHEMA 501
#define SET 502
#define AUTO_COMMIT 503
#define RETURN 504
#define ALTER 505
#define ADD 506
#define TABLE 507
#define COLUMN 508
#define TO 509
#define UNIQUE 510
#define VALUES 511
#define VIEW 512
#define WHERE 513
#define sqlDATE 514
#define TIME 515
#define TIMESTAMP 516
#define INTERVAL 517
#define YEAR 518
#define MONTH 519
#define DAY 520
#define HOUR 521
#define MINUTE 522
#define SECOND 523
#define ZONE 524
#define LIMIT 525
#define OFFSET 526
#define SAMPLE 527
#define CASE 528
#define WHEN 529
#define THEN 530
#define ELSE 531
#define NULLIF 532
#define COALESCE 533
#define IF 534
#define ELSEIF 535
#define WHILE 536
#define DO 537
#define ATOMIC 538
#define BEGIN 539
#define END 540
#define COPY 541
#define RECORDS 542
#define DELIMITERS 543
#define STDIN 544
#define STDOUT 545
#define INDEX 546
#define AS 547
#define TRIGGER 548
#define OF 549
#define BEFORE 550
#define AFTER 551
#define ROW 552
#define STATEMENT 553
#define sqlNEW 554
#define OLD 555
#define EACH 556
#define REFERENCING 557
#define OVER 558
#define PARTITION 559
#define CURRENT 560
#define EXCLUDE 561
#define FOLLOWING 562
#define PRECEDING 563
#define OTHERS 564
#define TIES 565
#define RANGE 566
#define UNBOUNDED 567

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 108 "sql_parser.y" /* yacc.c:1909  */

	int		i_val,bval;
	wrd		w_val;
	lng		l_val,operation;
	double		fval;
	char *		sval;
	symbol*		sym;
	dlist*		l;
	sql_subtype	type;

#line 689 "y.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int sqlparse (mvc *m);

#endif /* !YY_SQL_Y_TAB_H_INCLUDED  */
