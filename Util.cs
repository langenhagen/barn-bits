private static Color ColorFromHSL(float H, float S, float L)
{
	int Max, Mid = 0, Min;

	if (L <= 0.5){
		Min = (int)((L-(L*S))*255);
	}else{
		Min = (int)(((S*L)+L-S)*255);
	}
	Max = (int)(2*L*255) - Min;

	if ( H >= 0 && H <= 60 ){
		Mid = (int)((H/60)*(Max-Min))+Min;
		return Color.FromArgb(Max, Mid, Min);
	}else if ( H <= 120 ){
		Mid = (int)(-1*(((H-120)/60)*(Max-Min))+Min);
		return Color.FromArgb(Mid, Max, Min);
	}else if ( H <= 180 ){
		Mid = (int)((((H-120)/60)*(Max-Min))+Min);
		return Color.FromArgb(Min, Max, Mid);
	}else if ( H <= 240 ){
		Mid = (int)(-1*(((H-240)/60)*(Max-Min))+Min);
		return Color.FromArgb(Min, Mid, Max);
	}else if ( H <= 300 ){
		Mid = (int)((((H-240)/60)*(Max-Min))+Min);
		return Color.FromArgb(Mid, Min, Max);
	}else if ( H <= 360 ){
		Mid = (int)(-1*(((H-360)/60)*(Max-Min))+Min);
		return Color.FromArgb(Max, Min, Mid);
	}else{
		return Color.FromArgb(0, 0, 0);
	}
}
