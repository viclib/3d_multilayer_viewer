double guide_z(const vec & pos){ 
	return 0; 
}
vec guide_col(const vec & pos){ 
	double add=int(pos.x+pos.y)%2*0.2; 
	return vec(0.5+add,0.5+add,0.5+add); 
}
