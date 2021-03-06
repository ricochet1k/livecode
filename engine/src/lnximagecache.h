/* Copyright (C) 2003-2013 Runtime Revolution Ltd.

This file is part of LiveCode.

LiveCode is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License v3 as published by the Free
Software Foundation.

LiveCode is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with LiveCode.  If not see <http://www.gnu.org/licenses/>.  */

#ifndef XIMAGECACHE_H
#define XIMAGECACHE_H

#include <Xft.h>

#include "typedefs.h"
#include "lnxgtkthemedrawing.h"


class MCXImageCacheNode
{
private:
		
	MCBitmap	*cached_image ;
	Boolean		isText ;

		
	// Elements that make a rendered image "unique"
	GtkThemeWidgetType 	moztype ;
	GtkWidgetState		*state ;	// We only compare _some_ of the state flags.
	uint4				flags ;
	
	
	// Elements that make a text "Image" unique
	XftFont 	* font ;
	char 		* text_string ;
	uint4		text_string_length;
	uint4		fgColor ;			// Just storing the pixel value from the XftColor structure.
	uint4		bgColor ;
	
		
public:
	uint4  		total_pixels ;

	MCXImageCacheNode 	* next_ptr ;
	MCXImageCacheNode 	* prev_ptr ;
	

	MCXImageCacheNode(MCBitmap *p_bitmap, GtkThemeWidgetType p_moztype, GtkWidgetState *p_state, uint4 p_flags );
	MCXImageCacheNode(MCBitmap *p_bitmap, XftFont *p_font, const char *p_string, uint4 p_string_length, uint4 p_fgColor, uint4 p_bgColor ) ;
	~MCXImageCacheNode();
	
	Boolean matches ( uint4 p_width, uint4 p_height, GtkThemeWidgetType p_moztype, GtkWidgetState *p_state, uint4 p_flags ) ;
	Boolean matches ( XftFont *p_font, uint4 p_width, uint4 p_height, const char *p_string, uint4 p_string_length, uint4 p_fgColor, uint4 p_bgColor ) ;

	MCBitmap * get_cached_image (void);

	void add(MCXImageCacheNode *node) ;
	
	
	MCXImageCacheNode *next()
	{
		return ( next_ptr ) ;
	}
	
	MCXImageCacheNode *prev()
	{
		return (prev_ptr);
	}

};



class MCXImageCache
{
private:
	MCXImageCacheNode * cache_head ;
	MCXImageCacheNode * cache_tail ;
	uint4 		   cache_total_pixels ;
	
public:
	
	MCXImageCache() ;
	~MCXImageCache() ;
	
	MCBitmap 		* get_from_cache ( MCXImageCacheNode * p_node )  ;
	void 			destroy_image_cache (void);
	void			adjust_cache_size (MCBitmap * p_bitmap );
	bool 			too_big_to_cache ( MCBitmap * p_bitmap ) ;


	// These need to be overridden for each type of object we want to cache.
	bool 				add_to_cache (MCBitmap * p_bitmap, XftFont *p_font, const char *p_string, uint4 p_string_length, uint4 p_fgColor, uint4 p_bgColor   );
	bool 				add_to_cache (MCBitmap * p_bitmap, MCThemeDrawInfo& p_info );
	MCXImageCacheNode 	*find_cached_image ( uint4 p_width, uint4 p_height, XftFont *p_font, const char *p_string, uint4 p_string_length, uint4 p_fgColor, uint4 p_bgColor ) ;
	MCXImageCacheNode 	*find_cached_image ( uint4 p_width, uint4 p_height, GtkThemeWidgetType p_moztype, GtkWidgetState *p_state, uint4 p_flags ) ;
	
	void				cache_size(void);
} ;




#endif 

