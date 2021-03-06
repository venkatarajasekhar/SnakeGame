
#include "Excp.hh"
#include "OpenglWindow.hh"

extern "C"
{
  IWindow *getWindow()
  {
    return (new OpenglWindow());
  }
}

OpenglWindow::OpenglWindow()
{
  this->_keyTab[SDLK_UP] = Game::Up;
  this->_keyTab[SDLK_DOWN] = Game::Down;
  this->_keyTab[SDLK_RIGHT] = Game::Left;
  this->_keyTab[SDLK_LEFT] = Game::Right;
  this->_keyTab[SDLK_ESCAPE] = Game::Esc;
}

OpenglWindow::~OpenglWindow()
{
  TTF_Quit();
  SDL_Quit();
}

int			OpenglWindow::GetEvent()
{
  SDL_Event event;

  while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_KEYDOWN)
	return this->_keyTab[event.key.keysym.sym];
      else if (event.type == SDL_QUIT)
	return Game::Esc;
    }
  return (0);
}

int			OpenglWindow::Display(int score, int level)

{
  (void)score;
  (void)level;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  this->drawMap();

  glFlush();
  SDL_GL_SwapBuffers();
  return (0);
}

int			OpenglWindow::createImage()
{
  return 0;
}

void			OpenglWindow::drawMap()
{
  for (unsigned int i = 0; i < this->_grid->getSizeY(); ++i)
    {
      for (unsigned int j = 0; j < this->_grid->getSizeX(); ++j)
        {
          if (this->_grid->getMap(j, i) == Game::Border)
	    this->drawFullBox(j, i, 0);
          else if (this->_grid->getMap(j, i) == Game::Snake)
	    this->drawSnake(j, i, 0);
	  else if (this->_grid->getMap(j, i) == Game::Empty)
	    this->drawEmptyBox(j, i, 0);
	  else if (this->_grid->getMap(j, i) == Game::Food)
	    this->drawFood(j, i, 0, this->foodTexture);
	  else if (this->_grid->getMap(j, i) == Game::Bonus)
	    this->drawFood(j, i, 0, this->bonusTexture);
        }
    }
}

void			OpenglWindow::drawFood(int x, int y, int z, GLuint texture) const
{
  static int		rot = 0;

  glPushMatrix();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslated(x, y, z);
  glBindTexture(GL_TEXTURE_2D, this->floor);

  glBegin(GL_QUADS);
  glTexCoord2d(0,0);  glVertex3d(0.5,-0.5,-0.5);
  glTexCoord2d(1,0);  glVertex3d(0.5,0.5,-0.5);
  glTexCoord2d(1,1);  glVertex3d(-0.5,0.5,-0.5);
  glTexCoord2d(0,1);  glVertex3d(-0.5,-0.5,-0.5);
  glEnd();

  rot += 10;
  if (rot == 360)
    rot = 0;
  glRotated(rot, 0, 0, 1);

  GLUquadric* params = gluNewQuadric();

  glBindTexture(GL_TEXTURE_2D, texture);
  if (texture == this->bonusTexture)
    gluQuadricDrawStyle(params, GLU_LINE);
  else
    gluQuadricDrawStyle(params, GLU_FILL);
  gluQuadricTexture(params, GL_TRUE);
  gluSphere(params, 0.70, 20, 20);
  gluDeleteQuadric(params);

  glPopMatrix();
}

void			OpenglWindow::drawSnake(int x, int y, int z) const
{
  glPushMatrix();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslated(x, y, z);
  glBindTexture(GL_TEXTURE_2D, this->floor);

  glBegin(GL_QUADS);
  glTexCoord2d(0,0);  glVertex3d(0.5,-0.5,-0.5);
  glTexCoord2d(1,0);  glVertex3d(0.5,0.5,-0.5);
  glTexCoord2d(1,1);  glVertex3d(-0.5,0.5,-0.5);
  glTexCoord2d(0,1);  glVertex3d(-0.5,-0.5,-0.5);
  glEnd();

  GLUquadric* params = gluNewQuadric();

  glBindTexture(GL_TEXTURE_2D, this->snakeTexture);
  gluQuadricDrawStyle(params, GLU_FILL);
  gluQuadricTexture(params, GL_TRUE);
  gluSphere(params, 0.60, 20, 20);
  gluDeleteQuadric(params);

  glPopMatrix();
}

void			OpenglWindow::drawEmptyBox(int x, int y, int z) const
{
  glPushMatrix();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslated(x, y, z);
  glBindTexture(GL_TEXTURE_2D, this->floor);

  glBegin(GL_QUADS);
  glTexCoord2d(0,0);  glVertex3d(0.5,-0.5,-0.5);
  glTexCoord2d(1,0);  glVertex3d(0.5,0.5,-0.5);
  glTexCoord2d(1,1);  glVertex3d(-0.5,0.5,-0.5);
  glTexCoord2d(0,1);  glVertex3d(-0.5,-0.5,-0.5);
  glEnd();

  glPopMatrix();
}

