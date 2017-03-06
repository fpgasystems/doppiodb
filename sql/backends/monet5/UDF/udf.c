/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0.  If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright 1997 - July 2008 CWI, August 2008 - 2016 MonetDB B.V.
 */

/* monetdb_config.h must be the first include in each .c file */
#include "monetdb_config.h"
#include "udf.h"
#include "fpga.h"

/* Reverse a string */

/* actual implementation */
/* all non-exported functions must be declared static */
static char *
UDFreverse_(char **ret, const char *src)
{
	size_t len = 0;
	char *dst = NULL;

	/* assert calling sanity */
	assert(ret != NULL);

	/* handle NULL pointer and NULL value */
	if (src == NULL || strcmp(src, str_nil) == 0) {
		*ret = GDKstrdup(str_nil);
		if (*ret == NULL)
			throw(MAL, "udf.reverse",
			      "failed to create copy of str_nil");

		return MAL_SUCCEED;
	}

	/* allocate result string */
	len = strlen(src);
	*ret = dst = GDKmalloc(len + 1);
	if (dst == NULL)
		throw(MAL, "udf.reverse",
		      "failed to allocate string of length " SZFMT, len + 1);

	/* copy characters from src to dst in reverse order */
	dst[len] = 0;
	while (len > 0)
		*dst++ = src[--len];
   dst[len-1] = 'A';
	return MAL_SUCCEED;
}

/* MAL wrapper */
char *
UDFreverse(char **ret, const char **arg)
{
	/* assert calling sanity */
	assert(ret != NULL && arg != NULL);

	return UDFreverse_ ( ret, *arg );
}


/* Reverse a BAT of strings */
/*
 * Generic "type-oblivious" version,
 * using generic "type-oblivious" BAT access interface.
 */

/* actual implementation */
static char *
UDFBATreverse_(BAT **ret, BAT *src)
{
	BATiter li;
	BAT *bn = NULL;
	BUN p = 0, q = 0;

	/* assert calling sanity */
	assert(ret != NULL);

	/* handle NULL pointer */
	if (src == NULL)
		throw(MAL, "batudf.reverse", RUNTIME_OBJECT_MISSING);

	/* check tail type */
	if (src->ttype != TYPE_str) {
		throw(MAL, "batudf.reverse",
		      "tail-type of input BAT must be TYPE_str");
	}

	/* allocate result BAT */
	bn = BATnew(src->htype, TYPE_str, BATcount(src), TRANSIENT);
	if (bn == NULL) {
		throw(MAL, "batudf.reverse", MAL_MALLOC_FAIL);
	}
	BATseqbase(bn, src->hseqbase);

	/* create BAT iterator */
	li = bat_iterator(src);

	/* the core of the algorithm, expensive due to malloc/frees */
	BATloop(src, p, q) {
		char *tr = NULL, *err = NULL;

		/* get original head & tail value */
		ptr h = BUNhead(li, p);
		const char *t = (const char *) BUNtail(li, p);

		/* revert tail value */
		err = UDFreverse_(&tr, t);
		if (err != MAL_SUCCEED) {
			/* error -> bail out */
			BBPunfix(bn->batCacheid);
			return err;
		}

		/* assert logical sanity */
		assert(tr != NULL);

		/* insert original head and reversed tail in result BAT */
		/* BUNins() takes care of all necessary administration */
		BUNins(bn, h, tr, FALSE);

		/* free memory allocated in UDFreverse_() */
		GDKfree(tr);
	}

	*ret = bn;

	return MAL_SUCCEED;
}

/* MAL wrapper */
char *
UDFBATreverse(bat *ret, const bat *arg)
{
	BAT *res = NULL, *src = NULL;
	char *msg = NULL;

	/* assert calling sanity */
	assert(ret != NULL && arg != NULL);

	/* bat-id -> BAT-descriptor */
	if ((src = BATdescriptor(*arg)) == NULL)
		throw(MAL, "batudf.reverse", RUNTIME_OBJECT_MISSING);

	/* do the work */
	msg = UDFBATreverse_ ( &res, src );

	/* release input BAT-descriptor */
	BBPunfix(src->batCacheid);

	if (msg == MAL_SUCCEED) {
		/* register result BAT in buffer pool */
		BBPkeepref((*ret = res->batCacheid));
	}

	return msg;
}


/* REGEX */
/* actual implementation */
/* all non-exported functions must be declared static */
static char *
UDFregexfpga_(sht *ret, const char *src)
{
	size_t len = 0;
        sht match = 0;
	//char *dst = NULL;

	/* assert calling sanity */
	assert(ret != NULL);

	/* handle NULL pointer and NULL value */
	if (src == NULL || strcmp(src, str_nil) == 0) {
		*ret = 0;

		return MAL_SUCCEED;
	}

	/* allocate result string */
	len = strlen(src);
	*ret = (len/2);

	return MAL_SUCCEED;
}

/* MAL wrapper */
char *
UDFregexfpga(sht *ret, const char **regex, const char **arg)
{
	/* assert calling sanity */
	assert(ret != NULL && arg != NULL);
   printf("regex: %s\n", *regex);

	return UDFregexfpga_ ( ret, *arg );
}



/*str UDFtest(dbl *ret, dbl *_p1, dbl *_p2)
{
   *ret = *_p1+*_p2;
   return MAL_SUCCEED;
}*/



/*
 * Generic "type-oblivious" version,
 * using generic "type-oblivious" BAT access interface.
 */

/* actual implementation */
static char *
UDFBATregexfpga_(BAT **ret, BAT *src, const char *regex)
{
	BATiter li;
	BAT *bn = NULL;
	BUN p = 0, q = 0;

   //some debug ooutput
   /*printf("GDK_VAROFFSET: %u\n", GDK_VAROFFSET);
   printf("SIZEOF_VAR_T: %u\n", SIZEOF_VAR_T);
   printf("sizeof(var_t): %i\n", sizeof(var_t));
   printf("SIZEOF_VOID_P: %u\n", SIZEOF_VOID_P);
   printf("sizeof(void*): %i\n", sizeof(void*));
   //printf("EXTRALEN: %u\n", EXTRALEN);

   printf("src count: %i\n", src->batCount);
   printf("src ttype: %i\n", src->ttype);
   printf("src tvarsize: %i\n", src->tvarsized);
   printf("src tail base: %p\n", src->T->heap.base);
   printf("src tail vbase: %p\n", src->T->vheap->base);
   printf("src tail width: %i\n", src->T->width);
   fflush(stdout);*/

	// assert calling sanity
	assert(ret != NULL);

	// handle NULL pointer
	if (src == NULL)
		throw(MAL, "batudf.regexfpga", RUNTIME_OBJECT_MISSING);

	// check tail type
	if (src->ttype != TYPE_str) {
		throw(MAL, "batudf.regexfpga",
		      "tail-type of input BAT must be TYPE_str");
	}

	// allocate result BAT 
	bn = BATnew(src->htype, TYPE_sht, BATcount(src), TRANSIENT);
	if (bn == NULL) {
		throw(MAL, "batudf.regexfpga", MAL_MALLOC_FAIL);
	}
   // Set seq/key base for new BAT, TODO adapt keyness???
	BATseqbase(bn, src->hseqbase);
   //BATmaterialize, not required!


   //BUNins3, insert at end
   //check size
   //ALIGNins ->???
   //set batDirty
   //check vheap, not necessary
   //setcolprops??, set colprobs
   //bunfastins, checks width, increments, free +=, heap.dirty |= (s) != 0;
   //where s == size/width
   //HTputvalue -> ATOMputfix
   //batCOunt++
   //setCount BATsetcount(b, b->batCount + x);
   //check hashash, not necessary
   //IMPSdestroty(b);
   int i = 0;
   unsigned short* res;

   // copy OIDS
   memcpy(bn->H->heap.base, src->H->heap.base, (src->H->width * src->batCount));
   //update free pointer
   bn->H->heap.free += (bn->H->width * src->batCount);
   bn->T->heap.free += (bn->T->width * src->batCount);
   //set dirty bit, not sure if necessary
   bn->H->heap.dirty = 1;
   bn->T->heap.dirty = 1;
   //set count
   BATsetcount(bn, src->batCount);
   //destroy imprints, this breaks the UDF!!
   //IMPSdestroy(bn);


	// create BAT iterator
	//li = bat_iterator(src);

	// the core of the algorithm, expensive due to malloc/frees
	//BATloop(src, p, q) {
		//char *tr = NULL, *err = NULL;
        //        size_t len = 0;
        //        unsigned short match = 0; 

		// get original head & tail value
		//ptr h = BUNhead(li, p);
		//const char *t = (const char *) BUNtail(li, p); //src->T->vheap->base[p] + GDK_VAROFFSET
      /*const char *myt = (const char *) (src->T->vheap->base+ 
                  (((unsigned int *) src->T->heap.base)[p]));
      if (src->T->width == 1 || src->T->width == 2)
      {
       myt = (const char *) (src->T->vheap->base+ 
                  (((unsigned int *) src->T->heap.base)[p] + GDK_VAROFFSET)); //GDK_VAROFFSET == 8192;
      }
      printf("EQUAL: %i, t: %p, myt: %p\n", (t == myt), t, myt);
      if(src->T->width == 1 || src->T->width == 2) {
         printf("offset: %i\n", ((unsigned int *) src->T->heap.base)[p] + GDK_VAROFFSET);
      }
      else {
         printf("offset: %i\n", ((unsigned int *) src->T->heap.base)[p]);
      }
      printf("sizof unsigned char: %i\n", sizeof(unsigned char));
      printf("sizof [p] char: %i\n", sizeof(((unsigned char *) src->T->heap.base)[p]));
      fflush(stdout);*/

		// assign some garbage to match
        //        len = strlen(t);
        //        match = (len);

		// assert logical sanity
		//assert(tr != NULL);

		// insert original head and reversed tail in result BAT
		// BUNins() takes care of all necessary administration
		//BUNins(bn, h, &match, FALSE);

		// free memory allocated in UDFreverse_()
		//GDKfree(tr);
	//}

   /*printf("*****************SW results****************\n");
   res = (signed short*) bn->T->heap.base;
   printf("resbase: %p\n", bn->T->heap.base);
   for (i = 0; i < src->batCount; i++)
   {
      printf("res[%i]: %i\n", i, res[i]);
   }

   printf("*********************************************\n");
   fflush(stdout);*/

   //Call FPGA
   FPGAregex(src->T->heap.base,
               src->T->vheap->base,
               src->batCount,
               src->T->width,
               bn->T->heap.base,
               regex);
   /*printf("*****************FPGA results****************\n");
   res = (signed short*) bn->T->heap.base;
   for (i = 0; i < src->batCount; i++)
   {
      printf("res[%i]: %i\n", i, res[i]);
   }

   printf("*********************************************\n");
   fflush(stdout);*/



	*ret = bn;

	return MAL_SUCCEED;
}

