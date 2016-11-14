#include <time.h>
#include "Random.h"

hINT Random::qd2idnum;
hINT Random::seed;
hLONG Random::ran1idnum;
Random::Random() {
	seed = (unsigned)time(NULL);
	ran1idnum = -(hLONG)seed;
	qd2idnum = -(hINT)seed;
	srand(seed);
}

Random::~Random() {}

hDOUBLE Random::rand(hDOUBLE low, hDOUBLE high) {
	return (ran1()*(high - low)) + low;
}

hINT Random::rand(hINT low, hINT high) {
	return (hINT)rand((hDOUBLE)low, (hDOUBLE)high);
}

#define IA 16807
#define IM 2147483647
#define AM (1.0/IM)
#define IQ 127773
#define IR 2836
#define NTAB 32
#define NDIV (1+(IM-1)/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)
hDOUBLE  Random::ran1() 
{
	hINT j;
	hLONG k;
	static hLONG iy = 0;
	static hLONG iv[NTAB];
	hFLOAT temp;

	if (ran1idnum <= 0 || !iy) 
	{
		if (-(ran1idnum) < 1) 
			ran1idnum = 1;
		else 
			ran1idnum = -(ran1idnum);
		for (j = NTAB + 7; j >= 0; j--) 
		{
			k = (ran1idnum) / IQ;
			ran1idnum = IA*(ran1idnum - k*IQ) - IR*k;

			if (ran1idnum < 0) 
				ran1idnum += IM;
			if (j < NTAB) 
				iv[j] = ran1idnum;
		}
		iy = iv[0];
	}
	k = (ran1idnum) / IQ;
	ran1idnum = IA*(ran1idnum - k*IQ) - IR*k;

	if (ran1idnum < 0) 
		ran1idnum += IM;

	j = iy / NDIV;
	iy = iv[j];
	iv[j] = ran1idnum;
	temp = (hFLOAT)AM*iy;

	if (temp > RNMX) {
		return RNMX;
	}
	else {
		return temp;
	}
}
#undef IA
#undef IM
#undef AM
#undef IQ
#undef IR
#undef NTAB
#undef NDIV
#undef EPS
#undef RNMX



/* mean m, standard deviation s */
hFLOAT Random::box_muller(hFLOAT m, hFLOAT s) {
	hINT idnum = -1;
	hDOUBLE x1, x2, w, y1;
	static hDOUBLE y2;
	static hINT use_last = 0;

	if (use_last) {/* use value from previous call */
		y1 = y2;
		use_last = 0;
	}
	else {
		do {
			x1 = 2.0 * ran1() - 1.0;
			x2 = 2.0 * ran1() - 1.0;
			w = x1 * x1 + x2 * x2;
		} while (w >= 1.0);

		w = sqrt((-2.0 *log(w)) / w);
		y1 = x1 * w;
		y2 = x2 * w;
		use_last = 1;
	}

	return(m + y1 * s);
}
