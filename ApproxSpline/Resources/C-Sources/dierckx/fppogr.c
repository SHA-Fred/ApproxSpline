/* fppogr.f -- translated by f2c (version 20061008).
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

/* Table of constant values */

static integer c__1 = 1;

/*<    >*/
/* Subroutine */ int fppogr_(integer *iopt, integer *ider, doublereal *u, 
	integer *mu, doublereal *v, integer *mv, doublereal *z__, integer *mz,
	 doublereal *z0, doublereal *r__, doublereal *s, integer *nuest, 
	integer *nvest, doublereal *tol, integer *maxit, integer *nc, integer 
	*nu, doublereal *tu, integer *nv, doublereal *tv, doublereal *c__, 
	doublereal *fp, doublereal *fp0, doublereal *fpold, doublereal *
	reducu, doublereal *reducv, doublereal *fpintu, doublereal *fpintv, 
	doublereal *dz, doublereal *step, integer *lastdi, integer *nplusu, 
	integer *nplusv, integer *lasttu, integer *nru, integer *nrv, integer 
	*nrdatu, integer *nrdatv, doublereal *wrk, integer *lwrk, integer *
	ier)
{
    /* System generated locals */
    integer i__1, i__2, i__3, i__4, i__5;
    doublereal d__1;

    /* Builtin functions */
    double atan2(doublereal, doublereal);

    /* Local variables */
    static integer i__, j, l;
    static doublereal p, f1, f2, f3;
    static integer i1, i2, l1, l2, l3, l4;
    static doublereal p1, p2, p3, vb, pi, ve;
    static integer nn, ju;
    static doublereal rn;
    static integer mu0, mu1;
    static doublereal acc;
    static integer idd[2];
    static doublereal one, per;
    static integer nue, nve, mpm, ktu;
    static doublereal dzz[3];
    static integer ich1, ich3;
    static doublereal con1, con4, con9;
    static integer npl1, ifbu, ifbv, iter;
    static doublereal fpms;
    static integer ifsu, ifsv;
    static doublereal zmin;
    static integer nplu;
    static doublereal zmax;
    static integer nplv, mumin, numax, nvmax;
    extern /* Subroutine */ int fpopdi_(integer *, integer *, integer *, 
	    integer *, doublereal *, integer *, doublereal *, integer *, 
	    doublereal *, integer *, doublereal *, doublereal *, integer *, 
	    integer *, doublereal *, integer *, doublereal *, integer *, 
	    integer *, integer *, doublereal *, doublereal *, doublereal *, 
	    integer *, doublereal *, doublereal *, doublereal *, integer *, 
	    integer *, doublereal *, integer *);
    extern doublereal fprati_(doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);
    extern /* Subroutine */ int fpknot_(doublereal *, integer *, doublereal *,
	     integer *, doublereal *, integer *, integer *, integer *, 
	    integer *);
    static integer istart, nrintu, nrintv;

/*  .. */
/*  ..scalar arguments.. */
/*<    >*/
/*<       real z0,r,s,tol,fp,fp0,fpold,reducu,reducv,step >*/
/*  ..array arguments.. */
/*<    >*/
/*<    >*/
/*  ..local scalars.. */
/*<    >*/
/*<    >*/
/*  ..local arrays.. */
/*<       integer idd(2) >*/
/*<       real dzz(3) >*/
/*  ..function references.. */
/*<       real abs,atan2,fprati >*/
/*<       integer max0,min0 >*/
/*  ..subroutine references.. */
/*    fpknot,fpopdi */
/*  .. */
/*   set constants */
/*<       one = 1 >*/
    /* Parameter adjustments */
    --iopt;
    --ider;
    --nru;
    --u;
    --nrv;
    --v;
    --z__;
    --nrdatu;
    --fpintu;
    --tu;
    --nrdatv;
    --fpintv;
    --tv;
    --c__;
    --dz;
    --wrk;

    /* Function Body */
    one = 1.;
/*<       con1 = 0.1e0 >*/
    con1 = .1;
/*<       con9 = 0.9e0 >*/
    con9 = .9;
/*<       con4 = 0.4e-01 >*/
    con4 = .04;
/*   initialization */
/*<       ifsu = 0 >*/
    ifsu = 0;
/*<       ifsv = 0 >*/
    ifsv = 0;
/*<       ifbu = 0 >*/
    ifbu = 0;
/*<       ifbv = 0 >*/
    ifbv = 0;
/*<       p = -one >*/
    p = -one;
/*<       mumin = 4-iopt(3) >*/
    mumin = 4 - iopt[3];
/*<       if(ider(1).ge.0) mumin = mumin-1 >*/
    if (ider[1] >= 0) {
	--mumin;
    }
/*<       if(iopt(2).eq.1 .and. ider(2).eq.1) mumin = mumin-1 >*/
    if (iopt[2] == 1 && ider[2] == 1) {
	--mumin;
    }
/*<       pi = atan2(0.,-one) >*/
    pi = atan2(0., -one);
/*<       per = pi+pi >*/
    per = pi + pi;
/*<       vb = v(1) >*/
    vb = v[1];
/*<       ve = vb+per >*/
    ve = vb + per;
/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
/* part 1: determination of the number of knots and their position.     c */
/* ****************************************************************     c */
/*  given a set of knots we compute the least-squares spline sinf(u,v)  c */
/*  and the corresponding sum of squared residuals fp = f(p=inf).       c */
/*  if iopt(1)=-1  sinf(u,v) is the requested approximation.            c */
/*  if iopt(1)>=0  we check whether we can accept the knots:            c */
/*    if fp <= s we will continue with the current set of knots.        c */
/*    if fp >  s we will increase the number of knots and compute the   c */
/*       corresponding least-squares spline until finally fp <= s.      c */
/*    the initial choice of knots depends on the value of s and iopt.   c */
/*    if s=0 we have spline interpolation; in that case the number of   c */
/*     knots in the u-direction equals nu=numax=mu+5+iopt(2)+iopt(3)    c */
/*     and in the v-direction nv=nvmax=mv+7.                            c */
/*    if s>0 and                                                        c */
/*      iopt(1)=0 we first compute the least-squares polynomial,i.e. a  c */
/*       spline without interior knots : nu=8 ; nv=8.                   c */
/*      iopt(1)=1 we start with the set of knots found at the last call c */
/*       of the routine, except for the case that s > fp0; then we      c */
/*       compute the least-squares polynomial directly.                 c */
/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
/*<       if(iopt(1).lt.0) go to 120 >*/
    if (iopt[1] < 0) {
	goto L120;
    }
/*  acc denotes the absolute tolerance for the root of f(p)=s. */
/*<       acc = tol*s >*/
    acc = *tol * *s;
/*  numax and nvmax denote the number of knots needed for interpolation. */
/*<       numax = mu+5+iopt(2)+iopt(3) >*/
    numax = *mu + 5 + iopt[2] + iopt[3];
/*<       nvmax = mv+7 >*/
    nvmax = *mv + 7;
/*<       nue = min0(numax,nuest) >*/
    nue = min(numax,*nuest);
/*<       nve = min0(nvmax,nvest) >*/
    nve = min(nvmax,*nvest);
/*<       if(s.gt.0.) go to 100 >*/
    if (*s > 0.) {
	goto L100;
    }
/*  if s = 0, s(u,v) is an interpolating spline. */
/*<       nu = numax >*/
    *nu = numax;
/*<       nv = nvmax >*/
    *nv = nvmax;
/*  test whether the required storage space exceeds the available one. */
/*<       if(nu.gt.nuest .or. nv.gt.nvest) go to 420 >*/
    if (*nu > *nuest || *nv > *nvest) {
	goto L420;
    }
/*  find the position of the knots in the v-direction. */
/*<       do 10 l=1,mv >*/
    i__1 = *mv;
    for (l = 1; l <= i__1; ++l) {
/*<         tv(l+3) = v(l) >*/
	tv[l + 3] = v[l];
/*<   10  continue >*/
/* L10: */
    }
/*<       tv(mv+4) = ve >*/
    tv[*mv + 4] = ve;
/*<       l1 = mv-2 >*/
    l1 = *mv - 2;
/*<       l2 = mv+5 >*/
    l2 = *mv + 5;
/*<       do 20 i=1,3 >*/
    for (i__ = 1; i__ <= 3; ++i__) {
/*<          tv(i) = v(l1)-per >*/
	tv[i__] = v[l1] - per;
/*<          tv(l2) = v(i+1)+per >*/
	tv[l2] = v[i__ + 1] + per;
/*<          l1 = l1+1 >*/
	++l1;
/*<          l2 = l2+1 >*/
	++l2;
/*<   20  continue >*/
/* L20: */
    }
/*  if not all the derivative values g(i,j) are given, we will first */
/*  estimate these values by computing a least-squares spline */
/*<       idd(1) = ider(1) >*/
    idd[0] = ider[1];
/*<       if(idd(1).eq.0) idd(1) = 1 >*/
    if (idd[0] == 0) {
	idd[0] = 1;
    }
/*<       if(idd(1).gt.0) dz(1) = z0 >*/
    if (idd[0] > 0) {
	dz[1] = *z0;
    }
/*<       idd(2) = ider(2) >*/
    idd[1] = ider[2];
/*<       if(ider(1).lt.0) go to 30 >*/
    if (ider[1] < 0) {
	goto L30;
    }
/*<       if(iopt(2).eq.0 .or. ider(2).ne.0) go to 70 >*/
    if (iopt[2] == 0 || ider[2] != 0) {
	goto L70;
    }
/* we set up the knots in the u-direction for computing the least-squares */
/* spline. */
/*<   30  i1 = 3 >*/
L30:
    i1 = 3;
/*<       i2 = mu-2 >*/
    i2 = *mu - 2;
/*<       nu = 4 >*/
    *nu = 4;
/*<       do 40 i=1,mu >*/
    i__1 = *mu;
    for (i__ = 1; i__ <= i__1; ++i__) {
/*<          if(i1.gt.i2) go to 50 >*/
	if (i1 > i2) {
	    goto L50;
	}
/*<          nu = nu+1 >*/
	++(*nu);
/*<          tu(nu) = u(i1) >*/
	tu[*nu] = u[i1];
/*<          i1 = i1+2 >*/
	i1 += 2;
/*<   40  continue >*/
/* L40: */
    }
/*<   50  do 60 i=1,4 >*/
L50:
    for (i__ = 1; i__ <= 4; ++i__) {
/*<          tu(i) = 0. >*/
	tu[i__] = 0.;
/*<          nu = nu+1 >*/
	++(*nu);
/*<          tu(nu) = r >*/
	tu[*nu] = *r__;
/*<   60  continue >*/
/* L60: */
    }
/* we compute the least-squares spline for estimating the derivatives. */
/*<    >*/
    fpopdi_(&ifsu, &ifsv, &ifbu, &ifbv, &u[1], mu, &v[1], mv, &z__[1], mz, z0,
	     &dz[1], &iopt[1], idd, &tu[1], nu, &tv[1], nv, nuest, nvest, &p, 
	    step, &c__[1], nc, fp, &fpintu[1], &fpintv[1], &nru[1], &nrv[1], &
	    wrk[1], lwrk);
/*<       ifsu = 0 >*/
    ifsu = 0;
/* if all the derivatives at the origin are known, we compute the */
/* interpolating spline. */
/* we set up the knots in the u-direction, needed for interpolation. */
/*<   70  nn = numax-8 >*/
L70:
    nn = numax - 8;
/*<       if(nn.eq.0) go to 95 >*/
    if (nn == 0) {
	goto L95;
    }
/*<       ju = 2-iopt(2) >*/
    ju = 2 - iopt[2];
/*<       do 80 l=1,nn >*/
    i__1 = nn;
    for (l = 1; l <= i__1; ++l) {
/*<         tu(l+4) = u(ju) >*/
	tu[l + 4] = u[ju];
/*<         ju = ju+1 >*/
	++ju;
/*<   80  continue >*/
/* L80: */
    }
/*<       nu = numax >*/
    *nu = numax;
/*<       l = nu >*/
    l = *nu;
/*<       do 90 i=1,4 >*/
    for (i__ = 1; i__ <= 4; ++i__) {
/*<          tu(i) = 0. >*/
	tu[i__] = 0.;
/*<          tu(l) = r >*/
	tu[l] = *r__;
/*<          l = l-1 >*/
	--l;
/*<   90  continue >*/
/* L90: */
    }
/* we compute the interpolating spline. */
/*<    >*/
L95:
    fpopdi_(&ifsu, &ifsv, &ifbu, &ifbv, &u[1], mu, &v[1], mv, &z__[1], mz, z0,
	     &dz[1], &iopt[1], idd, &tu[1], nu, &tv[1], nv, nuest, nvest, &p, 
	    step, &c__[1], nc, fp, &fpintu[1], &fpintv[1], &nru[1], &nrv[1], &
	    wrk[1], lwrk);
/*<       go to 430 >*/
    goto L430;
/*  if s>0 our initial choice of knots depends on the value of iopt(1). */
/*<  100  ier = 0 >*/
L100:
    *ier = 0;
/*<       if(iopt(1).eq.0) go to 115 >*/
    if (iopt[1] == 0) {
	goto L115;
    }
/*<       step = -step >*/
    *step = -(*step);
/*<       if(fp0.le.s) go to 115 >*/
    if (*fp0 <= *s) {
	goto L115;
    }
/*  if iopt(1)=1 and fp0 > s we start computing the least-squares spline */
/*  according to the set of knots found at the last call of the routine. */
/*  we determine the number of grid coordinates u(i) inside each knot */
/*  interval (tu(l),tu(l+1)). */
/*<       l = 5 >*/
    l = 5;
/*<       j = 1 >*/
    j = 1;
/*<       nrdatu(1) = 0 >*/
    nrdatu[1] = 0;
/*<       mu0 = 2-iopt(2) >*/
    mu0 = 2 - iopt[2];
/*<       mu1 = mu-2+iopt(3) >*/
    mu1 = *mu - 2 + iopt[3];
/*<       do 105 i=mu0,mu1 >*/
    i__1 = mu1;
    for (i__ = mu0; i__ <= i__1; ++i__) {
/*<         nrdatu(j) = nrdatu(j)+1 >*/
	++nrdatu[j];
/*<         if(u(i).lt.tu(l)) go to 105 >*/
	if (u[i__] < tu[l]) {
	    goto L105;
	}
/*<         nrdatu(j) = nrdatu(j)-1 >*/
	--nrdatu[j];
/*<         l = l+1 >*/
	++l;
/*<         j = j+1 >*/
	++j;
/*<         nrdatu(j) = 0 >*/
	nrdatu[j] = 0;
/*<  105  continue >*/
L105:
	;
    }
/*  we determine the number of grid coordinates v(i) inside each knot */
/*  interval (tv(l),tv(l+1)). */
/*<       l = 5 >*/
    l = 5;
/*<       j = 1 >*/
    j = 1;
/*<       nrdatv(1) = 0 >*/
    nrdatv[1] = 0;
/*<       do 110 i=2,mv >*/
    i__1 = *mv;
    for (i__ = 2; i__ <= i__1; ++i__) {
/*<         nrdatv(j) = nrdatv(j)+1 >*/
	++nrdatv[j];
/*<         if(v(i).lt.tv(l)) go to 110 >*/
	if (v[i__] < tv[l]) {
	    goto L110;
	}
/*<         nrdatv(j) = nrdatv(j)-1 >*/
	--nrdatv[j];
/*<         l = l+1 >*/
	++l;
/*<         j = j+1 >*/
	++j;
/*<         nrdatv(j) = 0 >*/
	nrdatv[j] = 0;
/*<  110  continue >*/
L110:
	;
    }
/*<       idd(1) = ider(1) >*/
    idd[0] = ider[1];
/*<       idd(2) = ider(2) >*/
    idd[1] = ider[2];
/*<       go to 120 >*/
    goto L120;
/*  if iopt(1)=0 or iopt(1)=1 and s >= fp0,we start computing the least- */
/*  squares polynomial (which is a spline without interior knots). */
/*<  115  ier = -2 >*/
L115:
    *ier = -2;
/*<       idd(1) = ider(1) >*/
    idd[0] = ider[1];
/*<       idd(2) = 1 >*/
    idd[1] = 1;
/*<       nu = 8 >*/
    *nu = 8;
/*<       nv = 8 >*/
    *nv = 8;
/*<       nrdatu(1) = mu-3+iopt(2)+iopt(3) >*/
    nrdatu[1] = *mu - 3 + iopt[2] + iopt[3];
/*<       nrdatv(1) = mv-1 >*/
    nrdatv[1] = *mv - 1;
/*<       lastdi = 0 >*/
    *lastdi = 0;
/*<       nplusu = 0 >*/
    *nplusu = 0;
/*<       nplusv = 0 >*/
    *nplusv = 0;
/*<       fp0 = 0. >*/
    *fp0 = 0.;
/*<       fpold = 0. >*/
    *fpold = 0.;
/*<       reducu = 0. >*/
    *reducu = 0.;
/*<       reducv = 0. >*/
    *reducv = 0.;
/*  main loop for the different sets of knots.mpm=mu+mv is a save upper */
/*  bound for the number of trials. */
/*<  120  mpm = mu+mv >*/
L120:
    mpm = *mu + *mv;
/*<       do 270 iter=1,mpm >*/
    i__1 = mpm;
    for (iter = 1; iter <= i__1; ++iter) {
/*  find nrintu (nrintv) which is the number of knot intervals in the */
/*  u-direction (v-direction). */
/*<         nrintu = nu-7 >*/
	nrintu = *nu - 7;
/*<         nrintv = nv-7 >*/
	nrintv = *nv - 7;
/*  find the position of the additional knots which are needed for the */
/*  b-spline representation of s(u,v). */
/*<         i = nu >*/
	i__ = *nu;
/*<         do 130 j=1,4 >*/
	for (j = 1; j <= 4; ++j) {
/*<           tu(j) = 0. >*/
	    tu[j] = 0.;
/*<           tu(i) = r >*/
	    tu[i__] = *r__;
/*<           i = i-1 >*/
	    --i__;
/*<  130    continue >*/
/* L130: */
	}
/*<         l1 = 4 >*/
	l1 = 4;
/*<         l2 = l1 >*/
	l2 = l1;
/*<         l3 = nv-3 >*/
	l3 = *nv - 3;
/*<         l4 = l3 >*/
	l4 = l3;
/*<         tv(l2) = vb >*/
	tv[l2] = vb;
/*<         tv(l3) = ve >*/
	tv[l3] = ve;
/*<         do 140 j=1,3 >*/
	for (j = 1; j <= 3; ++j) {
/*<           l1 = l1+1 >*/
	    ++l1;
/*<           l2 = l2-1 >*/
	    --l2;
/*<           l3 = l3+1 >*/
	    ++l3;
/*<           l4 = l4-1 >*/
	    --l4;
/*<           tv(l2) = tv(l4)-per >*/
	    tv[l2] = tv[l4] - per;
/*<           tv(l3) = tv(l1)+per >*/
	    tv[l3] = tv[l1] + per;
/*<  140    continue >*/
/* L140: */
	}
/*  find an estimate of the range of possible values for the optimal */
/*  derivatives at the origin. */
/*<         ktu = nrdatu(1)+2-iopt(2) >*/
	ktu = nrdatu[1] + 2 - iopt[2];
/*<         if(nrintu.eq.1) ktu = mu >*/
	if (nrintu == 1) {
	    ktu = *mu;
	}
/*<         if(ktu.lt.mumin) ktu = mumin >*/
	if (ktu < mumin) {
	    ktu = mumin;
	}
/*<         if(ktu.eq.lasttu) go to 150 >*/
	if (ktu == *lasttu) {
	    goto L150;
	}
/*<          zmin = z0 >*/
	zmin = *z0;
/*<          zmax = z0 >*/
	zmax = *z0;
/*<          l = mv*ktu >*/
	l = *mv * ktu;
/*<          do 145 i=1,l >*/
	i__2 = l;
	for (i__ = 1; i__ <= i__2; ++i__) {
/*<             if(z(i).lt.zmin) zmin = z(i) >*/
	    if (z__[i__] < zmin) {
		zmin = z__[i__];
	    }
/*<             if(z(i).gt.zmax) zmax = z(i) >*/
	    if (z__[i__] > zmax) {
		zmax = z__[i__];
	    }
/*<  145     continue >*/
/* L145: */
	}
/*<          step = zmax-zmin >*/
	*step = zmax - zmin;
/*<          lasttu = ktu >*/
	*lasttu = ktu;
/*  find the least-squares spline sinf(u,v). */
/*<  1 >*/
L150:
	fpopdi_(&ifsu, &ifsv, &ifbu, &ifbv, &u[1], mu, &v[1], mv, &z__[1], mz,
		 z0, &dz[1], &iopt[1], idd, &tu[1], nu, &tv[1], nv, nuest, 
		nvest, &p, step, &c__[1], nc, fp, &fpintu[1], &fpintv[1], &
		nru[1], &nrv[1], &wrk[1], lwrk);
/*<         if(step.lt.0.) step = -step >*/
	if (*step < 0.) {
	    *step = -(*step);
	}
/*<         if(ier.eq.(-2)) fp0 = fp >*/
	if (*ier == -2) {
	    *fp0 = *fp;
	}
/*  test whether the least-squares spline is an acceptable solution. */
/*<         if(iopt(1).lt.0) go to 440 >*/
	if (iopt[1] < 0) {
	    goto L440;
	}
/*<         fpms = fp-s >*/
	fpms = *fp - *s;
/*<         if(abs(fpms) .lt. acc) go to 440 >*/
	if (abs(fpms) < acc) {
	    goto L440;
	}
/*  if f(p=inf) < s, we accept the choice of knots. */
/*<         if(fpms.lt.0.) go to 300 >*/
	if (fpms < 0.) {
	    goto L300;
	}
/*  if nu=numax and nv=nvmax, sinf(u,v) is an interpolating spline */
/*<         if(nu.eq.numax .and. nv.eq.nvmax) go to 430 >*/
	if (*nu == numax && *nv == nvmax) {
	    goto L430;
	}
/*  increase the number of knots. */
/*  if nu=nue and nv=nve we cannot further increase the number of knots */
/*  because of the storage capacity limitation. */
/*<         if(nu.eq.nue .and. nv.eq.nve) go to 420 >*/
	if (*nu == nue && *nv == nve) {
	    goto L420;
	}
/*<         if(ider(1).eq.0) fpintu(1) = fpintu(1)+(z0-c(1))**2 >*/
	if (ider[1] == 0) {
/* Computing 2nd power */
	    d__1 = *z0 - c__[1];
	    fpintu[1] += d__1 * d__1;
	}
/*<         ier = 0 >*/
	*ier = 0;
/*  adjust the parameter reducu or reducv according to the direction */
/*  in which the last added knots were located. */
/*<         if(lastdi) 160,155,170 >*/
	if (*lastdi < 0) {
	    goto L160;
	} else if (*lastdi == 0) {
	    goto L155;
	} else {
	    goto L170;
	}
/*<  155     nplv = 3 >*/
L155:
	nplv = 3;
/*<          idd(2) = ider(2) >*/
	idd[1] = ider[2];
/*<          fpold = fp >*/
	*fpold = *fp;
/*<          go to 230 >*/
	goto L230;
/*<  160    reducu = fpold-fp >*/
L160:
	*reducu = *fpold - *fp;
/*<         go to 175 >*/
	goto L175;
/*<  170    reducv = fpold-fp >*/
L170:
	*reducv = *fpold - *fp;
/*  store the sum of squared residuals for the current set of knots. */
/*<  175    fpold = fp >*/
L175:
	*fpold = *fp;
/*  find nplu, the number of knots we should add in the u-direction. */
/*<         nplu = 1 >*/
	nplu = 1;
/*<         if(nu.eq.8) go to 180 >*/
	if (*nu == 8) {
	    goto L180;
	}
/*<         npl1 = nplusu*2 >*/
	npl1 = *nplusu << 1;
/*<         rn = nplusu >*/
	rn = (doublereal) (*nplusu);
/*<         if(reducu.gt.acc) npl1 = rn*fpms/reducu >*/
	if (*reducu > acc) {
	    npl1 = (integer) (rn * fpms / *reducu);
	}
/*<         nplu = min0(nplusu*2,max0(npl1,nplusu/2,1)) >*/
/* Computing MIN */
/* Computing MAX */
	i__4 = npl1, i__5 = *nplusu / 2, i__4 = max(i__4,i__5);
	i__2 = *nplusu << 1, i__3 = max(i__4,1);
	nplu = min(i__2,i__3);
/*  find nplv, the number of knots we should add in the v-direction. */
/*<  180    nplv = 3 >*/
L180:
	nplv = 3;
/*<         if(nv.eq.8) go to 190 >*/
	if (*nv == 8) {
	    goto L190;
	}
/*<         npl1 = nplusv*2 >*/
	npl1 = *nplusv << 1;
/*<         rn = nplusv >*/
	rn = (doublereal) (*nplusv);
/*<         if(reducv.gt.acc) npl1 = rn*fpms/reducv >*/
	if (*reducv > acc) {
	    npl1 = (integer) (rn * fpms / *reducv);
	}
/*<         nplv = min0(nplusv*2,max0(npl1,nplusv/2,1)) >*/
/* Computing MIN */
/* Computing MAX */
	i__4 = npl1, i__5 = *nplusv / 2, i__4 = max(i__4,i__5);
	i__2 = *nplusv << 1, i__3 = max(i__4,1);
	nplv = min(i__2,i__3);
/*  test whether we are going to add knots in the u- or v-direction. */
/*<  190    if(nplu-nplv) 210,200,230 >*/
L190:
	if ((i__2 = nplu - nplv) < 0) {
	    goto L210;
	} else if (i__2 == 0) {
	    goto L200;
	} else {
	    goto L230;
	}
/*<  200    if(lastdi.lt.0) go to 230 >*/
L200:
	if (*lastdi < 0) {
	    goto L230;
	}
/*<  210    if(nu.eq.nue) go to 230 >*/
L210:
	if (*nu == nue) {
	    goto L230;
	}
/*  addition in the u-direction. */
/*<         lastdi = -1 >*/
	*lastdi = -1;
/*<         nplusu = nplu >*/
	*nplusu = nplu;
/*<         ifsu = 0 >*/
	ifsu = 0;
/*<         istart = 0 >*/
	istart = 0;
/*<         if(iopt(2).eq.0) istart = 1 >*/
	if (iopt[2] == 0) {
	    istart = 1;
	}
/*<         do 220 l=1,nplusu >*/
	i__2 = *nplusu;
	for (l = 1; l <= i__2; ++l) {
/*  add a new knot in the u-direction */
/*<           call fpknot(u,mu,tu,nu,fpintu,nrdatu,nrintu,nuest,istart) >*/
	    fpknot_(&u[1], mu, &tu[1], nu, &fpintu[1], &nrdatu[1], &nrintu, 
		    nuest, &istart);
/*  test whether we cannot further increase the number of knots in the */
/*  u-direction. */
/*<           if(nu.eq.nue) go to 270 >*/
	    if (*nu == nue) {
		goto L270;
	    }
/*<  220    continue >*/
/* L220: */
	}
/*<         go to 270 >*/
	goto L270;
/*<  230    if(nv.eq.nve) go to 210 >*/
L230:
	if (*nv == nve) {
	    goto L210;
	}
/*  addition in the v-direction. */
/*<         lastdi = 1 >*/
	*lastdi = 1;
/*<         nplusv = nplv >*/
	*nplusv = nplv;
/*<         ifsv = 0 >*/
	ifsv = 0;
/*<         do 240 l=1,nplusv >*/
	i__2 = *nplusv;
	for (l = 1; l <= i__2; ++l) {
/*  add a new knot in the v-direction. */
/*<           call fpknot(v,mv,tv,nv,fpintv,nrdatv,nrintv,nvest,1) >*/
	    fpknot_(&v[1], mv, &tv[1], nv, &fpintv[1], &nrdatv[1], &nrintv, 
		    nvest, &c__1);
/*  test whether we cannot further increase the number of knots in the */
/*  v-direction. */
/*<           if(nv.eq.nve) go to 270 >*/
	    if (*nv == nve) {
		goto L270;
	    }
/*<  240    continue >*/
/* L240: */
	}
/*  restart the computations with the new set of knots. */
/*<  270  continue >*/
L270:
	;
    }
/*  test whether the least-squares polynomial is a solution of our */
/*  approximation problem. */
/*<  300  if(ier.eq.(-2)) go to 440 >*/
L300:
    if (*ier == -2) {
	goto L440;
    }
/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
/* part 2: determination of the smoothing spline sp(u,v)                c */
/* *****************************************************                c */
/*  we have determined the number of knots and their position. we now   c */
/*  compute the b-spline coefficients of the smoothing spline sp(u,v).  c */
/*  this smoothing spline depends on the parameter p in such a way that c */
/*    f(p) = sumi=1,mu(sumj=1,mv((z(i,j)-sp(u(i),v(j)))**2)             c */
/*  is a continuous, strictly decreasing function of p. moreover the    c */
/*  least-squares polynomial corresponds to p=0 and the least-squares   c */
/*  spline to p=infinity. then iteratively we have to determine the     c */
/*  positive value of p such that f(p)=s. the process which is proposed c */
/*  here makes use of rational interpolation. f(p) is approximated by a c */
/*  rational function r(p)=(u*p+v)/(p+w); three values of p (p1,p2,p3)  c */
/*  with corresponding values of f(p) (f1=f(p1)-s,f2=f(p2)-s,f3=f(p3)-s)c */
/*  are used to calculate the new value of p such that r(p)=s.          c */
/*  convergence is guaranteed by taking f1 > 0 and f3 < 0.              c */
/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
/*  initial value for p. */
/*<       p1 = 0. >*/
    p1 = 0.;
/*<       f1 = fp0-s >*/
    f1 = *fp0 - *s;
/*<       p3 = -one >*/
    p3 = -one;
/*<       f3 = fpms >*/
    f3 = fpms;
/*<       p = one >*/
    p = one;
/*<       dzz(1) = dz(1) >*/
    dzz[0] = dz[1];
/*<       dzz(2) = dz(2) >*/
    dzz[1] = dz[2];
/*<       dzz(3) = dz(3) >*/
    dzz[2] = dz[3];
/*<       ich1 = 0 >*/
    ich1 = 0;
/*<       ich3 = 0 >*/
    ich3 = 0;
/*  iteration process to find the root of f(p)=s. */
/*<       do 350 iter = 1,maxit >*/
    i__1 = *maxit;
    for (iter = 1; iter <= i__1; ++iter) {
/*  find the smoothing spline sp(u,v) and the corresponding sum f(p). */
/*<    >*/
	fpopdi_(&ifsu, &ifsv, &ifbu, &ifbv, &u[1], mu, &v[1], mv, &z__[1], mz,
		 z0, dzz, &iopt[1], idd, &tu[1], nu, &tv[1], nv, nuest, nvest,
		 &p, step, &c__[1], nc, fp, &fpintu[1], &fpintv[1], &nru[1], &
		nrv[1], &wrk[1], lwrk);
/*  test whether the approximation sp(u,v) is an acceptable solution. */
/*<         fpms = fp-s >*/
	fpms = *fp - *s;
/*<         if(abs(fpms).lt.acc) go to 440 >*/
	if (abs(fpms) < acc) {
	    goto L440;
	}
/*  test whether the maximum allowable number of iterations has been */
/*  reached. */
/*<         if(iter.eq.maxit) go to 400 >*/
	if (iter == *maxit) {
	    goto L400;
	}
/*  carry out one more step of the iteration process. */
/*<         p2 = p >*/
	p2 = p;
/*<         f2 = fpms >*/
	f2 = fpms;
/*<         if(ich3.ne.0) go to 320 >*/
	if (ich3 != 0) {
	    goto L320;
	}
/*<         if((f2-f3).gt.acc) go to 310 >*/
	if (f2 - f3 > acc) {
	    goto L310;
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
/*<         go to 350 >*/
	goto L350;
/*<  310    if(f2.lt.0.) ich3 = 1 >*/
L310:
	if (f2 < 0.) {
	    ich3 = 1;
	}
/*<  320    if(ich1.ne.0) go to 340 >*/
L320:
	if (ich1 != 0) {
	    goto L340;
	}
/*<         if((f1-f2).gt.acc) go to 330 >*/
	if (f1 - f2 > acc) {
	    goto L330;
	}
/*  our initial choice of p is too small */
/*<         p1 = p2 >*/
	p1 = p2;
/*<         f1 = f2 >*/
	f1 = f2;
/*<         p = p/con4 >*/
	p /= con4;
/*<         if(p3.lt.0.) go to 350 >*/
	if (p3 < 0.) {
	    goto L350;
	}
/*<         if(p.ge.p3) p = p2*con1 + p3*con9 >*/
	if (p >= p3) {
	    p = p2 * con1 + p3 * con9;
	}
/*<         go to 350 >*/
	goto L350;
/*  test whether the iteration process proceeds as theoretically */
/*  expected. */
/*<  330    if(f2.gt.0.) ich1 = 1 >*/
L330:
	if (f2 > 0.) {
	    ich1 = 1;
	}
/*<  340    if(f2.ge.f1 .or. f2.le.f3) go to 410 >*/
L340:
	if (f2 >= f1 || f2 <= f3) {
	    goto L410;
	}
/*  find the new value of p. */
/*<         p = fprati(p1,f1,p2,f2,p3,f3) >*/
	p = fprati_(&p1, &f1, &p2, &f2, &p3, &f3);
/*<  350  continue >*/
L350:
	;
    }
/*  error codes and messages. */
/*<  400  ier = 3 >*/
L400:
    *ier = 3;
/*<       go to 440 >*/
    goto L440;
/*<  410  ier = 2 >*/
L410:
    *ier = 2;
/*<       go to 440 >*/
    goto L440;
/*<  420  ier = 1 >*/
L420:
    *ier = 1;
/*<       go to 440 >*/
    goto L440;
/*<  430  ier = -1 >*/
L430:
    *ier = -1;
/*<       fp = 0. >*/
    *fp = 0.;
/*<  440  return >*/
L440:
    return 0;
/*<       end >*/
} /* fppogr_ */