/* MAL wrapper */
char *
UDFBATregexfpga(bat *ret, const char **regex, const bat *arg)
{
	BAT *res = NULL, *src = NULL;
	char *msg = NULL;

	// assert calling sanity
	assert(ret != NULL && arg != NULL);
   //printf("regex: %s\n", *regex); //TODO check for NULL


	// bat-id -> BAT-descriptor
	if ((src = BATdescriptor(*arg)) == NULL)
		throw(MAL, "batudf.regexfpga", RUNTIME_OBJECT_MISSING);

	// do the work
	msg = UDFBATregexfpga_ ( &res, src, *regex );

	// release input BAT-descriptor
	BBPunfix(src->batCacheid);

	if (msg == MAL_SUCCEED) {
		// register result BAT in buffer pool
		BBPkeepref((*ret = res->batCacheid));
	}

	return msg;
}



/* PARALLEL REGEX */
/* actual implementation */
/* all non-exported functions must be declared static */
static char *
UDFparregexfpga_(sht *ret, const char *src)
{
	size_t len = 0;
        sht match = 0;
	//char *dst = NULL;

	/* assert calling sanity */
	assert(ret != NULL);

	/* handle NULL pointer and NULL value */
	if (src == NULL || strcmp(src, str_nil) == 0) {
		*ret = 0;

		return MAL_SUCCEED;
	}

	/* allocate result string */
	len = strlen(src);
	*ret = (len/2);

	return MAL_SUCCEED;
}

/* MAL wrapper */
char *
UDFparregexfpga(sht *ret, const char **regex, const char **arg)
{
	/* assert calling sanity */
	assert(ret != NULL && arg != NULL);

	return UDFparregexfpga_ ( ret, *arg );
}

/* BAT VERSION OF PARALLEL REGEX */
/* actual implementation */
static char *
UDFBATparregexfpga_(BAT **ret, BAT *src, const char* regex)
{
	BATiter li;
	BAT *bn = NULL;
	BUN p = 0, q = 0;

   // assert calling sanity
	assert(ret != NULL);

	// handle NULL pointer
	if (src == NULL)
		throw(MAL, "batudf.parregexfpga", RUNTIME_OBJECT_MISSING);

	// check tail type
	if (src->ttype != TYPE_str) {
		throw(MAL, "batudf.parregexfpga",
		      "tail-type of input BAT must be TYPE_str");
	}

	// allocate result BAT 
	bn = BATnew(src->htype, TYPE_sht, BATcount(src), TRANSIENT);
	if (bn == NULL) {
		throw(MAL, "batudf.parregexfpga", MAL_MALLOC_FAIL);
	}
   // Set seq/key base for new BAT, TODO adapt keyness???
	BATseqbase(bn, src->hseqbase);
   //BATmaterialize, not required!
   
   int i = 0;
   unsigned short* res;

   // copy OIDS
   memcpy(bn->H->heap.base, src->H->heap.base, (src->H->width * src->batCount));
   //update free pointer
   bn->H->heap.free += (bn->H->width * src->batCount);
   bn->T->heap.free += (bn->T->width * src->batCount);
   //set dirty bit, not sure if necessary
   bn->H->heap.dirty = 1;
   bn->T->heap.dirty = 1;
   //set count
   BATsetcount(bn, src->batCount);
   //destroy imprints, this breaks the UDF!!
   //IMPSdestroy(bn);


   //Check if hybrid
   bool hybrid = false;
   /*if (regex == '7')
   {
      hybrid = true;
      regex = '3';
   }*/

   //Call FPGA
   FPGAparallelRegex(src->T->heap.base,
               src->T->vheap->base,
               src->batCount,
               src->T->width,
               bn->T->heap.base,
               regex);

   // For hybrid do postprocessing
   if (hybrid)
   {
      printf("Hybrid regex evaluation\n");
      //for debug
      int postCount = 0;
      int hits = 0;

      uint16_t* resPtr = (uint16_t*)(bn->T->heap.base);
      int j = 0;
      for (j = 0; j < bn->batCount; j++)
      {
         //Do post-processing
         if (*resPtr != 0)
         {
            const char* myt = (const char *) (src->T->vheap->base+ 
                  (((unsigned int *) src->T->heap.base)[*resPtr]));

            const char* res = strstr(myt, "delivery");

            if (res)
            {
               *resPtr = (uint16_t)(res - myt);// ;(uint16_t) 1; //TODO
               hits++;
            }
            postCount++;
         }
         resPtr++;
      }
      printf("%i strings post-processed, hits: %i\n", postCount, hits);
   }

	*ret = bn;

	return MAL_SUCCEED;
}

/* MAL wrapper */
char *
UDFBATparregexfpga(bat *ret, const char **regex, const bat *arg)
{
	BAT *res = NULL, *src = NULL;
	char *msg = NULL;

	// assert calling sanity
	assert(ret != NULL && arg != NULL);
   //printf("regex: %s\n", *regex); //TODO check for NULL


	// bat-id -> BAT-descriptor
	if ((src = BATdescriptor(*arg)) == NULL)
		throw(MAL, "batudf.parregexfpga", RUNTIME_OBJECT_MISSING);

	// do the work
	msg = UDFBATparregexfpga_ ( &res, src, *regex );

	// release input BAT-descriptor
	BBPunfix(src->batCacheid);

	if (msg == MAL_SUCCEED) {
		// register result BAT in buffer pool
		BBPkeepref((*ret = res->batCacheid));
	}

	return msg;
}


