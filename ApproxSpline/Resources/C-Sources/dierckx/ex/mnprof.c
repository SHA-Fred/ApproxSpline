/* mnprof.f -- translated by f2c (version 19961017).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static integer c__1 = 1;
static integer c__15 = 15;

/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
/* c                                                                    cc */
/* c              mnprof : profil test program                          cc */
/* c                                                                    cc */
/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
/* Main program */ MAIN__(void)
{
    /* Format strings */
    static char fmt_900[] = "(\0020tensor product spline of degrees\002,2i3)";
    static char fmt_910[] = "(1x,\002position of the knots in the x-direction\002)";
    static char fmt_920[] = "(1x,15f5.1)";
    static char fmt_930[] = "(1x,\002position of the knots in the y-direction\002)";
    static char fmt_940[] = "(\002 b-spline coefficients \002)";
    static char fmt_950[] = "(1x,8f9.4)";
    static char fmt_955[] = "(\0020b-spline coefficients of the profile f(y)=s(\002,f3.1,\002,y)\002)";
    static char fmt_960[] = "(\0020\002,\002spline values at selected grid points\002)";
    static char fmt_970[] = "(\0020\002,8x,\002y\002,4x,6(4x,f4.1))";
    static char fmt_980[] = "(\002 \002,7x,\002x\002)";
    static char fmt_990[] = "(6x,f4.1,5x,6f8.2)";
    static char fmt_995[] = "(\0020b-spline coefficients of the profile g(x)=s(x,\002,f3.1,\002)\002)";

    /* System generated locals */
    integer i__1, i__2, i__3;

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);
    /* Subroutine */ int s_stop(char *, ftnlen);

    /* Local variables */
    static real facx;
    static integer iopt;
    static real c__[100];
    static integer i__, j, m;
    static real u, x[6], y[6], z__[36];
    extern /* Subroutine */ int splev_(real *, integer *, real *, integer *, real *, real *, integer *, integer *);
    static integer m0, m1, m2, m3;
    static real cc[15];
    static integer nc, kx, ky, mx, my, nx, ny;
    static real tx[15], ty[15];
    extern /* Subroutine */ int profil_(integer *, real *, integer *, real *, integer *, real *, integer *, integer *, real *, integer *, real *, integer *);
    static integer kx1, ky1;
    static real fac;
    static integer ier, nkx1, nky1;

    /* Fortran I/O blocks */
    static cilist io___25 = { 0, 6, 0, fmt_900, 0 };
    static cilist io___26 = { 0, 6, 0, fmt_910, 0 };
    static cilist io___27 = { 0, 6, 0, fmt_920, 0 };
    static cilist io___28 = { 0, 6, 0, fmt_930, 0 };
    static cilist io___29 = { 0, 6, 0, fmt_920, 0 };
    static cilist io___31 = { 0, 6, 0, fmt_940, 0 };
    static cilist io___32 = { 0, 6, 0, fmt_950, 0 };
    static cilist io___37 = { 0, 6, 0, fmt_955, 0 };
    static cilist io___38 = { 0, 6, 0, fmt_950, 0 };
    static cilist io___40 = { 0, 6, 0, fmt_960, 0 };
    static cilist io___41 = { 0, 6, 0, fmt_970, 0 };
    static cilist io___42 = { 0, 6, 0, fmt_980, 0 };
    static cilist io___43 = { 0, 6, 0, fmt_990, 0 };
    static cilist io___44 = { 0, 6, 0, fmt_995, 0 };
    static cilist io___45 = { 0, 6, 0, fmt_950, 0 };
    static cilist io___46 = { 0, 6, 0, fmt_960, 0 };
    static cilist io___47 = { 0, 6, 0, fmt_970, 0 };
    static cilist io___48 = { 0, 6, 0, fmt_980, 0 };
    static cilist io___49 = { 0, 6, 0, fmt_990, 0 };


/*  we set up the grid points for evaluating the tensor product splines. */
    mx = 6;
    my = 6;
    m = mx * my;
    for (i__ = 1; i__ <= 6; ++i__) {
	x[i__ - 1] = (i__ - 1) * .2f;
	y[i__ - 1] = x[i__ - 1];
/* L10: */
    }
/*  loop for different spline degrees with respect to the x-variable */
    for (kx = 3; kx <= 5; kx += 2) {
/*  the knots in the x-direction */
	tx[kx + 1] = .4f;
	tx[kx + 2] = .7f;
	tx[kx + 3] = .9f;
	kx1 = kx + 1;
	nx = (kx1 << 1) + 3;
	j = nx;
	i__1 = kx1;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    tx[i__ - 1] = 0.f;
	    tx[j - 1] = 1.f;
	    --j;
/* L20: */
	}
/*  loop for different spline degrees with respect to the y-variable */
	for (ky = 2; ky <= 3; ++ky) {
/*  the knots in the y-direction */
	    ty[ky + 1] = .3f;
	    ty[ky + 2] = .8f;
	    ky1 = ky + 1;
	    ny = (ky1 << 1) + 2;
	    j = ny;
	    i__1 = ky1;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		ty[i__ - 1] = 0.f;
		ty[j - 1] = 1.f;
		--j;
/* L30: */
	    }
/*  we generate the b-spline coefficients for the test function x*y */
	    nkx1 = nx - kx1;
	    nky1 = ny - ky1;
	    i__1 = nky1;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		c__[i__ - 1] = 0.f;
