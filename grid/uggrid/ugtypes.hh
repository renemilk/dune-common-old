#ifndef DUNE_UGTYPES_HH
#define DUNE_UGTYPES_HH

/** \file
 * \brief Encapsulates a few types from UG
 */

namespace UG2d {
    struct multigrid;
    struct domain;
    struct grid;

    union element;
    struct node;
    struct edge;
};

namespace UG3d {
    struct multigrid;
    struct domain;
    struct grid;

    union element;
    struct node;
    struct edge;
};


namespace Dune {

template <int dim>
class UGTypes
{
public:
    typedef void MultiGridType;

    typedef void DomainType;
};

template <>
class UGTypes<2>
{
public:
    typedef UG2d::multigrid MultiGridType;

    typedef UG2d::grid GridType;

    typedef UG2d::domain DomainType;
};

template <>
class UGTypes<3>
{
public:
    typedef UG3d::multigrid MultiGridType;

    typedef UG3d::grid GridType;

    typedef UG3d::domain DomainType;
};



    /*****************************************************************/
    /*****************************************************************/
    /*****************************************************************/
    /*****************************************************************/


template <int codim, int dim>
class TargetType
{
public:
    typedef void T;

};

template <>
class TargetType<0,3>
{
public:
    typedef UG3d::element T;
};

template <>
class TargetType<2,3>
{
public:
    typedef UG3d::edge T;
};

template <>
class TargetType<3,3>
{
public:
    typedef UG3d::node T;
};

template <>
class TargetType<0,2>
{
public:
    typedef UG2d::element T;
};

template <>
class TargetType<1,2>
{
public:
    typedef UG2d::edge T;
};

template <>
class TargetType<2,2>
{
public:
    typedef UG2d::node T;
};

} // end namespace Dune

#endif