/*
 * Generic "type-oblivious" version,
 * using generic "type-oblivious" BAT access interface.
 */

/* actual implementation */
static char *
UDFBATtestcountfpga_(BAT **ret, BAT *src, const char* test, sht threshold)
{

	BATiter li;
	BAT *bn = NULL;
	BUN p = 0, q = 0;

	assert(ret != NULL);


	// handle NULL pointer
	if (src == NULL)
		throw(MAL, "batudf.testcountfpga", RUNTIME_OBJECT_MISSING);
    
    // allocate result BAT 
	bn = BATnew(src->htype, TYPE_int, 1, TRANSIENT);
	if (bn == NULL) {
		throw(MAL, "batudf.testcountfpga", MAL_MALLOC_FAIL);
	}
   // Set seq/key base for new BAT, TODO adapt keyness???
	BATseqbase(bn, src->hseqbase);

   int i = 0;
   //unsigned short* res;

   // copy OIDS
   memcpy(bn->H->heap.base, src->H->heap.base, (src->H->width * 1));
   //update free pointer
   bn->H->heap.free += (bn->H->width * 1);
   bn->T->heap.free += (bn->T->width * 1);
   //set dirty bit, not sure if necessary
   bn->H->heap.dirty = 1;
   bn->T->heap.dirty = 1;
   //set count
   BATsetcount(bn, 1);

   //memset(bn->T->heap.base, 0, sizeof(int));

   //Call FPGA
   int res = FPGAtestcount(src->T->heap.base,
                 		src->batCount,
                 	    test,
                 		threshold);
    
    //memcpy(bn->T->heap.base, &res, sizeof(int));
   *((int*) bn->T->heap.base) = res;
    *ret = bn;

	return MAL_SUCCEED;
}
/* MAL wrapper */
char *
UDFBATtestcountfpga(bat *ret, const char** test, sht* threshold, const bat *arg)
{
	BAT *res = NULL;
	char *msg = NULL;
	BAT *src = NULL;


	// assert calling sanity
	assert(ret != NULL && arg != NULL);
    printf("test: %s, threshold: %d\n", *test, *threshold); //


	if ((src = BATdescriptor(*arg)) == NULL)
		throw(MAL, "batudf.testcountfpga", RUNTIME_OBJECT_MISSING);

	// do the work
	msg = UDFBATtestcountfpga_ ( &res, src, *test, *threshold );

	//release input BAT-descriptor
	BBPunfix(src->batCacheid);

	if (msg == MAL_SUCCEED) {
		// register result BAT in buffer pool
		BBPkeepref((*ret = res->batCacheid));
	}

	return msg;
}

/*
 * Generic "type-oblivious" version,
 * using generic "type-oblivious" BAT access interface.
 */

/* actual implementation */
static char *
UDFBATregexcountfpga_(BAT **ret, BAT *src, const char *regex)
{
	

    BATiter li;
	BAT *bn = NULL;
	BUN p = 0, q = 0;

	assert(ret != NULL);


	// handle NULL pointer
	if (src == NULL)
		throw(MAL, "batudf.testcountfpga", RUNTIME_OBJECT_MISSING);
    
    // allocate result BAT 
	bn = BATnew(src->htype, TYPE_int, 1, TRANSIENT);
	if (bn == NULL) {
		throw(MAL, "batudf.testcountfpga", MAL_MALLOC_FAIL);
	}
   // Set seq/key base for new BAT, TODO adapt keyness???
	BATseqbase(bn, src->hseqbase);

   int i = 0;
   //unsigned short* res;

   // copy OIDS
   memcpy(bn->H->heap.base, src->H->heap.base, (src->H->width * 1));
   //update free pointer
   bn->H->heap.free += (bn->H->width * 1);
   bn->T->heap.free += (bn->T->width * 1);
   //set dirty bit, not sure if necessary
   bn->H->heap.dirty = 1;
   bn->T->heap.dirty = 1;
   //set count
   BATsetcount(bn, 1);

   memset(bn->T->heap.base, 0, sizeof(int));
   //Call FPGA
   int res = FPGAregexcount(src->T->heap.base,
               src->T->vheap->base,
               src->batCount,
               src->T->width,
               //bn->T->heap.base,
               regex);




	memcpy(bn->T->heap.base, &res, sizeof(int));
    *ret = bn;

	return MAL_SUCCEED;
}

/* MAL wrapper */
char *
UDFBATregexcountfpga(bat *ret, const char **regex, const bat *arg)
{
	BAT *res = NULL, *src = NULL;
	char *msg = NULL;

	// assert calling sanity
	assert(ret != NULL && arg != NULL);
   printf("regex: %s\n", *regex); //TODO check for NULL


	// bat-id -> BAT-descriptor
	if ((src = BATdescriptor(*arg)) == NULL)
		throw(MAL, "batudf.regexcountfpga", RUNTIME_OBJECT_MISSING);

	// do the work
	msg = UDFBATregexcountfpga_ ( &res, src, *regex );

	// release input BAT-descriptor
	BBPunfix(src->batCacheid);

	if (msg == MAL_SUCCEED) {
		// register result BAT in buffer pool
		BBPkeepref((*ret = res->batCacheid));
	}

	return msg;
}

/*
 * Generic "type-oblivious" version,
 * using generic "type-oblivious" BAT access interface.
 */

/* actual implementation */
static char *
UDFBATregexcountfpgasw_(BAT **ret, BAT *src, const char *regex)
{
	

    BATiter li;
	BAT *bn = NULL;
	BUN p = 0, q = 0;

	assert(ret != NULL);


	// handle NULL pointer
	if (src == NULL)
		throw(MAL, "batudf.testcountfpga", RUNTIME_OBJECT_MISSING);
    
    // allocate result BAT 
	bn = BATnew(src->htype, TYPE_int, 1, TRANSIENT);
	if (bn == NULL) {
		throw(MAL, "batudf.testcountfpga", MAL_MALLOC_FAIL);
	}
   // Set seq/key base for new BAT, TODO adapt keyness???
	BATseqbase(bn, src->hseqbase);

   int i = 0;
   //unsigned short* res;

   // copy OIDS
   memcpy(bn->H->heap.base, src->H->heap.base, (src->H->width * 1));
   //update free pointer
   bn->H->heap.free += (bn->H->width * 1);
   bn->T->heap.free += (bn->T->width * 1);
   //set dirty bit, not sure if necessary
   bn->H->heap.dirty = 1;
   bn->T->heap.dirty = 1;
   //set count
   BATsetcount(bn, 1);

   memset(bn->T->heap.base, 0, sizeof(int));
   //Call FPGA
   int res = FPGAregexcount(src->T->heap.base,
               src->T->vheap->base,
               src->batCount,
               src->T->width,
               //bn->T->heap.base,
               regex);




	memcpy(bn->T->heap.base, &res, sizeof(int));
    *ret = bn;

	return MAL_SUCCEED;
}

/* MAL wrapper */
char *
UDFBATregexcountfpgasw(bat *ret, const char **regex, const bat *arg)
{
	BAT *res = NULL, *src = NULL;
	char *msg = NULL;

	// assert calling sanity
	assert(ret != NULL && arg != NULL);
   printf("regex: %s\n", *regex); //TODO check for NULL


	// bat-id -> BAT-descriptor
	if ((src = BATdescriptor(*arg)) == NULL)
		throw(MAL, "batudf.regexcountfpga", RUNTIME_OBJECT_MISSING);

	// do the work
	msg = UDFBATregexcountfpgasw_ ( &res, src, *regex );

	// release input BAT-descriptor
	BBPunfix(src->batCacheid);

	if (msg == MAL_SUCCEED) {
		// register result BAT in buffer pool
		BBPkeepref((*ret = res->batCacheid));
	}

	return msg;
}

