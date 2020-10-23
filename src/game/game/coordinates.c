#include "SBC.h"

#include "maths/maths.h"

#define field_size 200

signed char *game_get_coordinate(struct vec3f position)
{
	position.x=position.x/field_size;
	position.y=position.y/field_size;
	position.z=position.z/field_size;

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

struct vec3f game_set_coordinate(signed char coordinate[4])
{
	struct vec3f world_coordinates;
	if(	coordinate[0]>='A' && coordinate[0]<='I' &&
		coordinate[1]>='A' && coordinate[1]<='I' &&
		coordinate[2]>='1' && coordinate[2]<='5')
	{
		world_coordinates.x=(float)(coordinate[0]-'E')*field_size+0.5*field_size;
		world_coordinates.z=(float)(coordinate[1]-'E')*field_size+0.5*field_size;
		world_coordinates.y=(float)(coordinate[2]-'3')*field_size+0.5*field_size;
		printf("Coordinates: %s\n%f, %f, %f\n", coordinate, world_coordinates.x, world_coordinates.y, world_coordinates.z);
		return world_coordinates;
	}
}