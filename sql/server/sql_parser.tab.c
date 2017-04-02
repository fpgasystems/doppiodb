/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         sqlparse
#define yylex           sqllex
#define yyerror         sqlerror
#define yydebug         sqldebug
#define yynerrs         sqlnerrs


/* Copy the first part of user declarations.  */
#line 9 "sql_parser.y" /* yacc.c:339  */

#include "monetdb_config.h"
#include <sql_mem.h>
#include "sql_parser.h"
#include "sql_symbol.h"
#include "sql_datetime.h"
#include "sql_decimal.h"	/* for decimal_from_str() */
#include "sql_semantic.h"	/* for sql_add_param() & sql_add_arg() */
#include "sql_env.h"
#include "rel_sequence.h"	/* for sql_next_seq_name() */
#ifdef HAVE_HGE
#include "mal.h"		/* for have_hge */
#endif

#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define SA 	m->sa
#define _symbol_create(t,d)         symbol_create( SA, t, d)
#define _symbol_create_list(t,d)    symbol_create_list( SA, t, d)
#define _symbol_create_int(t,d)     symbol_create_int( SA, t, d)
#define _symbol_create_lng(t,d)     symbol_create_lng( SA, t, d)
#define _symbol_create_symbol(t,d)  symbol_create_symbol( SA, t, d)
#define _symbol_create_hexa(t,d)    symbol_create_hexa( SA, t, d)
#define _newAtomNode(d)		    newAtomNode( SA, d)

#define L()                  dlist_create( SA )

#define append_list(l,d)     dlist_append_list( SA, l, d)
#define append_int(l,d)      dlist_append_int( SA, l, d)
#define append_lng(l,d)      dlist_append_lng( SA, l, d)
#define append_symbol(l,d)   dlist_append_symbol( SA, l, d)
#define append_string(l,d)   dlist_append_string( SA, l, d)
#define append_type(l,d)     dlist_append_type( SA, l, d)

#define _atom_string(t, v)   atom_string(SA, t, v)

#define YYMALLOC malloc
#define YYFREE free

#define YY_parse_LSP_NEEDED	/* needed for bison++ 1.21.11-3 */

#ifdef HAVE_HGE
#define MAX_DEC_DIGITS (have_hge ? 38 : 18)
#define MAX_HEX_DIGITS (have_hge ? 32 : 16)
#else
#define MAX_DEC_DIGITS 18
#define MAX_HEX_DIGITS 16
#endif

static inline int
UTF8_strlen(const char *val)
{
	const unsigned char *s = (const unsigned char *) val;
	int pos = 0;

	while (*s) {
		int c = *s++;

		pos++;
		if (c < 0xC0)
			continue;
		if (*s++ < 0x80)
			return int_nil;
		if (c < 0xE0)
			continue;
		if (*s++ < 0x80)
			return int_nil;
		if (c < 0xF0)
			continue;
		if (*s++ < 0x80)
			return int_nil;
		if (c < 0xF8)
			continue;
		if (*s++ < 0x80)
			return int_nil;
		if (c < 0xFC)
			continue;
		if (*s++ < 0x80)
			return int_nil;
	}
	return pos;
}


#line 159 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
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
#line 108 "sql_parser.y" /* yacc.c:355  */

	int		i_val,bval;
	wrd		w_val;
	lng		l_val,operation;
	double		fval;
	char *		sval;
	symbol*		sym;
	dlist*		l;
	sql_subtype	type;

#line 834 "y.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int sqlparse (mvc *m);

#endif /* !YY_SQL_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */
#line 118 "sql_parser.y" /* yacc.c:358  */

extern int sqllex( YYSTYPE *yylval, void *m );
/* enable to activate debugging support
int yydebug=1;
*/

#line 854 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  219
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   15227

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  331
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  401
/* YYNRULES -- Number of rules.  */
#define YYNRULES  1073
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  1986

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   567

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint16 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,   202,   188,     2,
     167,   168,   200,   186,   325,   187,   326,   201,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   327,     2,
       2,   171,     2,   330,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   328,     2,   329,   190,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,   189,     2,   203,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   169,   170,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   312,   313,   314,   315,   316,
     317,   318,   319,   320,   321,   322,   323,   324
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   606,   606,   617,   617,   631,   631,   646,   646,   661,
     661,   676,   676,   686,   686,   692,   693,   694,   695,   696,
     701,   704,   707,   710,   714,   715,   716,   717,   718,   719,
     720,   721,   722,   729,   733,   734,   738,   740,   744,   749,
     757,   762,   770,   778,   786,   794,   800,   808,   816,   824,
     828,   832,   839,   842,   843,   847,   848,   852,   853,   857,
     857,   857,   857,   857,   860,   861,   865,   866,   870,   879,
     890,   891,   896,   897,   901,   902,   907,   908,   912,   920,
     930,   931,   935,   936,   940,   947,   948,   960,   961,   962,
     966,   967,   972,   973,   974,   975,   976,   977,   981,   982,
     987,   988,   994,  1000,  1005,  1010,  1015,  1020,  1025,  1030,
    1035,  1040,  1053,  1059,  1065,  1075,  1080,  1084,  1088,  1090,
    1098,  1106,  1111,  1116,  1124,  1125,  1129,  1130,  1131,  1132,
    1133,  1134,  1135,  1136,  1151,  1164,  1180,  1191,  1210,  1231,
    1232,  1245,  1246,  1247,  1249,  1260,  1261,  1272,  1273,  1274,
    1285,  1286,  1287,  1297,  1298,  1308,  1309,  1310,  1316,  1326,
    1327,  1347,  1352,  1363,  1364,  1365,  1369,  1379,  1389,  1399,
    1410,  1420,  1435,  1436,  1437,  1438,  1439,  1440,  1444,  1445,
    1446,  1447,  1451,  1452,  1456,  1466,  1467,  1471,  1473,  1477,
    1477,  1478,  1478,  1478,  1481,  1482,  1486,  1494,  1555,  1556,
    1560,  1562,  1567,  1576,  1578,  1582,  1582,  1582,  1585,  1589,
    1593,  1602,  1629,  1676,  1686,  1691,  1702,  1703,  1707,  1708,
    1709,  1710,  1711,  1715,  1719,  1723,  1724,  1725,  1726,  1727,
    1731,  1732,  1733,  1734,  1738,  1739,  1743,  1744,  1745,  1746,
    1747,  1757,  1761,  1763,  1765,  1780,  1784,  1786,  1791,  1795,
    1807,  1808,  1812,  1813,  1817,  1818,  1822,  1826,  1834,  1838,
    1851,  1864,  1889,  1902,  1915,  1941,  1953,  1968,  1970,  1974,
    1992,  1993,  1998,  1999,  2004,  2005,  2006,  2007,  2008,  2009,
    2010,  2011,  2012,  2013,  2014,  2015,  2019,  2020,  2021,  2022,
    2023,  2024,  2025,  2026,  2030,  2031,  2032,  2033,  2034,  2035,
    2048,  2052,  2056,  2065,  2068,  2069,  2070,  2076,  2080,  2081,
    2082,  2087,  2093,  2101,  2109,  2111,  2116,  2124,  2126,  2131,
    2132,  2139,  2153,  2154,  2156,  2167,  2188,  2189,  2193,  2194,
    2199,  2203,  2211,  2213,  2218,  2219,  2223,  2227,  2232,  2281,
    2295,  2296,  2300,  2301,  2302,  2303,  2307,  2308,  2312,  2313,
    2319,  2320,  2321,  2322,  2325,  2327,  2330,  2332,  2336,  2344,
    2345,  2349,  2350,  2354,  2355,  2359,  2361,  2367,  2372,  2380,
    2388,  2396,  2404,  2412,  2420,  2428,  2436,  2441,  2442,  2443,
    2444,  2448,  2449,  2450,  2454,  2457,  2462,  2463,  2464,  2469,
    2470,  2475,  2476,  2477,  2478,  2482,  2489,  2491,  2493,  2495,
    2499,  2501,  2503,  2508,  2509,  2513,  2515,  2521,  2522,  2523,
    2524,  2528,  2529,  2530,  2531,  2535,  2536,  2540,  2541,  2542,
    2546,  2547,  2551,  2564,  2577,  2587,  2594,  2604,  2605,  2609,
    2610,  2614,  2618,  2627,  2631,  2636,  2641,  2650,  2651,  2655,
    2656,  2657,  2658,  2660,  2665,  2666,  2670,  2671,  2675,  2676,
    2680,  2681,  2685,  2686,  2690,  2691,  2696,  2705,  2746,  2754,
    2765,  2766,  2768,  2770,  2775,  2776,  2781,  2782,  2787,  2788,
    2793,  2810,  2814,  2818,  2819,  2823,  2824,  2825,  2829,  2830,
    2835,  2840,  2848,  2849,  2855,  2857,  2863,  2871,  2879,  2887,
    2895,  2906,  2907,  2908,  2912,  2913,  2914,  2918,  2919,  2939,
    2943,  2953,  2954,  2958,  2970,  2975,  2977,  2981,  2992,  3003,
    3034,  3035,  3040,  3044,  3053,  3062,  3070,  3071,  3075,  3076,
    3077,  3082,  3083,  3085,  3090,  3094,  3104,  3105,  3109,  3110,
    3115,  3119,  3123,  3127,  3134,  3135,  3145,  3150,  3160,  3159,
    3172,  3177,  3182,  3187,  3195,  3196,  3200,  3202,  3208,  3209,
    3214,  3219,  3223,  3228,  3232,  3233,  3238,  3239,  3243,  3247,
    3248,  3252,  3256,  3257,  3261,  3265,  3269,  3270,  3275,  3284,
    3285,  3286,  3290,  3291,  3292,  3293,  3294,  3295,  3296,  3297,
    3298,  3302,  3319,  3323,  3330,  3340,  3347,  3357,  3358,  3359,
    3363,  3370,  3377,  3384,  3394,  3398,  3416,  3417,  3421,  3427,
    3433,  3438,  3446,  3448,  3453,  3464,  3465,  3466,  3470,  3474,
    3475,  3479,  3483,  3492,  3493,  3495,  3501,  3502,  3509,  3516,
    3523,  3530,  3537,  3544,  3551,  3558,  3564,  3571,  3578,  3585,
    3592,  3594,  3619,  3623,  3624,  3628,  3629,  3631,  3633,  3634,
    3635,  3636,  3637,  3638,  3639,  3640,  3641,  3642,  3643,  3644,
    3645,  3649,  3719,  3725,  3726,  3730,  3735,  3736,  3741,  3742,
    3747,  3748,  3753,  3754,  3758,  3759,  3763,  3764,  3765,  3769,
    3773,  3778,  3779,  3780,  3784,  3788,  3789,  3790,  3791,  3792,
    3796,  3800,  3804,  3832,  3833,  3838,  3839,  3840,  3841,  3845,
    3852,  3857,  3862,  3867,  3872,  3880,  3881,  3885,  3895,  3905,
    3912,  3919,  3926,  3933,  3946,  3947,  3952,  3957,  3962,  3967,
    3975,  3976,  3980,  4002,  4003,  4008,  4009,  4014,  4015,  4021,
    4027,  4033,  4039,  4045,  4051,  4058,  4062,  4063,  4064,  4068,
    4069,  4080,  4082,  4086,  4088,  4092,  4093,  4099,  4108,  4109,
    4110,  4111,  4112,  4116,  4117,  4121,  4127,  4130,  4136,  4139,
    4145,  4148,  4153,  4173,  4174,  4175,  4179,  4185,  4249,  4280,
    4331,  4370,  4387,  4403,  4419,  4435,  4436,  4453,  4470,  4487,
    4508,  4512,  4519,  4564,  4565,  4569,  4580,  4583,  4587,  4595,
    4601,  4609,  4613,  4618,  4620,  4626,  4634,  4636,  4641,  4645,
    4651,  4659,  4661,  4666,  4674,  4676,  4681,  4682,  4686,  4691,
    4702,  4713,  4724,  4734,  4744,  4754,  4756,  4761,  4762,  4764,
    4766,  4775,  4776,  4785,  4786,  4787,  4788,  4789,  4791,  4792,
    4805,  4823,  4824,  4838,  4858,  4859,  4860,  4861,  4862,  4863,
    4864,  4866,  4867,  4869,  4881,  4895,  4913,  4928,  4929,  4933,
    4934,  4935,  4938,  4939,  4942,  4944,  4947,  4948,  4949,  4950,
    4951,  4952,  4956,  4957,  4958,  4959,  4960,  4961,  4962,  4963,
    4967,  4968,  4969,  4970,  4971,  4972,  4973,  4974,  4975,  4976,
    4977,  4978,  4979,  4981,  4982,  4983,  4984,  4985,  4986,  4987,
    4988,  4989,  4990,  4991,  4992,  4993,  4994,  4996,  4997,  4998,
    4999,  5000,  5001,  5002,  5003,  5004,  5005,  5006,  5007,  5008,
    5009,  5011,  5012,  5013,  5014,  5015,  5016,  5017,  5018,  5019,
    5021,  5022,  5023,  5024,  5025,  5026,  5027,  5028,  5029,  5030,
    5031,  5032,  5033,  5034,  5035,  5036,  5037,  5038,  5039,  5040,
    5041,  5042,  5046,  5047,  5052,  5070,  5092,  5112,  5144,  5146,
    5154,  5161,  5166,  5181,  5182,  5186,  5189,  5192,  5196,  5198,
    5203,  5207,  5208,  5209,  5210,  5211,  5212,  5213,  5214,  5215,
    5216,  5220,  5228,  5236,  5243,  5257,  5258,  5262,  5266,  5270,
    5274,  5278,  5282,  5289,  5293,  5297,  5298,  5308,  5316,  5317,
    5321,  5325,  5329,  5336,  5338,  5343,  5347,  5348,  5352,  5353,
    5354,  5355,  5356,  5360,  5373,  5374,  5378,  5380,  5385,  5391,
    5395,  5396,  5400,  5405,  5414,  5415,  5419,  5430,  5434,  5435,
    5440,  5450,  5453,  5455,  5459,  5463,  5464,  5468,  5469,  5473,
    5477,  5480,  5482,  5486,  5487,  5491,  5499,  5508,  5509,  5513,
    5514,  5518,  5519,  5520,  5535,  5539,  5540,  5550,  5551,  5555,
    5559,  5563,  5573,  5577,  5580,  5582,  5586,  5587,  5590,  5592,
    5596,  5601,  5602,  5606,  5607,  5611,  5615,  5618,  5620,  5624,
    5628,  5632,  5635,  5637,  5641,  5642,  5646,  5648,  5652,  5656,
    5657,  5661,  5665,  5669
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "STRING", "X_BODY", "IDENT", "aTYPE",
  "ALIAS", "AGGR", "AGGR2", "RANK", "sqlINT", "OIDNUM", "HEXADECIMAL",
  "INTNUM", "APPROXNUM", "USING", "GLOBAL", "CAST", "CONVERT", "CHARACTER",
  "VARYING", "LARGE", "OBJECT", "VARCHAR", "CLOB", "sqlTEXT", "BINARY",
  "sqlBLOB", "sqlDECIMAL", "sqlFLOAT", "TINYINT", "SMALLINT", "BIGINT",
  "HUGEINT", "sqlINTEGER", "sqlDOUBLE", "sqlREAL", "PRECISION", "PARTIAL",
  "SIMPLE", "ACTION", "CASCADE", "RESTRICT", "BOOL_FALSE", "BOOL_TRUE",
  "CURRENT_DATE", "CURRENT_TIMESTAMP", "CURRENT_TIME", "LOCALTIMESTAMP",
  "LOCALTIME", "LEX_ERROR", "USER", "CURRENT_USER", "SESSION_USER",
  "LOCAL", "LOCKED", "BEST", "EFFORT", "CURRENT_ROLE", "sqlSESSION",
  "sqlDELETE", "UPDATE", "SELECT", "INSERT", "LEFT", "RIGHT", "FULL",
  "OUTER", "NATURAL", "CROSS", "JOIN", "INNER", "COMMIT", "ROLLBACK",
  "SAVEPOINT", "RELEASE", "WORK", "CHAIN", "NO", "PRESERVE", "ROWS",
  "START", "TRANSACTION", "READ", "WRITE", "ONLY", "ISOLATION", "LEVEL",
  "UNCOMMITTED", "COMMITTED", "sqlREPEATABLE", "SERIALIZABLE",
  "DIAGNOSTICS", "sqlSIZE", "STORAGE", "ASYMMETRIC", "SYMMETRIC", "ORDER",
  "BY", "EXISTS", "ESCAPE", "HAVING", "sqlGROUP", "sqlNULL", "FROM", "FOR",
  "MATCH", "EXTRACT", "SEQUENCE", "INCREMENT", "RESTART", "MAXVALUE",
  "MINVALUE", "CYCLE", "NOMAXVALUE", "NOMINVALUE", "NOCYCLE", "NEXT",
  "VALUE", "CACHE", "GENERATED", "ALWAYS", "IDENTITY", "SERIAL",
  "BIGSERIAL", "AUTO_INCREMENT", "SCOLON", "AT", "XMLCOMMENT", "XMLCONCAT",
  "XMLDOCUMENT", "XMLELEMENT", "XMLATTRIBUTES", "XMLFOREST", "XMLPARSE",
  "STRIP", "WHITESPACE", "XMLPI", "XMLQUERY", "PASSING", "XMLTEXT", "NIL",
  "REF", "ABSENT", "EMPTY", "DOCUMENT", "ELEMENT", "CONTENT",
  "XMLNAMESPACES", "NAMESPACE", "XMLVALIDATE", "RETURNING", "LOCATION",
  "ID", "ACCORDING", "XMLSCHEMA", "URI", "XMLAGG", "FILTER", "UNION",
  "EXCEPT", "INTERSECT", "CORRESPONDING", "UNIONJOIN", "WITH", "DATA",
  "'('", "')'", "FILTER_FUNC", "NOT", "'='", "ALL", "ANY", "NOT_BETWEEN",
  "BETWEEN", "NOT_IN", "sqlIN", "NOT_LIKE", "LIKE", "NOT_ILIKE", "ILIKE",
  "OR", "SOME", "AND", "COMPARISON", "'+'", "'-'", "'&'", "'|'", "'^'",
  "LEFT_SHIFT", "RIGHT_SHIFT", "LEFT_SHIFT_ASSIGN", "RIGHT_SHIFT_ASSIGN",
  "CONCATSTRING", "SUBSTRING", "POSITION", "SPLIT_PART", "UMINUS", "'*'",
  "'/'", "'%'", "'~'", "TEMP", "TEMPORARY", "STREAM", "MERGE", "REMOTE",
  "REPLICA", "ASC", "DESC", "AUTHORIZATION", "CHECK", "CONSTRAINT",
  "CREATE", "TYPE", "PROCEDURE", "FUNCTION", "AGGREGATE", "RETURNS",
  "EXTERNAL", "sqlNAME", "DECLARE", "CALL", "LANGUAGE", "ANALYZE",
  "MINMAX", "SQL_EXPLAIN", "SQL_PLAN", "SQL_DEBUG", "SQL_TRACE", "SQL_DOT",
  "PREPARE", "EXECUTE", "DEFAULT", "DISTINCT", "DROP", "FOREIGN", "RENAME",
  "ENCRYPTED", "UNENCRYPTED", "PASSWORD", "GRANT", "REVOKE", "ROLE",
  "ADMIN", "INTO", "IS", "KEY", "ON", "OPTION", "OPTIONS", "PATH",
  "PRIMARY", "PRIVILEGES", "PUBLIC", "REFERENCES", "SCHEMA", "SET",
  "AUTO_COMMIT", "RETURN", "ALTER", "ADD", "TABLE", "COLUMN", "TO",
  "UNIQUE", "VALUES", "VIEW", "WHERE", "sqlDATE", "TIME", "TIMESTAMP",
  "INTERVAL", "YEAR", "MONTH", "DAY", "HOUR", "MINUTE", "SECOND", "ZONE",
  "LIMIT", "OFFSET", "SAMPLE", "CASE", "WHEN", "THEN", "ELSE", "NULLIF",
  "COALESCE", "IF", "ELSEIF", "WHILE", "DO", "ATOMIC", "BEGIN", "END",
  "COPY", "RECORDS", "DELIMITERS", "STDIN", "STDOUT", "INDEX", "AS",
  "TRIGGER", "OF", "BEFORE", "AFTER", "ROW", "STATEMENT", "sqlNEW", "OLD",
  "EACH", "REFERENCING", "OVER", "PARTITION", "CURRENT", "EXCLUDE",
  "FOLLOWING", "PRECEDING", "OTHERS", "TIES", "RANGE", "UNBOUNDED", "','",
  "'.'", "':'", "'['", "']'", "'?'", "$accept", "sqlstmt", "$@1", "$@2",
  "$@3", "$@4", "$@5", "$@6", "create", "drop", "set", "declare", "sql",
  "opt_minmax", "declare_statement", "variable_list", "set_statement",
  "schema", "schema_name_clause", "authorization_identifier",
  "opt_schema_default_char_set", "opt_schema_element_list",
  "schema_element_list", "schema_element", "opt_grantor", "grantor",
  "grant", "authid_list", "opt_with_grant", "opt_with_admin",
  "opt_from_grantor", "revoke", "opt_grant_for", "opt_admin_for",
  "privileges", "object_name", "object_privileges", "operation_commalist",
  "operation", "grantee_commalist", "grantee", "alter_statement",
  "passwd_schema", "alter_table_element", "drop_table_element",
  "opt_column", "create_statement", "seq_def", "opt_seq_params",
  "opt_alt_seq_params", "opt_start", "opt_restart", "opt_increment",
  "opt_min", "opt_max", "opt_cache", "opt_cycle", "index_def",
  "opt_index_type", "role_def", "opt_encrypted", "table_def", "opt_temp",
  "opt_on_commit", "table_content_source", "as_subquery_clause",
  "with_or_without_data", "table_element_list", "add_table_element",
  "table_element", "serial_or_bigserial", "column_def",
  "opt_column_def_opt_list", "column_def_opt_list", "column_options",
  "column_option_list", "column_option", "default", "default_value",
  "column_constraint", "generated_column", "serial_opt_params",
  "table_constraint", "opt_constraint_name", "ref_action", "ref_on_update",
  "ref_on_delete", "opt_ref_action", "opt_match_type", "opt_match",
  "column_constraint_type", "table_constraint_type",
  "domain_constraint_type", "ident_commalist", "like_table", "view_def",
  "query_expression", "opt_with_check_option", "opt_column_list",
  "column_commalist_parens", "type_def", "external_function_name",
  "func_def", "routine_body", "procedure_statement_list",
  "trigger_procedure_statement_list", "procedure_statement",
  "trigger_procedure_statement", "control_statement", "call_statement",
  "call_procedure_statement", "routine_invocation", "routine_name",
  "argument_list", "return_statement", "return_value", "case_statement",
  "when_statement", "when_statements", "when_search_statement",
  "when_search_statements", "case_opt_else_statement", "if_statement",
  "if_opt_else", "while_statement", "opt_begin_label", "opt_end_label",
  "table_function_column_list", "func_data_type", "opt_paramlist",
  "paramlist", "trigger_def", "trigger_action_time", "trigger_event",
  "opt_referencing_list", "old_or_new_values_alias_list",
  "old_or_new_values_alias", "opt_as", "opt_row", "triggered_action",
  "opt_for_each", "row_or_statement", "opt_when", "triggered_statement",
  "drop_statement", "opt_typelist", "typelist", "drop_action",
  "update_statement", "transaction_statement", "_transaction_stmt",
  "transaction_mode_list", "_transaction_mode_list", "transaction_mode",
  "iso_level", "opt_work", "opt_chain", "opt_to_savepoint",
  "copyfrom_stmt", "opt_header_list", "header_list", "header", "opt_seps",
  "opt_using", "opt_nr", "opt_null_string", "opt_locked",
  "opt_best_effort", "opt_constraint", "string_commalist",
  "string_commalist_contents", "delete_stmt", "update_stmt", "insert_stmt",
  "values_or_query_spec", "row_commalist", "atom_commalist",
  "value_commalist", "null", "simple_atom", "insert_atom", "value",
  "opt_distinct", "assignment_commalist", "assignment", "opt_where_clause",
  "joined_table", "join_type", "outer_join_type", "join_spec",
  "with_query", "with_list", "with_list_element", "with_query_expression",
  "simple_select", "select_statement_single_row",
  "select_no_parens_orderby", "select_target_list", "target_specification",
  "select_no_parens", "set_distinct", "opt_corresponding", "selection",
  "table_exp", "opt_from_clause", "table_ref_commalist", "simple_table",
  "table_ref", "$@7", "table_name", "opt_group_by_clause",
  "column_ref_commalist", "opt_having_clause", "search_condition",
  "and_exp", "opt_order_by_clause", "opt_limit", "opt_offset",
  "opt_sample", "sort_specification_list", "ordering_spec", "opt_asc_desc",
  "predicate", "pred_exp", "comparison_predicate", "between_predicate",
  "opt_bounds", "like_predicate", "like_exp", "test_for_null",
  "in_predicate", "pred_exp_list", "all_or_any_predicate", "any_all_some",
  "existence_test", "filter_arg_list", "filter_args", "filter_exp",
  "subquery", "simple_scalar_exp", "scalar_exp", "value_exp", "param",
  "window_function", "window_function_type", "window_specification",
  "window_partition_clause", "window_order_clause", "window_frame_clause",
  "window_frame_units", "window_frame_extent", "window_frame_start",
  "window_frame_preceding", "window_frame_between", "window_frame_end",
  "window_frame_following", "window_frame_exclusion", "var_ref",
  "func_ref", "qfunc", "func_ident", "datetime_funcs", "opt_brackets",
  "string_funcs", "column_exp_commalist", "column_exp", "opt_alias_name",
  "atom", "qrank", "qaggr", "qaggr2", "aggr_ref", "opt_sign", "tz",
  "time_precision", "timestamp_precision", "datetime_type",
  "non_second_datetime_field", "datetime_field", "start_field",
  "end_field", "single_datetime_field", "interval_qualifier",
  "interval_type", "user", "literal", "interval_expression", "qname",
  "column_ref", "cast_exp", "cast_value", "case_exp", "scalar_exp_list",
  "case_scalar_exp_list", "when_value", "when_value_list", "when_search",
  "when_search_list", "case_opt_else", "case_scalar_exp", "nonzero",
  "nonzerolng", "nonzerowrd", "poslng", "poswrd", "posint", "data_type",
  "type_alias", "varchar", "clob", "blob", "column", "authid",
  "restricted_ident", "ident", "non_reserved_word", "name_commalist",
  "wrdval", "lngval", "intval", "string", "exec", "exec_ref",
  "opt_path_specification", "path_specification", "schema_name_list",
  "XML_value_expression", "XML_value_expression_list", "XML_primary",
  "XML_value_function", "XML_comment", "XML_concatenation", "XML_document",
  "XML_element",
  "opt_comma_XML_namespace_declaration_attributes_element_content",
  "XML_element_name", "XML_attributes", "XML_attribute_list",
  "XML_attribute", "opt_XML_attribute_name", "XML_attribute_value",
  "XML_attribute_name", "XML_element_content_and_option",
  "XML_element_content_list", "XML_element_content",
  "opt_XML_content_option", "XML_content_option", "XML_forest",
  "opt_XML_namespace_declaration_and_comma", "forest_element_list",
  "forest_element", "forest_element_value", "opt_forest_element_name",
  "forest_element_name", "XML_parse", "XML_whitespace_option", "XML_PI",
  "XML_PI_target", "opt_comma_string_value_expression", "XML_query",
  "XQuery_expression", "opt_XML_query_argument_list",
  "XML_query_default_passing_mechanism", "XML_query_argument_list",
  "XML_query_argument", "XML_query_context_item", "XML_query_variable",
  "opt_XML_query_returning_mechanism", "XML_query_empty_handling_option",
  "XML_text", "XML_validate", "document_or_content_or_sequence",
  "document_or_content", "opt_XML_returning_clause",
  "XML_namespace_declaration", "XML_namespace_declaration_item_list",
  "XML_namespace_declaration_item", "XML_namespace_prefix",
  "XML_namespace_URI", "XML_regular_namespace_declaration_item",
  "XML_default_namespace_declaration_item", "opt_XML_passing_mechanism",
  "XML_passing_mechanism", "opt_XML_valid_according_to_clause",
  "XML_valid_according_to_clause", "XML_valid_according_to_what",
  "XML_valid_according_to_URI", "XML_valid_target_namespace_URI",
  "XML_URI", "opt_XML_valid_schema_location",
  "XML_valid_schema_location_URI", "XML_valid_according_to_identifier",
  "registered_XML_Schema_name", "opt_XML_valid_element_clause",
  "XML_valid_element_clause", "opt_XML_valid_element_name_specification",
  "XML_valid_element_name_specification",
  "XML_valid_element_namespace_specification",
  "XML_valid_element_namespace_URI", "XML_valid_element_name",
  "XML_aggregate", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   421,    40,    41,   422,
     423,    61,   424,   425,   426,   427,   428,   429,   430,   431,
     432,   433,   434,   435,   436,   437,    43,    45,    38,   124,
      94,   438,   439,   440,   441,   442,   443,   444,   445,   446,
      42,    47,    37,   126,   447,   448,   449,   450,   451,   452,
     453,   454,   455,   456,   457,   458,   459,   460,   461,   462,
     463,   464,   465,   466,   467,   468,   469,   470,   471,   472,
     473,   474,   475,   476,   477,   478,   479,   480,   481,   482,
     483,   484,   485,   486,   487,   488,   489,   490,   491,   492,
     493,   494,   495,   496,   497,   498,   499,   500,   501,   502,
     503,   504,   505,   506,   507,   508,   509,   510,   511,   512,
     513,   514,   515,   516,   517,   518,   519,   520,   521,   522,
     523,   524,   525,   526,   527,   528,   529,   530,   531,   532,
     533,   534,   535,   536,   537,   538,   539,   540,   541,   542,
     543,   544,   545,   546,   547,   548,   549,   550,   551,   552,
     553,   554,   555,   556,   557,   558,   559,   560,   561,   562,
     563,   564,   565,   566,   567,    44,    46,    58,    91,    93,
      63
};
# endif

#define YYPACT_NINF -1510

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-1510)))

#define YYTABLE_NINF -1045

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1392,   408, -1510,   342, 14107,   476,   403,   616,   616, 14107,
     624,   632, -1510, 14107,   183, -1510, -1510, 11677, 14107, -1510,
   -1510, -1510, -1510, -1510, -1510,   379, -1510,  1537,   142,   401,
     326,   279,   753,  1043,   583, 11947, 10867,   629, -1510, -1510,
   -1510, -1510, -1510, -1510, -1510, -1510, -1510, -1510, -1510, -1510,
   -1510, -1510, -1510, -1510, -1510, -1510, -1510, -1510, -1510, -1510,
   -1510, -1510, -1510,   689,   633, -1510, 14107, -1510, -1510, -1510,
   -1510, -1510, -1510, -1510, -1510, -1510, -1510, -1510, -1510, -1510,
   -1510, -1510, -1510, -1510, -1510, -1510, -1510, -1510, -1510, -1510,
   -1510, -1510, -1510, -1510, -1510, -1510, -1510, -1510, -1510, -1510,
   -1510, -1510, -1510, -1510, -1510, -1510, -1510, -1510, -1510, -1510,
   -1510, -1510, -1510, -1510, -1510, -1510, -1510, -1510, -1510, -1510,
   -1510, -1510, -1510, -1510, -1510, -1510, -1510, -1510, -1510, -1510,
   -1510, -1510, -1510, -1510, -1510, -1510, -1510, -1510, -1510, -1510,
   -1510, -1510, -1510, -1510, -1510, -1510,   517,   473, -1510, -1510,
   -1510,  4132, 14107, -1510,   622,   622, -1510, 14107,   777,    48,
   -1510,   670,   476,   764, -1510, -1510, -1510, -1510,   676, -1510,
     536,   670,  2532,  2532,  1392,  1392,  2532,  2532, -1510, -1510,
     698, -1510, -1510, -1510, -1510, -1510, -1510, -1510, -1510,   670,
     670, -1510,   593, -1510,   670,   197,   608,   644,   554, -1510,
   -1510, -1510,   653,   664,    54,  1066,   836,   777, 13027, 14107,
   14107, -1510,   922,   694,    49, -1510, -1510,  -156, -1510, -1510,
     587, 14107,   725, 14107,   727, -1510, -1510,   687,   721,   724,
     738, 14107, 14107, 14107, 14107, 14107, 14377, 14107, -1510, 14107,
   14107,   658, -1510, -1510,   741, -1510, 14107, 14107,   793,   679,
   14107, 14107, 14107, 14107, 14107, 14107, 14107, 14107, 14107, -1510,
   -1510, -1510,   807, 14107, 14107,   756,   863,   888,   783,   800,
   14107,   744, -1510,   134, -1510, -1510,   978,   499,   499,   499,
     815, -1510,   830, 13297, 14107,  1101,  1101,  1101,  1108,   915,
     950,   956, -1510, -1510, -1510, -1510, -1510,   958,   966,  1113,
   -1510, -1510, -1510,   970,   970,   970,   970,   970, -1510,   992,
   -1510,   993,  1034, 14107,   996,   998,  1000,  1014,  1015,  1016,
    1018,  1025,  1026,  1027,  1030,  3154,  4458,  8543,  8543,  1031,
    1032,  1033, -1510,  8543,  1101,   107,   254,    84,  6689,  1037,
    1039,  4458, -1510, -1510,   252,   857,  1019, -1510,  1181, -1510,
   -1510, -1510, -1510, -1510, -1510, -1510, 14107, -1510, -1510, -1510,
    2876, -1510, -1510, -1510,   895, -1510,   869, -1510, -1510,   886,
   -1510, -1510,  1045,  1049,  1050,   899, -1510, -1510, -1510, -1510,
   -1510, -1510,  1101,  1101,    78, -1510, -1510, -1510, -1510, -1510,
   -1510, -1510, -1510, -1510, -1510, -1510, -1510, -1510,   340,   876,
   -1510,   953, -1510,   880,  1132,  1127, -1510,   897, -1510, 14107,
   -1510, -1510, 14107,   921, -1510,  4132, -1510,  6998, 11677,   942,
    1102,  1103, -1510, -1510,  1105,  1106,  5110, -1510, -1510, -1510,
   -1510,    83,  1066,    83, 14647,   205,  1122,  1129,  1131,   -43,
     777, -1510,   742,   249,  1130,   618, -1510,    26,  1006, 14107,
     922,   957, -1510, -1510,  1078, -1510, -1510,   951, 14107, 14107,
   14107, 14107, 14107,  1036,  1087,  1096,  1097,  1110, 14107,  1048,
    1070,  1118,   670,   716, 14107, 14107, -1510, -1510, 14107,  1068,
   14107, 14107, 14107,  1120,  1120,  1120, -1510,   986,   986,   986,
   -1510, -1510, 14107, -1510, -1510,    74, 14107,  8543, 14107,  1123,
    1135, -1510,   410, -1510, -1510, -1510,  1136,  1137, -1510, -1510,
   -1510, -1510, -1510,  1251, -1510, -1510,  1142,  1144,   810, 14107,
   -1510, -1510, -1510,  1147,  1148,  1149,  1153,  8543, -1510, -1510,
    1133,  1133,  1133,    35,  1054,  4458, -1510,  1126,  -170, -1510,
    1128, -1510,   972, -1510, -1510, -1510,  4458,  4458,  1305,  1164,
   -1510, -1510, -1510, -1510, -1510,   366, -1510,   900,  1232, -1510,
    8543,  8543,  8543,  1119,  1191,   -18,  1124,  1339,  8543,    -4,
    8543,  3154,  1177,  1179,   812,  1182,   732,   248, -1510,   194,
    1611,  3154,   794,   794,  8543,  8543,  8543, -1510, -1510,   379,
    1180,   379,  1180, -1510, -1510,  1101,  4458,  2210, -1510,   420,
    8543,  8543,  1611,    97,  2777, 14107, -1510,   830, 14107, -1510,
    4458,  4458,   959,   959,  1184,  1186,  8543,  8543,  8543,  8543,
    4458,  3480,  1021,  8543,  8543,  8543,  8543,  8543,  8543,  8543,
    8543,  8543,  8543,  8543,  8543,  8543,   271,  1196,  1167,  4132,
    1208,  5419,  8543, -1510, -1510, 11137, 12487,  1115,  1177, -1510,
     428, -1510, -1510,  1307,  1311, -1510, -1510, -1510,   868,   379,
     777, -1510,   255,  1220,  1283, -1510, -1510,  4120,   277, -1510,
   -1510,    53,  1162, -1510, -1510, -1510, -1510,  3154, -1510,   293,
   -1510, -1510,   881, -1510,    85, -1510, -1510, -1510,   184, 14107,
   -1510, -1510, -1510, -1510, -1510,    83,    83, -1510, -1510, -1510,
    1154,   742,  1125,  1139, -1510,  1225, -1510,  1285,   525,   455,
    1138,   797,    34,    34, 14107,   670,  1107,   922,   742,  2084,
    1233,  1118,  1118,  1118,  1118,  1183, 13567, 13567, 13567,  1155,
   -1510, -1510, -1510,  1382,  1156, 14107, 12757, -1510, -1510,  1104,
    1109, -1510, -1510,   859,  1157,  1118,  1120, 14107,   986,   986,
     986,  1464,   986,   986,   986, -1510, -1510, -1510, -1510, -1510,
   -1510, -1510,   907, -1510, -1510, -1510,   134,   379,   379, -1510,
    1387,   379,   379,   379, -1510,  1180,  1180, -1510, -1510, -1510,
   -1510, -1510,  1144,  1142,  1145, -1510, -1510, -1510,   379,   379,
     379,   379,  1090, -1510,  3911,  1319,   183,   183,   183, -1510,
   -1510, -1510, -1510,    35,   942, -1510,   992, 13297, -1510,  4458,
   14107, -1510,  1121,  1099, -1510, -1510, -1510, -1510,  1317, 14107,
    4120,   522,  4120, -1510,    75, -1510,  1274, 14107,  1260,  8543,
    1111, -1510, -1510,  8543, 14107, -1510,  1289,   522, -1510,  8543,
   -1510,  1332,   816,  8543,   299, -1510, -1510, -1510,   890,  4458,
   12217,  1079,  2778,  1689,  1264,  1161,  1101,  1266,  1101,   810,
    1150,  8543, -1510,   452,  8543, -1510,  1141,  1706,  1114,   302,
    4458, -1510,  2062, -1510, -1510,  1116, -1510,   617, 14917, 14917,
   14917,   219,     4, -1510, -1510,  1337, -1510, -1510,  1194, -1510,
   -1510,  4458,  4458,  7307,  7307, -1510,  2046, -1510, -1510, -1510,
   -1510, -1510, -1510, -1510, -1510,   992, -1510,   794,   794,   794,
     794,   794,   794,   794,   794,   794,   794,  1240,  1240, -1510,
   -1510,  1340,  1134, -1510, -1510, -1510,  8543,  1277,  8543,  4120,
    1279,   226,  1151,  1281,  1282,  1284, -1510,   227, -1510,  1152,
   -1510, -1510, 14107,  1013,  1368, -1510, -1510, -1510, -1510, -1510,
     183, -1510,  8543, -1510, -1510, -1510, -1510, -1510, -1510, -1510,
    7307,  1211,    83,  1353,  1216,  1353, -1510,    16,    16,  1101,
    1218, 14107, 14107,    69,  1362,   320, 14107, 14107, -1510, -1510,
   14107,  1376,  1028, -1510, 14107, 14107, 13837, -1510,  1359,  1172,
    1359,  1373,  1374, -1510, -1510,  1222,  1398, 13567, -1510, -1510,
    1231, -1510, 14107, -1510,  1314,  1158,  2084,  1318,  1334,   584,
    1226, 14107,   713, -1510, -1510, 14107, 14107,   304, -1510, -1510,
   -1510, -1510, -1510,   602, -1510,   697,   212,   599,   599, -1510,
    1197, -1510,  1237, 14107,  1254,   986,   986, -1510, -1510, -1510,
   -1510,  1341,  1185, -1510, -1510, -1510, -1510,  1343, -1510,  1344,
   -1510,  1345,   311,  1346,  1190, -1510, -1510, -1510,  1239,  1047,
    1349,  1195,  1354,  1356,  1357,  8543, -1510, -1510, -1510,  1360,
   -1510, -1510, -1510, -1510, -1510, -1510, -1510, -1510, -1510, -1510,
    2084,  2084,  8543, -1510,   589,  1358,  8543,  1361,  1363, -1510,
    1203,  7616,  4120,   215, -1510,  1204, -1510,   362, -1510,  1207,
    1408,  1274,  1365,  1366,  1274,   994,   314, -1510, -1510, -1510,
    1367,  1370,  1371,  1611,  8543,  8543,  8543,  8543, -1510,  1258,
   -1510, -1510, -1510, -1510,  8543,  2159, -1510,  1238,  4120, -1510,
    8543,  8543, -1510,  8543,  1611,  2062,  1372,   617,   183,  2777,
   -1510, -1510, -1510,   960,  1470,  2777, -1510,  2777,  1478,  1483,
   14107, -1510,  1385, -1510, -1510, 11677, 14107, -1510,  1455,  1453,
    1502,  1588,   317,   319,  1101, -1510, -1510,  1459,  1393,  1465,
    1394, -1510,  1397, -1510, 11407,  8543, 14107, -1510, -1510, -1510,
   -1510,  1399, -1510, -1510,  1315, -1510,   584, -1510,  1323, -1510,
   -1510, -1510,  1559,  1101, -1510, -1510, -1510, -1510,   922,   922,
   -1510,   500,   986,   986,   986, -1510, -1510, -1510,  -114, -1510,
   -1510,  1273, -1510,  1101, -1510,   231,    55,  1101,  1413, -1510,
    1285,  1411,  1581, -1510,  8833, 14107, -1510,  1369,  1383, -1510,
   -1510, -1510, 14107, -1510,  1261, -1510,  1364,   717, -1510,   713,
   -1510, -1510, -1510, -1510, -1510, -1510, -1510, -1510, -1510, 12757,
    1336,  1338,   670, -1510, -1510, -1510, -1510,   779,  1342,  1423,
    1425, 14107, 14107,  1424,  1519, -1510, -1510, -1510, -1510,  2084,
   -1510, -1510, -1510, -1510,   379, -1510,   379,  1144, -1510, -1510,
   -1510,   379, -1510, -1510, -1510, -1510, 14107,  1428,  1434,  2906,
   -1510, -1510, -1510, -1510, -1510, -1510,  5728,  1274,  1375,  8543,
    4120,   324, -1510,  1301, -1510, -1510,   740,  8543,  1274, 14107,
   -1510,  1469,  1471,  1443,  8543,  1274,    -6,  8543, -1510,  1408,
   -1510,  1347,  1444, -1510,  1446, -1510,  8543,  8543,  7307,  7307,
    2271,  1612,  2941,  1728, -1510, -1510,  8543, -1510,  3142, -1510,
   -1510, -1510,   101,   617,  2777,  1546,  2777,   383,   383,  2777,
   -1510,  1452, 14107,   230, -1510, 14107,  4458, -1510,  4458,  4458,
   -1510, -1510, -1510, 14107, -1510,  1528,   -26, -1510, -1510,  1462,
    1472, -1510, -1510, -1510, -1510, -1510,  1325,  1379, -1510, -1510,
   -1510,   922, -1510,  1523, -1510, -1510, -1510,  1404,   330, -1510,
    1101,  1320,  1101,  1565,  1321, -1510,  1480,  1480,  1426,   922,
     320,  1429, -1510,   476,   624,   632,  1427, 11677,  3806,  7925,
    4458,  1377, -1510, -1510, -1510, -1510, -1510, -1510, -1510, -1510,
   -1510, -1510, -1510, -1510, -1510, -1510, -1510, -1510,  1391, -1510,
   -1510, -1510, -1510,  1326,  2084,  1691,  1691, -1510, 14107, -1510,
   -1510,  1487,   670,   670, -1510,  1533, -1510,  8543, -1510,   779,
   -1510, -1510, -1510, -1510,   505,  1490,   312, -1510,  1447, -1510,
    1378,  1348, 14107,   214, -1510,  1491, -1510,  1495, -1510,  1496,
     327, -1510,  1380, -1510, -1510, -1510,  1498,  4120,  1388, -1510,
     360, -1510,  1389,  1499, -1510, -1510, -1510,  7616, 14107,  1439,
    1441,  1442,  1445, -1510, -1510,  1531, -1510, -1510, -1510, -1510,
   -1510,   542,  1532, -1510, -1510,   313,  1405, -1510, -1510, -1510,
     323, -1510,  1510, -1510, -1510, -1510,   370,   376,   386,  8543,
   -1510, -1510,  8543, -1510,  8543, -1510, -1510, 14917, -1510,  2777,
   -1510,   670,  4458, -1510, -1510,   383, 14107,   411,  1406, -1510,
    1516,  1516,  1406,  8543, -1510, -1510, -1510,  4784, -1510, -1510,
    1460,  1449, -1510,   922,   635, -1510,   406, -1510,  1600,  8543,
   -1510,  1101,   429,  1494, -1510,  1101, 14107,    34,    34,  1101,
   -1510,   500,  1507,  4132, 14107, -1510,  1538, -1510,  1545, -1510,
   -1510, -1510,  4458, -1510,   537,  2619,  1458, -1510, 10021,  4458,
   -1510, -1510,  1566,  9139, -1510,   336, -1510,  1475, -1510,  1430,
   -1510,  4237, -1510, -1510,  1635,  1573,  1493, 14107, -1510, -1510,
   -1510,   625,  1580, -1510,  1497,   804,  1641,   442,  1669,  1670,
   -1510, -1510, -1510, -1510, -1510, 14107, 14107,  8543,  8543,  8543,
   -1510,  8234, -1510, -1510, -1510, -1510,  1648,   334,  1649,  1651,
   -1510, -1510, 14107, -1510, -1510,  8543,  1508,  1520,  1589,   358,
   -1510, -1510, -1510,  3279,  3605,  3794, -1510, -1510, -1510, -1510,
   -1510,   460, -1510,  1090,  6037,  1451,  1454,  1456,  1461, -1510,
   -1510, -1510,  1101, 14107, -1510, -1510, -1510, -1510, -1510, -1510,
   -1510, -1510,  1468, -1510, -1510, -1510,   463, -1510,  1774,  1359,
    1359,  1525,  1523, 14107,  1534, -1510,  1482,  8543,   599,  1522,
   -1510, -1510,  1500,  8543, -1510,   613, -1510, 10021,  1668,  1517,
   14107,  1593,  1805, -1510,  1594,  1813, 14107,  1696, -1510,  4458,
   -1510,   670,   472, -1510, -1510, -1510,   352,   436,   804, -1510,
    1509, -1510,  1535, -1510, -1510, -1510, -1510,  1501,  4120,   491,
   -1510,  1524, -1510, -1510,  1505, -1510, -1510,  1672, -1510, -1510,
   -1510,  1408, -1510,  1679,  1681, -1510,  1682, 14107,  1828,   -14,
   -1510, -1510, -1510, -1510, -1510, -1510,  1650, -1510, -1510, -1510,
      23, -1510, -1510, -1510,  1101, -1510, 14107, -1510,  1780,  1780,
   14107,   635, -1510, 14107,   492,  4120,  1671, -1510,  9445,  1552,
    2193, -1510,  1541,  2415,  1713,  1548, -1510,   509,  2084, 14107,
    1839, 14107,  1842,   670,  1683,  1684,  1742, -1510,   625,  1273,
   -1510,  1273,  1273,  1273, -1510,   821,  4458, 10291, -1510,  8543,
   14107, -1510,  8543, -1510, -1510, -1510, -1510,  1701, -1510, -1510,
   -1510,  1701, -1510,  1705, 14107,  1828, -1510, -1510, -1510,  1710,
    6363,  1539, -1510,  1549, -1510, -1510, -1510, -1510,  1802,  1802,
   -1510, -1510, -1510, -1510,  8543, -1510,  9445,  1735, -1510, -1510,
    1578, -1510,  4458,  1567,  1568, -1510,  9751, -1510, 14107, -1510,
   -1510, -1510, -1510, -1510,  1742,  1398, -1510, -1510,   806,  1616,
   -1510, 14107, 14107, 14107, 14107, -1510, -1510, -1510, -1510,  1575,
   -1510, -1510, -1510, -1510, -1510, -1510, -1510, -1510, -1510, -1510,
   -1510, -1510, -1510, -1510,  1828, -1510, -1510, -1510, -1510, -1510,
   -1510, -1510, -1510, -1510,  1562,  1553,  1554, -1510, -1510, -1510,
   -1510,  1810,  1565,  1565,  4120, -1510,  9445, -1510,  9445,  1586,
    1595, -1510,  1610,  2084,  1616,  1719, -1510, -1510, -1510, -1510,
    1058,  1654,  1655, -1510, -1510, -1510, -1510, -1510, -1510, -1510,
   -1510, -1510, -1510, -1510, -1510, -1510, -1510, -1510, -1510, 14107,
   -1510, -1510, -1510,   181,   181,  1848, -1510,  1849, -1510, 10597,
    2415, -1510, -1510, -1510, -1510,  1869,   131, -1510, -1510, -1510,
    1785, -1510, -1510, -1510, -1510, -1510
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,     0,    19,     0,     0,   475,     0,   416,   416,     0,
       0,     0,    17,     0,     0,    20,    23,     0,     0,     7,
       5,    11,    13,     9,     3,     0,    21,     0,    80,    22,
       0,   439,     0,   160,     0,     0,     0,     0,    30,    31,
      24,    25,    26,    29,    27,   132,   131,   129,   130,    33,
     133,    28,   390,   389,   395,   394,   391,   393,   392,   499,
     517,   505,   506,   554,     0,    18,     0,   852,   853,   855,
     856,   857,   858,   860,   862,   907,   865,   873,   896,   870,
     909,   884,   895,   889,   868,   931,   890,   879,   880,   881,
     877,   871,   887,   910,   911,   912,   913,   914,   915,   916,
     917,   918,   919,   920,   921,   922,   923,   924,   925,   926,
     888,   854,   928,   927,   875,   869,   861,   894,   929,   930,
     903,   882,   905,   906,   904,   901,   902,   878,   863,   867,
     893,   891,   864,   866,   883,   908,   886,   876,   897,   898,
     899,   900,   872,   874,   892,   885,     0,   773,   859,   476,
     477,     0,     0,   415,   419,   419,   397,     0,   403,     0,
     502,   254,   475,     0,   688,   686,   687,   301,     0,   683,
     685,   254,     0,     0,     0,     0,     0,     0,   937,   936,
       0,   940,   846,   847,   848,   849,   850,   851,    93,   254,
     254,    92,    88,    97,   254,     0,     0,     0,    89,    90,
      70,   845,     0,     0,     0,     0,     0,   403,     0,     0,
       0,   935,     0,     0,     0,   251,   250,     0,   802,     1,
       0,     0,     0,     0,     0,   173,   172,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   159,     0,
       0,     0,   126,   127,     0,   128,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   753,
     755,   754,   896,   867,   883,   898,     0,     0,   928,   927,
     886,    36,    37,     0,   246,     2,     0,   518,   518,   518,
     556,    15,   482,     0,     0,   938,   852,   853,   855,   856,
     857,   858,   759,   758,   757,   760,   761,     0,     0,     0,
     842,   770,   771,   695,   695,   695,   695,   695,   637,     0,
     470,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   706,     0,   897,   898,   899,   900,     0,     0,
       0,     0,   651,   650,   526,   710,   551,   582,   553,   572,
     573,   574,   575,   576,   577,   578,     0,   579,   634,   633,
     580,   616,   649,   638,     0,   640,   642,   644,   645,   524,
     704,   635,     0,     0,     0,   641,   636,   712,   765,   639,
     647,   646,     0,     0,   776,   756,   648,   951,   952,   953,
     954,   955,   956,   957,   958,   959,   960,   725,   460,     0,
     396,   420,   398,     0,     0,     0,   400,   404,   405,     0,
     500,   504,     0,     0,   255,     0,   516,     0,     0,   562,
       0,     0,    12,    14,     0,     0,     0,    94,    95,    87,
      96,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     403,   402,   163,     0,   141,     0,   441,     0,     0,     0,
       0,   440,   177,   176,     0,   175,   174,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    64,   875,    53,
      49,   254,   254,     0,     0,     0,   378,   135,     0,     0,
       0,     0,     0,   381,   381,   381,   377,   386,   386,   386,
     379,   380,     0,    44,    42,     0,     0,     0,     0,   834,
     829,   836,   805,   837,   839,   840,   818,   821,   813,   814,
     816,   817,   815,   824,   826,   735,   732,   734,     0,     0,
     827,   828,    38,   831,   806,   807,   811,     0,   519,   520,
     521,   521,   521,     0,   559,     0,   456,     0,   482,   478,
       0,   844,   774,   939,   769,   767,     0,     0,     0,     0,
     690,   692,   691,   694,   693,     0,   608,     0,     0,   680,
       0,     0,     0,     0,   994,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   553,     0,   642,   776,
     581,     0,   630,   631,     0,     0,     0,   625,   762,     0,
     730,     0,   730,   726,   727,     0,     0,     0,   794,   796,
       0,     0,   609,     0,     0,     0,   507,   482,     0,   709,
       0,     0,   587,   587,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   768,   766,     0,     0,     0,     0,   463,
     460,   458,   417,     0,     0,   399,   408,   407,     0,     0,
       0,   501,     0,     0,   526,   681,   786,   471,     0,   684,
     685,     0,    34,     8,     6,    10,     4,     0,   941,     0,
     473,   468,   474,   100,    74,    98,   101,    71,    72,   886,
      84,    86,    91,    81,    83,     0,     0,   401,   165,   164,
       0,   163,     0,     0,   109,   142,   136,   145,   125,     0,
     125,   125,   433,   433,     0,   254,     0,     0,   163,     0,
       0,   254,   254,   254,   254,     0,   336,   336,   336,     0,
     161,    50,    52,     0,   943,     0,   216,   166,   183,     0,
       0,   340,   341,     0,     0,   254,   381,     0,   386,   386,
     386,     0,   386,   386,   386,   388,   387,    48,   367,   376,
      41,    45,   728,    46,    43,    40,     0,     0,     0,   838,
       0,     0,     0,     0,   825,   730,   730,   738,   739,   740,
     741,   742,   734,   732,     0,   751,   752,   247,     0,     0,
       0,     0,   555,   566,   569,   522,     0,     0,     0,   558,
     557,   801,   934,     0,   562,   483,     0,     0,   457,     0,
       0,   781,     0,     0,   843,   696,   744,   743,     0,     0,
       0,   616,   950,   948,  1031,   947,  1031,     0,     0,     0,
       0,  1029,  1030,     0,     0,  1011,  1012,   616,  1028,     0,
    1027,   554,     0,     0,     0,   615,   613,   632,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   791,   796,     0,   795,     0,     0,     0,     0,
       0,   611,     0,   538,   537,   527,   534,   528,   536,   533,
     530,   773,   526,   510,   512,   544,   711,   550,   584,   588,
     589,     0,     0,     0,     0,   590,   594,   592,   591,   593,
     552,   607,   605,   606,   583,     0,   612,   617,   618,   623,
     624,   622,   626,   627,   628,   629,   702,   619,   620,   621,
     597,     0,   656,   708,   705,   653,     0,     0,   878,   798,
       0,   776,     0,   856,   857,   858,   707,   777,   461,   462,
     459,   418,     0,     0,     0,   414,   409,   410,   406,   256,
       0,   682,     0,   564,   565,   563,   803,    35,    32,   942,
       0,     0,     0,    76,     0,    76,    85,    76,    76,     0,
       0,     0,     0,     0,     0,   147,     0,     0,   124,   105,
       0,     0,     0,   104,     0,     0,   216,   438,   444,     0,
     444,     0,     0,   442,   443,     0,   139,   336,   167,   168,
       0,   169,     0,   335,     0,   334,     0,     0,     0,     0,
       0,     0,    55,   944,    51,     0,     0,     0,   191,   187,
     189,   192,   190,     0,   193,     0,   844,     0,     0,   343,
     344,   342,     0,     0,   178,   386,   386,   375,   372,   374,
     383,     0,   384,   371,   368,   370,    39,     0,   799,     0,
     841,     0,     0,     0,   799,   736,   737,   749,   748,     0,
       0,   799,     0,     0,     0,     0,   570,   571,   568,     0,
     513,   514,   515,   561,   560,   509,   481,   479,   480,   775,
       0,     0,     0,   643,     0,     0,     0,     0,     0,   973,
     965,     0,   999,   986,   996,  1000,   995,   616,  1007,  1008,
       0,  1031,     0,  1048,  1031,   613,     0,   472,   466,   614,
       0,     0,     0,   603,     0,     0,     0,     0,   731,     0,
     763,   733,   764,   772,     0,     0,   792,     0,   797,   785,
       0,     0,   783,     0,   610,     0,   537,     0,     0,     0,
     494,   495,   496,     0,     0,     0,   491,     0,     0,   493,
     874,   535,   543,   532,   531,     0,     0,   508,     0,   548,
       0,     0,     0,     0,     0,   604,   596,     0,     0,   658,
       0,   719,     0,   723,     0,     0,     0,   421,   411,   412,
     413,     0,   787,   469,     0,    99,     0,    69,     0,    68,
      78,    79,     0,     0,   110,   113,   144,   143,     0,     0,
     149,   150,   386,   386,   386,   107,   108,   106,     0,   103,
     102,   354,   426,     0,   425,     0,     0,     0,     0,   134,
     145,     0,     0,   257,   326,     0,   338,     0,     0,    66,
      67,    65,     0,   932,   946,   945,   160,     0,    47,    56,
      57,    59,    60,    63,    61,    62,   248,   217,   182,   216,
       0,     0,     0,   215,   194,   195,   197,   198,     0,     0,
     252,     0,     0,     0,     0,   171,   369,   373,   382,     0,
     835,   830,   808,   819,     0,   822,     0,   734,   746,   750,
     832,     0,   809,   810,   812,   567,     0,     0,     0,     0,
    1033,  1032,   961,   949,   962,   963,     0,  1031,   909,     0,
    1040,     0,  1035,     0,  1037,  1038,     0,     0,  1031,     0,
     998,     0,     0,     0,     0,  1031,     0,     0,  1014,  1021,
    1025,     0,     0,  1049,     0,   464,     0,     0,     0,     0,
       0,     0,     0,     0,   729,   793,     0,   784,     0,   788,
     789,   484,     0,   529,     0,     0,     0,     0,     0,     0,
     492,   541,     0,   774,   511,     0,     0,   525,     0,     0,
     598,   599,   595,     0,   652,     0,   660,   722,   721,     0,
       0,   778,   503,    75,    77,    73,     0,   112,   146,   800,
     148,     0,   152,   153,   122,   123,   121,     0,     0,   355,
       0,   434,     0,   450,   452,   454,   427,   427,     0,     0,
     147,     0,   170,   475,   870,   884,     0,     0,     0,     0,
       0,   270,   282,   283,   276,   277,   278,   281,   279,   266,
     267,   284,   295,   294,   299,   298,   297,   296,     0,   280,
     275,   274,   285,     0,     0,     0,     0,    54,     0,    58,
     188,   844,     0,     0,   242,     0,   212,     0,   196,   199,
     200,   205,   206,   207,     0,     0,     0,   184,     0,   249,
     345,   346,     0,     0,   385,     0,   804,     0,   747,     0,
       0,   546,   776,   779,   780,   689,     0,   985,   970,   972,
     986,   983,   966,     0,  1043,  1042,  1034,     0,     0,     0,
       0,     0,     0,   987,   997,     0,  1002,  1001,  1004,  1005,
    1003,   616,     0,  1047,  1046,   616,  1013,  1015,  1017,  1018,
       0,  1022,     0,  1026,  1073,   467,     0,     0,     0,     0,
     699,   700,     0,   701,     0,   790,   782,     0,   488,     0,
     485,     0,     0,   487,   486,     0,     0,     0,   545,   549,
     585,   586,   657,     0,   662,   663,   655,     0,   720,   724,
       0,     0,   151,     0,   155,   118,     0,   116,     0,     0,
     445,     0,     0,     0,   424,     0,     0,   433,   433,     0,
     140,   150,     0,     0,     0,   300,     0,   303,   886,   308,
     307,   309,     0,   317,   319,     0,     0,   270,   326,     0,
     327,   337,     0,   326,   333,     0,   933,     0,   243,     0,
     208,   209,   201,   237,     0,     0,     0,     0,   238,   210,
     241,   216,     0,   186,     0,     0,   359,     0,     0,     0,
     181,   820,   823,   833,   523,     0,     0,     0,     0,     0,
     982,     0,   964,  1036,  1039,  1041,     0,     0,     0,     0,
     993,  1006,     0,  1019,  1045,     0,     0,     0,     0,     0,
     465,   600,   601,     0,     0,     0,   539,   490,   498,   497,
     489,     0,   542,   659,     0,     0,     0,   616,   675,   664,
     667,   665,     0,     0,   154,   156,   157,   138,   119,   120,
     117,   115,   435,   453,   451,   455,     0,   429,   431,   444,
     444,     0,   153,     0,     0,   265,     0,   304,     0,     0,
     270,   318,     0,     0,   314,   319,   270,   326,     0,     0,
       0,     0,   894,   260,     0,     0,     0,     0,   236,     0,
     239,   254,     0,   203,   185,   253,   356,   356,   347,   348,
       0,   339,   363,   158,   179,   180,   547,   777,   980,     0,
     975,   978,   971,   984,   967,   969,   988,     0,   991,   990,
     989,  1044,  1016,     0,     0,  1010,     0,     0,     0,  1062,
    1051,  1052,   697,   698,   703,   540,     0,   668,   666,   669,
       0,   661,   111,   114,     0,   428,     0,   432,   446,   446,
       0,   155,   262,     0,     0,   305,     0,   270,   320,     0,
       0,   315,     0,   322,     0,   271,   270,     0,     0,     0,
       0,     0,     0,   254,   213,     0,   234,   202,   216,   354,
     357,   354,   354,   354,   349,     0,     0,   326,   974,     0,
       0,   977,     0,   992,  1020,  1023,  1024,  1057,  1061,  1060,
    1056,  1057,  1055,     0,     0,     0,  1050,  1063,  1064,  1066,
       0,     0,   677,     0,   678,   436,   430,   447,   448,   448,
     162,   137,   258,   302,     0,   310,   316,     0,   312,   270,
       0,   270,     0,     0,   271,   268,   326,   332,     0,   330,
     259,   261,   263,   264,   234,   139,   211,   245,   230,   225,
     204,     0,     0,     0,     0,   361,   362,   360,   364,     0,
     290,   291,   288,   289,   365,   292,   358,   287,   286,   293,
     976,   981,   979,   968,     0,  1054,  1053,  1069,  1072,  1068,
    1071,  1070,  1065,  1067,     0,     0,   616,   670,   672,   679,
     676,     0,   450,   450,   306,   271,   313,   311,   323,     0,
       0,   269,     0,     0,   225,     0,   232,   233,   231,   235,
       0,   226,   227,   240,   353,   351,   352,   350,   272,  1059,
    1058,   673,   671,   674,   449,   423,   422,   270,   321,   328,
     331,   244,   214,     0,     0,     0,   229,     0,   228,   326,
     322,   325,   329,   219,   220,     0,     0,   224,   223,   366,
       0,   324,   218,   221,   222,   273
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1510,   965, -1510, -1510, -1510, -1510, -1510, -1510,  -930,  -929,
   -1510, -1510,   681, -1510,    12, -1510,    18,   481, -1510,  1192,
   -1510, -1510, -1510,   686, -1510,   745,     0,  1721, -1510, -1510,
      41,     6, -1510, -1510,  1729, -1510, -1510, -1510,  1503,  -379,
     973,    56, -1510, -1510, -1510,   438,    66, -1510,    57, -1510,
   -1510, -1510,   719,   540,   371,   253,   160, -1510, -1510, -1510,
    -228,  1908, -1510, -1510,   169, -1510, -1510, -1510,   961,   699,
   -1510, -1510, -1510, -1510, -1510, -1510, -1397, -1510,   387, -1510,
   -1510, -1510, -1510,  -694,   -11,    15,    13,    25, -1510,    86,
   -1510, -1510, -1510,   -34, -1510, -1510,   -24, -1510,  -145,  -273,
   -1510, -1015, -1510,   365, -1441, -1510, -1201,    -8, -1445, -1510,
     493, -1510, -1510, -1510, -1510, -1510, -1510,   261, -1510,   384,
   -1510,   262, -1510,     1, -1510, -1510, -1510, -1510,   534,  -653,
   -1510, -1510, -1510, -1510, -1510, -1510,   244,  -796,   246, -1510,
   -1510, -1510, -1510, -1510,    79,  -416,   705,  -390,    24,    30,
   -1510,  -154, -1510,  1322, -1510,  1971,  1825, -1510, -1510,   586,
   -1510,   209,  -696, -1510, -1510,  -970,   210,   139,  -780,   774,
     600, -1510, -1510, -1510,  1386,  1350,   668,  -853, -1510,  -383,
     665,  1044,  -157, -1510,  1199,  -110,  -799,   854, -1510, -1277,
     -30, -1510,  1598,  1053, -1510,    36,   -28, -1510,   852,    70,
     872,   626,  -402,  1140, -1510, -1510, -1510,  -571, -1510,  -848,
   -1510, -1231, -1510,  -298,  1390,  1168, -1510, -1510,  1209,   468,
     947, -1510, -1510,  -278, -1510, -1510,  1402, -1510,   432, -1510,
   -1510, -1510, -1510, -1510, -1510, -1510,  1396, -1510,  -208, -1046,
    1416,  -546,  -427, -1510, -1510, -1510, -1510, -1510, -1510, -1510,
   -1510,   355, -1510, -1510, -1510, -1510, -1510, -1510,   -13, -1510,
    -381, -1510,   802, -1510, -1510,  1381, -1510, -1510, -1510, -1510,
   -1510, -1510, -1510,  -495,  -477,  -498, -1510,  -536, -1510, -1510,
   -1510, -1510,  1165, -1510,  1986, -1510,  1530,   349, -1243, -1510,
    1476, -1510, -1510, -1510,  1163, -1510,  1431, -1510,  1166,  -591,
     356, -1164, -1510,  -203,  1249, -1510,  -245,  -262, -1510, -1510,
    -248,  -275,    11, -1510,    68, -1510, -1257,  1521,  -518,    32,
    -226, -1510, -1510, -1510, -1510, -1510,  -492, -1510, -1510, -1510,
   -1510, -1510, -1510, -1510, -1510, -1510,   397, -1510,   236, -1510,
   -1510, -1510, -1509, -1510,   427,   579, -1510, -1510, -1510, -1510,
     754, -1510, -1510, -1510, -1510, -1510, -1510, -1510, -1510, -1510,
   -1510, -1510, -1510, -1510,   415, -1510, -1510, -1510, -1510, -1510,
   -1510, -1510,  1504,  -730,   766, -1510,   576, -1510,   765, -1510,
   -1510,   315,  -965, -1510, -1510, -1510, -1510, -1510, -1341,   243,
   -1510, -1510, -1510, -1510, -1510, -1510,   237, -1510, -1510, -1510,
   -1510
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    32,   177,   173,   172,   176,   174,   175,    33,    34,
      35,    36,    37,   958,  1412,   271,  1413,  1414,   469,   731,
     734,  1238,  1239,  1240,   730,  1231,  1415,   195,   965,   963,
    1187,  1416,   204,   205,   196,   690,   197,   198,   199,   684,
     685,  1417,   704,   983,   979,   980,  1418,    45,  1219,   706,
    1220,   707,   975,  1201,  1383,  1554,  1677,    46,   241,   242,
     700,   243,   244,  1265,   737,   738,  1457,  1017,  1018,  1019,
    1256,  1020,  1448,  1449,  1021,  1722,  1450,  1451,  1600,  1452,
    1453,  1876,  1022,  1454,  1977,  1941,  1942,  1943,  1939,  1879,
    1609,  1253,  1610,   662,  1024,   245,   649,  1459,   739,   414,
      47,  1695,    48,  1419,  1588,  1969,  1857,  1894,  1421,  1422,
    1423,  1575,  1576,  1784,  1424,  1580,  1425,  1704,  1705,  1583,
    1584,  1702,  1426,  1863,  1427,  1428,  1971,  1797,  1593,  1004,
    1005,    50,   743,  1032,  1616,  1728,  1729,  1390,  1811,  1731,
    1732,  1887,  1817,  1896,  1429,   752,  1041,   757,  1430,  1431,
      54,   406,   407,   408,   946,   154,   400,   655,    55,  1567,
    1686,  1687,   988,   989,   214,  1212,  1848,  1922,  1564,  1393,
    1394,    56,    57,    58,   651,   844,  1106,   679,   343,   680,
    1108,   681,   151,   538,   539,   536,   874,  1148,  1149,  1533,
      59,   159,   160,   410,    60,  1432,    62,   882,   883,    63,
     530,   796,   344,   606,   607,   875,   876,  1137,  1138,  1151,
    1159,  1470,  1357,   345,   346,   280,   534,   804,   672,   792,
     793,  1068,   347,   348,   349,   350,   891,   351,   895,   352,
     353,   577,   354,   905,   355,   603,   356,   357,   358,   359,
     360,   361,   362,   363,   364,  1168,  1169,  1366,  1546,  1547,
    1668,  1669,  1670,  1671,  1917,  1918,  1771,   365,   578,   168,
     169,   367,   550,   368,   369,   370,   609,   371,   372,   373,
     374,   375,   595,   856,   590,   592,   520,   783,   818,   784,
    1279,   785,   786,   521,   376,   377,   378,   880,   379,   380,
     812,   381,   668,   869,   862,   863,   598,   599,   866,   930,
    1047,  1378,   800,   217,   955,  1465,  1042,   382,   524,   525,
     383,  1025,   686,   201,   579,   148,  1234,   956,   218,  1048,
     385,    64,   181,  1012,  1013,  1235,   823,   824,   825,   386,
     387,   388,   389,   390,  1297,  1090,  1478,  1739,  1740,  1821,
    1741,  1902,  1479,  1480,  1481,  1308,  1493,   391,   829,  1093,
    1094,  1095,  1310,  1497,   392,  1313,   393,  1099,  1315,   394,
     836,  1101,  1317,  1506,  1507,  1508,  1509,  1510,  1648,   395,
     396,   839,   833,  1085,   830,  1301,  1302,  1635,  1303,  1304,
    1305,  1643,  1644,  1322,  1323,  1759,  1760,  1831,  1832,  1905,
    1950,  1761,  1829,  1836,  1837,  1912,  1838,  1839,  1911,  1909,
     397
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      41,   215,   273,   216,   167,   415,    42,   213,   540,   446,
     537,   523,    38,   664,   821,   802,   413,   990,    39,   776,
    1214,   817,   837,  1420,    52,   526,   419,   575,   522,   285,
      53,  1153,  1154,   877,   666,  1380,    61,   669,   200,   775,
    1162,  1163,  1023,  1471,   427,   428,   211,   576,   580,   430,
     987,   932,  1602,   441,   688,  1544,    43,   180,   285,   543,
     544,   545,   696,   602,   211,  1833,    44,   953,   753,   754,
     826,  1534,   147,  1136,  1007,  1008,   448,   156,   841,    51,
     211,   161,  1236,  1237,   163,   170,   147,  -728,   182,   183,
     184,   185,   186,   187,  1087,  1537,  1088,   858,   758,   759,
     535,   556,  1841,   267,   274,   838,   799,  1102,   588,   604,
    -732,   162,  1471,  1503,   765,   188,   189,   190,   191,  1742,
    1471,  1186,  1745,  1387,  1538,   650,  1842,   450,   831,   761,
     832,   411,  1542,  1834,   147,  1318,  1835,  1504,   366,   499,
     500,   501,   831,   451,   832,  1388,  1707,   -82,   -82,   -82,
     -82,   -82,   -82,   802,   502,   807,   643,   644,   503,   504,
     505,   299,   300,   506,   507,   508,   509,   510,   511,   512,
     513,   514,    41,    41,    41,    41,    41,    41,    42,    42,
      42,    42,    42,    42,    38,    38,    38,    38,    38,    38,
      39,    39,    39,    39,    39,    39,    52,    52,    52,    52,
      52,    52,    53,    53,    53,    53,    53,    53,    61,    61,
      61,    61,    61,    61,  1723,    14,   200,  1552,   868,   384,
     147,   713,  1392,  1973,  1974,   402,   192,  1084,    43,    43,
      43,    43,    43,    43,   285,  1983,   555,   805,    44,    44,
      44,    44,    44,    44,   954,  -685,   162,   716,   811,   811,
     961,    51,    51,    51,    51,    51,    51,  -734,  1660,  1788,
    1975,   277,   278,   279,   669,  1793,   188,   189,   190,   191,
     593,   594,  -732,   575,   589,  1618,   443,   147,   147,  1661,
    1055,  1056,   432,   575,  1057,   802,   697,  1097,   193,   454,
     211,   147,  1023,   576,  1619,   573,   449,  1545,   860,   463,
     147,   147,   147,   467,   470,   147,  1058,   147,   147,  1236,
    1237,   194,   887,  1903,   476,   147,   967,   968,   147,   147,
     147,   486,   147,   147,   147,   147,   147,   740,   712,  1156,
    1035,   493,   494,   888,  -437,  1170,  1136,  1172,   147,   683,
    1843,   962,   162,   904,  1221,  1844,  1856,  1103,   762,   964,
      14,   541,   542,   146,  1511,  1866,  1396,   604,  1037,  1038,
    1039,  -685,  1043,  1044,  1045,   342,  1984,   171,   215,   859,
     216,  1319,  1895,   409,  1324,   920,  1073,  1258,   208,   575,
    -246,   559,  1736,   342,   178,   202,  -685,  1708,   203,  1674,
     179,  1612,  1420,  -685,  -685,   574,   878,  -685,  1392,  1531,
    1086,  1601,   366,   162,   645,   515,   516,   517,   518,  1678,
     962,  1880,  1316,  1747,   701,   282,   848, -1044,  1926,  -734,
    1928,   591,   870,   949,   147,  1556,   871,  1646,   808,   162,
    1527,   769,   770,  1199,  1557,   209,  1200,  1756,  1748,   193,
    1976,   921,  1311,   687,    13,   951,    14,    66,  1140,  1141,
    1142,  1620,  1143,  1144,  1145,  1146,   206,   523, -1044,   519,
    1107,   959,   194,   431,   766, -1044,  1306,  1109,  1647,   669,
    1132,   526,  1248,   970,   996,  1517,  1518,   161,  1613,  1273,
     274,    40,  1325,   384,   207,  1360,   670,  1361,   702,   523,
     995,   162,  1486,    49,  1910,  1624,   682,   885,  1312,   605,
    1558,   398,   147,   526,   523,    13,  1794,   646,   703,   962,
    1679,  1078,  1757,  1601,   994,  1758,  1970,   147,   526,   981,
     850,  1046,   432,  1278,  1895,   573,   147,   147,   147,   147,
     147,    13,   540,    14,   537,    65,   732,  -246,  1650,   982,
    1307,   573,   744,   147,  1651,  1155,   147,  1147,   147,   147,
     147,   573,  1174,  1176,  1652,  1023,   810,  1714,   444,   445,
     760,  1715,   212,  1949,   764,  1559,   274,  1483,  1343,  1182,
     992,  1113,   457,   849,  1347,   647,  1348,   771,  1495,  1662,
     519,   464,   465,   466,  1370,  1502,   471,   787,   472,   473,
     210,   879,  1134,    13,  1293,    14,   477,  1683,  1076,   483,
     484,   485,   952,   487,   488,   489,   490,   491,   648,  1603,
    1733,  1306,  1381,  1160,  1161,  1382,  1809,  1642,   960,   471,
     215,   854,   216,   857,  1110,   574,   366,  1133,  1765,  1249,
    1120,  1775,  1122,  1532,   572,   246,  1274,  1229, -1044,  1326,
    1807,   842,   960,  1230,   960,  1266,  1267,   573,   149,  1487,
     152,   574,  1625,    40,    40,    40,    40,    40,    40,  1818,
    1853,  1810,   162,   647,   878,    49,    49,    49,    49,    49,
      49,   528,   881,   884,  1084,  1604,   886,  1867,  1782,  1656,
    1379,  1379,  1140,  1141,  1142,  1629,  1143,  1144,  1145,  1146,
   -1031,   947,   247,   153, -1009,  1326,   648,  1165,  1290,   157,
    1812,   960,   499,   500,   501,   622,   596,   384,   864,   931,
   -1009,   960,   150,   937,   274,   158,   163,   502,  1605,  1778,
    1779,   503,   504,   505,   299,   300,   506,   507,   508,   509,
     510,   511,   512,   513,   514,   529,  1438,  1291,   861,   976,
     864,  1335,   248,  1192,   523,  1810,  1445,   842,  1339,  1675,
    1340,  1446,  1676,   219,  1565,   249,   275,   147,   526,  1606,
     281,  1226,  1607,   523,    13,  1196,    14,   519,  1501,   246,
    1197,  1505,  1608,  1528,   669,  1530,   283,   526,  1535,  1468,
    1257,  1147,   147,   691,  1870,  1438,  1872,   276,  1776,   977,
     978,   452,   453,   669,  1006,  1006,  1006,  1808,   715,   284,
     250,   251,   252,   732,  1026,  1054,   399,   720,   721,   722,
     723,   724,  1384,  1385,  1386,   147,  1819,  1854,   523,   523,
    1061,  1254,  1255,  1582,   745,  1700,   247,   746,   253,   748,
     749,   750,   526,   526,  1868,  1287,  1288,   412,   479,  1016,
    1250,   254,   573,   417,  1489,  1936,  1937,   255,   429,   277,
     278,   279,   256,   420,   421,   708,  1251,   424,   425,   879,
    1447,   403,   418,  1379,   404,   426,  1070,  1071,  1072,  1252,
     405,  1689,  1690,  1938,   433,   541,   248,   709,  1079,   435,
     710,   711,  1490,  -216,  1491,  1492,   257,   147,   258,   249,
     998,   999,  1000,  1001,   434,  1089,   480,   481,   482,  1703,
    1445,  1700,  1098,   611,   436,  1446,   612,   613,   614,   615,
     616,   617,   618,   619,  1034,   437,   620,   621,   937,   440,
    1029,  1030,   411,  1031,   277,   278,   279,   878,    15,   455,
     456,   878,   416,   211,   250,   251,   252,   878,  1362,   878,
     881,   447,   574,  1107,  1107,   458,  1152,  1152,  1152,  -216,
      26,   459,   943,  1525,   652,   653,    27,    28,  1657,   944,
     945,   474,   253,   682,   682,   656,   657,  1377,   515,   516,
     517,   518,   277,   278,   279,    30,   277,   278,   279,  1444,
     846,   255,   698,   699,  1105,   460,   256,  1391,   461,  1395,
    1395,  1398,  -216,  1016,   633,   634,   635,   215,   215,   216,
     216,  1667,   462,  1259,  1260,   475,  1189,   523,  1190,  1191,
    1177,   478,  1241,  1881,  1447,  1882,  1883,  1884,  1242,   492,
     257,   526,   258,   741,   742,  1140,  1141,  1142,   755,   756,
     682,  1344,  1146,  -216,   496,  1379,  -216,   495,   966,  1194,
    1195,   277,   278,   279,  1202,  1203,  -216,  -173,  1204,   897,
     898,   899,  1208,   147,   541,   889,   890,  -602,  1539,   497,
     220,   985,   978,   991,  -172,  1006,  1111,  1112,  1243,   498,
    1223,   182,   183,   184,   185,   186,   187,   527,  1244,  1233,
    1540,  1541,  -715,   147,  1247,   777,   778,   779,   780,   781,
     782,  1245,  -516,   593,   594,   221,  1036,   533,   222,  1505,
     535,   147,  1178,  1179,   285,   573,   551,   552,   553,   554,
    1581,  -836,  1586,  1206,  1207,  1726,  1727,  -717,  1667,  1963,
    1964,  -516,   879,  -713,  1049,   546,   879,  1051,  1052,  1053,
    1885,  1886,   879,   547,   879,   548,   878,   549,   878,   422,
     423,   878,  1955,  1956,  1060,  1062,  1063,  1064,   984,   986,
     531,   532,   223,   558,  -516,  -516,  -516,   797,   798,   555,
     557,   608,  -516,   560,  1560,   561,  1395,   562,  1083,  1597,
    1598,  1694,   523,   523,   523,   777,   778,   779,   780,   781,
     816,   563,   564,   565,  1114,   566,   526,   526,   526,  1591,
    1594,  1594,   567,   568,   569,   638,  1570,   570,   584,   585,
     586,   610,   224,   881,   600,   842,   601,   881,  1342,  -516,
     637,   639,   640,   881,  -654,   881,   641,   642,  1351,   654,
     658,   659,   660,  1353,   884,   663,   671,  1460,   693,   673,
     674,  -516,   675,   676,  1659,   694,   695,  -516,  -516,  1241,
     717,   705,   937,   718,  1371,  1242,  1573,   225,   226,   227,
     228,   229,   230,   714,   726,   719,  -516,   725,  1658,   231,
     232,   233,   234,   727,   728,   623,   624,   625,   626,   627,
     628,   629,   630,   631,   632,   729,  -516,  -516,  -516,   633,
     634,   635,   735,   733,  1699,   736,   747,   751,   235,   774,
     767,  1709,  1433,  1434,  1916,  1243,   795,   806,   810,   809,
    1437,   236,   768,   772,   773,  1244,  1466,   237,  1467,   589,
     238,   591,   239,  1469,   788,   789,   790,  1441,  1245,  -516,
     791,   878,   777,   778,   779,   780,   781,  1277,   814,   274,
    1461,   879,   815,   879,  1209,  1682,   879,   803,   819,  1685,
     828,   827,   835,  1691,   843,   855,   834,   845,   240,   341,
     847,   893,   611,   894,  1472,   612,   613,   614,   615,   616,
     617,   618,   619,   922,  1246,   620,   621,   923,   612,   613,
     614,   615,   616,   617,   618,   619,   925,  1496,   215,   621,
     216,   220,  1263,   938,  1579,   941,   942,   950,   604,   957,
     973,   971,   -16,     1,   167,   974,   969,   972,   682,   682,
     997,  1009,  1010,   978,  1115,  1002,   993,  1033,  1027,  1011,
    1050,  1059,   881,  1028,   881,  1065,   221,   881,  1069,   222,
    1233,  1805,  1082,  1472,  1081,  1080,  1084,  1091,  1617,  1100,
     276,  1472,  1118,  1119,  1121,  1798,  1096,  1124,  1129,  1131,
    1158,  1139,   635,     2,  1166,  1171,  1772,  1173,  -716,  -718,
    1167,  -714,  1180,     3,     4,     5,     6,  1184,  1186,  1188,
    1193,  1198,  1205,  1211,  1217,     7,     8,     9,    10,   499,
     500,   501,  1213,   223,    11,   881,  1175,  1110,  1215,  1216,
    1218,  1222,  1224,  1225,   502,  1232,  1227,  1262,   503,   504,
     505,   299,   300,   506,   507,   508,   509,   510,   511,   512,
     513,   514,  1228,  1261,  1264,  -745,  1596,  1316,  1309,  1268,
    1269,  1270,  1271,  1272,  1275,  1276,   879,  1280,  1888,    12,
    1281,  1321,  1282,   224,  1283,  1284,  1292,  1286,  1296,  1294,
     274,  1295,  1314,  1320,  1327,  1337,   523,  1328,  1329,  1334,
    1341,  1346,   182,   183,   184,   185,   186,   187,  1845,  1349,
     526,  1350,  1352,  1869,  1355,  1356,  1634,    13,  1363,    14,
     366,  1364,  1367,  1365,  1929,  1368,  1373,  1372,   225,   226,
     227,   228,   229,   230,  1375,  1376,  1806,  1389,  1399,  1401,
     231,   232,   233,   234,  1402,  1442,  1438,  1443,  1456,  1435,
    1458,  1462,  1463,  1933,  1455,  1152,  1473,   881,   188,   189,
     190,   191,  1474,  1436,  1233,  1488,  1498,    15,  1499,   235,
    1484,  1500,  1513,  1512,  1514,    16,    17,  1529,    18,  1536,
      19,    20,    21,    22,    23,    24,    25,  1543,   237,    26,
    1548,   238,  1040,   239,  1688,    27,    28,  1550,  1551,  1555,
    1549,   384,  1696,  1553,  1563,  1561,  1565,  1566,  1569,  1574,
    1572,    29,  1258,  1590,    30,  1599,  1433,  1611,  1874,  1621,
    1614,  1433,  1615,  1622,  1623,  1627,  1649,  1632,   215,   240,
     216,   523,  1587,   611,  1786,   147,   612,   613,   614,   615,
     616,   617,   618,   619,  1589,   526,  1358,   621,  1960,  1636,
      31,  1637,  1638,  1472,  1737,  1639,   499,   500,   501,  1640,
    1641,   621,  1672,   519,  1680,  1697,  1626,  1673,  1684,   192,
    1751,   502,  1698,  1628,  1631,   503,   504,   505,   299,   300,
     506,   507,   508,   509,   510,   511,   512,   513,   514,  1693,
    1645,  1625,  1716,  1710,  1717,   515,   516,   517,   518,  1718,
    1719,  1773,  1720,   582,   583,  1706,  1724,  1730,  1725,   587,
    1734,  1735,  1746,  1749,   597,  1750,  1577,  1755,  1753,   611,
    1767,  1696,   612,   613,   614,   615,   616,   617,   618,   619,
    1754,   193,  1359,   621,  1768,  1433,  1769,  1777,   541,  1770,
    1521,   605,   611,  1780,   147,   612,   613,   614,   615,   616,
     617,   618,   619,  1774,   194,  1795,   621,  1789,   623,   624,
     625,   626,   627,   628,   629,   630,   631,   632,  1783,  1787,
    1800,  1796,   633,   634,   635,  1799,  1801,  1892,  1802,  1804,
    1823,  1816,  1815,  1893,  1825,  1828,  1826,  1176,  1820,  1890,
    1822,  1830,  1827,   667,  1840,  1891,  1847,  1858,  1860,  1855,
    1864,  1897,   667,  1871,  1688,  1865,  1873,  1898,  1850,  1878,
    1875,  1852,  1877,  1899,  1904,  1907,  1433,  1834,  1920,  1921,
    1919,  1433,  1925,  1927,  1930,  1931,  1940,  1696,  1954,  1696,
    1948,  1951,  1952,  1957,  1953,   623,   624,   625,   626,   627,
     628,   629,   630,   631,   632,  1433,  1958,  1962,  1901,   633,
     634,   635,   623,   624,   625,   626,   627,   628,   629,   630,
     631,   632,  1908,  1959,  1965,  1967,   633,   634,   635,  1963,
    1982,  1964,  1985,   667,   623,   624,   625,   626,   627,   628,
     629,   630,   631,   632,  1433,  1439,   439,  1014,   633,   634,
     635,  1374,  1935,   438,  1433,  1185,   541,  1522,   692,  1400,
    1571,  1851,  1692,   794,   272,  1781,  1681,  1210,  1440,  1944,
    1945,  1946,  1947,  1978,  1966,  1592,  1721,  1968,  1713,  1961,
    1934,  1980,   515,   516,   517,   518,  1791,  1792,  1701,  1892,
    1595,  1981,  1814,  1813,  1464,  1893,   820,   822,   822,   155,
     401,  1890,   948,  1568,   820,  1846,   822,  1891,  1923,  1849,
    1397,  1515,  1562,  1897,  1433,  1516,  1433,  1345,   939,  1898,
     851,   852,   853,  1181,  1183,  1899,  1077,   661,  1354,  1104,
     900,  1663,  1285,  1075,  1117,   892,   867,   667,   906,  1766,
     924,   266,  1157,   813,  1123,   763,  1126,  1972,  1744,  1127,
     865,  1130,   896,   896,   896,   896,   940,  1433,  1433,   907,
     908,   909,   910,   911,   912,   913,   914,   915,   916,   917,
     918,   919,  1074,  1524,   801,  1900,  1743,   929,   929,  1630,
    1752,  1494,  1482,  1633,  1485,  1803,  1824,    67,    68,    69,
      70,    71,    72,   840,  1906,     0,  1913,     0,     0,     0,
       0,     0,     0,     0,    73,    74,     0,     0,    75,   499,
     500,   501,     0,     0,     0,     0,     0,     0,     0,     0,
      76,     0,     0,    77,   502,     0,     0,     0,   503,   504,
     505,   299,   300,   506,   507,   508,   509,   510,   511,   512,
     513,   514,    78,     0,     0,   162,   164,   165,   166,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    79,     0,
       0,    80,     0,     0,    81,     0,     0,  1164,     0,     0,
      82,     0,     0,     0,     0,    83,    84,    85,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    86,
       0,     0,    87,     0,    88,    89,    90,     0,     0,     0,
       0,    91,    92,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    93,    94,
       0,     0,    95,     0,    96,    97,    98,    99,   100,   101,
     102,     0,   103,     0,   104,   105,   106,   107,     0,   108,
       0,   109,     0,     0,     0,     0,     0,    13,   110,  1135,
       0,   111,   623,   624,   625,   626,   627,   628,   629,   630,
     631,   632,     0,     0,     0,  1092,   633,   634,   635,   820,
       0,     0,     0,     0,     0,   822,     0,     0,     0,   667,
       0,     0,     0,     0,     0,     0,   112,   113,     0,     0,
       0,     0,     0,     0,   114,     0,     0,  1125,   115,     0,
    1128,     0,     0,     0,   116,     0,     0,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,     0,   127,     0,
       0,     0,     0,     0,   128,     0,     0,   129,     0,   667,
     667,   130,     0,     0,   131,   132,     0,   133,     0,     0,
     134,     0,   135,     0,     0,     0,   136,   137,     0,     0,
     572,     0,     0,   138,   139,   140,   141,     0,     0,     0,
       0,     0,   929,   142,   929,   623,   624,   625,   626,   627,
     628,   629,   630,   631,   632,   515,   516,   517,   518,   633,
     634,   635,     0,     0,     0,     0,   143,     0,   667,     0,
       0,   144,   145,     0,     0,     0,   667,  1519,     0,   623,
     624,   625,   626,   627,   628,   629,   630,   631,   632,     0,
     873,     0,     0,   633,   634,   635,   623,   624,   625,   626,
     627,   628,   629,   630,   631,   632,     0,     0,     0,     0,
     633,   634,   635,     0,     0,     0,     0,     0,     0,     0,
      67,    68,    69,    70,    71,    72,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    73,    74,  1520,
       0,    75,     0,     0,     0,     0,  1336,     0,     0,     0,
       0,     0,     0,    76,     0,     0,    77,   623,   624,   625,
     626,   627,   628,   629,   630,   631,   632,     0,     0,     0,
       0,   633,   634,   635,     0,    78,     3,     4,  1403,     6,
    1859,   794,     0,     0,     0,     0,     0,     0,     7,     8,
       9,  1404,     0,     0,    80,     0,   861,  1405,  1289,     0,
       0,     0,   822,    82,     0,     0,     0,  1300,    83,    84,
      85,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    86,     0,     0,    87,     0,    88,    89,    90,
    1330,  1331,  1332,  1333,    91,    92,     0,     0,     0,     0,
     667,     0,     0,     0,     0,     0,  1338,   667,     0,   667,
       0,    93,    94,     0,     0,    95,     0,    96,    97,    98,
      99,   100,   101,   102,     0,   103,     0,   104,   105,   106,
     107,     0,   108,     0,   109,     0,     0,     0,     0,     0,
       0,   110,     0,     0,   111,     0,     0,     0,     0,     0,
       0,   929,     0,     3,     4,     5,     6,     0,     0,     0,
       0,     0,     0,     0,     0,     7,     8,     9,    10,     0,
       0,     0,     0,     0,    11,     0,     0,     0,     0,   112,
     113,     0,     0,     0,     0,     0,     0,   114,     0,     0,
      15,   115,     0,     0,     0,     0,     0,   116,    16,  1407,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
       0,   127,    26,     0,     0,     0,     0,   128,    27,    28,
     129,     0,     0,     0,   130,     0,     0,   131,   132,     0,
     133,     0,     0,   134,    29,   135,  1408,    30,     0,   136,
     137,     0,     0,     0,     0,     0,   138,   139,   140,   141,
       0,     0,     0,     0,     0,     0,   142,    13,     0,    14,
    1409,     0,     0,  1861,     0,     0,  1410,  1862,  -326,     0,
       0,     0,  1477,    31,     0,  1300,     0,     0,     0,   143,
       0,     0,     0,  1092,   144,   145,     0,     0,     0,     0,
     820,     0,     0,   820,     0,     0,     0,     0,     0,     0,
       0,     0,   667,   667,   667,   667,     0,    15,     0,     0,
       0,     0,   667,     0,     0,    16,    17,     0,    18,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    26,
       0,     0,     0,     0,     0,    27,    28,     0,     0,     0,
       0,     0,    67,    68,    69,    70,    71,    72,     0,     0,
       0,    29,     0,     0,    30,     0,     0,     0,     0,    73,
      74,     0,     0,    75,     0,   623,   624,   625,   626,   627,
     628,   629,   630,   631,   632,    76,     0,     0,    77,   633,
     634,   635,     0,     0,     0,  1585,     0,     0,     0,     0,
      31,     0,     0,     0,     0,     0,     0,    78,     0,     0,
       0,   164,   165,   166,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    79,     0,     0,    80,     0,     0,    81,
       0,     0,     0,   820,     0,    82,     0,     0,     0,     0,
      83,    84,    85,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    86,     0,     0,    87,     0,    88,
      89,    90,     0,     0,     0,     0,    91,    92,     0,     0,
       0,     0,     0,  1300,     0,  1703,     0,     0,     0,     0,
       0,     0,     0,    93,    94,     0,     0,    95,     0,    96,
      97,    98,    99,   100,   101,   102,     0,   103,     0,   104,
     105,   106,   107,     0,   108,  1653,   109,     0,  1654,     0,
    1655,     0,     0,   110,   872,     0,   111,     0,     0,     0,
       0,     0,     0,     0,     0,  1116,     0,     0,     0,   794,
       0,     0,     0,   820,   623,   624,   625,   626,   627,   628,
     629,   630,   631,   632,     0,   820,     0,     0,   633,   634,
     635,   112,   113,     0,     0,     0,     0,     0,     0,   114,
       0,     0,     0,   115,     0,     0,     0,     0,     0,   116,
       0,     0,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,     0,   127,     0,     0,     0,     0,     0,   128,
       0,     0,   129,     0,     0,     0,   130,     0,     0,   131,
     132,     0,   133,     0,     0,   134,     0,   135,     0,     0,
       0,   136,   137,  1738,  1477,  1477,     0,  1477,   138,   139,
     140,   141,     0,     0,     0,     0,     0,     0,   142,     0,
       0,   820,   623,   624,   625,   626,   627,   628,   629,   630,
     631,   632,     0,     0,  1475,     0,   633,   634,   635,     0,
     820,   143,     0,     0,     0,     0,   144,   145,     0,     0,
       0,     0,   623,   624,   625,   626,   627,   628,   629,   630,
     631,   632,     0,     0,     0,   873,   633,   634,   635,  1523,
       0,     0,     0,  1785,     0,     0,     0,     0,     0,  1790,
       0,     0,     0,     0,   636,     0,     0,   623,   624,   625,
     626,   627,   628,   629,   630,   631,   632,     0,     0,     0,
       0,   633,   634,   635,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   285,     0,   286,
     287,   288,   289,   290,   291,   292,   293,   294,   295,   296,
       0,     0,   297,   298,     0,     0,    73,    74,     0,     0,
      75,   299,   300,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    76,     0,     0,    77,     0,     0,   301,   302,
     303,   304,   305,   306,   307,     0,   259,   260,   261,     0,
       0,     0,     0,   308,    78,     0,     0,   162,   164,   165,
     166,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      79,     0,     0,    80,     0,  1738,    81,     0,  1477,     0,
       0,     0,    82,     0,     0,     0,     0,    83,    84,    85,
       0,     0,     0,     0,   309,     0,   820,     0,   310,     0,
       0,    86,   311,     0,    87,     0,    88,    89,    90,     0,
    1924,     0,   312,    91,    92,     0,     0,     0,     0,     0,
       0,     0,   313,   314,   315,   316,   317,     0,   318,   319,
      93,    94,   320,   321,    95,   322,    96,    97,    98,    99,
     100,   101,   102,     0,   103,   323,   104,   105,   106,   107,
    1526,   108,   324,   109,     0,     0,     0,     0,     0,    13,
     110,   571,     0,   111,   326,     0,     0,     0,   623,   624,
     625,   626,   627,   628,   629,   630,   631,   632,     0,     0,
     327,   328,   633,   634,   635,     0,     0,     0,     0,     0,
     329,   330,   331,     0,     0,     0,     0,   333,   112,   113,
       0,     0,     0,     0,     0,     0,   114,     0,     0,     0,
     115,     0,     0,     0,     0,     0,   116,     0,     0,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,     0,
     127,     0,     0,     0,     0,     0,   128,     0,     0,   129,
       0,     0,     0,   130,     0,     0,   131,   132,     0,   133,
       0,     0,   134,     0,   135,     0,     0,     0,   136,   137,
       0,     0,   572,     0,     0,   334,   335,   336,   337,     0,
       0,     0,     0,     0,     0,   142,     0,     0,     0,   338,
       0,     0,     0,   339,   340,     0,     0,  1762,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   143,     0,
       0,     0,     0,   144,   145,   623,   624,   625,   626,   627,
     628,   629,   630,   631,   632,     0,     0,     0,     0,   633,
     634,   635,   341,   285,   342,   286,   287,   288,   289,   290,
     291,   292,   293,   294,   295,   296,     0,     0,   297,   298,
       0,     0,    73,    74,     0,     0,    75,   299,   300,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    76,     0,
       0,    77,     0,     0,   301,   302,   303,   304,   305,   306,
     307,     0,   259,   260,   261,     0,     0,     0,     0,   308,
      78,     0,     0,     0,   164,   165,   166,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    79,     0,     0,    80,
       0,     0,    81,     0,     0,     0,     0,     0,    82,     0,
       0,     0,     0,    83,    84,    85,     0,     0,     0,     0,
     309,     0,     0,     0,   310,     0,     0,    86,   311,     0,
      87,     0,    88,    89,    90,     0,     0,     0,   312,    91,
      92,     0,     0,     0,     0,     0,     0,     0,   313,   314,
     315,   316,   317,     0,   318,   319,    93,    94,   320,   321,
      95,   322,    96,    97,    98,    99,   100,   101,   102,     0,
     103,   323,   104,   105,   106,   107,     0,   108,   324,   109,
       0,     0,     0,     0,     0,     0,   110,   325,     0,   111,
     326,     0,   901,   902,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   903,     0,     0,   327,   328,     0,     0,
       0,     0,     0,     0,     0,     0,   329,   330,   331,     0,
       0,     0,     0,   333,   112,   113,     0,     0,     0,     0,
       0,     0,   114,     0,     0,     0,   115,     0,     0,     0,
       0,     0,   116,     0,     0,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,     0,   127,     0,     0,     0,
       0,     0,   128,     0,     0,   129,     0,     0,     0,   130,
       0,     0,   131,   132,     0,   133,     0,     0,   134,     0,
     135,     0,     0,     0,   136,   137,     0,     0,     0,     0,
       0,   334,   335,   336,   337,     0,     0,     0,     0,     0,
       0,   142,     0,     0,     0,   338,     0,     0,     0,   339,
     340,     0,     0,  1763,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   143,     0,     0,     0,     0,   144,
     145,   623,   624,   625,   626,   627,   628,   629,   630,   631,
     632,     0,     0,     0,     0,   633,   634,   635,   341,   285,
     342,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,     0,     0,   297,   298,     0,     0,    73,    74,
       0,     0,    75,   299,   300,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    76,     0,     0,    77,     0,     0,
     301,   302,   303,   304,   305,   306,   307,     0,   259,   260,
     261,     0,     0,     0,     0,   308,    78,     0,     0,   162,
     164,   165,   166,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    79,     0,     0,    80,     0,     0,    81,     0,
       0,     0,     0,     0,    82,     0,     0,     0,     0,    83,
      84,    85,     0,     0,     0,     0,   309,     0,     0,     0,
     310,     0,     0,    86,   311,     0,    87,     0,    88,    89,
      90,     0,     0,     0,   312,    91,    92,     0,     0,     0,
       0,     0,     0,     0,   313,   314,   315,   316,   317,     0,
     318,   319,    93,    94,   320,   321,    95,   322,    96,    97,
      98,    99,   100,   101,   102,     0,   103,   323,   104,   105,
     106,   107,  1764,   108,   324,   109,     0,     0,     0,     0,
       0,    13,   110,   571,     0,   111,   326,     0,     0,     0,
     623,   624,   625,   626,   627,   628,   629,   630,   631,   632,
       0,     0,   327,   328,   633,   634,   635,     0,     0,     0,
       0,     0,   329,   330,   331,     0,     0,     0,     0,   333,
     112,   113,     0,     0,     0,     0,     0,     0,   114,     0,
       0,     0,   115,     0,     0,     0,     0,     0,   116,     0,
       0,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,     0,   127,     0,     0,     0,     0,     0,   128,     0,
       0,   129,     0,     0,     0,   130,     0,     0,   131,   132,
       0,   133,     0,     0,   134,     0,   135,     0,     0,     0,
    1578,   137,     0,     0,     0,     0,     0,   334,   335,   336,
     337,     0,     0,     0,     0,     0,     0,   142,     0,     0,
       0,   338,     0,     0,     0,   339,   340,   623,   624,   625,
     626,   627,   628,   629,   630,   631,   632,     0,     0,     0,
     143,   633,   634,   635,     0,   144,   145,     0,     0,     0,
       0,  1066,  1067,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   341,   285,   342,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,     0,     0,
     297,   298,     0,     0,    73,    74,     0,     0,    75,   299,
     300,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      76,     0,     0,    77,     0,     0,   301,   302,   303,   304,
     305,   306,   307,     0,   259,   260,   261,     0,     0,     0,
       0,   308,    78,     0,     0,     0,   164,   165,   166,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    79,     0,
       0,    80,     0,     0,    81,     0,     0,     0,     0,     0,
      82,     0,     0,     0,     0,    83,    84,    85,     0,     0,
       0,     0,   309,     0,     0,     0,   310,     0,     0,    86,
     311,     0,    87,     0,    88,    89,    90,     0,     0,     0,
     312,    91,    92,     0,     0,     0,     0,     0,     0,     0,
     313,   314,   315,   316,   317,     0,   318,   319,    93,    94,
     320,   321,    95,   322,    96,    97,    98,    99,   100,   101,
     102,     0,   103,   323,   104,   105,   106,   107,     0,   108,
     324,   109,     0,     0,     0,     0,     0,     0,   110,   325,
       0,   111,   326,     0,     0,     0,   623,   624,   625,   626,
     627,   628,   629,   630,   631,   632,     0,     0,   327,   328,
     633,   634,   635,     0,     0,     0,     0,     0,   329,   330,
     331,     0,   332,     0,     0,   333,   112,   113,     0,     0,
       0,     0,     0,     0,   114,     0,     0,     0,   115,     0,
       0,     0,     0,     0,   116,     0,     0,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,     0,   127,     0,
       0,     0,     0,     0,   128,     0,     0,   129,     0,     0,
       0,   130,     0,     0,   131,   132,     0,   133,     0,     0,
     134,     0,   135,     0,     0,     0,   136,   137,     0,     0,
       0,     0,     0,   334,   335,   336,   337,     0,     0,     0,
       0,     0,     0,   142,     0,     0,     0,   338,     0,     0,
       0,   339,   340,  -633,  -633,  -633,  -633,  -633,  -633,  -633,
    -633,  -633,  -633,     0,     0,     0,   143,  -633,  -633,  -633,
       0,   144,   145,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     341,   285,   342,   286,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   296,     0,     0,   297,   298,     0,     0,
      73,    74,     0,     0,    75,   299,   300,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    76,     0,     0,    77,
       0,     0,   301,   302,   303,   304,   305,   306,   307,     0,
     259,   260,   261,     0,     0,     0,     0,   308,    78,     0,
       0,     0,   164,   165,   166,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    79,     0,     0,    80,     0,     0,
      81,     0,     0,     0,     0,     0,    82,     0,     0,     0,
       0,    83,    84,    85,     0,     0,     0,     0,   309,     0,
       0,     0,   310,     0,     0,    86,   311,     0,    87,     0,
      88,    89,    90,     0,     0,     0,   312,    91,    92,     0,
       0,     0,     0,     0,     0,     0,   313,   314,   315,   316,
     317,     0,   318,   319,    93,    94,   320,   321,    95,   322,
      96,    97,    98,    99,   100,   101,   102,     0,   103,   323,
     104,   105,   106,   107,     0,   108,   324,   109,     0,     0,
       0,     0,     0,     0,   110,   325,     0,   111,   326,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   327,   328,     0,     0,     0,     0,
       0,     0,     0,     0,   329,   330,   331,     0,     0,     0,
       0,   333,   112,   113,     0,     0,     0,     0,     0,     0,
     114,     0,     0,     0,   115,     0,     0,     0,     0,     0,
     116,     0,     0,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,     0,   127,     0,     0,     0,     0,     0,
     128,     0,     0,   129,     0,     0,     0,   130,     0,     0,
     131,   132,     0,   133,     0,     0,   134,     0,   135,     0,
       0,     0,   136,   137,     0,     0,     0,     0,     0,   334,
     335,   336,   337,     0,     0,     0,     0,     0,     0,   142,
       0,     0,     0,   338,     0,     0,     0,   339,   340,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   143,     0,     0,     0,     0,   144,   145,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   341,   285,   342,   286,
     287,   288,   289,   290,   291,   292,   293,   294,   295,   296,
       0,     0,   297,   298,     0,     0,    73,    74,     0,     0,
      75,   299,   300,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    76,     0,     0,    77,     0,     0,   301,   302,
     303,   304,   305,   306,   307,     0,   259,   260,   261,     0,
       0,     0,     0,   308,    78,     0,     0,     0,   164,   165,
     166,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      79,     0,     0,    80,     0,     0,    81,     0,     0,     0,
       0,     0,    82,     0,     0,     0,     0,    83,    84,    85,
       0,     0,     0,     0,     0,     0,     0,     0,   310,     0,
       0,    86,   311,     0,    87,     0,    88,    89,    90,     0,
       0,     0,   312,    91,    92,     0,     0,     0,     0,     0,
       0,     0,   313,   314,   315,   316,   317,     0,   318,   319,
      93,    94,   320,   321,    95,   322,    96,    97,    98,    99,
     100,   101,   102,     0,   103,   323,   104,   105,   106,   107,
       0,   108,   324,   109,     0,     0,     0,     0,     0,     0,
     110,   581,     0,   111,     0,     0,     0,     0,     0,  1664,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     327,   328,     0,     0,     0,     0,     0,     0,     0,     0,
     329,   330,   331,     0,     0,     0,     0,   333,   112,   113,
       0,     0,     0,     0,     0,     0,   114,     0,     0,     0,
     115,     0,     0,     0,     0,     0,   116,     0,     0,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,     0,
     127,     0,     0,     0,     0,     0,   128,     0,     0,   129,
       0,     0,     0,   130,     0,     0,   131,   132,     0,   133,
       0,     0,   134,     0,   135,     0,     0,     0,   136,   137,
       0,     0,     0,     0,     0,   334,   335,   336,   337,     0,
       0,     0,     0,     0,     0,   142,     0,     0,     0,   338,
       0,     0,     0,   339,   340,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   143,     0,
       0,     0,     0,   144,   145,     0,     0,     0,     0,     0,
       0,  1665,     0,     0,     0,     0,     0,     0,  1666,     0,
       0,     0,     0,   285,   342,   286,   287,   288,   289,   290,
     291,   292,   293,   294,   295,   296,     0,     0,   297,   298,
       0,     0,    73,    74,     0,     0,    75,   299,   300,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    76,     0,
       0,    77,     0,     0,   301,   302,   303,   304,   305,   306,
     307,     0,   259,   260,   261,     0,     0,     0,     0,   308,
      78,     0,     0,   162,   164,   165,   166,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    79,     0,     0,    80,
       0,     0,    81,     0,     0,     0,     0,     0,    82,     0,
       0,     0,     0,    83,    84,    85,     0,     0,     0,     0,
       0,     0,     0,     0,   310,     0,     0,    86,   311,     0,
      87,     0,    88,    89,    90,     0,     0,     0,   312,    91,
      92,     0,     0,     0,     0,     0,     0,     0,   313,   314,
     315,   316,   317,     0,   318,   319,    93,    94,   320,   321,
      95,   322,    96,    97,    98,    99,   100,   101,   102,     0,
     103,   323,   104,   105,   106,   107,     0,   108,   324,   109,
       0,     0,     0,     0,     0,     0,   110,   677,   678,   111,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   327,   328,     0,     0,
       0,     0,     0,     0,     0,     0,   329,   330,   331,     0,
       0,     0,     0,   333,   112,   113,     0,     0,     0,     0,
       0,     0,   114,     0,     0,     0,   115,     0,     0,     0,
       0,     0,   116,     0,     0,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,     0,   127,     0,     0,     0,
       0,     0,   128,     0,     0,   129,     0,     0,     0,   130,
       0,     0,   131,   132,     0,   133,     0,     0,   134,     0,
     135,     0,     0,     0,   136,   137,     0,     0,     0,     0,
       0,   334,   335,   336,   337,     0,     0,     0,     0,     0,
       0,   142,     0,     0,     0,   338,     0,     0,     0,   339,
     340,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   143,     0,     0,     0,     0,   144,
     145,     0,   285,     0,   286,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,     0,     0,   297,   298,     0,
     342,    73,    74,     0,     0,    75,   299,   300,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    76,     0,     0,
      77,     0,     0,   301,   302,   303,   304,   305,   306,   307,
       0,   259,   260,   261,     0,     0,     0,     0,   308,    78,
       0,     0,     0,   164,   165,   166,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    79,     0,     0,    80,     0,
       0,    81,     0,     0,     0,     0,     0,    82,     0,     0,
       0,     0,    83,    84,    85,     0,     0,     0,     0,     0,
       0,     0,     0,   310,     0,     0,    86,   311,     0,    87,
       0,    88,    89,    90,     0,     0,     0,   312,    91,    92,
       0,     0,     0,     0,     0,     0,     0,   313,   314,   315,
     316,   317,     0,   318,   319,    93,    94,   320,   321,    95,
     322,    96,    97,    98,    99,   100,   101,   102,     0,   103,
     323,   104,   105,   106,   107,     0,   108,   324,   109,     0,
       0,     0,     0,     0,     0,   110,   581,     0,   111,     0,
       0,   926,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   327,   328,     0,     0,     0,
       0,     0,     0,     0,     0,   329,   330,   331,     0,   927,
       0,     0,   333,   112,   113,     0,     0,     0,     0,     0,
       0,   114,     0,     0,     0,   115,     0,     0,     0,     0,
       0,   116,     0,     0,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,     0,   928,     0,     0,     0,     0,
       0,   128,     0,     0,   129,     0,     0,     0,   130,     0,
       0,   131,   132,     0,   133,     0,     0,   134,     0,   135,
       0,     0,     0,   136,   137,     0,     0,     0,     0,     0,
     334,   335,   336,   337,     0,     0,     0,     0,     0,     0,
     142,     0,     0,     0,   338,     0,     0,     0,   339,   340,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   143,     0,     0,     0,     0,   144,   145,
       0,   285,     0,   286,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   296,     0,     0,   297,   298,     0,   342,
      73,    74,     0,     0,    75,   299,   300,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    76,     0,     0,    77,
       0,     0,   301,   302,   303,   304,   305,   306,   307,     0,
     259,   260,   261,     0,     0,     0,     0,   308,    78,     0,
       0,     0,   164,   165,   166,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    79,     0,     0,    80,     0,     0,
      81,     0,     0,     0,     0,     0,    82,     0,     0,     0,
       0,    83,    84,    85,     0,     0,     0,     0,     0,     0,
       0,     0,   310,     0,     0,    86,   311,     0,    87,     0,
      88,    89,    90,     0,     0,     0,   312,    91,    92,     0,
       0,     0,     0,     0,     0,     0,   313,   314,   315,   316,
     317,  1476,   318,   319,    93,    94,   320,   321,    95,   322,
      96,    97,    98,    99,   100,   101,   102,   828,   103,   323,
     104,   105,   106,   107,     0,   108,   324,   109,     0,     0,
       0,     0,     0,     0,   110,   581,     0,   111,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   327,   328,     0,     0,     0,     0,
       0,     0,     0,     0,   329,   330,   331,     0,     0,     0,
       0,   333,   112,   113,     0,     0,     0,     0,     0,     0,
     114,     0,     0,     0,   115,     0,     0,     0,     0,     0,
     116,     0,     0,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,     0,   127,     0,     0,     0,     0,     0,
     128,     0,     0,   129,     0,     0,     0,   130,     0,     0,
     131,   132,     0,   133,     0,     0,   134,     0,   135,     0,
       0,     0,   136,   137,     0,     0,     0,     0,     0,   334,
     335,   336,   337,     0,     0,     0,     0,     0,     0,   142,
       0,     0,     0,   338,     0,     0,     0,   339,   340,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   143,     0,     0,     0,     0,   144,   145,     0,
     285,     0,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,     0,     0,   297,   298,     0,   342,    73,
      74,     0,     0,    75,   299,   300,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    76,     0,     0,    77,     0,
       0,   301,   302,   303,   304,   305,   306,   307,     0,   259,
     260,   261,     0,     0,     0,     0,   308,    78,     0,     0,
       0,   164,   165,   166,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    79,     0,     0,    80,     0,     0,    81,
       0,     0,     0,     0,     0,    82,     0,     0,     0,     0,
      83,    84,    85,     0,     0,     0,     0,     0,     0,     0,
       0,   310,     0,     0,    86,   311,     0,    87,     0,    88,
      89,    90,     0,     0,     0,   312,    91,    92,     0,     0,
       0,     0,     0,     0,     0,   313,   314,   315,   316,   317,
       0,   318,   319,    93,    94,   320,   321,    95,   322,    96,
      97,    98,    99,   100,   101,   102,     0,   103,   323,   104,
     105,   106,   107,     0,   108,   324,   109,     0,     0,     0,
       0,     0,     0,   110,   581,     0,   111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   327,   328,     0,     0,     0,     0,     0,
       0,     0,     0,   329,   330,   331,     0,     0,     0,     0,
     333,   112,   113,     0,     0,     0,     0,     0,     0,   114,
       0,     0,     0,   115,     0,     0,     0,     0,     0,   116,
       0,     0,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,     0,   127,     0,     0,     0,     0,     0,   128,
       0,     0,   129,     0,     0,     0,   130,     0,     0,   131,
     132,     0,   133,     0,     0,   134,     0,   135,     0,     0,
       0,   136,   137,     0,     0,     0,     0,     0,   334,   335,
     336,   337,     0,     0,     0,     0,     0,     0,   142,     0,
       0,     0,   338,     0,     0,     0,   339,   340,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   143,     0,     0,     0,     0,   144,   145,     0,     0,
       0,     0,     0,     0,  1665,     0,     0,     0,     0,     0,
       0,  1666,     0,     0,     0,     0,   285,   342,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,     0,
       0,   297,   298,     0,     0,    73,    74,     0,     0,    75,
     299,   300,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    76,     0,     0,    77,     0,     0,   301,   302,   303,
     304,   305,   306,   307,     0,   259,   260,   261,     0,     0,
       0,     0,   308,    78,     0,     0,     0,   164,   165,   166,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    79,
       0,     0,    80,     0,     0,    81,     0,     0,     0,     0,
       0,    82,     0,     0,     0,     0,    83,    84,    85,     0,
       0,     0,     0,     0,     0,     0,     0,   310,     0,     0,
      86,   311,     0,    87,     0,    88,    89,    90,     0,     0,
       0,   312,    91,    92,     0,     0,     0,     0,     0,     0,
       0,   313,   314,   315,   316,   317,     0,   318,   319,    93,
      94,   320,   321,    95,   322,    96,    97,    98,    99,   100,
     101,   102,     0,   103,   323,   104,   105,   106,   107,     0,
     108,   324,   109,     0,     0,     0,     0,     0,     0,   110,
     581,     0,   111,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   327,
     328,     0,     0,     0,     0,     0,     0,     0,     0,   329,
     330,   331,     0,     0,     0,     0,   333,   112,   113,     0,
       0,     0,     0,     0,     0,   114,     0,     0,     0,   115,
       0,     0,     0,     0,     0,   116,     0,     0,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,     0,   127,
       0,     0,     0,     0,     0,   128,     0,     0,   129,     0,
       0,     0,   130,     0,     0,   131,   132,     0,   133,     0,
       0,   134,     0,   135,     0,     0,     0,   136,   137,     0,
       0,     0,     0,     0,   334,   335,   336,   337,     0,     0,
       0,     0,     0,     0,   142,     0,     0,     0,   338,     0,
       0,     0,   339,   340,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   143,     0,     0,
       0,     0,   144,   145,     0,     0,     0,     0,     0,     0,
    1914,     0,     0,     0,     0,     0,     0,  1915,     0,     0,
       0,     0,   285,   342,   286,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,     0,     0,   297,   298,     0,
       0,    73,    74,     0,     0,    75,   299,   300,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    76,     0,     0,
      77,     0,     0,   301,   302,   303,   304,   305,   306,   307,
       0,   259,   260,   261,     0,     0,     0,     0,   308,    78,
       0,     0,     0,   164,   165,   166,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    79,     0,     0,    80,     0,
       0,    81,     0,     0,     0,     0,     0,    82,     0,     0,
       0,     0,    83,    84,    85,     0,     0,     0,     0,     0,
       0,     0,     0,   310,     0,     0,    86,   311,     0,    87,
       0,    88,    89,    90,     0,     0,     0,   312,    91,    92,
       0,     0,     0,     0,     0,     0,     0,   313,   314,   315,
     316,   317,     0,   318,   319,    93,    94,   320,   321,    95,
     322,    96,    97,    98,    99,   100,   101,   102,     0,   103,
     323,   104,   105,   106,   107,     0,   108,   324,   109,     0,
       0,     0,     0,     0,     0,   110,   581,     0,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   327,   328,     0,     0,     0,
       0,     0,     0,     0,     0,   329,   330,   331,     0,     0,
       0,     0,   333,   112,   113,     0,     0,     0,     0,     0,
       0,   114,     0,     0,     0,   115,     0,     0,     0,     0,
       0,   116,     0,     0,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,     0,   127,     0,     0,     0,     0,
       0,   128,     0,     0,   129,     0,     0,     0,   130,     0,
       0,   131,   132,     0,   133,     0,     0,   134,     0,   135,
       0,     0,     0,   136,   137,     0,     0,     0,     0,     0,
     334,   335,   336,   337,     0,     0,     0,     0,     0,     0,
     142,     0,     0,     0,   338,   596,     0,     0,   339,   340,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   143,     0,     0,     0,     0,   144,   145,
       0,   285,     0,   286,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   296,     0,     0,   297,   298,     0,   342,
      73,    74,     0,     0,    75,   299,   300,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    76,     0,     0,    77,
       0,     0,   301,   302,   303,   304,   305,   306,   307,     0,
     259,   260,   261,     0,     0,     0,     0,   308,    78,     0,
       0,     0,   164,   165,   166,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    79,     0,     0,    80,     0,     0,
      81,     0,     0,     0,     0,     0,    82,     0,     0,     0,
       0,    83,    84,    85,     0,     0,     0,     0,     0,     0,
       0,     0,   310,     0,     0,    86,   311,     0,    87,     0,
      88,    89,    90,     0,     0,     0,   312,    91,    92,     0,
       0,     0,     0,     0,     0,     0,   313,   314,   315,   316,
     317,     0,   318,   319,    93,    94,   320,   321,    95,   322,
      96,    97,    98,    99,   100,   101,   102,     0,   103,   323,
     104,   105,   106,   107,     0,   108,   324,   109,     0,     0,
       0,     0,     0,     0,   110,   581,   665,   111,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   327,   328,     0,     0,     0,     0,
       0,     0,     0,     0,   329,   330,   331,     0,     0,     0,
       0,   333,   112,   113,     0,     0,     0,     0,     0,     0,
     114,     0,     0,     0,   115,     0,     0,     0,     0,     0,
     116,     0,     0,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,     0,   127,     0,     0,     0,     0,     0,
     128,     0,     0,   129,     0,     0,     0,   130,     0,     0,
     131,   132,     0,   133,     0,     0,   134,     0,   135,     0,
       0,     0,   136,   137,     0,     0,     0,     0,     0,   334,
     335,   336,   337,     0,     0,     0,     0,     0,     0,   142,
       0,     0,     0,   338,     0,     0,     0,   339,   340,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   143,     0,     0,     0,     0,   144,   145,     0,
     285,     0,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,     0,     0,   297,   298,     0,   342,    73,
      74,     0,     0,    75,   299,   300,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    76,     0,     0,    77,     0,
       0,   301,   302,   303,   304,   305,   306,   307,     0,   259,
     260,   261,     0,     0,     0,     0,   308,    78,     0,     0,
     162,   164,   165,   166,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    79,     0,     0,    80,     0,     0,    81,
       0,     0,     0,     0,     0,    82,     0,     0,     0,     0,
      83,    84,    85,     0,     0,     0,     0,     0,     0,     0,
       0,   310,     0,     0,    86,   311,     0,    87,     0,    88,
      89,    90,     0,     0,     0,   312,    91,    92,     0,     0,
       0,     0,     0,     0,     0,   313,   314,   315,   316,   317,
       0,   318,   319,    93,    94,   320,   321,    95,   322,    96,
      97,    98,    99,   100,   101,   102,     0,   103,   323,   104,
     105,   106,   107,     0,   108,   324,   109,     0,     0,     0,
       0,     0,     0,   110,   677,     0,   111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   327,   328,     0,     0,     0,     0,     0,
       0,     0,     0,   329,   330,   331,     0,     0,     0,     0,
     333,   112,   113,     0,     0,     0,     0,     0,     0,   114,
       0,     0,     0,   115,     0,     0,     0,     0,     0,   116,
       0,     0,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,     0,   127,     0,     0,     0,     0,     0,   128,
       0,     0,   129,     0,     0,     0,   130,     0,     0,   131,
     132,     0,   133,     0,     0,   134,     0,   135,     0,     0,
       0,   136,   137,     0,     0,     0,     0,     0,   334,   335,
     336,   337,     0,     0,     0,     0,     0,     0,   142,     0,
       0,     0,   338,     0,     0,     0,   339,   340,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   143,     0,     0,     0,     0,   144,   145,     0,   285,
       0,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,     0,     0,   297,   298,     0,   342,    73,    74,
       0,     0,    75,   299,   300,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    76,     0,     0,    77,     0,     0,
     301,   302,   303,   304,   305,   306,   307,     0,   259,   260,
     261,     0,     0,     0,     0,   308,    78,     0,     0,     0,
     164,   165,   166,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    79,     0,     0,  1298,     0,     0,    81,     0,
       0,     0,     0,     0,    82,     0,     0,     0,     0,    83,
      84,    85,     0,     0,     0,     0,     0,     0,     0,     0,
     310,     0,     0,    86,   311,     0,    87,     0,    88,    89,
      90,     0,     0,     0,   312,    91,    92,     0,     0,     0,
       0,     0,     0,     0,   313,   314,   315,   316,   317,     0,
     318,   319,    93,    94,   320,   321,    95,   322,    96,    97,
      98,    99,   100,   101,   102,     0,   103,   323,   104,   105,
     106,   107,     0,   108,   324,   109,     0,     0,     0,     0,
       0,     0,   110,   581,     0,   111,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   327,   328,     0,     0,     0,     0,     0,     0,
       0,     0,   329,   330,   331,     0,     0,     0,     0,   333,
     112,   113,     0,     0,     0,     0,     0,     0,   114,     0,
       0,     0,   115,     0,     0,     0,     0,     0,   116,     0,
       0,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,  1299,   127,     0,     0,     0,     0,     0,   128,     0,
       0,   129,     0,     0,     0,   130,     0,     0,   131,   132,
       0,   133,     0,     0,   134,     0,   135,     0,     0,     0,
     136,   137,     0,     0,     0,     0,     0,   334,   335,   336,
     337,     0,     0,     0,     0,     0,     0,   142,     0,     0,
       0,   338,     0,     0,     0,   339,   340,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     143,     0,     0,     0,     0,   144,   145,     0,   285,     0,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,     0,     0,   297,   298,     0,   342,    73,    74,     0,
       0,    75,   299,   300,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    76,     0,     0,    77,     0,     0,   301,
     302,   303,   304,   305,   306,   307,     0,   259,   260,   261,
       0,     0,     0,     0,   308,    78,     0,     0,     0,   164,
     165,   166,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    79,     0,     0,    80,     0,     0,    81,     0,     0,
       0,     0,     0,    82,     0,     0,     0,     0,    83,    84,
      85,     0,     0,     0,     0,     0,     0,     0,     0,   310,
       0,     0,    86,   311,     0,    87,     0,    88,    89,    90,
       0,     0,     0,   312,    91,    92,     0,     0,     0,     0,
       0,     0,     0,   313,   314,   315,   316,   317,     0,   318,
     319,    93,    94,   320,   321,    95,   322,    96,    97,    98,
      99,   100,   101,   102,     0,   103,   323,   104,   105,   106,
     107,     0,   108,   324,   109,     0,     0,     0,     0,     0,
       0,   110,   581,     0,   111,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   327,   328,     0,     0,     0,     0,     0,     0,     0,
       0,   329,   330,   331,     0,     0,     0,     0,   333,   112,
     113,     0,     0,     0,     0,     0,     0,   114,     0,     0,
       0,   115,     0,     0,     0,     0,     0,   116,     0,     0,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
       0,   127,     0,     0,     0,     0,     0,   128,     0,     0,
     129,     0,     0,     0,   130,     0,     0,   131,   132,     0,
     133,     0,     0,   134,     0,   135,     0,     0,     0,   136,
     137,     0,     0,     0,     0,     0,   334,   335,   336,   337,
       0,     0,     0,     0,     0,     0,   142,     0,     0,     0,
     338,  1582,     0,     0,   339,   340,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   143,
       0,     0,     0,     0,   144,   145,     0,   285,     0,   286,
     287,   288,   289,   290,   291,   292,   293,   294,   295,   296,
       0,     0,   297,   298,     0,   342,    73,    74,     0,     0,
      75,   299,   300,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    76,     0,     0,    77,     0,     0,   301,   302,
     303,   304,   305,   306,   307,     0,   259,   260,   261,     0,
       0,     0,     0,   308,    78,     0,     0,     0,   164,   165,
     166,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      79,     0,     0,    80,     0,     0,    81,     0,     0,     0,
       0,     0,    82,     0,     0,     0,     0,    83,    84,    85,
       0,     0,     0,     0,     0,     0,     0,     0,   310,     0,
       0,    86,   311,     0,    87,     0,    88,    89,    90,     0,
       0,     0,   312,    91,    92,     0,     0,     0,     0,     0,
       0,     0,   313,   314,   315,   316,   317,  1476,   318,   319,
      93,    94,   320,   321,    95,   322,    96,    97,    98,    99,
     100,   101,   102,     0,   103,   323,   104,   105,   106,   107,
       0,   108,   324,   109,     0,     0,     0,     0,     0,     0,
     110,   581,     0,   111,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     327,   328,     0,     0,     0,     0,     0,     0,     0,     0,
     329,   330,   331,     0,     0,     0,     0,   333,   112,   113,
       0,     0,     0,     0,     0,     0,   114,     0,     0,     0,
     115,     0,     0,     0,     0,     0,   116,     0,     0,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,     0,
     127,     0,     0,     0,     0,     0,   128,     0,     0,   129,
       0,     0,     0,   130,     0,     0,   131,   132,     0,   133,
       0,     0,   134,     0,   135,     0,     0,     0,   136,   137,
       0,     0,     0,     0,     0,   334,   335,   336,   337,     0,
       0,     0,     0,     0,     0,   142,     0,     0,     0,   338,
       0,     0,     0,   339,   340,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   143,     0,
       0,     0,     0,   144,   145,     0,   285,     0,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,     0,
       0,   297,   298,     0,   342,    73,    74,     0,     0,    75,
     299,   300,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    76,     0,     0,    77,     0,     0,   301,   302,   303,
     304,   305,   306,   307,     0,   259,   260,   261,     0,     0,
       0,     0,   308,    78,     0,     0,     0,   164,   165,   166,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    79,
       0,     0,    80,     0,     0,    81,     0,     0,     0,     0,
       0,    82,     0,     0,     0,     0,    83,    84,    85,     0,
       0,     0,     0,     0,     0,     0,     0,   310,     0,     0,
      86,   311,     0,    87,     0,    88,    89,    90,     0,     0,
       0,   312,    91,    92,     0,     0,     0,     0,     0,     0,
       0,   313,   314,   315,   316,   317,     0,   318,   319,    93,
      94,   320,   321,    95,   322,    96,    97,    98,    99,   100,
     101,   102,     0,   103,   323,   104,   105,   106,   107,     0,
     108,   324,   109,     0,     0,     0,     0,     0,     0,   110,
     581,     0,   111,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   327,
     328,     0,     0,     0,     0,     0,     0,     0,     0,   329,
     330,   331,     0,     0,     0,     0,   333,   112,   113,     0,
       0,     0,     0,     0,     0,   114,     0,     0,     0,   115,
       0,     0,     0,     0,     0,   116,     0,     0,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,     0,   127,
       0,     0,     0,     0,     0,   128,     0,     0,   129,     0,
       0,     0,   130,     0,     0,   131,   132,     0,   133,     0,
       0,   134,     0,   135,     0,     0,     0,   136,   137,     0,
       0,     0,     0,     0,   334,   335,   336,   337,     0,     0,
       0,     0,     0,     0,   142,     0,     0,     0,   338,     0,
       0,     0,   339,   340,     0,     0,     0,     0,    67,    68,
      69,    70,    71,    72,     0,     0,     0,   143,     0,     0,
       0,     0,   144,   145,     0,    73,    74,     0,     0,    75,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    76,     0,   342,    77,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    78,     3,     4,  1403,     6,     0,     0,
       0,     0,     0,     0,     0,     0,     7,     8,     9,  1404,
       0,     0,    80,     0,     0,  1405,     0,     0,     0,     0,
       0,    82,     0,     0,     0,     0,    83,    84,    85,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      86,     0,     0,    87,     0,    88,    89,    90,     0,     0,
       0,     0,    91,    92,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    93,
      94,     0,     0,    95,     0,    96,    97,    98,    99,   100,
     101,   102,     0,   103,     0,   104,   105,   106,   107,     0,
     108,     0,   109,     0,     0,     0,     0,     0,     0,   110,
       0,     0,   111,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   112,   113,     0,
       0,     0,     0,     0,     0,   114,     0,     0,    15,   115,
       0,     0,     0,     0,  1406,   116,    16,  1407,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,     0,   127,
      26,     0,     0,     0,     0,   128,    27,    28,   129,     0,
       0,     0,   130,     0,     0,   131,   132,     0,   133,     0,
       0,   134,    29,   135,  1408,    30,     0,   136,   137,     0,
       0,     0,     0,     0,   138,   139,   140,   141,     0,     0,
       0,     0,     0,     0,   142,     0,     0,     0,  1409,     0,
       0,     0,     0,     0,  1410,     0,     0,     0,     0,  1411,
       0,    31,     0,     0,     0,     0,     0,   143,     0,     0,
       0,     0,   144,   145,    67,    68,    69,    70,    71,    72,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    73,    74,     0,     0,    75,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    76,     0,     0,
      77,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    78,
       3,     4,  1403,     6,     0,     0,     0,     0,     0,     0,
       0,     0,     7,     8,     9,  1404,     0,     0,    80,     0,
       0,  1405,     0,     0,     0,     0,     0,    82,     0,     0,
       0,     0,    83,    84,    85,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    86,     0,     0,    87,
       0,    88,    89,    90,     0,     0,     0,     0,    91,    92,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    93,    94,     0,     0,    95,
       0,    96,    97,    98,    99,   100,   101,   102,     0,   103,
       0,   104,   105,   106,   107,     0,   108,     0,   109,     0,
       0,     0,     0,     0,     0,   110,     0,     0,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   112,   113,     0,     0,     0,     0,     0,
       0,   114,     0,     0,    15,   115,     0,     0,     0,     0,
    1711,   116,    16,  1407,  1712,   118,   119,   120,   121,   122,
     123,   124,   125,   126,     0,   127,    26,     0,     0,     0,
       0,   128,    27,    28,   129,     0,     0,     0,   130,     0,
       0,   131,   132,     0,   133,     0,     0,   134,    29,   135,
    1408,    30,     0,   136,   137,     0,     0,     0,     0,     0,
     138,   139,   140,   141,     0,     0,     0,     0,     0,     0,
     142,     0,     0,     0,  1409,     0,     0,     0,     0,     0,
    1410,     0,     0,     0,     0,  1411,     0,    31,     0,     0,
       0,     0,     0,   143,     0,     0,     0,     0,   144,   145,
      67,    68,    69,    70,    71,    72,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    73,    74,     0,
       0,    75,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    76,     0,     0,    77,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    78,     3,     4,  1403,     6,
       0,     0,     0,     0,     0,     0,     0,     0,     7,     8,
       9,  1404,     0,     0,    80,     0,     0,  1405,     0,     0,
       0,     0,     0,    82,     0,     0,     0,     0,    83,    84,
      85,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    86,     0,     0,    87,     0,    88,    89,    90,
       0,     0,     0,     0,    91,    92,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    93,    94,     0,     0,    95,     0,    96,    97,    98,
      99,   100,   101,   102,     0,   103,     0,   104,   105,   106,
     107,     0,   108,     0,   109,     0,     0,     0,     0,     0,
       0,   110,     0,     0,   111,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   112,
     113,     0,     0,     0,     0,     0,     0,   114,     0,     0,
      15,   115,     0,     0,     0,     0,     0,   116,    16,  1407,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
       0,   127,    26,     0,     0,     0,     0,   128,    27,    28,
     129,     0,     0,     0,   130,     0,     0,   131,   132,     0,
     133,     0,     0,   134,    29,   135,  1408,    30,     0,   136,
     137,     0,     0,     0,     0,     0,   138,   139,   140,   141,
       0,     0,     0,     0,     0,     0,   142,     0,     0,     0,
    1409,     0,     0,     0,     0,     0,  1410,     0,  -326,     0,
       0,     0,     0,    31,     0,     0,     0,     0,     0,   143,
       0,     0,     0,     0,   144,   145,    67,    68,    69,    70,
      71,    72,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    73,    74,     0,     0,    75,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    76,
       0,     0,    77,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    78,     3,     4,  1403,     6,     0,     0,     0,     0,
       0,     0,     0,     0,     7,     8,     9,  1404,     0,     0,
      80,     0,     0,  1405,     0,     0,     0,     0,     0,    82,
       0,     0,     0,     0,    83,    84,    85,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    86,     0,
       0,    87,     0,    88,    89,    90,     0,     0,     0,     0,
      91,    92,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    93,    94,     0,
       0,    95,     0,    96,    97,    98,    99,   100,   101,   102,
       0,   103,     0,   104,   105,   106,   107,     0,   108,     0,
     109,     0,     0,     0,     0,     0,     0,   110,     0,     0,
     111,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   112,   113,     0,     0,     0,
       0,     0,     0,   114,     0,     0,    15,   115,     0,     0,
       0,     0,     0,   116,    16,  1407,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,     0,   127,    26,     0,
       0,     0,     0,   128,    27,    28,   129,     0,     0,     0,
     130,     0,     0,   131,   132,     0,   133,     0,     0,   134,
      29,   135,  1408,    30,     0,   136,   137,     0,     0,     0,
       0,     0,   138,   139,   140,   141,    67,    68,    69,    70,
      71,    72,   142,     0,     0,     0,  1409,     0,     0,     0,
       0,     0,  1410,    73,    74,     0,     0,    75,  1932,    31,
       0,     0,     0,     0,     0,   143,     0,     0,     0,    76,
     144,   145,    77,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    78,     3,     4,  1403,     6,     0,     0,     0,     0,
       0,     0,     0,     0,     7,     8,     9,  1404,     0,     0,
      80,     0,     0,  1405,     0,     0,     0,     0,     0,    82,
       0,     0,     0,     0,    83,    84,    85,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    86,     0,
       0,    87,     0,    88,    89,    90,     0,     0,     0,     0,
      91,    92,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    93,    94,     0,
       0,    95,     0,    96,    97,    98,    99,   100,   101,   102,
       0,   103,     0,   104,   105,   106,   107,     0,   108,     0,
     109,     0,     0,     0,     0,     0,     0,   110,     0,     0,
     111,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   112,   113,     0,     0,     0,
       0,     0,     0,   114,     0,     0,    15,   115,     0,     0,
       0,     0,     0,   116,    16,  1407,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,     0,   127,    26,     0,
       0,     0,     0,   128,    27,    28,   129,     0,     0,     0,
     130,     0,     0,   131,   132,     0,   133,     0,     0,   134,
      29,   135,  1408,    30,     0,   136,   137,     0,     0,     0,
       0,     0,   138,   139,   140,   141,    67,    68,    69,    70,
      71,    72,   142,     0,     0,     0,  1409,     0,     0,     0,
       0,     0,  1410,    73,    74,     0,     0,    75,     0,    31,
       0,     0,     0,     0,     0,   143,     0,     0,     0,    76,
     144,   145,    77,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    78,     3,     4,  1403,     6,     0,     0,     0,     0,
       0,     0,     0,     0,     7,     8,     9,  1404,     0,     0,
      80,     0,     0,  1405,     0,     0,     0,     0,     0,    82,
       0,     0,     0,     0,    83,    84,    85,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    86,     0,
       0,    87,     0,    88,    89,    90,     0,     0,     0,     0,
      91,    92,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    93,    94,     0,
       0,    95,     0,    96,    97,    98,    99,   100,   101,   102,
       0,   103,     0,   104,   105,   106,   107,     0,   108,     0,
     109,     0,     0,     0,     0,     0,     0,   110,     0,     0,
     111,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   112,   113,     0,     0,     0,
       0,     0,     0,   114,     0,     0,     0,   115,     0,     0,
       0,     0,     0,   116,    16,  1407,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,     0,   127,     0,     0,
       0,     0,     0,   128,    27,    28,   129,     0,     0,     0,
     130,     0,     0,   131,   132,     0,   133,     0,     0,   134,
      29,   135,  1408,     0,     0,   136,   137,     0,     0,     0,
       0,     0,   138,   139,   140,   141,     0,     0,     0,     0,
       0,     0,   142,     0,     0,     0,  1409,     0,     0,     0,
       0,     0,  1410,     0,     0,     0,     0,  1889,     0,    31,
       0,     0,     0,     0,     0,   143,     0,     0,     0,     0,
     144,   145,    67,    68,    69,    70,    71,    72,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    73,
      74,     0,     0,    75,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    76,     0,     0,    77,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    78,     3,     4,
    1403,     6,     0,     0,     0,     0,     0,     0,     0,     0,
       7,     8,     9,  1404,     0,     0,    80,     0,     0,  1405,
       0,     0,     0,     0,     0,    82,     0,     0,     0,     0,
      83,    84,    85,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    86,     0,     0,    87,     0,    88,
      89,    90,     0,     0,     0,     0,    91,    92,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    93,    94,     0,     0,    95,     0,    96,
      97,    98,    99,   100,   101,   102,     0,   103,     0,   104,
     105,   106,   107,     0,   108,     0,   109,     0,     0,     0,
       0,     0,     0,   110,     0,     0,   111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   112,   113,     0,     0,     0,     0,     0,     0,   114,
       0,     0,     0,   115,     0,     0,     0,     0,     0,   116,
      16,  1407,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,     0,   127,     0,     0,     0,     0,     0,   128,
      27,    28,   129,     0,     0,     0,   130,     0,     0,   131,
     132,     0,   133,     0,     0,   134,    29,   135,  1408,     0,
       0,   136,   137,     0,     0,     0,     0,     0,   138,   139,
     140,   141,    67,    68,    69,    70,    71,    72,   142,     0,
       0,     0,  1409,     0,   220,     0,     0,     0,  1410,    73,
      74,     0,     0,    75,  1979,    31,     0,     0,     0,     0,
       0,   143,     0,     0,     0,    76,   144,   145,    77,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   222,     0,     0,     0,     0,    78,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    79,     0,     0,    80,     0,     0,    81,
       0,     0,     0,     0,     0,    82,     0,     0,     0,     0,
      83,    84,    85,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    86,     0,     0,    87,     0,    88,
      89,    90,     0,     0,     0,     0,    91,    92,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    93,    94,     0,     0,    95,     0,    96,
      97,    98,    99,   100,   101,   102,     0,   103,     0,   104,
     105,   106,   107,     0,   108,     0,   109,     0,     0,     0,
       0,     0,     0,   110,     0,     0,   111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   268,   269,   227,   228,   229,   230,     0,     0,   114,
       0,     0,     0,   115,     0,     0,     0,     0,     0,   116,
       0,     0,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,     0,   127,     0,     0,     0,     0,     0,   128,
       0,     0,   129,     0,     0,     0,   130,     0,     0,   131,
     132,     0,   133,     0,     0,   134,     0,   135,     0,     0,
       0,   270,   137,     0,     0,     0,     0,     0,   138,   139,
     140,   141,    67,    68,    69,   933,   934,   935,   142,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    73,
      74,     0,     0,    75,     0,     0,     0,     0,     0,     0,
       0,   143,     0,     0,     0,    76,   144,   145,    77,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    78,     0,     0,
       0,   164,   165,   166,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    79,     0,     0,    80,     0,     0,    81,
       0,     0,     0,     0,     0,    82,     0,     0,     0,     0,
      83,    84,    85,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    86,     0,     0,    87,     0,    88,
      89,    90,     0,     0,     0,     0,    91,    92,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    93,    94,     0,     0,    95,     0,    96,
      97,    98,    99,   100,   101,   102,     0,   103,     0,   104,
     105,   106,   107,     0,   108,     0,   109,     0,     0,     0,
       0,     0,     0,   110,     0,     0,   111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   936,     0,     0,
       0,   112,   113,     0,     0,     0,     0,     0,     0,   114,
       0,     0,     0,   115,     0,     0,     0,     0,     0,   116,
       0,     0,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,     0,   127,     0,     0,     0,     0,     0,   128,
       0,     0,   129,     0,     0,     0,   130,     0,     0,   131,
     132,     0,   133,     0,     0,   134,     0,   135,     0,     0,
       0,   136,   137,     0,     0,     0,     0,     0,   138,   139,
     140,   141,    67,    68,    69,   933,   934,   935,   142,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    73,
      74,     0,     0,    75,     0,     0,     0,     0,     0,     0,
       0,   143,     0,     0,     0,    76,   144,   145,    77,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    78,     0,     0,
       0,   164,   165,   166,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    79,     0,     0,    80,     0,     0,    81,
       0,     0,     0,     0,     0,    82,     0,     0,     0,     0,
      83,    84,    85,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    86,     0,     0,    87,     0,    88,
      89,    90,     0,     0,     0,     0,    91,    92,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    93,    94,     0,     0,    95,     0,    96,
      97,    98,    99,   100,   101,   102,     0,   103,     0,   104,
     105,   106,   107,     0,   108,     0,   109,     0,     0,     0,
       0,     0,     0,   110,     0,     0,   111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1369,     0,     0,
       0,   112,   113,     0,     0,     0,     0,     0,     0,   114,
       0,     0,     0,   115,     0,     0,     0,     0,     0,   116,
       0,     0,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,     0,   127,     0,     0,     0,     0,     0,   128,
       0,     0,   129,     0,     0,     0,   130,     0,     0,   131,
     132,     0,   133,     0,     0,   134,     0,   135,     0,     0,
       0,   136,   137,     0,     0,     0,     0,     0,   138,   139,
     140,   141,    67,    68,    69,    70,    71,    72,   142,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    73,
      74,     0,     0,    75,     0,     0,     0,     0,     0,     0,
       0,   143,     0,     0,     0,    76,   144,   145,    77,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    78,     0,     0,
       0,   164,   165,   166,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    79,     0,     0,    80,     0,     0,    81,
       0,     0,     0,     0,     0,    82,     0,     0,     0,     0,
      83,    84,    85,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    86,     0,     0,    87,     0,    88,
      89,    90,     0,     0,     0,     0,    91,    92,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    93,    94,     0,     0,    95,     0,    96,
      97,    98,    99,   100,   101,   102,     0,   103,     0,   104,
     105,   106,   107,     0,   108,     0,   109,     0,     0,     0,
       0,     0,     0,   110,     0,     0,   111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   112,   113,     0,     0,     0,     0,     0,     0,   114,
       0,     0,     0,   115,     0,     0,     0,     0,     0,   116,
       0,     0,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,     0,   127,     0,     0,     0,     0,     0,   128,
       0,     0,   129,     0,     0,     0,   130,     0,     0,   131,
     132,     0,   133,     0,     0,   134,     0,   135,     0,     0,
       0,   136,   137,     0,     0,     0,     0,     0,   138,   139,
     140,   141,    67,    68,    69,    70,    71,    72,   142,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    73,
      74,     0,     0,    75,     0,     0,     0,     0,     0,     0,
       0,   143,     0,     0,     0,    76,   144,   145,    77,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   259,
     260,   261,     0,     0,     0,     0,     0,   262,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    79,     0,     0,    80,     0,     0,    81,
       0,     0,     0,     0,     0,    82,     0,     0,     0,     0,
      83,    84,    85,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    86,     0,     0,    87,     0,    88,
      89,    90,     0,     0,     0,     0,    91,    92,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    93,    94,     0,     0,    95,     0,    96,
      97,    98,    99,   100,   101,   102,     0,   103,     0,   104,
     105,   106,   107,     0,   108,     0,   109,     0,     0,     0,
       0,     0,     0,   110,     0,     0,   111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   112,   113,     0,     0,     0,     0,     0,     0,   114,
       0,     0,     0,   115,     0,     0,     0,     0,     0,   116,
       0,     0,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,     0,   127,     0,     0,     0,     0,     0,   128,
       0,     0,   263,     0,     0,     0,   130,     0,     0,   131,
     132,     0,   133,     0,     0,   264,     0,   135,     0,     0,
       0,   136,   137,     0,     0,     0,     0,     0,   138,   265,
     140,   141,    67,    68,    69,   933,   934,   935,   142,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    73,
      74,     0,     0,    75,     0,     0,     0,     0,     0,     0,
       0,   143,     0,     0,     0,    76,   144,   145,    77,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    78,     0,     0,
       0,   164,   165,   166,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    79,     0,     0,    80,     0,     0,    81,
       0,     0,     0,     0,     0,    82,     0,     0,     0,     0,
      83,    84,    85,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    86,     0,     0,    87,     0,    88,
      89,    90,     0,     0,     0,     0,    91,    92,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    93,    94,     0,     0,    95,     0,    96,
      97,    98,    99,   100,   101,   102,     0,   103,     0,   104,
     105,   106,   107,     0,   108,     0,   109,     0,     0,     0,
       0,     0,     0,   110,     0,     0,   111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   112,   113,     0,     0,     0,     0,     0,     0,   114,
       0,     0,     0,   115,     0,     0,     0,     0,     0,   116,
       0,     0,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,     0,   127,     0,     0,     0,     0,     0,   128,
       0,     0,   129,     0,     0,     0,   130,     0,     0,   131,
     132,     0,   133,     0,     0,   134,     0,   135,     0,     0,
       0,   136,   137,     0,     0,     0,     0,     0,   138,   139,
     140,   141,    67,    68,    69,    70,    71,    72,   142,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    73,
      74,     0,     0,    75,     0,     0,     0,     0,     0,     0,
       0,   143,     0,     0,     0,    76,   144,   145,    77,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    78,     0,     0,
     162,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    79,     0,     0,    80,     0,     0,    81,
       0,     0,     0,     0,     0,    82,     0,     0,     0,     0,
      83,    84,    85,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    86,     0,     0,    87,     0,    88,
      89,    90,     0,     0,     0,     0,    91,    92,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    93,    94,     0,     0,    95,     0,    96,
      97,    98,    99,   100,   101,   102,     0,   103,     0,   104,
     105,   106,   107,     0,   108,     0,   109,     0,     0,     0,
       0,     0,     0,   110,    14,     0,   111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   112,   113,     0,     0,     0,     0,     0,     0,   114,
       0,     0,     0,   115,     0,     0,     0,     0,     0,   116,
       0,     0,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,     0,   127,     0,     0,     0,     0,     0,   128,
       0,     0,   129,     0,     0,     0,   130,     0,     0,   131,
     132,     0,   133,     0,     0,   134,     0,   135,     0,     0,
       0,   136,   137,     0,     0,     0,     0,     0,   138,   139,
     140,   141,    67,    68,    69,    70,    71,    72,   142,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    73,
      74,     0,     0,    75,     0,     0,     0,     0,     0,     0,
       0,   143,     0,     0,     0,    76,   144,   145,    77,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    78,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    79,     0,     0,    80,     0,     0,    81,
       0,     0,     0,     0,     0,    82,     0,     0,     0,     0,
      83,    84,    85,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    86,     0,     0,    87,     0,    88,
      89,    90,     0,     0,     0,     0,    91,    92,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    93,    94,     0,     0,    95,     0,    96,
      97,    98,    99,   100,   101,   102,     0,   103,     0,   104,
     105,   106,   107,     0,   108,     0,   109,     0,     0,     0,
       0,     0,     0,   110,     0,     0,   111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1015,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   112,   113,     0,     0,     0,     0,     0,     0,   114,
       0,  1016,     0,   115,     0,     0,     0,     0,     0,   116,
       0,     0,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,     0,   127,     0,     0,     0,     0,     0,   128,
       0,     0,   129,     0,     0,     0,   130,     0,     0,   131,
     132,     0,   133,     0,     0,   134,     0,   135,     0,     0,
       0,   136,   137,     0,     0,     0,     0,     0,   138,   139,
     140,   141,    67,    68,    69,    70,    71,    72,   142,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    73,
      74,     0,     0,    75,     0,     0,     0,     0,     0,     0,
       0,   143,     0,     0,     0,    76,   144,   145,    77,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    78,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    79,     0,     0,    80,     0,     0,    81,
       0,     0,     0,     0,     0,    82,     0,     0,     0,     0,
      83,    84,    85,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    86,     0,     0,    87,     0,    88,
      89,    90,     0,     0,     0,     0,    91,    92,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    93,    94,     0,     0,    95,     0,    96,
      97,    98,    99,   100,   101,   102,     0,   103,     0,   104,
     105,   106,   107,     0,   108,     0,   109,     0,     0,     0,
       0,     0,     0,   110,     0,     0,   111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   112,   113,     0,     0,     0,     0,     0,     0,   114,
       0,     0,     0,   115,     0,     0,     0,     0,     0,   116,
       0,     0,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,     0,   127,     0,     0,     0,     0,     0,   128,
       0,     0,   129,     0,     0,     0,   130,     0,     0,   131,
     132,     0,   133,     0,     0,   134,   442,   135,     0,     0,
       0,   136,   137,     0,     0,     0,     0,     0,   138,   139,
     140,   141,    67,    68,    69,    70,    71,    72,   142,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    73,
      74,     0,     0,    75,     0,     0,     0,     0,     0,     0,
       0,   143,     0,     0,     0,    76,   144,   145,    77,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    78,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    79,     0,     0,    80,     0,     0,    81,
       0,     0,     0,     0,     0,    82,     0,     0,     0,     0,
      83,    84,    85,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    86,     0,     0,    87,     0,    88,
      89,    90,     0,     0,     0,     0,    91,    92,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    93,    94,     0,     0,    95,     0,    96,
      97,    98,    99,   100,   101,   102,     0,   103,     0,   104,
     105,   106,   107,     0,   108,     0,   109,     0,     0,     0,
       0,     0,     0,   110,   412,     0,   111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   112,   113,     0,     0,     0,     0,     0,     0,   114,
       0,     0,     0,   115,     0,     0,     0,     0,     0,   116,
       0,     0,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,     0,   127,     0,     0,     0,     0,     0,   128,
       0,     0,   129,     0,     0,     0,   130,     0,     0,   131,
     132,     0,   133,     0,     0,   134,     0,   135,     0,     0,
       0,   136,   137,     0,     0,     0,     0,     0,   138,   139,
     140,   141,    67,    68,    69,    70,    71,    72,   142,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    73,
      74,     0,     0,    75,     0,     0,     0,     0,     0,     0,
       0,   143,     0,     0,     0,    76,   144,   145,    77,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    78,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    79,     0,     0,    80,     0,     0,    81,
       0,     0,     0,     0,     0,    82,     0,     0,     0,     0,
      83,    84,    85,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    86,     0,     0,    87,     0,    88,
      89,    90,     0,     0,     0,     0,    91,    92,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    93,    94,     0,     0,    95,     0,    96,
      97,    98,    99,   100,   101,   102,     0,   103,     0,   104,
     105,   106,   107,     0,   108,     0,   109,     0,     0,     0,
       0,     0,     0,   110,     0,     0,   111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1003,     0,     0,
       0,   112,   113,     0,     0,     0,     0,     0,     0,   114,
       0,     0,     0,   115,     0,     0,     0,     0,     0,   116,
       0,     0,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,     0,   127,     0,     0,     0,     0,     0,   128,
       0,     0,   129,     0,     0,     0,   130,     0,     0,   131,
     132,     0,   133,     0,     0,   134,     0,   135,     0,     0,
       0,   136,   137,     0,     0,     0,     0,     0,   138,   139,
     140,   141,    67,    68,    69,    70,    71,    72,   142,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    73,
      74,     0,     0,    75,     0,     0,     0,     0,     0,     0,
       0,   143,     0,     0,     0,    76,   144,   145,    77,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    78,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    79,     0,     0,    80,     0,     0,    81,
       0,     0,     0,     0,     0,    82,     0,     0,     0,     0,
      83,    84,    85,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    86,     0,     0,    87,     0,    88,
      89,    90,     0,     0,     0,     0,    91,    92,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    93,    94,     0,     0,    95,     0,    96,
      97,    98,    99,   100,   101,   102,     0,   103,     0,   104,
     105,   106,   107,     0,   108,     0,   109,     0,     0,     0,
       0,     0,     0,   110,     0,     0,   111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   112,   113,     0,     0,     0,     0,     0,     0,   114,
       0,  1016,     0,   115,     0,     0,     0,     0,     0,   116,
       0,     0,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,     0,   127,     0,     0,     0,     0,     0,   128,
       0,     0,   129,     0,     0,     0,   130,     0,     0,   131,
     132,     0,   133,     0,     0,   134,     0,   135,     0,     0,
       0,   136,   137,     0,     0,     0,     0,     0,   138,   139,
     140,   141,    67,    68,    69,    70,    71,    72,   142,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    73,
      74,     0,     0,    75,     0,     0,     0,     0,     0,     0,
       0,   143,     0,     0,     0,    76,   144,   145,    77,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    78,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    79,     0,     0,    80,     0,     0,    81,
       0,     0,     0,     0,     0,    82,     0,     0,     0,     0,
      83,    84,    85,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    86,     0,     0,    87,     0,    88,
      89,    90,     0,     0,     0,     0,    91,    92,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    93,    94,     0,     0,    95,     0,    96,
      97,    98,    99,   100,   101,   102,     0,   103,     0,   104,
     105,   106,   107,     0,   108,     0,   109,     0,     0,     0,
       0,     0,     0,   110,     0,     0,   111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   112,   113,     0,     0,     0,     0,     0,     0,   114,
       0,     0,     0,   115,     0,     0,     0,     0,     0,   116,
       0,     0,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,     0,   127,     0,     0,     0,     0,     0,   128,
       0,     0,   129,     0,     0,     0,   130,     0,     0,   131,
     132,     0,   133,     0,     0,   134,     0,   135,     0,     0,
       0,   136,   137,     0,     0,     0,     0,     0,   138,   139,
     140,   141,    67,    68,    69,    70,    71,    72,   142,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    73,
      74,     0,     0,    75,     0,     0,     0,     0,     0,     0,
       0,   143,     0,     0,     0,    76,   144,   145,    77,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    78,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    79,     0,     0,    80,     0,     0,    81,
       0,     0,     0,     0,     0,    82,     0,     0,     0,     0,
      83,    84,    85,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    86,     0,     0,    87,     0,    88,
      89,    90,     0,     0,     0,     0,    91,    92,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    93,    94,     0,     0,    95,     0,    96,
      97,    98,    99,   100,   101,   102,     0,   103,     0,   104,
     105,   106,   107,     0,   108,     0,   109,     0,     0,     0,
       0,     0,     0,   110,     0,     0,   111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   112,   113,     0,     0,     0,     0,     0,     0,   468,
       0,     0,     0,   115,     0,     0,     0,     0,     0,   116,
       0,     0,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,     0,   127,     0,     0,     0,     0,     0,   128,
       0,     0,   129,     0,     0,     0,   130,     0,     0,   131,
     132,     0,   133,     0,     0,   134,     0,   135,     0,     0,
       0,   136,   137,     0,     0,     0,     0,     0,   138,   139,
     140,   141,    67,    68,    69,    70,    71,    72,   142,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    73,
      74,     0,     0,    75,     0,     0,     0,     0,     0,     0,
       0,   143,     0,     0,     0,    76,   144,   145,    77,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    78,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    79,     0,     0,    80,     0,     0,    81,
       0,     0,     0,     0,     0,    82,     0,     0,     0,     0,
      83,    84,    85,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    86,     0,     0,    87,     0,    88,
      89,    90,     0,     0,     0,     0,    91,    92,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    93,    94,     0,     0,    95,     0,    96,
      97,    98,    99,   100,   101,   102,     0,   103,     0,   104,
     105,   106,   107,     0,   108,     0,   109,     0,     0,     0,
       0,     0,     0,   110,     0,     0,   111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   112,   113,     0,     0,     0,     0,     0,     0,   114,
       0,     0,     0,   115,     0,     0,     0,     0,     0,   116,
       0,     0,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,     0,   127,     0,     0,     0,     0,     0,   128,
       0,     0,   129,     0,     0,     0,   130,     0,     0,   131,
     132,     0,   133,     0,     0,   134,     0,   135,     0,     0,
       0,   689,   137,     0,     0,     0,     0,     0,   138,   139,
     140,   141,    67,    68,    69,    70,    71,    72,   142,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    73,
      74,     0,     0,    75,     0,     0,     0,     0,     0,     0,
       0,   143,     0,     0,     0,    76,   144,   145,    77,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    78,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    79,     0,     0,    80,     0,     0,    81,
       0,     0,     0,     0,     0,    82,     0,     0,     0,     0,
      83,    84,    85,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    86,     0,     0,    87,     0,    88,
      89,    90,     0,     0,     0,     0,    91,    92,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    93,    94,     0,     0,    95,     0,    96,
      97,    98,    99,   100,   101,   102,     0,   103,     0,   104,
     105,   106,   107,     0,   108,     0,   109,     0,     0,     0,
       0,     0,     0,   110,     0,     0,   111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   112,   113,     0,     0,     0,     0,     0,     0,   114,
       0,     0,     0,   115,     0,     0,     0,     0,     0,   116,
       0,     0,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,     0,   127,     0,     0,     0,     0,     0,   128,
       0,     0,   129,     0,     0,     0,   130,     0,     0,   131,
     132,     0,   133,     0,     0,   134,     0,   135,     0,     0,
       0,   136,   137,     0,     0,     0,     0,     0,   138,   139,
     140,   141,     0,     0,     0,     0,     0,     0,   142,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1150,     0,     0,     0,     0,   144,   145
};

static const yytype_int16 yycheck[] =
{
       0,    31,    36,    31,    17,   162,     0,    31,   283,   212,
     283,   273,     0,   415,   560,   533,   161,   713,     0,   517,
     990,   557,   568,  1224,     0,   273,   171,   325,   273,     3,
       0,   879,   880,   604,   417,  1199,     0,   418,    27,   516,
     893,   894,   736,  1286,   189,   190,    11,   325,   326,   194,
      16,   642,  1449,   207,   433,    81,     0,    25,     3,   285,
     286,   287,   105,   341,    11,    79,     0,    14,   484,   485,
     562,  1348,     4,   872,   727,   728,    27,     9,   570,     0,
      11,    13,  1012,  1012,    14,    17,    18,     3,     5,     6,
       7,     8,     9,    10,   824,  1352,   826,   592,   488,   489,
     270,   309,    79,    35,    36,   109,   533,   837,   334,   105,
       3,    63,  1355,   119,   497,    61,    62,    63,    64,  1628,
    1363,   105,  1631,   237,  1355,   398,   103,   283,   146,    55,
     148,   159,  1363,   147,    66,  1100,   150,   143,   151,     5,
       6,     7,   146,   299,   148,   259,  1587,     5,     6,     7,
       8,     9,    10,   671,    20,   325,   382,   383,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,   172,   173,   174,   175,   176,   177,   172,   173,
     174,   175,   176,   177,   172,   173,   174,   175,   176,   177,
     172,   173,   174,   175,   176,   177,   172,   173,   174,   175,
     176,   177,   172,   173,   174,   175,   176,   177,   172,   173,
     174,   175,   176,   177,  1611,   167,   205,  1381,   601,   151,
     152,   447,   167,    42,    43,   157,   172,   152,   172,   173,
     174,   175,   176,   177,     3,   104,   167,   535,   172,   173,
     174,   175,   176,   177,   671,   167,    63,   450,   546,   547,
     165,   172,   173,   174,   175,   176,   177,     3,  1535,  1700,
      79,   160,   161,   162,   645,  1706,    61,    62,    63,    64,
     186,   187,   165,   571,   167,    61,   208,   209,   210,  1536,
     775,   776,   325,   581,   782,   803,   440,   833,   234,   221,
      11,   223,   986,   571,    80,   325,   247,   323,   596,   231,
     232,   233,   234,   235,   236,   237,   783,   239,   240,  1239,
    1239,   257,   610,  1822,   246,   247,   695,   696,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   472,   302,   325,
     746,   263,   264,   611,   300,   926,  1135,   928,   270,   256,
     317,   325,    63,   621,   997,   322,  1787,   839,   274,   165,
     167,   283,   284,     4,  1319,  1796,   301,   105,   748,   749,
     750,   167,   752,   753,   754,   330,   235,    18,   398,   595,
     398,  1101,  1817,   325,  1104,   104,   803,   165,    52,   677,
     168,   313,  1625,   330,     5,   243,   167,  1588,   246,  1553,
      11,    79,  1593,   167,   167,   325,   604,   167,   167,    16,
     325,  1447,   415,    63,   326,   271,   272,   273,   274,     3,
     325,  1808,    99,    79,   165,    66,   168,   104,  1859,   165,
    1861,   167,   325,   168,   356,    95,   329,   104,   538,    63,
     329,    21,    22,   113,   104,   109,   116,    79,   104,   234,
     259,   170,    80,   432,   165,   168,   167,   105,    65,    66,
      67,   237,    69,    70,    71,    72,    55,   719,   145,   325,
     843,   168,   257,   266,   498,   152,   251,   168,   145,   850,
     168,   719,   168,   701,   719,  1328,  1329,   409,   166,   168,
     412,     0,   168,   415,    83,   168,   418,   168,   239,   751,
     718,    63,   168,     0,  1835,   168,   426,   607,   136,   247,
     170,   152,   434,   751,   766,   165,  1707,   167,   259,   325,
     104,   809,   154,  1559,   717,   157,  1957,   449,   766,    64,
     326,   766,   325,  1059,  1969,   555,   458,   459,   460,   461,
     462,   165,   807,   167,   807,   127,   468,   325,   168,    84,
     325,   571,   474,   475,   168,   326,   478,   164,   480,   481,
     482,   581,   326,   326,   168,  1249,   326,   221,   209,   210,
     492,   225,   283,  1904,   496,   235,   498,  1297,  1139,   952,
     715,   849,   223,   325,  1145,   235,  1147,   167,  1308,   168,
     325,   232,   233,   234,  1175,  1315,   237,   519,   239,   240,
     264,   604,   870,   165,  1086,   167,   247,   168,   806,   250,
     251,   252,   325,   254,   255,   256,   257,   258,   268,   104,
     168,   251,   112,   891,   892,   115,   264,   304,   325,   270,
     650,   589,   650,   591,   325,   555,   639,   325,   168,   325,
     856,   168,   858,   250,   268,    52,   325,    53,   325,   325,
     168,   571,   325,    59,   325,  1035,  1036,   677,   172,   325,
     247,   581,   325,   172,   173,   174,   175,   176,   177,   168,
     168,   309,    63,   235,   872,   172,   173,   174,   175,   176,
     177,   172,   604,   605,   152,   170,   608,   168,  1693,  1527,
    1198,  1199,    65,    66,    67,   325,    69,    70,    71,    72,
     168,   659,   109,    77,   152,   325,   268,   905,   109,    75,
     264,   325,     5,     6,     7,   356,   286,   639,   288,   641,
     168,   325,   236,   645,   646,    83,   646,    20,   213,  1689,
    1690,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,   236,   325,   148,   286,   214,
     288,  1124,   159,   969,  1006,   309,   121,   677,  1131,   114,
    1133,   126,   117,     0,   325,   172,   127,   689,  1006,   254,
     127,  1006,   257,  1025,   165,   973,   167,   325,  1314,    52,
     973,  1317,   267,  1344,  1155,  1346,   259,  1025,  1349,  1277,
    1025,   164,   714,   434,  1799,   325,  1801,    98,   325,   264,
     265,   204,   205,  1174,   726,   727,   728,   325,   449,   326,
     217,   218,   219,   735,   736,   773,   184,   458,   459,   460,
     461,   462,  1202,  1203,  1204,   747,   325,   325,  1080,  1081,
     788,   124,   125,   286,   475,   288,   109,   478,   245,   480,
     481,   482,  1080,  1081,   325,  1080,  1081,   167,   159,   214,
     238,   258,   872,   167,   104,    39,    40,   264,   255,   160,
     161,   162,   269,   172,   173,   237,   254,   176,   177,   872,
     235,    84,   326,  1381,    87,   167,   796,   797,   798,   267,
      93,  1567,  1568,    67,   266,   807,   159,   259,   810,   325,
     262,   263,   142,   104,   144,   145,   303,   819,   305,   172,
     721,   722,   723,   724,   250,   827,   217,   218,   219,   286,
     121,   288,   834,   171,   251,   126,   174,   175,   176,   177,
     178,   179,   180,   181,   745,   251,   184,   185,   850,    83,
      61,    62,   950,    64,   160,   161,   162,  1135,   215,   204,
     205,  1139,   168,    11,   217,   218,   219,  1145,  1164,  1147,
     872,   247,   872,  1326,  1327,   218,   878,   879,   880,   170,
     237,   264,    84,  1336,    78,    79,   243,   244,  1529,    91,
      92,   303,   245,   893,   894,    85,    86,  1193,   271,   272,
     273,   274,   160,   161,   162,   262,   160,   161,   162,  1252,
     168,   264,   240,   241,   168,   264,   269,  1213,   264,  1215,
    1216,  1217,   213,   214,   200,   201,   202,  1027,  1028,  1027,
    1028,  1547,   264,  1027,  1028,   264,   965,  1269,   967,   968,
     942,   218,  1012,  1809,   235,  1811,  1812,  1813,  1012,   212,
     303,  1269,   305,   307,   308,    65,    66,    67,    42,    43,
     960,    71,    72,   254,   171,  1553,   257,   281,   689,   971,
     972,   160,   161,   162,   976,   977,   267,   264,   980,   617,
     618,   619,   984,   985,   986,    96,    97,   325,  1356,   171,
      17,   264,   265,   714,   264,   997,   176,   177,  1012,   325,
    1002,     5,     6,     7,     8,     9,    10,    99,  1012,  1011,
    1358,  1359,   167,  1015,  1016,   275,   276,   277,   278,   279,
     280,  1012,    98,   186,   187,    52,   747,   282,    55,  1645,
     270,  1033,    89,    90,     3,  1135,   304,   305,   306,   307,
    1408,     3,  1410,    85,    86,   311,   312,   167,  1664,    61,
      62,   127,  1135,   167,   768,   167,  1139,   771,   772,   773,
     309,   310,  1145,   167,  1147,    22,  1344,   167,  1346,   174,
     175,  1349,  1922,  1923,   788,   789,   790,   791,   710,   711,
     278,   279,   109,   119,   160,   161,   162,   531,   532,   167,
     167,   304,   168,   167,  1390,   167,  1392,   167,   819,  1442,
    1443,  1573,  1434,  1435,  1436,   275,   276,   277,   278,   279,
     280,   167,   167,   167,   105,   167,  1434,  1435,  1436,  1434,
    1435,  1436,   167,   167,   167,   326,  1399,   167,   167,   167,
     167,   182,   159,  1135,   167,  1135,   167,  1139,  1138,   215,
     315,   325,   167,  1145,   315,  1147,   167,   167,  1150,   266,
      88,    94,   325,  1155,  1156,   304,   284,  1261,   106,   127,
     127,   237,   127,   127,  1532,   106,   105,   243,   244,  1239,
     283,   111,  1174,   165,  1176,  1239,  1403,   204,   205,   206,
     207,   208,   209,   247,   167,   304,   262,   221,  1531,   216,
     217,   218,   219,   167,   167,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   165,   282,   283,   284,   200,
     201,   202,   212,   235,  1582,   167,   218,   167,   245,    38,
     167,  1589,  1224,  1225,  1840,  1239,   163,   171,   326,   171,
    1232,   258,   167,   167,   167,  1239,  1274,   264,  1276,   167,
     267,   167,   269,  1281,   167,   167,   167,  1249,  1239,   325,
     167,  1529,   275,   276,   277,   278,   279,   280,    23,  1261,
    1262,  1344,   168,  1346,   985,  1561,  1349,   283,   106,  1565,
     149,   222,     3,  1569,   167,   165,   222,   168,   305,   328,
     168,   167,   171,   167,  1286,   174,   175,   176,   177,   178,
     179,   180,   181,   167,  1015,   184,   185,   200,   174,   175,
     176,   177,   178,   179,   180,   181,   168,  1309,  1408,   185,
    1408,    17,  1033,   268,  1408,    78,    75,   167,   105,   227,
     165,   266,     0,     1,  1407,   110,   242,   258,  1328,  1329,
     167,   246,    20,   265,   325,   222,   299,   250,   304,   253,
      23,   266,  1344,   304,  1346,   325,    52,  1349,    99,    55,
    1352,  1719,   105,  1355,   325,   304,   152,   167,  1462,   140,
      98,  1363,   168,   272,   168,  1710,   325,   287,   297,   325,
     103,   325,   202,    51,   104,   168,  1672,   168,   167,   167,
     316,   167,    84,    61,    62,    63,    64,   246,   105,   243,
     242,    99,    86,   104,   242,    73,    74,    75,    76,     5,
       6,     7,   300,   109,    82,  1407,   325,   325,   105,   105,
      82,   250,   168,   325,    20,   259,   168,   250,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,   168,   306,   250,   266,  1438,    99,   304,   168,
     325,   168,   168,   168,   168,   325,  1529,   168,  1816,   127,
     325,   155,   168,   159,   168,   168,   168,   167,   325,   168,
    1462,   168,   325,   168,   167,   297,  1798,   167,   167,   281,
     168,    71,     5,     6,     7,     8,     9,    10,  1774,    71,
    1798,    68,   167,  1798,    99,   102,  1488,   165,    99,   167,
    1573,   168,   168,    98,  1862,   168,   251,   168,   204,   205,
     206,   207,   208,   209,   251,    16,  1721,   304,   165,   168,
     216,   217,   218,   219,     3,   249,   325,   249,   165,   220,
     165,   167,    73,  1868,   252,  1527,   168,  1529,    61,    62,
      63,    64,   168,   220,  1536,   304,   137,   215,   137,   245,
     235,   168,   168,   266,   168,   223,   224,    71,   226,   167,
     228,   229,   230,   231,   232,   233,   234,    99,   264,   237,
     168,   267,   168,   269,  1566,   243,   244,   312,   259,   235,
     168,  1573,  1574,   120,    79,   325,   325,   167,   222,   222,
     221,   259,   165,   327,   262,   122,  1588,   167,  1803,   168,
     213,  1593,   314,   168,   168,   167,   156,   168,  1698,   305,
    1698,  1933,   295,   171,  1698,  1607,   174,   175,   176,   177,
     178,   179,   180,   181,   293,  1933,   184,   185,  1933,   250,
     298,   250,   250,  1625,  1626,   250,     5,     6,     7,   168,
     168,   185,   242,   325,   104,   167,   326,   258,   214,   172,
    1642,    20,   167,   325,   325,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,   222,
     325,   325,   257,   167,   304,   271,   272,   273,   274,   104,
     167,  1673,   249,   327,   328,   287,   166,   106,   251,   333,
      81,    81,   104,   104,   338,   104,  1407,   168,   250,   171,
     309,  1693,   174,   175,   176,   177,   178,   179,   180,   181,
     250,   234,   184,   185,   320,  1707,   320,     3,  1710,   318,
     168,   247,   171,   258,  1716,   174,   175,   176,   177,   178,
     179,   180,   181,   325,   257,   127,   185,   297,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   326,   287,
       5,   294,   200,   201,   202,   222,   222,  1817,     5,   123,
     148,   286,   313,  1817,   145,  1757,   145,   326,   304,  1817,
     325,     3,   150,   417,   184,  1817,    56,   285,   297,   168,
     127,  1817,   426,     4,  1776,   297,     4,  1817,  1780,   107,
     167,  1783,   168,  1817,   153,   150,  1788,   147,   309,    57,
     321,  1793,   127,   285,   297,   297,   250,  1799,    58,  1801,
     295,   309,   319,   287,   320,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,  1817,   291,   168,  1820,   200,
     201,   202,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,  1834,   293,   250,   250,   200,   201,   202,    61,
      41,    62,   127,   497,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,  1856,  1239,   205,   735,   200,   201,
     202,  1186,  1875,   204,  1866,   962,  1868,   325,   435,  1220,
    1400,  1781,  1571,   527,    36,  1692,  1559,   986,  1249,  1881,
    1882,  1883,  1884,  1964,  1941,   264,  1607,  1942,  1593,  1934,
    1874,  1969,   271,   272,   273,   274,  1705,  1705,  1584,  1969,
    1436,  1970,  1728,  1727,  1269,  1969,   560,   561,   562,     8,
     155,  1969,   660,  1397,   568,  1776,   570,  1969,  1849,  1779,
    1216,  1326,  1392,  1969,  1926,  1327,  1928,  1143,   648,  1969,
     584,   585,   586,   950,   960,  1969,   807,   409,  1156,   841,
     620,  1543,  1065,   804,   325,   613,   600,   601,   622,  1664,
     639,    35,   882,   547,   859,   495,   863,  1959,  1631,   863,
     599,   325,   616,   617,   618,   619,   650,  1969,  1970,   623,
     624,   625,   626,   627,   628,   629,   630,   631,   632,   633,
     634,   635,   803,   325,   533,  1819,  1629,   641,   642,  1480,
    1645,  1307,  1296,  1487,  1299,  1716,  1751,     5,     6,     7,
       8,     9,    10,   569,  1831,    -1,  1839,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    22,    23,    -1,    -1,    26,     5,
       6,     7,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      38,    -1,    -1,    41,    20,    -1,    -1,    -1,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    60,    -1,    -1,    63,    64,    65,    66,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,
      -1,    79,    -1,    -1,    82,    -1,    -1,   101,    -1,    -1,
      88,    -1,    -1,    -1,    -1,    93,    94,    95,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   107,
      -1,    -1,   110,    -1,   112,   113,   114,    -1,    -1,    -1,
      -1,   119,   120,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   136,   137,
      -1,    -1,   140,    -1,   142,   143,   144,   145,   146,   147,
     148,    -1,   150,    -1,   152,   153,   154,   155,    -1,   157,
      -1,   159,    -1,    -1,    -1,    -1,    -1,   165,   166,   167,
      -1,   169,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,    -1,    -1,    -1,   829,   200,   201,   202,   833,
      -1,    -1,    -1,    -1,    -1,   839,    -1,    -1,    -1,   843,
      -1,    -1,    -1,    -1,    -1,    -1,   204,   205,    -1,    -1,
      -1,    -1,    -1,    -1,   212,    -1,    -1,   861,   216,    -1,
     864,    -1,    -1,    -1,   222,    -1,    -1,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,    -1,   236,    -1,
      -1,    -1,    -1,    -1,   242,    -1,    -1,   245,    -1,   893,
     894,   249,    -1,    -1,   252,   253,    -1,   255,    -1,    -1,
     258,    -1,   260,    -1,    -1,    -1,   264,   265,    -1,    -1,
     268,    -1,    -1,   271,   272,   273,   274,    -1,    -1,    -1,
      -1,    -1,   926,   281,   928,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   271,   272,   273,   274,   200,
     201,   202,    -1,    -1,    -1,    -1,   304,    -1,   952,    -1,
      -1,   309,   310,    -1,    -1,    -1,   960,   106,    -1,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,    -1,
     328,    -1,    -1,   200,   201,   202,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,    -1,    -1,    -1,    -1,
     200,   201,   202,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       5,     6,     7,     8,     9,    10,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    22,    23,   168,
      -1,    26,    -1,    -1,    -1,    -1,   287,    -1,    -1,    -1,
      -1,    -1,    -1,    38,    -1,    -1,    41,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,    -1,    -1,    -1,
      -1,   200,   201,   202,    -1,    60,    61,    62,    63,    64,
     287,  1065,    -1,    -1,    -1,    -1,    -1,    -1,    73,    74,
      75,    76,    -1,    -1,    79,    -1,   286,    82,  1082,    -1,
      -1,    -1,  1086,    88,    -1,    -1,    -1,  1091,    93,    94,
      95,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   107,    -1,    -1,   110,    -1,   112,   113,   114,
    1114,  1115,  1116,  1117,   119,   120,    -1,    -1,    -1,    -1,
    1124,    -1,    -1,    -1,    -1,    -1,  1130,  1131,    -1,  1133,
      -1,   136,   137,    -1,    -1,   140,    -1,   142,   143,   144,
     145,   146,   147,   148,    -1,   150,    -1,   152,   153,   154,
     155,    -1,   157,    -1,   159,    -1,    -1,    -1,    -1,    -1,
      -1,   166,    -1,    -1,   169,    -1,    -1,    -1,    -1,    -1,
      -1,  1175,    -1,    61,    62,    63,    64,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    73,    74,    75,    76,    -1,
      -1,    -1,    -1,    -1,    82,    -1,    -1,    -1,    -1,   204,
     205,    -1,    -1,    -1,    -1,    -1,    -1,   212,    -1,    -1,
     215,   216,    -1,    -1,    -1,    -1,    -1,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
      -1,   236,   237,    -1,    -1,    -1,    -1,   242,   243,   244,
     245,    -1,    -1,    -1,   249,    -1,    -1,   252,   253,    -1,
     255,    -1,    -1,   258,   259,   260,   261,   262,    -1,   264,
     265,    -1,    -1,    -1,    -1,    -1,   271,   272,   273,   274,
      -1,    -1,    -1,    -1,    -1,    -1,   281,   165,    -1,   167,
     285,    -1,    -1,   288,    -1,    -1,   291,   292,   293,    -1,
      -1,    -1,  1296,   298,    -1,  1299,    -1,    -1,    -1,   304,
      -1,    -1,    -1,  1307,   309,   310,    -1,    -1,    -1,    -1,
    1314,    -1,    -1,  1317,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1326,  1327,  1328,  1329,    -1,   215,    -1,    -1,
      -1,    -1,  1336,    -1,    -1,   223,   224,    -1,   226,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   237,
      -1,    -1,    -1,    -1,    -1,   243,   244,    -1,    -1,    -1,
      -1,    -1,     5,     6,     7,     8,     9,    10,    -1,    -1,
      -1,   259,    -1,    -1,   262,    -1,    -1,    -1,    -1,    22,
      23,    -1,    -1,    26,    -1,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,    38,    -1,    -1,    41,   200,
     201,   202,    -1,    -1,    -1,  1409,    -1,    -1,    -1,    -1,
     298,    -1,    -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,
      -1,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    -1,    -1,    79,    -1,    -1,    82,
      -1,    -1,    -1,  1447,    -1,    88,    -1,    -1,    -1,    -1,
      93,    94,    95,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   107,    -1,    -1,   110,    -1,   112,
     113,   114,    -1,    -1,    -1,    -1,   119,   120,    -1,    -1,
      -1,    -1,    -1,  1487,    -1,   286,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   136,   137,    -1,    -1,   140,    -1,   142,
     143,   144,   145,   146,   147,   148,    -1,   150,    -1,   152,
     153,   154,   155,    -1,   157,  1519,   159,    -1,  1522,    -1,
    1524,    -1,    -1,   166,   167,    -1,   169,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   177,    -1,    -1,    -1,  1543,
      -1,    -1,    -1,  1547,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,    -1,  1559,    -1,    -1,   200,   201,
     202,   204,   205,    -1,    -1,    -1,    -1,    -1,    -1,   212,
      -1,    -1,    -1,   216,    -1,    -1,    -1,    -1,    -1,   222,
      -1,    -1,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,    -1,   236,    -1,    -1,    -1,    -1,    -1,   242,
      -1,    -1,   245,    -1,    -1,    -1,   249,    -1,    -1,   252,
     253,    -1,   255,    -1,    -1,   258,    -1,   260,    -1,    -1,
      -1,   264,   265,  1627,  1628,  1629,    -1,  1631,   271,   272,
     273,   274,    -1,    -1,    -1,    -1,    -1,    -1,   281,    -1,
      -1,  1645,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,    -1,    -1,   168,    -1,   200,   201,   202,    -1,
    1664,   304,    -1,    -1,    -1,    -1,   309,   310,    -1,    -1,
      -1,    -1,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,    -1,    -1,    -1,   328,   200,   201,   202,   168,
      -1,    -1,    -1,  1697,    -1,    -1,    -1,    -1,    -1,  1703,
      -1,    -1,    -1,    -1,   248,    -1,    -1,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,    -1,    -1,    -1,
      -1,   200,   201,   202,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      -1,    -1,    18,    19,    -1,    -1,    22,    23,    -1,    -1,
      26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    38,    -1,    -1,    41,    -1,    -1,    44,    45,
      46,    47,    48,    49,    50,    -1,    52,    53,    54,    -1,
      -1,    -1,    -1,    59,    60,    -1,    -1,    63,    64,    65,
      66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      76,    -1,    -1,    79,    -1,  1819,    82,    -1,  1822,    -1,
      -1,    -1,    88,    -1,    -1,    -1,    -1,    93,    94,    95,
      -1,    -1,    -1,    -1,   100,    -1,  1840,    -1,   104,    -1,
      -1,   107,   108,    -1,   110,    -1,   112,   113,   114,    -1,
    1854,    -1,   118,   119,   120,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   128,   129,   130,   131,   132,    -1,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,    -1,   150,   151,   152,   153,   154,   155,
     168,   157,   158,   159,    -1,    -1,    -1,    -1,    -1,   165,
     166,   167,    -1,   169,   170,    -1,    -1,    -1,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,    -1,    -1,
     186,   187,   200,   201,   202,    -1,    -1,    -1,    -1,    -1,
     196,   197,   198,    -1,    -1,    -1,    -1,   203,   204,   205,
      -1,    -1,    -1,    -1,    -1,    -1,   212,    -1,    -1,    -1,
     216,    -1,    -1,    -1,    -1,    -1,   222,    -1,    -1,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,    -1,
     236,    -1,    -1,    -1,    -1,    -1,   242,    -1,    -1,   245,
      -1,    -1,    -1,   249,    -1,    -1,   252,   253,    -1,   255,
      -1,    -1,   258,    -1,   260,    -1,    -1,    -1,   264,   265,
      -1,    -1,   268,    -1,    -1,   271,   272,   273,   274,    -1,
      -1,    -1,    -1,    -1,    -1,   281,    -1,    -1,    -1,   285,
      -1,    -1,    -1,   289,   290,    -1,    -1,   168,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   304,    -1,
      -1,    -1,    -1,   309,   310,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,    -1,    -1,    -1,    -1,   200,
     201,   202,   328,     3,   330,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    -1,    -1,    18,    19,
      -1,    -1,    22,    23,    -1,    -1,    26,    27,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,
      -1,    41,    -1,    -1,    44,    45,    46,    47,    48,    49,
      50,    -1,    52,    53,    54,    -1,    -1,    -1,    -1,    59,
      60,    -1,    -1,    -1,    64,    65,    66,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,    79,
      -1,    -1,    82,    -1,    -1,    -1,    -1,    -1,    88,    -1,
      -1,    -1,    -1,    93,    94,    95,    -1,    -1,    -1,    -1,
     100,    -1,    -1,    -1,   104,    -1,    -1,   107,   108,    -1,
     110,    -1,   112,   113,   114,    -1,    -1,    -1,   118,   119,
     120,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   128,   129,
     130,   131,   132,    -1,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,    -1,
     150,   151,   152,   153,   154,   155,    -1,   157,   158,   159,
      -1,    -1,    -1,    -1,    -1,    -1,   166,   167,    -1,   169,
     170,    -1,   172,   173,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   183,    -1,    -1,   186,   187,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   196,   197,   198,    -1,
      -1,    -1,    -1,   203,   204,   205,    -1,    -1,    -1,    -1,
      -1,    -1,   212,    -1,    -1,    -1,   216,    -1,    -1,    -1,
      -1,    -1,   222,    -1,    -1,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,    -1,   236,    -1,    -1,    -1,
      -1,    -1,   242,    -1,    -1,   245,    -1,    -1,    -1,   249,
      -1,    -1,   252,   253,    -1,   255,    -1,    -1,   258,    -1,
     260,    -1,    -1,    -1,   264,   265,    -1,    -1,    -1,    -1,
      -1,   271,   272,   273,   274,    -1,    -1,    -1,    -1,    -1,
      -1,   281,    -1,    -1,    -1,   285,    -1,    -1,    -1,   289,
     290,    -1,    -1,   168,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   304,    -1,    -1,    -1,    -1,   309,
     310,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,    -1,    -1,    -1,    -1,   200,   201,   202,   328,     3,
     330,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    -1,    -1,    18,    19,    -1,    -1,    22,    23,
      -1,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    38,    -1,    -1,    41,    -1,    -1,
      44,    45,    46,    47,    48,    49,    50,    -1,    52,    53,
      54,    -1,    -1,    -1,    -1,    59,    60,    -1,    -1,    63,
      64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    76,    -1,    -1,    79,    -1,    -1,    82,    -1,
      -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,    93,
      94,    95,    -1,    -1,    -1,    -1,   100,    -1,    -1,    -1,
     104,    -1,    -1,   107,   108,    -1,   110,    -1,   112,   113,
     114,    -1,    -1,    -1,   118,   119,   120,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   128,   129,   130,   131,   132,    -1,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,    -1,   150,   151,   152,   153,
     154,   155,   168,   157,   158,   159,    -1,    -1,    -1,    -1,
      -1,   165,   166,   167,    -1,   169,   170,    -1,    -1,    -1,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
      -1,    -1,   186,   187,   200,   201,   202,    -1,    -1,    -1,
      -1,    -1,   196,   197,   198,    -1,    -1,    -1,    -1,   203,
     204,   205,    -1,    -1,    -1,    -1,    -1,    -1,   212,    -1,
      -1,    -1,   216,    -1,    -1,    -1,    -1,    -1,   222,    -1,
      -1,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,    -1,   236,    -1,    -1,    -1,    -1,    -1,   242,    -1,
      -1,   245,    -1,    -1,    -1,   249,    -1,    -1,   252,   253,
      -1,   255,    -1,    -1,   258,    -1,   260,    -1,    -1,    -1,
     264,   265,    -1,    -1,    -1,    -1,    -1,   271,   272,   273,
     274,    -1,    -1,    -1,    -1,    -1,    -1,   281,    -1,    -1,
      -1,   285,    -1,    -1,    -1,   289,   290,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,    -1,    -1,    -1,
     304,   200,   201,   202,    -1,   309,   310,    -1,    -1,    -1,
      -1,   210,   211,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   328,     3,   330,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
      18,    19,    -1,    -1,    22,    23,    -1,    -1,    26,    27,
      28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      38,    -1,    -1,    41,    -1,    -1,    44,    45,    46,    47,
      48,    49,    50,    -1,    52,    53,    54,    -1,    -1,    -1,
      -1,    59,    60,    -1,    -1,    -1,    64,    65,    66,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,
      -1,    79,    -1,    -1,    82,    -1,    -1,    -1,    -1,    -1,
      88,    -1,    -1,    -1,    -1,    93,    94,    95,    -1,    -1,
      -1,    -1,   100,    -1,    -1,    -1,   104,    -1,    -1,   107,
     108,    -1,   110,    -1,   112,   113,   114,    -1,    -1,    -1,
     118,   119,   120,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     128,   129,   130,   131,   132,    -1,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,    -1,   150,   151,   152,   153,   154,   155,    -1,   157,
     158,   159,    -1,    -1,    -1,    -1,    -1,    -1,   166,   167,
      -1,   169,   170,    -1,    -1,    -1,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,    -1,    -1,   186,   187,
     200,   201,   202,    -1,    -1,    -1,    -1,    -1,   196,   197,
     198,    -1,   200,    -1,    -1,   203,   204,   205,    -1,    -1,
      -1,    -1,    -1,    -1,   212,    -1,    -1,    -1,   216,    -1,
      -1,    -1,    -1,    -1,   222,    -1,    -1,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,    -1,   236,    -1,
      -1,    -1,    -1,    -1,   242,    -1,    -1,   245,    -1,    -1,
      -1,   249,    -1,    -1,   252,   253,    -1,   255,    -1,    -1,
     258,    -1,   260,    -1,    -1,    -1,   264,   265,    -1,    -1,
      -1,    -1,    -1,   271,   272,   273,   274,    -1,    -1,    -1,
      -1,    -1,    -1,   281,    -1,    -1,    -1,   285,    -1,    -1,
      -1,   289,   290,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,    -1,    -1,    -1,   304,   200,   201,   202,
      -1,   309,   310,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     328,     3,   330,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    -1,    18,    19,    -1,    -1,
      22,    23,    -1,    -1,    26,    27,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,    -1,    41,
      -1,    -1,    44,    45,    46,    47,    48,    49,    50,    -1,
      52,    53,    54,    -1,    -1,    -1,    -1,    59,    60,    -1,
      -1,    -1,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    76,    -1,    -1,    79,    -1,    -1,
      82,    -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,
      -1,    93,    94,    95,    -1,    -1,    -1,    -1,   100,    -1,
      -1,    -1,   104,    -1,    -1,   107,   108,    -1,   110,    -1,
     112,   113,   114,    -1,    -1,    -1,   118,   119,   120,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   128,   129,   130,   131,
     132,    -1,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,    -1,   150,   151,
     152,   153,   154,   155,    -1,   157,   158,   159,    -1,    -1,
      -1,    -1,    -1,    -1,   166,   167,    -1,   169,   170,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   186,   187,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   196,   197,   198,    -1,    -1,    -1,
      -1,   203,   204,   205,    -1,    -1,    -1,    -1,    -1,    -1,
     212,    -1,    -1,    -1,   216,    -1,    -1,    -1,    -1,    -1,
     222,    -1,    -1,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,    -1,   236,    -1,    -1,    -1,    -1,    -1,
     242,    -1,    -1,   245,    -1,    -1,    -1,   249,    -1,    -1,
     252,   253,    -1,   255,    -1,    -1,   258,    -1,   260,    -1,
      -1,    -1,   264,   265,    -1,    -1,    -1,    -1,    -1,   271,
     272,   273,   274,    -1,    -1,    -1,    -1,    -1,    -1,   281,
      -1,    -1,    -1,   285,    -1,    -1,    -1,   289,   290,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   304,    -1,    -1,    -1,    -1,   309,   310,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   328,     3,   330,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      -1,    -1,    18,    19,    -1,    -1,    22,    23,    -1,    -1,
      26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    38,    -1,    -1,    41,    -1,    -1,    44,    45,
      46,    47,    48,    49,    50,    -1,    52,    53,    54,    -1,
      -1,    -1,    -1,    59,    60,    -1,    -1,    -1,    64,    65,
      66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      76,    -1,    -1,    79,    -1,    -1,    82,    -1,    -1,    -1,
      -1,    -1,    88,    -1,    -1,    -1,    -1,    93,    94,    95,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   104,    -1,
      -1,   107,   108,    -1,   110,    -1,   112,   113,   114,    -1,
      -1,    -1,   118,   119,   120,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   128,   129,   130,   131,   132,    -1,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,    -1,   150,   151,   152,   153,   154,   155,
      -1,   157,   158,   159,    -1,    -1,    -1,    -1,    -1,    -1,
     166,   167,    -1,   169,    -1,    -1,    -1,    -1,    -1,   175,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     186,   187,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     196,   197,   198,    -1,    -1,    -1,    -1,   203,   204,   205,
      -1,    -1,    -1,    -1,    -1,    -1,   212,    -1,    -1,    -1,
     216,    -1,    -1,    -1,    -1,    -1,   222,    -1,    -1,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,    -1,
     236,    -1,    -1,    -1,    -1,    -1,   242,    -1,    -1,   245,
      -1,    -1,    -1,   249,    -1,    -1,   252,   253,    -1,   255,
      -1,    -1,   258,    -1,   260,    -1,    -1,    -1,   264,   265,
      -1,    -1,    -1,    -1,    -1,   271,   272,   273,   274,    -1,
      -1,    -1,    -1,    -1,    -1,   281,    -1,    -1,    -1,   285,
      -1,    -1,    -1,   289,   290,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   304,    -1,
      -1,    -1,    -1,   309,   310,    -1,    -1,    -1,    -1,    -1,
      -1,   317,    -1,    -1,    -1,    -1,    -1,    -1,   324,    -1,
      -1,    -1,    -1,     3,   330,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    -1,    -1,    18,    19,
      -1,    -1,    22,    23,    -1,    -1,    26,    27,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,
      -1,    41,    -1,    -1,    44,    45,    46,    47,    48,    49,
      50,    -1,    52,    53,    54,    -1,    -1,    -1,    -1,    59,
      60,    -1,    -1,    63,    64,    65,    66,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,    79,
      -1,    -1,    82,    -1,    -1,    -1,    -1,    -1,    88,    -1,
      -1,    -1,    -1,    93,    94,    95,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   104,    -1,    -1,   107,   108,    -1,
     110,    -1,   112,   113,   114,    -1,    -1,    -1,   118,   119,
     120,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   128,   129,
     130,   131,   132,    -1,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,    -1,
     150,   151,   152,   153,   154,   155,    -1,   157,   158,   159,
      -1,    -1,    -1,    -1,    -1,    -1,   166,   167,   168,   169,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   186,   187,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   196,   197,   198,    -1,
      -1,    -1,    -1,   203,   204,   205,    -1,    -1,    -1,    -1,
      -1,    -1,   212,    -1,    -1,    -1,   216,    -1,    -1,    -1,
      -1,    -1,   222,    -1,    -1,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,    -1,   236,    -1,    -1,    -1,
      -1,    -1,   242,    -1,    -1,   245,    -1,    -1,    -1,   249,
      -1,    -1,   252,   253,    -1,   255,    -1,    -1,   258,    -1,
     260,    -1,    -1,    -1,   264,   265,    -1,    -1,    -1,    -1,
      -1,   271,   272,   273,   274,    -1,    -1,    -1,    -1,    -1,
      -1,   281,    -1,    -1,    -1,   285,    -1,    -1,    -1,   289,
     290,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   304,    -1,    -1,    -1,    -1,   309,
     310,    -1,     3,    -1,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    -1,    -1,    18,    19,    -1,
     330,    22,    23,    -1,    -1,    26,    27,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,    -1,
      41,    -1,    -1,    44,    45,    46,    47,    48,    49,    50,
      -1,    52,    53,    54,    -1,    -1,    -1,    -1,    59,    60,
      -1,    -1,    -1,    64,    65,    66,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,    79,    -1,
      -1,    82,    -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,
      -1,    -1,    93,    94,    95,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   104,    -1,    -1,   107,   108,    -1,   110,
      -1,   112,   113,   114,    -1,    -1,    -1,   118,   119,   120,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   128,   129,   130,
     131,   132,    -1,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,    -1,   150,
     151,   152,   153,   154,   155,    -1,   157,   158,   159,    -1,
      -1,    -1,    -1,    -1,    -1,   166,   167,    -1,   169,    -1,
      -1,   172,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   186,   187,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   196,   197,   198,    -1,   200,
      -1,    -1,   203,   204,   205,    -1,    -1,    -1,    -1,    -1,
      -1,   212,    -1,    -1,    -1,   216,    -1,    -1,    -1,    -1,
      -1,   222,    -1,    -1,   225,   226,   227,   228,   229,   230,
     231,   232,   233,   234,    -1,   236,    -1,    -1,    -1,    -1,
      -1,   242,    -1,    -1,   245,    -1,    -1,    -1,   249,    -1,
      -1,   252,   253,    -1,   255,    -1,    -1,   258,    -1,   260,
      -1,    -1,    -1,   264,   265,    -1,    -1,    -1,    -1,    -1,
     271,   272,   273,   274,    -1,    -1,    -1,    -1,    -1,    -1,
     281,    -1,    -1,    -1,   285,    -1,    -1,    -1,   289,   290,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   304,    -1,    -1,    -1,    -1,   309,   310,
      -1,     3,    -1,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    -1,    18,    19,    -1,   330,
      22,    23,    -1,    -1,    26,    27,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,    -1,    41,
      -1,    -1,    44,    45,    46,    47,    48,    49,    50,    -1,
      52,    53,    54,    -1,    -1,    -1,    -1,    59,    60,    -1,
      -1,    -1,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    76,    -1,    -1,    79,    -1,    -1,
      82,    -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,
      -1,    93,    94,    95,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   104,    -1,    -1,   107,   108,    -1,   110,    -1,
     112,   113,   114,    -1,    -1,    -1,   118,   119,   120,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,    -1,   157,   158,   159,    -1,    -1,
      -1,    -1,    -1,    -1,   166,   167,    -1,   169,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   186,   187,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   196,   197,   198,    -1,    -1,    -1,
      -1,   203,   204,   205,    -1,    -1,    -1,    -1,    -1,    -1,
     212,    -1,    -1,    -1,   216,    -1,    -1,    -1,    -1,    -1,
     222,    -1,    -1,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,    -1,   236,    -1,    -1,    -1,    -1,    -1,
     242,    -1,    -1,   245,    -1,    -1,    -1,   249,    -1,    -1,
     252,   253,    -1,   255,    -1,    -1,   258,    -1,   260,    -1,
      -1,    -1,   264,   265,    -1,    -1,    -1,    -1,    -1,   271,
     272,   273,   274,    -1,    -1,    -1,    -1,    -1,    -1,   281,
      -1,    -1,    -1,   285,    -1,    -1,    -1,   289,   290,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   304,    -1,    -1,    -1,    -1,   309,   310,    -1,
       3,    -1,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,    -1,    18,    19,    -1,   330,    22,
      23,    -1,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    38,    -1,    -1,    41,    -1,
      -1,    44,    45,    46,    47,    48,    49,    50,    -1,    52,
      53,    54,    -1,    -1,    -1,    -1,    59,    60,    -1,    -1,
      -1,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    -1,    -1,    79,    -1,    -1,    82,
      -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,
      93,    94,    95,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   104,    -1,    -1,   107,   108,    -1,   110,    -1,   112,
     113,   114,    -1,    -1,    -1,   118,   119,   120,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   128,   129,   130,   131,   132,
      -1,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,    -1,   150,   151,   152,
     153,   154,   155,    -1,   157,   158,   159,    -1,    -1,    -1,
      -1,    -1,    -1,   166,   167,    -1,   169,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   186,   187,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   196,   197,   198,    -1,    -1,    -1,    -1,
     203,   204,   205,    -1,    -1,    -1,    -1,    -1,    -1,   212,
      -1,    -1,    -1,   216,    -1,    -1,    -1,    -1,    -1,   222,
      -1,    -1,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,    -1,   236,    -1,    -1,    -1,    -1,    -1,   242,
      -1,    -1,   245,    -1,    -1,    -1,   249,    -1,    -1,   252,
     253,    -1,   255,    -1,    -1,   258,    -1,   260,    -1,    -1,
      -1,   264,   265,    -1,    -1,    -1,    -1,    -1,   271,   272,
     273,   274,    -1,    -1,    -1,    -1,    -1,    -1,   281,    -1,
      -1,    -1,   285,    -1,    -1,    -1,   289,   290,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   304,    -1,    -1,    -1,    -1,   309,   310,    -1,    -1,
      -1,    -1,    -1,    -1,   317,    -1,    -1,    -1,    -1,    -1,
      -1,   324,    -1,    -1,    -1,    -1,     3,   330,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      -1,    18,    19,    -1,    -1,    22,    23,    -1,    -1,    26,
      27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    38,    -1,    -1,    41,    -1,    -1,    44,    45,    46,
      47,    48,    49,    50,    -1,    52,    53,    54,    -1,    -1,
      -1,    -1,    59,    60,    -1,    -1,    -1,    64,    65,    66,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,
      -1,    -1,    79,    -1,    -1,    82,    -1,    -1,    -1,    -1,
      -1,    88,    -1,    -1,    -1,    -1,    93,    94,    95,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   104,    -1,    -1,
     107,   108,    -1,   110,    -1,   112,   113,   114,    -1,    -1,
      -1,   118,   119,   120,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   128,   129,   130,   131,   132,    -1,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,    -1,   150,   151,   152,   153,   154,   155,    -1,
     157,   158,   159,    -1,    -1,    -1,    -1,    -1,    -1,   166,
     167,    -1,   169,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   186,
     187,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   196,
     197,   198,    -1,    -1,    -1,    -1,   203,   204,   205,    -1,
      -1,    -1,    -1,    -1,    -1,   212,    -1,    -1,    -1,   216,
      -1,    -1,    -1,    -1,    -1,   222,    -1,    -1,   225,   226,
     227,   228,   229,   230,   231,   232,   233,   234,    -1,   236,
      -1,    -1,    -1,    -1,    -1,   242,    -1,    -1,   245,    -1,
      -1,    -1,   249,    -1,    -1,   252,   253,    -1,   255,    -1,
      -1,   258,    -1,   260,    -1,    -1,    -1,   264,   265,    -1,
      -1,    -1,    -1,    -1,   271,   272,   273,   274,    -1,    -1,
      -1,    -1,    -1,    -1,   281,    -1,    -1,    -1,   285,    -1,
      -1,    -1,   289,   290,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   304,    -1,    -1,
      -1,    -1,   309,   310,    -1,    -1,    -1,    -1,    -1,    -1,
     317,    -1,    -1,    -1,    -1,    -1,    -1,   324,    -1,    -1,
      -1,    -1,     3,   330,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    -1,    -1,    18,    19,    -1,
      -1,    22,    23,    -1,    -1,    26,    27,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,    -1,
      41,    -1,    -1,    44,    45,    46,    47,    48,    49,    50,
      -1,    52,    53,    54,    -1,    -1,    -1,    -1,    59,    60,
      -1,    -1,    -1,    64,    65,    66,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,    79,    -1,
      -1,    82,    -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,
      -1,    -1,    93,    94,    95,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   104,    -1,    -1,   107,   108,    -1,   110,
      -1,   112,   113,   114,    -1,    -1,    -1,   118,   119,   120,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   128,   129,   130,
     131,   132,    -1,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,    -1,   150,
     151,   152,   153,   154,   155,    -1,   157,   158,   159,    -1,
      -1,    -1,    -1,    -1,    -1,   166,   167,    -1,   169,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   186,   187,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   196,   197,   198,    -1,    -1,
      -1,    -1,   203,   204,   205,    -1,    -1,    -1,    -1,    -1,
      -1,   212,    -1,    -1,    -1,   216,    -1,    -1,    -1,    -1,
      -1,   222,    -1,    -1,   225,   226,   227,   228,   229,   230,
     231,   232,   233,   234,    -1,   236,    -1,    -1,    -1,    -1,
      -1,   242,    -1,    -1,   245,    -1,    -1,    -1,   249,    -1,
      -1,   252,   253,    -1,   255,    -1,    -1,   258,    -1,   260,
      -1,    -1,    -1,   264,   265,    -1,    -1,    -1,    -1,    -1,
     271,   272,   273,   274,    -1,    -1,    -1,    -1,    -1,    -1,
     281,    -1,    -1,    -1,   285,   286,    -1,    -1,   289,   290,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   304,    -1,    -1,    -1,    -1,   309,   310,
      -1,     3,    -1,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    -1,    18,    19,    -1,   330,
      22,    23,    -1,    -1,    26,    27,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,    -1,    41,
      -1,    -1,    44,    45,    46,    47,    48,    49,    50,    -1,
      52,    53,    54,    -1,    -1,    -1,    -1,    59,    60,    -1,
      -1,    -1,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    76,    -1,    -1,    79,    -1,    -1,
      82,    -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,
      -1,    93,    94,    95,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   104,    -1,    -1,   107,   108,    -1,   110,    -1,
     112,   113,   114,    -1,    -1,    -1,   118,   119,   120,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   128,   129,   130,   131,
     132,    -1,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,    -1,   150,   151,
     152,   153,   154,   155,    -1,   157,   158,   159,    -1,    -1,
      -1,    -1,    -1,    -1,   166,   167,   168,   169,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   186,   187,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   196,   197,   198,    -1,    -1,    -1,
      -1,   203,   204,   205,    -1,    -1,    -1,    -1,    -1,    -1,
     212,    -1,    -1,    -1,   216,    -1,    -1,    -1,    -1,    -1,
     222,    -1,    -1,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,    -1,   236,    -1,    -1,    -1,    -1,    -1,
     242,    -1,    -1,   245,    -1,    -1,    -1,   249,    -1,    -1,
     252,   253,    -1,   255,    -1,    -1,   258,    -1,   260,    -1,
      -1,    -1,   264,   265,    -1,    -1,    -1,    -1,    -1,   271,
     272,   273,   274,    -1,    -1,    -1,    -1,    -1,    -1,   281,
      -1,    -1,    -1,   285,    -1,    -1,    -1,   289,   290,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   304,    -1,    -1,    -1,    -1,   309,   310,    -1,
       3,    -1,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,    -1,    18,    19,    -1,   330,    22,
      23,    -1,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    38,    -1,    -1,    41,    -1,
      -1,    44,    45,    46,    47,    48,    49,    50,    -1,    52,
      53,    54,    -1,    -1,    -1,    -1,    59,    60,    -1,    -1,
      63,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    -1,    -1,    79,    -1,    -1,    82,
      -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,
      93,    94,    95,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   104,    -1,    -1,   107,   108,    -1,   110,    -1,   112,
     113,   114,    -1,    -1,    -1,   118,   119,   120,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   128,   129,   130,   131,   132,
      -1,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,    -1,   150,   151,   152,
     153,   154,   155,    -1,   157,   158,   159,    -1,    -1,    -1,
      -1,    -1,    -1,   166,   167,    -1,   169,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   186,   187,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   196,   197,   198,    -1,    -1,    -1,    -1,
     203,   204,   205,    -1,    -1,    -1,    -1,    -1,    -1,   212,
      -1,    -1,    -1,   216,    -1,    -1,    -1,    -1,    -1,   222,
      -1,    -1,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,    -1,   236,    -1,    -1,    -1,    -1,    -1,   242,
      -1,    -1,   245,    -1,    -1,    -1,   249,    -1,    -1,   252,
     253,    -1,   255,    -1,    -1,   258,    -1,   260,    -1,    -1,
      -1,   264,   265,    -1,    -1,    -1,    -1,    -1,   271,   272,
     273,   274,    -1,    -1,    -1,    -1,    -1,    -1,   281,    -1,
      -1,    -1,   285,    -1,    -1,    -1,   289,   290,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   304,    -1,    -1,    -1,    -1,   309,   310,    -1,     3,
      -1,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    -1,    -1,    18,    19,    -1,   330,    22,    23,
      -1,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    38,    -1,    -1,    41,    -1,    -1,
      44,    45,    46,    47,    48,    49,    50,    -1,    52,    53,
      54,    -1,    -1,    -1,    -1,    59,    60,    -1,    -1,    -1,
      64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    76,    -1,    -1,    79,    -1,    -1,    82,    -1,
      -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,    93,
      94,    95,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     104,    -1,    -1,   107,   108,    -1,   110,    -1,   112,   113,
     114,    -1,    -1,    -1,   118,   119,   120,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   128,   129,   130,   131,   132,    -1,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,    -1,   150,   151,   152,   153,
     154,   155,    -1,   157,   158,   159,    -1,    -1,    -1,    -1,
      -1,    -1,   166,   167,    -1,   169,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   186,   187,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   196,   197,   198,    -1,    -1,    -1,    -1,   203,
     204,   205,    -1,    -1,    -1,    -1,    -1,    -1,   212,    -1,
      -1,    -1,   216,    -1,    -1,    -1,    -1,    -1,   222,    -1,
      -1,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,    -1,    -1,    -1,    -1,    -1,   242,    -1,
      -1,   245,    -1,    -1,    -1,   249,    -1,    -1,   252,   253,
      -1,   255,    -1,    -1,   258,    -1,   260,    -1,    -1,    -1,
     264,   265,    -1,    -1,    -1,    -1,    -1,   271,   272,   273,
     274,    -1,    -1,    -1,    -1,    -1,    -1,   281,    -1,    -1,
      -1,   285,    -1,    -1,    -1,   289,   290,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     304,    -1,    -1,    -1,    -1,   309,   310,    -1,     3,    -1,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    -1,    -1,    18,    19,    -1,   330,    22,    23,    -1,
      -1,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    38,    -1,    -1,    41,    -1,    -1,    44,
      45,    46,    47,    48,    49,    50,    -1,    52,    53,    54,
      -1,    -1,    -1,    -1,    59,    60,    -1,    -1,    -1,    64,
      65,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    76,    -1,    -1,    79,    -1,    -1,    82,    -1,    -1,
      -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,    93,    94,
      95,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   104,
      -1,    -1,   107,   108,    -1,   110,    -1,   112,   113,   114,
      -1,    -1,    -1,   118,   119,   120,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   128,   129,   130,   131,   132,    -1,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,    -1,   150,   151,   152,   153,   154,
     155,    -1,   157,   158,   159,    -1,    -1,    -1,    -1,    -1,
      -1,   166,   167,    -1,   169,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   186,   187,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   196,   197,   198,    -1,    -1,    -1,    -1,   203,   204,
     205,    -1,    -1,    -1,    -1,    -1,    -1,   212,    -1,    -1,
      -1,   216,    -1,    -1,    -1,    -1,    -1,   222,    -1,    -1,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
      -1,   236,    -1,    -1,    -1,    -1,    -1,   242,    -1,    -1,
     245,    -1,    -1,    -1,   249,    -1,    -1,   252,   253,    -1,
     255,    -1,    -1,   258,    -1,   260,    -1,    -1,    -1,   264,
     265,    -1,    -1,    -1,    -1,    -1,   271,   272,   273,   274,
      -1,    -1,    -1,    -1,    -1,    -1,   281,    -1,    -1,    -1,
     285,   286,    -1,    -1,   289,   290,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   304,
      -1,    -1,    -1,    -1,   309,   310,    -1,     3,    -1,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      -1,    -1,    18,    19,    -1,   330,    22,    23,    -1,    -1,
      26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    38,    -1,    -1,    41,    -1,    -1,    44,    45,
      46,    47,    48,    49,    50,    -1,    52,    53,    54,    -1,
      -1,    -1,    -1,    59,    60,    -1,    -1,    -1,    64,    65,
      66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      76,    -1,    -1,    79,    -1,    -1,    82,    -1,    -1,    -1,
      -1,    -1,    88,    -1,    -1,    -1,    -1,    93,    94,    95,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   104,    -1,
      -1,   107,   108,    -1,   110,    -1,   112,   113,   114,    -1,
      -1,    -1,   118,   119,   120,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,    -1,   150,   151,   152,   153,   154,   155,
      -1,   157,   158,   159,    -1,    -1,    -1,    -1,    -1,    -1,
     166,   167,    -1,   169,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     186,   187,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     196,   197,   198,    -1,    -1,    -1,    -1,   203,   204,   205,
      -1,    -1,    -1,    -1,    -1,    -1,   212,    -1,    -1,    -1,
     216,    -1,    -1,    -1,    -1,    -1,   222,    -1,    -1,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,    -1,
     236,    -1,    -1,    -1,    -1,    -1,   242,    -1,    -1,   245,
      -1,    -1,    -1,   249,    -1,    -1,   252,   253,    -1,   255,
      -1,    -1,   258,    -1,   260,    -1,    -1,    -1,   264,   265,
      -1,    -1,    -1,    -1,    -1,   271,   272,   273,   274,    -1,
      -1,    -1,    -1,    -1,    -1,   281,    -1,    -1,    -1,   285,
      -1,    -1,    -1,   289,   290,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   304,    -1,
      -1,    -1,    -1,   309,   310,    -1,     3,    -1,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      -1,    18,    19,    -1,   330,    22,    23,    -1,    -1,    26,
      27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    38,    -1,    -1,    41,    -1,    -1,    44,    45,    46,
      47,    48,    49,    50,    -1,    52,    53,    54,    -1,    -1,
      -1,    -1,    59,    60,    -1,    -1,    -1,    64,    65,    66,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,
      -1,    -1,    79,    -1,    -1,    82,    -1,    -1,    -1,    -1,
      -1,    88,    -1,    -1,    -1,    -1,    93,    94,    95,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   104,    -1,    -1,
     107,   108,    -1,   110,    -1,   112,   113,   114,    -1,    -1,
      -1,   118,   119,   120,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   128,   129,   130,   131,   132,    -1,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,    -1,   150,   151,   152,   153,   154,   155,    -1,
     157,   158,   159,    -1,    -1,    -1,    -1,    -1,    -1,   166,
     167,    -1,   169,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   186,
     187,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   196,
     197,   198,    -1,    -1,    -1,    -1,   203,   204,   205,    -1,
      -1,    -1,    -1,    -1,    -1,   212,    -1,    -1,    -1,   216,
      -1,    -1,    -1,    -1,    -1,   222,    -1,    -1,   225,   226,
     227,   228,   229,   230,   231,   232,   233,   234,    -1,   236,
      -1,    -1,    -1,    -1,    -1,   242,    -1,    -1,   245,    -1,
      -1,    -1,   249,    -1,    -1,   252,   253,    -1,   255,    -1,
      -1,   258,    -1,   260,    -1,    -1,    -1,   264,   265,    -1,
      -1,    -1,    -1,    -1,   271,   272,   273,   274,    -1,    -1,
      -1,    -1,    -1,    -1,   281,    -1,    -1,    -1,   285,    -1,
      -1,    -1,   289,   290,    -1,    -1,    -1,    -1,     5,     6,
       7,     8,     9,    10,    -1,    -1,    -1,   304,    -1,    -1,
      -1,    -1,   309,   310,    -1,    22,    23,    -1,    -1,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    38,    -1,   330,    41,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    60,    61,    62,    63,    64,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    75,    76,
      -1,    -1,    79,    -1,    -1,    82,    -1,    -1,    -1,    -1,
      -1,    88,    -1,    -1,    -1,    -1,    93,    94,    95,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     107,    -1,    -1,   110,    -1,   112,   113,   114,    -1,    -1,
      -1,    -1,   119,   120,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   136,
     137,    -1,    -1,   140,    -1,   142,   143,   144,   145,   146,
     147,   148,    -1,   150,    -1,   152,   153,   154,   155,    -1,
     157,    -1,   159,    -1,    -1,    -1,    -1,    -1,    -1,   166,
      -1,    -1,   169,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   204,   205,    -1,
      -1,    -1,    -1,    -1,    -1,   212,    -1,    -1,   215,   216,
      -1,    -1,    -1,    -1,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   232,   233,   234,    -1,   236,
     237,    -1,    -1,    -1,    -1,   242,   243,   244,   245,    -1,
      -1,    -1,   249,    -1,    -1,   252,   253,    -1,   255,    -1,
      -1,   258,   259,   260,   261,   262,    -1,   264,   265,    -1,
      -1,    -1,    -1,    -1,   271,   272,   273,   274,    -1,    -1,
      -1,    -1,    -1,    -1,   281,    -1,    -1,    -1,   285,    -1,
      -1,    -1,    -1,    -1,   291,    -1,    -1,    -1,    -1,   296,
      -1,   298,    -1,    -1,    -1,    -1,    -1,   304,    -1,    -1,
      -1,    -1,   309,   310,     5,     6,     7,     8,     9,    10,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    22,    23,    -1,    -1,    26,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,    -1,
      41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,
      61,    62,    63,    64,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    73,    74,    75,    76,    -1,    -1,    79,    -1,
      -1,    82,    -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,
      -1,    -1,    93,    94,    95,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   107,    -1,    -1,   110,
      -1,   112,   113,   114,    -1,    -1,    -1,    -1,   119,   120,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   136,   137,    -1,    -1,   140,
      -1,   142,   143,   144,   145,   146,   147,   148,    -1,   150,
      -1,   152,   153,   154,   155,    -1,   157,    -1,   159,    -1,
      -1,    -1,    -1,    -1,    -1,   166,    -1,    -1,   169,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   204,   205,    -1,    -1,    -1,    -1,    -1,
      -1,   212,    -1,    -1,   215,   216,    -1,    -1,    -1,    -1,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   230,
     231,   232,   233,   234,    -1,   236,   237,    -1,    -1,    -1,
      -1,   242,   243,   244,   245,    -1,    -1,    -1,   249,    -1,
      -1,   252,   253,    -1,   255,    -1,    -1,   258,   259,   260,
     261,   262,    -1,   264,   265,    -1,    -1,    -1,    -1,    -1,
     271,   272,   273,   274,    -1,    -1,    -1,    -1,    -1,    -1,
     281,    -1,    -1,    -1,   285,    -1,    -1,    -1,    -1,    -1,
     291,    -1,    -1,    -1,    -1,   296,    -1,   298,    -1,    -1,
      -1,    -1,    -1,   304,    -1,    -1,    -1,    -1,   309,   310,
       5,     6,     7,     8,     9,    10,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    22,    23,    -1,
      -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    38,    -1,    -1,    41,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    60,    61,    62,    63,    64,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,    74,
      75,    76,    -1,    -1,    79,    -1,    -1,    82,    -1,    -1,
      -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,    93,    94,
      95,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   107,    -1,    -1,   110,    -1,   112,   113,   114,
      -1,    -1,    -1,    -1,   119,   120,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   136,   137,    -1,    -1,   140,    -1,   142,   143,   144,
     145,   146,   147,   148,    -1,   150,    -1,   152,   153,   154,
     155,    -1,   157,    -1,   159,    -1,    -1,    -1,    -1,    -1,
      -1,   166,    -1,    -1,   169,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   204,
     205,    -1,    -1,    -1,    -1,    -1,    -1,   212,    -1,    -1,
     215,   216,    -1,    -1,    -1,    -1,    -1,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
      -1,   236,   237,    -1,    -1,    -1,    -1,   242,   243,   244,
     245,    -1,    -1,    -1,   249,    -1,    -1,   252,   253,    -1,
     255,    -1,    -1,   258,   259,   260,   261,   262,    -1,   264,
     265,    -1,    -1,    -1,    -1,    -1,   271,   272,   273,   274,
      -1,    -1,    -1,    -1,    -1,    -1,   281,    -1,    -1,    -1,
     285,    -1,    -1,    -1,    -1,    -1,   291,    -1,   293,    -1,
      -1,    -1,    -1,   298,    -1,    -1,    -1,    -1,    -1,   304,
      -1,    -1,    -1,    -1,   309,   310,     5,     6,     7,     8,
       9,    10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    22,    23,    -1,    -1,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,
      -1,    -1,    41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    60,    61,    62,    63,    64,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    73,    74,    75,    76,    -1,    -1,
      79,    -1,    -1,    82,    -1,    -1,    -1,    -1,    -1,    88,
      -1,    -1,    -1,    -1,    93,    94,    95,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   107,    -1,
      -1,   110,    -1,   112,   113,   114,    -1,    -1,    -1,    -1,
     119,   120,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   136,   137,    -1,
      -1,   140,    -1,   142,   143,   144,   145,   146,   147,   148,
      -1,   150,    -1,   152,   153,   154,   155,    -1,   157,    -1,
     159,    -1,    -1,    -1,    -1,    -1,    -1,   166,    -1,    -1,
     169,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   204,   205,    -1,    -1,    -1,
      -1,    -1,    -1,   212,    -1,    -1,   215,   216,    -1,    -1,
      -1,    -1,    -1,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,    -1,   236,   237,    -1,
      -1,    -1,    -1,   242,   243,   244,   245,    -1,    -1,    -1,
     249,    -1,    -1,   252,   253,    -1,   255,    -1,    -1,   258,
     259,   260,   261,   262,    -1,   264,   265,    -1,    -1,    -1,
      -1,    -1,   271,   272,   273,   274,     5,     6,     7,     8,
       9,    10,   281,    -1,    -1,    -1,   285,    -1,    -1,    -1,
      -1,    -1,   291,    22,    23,    -1,    -1,    26,   297,   298,
      -1,    -1,    -1,    -1,    -1,   304,    -1,    -1,    -1,    38,
     309,   310,    41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    60,    61,    62,    63,    64,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    73,    74,    75,    76,    -1,    -1,
      79,    -1,    -1,    82,    -1,    -1,    -1,    -1,    -1,    88,
      -1,    -1,    -1,    -1,    93,    94,    95,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   107,    -1,
      -1,   110,    -1,   112,   113,   114,    -1,    -1,    -1,    -1,
     119,   120,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   136,   137,    -1,
      -1,   140,    -1,   142,   143,   144,   145,   146,   147,   148,
      -1,   150,    -1,   152,   153,   154,   155,    -1,   157,    -1,
     159,    -1,    -1,    -1,    -1,    -1,    -1,   166,    -1,    -1,
     169,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   204,   205,    -1,    -1,    -1,
      -1,    -1,    -1,   212,    -1,    -1,   215,   216,    -1,    -1,
      -1,    -1,    -1,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,    -1,   236,   237,    -1,
      -1,    -1,    -1,   242,   243,   244,   245,    -1,    -1,    -1,
     249,    -1,    -1,   252,   253,    -1,   255,    -1,    -1,   258,
     259,   260,   261,   262,    -1,   264,   265,    -1,    -1,    -1,
      -1,    -1,   271,   272,   273,   274,     5,     6,     7,     8,
       9,    10,   281,    -1,    -1,    -1,   285,    -1,    -1,    -1,
      -1,    -1,   291,    22,    23,    -1,    -1,    26,    -1,   298,
      -1,    -1,    -1,    -1,    -1,   304,    -1,    -1,    -1,    38,
     309,   310,    41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    60,    61,    62,    63,    64,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    73,    74,    75,    76,    -1,    -1,
      79,    -1,    -1,    82,    -1,    -1,    -1,    -1,    -1,    88,
      -1,    -1,    -1,    -1,    93,    94,    95,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   107,    -1,
      -1,   110,    -1,   112,   113,   114,    -1,    -1,    -1,    -1,
     119,   120,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   136,   137,    -1,
      -1,   140,    -1,   142,   143,   144,   145,   146,   147,   148,
      -1,   150,    -1,   152,   153,   154,   155,    -1,   157,    -1,
     159,    -1,    -1,    -1,    -1,    -1,    -1,   166,    -1,    -1,
     169,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   204,   205,    -1,    -1,    -1,
      -1,    -1,    -1,   212,    -1,    -1,    -1,   216,    -1,    -1,
      -1,    -1,    -1,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,    -1,   236,    -1,    -1,
      -1,    -1,    -1,   242,   243,   244,   245,    -1,    -1,    -1,
     249,    -1,    -1,   252,   253,    -1,   255,    -1,    -1,   258,
     259,   260,   261,    -1,    -1,   264,   265,    -1,    -1,    -1,
      -1,    -1,   271,   272,   273,   274,    -1,    -1,    -1,    -1,
      -1,    -1,   281,    -1,    -1,    -1,   285,    -1,    -1,    -1,
      -1,    -1,   291,    -1,    -1,    -1,    -1,   296,    -1,   298,
      -1,    -1,    -1,    -1,    -1,   304,    -1,    -1,    -1,    -1,
     309,   310,     5,     6,     7,     8,     9,    10,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    22,
      23,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    38,    -1,    -1,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,    62,
      63,    64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      73,    74,    75,    76,    -1,    -1,    79,    -1,    -1,    82,
      -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,
      93,    94,    95,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   107,    -1,    -1,   110,    -1,   112,
     113,   114,    -1,    -1,    -1,    -1,   119,   120,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   136,   137,    -1,    -1,   140,    -1,   142,
     143,   144,   145,   146,   147,   148,    -1,   150,    -1,   152,
     153,   154,   155,    -1,   157,    -1,   159,    -1,    -1,    -1,
      -1,    -1,    -1,   166,    -1,    -1,   169,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   204,   205,    -1,    -1,    -1,    -1,    -1,    -1,   212,
      -1,    -1,    -1,   216,    -1,    -1,    -1,    -1,    -1,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,    -1,   236,    -1,    -1,    -1,    -1,    -1,   242,
     243,   244,   245,    -1,    -1,    -1,   249,    -1,    -1,   252,
     253,    -1,   255,    -1,    -1,   258,   259,   260,   261,    -1,
      -1,   264,   265,    -1,    -1,    -1,    -1,    -1,   271,   272,
     273,   274,     5,     6,     7,     8,     9,    10,   281,    -1,
      -1,    -1,   285,    -1,    17,    -1,    -1,    -1,   291,    22,
      23,    -1,    -1,    26,   297,   298,    -1,    -1,    -1,    -1,
      -1,   304,    -1,    -1,    -1,    38,   309,   310,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    55,    -1,    -1,    -1,    -1,    60,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    -1,    -1,    79,    -1,    -1,    82,
      -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,
      93,    94,    95,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   107,    -1,    -1,   110,    -1,   112,
     113,   114,    -1,    -1,    -1,    -1,   119,   120,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   136,   137,    -1,    -1,   140,    -1,   142,
     143,   144,   145,   146,   147,   148,    -1,   150,    -1,   152,
     153,   154,   155,    -1,   157,    -1,   159,    -1,    -1,    -1,
      -1,    -1,    -1,   166,    -1,    -1,   169,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   204,   205,   206,   207,   208,   209,    -1,    -1,   212,
      -1,    -1,    -1,   216,    -1,    -1,    -1,    -1,    -1,   222,
      -1,    -1,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,    -1,   236,    -1,    -1,    -1,    -1,    -1,   242,
      -1,    -1,   245,    -1,    -1,    -1,   249,    -1,    -1,   252,
     253,    -1,   255,    -1,    -1,   258,    -1,   260,    -1,    -1,
      -1,   264,   265,    -1,    -1,    -1,    -1,    -1,   271,   272,
     273,   274,     5,     6,     7,     8,     9,    10,   281,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    22,
      23,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   304,    -1,    -1,    -1,    38,   309,   310,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,
      -1,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    -1,    -1,    79,    -1,    -1,    82,
      -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,
      93,    94,    95,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   107,    -1,    -1,   110,    -1,   112,
     113,   114,    -1,    -1,    -1,    -1,   119,   120,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   136,   137,    -1,    -1,   140,    -1,   142,
     143,   144,   145,   146,   147,   148,    -1,   150,    -1,   152,
     153,   154,   155,    -1,   157,    -1,   159,    -1,    -1,    -1,
      -1,    -1,    -1,   166,    -1,    -1,   169,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   200,    -1,    -1,
      -1,   204,   205,    -1,    -1,    -1,    -1,    -1,    -1,   212,
      -1,    -1,    -1,   216,    -1,    -1,    -1,    -1,    -1,   222,
      -1,    -1,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,    -1,   236,    -1,    -1,    -1,    -1,    -1,   242,
      -1,    -1,   245,    -1,    -1,    -1,   249,    -1,    -1,   252,
     253,    -1,   255,    -1,    -1,   258,    -1,   260,    -1,    -1,
      -1,   264,   265,    -1,    -1,    -1,    -1,    -1,   271,   272,
     273,   274,     5,     6,     7,     8,     9,    10,   281,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    22,
      23,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   304,    -1,    -1,    -1,    38,   309,   310,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,
      -1,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    -1,    -1,    79,    -1,    -1,    82,
      -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,
      93,    94,    95,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   107,    -1,    -1,   110,    -1,   112,
     113,   114,    -1,    -1,    -1,    -1,   119,   120,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   136,   137,    -1,    -1,   140,    -1,   142,
     143,   144,   145,   146,   147,   148,    -1,   150,    -1,   152,
     153,   154,   155,    -1,   157,    -1,   159,    -1,    -1,    -1,
      -1,    -1,    -1,   166,    -1,    -1,   169,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   200,    -1,    -1,
      -1,   204,   205,    -1,    -1,    -1,    -1,    -1,    -1,   212,
      -1,    -1,    -1,   216,    -1,    -1,    -1,    -1,    -1,   222,
      -1,    -1,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,    -1,   236,    -1,    -1,    -1,    -1,    -1,   242,
      -1,    -1,   245,    -1,    -1,    -1,   249,    -1,    -1,   252,
     253,    -1,   255,    -1,    -1,   258,    -1,   260,    -1,    -1,
      -1,   264,   265,    -1,    -1,    -1,    -1,    -1,   271,   272,
     273,   274,     5,     6,     7,     8,     9,    10,   281,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    22,
      23,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   304,    -1,    -1,    -1,    38,   309,   310,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,
      -1,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    -1,    -1,    79,    -1,    -1,    82,
      -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,
      93,    94,    95,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   107,    -1,    -1,   110,    -1,   112,
     113,   114,    -1,    -1,    -1,    -1,   119,   120,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   136,   137,    -1,    -1,   140,    -1,   142,
     143,   144,   145,   146,   147,   148,    -1,   150,    -1,   152,
     153,   154,   155,    -1,   157,    -1,   159,    -1,    -1,    -1,
      -1,    -1,    -1,   166,    -1,    -1,   169,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   204,   205,    -1,    -1,    -1,    -1,    -1,    -1,   212,
      -1,    -1,    -1,   216,    -1,    -1,    -1,    -1,    -1,   222,
      -1,    -1,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,    -1,   236,    -1,    -1,    -1,    -1,    -1,   242,
      -1,    -1,   245,    -1,    -1,    -1,   249,    -1,    -1,   252,
     253,    -1,   255,    -1,    -1,   258,    -1,   260,    -1,    -1,
      -1,   264,   265,    -1,    -1,    -1,    -1,    -1,   271,   272,
     273,   274,     5,     6,     7,     8,     9,    10,   281,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    22,
      23,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   304,    -1,    -1,    -1,    38,   309,   310,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,
      53,    54,    -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    -1,    -1,    79,    -1,    -1,    82,
      -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,
      93,    94,    95,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   107,    -1,    -1,   110,    -1,   112,
     113,   114,    -1,    -1,    -1,    -1,   119,   120,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   136,   137,    -1,    -1,   140,    -1,   142,
     143,   144,   145,   146,   147,   148,    -1,   150,    -1,   152,
     153,   154,   155,    -1,   157,    -1,   159,    -1,    -1,    -1,
      -1,    -1,    -1,   166,    -1,    -1,   169,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   204,   205,    -1,    -1,    -1,    -1,    -1,    -1,   212,
      -1,    -1,    -1,   216,    -1,    -1,    -1,    -1,    -1,   222,
      -1,    -1,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,    -1,   236,    -1,    -1,    -1,    -1,    -1,   242,
      -1,    -1,   245,    -1,    -1,    -1,   249,    -1,    -1,   252,
     253,    -1,   255,    -1,    -1,   258,    -1,   260,    -1,    -1,
      -1,   264,   265,    -1,    -1,    -1,    -1,    -1,   271,   272,
     273,   274,     5,     6,     7,     8,     9,    10,   281,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    22,
      23,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   304,    -1,    -1,    -1,    38,   309,   310,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,
      -1,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    -1,    -1,    79,    -1,    -1,    82,
      -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,
      93,    94,    95,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   107,    -1,    -1,   110,    -1,   112,
     113,   114,    -1,    -1,    -1,    -1,   119,   120,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   136,   137,    -1,    -1,   140,    -1,   142,
     143,   144,   145,   146,   147,   148,    -1,   150,    -1,   152,
     153,   154,   155,    -1,   157,    -1,   159,    -1,    -1,    -1,
      -1,    -1,    -1,   166,    -1,    -1,   169,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   204,   205,    -1,    -1,    -1,    -1,    -1,    -1,   212,
      -1,    -1,    -1,   216,    -1,    -1,    -1,    -1,    -1,   222,
      -1,    -1,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,    -1,   236,    -1,    -1,    -1,    -1,    -1,   242,
      -1,    -1,   245,    -1,    -1,    -1,   249,    -1,    -1,   252,
     253,    -1,   255,    -1,    -1,   258,    -1,   260,    -1,    -1,
      -1,   264,   265,    -1,    -1,    -1,    -1,    -1,   271,   272,
     273,   274,     5,     6,     7,     8,     9,    10,   281,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    22,
      23,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   304,    -1,    -1,    -1,    38,   309,   310,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,
      63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    -1,    -1,    79,    -1,    -1,    82,
      -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,
      93,    94,    95,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   107,    -1,    -1,   110,    -1,   112,
     113,   114,    -1,    -1,    -1,    -1,   119,   120,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   136,   137,    -1,    -1,   140,    -1,   142,
     143,   144,   145,   146,   147,   148,    -1,   150,    -1,   152,
     153,   154,   155,    -1,   157,    -1,   159,    -1,    -1,    -1,
      -1,    -1,    -1,   166,   167,    -1,   169,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   204,   205,    -1,    -1,    -1,    -1,    -1,    -1,   212,
      -1,    -1,    -1,   216,    -1,    -1,    -1,    -1,    -1,   222,
      -1,    -1,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,    -1,   236,    -1,    -1,    -1,    -1,    -1,   242,
      -1,    -1,   245,    -1,    -1,    -1,   249,    -1,    -1,   252,
     253,    -1,   255,    -1,    -1,   258,    -1,   260,    -1,    -1,
      -1,   264,   265,    -1,    -1,    -1,    -1,    -1,   271,   272,
     273,   274,     5,     6,     7,     8,     9,    10,   281,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    22,
      23,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   304,    -1,    -1,    -1,    38,   309,   310,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    -1,    -1,    79,    -1,    -1,    82,
      -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,
      93,    94,    95,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   107,    -1,    -1,   110,    -1,   112,
     113,   114,    -1,    -1,    -1,    -1,   119,   120,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   136,   137,    -1,    -1,   140,    -1,   142,
     143,   144,   145,   146,   147,   148,    -1,   150,    -1,   152,
     153,   154,   155,    -1,   157,    -1,   159,    -1,    -1,    -1,
      -1,    -1,    -1,   166,    -1,    -1,   169,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   179,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   204,   205,    -1,    -1,    -1,    -1,    -1,    -1,   212,
      -1,   214,    -1,   216,    -1,    -1,    -1,    -1,    -1,   222,
      -1,    -1,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,    -1,   236,    -1,    -1,    -1,    -1,    -1,   242,
      -1,    -1,   245,    -1,    -1,    -1,   249,    -1,    -1,   252,
     253,    -1,   255,    -1,    -1,   258,    -1,   260,    -1,    -1,
      -1,   264,   265,    -1,    -1,    -1,    -1,    -1,   271,   272,
     273,   274,     5,     6,     7,     8,     9,    10,   281,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    22,
      23,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   304,    -1,    -1,    -1,    38,   309,   310,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    -1,    -1,    79,    -1,    -1,    82,
      -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,
      93,    94,    95,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   107,    -1,    -1,   110,    -1,   112,
     113,   114,    -1,    -1,    -1,    -1,   119,   120,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   136,   137,    -1,    -1,   140,    -1,   142,
     143,   144,   145,   146,   147,   148,    -1,   150,    -1,   152,
     153,   154,   155,    -1,   157,    -1,   159,    -1,    -1,    -1,
      -1,    -1,    -1,   166,    -1,    -1,   169,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   204,   205,    -1,    -1,    -1,    -1,    -1,    -1,   212,
      -1,    -1,    -1,   216,    -1,    -1,    -1,    -1,    -1,   222,
      -1,    -1,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,    -1,   236,    -1,    -1,    -1,    -1,    -1,   242,
      -1,    -1,   245,    -1,    -1,    -1,   249,    -1,    -1,   252,
     253,    -1,   255,    -1,    -1,   258,   259,   260,    -1,    -1,
      -1,   264,   265,    -1,    -1,    -1,    -1,    -1,   271,   272,
     273,   274,     5,     6,     7,     8,     9,    10,   281,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    22,
      23,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   304,    -1,    -1,    -1,    38,   309,   310,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    -1,    -1,    79,    -1,    -1,    82,
      -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,
      93,    94,    95,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   107,    -1,    -1,   110,    -1,   112,
     113,   114,    -1,    -1,    -1,    -1,   119,   120,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   136,   137,    -1,    -1,   140,    -1,   142,
     143,   144,   145,   146,   147,   148,    -1,   150,    -1,   152,
     153,   154,   155,    -1,   157,    -1,   159,    -1,    -1,    -1,
      -1,    -1,    -1,   166,   167,    -1,   169,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   204,   205,    -1,    -1,    -1,    -1,    -1,    -1,   212,
      -1,    -1,    -1,   216,    -1,    -1,    -1,    -1,    -1,   222,
      -1,    -1,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,    -1,   236,    -1,    -1,    -1,    -1,    -1,   242,
      -1,    -1,   245,    -1,    -1,    -1,   249,    -1,    -1,   252,
     253,    -1,   255,    -1,    -1,   258,    -1,   260,    -1,    -1,
      -1,   264,   265,    -1,    -1,    -1,    -1,    -1,   271,   272,
     273,   274,     5,     6,     7,     8,     9,    10,   281,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    22,
      23,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   304,    -1,    -1,    -1,    38,   309,   310,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    -1,    -1,    79,    -1,    -1,    82,
      -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,
      93,    94,    95,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   107,    -1,    -1,   110,    -1,   112,
     113,   114,    -1,    -1,    -1,    -1,   119,   120,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   136,   137,    -1,    -1,   140,    -1,   142,
     143,   144,   145,   146,   147,   148,    -1,   150,    -1,   152,
     153,   154,   155,    -1,   157,    -1,   159,    -1,    -1,    -1,
      -1,    -1,    -1,   166,    -1,    -1,   169,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   200,    -1,    -1,
      -1,   204,   205,    -1,    -1,    -1,    -1,    -1,    -1,   212,
      -1,    -1,    -1,   216,    -1,    -1,    -1,    -1,    -1,   222,
      -1,    -1,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,    -1,   236,    -1,    -1,    -1,    -1,    -1,   242,
      -1,    -1,   245,    -1,    -1,    -1,   249,    -1,    -1,   252,
     253,    -1,   255,    -1,    -1,   258,    -1,   260,    -1,    -1,
      -1,   264,   265,    -1,    -1,    -1,    -1,    -1,   271,   272,
     273,   274,     5,     6,     7,     8,     9,    10,   281,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    22,
      23,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   304,    -1,    -1,    -1,    38,   309,   310,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    -1,    -1,    79,    -1,    -1,    82,
      -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,
      93,    94,    95,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   107,    -1,    -1,   110,    -1,   112,
     113,   114,    -1,    -1,    -1,    -1,   119,   120,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   136,   137,    -1,    -1,   140,    -1,   142,
     143,   144,   145,   146,   147,   148,    -1,   150,    -1,   152,
     153,   154,   155,    -1,   157,    -1,   159,    -1,    -1,    -1,
      -1,    -1,    -1,   166,    -1,    -1,   169,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   204,   205,    -1,    -1,    -1,    -1,    -1,    -1,   212,
      -1,   214,    -1,   216,    -1,    -1,    -1,    -1,    -1,   222,
      -1,    -1,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,    -1,   236,    -1,    -1,    -1,    -1,    -1,   242,
      -1,    -1,   245,    -1,    -1,    -1,   249,    -1,    -1,   252,
     253,    -1,   255,    -1,    -1,   258,    -1,   260,    -1,    -1,
      -1,   264,   265,    -1,    -1,    -1,    -1,    -1,   271,   272,
     273,   274,     5,     6,     7,     8,     9,    10,   281,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    22,
      23,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   304,    -1,    -1,    -1,    38,   309,   310,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    -1,    -1,    79,    -1,    -1,    82,
      -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,
      93,    94,    95,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   107,    -1,    -1,   110,    -1,   112,
     113,   114,    -1,    -1,    -1,    -1,   119,   120,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   136,   137,    -1,    -1,   140,    -1,   142,
     143,   144,   145,   146,   147,   148,    -1,   150,    -1,   152,
     153,   154,   155,    -1,   157,    -1,   159,    -1,    -1,    -1,
      -1,    -1,    -1,   166,    -1,    -1,   169,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   204,   205,    -1,    -1,    -1,    -1,    -1,    -1,   212,
      -1,    -1,    -1,   216,    -1,    -1,    -1,    -1,    -1,   222,
      -1,    -1,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,    -1,   236,    -1,    -1,    -1,    -1,    -1,   242,
      -1,    -1,   245,    -1,    -1,    -1,   249,    -1,    -1,   252,
     253,    -1,   255,    -1,    -1,   258,    -1,   260,    -1,    -1,
      -1,   264,   265,    -1,    -1,    -1,    -1,    -1,   271,   272,
     273,   274,     5,     6,     7,     8,     9,    10,   281,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    22,
      23,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   304,    -1,    -1,    -1,    38,   309,   310,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    -1,    -1,    79,    -1,    -1,    82,
      -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,
      93,    94,    95,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   107,    -1,    -1,   110,    -1,   112,
     113,   114,    -1,    -1,    -1,    -1,   119,   120,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   136,   137,    -1,    -1,   140,    -1,   142,
     143,   144,   145,   146,   147,   148,    -1,   150,    -1,   152,
     153,   154,   155,    -1,   157,    -1,   159,    -1,    -1,    -1,
      -1,    -1,    -1,   166,    -1,    -1,   169,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   204,   205,    -1,    -1,    -1,    -1,    -1,    -1,   212,
      -1,    -1,    -1,   216,    -1,    -1,    -1,    -1,    -1,   222,
      -1,    -1,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,    -1,   236,    -1,    -1,    -1,    -1,    -1,   242,
      -1,    -1,   245,    -1,    -1,    -1,   249,    -1,    -1,   252,
     253,    -1,   255,    -1,    -1,   258,    -1,   260,    -1,    -1,
      -1,   264,   265,    -1,    -1,    -1,    -1,    -1,   271,   272,
     273,   274,     5,     6,     7,     8,     9,    10,   281,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    22,
      23,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   304,    -1,    -1,    -1,    38,   309,   310,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    -1,    -1,    79,    -1,    -1,    82,
      -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,
      93,    94,    95,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   107,    -1,    -1,   110,    -1,   112,
     113,   114,    -1,    -1,    -1,    -1,   119,   120,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   136,   137,    -1,    -1,   140,    -1,   142,
     143,   144,   145,   146,   147,   148,    -1,   150,    -1,   152,
     153,   154,   155,    -1,   157,    -1,   159,    -1,    -1,    -1,
      -1,    -1,    -1,   166,    -1,    -1,   169,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   204,   205,    -1,    -1,    -1,    -1,    -1,    -1,   212,
      -1,    -1,    -1,   216,    -1,    -1,    -1,    -1,    -1,   222,
      -1,    -1,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,    -1,   236,    -1,    -1,    -1,    -1,    -1,   242,
      -1,    -1,   245,    -1,    -1,    -1,   249,    -1,    -1,   252,
     253,    -1,   255,    -1,    -1,   258,    -1,   260,    -1,    -1,
      -1,   264,   265,    -1,    -1,    -1,    -1,    -1,   271,   272,
     273,   274,     5,     6,     7,     8,     9,    10,   281,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    22,
      23,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   304,    -1,    -1,    -1,    38,   309,   310,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    -1,    -1,    79,    -1,    -1,    82,
      -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,
      93,    94,    95,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   107,    -1,    -1,   110,    -1,   112,
     113,   114,    -1,    -1,    -1,    -1,   119,   120,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   136,   137,    -1,    -1,   140,    -1,   142,
     143,   144,   145,   146,   147,   148,    -1,   150,    -1,   152,
     153,   154,   155,    -1,   157,    -1,   159,    -1,    -1,    -1,
      -1,    -1,    -1,   166,    -1,    -1,   169,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   204,   205,    -1,    -1,    -1,    -1,    -1,    -1,   212,
      -1,    -1,    -1,   216,    -1,    -1,    -1,    -1,    -1,   222,
      -1,    -1,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,    -1,   236,    -1,    -1,    -1,    -1,    -1,   242,
      -1,    -1,   245,    -1,    -1,    -1,   249,    -1,    -1,   252,
     253,    -1,   255,    -1,    -1,   258,    -1,   260,    -1,    -1,
      -1,   264,   265,    -1,    -1,    -1,    -1,    -1,   271,   272,
     273,   274,    -1,    -1,    -1,    -1,    -1,    -1,   281,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   304,    -1,    -1,    -1,    -1,   309,   310
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     1,    51,    61,    62,    63,    64,    73,    74,    75,
      76,    82,   127,   165,   167,   215,   223,   224,   226,   228,
     229,   230,   231,   232,   233,   234,   237,   243,   244,   259,
     262,   298,   332,   339,   340,   341,   342,   343,   345,   347,
     348,   357,   362,   372,   377,   378,   388,   431,   433,   441,
     462,   475,   479,   480,   481,   489,   502,   503,   504,   521,
     525,   526,   527,   530,   652,   127,   105,     5,     6,     7,
       8,     9,    10,    22,    23,    26,    38,    41,    60,    76,
      79,    82,    88,    93,    94,    95,   107,   110,   112,   113,
     114,   119,   120,   136,   137,   140,   142,   143,   144,   145,
     146,   147,   148,   150,   152,   153,   154,   155,   157,   159,
     166,   169,   204,   205,   212,   216,   222,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   236,   242,   245,
     249,   252,   253,   255,   258,   260,   264,   265,   271,   272,
     273,   274,   281,   304,   309,   310,   618,   645,   646,   172,
     236,   513,   247,    77,   486,   486,   645,    75,    83,   522,
     523,   645,    63,   530,    64,    65,    66,   589,   590,   591,
     645,   618,   335,   334,   337,   338,   336,   333,     5,    11,
     650,   653,     5,     6,     7,     8,     9,    10,    61,    62,
      63,    64,   172,   234,   257,   358,   365,   367,   368,   369,
     643,   644,   243,   246,   363,   364,    55,    83,    52,   109,
     264,    11,   283,   427,   495,   521,   527,   634,   649,     0,
      17,    52,    55,   109,   159,   204,   205,   206,   207,   208,
     209,   216,   217,   218,   219,   245,   258,   264,   267,   269,
     305,   389,   390,   392,   393,   426,    52,   109,   159,   172,
     217,   218,   219,   245,   258,   264,   269,   303,   305,    52,
      53,    54,    60,   245,   258,   272,   615,   645,   204,   205,
     264,   346,   392,   424,   645,   127,    98,   160,   161,   162,
     546,   127,   618,   259,   326,     3,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    18,    19,    27,
      28,    44,    45,    46,    47,    48,    49,    50,    59,   100,
     104,   108,   118,   128,   129,   130,   131,   132,   134,   135,
     138,   139,   141,   151,   158,   167,   170,   186,   187,   196,
     197,   198,   200,   203,   271,   272,   273,   274,   285,   289,
     290,   328,   330,   509,   533,   544,   545,   553,   554,   555,
     556,   558,   560,   561,   563,   565,   567,   568,   569,   570,
     571,   572,   573,   574,   575,   588,   589,   592,   594,   595,
     596,   598,   599,   600,   601,   602,   615,   616,   617,   619,
     620,   622,   638,   641,   645,   651,   660,   661,   662,   663,
     664,   678,   685,   687,   690,   700,   701,   731,   618,   184,
     487,   487,   645,    84,    87,    93,   482,   483,   484,   325,
     524,   527,   167,   429,   430,   513,   168,   167,   326,   429,
     343,   343,   332,   332,   343,   343,   167,   429,   429,   255,
     429,   266,   325,   266,   250,   325,   251,   251,   365,   358,
      83,   482,   259,   645,   618,   618,   634,   247,    27,   247,
     283,   299,   204,   205,   645,   204,   205,   618,   218,   264,
     264,   264,   264,   645,   618,   618,   618,   645,   212,   349,
     645,   618,   618,   618,   303,   264,   645,   618,   218,   159,
     217,   218,   219,   618,   618,   618,   645,   618,   618,   618,
     618,   618,   212,   645,   645,   281,   171,   171,   325,     5,
       6,     7,    20,    24,    25,    26,    29,    30,    31,    32,
      33,    34,    35,    36,    37,   271,   272,   273,   274,   325,
     607,   614,   637,   638,   639,   640,   641,    99,   172,   236,
     531,   531,   531,   282,   547,   270,   516,   430,   514,   515,
     642,   645,   645,   651,   651,   651,   167,   167,    22,   167,
     593,   593,   593,   593,   593,   167,   569,   167,   119,   645,
     167,   167,   167,   167,   167,   167,   167,   167,   167,   167,
     167,   167,   268,   521,   530,   544,   554,   562,   589,   645,
     554,   167,   571,   571,   167,   167,   167,   571,   651,   167,
     605,   167,   606,   186,   187,   603,   286,   571,   627,   628,
     167,   167,   554,   566,   105,   247,   534,   535,   304,   597,
     182,   171,   174,   175,   176,   177,   178,   179,   180,   181,
     184,   185,   618,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   200,   201,   202,   248,   315,   326,   325,
     167,   167,   167,   651,   651,   326,   167,   235,   268,   427,
     430,   505,    78,    79,   266,   488,    85,    86,    88,    94,
     325,   523,   424,   304,   533,   168,   510,   571,   623,   591,
     645,   284,   549,   127,   127,   127,   127,   167,   168,   508,
     510,   512,   530,   256,   370,   371,   643,   643,   370,   264,
     366,   618,   369,   106,   106,   105,   105,   482,   240,   241,
     391,   165,   239,   259,   373,   111,   380,   382,   237,   259,
     262,   263,   302,   651,   247,   618,   634,   283,   165,   304,
     618,   618,   618,   618,   618,   221,   167,   167,   167,   165,
     355,   350,   645,   235,   351,   212,   167,   395,   396,   429,
     429,   307,   308,   463,   645,   618,   618,   218,   618,   618,
     618,   167,   476,   476,   476,    42,    43,   478,   478,   478,
     645,    55,   274,   617,   645,   510,   424,   167,   167,    21,
      22,   167,   167,   167,    38,   605,   606,   275,   276,   277,
     278,   279,   280,   608,   610,   612,   613,   645,   167,   167,
     167,   167,   550,   551,   571,   163,   532,   532,   532,   573,
     633,   648,   649,   283,   548,   544,   171,   325,   516,   171,
     326,   544,   621,   621,    23,   168,   280,   608,   609,   106,
     571,   572,   571,   657,   658,   659,   657,   222,   149,   679,
     705,   146,   148,   703,   222,     3,   691,   572,   109,   702,
     703,   657,   530,   167,   506,   168,   168,   168,   168,   325,
     326,   571,   571,   571,   650,   165,   604,   650,   604,   651,
     544,   286,   625,   626,   288,   627,   629,   571,   510,   624,
     325,   329,   167,   328,   517,   536,   537,   538,   569,   589,
     618,   645,   528,   529,   645,   516,   645,   544,   554,    96,
      97,   557,   557,   167,   167,   559,   571,   559,   559,   559,
     545,   172,   173,   183,   554,   564,   567,   571,   571,   571,
     571,   571,   571,   571,   571,   571,   571,   571,   571,   571,
     104,   170,   167,   200,   596,   168,   172,   200,   236,   571,
     630,   645,   630,     8,     9,    10,   200,   645,   268,   506,
     505,    78,    75,    84,    91,    92,   485,   650,   484,   168,
     167,   168,   325,    14,   573,   635,   648,   227,   344,   168,
     325,   165,   325,   360,   165,   359,   618,   370,   370,   242,
     391,   266,   258,   165,   110,   383,   214,   264,   265,   375,
     376,    64,    84,   374,   376,   264,   376,    16,   493,   494,
     493,   618,   429,   299,   634,   391,   637,   167,   395,   395,
     395,   395,   222,   200,   460,   461,   645,   460,   460,   246,
      20,   253,   654,   655,   350,   179,   214,   398,   399,   400,
     402,   405,   413,   414,   425,   642,   645,   304,   304,    61,
      62,    64,   464,   250,   395,   476,   618,   478,   478,   478,
     168,   477,   637,   478,   478,   478,   637,   631,   650,   631,
      23,   631,   631,   631,   650,   604,   604,   606,   605,   266,
     631,   650,   631,   631,   631,   325,   210,   211,   552,    99,
     530,   530,   530,   573,   635,   549,   569,   515,   544,   645,
     304,   325,   105,   618,   152,   704,   325,   704,   704,   645,
     666,   167,   571,   680,   681,   682,   325,   572,   645,   688,
     140,   692,   704,   657,   546,   168,   507,   510,   511,   168,
     325,   176,   177,   554,   105,   325,   177,   325,   168,   272,
     651,   168,   651,   613,   287,   571,   625,   629,   571,   297,
     325,   325,   168,   325,   554,   167,   517,   538,   539,   325,
      65,    66,    67,    69,    70,    71,    72,   164,   518,   519,
     304,   540,   645,   540,   540,   326,   325,   534,   103,   541,
     554,   554,   508,   508,   101,   569,   104,   316,   576,   577,
     630,   168,   630,   168,   326,   325,   326,   645,    89,    90,
      84,   524,   510,   512,   246,   371,   105,   361,   243,   361,
     361,   361,   651,   242,   645,   645,   569,   634,    99,   113,
     116,   384,   645,   645,   645,    86,    85,    86,   645,   618,
     399,   104,   496,   300,   496,   105,   105,   242,    82,   379,
     381,   460,   250,   645,   168,   325,   637,   168,   168,    53,
      59,   356,   259,   645,   647,   656,   339,   340,   352,   353,
     354,   357,   362,   372,   377,   475,   618,   645,   168,   325,
     238,   254,   267,   422,   124,   125,   401,   637,   165,   427,
     427,   306,   250,   618,   250,   394,   478,   478,   168,   325,
     168,   168,   168,   168,   325,   168,   325,   280,   608,   611,
     168,   325,   168,   168,   168,   551,   167,   637,   637,   571,
     109,   148,   168,   657,   168,   168,   325,   665,    79,   235,
     571,   706,   707,   709,   710,   711,   251,   325,   676,   304,
     683,    80,   136,   686,   325,   689,    99,   693,   713,   704,
     168,   155,   714,   715,   704,   168,   325,   167,   167,   167,
     571,   571,   571,   571,   281,   510,   287,   297,   571,   510,
     510,   168,   530,   538,    71,   518,    71,   538,   538,    71,
      68,   645,   167,   645,   529,    99,   102,   543,   184,   184,
     168,   168,   651,    99,   168,    98,   578,   168,   168,   200,
     630,   645,   168,   251,   356,   251,    16,   651,   632,   649,
     632,   112,   115,   385,   478,   478,   478,   237,   259,   304,
     468,   651,   167,   500,   501,   651,   301,   500,   651,   165,
     383,   168,     3,    63,    76,    82,   221,   224,   261,   285,
     291,   296,   345,   347,   348,   357,   362,   372,   377,   434,
     437,   439,   440,   441,   445,   447,   453,   455,   456,   475,
     479,   480,   526,   645,   645,   220,   220,   645,   325,   354,
     400,   645,   249,   249,   430,   121,   126,   235,   403,   404,
     407,   408,   410,   411,   414,   252,   165,   397,   165,   428,
     424,   645,   167,    73,   477,   636,   650,   650,   606,   650,
     542,   619,   645,   168,   168,   168,   133,   571,   667,   673,
     674,   675,   705,   704,   235,   709,   168,   325,   304,   104,
     142,   144,   145,   677,   681,   704,   645,   684,   137,   137,
     168,   572,   704,   119,   143,   572,   694,   695,   696,   697,
     698,   713,   266,   168,   168,   511,   507,   508,   508,   106,
     168,   168,   325,   168,   325,   510,   168,   329,   538,    71,
     538,    16,   250,   520,   520,   538,   167,   647,   542,   544,
     554,   554,   542,    99,    81,   323,   579,   580,   168,   168,
     312,   259,   632,   120,   386,   235,    95,   104,   170,   235,
     651,   325,   501,    79,   499,   325,   167,   490,   490,   222,
     634,   384,   221,   513,   222,   442,   443,   618,   264,   427,
     446,   544,   286,   450,   451,   571,   544,   295,   435,   293,
     327,   637,   264,   459,   637,   459,   645,   430,   430,   122,
     409,   570,   407,   104,   170,   213,   254,   257,   267,   421,
     423,   167,    79,   166,   213,   314,   465,   424,    61,    80,
     237,   168,   168,   168,   168,   325,   326,   167,   325,   325,
     676,   325,   168,   707,   645,   708,   250,   250,   250,   250,
     168,   168,   304,   712,   713,   325,   104,   145,   699,   156,
     168,   168,   168,   571,   571,   571,   540,   538,   430,   544,
     520,   647,   168,   550,   175,   317,   324,   572,   581,   582,
     583,   584,   242,   258,   632,   114,   117,   387,     3,   104,
     104,   409,   651,   168,   214,   651,   491,   492,   645,   493,
     493,   651,   385,   222,   533,   432,   645,   167,   167,   544,
     288,   450,   452,   286,   448,   449,   287,   435,   437,   544,
     167,   221,   225,   434,   221,   225,   257,   304,   104,   167,
     249,   618,   406,   407,   166,   251,   311,   312,   466,   467,
     106,   470,   471,   168,    81,    81,   619,   645,   571,   668,
     669,   671,   673,   675,   667,   673,   104,    79,   104,   104,
     104,   645,   695,   250,   250,   168,    79,   154,   157,   716,
     717,   722,   168,   168,   168,   168,   582,   309,   320,   320,
     318,   587,   651,   645,   325,   168,   325,     3,   496,   496,
     258,   386,   432,   326,   444,   571,   427,   287,   435,   297,
     571,   448,   452,   435,   437,   127,   294,   458,   642,   222,
       5,   222,     5,   618,   123,   544,   429,   168,   325,   264,
     309,   469,   264,   469,   467,   313,   286,   473,   168,   325,
     304,   670,   325,   148,   712,   145,   145,   150,   645,   723,
       3,   718,   719,    79,   147,   150,   724,   725,   727,   728,
     184,    79,   103,   317,   322,   651,   492,    56,   497,   497,
     645,   387,   645,   168,   325,   168,   435,   437,   285,   287,
     297,   288,   292,   454,   127,   297,   435,   168,   325,   637,
     432,     4,   432,     4,   429,   167,   412,   168,   107,   420,
     407,   468,   468,   468,   468,   309,   310,   472,   544,   296,
     345,   347,   357,   362,   438,   439,   474,   479,   480,   526,
     669,   645,   672,   673,   153,   720,   720,   150,   645,   730,
     719,   729,   726,   727,   317,   324,   572,   585,   586,   321,
     309,    57,   498,   498,   571,   127,   435,   285,   435,   544,
     297,   297,   297,   642,   420,   379,    39,    40,    67,   419,
     250,   416,   417,   418,   645,   645,   645,   645,   295,   719,
     721,   309,   319,   320,    58,   499,   499,   287,   291,   293,
     637,   418,   168,    61,    62,   250,   417,   250,   416,   436,
     435,   457,   645,    42,    43,    79,   259,   415,   415,   297,
     438,   454,    41,   104,   235,   127
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   331,   332,   333,   332,   334,   332,   335,   332,   336,
     332,   337,   332,   338,   332,   332,   332,   332,   332,   332,
     339,   340,   341,   342,   343,   343,   343,   343,   343,   343,
     343,   343,   343,   343,   344,   344,   345,   345,   346,   346,
     347,   347,   347,   347,   347,   347,   347,   348,   348,   349,
     349,   349,   350,   351,   351,   352,   352,   353,   353,   354,
     354,   354,   354,   354,   355,   355,   356,   356,   357,   357,
     358,   358,   359,   359,   360,   360,   361,   361,   362,   362,
     363,   363,   364,   364,   365,   366,   366,   367,   367,   367,
     368,   368,   369,   369,   369,   369,   369,   369,   370,   370,
     371,   371,   372,   372,   372,   372,   372,   372,   372,   372,
     372,   372,   373,   373,   373,   374,   374,   374,   374,   374,
     374,   375,   375,   375,   376,   376,   377,   377,   377,   377,
     377,   377,   377,   377,   378,   378,   378,   379,   380,   381,
     381,   382,   382,   382,   382,   383,   383,   384,   384,   384,
     385,   385,   385,   386,   386,   387,   387,   387,   388,   389,
     389,   390,   390,   391,   391,   391,   392,   392,   392,   392,
     392,   392,   393,   393,   393,   393,   393,   393,   394,   394,
     394,   394,   395,   395,   396,   397,   397,   398,   398,   399,
     399,   400,   400,   400,   401,   401,   402,   402,   403,   403,
     404,   404,   405,   406,   406,   407,   407,   407,   408,   409,
     410,   411,   411,   412,   412,   413,   414,   414,   415,   415,
     415,   415,   415,   416,   417,   418,   418,   418,   418,   418,
     419,   419,   419,   419,   420,   420,   421,   421,   421,   421,
     421,   421,   422,   422,   422,   423,   424,   424,   425,   426,
     427,   427,   428,   428,   429,   429,   430,   431,   432,   433,
     433,   433,   433,   433,   433,   433,   433,   434,   434,   434,
     435,   435,   436,   436,   437,   437,   437,   437,   437,   437,
     437,   437,   437,   437,   437,   437,   438,   438,   438,   438,
     438,   438,   438,   438,   439,   439,   439,   439,   439,   439,
     440,   441,   442,   443,   444,   444,   444,   445,   446,   446,
     446,   447,   447,   448,   449,   449,   450,   451,   451,   452,
     452,   453,   454,   454,   454,   455,   456,   456,   457,   457,
     458,   458,   459,   459,   460,   460,   460,   461,   461,   462,
     463,   463,   464,   464,   464,   464,   465,   465,   466,   466,
     467,   467,   467,   467,   468,   468,   469,   469,   470,   471,
     471,   472,   472,   473,   473,   474,   474,   475,   475,   475,
     475,   475,   475,   475,   475,   475,   475,   475,   475,   475,
     475,   476,   476,   476,   477,   477,   478,   478,   478,   343,
     343,   479,   479,   479,   479,   480,   481,   481,   481,   481,
     481,   481,   481,   482,   482,   483,   483,   484,   484,   484,
     484,   485,   485,   485,   485,   486,   486,   487,   487,   487,
     488,   488,   489,   489,   489,   489,   489,   490,   490,   491,
     491,   492,   492,   493,   493,   493,   493,   494,   494,   495,
     495,   495,   495,   495,   496,   496,   497,   497,   498,   498,
     499,   499,   500,   500,   501,   501,   502,   503,   504,   504,
     505,   505,   505,   505,   506,   506,   507,   507,   508,   508,
     509,   510,   511,   512,   512,   513,   513,   513,   514,   514,
     515,   515,   516,   516,   517,   517,   517,   517,   517,   517,
     517,   518,   518,   518,   519,   519,   519,   520,   520,   343,
     521,   522,   522,   523,   524,   343,   343,   525,   526,   527,
     528,   528,   529,   530,   530,   530,   530,   530,   531,   531,
     531,   532,   532,   532,   533,   534,   535,   535,   536,   536,
     537,   537,   537,   537,   538,   538,   538,   538,   539,   538,
     540,   540,   540,   540,   541,   541,   542,   542,   543,   543,
     544,   544,   545,   545,   546,   546,   547,   547,   547,   548,
     548,   548,   549,   549,   549,   549,   550,   550,   551,   552,
     552,   552,   553,   553,   553,   553,   553,   553,   553,   553,
     553,   554,   554,   555,   555,   556,   556,   557,   557,   557,
     558,   558,   558,   558,   559,   559,   560,   560,   561,   561,
     561,   561,   562,   562,   563,   564,   564,   564,   565,   566,
     566,   567,   568,   569,   569,   569,   570,   570,   570,   570,
     570,   570,   570,   570,   570,   570,   570,   570,   570,   570,
     570,   570,   570,   571,   571,   572,   572,   572,   572,   572,
     572,   572,   572,   572,   572,   572,   572,   572,   572,   572,
     572,   573,   574,   575,   575,   576,   577,   577,   578,   578,
     579,   579,   580,   580,   581,   581,   582,   582,   582,   583,
     584,   585,   585,   585,   586,   587,   587,   587,   587,   587,
     588,   589,   589,   590,   590,   591,   591,   591,   591,   592,
     592,   592,   592,   592,   592,   593,   593,   594,   594,   594,
     594,   594,   594,   594,   595,   595,   596,   596,   596,   596,
     597,   597,   598,   599,   599,   600,   600,   601,   601,   602,
     602,   602,   602,   602,   602,   602,   603,   603,   603,   604,
     604,   605,   605,   606,   606,   607,   607,   607,   608,   608,
     608,   608,   608,   609,   609,   610,   611,   611,   612,   612,
     613,   613,   614,   615,   615,   615,   616,   616,   616,   616,
     616,   616,   616,   616,   616,   616,   616,   616,   616,   616,
     616,   616,   617,   618,   618,   618,   619,   619,   619,   620,
     620,   621,   622,   622,   622,   622,   623,   623,   624,   624,
     625,   626,   626,   627,   628,   628,   629,   629,   630,   631,
     632,   633,   634,   635,   636,   637,   637,   637,   637,   637,
     637,   637,   637,   637,   637,   637,   637,   637,   637,   637,
     637,   637,   637,   637,   637,   637,   637,   637,   637,   637,
     637,   637,   637,   637,   637,   637,   638,   639,   639,   640,
     640,   640,   641,   641,   642,   643,   644,   644,   644,   644,
     644,   644,   645,   645,   645,   645,   645,   645,   645,   645,
     646,   646,   646,   646,   646,   646,   646,   646,   646,   646,
     646,   646,   646,   646,   646,   646,   646,   646,   646,   646,
     646,   646,   646,   646,   646,   646,   646,   646,   646,   646,
     646,   646,   646,   646,   646,   646,   646,   646,   646,   646,
     646,   646,   646,   646,   646,   646,   646,   646,   646,   646,
     646,   646,   646,   646,   646,   646,   646,   646,   646,   646,
     646,   646,   646,   646,   646,   646,   646,   646,   646,   646,
     646,   646,   647,   647,   648,   649,   650,   650,   651,   651,
     652,   653,   653,   654,   654,   655,   656,   657,   658,   658,
     659,   660,   660,   660,   660,   660,   660,   660,   660,   660,
     660,   661,   662,   663,   664,   665,   665,   665,   665,   665,
     665,   665,   665,   666,   667,   668,   668,   669,   670,   670,
     671,   672,   673,   674,   674,   675,   676,   676,   677,   677,
     677,   677,   677,   678,   679,   679,   680,   680,   681,   682,
     683,   683,   684,   685,   686,   686,   687,   688,   689,   689,
     690,   691,   692,   692,   693,   694,   694,   695,   695,   696,
     697,   698,   698,   699,   699,   700,   701,   702,   702,   703,
     703,   704,   704,   704,   705,   706,   706,   707,   707,   708,
     709,   710,   711,   711,   712,   712,   713,   713,   714,   714,
     715,   716,   716,   717,   717,   718,   719,   720,   720,   721,
     722,   723,   724,   724,   725,   725,   726,   726,   727,   728,
     728,   729,   730,   731
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     3,     0,     3,     2,     0,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     5,     1,     0,     1,     2,     2,     2,     4,
       4,     4,     3,     4,     3,     4,     4,     6,     4,     1,
       2,     3,     1,     0,     4,     0,     1,     1,     2,     1,
       1,     1,     1,     1,     0,     3,     1,     1,     6,     6,
       1,     3,     0,     3,     0,     3,     0,     2,     6,     6,
       0,     3,     0,     3,     3,     2,     1,     2,     1,     1,
       1,     3,     1,     1,     2,     2,     2,     1,     1,     3,
       1,     1,     6,     6,     5,     5,     6,     6,     6,     4,
       6,    10,     4,     3,     7,     5,     4,     5,     4,     5,
       5,     3,     3,     3,     1,     0,     2,     2,     2,     1,
       1,     1,     1,     1,     6,     3,     4,     6,     6,     0,
       3,     0,     1,     3,     3,     0,     3,     0,     2,     1,
       0,     2,     1,     0,     2,     0,     1,     1,     9,     1,
       0,     3,    10,     0,     1,     1,     3,     4,     4,     4,
       6,     5,     1,     1,     2,     2,     2,     2,     0,     4,
       4,     3,     3,     1,     4,     3,     2,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     3,     2,     0,     1,
       1,     2,     6,     1,     3,     1,     1,     1,     2,     1,
       2,     5,     1,     0,     3,     2,     0,     2,     2,     1,
       1,     2,     2,     3,     3,     0,     1,     1,     2,     2,
       0,     1,     1,     1,     0,     2,     2,     1,     1,     2,
       5,     1,     2,     3,     8,     4,     1,     3,     2,     6,
       1,     1,     0,     3,     0,     1,     3,     6,     3,    11,
       9,    11,    10,    11,    11,     9,     7,     1,     5,     6,
       0,     3,     0,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     4,     1,     0,     1,     3,     2,     1,     1,
       4,     6,     5,     4,     1,     2,     4,     1,     2,     0,
       2,     7,     0,     2,     5,     8,     0,     2,     0,     1,
       2,     4,     4,     1,     1,     1,     0,     4,     2,     9,
       1,     1,     1,     1,     1,     3,     0,     2,     1,     2,
       4,     4,     4,     4,     0,     1,     0,     1,     3,     0,
       3,     1,     1,     0,     2,     1,     4,     4,     5,     6,
       5,     5,     5,     6,     5,     5,     4,     3,     3,     3,
       3,     0,     3,     2,     1,     3,     0,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     2,     3,     4,
       3,     4,     3,     0,     1,     1,     3,     2,     2,     3,
       3,     2,     2,     2,     1,     1,     0,     2,     3,     0,
       0,     3,    13,    13,     8,     6,     6,     0,     3,     1,
       3,     1,     2,     0,     3,     5,     7,     0,     1,     0,
       2,     2,     4,     4,     0,     3,     0,     1,     0,     2,
       0,     2,     1,     3,     1,     3,     4,     5,     4,     5,
       0,     2,     2,     1,     3,     5,     1,     3,     1,     3,
       1,     1,     1,     1,     1,     0,     1,     1,     1,     3,
       3,     3,     0,     2,     3,     4,     4,     4,     4,     5,
       5,     1,     2,     1,     1,     1,     1,     2,     2,     1,
       3,     3,     1,     6,     1,     1,     1,     4,     6,     5,
       1,     3,     1,     5,     5,     5,     3,     1,     0,     1,
       1,     0,     1,     5,     1,     4,     0,     2,     1,     3,
       1,     2,     2,     1,     1,     2,     1,     1,     0,     5,
       5,     2,     4,     1,     0,     3,     1,     3,     0,     2,
       3,     1,     3,     1,     0,     3,     0,     2,     2,     0,
       2,     2,     0,     2,     2,     2,     1,     3,     2,     0,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     3,     3,     6,     6,     0,     1,     1,
       3,     3,     3,     3,     1,     3,     4,     3,     5,     5,
       7,     7,     1,     3,     4,     1,     1,     1,     2,     1,
       3,     3,     3,     3,     4,     3,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     3,     3,     3,     3,
       2,     2,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     4,     1,     1,     1,     1,     1,     1,
       1,     1,     5,     3,     1,     3,     0,     3,     0,     3,
       0,     3,     1,     1,     1,     1,     2,     1,     2,     2,
       4,     2,     1,     2,     2,     0,     3,     2,     2,     3,
       2,     3,     4,     1,     3,     1,     1,     1,     1,     6,
       2,     2,     2,     2,     2,     0,     2,     8,     8,     6,
       6,     6,     3,     8,     1,     3,     1,     3,     3,     2,
       0,     2,     1,     1,     3,     1,     3,     1,     3,     4,
       6,     5,     5,     4,     6,     1,     1,     1,     0,     3,
       0,     3,     0,     3,     0,     1,     3,     3,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     2,     2,     2,
       3,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     4,     4,     1,     2,     2,     2,     2,
       1,     1,     4,     1,     3,     5,     1,     3,     5,     6,
       6,     1,     6,     4,     5,     4,     1,     3,     3,     3,
       4,     1,     2,     4,     1,     2,     0,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     4,     4,
       4,     1,     4,     1,     1,     1,     1,     1,     1,     4,
       6,     1,     4,     6,     1,     2,     1,     1,     1,     1,
       4,     1,     4,     6,     1,     4,     1,     1,     2,     1,
       1,     3,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     1,     1,     1,     1,     2,
       2,     3,     4,     0,     1,     2,     1,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     5,     5,     5,     7,     0,     2,     4,     6,     4,
       2,     4,     2,     1,     4,     1,     3,     2,     0,     2,
       1,     1,     2,     1,     3,     1,     0,     2,     3,     3,
       3,     3,     4,     7,     0,     2,     1,     3,     2,     1,
       0,     2,     1,     6,     2,     2,     7,     1,     0,     2,
       8,     1,     0,     3,     1,     1,     3,     1,     1,     2,
       4,     0,     1,     3,     3,     5,     6,     1,     1,     1,
       1,     0,     2,     2,     4,     1,     3,     1,     1,     1,
       1,     3,     2,     2,     0,     1,     2,     2,     0,     1,
       5,     1,     1,     3,     3,     1,     1,     0,     2,     1,
       2,     1,     0,     1,     1,     2,     0,     1,     2,     2,
       2,     1,     1,     6
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (m, YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, m); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, mvc *m)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (m);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, mvc *m)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, m);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule, mvc *m)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              , m);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, m); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, mvc *m)
{
  YYUSE (yyvaluep);
  YYUSE (m);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (mvc *m)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex (&yylval, m);
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 607 "sql_parser.y" /* yacc.c:1646  */
    {
		if (m->sym) {
			append_symbol(m->sym->data.lval, (yyval.sym));
			(yyval.sym) = m->sym;
		} else {
			m->sym = (yyval.sym) = (yyvsp[-1].sym);
		}
		YYACCEPT;
	}
#line 6204 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 617 "sql_parser.y" /* yacc.c:1646  */
    {
		  	  m->emode = m_prepare; 
			  m->scanner.as = m->scanner.yycur; 
			  m->scanner.key = 0;
			}
#line 6214 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 622 "sql_parser.y" /* yacc.c:1646  */
    {
			  if (m->sym) {
				append_symbol(m->sym->data.lval, (yyvsp[-1].sym));
				(yyval.sym) = m->sym;
			  } else {
				m->sym = (yyval.sym) = (yyvsp[-1].sym);
			  }
			  YYACCEPT;
			}
#line 6228 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 631 "sql_parser.y" /* yacc.c:1646  */
    {
		  	  m->emode = m_plan;
			  m->scanner.as = m->scanner.yycur; 
			  m->scanner.key = 0;
			}
#line 6238 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 636 "sql_parser.y" /* yacc.c:1646  */
    {
			  if (m->sym) {
				append_symbol(m->sym->data.lval, (yyvsp[-1].sym));
				(yyval.sym) = m->sym;
			  } else {
				m->sym = (yyval.sym) = (yyvsp[-1].sym);
			  }
			  YYACCEPT;
			}
#line 6252 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 646 "sql_parser.y" /* yacc.c:1646  */
    {
		  	  m->emod |= mod_explain;
			  m->scanner.as = m->scanner.yycur; 
			  m->scanner.key = 0;
			}
#line 6262 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 651 "sql_parser.y" /* yacc.c:1646  */
    {
			  if (m->sym) {
				append_symbol(m->sym->data.lval, (yyvsp[-1].sym));
				(yyval.sym) = m->sym;
			  } else {
				m->sym = (yyval.sym) = (yyvsp[-1].sym);
			  }
			  YYACCEPT;
			}
#line 6276 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 661 "sql_parser.y" /* yacc.c:1646  */
    {
		  	  m->emod |= mod_dot;
			  m->scanner.as = m->scanner.yycur; 
			  m->scanner.key = 0;
			}
#line 6286 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 666 "sql_parser.y" /* yacc.c:1646  */
    {
			  if (m->sym) {
				append_symbol(m->sym->data.lval, (yyvsp[-1].sym));
				(yyval.sym) = m->sym;
			  } else {
				m->sym = (yyval.sym) = (yyvsp[-1].sym);
			  }
			  YYACCEPT;
			}
#line 6300 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 676 "sql_parser.y" /* yacc.c:1646  */
    {
			  if (m->scanner.mode == LINE_1) {
				yyerror(m, "SQL debugging only supported in interactive mode");
				YYABORT;
			  }
		  	  m->emod |= mod_debug;
			  m->scanner.as = m->scanner.yycur; 
			  m->scanner.key = 0;
			}
#line 6314 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 685 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); YYACCEPT; }
#line 6320 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 686 "sql_parser.y" /* yacc.c:1646  */
    {
		  	  m->emod |= mod_trace;
			  m->scanner.as = m->scanner.yycur; 
			  m->scanner.key = 0;
			}
#line 6330 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 691 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); YYACCEPT; }
#line 6336 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 692 "sql_parser.y" /* yacc.c:1646  */
    { m->sym = (yyval.sym) = (yyvsp[-1].sym); YYACCEPT; }
#line 6342 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 693 "sql_parser.y" /* yacc.c:1646  */
    { m->sym = (yyval.sym) = NULL; YYACCEPT; }
#line 6348 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 694 "sql_parser.y" /* yacc.c:1646  */
    { m->sym = (yyval.sym) = NULL; YYACCEPT; }
#line 6354 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 695 "sql_parser.y" /* yacc.c:1646  */
    { m->sym = (yyval.sym) = NULL; YYACCEPT; }
#line 6360 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 696 "sql_parser.y" /* yacc.c:1646  */
    { m->sym = (yyval.sym) = NULL; YYABORT; }
#line 6366 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 723 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		append_list(l, (yyvsp[-3].l));
		append_list(l, (yyvsp[-2].l));
		append_symbol(l, (yyvsp[-1].sym));
		append_int(l, (yyvsp[0].i_val));
		(yyval.sym) = _symbol_create_list( SQL_ANALYZE, l); }
#line 6377 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 733 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 6383 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 734 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 1; }
#line 6389 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 739 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_DECLARE, (yyvsp[0].l)); }
#line 6395 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 740 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 6401 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 745 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		append_list(l, (yyvsp[-1].l) );
		append_type(l, &(yyvsp[0].type) );
		(yyval.l) = append_symbol(L(), _symbol_create_list( SQL_DECLARE, l)); }
#line 6410 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 750 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		append_list(l, (yyvsp[-1].l) );
		append_type(l, &(yyvsp[0].type) );
		(yyval.l) = append_symbol((yyvsp[-3].l), _symbol_create_list( SQL_DECLARE, l)); }
#line 6419 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 758 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		append_string(l, (yyvsp[-2].sval) );
		append_symbol(l, (yyvsp[0].sym) );
		(yyval.sym) = _symbol_create_list( SQL_SET, l); }
#line 6428 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 763 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  sql_subtype t;
	        sql_find_subtype(&t, "char", UTF8_strlen((yyvsp[0].sval)), 0 );
		append_string(l, sa_strdup(SA, "current_user"));
		append_symbol(l,
			_newAtomNode( _atom_string(&t, sql2str((yyvsp[0].sval)))) );
		(yyval.sym) = _symbol_create_list( SQL_SET, l); }
#line 6440 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 771 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  sql_subtype t;
		sql_find_subtype(&t, "char", UTF8_strlen((yyvsp[0].sval)), 0 );
		append_string(l, sa_strdup(SA, "current_schema"));
		append_symbol(l,
			_newAtomNode( _atom_string(&t, sql2str((yyvsp[0].sval)))) );
		(yyval.sym) = _symbol_create_list( SQL_SET, l); }
#line 6452 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 779 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  sql_subtype t;
		sql_find_subtype(&t, "char", UTF8_strlen((yyvsp[0].sval)), 0 );
		append_string(l, sa_strdup(SA, "current_user"));
		append_symbol(l,
			_newAtomNode( _atom_string(&t, sql2str((yyvsp[0].sval)))) );
		(yyval.sym) = _symbol_create_list( SQL_SET, l); }
#line 6464 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 787 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  sql_subtype t;
		sql_find_subtype(&t, "char", UTF8_strlen((yyvsp[0].sval)), 0);
		append_string(l, sa_strdup(SA, "current_role"));
		append_symbol(l,
			_newAtomNode( _atom_string(&t, sql2str((yyvsp[0].sval)))) );
		(yyval.sym) = _symbol_create_list( SQL_SET, l); }
#line 6476 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 795 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		append_string(l, sa_strdup(SA, "current_timezone"));
		append_symbol(l, _symbol_create_list( SQL_OP, append_list(L(),
			append_string( L(), sa_strdup(SA, "local_timezone")))));
		(yyval.sym) = _symbol_create_list( SQL_SET, l); }
#line 6486 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 801 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		append_string(l, sa_strdup(SA, "current_timezone"));
		append_symbol(l, (yyvsp[0].sym) );
		(yyval.sym) = _symbol_create_list( SQL_SET, l); }
#line 6495 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 810 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		append_list(l, (yyvsp[-3].l));
		append_symbol(l, (yyvsp[-2].sym));
		append_symbol(l, (yyvsp[-1].sym));
		append_list(l, (yyvsp[0].l));
		(yyval.sym) = _symbol_create_list( SQL_CREATE_SCHEMA, l); }
#line 6506 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 817 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		append_list(l, (yyvsp[-1].l));
		append_int(l, (yyvsp[0].i_val));
		(yyval.sym) = _symbol_create_list( SQL_DROP_SCHEMA, l); }
#line 6515 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 825 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = L();
	  append_string((yyval.l), (yyvsp[0].sval) );
	  append_string((yyval.l), NULL ); }
#line 6523 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 829 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = L();
	  append_string((yyval.l), NULL );
	  append_string((yyval.l), (yyvsp[0].sval) ); }
#line 6531 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 833 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = L();
	  append_string((yyval.l), (yyvsp[-2].sval) );
	  append_string((yyval.l), (yyvsp[0].sval) ); }
#line 6539 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 842 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 6545 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 843 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create( SQL_CHARSET, (yyvsp[0].sval) ); }
#line 6551 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 847 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = L(); }
#line 6557 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 852 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 6563 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 854 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol( (yyvsp[-1].l), (yyvsp[0].sym) ); }
#line 6569 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 860 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = cur_user; }
#line 6575 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 861 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = (yyvsp[0].i_val); }
#line 6581 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 865 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = cur_user; }
#line 6587 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 866 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = cur_role; }
#line 6593 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 871 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-4].l));
	  append_list(l, (yyvsp[-2].l));
	  append_int(l, (yyvsp[-1].bval));
	  append_int(l, (yyvsp[0].i_val));
	(yyval.sym) = _symbol_create_list( SQL_GRANT, l);
	}
#line 6605 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 881 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-4].l));
	  append_list(l, (yyvsp[-2].l));
	  append_int(l, (yyvsp[-1].bval));
	  append_int(l, (yyvsp[0].i_val));
	(yyval.sym) = _symbol_create_list( SQL_GRANT_ROLES, l); }
#line 6616 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 890 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string(L(), (yyvsp[0].sval)); }
#line 6622 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 892 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string((yyvsp[-2].l), (yyvsp[0].sval)); }
#line 6628 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 896 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = 0; }
#line 6634 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 897 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = 1; }
#line 6640 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 901 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = 0; }
#line 6646 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 902 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = 1; }
#line 6652 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 907 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = cur_user; }
#line 6658 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 908 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = (yyvsp[0].i_val); }
#line 6664 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 913 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-3].l));
	  append_list(l, (yyvsp[-1].l));
	  append_int(l, (yyvsp[-4].bval)); /* GRANT OPTION FOR */
	  append_int(l, 0);
	  append_int(l, (yyvsp[0].i_val));
	(yyval.sym) = _symbol_create_list( SQL_REVOKE, l); }
#line 6676 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 921 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-3].l));
	  append_list(l, (yyvsp[-1].l));
	  append_int(l, (yyvsp[-4].bval));
	  append_int(l, (yyvsp[0].i_val));
	(yyval.sym) = _symbol_create_list( SQL_REVOKE_ROLES, l); }
#line 6687 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 930 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = 0; }
#line 6693 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 931 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = 1; }
#line 6699 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 935 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = 0; }
#line 6705 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 936 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = 1; }
#line 6711 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 941 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = L();
	  append_list((yyval.l), (yyvsp[-2].l));
	  append_symbol((yyval.l), (yyvsp[0].sym)); }
#line 6719 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 947 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_TABLE, (yyvsp[0].l)); }
#line 6725 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 948 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_NAME, (yyvsp[0].l)); }
#line 6731 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 960 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = NULL; }
#line 6737 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 961 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = NULL; }
#line 6743 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 966 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 6749 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 968 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol((yyvsp[-2].l), (yyvsp[0].sym)); }
#line 6755 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 972 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create(SQL_INSERT,NULL); }
#line 6761 "y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 973 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create(SQL_DELETE,NULL); }
#line 6767 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 974 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_UPDATE,(yyvsp[0].l)); }
#line 6773 "y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 975 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_SELECT,(yyvsp[0].l)); }
#line 6779 "y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 976 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_SELECT,(yyvsp[0].l)); }
#line 6785 "y.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 977 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create(SQL_EXECUTE,NULL); }
#line 6791 "y.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 981 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string(L(), (yyvsp[0].sval)); }
#line 6797 "y.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 983 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string((yyvsp[-2].l), (yyvsp[0].sval)); }
#line 6803 "y.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 987 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = NULL; }
#line 6809 "y.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 988 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 6815 "y.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 996 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-3].l));
	  append_symbol(l, (yyvsp[0].sym));
	  (yyval.sym) = _symbol_create_list( SQL_ALTER_TABLE, l ); }
#line 6824 "y.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 1001 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-3].l));
	  append_symbol(l, _symbol_create_list( SQL_TABLE, (yyvsp[0].l)));
	  (yyval.sym) = _symbol_create_list( SQL_ALTER_TABLE, l ); }
#line 6833 "y.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 1006 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-2].l));
	  append_symbol(l, (yyvsp[0].sym));
	  (yyval.sym) = _symbol_create_list( SQL_ALTER_TABLE, l ); }
#line 6842 "y.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 1011 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-2].l));
	  append_symbol(l, (yyvsp[0].sym));
	  (yyval.sym) = _symbol_create_list( SQL_ALTER_TABLE, l ); }
#line 6851 "y.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 1016 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-3].l));
	  append_symbol(l, _symbol_create_int(SQL_ALTER_TABLE, tr_readonly));
	  (yyval.sym) = _symbol_create_list( SQL_ALTER_TABLE, l ); }
#line 6860 "y.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 1021 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-3].l));
	  append_symbol(l, _symbol_create_int(SQL_ALTER_TABLE, tr_append));
	  (yyval.sym) = _symbol_create_list( SQL_ALTER_TABLE, l ); }
#line 6869 "y.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 1026 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-3].l));
	  append_symbol(l, _symbol_create_int(SQL_ALTER_TABLE, tr_writable));
	  (yyval.sym) = _symbol_create_list( SQL_ALTER_TABLE, l ); }
#line 6878 "y.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 1031 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_string(l, (yyvsp[-1].sval));
	  append_list(l, (yyvsp[0].l));
	  (yyval.sym) = _symbol_create_list( SQL_ALTER_USER, l ); }
#line 6887 "y.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 1036 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_string(l, (yyvsp[-3].sval));
	  append_string(l, (yyvsp[0].sval));
	  (yyval.sym) = _symbol_create_list( SQL_RENAME_USER, l ); }
#line 6896 "y.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 1041 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  dlist *p = L();
	  append_string(l, NULL);
	  append_string(p, (yyvsp[-4].sval));
	  append_string(p, NULL);
	  append_int(p, (yyvsp[-6].i_val));
	  append_string(p, (yyvsp[0].sval));
	  append_list(l, p);
	  (yyval.sym) = _symbol_create_list( SQL_ALTER_USER, l ); }
#line 6910 "y.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 1053 "sql_parser.y" /* yacc.c:1646  */
    { dlist * l = L();
				  append_string(l, (yyvsp[0].sval));
				  append_string(l, NULL);
				  append_int(l, (yyvsp[-2].i_val));
				  append_string(l, NULL);
				  (yyval.l) = l; }
#line 6921 "y.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 1059 "sql_parser.y" /* yacc.c:1646  */
    { dlist * l = L();
				  append_string(l, NULL);
				  append_string(l, (yyvsp[0].sval));
				  append_int(l, 0);
				  append_string(l, NULL);
				  (yyval.l) = l; }
#line 6932 "y.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 1066 "sql_parser.y" /* yacc.c:1646  */
    { dlist * l = L();
				  append_string(l, (yyvsp[-3].sval));
				  append_string(l, (yyvsp[0].sval));
				  append_int(l, (yyvsp[-5].i_val));
				  append_string(l, NULL);
				  (yyval.l) = l; }
#line 6943 "y.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 1076 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_string(l, (yyvsp[-3].sval));
	  append_symbol(l, (yyvsp[0].sym));
	  (yyval.sym) = _symbol_create_list( SQL_DEFAULT, l); }
#line 6952 "y.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 1081 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_string(l, (yyvsp[-2].sval));
	  (yyval.sym) = _symbol_create_list( SQL_NULL, l); }
#line 6960 "y.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 1085 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_string(l, (yyvsp[-3].sval));
	  (yyval.sym) = _symbol_create_list( SQL_NOT_NULL, l); }
#line 6968 "y.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 1089 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create( SQL_DROP_DEFAULT, (yyvsp[-2].sval)); }
#line 6974 "y.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 1091 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_string(l, (yyvsp[-3].sval));
	  if (!strlen((yyvsp[0].sval)))
	  	append_string(l, NULL);
	  else
	  	append_string(l, (yyvsp[0].sval));
	  (yyval.sym) = _symbol_create_list( SQL_STORAGE, l); }
#line 6986 "y.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 1099 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_string(l, (yyvsp[-3].sval));
	  append_string(l, NULL);
	  (yyval.sym) = _symbol_create_list( SQL_STORAGE, l); }
#line 6995 "y.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 1107 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_string(l, (yyvsp[-1].sval) );
	  append_int(l, (yyvsp[0].i_val) );
	  (yyval.sym) = _symbol_create_list( SQL_DROP_COLUMN, l ); }
#line 7004 "y.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 1112 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_string(l, (yyvsp[-1].sval) );
	  append_int(l, (yyvsp[0].i_val) );
	  (yyval.sym) = _symbol_create_list( SQL_DROP_CONSTRAINT, l ); }
#line 7013 "y.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 1117 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_string(l, (yyvsp[-1].sval) );
	  append_int(l, (yyvsp[0].i_val) );
	  (yyval.sym) = _symbol_create_list( SQL_DROP_TABLE, l ); }
#line 7022 "y.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 1124 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 7028 "y.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 1125 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 7034 "y.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 1129 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 7040 "y.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 1130 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 7046 "y.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 1131 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 7052 "y.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 1154 "sql_parser.y" /* yacc.c:1646  */
    {
		dlist *l = L();
		append_list(l, (yyvsp[-3].l));
		append_type(l, &(yyvsp[-1].type));
		append_list(l, (yyvsp[0].l));
		(yyval.sym) = _symbol_create_list(SQL_CREATE_SEQ, l);
	}
#line 7064 "y.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 1165 "sql_parser.y" /* yacc.c:1646  */
    {
		dlist *l = L();
		append_list(l, (yyvsp[0].l));
		(yyval.sym) = _symbol_create_list(SQL_DROP_SEQ, l);
	}
#line 7074 "y.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 1181 "sql_parser.y" /* yacc.c:1646  */
    {
		dlist *l = L();
		append_list(l, (yyvsp[-1].l));
		append_type(l, NULL);
		append_list(l, (yyvsp[0].l));
		(yyval.sym) = _symbol_create_list(SQL_ALTER_SEQ, l);
	}
#line 7086 "y.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 1197 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_lng(l, (yyvsp[-5].l_val));
	  append_lng(l, (yyvsp[-4].l_val));
	  append_lng(l, (yyvsp[-3].l_val));
	  append_lng(l, (yyvsp[-2].l_val));
	  append_lng(l, (yyvsp[-1].l_val));
	  append_int(l, (yyvsp[0].i_val));
	  append_int(l, 0);	/* bedropped */
	  (yyval.l) = l;
	}
#line 7101 "y.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 1216 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-5].l));
	  append_lng(l, (yyvsp[-4].l_val));
	  append_lng(l, (yyvsp[-3].l_val));
	  append_lng(l, (yyvsp[-2].l_val));
	  append_lng(l, (yyvsp[-1].l_val));
	  append_int(l, (yyvsp[0].i_val));
	  (yyval.l) = l;
	}
#line 7115 "y.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 1231 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l_val) = 1; }
#line 7121 "y.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 1232 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l_val) = (yyvsp[0].l_val); }
#line 7127 "y.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 1245 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_int(L(), -1); }
#line 7133 "y.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 1246 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_int(L(), 0); }
#line 7139 "y.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 1248 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_lng(append_int(L(), 2), (yyvsp[0].l_val)); }
#line 7145 "y.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 1250 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(append_int(L(), 1), (yyvsp[0].sym)); }
#line 7151 "y.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 1260 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l_val) = -1; }
#line 7157 "y.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 1261 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l_val) = (yyvsp[0].l_val); }
#line 7163 "y.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 1272 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l_val) = -1; }
#line 7169 "y.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 1273 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l_val) = (yyvsp[0].l_val); }
#line 7175 "y.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 1274 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l_val) =  0; }
#line 7181 "y.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 1285 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l_val) = -1; }
#line 7187 "y.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 1286 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l_val) = (yyvsp[0].l_val); }
#line 7193 "y.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 1287 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l_val) =  0; }
#line 7199 "y.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 1297 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l_val) = -1; }
#line 7205 "y.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 1298 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l_val) = (yyvsp[0].l_val); }
#line 7211 "y.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 1308 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 7217 "y.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 1309 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 1; }
#line 7223 "y.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 1310 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 7229 "y.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 1317 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_string(l, (yyvsp[-5].sval));
	  append_int(l, (yyvsp[-7].i_val));
	  append_list(l, (yyvsp[-3].l));
	  append_list(l, (yyvsp[-1].l));
	  (yyval.sym) = _symbol_create_list( SQL_CREATE_INDEX, l); }
#line 7240 "y.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 1326 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = hash_idx; }
#line 7246 "y.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 1327 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = hash_idx; }
#line 7252 "y.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 1348 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_string(l, (yyvsp[-1].sval));
	  append_int(l, (yyvsp[0].i_val));
	  (yyval.sym) = _symbol_create_list( SQL_CREATE_ROLE, l ); }
#line 7261 "y.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 1353 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_string(l, (yyvsp[-8].sval));
	  append_string(l, (yyvsp[-4].sval));
	  append_string(l, (yyvsp[-2].sval));
	  append_string(l, (yyvsp[0].sval));
	  append_int(l, (yyvsp[-6].i_val));
	  (yyval.sym) = _symbol_create_list( SQL_CREATE_USER, l ); }
#line 7273 "y.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 1363 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = SQL_PW_UNENCRYPTED; }
#line 7279 "y.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 1364 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = SQL_PW_UNENCRYPTED; }
#line 7285 "y.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 1365 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = SQL_PW_ENCRYPTED; }
#line 7291 "y.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 1370 "sql_parser.y" /* yacc.c:1646  */
    { int commit_action = CA_COMMIT;
	  dlist *l = L();

	  append_int(l, SQL_PERSIST);
	  append_list(l, (yyvsp[-1].l));
	  append_symbol(l, (yyvsp[0].sym));
	  append_int(l, commit_action);
	  append_string(l, NULL);
	  (yyval.sym) = _symbol_create_list( SQL_CREATE_TABLE, l ); }
#line 7305 "y.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 1380 "sql_parser.y" /* yacc.c:1646  */
    { int commit_action = CA_COMMIT, tpe = SQL_STREAM;
	  dlist *l = L();

	  append_int(l, tpe);
	  append_list(l, (yyvsp[-1].l));
	  append_symbol(l, (yyvsp[0].sym));
	  append_int(l, commit_action);
	  append_string(l, NULL);
	  (yyval.sym) = _symbol_create_list( SQL_CREATE_TABLE, l ); }
#line 7319 "y.tab.c" /* yacc.c:1646  */
    break;

  case 168:
#line 1390 "sql_parser.y" /* yacc.c:1646  */
    { int commit_action = CA_COMMIT, tpe = SQL_MERGE_TABLE;
	  dlist *l = L();

	  append_int(l, tpe);
	  append_list(l, (yyvsp[-1].l));
	  append_symbol(l, (yyvsp[0].sym));
	  append_int(l, commit_action);
	  append_string(l, NULL);
	  (yyval.sym) = _symbol_create_list( SQL_CREATE_TABLE, l ); }
#line 7333 "y.tab.c" /* yacc.c:1646  */
    break;

  case 169:
#line 1400 "sql_parser.y" /* yacc.c:1646  */
    { int commit_action = CA_COMMIT, tpe = SQL_REPLICA_TABLE;
	  dlist *l = L();

	  append_int(l, tpe);
	  append_list(l, (yyvsp[-1].l));
	  append_symbol(l, (yyvsp[0].sym));
	  append_int(l, commit_action);
	  append_string(l, NULL);
	  (yyval.sym) = _symbol_create_list( SQL_CREATE_TABLE, l ); }
#line 7347 "y.tab.c" /* yacc.c:1646  */
    break;

  case 170:
#line 1411 "sql_parser.y" /* yacc.c:1646  */
    { int commit_action = CA_COMMIT, tpe = SQL_REMOTE;
	  dlist *l = L();

	  append_int(l, tpe);
	  append_list(l, (yyvsp[-3].l));
	  append_symbol(l, (yyvsp[-2].sym));
	  append_int(l, commit_action);
	  append_string(l, (yyvsp[0].sval));
	  (yyval.sym) = _symbol_create_list( SQL_CREATE_TABLE, l ); }
#line 7361 "y.tab.c" /* yacc.c:1646  */
    break;

  case 171:
#line 1421 "sql_parser.y" /* yacc.c:1646  */
    { int commit_action = CA_COMMIT;
	  dlist *l = L();

	  append_int(l, (yyvsp[-4].i_val));
	  append_list(l, (yyvsp[-2].l));
	  append_symbol(l, (yyvsp[-1].sym));
	  if ((yyvsp[-4].i_val) != SQL_PERSIST)
		commit_action = (yyvsp[0].i_val);
	  append_int(l, commit_action);
	  append_string(l, NULL);
	  (yyval.sym) = _symbol_create_list( SQL_CREATE_TABLE, l ); }
#line 7377 "y.tab.c" /* yacc.c:1646  */
    break;

  case 172:
#line 1435 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = SQL_LOCAL_TEMP; }
#line 7383 "y.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 1436 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = SQL_LOCAL_TEMP; }
#line 7389 "y.tab.c" /* yacc.c:1646  */
    break;

  case 174:
#line 1437 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = SQL_LOCAL_TEMP; }
#line 7395 "y.tab.c" /* yacc.c:1646  */
    break;

  case 175:
#line 1438 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = SQL_LOCAL_TEMP; }
#line 7401 "y.tab.c" /* yacc.c:1646  */
    break;

  case 176:
#line 1439 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = SQL_GLOBAL_TEMP; }
#line 7407 "y.tab.c" /* yacc.c:1646  */
    break;

  case 177:
#line 1440 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = SQL_GLOBAL_TEMP; }
#line 7413 "y.tab.c" /* yacc.c:1646  */
    break;

  case 178:
#line 1444 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = CA_COMMIT; }
#line 7419 "y.tab.c" /* yacc.c:1646  */
    break;

  case 179:
#line 1445 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = CA_DELETE; }
#line 7425 "y.tab.c" /* yacc.c:1646  */
    break;

  case 180:
#line 1446 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = CA_PRESERVE; }
#line 7431 "y.tab.c" /* yacc.c:1646  */
    break;

  case 181:
#line 1447 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = CA_DROP; }
#line 7437 "y.tab.c" /* yacc.c:1646  */
    break;

  case 182:
#line 1451 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_CREATE_TABLE, (yyvsp[-1].l)); }
#line 7443 "y.tab.c" /* yacc.c:1646  */
    break;

  case 183:
#line 1452 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_SELECT, (yyvsp[0].l)); }
#line 7449 "y.tab.c" /* yacc.c:1646  */
    break;

  case 184:
#line 1460 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_list(L(), (yyvsp[-3].l));
			  append_symbol((yyval.l), (yyvsp[-1].sym)); 
			  append_int((yyval.l), (yyvsp[0].i_val)); }
#line 7457 "y.tab.c" /* yacc.c:1646  */
    break;

  case 185:
#line 1466 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 7463 "y.tab.c" /* yacc.c:1646  */
    break;

  case 186:
#line 1467 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 1; }
#line 7469 "y.tab.c" /* yacc.c:1646  */
    break;

  case 187:
#line 1472 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 7475 "y.tab.c" /* yacc.c:1646  */
    break;

  case 188:
#line 1474 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol( (yyvsp[-2].l), (yyvsp[0].sym) ); }
#line 7481 "y.tab.c" /* yacc.c:1646  */
    break;

  case 194:
#line 1481 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 7487 "y.tab.c" /* yacc.c:1646  */
    break;

  case 195:
#line 1482 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 1; }
#line 7493 "y.tab.c" /* yacc.c:1646  */
    break;

  case 196:
#line 1487 "sql_parser.y" /* yacc.c:1646  */
    {
			dlist *l = L();
			append_string(l, (yyvsp[-2].sval));
			append_type(l, &(yyvsp[-1].type));
			append_list(l, (yyvsp[0].l));
			(yyval.sym) = _symbol_create_list(SQL_COLUMN, l);
		}
#line 7505 "y.tab.c" /* yacc.c:1646  */
    break;

  case 197:
#line 1495 "sql_parser.y" /* yacc.c:1646  */
    { /* SERIAL = INTEGER GENERATED ALWAYS AS IDENTITY PRIMARY KEY */
			/* handle multi-statements by wrapping them in a list */
			sql_subtype it;
			dlist* stmts;
			/* note: sql_next_seq_name uses sa_alloc */
			str sn = sql_next_seq_name(m);
			dlist *p; /* primary key */
			/* sequence generation code */
			dlist *l = L();
			/* finally all the options */
			dlist *o = L();

			/* the name of the sequence */
			dlist *seqn1 = L(), *seqn2 = L();

			if (m->scanner.schema)
				append_string(seqn1, m->scanner.schema);
			append_list(l, append_string(seqn1, sn));
			/* ultra dirty: inline 'integer' type generation */
			if ((yyvsp[0].i_val) == 1)
				sql_find_subtype(&it, "bigint", 64, 0);
			else
				sql_find_subtype(&it, "int", 32, 0);
			append_type(l, &it);
			/* finally all the options (no defaults here) */
			append_lng(o, 1); /* start */
			append_lng(o, 1); /* increment */
			append_lng(o, 1); /* min */
			append_lng(o, 0); /* max */
			append_lng(o, 1); /* cache */
			append_int(o, 0); /* cycle */
			append_int(o, 1); /* bedropped */
			append_list(l, o);

			if (m->sym) {
				stmts = m->sym->data.lval;
			} else {
				stmts = L();
				m->sym = _symbol_create_list(SQL_MULSTMT, stmts);
			}	
			append_symbol(stmts, _symbol_create_list(SQL_CREATE_SEQ, l));

			l = L();
			append_string(l, (yyvsp[-1].sval));
			append_type(l, &it);
			o = L();
			if (m->scanner.schema)
				append_string(seqn2, m->scanner.schema);
			append_string(seqn2, sn);
			append_symbol(o, _symbol_create_symbol(SQL_DEFAULT, _symbol_create_list(SQL_NEXT, seqn2)));
			p = L();
			append_string(p, NULL);
			append_symbol(p, _symbol_create(SQL_PRIMARY_KEY, NULL));
			append_symbol(o, _symbol_create_list(SQL_CONSTRAINT, p));
			append_list(l, o);
			(yyval.sym) = _symbol_create_list(SQL_COLUMN, l);
		}
#line 7567 "y.tab.c" /* yacc.c:1646  */
    break;

  case 198:
#line 1555 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = NULL; }
#line 7573 "y.tab.c" /* yacc.c:1646  */
    break;

  case 200:
#line 1561 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[0].sym) ); }
#line 7579 "y.tab.c" /* yacc.c:1646  */
    break;

  case 201:
#line 1563 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol( (yyvsp[-1].l), (yyvsp[0].sym) ); }
#line 7585 "y.tab.c" /* yacc.c:1646  */
    break;

  case 202:
#line 1569 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_string(l, (yyvsp[-5].sval) );
	  append_list(l, (yyvsp[-1].l) );
	  (yyval.sym) = _symbol_create_list( SQL_COLUMN_OPTIONS, l ); }
#line 7594 "y.tab.c" /* yacc.c:1646  */
    break;

  case 203:
#line 1577 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[0].sym) ); }
#line 7600 "y.tab.c" /* yacc.c:1646  */
    break;

  case 204:
#line 1579 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol((yyvsp[-2].l), (yyvsp[0].sym) ); }
#line 7606 "y.tab.c" /* yacc.c:1646  */
    break;

  case 208:
#line 1585 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_symbol(SQL_DEFAULT, (yyvsp[0].sym)); }
#line 7612 "y.tab.c" /* yacc.c:1646  */
    break;

  case 209:
#line 1589 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 7618 "y.tab.c" /* yacc.c:1646  */
    break;

  case 210:
#line 1595 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_string(l, (yyvsp[-1].sval) );
	  append_symbol(l, (yyvsp[0].sym) );
	  (yyval.sym) = _symbol_create_list( SQL_CONSTRAINT, l ); }
#line 7627 "y.tab.c" /* yacc.c:1646  */
    break;

  case 211:
#line 1603 "sql_parser.y" /* yacc.c:1646  */
    {
		/* handle multi-statements by wrapping them in a list */
		sql_subtype it;
		dlist* stmts;
		/* note: sql_next_seq_name uses sa_alloc */
		str sn = sql_next_seq_name(m);
		/* sequence generation code */
		dlist *l = L();
		/* the name of the sequence */
		append_list(l, append_string(L(), sn));
		/* ultra dirty: inline 'integer' type generation */
		sql_find_subtype(&it, "int", 32, 0);
		append_type(l, &it);

		/* finally all the options */
		append_list(l, (yyvsp[0].l));
		(yyval.sym) = _symbol_create_symbol(SQL_DEFAULT, _symbol_create_list(SQL_NEXT, append_string(L(), sn)));

		if (m->sym) {
			stmts = m->sym->data.lval;
		} else {
			stmts = L();
			m->sym = _symbol_create_list(SQL_MULSTMT, stmts);
		}	
		append_symbol(stmts, _symbol_create_list(SQL_CREATE_SEQ, l));
	}
#line 7658 "y.tab.c" /* yacc.c:1646  */
    break;

  case 212:
#line 1630 "sql_parser.y" /* yacc.c:1646  */
    {
		/* handle multi-statements by wrapping them in a list */
		sql_subtype it;
		dlist* stmts;
		/* note: sql_next_seq_name uses sa_alloc */
		str sn = sql_next_seq_name(m);
		/* sequence generation code */
		dlist *l = L();
		/* finally all the options */
		dlist *o = L();

		/* the name of the sequence */
		dlist *seqn1 = L(), *seqn2 = L();

		if (m->scanner.schema)
			append_string(seqn1, m->scanner.schema);
		append_list(l, append_string(seqn1, sn));
		/* ultra dirty: inline 'integer' type generation */
		sql_find_subtype(&it, "int", 32, 0);
		append_type(l, &it);
		/* finally all the options (no defaults here) */
		append_lng(o, 1); /* start */
		append_lng(o, 1); /* increment */
		append_lng(o, 1); /* min */
		append_lng(o, 0); /* max */
		append_lng(o, 1); /* cache */
		append_int(o, 0); /* cycle */
		append_int(o, 0); /* bedropped */
		append_list(l, o);
		if (m->scanner.schema)
			append_string(seqn2, m->scanner.schema);
		append_string(seqn2, sn);
		(yyval.sym) = _symbol_create_symbol(SQL_DEFAULT, _symbol_create_list(SQL_NEXT, seqn2));

		if (m->sym) {
			stmts = m->sym->data.lval;
		} else {
			stmts = L();
			m->sym = _symbol_create_list(SQL_MULSTMT, stmts);
		}	
		append_symbol(stmts, _symbol_create_list(SQL_CREATE_SEQ, l));
	}
#line 7705 "y.tab.c" /* yacc.c:1646  */
    break;

  case 213:
#line 1676 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = L();
	  /* finally all the options (no defaults here) */
	  append_lng((yyval.l), 1); /* start */
	  append_lng((yyval.l), -1); /* increment */
	  append_lng((yyval.l), -1); /* min */
	  append_lng((yyval.l), -1); /* max */
	  append_lng((yyval.l), -1); /* cache */
	  append_int((yyval.l), 0);  /* cycle */
	  append_int((yyval.l), 0);  /* bedropped */
	}
#line 7720 "y.tab.c" /* yacc.c:1646  */
    break;

  case 214:
#line 1686 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = (yyvsp[-1].l); }
#line 7726 "y.tab.c" /* yacc.c:1646  */
    break;

  case 215:
#line 1693 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_string(l, (yyvsp[-1].sval) );
	  append_symbol(l, (yyvsp[0].sym) );
	  (yyval.sym) = _symbol_create_list( SQL_CONSTRAINT, l ); }
#line 7735 "y.tab.c" /* yacc.c:1646  */
    break;

  case 216:
#line 1702 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = NULL; }
#line 7741 "y.tab.c" /* yacc.c:1646  */
    break;

  case 217:
#line 1703 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 7747 "y.tab.c" /* yacc.c:1646  */
    break;

  case 218:
#line 1707 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 7753 "y.tab.c" /* yacc.c:1646  */
    break;

  case 219:
#line 1708 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 1; }
#line 7759 "y.tab.c" /* yacc.c:1646  */
    break;

  case 220:
#line 1709 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 2; }
#line 7765 "y.tab.c" /* yacc.c:1646  */
    break;

  case 221:
#line 1710 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 3; }
#line 7771 "y.tab.c" /* yacc.c:1646  */
    break;

  case 222:
#line 1711 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 4; }
#line 7777 "y.tab.c" /* yacc.c:1646  */
    break;

  case 223:
#line 1715 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = ((yyvsp[0].i_val) << 8); }
#line 7783 "y.tab.c" /* yacc.c:1646  */
    break;

  case 224:
#line 1719 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = (yyvsp[0].i_val); }
#line 7789 "y.tab.c" /* yacc.c:1646  */
    break;

  case 225:
#line 1723 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = (2 << 8) + 2; /* defaults are RESTRICT */ }
#line 7795 "y.tab.c" /* yacc.c:1646  */
    break;

  case 226:
#line 1724 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = (yyvsp[0].i_val); }
#line 7801 "y.tab.c" /* yacc.c:1646  */
    break;

  case 227:
#line 1725 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = (yyvsp[0].i_val); }
#line 7807 "y.tab.c" /* yacc.c:1646  */
    break;

  case 228:
#line 1726 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = (yyvsp[-1].i_val) + (yyvsp[0].i_val); }
#line 7813 "y.tab.c" /* yacc.c:1646  */
    break;

  case 229:
#line 1727 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = (yyvsp[-1].i_val) + (yyvsp[0].i_val); }
#line 7819 "y.tab.c" /* yacc.c:1646  */
    break;

  case 230:
#line 1731 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 7825 "y.tab.c" /* yacc.c:1646  */
    break;

  case 231:
#line 1732 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 1; }
#line 7831 "y.tab.c" /* yacc.c:1646  */
    break;

  case 232:
#line 1733 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 2; }
#line 7837 "y.tab.c" /* yacc.c:1646  */
    break;

  case 233:
#line 1734 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 7843 "y.tab.c" /* yacc.c:1646  */
    break;

  case 234:
#line 1738 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 7849 "y.tab.c" /* yacc.c:1646  */
    break;

  case 235:
#line 1739 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = (yyvsp[0].i_val); }
#line 7855 "y.tab.c" /* yacc.c:1646  */
    break;

  case 236:
#line 1743 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create( SQL_NOT_NULL, NULL); }
#line 7861 "y.tab.c" /* yacc.c:1646  */
    break;

  case 237:
#line 1744 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create( SQL_NULL, NULL); }
#line 7867 "y.tab.c" /* yacc.c:1646  */
    break;

  case 238:
#line 1745 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create( SQL_UNIQUE, NULL ); }
#line 7873 "y.tab.c" /* yacc.c:1646  */
    break;

  case 239:
#line 1746 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create( SQL_PRIMARY_KEY, NULL ); }
#line 7879 "y.tab.c" /* yacc.c:1646  */
    break;

  case 240:
#line 1749 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l, (yyvsp[-3].l) );
			  append_list(l, (yyvsp[-2].l) );
			  append_int(l, (yyvsp[-1].i_val) );
			  append_int(l, (yyvsp[0].i_val) );
			  (yyval.sym) = _symbol_create_list( SQL_FOREIGN_KEY, l); }
#line 7890 "y.tab.c" /* yacc.c:1646  */
    break;

  case 242:
#line 1762 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_UNIQUE, (yyvsp[0].l)); }
#line 7896 "y.tab.c" /* yacc.c:1646  */
    break;

  case 243:
#line 1764 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_PRIMARY_KEY, (yyvsp[0].l)); }
#line 7902 "y.tab.c" /* yacc.c:1646  */
    break;

  case 244:
#line 1768 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l, (yyvsp[-3].l) );
			  append_list(l, (yyvsp[-5].l) );
			  append_list(l, (yyvsp[-2].l) );
			  append_int(l, (yyvsp[-1].i_val) );
			  append_int(l, (yyvsp[0].i_val) );
			  (yyval.sym) = _symbol_create_list( SQL_FOREIGN_KEY, l); }
#line 7914 "y.tab.c" /* yacc.c:1646  */
    break;

  case 245:
#line 1780 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 7920 "y.tab.c" /* yacc.c:1646  */
    break;

  case 246:
#line 1785 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string(L(), (yyvsp[0].sval)); }
#line 7926 "y.tab.c" /* yacc.c:1646  */
    break;

  case 247:
#line 1787 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string( (yyvsp[-2].l), (yyvsp[0].sval) ); }
#line 7932 "y.tab.c" /* yacc.c:1646  */
    break;

  case 248:
#line 1791 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_LIKE, (yyvsp[0].l) ); }
#line 7938 "y.tab.c" /* yacc.c:1646  */
    break;

  case 249:
#line 1796 "sql_parser.y" /* yacc.c:1646  */
    {  dlist *l = L();
	  append_list(l, (yyvsp[-4].l));
	  append_list(l, (yyvsp[-3].l));
	  append_symbol(l, (yyvsp[-1].sym));
	  append_int(l, (yyvsp[0].bval));
	  append_int(l, TRUE);	/* persistent view */
	  (yyval.sym) = _symbol_create_list( SQL_CREATE_VIEW, l ); 
	}
#line 7951 "y.tab.c" /* yacc.c:1646  */
    break;

  case 252:
#line 1812 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = FALSE; }
#line 7957 "y.tab.c" /* yacc.c:1646  */
    break;

  case 253:
#line 1813 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = TRUE; }
#line 7963 "y.tab.c" /* yacc.c:1646  */
    break;

  case 254:
#line 1817 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = NULL; }
#line 7969 "y.tab.c" /* yacc.c:1646  */
    break;

  case 256:
#line 1822 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = (yyvsp[-1].l); }
#line 7975 "y.tab.c" /* yacc.c:1646  */
    break;

  case 257:
#line 1827 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
				append_string(l, (yyvsp[-3].sval));
				append_string(l, (yyvsp[0].sval));
			  (yyval.sym) = _symbol_create_list( SQL_CREATE_TYPE, l ); }
#line 7984 "y.tab.c" /* yacc.c:1646  */
    break;

  case 258:
#line 1834 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string(append_string(L(), (yyvsp[-2].sval)), (yyvsp[0].sval)); }
#line 7990 "y.tab.c" /* yacc.c:1646  */
    break;

  case 259:
#line 1842 "sql_parser.y" /* yacc.c:1646  */
    { dlist *f = L();
				append_list(f, (yyvsp[-8].l));
				append_list(f, (yyvsp[-6].l));
				append_symbol(f, (yyvsp[-3].sym));
				append_list(f, (yyvsp[0].l));
				append_list(f, NULL);
				append_int(f, F_FUNC);
				append_int(f, FUNC_LANG_MAL);
			  (yyval.sym) = _symbol_create_list( SQL_CREATE_FUNC, f ); }
#line 8004 "y.tab.c" /* yacc.c:1646  */
    break;

  case 260:
#line 1855 "sql_parser.y" /* yacc.c:1646  */
    { dlist *f = L();
				append_list(f, (yyvsp[-6].l));
				append_list(f, (yyvsp[-4].l));
				append_symbol(f, (yyvsp[-1].sym));
				append_list(f, NULL);
				append_list(f, (yyvsp[0].l));
				append_int(f, F_FUNC);
				append_int(f, FUNC_LANG_SQL);
			  (yyval.sym) = _symbol_create_list( SQL_CREATE_FUNC, f ); }
#line 8018 "y.tab.c" /* yacc.c:1646  */
    break;

  case 261:
#line 1867 "sql_parser.y" /* yacc.c:1646  */
    { 
			int lang = 0;
			dlist *f = L();
			char l = *(yyvsp[-1].sval);

			if (l == 'R' || l == 'r')
				lang = FUNC_LANG_R;
			else if (l == 'C' || l == 'c')
				lang = FUNC_LANG_C;
			else if (l == 'J' || l == 'j')
				lang = FUNC_LANG_J;
			else
				yyerror(m, sql_message("Language name R, C, or J(avascript):expected, received '%c'", l));

			append_list(f, (yyvsp[-8].l));
			append_list(f, (yyvsp[-6].l));
			append_symbol(f, (yyvsp[-3].sym));
			append_list(f, NULL); 
			append_list(f, append_string(L(), (yyvsp[0].sval)));
			append_int(f, F_FUNC);
			append_int(f, lang);
			(yyval.sym) = _symbol_create_list( SQL_CREATE_FUNC, f ); }
#line 8045 "y.tab.c" /* yacc.c:1646  */
    break;

  case 262:
#line 1892 "sql_parser.y" /* yacc.c:1646  */
    { dlist *f = L();
				append_list(f, (yyvsp[-6].l));
				append_list(f, (yyvsp[-4].l)); 
				/* no returns - use OID */
				append_symbol(f, NULL); 
				append_list(f, (yyvsp[0].l));
				append_list(f, NULL);
				append_int(f, F_FILT);
				append_int(f, FUNC_LANG_MAL);
			  (yyval.sym) = _symbol_create_list( SQL_CREATE_FUNC, f ); }
#line 8060 "y.tab.c" /* yacc.c:1646  */
    break;

  case 263:
#line 1906 "sql_parser.y" /* yacc.c:1646  */
    { dlist *f = L();
				append_list(f, (yyvsp[-8].l));
				append_list(f, (yyvsp[-6].l));
				append_symbol(f, (yyvsp[-3].sym));
				append_list(f, (yyvsp[0].l));
				append_list(f, NULL);
				append_int(f, F_AGGR);
				append_int(f, FUNC_LANG_MAL);
			  (yyval.sym) = _symbol_create_list( SQL_CREATE_FUNC, f ); }
#line 8074 "y.tab.c" /* yacc.c:1646  */
    break;

  case 264:
#line 1918 "sql_parser.y" /* yacc.c:1646  */
    { 
			int lang = 0;
			dlist *f = L();
			char l = *(yyvsp[-1].sval);

			if (l == 'R' || l == 'r')
				lang = FUNC_LANG_R;
			else if (l == 'C' || l == 'c')
				lang = FUNC_LANG_C;
			else if (l == 'J' || l == 'j')
				lang = FUNC_LANG_J;
			else
				yyerror(m, sql_message("Language name R, C, or J(avascript):expected, received '%c'", l));

			append_list(f, (yyvsp[-8].l));
			append_list(f, (yyvsp[-6].l));
			append_symbol(f, (yyvsp[-3].sym));
			append_list(f, NULL);
			append_list(f, append_string(L(), (yyvsp[0].sval)));
			append_int(f, F_AGGR);
			append_int(f, lang);
			(yyval.sym) = _symbol_create_list( SQL_CREATE_FUNC, f ); }
#line 8101 "y.tab.c" /* yacc.c:1646  */
    break;

  case 265:
#line 1944 "sql_parser.y" /* yacc.c:1646  */
    { dlist *f = L();
				append_list(f, (yyvsp[-6].l));
				append_list(f, (yyvsp[-4].l));
				append_symbol(f, NULL); /* no result */
				append_list(f, (yyvsp[0].l));
				append_list(f, NULL);
				append_int(f, F_PROC);
				append_int(f, FUNC_LANG_MAL);
			  (yyval.sym) = _symbol_create_list( SQL_CREATE_FUNC, f ); }
#line 8115 "y.tab.c" /* yacc.c:1646  */
    break;

  case 266:
#line 1956 "sql_parser.y" /* yacc.c:1646  */
    { dlist *f = L();
				append_list(f, (yyvsp[-4].l));
				append_list(f, (yyvsp[-2].l));
				append_symbol(f, NULL); /* no result */
				append_list(f, NULL); 
				append_list(f, (yyvsp[0].l));
				append_int(f, F_PROC);
				append_int(f, FUNC_LANG_SQL);
			  (yyval.sym) = _symbol_create_list( SQL_CREATE_FUNC, f ); }
#line 8129 "y.tab.c" /* yacc.c:1646  */
    break;

  case 267:
#line 1969 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = L(); append_symbol( (yyval.l), (yyvsp[0].sym)); }
#line 8135 "y.tab.c" /* yacc.c:1646  */
    break;

  case 268:
#line 1973 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol((yyvsp[-3].l),(yyvsp[-2].sym)); }
#line 8141 "y.tab.c" /* yacc.c:1646  */
    break;

  case 269:
#line 1977 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol((yyvsp[-3].l),(yyvsp[-2].sym)); }
#line 8147 "y.tab.c" /* yacc.c:1646  */
    break;

  case 270:
#line 1992 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = L(); }
#line 8153 "y.tab.c" /* yacc.c:1646  */
    break;

  case 271:
#line 1994 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol((yyvsp[-2].l),(yyvsp[-1].sym));}
#line 8159 "y.tab.c" /* yacc.c:1646  */
    break;

  case 272:
#line 1998 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = L(); }
#line 8165 "y.tab.c" /* yacc.c:1646  */
    break;

  case 273:
#line 2000 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol((yyvsp[-2].l),(yyvsp[-1].sym));}
#line 8171 "y.tab.c" /* yacc.c:1646  */
    break;

  case 300:
#line 2048 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 8177 "y.tab.c" /* yacc.c:1646  */
    break;

  case 301:
#line 2052 "sql_parser.y" /* yacc.c:1646  */
    {(yyval.sym) = _symbol_create_symbol(SQL_CALL, (yyvsp[0].sym));}
#line 8183 "y.tab.c" /* yacc.c:1646  */
    break;

  case 302:
#line 2057 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L(); 
		  append_list( l, (yyvsp[-3].l));
		  append_list( l, (yyvsp[-1].l));
		  assert(0);
		  (yyval.sym) = _symbol_create_list( SQL_FUNC, l);
		}
#line 8194 "y.tab.c" /* yacc.c:1646  */
    break;

  case 304:
#line 2068 "sql_parser.y" /* yacc.c:1646  */
    {(yyval.l) = L();}
#line 8200 "y.tab.c" /* yacc.c:1646  */
    break;

  case 305:
#line 2069 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol( L(), (yyvsp[0].sym)); }
#line 8206 "y.tab.c" /* yacc.c:1646  */
    break;

  case 306:
#line 2071 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol( (yyvsp[-2].l), (yyvsp[0].sym)); }
#line 8212 "y.tab.c" /* yacc.c:1646  */
    break;

  case 307:
#line 2076 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_symbol(SQL_RETURN, (yyvsp[0].sym)); }
#line 8218 "y.tab.c" /* yacc.c:1646  */
    break;

  case 310:
#line 2083 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_symbol(SQL_TABLE, (yyvsp[-1].sym)); }
#line 8224 "y.tab.c" /* yacc.c:1646  */
    break;

  case 311:
#line 2088 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_CASE,
		   append_list(
		    append_list(
		     append_symbol(
		      L(),(yyvsp[-4].sym)),(yyvsp[-3].l)),(yyvsp[-2].l))); }
#line 8234 "y.tab.c" /* yacc.c:1646  */
    break;

  case 312:
#line 2094 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_CASE,
		   append_list(
		    append_list(
		     L(),(yyvsp[-3].l)),(yyvsp[-2].l))); }
#line 8243 "y.tab.c" /* yacc.c:1646  */
    break;

  case 313:
#line 2102 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_WHEN,
			   append_list(
			    append_symbol(
			     L(), (yyvsp[-2].sym)),(yyvsp[0].l))); }
#line 8252 "y.tab.c" /* yacc.c:1646  */
    break;

  case 314:
#line 2110 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol( L(), (yyvsp[0].sym));}
#line 8258 "y.tab.c" /* yacc.c:1646  */
    break;

  case 315:
#line 2112 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol( (yyvsp[-1].l), (yyvsp[0].sym)); }
#line 8264 "y.tab.c" /* yacc.c:1646  */
    break;

  case 316:
#line 2117 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_WHEN,
			   append_list(
			    append_symbol(
			     L(), (yyvsp[-2].sym)),(yyvsp[0].l))); }
#line 8273 "y.tab.c" /* yacc.c:1646  */
    break;

  case 317:
#line 2125 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol( L(), (yyvsp[0].sym)); }
#line 8279 "y.tab.c" /* yacc.c:1646  */
    break;

  case 318:
#line 2127 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol( (yyvsp[-1].l), (yyvsp[0].sym)); }
#line 8285 "y.tab.c" /* yacc.c:1646  */
    break;

  case 319:
#line 2131 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = NULL; }
#line 8291 "y.tab.c" /* yacc.c:1646  */
    break;

  case 320:
#line 2132 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = (yyvsp[0].l); }
#line 8297 "y.tab.c" /* yacc.c:1646  */
    break;

  case 321:
#line 2142 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  append_symbol(l, (yyvsp[-5].sym));
		  append_list(l, (yyvsp[-3].l));
		  append_symbol(l, (yyvsp[-2].sym));
		  (yyval.sym) = _symbol_create_list(SQL_IF, l);
		}
#line 8308 "y.tab.c" /* yacc.c:1646  */
    break;

  case 322:
#line 2153 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 8314 "y.tab.c" /* yacc.c:1646  */
    break;

  case 323:
#line 2155 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_ELSE, (yyvsp[0].l)); }
#line 8320 "y.tab.c" /* yacc.c:1646  */
    break;

  case 324:
#line 2158 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  append_symbol(l, (yyvsp[-3].sym));
		  append_list(l, (yyvsp[-1].l));
		  append_symbol(l, (yyvsp[0].sym));
		  { (yyval.sym) = _symbol_create_list(SQL_IF, l); }
		}
#line 8331 "y.tab.c" /* yacc.c:1646  */
    break;

  case 325:
#line 2172 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l;
		  char *label = (yyvsp[-7].sval)?(yyvsp[-7].sval):(yyvsp[0].sval);
		  if ((yyvsp[-7].sval) && (yyvsp[0].sval) && strcmp((yyvsp[-7].sval), (yyvsp[0].sval)) != 0) {
			(yyval.sym) = NULL;
			yyerror(m, "WHILE: labels should match");
			YYABORT;
		  }
 		  l = L();
		  append_symbol(l, (yyvsp[-5].sym)); /* condition */
		  append_list(l, (yyvsp[-3].l));	/* statements */
		  append_string(l, label);
		  (yyval.sym) = _symbol_create_list(SQL_WHILE, l);
		}
#line 8349 "y.tab.c" /* yacc.c:1646  */
    break;

  case 326:
#line 2188 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = NULL; }
#line 8355 "y.tab.c" /* yacc.c:1646  */
    break;

  case 328:
#line 2193 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = NULL; }
#line 8361 "y.tab.c" /* yacc.c:1646  */
    break;

  case 330:
#line 2199 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = L();
				  append_string((yyval.l), (yyvsp[-1].sval));
			  	  append_type((yyval.l), &(yyvsp[0].type));
				}
#line 8370 "y.tab.c" /* yacc.c:1646  */
    break;

  case 331:
#line 2204 "sql_parser.y" /* yacc.c:1646  */
    { 
				  append_string((yyval.l), (yyvsp[-1].sval));
			  	  append_type((yyval.l), &(yyvsp[0].type));
				}
#line 8379 "y.tab.c" /* yacc.c:1646  */
    break;

  case 332:
#line 2212 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_TABLE, (yyvsp[-1].l)); }
#line 8385 "y.tab.c" /* yacc.c:1646  */
    break;

  case 333:
#line 2214 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_TYPE, append_type(L(),&(yyvsp[0].type))); }
#line 8391 "y.tab.c" /* yacc.c:1646  */
    break;

  case 335:
#line 2219 "sql_parser.y" /* yacc.c:1646  */
    { dlist *vararg = L();
			  append_string(vararg, "*");
			  append_type(vararg, NULL);
			  (yyval.l) = append_list(L(), vararg); }
#line 8400 "y.tab.c" /* yacc.c:1646  */
    break;

  case 336:
#line 2223 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = NULL; }
#line 8406 "y.tab.c" /* yacc.c:1646  */
    break;

  case 337:
#line 2228 "sql_parser.y" /* yacc.c:1646  */
    { dlist *p = L();
			  append_string(p, (yyvsp[-1].sval));
			  append_type(p, &(yyvsp[0].type));
			  (yyval.l) = append_list((yyvsp[-3].l), p); }
#line 8415 "y.tab.c" /* yacc.c:1646  */
    break;

  case 338:
#line 2233 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  dlist *p = L();
			  append_string(p, (yyvsp[-1].sval));
			  append_type(p, &(yyvsp[0].type));
			  (yyval.l) = append_list(l, p); }
#line 8425 "y.tab.c" /* yacc.c:1646  */
    break;

  case 339:
#line 2283 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-6].l));
	  append_int(l, (yyvsp[-5].i_val));
	  append_symbol(l, (yyvsp[-4].sym));
	  append_string(l, (yyvsp[-2].sval));
	  append_list(l, (yyvsp[-1].l));
	  append_list(l, (yyvsp[0].l));
	  (yyval.sym) = _symbol_create_list(SQL_CREATE_TRIGGER, l); 
	}
#line 8439 "y.tab.c" /* yacc.c:1646  */
    break;

  case 340:
#line 2295 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 8445 "y.tab.c" /* yacc.c:1646  */
    break;

  case 341:
#line 2296 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 1; }
#line 8451 "y.tab.c" /* yacc.c:1646  */
    break;

  case 342:
#line 2300 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_INSERT, NULL); }
#line 8457 "y.tab.c" /* yacc.c:1646  */
    break;

  case 343:
#line 2301 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_DELETE, NULL); }
#line 8463 "y.tab.c" /* yacc.c:1646  */
    break;

  case 344:
#line 2302 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_UPDATE, NULL); }
#line 8469 "y.tab.c" /* yacc.c:1646  */
    break;

  case 345:
#line 2303 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_UPDATE, (yyvsp[0].l)); }
#line 8475 "y.tab.c" /* yacc.c:1646  */
    break;

  case 346:
#line 2307 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = NULL; }
#line 8481 "y.tab.c" /* yacc.c:1646  */
    break;

  case 347:
#line 2308 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = (yyvsp[0].l); }
#line 8487 "y.tab.c" /* yacc.c:1646  */
    break;

  case 348:
#line 2312 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_list(L(), (yyvsp[0].l)); }
#line 8493 "y.tab.c" /* yacc.c:1646  */
    break;

  case 349:
#line 2314 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_list((yyvsp[-1].l), (yyvsp[0].l)); }
#line 8499 "y.tab.c" /* yacc.c:1646  */
    break;

  case 350:
#line 2319 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string(append_int(L(), 0), (yyvsp[0].sval)); }
#line 8505 "y.tab.c" /* yacc.c:1646  */
    break;

  case 351:
#line 2320 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string(append_int(L(), 1), (yyvsp[0].sval)); }
#line 8511 "y.tab.c" /* yacc.c:1646  */
    break;

  case 352:
#line 2321 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string(append_int(L(), 0), (yyvsp[0].sval)); }
#line 8517 "y.tab.c" /* yacc.c:1646  */
    break;

  case 353:
#line 2322 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string(append_int(L(), 1), (yyvsp[0].sval)); }
#line 8523 "y.tab.c" /* yacc.c:1646  */
    break;

  case 358:
#line 2337 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = L();
	  append_int((yyval.l), (yyvsp[-2].i_val));
	  append_symbol((yyval.l), (yyvsp[-1].sym));
	  append_list((yyval.l), (yyvsp[0].l));
	}
#line 8533 "y.tab.c" /* yacc.c:1646  */
    break;

  case 359:
#line 2344 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 1; }
#line 8539 "y.tab.c" /* yacc.c:1646  */
    break;

  case 360:
#line 2345 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = (yyvsp[0].i_val); }
#line 8545 "y.tab.c" /* yacc.c:1646  */
    break;

  case 361:
#line 2349 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 8551 "y.tab.c" /* yacc.c:1646  */
    break;

  case 362:
#line 2350 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 1; }
#line 8557 "y.tab.c" /* yacc.c:1646  */
    break;

  case 363:
#line 2354 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 8563 "y.tab.c" /* yacc.c:1646  */
    break;

  case 364:
#line 2355 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 8569 "y.tab.c" /* yacc.c:1646  */
    break;

  case 365:
#line 2360 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 8575 "y.tab.c" /* yacc.c:1646  */
    break;

  case 366:
#line 2363 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = (yyvsp[-1].l); }
#line 8581 "y.tab.c" /* yacc.c:1646  */
    break;

  case 367:
#line 2368 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-1].l) );
	  append_int(l, (yyvsp[0].i_val) );
	  (yyval.sym) = _symbol_create_list( SQL_DROP_TABLE, l ); }
#line 8590 "y.tab.c" /* yacc.c:1646  */
    break;

  case 368:
#line 2373 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-2].l) );
	  append_int(l, 0 );
	  append_list(l, (yyvsp[-1].l) );
	  append_int(l, (yyvsp[0].i_val) );
	  append_int(l, F_FUNC );
	  (yyval.sym) = _symbol_create_list( SQL_DROP_FUNC, l ); }
#line 8602 "y.tab.c" /* yacc.c:1646  */
    break;

  case 369:
#line 2381 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-2].l) );
	  append_int(l, 0 );
	  append_list(l, (yyvsp[-1].l) );
	  append_int(l, (yyvsp[0].i_val) );
	  append_int(l, F_FILT );
	  (yyval.sym) = _symbol_create_list( SQL_DROP_FUNC, l ); }
#line 8614 "y.tab.c" /* yacc.c:1646  */
    break;

  case 370:
#line 2389 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-2].l) );
	  append_int(l, 0 );
	  append_list(l, (yyvsp[-1].l) );
	  append_int(l, (yyvsp[0].i_val) );
	  append_int(l, F_AGGR );
	  (yyval.sym) = _symbol_create_list( SQL_DROP_FUNC, l ); }
#line 8626 "y.tab.c" /* yacc.c:1646  */
    break;

  case 371:
#line 2397 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-2].l) );
	  append_int(l, 0 );
	  append_list(l, (yyvsp[-1].l) );
	  append_int(l, (yyvsp[0].i_val) );
	  append_int(l, F_PROC );
	  (yyval.sym) = _symbol_create_list( SQL_DROP_FUNC, l ); }
#line 8638 "y.tab.c" /* yacc.c:1646  */
    break;

  case 372:
#line 2405 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-1].l) );
	  append_int(l, 1 );
	  append_list(l, NULL );
	  append_int(l, (yyvsp[0].i_val) );
	  append_int(l, F_FUNC );
	  (yyval.sym) = _symbol_create_list( SQL_DROP_FUNC, l ); }
#line 8650 "y.tab.c" /* yacc.c:1646  */
    break;

  case 373:
#line 2413 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-1].l) );
	  append_int(l, 1 );
	  append_list(l, NULL );
	  append_int(l, (yyvsp[0].i_val) );
	  append_int(l, F_FILT );
	  (yyval.sym) = _symbol_create_list( SQL_DROP_FUNC, l ); }
#line 8662 "y.tab.c" /* yacc.c:1646  */
    break;

  case 374:
#line 2421 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-1].l) );
	  append_int(l, 1 );
	  append_list(l, NULL );
	  append_int(l, (yyvsp[0].i_val) );
	  append_int(l, F_AGGR );
	  (yyval.sym) = _symbol_create_list( SQL_DROP_FUNC, l ); }
#line 8674 "y.tab.c" /* yacc.c:1646  */
    break;

  case 375:
#line 2429 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-1].l) );
	  append_int(l, 1 );
	  append_list(l, NULL );
	  append_int(l, (yyvsp[0].i_val) );
	  append_int(l, F_PROC );
	  (yyval.sym) = _symbol_create_list( SQL_DROP_FUNC, l ); }
#line 8686 "y.tab.c" /* yacc.c:1646  */
    break;

  case 376:
#line 2437 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-1].l) );
	  append_int(l, (yyvsp[0].i_val) );
	  (yyval.sym) = _symbol_create_list( SQL_DROP_VIEW, l ); }
#line 8695 "y.tab.c" /* yacc.c:1646  */
    break;

  case 377:
#line 2441 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create( SQL_DROP_ROLE, (yyvsp[0].sval) ); }
#line 8701 "y.tab.c" /* yacc.c:1646  */
    break;

  case 378:
#line 2442 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create( SQL_DROP_USER, (yyvsp[0].sval) ); }
#line 8707 "y.tab.c" /* yacc.c:1646  */
    break;

  case 379:
#line 2443 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_DROP_INDEX, (yyvsp[0].l) ); }
#line 8713 "y.tab.c" /* yacc.c:1646  */
    break;

  case 380:
#line 2444 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_DROP_TRIGGER, (yyvsp[0].l) ); }
#line 8719 "y.tab.c" /* yacc.c:1646  */
    break;

  case 381:
#line 2448 "sql_parser.y" /* yacc.c:1646  */
    {(yyval.l) = NULL;}
#line 8725 "y.tab.c" /* yacc.c:1646  */
    break;

  case 382:
#line 2449 "sql_parser.y" /* yacc.c:1646  */
    {(yyval.l) = (yyvsp[-1].l);}
#line 8731 "y.tab.c" /* yacc.c:1646  */
    break;

  case 383:
#line 2450 "sql_parser.y" /* yacc.c:1646  */
    {(yyval.l) = L(); }
#line 8737 "y.tab.c" /* yacc.c:1646  */
    break;

  case 384:
#line 2454 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
				  append_type(l, &(yyvsp[0].type) );
				  (yyval.l)= l; }
#line 8745 "y.tab.c" /* yacc.c:1646  */
    break;

  case 385:
#line 2457 "sql_parser.y" /* yacc.c:1646  */
    { append_type((yyvsp[0].l), &(yyvsp[-2].type));
				  (yyval.l) = (yyvsp[0].l); }
#line 8752 "y.tab.c" /* yacc.c:1646  */
    break;

  case 386:
#line 2462 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 8758 "y.tab.c" /* yacc.c:1646  */
    break;

  case 387:
#line 2463 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 8764 "y.tab.c" /* yacc.c:1646  */
    break;

  case 388:
#line 2464 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 1; }
#line 8770 "y.tab.c" /* yacc.c:1646  */
    break;

  case 395:
#line 2483 "sql_parser.y" /* yacc.c:1646  */
    {
	  (yyval.sym) = (yyvsp[0].sym);
	  m->type = Q_TRANS;					}
#line 8778 "y.tab.c" /* yacc.c:1646  */
    break;

  case 396:
#line 2490 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_int( TR_COMMIT, (yyvsp[0].bval));  }
#line 8784 "y.tab.c" /* yacc.c:1646  */
    break;

  case 397:
#line 2492 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create( TR_SAVEPOINT, (yyvsp[0].sval)); }
#line 8790 "y.tab.c" /* yacc.c:1646  */
    break;

  case 398:
#line 2494 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create( TR_RELEASE, (yyvsp[0].sval)); }
#line 8796 "y.tab.c" /* yacc.c:1646  */
    break;

  case 399:
#line 2496 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( TR_ROLLBACK,
		   append_string(
			append_int(L(), (yyvsp[-1].bval)), (yyvsp[0].sval) )); }
#line 8804 "y.tab.c" /* yacc.c:1646  */
    break;

  case 400:
#line 2500 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_int( TR_START, (yyvsp[0].i_val)); }
#line 8810 "y.tab.c" /* yacc.c:1646  */
    break;

  case 401:
#line 2502 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_int( TR_MODE, (yyvsp[0].i_val)); }
#line 8816 "y.tab.c" /* yacc.c:1646  */
    break;

  case 402:
#line 2504 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_int( TR_MODE, (yyvsp[0].i_val)); }
#line 8822 "y.tab.c" /* yacc.c:1646  */
    break;

  case 403:
#line 2508 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = tr_none; }
#line 8828 "y.tab.c" /* yacc.c:1646  */
    break;

  case 405:
#line 2514 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = (yyvsp[0].i_val); }
#line 8834 "y.tab.c" /* yacc.c:1646  */
    break;

  case 406:
#line 2516 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = ((yyvsp[-2].i_val) | (yyvsp[0].i_val)); }
#line 8840 "y.tab.c" /* yacc.c:1646  */
    break;

  case 407:
#line 2521 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = tr_readonly; }
#line 8846 "y.tab.c" /* yacc.c:1646  */
    break;

  case 408:
#line 2522 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = tr_writable; }
#line 8852 "y.tab.c" /* yacc.c:1646  */
    break;

  case 409:
#line 2523 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = tr_serializable; }
#line 8858 "y.tab.c" /* yacc.c:1646  */
    break;

  case 410:
#line 2524 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = tr_none; /* not supported */ }
#line 8864 "y.tab.c" /* yacc.c:1646  */
    break;

  case 415:
#line 2535 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = 0; }
#line 8870 "y.tab.c" /* yacc.c:1646  */
    break;

  case 416:
#line 2536 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = 0; }
#line 8876 "y.tab.c" /* yacc.c:1646  */
    break;

  case 417:
#line 2540 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = 1; }
#line 8882 "y.tab.c" /* yacc.c:1646  */
    break;

  case 418:
#line 2541 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = 0; }
#line 8888 "y.tab.c" /* yacc.c:1646  */
    break;

  case 419:
#line 2542 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = 0; }
#line 8894 "y.tab.c" /* yacc.c:1646  */
    break;

  case 420:
#line 2546 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = NULL; }
#line 8900 "y.tab.c" /* yacc.c:1646  */
    break;

  case 421:
#line 2547 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 8906 "y.tab.c" /* yacc.c:1646  */
    break;

  case 422:
#line 2552 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-9].l));
	  append_list(l, (yyvsp[-8].l));
	  append_list(l, (yyvsp[-6].l));
	  append_list(l, (yyvsp[-5].l));
	  append_list(l, (yyvsp[-4].l));
	  append_list(l, (yyvsp[-11].l));
	  append_string(l, (yyvsp[-3].sval));
	  append_int(l, (yyvsp[-2].bval));
	  append_int(l, (yyvsp[-1].bval));
	  append_int(l, (yyvsp[0].bval));
	  (yyval.sym) = _symbol_create_list( SQL_COPYFROM, l ); }
#line 8923 "y.tab.c" /* yacc.c:1646  */
    break;

  case 423:
#line 2565 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-9].l));
	  append_list(l, (yyvsp[-8].l));
	  append_list(l, NULL);
	  append_list(l, (yyvsp[-5].l));
	  append_list(l, (yyvsp[-4].l));
	  append_list(l, (yyvsp[-11].l));
	  append_string(l, (yyvsp[-3].sval));
	  append_int(l, (yyvsp[-2].bval));
	  append_int(l, (yyvsp[-1].bval));
	  append_int(l, (yyvsp[0].bval));
	  (yyval.sym) = _symbol_create_list( SQL_COPYFROM, l ); }
#line 8940 "y.tab.c" /* yacc.c:1646  */
    break;

  case 424:
#line 2578 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  if ((yyvsp[-6].l) != NULL) {
	  	yyerror(m, "COPY INTO: cannot pass number of records when using binary COPY INTO");
		YYABORT;
	  }
	  append_list(l, (yyvsp[-3].l));
	  append_list(l, (yyvsp[-1].l));
	  append_int(l, (yyvsp[0].bval));
	  (yyval.sym) = _symbol_create_list( SQL_BINCOPYFROM, l ); }
#line 8954 "y.tab.c" /* yacc.c:1646  */
    break;

  case 425:
#line 2588 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_symbol(l, (yyvsp[-4].sym));
	  append_string(l, (yyvsp[-2].sval));
	  append_list(l, (yyvsp[-1].l));
	  append_string(l, (yyvsp[0].sval));
	  (yyval.sym) = _symbol_create_list( SQL_COPYTO, l ); }
#line 8965 "y.tab.c" /* yacc.c:1646  */
    break;

  case 426:
#line 2595 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_symbol(l, (yyvsp[-4].sym));
	  append_string(l, NULL);
	  append_list(l, (yyvsp[-1].l));
	  append_string(l, (yyvsp[0].sval));
	  (yyval.sym) = _symbol_create_list( SQL_COPYTO, l ); }
#line 8976 "y.tab.c" /* yacc.c:1646  */
    break;

  case 427:
#line 2604 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = NULL; }
#line 8982 "y.tab.c" /* yacc.c:1646  */
    break;

  case 428:
#line 2605 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = (yyvsp[-1].l); }
#line 8988 "y.tab.c" /* yacc.c:1646  */
    break;

  case 429:
#line 2609 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_list(L(), (yyvsp[0].l)); }
#line 8994 "y.tab.c" /* yacc.c:1646  */
    break;

  case 430:
#line 2610 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_list((yyvsp[-2].l), (yyvsp[0].l)); }
#line 9000 "y.tab.c" /* yacc.c:1646  */
    break;

  case 431:
#line 2615 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_string(l, (yyvsp[0].sval) );
			  (yyval.l) = l; }
#line 9008 "y.tab.c" /* yacc.c:1646  */
    break;

  case 432:
#line 2619 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_string(l, (yyvsp[-1].sval) );
			  append_string(l, (yyvsp[0].sval) );
			  (yyval.l) = l; }
#line 9017 "y.tab.c" /* yacc.c:1646  */
    break;

  case 433:
#line 2627 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
				  append_string(l, sa_strdup(SA, "|"));
				  append_string(l, sa_strdup(SA, "\\n"));
				  (yyval.l) = l; }
#line 9026 "y.tab.c" /* yacc.c:1646  */
    break;

  case 434:
#line 2632 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
				  append_string(l, (yyvsp[0].sval));
				  append_string(l, sa_strdup(SA, "\\n"));
				  (yyval.l) = l; }
#line 9035 "y.tab.c" /* yacc.c:1646  */
    break;

  case 435:
#line 2637 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
				  append_string(l, (yyvsp[-2].sval));
				  append_string(l, (yyvsp[0].sval));
				  (yyval.l) = l; }
#line 9044 "y.tab.c" /* yacc.c:1646  */
    break;

  case 436:
#line 2642 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
				  append_string(l, (yyvsp[-4].sval));
				  append_string(l, (yyvsp[-2].sval));
				  append_string(l, sql2str((yyvsp[0].sval)));
				  (yyval.l) = l; }
#line 9054 "y.tab.c" /* yacc.c:1646  */
    break;

  case 437:
#line 2650 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = NULL; }
#line 9060 "y.tab.c" /* yacc.c:1646  */
    break;

  case 438:
#line 2651 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = NULL; }
#line 9066 "y.tab.c" /* yacc.c:1646  */
    break;

  case 439:
#line 2655 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = NULL; }
#line 9072 "y.tab.c" /* yacc.c:1646  */
    break;

  case 440:
#line 2656 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_lng(append_lng(L(), (yyvsp[-1].l_val)), 0); }
#line 9078 "y.tab.c" /* yacc.c:1646  */
    break;

  case 441:
#line 2657 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_lng(append_lng(L(), -1), (yyvsp[0].l_val)); }
#line 9084 "y.tab.c" /* yacc.c:1646  */
    break;

  case 442:
#line 2659 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_lng(append_lng(L(), (yyvsp[-3].l_val)), (yyvsp[-1].l_val)); }
#line 9090 "y.tab.c" /* yacc.c:1646  */
    break;

  case 443:
#line 2661 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_lng(append_lng(L(), (yyvsp[-3].l_val)), (yyvsp[0].l_val)); }
#line 9096 "y.tab.c" /* yacc.c:1646  */
    break;

  case 444:
#line 2665 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = NULL; }
#line 9102 "y.tab.c" /* yacc.c:1646  */
    break;

  case 445:
#line 2666 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 9108 "y.tab.c" /* yacc.c:1646  */
    break;

  case 446:
#line 2670 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = FALSE; }
#line 9114 "y.tab.c" /* yacc.c:1646  */
    break;

  case 447:
#line 2671 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = TRUE; }
#line 9120 "y.tab.c" /* yacc.c:1646  */
    break;

  case 448:
#line 2675 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = FALSE; }
#line 9126 "y.tab.c" /* yacc.c:1646  */
    break;

  case 449:
#line 2676 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = TRUE; }
#line 9132 "y.tab.c" /* yacc.c:1646  */
    break;

  case 450:
#line 2680 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = TRUE; }
#line 9138 "y.tab.c" /* yacc.c:1646  */
    break;

  case 451:
#line 2681 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = FALSE; }
#line 9144 "y.tab.c" /* yacc.c:1646  */
    break;

  case 452:
#line 2685 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = (yyvsp[0].l); }
#line 9150 "y.tab.c" /* yacc.c:1646  */
    break;

  case 453:
#line 2686 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = (yyvsp[-1].l); }
#line 9156 "y.tab.c" /* yacc.c:1646  */
    break;

  case 454:
#line 2690 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string(L(), (yyvsp[0].sval)); }
#line 9162 "y.tab.c" /* yacc.c:1646  */
    break;

  case 455:
#line 2692 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string((yyvsp[-2].l), (yyvsp[0].sval)); }
#line 9168 "y.tab.c" /* yacc.c:1646  */
    break;

  case 456:
#line 2698 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-1].l));
	  append_symbol(l, (yyvsp[0].sym));
	  (yyval.sym) = _symbol_create_list( SQL_DELETE, l ); }
#line 9177 "y.tab.c" /* yacc.c:1646  */
    break;

  case 457:
#line 2707 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-3].l));
	  append_list(l, (yyvsp[-1].l));
	  append_symbol(l, (yyvsp[0].sym));
	  (yyval.sym) = _symbol_create_list( SQL_UPDATE, l ); }
#line 9187 "y.tab.c" /* yacc.c:1646  */
    break;

  case 458:
#line 2748 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-1].l));
	  append_list(l, NULL);
	  append_symbol(l, (yyvsp[0].sym));
	  (yyval.sym) = _symbol_create_list( SQL_INSERT, l ); }
#line 9197 "y.tab.c" /* yacc.c:1646  */
    break;

  case 459:
#line 2756 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-2].l));
	  append_list(l, (yyvsp[-1].l));
	  append_symbol(l, (yyvsp[0].sym));
	  (yyval.sym) = _symbol_create_list( SQL_INSERT, l ); }
#line 9207 "y.tab.c" /* yacc.c:1646  */
    break;

  case 460:
#line 2765 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_VALUES, L()); }
#line 9213 "y.tab.c" /* yacc.c:1646  */
    break;

  case 461:
#line 2767 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_VALUES, L()); }
#line 9219 "y.tab.c" /* yacc.c:1646  */
    break;

  case 462:
#line 2769 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_VALUES, (yyvsp[0].l)); }
#line 9225 "y.tab.c" /* yacc.c:1646  */
    break;

  case 464:
#line 2775 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_list(L(), (yyvsp[-1].l)); }
#line 9231 "y.tab.c" /* yacc.c:1646  */
    break;

  case 465:
#line 2777 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_list((yyvsp[-4].l), (yyvsp[-1].l)); }
#line 9237 "y.tab.c" /* yacc.c:1646  */
    break;

  case 466:
#line 2781 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 9243 "y.tab.c" /* yacc.c:1646  */
    break;

  case 467:
#line 2783 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol((yyvsp[-2].l), (yyvsp[0].sym)); }
#line 9249 "y.tab.c" /* yacc.c:1646  */
    break;

  case 468:
#line 2787 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 9255 "y.tab.c" /* yacc.c:1646  */
    break;

  case 469:
#line 2789 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol((yyvsp[-2].l), (yyvsp[0].sym)); }
#line 9261 "y.tab.c" /* yacc.c:1646  */
    break;

  case 470:
#line 2794 "sql_parser.y" /* yacc.c:1646  */
    { 
	  if (m->emode == m_normal && m->caching) {
		/* replace by argument */
		atom *a = atom_general(SA, sql_bind_localtype("void"), NULL);

		sql_add_arg( m, a);
		(yyval.sym) = _symbol_create_list( SQL_COLUMN,
			append_int(L(), m->argc-1));
	   } else {
		(yyval.sym) = _symbol_create(SQL_NULL, NULL );
	   }
	}
#line 9278 "y.tab.c" /* yacc.c:1646  */
    break;

  case 475:
#line 2823 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = FALSE; }
#line 9284 "y.tab.c" /* yacc.c:1646  */
    break;

  case 476:
#line 2824 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = FALSE; }
#line 9290 "y.tab.c" /* yacc.c:1646  */
    break;

  case 477:
#line 2825 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = TRUE; }
#line 9296 "y.tab.c" /* yacc.c:1646  */
    break;

  case 478:
#line 2829 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[0].sym) ); }
#line 9302 "y.tab.c" /* yacc.c:1646  */
    break;

  case 479:
#line 2831 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol((yyvsp[-2].l), (yyvsp[0].sym) ); }
#line 9308 "y.tab.c" /* yacc.c:1646  */
    break;

  case 480:
#line 2836 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_symbol(l, (yyvsp[0].sym) );
	  append_string(l, (yyvsp[-2].sval));
	  (yyval.sym) = _symbol_create_list( SQL_ASSIGN, l); }
#line 9317 "y.tab.c" /* yacc.c:1646  */
    break;

  case 481:
#line 2841 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_symbol(l, (yyvsp[0].sym));
	  append_list(l, (yyvsp[-2].l));
	  (yyval.sym) = _symbol_create_list( SQL_ASSIGN, l ); }
#line 9326 "y.tab.c" /* yacc.c:1646  */
    break;

  case 482:
#line 2848 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 9332 "y.tab.c" /* yacc.c:1646  */
    break;

  case 483:
#line 2849 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 9338 "y.tab.c" /* yacc.c:1646  */
    break;

  case 484:
#line 2856 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[-1].sym); }
#line 9344 "y.tab.c" /* yacc.c:1646  */
    break;

  case 485:
#line 2859 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_symbol(l, (yyvsp[-3].sym));
	  append_symbol(l, (yyvsp[0].sym));
	  (yyval.sym) = _symbol_create_list( SQL_CROSS, l); }
#line 9353 "y.tab.c" /* yacc.c:1646  */
    break;

  case 486:
#line 2864 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_symbol(l, (yyvsp[-3].sym));
	  append_int(l, 0);
	  append_int(l, 4);
	  append_symbol(l, (yyvsp[-1].sym));
	  append_symbol(l, (yyvsp[0].sym));
	  (yyval.sym) = _symbol_create_list( SQL_UNIONJOIN, l); }
#line 9365 "y.tab.c" /* yacc.c:1646  */
    break;

  case 487:
#line 2872 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_symbol(l, (yyvsp[-3].sym));
	  append_int(l, 0);
	  append_int(l, 0);
	  append_symbol(l, (yyvsp[-1].sym));
	  append_symbol(l, (yyvsp[0].sym));
	  (yyval.sym) = _symbol_create_list( SQL_JOIN, l); }
#line 9377 "y.tab.c" /* yacc.c:1646  */
    break;

  case 488:
#line 2880 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_symbol(l, (yyvsp[-3].sym));
	  append_int(l, 1);
	  append_int(l, 0);
	  append_symbol(l, (yyvsp[0].sym));
	  append_symbol(l, NULL);
	  (yyval.sym) = _symbol_create_list( SQL_JOIN, l); }
#line 9389 "y.tab.c" /* yacc.c:1646  */
    break;

  case 489:
#line 2888 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_symbol(l, (yyvsp[-4].sym));
	  append_int(l, 0);
	  append_int(l, (yyvsp[-3].i_val));
	  append_symbol(l, (yyvsp[-1].sym));
	  append_symbol(l, (yyvsp[0].sym));
	  (yyval.sym) = _symbol_create_list( SQL_JOIN, l); }
#line 9401 "y.tab.c" /* yacc.c:1646  */
    break;

  case 490:
#line 2896 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_symbol(l, (yyvsp[-4].sym));
	  append_int(l, 1);
	  append_int(l, (yyvsp[-2].i_val));
	  append_symbol(l, (yyvsp[0].sym));
	  append_symbol(l, NULL);
	  (yyval.sym) = _symbol_create_list( SQL_JOIN, l); }
#line 9413 "y.tab.c" /* yacc.c:1646  */
    break;

  case 491:
#line 2906 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 9419 "y.tab.c" /* yacc.c:1646  */
    break;

  case 492:
#line 2907 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 1 + (yyvsp[-1].i_val); }
#line 9425 "y.tab.c" /* yacc.c:1646  */
    break;

  case 493:
#line 2908 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 1 + (yyvsp[0].i_val); }
#line 9431 "y.tab.c" /* yacc.c:1646  */
    break;

  case 494:
#line 2912 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 9437 "y.tab.c" /* yacc.c:1646  */
    break;

  case 495:
#line 2913 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 1; }
#line 9443 "y.tab.c" /* yacc.c:1646  */
    break;

  case 496:
#line 2914 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 2; }
#line 9449 "y.tab.c" /* yacc.c:1646  */
    break;

  case 497:
#line 2918 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 9455 "y.tab.c" /* yacc.c:1646  */
    break;

  case 498:
#line 2920 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_USING, (yyvsp[0].l)); }
#line 9461 "y.tab.c" /* yacc.c:1646  */
    break;

  case 500:
#line 2944 "sql_parser.y" /* yacc.c:1646  */
    {
		dlist *l = L();
	  	append_list(l, (yyvsp[-1].l));
	  	append_symbol(l, (yyvsp[0].sym));
	  	(yyval.sym) = _symbol_create_list( SQL_WITH, l ); 
	}
#line 9472 "y.tab.c" /* yacc.c:1646  */
    break;

  case 501:
#line 2953 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol((yyvsp[-2].l), (yyvsp[0].sym)); }
#line 9478 "y.tab.c" /* yacc.c:1646  */
    break;

  case 502:
#line 2954 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 9484 "y.tab.c" /* yacc.c:1646  */
    break;

  case 503:
#line 2959 "sql_parser.y" /* yacc.c:1646  */
    {  dlist *l = L();
	  append_list(l, append_string(L(), (yyvsp[-5].sval)));
	  append_list(l, (yyvsp[-4].l));
	  append_symbol(l, (yyvsp[-1].sym));
	  append_int(l, FALSE);	/* no with check */
	  append_int(l, FALSE);	/* inlined view  (ie not persistent) */
	  (yyval.sym) = _symbol_create_list( SQL_CREATE_VIEW, l ); 
	}
#line 9497 "y.tab.c" /* yacc.c:1646  */
    break;

  case 507:
#line 2982 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = newSelectNode( SA, (yyvsp[-2].bval), (yyvsp[-1].l), NULL,
		(yyvsp[0].l)->h->data.sym,
		(yyvsp[0].l)->h->next->data.sym,
		(yyvsp[0].l)->h->next->next->data.sym,
		(yyvsp[0].l)->h->next->next->next->data.sym,
		NULL, NULL, NULL, NULL, NULL);
	}
#line 9509 "y.tab.c" /* yacc.c:1646  */
    break;

  case 508:
#line 2993 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = newSelectNode( SA, (yyvsp[-4].bval), (yyvsp[-3].l), (yyvsp[-1].l),
		(yyvsp[0].l)->h->data.sym,
		(yyvsp[0].l)->h->next->data.sym,
		(yyvsp[0].l)->h->next->next->data.sym,
		(yyvsp[0].l)->h->next->next->next->data.sym,
		NULL, NULL, NULL, NULL, NULL);
	}
#line 9521 "y.tab.c" /* yacc.c:1646  */
    break;

  case 509:
#line 3004 "sql_parser.y" /* yacc.c:1646  */
    { 
	  (yyval.sym) = (yyvsp[-4].sym);
	  if ((yyvsp[-3].sym) || (yyvsp[-2].sym) || (yyvsp[-1].sym) || (yyvsp[0].sym)) {
	  	if ((yyvsp[-4].sym) != NULL &&
		    ((yyvsp[-4].sym)->token == SQL_SELECT ||
		     (yyvsp[-4].sym)->token == SQL_UNION  ||
		     (yyvsp[-4].sym)->token == SQL_EXCEPT ||
		     (yyvsp[-4].sym)->token == SQL_INTERSECT)) {
			if ((yyvsp[-4].sym)->token == SQL_SELECT) {
	 			SelectNode *s = (SelectNode*)(yyvsp[-4].sym);
	
	  			s -> orderby = (yyvsp[-3].sym);
	  			s -> limit = (yyvsp[-2].sym);
	  			s -> offset = (yyvsp[-1].sym);
	  			s -> sample = (yyvsp[0].sym);
			} else { /* Add extra select * from .. in case of UNION, EXCEPT, INTERSECT */
				(yyval.sym) = newSelectNode( 
					SA, 0, 
					append_symbol(L(), _symbol_create_list(SQL_TABLE, append_string(append_string(L(),NULL),NULL))), NULL,
					_symbol_create_list( SQL_FROM, append_symbol(L(), (yyvsp[-4].sym))), NULL, NULL, NULL, (yyvsp[-3].sym), _symbol_create_list(SQL_NAME, append_list(append_string(L(),"inner"),NULL)), (yyvsp[-2].sym), (yyvsp[-1].sym), (yyvsp[0].sym));
			}
	  	} else {
			yyerror(m, "missing SELECT operator");
			YYABORT;
	  	}
	 } 
	}
#line 9553 "y.tab.c" /* yacc.c:1646  */
    break;

  case 510:
#line 3034 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string(L(), (yyvsp[0].sval)); }
#line 9559 "y.tab.c" /* yacc.c:1646  */
    break;

  case 511:
#line 3036 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string((yyvsp[-2].l), (yyvsp[0].sval)); }
#line 9565 "y.tab.c" /* yacc.c:1646  */
    break;

  case 513:
#line 3046 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_symbol(l, (yyvsp[-4].sym));
	  append_int(l, (yyvsp[-2].bval));
	  append_list(l, (yyvsp[-1].l));
	  append_symbol(l, (yyvsp[0].sym));
	  (yyval.sym) = _symbol_create_list( SQL_UNION, l); }
#line 9576 "y.tab.c" /* yacc.c:1646  */
    break;

  case 514:
#line 3055 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_symbol(l, (yyvsp[-4].sym));
	  append_int(l, (yyvsp[-2].bval));
	  append_list(l, (yyvsp[-1].l));
	  append_symbol(l, (yyvsp[0].sym));
	  (yyval.sym) = _symbol_create_list( SQL_EXCEPT, l); }
#line 9587 "y.tab.c" /* yacc.c:1646  */
    break;

  case 515:
#line 3064 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_symbol(l, (yyvsp[-4].sym));
	  append_int(l, (yyvsp[-2].bval));
	  append_list(l, (yyvsp[-1].l));
	  append_symbol(l, (yyvsp[0].sym));
	  (yyval.sym) = _symbol_create_list( SQL_INTERSECT, l); }
#line 9598 "y.tab.c" /* yacc.c:1646  */
    break;

  case 516:
#line 3070 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[-1].sym); }
#line 9604 "y.tab.c" /* yacc.c:1646  */
    break;

  case 518:
#line 3075 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = TRUE; }
#line 9610 "y.tab.c" /* yacc.c:1646  */
    break;

  case 519:
#line 3076 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = FALSE; }
#line 9616 "y.tab.c" /* yacc.c:1646  */
    break;

  case 520:
#line 3077 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = TRUE; }
#line 9622 "y.tab.c" /* yacc.c:1646  */
    break;

  case 521:
#line 3082 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = NULL; }
#line 9628 "y.tab.c" /* yacc.c:1646  */
    break;

  case 522:
#line 3084 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = L(); }
#line 9634 "y.tab.c" /* yacc.c:1646  */
    break;

  case 523:
#line 3086 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = (yyvsp[-1].l); }
#line 9640 "y.tab.c" /* yacc.c:1646  */
    break;

  case 525:
#line 3096 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = L();
	  append_symbol((yyval.l), (yyvsp[-3].sym));
	  append_symbol((yyval.l), (yyvsp[-2].sym));
	  append_symbol((yyval.l), (yyvsp[-1].sym));
	  append_symbol((yyval.l), (yyvsp[0].sym)); }
#line 9650 "y.tab.c" /* yacc.c:1646  */
    break;

  case 526:
#line 3104 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 9656 "y.tab.c" /* yacc.c:1646  */
    break;

  case 527:
#line 3105 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_FROM, (yyvsp[0].l)); }
#line 9662 "y.tab.c" /* yacc.c:1646  */
    break;

  case 528:
#line 3109 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 9668 "y.tab.c" /* yacc.c:1646  */
    break;

  case 529:
#line 3111 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol((yyvsp[-2].l), (yyvsp[0].sym)); }
#line 9674 "y.tab.c" /* yacc.c:1646  */
    break;

  case 530:
#line 3115 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  		  append_list(l, (yyvsp[0].l));
		  	  	  append_symbol(l, NULL);
		  		  (yyval.sym) = _symbol_create_list(SQL_NAME, l); }
#line 9683 "y.tab.c" /* yacc.c:1646  */
    break;

  case 531:
#line 3119 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  		  append_list(l, (yyvsp[-1].l));
		  	  	  append_symbol(l, (yyvsp[0].sym));
		  		  (yyval.sym) = _symbol_create_list(SQL_NAME, l); }
#line 9692 "y.tab.c" /* yacc.c:1646  */
    break;

  case 532:
#line 3123 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  		  append_symbol(l, (yyvsp[-1].sym));
		  	  	  append_symbol(l, (yyvsp[0].sym));
		  		  (yyval.sym) = _symbol_create_list(SQL_TABLE, l); }
#line 9701 "y.tab.c" /* yacc.c:1646  */
    break;

  case 533:
#line 3127 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  		  append_symbol(l, (yyvsp[0].sym));
		  	  	  append_symbol(l, NULL);
		  		  (yyval.sym) = _symbol_create_list(SQL_TABLE, l); }
#line 9710 "y.tab.c" /* yacc.c:1646  */
    break;

  case 535:
#line 3136 "sql_parser.y" /* yacc.c:1646  */
    {
				  (yyval.sym) = (yyvsp[-1].sym);
				  if ((yyval.sym)->token == SQL_SELECT) {
				  	SelectNode *sn = (SelectNode*)(yyvsp[-1].sym);
				  	sn->name = (yyvsp[0].sym);
				  } else {
				  	append_symbol((yyvsp[-1].sym)->data.lval, (yyvsp[0].sym));
				  }
				}
#line 9724 "y.tab.c" /* yacc.c:1646  */
    break;

  case 536:
#line 3146 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL;
				  yyerror(m, "subquery table reference needs alias, use AS xxx");
				  YYABORT;
				}
#line 9733 "y.tab.c" /* yacc.c:1646  */
    break;

  case 537:
#line 3150 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym);
				  append_symbol((yyvsp[0].sym)->data.lval, NULL); }
#line 9740 "y.tab.c" /* yacc.c:1646  */
    break;

  case 538:
#line 3160 "sql_parser.y" /* yacc.c:1646  */
    { m->caching = 0; }
#line 9746 "y.tab.c" /* yacc.c:1646  */
    break;

  case 539:
#line 3162 "sql_parser.y" /* yacc.c:1646  */
    {
		dlist *op = L();

 	  	append_symbol(op, (yyvsp[-2].sym));
		append_symbol(op, (yyvsp[0].sym));
		(yyval.sym) = _symbol_create_list(SQL_TABLE_OPERATOR, op); 
	}
#line 9758 "y.tab.c" /* yacc.c:1646  */
    break;

  case 540:
#line 3173 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  		  append_string(l, (yyvsp[-3].sval));
		  	  	  append_list(l, (yyvsp[-1].l));
		  		  (yyval.sym) = _symbol_create_list(SQL_NAME, l); }
#line 9767 "y.tab.c" /* yacc.c:1646  */
    break;

  case 541:
#line 3178 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  		  append_string(l, (yyvsp[0].sval));
		  	  	  append_list(l, NULL);
		  		  (yyval.sym) = _symbol_create_list(SQL_NAME, l); }
#line 9776 "y.tab.c" /* yacc.c:1646  */
    break;

  case 542:
#line 3183 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  		  append_string(l, (yyvsp[-3].sval));
		  	  	  append_list(l, (yyvsp[-1].l));
		  		  (yyval.sym) = _symbol_create_list(SQL_NAME, l); }
#line 9785 "y.tab.c" /* yacc.c:1646  */
    break;

  case 543:
#line 3188 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  		  append_string(l, (yyvsp[0].sval));
		  	  	  append_list(l, NULL);
		  		  (yyval.sym) = _symbol_create_list(SQL_NAME, l); }
#line 9794 "y.tab.c" /* yacc.c:1646  */
    break;

  case 544:
#line 3195 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 9800 "y.tab.c" /* yacc.c:1646  */
    break;

  case 545:
#line 3196 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_GROUPBY, (yyvsp[0].l) );}
#line 9806 "y.tab.c" /* yacc.c:1646  */
    break;

  case 546:
#line 3200 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(),
			       _symbol_create_list(SQL_COLUMN,(yyvsp[0].l))); }
#line 9813 "y.tab.c" /* yacc.c:1646  */
    break;

  case 547:
#line 3203 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol( (yyvsp[-2].l),
			       _symbol_create_list(SQL_COLUMN,(yyvsp[0].l))); }
#line 9820 "y.tab.c" /* yacc.c:1646  */
    break;

  case 548:
#line 3208 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 9826 "y.tab.c" /* yacc.c:1646  */
    break;

  case 549:
#line 3209 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 9832 "y.tab.c" /* yacc.c:1646  */
    break;

  case 550:
#line 3215 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  append_symbol(l, (yyvsp[-2].sym));
		  append_symbol(l, (yyvsp[0].sym));
		  (yyval.sym) = _symbol_create_list(SQL_OR, l ); }
#line 9841 "y.tab.c" /* yacc.c:1646  */
    break;

  case 551:
#line 3219 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 9847 "y.tab.c" /* yacc.c:1646  */
    break;

  case 552:
#line 3224 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  append_symbol(l, (yyvsp[-2].sym));
		  append_symbol(l, (yyvsp[0].sym));
		  (yyval.sym) = _symbol_create_list(SQL_AND, l ); }
#line 9856 "y.tab.c" /* yacc.c:1646  */
    break;

  case 553:
#line 3228 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 9862 "y.tab.c" /* yacc.c:1646  */
    break;

  case 554:
#line 3232 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 9868 "y.tab.c" /* yacc.c:1646  */
    break;

  case 555:
#line 3234 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_ORDERBY, (yyvsp[0].l)); }
#line 9874 "y.tab.c" /* yacc.c:1646  */
    break;

  case 556:
#line 3238 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 9880 "y.tab.c" /* yacc.c:1646  */
    break;

  case 557:
#line 3239 "sql_parser.y" /* yacc.c:1646  */
    { 
		  	  sql_subtype *t = sql_bind_localtype("wrd");
			  (yyval.sym) = _newAtomNode( atom_int(SA, t, (yyvsp[0].w_val))); 
			}
#line 9889 "y.tab.c" /* yacc.c:1646  */
    break;

  case 558:
#line 3243 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 9895 "y.tab.c" /* yacc.c:1646  */
    break;

  case 559:
#line 3247 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 9901 "y.tab.c" /* yacc.c:1646  */
    break;

  case 560:
#line 3248 "sql_parser.y" /* yacc.c:1646  */
    { 
		  	  sql_subtype *t = sql_bind_localtype("wrd");
			  (yyval.sym) = _newAtomNode( atom_int(SA, t, (yyvsp[0].w_val))); 
			}
#line 9910 "y.tab.c" /* yacc.c:1646  */
    break;

  case 561:
#line 3252 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 9916 "y.tab.c" /* yacc.c:1646  */
    break;

  case 562:
#line 3256 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 9922 "y.tab.c" /* yacc.c:1646  */
    break;

  case 563:
#line 3257 "sql_parser.y" /* yacc.c:1646  */
    {
		  	  sql_subtype *t = sql_bind_localtype("wrd");
			  (yyval.sym) = _newAtomNode( atom_int(SA, t, (yyvsp[0].w_val)));
			}
#line 9931 "y.tab.c" /* yacc.c:1646  */
    break;

  case 564:
#line 3261 "sql_parser.y" /* yacc.c:1646  */
    {
		  	  sql_subtype *t = sql_bind_localtype("dbl");
			  (yyval.sym) = _newAtomNode( atom_float(SA, t, strtod((yyvsp[0].sval),NULL)));
			}
#line 9940 "y.tab.c" /* yacc.c:1646  */
    break;

  case 565:
#line 3265 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 9946 "y.tab.c" /* yacc.c:1646  */
    break;

  case 566:
#line 3269 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 9952 "y.tab.c" /* yacc.c:1646  */
    break;

  case 567:
#line 3271 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol( (yyvsp[-2].l), (yyvsp[0].sym) ); }
#line 9958 "y.tab.c" /* yacc.c:1646  */
    break;

  case 568:
#line 3276 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_symbol(l, (yyvsp[-1].sym));
	  append_int(l, (yyvsp[0].bval));
	  (yyval.sym) = _symbol_create_list(SQL_COLUMN, l ); }
#line 9967 "y.tab.c" /* yacc.c:1646  */
    break;

  case 569:
#line 3284 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = TRUE; }
#line 9973 "y.tab.c" /* yacc.c:1646  */
    break;

  case 570:
#line 3285 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = TRUE; }
#line 9979 "y.tab.c" /* yacc.c:1646  */
    break;

  case 571:
#line 3286 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = FALSE; }
#line 9985 "y.tab.c" /* yacc.c:1646  */
    break;

  case 581:
#line 3303 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym);

		  if ((yyval.sym)->token == SQL_EXISTS)
			(yyval.sym)->token = SQL_NOT_EXISTS;
		  else if ((yyval.sym)->token == SQL_NOT_EXISTS)
			(yyval.sym)->token = SQL_EXISTS;
		  else if ((yyval.sym)->token == SQL_NOT_BETWEEN)
			(yyval.sym)->token = SQL_BETWEEN;
		  else if ((yyval.sym)->token == SQL_BETWEEN)
			(yyval.sym)->token = SQL_NOT_BETWEEN;
		  else if ((yyval.sym)->token == SQL_NOT_LIKE)
			(yyval.sym)->token = SQL_LIKE;
		  else if ((yyval.sym)->token == SQL_LIKE)
			(yyval.sym)->token = SQL_NOT_LIKE;
		  else
			(yyval.sym) = _symbol_create_symbol(SQL_NOT, (yyvsp[0].sym)); }
#line 10006 "y.tab.c" /* yacc.c:1646  */
    break;

  case 582:
#line 3319 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 10012 "y.tab.c" /* yacc.c:1646  */
    break;

  case 583:
#line 3324 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();

		  append_symbol(l, (yyvsp[-2].sym));
		  append_string(l, (yyvsp[-1].sval));
		  append_symbol(l, (yyvsp[0].sym));
		  (yyval.sym) = _symbol_create_list(SQL_COMPARE, l ); }
#line 10023 "y.tab.c" /* yacc.c:1646  */
    break;

  case 584:
#line 3331 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();

		  append_symbol(l, (yyvsp[-2].sym));
		  append_string(l, sa_strdup(SA, "="));
		  append_symbol(l, (yyvsp[0].sym));
		  (yyval.sym) = _symbol_create_list(SQL_COMPARE, l ); }
#line 10034 "y.tab.c" /* yacc.c:1646  */
    break;

  case 585:
#line 3341 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  append_symbol(l, (yyvsp[-5].sym));
		  append_int(l, (yyvsp[-3].i_val));
		  append_symbol(l, (yyvsp[-2].sym));
		  append_symbol(l, (yyvsp[0].sym));
		  (yyval.sym) = _symbol_create_list(SQL_NOT_BETWEEN, l ); }
#line 10045 "y.tab.c" /* yacc.c:1646  */
    break;

  case 586:
#line 3348 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  append_symbol(l, (yyvsp[-5].sym));
		  append_int(l, (yyvsp[-3].i_val));
		  append_symbol(l, (yyvsp[-2].sym));
		  append_symbol(l, (yyvsp[0].sym));
		  (yyval.sym) = _symbol_create_list(SQL_BETWEEN, l ); }
#line 10056 "y.tab.c" /* yacc.c:1646  */
    break;

  case 587:
#line 3357 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 10062 "y.tab.c" /* yacc.c:1646  */
    break;

  case 588:
#line 3358 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 10068 "y.tab.c" /* yacc.c:1646  */
    break;

  case 589:
#line 3359 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 1; }
#line 10074 "y.tab.c" /* yacc.c:1646  */
    break;

  case 590:
#line 3364 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  append_symbol(l, (yyvsp[-2].sym));
		  append_symbol(l, (yyvsp[0].sym));
		  append_int(l, FALSE);  /* case sensitive */
		  append_int(l, TRUE);  /* anti */
		  (yyval.sym) = _symbol_create_list( SQL_LIKE, l ); }
#line 10085 "y.tab.c" /* yacc.c:1646  */
    break;

  case 591:
#line 3371 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  append_symbol(l, (yyvsp[-2].sym));
		  append_symbol(l, (yyvsp[0].sym));
		  append_int(l, TRUE);  /* case insensitive */
		  append_int(l, TRUE);  /* anti */
		  (yyval.sym) = _symbol_create_list( SQL_LIKE, l ); }
#line 10096 "y.tab.c" /* yacc.c:1646  */
    break;

  case 592:
#line 3378 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  append_symbol(l, (yyvsp[-2].sym));
		  append_symbol(l, (yyvsp[0].sym));
		  append_int(l, FALSE);  /* case sensitive */
		  append_int(l, FALSE);  /* anti */
		  (yyval.sym) = _symbol_create_list( SQL_LIKE, l ); }
#line 10107 "y.tab.c" /* yacc.c:1646  */
    break;

  case 593:
#line 3385 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  append_symbol(l, (yyvsp[-2].sym));
		  append_symbol(l, (yyvsp[0].sym));
		  append_int(l, TRUE);  /* case insensitive */
		  append_int(l, FALSE);  /* anti */
		  (yyval.sym) = _symbol_create_list( SQL_LIKE, l ); }
#line 10118 "y.tab.c" /* yacc.c:1646  */
    break;

  case 594:
#line 3395 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_symbol(l, (yyvsp[0].sym));
	  (yyval.sym) = _symbol_create_list(SQL_ESCAPE, l ); }
#line 10126 "y.tab.c" /* yacc.c:1646  */
    break;

  case 595:
#line 3399 "sql_parser.y" /* yacc.c:1646  */
    { char *s = sql2str((yyvsp[0].sval));
	  if (_strlen(s) != 1) {
		char *msg = sql_message("\b22025!ESCAPE must be one character");
		yyerror(m, msg);
		_DELETE(msg);
		(yyval.sym) = NULL;
		YYABORT;
	  } else {
		dlist *l = L();
		append_symbol(l, (yyvsp[-2].sym));
		append_string(l, s);
		(yyval.sym) = _symbol_create_list(SQL_ESCAPE, l);
	  }
	}
#line 10145 "y.tab.c" /* yacc.c:1646  */
    break;

  case 596:
#line 3416 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_symbol( SQL_IS_NOT_NULL, (yyvsp[-3].sym) );}
#line 10151 "y.tab.c" /* yacc.c:1646  */
    break;

  case 597:
#line 3417 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_symbol( SQL_IS_NULL, (yyvsp[-2].sym) ); }
#line 10157 "y.tab.c" /* yacc.c:1646  */
    break;

  case 598:
#line 3422 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();

		  append_symbol(l, (yyvsp[-4].sym));
		  append_list(l, (yyvsp[-1].l));
		  (yyval.sym) = _symbol_create_list(SQL_NOT_IN, l ); }
#line 10167 "y.tab.c" /* yacc.c:1646  */
    break;

  case 599:
#line 3428 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();

		  append_symbol(l, (yyvsp[-4].sym));
		  append_list(l, (yyvsp[-1].l));
		  (yyval.sym) = _symbol_create_list(SQL_IN, l ); }
#line 10177 "y.tab.c" /* yacc.c:1646  */
    break;

  case 600:
#line 3434 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  append_list(l, (yyvsp[-5].l));
		  append_list(l, (yyvsp[-1].l));
		  (yyval.sym) = _symbol_create_list(SQL_NOT_IN, l ); }
#line 10186 "y.tab.c" /* yacc.c:1646  */
    break;

  case 601:
#line 3439 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  append_list(l, (yyvsp[-5].l));
		  append_list(l, (yyvsp[-1].l));
		  (yyval.sym) = _symbol_create_list(SQL_IN, l ); }
#line 10195 "y.tab.c" /* yacc.c:1646  */
    break;

  case 602:
#line 3447 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol( L(), (yyvsp[0].sym));}
#line 10201 "y.tab.c" /* yacc.c:1646  */
    break;

  case 603:
#line 3449 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol( (yyvsp[-2].l), (yyvsp[0].sym)); }
#line 10207 "y.tab.c" /* yacc.c:1646  */
    break;

  case 604:
#line 3455 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  append_symbol(l, (yyvsp[-3].sym));
		  append_string(l, (yyvsp[-2].sval));
		  append_symbol(l, (yyvsp[0].sym));
		  append_int(l, (yyvsp[-1].i_val));
		  (yyval.sym) = _symbol_create_list(SQL_COMPARE, l ); }
#line 10218 "y.tab.c" /* yacc.c:1646  */
    break;

  case 605:
#line 3464 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 10224 "y.tab.c" /* yacc.c:1646  */
    break;

  case 606:
#line 3465 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 10230 "y.tab.c" /* yacc.c:1646  */
    break;

  case 607:
#line 3466 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 1; }
#line 10236 "y.tab.c" /* yacc.c:1646  */
    break;

  case 608:
#line 3470 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_symbol( SQL_EXISTS, (yyvsp[0].sym) ); }
#line 10242 "y.tab.c" /* yacc.c:1646  */
    break;

  case 609:
#line 3474 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 10248 "y.tab.c" /* yacc.c:1646  */
    break;

  case 610:
#line 3475 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol((yyvsp[-2].l), (yyvsp[0].sym));  }
#line 10254 "y.tab.c" /* yacc.c:1646  */
    break;

  case 611:
#line 3479 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = (yyvsp[-1].l); }
#line 10260 "y.tab.c" /* yacc.c:1646  */
    break;

  case 612:
#line 3484 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  append_list(l, (yyvsp[-2].l));
		  append_list(l, (yyvsp[-1].l));
		  append_list(l, (yyvsp[0].l));
		  (yyval.sym) = _symbol_create_list(SQL_FILTER, l ); }
#line 10270 "y.tab.c" /* yacc.c:1646  */
    break;

  case 613:
#line 3492 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[-1].sym); }
#line 10276 "y.tab.c" /* yacc.c:1646  */
    break;

  case 614:
#line 3494 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_VALUES, (yyvsp[-1].l)); }
#line 10282 "y.tab.c" /* yacc.c:1646  */
    break;

  case 615:
#line 3496 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[-1].sym); }
#line 10288 "y.tab.c" /* yacc.c:1646  */
    break;

  case 617:
#line 3503 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l, 
			  	append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "sql_add")));
	  		  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 10299 "y.tab.c" /* yacc.c:1646  */
    break;

  case 618:
#line 3510 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l, 
			  	append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "sql_sub")));
	  		  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 10310 "y.tab.c" /* yacc.c:1646  */
    break;

  case 619:
#line 3517 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l, 
			  	append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "sql_mul")));
	  		  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 10321 "y.tab.c" /* yacc.c:1646  */
    break;

  case 620:
#line 3524 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l, 
			  	append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "sql_div")));
	  		  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 10332 "y.tab.c" /* yacc.c:1646  */
    break;

  case 621:
#line 3531 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l, 
			  	append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "mod")));
	  		  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 10343 "y.tab.c" /* yacc.c:1646  */
    break;

  case 622:
#line 3538 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l, 
			  	append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "bit_xor")));
	  		  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 10354 "y.tab.c" /* yacc.c:1646  */
    break;

  case 623:
#line 3545 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l, 
			  	append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "bit_and")));
	  		  append_symbol(l, (yyvsp[-2].sym));
			  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 10365 "y.tab.c" /* yacc.c:1646  */
    break;

  case 624:
#line 3552 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l, 
			  	append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "bit_or")));
	  		  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 10376 "y.tab.c" /* yacc.c:1646  */
    break;

  case 625:
#line 3559 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l, 
			  	append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "bit_not")));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_UNOP, l ); }
#line 10386 "y.tab.c" /* yacc.c:1646  */
    break;

  case 626:
#line 3565 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l, 
			  	append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "left_shift")));
	  		  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 10397 "y.tab.c" /* yacc.c:1646  */
    break;

  case 627:
#line 3572 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l, 
			  	append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "right_shift")));
	  		  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 10408 "y.tab.c" /* yacc.c:1646  */
    break;

  case 628:
#line 3579 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l, 
			  	append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "left_shift_assign")));
	  		  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 10419 "y.tab.c" /* yacc.c:1646  */
    break;

  case 629:
#line 3586 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l, 
			  	append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "right_shift_assign")));
	  		  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 10430 "y.tab.c" /* yacc.c:1646  */
    break;

  case 630:
#line 3593 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 10436 "y.tab.c" /* yacc.c:1646  */
    break;

  case 631:
#line 3595 "sql_parser.y" /* yacc.c:1646  */
    { 
 			  (yyval.sym) = NULL;
			  assert((yyvsp[0].sym)->token != SQL_COLUMN || (yyvsp[0].sym)->data.lval->h->type != type_lng);
			  if ((yyvsp[0].sym)->token == SQL_COLUMN && (yyvsp[0].sym)->data.lval->h->type == type_int) {
				atom *a = sql_bind_arg(m, (yyvsp[0].sym)->data.lval->h->data.i_val);
				if (!atom_neg(a)) {
					(yyval.sym) = (yyvsp[0].sym);
				} else {
					char *msg = sql_message("\b22003!value too large or not a number");

					yyerror(m, msg);
					_DELETE(msg);
					(yyval.sym) = NULL;
					YYABORT;
				}
			  } 
			  if (!(yyval.sym)) {
				dlist *l = L();
			  	append_list(l, 
			  		append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "sql_neg")));
	  		  	append_symbol(l, (yyvsp[0].sym));
	  		  	(yyval.sym) = _symbol_create_list( SQL_UNOP, l ); 
			  }
			}
#line 10465 "y.tab.c" /* yacc.c:1646  */
    break;

  case 632:
#line 3619 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[-1].sym); }
#line 10471 "y.tab.c" /* yacc.c:1646  */
    break;

  case 633:
#line 3623 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 10477 "y.tab.c" /* yacc.c:1646  */
    break;

  case 636:
#line 3629 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_COLUMN, 
			  append_string(L(), sa_strdup(SA, "current_user"))); }
#line 10484 "y.tab.c" /* yacc.c:1646  */
    break;

  case 637:
#line 3631 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_COLUMN, 
			  append_string(L(), sa_strdup(SA, "current_role"))); }
#line 10491 "y.tab.c" /* yacc.c:1646  */
    break;

  case 639:
#line 3634 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_COLUMN, (yyvsp[0].l)); }
#line 10497 "y.tab.c" /* yacc.c:1646  */
    break;

  case 643:
#line 3638 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_NEXT, (yyvsp[0].l)); }
#line 10503 "y.tab.c" /* yacc.c:1646  */
    break;

  case 651:
#line 3650 "sql_parser.y" /* yacc.c:1646  */
    { 
	  int nr = (m->params)?list_length(m->params):0;

	  sql_add_param(m, NULL, NULL);
	  (yyval.sym) = _symbol_create_int( SQL_PARAMETER, nr ); 
	}
#line 10514 "y.tab.c" /* yacc.c:1646  */
    break;

  case 652:
#line 3720 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_RANK, 
		append_list(append_symbol(L(), (yyvsp[-4].sym)), (yyvsp[-1].l))); }
#line 10521 "y.tab.c" /* yacc.c:1646  */
    break;

  case 653:
#line 3725 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_RANK, (yyvsp[-2].l) ); }
#line 10527 "y.tab.c" /* yacc.c:1646  */
    break;

  case 655:
#line 3731 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(append_symbol(append_symbol(L(), (yyvsp[-2].sym)), (yyvsp[-1].sym)), (yyvsp[0].sym)); }
#line 10533 "y.tab.c" /* yacc.c:1646  */
    break;

  case 656:
#line 3735 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 10539 "y.tab.c" /* yacc.c:1646  */
    break;

  case 657:
#line 3737 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_GROUPBY, (yyvsp[0].l) ); }
#line 10545 "y.tab.c" /* yacc.c:1646  */
    break;

  case 658:
#line 3741 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 10551 "y.tab.c" /* yacc.c:1646  */
    break;

  case 659:
#line 3743 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_ORDERBY, (yyvsp[0].l) ); }
#line 10557 "y.tab.c" /* yacc.c:1646  */
    break;

  case 660:
#line 3747 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 10563 "y.tab.c" /* yacc.c:1646  */
    break;

  case 661:
#line 3749 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_FRAME, append_int(append_int((yyvsp[-1].l), (yyvsp[-2].i_val)), (yyvsp[0].i_val))); }
#line 10569 "y.tab.c" /* yacc.c:1646  */
    break;

  case 662:
#line 3753 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = FRAME_ROWS; }
#line 10575 "y.tab.c" /* yacc.c:1646  */
    break;

  case 663:
#line 3754 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = FRAME_RANGE; }
#line 10581 "y.tab.c" /* yacc.c:1646  */
    break;

  case 664:
#line 3758 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(append_symbol(L(), (yyvsp[0].sym)), _symbol_create_int(SQL_FRAME, -1)); }
#line 10587 "y.tab.c" /* yacc.c:1646  */
    break;

  case 665:
#line 3759 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = (yyvsp[0].l); }
#line 10593 "y.tab.c" /* yacc.c:1646  */
    break;

  case 666:
#line 3763 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_int(SQL_FRAME, -1); }
#line 10599 "y.tab.c" /* yacc.c:1646  */
    break;

  case 667:
#line 3764 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 10605 "y.tab.c" /* yacc.c:1646  */
    break;

  case 668:
#line 3765 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_int(SQL_FRAME, 0); }
#line 10611 "y.tab.c" /* yacc.c:1646  */
    break;

  case 669:
#line 3769 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[-1].sym); }
#line 10617 "y.tab.c" /* yacc.c:1646  */
    break;

  case 670:
#line 3774 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(append_symbol(L(), (yyvsp[-2].sym)), (yyvsp[0].sym)); }
#line 10623 "y.tab.c" /* yacc.c:1646  */
    break;

  case 671:
#line 3778 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_int(SQL_FRAME, -1); }
#line 10629 "y.tab.c" /* yacc.c:1646  */
    break;

  case 672:
#line 3779 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 10635 "y.tab.c" /* yacc.c:1646  */
    break;

  case 673:
#line 3780 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_int(SQL_FRAME, 0); }
#line 10641 "y.tab.c" /* yacc.c:1646  */
    break;

  case 674:
#line 3784 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[-1].sym); }
#line 10647 "y.tab.c" /* yacc.c:1646  */
    break;

  case 675:
#line 3788 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = EXCLUDE_NONE; }
#line 10653 "y.tab.c" /* yacc.c:1646  */
    break;

  case 676:
#line 3789 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = EXCLUDE_CURRENT_ROW; }
#line 10659 "y.tab.c" /* yacc.c:1646  */
    break;

  case 677:
#line 3790 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = EXCLUDE_GROUP; }
#line 10665 "y.tab.c" /* yacc.c:1646  */
    break;

  case 678:
#line 3791 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = EXCLUDE_TIES; }
#line 10671 "y.tab.c" /* yacc.c:1646  */
    break;

  case 679:
#line 3792 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = EXCLUDE_NO_OTHERS; }
#line 10677 "y.tab.c" /* yacc.c:1646  */
    break;

  case 680:
#line 3796 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create( SQL_NAME, (yyvsp[0].sval) ); }
#line 10683 "y.tab.c" /* yacc.c:1646  */
    break;

  case 681:
#line 3801 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
  	  append_list(l, (yyvsp[-2].l));
	  (yyval.sym) = _symbol_create_list( SQL_OP, l ); }
#line 10691 "y.tab.c" /* yacc.c:1646  */
    break;

  case 682:
#line 3805 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
  	  append_list(l, (yyvsp[-3].l));
	  if (dlist_length((yyvsp[-1].l)) == 1) {
  	  	append_symbol(l, (yyvsp[-1].l)->h->data.sym);
	  	(yyval.sym) = _symbol_create_list( SQL_UNOP, l ); 
	  } else if (dlist_length((yyvsp[-1].l)) == 2) {
  	  	append_symbol(l, (yyvsp[-1].l)->h->data.sym);
  	  	append_symbol(l, (yyvsp[-1].l)->h->next->data.sym);
	  	(yyval.sym) = _symbol_create_list( SQL_BINOP, l ); 
	  } else {
  	  	append_list(l, (yyvsp[-1].l));
	  	(yyval.sym) = _symbol_create_list( SQL_NOP, l ); 
	  }
	}
#line 10710 "y.tab.c" /* yacc.c:1646  */
    break;

  case 683:
#line 3832 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string(L(), (yyvsp[0].sval)); }
#line 10716 "y.tab.c" /* yacc.c:1646  */
    break;

  case 684:
#line 3833 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string(
					append_string(L(), (yyvsp[-2].sval)), (yyvsp[0].sval));}
#line 10723 "y.tab.c" /* yacc.c:1646  */
    break;

  case 685:
#line 3838 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 10729 "y.tab.c" /* yacc.c:1646  */
    break;

  case 686:
#line 3839 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "left"); }
#line 10735 "y.tab.c" /* yacc.c:1646  */
    break;

  case 687:
#line 3840 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "right"); }
#line 10741 "y.tab.c" /* yacc.c:1646  */
    break;

  case 688:
#line 3841 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "insert"); }
#line 10747 "y.tab.c" /* yacc.c:1646  */
    break;

  case 689:
#line 3846 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  const char *ident = datetime_field((itype)(yyvsp[-3].i_val));
			  append_list(l,
  		  	  	append_string(L(), sa_strdup(SA, ident)));
  		  	  append_symbol(l, (yyvsp[-1].sym));
		  	  (yyval.sym) = _symbol_create_list( SQL_UNOP, l ); }
#line 10758 "y.tab.c" /* yacc.c:1646  */
    break;

  case 690:
#line 3853 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l,
			  	append_string(L(), sa_strdup(SA, "current_date")));
	  		  (yyval.sym) = _symbol_create_list( SQL_OP, l ); }
#line 10767 "y.tab.c" /* yacc.c:1646  */
    break;

  case 691:
#line 3858 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l,
			  	append_string(L(), sa_strdup(SA, "current_time")));
	  		  (yyval.sym) = _symbol_create_list( SQL_OP, l ); }
#line 10776 "y.tab.c" /* yacc.c:1646  */
    break;

  case 692:
#line 3863 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l,
			  	append_string(L(), sa_strdup(SA, "current_timestamp")));
	  		  (yyval.sym) = _symbol_create_list( SQL_OP, l ); }
#line 10785 "y.tab.c" /* yacc.c:1646  */
    break;

  case 693:
#line 3868 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l,
			  	append_string(L(), sa_strdup(SA, "localtime")));
	  		  (yyval.sym) = _symbol_create_list( SQL_OP, l ); }
#line 10794 "y.tab.c" /* yacc.c:1646  */
    break;

  case 694:
#line 3873 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l,
			  	append_string(L(), sa_strdup(SA, "localtimestamp")));
	  		  (yyval.sym) = _symbol_create_list( SQL_OP, l ); }
#line 10803 "y.tab.c" /* yacc.c:1646  */
    break;

  case 695:
#line 3880 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = 0; }
#line 10809 "y.tab.c" /* yacc.c:1646  */
    break;

  case 696:
#line 3881 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = 1; }
#line 10815 "y.tab.c" /* yacc.c:1646  */
    break;

  case 697:
#line 3886 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  dlist *ops = L();
  		  	  append_list(l,
				append_string(L(), sa_strdup(SA, "substring")));
  		  	  append_symbol(ops, (yyvsp[-5].sym));
  		  	  append_symbol(ops, (yyvsp[-3].sym));
  		  	  append_symbol(ops, (yyvsp[-1].sym));
			  append_list(l, ops);
		  	  (yyval.sym) = _symbol_create_list( SQL_NOP, l ); }
#line 10829 "y.tab.c" /* yacc.c:1646  */
    break;

  case 698:
#line 3896 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  dlist *ops = L();
  		  	  append_list(l,
  		  	  	append_string(L(), sa_strdup(SA, "substring")));
  		  	  append_symbol(ops, (yyvsp[-5].sym));
  		  	  append_symbol(ops, (yyvsp[-3].sym));
  		  	  append_symbol(ops, (yyvsp[-1].sym));
			  append_list(l, ops);
		  	  (yyval.sym) = _symbol_create_list( SQL_NOP, l ); }
#line 10843 "y.tab.c" /* yacc.c:1646  */
    break;

  case 699:
#line 3906 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
  		  	  append_list(l,
  		  	  	append_string(L(), sa_strdup(SA, "substring")));
  		  	  append_symbol(l, (yyvsp[-3].sym));
  		  	  append_symbol(l, (yyvsp[-1].sym));
		  	  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 10854 "y.tab.c" /* yacc.c:1646  */
    break;

  case 700:
#line 3913 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
  		  	  append_list(l,
  		  	  	append_string(L(), sa_strdup(SA, "substring")));
  		  	  append_symbol(l, (yyvsp[-3].sym));
  		  	  append_symbol(l, (yyvsp[-1].sym));
		  	  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 10865 "y.tab.c" /* yacc.c:1646  */
    break;

  case 701:
#line 3920 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
  		  	  append_list(l,
  		  	  	append_string(L(), sa_strdup(SA, "locate")));
  		  	  append_symbol(l, (yyvsp[-3].sym));
  		  	  append_symbol(l, (yyvsp[-1].sym));
		  	  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 10876 "y.tab.c" /* yacc.c:1646  */
    break;

  case 702:
#line 3927 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
  		  	  append_list(l,
  		  	  	append_string(L(), sa_strdup(SA, "concat")));
  		  	  append_symbol(l, (yyvsp[-2].sym));
  		  	  append_symbol(l, (yyvsp[0].sym));
		  	  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 10887 "y.tab.c" /* yacc.c:1646  */
    break;

  case 703:
#line 3934 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  dlist *ops = L();
  		  	  append_list(l,
				append_string(L(), sa_strdup(SA, "splitpart")));
  		  	  append_symbol(ops, (yyvsp[-5].sym));
  		  	  append_symbol(ops, (yyvsp[-3].sym));
  		  	  append_symbol(ops, (yyvsp[-1].sym));
			  append_list(l, ops);
		  	  (yyval.sym) = _symbol_create_list( SQL_NOP, l ); }
#line 10901 "y.tab.c" /* yacc.c:1646  */
    break;

  case 704:
#line 3946 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[0].sym) ); }
#line 10907 "y.tab.c" /* yacc.c:1646  */
    break;

  case 705:
#line 3948 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol( (yyvsp[-2].l), (yyvsp[0].sym) ); }
#line 10913 "y.tab.c" /* yacc.c:1646  */
    break;

  case 706:
#line 3953 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
  		  append_string(l, NULL);
  		  append_string(l, NULL);
  		  (yyval.sym) = _symbol_create_list( SQL_TABLE, l ); }
#line 10922 "y.tab.c" /* yacc.c:1646  */
    break;

  case 707:
#line 3958 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
  		  append_string(l, (yyvsp[-2].sval));
  		  append_string(l, NULL);
  		  (yyval.sym) = _symbol_create_list( SQL_TABLE, l ); }
#line 10931 "y.tab.c" /* yacc.c:1646  */
    break;

  case 708:
#line 3963 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
  		  append_symbol(l, (yyvsp[-2].sym));
  		  append_string(l, NULL);
  		  (yyval.sym) = _symbol_create_list( SQL_TABLE, l ); }
#line 10940 "y.tab.c" /* yacc.c:1646  */
    break;

  case 709:
#line 3968 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
  		  append_symbol(l, (yyvsp[-1].sym));
  		  append_string(l, (yyvsp[0].sval));
  		  (yyval.sym) = _symbol_create_list( SQL_COLUMN, l ); }
#line 10949 "y.tab.c" /* yacc.c:1646  */
    break;

  case 710:
#line 3975 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = NULL; }
#line 10955 "y.tab.c" /* yacc.c:1646  */
    break;

  case 711:
#line 3976 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 10961 "y.tab.c" /* yacc.c:1646  */
    break;

  case 712:
#line 3981 "sql_parser.y" /* yacc.c:1646  */
    { 
	  if (m->emode == m_normal && m->caching) { 
	  	/* replace by argument */
	  	AtomNode *an = (AtomNode*)(yyvsp[0].sym);
	
	  	sql_add_arg( m, an->a);
		an->a = NULL;
	  	/* we miss use SQL_COLUMN also for param's, maybe
	     		change SQL_COLUMN to SQL_IDENT */
 	  	(yyval.sym) = _symbol_create_list( SQL_COLUMN,
			append_int(L(), m->argc-1));
	   } else {
	  	AtomNode *an = (AtomNode*)(yyvsp[0].sym);
		atom *a = an->a; 
		an->a = atom_dup(SA, a); 
		(yyval.sym) = (yyvsp[0].sym);
	   }
	}
#line 10984 "y.tab.c" /* yacc.c:1646  */
    break;

  case 713:
#line 4002 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string(L(), (yyvsp[0].sval)); }
#line 10990 "y.tab.c" /* yacc.c:1646  */
    break;

  case 714:
#line 4003 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string(
			  append_string(L(), (yyvsp[-2].sval)), (yyvsp[0].sval));}
#line 10997 "y.tab.c" /* yacc.c:1646  */
    break;

  case 715:
#line 4008 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string(L(), (yyvsp[0].sval)); }
#line 11003 "y.tab.c" /* yacc.c:1646  */
    break;

  case 716:
#line 4009 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string(
			  append_string(L(), (yyvsp[-2].sval)), (yyvsp[0].sval));}
#line 11010 "y.tab.c" /* yacc.c:1646  */
    break;

  case 717:
#line 4014 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string(L(), (yyvsp[0].sval)); }
#line 11016 "y.tab.c" /* yacc.c:1646  */
    break;

  case 718:
#line 4015 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string(
			  append_string(L(), (yyvsp[-2].sval)), (yyvsp[0].sval));}
#line 11023 "y.tab.c" /* yacc.c:1646  */
    break;

  case 719:
#line 4022 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
  		  append_list(l, (yyvsp[-3].l));
  		  append_int(l, FALSE);
  		  append_symbol(l, NULL);
		  (yyval.sym) = _symbol_create_list( SQL_AGGR, l ); }
#line 11033 "y.tab.c" /* yacc.c:1646  */
    break;

  case 720:
#line 4028 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
  		  append_list(l, (yyvsp[-5].l));
  		  append_int(l, FALSE);
  		  append_symbol(l, NULL);
		  (yyval.sym) = _symbol_create_list( SQL_AGGR, l ); }
#line 11043 "y.tab.c" /* yacc.c:1646  */
    break;

  case 721:
#line 4034 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
  		  append_list(l, (yyvsp[-4].l));
  		  append_int(l, TRUE);
  		  append_symbol(l, (yyvsp[-1].sym));
		  (yyval.sym) = _symbol_create_list( SQL_AGGR, l ); }
#line 11053 "y.tab.c" /* yacc.c:1646  */
    break;

  case 722:
#line 4040 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
  		  append_list(l, (yyvsp[-4].l));
  		  append_int(l, FALSE);
  		  append_symbol(l, (yyvsp[-1].sym));
		  (yyval.sym) = _symbol_create_list( SQL_AGGR, l ); }
#line 11063 "y.tab.c" /* yacc.c:1646  */
    break;

  case 723:
#line 4046 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
  		  append_list(l, (yyvsp[-3].l));
  		  append_int(l, FALSE);
  		  append_symbol(l, (yyvsp[-1].sym));
		  (yyval.sym) = _symbol_create_list( SQL_AGGR, l ); }
#line 11073 "y.tab.c" /* yacc.c:1646  */
    break;

  case 724:
#line 4052 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
  		  append_list(l, (yyvsp[-5].l));
  		  append_int(l, FALSE);
  		  append_symbol(l, (yyvsp[-3].sym));
  		  append_symbol(l, (yyvsp[-1].sym));
		  (yyval.sym) = _symbol_create_list( SQL_AGGR, l ); }
#line 11084 "y.tab.c" /* yacc.c:1646  */
    break;

  case 726:
#line 4062 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 1; }
#line 11090 "y.tab.c" /* yacc.c:1646  */
    break;

  case 727:
#line 4063 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = -1; }
#line 11096 "y.tab.c" /* yacc.c:1646  */
    break;

  case 728:
#line 4064 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 1; }
#line 11102 "y.tab.c" /* yacc.c:1646  */
    break;

  case 729:
#line 4068 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = 1; }
#line 11108 "y.tab.c" /* yacc.c:1646  */
    break;

  case 730:
#line 4069 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = 0; }
#line 11114 "y.tab.c" /* yacc.c:1646  */
    break;

  case 731:
#line 4080 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = (yyvsp[-1].i_val)+1; }
#line 11120 "y.tab.c" /* yacc.c:1646  */
    break;

  case 732:
#line 4082 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0+1; }
#line 11126 "y.tab.c" /* yacc.c:1646  */
    break;

  case 733:
#line 4086 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = (yyvsp[-1].i_val)+1; }
#line 11132 "y.tab.c" /* yacc.c:1646  */
    break;

  case 734:
#line 4088 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 6+1; }
#line 11138 "y.tab.c" /* yacc.c:1646  */
    break;

  case 735:
#line 4092 "sql_parser.y" /* yacc.c:1646  */
    { sql_find_subtype(&(yyval.type), "date", 0, 0); }
#line 11144 "y.tab.c" /* yacc.c:1646  */
    break;

  case 736:
#line 4094 "sql_parser.y" /* yacc.c:1646  */
    { if ((yyvsp[0].bval))
				sql_find_subtype(&(yyval.type), "timetz", (yyvsp[-1].i_val), 0); 
			  else
				sql_find_subtype(&(yyval.type), "time", (yyvsp[-1].i_val), 0); 
			}
#line 11154 "y.tab.c" /* yacc.c:1646  */
    break;

  case 737:
#line 4100 "sql_parser.y" /* yacc.c:1646  */
    { if ((yyvsp[0].bval))
				sql_find_subtype(&(yyval.type), "timestamptz", (yyvsp[-1].i_val), 0); 
			  else
				sql_find_subtype(&(yyval.type), "timestamp", (yyvsp[-1].i_val), 0); 
			}
#line 11164 "y.tab.c" /* yacc.c:1646  */
    break;

  case 738:
#line 4108 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = iyear; }
#line 11170 "y.tab.c" /* yacc.c:1646  */
    break;

  case 739:
#line 4109 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = imonth; }
#line 11176 "y.tab.c" /* yacc.c:1646  */
    break;

  case 740:
#line 4110 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = iday; }
#line 11182 "y.tab.c" /* yacc.c:1646  */
    break;

  case 741:
#line 4111 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = ihour; }
#line 11188 "y.tab.c" /* yacc.c:1646  */
    break;

  case 742:
#line 4112 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = imin; }
#line 11194 "y.tab.c" /* yacc.c:1646  */
    break;

  case 744:
#line 4117 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = isec; }
#line 11200 "y.tab.c" /* yacc.c:1646  */
    break;

  case 745:
#line 4122 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_int(
			 	append_int( L(), (yyvsp[-1].i_val)), (yyvsp[0].i_val)-1);  }
#line 11207 "y.tab.c" /* yacc.c:1646  */
    break;

  case 746:
#line 4128 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_int(
			 	append_int( L(), (yyvsp[0].i_val)), 0);  }
#line 11214 "y.tab.c" /* yacc.c:1646  */
    break;

  case 747:
#line 4131 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_int(
			 	append_int( L(), isec), (yyvsp[0].i_val)-1);  }
#line 11221 "y.tab.c" /* yacc.c:1646  */
    break;

  case 748:
#line 4137 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_int(
			 	append_int( L(), (yyvsp[-1].i_val)), (yyvsp[0].i_val)-1);  }
#line 11228 "y.tab.c" /* yacc.c:1646  */
    break;

  case 749:
#line 4140 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_int(
			 	append_int( L(), isec), (yyvsp[0].i_val)-1);  }
#line 11235 "y.tab.c" /* yacc.c:1646  */
    break;

  case 750:
#line 4146 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) =  append_list(
			append_list( L(), (yyvsp[-2].l)), (yyvsp[0].l) ); }
#line 11242 "y.tab.c" /* yacc.c:1646  */
    break;

  case 751:
#line 4149 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) =  append_list( L(), (yyvsp[0].l)); }
#line 11248 "y.tab.c" /* yacc.c:1646  */
    break;

  case 752:
#line 4153 "sql_parser.y" /* yacc.c:1646  */
    {
		int sk, ek, sp, ep;
	  	int tpe;

		(yyval.type).type = NULL;
	  	if ( (tpe = parse_interval_qualifier( m, (yyvsp[0].l), &sk, &ek, &sp, &ep )) < 0){
			yyerror(m, "\b22006!incorrect interval");
			YYABORT;
	  	} else {
			int d = inttype2digits(sk, ek);
			if (tpe == 0){
				sql_find_subtype(&(yyval.type), "month_interval", d, 0);
			} else {
				sql_find_subtype(&(yyval.type), "sec_interval", d, 0);
			}
	  	}
	}
#line 11270 "y.tab.c" /* yacc.c:1646  */
    break;

  case 756:
#line 4179 "sql_parser.y" /* yacc.c:1646  */
    { char *s = sql2str((yyvsp[0].sval));
		  int len = UTF8_strlen(s);
		  sql_subtype t;
		  sql_find_subtype(&t, "char", len, 0 );
		  (yyval.sym) = _newAtomNode( _atom_string(&t, s)); }
#line 11280 "y.tab.c" /* yacc.c:1646  */
    break;

  case 757:
#line 4185 "sql_parser.y" /* yacc.c:1646  */
    { int len = _strlen((yyvsp[0].sval)), i = 2, err = 0;
		  char * hexa = (yyvsp[0].sval);
	 	  sql_subtype t;
#ifdef HAVE_HGE
		  hge res = 0;
#else
		  lng res = 0;
#endif
		  /* skip leading '0' */
		  while (i < len && hexa[i] == '0')
		  	i++;

		  /* we only support positive values that fit in a signed 128-bit type,
		   * i.e., max. 63/127 bit => < 2^63/2^127 => < 0x800...
		   * (leading sign (-0x...) is handled separately elsewhere)
		   */
		  if (len - i < MAX_HEX_DIGITS || (len - i == MAX_HEX_DIGITS && hexa[i] < '8'))
		  	while (err == 0 && i < len)
		  	{
				res <<= 4;
				if ('0'<= hexa[i] && hexa[i] <= '9')
					res = res + (hexa[i] - '0');
				else if ('A' <= hexa[i] && hexa[i] <= 'F')
					res = res + (hexa[i] - 'A' + 10);
				else if ('a' <= hexa[i] && hexa[i] <= 'f')
					res = res + (hexa[i] - 'a' + 10);
				else
					err = 1;
		  		i++;
			}
		  else
			err = 1;

		  if (err == 0) {
		  	assert(res >= 0);

		  	/* use smallest type that can accommodate the given value */
			if (res <= GDK_bte_max)
				sql_find_subtype(&t, "tinyint", 8, 0 );
			else if (res <= GDK_sht_max)
				sql_find_subtype(&t, "smallint", 16, 0 );
		  	else if (res <= GDK_int_max)
				sql_find_subtype(&t, "int", 32, 0 );
			else if (res <= GDK_lng_max)
				sql_find_subtype(&t, "bigint", 64, 0 );
#ifdef HAVE_HGE
			else if (res <= GDK_hge_max && have_hge)
				sql_find_subtype(&t, "hugeint", 128, 0 );
#endif
			else
				err = 1;
		  }

		  if (err != 0) {
			char *msg = sql_message("\b22003!invalid hexadecimal number or hexadecimal too large (%s)", (yyvsp[0].sval));

			yyerror(m, msg);
			_DELETE(msg);
			(yyval.sym) = NULL;
			YYABORT;
		  } else {
			(yyval.sym) = _newAtomNode( atom_int(SA, &t, res));
		  }
		}
#line 11349 "y.tab.c" /* yacc.c:1646  */
    break;

  case 758:
#line 4250 "sql_parser.y" /* yacc.c:1646  */
    { int err = 0, len = sizeof(lng);
		  lng value, *p = &value;
		  sql_subtype t;

		  lngFromStr((yyvsp[0].sval), &len, &p);
		  if (value == lng_nil)
		  	err = 2;

		  if (!err) {
		    if ((value > GDK_lng_min && value <= GDK_lng_max))
#if SIZEOF_OID == SIZEOF_INT
		  	  sql_find_subtype(&t, "oid", 31, 0 );
#else
		  	  sql_find_subtype(&t, "oid", 63, 0 );
#endif
		    else
			  err = 1;
		  }

		  if (err) {
			char *msg = sql_message("\b22003!OID value too large or not a number (%s)", (yyvsp[0].sval));

			yyerror(m, msg);
			_DELETE(msg);
			(yyval.sym) = NULL;
			YYABORT;
		  } else {
		  	(yyval.sym) = _newAtomNode( atom_int(SA, &t, value));
		  }
		}
#line 11384 "y.tab.c" /* yacc.c:1646  */
    break;

  case 759:
#line 4281 "sql_parser.y" /* yacc.c:1646  */
    { int digits = _strlen((yyvsp[0].sval)), err = 0;
#ifdef HAVE_HGE
		  hge value, *p = &value;
		  int len = sizeof(hge);
#else
		  lng value, *p = &value;
		  int len = sizeof(lng);
#endif
		  sql_subtype t;

#ifdef HAVE_HGE
		  hgeFromStr((yyvsp[0].sval), &len, &p);
		  if (value == hge_nil)
		  	err = 2;
#else
		  lngFromStr((yyvsp[0].sval), &len, &p);
		  if (value == lng_nil)
		  	err = 2;
#endif

		  /* find the most suitable data type for the given number */
		  if (!err) {
		    int bits = digits2bits(digits);
		    if (value > GDK_bte_min && value <= GDK_bte_max)
		  	  sql_find_subtype(&t, "tinyint", bits, 0 );
		    else if (value > GDK_sht_min && value <= GDK_sht_max)
		  	  sql_find_subtype(&t, "smallint", bits, 0 );
		    else if (value > GDK_int_min && value <= GDK_int_max)
		  	  sql_find_subtype(&t, "int", bits, 0 );
		    else if (value > GDK_lng_min && value <= GDK_lng_max)
		  	  sql_find_subtype(&t, "bigint", bits, 0 );
#ifdef HAVE_HGE
		    else if (value > GDK_hge_min && value <= GDK_hge_max && have_hge)
		  	  sql_find_subtype(&t, "hugeint", bits, 0 );
#endif
		    else
			  err = 1;
		  }

		  if (err) {
			char *msg = sql_message("\b22003!integer value too large or not a number (%s)", (yyvsp[0].sval));

			yyerror(m, msg);
			_DELETE(msg);
			(yyval.sym) = NULL;
			YYABORT;
		  } else {
		  	(yyval.sym) = _newAtomNode( atom_int(SA, &t, value));
		  }
		}
#line 11439 "y.tab.c" /* yacc.c:1646  */
    break;

  case 760:
#line 4332 "sql_parser.y" /* yacc.c:1646  */
    { char *s = strip_extra_zeros(sa_strdup(SA, (yyvsp[0].sval)));
		  char *dot = strchr(s, '.');
		  int digits = _strlen(s) - 1;
		  int scale = digits - (int) (dot-s);
		  sql_subtype t;

		  if (digits <= 0)
			digits = 1;
		  if (digits <= MAX_DEC_DIGITS) {
		  	double val = strtod((yyvsp[0].sval),NULL);
#ifdef HAVE_HGE
		  	hge value = decimal_from_str(s, NULL);
#else
		  	lng value = decimal_from_str(s, NULL);
#endif

		  	if (*s == '+' || *s == '-')
				digits --;
		  	sql_find_subtype(&t, "decimal", digits, scale );
		  	(yyval.sym) = _newAtomNode( atom_dec(SA, &t, value, val));
		   } else {
			char *p = (yyvsp[0].sval);
			double val;

			errno = 0;
			val = strtod((yyvsp[0].sval),&p);
			if (p == (yyvsp[0].sval) || val == dbl_nil || (errno == ERANGE && (val < -1 || val > 1))) {
				char *msg = sql_message("\b22003!double value too large or not a number (%s)", (yyvsp[0].sval));

				yyerror(m, msg);
				_DELETE(msg);
				(yyval.sym) = NULL;
				YYABORT;
			}
		  	sql_find_subtype(&t, "double", 51, 0 );
		  	(yyval.sym) = _newAtomNode(atom_float(SA, &t, val));
		   }
		}
#line 11482 "y.tab.c" /* yacc.c:1646  */
    break;

  case 761:
#line 4371 "sql_parser.y" /* yacc.c:1646  */
    { sql_subtype t;
  		  char *p = (yyvsp[0].sval);
		  double val;

		  errno = 0;
 		  val = strtod((yyvsp[0].sval),&p);
		  if (p == (yyvsp[0].sval) || val == dbl_nil || (errno == ERANGE && (val < -1 || val > 1))) {
			char *msg = sql_message("\b22003!double value too large or not a number (%s)", (yyvsp[0].sval));

			yyerror(m, msg);
			_DELETE(msg);
			(yyval.sym) = NULL;
			YYABORT;
		  }
		  sql_find_subtype(&t, "double", 51, 0 );
		  (yyval.sym) = _newAtomNode(atom_float(SA, &t, val)); }
#line 11503 "y.tab.c" /* yacc.c:1646  */
    break;

  case 762:
#line 4388 "sql_parser.y" /* yacc.c:1646  */
    { sql_subtype t;
		  atom *a;
		  int r;

 		  r = sql_find_subtype(&t, "date", 0, 0 );
		  if (!r || (a = atom_general(SA, &t, (yyvsp[0].sval))) == NULL) {
			char *msg = sql_message("\b22007!incorrect date value (%s)", (yyvsp[0].sval));

			yyerror(m, msg);
			_DELETE(msg);
			(yyval.sym) = NULL;
			YYABORT;
		  } else {
		  	(yyval.sym) = _newAtomNode(a);
		} }
#line 11523 "y.tab.c" /* yacc.c:1646  */
    break;

  case 763:
#line 4404 "sql_parser.y" /* yacc.c:1646  */
    { sql_subtype t;
		  atom *a;
		  int r;

	          r = sql_find_subtype(&t, ((yyvsp[-1].bval))?"timetz":"time", (yyvsp[-2].i_val), 0);
		  if (!r || (a = atom_general(SA, &t, (yyvsp[0].sval))) == NULL) {
			char *msg = sql_message("\b22007!incorrect time value (%s)", (yyvsp[0].sval));

			yyerror(m, msg);
			_DELETE(msg);
			(yyval.sym) = NULL;
			YYABORT;
		  } else {
		  	(yyval.sym) = _newAtomNode(a);
		} }
#line 11543 "y.tab.c" /* yacc.c:1646  */
    break;

  case 764:
#line 4420 "sql_parser.y" /* yacc.c:1646  */
    { sql_subtype t;
		  atom *a;
		  int r;

 		  r = sql_find_subtype(&t, ((yyvsp[-1].bval))?"timestamptz":"timestamp",(yyvsp[-2].i_val),0);
		  if (!r || (a = atom_general(SA, &t, (yyvsp[0].sval))) == NULL) {
			char *msg = sql_message("\b22007!incorrect timestamp value (%s)", (yyvsp[0].sval));

			yyerror(m, msg);
			_DELETE(msg);
			(yyval.sym) = NULL;
			YYABORT;
		  } else {
		  	(yyval.sym) = _newAtomNode(a);
		} }
#line 11563 "y.tab.c" /* yacc.c:1646  */
    break;

  case 766:
#line 4437 "sql_parser.y" /* yacc.c:1646  */
    { sql_subtype t;
		  atom *a= 0;
		  int r;

		  (yyval.sym) = NULL;
 		  r = sql_find_subtype(&t, "blob", 0, 0);
	          if (r && (a = atom_general(SA, &t, (yyvsp[0].sval))) != NULL)
			(yyval.sym) = _newAtomNode(a);
		  if (!(yyval.sym)) {
			char *msg = sql_message("\b22M28!incorrect blob %s", (yyvsp[0].sval));

			yyerror(m, msg);
			_DELETE(msg);
			YYABORT;
		  }
		}
#line 11584 "y.tab.c" /* yacc.c:1646  */
    break;

  case 767:
#line 4454 "sql_parser.y" /* yacc.c:1646  */
    { sql_subtype t;
		  atom *a= 0;
		  int r;

		  (yyval.sym) = NULL;
		  r = sql_find_subtype(&t, (yyvsp[-1].sval), 0, 0);
	          if (r && (a = atom_general(SA, &t, (yyvsp[0].sval))) != NULL)
			(yyval.sym) = _newAtomNode(a);
		  if (!(yyval.sym)) {
			char *msg = sql_message("\b22000!incorrect %s %s", (yyvsp[-1].sval), (yyvsp[0].sval));

			yyerror(m, msg);
			_DELETE(msg);
			YYABORT;
		  }
		}
#line 11605 "y.tab.c" /* yacc.c:1646  */
    break;

  case 768:
#line 4471 "sql_parser.y" /* yacc.c:1646  */
    { sql_subtype t; 
		  atom *a = 0;
		  int r;

		  (yyval.sym) = NULL;
		  r = sql_find_subtype(&t, (yyvsp[-1].sval), 0, 0);
	          if (r && (a = atom_general(SA, &t, (yyvsp[0].sval))) != NULL)
			(yyval.sym) = _newAtomNode(a);
		  if (!(yyval.sym)) {
			char *msg = sql_message("\b22000!incorrect %s %s", (yyvsp[-1].sval), (yyvsp[0].sval));

			yyerror(m, msg);
			_DELETE(msg);
			YYABORT;
		  }
		}
#line 11626 "y.tab.c" /* yacc.c:1646  */
    break;

  case 769:
#line 4488 "sql_parser.y" /* yacc.c:1646  */
    {
		  sql_type *t = mvc_bind_type(m, (yyvsp[-1].sval));
		  atom *a;

		  (yyval.sym) = NULL;
		  if (t) {
		  	sql_subtype tpe;
			sql_init_subtype(&tpe, t, 0, 0);
			a = atom_general(SA, &tpe, (yyvsp[0].sval));
			if (a)
				(yyval.sym) = _newAtomNode(a);
		  }
		  if (!t || !(yyval.sym)) {
			char *msg = sql_message("\b22000!type (%s) unknown", (yyvsp[-1].sval));

			yyerror(m, msg);
			_DELETE(msg);
			YYABORT;
		  }
		}
#line 11651 "y.tab.c" /* yacc.c:1646  */
    break;

  case 770:
#line 4509 "sql_parser.y" /* yacc.c:1646  */
    { sql_subtype t;
		  sql_find_subtype(&t, "boolean", 0, 0 );
		  (yyval.sym) = _newAtomNode( atom_bool(SA, &t, FALSE)); }
#line 11659 "y.tab.c" /* yacc.c:1646  */
    break;

  case 771:
#line 4513 "sql_parser.y" /* yacc.c:1646  */
    { sql_subtype t;
		  sql_find_subtype(&t, "boolean", 0, 0 );
		  (yyval.sym) = _newAtomNode( atom_bool(SA, &t, TRUE)); }
#line 11667 "y.tab.c" /* yacc.c:1646  */
    break;

  case 772:
#line 4519 "sql_parser.y" /* yacc.c:1646  */
    { 
		sql_subtype t;
		int sk, ek, sp, ep, tpe;
	  	lng i = 0;
		int r = 0;

		(yyval.sym) = NULL;
	  	if ( (tpe = parse_interval_qualifier( m, (yyvsp[0].l), &sk, &ek, &sp, &ep )) < 0){
			yyerror(m, "incorrect interval");
			YYABORT;
	  	} else {
			int d = inttype2digits(sk, ek);
			if (tpe == 0){
				r=sql_find_subtype(&t, "month_interval", d, 0);
			} else {
				r=sql_find_subtype(&t, "sec_interval", d, 0);
			}
	  	}
	  	if (!r || (tpe = parse_interval( m, (yyvsp[-2].i_val), (yyvsp[-1].sval), sk, ek, sp, ep, &i)) < 0) { 
			yyerror(m, "incorrect interval");
			(yyval.sym) = NULL;
			YYABORT;
	  	} else {
			/* count the number of digits in the input */
/*
			lng cpyval = i, inlen = 1;

			cpyval /= qualifier2multiplier(ek);
			while (cpyval /= 10)
				inlen++;
		    	if (inlen > t.digits) {
				char *msg = sql_message("\b22006!incorrect interval (" LLFMT " > %d)", inlen, t.digits);
				yyerror(m, msg);
				$$ = NULL;
				YYABORT;
			}
*/
	  		(yyval.sym) = _newAtomNode( atom_int(SA, &t, i));
	  	}
	}
#line 11712 "y.tab.c" /* yacc.c:1646  */
    break;

  case 773:
#line 4564 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string(L(), (yyvsp[0].sval)); }
#line 11718 "y.tab.c" /* yacc.c:1646  */
    break;

  case 774:
#line 4565 "sql_parser.y" /* yacc.c:1646  */
    {
				  m->scanner.schema = (yyvsp[-2].sval);
				  (yyval.l) = append_string(
					append_string(L(), (yyvsp[-2].sval)), (yyvsp[0].sval));}
#line 11727 "y.tab.c" /* yacc.c:1646  */
    break;

  case 775:
#line 4569 "sql_parser.y" /* yacc.c:1646  */
    {
				  m->scanner.schema = (yyvsp[-4].sval);
				  (yyval.l) = append_string(
					append_string(
						append_string(L(), (yyvsp[-4].sval)), 
						(yyvsp[-2].sval)), 
					(yyvsp[0].sval))
				;}
#line 11740 "y.tab.c" /* yacc.c:1646  */
    break;

  case 776:
#line 4580 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string(
				L(), (yyvsp[0].sval)); }
#line 11747 "y.tab.c" /* yacc.c:1646  */
    break;

  case 777:
#line 4583 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string(
				append_string(
				 L(), (yyvsp[-2].sval)), (yyvsp[0].sval));}
#line 11755 "y.tab.c" /* yacc.c:1646  */
    break;

  case 778:
#line 4588 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string(
				append_string(
				 append_string(
				  L(), (yyvsp[-4].sval)), (yyvsp[-2].sval)), (yyvsp[0].sval));}
#line 11764 "y.tab.c" /* yacc.c:1646  */
    break;

  case 779:
#line 4596 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_symbol(l, (yyvsp[-3].sym));
	  append_type(l, &(yyvsp[-1].type));
	  (yyval.sym) = _symbol_create_list( SQL_CAST, l ); }
#line 11773 "y.tab.c" /* yacc.c:1646  */
    break;

  case 780:
#line 4602 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_symbol(l, (yyvsp[-3].sym));
	  append_type(l, &(yyvsp[-1].type));
	  (yyval.sym) = _symbol_create_list( SQL_CAST, l ); }
#line 11782 "y.tab.c" /* yacc.c:1646  */
    break;

  case 782:
#line 4614 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_NULLIF,
		   append_symbol(
		    append_symbol(
		     L(), (yyvsp[-3].sym)), (yyvsp[-1].sym))); }
#line 11791 "y.tab.c" /* yacc.c:1646  */
    break;

  case 783:
#line 4619 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_COALESCE, (yyvsp[-1].l)); }
#line 11797 "y.tab.c" /* yacc.c:1646  */
    break;

  case 784:
#line 4621 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_CASE,
		   append_symbol(
		    append_list(
		     append_symbol(
		      L(),(yyvsp[-3].sym)),(yyvsp[-2].l)),(yyvsp[-1].sym))); }
#line 11807 "y.tab.c" /* yacc.c:1646  */
    break;

  case 785:
#line 4627 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_CASE,
		   append_symbol(
		    append_list(
		     L(),(yyvsp[-2].l)),(yyvsp[-1].sym))); }
#line 11816 "y.tab.c" /* yacc.c:1646  */
    break;

  case 786:
#line 4635 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol( L(), (yyvsp[0].sym)); }
#line 11822 "y.tab.c" /* yacc.c:1646  */
    break;

  case 787:
#line 4637 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol( (yyvsp[-2].l), (yyvsp[0].sym)); }
#line 11828 "y.tab.c" /* yacc.c:1646  */
    break;

  case 788:
#line 4642 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol( L(), (yyvsp[-2].sym));
			  (yyval.l) = append_symbol( (yyval.l), (yyvsp[0].sym));
			}
#line 11836 "y.tab.c" /* yacc.c:1646  */
    break;

  case 789:
#line 4646 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol( (yyvsp[-2].l), (yyvsp[0].sym)); }
#line 11842 "y.tab.c" /* yacc.c:1646  */
    break;

  case 790:
#line 4652 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_WHEN,
			   append_symbol(
			    append_symbol(
			     L(), (yyvsp[-2].sym)),(yyvsp[0].sym))); }
#line 11851 "y.tab.c" /* yacc.c:1646  */
    break;

  case 791:
#line 4660 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol( L(), (yyvsp[0].sym));}
#line 11857 "y.tab.c" /* yacc.c:1646  */
    break;

  case 792:
#line 4662 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol( (yyvsp[-1].l), (yyvsp[0].sym)); }
#line 11863 "y.tab.c" /* yacc.c:1646  */
    break;

  case 793:
#line 4667 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_WHEN,
			   append_symbol(
			    append_symbol(
			     L(), (yyvsp[-2].sym)),(yyvsp[0].sym))); }
#line 11872 "y.tab.c" /* yacc.c:1646  */
    break;

  case 794:
#line 4675 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol( L(), (yyvsp[0].sym)); }
#line 11878 "y.tab.c" /* yacc.c:1646  */
    break;

  case 795:
#line 4677 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol( (yyvsp[-1].l), (yyvsp[0].sym)); }
#line 11884 "y.tab.c" /* yacc.c:1646  */
    break;

  case 796:
#line 4681 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 11890 "y.tab.c" /* yacc.c:1646  */
    break;

  case 797:
#line 4682 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 11896 "y.tab.c" /* yacc.c:1646  */
    break;

  case 799:
#line 4692 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = (yyvsp[0].i_val);
		  if ((yyval.i_val) <= 0) {
			(yyval.i_val) = -1;
			yyerror(m, "Positive value greater than 0 expected");
			YYABORT;
		  }
		}
#line 11908 "y.tab.c" /* yacc.c:1646  */
    break;

  case 800:
#line 4703 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l_val) = (yyvsp[0].l_val);
		  if ((yyval.l_val) <= 0) {
			(yyval.l_val) = -1;
			yyerror(m, "Positive value greater than 0 expected");
			YYABORT;
		  }
		}
#line 11920 "y.tab.c" /* yacc.c:1646  */
    break;

  case 801:
#line 4714 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.w_val) = (yyvsp[0].w_val);
		  if ((yyval.w_val) <= 0) {
			(yyval.w_val) = -1;
			yyerror(m, "Positive value greater than 0 expected");
			YYABORT;
		  }
		}
#line 11932 "y.tab.c" /* yacc.c:1646  */
    break;

  case 802:
#line 4724 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l_val) = (yyvsp[0].l_val);
		  if ((yyval.l_val) < 0) {
			(yyval.l_val) = -1;
			yyerror(m, "Positive value expected");
			YYABORT;
		  }
		}
#line 11944 "y.tab.c" /* yacc.c:1646  */
    break;

  case 803:
#line 4734 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.w_val) = (yyvsp[0].w_val);
		  if ((yyval.w_val) < 0) {
			(yyval.w_val) = -1;
			yyerror(m, "Positive value expected");
			YYABORT;
		  }
		}
#line 11956 "y.tab.c" /* yacc.c:1646  */
    break;

  case 804:
#line 4744 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = (yyvsp[0].i_val);
		  if ((yyval.i_val) < 0) {
			(yyval.i_val) = -1;
			yyerror(m, "Positive value expected");
			YYABORT;
		  }
		}
#line 11968 "y.tab.c" /* yacc.c:1646  */
    break;

  case 805:
#line 4755 "sql_parser.y" /* yacc.c:1646  */
    { sql_find_subtype(&(yyval.type), "char", 1, 0); }
#line 11974 "y.tab.c" /* yacc.c:1646  */
    break;

  case 806:
#line 4757 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.type).type = NULL;
			  yyerror(m, "CHARACTER VARYING needs a mandatory length specification");
			  YYABORT;
			}
#line 11983 "y.tab.c" /* yacc.c:1646  */
    break;

  case 807:
#line 4761 "sql_parser.y" /* yacc.c:1646  */
    { sql_find_subtype(&(yyval.type), "clob", 0, 0); }
#line 11989 "y.tab.c" /* yacc.c:1646  */
    break;

  case 808:
#line 4763 "sql_parser.y" /* yacc.c:1646  */
    { sql_find_subtype(&(yyval.type), "char", (yyvsp[-1].i_val), 0); }
#line 11995 "y.tab.c" /* yacc.c:1646  */
    break;

  case 809:
#line 4765 "sql_parser.y" /* yacc.c:1646  */
    { sql_find_subtype(&(yyval.type), "varchar", (yyvsp[-1].i_val), 0); }
#line 12001 "y.tab.c" /* yacc.c:1646  */
    break;

  case 810:
#line 4767 "sql_parser.y" /* yacc.c:1646  */
    { sql_find_subtype(&(yyval.type), "clob", (yyvsp[-1].i_val), 0);
			  /* NOTE: CLOB may be called as CLOB(2K) which is equivalent
			   *       to CLOB(2048).  Due to 'nonzero' it is not possible
			   *       to enter this as the parser rejects it.  However it
			   *       might be a ToDo for the future.
			   *       See p. 125 SQL-99
			   */
			}
#line 12014 "y.tab.c" /* yacc.c:1646  */
    break;

  case 811:
#line 4775 "sql_parser.y" /* yacc.c:1646  */
    { sql_find_subtype(&(yyval.type), "blob", 0, 0); }
#line 12020 "y.tab.c" /* yacc.c:1646  */
    break;

  case 812:
#line 4777 "sql_parser.y" /* yacc.c:1646  */
    { sql_find_subtype(&(yyval.type), "blob", (yyvsp[-1].i_val), 0);
			  /* NOTE: BLOB may be called as BLOB(2K) which is equivalent
			   *       to BLOB(2048).  Due to 'nonzero' it is not possible
			   *       to enter this as the parser rejects it.  However it
			   *       might be a ToDo for the future.
			   *       See p. 85 SQL-99
			   */
			}
#line 12033 "y.tab.c" /* yacc.c:1646  */
    break;

  case 813:
#line 4785 "sql_parser.y" /* yacc.c:1646  */
    { sql_find_subtype(&(yyval.type), "tinyint", 0, 0); }
#line 12039 "y.tab.c" /* yacc.c:1646  */
    break;

  case 814:
#line 4786 "sql_parser.y" /* yacc.c:1646  */
    { sql_find_subtype(&(yyval.type), "smallint", 0, 0); }
#line 12045 "y.tab.c" /* yacc.c:1646  */
    break;

  case 815:
#line 4787 "sql_parser.y" /* yacc.c:1646  */
    { sql_find_subtype(&(yyval.type), "int", 0, 0); }
#line 12051 "y.tab.c" /* yacc.c:1646  */
    break;

  case 816:
#line 4788 "sql_parser.y" /* yacc.c:1646  */
    { sql_find_subtype(&(yyval.type), "bigint", 0, 0); }
#line 12057 "y.tab.c" /* yacc.c:1646  */
    break;

  case 817:
#line 4789 "sql_parser.y" /* yacc.c:1646  */
    { sql_find_subtype(&(yyval.type), "hugeint", 0, 0); }
#line 12063 "y.tab.c" /* yacc.c:1646  */
    break;

  case 818:
#line 4791 "sql_parser.y" /* yacc.c:1646  */
    { sql_find_subtype(&(yyval.type), "decimal", 18, 3); }
#line 12069 "y.tab.c" /* yacc.c:1646  */
    break;

  case 819:
#line 4793 "sql_parser.y" /* yacc.c:1646  */
    { 
			  int d = (yyvsp[-1].i_val);
			  if (d > MAX_DEC_DIGITS) {
				char *msg = sql_message("\b22003!decimal of %d digits are not supported", d);
				yyerror(m, msg);
				_DELETE(msg);
				(yyval.type).type = NULL;
				YYABORT;
			  } else {
			        sql_find_subtype(&(yyval.type), "decimal", d, 0); 
			  }
			}
#line 12086 "y.tab.c" /* yacc.c:1646  */
    break;

  case 820:
#line 4806 "sql_parser.y" /* yacc.c:1646  */
    { 
			  int d = (yyvsp[-3].i_val);
			  int s = (yyvsp[-1].i_val);
			  if (s > d || d > MAX_DEC_DIGITS) {
				char *msg = NULL;
				if (s > d)
					msg = sql_message("\b22003!scale (%d) should be less or equal to the precision (%d)", s, d);
				else
					msg = sql_message("\b22003!decimal(%d,%d) isn't supported because P=%d > %d", d, s, d, MAX_DEC_DIGITS);
				yyerror(m, msg);
				_DELETE(msg);
				(yyval.type).type = NULL;
				YYABORT;
			  } else {
				sql_find_subtype(&(yyval.type), "decimal", d, s);
			  }
			}
#line 12108 "y.tab.c" /* yacc.c:1646  */
    break;

  case 821:
#line 4823 "sql_parser.y" /* yacc.c:1646  */
    { sql_find_subtype(&(yyval.type), "double", 0, 0); }
#line 12114 "y.tab.c" /* yacc.c:1646  */
    break;

  case 822:
#line 4825 "sql_parser.y" /* yacc.c:1646  */
    { if ((yyvsp[-1].i_val) > 0 && (yyvsp[-1].i_val) <= 24) {
				sql_find_subtype(&(yyval.type), "real", (yyvsp[-1].i_val), 0);
			  } else if ((yyvsp[-1].i_val) > 24 && (yyvsp[-1].i_val) <= 53) {
				sql_find_subtype(&(yyval.type), "double", (yyvsp[-1].i_val), 0);
			  } else {
				char *msg = sql_message("\b22003!number of digits for FLOAT values should be between 1 and 53");

				yyerror(m, msg);
				_DELETE(msg);
				(yyval.type).type = NULL;
				YYABORT;
			  }
			}
#line 12132 "y.tab.c" /* yacc.c:1646  */
    break;

  case 823:
#line 4839 "sql_parser.y" /* yacc.c:1646  */
    { if ((yyvsp[-1].i_val) >= (yyvsp[-3].i_val)) {
				char *msg = sql_message("\b22003!precision(%d) should be less than number of digits(%d)", (yyvsp[-1].i_val), (yyvsp[-3].i_val));

				yyerror(m, msg);
				_DELETE(msg);
				(yyval.type).type = NULL;
				YYABORT;
			  } else if ((yyvsp[-3].i_val) > 0 && (yyvsp[-3].i_val) <= 24) {
				sql_find_subtype(&(yyval.type), "real", (yyvsp[-3].i_val), (yyvsp[-1].i_val));
			  } else if ((yyvsp[-3].i_val) > 24 && (yyvsp[-3].i_val) <= 53) {
				sql_find_subtype(&(yyval.type), "double", (yyvsp[-3].i_val), (yyvsp[-1].i_val));
			  } else {
				char *msg = sql_message("\b22003!number of digits for FLOAT values should be between 1 and 53");
				yyerror(m, msg);
				_DELETE(msg);
				(yyval.type).type = NULL;
				YYABORT;
			  }
			}
#line 12156 "y.tab.c" /* yacc.c:1646  */
    break;

  case 824:
#line 4858 "sql_parser.y" /* yacc.c:1646  */
    { sql_find_subtype(&(yyval.type), "double", 0, 0); }
#line 12162 "y.tab.c" /* yacc.c:1646  */
    break;

  case 825:
#line 4859 "sql_parser.y" /* yacc.c:1646  */
    { sql_find_subtype(&(yyval.type), "double", 0, 0); }
#line 12168 "y.tab.c" /* yacc.c:1646  */
    break;

  case 826:
#line 4860 "sql_parser.y" /* yacc.c:1646  */
    { sql_find_subtype(&(yyval.type), "real", 0, 0); }
#line 12174 "y.tab.c" /* yacc.c:1646  */
    break;

  case 829:
#line 4863 "sql_parser.y" /* yacc.c:1646  */
    { sql_find_subtype(&(yyval.type), (yyvsp[0].sval), 0, 0); }
#line 12180 "y.tab.c" /* yacc.c:1646  */
    break;

  case 830:
#line 4865 "sql_parser.y" /* yacc.c:1646  */
    { sql_find_subtype(&(yyval.type), (yyvsp[-3].sval), (yyvsp[-1].i_val), 0); }
#line 12186 "y.tab.c" /* yacc.c:1646  */
    break;

  case 831:
#line 4866 "sql_parser.y" /* yacc.c:1646  */
    { sql_find_subtype(&(yyval.type), (yyvsp[0].sval), 0, 0); }
#line 12192 "y.tab.c" /* yacc.c:1646  */
    break;

  case 832:
#line 4868 "sql_parser.y" /* yacc.c:1646  */
    { sql_find_subtype(&(yyval.type), (yyvsp[-3].sval), (yyvsp[-1].i_val), 0); }
#line 12198 "y.tab.c" /* yacc.c:1646  */
    break;

  case 833:
#line 4870 "sql_parser.y" /* yacc.c:1646  */
    { if ((yyvsp[-1].i_val) >= (yyvsp[-3].i_val)) {
				char *msg = sql_message("\b22003!precision(%d) should be less than number of digits(%d)", (yyvsp[-1].i_val), (yyvsp[-3].i_val));

				yyerror(m, msg);
				_DELETE(msg);
				(yyval.type).type = NULL;
				YYABORT;
			  } else {
			 	sql_find_subtype(&(yyval.type), (yyvsp[-5].sval), (yyvsp[-3].i_val), (yyvsp[-1].i_val));
			  }
			}
#line 12214 "y.tab.c" /* yacc.c:1646  */
    break;

  case 834:
#line 4881 "sql_parser.y" /* yacc.c:1646  */
    {
			  sql_type *t = mvc_bind_type(m, (yyvsp[0].sval));
			  if (!t) {
				char *msg = sql_message("\b22000!type (%s) unknown", (yyvsp[0].sval));

				yyerror(m, msg);
				_DELETE(msg);
				(yyval.type).type = NULL;
				YYABORT;
			  } else {
				sql_init_subtype(&(yyval.type), t, 0, 0);
			  }
			}
#line 12232 "y.tab.c" /* yacc.c:1646  */
    break;

  case 835:
#line 4896 "sql_parser.y" /* yacc.c:1646  */
    {
			  sql_type *t = mvc_bind_type(m, (yyvsp[-3].sval));
			  if (!t) {
				char *msg = sql_message("\b22000!type (%s) unknown", (yyvsp[-3].sval));

				yyerror(m, msg);
				_DELETE(msg);
				(yyval.type).type = NULL;
				YYABORT;
			  } else {
				sql_init_subtype(&(yyval.type), t, (yyvsp[-1].i_val), 0);
			  }
			}
#line 12250 "y.tab.c" /* yacc.c:1646  */
    break;

  case 836:
#line 4914 "sql_parser.y" /* yacc.c:1646  */
    { 	char *t = sql_bind_alias((yyvsp[0].sval));
	  	if (!t) {
			char *msg = sql_message("\b22000!type (%s) unknown", (yyvsp[0].sval));

			yyerror(m, msg);
			_DELETE(msg);
			(yyval.sval) = NULL;
			YYABORT;
		}
		(yyval.sval) = t;
	}
#line 12266 "y.tab.c" /* yacc.c:1646  */
    break;

  case 837:
#line 4928 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 12272 "y.tab.c" /* yacc.c:1646  */
    break;

  case 838:
#line 4929 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[-1].sval); }
#line 12278 "y.tab.c" /* yacc.c:1646  */
    break;

  case 839:
#line 4933 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 12284 "y.tab.c" /* yacc.c:1646  */
    break;

  case 840:
#line 4934 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 12290 "y.tab.c" /* yacc.c:1646  */
    break;

  case 841:
#line 4935 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[-2].sval); }
#line 12296 "y.tab.c" /* yacc.c:1646  */
    break;

  case 842:
#line 4938 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 12302 "y.tab.c" /* yacc.c:1646  */
    break;

  case 843:
#line 4939 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[-2].sval); }
#line 12308 "y.tab.c" /* yacc.c:1646  */
    break;

  case 846:
#line 4947 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 12314 "y.tab.c" /* yacc.c:1646  */
    break;

  case 847:
#line 4948 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 12320 "y.tab.c" /* yacc.c:1646  */
    break;

  case 848:
#line 4949 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 12326 "y.tab.c" /* yacc.c:1646  */
    break;

  case 849:
#line 4950 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 12332 "y.tab.c" /* yacc.c:1646  */
    break;

  case 850:
#line 4951 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 12338 "y.tab.c" /* yacc.c:1646  */
    break;

  case 851:
#line 4952 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 12344 "y.tab.c" /* yacc.c:1646  */
    break;

  case 852:
#line 4956 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 12350 "y.tab.c" /* yacc.c:1646  */
    break;

  case 853:
#line 4957 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 12356 "y.tab.c" /* yacc.c:1646  */
    break;

  case 854:
#line 4958 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 12362 "y.tab.c" /* yacc.c:1646  */
    break;

  case 855:
#line 4959 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 12368 "y.tab.c" /* yacc.c:1646  */
    break;

  case 856:
#line 4960 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 12374 "y.tab.c" /* yacc.c:1646  */
    break;

  case 857:
#line 4961 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 12380 "y.tab.c" /* yacc.c:1646  */
    break;

  case 858:
#line 4962 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 12386 "y.tab.c" /* yacc.c:1646  */
    break;

  case 860:
#line 4967 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "large"); }
#line 12392 "y.tab.c" /* yacc.c:1646  */
    break;

  case 861:
#line 4968 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "name"); }
#line 12398 "y.tab.c" /* yacc.c:1646  */
    break;

  case 862:
#line 4969 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "object"); }
#line 12404 "y.tab.c" /* yacc.c:1646  */
    break;

  case 863:
#line 4970 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "password"); }
#line 12410 "y.tab.c" /* yacc.c:1646  */
    break;

  case 864:
#line 4971 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "path"); }
#line 12416 "y.tab.c" /* yacc.c:1646  */
    break;

  case 865:
#line 4972 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "precision"); }
#line 12422 "y.tab.c" /* yacc.c:1646  */
    break;

  case 866:
#line 4973 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "privileges"); }
#line 12428 "y.tab.c" /* yacc.c:1646  */
    break;

  case 867:
#line 4974 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "role"); }
#line 12434 "y.tab.c" /* yacc.c:1646  */
    break;

  case 868:
#line 4975 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "size"); }
#line 12440 "y.tab.c" /* yacc.c:1646  */
    break;

  case 869:
#line 4976 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "type"); }
#line 12446 "y.tab.c" /* yacc.c:1646  */
    break;

  case 870:
#line 4977 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "release"); }
#line 12452 "y.tab.c" /* yacc.c:1646  */
    break;

  case 871:
#line 4978 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "value"); }
#line 12458 "y.tab.c" /* yacc.c:1646  */
    break;

  case 872:
#line 4979 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "zone"); }
#line 12464 "y.tab.c" /* yacc.c:1646  */
    break;

  case 873:
#line 4981 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "action"); }
#line 12470 "y.tab.c" /* yacc.c:1646  */
    break;

  case 874:
#line 4982 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "as"); }
#line 12476 "y.tab.c" /* yacc.c:1646  */
    break;

  case 875:
#line 4983 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "authorization"); }
#line 12482 "y.tab.c" /* yacc.c:1646  */
    break;

  case 876:
#line 4984 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "column"); }
#line 12488 "y.tab.c" /* yacc.c:1646  */
    break;

  case 877:
#line 4985 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "cycle"); }
#line 12494 "y.tab.c" /* yacc.c:1646  */
    break;

  case 878:
#line 4986 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "distinct"); }
#line 12500 "y.tab.c" /* yacc.c:1646  */
    break;

  case 879:
#line 4987 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "increment"); }
#line 12506 "y.tab.c" /* yacc.c:1646  */
    break;

  case 880:
#line 4988 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "maxvalue"); }
#line 12512 "y.tab.c" /* yacc.c:1646  */
    break;

  case 881:
#line 4989 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "minvalue"); }
#line 12518 "y.tab.c" /* yacc.c:1646  */
    break;

  case 882:
#line 4990 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "plan"); }
#line 12524 "y.tab.c" /* yacc.c:1646  */
    break;

  case 883:
#line 4991 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "schema"); }
#line 12530 "y.tab.c" /* yacc.c:1646  */
    break;

  case 884:
#line 4992 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "start"); }
#line 12536 "y.tab.c" /* yacc.c:1646  */
    break;

  case 885:
#line 4993 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "statement"); }
#line 12542 "y.tab.c" /* yacc.c:1646  */
    break;

  case 886:
#line 4994 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "table"); }
#line 12548 "y.tab.c" /* yacc.c:1646  */
    break;

  case 887:
#line 4996 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "cache"); }
#line 12554 "y.tab.c" /* yacc.c:1646  */
    break;

  case 888:
#line 4997 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "data"); }
#line 12560 "y.tab.c" /* yacc.c:1646  */
    break;

  case 889:
#line 4998 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "diagnostics"); }
#line 12566 "y.tab.c" /* yacc.c:1646  */
    break;

  case 890:
#line 4999 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "match"); }
#line 12572 "y.tab.c" /* yacc.c:1646  */
    break;

  case 891:
#line 5000 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "options"); }
#line 12578 "y.tab.c" /* yacc.c:1646  */
    break;

  case 892:
#line 5001 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "row"); }
#line 12584 "y.tab.c" /* yacc.c:1646  */
    break;

  case 893:
#line 5002 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "key"); }
#line 12590 "y.tab.c" /* yacc.c:1646  */
    break;

  case 894:
#line 5003 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "language"); }
#line 12596 "y.tab.c" /* yacc.c:1646  */
    break;

  case 895:
#line 5004 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "level"); }
#line 12602 "y.tab.c" /* yacc.c:1646  */
    break;

  case 896:
#line 5005 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "session"); }
#line 12608 "y.tab.c" /* yacc.c:1646  */
    break;

  case 897:
#line 5006 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "date"); }
#line 12614 "y.tab.c" /* yacc.c:1646  */
    break;

  case 898:
#line 5007 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "time"); }
#line 12620 "y.tab.c" /* yacc.c:1646  */
    break;

  case 899:
#line 5008 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "timestamp"); }
#line 12626 "y.tab.c" /* yacc.c:1646  */
    break;

  case 900:
#line 5009 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "interval"); }
#line 12632 "y.tab.c" /* yacc.c:1646  */
    break;

  case 901:
#line 5011 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "prepare"); }
#line 12638 "y.tab.c" /* yacc.c:1646  */
    break;

  case 902:
#line 5012 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "execute"); }
#line 12644 "y.tab.c" /* yacc.c:1646  */
    break;

  case 903:
#line 5013 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "explain"); }
#line 12650 "y.tab.c" /* yacc.c:1646  */
    break;

  case 904:
#line 5014 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "dot"); }
#line 12656 "y.tab.c" /* yacc.c:1646  */
    break;

  case 905:
#line 5015 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "debug"); }
#line 12662 "y.tab.c" /* yacc.c:1646  */
    break;

  case 906:
#line 5016 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "trace"); }
#line 12668 "y.tab.c" /* yacc.c:1646  */
    break;

  case 907:
#line 5017 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "text"); }
#line 12674 "y.tab.c" /* yacc.c:1646  */
    break;

  case 908:
#line 5018 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "auto_commit"); }
#line 12680 "y.tab.c" /* yacc.c:1646  */
    break;

  case 909:
#line 5019 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "no"); }
#line 12686 "y.tab.c" /* yacc.c:1646  */
    break;

  case 910:
#line 5021 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "strip"); }
#line 12692 "y.tab.c" /* yacc.c:1646  */
    break;

  case 911:
#line 5022 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "whitespace"); }
#line 12698 "y.tab.c" /* yacc.c:1646  */
    break;

  case 912:
#line 5023 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "passing"); }
#line 12704 "y.tab.c" /* yacc.c:1646  */
    break;

  case 913:
#line 5024 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "nil"); }
#line 12710 "y.tab.c" /* yacc.c:1646  */
    break;

  case 914:
#line 5025 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "ref"); }
#line 12716 "y.tab.c" /* yacc.c:1646  */
    break;

  case 915:
#line 5026 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "absent"); }
#line 12722 "y.tab.c" /* yacc.c:1646  */
    break;

  case 916:
#line 5027 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "empty"); }
#line 12728 "y.tab.c" /* yacc.c:1646  */
    break;

  case 917:
#line 5028 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "document"); }
#line 12734 "y.tab.c" /* yacc.c:1646  */
    break;

  case 918:
#line 5029 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "element"); }
#line 12740 "y.tab.c" /* yacc.c:1646  */
    break;

  case 919:
#line 5030 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "content"); }
#line 12746 "y.tab.c" /* yacc.c:1646  */
    break;

  case 920:
#line 5031 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "namespace"); }
#line 12752 "y.tab.c" /* yacc.c:1646  */
    break;

  case 921:
#line 5032 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "returning"); }
#line 12758 "y.tab.c" /* yacc.c:1646  */
    break;

  case 922:
#line 5033 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "location"); }
#line 12764 "y.tab.c" /* yacc.c:1646  */
    break;

  case 923:
#line 5034 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "id"); }
#line 12770 "y.tab.c" /* yacc.c:1646  */
    break;

  case 924:
#line 5035 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "according"); }
#line 12776 "y.tab.c" /* yacc.c:1646  */
    break;

  case 925:
#line 5036 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "uri"); }
#line 12782 "y.tab.c" /* yacc.c:1646  */
    break;

  case 926:
#line 5037 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "filter"); }
#line 12788 "y.tab.c" /* yacc.c:1646  */
    break;

  case 927:
#line 5038 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "temporary"); }
#line 12794 "y.tab.c" /* yacc.c:1646  */
    break;

  case 928:
#line 5039 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "temp"); }
#line 12800 "y.tab.c" /* yacc.c:1646  */
    break;

  case 929:
#line 5040 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "analyze"); }
#line 12806 "y.tab.c" /* yacc.c:1646  */
    break;

  case 930:
#line 5041 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "MinMax"); }
#line 12812 "y.tab.c" /* yacc.c:1646  */
    break;

  case 931:
#line 5042 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "storage"); }
#line 12818 "y.tab.c" /* yacc.c:1646  */
    break;

  case 932:
#line 5046 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string(L(), (yyvsp[0].sval)); }
#line 12824 "y.tab.c" /* yacc.c:1646  */
    break;

  case 933:
#line 5048 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string((yyvsp[-2].l), (yyvsp[0].sval)); }
#line 12830 "y.tab.c" /* yacc.c:1646  */
    break;

  case 934:
#line 5052 "sql_parser.y" /* yacc.c:1646  */
    { 
		lng l = (yyvsp[0].l_val);
#if SIZEOF_WRD == SIZEOF_INT

		if (l > GDK_int_max) {
			char *msg = sql_message("\b22000!constant (" LLFMT ") has wrong type (number expected)", l);

			yyerror(m, msg);
			_DELETE(msg);
			(yyval.w_val) = 0;
			YYABORT;
		}
#endif
		(yyval.w_val) = (wrd) l;
	}
#line 12850 "y.tab.c" /* yacc.c:1646  */
    break;

  case 935:
#line 5071 "sql_parser.y" /* yacc.c:1646  */
    {
		  char *end = NULL, *s = (yyvsp[0].sval);
		  int l = _strlen(s);

		  if (l <= 19) {
		  	(yyval.l_val) = strtoll(s,&end,10);
		  } else {
			(yyval.l_val) = 0;
		  }
		  if (s+l != end || errno == ERANGE) {
			char *msg = sql_message("\b22003!integer value too large or not a number (%s)", (yyvsp[0].sval));

			errno = 0;
			yyerror(m, msg);
			_DELETE(msg);
			(yyval.l_val) = 0;
			YYABORT;
		  }
		}
#line 12874 "y.tab.c" /* yacc.c:1646  */
    break;

  case 936:
#line 5093 "sql_parser.y" /* yacc.c:1646  */
    {
		  char *end = NULL, *s = (yyvsp[0].sval);
		  int l = _strlen(s);

		  if (l <= 10) {
		  	(yyval.i_val) = strtol(s,&end,10);
		  } else {
			(yyval.i_val) = 0;
		  }
		  if (s+l != end || errno == ERANGE) {
			char *msg = sql_message("\b22003!integer value too large or not a number (%s)", (yyvsp[0].sval));

			errno = 0;
			yyerror(m, msg);
			_DELETE(msg);
			(yyval.i_val) = 0;
			YYABORT;
		  }
		}
#line 12898 "y.tab.c" /* yacc.c:1646  */
    break;

  case 937:
#line 5112 "sql_parser.y" /* yacc.c:1646  */
    {
		  char *name = (yyvsp[0].sval);
		  sql_subtype *tpe;

		  if (!stack_find_var(m, name)) {
			char *msg = sql_message("\b22000!constant (%s) unknown", (yyvsp[0].sval));

			yyerror(m, msg);
			_DELETE(msg);
			(yyval.i_val) = 0;
			YYABORT;
		  }
		  tpe = stack_find_type(m, name);
		  if (tpe->type->localtype == TYPE_lng ||
		      tpe->type->localtype == TYPE_int ||
		      tpe->type->localtype == TYPE_sht ||
		      tpe->type->localtype == TYPE_bte ) {
			lng sgn = stack_get_number(m, name);
			assert((lng) GDK_int_min < sgn && sgn <= (lng) GDK_int_max);
			(yyval.i_val) = (int) sgn;
		  } else {
			char *msg = sql_message("\b22000!constant (%s) has wrong type (number expected)", (yyvsp[0].sval));

			yyerror(m, msg);
			_DELETE(msg);
			(yyval.i_val) = 0;
			YYABORT;
		  }
		}
#line 12932 "y.tab.c" /* yacc.c:1646  */
    break;

  case 938:
#line 5145 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 12938 "y.tab.c" /* yacc.c:1646  */
    break;

  case 939:
#line 5147 "sql_parser.y" /* yacc.c:1646  */
    { char *s = strconcat((yyvsp[-1].sval),(yyvsp[0].sval)); 
	 	  (yyval.sval) = sa_strdup(SA, s);	
		  _DELETE(s);
		}
#line 12947 "y.tab.c" /* yacc.c:1646  */
    break;

  case 940:
#line 5155 "sql_parser.y" /* yacc.c:1646  */
    {
		  m->emode = m_execute;
		  (yyval.sym) = (yyvsp[0].sym); }
#line 12955 "y.tab.c" /* yacc.c:1646  */
    break;

  case 941:
#line 5162 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
  	  append_int(l, (yyvsp[-2].i_val));
  	  append_list(l, NULL);
	  (yyval.sym) = _symbol_create_list( SQL_NOP, l ); }
#line 12964 "y.tab.c" /* yacc.c:1646  */
    break;

  case 942:
#line 5167 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
  	  append_int(l, (yyvsp[-3].i_val));
  	  append_list(l, (yyvsp[-1].l));
	  (yyval.sym) = _symbol_create_list( SQL_NOP, l ); }
#line 12973 "y.tab.c" /* yacc.c:1646  */
    break;

  case 943:
#line 5181 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 12979 "y.tab.c" /* yacc.c:1646  */
    break;

  case 945:
#line 5186 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_PATH, (yyvsp[0].l)); }
#line 12985 "y.tab.c" /* yacc.c:1646  */
    break;

  case 948:
#line 5197 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 12991 "y.tab.c" /* yacc.c:1646  */
    break;

  case 949:
#line 5199 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol((yyvsp[-2].l), (yyvsp[0].sym)); }
#line 12997 "y.tab.c" /* yacc.c:1646  */
    break;

  case 961:
#line 5221 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_symbol(l, (yyvsp[-2].sym));
	  append_int(l, (yyvsp[-1].i_val));
	  (yyval.sym) = _symbol_create_list( SQL_XMLCOMMENT, l); }
#line 13006 "y.tab.c" /* yacc.c:1646  */
    break;

  case 962:
#line 5229 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-2].l));
	  append_int(l, (yyvsp[-1].i_val));
	  (yyval.sym) = _symbol_create_list( SQL_XMLCONCAT, l); }
#line 13015 "y.tab.c" /* yacc.c:1646  */
    break;

  case 963:
#line 5237 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_symbol(l, (yyvsp[-2].sym));
	  append_int(l, (yyvsp[-1].i_val));
	  (yyval.sym) = _symbol_create_list( SQL_XMLDOCUMENT, l); }
#line 13024 "y.tab.c" /* yacc.c:1646  */
    break;

  case 964:
#line 5247 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_string(l, (yyvsp[-3].sval));
	  append_list(l, (yyvsp[-2].l));
	  append_int(l, (yyvsp[-1].i_val));
	  (yyval.sym) = _symbol_create_list( SQL_XMLELEMENT, l);
	}
#line 13035 "y.tab.c" /* yacc.c:1646  */
    break;

  case 965:
#line 5257 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = NULL; }
#line 13041 "y.tab.c" /* yacc.c:1646  */
    break;

  case 966:
#line 5259 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[0].sym));
	  (yyval.l) = append_symbol((yyval.l), NULL);
	  (yyval.l) = append_list((yyval.l), NULL); }
#line 13049 "y.tab.c" /* yacc.c:1646  */
    break;

  case 967:
#line 5263 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[-2].sym));
	  (yyval.l) = append_symbol((yyval.l), (yyvsp[0].sym));
	  (yyval.l) = append_list((yyval.l), NULL); }
#line 13057 "y.tab.c" /* yacc.c:1646  */
    break;

  case 968:
#line 5267 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[-4].sym));
	  (yyval.l) = append_symbol((yyval.l), (yyvsp[-2].sym));
	  (yyval.l) = append_list((yyval.l), (yyvsp[0].l)); }
#line 13065 "y.tab.c" /* yacc.c:1646  */
    break;

  case 969:
#line 5271 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[-2].sym));
	  (yyval.l) = append_symbol((yyval.l), NULL);
	  (yyval.l) = append_list((yyval.l), (yyvsp[0].l)); }
#line 13073 "y.tab.c" /* yacc.c:1646  */
    break;

  case 970:
#line 5275 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), NULL);
	  (yyval.l) = append_symbol((yyval.l), (yyvsp[0].sym));
	  (yyval.l) = append_list((yyval.l), NULL); }
#line 13081 "y.tab.c" /* yacc.c:1646  */
    break;

  case 971:
#line 5279 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), NULL);
	  (yyval.l) = append_symbol((yyval.l), (yyvsp[-2].sym));
	  (yyval.l) = append_list((yyval.l), (yyvsp[0].l)); }
#line 13089 "y.tab.c" /* yacc.c:1646  */
    break;

  case 972:
#line 5283 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), NULL);
	  (yyval.l) = append_symbol((yyval.l), NULL);
	  (yyval.l) = append_list((yyval.l), (yyvsp[0].l)); }
#line 13097 "y.tab.c" /* yacc.c:1646  */
    break;

  case 974:
#line 5293 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[-1].sym); }
#line 13103 "y.tab.c" /* yacc.c:1646  */
    break;

  case 975:
#line 5297 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 13109 "y.tab.c" /* yacc.c:1646  */
    break;

  case 976:
#line 5299 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  append_list(l, 
		  	append_string(L(), sa_strdup(SA, "concat")));
	  	  append_symbol(l, (yyvsp[-2].sym));
	  	  append_symbol(l, (yyvsp[0].sym));
	  	  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 13120 "y.tab.c" /* yacc.c:1646  */
    break;

  case 977:
#line 5309 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_string(l, (yyvsp[0].sval));
	  append_symbol(l, (yyvsp[-1].sym));
	  (yyval.sym) = _symbol_create_list( SQL_XMLATTRIBUTE, l ); }
#line 13129 "y.tab.c" /* yacc.c:1646  */
    break;

  case 978:
#line 5316 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = NULL; }
#line 13135 "y.tab.c" /* yacc.c:1646  */
    break;

  case 979:
#line 5317 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 13141 "y.tab.c" /* yacc.c:1646  */
    break;

  case 982:
#line 5330 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = L();
		  (yyval.l) = append_list((yyval.l), (yyvsp[-1].l));
		  (yyval.l) = append_int((yyval.l), (yyvsp[0].i_val)); 	}
#line 13149 "y.tab.c" /* yacc.c:1646  */
    break;

  case 983:
#line 5337 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 13155 "y.tab.c" /* yacc.c:1646  */
    break;

  case 984:
#line 5339 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol((yyvsp[-2].l), (yyvsp[0].sym)); }
#line 13161 "y.tab.c" /* yacc.c:1646  */
    break;

  case 986:
#line 5347 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 13167 "y.tab.c" /* yacc.c:1646  */
    break;

  case 987:
#line 5348 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = (yyvsp[0].i_val); }
#line 13173 "y.tab.c" /* yacc.c:1646  */
    break;

  case 988:
#line 5352 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 13179 "y.tab.c" /* yacc.c:1646  */
    break;

  case 989:
#line 5353 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 1; }
#line 13185 "y.tab.c" /* yacc.c:1646  */
    break;

  case 990:
#line 5354 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 2; }
#line 13191 "y.tab.c" /* yacc.c:1646  */
    break;

  case 991:
#line 5355 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 3; }
#line 13197 "y.tab.c" /* yacc.c:1646  */
    break;

  case 992:
#line 5356 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 4; }
#line 13203 "y.tab.c" /* yacc.c:1646  */
    break;

  case 993:
#line 5363 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_symbol(l, (yyvsp[-4].sym));
	  append_list(l, (yyvsp[-3].l));
	  append_int(l, (yyvsp[-2].i_val));
	  append_int(l, (yyvsp[-1].i_val));
	  (yyval.sym) = _symbol_create_list( SQL_XMLFOREST, l);
	}
#line 13215 "y.tab.c" /* yacc.c:1646  */
    break;

  case 994:
#line 5373 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 13221 "y.tab.c" /* yacc.c:1646  */
    break;

  case 995:
#line 5374 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[-1].sym); }
#line 13227 "y.tab.c" /* yacc.c:1646  */
    break;

  case 996:
#line 5379 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_list(L(), (yyvsp[0].l)); }
#line 13233 "y.tab.c" /* yacc.c:1646  */
    break;

  case 997:
#line 5381 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_list((yyvsp[-2].l), (yyvsp[0].l)); }
#line 13239 "y.tab.c" /* yacc.c:1646  */
    break;

  case 998:
#line 5386 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[-1].sym));
		  (yyval.l) = append_string((yyval.l), (yyvsp[0].sval)); }
#line 13246 "y.tab.c" /* yacc.c:1646  */
    break;

  case 999:
#line 5391 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 13252 "y.tab.c" /* yacc.c:1646  */
    break;

  case 1000:
#line 5395 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = NULL; }
#line 13258 "y.tab.c" /* yacc.c:1646  */
    break;

  case 1001:
#line 5396 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 13264 "y.tab.c" /* yacc.c:1646  */
    break;

  case 1002:
#line 5400 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 13270 "y.tab.c" /* yacc.c:1646  */
    break;

  case 1003:
#line 5407 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_int(l, (yyvsp[-3].i_val) );
	  append_symbol(l, (yyvsp[-2].sym));
	  append_int(l, (yyvsp[-1].i_val));
	  (yyval.sym) = _symbol_create_list( SQL_XMLPARSE, l); }
#line 13280 "y.tab.c" /* yacc.c:1646  */
    break;

  case 1004:
#line 5414 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 13286 "y.tab.c" /* yacc.c:1646  */
    break;

  case 1005:
#line 5415 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 1; }
#line 13292 "y.tab.c" /* yacc.c:1646  */
    break;

  case 1006:
#line 5422 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_string(l, (yyvsp[-3].sval));
	  append_symbol(l, (yyvsp[-2].sym));
	  append_int(l, (yyvsp[-1].i_val));
	  (yyval.sym) = _symbol_create_list( SQL_XMLPI, l); }
#line 13302 "y.tab.c" /* yacc.c:1646  */
    break;

  case 1008:
#line 5434 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 13308 "y.tab.c" /* yacc.c:1646  */
    break;

  case 1009:
#line 5436 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 13314 "y.tab.c" /* yacc.c:1646  */
    break;

  case 1010:
#line 5447 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 13320 "y.tab.c" /* yacc.c:1646  */
    break;

  case 1025:
#line 5493 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_symbol(l, (yyvsp[-2].sym));
	  append_int(l, (yyvsp[-1].i_val));
	  (yyval.sym) = _symbol_create_list( SQL_XMLTEXT, l); }
#line 13329 "y.tab.c" /* yacc.c:1646  */
    break;

  case 1026:
#line 5504 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 13335 "y.tab.c" /* yacc.c:1646  */
    break;

  case 1028:
#line 5509 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 2; }
#line 13341 "y.tab.c" /* yacc.c:1646  */
    break;

  case 1029:
#line 5513 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 13347 "y.tab.c" /* yacc.c:1646  */
    break;

  case 1030:
#line 5514 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 1; }
#line 13353 "y.tab.c" /* yacc.c:1646  */
    break;

  case 1031:
#line 5518 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 13359 "y.tab.c" /* yacc.c:1646  */
    break;

  case 1032:
#line 5519 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 13365 "y.tab.c" /* yacc.c:1646  */
    break;

  case 1033:
#line 5520 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 1; }
#line 13371 "y.tab.c" /* yacc.c:1646  */
    break;

  case 1034:
#line 5535 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[-1].sym); }
#line 13377 "y.tab.c" /* yacc.c:1646  */
    break;

  case 1035:
#line 5539 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 13383 "y.tab.c" /* yacc.c:1646  */
    break;

  case 1036:
#line 5541 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  append_list(l, 
		  	append_string(L(), sa_strdup(SA, "concat")));
	  	  append_symbol(l, (yyvsp[-2].sym));
	  	  append_symbol(l, (yyvsp[0].sym));
	  	  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 13394 "y.tab.c" /* yacc.c:1646  */
    break;

  case 1041:
#line 5564 "sql_parser.y" /* yacc.c:1646  */
    { char *s = strconcat("xmlns:", (yyvsp[0].sval));
				  dlist *l = L();
	  			  append_string(l, sa_strdup(SA, s));
				  _DELETE(s);
	  			  append_symbol(l, (yyvsp[-2].sym));
	  			  (yyval.sym) = _symbol_create_list( SQL_XMLATTRIBUTE, l ); }
#line 13405 "y.tab.c" /* yacc.c:1646  */
    break;

  case 1042:
#line 5573 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  			  append_string(l, sa_strdup(SA, "xmlns" ));
	  			  append_symbol(l, (yyvsp[0].sym));
	  			  (yyval.sym) = _symbol_create_list( SQL_XMLATTRIBUTE, l ); }
#line 13414 "y.tab.c" /* yacc.c:1646  */
    break;

  case 1043:
#line 5577 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 13420 "y.tab.c" /* yacc.c:1646  */
    break;

  case 1073:
#line 5673 "sql_parser.y" /* yacc.c:1646  */
    { 
          dlist *aggr = L();

          if ((yyvsp[-2].sym)) {
	  	if ((yyvsp[-3].sym) != NULL && (yyvsp[-3].sym)->token == SQL_SELECT) {
			SelectNode *s = (SelectNode*)(yyvsp[-3].sym);
	
			s->orderby = (yyvsp[-2].sym);
	  	} else {
			yyerror(m, "ORDER BY: missing select operator");
			YYABORT;
		}
	  }
          append_list(aggr, append_string(append_string(L(), "sys"), "xmlagg"));
  	  append_int(aggr, FALSE);
	  append_symbol(aggr, (yyvsp[-3].sym));
	  /* int returning not used */
	  (yyval.sym) = _symbol_create_list( SQL_AGGR, aggr);
	}
#line 13444 "y.tab.c" /* yacc.c:1646  */
    break;


#line 13448 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (m, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (m, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, m);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, m);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (m, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, m);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, m);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 5694 "sql_parser.y" /* yacc.c:1906  */

char *token2string(int token)
{
	switch (token) {
#define SQL(TYPE) case SQL_##TYPE : return #TYPE
	SQL(CREATE_SCHEMA);
	SQL(CREATE_TABLE);
	SQL(CREATE_VIEW);
	SQL(CREATE_INDEX);
	SQL(CREATE_ROLE);
	SQL(CREATE_USER);
	SQL(CREATE_TYPE);
	SQL(CREATE_FUNC);
	SQL(CREATE_SEQ);
	SQL(CREATE_TRIGGER);
	SQL(DROP_SCHEMA);
	SQL(DROP_TABLE);
	SQL(DROP_VIEW);
	SQL(DROP_INDEX);
	SQL(DROP_ROLE);
	SQL(DROP_USER);
	SQL(DROP_TYPE);
	SQL(DROP_FUNC);
	SQL(DROP_SEQ);
	SQL(DROP_TRIGGER);
	SQL(ALTER_TABLE);
	SQL(ALTER_SEQ);
	SQL(ALTER_USER);
	SQL(DROP_COLUMN);
	SQL(DROP_CONSTRAINT);
	SQL(DROP_DEFAULT);
	SQL(DECLARE);
	SQL(SET);
	SQL(PREP);
	SQL(NAME);
	SQL(USER);
	SQL(PATH);
	SQL(CHARSET);
	SQL(SCHEMA);
	SQL(TABLE);
	SQL(TYPE);
	SQL(CASE);
	SQL(CAST);
	SQL(RETURN);
	SQL(IF);
	SQL(ELSE);
	SQL(WHILE);
	SQL(COLUMN);
	SQL(COLUMN_OPTIONS);
	SQL(COALESCE);
	SQL(CONSTRAINT);
	SQL(CHECK);
	SQL(DEFAULT);
	SQL(NOT_NULL);
	SQL(NULL);
	SQL(NULLIF);
	SQL(UNIQUE);
	SQL(PRIMARY_KEY);
	SQL(FOREIGN_KEY);
	SQL(BEGIN);
#define TR(TYPE) case TR_##TYPE : return #TYPE
	TR(COMMIT);
	TR(ROLLBACK);
	TR(SAVEPOINT);
	TR(RELEASE);
	TR(START);
	TR(MODE);
	SQL(INSERT);
	SQL(DELETE);
	SQL(UPDATE);
	SQL(CROSS);
	SQL(JOIN);
	SQL(SELECT);
	SQL(WHERE);
	SQL(FROM);
	SQL(UNIONJOIN);
	SQL(UNION);
	SQL(EXCEPT);
	SQL(INTERSECT);
	SQL(VALUES);
	SQL(ASSIGN);
	SQL(ORDERBY);
	SQL(GROUPBY);
	SQL(DESC);
	SQL(AND);
	SQL(OR);
	SQL(NOT);
	SQL(EXISTS);
	SQL(NOT_EXISTS);
	SQL(OP);
	SQL(UNOP);
	SQL(BINOP);
	SQL(NOP);
	SQL(BETWEEN);
	SQL(NOT_BETWEEN);
	SQL(LIKE);
	SQL(IN);
	SQL(NOT_IN);
	SQL(GRANT);
	SQL(GRANT_ROLES);
	SQL(REVOKE);
	SQL(REVOKE_ROLES);
	SQL(EXECUTE);
	SQL(PRIVILEGES);
	SQL(ROLE);
	SQL(PARAMETER);
	SQL(FUNC);
	SQL(AGGR);
	SQL(RANK);
	SQL(FRAME);
	SQL(COMPARE);
	SQL(FILTER);
	SQL(TEMP_LOCAL);
	SQL(TEMP_GLOBAL);
	SQL(INT_VALUE);
	SQL(ATOM);
	SQL(USING);
	SQL(WHEN);
	SQL(ESCAPE);
	SQL(COPYFROM);
	SQL(BINCOPYFROM);
	SQL(COPYTO);
	SQL(EXPORT);
	SQL(NEXT);
	SQL(MULSTMT);
	SQL(WITH);
	SQL(XMLCOMMENT);
	SQL(XMLCONCAT);
	SQL(XMLDOCUMENT);
	SQL(XMLELEMENT);
	SQL(XMLATTRIBUTE);
	SQL(XMLFOREST);
	SQL(XMLPARSE);
	SQL(XMLPI);
	SQL(XMLQUERY);
	SQL(XMLTEXT);
	SQL(XMLVALIDATE);
	SQL(XMLNAMESPACES);
	}
	return "unknown";	/* just needed for broken compilers ! */
}

void *sql_error( mvc * sql, int error_code, char *format, ... )
{
	va_list	ap;

	va_start (ap,format);
	if (sql->errstr[0] == '\0') 
		vsnprintf(sql->errstr, ERRSIZE-1, _(format), ap);
	if (!sql->session->status)
		sql->session->status = -error_code;
	va_end (ap);
	return NULL;
}

int sqlerror(mvc * c, const char *err)
{
	char *sqlstate = "42000!";
	if (err && *err == '\b') {
		sqlstate = "";
		err++;
	}
	if (c->scanner.errstr) {
		if (c->scanner.errstr[0] == '!')
			(void)sql_error(c, 4,
					"!%s%s: %s\n",
					sqlstate, err, c->scanner.errstr + 1);
		else
			(void)sql_error(c, 4,
					"!%s%s: %s in \"%.80s\"\n",
					sqlstate, err, c->scanner.errstr,
					QUERY(c->scanner));
	} else
		(void)sql_error(c, 4,
				"!%s%s in: \"%.80s\"\n",
				sqlstate, err, QUERY(c->scanner));
	return 1;
}