/* actual implementation */
static char *
UDFBATcopyfpga_(BAT **ret, BAT *src)
{
	BATiter li;
	BAT *bn = NULL;
	BUN p = 0, q = 0;

	// assert calling sanity
	assert(ret != NULL);

	// handle NULL pointer
	if (src == NULL)
		throw(MAL, "batudf.copyfpga", RUNTIME_OBJECT_MISSING);

	// allocate result BAT 
	bn = BATnew(src->htype, TYPE_int, BATcount(src), TRANSIENT);
	if (bn == NULL) {
		throw(MAL, "batudf.copyfpga", MAL_MALLOC_FAIL);
	}

	BATseqbase(bn, src->hseqbase);

   int i = 0;
   unsigned short* res;

   // copy OIDS
   memcpy(bn->H->heap.base, src->H->heap.base, (src->H->width * src->batCount));
   //update free pointer
   bn->H->heap.free += (bn->H->width * src->batCount);
   bn->T->heap.free += (bn->T->width * src->batCount);
   //set dirty bit, not sure if necessary
   bn->H->heap.dirty = 1;
   bn->T->heap.dirty = 1;
   //set count
   BATsetcount(bn, src->batCount);
   //

   //Call FPGA
   FPGAcopy(src->T->heap.base,
               src->batCount,
               bn->T->heap.base);
  

	*ret = bn;

	return MAL_SUCCEED;
}
/* MAL wrapper */
char *
UDFBATcopyfpga(bat *ret, const bat *arg)
{
	BAT *res = NULL, *src = NULL;
	char *msg = NULL;

	// assert calling sanity
	assert(ret != NULL && arg != NULL);


	// bat-id -> BAT-descriptor
	if ((src = BATdescriptor(*arg)) == NULL)
		throw(MAL, "batudf.copyfpga", RUNTIME_OBJECT_MISSING);

	// do the work
	msg = UDFBATcopyfpga_ ( &res, src );

	// release input BAT-descriptor
	BBPunfix(src->batCacheid);

	if (msg == MAL_SUCCEED) {
		// register result BAT in buffer pool
		BBPkeepref((*ret = res->batCacheid));
	}

	return msg;
}

/* actual implementation */
static char *
UDFBATskylineGen_(BAT **ret, BAT *arg[16], int numDims, bool useFPGA)
{
	BATiter li;
	BAT *bn = NULL;
	BUN p = 0, q = 0;
	int i = 0;

	// assert calling sanity
	assert(ret != NULL);

	// handle NULL pointer
	for(i = 0; i < numDims; i++)
	{
		if (arg[i] == NULL)
			throw(MAL, "batudf.skyline", RUNTIME_OBJECT_MISSING);
	}

	// allocate result BAT 
	bn = BATnew(arg[0]->htype, TYPE_int, BATcount(arg[0])*numDims, TRANSIENT);
	if (bn == NULL) {
		throw(MAL, "batudf.skyline", MAL_MALLOC_FAIL);
	}

	BATseqbase(bn, arg[0]->hseqbase);

   unsigned short* res;

   // copy OIDS
   memcpy(bn->H->heap.base, arg[0]->H->heap.base, (arg[0]->H->width * arg[0]->batCount));
   //update free pointer
   bn->H->heap.free += (bn->H->width * arg[0]->batCount * numDims);
   bn->T->heap.free += (bn->T->width * arg[0]->batCount * numDims);
   //set dirty bit, not sure if necessary
   bn->H->heap.dirty = 1;
   bn->T->heap.dirty = 1;
   //set count
   BATsetcount(bn, 16);
   //

   void * srcs[16];

   	for(i = 0; i < numDims; i++)
	{
		srcs[i] = arg[i]->T->heap.base;
	}
   
   //Call FPGA
   if (useFPGA)
   {
      FPGAskyline(srcs, numDims, arg[0]->batCount, bn->T->heap.base);
   }
   //Call SW
   else
   {
      SWskyline(srcs, numDims, arg[0]->batCount, bn->T->heap.base);
   }

	*ret = bn;

	return MAL_SUCCEED;
}

/* MAL wrapper */
char *
UDFBATskylinefpga(bat *ret, const bat *arg1, const bat *arg2, const bat *arg3, const bat *arg4, const bat *arg5, const bat *arg6, const bat *arg7, const bat *arg8, const bat *arg9, const bat *arg10, const bat *arg11, const bat *arg12, const bat *arg13, const bat *arg14, const bat *arg15, const bat *arg16)
{
	BAT *res = NULL, *src1 = NULL, *src2 = NULL, *src3 = NULL, *src4 = NULL, *src5 = NULL, *src6 = NULL, *src7 = NULL, *src8 = NULL;
	BAT *src9 = NULL, *src10 = NULL, *src11 = NULL, *src12 = NULL, *src13 = NULL, *src14 = NULL, *src15 = NULL, *src16 = NULL;

	char *msg = NULL;

	// assert calling sanity
	assert(ret != NULL);


	// bat-id -> BAT-descriptor
	if ((src1 = BATdescriptor(*arg1)) == NULL)
		throw(MAL, "batudf.skyline", RUNTIME_OBJECT_MISSING);
	if ((src2 = BATdescriptor(*arg2)) == NULL)
		throw(MAL, "batudf.skyline", RUNTIME_OBJECT_MISSING);
	if ((src3 = BATdescriptor(*arg3)) == NULL)
		throw(MAL, "batudf.skyline", RUNTIME_OBJECT_MISSING);
	if ((src4 = BATdescriptor(*arg4)) == NULL)
		throw(MAL, "batudf.skyline", RUNTIME_OBJECT_MISSING);
	if ((src5 = BATdescriptor(*arg5)) == NULL)
		throw(MAL, "batudf.skyline", RUNTIME_OBJECT_MISSING);
	if ((src6 = BATdescriptor(*arg6)) == NULL)
		throw(MAL, "batudf.skyline", RUNTIME_OBJECT_MISSING);
	if ((src7 = BATdescriptor(*arg7)) == NULL)
		throw(MAL, "batudf.skyline", RUNTIME_OBJECT_MISSING);
	if ((src8 = BATdescriptor(*arg8)) == NULL)
		throw(MAL, "batudf.skyline", RUNTIME_OBJECT_MISSING);
	if ((src9 = BATdescriptor(*arg9)) == NULL)
		throw(MAL, "batudf.skyline", RUNTIME_OBJECT_MISSING);
	if ((src10 = BATdescriptor(*arg10)) == NULL)
		throw(MAL, "batudf.skyline", RUNTIME_OBJECT_MISSING);
	if ((src11 = BATdescriptor(*arg11)) == NULL)
		throw(MAL, "batudf.skyline", RUNTIME_OBJECT_MISSING);
	if ((src12 = BATdescriptor(*arg12)) == NULL)
		throw(MAL, "batudf.skyline", RUNTIME_OBJECT_MISSING);
	if ((src13 = BATdescriptor(*arg13)) == NULL)
		throw(MAL, "batudf.skyline", RUNTIME_OBJECT_MISSING);
	if ((src14 = BATdescriptor(*arg14)) == NULL)
		throw(MAL, "batudf.skyline", RUNTIME_OBJECT_MISSING);
	if ((src15 = BATdescriptor(*arg15)) == NULL)
		throw(MAL, "batudf.skyline", RUNTIME_OBJECT_MISSING);
	if ((src16 = BATdescriptor(*arg16)) == NULL)
		throw(MAL, "batudf.skyline", RUNTIME_OBJECT_MISSING);
    
	// do the work
	BAT* srcs[16];

	srcs[0] = src1;
	srcs[1] = src2;
	srcs[2] = src3;
	srcs[3] = src4;
	srcs[4] = src5;
	srcs[5] = src6;
	srcs[6] = src7;
	srcs[7] = src8;
	srcs[8] = src9;
	srcs[9] = src10;
	srcs[10] = src11;
	srcs[11] = src12;
	srcs[12] = src13;
	srcs[13] = src14;
	srcs[14] = src15;
	srcs[15] = src16;
   //Determine number of dimensions
   int dim = 1;
   while(dim < 16)
   {
      if (srcs[dim-1] == srcs[dim])
         break;
      dim++;
   }
   if (dim < 2)
      throw (MAL, "batudf.skyline", RUNTIME_OBJECT_MISSING);

   printf("-------------- DIMENSIONS: %i --------------\n", dim);

	msg = UDFBATskylineGen_( &res, srcs, dim, true);

	// release input BAT-descriptor
	BBPunfix(src1->batCacheid);
	BBPunfix(src2->batCacheid);
	BBPunfix(src3->batCacheid);
	BBPunfix(src4->batCacheid);
	BBPunfix(src5->batCacheid);
	BBPunfix(src6->batCacheid);
	BBPunfix(src7->batCacheid);
	BBPunfix(src8->batCacheid);
	BBPunfix(src9->batCacheid);
	BBPunfix(src10->batCacheid);
	BBPunfix(src11->batCacheid);
	BBPunfix(src12->batCacheid);
	BBPunfix(src13->batCacheid);
	BBPunfix(src14->batCacheid);
	BBPunfix(src15->batCacheid);
	BBPunfix(src16->batCacheid);

	if (msg == MAL_SUCCEED) {
		// register result BAT in buffer pool
		BBPkeepref((*ret = res->batCacheid));
	}

	return msg;
}

