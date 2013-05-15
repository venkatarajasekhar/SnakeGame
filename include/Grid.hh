//
// Map.hh for nibbler in /home/moreau_c//work/nibbler
// 
// Made by christopher moreau
// Login   <moreau_c@epitech.net>
// 
// Started on  Wed Mar  2 14:09:47 2011 christopher moreau
// Last update Sun Mar 20 21:03:41 2011 christopher moreau
//

#ifndef		GRID_HH_
# define	GRID_HH_

# include	<list>
# include	<vector>



namespace Core
{
  typedef std::pair<int, int>	Coord;
  typedef std::list<Coord>	CoordList;
  class				Snake;
  class				Bonus;
  class				Food;
}

class		Grid
{
public:
  Grid();
  Grid(unsigned int, unsigned int, Core::Snake const &);
  ~Grid();
  Grid(Grid const&);
  Grid& operator=(Grid const&);

  void				setMap(unsigned int, unsigned int, Game::BoxType);
  Game::BoxType			getMap(unsigned int, unsigned int) const;

  int				accessMap(unsigned int, unsigned int) const;

  void				snakeToMap(Core::Coord const &, Core::Coord const &);
  void				foodToMap(Core::Coord const &);
  void				bonusToMap(Core::Bonus &, Core::Food &);

  unsigned int			getSizeX() const;
  unsigned int			getSizeY() const;

private:
  unsigned int			_size_x;
  unsigned int			_size_y;

  std::vector<Game::BoxType>	_map;
};

#endif		// !GRID_HH_
