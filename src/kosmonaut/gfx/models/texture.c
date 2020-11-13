#include "gfx/gfx.h"

#include "gfx/data/data.h"

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>

void gfx_model_load_texture(char *file_location, struct model *model)
{
	data_texture_load(file_location, &model->textureID);
}