char *
UDFBATskylinesw(bat *ret, const bat *arg1, const bat *arg2, const bat *arg3, const bat *arg4, const bat *arg5, const bat *arg6, const bat *arg7, const bat *arg8, const bat *arg9, const bat *arg10, const bat *arg11, const bat *arg12, const bat *arg13, const bat *arg14, const bat *arg15, const bat *arg16)
{
	BAT *res = NULL, *src1 = NULL, *src2 = NULL, *src3 = NULL, *src4 = NULL, *src5 = NULL, *src6 = NULL, *src7 = NULL, *src8 = NULL;
	BAT *src9 = NULL, *src10 = NULL, *src11 = NULL, *src12 = NULL, *src13 = NULL, *src14 = NULL, *src15 = NULL, *src16 = NULL;

	char *msg = NULL;

	// assert calling sanity
	assert(ret != NULL);


	// bat-id -> BAT-descriptor
	if ((src1 = BATdescriptor(*arg1)) == NULL)
		throw(MAL, "batudf.skyline", RUNTIME_OBJECT_MISSING);
	if ((src2 = BATdescriptor(*arg2)) == NULL)
		throw(MAL, "batudf.skyline", RUNTIME_OBJECT_MISSING);
	if ((src3 = BATdescriptor(*arg3)) == NULL)
		throw(MAL, "batudf.skyline", RUNTIME_OBJECT_MISSING);
	if ((src4 = BATdescriptor(*arg4)) == NULL)
		throw(MAL, "batudf.skyline", RUNTIME_OBJECT_MISSING);
	if ((src5 = BATdescriptor(*arg5)) == NULL)
		throw(MAL, "batudf.skyline", RUNTIME_OBJECT_MISSING);
	if ((src6 = BATdescriptor(*arg6)) == NULL)
		throw(MAL, "batudf.skyline", RUNTIME_OBJECT_MISSING);
	if ((src7 = BATdescriptor(*arg7)) == NULL)
		throw(MAL, "batudf.skyline", RUNTIME_OBJECT_MISSING);
	if ((src8 = BATdescriptor(*arg8)) == NULL)
		throw(MAL, "batudf.skyline", RUNTIME_OBJECT_MISSING);
	if ((src9 = BATdescriptor(*arg9)) == NULL)
		throw(MAL, "batudf.skyline", RUNTIME_OBJECT_MISSING);
	if ((src10 = BATdescriptor(*arg10)) == NULL)
		throw(MAL, "batudf.skyline", RUNTIME_OBJECT_MISSING);
	if ((src11 = BATdescriptor(*arg11)) == NULL)
		throw(MAL, "batudf.skyline", RUNTIME_OBJECT_MISSING);
	if ((src12 = BATdescriptor(*arg12)) == NULL)
		throw(MAL, "batudf.skyline", RUNTIME_OBJECT_MISSING);
	if ((src13 = BATdescriptor(*arg13)) == NULL)
		throw(MAL, "batudf.skyline", RUNTIME_OBJECT_MISSING);
	if ((src14 = BATdescriptor(*arg14)) == NULL)
		throw(MAL, "batudf.skyline", RUNTIME_OBJECT_MISSING);
	if ((src15 = BATdescriptor(*arg15)) == NULL)
		throw(MAL, "batudf.skyline", RUNTIME_OBJECT_MISSING);
	if ((src16 = BATdescriptor(*arg16)) == NULL)
		throw(MAL, "batudf.skyline", RUNTIME_OBJECT_MISSING);
    
	// do the work
	BAT* srcs[16];

	srcs[0] = src1;
	srcs[1] = src2;
	srcs[2] = src3;
	srcs[3] = src4;
	srcs[4] = src5;
	srcs[5] = src6;
	srcs[6] = src7;
	srcs[7] = src8;
	srcs[8] = src9;
	srcs[9] = src10;
	srcs[10] = src11;
	srcs[11] = src12;
	srcs[12] = src13;
	srcs[13] = src14;
	srcs[14] = src15;
	srcs[15] = src16;
   //Determine number of dimensions
   int dim = 1;
   while(dim < 16)
   {
      if (srcs[dim-1] == srcs[dim])
         break;
      dim++;
   }
   if (dim < 2)
      throw (MAL, "batudf.skyline", RUNTIME_OBJECT_MISSING);

   printf("-------------- DIMENSIONS: %i --------------\n", dim);

	msg = UDFBATskylineGen_( &res, srcs, dim, false);

	// release input BAT-descriptor
	BBPunfix(src1->batCacheid);
	BBPunfix(src2->batCacheid);
	BBPunfix(src3->batCacheid);
	BBPunfix(src4->batCacheid);
	BBPunfix(src5->batCacheid);
	BBPunfix(src6->batCacheid);
	BBPunfix(src7->batCacheid);
	BBPunfix(src8->batCacheid);
	BBPunfix(src9->batCacheid);
	BBPunfix(src10->batCacheid);
	BBPunfix(src11->batCacheid);
	BBPunfix(src12->batCacheid);
	BBPunfix(src13->batCacheid);
	BBPunfix(src14->batCacheid);
	BBPunfix(src15->batCacheid);
	BBPunfix(src16->batCacheid);

	if (msg == MAL_SUCCEED) {
		// register result BAT in buffer pool
		BBPkeepref((*ret = res->batCacheid));
	}

	return msg;
}


/* actual implementation */
static char *
UDFBATmacfpga_(BAT **ret, BAT *src, const sht mul, const int add)
{
	BATiter li;
	BAT *bn = NULL;
	BUN p = 0, q = 0;

	// assert calling sanity
	assert(ret != NULL);

	// handle NULL pointer
	if (src == NULL)
		throw(MAL, "batudf.macfpga", RUNTIME_OBJECT_MISSING);

	// allocate result BAT 
	bn = BATnew(src->htype, TYPE_int, BATcount(src), TRANSIENT);
	if (bn == NULL) {
		throw(MAL, "batudf.macfpga", MAL_MALLOC_FAIL);
	}

	BATseqbase(bn, src->hseqbase);

   int i = 0;
   //unsigned short* res;

   // copy OIDS
   memcpy(bn->H->heap.base, src->H->heap.base, (src->H->width * src->batCount));
   //update free pointer
   bn->H->heap.free += (bn->H->width * src->batCount);
   bn->T->heap.free += (bn->T->width * src->batCount);
   //set dirty bit, not sure if necessary
   bn->H->heap.dirty = 1;
   bn->T->heap.dirty = 1;
   //set count
   BATsetcount(bn, src->batCount);
   //

   //Call FPGA
   FPGAmac(src->T->heap.base,
               src->batCount,
               bn->T->heap.base, 
               mul, 
               add);
  

	*ret = bn;

	return MAL_SUCCEED;
}
/* MAL wrapper */
char *
UDFBATmacfpga(bat *ret, const sht* mularg, const int* addarg,  const bat *arg)
{
	BAT *res = NULL, *src = NULL;
	char *msg = NULL;

	// assert calling sanity
	assert(ret != NULL && arg != NULL);


	// bat-id -> BAT-descriptor
	if ((src = BATdescriptor(*arg)) == NULL)
		throw(MAL, "batudf.macfpga", RUNTIME_OBJECT_MISSING);

	// do the work
	msg = UDFBATmacfpga_ ( &res, src, *mularg, *addarg );

	// release input BAT-descriptor
	BBPunfix(src->batCacheid);

	if (msg == MAL_SUCCEED) {
		// register result BAT in buffer pool
		BBPkeepref((*ret = res->batCacheid));
	}

	return msg;
}
/*
 * Generic "type-oblivious" version,
 * using generic "type-oblivious" BAT access interface.
 */