void			OpenglWindow::drawFullBox(int x, int y, int z) const
{
  glPushMatrix();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslated(x, y, z);
  glBindTexture(GL_TEXTURE_2D, this->fullBoxTexture);

  for (int i = 0; i < 4; i++)
    {
      glBegin(GL_QUADS);
      glTexCoord2d(0, 1);
      glVertex3d(0.5, 0.5, 0.5);
      glTexCoord2d(0, 0);
      glVertex3d(0.5, 0.5, -0.5);
      glTexCoord2d(1, 0);
      glVertex3d(-0.5, 0.5, -0.5);
      glTexCoord2d(1, 1);
      glVertex3d(-0.5, 0.5, 0.5);
      glEnd();
      glRotated(90, 0, 0, 1);
    }
  glBegin(GL_QUADS);
  glTexCoord2d(0, 0);
  glVertex3d(0.5, -0.5, 0.5);
  glTexCoord2d(1, 0);
  glVertex3d(0.5, 0.5, 0.5);
  glTexCoord2d(1, 1);
  glVertex3d(-0.5, 0.5, 0.5);
  glTexCoord2d(0, 1);
  glVertex3d(-0.5,-0.5,0.5);
  glEnd();
  glPopMatrix();
}

SDL_Surface		*OpenglWindow::flipSurface(SDL_Surface * surface)
{
  int			pitch;
  SDL_Surface		*flpSurface;

  flpSurface = SDL_CreateRGBSurface(SDL_SWSURFACE,
				    surface->w,surface->h,
				    surface->format->BitsPerPixel,
				    surface->format->Rmask,
				    surface->format->Gmask,
				    surface->format->Bmask,
				    surface->format->Amask);
  SDL_LockSurface(surface);
  SDL_LockSurface(flpSurface);
  pitch = surface->pitch;
  for (int cur_line = 0; cur_line < surface->h; cur_line ++)
    {
      memcpy(&((unsigned char*)flpSurface->pixels)[cur_line * pitch],
	     &((unsigned char*)surface->pixels)[(surface->h - 1  -
						 cur_line)*pitch],
	     pitch);
    }
  SDL_UnlockSurface(flpSurface);
  SDL_UnlockSurface(surface);
  return flpSurface;
}

GLuint			OpenglWindow::loadTexture(const char * filename)
{
  GLuint		idTexture;
  SDL_Surface		*picture_surface = NULL;
  SDL_Surface		*gl_surface = NULL;
  SDL_Surface		*gl_fliped_surface = NULL;
  SDL_PixelFormat	format;

  picture_surface = IMG_Load(filename);
  if (picture_surface == NULL)
    return 0;
  format = *(picture_surface->format);
  format.BitsPerPixel = 32;
  format.BytesPerPixel = 4;
  format.Rmask = 0xff;
  format.Gmask = 0xff00;
  format.Bmask = 0xff0000;
  format.Amask = 0xff000000;
  gl_surface = SDL_ConvertSurface(picture_surface, &format, SDL_SWSURFACE);
  gl_fliped_surface = flipSurface(gl_surface);
  glGenTextures(1, &idTexture);
  glBindTexture(GL_TEXTURE_2D, idTexture);
  gluBuild2DMipmaps(GL_TEXTURE_2D, 4, gl_fliped_surface->w,
		    gl_fliped_surface->h, GL_RGBA,GL_UNSIGNED_BYTE,
		    gl_fliped_surface->pixels);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,
		  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  SDL_FreeSurface(gl_fliped_surface);
  SDL_FreeSurface(gl_surface);
  SDL_FreeSurface(picture_surface);
  return (idTexture);
}

int			OpenglWindow::CreateWindow(Grid const *g, float box_x, float box_y) throw (std::exception&)
{
  this->_grid = g;
  this->_box_x = box_x;
  this->_box_y = box_y;

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    throw (excp("SDL init failed"));
  if (SDL_SetVideoMode(800, 600, 32, SDL_OPENGL) == NULL)
    throw (excp("SDL settings failed"));
  SDL_WM_SetCaption("Nibbler - lib Opengl - epitech 2014", NULL);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70, 800.0 / 600.0, 1, 1000);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);

  this->fullBoxTexture = this->loadTexture("./img/wall.jpg");
  this->floor = this->loadTexture("./img/floor.jpg");
  this->snakeTexture = this->loadTexture("./img/snake_gl.jpg");
  this->foodTexture = this->loadTexture("./img/food_gl.jpg");
  this->bonusTexture = this->loadTexture("./img/bonus.png");

  gluLookAt(this->_grid->getSizeX() / 2.0,
	    this->_grid->getSizeY(),
	    (this->_grid->getSizeY() > this->_grid->getSizeX() ?
	     this->_grid->getSizeY() : this->_grid->getSizeX()) / 3.0 * 2.0,
	    this->_grid->getSizeX() / 2.0, this->_grid->getSizeY() / 2.0, 0,
	    0, 0, 1);
  return (0);
}
