



void fill(int v[], int s, int e){
    m = (s + e)/2;
	if(e-s+1 = 3){
		v[e] = m + 1;
        v[s] = m;
        v[s+1] = m + 2;
	}
	else if(e-s+1 > 3){
        fill(v, s, m-1);
        fill(v, m+1, e);
		v[m] = v[e] (+1); 
        v[e] = m (+1);
	}
}



n = {127, 255, 511, 1023, 2047, 4095, 9191}
2^x - 1