/* actual implementation */
static char *
UDFBATpercentagefpga_(BAT **ret, BAT *p_src, BAT *d_src)
{
    BATiter li;
	BAT *bn = NULL;
	BUN p = 0, q = 0;

	assert(ret != NULL);


	// handle NULL pointer
	if ((d_src == NULL) || (p_src == NULL))
		throw(MAL, "batudf.percentagefpga", RUNTIME_OBJECT_MISSING);
    
    // allocate result BAT 
	bn = BATnew(d_src->htype, TYPE_lng, 3, TRANSIENT);
	if (bn == NULL) {
		throw(MAL, "batudf.percentagefpga", MAL_MALLOC_FAIL);
	}
   // Set seq/key base for new BAT, TODO adapt keyness???
	BATseqbase(bn, d_src->hseqbase);

   int i = 0;
   //unsigned short* res;

   // copy OIDS
   memcpy(bn->H->heap.base, d_src->H->heap.base, (d_src->H->width * 3));
   //update free pointer
   bn->H->heap.free += (bn->H->width * 3);
   bn->T->heap.free += (bn->T->width * 3);
   //set dirty bit, not sure if necessary
   bn->H->heap.dirty = 1;
   bn->T->heap.dirty = 1;
   //set count
   BATsetcount(bn, 3);

   //Call FPGA
   unsigned long int * res = FPGApercentage(d_src->T->heap.base,
                            p_src->T->heap.base,
                            bn->T->heap.base,
               				d_src->batCount);


    memcpy(bn->T->heap.base, res, 3*sizeof(unsigned long int));
    *ret = bn;
}

/* MAL wrapper */
char *
UDFBATpercentagefpga(bat *ret, bat *arg1, const bat *arg2)
{
	BAT *res = NULL, *d_src = NULL, *p_src = NULL;
	char *msg = NULL;

	// assert calling sanity
	assert(ret != NULL && arg1 != NULL && arg2 != NULL);


	// bat-id -> BAT-descriptor
	if ((d_src = BATdescriptor(*arg2)) == NULL)
		throw(MAL, "batudf.percentagefpga", RUNTIME_OBJECT_MISSING);

	if ((p_src = BATdescriptor(*arg1)) == NULL)
		throw(MAL, "batudf.percentagefpga", RUNTIME_OBJECT_MISSING);

	// do the work
	msg = UDFBATpercentagefpga_ ( &res, p_src, d_src );

	// release input BAT-descriptor
	BBPunfix(d_src->batCacheid);
	BBPunfix(p_src->batCacheid);

	if (msg == MAL_SUCCEED) {
		// register result BAT in buffer pool
		BBPkeepref((*ret = res->batCacheid));
	}

	return msg;
}

/*
 * Generic "type-oblivious" version,
 * using generic "type-oblivious" BAT access interface.
 */

/* actual implementation */
static char *
UDFBATmadpercfpga_(BAT **ret, BAT *p_src, BAT *d_src, int a, int b)
{
	

    BATiter li;
	BAT *bn = NULL;
	BUN p = 0, q = 0;

	assert(ret != NULL);


	// handle NULL pointer
	if ((d_src == NULL) || (p_src == NULL))
		throw(MAL, "batudf.madpercfpga", RUNTIME_OBJECT_MISSING);
    
    // allocate result BAT 
	bn = BATnew(d_src->htype, TYPE_lng, 3, TRANSIENT);
	if (bn == NULL) {
		throw(MAL, "batudf.madpercfpga", MAL_MALLOC_FAIL);
	}
   // Set seq/key base for new BAT, TODO adapt keyness???
	BATseqbase(bn, d_src->hseqbase);

   int i = 0;
   //unsigned short* res;

   // copy OIDS
   memcpy(bn->H->heap.base, d_src->H->heap.base, (d_src->H->width * 3));
   //update free pointer
   bn->H->heap.free += (bn->H->width * 3);
   bn->T->heap.free += (bn->T->width * 3);
   //set dirty bit, not sure if necessary
   bn->H->heap.dirty = 1;
   bn->T->heap.dirty = 1;
   //set count
   BATsetcount(bn, 3);

   //Call FPGA
   unsigned long int * res = FPGAmadperc(d_src->T->heap.base,
                            p_src->T->heap.base,
                            bn->T->heap.base,
               				d_src->batCount, a, b);


    memcpy(bn->T->heap.base, res, 3*sizeof(unsigned long int));
    *ret = bn;

	return MAL_SUCCEED;
}

/* MAL wrapper */
char *
UDFBATmadpercfpga(bat *ret, const int* alpha, const int* beta, bat *arg1, const bat *arg2)
{
	BAT *res = NULL, *d_src = NULL, *p_src = NULL;
	char *msg = NULL;

	// assert calling sanity
	assert(ret != NULL && arg1 != NULL && arg2 != NULL);


	// bat-id -> BAT-descriptor
	if ((d_src = BATdescriptor(*arg2)) == NULL)
		throw(MAL, "batudf.percentagefpga", RUNTIME_OBJECT_MISSING);

	if ((p_src = BATdescriptor(*arg1)) == NULL)
		throw(MAL, "batudf.percentagefpga", RUNTIME_OBJECT_MISSING);

	// do the work
	msg = UDFBATmadpercfpga_ ( &res, p_src, d_src, *alpha, *beta );

	// release input BAT-descriptor
	BBPunfix(d_src->batCacheid);
	BBPunfix(p_src->batCacheid);

	if (msg == MAL_SUCCEED) {
		// register result BAT in buffer pool
		BBPkeepref((*ret = res->batCacheid));
	}

	return msg;
}

/*
 * Generic "type-oblivious" version,
 * using generic "type-oblivious" BAT access interface.
 */

/* actual implementation */
static char *
UDFBATregexpercfpga_(BAT **ret, BAT *src_int, BAT *src_str, const char *regex)
{
    BATiter li;
	BAT *bn = NULL;
	BUN p = 0, q = 0;

	assert(ret != NULL);


	// handle NULL pointer
	if (src_str == NULL)
		throw(MAL, "batudf.regexpercfpga", RUNTIME_OBJECT_MISSING);

	if (src_int == NULL)
		throw(MAL, "batudf.regexpercfpga", RUNTIME_OBJECT_MISSING);
    
    // allocate result BAT 
	bn = BATnew(src_int->htype, TYPE_lng, 3, TRANSIENT);
	if (bn == NULL) {
		throw(MAL, "batudf.regexpercfpga", MAL_MALLOC_FAIL);
	}
   // Set seq/key base for new BAT, TODO adapt keyness???
	BATseqbase(bn, src_int->hseqbase);

   int i = 0;
   //unsigned short* res;

   // copy OIDS
   memcpy(bn->H->heap.base, src_int->H->heap.base, (src_int->H->width * 3));
   //update free pointer
   bn->H->heap.free += (bn->H->width * 3);
   bn->T->heap.free += (bn->T->width * 3);
   //set dirty bit, not sure if necessary
   bn->H->heap.dirty = 1;
   bn->T->heap.dirty = 1;
   //set count
   BATsetcount(bn, 3);

   //memset(bn->T->heap.base, 0, sizeof(int));
   //Call FPGA
   unsigned long int * res = FPGAregexperc(src_str->T->heap.base,
               src_str->T->vheap->base,
               src_str->batCount,
               src_str->T->width,
               src_int->T->heap.base,
               regex);

	memcpy(bn->T->heap.base, res, 3*sizeof(unsigned long int));
    *ret = bn;

	return MAL_SUCCEED;
}

