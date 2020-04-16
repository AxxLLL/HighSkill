/***************************
 *   --- Data system ---   *
 *       Autor: AxL_       *
 *     Version: 1.0.0      *
 ***************************/


/*

*/

#if defined _a_data_included
  #endinput
#endif

#define _a_data_included
#pragma library a_data

/*
native timestamp(Y = 0, M = 0, D = 0, h = 0, m = 0, s = 0);
native dtimestamp(time_stamp, &Y = 0, &M = 0, &D = 0, &h = 0, &m = 0, &s = 0);
native GetDaysInMonth(_month, bool:leap_year = false);
native IsRealData(_year, _month, _day);
native DataSplit(rrrrmmdd[], &Y = 0, &M = 0, &D = 0, separator[] = "-");
native GetHighestData(first_Y, first_M, first_D, second_Y, second_M, second_D);
native strData(_year, _month, _day, _separator[4] = '-', bool:year_first = true, bool:_special = false, bool:full_month_name = false, bool:cut_month_name = false);
native DataSub(_year, _month, _day, _hour, _minute, _second, sub_val, DATE_TYPE:type, &r_year = 0, &r_month = 0, &r_day = 0, &r_hour = 0, &r_minute = 0, &r_second = 0);
native DataAdd(_year, _month, _day, _hour, _minute, _second, add_val, DATE_TYPE:type, &r_year = 0, &r_month = 0, &r_day = 0, &r_hour = 0, &r_minute = 0, &r_second = 0);
native ToSeconds(timeval, DATE_TYPE:type);
native convertSeconds(time);
*/
//==============================================================================
#define INVALID_DATA	0
#define _DATA			1

#define SAME_DATA		2
#define FIRST_DATA		3
#define SECOND_DATA		4


#define TIMESTAMP_YEAR	2011
#define TIMESTAMP_MONTH	1
#define TIMESTAMP_DAY	1

#define SECONDS_DAY			86400
#define SECONDS_MINUTE		60
#define SECONDS_HOUR		3600
#define SECONDS_YEAR		31536000
#define SECONDS_LEAP_YEAR	31622400

#define LEAP_DAYS	5097600

#define UNIX_DAY	1
#define UNIX_MONTH	1
#define UNIX_YEAR	1970

enum DATE_TYPE {_YEAR, _MONTH, _DAY, _HOUR, _MINUTE, _SECOND}
//==============================================================================
enum DATA_INFO	{	_NAME[4],	_DAYS, _SECONDS, _YEARSTAMP	}
new const Month[12][DATA_INFO] = {	
	{!"Styczen", 31, 2678400, 2678400},    		{!"Luty", 28, 2419200, 5097600},    			{!"Marzec", 31, 2678400, 7776000},    	{!"Kwiecien", 30, 2592000, 10368000},
	{!"Maj", 31, 2678400, 13046400},    		{!"Czerwiec", 30, 2592000, 15638400},    		{!"Lipiec", 31, 2678400, 18316800},    	{!"Sierpien", 31, 2678400, 20995200},
	{!"Wrzesien", 30, 2592000, 23587200},    	{!"Pazdziernik", 31, 2678400, 26265600},    	{!"Listopad", 30, 2592000, 28857600},  	{!"Grudzien", 31, 2678400, 31536000}
};
//==============================================================================
stock timestamp(Y = 0, M = 0, D = 0, h = 0, m = 0, s = 0) {
	if(Y == 0 && M == 0 && D == 0 && h == 0 && m == 0 && s == 0) return gettime();
	else {
		if(IsRealData(Y, M, D) && 23 >= h >= 0 && 59 >= m >= 0 && 59 >= s >= 0) {
			new time = -3600, leap_years = floatround(floatdiv(Y - UNIX_YEAR + 2, 4), floatround_floor);
			new bool:add_day;
			time += (Y - UNIX_YEAR) * SECONDS_YEAR + (leap_years * SECONDS_DAY);
			if(Y % 4 == 0) {
				add_day = true;
				if(M < 3) time -= SECONDS_DAY;
			}
			
			for(new i, y = M - 1; i < y; i ++) {
				time += Month[i][_SECONDS];
			}			
			
			if(10 >= M >= 3) {	
				if(M == 3) {
					if(D <= 28) {
						if(D == 28 && h >= 3) time -= SECONDS_HOUR;
					} else time -= SECONDS_HOUR;
				} else if(M == 10) {
					if(D < 31) time -= SECONDS_HOUR;	
					else {
						if(h < 2) time -= SECONDS_HOUR;
					}
				} else time -= SECONDS_HOUR;	
			}						
			
			if(add_day == true) {
				if((M == 3 && ((27 == D && h >= 3) || (D == 28 && h < 3)))) time -= SECONDS_HOUR;
				else if((M == 10 && ((30 == D && h >= 3) || (D == 31 && h < 2)))) time += SECONDS_HOUR;
			}
			
			time += ((D - 1) * SECONDS_DAY + h * SECONDS_HOUR + m * SECONDS_MINUTE + s);		
			return time;
		}
	}
	return -1;
}

