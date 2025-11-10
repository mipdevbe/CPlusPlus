#include "classes.h"


Distance operator "" _mi(long double km) {
	return Distance{ km * 1.6 };
}

Distance operator "" _meters(long double km) {
	return Distance{ km / 1000 };
}