/* MAL wrapper */
char *
UDFBATregexpercfpga(bat *ret, const char **regex, const bat *arg1, const bat *arg2)
{
	BAT *res = NULL, *src_str = NULL, *src_int = NULL;
	char *msg = NULL;

	// assert calling sanity
	assert(ret != NULL && arg1 != NULL && arg2 != NULL);
   printf("regex: %s\n", *regex); //TODO check for NULL


	// bat-id -> BAT-descriptor
	if ((src_str = BATdescriptor(*arg1)) == NULL)
		throw(MAL, "batudf.regexpercfpga", RUNTIME_OBJECT_MISSING);

	if ((src_int = BATdescriptor(*arg2)) == NULL)
		throw(MAL, "batudf.regexpercfpga", RUNTIME_OBJECT_MISSING);

	// do the work
	msg = UDFBATregexpercfpga_ ( &res, src_int, src_str, *regex );

	// release input BAT-descriptor
	BBPunfix(src_int->batCacheid);
	BBPunfix(src_str->batCacheid);

	if (msg == MAL_SUCCEED) {
		// register result BAT in buffer pool
		BBPkeepref((*ret = res->batCacheid));
	}

	return msg;
}


static char *
UDFBAThwselection_(BAT **res, 	const BAT *b1, const char* selectionType1, const int lowerThreshold1, const int upperThreshold1)
{
	/* handle NULL pointer */
	if (b1 == NULL)
	        throw(MAL, "batudf.hwselection", RUNTIME_OBJECT_MISSING);

	int oneCount = (int)BATcount(b1);

	int *one;
	one = (int*) Tloc(b1, BUNfirst(b1));

	printf("rel1 num_tuples %d\n", oneCount);

	BAT *bres = NULL;
	bres = BATnew(TYPE_void, TYPE_int, oneCount, TRANSIENT);
	if (bres == NULL)
	    throw(MAL, "batudf.hwselection", MAL_MALLOC_FAIL);

	int* dest = (int*)Tloc(bres, BUNfirst(bres));

	//--------------------------------------------------------------------------------------FPGA Part Begin
	int result =  FPGAselection(one, selectionType1, lowerThreshold1, upperThreshold1, oneCount, dest);
	//--------------------------------------------------------------------------------------FPGA Part End

	// bit* output = (bit*)Tloc(bres, BUNfirst(bres));

	// int i;
	// for (i = 0; i < oneCount; i++) {
	// 	if (dest [i] > 0)
	// 		output[i] = TRUE;
	// 	else
	// 		output[i] = FALSE;
	// }

	BATseqbase(bres, b1->hseqbase); /* result head has same seqbase as input */
	// copy OIDS
	memcpy(bres->H->heap.base, b1->H->heap.base, (b1->H->width * b1->batCount));
	//update free pointer
	bres->H->heap.free += (bres->H->width * b1->batCount);
	bres->T->heap.free += (bres->T->width * b1->batCount);
	//set dirty bit, not sure if necessary
	bres->H->heap.dirty = 1;
	bres->T->heap.dirty = 1;
	BATsetcount(bres, oneCount);

	/* set result properties */
	// bres->hdense = TRUE;              /* result head is dense */
	// bres->hsorted = 1;                 result head is sorted 
	// bres->hrevsorted = (BATcount(bres) <= 1);
	// BATkey(bres, TRUE);               /* result head is key (unique) */

	*res = bres;

	return MAL_SUCCEED;
}

char *
UDFBAThwselection(bat *res, const bat *i1, const char** selectionType1, const int* lowerThreshold1, const int* upperThreshold1)
{
	printf("I am HW BAT selection!\n");
	fflush(stdout);

	BAT *bres = NULL, *b1 = NULL;
	char *msg = NULL;

	/* assert calling sanity */
	assert(res != NULL && i1 != NULL);

	/* bat-id -> BAT-descriptor */
	if ((b1 = BATdescriptor(*i1)) == NULL)
	        throw(MAL, "batudf.hwselection", RUNTIME_OBJECT_MISSING);

	/* do the work */
	msg = UDFBAThwselection_(&bres, b1, *selectionType1, *lowerThreshold1, *upperThreshold1);

	/* release input BAT-descriptors */
	BBPunfix(b1->batCacheid);

	if (msg == MAL_SUCCEED) {
        // register result BAT in buffer pool 
        BBPkeepref((*res = bres->batCacheid));
	}

	printf("HW BAT selection out!\n");
	fflush(stdout);

	return msg;
}

static char *
UDFBAThwselection2_(BAT **res, 	const BAT *b1, const char* selectionType1, const int lowerThreshold1, const int upperThreshold1,
								const BAT *b2, const char* selectionType2, const int lowerThreshold2, const int upperThreshold2)
{
	/* handle NULL pointer */
	if (b1 == NULL || b2 == NULL)
	        throw(MAL, "batudf.hwselection", RUNTIME_OBJECT_MISSING);

	/* check tail types */
	if (b1->ttype != b2->ttype) {
	        throw(MAL, "batudf.hwselection", "tails of input BATs must be identical");
	}

	int oneCount = (int)BATcount(b1);
	int twoCount = (int)BATcount(b2);

	int *one, *two;
	one = (int*) Tloc(b1, BUNfirst(b1));
	two = (int*) Tloc(b2, BUNfirst(b2));

	printf("rel1 num_tuples %d, rel2 num_tuples %d\n", oneCount, twoCount);

	BAT *bres = NULL;
	bres = BATnew(TYPE_void, TYPE_int, oneCount, TRANSIENT);
	if (bres == NULL)
	    throw(MAL, "batudf.hwselection", MAL_MALLOC_FAIL);

	int* dest = (int*) Tloc(bres, BUNfirst(bres));

	//--------------------------------------------------------------------------------------FPGA Part Begin
	int result =  FPGAselection2(one, selectionType1, lowerThreshold1, upperThreshold1, two, selectionType2, lowerThreshold2, upperThreshold2, oneCount, dest);
	//int result = memcpy(dest, one, oneCount*sizeof(int));
	//--------------------------------------------------------------------------------------FPGA Part End

	fflush(stdout);	
/*
	int *result;
	result = (int*) Tloc(bres, BUNfirst(bres));
	result[0] = (int)matches;
*/
	BATsetcount(bres, oneCount);

	/* set result properties */
	bres->hdense = TRUE;              /* result head is dense */
	BATseqbase(bres, b1->hseqbase); /* result head has same seqbase as input */
	bres->hsorted = 1;                /* result head is sorted */
	bres->hrevsorted = (BATcount(bres) <= 1);
	BATkey(bres, TRUE);               /* result head is key (unique) */

	*res = bres;

	return MAL_SUCCEED;
}

char *
UDFBAThwselection2(bat *res, const bat *i1, const char** selectionType1, const int* lowerThreshold1, const int* upperThreshold1, 
							const bat *i2, const char** selectionType2, const int* lowerThreshold2, const int* upperThreshold2)
{
	printf("I am HW BAT selection2!\n");
	fflush(stdout);

	BAT *bres = NULL, *b1 = NULL, *b2 = NULL;
	char *msg = NULL;

	/* assert calling sanity */
	assert(res != NULL && i1 != NULL && i2 != NULL);

	/* bat-id -> BAT-descriptor */
	if ((b1 = BATdescriptor(*i1)) == NULL)
	        throw(MAL, "batudf.hwselection", RUNTIME_OBJECT_MISSING);

	/* bat-id -> BAT-descriptor */
	if ((b2 = BATdescriptor(*i2)) == NULL) {
	        BBPunfix(b1->batCacheid);
	        throw(MAL, "batudf.hwselection", RUNTIME_OBJECT_MISSING);
	}

	/* do the work */
	msg = UDFBAThwselection2_(&bres, b1, *selectionType1, *lowerThreshold1, *upperThreshold1, b2, *selectionType2, *lowerThreshold2, *upperThreshold2);

	/* release input BAT-descriptors */
	BBPunfix(b1->batCacheid);
	BBPunfix(b2->batCacheid);

	if (msg == MAL_SUCCEED) {
        // register result BAT in buffer pool 
        BBPkeepref((*res = bres->batCacheid));
	}

	printf("HW BAT selection2 out!\n");
	fflush(stdout);

	return msg;
}

