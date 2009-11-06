/* fpgivs.f -- translated by f2c (version 20061008).
   You must link the resulting object file with libf2c:
	on Microsoft Windows system, link with libf2c.lib;
	on Linux or Unix systems, link with .../path/to/libf2c.a -lm
	or, if you install libf2c.a in a standard place, with -lf2c -lm
	-- in that order, at the end of the command line, as in
		cc *.o -lf2c -lm
	Source for libf2c is in /netlib/f2c/libf2c.zip, e.g.,

		http://www.netlib.org/f2c/libf2c.zip
*/

#include "f2c.h"

/*<       subroutine fpgivs(piv,ww,cos,sin) >*/
/* Subroutine */ int fpgivs_(doublereal *piv, doublereal *ww, doublereal *
	cos__, doublereal *sin__)
{
    /* System generated locals */
    doublereal d__1;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    static doublereal dd, one, store;

/*  subroutine fpgivs calculates the parameters of a givens */
/*  transformation . */
/*  .. */
/*  ..scalar arguments.. */
/*<       real piv,ww,cos,sin >*/
/*  ..local scalars.. */
/*<       real dd,one,store >*/
/*  ..function references.. */
/*<       real abs,sqrt >*/
/*  .. */
/*<       one = 0.1e+01 >*/
    one = 1.;
/*<       store = abs(piv) >*/
    store = abs(*piv);
/*<       if(store.ge.ww) dd = store*sqrt(one+(ww/piv)**2) >*/
    if (store >= *ww) {
/* Computing 2nd power */
	d__1 = *ww / *piv;
	dd = store * sqrt(one + d__1 * d__1);
    }
/*<       if(store.lt.ww) dd = ww*sqrt(one+(piv/ww)**2) >*/
    if (store < *ww) {
/* Computing 2nd power */
	d__1 = *piv / *ww;
	dd = *ww * sqrt(one + d__1 * d__1);
    }
/*<       cos = ww/dd >*/
    *cos__ = *ww / dd;
/*<       sin = piv/dd >*/
    *sin__ = *piv / dd;
/*<       ww = dd >*/
    *ww = dd;
/*<       return >*/
    return 0;
/*<       end >*/
} /* fpgivs_ */

