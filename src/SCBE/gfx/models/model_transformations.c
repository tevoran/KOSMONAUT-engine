#include "gfx/gfx.h"
#include "maths/maths.h"



void gfx_update_model_location(struct entry* model, struct vec3f location)
{
    /*calculating world transform matrix*/
    GLfloat world_matrix[4][4]=
    {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        location.x, location.y, location.z, 1
    };
    
    for(int ix=0,iy=0; iy<4; ix++)
    {
        model->world_transform_matrix[ix][iy]=world_matrix[ix][iy];
        if(ix==3)
        {
            ix=-1;
            iy++;
        }
    }
}