/* fpsurf.f -- translated by f2c (version 20061008).
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

/*<    >*/
/* Subroutine */ int fpsurf_(integer *iopt, integer *m, doublereal *x, 
	doublereal *y, doublereal *z__, doublereal *w, doublereal *xb, 
	doublereal *xe, doublereal *yb, doublereal *ye, integer *kxx, integer 
	*kyy, doublereal *s, integer *nxest, integer *nyest, doublereal *eta, 
	doublereal *tol, integer *maxit, integer *nmax, integer *km1, integer 
	*km2, integer *ib1, integer *ib3, integer *nc, integer *intest, 
	integer *nrest, integer *nx0, doublereal *tx, integer *ny0, 
	doublereal *ty, doublereal *c__, doublereal *fp, doublereal *fp0, 
	doublereal *fpint, doublereal *coord, doublereal *f, doublereal *ff, 
	doublereal *a, doublereal *q, doublereal *bx, doublereal *by, 
	doublereal *spx, doublereal *spy, doublereal *h__, integer *index, 
	integer *nummer, doublereal *wrk, integer *lwrk, integer *ier)
{
    /* System generated locals */
    integer a_dim1, a_offset, q_dim1, q_offset, bx_dim1, bx_offset, by_dim1, 
	    by_offset, spx_dim1, spx_offset, spy_dim1, spy_offset, i__1, i__2,
	     i__3, i__4, i__5, i__6;
    doublereal d__1;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    static integer i__, j, l, n;
    static doublereal p, f1, f2, f3;
    static integer i1, i2, i3, j1, l1, l2, n1;
    static doublereal p1, p2, p3, x0, x1, y0, y1;
    static integer la, ii, lf, lh, in;
    static doublereal wi, rn, hx[6], zi, sq;
    static integer kx, ky, lx, ly, nx, ny;
    static doublereal hy[6];
    static integer kx1, kx2, ky1, ky2;
    static doublereal acc;
    static integer ibb;
    static doublereal arg, one, cos__, ten, eps, hxi, sin__;
    static integer nxe, nye;
    static doublereal piv;
    static integer num;
    static doublereal fac1, fac2;
    static integer jxy, nxx, nyy, ich1, ich3;
    static doublereal con1, con4, con9;
    static integer num1, nk1x, nk1y;
    static doublereal half;
    static integer ncof;
    static doublereal dmax__;
    static integer nreg, rank, iter;
    static doublereal fpms, pinv;
    static integer irot, jrot, iband;
    static doublereal sigma, fpmax;
    static integer nminx, nminy;
    static doublereal store;
    static integer nrint, iband1, lwest, iband3, iband4;
    extern /* Subroutine */ int fpback_(doublereal *, doublereal *, integer *,
	     integer *, doublereal *, integer *);
    static integer ichang;
    extern /* Subroutine */ int fpdisc_(doublereal *, integer *, integer *, 
	    doublereal *, integer *), fporde_(doublereal *, doublereal *, 
	    integer *, integer *, integer *, doublereal *, integer *, 
	    doublereal *, integer *, integer *, integer *, integer *), 
	    fprank_(doublereal *, doublereal *, integer *, integer *, integer 
	    *, doublereal *, doublereal *, doublereal *, integer *, 
	    doublereal *, doublereal *, doublereal *);
    extern doublereal fprati_(doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);
    extern /* Subroutine */ int fpbspl_(doublereal *, integer *, integer *, 
	    doublereal *, integer *, doublereal *), fprota_(doublereal *, 
	    doublereal *, doublereal *, doublereal *), fpgivs_(doublereal *, 
	    doublereal *, doublereal *, doublereal *);

/*  .. */
/*  ..scalar arguments.. */
/*<       real xb,xe,yb,ye,s,eta,tol,fp,fp0 >*/
/*<    >*/
/*  ..array arguments.. */
/*<    >*/
/*<       integer index(nrest),nummer(m) >*/
/*  ..local scalars.. */
/*<    >*/
/*<    >*/
/*  ..local arrays.. */
/*<       real hx(6),hy(6) >*/
/*  ..function references.. */
/*<       real abs,fprati,sqrt >*/
/*<       integer min0 >*/
/*  ..subroutine references.. */
/*    fpback,fpbspl,fpgivs,fpdisc,fporde,fprank,fprota */
/*  .. */
/*  set constants */
/*<       one = 0.1e+01 >*/
    /* Parameter adjustments */
    --nummer;
    --w;
    --z__;
    --y;
    --x;
    --ty;
    --tx;
    spy_dim1 = *m;
    spy_offset = 1 + spy_dim1;
    spy -= spy_offset;
    spx_dim1 = *m;
    spx_offset = 1 + spx_dim1;
    spx -= spx_offset;
    by_dim1 = *nmax;
    by_offset = 1 + by_dim1;
    by -= by_offset;
    bx_dim1 = *nmax;
    bx_offset = 1 + bx_dim1;
    bx -= bx_offset;
    --h__;
    q_dim1 = *nc;
    q_offset = 1 + q_dim1;
    q -= q_offset;
    a_dim1 = *nc;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --ff;
    --f;
    --c__;
    --coord;
    --fpint;
    --index;
    --wrk;

    /* Function Body */
    one = 1.;
/*<       con1 = 0.1e0 >*/
    con1 = .1;
/*<       con9 = 0.9e0 >*/
    con9 = .9;
/*<       con4 = 0.4e-01 >*/
    con4 = .04;
/*<       half = 0.5e0 >*/
    half = .5;
/*<       ten = 0.1e+02 >*/
    ten = 10.;
/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
/* part 1: determination of the number of knots and their position.     c */
/* ****************************************************************     c */
/* given a set of knots we compute the least-squares spline sinf(x,y),  c */
/* and the corresponding weighted sum of squared residuals fp=f(p=inf). c */
/* if iopt=-1  sinf(x,y) is the requested approximation.                c */
/* if iopt=0 or iopt=1 we check whether we can accept the knots:        c */
/*   if fp <=s we will continue with the current set of knots.          c */
/*   if fp > s we will increase the number of knots and compute the     c */
/*      corresponding least-squares spline until finally  fp<=s.        c */
/* the initial choice of knots depends on the value of s and iopt.      c */
/*   if iopt=0 we first compute the least-squares polynomial of degree  c */
/*     kx in x and ky in y; nx=nminx=2*kx+2 and ny=nminy=2*ky+2.        c */
/*     fp0=f(0) denotes the corresponding weighted sum of squared       c */
/*     residuals                                                        c */
/*   if iopt=1 we start with the knots found at the last call of the    c */
/*     routine, except for the case that s>=fp0; then we can compute    c */
/*     the least-squares polynomial directly.                           c */
/* eventually the independent variables x and y (and the corresponding  c */
/* parameters) will be switched if this can reduce the bandwidth of the c */
/* system to be solved.                                                 c */
/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
/*  ichang denotes whether(1) or not(-1) the directions have been inter- */
/*  changed. */
/*<       ichang = -1 >*/
    ichang = -1;
/*<       x0 = xb >*/
    x0 = *xb;
/*<       x1 = xe >*/
    x1 = *xe;
/*<       y0 = yb >*/
    y0 = *yb;
/*<       y1 = ye >*/
    y1 = *ye;
/*<       kx = kxx >*/
    kx = *kxx;
/*<       ky = kyy >*/
    ky = *kyy;
/*<       kx1 = kx+1 >*/
    kx1 = kx + 1;
/*<       ky1 = ky+1 >*/
    ky1 = ky + 1;
/*<       nxe = nxest >*/
    nxe = *nxest;
/*<       nye = nyest >*/
    nye = *nyest;
/*<       eps = sqrt(eta) >*/
    eps = sqrt(*eta);
/*<       if(iopt.lt.0) go to 20 >*/
    if (*iopt < 0) {
	goto L20;
    }
/*  calculation of acc, the absolute tolerance for the root of f(p)=s. */
/*<       acc = tol*s >*/
    acc = *tol * *s;
/*<       if(iopt.eq.0) go to 10 >*/
    if (*iopt == 0) {
	goto L10;
    }
/*<       if(fp0.gt.s) go to 20 >*/
    if (*fp0 > *s) {
	goto L20;
    }
/*  initialization for the least-squares polynomial. */
/*<   10  nminx = 2*kx1 >*/
L10:
    nminx = kx1 << 1;
/*<       nminy = 2*ky1 >*/
    nminy = ky1 << 1;
/*<       nx = nminx >*/
    nx = nminx;
/*<       ny = nminy >*/
    ny = nminy;
/*<       ier = -2 >*/
    *ier = -2;
/*<       go to 30 >*/
    goto L30;
/*<   20  nx = nx0 >*/
L20:
    nx = *nx0;
/*<       ny = ny0 >*/
    ny = *ny0;
/*  main loop for the different sets of knots. m is a save upper bound */
/*  for the number of trials. */
/*<   30  do 420 iter=1,m >*/
L30:
    i__1 = *m;
    for (iter = 1; iter <= i__1; ++iter) {
/*  find the position of the additional knots which are needed for the */
/*  b-spline representation of s(x,y). */
/*<         l = nx >*/
	l = nx;
/*<         do 40 i=1,kx1 >*/
	i__2 = kx1;
	for (i__ = 1; i__ <= i__2; ++i__) {
/*<           tx(i) = x0 >*/
	    tx[i__] = x0;
/*<           tx(l) = x1 >*/
	    tx[l] = x1;
/*<           l = l-1 >*/
	    --l;
/*<   40    continue >*/
/* L40: */
	}
/*<         l = ny >*/
	l = ny;
/*<         do 50 i=1,ky1 >*/
	i__2 = ky1;
	for (i__ = 1; i__ <= i__2; ++i__) {
/*<           ty(i) = y0 >*/
	    ty[i__] = y0;
/*<           ty(l) = y1 >*/
	    ty[l] = y1;
/*<           l = l-1 >*/
	    --l;
/*<   50    continue >*/
/* L50: */
	}
/*  find nrint, the total number of knot intervals and nreg, the number */
/*  of panels in which the approximation domain is subdivided by the */
/*  intersection of knots. */
/*<         nxx = nx-2*kx1+1 >*/
	nxx = nx - (kx1 << 1) + 1;
/*<         nyy = ny-2*ky1+1 >*/
	nyy = ny - (ky1 << 1) + 1;
/*<         nrint = nxx+nyy >*/
	nrint = nxx + nyy;
/*<         nreg = nxx*nyy >*/
	nreg = nxx * nyy;
/*  find the bandwidth of the observation matrix a. */
/*  if necessary, interchange the variables x and y, in order to obtain */
/*  a minimal bandwidth. */
/*<         iband1 = kx*(ny-ky1)+ky >*/
	iband1 = kx * (ny - ky1) + ky;
/*<         l = ky*(nx-kx1)+kx >*/
	l = ky * (nx - kx1) + kx;
/*<         if(iband1.le.l) go to 130 >*/
	if (iband1 <= l) {
	    goto L130;
	}
/*<         iband1 = l >*/
	iband1 = l;
/*<         ichang = -ichang >*/
	ichang = -ichang;
/*<         do 60 i=1,m >*/
	i__2 = *m;
	for (i__ = 1; i__ <= i__2; ++i__) {
/*<           store = x(i) >*/
	    store = x[i__];
/*<           x(i) = y(i) >*/
	    x[i__] = y[i__];
/*<           y(i) = store >*/
	    y[i__] = store;
/*<   60    continue >*/
/* L60: */
	}
/*<         store = x0 >*/
	store = x0;
/*<         x0 = y0 >*/
	x0 = y0;
/*<         y0 = store >*/
	y0 = store;
/*<         store = x1 >*/
	store = x1;
/*<         x1 = y1 >*/
	x1 = y1;
/*<         y1 = store >*/
	y1 = store;
/*<         n = min0(nx,ny) >*/
	n = min(nx,ny);
/*<         do 70 i=1,n >*/
	i__2 = n;
	for (i__ = 1; i__ <= i__2; ++i__) {
/*<           store = tx(i) >*/
	    store = tx[i__];
/*<           tx(i) = ty(i) >*/
	    tx[i__] = ty[i__];
/*<           ty(i) = store >*/
	    ty[i__] = store;
/*<   70    continue >*/
/* L70: */
	}
/*<         n1 = n+1 >*/
	n1 = n + 1;
/*<         if(nx-ny) 80,120,100 >*/
	if ((i__2 = nx - ny) < 0) {
	    goto L80;
	} else if (i__2 == 0) {
	    goto L120;
	} else {
	    goto L100;
	}
/*<   80    do 90 i=n1,ny >*/
L80:
	i__2 = ny;
	for (i__ = n1; i__ <= i__2; ++i__) {
/*<           tx(i) = ty(i) >*/
	    tx[i__] = ty[i__];
/*<   90    continue >*/
/* L90: */
	}
/*<         go to 120 >*/
	goto L120;
/*<  100    do 110 i=n1,nx >*/
L100:
	i__2 = nx;
	for (i__ = n1; i__ <= i__2; ++i__) {
/*<           ty(i) = tx(i) >*/
	    ty[i__] = tx[i__];
/*<  110    continue >*/
/* L110: */
	}
/*<  120    l = nx >*/
L120:
	l = nx;
/*<         nx = ny >*/
	nx = ny;
/*<         ny = l >*/
	ny = l;
/*<         l = nxe >*/
	l = nxe;
/*<         nxe = nye >*/
	nxe = nye;
/*<         nye = l >*/
	nye = l;
/*<         l = nxx >*/
	l = nxx;
/*<         nxx = nyy >*/
	nxx = nyy;
/*<         nyy = l >*/
	nyy = l;
/*<         l = kx >*/
	l = kx;
/*<         kx = ky >*/
	kx = ky;
/*<         ky = l >*/
	ky = l;
/*<         kx1 = kx+1 >*/
	kx1 = kx + 1;
/*<         ky1 = ky+1 >*/
	ky1 = ky + 1;
/*<  130    iband = iband1+1 >*/
L130:
	iband = iband1 + 1;
/*  arrange the data points according to the panel they belong to. */
/*<         call fporde(x,y,m,kx,ky,tx,nx,ty,ny,nummer,index,nreg) >*/
	fporde_(&x[1], &y[1], m, &kx, &ky, &tx[1], &nx, &ty[1], &ny, &nummer[
		1], &index[1], &nreg);
/*  find ncof, the number of b-spline coefficients. */
/*<         nk1x = nx-kx1 >*/
	nk1x = nx - kx1;
/*<         nk1y = ny-ky1 >*/
	nk1y = ny - ky1;
/*<         ncof = nk1x*nk1y >*/
	ncof = nk1x * nk1y;
/*  initialize the observation matrix a. */
/*<         do 140 i=1,ncof >*/
	i__2 = ncof;
	for (i__ = 1; i__ <= i__2; ++i__) {
/*<           f(i) = 0. >*/
	    f[i__] = 0.;
/*<           do 140 j=1,iband >*/
	    i__3 = iband;
	    for (j = 1; j <= i__3; ++j) {
/*<             a(i,j) = 0. >*/
		a[i__ + j * a_dim1] = 0.;
/*<  140    continue >*/
/* L140: */
	    }
	}
/*  initialize the sum of squared residuals. */
/*<         fp = 0. >*/
	*fp = 0.;
/*  fetch the data points in the new order. main loop for the */
/*  different panels. */
/*<         do 250 num=1,nreg >*/
	i__3 = nreg;
	for (num = 1; num <= i__3; ++num) {
/*  fix certain constants for the current panel; jrot records the column */
/*  number of the first non-zero element in a row of the observation */
/*  matrix according to a data point of the panel. */
/*<           num1 = num-1 >*/
	    num1 = num - 1;
/*<           lx = num1/nyy >*/
	    lx = num1 / nyy;
/*<           l1 = lx+kx1 >*/
	    l1 = lx + kx1;
/*<           ly = num1-lx*nyy >*/
	    ly = num1 - lx * nyy;
/*<           l2 = ly+ky1 >*/
	    l2 = ly + ky1;
/*<           jrot = lx*nk1y+ly >*/
	    jrot = lx * nk1y + ly;
/*  test whether there are still data points in the panel. */
/*<           in = index(num) >*/
	    in = index[num];
/*<  150      if(in.eq.0) go to 250 >*/
L150:
	    if (in == 0) {
		goto L250;
	    }
/*  fetch a new data point. */
/*<           wi = w(in) >*/
	    wi = w[in];
/*<           zi = z(in)*wi >*/
	    zi = z__[in] * wi;
/*  evaluate for the x-direction, the (kx+1) non-zero b-splines at x(in). */
/*<           call fpbspl(tx,nx,kx,x(in),l1,hx) >*/
	    fpbspl_(&tx[1], &nx, &kx, &x[in], &l1, hx);
/*  evaluate for the y-direction, the (ky+1) non-zero b-splines at y(in). */
/*<           call fpbspl(ty,ny,ky,y(in),l2,hy) >*/
	    fpbspl_(&ty[1], &ny, &ky, &y[in], &l2, hy);
/*  store the value of these b-splines in spx and spy respectively. */
/*<           do 160 i=1,kx1 >*/
	    i__2 = kx1;
	    for (i__ = 1; i__ <= i__2; ++i__) {
/*<             spx(in,i) = hx(i) >*/
		spx[in + i__ * spx_dim1] = hx[i__ - 1];
/*<  160      continue >*/
/* L160: */
	    }
/*<           do 170 i=1,ky1 >*/
	    i__2 = ky1;
	    for (i__ = 1; i__ <= i__2; ++i__) {
/*<             spy(in,i) = hy(i) >*/
		spy[in + i__ * spy_dim1] = hy[i__ - 1];
/*<  170      continue >*/
/* L170: */
	    }
/*  initialize the new row of observation matrix. */
/*<           do 180 i=1,iband >*/
	    i__2 = iband;
	    for (i__ = 1; i__ <= i__2; ++i__) {
/*<             h(i) = 0. >*/
		h__[i__] = 0.;
/*<  180      continue >*/
/* L180: */
	    }
/*  calculate the non-zero elements of the new row by making the cross */
/*  products of the non-zero b-splines in x- and y-direction. */
/*<           i1 = 0 >*/
	    i1 = 0;
/*<           do 200 i=1,kx1 >*/
	    i__2 = kx1;
	    for (i__ = 1; i__ <= i__2; ++i__) {
/*<             hxi = hx(i) >*/
		hxi = hx[i__ - 1];
/*<             j1 = i1 >*/
		j1 = i1;
/*<             do 190 j=1,ky1 >*/
		i__4 = ky1;
		for (j = 1; j <= i__4; ++j) {
/*<               j1 = j1+1 >*/
		    ++j1;
/*<               h(j1) = hxi*hy(j)*wi >*/
		    h__[j1] = hxi * hy[j - 1] * wi;
/*<  190        continue >*/
/* L190: */
		}
/*<             i1 = i1+nk1y >*/
		i1 += nk1y;
/*<  200      continue >*/
/* L200: */
	    }
/*  rotate the row into triangle by givens transformations . */
/*<           irot = jrot >*/
	    irot = jrot;
/*<           do 220 i=1,iband >*/
	    i__2 = iband;
	    for (i__ = 1; i__ <= i__2; ++i__) {
/*<             irot = irot+1 >*/
		++irot;
/*<             piv = h(i) >*/
		piv = h__[i__];
/*<             if(piv.eq.0.) go to 220 >*/
		if (piv == 0.) {
		    goto L220;
		}
/*  calculate the parameters of the givens transformation. */
/*<             call fpgivs(piv,a(irot,1),cos,sin) >*/
		fpgivs_(&piv, &a[irot + a_dim1], &cos__, &sin__);
/*  apply that transformation to the right hand side. */
/*<             call fprota(cos,sin,zi,f(irot)) >*/
		fprota_(&cos__, &sin__, &zi, &f[irot]);
/*<             if(i.eq.iband) go to 230 >*/
		if (i__ == iband) {
		    goto L230;
		}
/*  apply that transformation to the left hand side. */
/*<             i2 = 1 >*/
		i2 = 1;
/*<             i3 = i+1 >*/
		i3 = i__ + 1;
/*<             do 210 j=i3,iband >*/
		i__4 = iband;
		for (j = i3; j <= i__4; ++j) {
/*<               i2 = i2+1 >*/
		    ++i2;
/*<               call fprota(cos,sin,h(j),a(irot,i2)) >*/
		    fprota_(&cos__, &sin__, &h__[j], &a[irot + i2 * a_dim1]);
/*<  210        continue >*/
/* L210: */
		}
/*<  220      continue >*/
L220:
		;
	    }
/*  add the contribution of the row to the sum of squares of residual */
/*  right hand sides. */
/*<  230      fp = fp+zi**2 >*/
L230:
/* Computing 2nd power */
	    d__1 = zi;
	    *fp += d__1 * d__1;
/*  find the number of the next data point in the panel. */
/*<  240      in = nummer(in) >*/
/* L240: */
	    in = nummer[in];
/*<           go to 150 >*/
	    goto L150;
/*<  250    continue >*/
L250:
	    ;
	}
/*  find dmax, the maximum value for the diagonal elements in the reduced */
/*  triangle. */
/*<         dmax = 0. >*/
	dmax__ = 0.;
/*<         do 260 i=1,ncof >*/
	i__3 = ncof;
	for (i__ = 1; i__ <= i__3; ++i__) {
/*<           if(a(i,1).le.dmax) go to 260 >*/
	    if (a[i__ + a_dim1] <= dmax__) {
		goto L260;
	    }
/*<           dmax = a(i,1) >*/
	    dmax__ = a[i__ + a_dim1];
/*<  260    continue >*/
L260:
	    ;
	}
/*  check whether the observation matrix is rank deficient. */
/*<         sigma = eps*dmax >*/
	sigma = eps * dmax__;
/*<         do 270 i=1,ncof >*/
	i__3 = ncof;
	for (i__ = 1; i__ <= i__3; ++i__) {
/*<           if(a(i,1).le.sigma) go to 280 >*/
	    if (a[i__ + a_dim1] <= sigma) {
		goto L280;
	    }
/*<  270    continue >*/
/* L270: */
	}
/*  backward substitution in case of full rank. */
/*<         call fpback(a,f,ncof,iband,c,nc) >*/
	fpback_(&a[a_offset], &f[1], &ncof, &iband, &c__[1], nc);
/*<         rank = ncof >*/
	rank = ncof;
/*<         do 275 i=1,ncof >*/
	i__3 = ncof;
	for (i__ = 1; i__ <= i__3; ++i__) {
/*<           q(i,1) = a(i,1)/dmax >*/
	    q[i__ + q_dim1] = a[i__ + a_dim1] / dmax__;
/*<  275    continue >*/
/* L275: */
	}
/*<         go to 300 >*/
	goto L300;
/*  in case of rank deficiency, find the minimum norm solution. */
/*  check whether there is sufficient working space */
/*<  280    lwest = ncof*iband+ncof+iband >*/
L280:
	lwest = ncof * iband + ncof + iband;
/*<         if(lwrk.lt.lwest) go to 780 >*/
	if (*lwrk < lwest) {
	    goto L780;
	}
/*<         do 290 i=1,ncof >*/
	i__3 = ncof;
	for (i__ = 1; i__ <= i__3; ++i__) {
/*<           ff(i) = f(i) >*/
	    ff[i__] = f[i__];
/*<           do 290 j=1,iband >*/
	    i__2 = iband;
	    for (j = 1; j <= i__2; ++j) {
/*<             q(i,j) = a(i,j) >*/
		q[i__ + j * q_dim1] = a[i__ + j * a_dim1];
/*<  290    continue >*/
/* L290: */
	    }
	}
/*<         lf =1 >*/
	lf = 1;
/*<         lh = lf+ncof >*/
	lh = lf + ncof;
/*<         la = lh+iband >*/
	la = lh + iband;
/*<    >*/
	fprank_(&q[q_offset], &ff[1], &ncof, &iband, nc, &sigma, &c__[1], &sq,
		 &rank, &wrk[la], &wrk[lf], &wrk[lh]);
/*<         do 295 i=1,ncof >*/
	i__2 = ncof;
	for (i__ = 1; i__ <= i__2; ++i__) {
/*<           q(i,1) = q(i,1)/dmax >*/
	    q[i__ + q_dim1] /= dmax__;
/*<  295    continue >*/
/* L295: */
	}
/*  add to the sum of squared residuals, the contribution of reducing */
/*  the rank. */
/*<         fp = fp+sq >*/
	*fp += sq;
/*<  300    if(ier.eq.(-2)) fp0 = fp >*/
L300:
	if (*ier == -2) {
	    *fp0 = *fp;
	}
/*  test whether the least-squares spline is an acceptable solution. */
/*<         if(iopt.lt.0) go to 820 >*/
	if (*iopt < 0) {
	    goto L820;
	}
/*<         fpms = fp-s >*/
	fpms = *fp - *s;
/*<         if(abs(fpms).le.acc) if(fp) 815,815,820 >*/
	if (abs(fpms) <= acc) {
	    if (*fp <= 0.) {
		goto L815;
	    } else {
		goto L820;
	    }
	}
/*  test whether we can accept the choice of knots. */
/*<         if(fpms.lt.0.) go to 430 >*/
	if (fpms < 0.) {
	    goto L430;
	}
/*  test whether we cannot further increase the number of knots. */
/*<         if(ncof.gt.m) go to 790 >*/
	if (ncof > *m) {
	    goto L790;
	}
/*<         ier = 0 >*/
	*ier = 0;
/*  search where to add a new knot. */
/*  find for each interval the sum of squared residuals fpint for the */
/*  data points having the coordinate belonging to that knot interval. */
/*  calculate also coord which is the same sum, weighted by the position */
/*  of the data points considered. */
/*<  310    do 320 i=1,nrint >*/
/* L310: */
	i__2 = nrint;
	for (i__ = 1; i__ <= i__2; ++i__) {
/*<           fpint(i) = 0. >*/
	    fpint[i__] = 0.;
/*<           coord(i) = 0. >*/
	    coord[i__] = 0.;
/*<  320    continue >*/
/* L320: */
	}
/*<         do 360 num=1,nreg >*/
	i__2 = nreg;
	for (num = 1; num <= i__2; ++num) {
/*<           num1 = num-1 >*/
	    num1 = num - 1;
/*<           lx = num1/nyy >*/
	    lx = num1 / nyy;
/*<           l1 = lx+1 >*/
	    l1 = lx + 1;
/*<           ly = num1-lx*nyy >*/
	    ly = num1 - lx * nyy;
/*<           l2 = ly+1+nxx >*/
	    l2 = ly + 1 + nxx;
/*<           jrot = lx*nk1y+ly >*/
	    jrot = lx * nk1y + ly;
/*<           in = index(num) >*/
	    in = index[num];
/*<  330      if(in.eq.0) go to 360 >*/
L330:
	    if (in == 0) {
		goto L360;
	    }
/*<           store = 0. >*/
	    store = 0.;
/*<           i1 = jrot >*/
	    i1 = jrot;
/*<           do 350 i=1,kx1 >*/
	    i__3 = kx1;
	    for (i__ = 1; i__ <= i__3; ++i__) {
/*<             hxi = spx(in,i) >*/
		hxi = spx[in + i__ * spx_dim1];
/*<             j1 = i1 >*/
		j1 = i1;
/*<             do 340 j=1,ky1 >*/
		i__4 = ky1;
		for (j = 1; j <= i__4; ++j) {
/*<               j1 = j1+1 >*/
		    ++j1;
/*<               store = store+hxi*spy(in,j)*c(j1) >*/
		    store += hxi * spy[in + j * spy_dim1] * c__[j1];
/*<  340        continue >*/
/* L340: */
		}
/*<             i1 = i1+nk1y >*/
		i1 += nk1y;
/*<  350      continue >*/
/* L350: */
	    }
/*<           store = (w(in)*(z(in)-store))**2 >*/
/* Computing 2nd power */
	    d__1 = w[in] * (z__[in] - store);
	    store = d__1 * d__1;
/*<           fpint(l1) = fpint(l1)+store >*/
	    fpint[l1] += store;
/*<           coord(l1) = coord(l1)+store*x(in) >*/
	    coord[l1] += store * x[in];
/*<           fpint(l2) = fpint(l2)+store >*/
	    fpint[l2] += store;
/*<           coord(l2) = coord(l2)+store*y(in) >*/
	    coord[l2] += store * y[in];
/*<           in = nummer(in) >*/
	    in = nummer[in];
/*<           go to 330 >*/
	    goto L330;
/*<  360    continue >*/
L360:
	    ;
	}
/*  find the interval for which fpint is maximal on the condition that */
/*  there still can be added a knot. */
/*<  370    l = 0 >*/
L370:
	l = 0;
/*<         fpmax = 0. >*/
	fpmax = 0.;
/*<         l1 = 1 >*/
	l1 = 1;
/*<         l2 = nrint >*/
	l2 = nrint;
/*<         if(nx.eq.nxe) l1 = nxx+1 >*/
	if (nx == nxe) {
	    l1 = nxx + 1;
	}
/*<         if(ny.eq.nye) l2 = nxx >*/
	if (ny == nye) {
	    l2 = nxx;
	}
/*<         if(l1.gt.l2) go to 810 >*/
	if (l1 > l2) {
	    goto L810;
	}
/*<         do 380 i=l1,l2 >*/
	i__2 = l2;
	for (i__ = l1; i__ <= i__2; ++i__) {
/*<           if(fpmax.ge.fpint(i)) go to 380 >*/
	    if (fpmax >= fpint[i__]) {
		goto L380;
	    }
/*<           l = i >*/
	    l = i__;
/*<           fpmax = fpint(i) >*/
	    fpmax = fpint[i__];
/*<  380    continue >*/
L380:
	    ;
	}
/*  test whether we cannot further increase the number of knots. */
/*<         if(l.eq.0) go to 785 >*/
	if (l == 0) {
	    goto L785;
	}
/*  calculate the position of the new knot. */
/*<         arg = coord(l)/fpint(l) >*/
	arg = coord[l] / fpint[l];
/*  test in what direction the new knot is going to be added. */
/*<         if(l.gt.nxx) go to 400 >*/
	if (l > nxx) {
	    goto L400;
	}
/*  addition in the x-direction. */
/*<         jxy = l+kx1 >*/
	jxy = l + kx1;
/*<         fpint(l) = 0. >*/
	fpint[l] = 0.;
/*<         fac1 = tx(jxy)-arg >*/
	fac1 = tx[jxy] - arg;
/*<         fac2 = arg-tx(jxy-1) >*/
	fac2 = arg - tx[jxy - 1];
/*<         if(fac1.gt.(ten*fac2) .or. fac2.gt.(ten*fac1)) go to 370 >*/
	if (fac1 > ten * fac2 || fac2 > ten * fac1) {
	    goto L370;
	}
/*<         j = nx >*/
	j = nx;
/*<         do 390 i=jxy,nx >*/
	i__2 = nx;
	for (i__ = jxy; i__ <= i__2; ++i__) {
/*<           tx(j+1) = tx(j) >*/
	    tx[j + 1] = tx[j];
/*<           j = j-1 >*/
	    --j;
/*<  390    continue >*/
/* L390: */
	}
/*<         tx(jxy) = arg >*/
	tx[jxy] = arg;
/*<         nx = nx+1 >*/
	++nx;
/*<         go to 420 >*/
	goto L420;
/*  addition in the y-direction. */
/*<  400    jxy = l+ky1-nxx >*/
L400:
	jxy = l + ky1 - nxx;
/*<         fpint(l) = 0. >*/
	fpint[l] = 0.;
/*<         fac1 = ty(jxy)-arg >*/
	fac1 = ty[jxy] - arg;
/*<         fac2 = arg-ty(jxy-1) >*/
	fac2 = arg - ty[jxy - 1];
/*<         if(fac1.gt.(ten*fac2) .or. fac2.gt.(ten*fac1)) go to 370 >*/
	if (fac1 > ten * fac2 || fac2 > ten * fac1) {
	    goto L370;
	}
/*<         j = ny >*/
	j = ny;
/*<         do 410 i=jxy,ny >*/
	i__2 = ny;
	for (i__ = jxy; i__ <= i__2; ++i__) {
/*<           ty(j+1) = ty(j) >*/
	    ty[j + 1] = ty[j];
/*<           j = j-1 >*/
	    --j;
/*<  410    continue >*/
/* L410: */
	}
/*<         ty(jxy) = arg >*/
	ty[jxy] = arg;
/*<         ny = ny+1 >*/
	++ny;
/*  restart the computations with the new set of knots. */
/*<  420  continue >*/
L420:
	;
    }
/*  test whether the least-squares polynomial is a solution of our */
/*  approximation problem. */
/*<  430  if(ier.eq.(-2)) go to 830 >*/
L430:
    if (*ier == -2) {
	goto L830;
    }
/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
/* part 2: determination of the smoothing spline sp(x,y)                c */
/* *****************************************************                c */
/* we have determined the number of knots and their position. we now    c */
/* compute the b-spline coefficients of the smoothing spline sp(x,y).   c */
/* the observation matrix a is extended by the rows of a matrix,        c */
/* expressing that sp(x,y) must be a polynomial of degree kx in x and   c */
/* ky in y. the corresponding weights of these additional rows are set  c */
/* to 1./p.  iteratively we than have to determine the value of p       c */
/* such that f(p)=sum((w(i)*(z(i)-sp(x(i),y(i))))**2) be = s.           c */
/* we already know that the least-squares polynomial corresponds to     c */
/* p=0  and that the least-squares spline corresponds to p=infinity.    c */
/* the iteration process which is proposed here makes use of rational   c */
/* interpolation. since f(p) is a convex and strictly decreasing        c */
/* function of p, it can be approximated by a rational function r(p)=   c */
/* (u*p+v)/(p+w). three values of p(p1,p2,p3) with corresponding values c */
/* of f(p) (f1=f(p1)-s,f2=f(p2)-s,f3=f(p3)-s) are used to calculate the c */
/* new value of p such that r(p)=s. convergence is guaranteed by taking c */
/* f1 > 0 and f3 < 0.                                                   c */
/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
/*<       kx2 = kx1+1 >*/
    kx2 = kx1 + 1;
/*  test whether there are interior knots in the x-direction. */
/*<       if(nk1x.eq.kx1) go to 440 >*/
    if (nk1x == kx1) {
	goto L440;
    }
/*  evaluate the discotinuity jumps of the kx-th order derivative of */
/*  the b-splines at the knots tx(l),l=kx+2,...,nx-kx-1. */
/*<       call fpdisc(tx,nx,kx2,bx,nmax) >*/
    fpdisc_(&tx[1], &nx, &kx2, &bx[bx_offset], nmax);
/*<  440  ky2 = ky1 + 1 >*/
L440:
    ky2 = ky1 + 1;
/*  test whether there are interior knots in the y-direction. */
/*<       if(nk1y.eq.ky1) go to 450 >*/
    if (nk1y == ky1) {
	goto L450;
    }
/*  evaluate the discontinuity jumps of the ky-th order derivative of */
/*  the b-splines at the knots ty(l),l=ky+2,...,ny-ky-1. */
/*<       call fpdisc(ty,ny,ky2,by,nmax) >*/
    fpdisc_(&ty[1], &ny, &ky2, &by[by_offset], nmax);
/*  initial value for p. */
/*<  450  p1 = 0. >*/
L450:
    p1 = 0.;
/*<       f1 = fp0-s >*/
    f1 = *fp0 - *s;
/*<       p3 = -one >*/
    p3 = -one;
/*<       f3 = fpms >*/
    f3 = fpms;
/*<       p = 0. >*/
    p = 0.;
/*<       do 460 i=1,ncof >*/
    i__1 = ncof;
    for (i__ = 1; i__ <= i__1; ++i__) {
/*<         p = p+a(i,1) >*/
	p += a[i__ + a_dim1];
/*<  460  continue >*/
/* L460: */
    }
/*<       rn = ncof >*/
    rn = (doublereal) ncof;
/*<       p = rn/p >*/
    p = rn / p;
/*  find the bandwidth of the extended observation matrix. */
/*<       iband3 = kx1*nk1y >*/
    iband3 = kx1 * nk1y;
/*<       iband4 = iband3 +1 >*/
    iband4 = iband3 + 1;
/*<       ich1 = 0 >*/
    ich1 = 0;
/*<       ich3 = 0 >*/
    ich3 = 0;
/*  iteration process to find the root of f(p)=s. */
/*<       do 770 iter=1,maxit >*/
    i__1 = *maxit;
    for (iter = 1; iter <= i__1; ++iter) {
/*<         pinv = one/p >*/
	pinv = one / p;
/*  store the triangularized observation matrix into q. */
/*<         do 480 i=1,ncof >*/
	i__2 = ncof;
	for (i__ = 1; i__ <= i__2; ++i__) {
/*<           ff(i) = f(i) >*/
	    ff[i__] = f[i__];
/*<           do 470 j=1,iband >*/
	    i__3 = iband;
	    for (j = 1; j <= i__3; ++j) {
/*<             q(i,j) = a(i,j) >*/
		q[i__ + j * q_dim1] = a[i__ + j * a_dim1];
/*<  470      continue >*/
/* L470: */
	    }
/*<           ibb = iband+1 >*/
	    ibb = iband + 1;
/*<           do 480 j=ibb,iband4 >*/
	    i__3 = iband4;
	    for (j = ibb; j <= i__3; ++j) {
/*<             q(i,j) = 0. >*/
		q[i__ + j * q_dim1] = 0.;
/*<  480    continue >*/
/* L480: */
	    }
	}
/*<         if(nk1y.eq.ky1) go to 560 >*/
	if (nk1y == ky1) {
	    goto L560;
	}
/*  extend the observation matrix with the rows of a matrix, expressing */
/*  that for x=cst. sp(x,y) must be a polynomial in y of degree ky. */
/*<         do 550 i=ky2,nk1y >*/
	i__3 = nk1y;
	for (i__ = ky2; i__ <= i__3; ++i__) {
/*<           ii = i-ky1 >*/
	    ii = i__ - ky1;
/*<           do 550 j=1,nk1x >*/
	    i__2 = nk1x;
	    for (j = 1; j <= i__2; ++j) {
/*  initialize the new row. */
/*<             do 490 l=1,iband >*/
		i__4 = iband;
		for (l = 1; l <= i__4; ++l) {
/*<               h(l) = 0. >*/
		    h__[l] = 0.;
/*<  490        continue >*/
/* L490: */
		}
/*  fill in the non-zero elements of the row. jrot records the column */
/*  number of the first non-zero element in the row. */
/*<             do 500 l=1,ky2 >*/
		i__4 = ky2;
		for (l = 1; l <= i__4; ++l) {
/*<               h(l) = by(ii,l)*pinv >*/
		    h__[l] = by[ii + l * by_dim1] * pinv;
/*<  500        continue >*/
/* L500: */
		}
/*<             zi = 0. >*/
		zi = 0.;
/*<             jrot = (j-1)*nk1y+ii >*/
		jrot = (j - 1) * nk1y + ii;
/*  rotate the new row into triangle by givens transformations without */
/*  square roots. */
/*<             do 540 irot=jrot,ncof >*/
		i__4 = ncof;
		for (irot = jrot; irot <= i__4; ++irot) {
/*<               piv = h(1) >*/
		    piv = h__[1];
/*<               i2 = min0(iband1,ncof-irot) >*/
/* Computing MIN */
		    i__5 = iband1, i__6 = ncof - irot;
		    i2 = min(i__5,i__6);
/*<               if(piv.eq.0.) if(i2) 550,550,520 >*/
		    if (piv == 0.) {
			if (i2 <= 0) {
			    goto L550;
			} else {
			    goto L520;
			}
		    }
/*  calculate the parameters of the givens transformation. */
/*<               call fpgivs(piv,q(irot,1),cos,sin) >*/
		    fpgivs_(&piv, &q[irot + q_dim1], &cos__, &sin__);
/*  apply that givens transformation to the right hand side. */
/*<               call fprota(cos,sin,zi,ff(irot)) >*/
		    fprota_(&cos__, &sin__, &zi, &ff[irot]);
/*<               if(i2.eq.0) go to 550 >*/
		    if (i2 == 0) {
			goto L550;
		    }
/*  apply that givens transformation to the left hand side. */
/*<               do 510 l=1,i2 >*/
		    i__5 = i2;
		    for (l = 1; l <= i__5; ++l) {
/*<                 l1 = l+1 >*/
			l1 = l + 1;
/*<                 call fprota(cos,sin,h(l1),q(irot,l1)) >*/
			fprota_(&cos__, &sin__, &h__[l1], &q[irot + l1 * 
				q_dim1]);
/*<  510          continue >*/
/* L510: */
		    }
/*<  520          do 530 l=1,i2 >*/
L520:
		    i__5 = i2;
		    for (l = 1; l <= i__5; ++l) {
/*<                 h(l) = h(l+1) >*/
			h__[l] = h__[l + 1];
/*<  530          continue >*/
/* L530: */
		    }
/*<               h(i2+1) = 0. >*/
		    h__[i2 + 1] = 0.;
/*<  540        continue >*/
/* L540: */
		}
/*<  550    continue >*/
L550:
		;
	    }
	}
/*<  560    if(nk1x.eq.kx1) go to 640 >*/
L560:
	if (nk1x == kx1) {
	    goto L640;
	}
/*  extend the observation matrix with the rows of a matrix expressing */
/*  that for y=cst. sp(x,y) must be a polynomial in x of degree kx. */
/*<         do 630 i=kx2,nk1x >*/
	i__2 = nk1x;
	for (i__ = kx2; i__ <= i__2; ++i__) {
/*<           ii = i-kx1 >*/
	    ii = i__ - kx1;
/*<           do 630 j=1,nk1y >*/
	    i__3 = nk1y;
	    for (j = 1; j <= i__3; ++j) {
/*  initialize the new row */
/*<             do 570 l=1,iband4 >*/
		i__4 = iband4;
		for (l = 1; l <= i__4; ++l) {
/*<               h(l) = 0. >*/
		    h__[l] = 0.;
/*<  570        continue >*/
/* L570: */
		}
/*  fill in the non-zero elements of the row. jrot records the column */
/*  number of the first non-zero element in the row. */
/*<             j1 = 1 >*/
		j1 = 1;
/*<             do 580 l=1,kx2 >*/
		i__4 = kx2;
		for (l = 1; l <= i__4; ++l) {
/*<               h(j1) = bx(ii,l)*pinv >*/
		    h__[j1] = bx[ii + l * bx_dim1] * pinv;
/*<               j1 = j1+nk1y >*/
		    j1 += nk1y;
/*<  580        continue >*/
/* L580: */
		}
/*<             zi = 0. >*/
		zi = 0.;
/*<             jrot = (i-kx2)*nk1y+j >*/
		jrot = (i__ - kx2) * nk1y + j;
/*  rotate the new row into triangle by givens transformations . */
/*<             do 620 irot=jrot,ncof >*/
		i__4 = ncof;
		for (irot = jrot; irot <= i__4; ++irot) {
/*<               piv = h(1) >*/
		    piv = h__[1];
/*<               i2 = min0(iband3,ncof-irot) >*/
/* Computing MIN */
		    i__5 = iband3, i__6 = ncof - irot;
		    i2 = min(i__5,i__6);
/*<               if(piv.eq.0.) if(i2) 630,630,600 >*/
		    if (piv == 0.) {
			if (i2 <= 0) {
			    goto L630;
			} else {
			    goto L600;
			}
		    }
/*  calculate the parameters of the givens transformation. */
/*<               call fpgivs(piv,q(irot,1),cos,sin) >*/
		    fpgivs_(&piv, &q[irot + q_dim1], &cos__, &sin__);
/*  apply that givens transformation to the right hand side. */
/*<               call fprota(cos,sin,zi,ff(irot)) >*/
		    fprota_(&cos__, &sin__, &zi, &ff[irot]);
/*<               if(i2.eq.0) go to 630 >*/
		    if (i2 == 0) {
			goto L630;
		    }
/*  apply that givens transformation to the left hand side. */
/*<               do 590 l=1,i2 >*/
		    i__5 = i2;
		    for (l = 1; l <= i__5; ++l) {
/*<                 l1 = l+1 >*/
			l1 = l + 1;
/*<                 call fprota(cos,sin,h(l1),q(irot,l1)) >*/
			fprota_(&cos__, &sin__, &h__[l1], &q[irot + l1 * 
				q_dim1]);
/*<  590          continue >*/
/* L590: */
		    }
/*<  600          do 610 l=1,i2 >*/
L600:
		    i__5 = i2;
		    for (l = 1; l <= i__5; ++l) {
/*<                 h(l) = h(l+1) >*/
			h__[l] = h__[l + 1];
/*<  610          continue >*/
/* L610: */
		    }
/*<               h(i2+1) = 0. >*/
		    h__[i2 + 1] = 0.;
/*<  620        continue >*/
/* L620: */
		}
/*<  630    continue >*/
L630:
		;
	    }
	}
/*  find dmax, the maximum value for the diagonal elements in the */
/*  reduced triangle. */
/*<  640    dmax = 0. >*/
L640:
	dmax__ = 0.;
/*<         do 650 i=1,ncof >*/
	i__3 = ncof;
	for (i__ = 1; i__ <= i__3; ++i__) {
/*<           if(q(i,1).le.dmax) go to 650 >*/
	    if (q[i__ + q_dim1] <= dmax__) {
		goto L650;
	    }
/*<           dmax = q(i,1) >*/
	    dmax__ = q[i__ + q_dim1];
/*<  650    continue >*/
L650:
	    ;
	}
/*  check whether the matrix is rank deficient. */
/*<         sigma = eps*dmax >*/
	sigma = eps * dmax__;
/*<         do 660 i=1,ncof >*/
	i__3 = ncof;
	for (i__ = 1; i__ <= i__3; ++i__) {
/*<           if(q(i,1).le.sigma) go to 670 >*/
	    if (q[i__ + q_dim1] <= sigma) {
		goto L670;
	    }
/*<  660    continue >*/
/* L660: */
	}
/*  backward substitution in case of full rank. */
/*<         call fpback(q,ff,ncof,iband4,c,nc) >*/
	fpback_(&q[q_offset], &ff[1], &ncof, &iband4, &c__[1], nc);
/*<         rank = ncof >*/
	rank = ncof;
/*<         go to 675 >*/
	goto L675;
/*  in case of rank deficiency, find the minimum norm solution. */
/*<  670    lwest = ncof*iband4+ncof+iband4 >*/
L670:
	lwest = ncof * iband4 + ncof + iband4;
/*<         if(lwrk.lt.lwest) go to 780 >*/
	if (*lwrk < lwest) {
	    goto L780;
	}
/*<         lf = 1 >*/
	lf = 1;
/*<         lh = lf+ncof >*/
	lh = lf + ncof;
/*<         la = lh+iband4 >*/
	la = lh + iband4;
/*<    >*/
	fprank_(&q[q_offset], &ff[1], &ncof, &iband4, nc, &sigma, &c__[1], &
		sq, &rank, &wrk[la], &wrk[lf], &wrk[lh]);
/*<  675    do 680 i=1,ncof >*/
L675:
	i__3 = ncof;
	for (i__ = 1; i__ <= i__3; ++i__) {
/*<           q(i,1) = q(i,1)/dmax >*/
	    q[i__ + q_dim1] /= dmax__;
/*<  680    continue >*/
/* L680: */
	}
/*  compute f(p). */
/*<         fp = 0. >*/
	*fp = 0.;
/*<         do 720 num = 1,nreg >*/
	i__3 = nreg;
	for (num = 1; num <= i__3; ++num) {
/*<           num1 = num-1 >*/
	    num1 = num - 1;
/*<           lx = num1/nyy >*/
	    lx = num1 / nyy;
/*<           ly = num1-lx*nyy >*/
	    ly = num1 - lx * nyy;
/*<           jrot = lx*nk1y+ly >*/
	    jrot = lx * nk1y + ly;
/*<           in = index(num) >*/
	    in = index[num];
/*<  690      if(in.eq.0) go to 720 >*/
L690:
	    if (in == 0) {
		goto L720;
	    }
/*<           store = 0. >*/
	    store = 0.;
/*<           i1 = jrot >*/
	    i1 = jrot;
/*<           do 710 i=1,kx1 >*/
	    i__2 = kx1;
	    for (i__ = 1; i__ <= i__2; ++i__) {
/*<             hxi = spx(in,i) >*/
		hxi = spx[in + i__ * spx_dim1];
/*<             j1 = i1 >*/
		j1 = i1;
/*<             do 700 j=1,ky1 >*/
		i__4 = ky1;
		for (j = 1; j <= i__4; ++j) {
/*<               j1 = j1+1 >*/
		    ++j1;
/*<               store = store+hxi*spy(in,j)*c(j1) >*/
		    store += hxi * spy[in + j * spy_dim1] * c__[j1];
/*<  700        continue >*/
/* L700: */
		}
/*<             i1 = i1+nk1y >*/
		i1 += nk1y;
/*<  710      continue >*/
/* L710: */
	    }
/*<           fp = fp+(w(in)*(z(in)-store))**2 >*/
/* Computing 2nd power */
	    d__1 = w[in] * (z__[in] - store);
	    *fp += d__1 * d__1;
/*<           in = nummer(in) >*/
	    in = nummer[in];
/*<           go to 690 >*/
	    goto L690;
/*<  720    continue >*/
L720:
	    ;
	}
/*  test whether the approximation sp(x,y) is an acceptable solution. */
/*<         fpms = fp-s >*/
	fpms = *fp - *s;
/*<         if(abs(fpms).le.acc) go to 820 >*/
	if (abs(fpms) <= acc) {
	    goto L820;
	}
/*  test whether the maximum allowable number of iterations has been */
/*  reached. */
/*<         if(iter.eq.maxit) go to 795 >*/
	if (iter == *maxit) {
	    goto L795;
	}
/*  carry out one more step of the iteration process. */
/*<         p2 = p >*/
	p2 = p;
/*<         f2 = fpms >*/
	f2 = fpms;
/*<         if(ich3.ne.0) go to 740 >*/
	if (ich3 != 0) {
	    goto L740;
	}
/*<         if((f2-f3).gt.acc) go to 730 >*/
	if (f2 - f3 > acc) {
	    goto L730;
	}
/*  our initial choice of p is too large. */
/*<         p3 = p2 >*/
	p3 = p2;
/*<         f3 = f2 >*/
	f3 = f2;
/*<         p = p*con4 >*/
	p *= con4;
/*<         if(p.le.p1) p = p1*con9 + p2*con1 >*/
	if (p <= p1) {
	    p = p1 * con9 + p2 * con1;
	}
/*<         go to 770 >*/
	goto L770;
/*<  730    if(f2.lt.0.) ich3 = 1 >*/
L730:
	if (f2 < 0.) {
	    ich3 = 1;
	}
/*<  740    if(ich1.ne.0) go to 760 >*/
L740:
	if (ich1 != 0) {
	    goto L760;
	}
/*<         if((f1-f2).gt.acc) go to 750 >*/
	if (f1 - f2 > acc) {
	    goto L750;
	}
/*  our initial choice of p is too small */
/*<         p1 = p2 >*/
	p1 = p2;
/*<         f1 = f2 >*/
	f1 = f2;
/*<         p = p/con4 >*/
	p /= con4;
/*<         if(p3.lt.0.) go to 770 >*/
	if (p3 < 0.) {
	    goto L770;
	}
/*<         if(p.ge.p3) p = p2*con1 + p3*con9 >*/
	if (p >= p3) {
	    p = p2 * con1 + p3 * con9;
	}
/*<         go to 770 >*/
	goto L770;
/*<  750    if(f2.gt.0.) ich1 = 1 >*/
L750:
	if (f2 > 0.) {
	    ich1 = 1;
	}
/*  test whether the iteration process proceeds as theoretically */
/*  expected. */
/*<  760    if(f2.ge.f1 .or. f2.le.f3) go to 800 >*/
L760:
	if (f2 >= f1 || f2 <= f3) {
	    goto L800;
	}
/*  find the new value of p. */
/*<         p = fprati(p1,f1,p2,f2,p3,f3) >*/
	p = fprati_(&p1, &f1, &p2, &f2, &p3, &f3);
/*<  770  continue >*/
L770:
	;
    }
/*  error codes and messages. */
/*<  780  ier = lwest >*/
L780:
    *ier = lwest;
/*<       go to 830 >*/
    goto L830;
/*<  785  ier = 5 >*/
L785:
    *ier = 5;
/*<       go to 830 >*/
    goto L830;
/*<  790  ier = 4 >*/
L790:
    *ier = 4;
/*<       go to 830 >*/
    goto L830;
/*<  795  ier = 3 >*/
L795:
    *ier = 3;
/*<       go to 830 >*/
    goto L830;
/*<  800  ier = 2 >*/
L800:
    *ier = 2;
/*<       go to 830 >*/
    goto L830;
/*<  810  ier = 1 >*/
L810:
    *ier = 1;
/*<       go to 830 >*/
    goto L830;
/*<  815  ier = -1 >*/
L815:
    *ier = -1;
/*<       fp = 0. >*/
    *fp = 0.;
/*<  820  if(ncof.ne.rank) ier = -rank >*/
L820:
    if (ncof != rank) {
	*ier = -rank;
    }
/*  test whether x and y are in the original order. */
/*<  830  if(ichang.lt.0) go to 930 >*/
L830:
    if (ichang < 0) {
	goto L930;
    }
/*  if not, interchange x and y once more. */
/*<       l1 = 1 >*/
    l1 = 1;
/*<       do 840 i=1,nk1x >*/
    i__1 = nk1x;
    for (i__ = 1; i__ <= i__1; ++i__) {
/*<         l2 = i >*/
	l2 = i__;
/*<         do 840 j=1,nk1y >*/
	i__3 = nk1y;
	for (j = 1; j <= i__3; ++j) {
/*<           f(l2) = c(l1) >*/
	    f[l2] = c__[l1];
/*<           l1 = l1+1 >*/
	    ++l1;
/*<           l2 = l2+nk1x >*/
	    l2 += nk1x;
/*<  840  continue >*/
/* L840: */
	}
    }
/*<       do 850 i=1,ncof >*/
    i__3 = ncof;
    for (i__ = 1; i__ <= i__3; ++i__) {
/*<         c(i) = f(i) >*/
	c__[i__] = f[i__];
/*<  850  continue >*/
/* L850: */
    }
/*<       do 860 i=1,m >*/
    i__3 = *m;
    for (i__ = 1; i__ <= i__3; ++i__) {
/*<         store = x(i) >*/
	store = x[i__];
/*<         x(i) = y(i) >*/
	x[i__] = y[i__];
/*<         y(i) = store >*/
	y[i__] = store;
/*<  860  continue >*/
/* L860: */
    }
/*<       n = min0(nx,ny) >*/
    n = min(nx,ny);
/*<       do 870 i=1,n >*/
    i__3 = n;
    for (i__ = 1; i__ <= i__3; ++i__) {
/*<         store = tx(i) >*/
	store = tx[i__];
/*<         tx(i) = ty(i) >*/
	tx[i__] = ty[i__];
/*<         ty(i) = store >*/
	ty[i__] = store;
/*<  870  continue >*/
/* L870: */
    }
/*<       n1 = n+1 >*/
    n1 = n + 1;
/*<       if(nx-ny) 880,920,900 >*/
    if ((i__3 = nx - ny) < 0) {
	goto L880;
    } else if (i__3 == 0) {
	goto L920;
    } else {
	goto L900;
    }
/*<  880  do 890 i=n1,ny >*/
L880:
    i__3 = ny;
    for (i__ = n1; i__ <= i__3; ++i__) {
/*<         tx(i) = ty(i) >*/
	tx[i__] = ty[i__];
/*<  890  continue >*/
/* L890: */
    }
/*<       go to 920 >*/
    goto L920;
/*<  900  do 910 i=n1,nx >*/
L900:
    i__3 = nx;
    for (i__ = n1; i__ <= i__3; ++i__) {
/*<         ty(i) = tx(i) >*/
	ty[i__] = tx[i__];
/*<  910  continue >*/
/* L910: */
    }
/*<  920  l = nx >*/
L920:
    l = nx;
/*<       nx = ny >*/
    nx = ny;
/*<       ny = l >*/
    ny = l;
/*<  930  if(iopt.lt.0) go to 940 >*/
L930:
    if (*iopt < 0) {
	goto L940;
    }
/*<       nx0 = nx >*/
    *nx0 = nx;
/*<       ny0 = ny >*/
    *ny0 = ny;
/*<  940  return >*/
L940:
    return 0;
/*<       end >*/
} /* fpsurf_ */