//------------------------------------------------------------------------------
stock dtimestamp(time_stamp, &Y = 0, &M = 0, &D = 0, &h = 0, &m = 0, &s = 0) {
	Y = M = D = h = m = 0;
	if(time_stamp >= -3600) {
		time_stamp += 3600;			
		new years;
		new x = SECONDS_YEAR;
		while(time_stamp >= x) {
			time_stamp -= x;
			years ++;
			x = (years + 2) % 4 == 0 ? SECONDS_LEAP_YEAR : SECONDS_YEAR;
		}					
		Y = UNIX_YEAR + years;
		years = Y % 4 == 0 ? 1 : 0;
		
		if(7441200 <= time_stamp < 26186400) time_stamp += SECONDS_HOUR;
		
		new months;
		for(new i, limit; i < 12; i ++) {
			limit = (years == 1 && i == 1 ? Month[i][_SECONDS] + SECONDS_DAY : Month[i][_SECONDS]);		
			
			if(time_stamp > limit) {
				time_stamp -= limit;
			} else {
				if(time_stamp == limit) {
					months = i + 2;
					time_stamp -= limit;
				} else months = i +1;
				break;
			}
		}
		
		M = months;			
		D = floatround(time_stamp / SECONDS_DAY, floatround_floor) + 1;
		time_stamp -= ((D - 1) * SECONDS_DAY);
		h = floatround(time_stamp / SECONDS_HOUR, floatround_floor);
		time_stamp -= (h * SECONDS_HOUR);
		m = floatround(time_stamp / SECONDS_MINUTE, floatround_floor);
		time_stamp -= (m * SECONDS_MINUTE);
		s = time_stamp;
	}
}
//==============================================================================
/*
	Returns the numbers of day in month (from 'Month' varible)
*/
stock GetDaysInMonth(_month, bool:leap_year = false) return 1 <= _month <= 12 ? leap_year == false ? Month[_month - 1][_DAYS] : _month == 2 ? 29 : Month[_month - 1][_DAYS] : INVALID_DATA;
//------------------------------------------------------------------------------
/*
	Checks if the date is correct
	Returns:
		_DATA (1) - true
		INVALID_DATA (0) - false
*/
stock IsRealData(_year, _month, _day) {
	if(1970 <= _year <= 3000 && 1 <= _month <= 12) {
		if(1 <= _day <= GetDaysInMonth(_month, _year % 4 == 0 ? true : false))	return _DATA;
	}
	return INVALID_DATA;
} 
//------------------------------------------------------------------------------
/*
	Split string data in rrrrmmdd format by 'separator'
	New date values are saving in 'Y', 'M', 'D' variables
*/
stock DataSplit(rrrrmmdd[], &Y = 0, &M = 0, &D = 0, separator[] = "-") {
	new length;
	if(10 >= (length = strlen(rrrrmmdd)) >= 8) {
		new index_1, index_2;
		if((index_1 = strfind(rrrrmmdd, separator)) > 0 && 2 < (index_2 = strfind(rrrrmmdd, separator, false, index_1 + 1)) < length - 1 and strfind(rrrrmmdd, separator, false, index_2 + 1) == -1) {
			new s_year[6], s_month[4], s_day[4];
			if(index_1 <= 2) {
				strmid(s_day, rrrrmmdd, 0, index_1);
				strmid(s_year, rrrrmmdd, index_2 + 1, length);
			} else {
				strmid(s_year, rrrrmmdd, 0, index_1);
				strmid(s_day, rrrrmmdd, index_2 + 1, length);
			}
			
			strmid(s_month, rrrrmmdd, index_1 + 1, index_2);			
			Y = strval(s_year);
			M = strval(s_month);
			D = strval(s_day);
			if(IsRealData(Y, M, D) == _DATA) return 1;
		}
	}
	Y = M = D = 0;
	
	return 0;
}

