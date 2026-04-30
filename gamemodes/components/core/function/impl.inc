#if defined _inc_impl
	#undef _inc_impl
#endif

jdzrandom(min, max){
	new number = min + random(max) % (max);
	if(number > max) number = max;
    return number; 
}