static char*
UDFBAThwminmaxsum_(BAT **res, const BAT *b)
{
	/* handle NULL pointer */
	if (b == NULL)
	    throw(MAL, "batudf.hwselection", RUNTIME_OBJECT_MISSING);

	int oneCount = (int)BATcount(b);

	int *one;
	one = (int*) Tloc(b, BUNfirst(b));

	printf("rel num_tuples %d\n", oneCount);

	BAT *bres = NULL;
	bres = BATnew(TYPE_void, TYPE_int, oneCount, TRANSIENT);
	if (bres == NULL)
	    throw(MAL, "batudf.hwselection", MAL_MALLOC_FAIL);

	int* dest = (int*) Tloc(bres, BUNfirst(bres));

	//--------------------------------------------------------------------------------------FPGA Part Begin
	int result =  FPGAminmaxsum(one, oneCount, dest);
	//--------------------------------------------------------------------------------------FPGA Part End

	BATsetcount(bres, 3);

	/* set result properties */
	bres->hdense = TRUE;              /* result head is dense */
	BATseqbase(bres, b->hseqbase); 		/* result head has same seqbase as input */
	bres->hsorted = 1;                /* result head is sorted */
	bres->hrevsorted = (BATcount(bres) <= 1);
	BATkey(bres, TRUE);               /* result head is key (unique) */

	*res = bres;

	return MAL_SUCCEED;
}

char *
UDFBAThwminmaxsum(bat* res, const bat* i)
{
	printf("I am HW BAT minmaxsum\n");
	fflush(stdout);

	BAT *bres = NULL, *b = NULL;
	char *msg = NULL;

	/* assert calling sanity */
	assert(res != NULL && i != NULL);

	/* bat-id -> BAT-descriptor */
	if ((b = BATdescriptor(*i)) == NULL)
	        throw(MAL, "batudf.hwselection", RUNTIME_OBJECT_MISSING);

	msg = UDFBAThwminmaxsum_(&bres, b);

	BBPunfix(b->batCacheid);

	if(msg == MAL_SUCCEED){
		// register result BAT in buffer pool 
        BBPkeepref((*res = bres->batCacheid));
	}

	printf("HW BAT minmaxsum out!\n");
	fflush(stdout);

	return msg;
}


/* fuse */

/* instantiate type-specific functions */

#define UI bte
#define UU unsigned char
#define UO sht
#include "udf_impl.h"
#undef UI
#undef UU
#undef UO

#define UI sht
#define UU unsigned short
#define UO int
#include "udf_impl.h"
#undef UI
#undef UU
#undef UO

#define UI int
#define UU unsigned int
#define UO lng
#include "udf_impl.h"
#undef UI
#undef UU
#undef UO

#ifdef HAVE_HGE
#define UI lng
#ifdef HAVE_LONG_LONG
#define UU unsigned long long
#else
#ifdef HAVE___INT64
#define UU unsigned __int64
#endif
#endif
#define UO hge
#include "udf_impl.h"
#undef UI
#undef UU
#undef UO
#endif

/* BAT fuse */

/* actual implementation */
static char *
UDFBATfuse_(BAT **ret, const BAT *bone, const BAT *btwo)
{
	BAT *bres = NULL;
	bit two_tail_sorted_unsigned = FALSE;
	bit two_tail_revsorted_unsigned = FALSE;
	BUN n;
	char *msg = NULL;

	/* assert calling sanity */
	assert(ret != NULL);

	/* handle NULL pointer */
	if (bone == NULL || btwo == NULL)
		throw(MAL, "batudf.fuse", RUNTIME_OBJECT_MISSING);

	/* check for dense & aligned heads */
	if (!BAThdense(bone) ||
	    !BAThdense(btwo) ||
	    BATcount(bone) != BATcount(btwo) ||
	    bone->hseqbase != btwo->hseqbase) {
		throw(MAL, "batudf.fuse",
		      "heads of input BATs must be aligned");
	}
	n = BATcount(bone);

	/* check tail types */
	if (bone->ttype != btwo->ttype) {
		throw(MAL, "batudf.fuse",
		      "tails of input BATs must be identical");
	}

	/* allocate result BAT */
	switch (bone->ttype) {
	case TYPE_bte:
		bres = BATnew(TYPE_void, TYPE_sht, n, TRANSIENT);
		break;
	case TYPE_sht:
		bres = BATnew(TYPE_void, TYPE_int, n, TRANSIENT);
		break;
	case TYPE_int:
		bres = BATnew(TYPE_void, TYPE_lng, n, TRANSIENT);
		break;
#ifdef HAVE_HGE
	case TYPE_lng:
		bres = BATnew(TYPE_void, TYPE_hge, n, TRANSIENT);
		break;
#endif
	default:
		throw(MAL, "batudf.fuse",
		      "tails of input BATs must be one of {bte, sht, int"
#ifdef HAVE_HGE
		      ", lng"
#endif
		      "}");
	}
	if (bres == NULL)
		throw(MAL, "batudf.fuse", MAL_MALLOC_FAIL);

	/* call type-specific core algorithm */
	switch (bone->ttype) {
	case TYPE_bte:
		msg = UDFBATfuse_bte_sht ( bres, bone, btwo, n,
			&two_tail_sorted_unsigned, &two_tail_revsorted_unsigned );
		break;
	case TYPE_sht:
		msg = UDFBATfuse_sht_int ( bres, bone, btwo, n,
			&two_tail_sorted_unsigned, &two_tail_revsorted_unsigned );
		break;
	case TYPE_int:
		msg = UDFBATfuse_int_lng ( bres, bone, btwo, n,
			&two_tail_sorted_unsigned, &two_tail_revsorted_unsigned );
		break;
#ifdef HAVE_HGE
	case TYPE_lng:
		msg = UDFBATfuse_lng_hge ( bres, bone, btwo, n,
			&two_tail_sorted_unsigned, &two_tail_revsorted_unsigned );
		break;
#endif
	default:
		BBPunfix(bres->batCacheid);
		throw(MAL, "batudf.fuse",
		      "tails of input BATs must be one of {bte, sht, int"
#ifdef HAVE_HGE
		      ", lng"
#endif
		      "}");
	}

	if (msg != MAL_SUCCEED) {
		BBPunfix(bres->batCacheid);
	} else {
		/* set number of tuples in result BAT */
		BATsetcount(bres, n);

		/* set result properties */
		bres->hdense = TRUE;              /* result head is dense */
		BATseqbase(bres, bone->hseqbase); /* result head has same seqbase as input */
		bres->hsorted = 1;                /* result head is sorted */
		bres->hrevsorted = (BATcount(bres) <= 1);
		BATkey(bres, TRUE);               /* result head is key (unique) */

		/* Result tail is sorted, if the left/first input tail is
		 * sorted and key (unique), or if the left/first input tail is
		 * sorted and the second/right input tail is sorted and the
		 * second/right tail values are either all >= 0 or all < 0;
		 * otherwise, we cannot tell.
		 */
		if (BATtordered(bone)
		    && (BATtkey(bone) || two_tail_sorted_unsigned))
			bres->tsorted = 1;
		else
			bres->tsorted = (BATcount(bres) <= 1);
		if (BATtrevordered(bone)
		    && (BATtkey(bone) || two_tail_revsorted_unsigned))
			bres->trevsorted = 1;
		else
			bres->trevsorted = (BATcount(bres) <= 1);
		/* result tail is key (unique), iff both input tails are */
		BATkey(BATmirror(bres), BATtkey(bone) || BATtkey(btwo));

		*ret = bres;
	}

	return msg;
}

/* MAL wrapper */
char *
UDFBATfuse(bat *ires, const bat *ione, const bat *itwo)
{
	BAT *bres = NULL, *bone = NULL, *btwo = NULL;
	char *msg = NULL;

	/* assert calling sanity */
	assert(ires != NULL && ione != NULL && itwo != NULL);

	/* bat-id -> BAT-descriptor */
	if ((bone = BATdescriptor(*ione)) == NULL)
		throw(MAL, "batudf.fuse", RUNTIME_OBJECT_MISSING);

	/* bat-id -> BAT-descriptor */
	if ((btwo = BATdescriptor(*itwo)) == NULL) {
		BBPunfix(bone->batCacheid);
		throw(MAL, "batudf.fuse", RUNTIME_OBJECT_MISSING);
	}

	/* do the work */
	msg = UDFBATfuse_ ( &bres, bone, btwo );

	/* release input BAT-descriptors */
	BBPunfix(bone->batCacheid);
	BBPunfix(btwo->batCacheid);

	if (msg == MAL_SUCCEED) {
		/* register result BAT in buffer pool */
		BBPkeepref((*ires = bres->batCacheid));
	}

	return msg;
}