//------------------------------------------------------------------------------
/*
	Checks two dates and returns higher
	Returns:
		INVALID_DATA (0) - if one of date is invalid
		SAME_DATA (2) - if dates are same
		FIRST_DATA (3) - if first data is higher
		SECOND_DATA (4) - if second data is higher
*/
stock GetHighestData(first_Y, first_M, first_D, second_Y, second_M, second_D) {
	if(IsRealData(first_Y, first_M, first_D) == _DATA && IsRealData(second_Y, second_M, second_D) == _DATA) {
		if(first_Y == second_Y) {
			if(first_M == second_M) return first_D > second_D ? FIRST_DATA : first_D < second_D ? SECOND_DATA : SAME_DATA;
			else return first_M > second_M ? FIRST_DATA : SECOND_DATA;			
		}	else return first_Y > second_Y ? FIRST_DATA : SECOND_DATA;
	}
	return INVALID_DATA;
}
//------------------------------------------------------------------------------
stock strData(_year, _month, _day, _separator[4] = '-', bool:year_first = true, bool:_special = false, bool:full_month_name = false, bool:cut_month_name = false) {
	new _strData[32] = "WRONG DATA";
	if(IsRealData(_year, _month, _day) == _DATA) {
		new month[16];
	    strdel(_strData, 0, 32);
		if(year_first == true) {
			if(full_month_name == false) {
				if(_special == true)	format(_strData, 32, "%d%s%02d%s%02d",_year, _separator, _month, _separator, _day);
				else                    format(_strData, 32, "%d%s%d%s%d",_year, _separator, _month, _separator, _day);
			} else {
				strunpack(month, Month[_month - 1][_NAME]);
			    strmid(_strData, month, 0, cut_month_name == true ? 3 : strlen(month));
				if(_special == true)	format(_strData, 32, "%d%s%s%s%02d",_year, _separator, _strData, _separator, _day);
				else                    format(_strData, 32, "%d%s%s%s%d",_year, _separator, _strData, _separator, _day);
			}
		} else {
			if(full_month_name == false) {
				if(_special == true)	format(_strData, 32, "%02d%s%02d%s%d",_day, _separator, _month, _separator, _year);
				else                    format(_strData, 32, "%d%s%d%s%d",_day, _separator, _month, _separator, _year);
			} else {
				strunpack(month, Month[_month - 1][_NAME]);
			    strmid(_strData, month, 0, cut_month_name == true ? 3 : strlen(month));
				if(_special == true)	format(_strData, 32, "%02d%s%s%s%d",_day, _separator, _strData, _separator, _year);
				else                    format(_strData, 32, "%d%s%s%s%d",_day, _separator, _strData, _separator, _year);
			}
		}
	}
	return _strData;
}
//------------------------------------------------------------------------------
stock DataSub(_year, _month, _day, _hour, _minute, _second, sub_val, DATE_TYPE:type, &r_year = 0, &r_month = 0, &r_day = 0, &r_hour = 0, &r_minute = 0, &r_second = 0) {
	if(IsRealData(_year, _month, _day) && 23 >= _hour >= 0 && 59 >= _minute >= 0 && 59 >= _second >= 0) {
		new data_stamp = timestamp(_year, _month, _day, _hour, _minute, _second);
		data_stamp -= ToSeconds(add_val, type);
		if(data_stamp < -3600) data_stamp = -3600;
		dtimestamp(data_stamp, r_year, r_month, r_day, r_hour, r_minute, r_second);
		return data_stamp;		
	}
    return -3601;
}
//------------------------------------------------------------------------------
stock DataAdd(_year, _month, _day, _hour, _minute, _second, add_val, DATE_TYPE:type, &r_year = 0, &r_month = 0, &r_day = 0, &r_hour = 0, &r_minute = 0, &r_second = 0) {
	if(IsRealData(_year, _month, _day) && 23 >= _hour >= 0 && 59 >= _minute >= 0 && 59 >= _second >= 0) {
		new data_stamp = timestamp(_year, _month, _day, _hour, _minute, _second);
		data_stamp += ToSeconds(add_val, type);
		if(data_stamp < -3600) data_stamp = -3600;
		dtimestamp(data_stamp, r_year, r_month, r_day, r_hour, r_minute, r_second);
		return data_stamp;		
	}
    return -3601;
}
//------------------------------------------------------------------------------
stock ToSeconds(timeval, DATE_TYPE:type) {
	if(timeval > 0) {
		switch(type) {
			case _YEAR:		return timeval * SECONDS_YEAR;
			case _MONTH:	return timeval * 15638400;
			case _DAY:		return timeval * SECONDS_DAY;
			case _HOUR:		return timeval * SECONDS_HOUR;
			case _MINUTE:	return timeval * SECONDS_MINUTE;
			case _SECOND:	return timeval;
		}
	}
	return 0;
}
//------------------------------------------------------------------------------
stock convertSeconds(time, &days = 0, &hours = 0, &minutes = 0, &seconds = 0) {
	new string[32];
	if(time > 0) {
		while(time >= SECONDS_DAY) {
			days ++;
			time -= SECONDS_DAY;
		}
		while(time >= SECONDS_HOUR) {
			hours ++;
			time -= SECONDS_HOUR;
		}		
		while(time >= SECONDS_MINUTE) {
			minutes ++;
			time -= SECONDS_MINUTE;
		}				
		seconds = time;
		if(days > 0) format(string, sizeof(string), "%dd", days);
		if(hours > 0) format(string, sizeof(string), "%s %dg", string, hours);
		if(minutes > 0) format(string, sizeof(string), "%s %dm", string, minutes);
		if(seconds > 0) format(string, sizeof(string), "%s %ds", string, seconds);
		
		for(new i, len = strlen(string); i < len; ) {
			if(string[i] == ' ') {
				strdel(string, i, i + 1);
				len --;
				continue;
			} else break;
			i ++;
		}		
	}
	return string;
}

