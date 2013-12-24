//////////////////////////////////////////////////////////////////////////////
//OPENGL
//////////////////////////////////////////////////////////////////////////////

/*------------------------------------------------------------------
OPENGL: Column Major Matrix / Right Handed Coordinate System
------------------------------------------------------------------
Trans * Rot * Scale = LocalWorld
ParentWorld * LocalWorld = World
Proj * Veiw * World * Vertex = FinalVertex in screenspace

| Right.x  Up.x  For.x  Pos.x |    UP: +Y
| Right.y  Up.y  For.y  Pos.y |    RIGHT: +X
| Right.z  Up.z  For.z  Pos.z |    FORWARD: -Z
|   0       0       0     1   |
------------------------------------------------------------------*/

//////////////////////////////////////////////////////////////////////////////
//RENDERING
//////////////////////////////////////////////////////////////////////////////

// Rendering textures
glBindTexture(GL_TEXTURE_2D, texture);
glColor4f(1.0f, 1.0f, 1.0f, 1.0f); // set the global tint color
glBegin(GL_QUADS);

glTexCoord2f(uvLeft, uvTop); //top left corner
glVertex2i(GLint(std::round(topLeft.x)),GLint(std::round(topLeft.y)));
    
glTexCoord2f(uvRight, uvTop); //top right corner
glVertex2i(GLint(std::round(topRight.x)),GLint(std::round(topRight.y)));

glTexCoord2f(uvRight, uvBot); //Bottom right corner
glVertex2i(GLint(std::round(botRight.x)),GLint(std::round(botRight.y)));

glTexCoord2f(uvLeft, uvBot); //Bottom left corner
glVertex2i(GLint(std::round(botLeft.x)),GLint(std::round(botLeft.y)));
glEnd();

// Rendering lines
glColor4f(1.0f, 1.0f, 1.0f, 1.0f); // set the global tint color
glBegin(GL_LINES);
glVertex2d(start.x, start.y);
glVertex2d(end.x, end.y);
glEnd();

//////////////////////////////////////////////////////////////////////////////
//SETTING UP OPENGL FOR 2D
//////////////////////////////////////////////////////////////////////////////

std::array<float, 16> ViewMatrix;
std::array<float, 16> ProjMatrix;

glEnable(GL_TEXTURE_2D);
glEnable(GL_BLEND);
glViewport(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//Create the 2D projection matrix
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho(0,SCREEN_WIDTH,SCREEN_HEIGHT,0,0,100.0f);
glGetFloatv(GL_PROJECTION_MATRIX, &ProjMatrix[0]);

glDisable(GL_DEPTH_TEST);
glDisable(GL_CULL_FACE);
glMatrixMode(GL_PROJECTION);
glLoadMatrixf(&ProjMatrix[0]);

//Create the 2D view matrix
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
gluLookAt(0.0f, 0.0f, 1.0f,  // the camera position
          0.0f, 0.0f, 0.0f,  // the look-at position
          0.0f, 1.0f, 0.0f); // the up direction
glPushMatrix();
glGetFloatv(GL_MODELVIEW_MATRIX,&ViewMatrix[0]);

glMatrixMode(GL_MODELVIEW);
glLoadMatrixf(&ViewMatrix[0]);

//////////////////////////////////////////////////////////////////////////////
//MODIFYING TEXTURE
//////////////////////////////////////////////////////////////////////////////

// Creating array of pixels from texture
unsigned int* pixels = new unsigned int[width*height];
glBindTexture(GL_TEXTURE_2D, texture);
glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

// Modifying a texture with an array
// where x,y is the offset in the texture to start overwriting with the array
unsigned int pixels = new unsigned int[width*height];
glBindTexture(GL_TEXTURE_2D, texture);
glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

//////////////////////////////////////////////////////////////////////////////
//CREATE A TEXTURE
//////////////////////////////////////////////////////////////////////////////

GLuint textureNum[1];

SDL_Surface* imageFile = IMG_Load(path.c_str());
if (imageFile == 0) 
{
    Logger::LogError("Texture " + path + " failed to load");
    return false;
}

glPixelStorei(GL_UNPACK_ALIGNMENT,4);
glGenTextures(1, textureNum);
glBindTexture(GL_TEXTURE_2D, textureNum[0]);

SDL_PixelFormat format;
format.Aloss = 0;
format.Rloss = 0;
format.Bloss = 0;
format.Gloss = 0;
format.BitsPerPixel = 32;
format.BytesPerPixel = 4; 
format.Rshift = 0; 
format.Gshift = 8; 
format.Bshift = 16; 
format.Ashift = 24; 
format.Rmask = 0xFF; 
format.Gmask = 0xFF00; 
format.Bmask = 0xFF0000; 
format.Amask = 0xFF000000; 
format.colorkey = 0;
format.alpha = 255;
format.palette = nullptr; 

SDL_Surface* image = SDL_ConvertSurface(imageFile, &format, 0);
SDL_FreeSurface(imageFile);
    
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h,
    0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);

SDL_FreeSurface(image);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST); // Can be GL_LINEAR
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_NEAREST);

GLuint texture = textureNum[0]; // final texture number used when binding