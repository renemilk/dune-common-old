// $Id$

#ifndef __DUNE_GRIDINFO_HH__
#define __DUNE_GRIDINFO_HH__

#include<iostream>
#include <common/exceptions.hh>
#include "common/helpertemplates.hh"
#include "grid.hh"
#include "referenceelements.hh"

/** @file
 * @author Peter Bastian
 * @brief Some functions to list information about a grid
 *
 */

namespace Dune
{
  /** 
   * @addtogroup Grid
   *
   * @{ 
   */

  /** @brief A function to print some information about the grid as a whole.
   */
  template<class G>
  void gridinfo (const G& grid, std::string prefix)
  {
	// first we extract the dimensions of the grid  
	const int dim = G::dimension;
	const int dimworld = G::dimensionworld;

	// grid type and dimension
	std::cout << prefix << "===> " << transformToGridName(grid.type())
			  << "(dim=" << dim
			  << ",dimworld=" << dimworld
			  << ")" << std::endl;

	// level information
	for (int level=0; level<=grid.maxlevel(); level++)
	  {
		std::cout << prefix << "level " << level 
				  << ": elements=" << grid.size(level,0)
				  << " vertices=" << grid.size(level,dim)
				  << std::endl;
	  }

	// leaf information
	std::cout << prefix << "leaf:" 
			  << " elements=" << grid.size(0)
			  << " vertices=" << grid.size(dim)
			  << std::endl;

	return;
  }

 
  /** @brief A function to print info about a grid level and its entities
   */
  template<class G>
  void gridlevellist (const G& grid, int level, std::string prefix)
  {
	// first we extract the dimensions of the grid  
	const int dim = G::dimension;
	const int dimworld = G::dimensionworld;

	// type used for coordinates in the grid
	typedef typename G::ctype ct;

	// the grid has an iterator providing the access to
	// all elements (better codim 0 entities) on a grid level
	// Note the use of the typename and template keywords.
	typedef typename G::Traits::template Codim<0>::LevelIterator LevelIterator;

	// print info about this level
	std::cout << prefix << "level=" << level
			  << " dim=" << dim
			  << " geomTypes=(";
	bool first=true;
	for (int i=0; i<grid.levelIndexSet(level).geomTypes(0).size(); i++)
	  {
		if (!first) std::cout << ",";
		std::cout << GeometryName(grid.levelIndexSet(level).geomTypes(0)[i])
				  << "=" << grid.levelIndexSet(level).size(0,grid.levelIndexSet(level).geomTypes(0)[i]);
		first=false;
	  }
	std::cout << ")" << std::endl;

	// print info about each element on given level
	LevelIterator eendit = grid.template lend<0>(level);
	for (LevelIterator it = grid.template lbegin<0>(level); it!=eendit; ++it)
	  {
		std::cout << prefix << "level=" << it->level()
				  << " " << GeometryName(it->geometry().type()) << "[" << dim << "]"
				  << " index=" << grid.levelIndexSet(level).index(*it)
				  << " gid=" << grid.globalIdSet().template id<0>(*it)
				  << " leaf=" << it->isLeaf()
				  << " partition=" << PartitionName(it->partitionType())
				  << " center=(" 
				  << it->geometry().global(Dune::ReferenceElements<ct,dim>::general(it->geometry().type()).position(0,0))
				  << ")"
				  << " first=(" << it->geometry()[0] << ")"
				  << std::endl;
	  }

	return;
  }


  /** @brief A function to print info about a leaf grid and its entities
   */
  template<class G>
  void gridleaflist (const G& grid, std::string prefix)
  {
	// first we extract the dimensions of the grid  
	const int dim = G::dimension;
	const int dimworld = G::dimensionworld;

	// type used for coordinates in the grid
	typedef typename G::ctype ct;

	// the grid has an iterator providing the access to
	// all elements (better codim 0 entities) on a grid level
	// Note the use of the typename and template keywords.
	typedef typename G::Traits::template Codim<0>::LeafIterator LeafIterator;

	// print info about the leaf grid
	std::cout << prefix << "leaf"
			  << " dim=" << dim
			  << " geomTypes=(";
	bool first=true;
	for (int i=0; i<grid.leafIndexSet().geomTypes(0).size(); i++)
	  {
		if (!first) std::cout << ",";
		std::cout << GeometryName(grid.leafIndexSet().geomTypes(0)[i])
				  << "=" << grid.leafIndexSet().size(0,grid.leafIndexSet().geomTypes(0)[i]);
		first=false;
	  }
	std::cout << ")" << std::endl;

	// print info about each element in leaf grid
	LeafIterator eendit = grid.template leafend<0>();
	for (LeafIterator it = grid.template leafbegin<0>(); it!=eendit; ++it)
	  {
		std::cout << prefix << "level=" << it->level()
				  << " " << GeometryName(it->geometry().type()) << "[" << dim << "]"
				  << " index=" << grid.leafIndexSet().index(*it)
				  << " gid=" << grid.globalIdSet().template id<0>(*it)
				  << " leaf=" << it->isLeaf()
				  << " partition=" << PartitionName(it->partitionType())
				  << " center=(" 
				  << it->geometry().global(Dune::ReferenceElements<ct,dim>::general(it->geometry().type()).position(0,0))
				  << ")"
				  << " first=(" << it->geometry()[0] << ")"
				  << std::endl;
	  }

	return;
  }

 
  /** @} */

}
#endif
