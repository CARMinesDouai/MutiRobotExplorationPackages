/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright (C) 2015  Guillaume L. <guillaume.lozenguez@mines-douai.fr>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef MIA_MATRICE_H
#define MIA_MATRICE_H

#include <math.h>
#include <list>
#include <assert.h>

#include <iostream>

namespace mia
{

template<class Obj>
class matrice
{
protected :
    Obj ** a_content;
    int a_line, a_column;

public :
    class line{
    protected:
        matrice<Obj> * a_m;
        int a_iLine;
    public:
        line(matrice<Obj> * a_matrice, int iLine= 0){}
        ~line(){};
    }

/// Constructor destructor :
///-------------------------
    matrice( int size = 0):a_size(size)
    {
        a_item = new Obj[ std::max(1, a_size) ];
    };

    array( int size, const Obj & defaultObj):array(size)
    {
        for(int i=0; i < a_size; i++)
            a_item[i]= defaultObj;
    };

    array( int size, Obj * const tab ):array(size)
    {
        for(int i= 0; i < a_size; i++)
            a_item[i]= tab[i];
    }

    array( const array<Obj> &lobj ):array(lobj.a_size)
    {
        for(int i= 0; i < a_size; i++)
            a_item[i]= lobj.a_item[i];
    };

    array( const std::list<Obj> & listObj ):array(listObj.size())
    {
        typedef typename std::list<Obj>::const_iterator theIterator;
        int i= 0;
        
        theIterator itEnd( listObj.end() );
        for( theIterator it = listObj.begin(); it != itEnd; ++it )
        {
            a_item[i]= *it;
            ++i;
        }
    }

    virtual ~array()
    {
        delete [] a_item;
    };

/// Initialize :
///-------------
    virtual void initialize( int size= 0 )
    {
        assert( size >= 0 );

// delete :
        delete [] a_item;
// new :

        a_size= size;
        a_item= new Obj[ std::max(1, a_size) ];
    }

    virtual void initialize( int size, const Obj & defaultObj )
    {
        initialize(size);
        setAll(defaultObj);
    }

    virtual void initialize( const Obj * tab, int size )
    {
        initialize(size);
        for(int i= 0; i < size; i++)
            a_item[i]= tab[i];
    }

/// Affectation :
///--------------
    virtual const array<Obj> & operator=( const Obj & obj )
    {
        for(int i= 0; i < size(); ++i)
            a_item[i]= obj;

        return (*this);
    }

    virtual const array<Obj> & operator=( const array<Obj> & arrayObj )
    {
        initialize( arrayObj.size() );
        for(int i= 0; i < a_size; ++i)
            a_item[i]= arrayObj[i];

        return (*this);
    }

    virtual const array<Obj> & operator=( const std::list<Obj> & listObj )
    {
        initialize( listObj.size() );

        typedef typename std::list<Obj>::const_iterator theIterator;
        int i= 0;

        for( theIterator it = listObj.begin(); it != listObj.end(); ++it )
        {
            a_item[i]= *it;
            ++i;
        }

        return (*this);
    }

    /// Comparison :
    ///-------------
    /*
    	virtual inline bool operator==(const array<Obj> & other)const
    	{
    		if( size() != other.size() )
    			return false;

    		for(int i= 0; i < size(); ++i )
    			if( !(a_item[i] == other[i] ) )
    				return false;

    		return true;
    	}

    	virtual bool operator!=(const array<Obj> & other)const
    	{
    		return ! operator==(other);
    	}
    */

/// getter and setter :
///--------------------
    virtual inline Obj & operator[](int i)
    {
        assert(i < a_size);
        return a_item[i];
    }

    virtual inline const Obj & operator[](int i)const
    {
        assert(i < a_size);
        return a_item[i];
    }

//	virtual inline const Obj & operator()(int i)const
//	{
//		assert(i < a_size);
//		return a_item[i];
//	}

    virtual Obj get(int i)const
    {
        assert(i < a_size);
        return a_item[i];
    }

    virtual Obj getLast()const
    {
        return a_item[a_size-1];
    }

    virtual Obj getFirst()const
    {
        return a_item[0];
    }

    virtual Obj & last()
    {
        return a_item[a_size-1];
    }

    virtual Obj & first()
    {
        return a_item[0];
    }

    virtual void set(int i,const Obj &o)
    {
        assert(i < a_size);
        a_item[i]= o;
    }

    virtual void setAll(const Obj & defaultObj)
    {
        for(int i= 0; i < a_size; i++)
            a_item[i]= defaultObj;
    }

    virtual void push_backToList( std::list<Obj> & listObj )const
    {
        for( int i= 0; i < size(); ++i )
            listObj.push_back( a_item[i] );
    }


/// Size :
///-------
    virtual bool empty()const
    {
        return a_size == 0;
    }

    virtual int size()const
    {
        return a_size;
    }

    virtual void resize(int size, const Obj& defaultObj= Obj())
    {
        assert( size >= 0 );
        Obj oldItem[size];

// save
        for(int i= 0; i < size; i++)
        {
            if( i < a_size )
                oldItem[i]= a_item[i];
            else
                oldItem[i]= defaultObj;
        }

// new structure :
        initialize(size);

// Copi
        for(int i= 0; i < size; i++)
            a_item[i]= oldItem[i];

// end :
        a_size= size;
    }

/// opration :
///-----------
    virtual void reverse()
    {
        int medium= a_size / 2;
        for( int i= 0; i < medium; ++i )
        {
            Obj obj( a_item[i] );
            a_item[i]= a_item[ (a_size-1)-i ];
            a_item[ (a_size-1)-i ]= obj;
        }
    }

/// not virtual operation :
///------------------------
    int count(const Obj & obj)const
    {
        int ct= 0;
        for( int i= 0; i < size(); ++i )
            if( a_item[i] == obj )
                ++ct;
        return ct;
    }

    void setIdentity()
    {
        for( int i= 0; i < size(); ++i )
            a_item[i]= i;
    }

    /// Stream :
    ///---------
    friend std::ostream & operator<< ( std::ostream & os, const array<Obj> & ar )
    {
        os << "[ ";
        for( int i= 0; i < ar.size(); ++i )
            os << ar[i] << " ";

        os << "]";

        return os;
    }

};

};

#endif // MIA_ARRAY_H
