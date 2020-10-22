#include "SBC.h"

#include "maths/maths.h"

char *game_get_coordinate(struct vec3f position)
{
	position.x=position.x/100;
	position.y=position.y/100;
	position.z=position.z/100;

	signed int position_int[3];
	position_int[0]=(signed int)position.x;
	position_int[2]=(signed int)position.y;
	position_int[1]=(signed int)position.z;

	char *coordinate=malloc(4*sizeof(char));

	if(	position_int[0]<5 && position_int[0]>-5 &&
		position_int[1]<5 && position_int[1]>-5 &&
		position_int[2]<3 && position_int[2]>-3)
	{
		*(coordinate)='E'+(signed char)position_int[0];
		*(coordinate+sizeof(char))='E'+(signed char)position_int[1];
		*(coordinate+sizeof(char)*2)='3'+(signed char)position_int[2];
		*(coordinate+sizeof(char)*3)='\0';
	}
	else
	{
		*(coordinate)='O';
		*(coordinate+sizeof(char))='o';
		*(coordinate+sizeof(char)*2)='B';
		*(coordinate+sizeof(char)*3)='\0';
	}

	return coordinate;

}