/* L40: */
	    }
	    i__1 = nkx1;
	    for (i__ = 2; i__ <= i__1; ++i__) {
		c__[(i__ - 1) * nky1] = 0.f;
/* L50: */
	    }
	    fac = (real) (kx * ky);
	    m0 = 1;
	    i__1 = nkx1;
	    for (i__ = 2; i__ <= i__1; ++i__) {
		m1 = m0 + nky1;
		facx = (tx[i__ + kx - 1] - tx[i__ - 1]) / fac;
		i__2 = nky1;
		for (j = 2; j <= i__2; ++j) {
		    m2 = m0 + 1;
		    m3 = m1 + 1;
		    c__[m3 - 1] = c__[m1 - 1] + c__[m2 - 1] - c__[m0 - 1] + facx * (ty[j + ky - 1] - ty[j - 1]);
		    ++m0;
		    ++m1;
/* L60: */
		}
		++m0;
/* L70: */
	    }
/*  printing of the spline information */
	    s_wsfe(&io___25);
	    do_fio(&c__1, (char *)&kx, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&ky, (ftnlen)sizeof(integer));
	    e_wsfe();
	    s_wsfe(&io___26);
	    e_wsfe();
	    s_wsfe(&io___27);
	    i__1 = nx;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		do_fio(&c__1, (char *)&tx[i__ - 1], (ftnlen)sizeof(real));
	    }
	    e_wsfe();
	    s_wsfe(&io___28);
	    e_wsfe();
	    s_wsfe(&io___29);
	    i__1 = ny;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		do_fio(&c__1, (char *)&ty[i__ - 1], (ftnlen)sizeof(real));
	    }
	    e_wsfe();
	    nc = nkx1 * nky1;
	    s_wsfe(&io___31);
	    e_wsfe();
	    s_wsfe(&io___32);
	    i__1 = nc;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		do_fio(&c__1, (char *)&c__[i__ - 1], (ftnlen)sizeof(real));
	    }
	    e_wsfe();
/*  we calculate a number of profiles f(y)=s(u,y) */
	    iopt = 0;
	    m0 = 1;
	    i__1 = mx;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		u = x[i__ - 1];
		profil_(&iopt, tx, &nx, ty, &ny, c__, &kx, &ky, &u, &c__15, cc, &ier);
		s_wsfe(&io___37);
		do_fio(&c__1, (char *)&u, (ftnlen)sizeof(real));
		e_wsfe();
		s_wsfe(&io___38);
		i__2 = nky1;
		for (j = 1; j <= i__2; ++j) {
		    do_fio(&c__1, (char *)&cc[j - 1], (ftnlen)sizeof(real));
		}
		e_wsfe();
/*  evaluation of the one-dimensional spline f(y) */
		splev_(ty, &ny, cc, &ky, y, &z__[m0 - 1], &my, &ier);
		m0 += my;
/* L80: */
	    }
	    s_wsfe(&io___40);
	    e_wsfe();
	    s_wsfe(&io___41);
	    i__1 = my;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		do_fio(&c__1, (char *)&y[i__ - 1], (ftnlen)sizeof(real));
	    }
	    e_wsfe();
	    s_wsfe(&io___42);
	    e_wsfe();
	    m2 = 0;
	    i__1 = mx;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		m1 = m2 + 1;
		m2 += my;
		s_wsfe(&io___43);
		do_fio(&c__1, (char *)&x[i__ - 1], (ftnlen)sizeof(real));
		i__2 = m2;
		for (j = m1; j <= i__2; ++j) {
		    do_fio(&c__1, (char *)&z__[j - 1], (ftnlen)sizeof(real));
		}
		e_wsfe();
/* L100: */
	    }
/*  we calculate a number of profiles g(x)=s(x,u) */
	    iopt = 1;
	    m0 = 1;
	    i__1 = my;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		u = y[i__ - 1];
		profil_(&iopt, tx, &nx, ty, &ny, c__, &kx, &ky, &u, &c__15, cc, &ier);
		s_wsfe(&io___44);
		do_fio(&c__1, (char *)&u, (ftnlen)sizeof(real));
		e_wsfe();
		s_wsfe(&io___45);
		i__2 = nkx1;
		for (j = 1; j <= i__2; ++j) {
		    do_fio(&c__1, (char *)&cc[j - 1], (ftnlen)sizeof(real));
		}
		e_wsfe();
/*  evaluation of the one-dimensional spline g(x) */
		splev_(tx, &nx, cc, &kx, x, &z__[m0 - 1], &mx, &ier);
		m0 += mx;
/* L120: */
	    }
	    s_wsfe(&io___46);
	    e_wsfe();
	    s_wsfe(&io___47);
	    i__1 = my;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		do_fio(&c__1, (char *)&y[i__ - 1], (ftnlen)sizeof(real));
	    }
	    e_wsfe();
	    s_wsfe(&io___48);
	    e_wsfe();
	    i__1 = mx;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		s_wsfe(&io___49);
		do_fio(&c__1, (char *)&x[i__ - 1], (ftnlen)sizeof(real));
		i__2 = m;
		i__3 = mx;
		for (j = i__; i__3 < 0 ? j >= i__2 : j <= i__2; j += i__3) {
		    do_fio(&c__1, (char *)&z__[j - 1], (ftnlen)sizeof(real));
		}
		e_wsfe();
/* L140: */
	    }
/* L200: */
	}
/* L300: */
    }
    s_stop("", 0L);
/*  format statements. */
    return 0;
} /* MAIN__ */

